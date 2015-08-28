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
/* Contains system functions.
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

#include "SYSTEM.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned char System_State = RUN;
unsigned char System_State_Change = FALSE;

/******************************************************************************/
/* Functions
/******************************************************************************/

/******************************************************************************/
/* SYS_ConfigureOscillator
 *
 * The function configures the oscillator.
/******************************************************************************/
void SYS_ConfigureOscillator(void)
{
    /* This functionality is done in the configuration bits */
    OSCTUNEbits.PLLEN = 1;      // PLL enabled
    while(!OSCCONbits.OSTS);    // Wait until primary oscillator is ready
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/