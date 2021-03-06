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
#ifndef LDO_H
#define	LDO_H

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
#include <stdio.h>         /* For true/false definition */
#include <string.h>
#endif

/******************************************************************************/
/* VIN_LOW_LIMIT
 *
 * This is low voltage limit on VIN.
/******************************************************************************/
#define VIN_LOW_LIMIT 3.4

/******************************************************************************/
/* VIN_HIGH_LIMIT
 *
 * This is high voltage limit on VIN.
/******************************************************************************/
#define VIN_HIGH_LIMIT 5.5

/******************************************************************************/
/* R10
 *
 * This is R10 on the board which is connected to the voltage divider to read
 *  VIN.
/******************************************************************************/
#define R10 500000.0

/******************************************************************************/
/* R11
 *
 * This is R11 on the board which is connected to the voltage divider to read
 *  VIN.
/******************************************************************************/
#define R11 200000.0

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern double Rail_VIN;

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitLDO(void);

#endif	/* LDO_H */