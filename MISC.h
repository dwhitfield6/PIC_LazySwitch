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
#define NOPS_DELAYMS 466

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
unsigned char MSC_IsCharacter(unsigned char data);
void MSC_CleanBuffer(unsigned char* data, unsigned int count);
void MSC_CleanBufferInt(unsigned int* data, unsigned int count);
double MSC_Round(double input);
void MSC_BufferCopy(unsigned char* from,unsigned char* to, unsigned int count, unsigned int shift);
unsigned char MSC_StringMatch(const unsigned char* This, const unsigned char* That);
unsigned char MSC_StringMatchCaseInsensitive(const unsigned char* This, const unsigned char* That);
unsigned char MSC_StringContains(const unsigned char* This, const unsigned char* That);
unsigned char MSC_StringContainsCaseInsensitive(const unsigned char* This, const unsigned char* That);
void MSC_LowercaseChar(unsigned char* Input);
void MSC_LowercaseString(unsigned char* Input);
void MSC_DelayNOP(unsigned int NOPs);
unsigned char MSC_ReverseByte(unsigned char This);
unsigned int MSC_ReverseInt(unsigned int This);
unsigned long MSC_ReverseLong(unsigned long This);
unsigned char MSC_GetNumber(unsigned char* This, unsigned char CommaNumber, long* result);
unsigned char MSC_StringAddEqual(unsigned char* Input);
unsigned char MSC_GetStringAfterComma(unsigned char* This, unsigned char CommaNumber, unsigned char* result);
unsigned char MSC_GetNumberUnsigned(unsigned char* This, unsigned char CommaNumber, unsigned long* result);
unsigned char MSC_IsAlphaNumericString(unsigned char* data);
unsigned char MSC_IsAlphaNumeric(unsigned char data);
unsigned char MSC_IsNumber(unsigned char data);
double MSC_DB_Round(double Input);
long MSC_Scale(long Input, long InputRangeLow, long InputRangeHigh, long OutputRangeLow, long OutputRangeHigh);
unsigned int MSC_BCDtoHEX(unsigned int input);
unsigned int MSC_HEXtoBCD(unsigned int input);
unsigned char MSC_BufferMatch(unsigned char* This, unsigned char* That, unsigned int size);
long MSC_LG_Round(long Input,unsigned char places);
void MSC_TestFunctionPointer(void);
unsigned int MSC_EndianInt(unsigned int number);
unsigned int MSC_EndianIntArray(unsigned char* buffer);
unsigned long MSC_EndianLong(unsigned long number);
unsigned long MSC_EndianLongArray(unsigned char* buffer);
void MSC_BlinkLED(unsigned int blink);
void MSC_BufferCopyInt(unsigned int* from,unsigned int* to, unsigned int count, unsigned int shift);
void MSC_BufferCopyIntConst(const unsigned int* from,unsigned int* to, unsigned int count, unsigned int shift);

#endif	/* MISC_H */