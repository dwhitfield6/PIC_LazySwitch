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
#ifndef MISC_H
#define	MISC_H

#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "SYSTEM.h"

/******************************************************************************/
/* NOPS_DELAYMS
 *
 * This defines the number of NOPS for a MS delay.
/******************************************************************************/
#define NOPS_DELAYMS 1000

/******************************************************************************/
/* Blink rates
 *
 * This defines the number of milliseconds for the blink timing.
/******************************************************************************/
#define BLINK_VERYSLOW 100
#define BLINK_SLOW 75
#define BLINK_MEDIUM 50
#define BLINK_FAST 25
#define BLINK_VERYFAST 15

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
#define Even        2
#define Odd         3
#define NOCOMMA     1
#define DOUBLECOMMA 2
#define NOVALUE     3
#define TOOBIG      4
#define NEGATIVE    5
#define NoError     0

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~ RED LED ~~~~~~~~~~~~~~~~~~~~~~~~~*/
/******************************************************************************/
/* MSC_RedLEDON
 *
 * The function turns on the Red LED.
/******************************************************************************/
#define MSC_RedLEDON()  (LATC |= REDLED)

/******************************************************************************/
/* MSC_RedLEDOFF
 *
 * The function turns off the Red LED.
/******************************************************************************/
#define MSC_RedLEDOFF()  (LATC &= ~REDLED)

/******************************************************************************/
/* MSC_RedLEDTOGGLE
 *
 * The function toggles the Red LED.
/******************************************************************************/
#define MSC_RedLEDTOGGLE()  (LATC ^= REDLED)

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void MSC_DelayMS(long US);
void MSC_DelayNOP(unsigned int NOPs);
void MSC_CleanBuffer(unsigned char* data, unsigned int count);
void MSC_CleanBufferInt(unsigned int* data, unsigned int count);
void MSC_BufferCopy(unsigned char* from,unsigned char* to, unsigned int count, unsigned int shift);
void MSC_BufferCopyInt(unsigned int* from,unsigned int* to, unsigned int count, unsigned int shift);
void MSC_BufferCopyIntConst(const unsigned int* from,unsigned int* to, unsigned int count, unsigned int shift);
void MSC_BlinkLED(unsigned int blink, unsigned int speed);

#endif	/* MISC_H */