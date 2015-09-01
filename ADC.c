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
/* Contains functions for the analog to digital converter.
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
#include "ADC.h"
#include "LDO.h"
#include "RF.h"
#include "IR.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned char ADC_CurrentSource = VIN;
unsigned int ADC_SampleCount = 0;

/******************************************************************************/
/* Inline Functions
/******************************************************************************/

/******************************************************************************/
/* Functions
/******************************************************************************/

/******************************************************************************/
/* InitADC
 *
 * The function initializes the ADC.
/******************************************************************************/
void InitADC(void)
{
    ADCON1bits.VCFG1 = 0;       // negative reference is VSS
    ADCON1bits.VCFG0 = 0;       // positive reference is VDD
    ADCON2bits.ADFM = 1;        // result is right justified
    ADCON2bits.ACQT = 0b111;    // A/D Acquisition Time is 20 TAD
    ADCON2bits.ADCS = 0b110;    // A/D Conversion Clock is FOSC/64 
    IPR1bits.ADIP   = 0;        // Low priority interrupt
    ADC_ChangeChannel();
    ADC_ConversionInt(ON);
    ADC_Module(ON);
}

/******************************************************************************/
/* ADC_CalculateVoltage
 *
 * The function calculates the voltage on the ADC input pin.
/******************************************************************************/
void ADC_CalculateVoltage(void)
{
    unsigned int ADCcounts = 0;
    double Voltage;
    
    ADCcounts = ADRESH;
    ADCcounts <<= 8;
    ADCcounts += ADRESL;
    
    Voltage = ((double)ADCcounts / (1 << ADC_RES)) * ADC_REFFERENCE;
    if(ADC_CurrentSource == VIN)
    {
        Rail_VIN = Voltage * (R11 + R10) / R11;
        NOP();
    }
    else
    {
        Rail_RSSI = Voltage;
        NOP();
    }
    ADC_ChangeChannel();
}

/******************************************************************************/
/* ADC_CalculateVoltage
 *
 * The function calculates the voltage on the ADC input pin.
/******************************************************************************/
void ADC_ChangeChannel(void)
{
    if(ADC_CurrentSource == VIN)
    {
        ADC_CurrentSource = RSSI;
        ADCON0bits.CHS = RF_RSSI_AN;
    }
    else
    {
        ADC_CurrentSource = VIN;
        ADCON0bits.CHS = ADC_VIN_AN;
    }
}

/******************************************************************************/
/* ADC_Module
 *
 * The function controls the ADC module.
/******************************************************************************/
void ADC_Module(unsigned char state)
{
    if(state)
    {
        /* Turn on the ADC module */
        ADCON0bits.ADON = TRUE;
    }
    else
    {
        /* Turn off the ADC module */
        ADCON0bits.ADON = FALSE;
    }
}

/******************************************************************************/
/* ADC_Start
 *
 * The function starts an ADC conversion.
/******************************************************************************/
void ADC_Start(void)
{
    ADCON0bits.GO = 1; // A/D conversion in progress
}

/******************************************************************************/
/* ADC_ConversionStatus
 *
 * The function returns the status of an ADC conversion.
/******************************************************************************/
unsigned char ADC_ConversionStatus(void)
{
    if(ADCON0bits.GO == 1)
    {
        return TRUE; // A/D conversion in progress
    }
    return FALSE;
}

/******************************************************************************/
/* ADC_ConversionInt
 *
 * The function controls the ADC interrupt.
/******************************************************************************/
void ADC_ConversionInt(unsigned char state)
{
    if(state)
    {
        /* Enable the ADC interrupt */
        PIE1bits.ADIE = TRUE;
    }
    else
    {
        /* Disable the ADC interrupt */
        PIE1bits.ADIE = FALSE;
    }
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/