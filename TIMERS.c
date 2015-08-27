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
/* TMR_Timer0Status
 *
 * The function returns the current status of timer 0. 
 *   (whether it is on or off).
/******************************************************************************/
inline unsigned char TMR_Timer0Status(void)
{
    if(T0CONbits.TMR0ON)
    {
        /* Timer 0 is on */
        return 1;       
    }
    return 0;
}

/******************************************************************************/
/* TMR_Timer0
 *
 * The function turns timer 0 on or off.
/******************************************************************************/
inline void TMR_Timer0(unsigned char state)
{
    if(state)
    {
        /* Turn on timer 0 */
        T0CONbits.TMR0ON = 1;        
    }
    else
    {
        /* Turn off timer 0 */
        T0CONbits.TMR0ON = 0;
    }
}

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
/* TMR_ResetTimer0
 *
 * The function resets timer 0.
/******************************************************************************/
inline void TMR_ResetTimer0(void)
{
    unsigned char TimerOn = T0CONbits.TMR0ON;
    
    TMR_Timer0(OFF);
    TMR0H = 0;
    TMR0L = 2;
    if(TimerOn)
    {
        TMR_Timer0(ON);
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
/* TMR_Timer0Int
 *
 * The function controls the timer 0 interrupt.
/******************************************************************************/
inline void TMR_Timer0Int(unsigned char state)
{
    if(state)
    {
        /* Enable timer 0 interrupt */
        INTCONbits.TMR0IE = 1;        
    }
    else
    {
        /* Disable timer 0 interrupt */
        INTCONbits.TMR0IE = 0; 
    }
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
    InitTimer0();
    InitTimer2();
}

/******************************************************************************/
/* InitTimer2
 *
 * The function initializes timer2 which is used for the RF receiver.
/******************************************************************************/
void InitTimer0(void)
{
    TMR_Timer0(OFF);
    TMR_ResetTimer0();
    T0CONbits.T08BIT = 0;   // 16 bit counter
    T0CONbits.T0CS = 0;     // Internal instruction cycle clock (CLKO) 
    T0CONbits.PSA = 0;      // prescaler is assigned
    T0CONbits.T0PS = 0b011; // prescaler is 16
    INTCON2bits.TMR0IP = 1; // high priority interrupt
    TMR_Timer0Int(ON);
}

/******************************************************************************/
/* InitTimer2
 *
 * The function initializes timer2 which is used for the pushbutton.
/******************************************************************************/
void InitTimer2(void)
{
    TMR_Timer2(OFF);
    T2CONbits.TOUTPS = 0b1111; // Postscale is 16
    T2CONbits.T2CKPS = 0b11; // Prescale is 16
    IPR1bits.TMR2IP = 0; // low priority interrupt
    PR2 = 0xFF;
    TMR_Timer2Int(ON);
}

/******************************************************************************/
/* TMR_Timer0Start
 *
 * The function starts timer 0.
/******************************************************************************/
void TMR_Timer0Start(void)
{
    TMR_Timer0(OFF);
    TMR_ResetTimer0();
    TMR_Timer0(ON);
}

/******************************************************************************/
/* TMR_Timer2Start
 *
 * The function starts timer 2.
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