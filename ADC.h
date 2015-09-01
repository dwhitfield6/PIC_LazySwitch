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
#ifndef ADC_H
#define	ADC_H

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
/* ADC_SAMPLERATE
 *
 * This defines the number of loops around main() to take an ADC reading.
/******************************************************************************/
#define ADC_SAMPLERATE 10

/******************************************************************************/
/* ADCRES
 *
 * This defines the number of bits of resolution of the ADC.
/******************************************************************************/
#define ADC_RES 10

/******************************************************************************/
/* ADC_REF
 *
 * This defines the reference voltage.
/******************************************************************************/
#define ADC_REFFERENCE 3.3

/******************************************************************************/
/* ADC Sources
 *
 * This defines the analog sources to read from.
/******************************************************************************/
#define VIN 10
#define RSSI 11

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern unsigned char ADC_CurrentSource;
extern unsigned int ADC_SampleCount;

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitADC(void);
void ADC_Module(unsigned char state);
void ADC_Start(void);
unsigned char ADC_ConversionStatus(void);
void ADC_ConversionInt(unsigned char state);
void ADC_CalculateVoltage(void);
void ADC_ChangeChannel(void);

#endif	/* ADC_H */