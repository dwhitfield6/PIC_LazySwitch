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
#include "ADC.h"

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
            TMR_ResetTimer0();
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
                SYS_ActivityTimerReset();
                if(RF_DataPlace < RFBUFFERSIZE)
                {
                    RF_DataTiming[RF_DataPlace] = RFtemp;
                    RF_DataPlace++;
                    if(RF_DataPlace >= RF_CodeSize)
                    {
                        if(!RF_Data)
                        {
                            RF_Data = RF_CheckCode();
                        }
                        TMR_Timer0(OFF);
                        RF_ResetData();
                    }
                }
            }
        }
        INTCON3bits.INT1IF = 0; // Clear rising edge Flag
        INTCON3bits.INT2IF = 0; // Clear falling edge Flag
    }
    else if(INTCONbits.TMR0IF)
    {
        /* RF timeout occurred */
        TMR_Timer0(OFF);
        TMR_ResetTimer0();
        RF_ResetData();
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
    unsigned char IR_state;
    unsigned int IRtemp = 0;
    
    if(INTCONbits.RBIF)
    {
        /* interrupt on change pin 
         * This means there was a change on the button pin or IR pin 
         */
        
        button_state = BUT_ReadButton();
        IR_state = IR_ReadReceiver();
        SYS_ActivityTimerReset(); 
        if(ButtonChange)
        {
            /* the push button is the source of the interrupt */
            TMR_Timer2(OFF);           
            if(button_state)
            {
                /* Button is pressed */
                if(System_State == RUN)
                {
                    Timer2Use = BUTTONPRESS;
                    TMR_Timer2Start(PRESSCOUNT);
                }
                else
                {
                    Timer2Use = MOTORTIMING;
                    TMR_Timer2Start(WAITCOUNT);
                }
            }
            else
            {
                if(System_State != PROGRAM)
                {
                    /* The button was let go before a timeout */
                    Button_Data = TRUE;
                    Timer2Use = MOTORTIMING;
                    TMR_Timer2Start(WAITCOUNT);
                }
                else
                {
                    Timer2Use = BUTTONRELEASE;
                    TMR_Timer2Start(PROGRAMTIMEOUT);
                }
            }
            ButtonChange = 0;
        }
        else if(IRChange)
        {
            /* the IR receiver is the source of the interrupt */
            if(!TMR_Timer1Status())
            {
                /* Turn on timer 1 */
                TMR_Timer1Start();
            }
            else
            {
                IRtemp = TMR1L;
                IRtemp += (unsigned int)TMR1H << 8;
                TMR_ResetTimer1();
                if(!IRStarted)
                {
                    if(System_State == RUN)
                    {
                        if(IRtemp >= IR_SyncLow && IRtemp <= IR_SyncHigh)
                        {
                            RF_DataInt(OFF);
                            IRStarted = TRUE;
                        }
                    }
                    else
                    {
                        if(IRtemp >= IR_SYNCLOWBOUND && IRtemp <= IR_SYNCHIGHBOUND)
                        {
                            RF_DataInt(OFF);
                            IRStarted = TRUE;
                        }
                    }
                }
                if(IRStarted)
                {
                    RF_Disable(); // disable the RF receive if IR receive is already starting
                    if(IR_DataPlace < IRBUFFERSIZE)
                    {
                        IR_DataTiming[IR_DataPlace] = IRtemp;
                        IR_DataPlace++;
                        if(System_State == RUN)
                        {
                            if(IR_DataPlace >= IR_CodeSize)
                            {
                                PIR1bits.TMR1IF = 1; // set timer 1 interrupt
                            }
                        }
                    }
                }
            }
            IRChange = 0;
        }
        else
        {
            /* Unknown pin change interrupt */
            Nop();           
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
            SYS_ActivityTimerReset();
            Timer2PostCount++;
        }
        PIR1bits.TMR2IF = 0; // clear timer 2 flag
    }
    else if(PIR1bits.ADIF)
    {
        /* ADC interrupt */
        ADC_CalculateVoltage();
        PIR1bits.ADIF = 0; // clear the ADC flag
    }
    else if(PIR1bits.TMR1IF)
    {
        /* IR timeout occurred */
        BUT_IR_PinChangeInt(OFF);
        TMR_Timer1(OFF);
        SYS_ActivityTimerReset();
        BUT_ReadButton();
        IR_ReadReceiver();
        INTCONbits.RBIF = 0; //clear the interrupt on change flag
        if(System_State == PROGRAM)
        {
            if(IR_DataPlace >= IR_EDGENUM)
            {
                /* Valid IR code to program */
                IR_Data = IR_CheckCode();
            }
        }
        else
        {
            if(!IR_Data)
            {
                if(IR_DataPlace >= IR_CodeSize)
                {
                    IR_Data = IR_CheckCode();
                }
            }
        }
        TMR_ResetTimer1();
        IR_ResetData();
        INTCON3bits.INT1IF = 0; // Clear rising edge Flag
        INTCON3bits.INT2IF = 0; // Clear falling edge Flag
        RF_DataInt(ON);
        BUT_IR_PinChangeInt(ON);
        PIR1bits.TMR1IF = 0; // clear timer 1 flag
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