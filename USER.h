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
#ifndef USER_H
#define	USER_H

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
/* PCB board
 *
 * This code is used with boards:
 * 1. PCB_REVB             (use configuration "LaztSwitch_PIC18f24J10")
/******************************************************************************/
#define PCB_REVB

/******************************************************************************/
/* Optional UART
 *
 * Uncomment if the optional UART is being used. If this is being used,
 *  populate R9 or R12 and R6 or R7 and remove R13 and R15 (See PCB manual).
/******************************************************************************/
//#define OPTIONAL_UART

/******************************************************************************/
/* Version
 *
 * This defines the Firmware version.
/******************************************************************************/
#define Version "2.0_DW0a"

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
#define ON 1
#define OFF 0
#define TRUE 1
#define FALSE 0
#define INPUT 1
#define OUTPUT 0
#define PASS 1
#define FAIL 0
#define YES 1
#define NO 0

#define FINISHED 1
#define NOTFINISHED 0

/******************************************************************************/
/* Pin Defines                                                                */
/******************************************************************************/

/************* Oscillator *************/
/* Connected to the secondary oscillator  */
#define T1OSOTris	TRISCbits.TRISC0

/* Connected to the secondary oscillator  */
#define T1OSITris	TRISCbits.TRISC1

/************* Voltage Monitoring *************/
/* Connected to the voltage divider connected to VIN */
#define ADC_VINTris	TRISAbits.TRISA0
#define ADC_VIN 0x01    //RA0 used as AN0
#define ADC_VIN_AN  0   //AN0

/************* RF Module *************/
/* Connected to the analog RSSI diagnostic */
#define RF_RSSITris	TRISAbits.TRISA1
#define RF_RSSI 0x02    //RA1 used as AN1
#define RF_RSSI_AN  1   //AN1

/* Connected to RF shutdown pin */
#define RF_SHDNTris	TRISAbits.TRISA2
#define RF_SHDN 0x04    //RA2

/* Connected to RF squelch control pin */
#define RF_SquelchTris	TRISAbits.TRISA5
#define RF_Squelch 0x20    //RA5

/* Connected to RF modulated data output pin */
#define RF_DATA1Tris	TRISBbits.TRISB1
#define RF_DATA1 0x02   //RB1 used as INT1

#define RF_DATA2Tris	TRISBbits.TRISB2
#define RF_DATA2 0x04   //RB1 used as INT2

#ifndef OPTIONAL_UART
/* Connected to RF SEL0 pin */
#define RF_SEL0Tris	TRISCbits.TRISC6
#define RF_SEL0 0x40    //RC6

/* Connected to RF SEL1 pin */
#define RF_SEL1Tris	TRISCbits.TRISC7
#define RF_SEL1 0x80    //RC7
#endif

/************* Motor driver *************/
/* Connected to the IN1 pin of the motor driver */
#define MTR_FWDTris	TRISBbits.TRISB3
#define MTR_FWD 0x08    //RB3

/* Connected to the IN2 pin of the motor driver */
#define MTR_REVTris	TRISCbits.TRISC2
#define MTR_REV 0x04    //RC2

/************* ADC reference *************/
/* Connected to the 2.5 volt reference */
#define ADC_REFTris	TRISAbits.TRISA3
#define ADC_REF 0x08    //RA3 used as VREF+

/************* IR receiver *************/
/* Connected to the modulated IR output pin of the IR receiver */
#define IR_REC1Tris	TRISBbits.TRISB0
#define IR_REC1 0x01    //RB0 used as INT0

#define IR_REC2Tris	TRISBbits.TRISB4
#define IR_REC2 0x10    //RB4

/************* Pushbutton switch *************/
/* Connected to the pushbutton switch */
#define SwitchTris	TRISBbits.TRISB5
#define Switch 0x20    //RB5 used as KBI1

/************* LDO *************/
/* Connected to the LDO shutdown pin */
#define LDO_SHDNTris	TRISCbits.TRISC3
#define LDO_SHDN 0x08    //RC3

/* Connected to the LDO passthrough MOSFET */
#define LDO_PASSTris	TRISCbits.TRISC5
#define LDO_PASS 0x20    //RC5

/************* LED *************/
/* Connected to the LED indicator */
#define REDLEDTris	TRISCbits.TRISC4
#define REDLED 0x10    //RC4

#ifdef OPTIONAL_UART
/************* Optional UART *************/
/* Connected to the optional UART transmit */
#define UART_TXTris	TRISCbits.TRISC6
#define UART_TX 0x40    //RC6

/* Connected to the optional UART receive */
#define UART_RXTris	TRISCbits.TRISC7
#define UART_RX 0x80    //RC7
#endif

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void Init_App(void);        
void Init_System (void);

#endif	/* USER_H */