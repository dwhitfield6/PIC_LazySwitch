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
/* Files to Include                                                           */
/******************************************************************************/
#ifndef MOTOR_H
#define	MOTOR_H

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
/* MOTORWAIT
 *
 * This defines the milliseconds to wait between motor activations.
/******************************************************************************/
#define MOTORWAIT 200

/******************************************************************************/
/* CW_MS
 *
 * This defines the milliseconds to spin the motor clockwise.
/******************************************************************************/
#define CW_MS 400

/******************************************************************************/
/* CCW_MS
 *
 * This defines the milliseconds to spin the motor counter-clockwise.
/******************************************************************************/
#define CCW_MS 400

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
#define CW 0
#define CCW 1

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned char DC_Motor;

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitMOTOR(void);
void MTR_Rotate(void);

#endif	/* MOTOR_H */