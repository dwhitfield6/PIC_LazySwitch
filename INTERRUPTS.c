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

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/******************************************************************************/
/* High priority Interrupt routine                                            */
/******************************************************************************/
void interrupt high_isr(void)
{
    
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
            /* the push button is the source of the interrupt */
            if(button_state)
            {
                /* Button is pressed */
                if(ButtonTimer == FINISHED)
                {
                    Button_Data = TRUE;
                }
                ButtonTimer = NOTFINISHED;
                if(TMR_Timer2Free())
                {
                    Timer2Use = BUTTON;
                    TMR_Timer2Start(PRESSCOUNT);                
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
            if(Timer2Use == BUTTON)
            {
                ButtonTimer = FINISHED;
                Timer2Use = 0; // Free the timer
            }
            else
            {
                Nop();
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