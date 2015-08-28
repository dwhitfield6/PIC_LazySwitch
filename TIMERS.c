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
/* TMR_Timer1Status
 *
 * The function returns the current status of timer 1. 
 *   (whether it is on or off).
/******************************************************************************/
inline unsigned char TMR_Timer1Status(void)
{
    if(T1CONbits.TMR1ON)
    {
        /* Timer 1 is on */
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
/* TMR_Timer1
 *
 * The function turns timer 1 on or off.
/******************************************************************************/
inline void TMR_Timer1(unsigned char state)
{
    if(state)
    {
        /* Turn on timer 1 */
        T1CONbits.TMR1ON = 1;        
    }
    else
    {
        /* Turn off timer 1 */
        T1CONbits.TMR1ON = 0;
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
/* TMR_ResetTimer1
 *
 * The function resets timer 1.
/******************************************************************************/
inline void TMR_ResetTimer1(void)
{
    unsigned char TimerOn = T1CONbits.TMR1ON;
    
    TMR_Timer1(OFF);
    TMR1H = 0;
    TMR1L = 2;
    if(TimerOn)
    {
        TMR_Timer1(ON);
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
/* TMR_Timer1Int
 *
 * The function controls the timer 1 interrupt.
/******************************************************************************/
inline void TMR_Timer1Int(unsigned char state)
{
    if(state)
    {
        /* Enable timer 1 interrupt */
        PIE1bits.TMR1IE = 1;        
    }
    else
    {
        /* Disable timer 1 interrupt */
        PIE1bits.TMR1IE = 0;  
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
/* TMR_Timer1Osc
 *
 * The function turns on or off the external 32.768kHz oscillator for timer 1.
/******************************************************************************/
inline void TMR_Timer1Osc(unsigned char state)
{
    if(state)
    {
        T1CONbits.T1RUN = 1;    // Device clock is derived from Timer1 oscillator
        T1CONbits.T1OSCEN = 1;  // Timer1 oscillator is enabled  
        T1CONbits.TMR1CS = 1;   // External clock from pin RC0/T1OSO/T13CKI (on the rising edge)  
    }
    else
    {
        T1CONbits.T1RUN = 0;    // Device clock is derived from another source 
        T1CONbits.T1OSCEN = 0;  // Timer1 oscillator is disabled 
        T1CONbits.TMR1CS = 0;   // Internal clock (FOSC/4)
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
    InitTimer1();
    InitTimer2();
}

/******************************************************************************/
/* InitTimer0
 *
 * The function initializes timer 0 which is used for the RF receiver.
/******************************************************************************/
void InitTimer0(void)
{
    TMR_Timer0(OFF);
    TMR_ResetTimer0();
    T0CONbits.T08BIT = 0;   // 16 bit counter
    T0CONbits.T0CS = 0;     // Internal instruction cycle clock (CLKO) 
    T0CONbits.PSA = 0;      // prescaler is assigned
    T0CONbits.T0PS = 0b101; // prescaler is 64
    INTCON2bits.TMR0IP = 1; // high priority interrupt
    TMR_Timer0Int(ON);
}

/******************************************************************************/
/* InitTimer1
 *
 * The function initializes timer 1 which is used for the IR receiver.
/******************************************************************************/
void InitTimer1(void)
{
    TMR_Timer1(OFF);
    TMR_ResetTimer1();
    T1CONbits.RD16 = 1;         // Enables register read/write of TImer1 in one 16-bit operation
    TMR_Timer1Function(IR);
    IPR1bits.TMR1IP = 0;        // low priority interrupt
    TMR_Timer1Int(ON);    
}

/******************************************************************************/
/* InitTimer2
 *
 * The function initializes timer 2 which is used for the pushbutton.
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
/* TMR_Timer1Start
 *
 * The function starts timer 1.
/******************************************************************************/
void TMR_Timer1Start(void)
{
    TMR_Timer1(OFF);
    TMR_ResetTimer1();
    TMR_Timer1(ON);
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

/******************************************************************************/
/* TMR_Timer1Function
 *
 * The function controls the mode of timer 1. If the timer is used for IR, the
 *  clock source is the main oscillator. If the timer is used as an RTC, the
 *  clock source is the external oscillator.
/******************************************************************************/
void TMR_Timer1Function(unsigned char mode)
{
    TMR_Timer1(OFF);
    if(mode == RTC)
    {
        T1CONbits.T1CKPS = 0b00;    // 1:1 Prescale value 
        TMR_Timer1Osc(ON);
    }
    else
    {
        T1CONbits.T1CKPS = 0b11;    // 1:8 Prescale value 
        TMR_Timer1Osc(OFF);
    }
    TMR_ResetTimer1(); 
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/