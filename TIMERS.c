/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 08/25/15     2.0_DW0a    Initial project make.
/******************************************************************************/

/******************************************************************************/
/* Contains functions for the timers.
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
#include "TIMERS.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned char Timer2Use = 0;
unsigned int Timer2Post = 0;
unsigned int Timer2PostCount = 0;

/******************************************************************************/
/* Inline Functions
/******************************************************************************/

/******************************************************************************/
/* TMR_Timer2
 *
 * The function turns timer 2 on or off.
/******************************************************************************/
inline void TMR_Timer2(unsigned char state)
{
    if(state)
    {
        /* Turn on timer 2 */
        T2CONbits.TMR2ON = 1;        
    }
    else
    {
        /* Turn off timer 2 */
        T2CONbits.TMR2ON = 0;
    }
}

/******************************************************************************/
/* TMR_ResetTimer2
 *
 * The function resets timer 2.
/******************************************************************************/
inline void TMR_ResetTimer2(void)
{
    unsigned char TimerOn = T2CONbits.TMR2ON;
    
    TMR_Timer2(OFF);
    Timer2PostCount = 0;
    TMR2 = 0;
    if(TimerOn)
    {
        TMR_Timer2(ON);
    }
}

/******************************************************************************/
/* TMR_Timer2SetUse
 *
 * The function sets the use of timer 2.
/******************************************************************************/
inline void TMR_Timer2SetUse(unsigned char use)
{
    Timer2Use = use;
}

/******************************************************************************/
/* TMR_Timer2Int
 *
 * The function controls the timer 2 interrupt.
/******************************************************************************/
inline void TMR_Timer2Int(unsigned char state)
{
    if(state)
    {
        /* Enable timer 2 interrupt */
        PIE1bits.TMR2IE = 1;        
    }
    else
    {
        /* Disable timer 2 interrupt */
        PIE1bits.TMR2IE = 0; 
    }
}

/******************************************************************************/
/* TMR_Timer2Free
 *
 * The function returns true if the timer is available for use.
/******************************************************************************/
inline unsigned char TMR_Timer2Free(void)
{
    if(!Timer2Use)
    {
        return TRUE;
    }
    return FALSE;
}

/******************************************************************************/
/* Functions
/******************************************************************************/

/******************************************************************************/
/* InitTimers
 *
 * The function initializes the timers.
/******************************************************************************/
void InitTimers(void)
{
    InitTimer2();
}

/******************************************************************************/
/* InitTimer2
 *
 * The function initializes timer2.
/******************************************************************************/
void InitTimer2(void)
{
    T2CONbits.TOUTPS = 0b1111; // Postscale is 16
    T2CONbits.T2CKPS = 0b11; // Prescale is 16
    IPR1bits.TMR2IP = 0; // low priority interrupt
    PR2 = 0xFF;
    TMR_Timer2Int(ON);
}

/******************************************************************************/
/* TMR_Timer2Start
 *
 * The function starts timer2.
/******************************************************************************/
void TMR_Timer2Start(unsigned int time)
{
    TMR_Timer2(OFF);
    Timer2Post = time;
    TMR_ResetTimer2();
    TMR_Timer2(ON);
}
/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/