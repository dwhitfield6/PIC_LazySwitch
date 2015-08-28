/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 08/27/15     2.0a_DW0a   Added rail voltage monitoring.
 *                          Added IR functionality and IR default code.
 *                          Increased clock from 8MHz oto 32MHz. (This was a
 *                            bug in the previous versions as the system was
 *                            was always supposed to be at 32MHz.)
 * 08/27/15     2.0a        Version change only. Tagged version!
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
#include "ADC.h"
#include "LDO.h"

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

    /* load RF code */
    if(RF_Saved == EMPTY)
    {
        RF_LoadDefaultCode();
        MSC_BlinkLED(10);
    }
    else
    {
        MSC_BlinkLED(4);
    }
    MSC_RedLEDOFF();    
    MSC_DelayMS(1000);
    
    /* load IR code */
    if(IR_Saved == EMPTY)
    {
        IR_LoadDefaultCode();
        MSC_BlinkLED(10);
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
                if(IR_Saved == NEW)
                {
                    MSC_BlinkLED(4);
                    IR_Saved = OLD;
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
            if(Rail_VIN < VIN_LOW_LIMIT || Rail_VIN > VIN_HIGH_LIMIT )
            {
                MSC_DelayMS(BLINK_VERYSLOW);
                MSC_RedLEDTOGGLE();
            }
        }
        else if(System_State == PROGRAM)
        {
            /* The system is in program mode */
            MSC_DelayMS(BLINK_FAST);
            MSC_RedLEDTOGGLE();
            if(RF_Data)
            {
                /* RF code needs to be saved */
                RF_Data = FALSE;
                System_State = RUN;
                System_State_Change = TRUE;
            }
            if(IR_Data)
            {
                /* IR code needs to be saved */
                IR_Data = FALSE;
                System_State = RUN;
                System_State_Change = TRUE;
            }                       
        }   
        
        ADC_SampleCount++;
        if(ADC_SampleCount > ADC_SAMPLERATE)
        {
            ADC_Start();
            ADC_SampleCount = 0;
        }
    }
}
/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
