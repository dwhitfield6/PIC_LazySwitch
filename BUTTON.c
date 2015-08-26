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
/* Contains functions for the Push button.
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
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned char Button_Data = FALSE;
unsigned char ButtonValue_prev = TRUE;
unsigned char ButtonChange = FALSE;
unsigned char ButtonTimer = FINISHED;

/******************************************************************************/
/* Inline Functions
/******************************************************************************/

/******************************************************************************/
/* BUT_IR_PinChangeInt
 *
 * The function controls the portB interruptt-on-change module.
/******************************************************************************/
inline void BUT_IR_PinChangeInt(unsigned char state)
{
    if(state)
    {
        /* Enable interrupt on change interrupt */
        INTCONbits.RBIE = 1;
    }
    else
    {
        /* Disable interrupt on change interrupt */
        INTCONbits.RBIE = 0;
    }
}

/******************************************************************************/
/* Functions
/******************************************************************************/

/******************************************************************************/
/* InitIR
 *
 * The function initializes the Push button.
/******************************************************************************/
void InitButton(void)
{
    /* the push button is used as KBI1 */
    INTCON2bits.RBIP = 0; // Interrupt Low priority
    BUT_IR_PinChangeInt(TRUE);
}

/******************************************************************************/
/* BUT_ReadButton
 *
 * The function reads the pushbutton and modifies the value of the pushbutton
 *   and determines if there was a change.
/******************************************************************************/
unsigned char BUT_ReadButton(void)
{
    unsigned char value = PORTB;
    if((value & Switch) == 0)
    {
        /* pushbutton switch is pressed */
        if(ButtonValue_prev == FALSE)
        {
            ButtonChange = TRUE;  
        }
        ButtonValue_prev = TRUE;
        return TRUE;
    }
    
    /* pushbutton switch is released */
    if(ButtonValue_prev == TRUE)
    {
        ButtonChange = TRUE;  
    }
    ButtonValue_prev = FALSE;
    return FALSE;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/