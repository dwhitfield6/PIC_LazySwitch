/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 08/24/15     2.0_DW0a    Initial project make.
/******************************************************************************/

/******************************************************************************/
/* Contains functions for the RF transmitter.
 *
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <stdio.h>       /* For true/false definition */
#include <string.h>
#endif

#include "USER.h"
#include "RF.h"
#include "MISC.h"
#include "TIMERS.h"
#include "FLASH.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
volatile unsigned char RF_Data = FALSE;
unsigned int RF_DataTiming[RFBUFFERSIZE];
unsigned char RF_DataPlace = 0;
unsigned char RFStarted = FALSE;
unsigned int RF_SyncLow  = 0;
unsigned int RF_SyncHigh = 0;
unsigned char RF_Saved = OLD;
unsigned char RF_CodeSize = 0;
double Rail_RSSI;

/******************************************************************************/
/* Inline Functions
/******************************************************************************/

/******************************************************************************/
/* Functions
/******************************************************************************/

/******************************************************************************/
/* InitRF
 *
 * The function initializes the RF transmitter.
/******************************************************************************/
void InitRF(void)
{
#ifdef RF_CAPABLE
    RF_Receiver(ON);
    RF_SetBandwidth(FAST);
    MSC_CleanBufferInt(&RF_DataTiming,RFBUFFERSIZE);
    RF_SetSquelch(OFF);      // Low sensitivity
    INTCON3bits.INT1P = 1;  // High priority interrupt
    INTCON3bits.INT2P = 1;  // High priority interrupt
    INTCON2bits.INTEDG1 = 1; // Rising edge
    INTCON2bits.INTEDG2 = 0; // Falling edge
    RF_DataInt(ON);
#else
    RF_Receiver(OFF);
#endif
}

/******************************************************************************/
/* RF_Disable
 *
 * The function disables the RF receiving interrupts.
/******************************************************************************/
void RF_Disable(void)
{
    RF_DataInt(OFF);
    TMR_Timer0Int(OFF);
    TMR_Timer0(OFF);
}
/******************************************************************************/
/* RF_Enable
 *
 * The function enables the RF receiving interrupts.
/******************************************************************************/
void RF_Enable(void)
{
    INTCON3bits.INT1IF = 0; // Clear rising edge Flag
    INTCON3bits.INT2IF = 0; // Clear falling edge Flag
    INTCONbits.TMR0IF = 0;
    RF_DataInt(ON);
    TMR_Timer0Int(ON);
}


/******************************************************************************/
/* RF_ResetData
 *
 * The function resets the RF buffer.
/******************************************************************************/
void RF_ResetData(void)
{
    RF_DataPlace = 0;
    RFStarted = FALSE;
}

/******************************************************************************/
/* RF_LoadCode
 *
 * The function loads the default code.
/******************************************************************************/
void RF_LoadCode(void)
{   
    double Low = 0.0;
    double High = 0.0;
    
    Low = (double)RF_SavedTiming[0] * (1.0 - RF_TOLERANCESMALL);
    High = (double)RF_SavedTiming[0] * (1.0 + RF_TOLERANCESMALL);
    
    if(Low < RF_PROGRAMSYNCLOW)
    {
        Low = RF_PROGRAMSYNCLOW;
    }
    if(High > RF_PROGRAMSYNCHIGH)
    {
        High = RF_PROGRAMSYNCHIGH;
    }
    
    RF_SyncLow = (unsigned int) Low;
    RF_SyncHigh = (unsigned int) High;
    
    RF_CodeSize = RF_CalculateCodesize();
}

/******************************************************************************/
/* RF_CalculateCodesize
 *
 * The function calculates the code size of the saved RF code.
/******************************************************************************/
unsigned char RF_CalculateCodesize(void)
{   
    unsigned char i;
    
    for(i=0; i<RFBUFFERSIZE;i++)
    {
        if(RF_SavedTiming[i] == 0)
        {
            return i;
        }
    }
    return RFBUFFERSIZE;
}

