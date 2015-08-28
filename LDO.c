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
/* Contains functions for the IR receiver.
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
double Rail_VIN = 4.5;

/******************************************************************************/
/* Inline Functions
/******************************************************************************/

/******************************************************************************/
/* LDO_Pass
 *
 * The function controls the LDO pass through.
/******************************************************************************/
inline void LDO_Pass(unsigned char state)
{
    if(state)
    {
        /* Enable the LDO pass through */
        LDO_PASSTris    = OUTPUT;
        LATC &= ~LDO_PASS;
    }
    else
    {
        /* Disable the LDO pass through */
        LDO_PASSTris    = INPUT;
    }
}
/******************************************************************************/
/* Functions
/******************************************************************************/

/******************************************************************************/
/* InitLDO
 *
 * The function initializes the LDO.
/******************************************************************************/
void InitLDO(void)
{
    LDO_Pass(NO); // Turn off pass through;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/