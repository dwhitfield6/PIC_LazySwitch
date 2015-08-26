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
/* Contains functions for the DC motor driver.
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
#include "MOTOR.h"
#include "MISC.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned char DC_Motor = CW;

/******************************************************************************/
/* Inline Functions
/******************************************************************************/

/******************************************************************************/
/* MTR_IN1
 *
 * The function controls the DC motor drivers in1 pin.
/******************************************************************************/
inline void MTR_IN1(unsigned char state)
{
    if(state)
    {
        LATB |= MTR_FWD;
    }
    else
    {
        LATB &= ~MTR_FWD;
    }
}

/******************************************************************************/
/* MTR_IN2
 *
 * The function controls the DC motor drivers in2 pin.
/******************************************************************************/
inline void MTR_IN2(unsigned char state)
{
    if(state)
    {
        LATC |= MTR_REV;
    }
    else
    {
        LATC &= ~MTR_REV;
    }
}

/******************************************************************************/
/* Functions
/******************************************************************************/

/******************************************************************************/
/* InitRF
 *
 * The function initializes the DC motor driver.
/******************************************************************************/
void InitMOTOR(void)
{
    /* all of the pin initialization is done in Init_App() */
    Nop();
}

/******************************************************************************/
/* MTR_Rotate
 *
 * The function rotated the motor either clockwise or counter clockwise
 *   depending upon what was done previously. The direction is toggled.
/******************************************************************************/
void MTR_Rotate(void)
{
    if(DC_Motor == CW)
    {
        MTR_IN1(0);
        MTR_IN2(1);
        MSC_DelayMS(CW_MS);
        DC_Motor = CCW;
    }
    else
    {
        MTR_IN1(1);
        MTR_IN2(0);
        MSC_DelayMS(CCW_MS);
        DC_Motor = CW;
    }
    MTR_IN1(0);
    MTR_IN2(0);
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/