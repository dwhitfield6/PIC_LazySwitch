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
    
    /*~~~~~~~~~~~~~ Primary crystal oscillator ~~~~~~~~~~~~~~~~~*/
    T1OSOTris       = INPUT;
    T1OSITris       = INPUT;
    
    /*~~~~~~~~~~~~~ ADC voltage monitoring of VIN ~~~~~~~~~~~~~~~~~*/
    ADC_VINTris     = INPUT;
    
    /*~~~~~~~~~~~~~ RF transmitter ~~~~~~~~~~~~~~~~~*/
    /* analog RSSI measuring */
    RF_RSSITris     = INPUT;
   
    /* shutdown control */
    RF_SHDNTris     = OUTPUT;
    
    /* Squelch control to reduce random noise on output pin during no RF */
    RF_SquelchTris  = OUTPUT;
    
    /* RF modulated data */
    RF_DATA1Tris    = INPUT;
    RF_DATA2Tris    = INPUT;
    
    /*~~~~~~~~~~~~~ Motor controller ~~~~~~~~~~~~~~~~~*/
    /* Forward movement */
    MTR_FWDTris     = OUTPUT;
    
    /* Backward movement */
    MTR_REVTris     = OUTPUT;
    
    /*~~~~~~~~~~~~~ LDO ~~~~~~~~~~~~~~~~~*/
    /* Shutdown enable */
    LDO_SHDNTris    = OUTPUT;
    
    /* Pass-through to save power at low battery voltages */
    LDO_PASSTris    = OUTPUT;
    
    /*~~~~~~~~~~~~~ LED indication ~~~~~~~~~~~~~~~~~*/
    /* RED LED */
    REDLEDTris         = OUTPUT;
    
    /*~~~~~~~~~~~~~ IR receiver ~~~~~~~~~~~~~~~~~*/
    /* IR modulated signal */
    IR_REC1Tris     = INPUT;
    IR_REC2Tris     = INPUT;
    
    /*~~~~~~~~~~~~~ Push-Button switch ~~~~~~~~~~~~~~~~~*/
    /* pushbutton switch with pull-up resistor */
    SwitchTris      = INPUT;
        
    /*~~~~~~~~~~~~~ ADC ~~~~~~~~~~~~~~~~~*/
    /* 2.5 volt reference */
    ADC_REFTris     = INPUT;
    
#ifdef OPTIONAL_UART
    /*~~~~~~~~~~~~~ Optional UART ~~~~~~~~~~~~~~~~~*/
    /* UART transmit */
    UART_TXTris = OUTPUT;
    
    /* UART receive */
    UART_RXTris = INPUT;
#else
    /*~~~~~~~~~~~~~ RF transmitter ~~~~~~~~~~~~~~~~~*/
    /* Baud rate selection */
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