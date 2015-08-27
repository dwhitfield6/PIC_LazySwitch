/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 08/26/15     2.0_DW0a    Initial project make.
 *                          Derived from project 'Catalyst_RPI_daughter'.
 *                          Added timer functionality for push button.
 *                          Move the motor in alternating directions for each
 *                            button press.
 *                          Improved the button functionality.
 *                          Added RF capability and a default code to check
 *                            against.
/******************************************************************************/

/******************************************************************************/
/* Contains main function.
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


#include "SYSTEM.h"
#include "USER.h"
#include "MISC.h"
#include "RF.h"
#include "IR.h"
#include "BUTTON.h"
#include "MOTOR.h"

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int main (void)
{   
    /* Initialize */
    SYS_ConfigureOscillator();
    Init_App();
    Init_System();

    if(RF_Saved == EMPTY)
    {
        TMR_LoadDefaultCode();
        MSC_BlinkLED(15);
    }
    else
    {
        MSC_BlinkLED(4);
    }
    MSC_RedLEDOFF();
    
    while(1)
    {
        if(System_State == RUN)
        {
            /* The system is in normal run mode */
            if(System_State_Change)
            {
                /* System state just changed */
                MSC_RedLEDOFF();
                if(RF_Saved == NEW)
                {
                    MSC_BlinkLED(4);
                    RF_Saved = OLD;
                }
                System_State_Change = FALSE;
            }
            if(RF_Data || IR_Data || Button_Data)
            {
                MSC_RedLEDON();
                MTR_Rotate();
                RF_Data = FALSE;
                IR_Data = FALSE;
                Button_Data = FALSE;
                MSC_RedLEDOFF();
            }
        }
        else if(System_State == PROGRAM)
        {
            /* The system is in program mode */
            MSC_DelayMS(25);
            MSC_RedLEDTOGGLE();
            if(RF_Data)
            {
                /* RF code needs to be saved */
                RF_Data = FALSE;
                System_State = RUN;
                System_State_Change = TRUE;
            }
                       
        }   
    }
}
/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
