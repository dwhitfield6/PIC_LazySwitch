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
/* Contains Functions for PIC initialization
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

/******************************************************************************/
/* Special Variables                                                          */
/******************************************************************************/
#ifdef PCB_REVB
const unsigned char PCB_Version[] = "PCB revA";
#endif

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Inline Functions
/******************************************************************************/

/******************************************************************************/
/* Functions
/******************************************************************************/

/******************************************************************************/
/* Init_App
 *
 * The function initializes the application. It sets the pins and pull-ups.
/******************************************************************************/
void Init_App(void)
{
    LATA = 0;
    LATB = 0;
    LATC = 0;
    
    T1OSOTris       = INPUT;
    T1OSITris       = INPUT;
    VINTris         = INPUT;
    RF_RSSITris     = INPUT;
    RF_SHDNTris     = OUTPUT;
    RF_SquelchTris  = OUTPUT;
    MTR_FWDTris     = OUTPUT;
    MTR_REVTris     = OUTPUT;
    LDO_SHDNTris    = OUTPUT;
    LDO_PASSTris    = OUTPUT;
    LEDTris         = OUTPUT;
    RF_DATA1Tris    = INPUT;
    RF_DATA2Tris    = INPUT;
    ADC_REFTris     = INPUT;
    IR_REC1Tris     = INPUT;
    IR_REC2Tris     = INPUT;
    SwitchTris      = INPUT;
    
#ifdef OPTIONAL_UART
    UART_TXTris = OUTPUT;
    UART_RXTris = INPUT;
#else
    RF_SEL0Tris = OUTPUT;
    RF_SEL1Tris = OUTPUT;
#endif
    
}

/******************************************************************************/
/* Init_System
 *
 * The function initializes the modules.
/******************************************************************************/
void Init_System(void)
{

}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/