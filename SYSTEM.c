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
/* Contains system functions.
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
#include "IR.h"
#include "BUTTON.h"
#include "RF.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
volatile unsigned char System_State = RUN;
volatile unsigned char System_State_Change = FALSE;
unsigned long Activity_Timer = 0;

/******************************************************************************/
/* Functions
/******************************************************************************/

/******************************************************************************/
/* SYS_ActivityTimerReset
 *
 * The function check for activity an puts system to sleep if there is no
 *  activity.
/******************************************************************************/
inline void SYS_ActivityTimerReset(void)
{
    Activity_Timer = 0;
}

/******************************************************************************/
/* SYS_DisableInt
 *
 * The function disables low and high priority interrupts.
/******************************************************************************/
inline void SYS_DisableInt(void)
{
    INTCONbits.GIE = 0;     // Disable high priority interrupts
    INTCONbits.PEIE = 0;    // Disable low priority interrupts
}

/******************************************************************************/
/* SYS_EnableInt
 *
 * The function disables low and high priority interrupts.
/******************************************************************************/
inline void SYS_EnableInt(void)
{
    BUT_IR_PinChangeInt(ON);
    RF_DataInt(ON);
    INTCONbits.PEIE = 1;    // Enable low priority interrupts
    INTCONbits.GIE = 1;     // Enable high priority interrupts
}

/******************************************************************************/
/* SYS_Sleep
 *
 * The function puts the device in sleep mode.
/******************************************************************************/
inline void SYS_Sleep(void)
{
    OSCCON &= ~0b10000000;  // enter sleep mode on sleep instruction
    asm("sleep");
}

/******************************************************************************/
/* SYS_Idle
 *
 * The function puts the device in idle mode.
/******************************************************************************/
inline void SYS_Idle(void)
{
    OSCCON |= 0b10000000;  // enter idle mode on sleep instruction
    asm("sleep");
}

/******************************************************************************/
/* SYS_ConfigureOscillator
 *
 * The function configures the oscillator.
/******************************************************************************/
void SYS_ConfigureOscillator(void)
{
    /* This functionality is done in the configuration bits */
    OSCTUNEbits.PLLEN = 1;      // PLL enabled
    while(!OSCCONbits.OSTS);    // Wait until primary oscillator is ready
}

/******************************************************************************/
/* SYS_ActivityTimer
 *
 * The function check for activity an puts system to sleep if there is no
 *  activity.
/******************************************************************************/
void SYS_ActivityTimer(void)
{
    if(Activity_Timer > ActivityTimeout)
    {
        SYS_ActivityTimerReset();
        SYS_EnableInt();
        SYS_Sleep();
    }
    else
    {
        Activity_Timer++;
    }
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/