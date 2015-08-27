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
/* Files to Include                                                           */
/******************************************************************************/
#ifndef TIMERS_H
#define	TIMERS_H

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

/******************************************************************************/
/* Timer2 uses
 *
 * This defines the functions of timer 2.
/******************************************************************************/
#define BUTTONPRESS 17
#define BUTTONRELEASE 18

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern unsigned char Timer2Use;
extern unsigned int Timer2Post;
extern unsigned int Timer2PostCount;

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitTimers(void);
inline unsigned char TMR_Timer0Status(void);
inline void TMR_Timer0(unsigned char state);
inline void TMR_Timer2(unsigned char state);
inline void TMR_ResetTimer0(void);
inline void TMR_ResetTimer2(void);
inline void TMR_Timer2SetUse(unsigned char use);
inline void TMR_Timer0Int(unsigned char state);
inline void TMR_Timer2Int(unsigned char state);
inline unsigned char TMR_Timer2Free(void);
void InitTimer0(void);
void InitTimer2(void);
void TMR_Timer0Start(void);
void TMR_Timer2Start(unsigned int time);

#endif	/* IR_H */