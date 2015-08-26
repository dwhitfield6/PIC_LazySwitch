/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 08/25/15     2.0_DW0a    Initial project make.
 *                          Derived from project 'Catalyst_RPI_daughter'.
 *                          Added timer functionality for push button.
 *                          Move the motor in alternating directions for each
 *                            button press.
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

    MSC_BlinkLED(15);
    MSC_RedLEDOFF();
    
    while(1)
    {
        if(RF_Data || IR_Data || Button_Data)
        {
            MTR_Rotate();
            RF_Data = FALSE;
            IR_Data = FALSE;
            Button_Data = FALSE;
        }
    }
}
/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
