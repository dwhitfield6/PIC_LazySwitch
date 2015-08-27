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
#ifndef BUTTON_H
#define	BUTTON_H

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
/* PRESSCOUNT
 *
 * This defines the number of timer 2 overflow counts until the system goes
 *  into Program mode. This happens when the button is held down.
/******************************************************************************/
#define PRESSCOUNT 100

/******************************************************************************/
/* RELEASECOUNT
 *
 * This defines the number of timer 2 overflow counts until the system goes
 *  back to Run mode after inactivity.
/******************************************************************************/
#define PROGRAMTIMEOUT 70

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern volatile unsigned char Button_Data;
extern unsigned char ButtonValue_prev;
extern unsigned char ButtonChange;

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitButton(void);
inline void BUT_IR_PinChangeInt(unsigned char state);
unsigned char BUT_ReadButton(void);

#endif	/* BUTTON_H */