/******************************************************************************/
/* RF_CheckCode
 *
 * The function checks the current RF buffer against the stored code to see if
 *  it is a match.
/******************************************************************************/
unsigned char RF_CheckCode(void)
{   
    unsigned char i;
    double Low = 0.0;
    double High = 0.0;
    
    if(System_State == RUN)
    {
        for(i=0; i<RF_CodeSize;i++)
        {
            if(i == 0)
            {
                Low = (double)RF_SavedTiming[i] * (1.0 - RF_TOLERANCESMALL);
                High = (double)RF_SavedTiming[i] * (1.0 + RF_TOLERANCESMALL);
            }
            else
            {
                Low = (double)RF_SavedTiming[i] * (1.0 - RF_TOLERANCELARGE);
                High = (double)RF_SavedTiming[i] * (1.0 + RF_TOLERANCELARGE);
            }

            if((double)RF_DataTiming[i] < Low || (double)RF_DataTiming[i] > High )
            {
                return FALSE;
            }
        }
        return TRUE;
    }
    else
    {
        if(RF_DataPlace >= RF_EDGENUM)
        {
            for(i=0;i<RF_DataPlace;i++)
            {
                if(RF_DataTiming[i] < 5)
                {
                    /* There are some invalid values in this code */
                    return FALSE;
                }
            }
            
            for(i=RF_DataPlace;i<RFBUFFERSIZE;i++)
            {
                /* clear unused buffer */
                RF_DataTiming[i] = 0;
            }
            
            /* The RF signal is valid for program */
            RF_Saved = NEW;
            Flash_Status = FSH_Write_IR_RF();
            if(Flash_Status)
            {
                RF_LoadCode();
            }
            System_State = RUN;
        }
        return FALSE;
    }
}

/******************************************************************************/
/* RF_ReadReceiver
 *
 * The function reads the RF receiver.
/******************************************************************************/
unsigned char RF_ReadReceiver(void)
{
    if(PORTB & RF_DATA1)
    {
        return 0;
    }
    return 1;
}

/******************************************************************************/
/* RF_DataInt
 *
 * The function controls the RF data interrupts.
/******************************************************************************/
void RF_DataInt(unsigned char state)
{
#ifdef RF_CAPABLE
    if(state)
    {
        /* Enable falling edge and rising edge interrupts */
        INTCON3bits.INT1E = 1;
        INTCON3bits.INT2E = 1;
    }
    else
    {
        /* Disable falling edge and rising edge interrupts */
        INTCON3bits.INT1E = 0;
        INTCON3bits.INT2E = 0;
    }
#else
    INTCON3bits.INT1E = 0;
    INTCON3bits.INT2E = 0;
#endif
}


/******************************************************************************/
/* RF_Receiver
 *
 * The function controls the RF receiver state.
/******************************************************************************/
void RF_Receiver(unsigned char state)
{
    if(!state)
    {
        /* Shutdown the RF receiver */
        LATA |= RF_SHDN;
    }
    else
    {
        /* Turn on the RF receiver */
        LATA &= ~RF_SHDN;
    }
}

/******************************************************************************/
/* RF_SetBandwidth
 *
 * The function controls the demodulator filter bandwidth.
/******************************************************************************/
void RF_SetBandwidth(unsigned char band)
{
    if(band == VERYSLOW)
    {
        /* Optimized for 1.8 kbps Bit rate */
        LATC &= ~RF_SEL0;
        LATC &= ~RF_SEL1;
    }
    else if(band == SLOW)
    {
        /* Optimized for 3.6 kbps Bit rate */
        LATC |= RF_SEL0;
        LATC &= ~RF_SEL1;
    }
    else if(band == FAST)
    {
        /* Optimized for 7.2 kbps Bit rate */
        LATC &= ~RF_SEL0;
        LATC |= RF_SEL1;
    }
    else
    {
        /* Optimized for 14.4 kbps Bit rate */
        LATC |= RF_SEL0;
        LATC |= RF_SEL1;
    }
}

/******************************************************************************/
/* RF_SetSquelch
 *
 * The function controls the squelch pin in the RF receiver. When enabled,
 *  the random received activity is decreased.
/******************************************************************************/
void RF_SetSquelch(unsigned char state)
{
    if(!state)
    {
        /* Shutdown the RF receiver */
        LATA |= RF_Squelch;
    }
    else
    {
        /* Turn on the RF receiver */
        LATA &= ~RF_Squelch;
    }
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/