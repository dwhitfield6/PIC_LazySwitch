/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 08/13/15     2.0_DW0a    Initial project make.
 *                          Derived from project 'Catalyst_RPI_daughter'.
/******************************************************************************/

/******************************************************************************/
/*Files to Include                                                            */
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
#include "BUTTON.h"
#include "IR.h"
#include "RF.h"
#include "TIMERS.h"
#include "SYSTEM.h"
#include "MISC.h"

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/******************************************************************************/
/* High priority Interrupt routine                                            */
/******************************************************************************/
void interrupt high_isr(void)
{
    unsigned int RFtemp = 0;
    
    if(INTCON3bits.INT1IF || INTCON3bits.INT2IF)
    {
        /* RF data interrupt */
        if(!TMR_Timer0Status())
        {
            /* Turn on timer 0 */
            TMR_Timer0Start();
        }
        else
        {
            RFtemp = TMR0L;
            RFtemp += (unsigned int)TMR0H << 8;
            if(!RFStarted)
            {
                if(System_State == RUN)
                {
                    if(RFtemp >= RF_SyncLow && RFtemp <= RF_SyncHigh)
                    {
                        RFStarted = TRUE;
                    }
                }
                else
                {
                    if(RFtemp >= RF_PROGRAMSYNCLOW && RFtemp <= RF_PROGRAMSYNCHIGH)
                    {
                        RFStarted = TRUE;
                    }
                }
            }
            if(RFStarted)
            {
                if(RF_DataPlace < RFBUFFERSIZE)
                {
                    RF_DataTiming[RF_DataPlace] = RFtemp;
                    RF_DataPlace++;
                    if(RF_DataPlace >= RF_CodeSize)
                    {
                        RF_Data = RF_CheckCode();
                        TMR_Timer0(OFF);
                        RF_ResetRFData();
                    }
                }
                else
                {
                    /* Too many edges */
                    TMR_Timer0(OFF);
                    RF_ResetRFData();
                }
            }
            TMR_ResetTimer0();
        }
        INTCON3bits.INT1IF = 0; // Clear Flag
        INTCON3bits.INT2IF = 0; // Clear Flag
    }
    else if(INTCONbits.TMR0IF)
    {
        /* and RF timeout occurred */
        TMR_Timer0(OFF);
        TMR_ResetTimer0();
        RF_ResetRFData();
        INTCONbits.TMR0IF = 0;
    }
    else
    {
        /* Unknown interrupt */
        Nop();
    }
}

/******************************************************************************/
/* Low priority Interrupt routine                                             */
/******************************************************************************/
void low_priority interrupt low_isr(void)
{
    unsigned char button_state;
    
    if(INTCONbits.RBIF)
    {
        /* interrupt on change pin 
         * This means there was a change on the button pin or IR pin 
         */
        
        button_state = BUT_ReadButton();        
        if(ButtonChange)
        {
            TMR_Timer2(OFF);
            
            /* the push button is the source of the interrupt */
            if(button_state)
            {
                /* Button is pressed */
                if(System_State == RUN)
                {
                    Timer2Use = BUTTONPRESS;
                    TMR_Timer2Start(PRESSCOUNT);
                }
            }
            else
            {
                if(System_State != PROGRAM)
                {
                    /* The button was let go before a timeout */
                    Button_Data = TRUE;
                }
                else
                {
                    Timer2Use = BUTTONRELEASE;
                    TMR_Timer2Start(PROGRAMTIMEOUT);
                }
            }
            ButtonChange = 0;
        }
        else
        {
            IR_ReadReceiver();
        }
        INTCONbits.RBIF = 0; //clear the interrupt on change flag
    }
    else if(PIR1bits.TMR2IF)
    {
        /* timer 2 interrupt */
        if(Timer2PostCount >= Timer2Post)
        {
            TMR_Timer2(OFF);
            if(Timer2Use == BUTTONPRESS)
            {
                /* The button was held down for longer than the timeout */
                System_State = PROGRAM; 
                System_State_Change = TRUE;
            }
            else if(Timer2Use == BUTTONRELEASE)
            {
                System_State = RUN; 
                System_State_Change = TRUE;
            }
        }
        else
        {
            Timer2PostCount++;
        }
        PIR1bits.TMR2IF = 0; // clear timer 2 flag
    }
    else
    {
        /* unknown interrupt*/
        Nop();
    }
}
/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/