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
/* Files to Include                                                           */
/******************************************************************************/
#ifndef SYSTEM_H
#define	SYSTEM_H

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

/******************************************************************************/
/* ActivityTimeout
 *
 * This defines the activity timeout before sleep is called.
/******************************************************************************/
#define ActivityTimeout     1000

/******************************************************************************/
/* System frequency
 *
 * This is the CPU clock frequency.
 *
 * For this system the clock is 32MHz and the internal PLL is used.
 *
/******************************************************************************/
#define FOSC        32000000L
/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
#define FCY             (FOSC/2)
#define SYS_FREQ        FCY

/******************************************************************************/
/* System States
 *
 * This defines the system states.
/******************************************************************************/
#define PROGRAM     10
#define RUN         8

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern unsigned char System_State;
extern unsigned char System_State_Change;

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void SYS_ConfigureOscillator(void); /* Handles clock switching/osc initialization */
inline void SYS_Idle(void);
inline void SYS_Sleep(void);
void SYS_ActivityTimer(void);
void SYS_ActivityTimerReset(void);

#endif	/* SYSTEM_H */