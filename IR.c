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
#include "IR.h"
#include "RF.h"
#include "MISC.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
volatile unsigned char IR_Data = FALSE;
unsigned int IR_DataTiming[IRBUFFERSIZE];
unsigned int IR_SavedTiming[IRBUFFERSIZE];
unsigned char IR_DataPlace = 0;
unsigned char IRStarted = FALSE;
unsigned int IR_SyncLow  = 0;
unsigned int IR_SyncHigh = 0;
unsigned char IR_Saved = EMPTY;
unsigned char IR_CodeSize = 0;
unsigned char IRValue_prev = FALSE;
unsigned char IRChange = FALSE;

/******************************************************************************/
/* Inline Functions
/******************************************************************************/

/******************************************************************************/
/* Functions
/******************************************************************************/

/******************************************************************************/
/* InitIR
 *
 * The function initializes the IR receiver.
/******************************************************************************/
void InitIR(void)
{
    MSC_CleanBufferInt(&IR_DataTiming,IRBUFFERSIZE);
}

/******************************************************************************/
/* IR_ReadReceiver
 *
 * The function reads the state of the IR sensor.
/******************************************************************************/
unsigned char IR_ReadReceiver(void)
{
    unsigned char value = PORTB;
    
    if(value & IR_REC2)
    {
        if(IRValue_prev == FALSE)
        {
            IRChange = TRUE;  
        }
        IRValue_prev = TRUE;
        return TRUE;
    }
    
    if(IRValue_prev == TRUE)
    {
        IRChange = TRUE;  
    }
    IRValue_prev = FALSE;
    return FALSE;
}

/******************************************************************************/
/* IR_ResetData
 *
 * The function resets the IR buffer.
/******************************************************************************/
void IR_ResetData(void)
{
    IR_DataPlace = 0;
    IRStarted = FALSE;
    RF_Enable(); // re enable RF receive because IR receive is done
}

/******************************************************************************/
/* IR_CleanBuffer
 *
 * The function clears the IR buffer.
/******************************************************************************/
void IR_CleanBuffer(void)
{
    MSC_CleanBufferInt(&IR_DataTiming,IRBUFFERSIZE);
}

/******************************************************************************/
/* IR_CalculateNewCode
 *
 * The function calculates the sync window for the new code.
/******************************************************************************/
void IR_CalculateNewCode(void)
{
    double Low = 0.0;
    double High = 0.0;
    
    Low = (double)IR_DataTiming[0] * (1.0 - IR_TOLERANCESMALL);
    High = (double)IR_DataTiming[0] * (1.0 + IR_TOLERANCESMALL);
    
    IR_SyncLow = (unsigned int) Low;
    IR_SyncHigh = (unsigned int) High;
}

/******************************************************************************/
/* IR_LoadDefaultCode
 *
 * The function loads the default code.
/******************************************************************************/
void IR_LoadDefaultCode(void)
{   
    double Low = 0.0;
    double High = 0.0;
    
    Low = (double)PIONEER_PLUS_Sync * (1.0 - IR_TOLERANCESMALL);
    High = (double)PIONEER_PLUS_Sync * (1.0 + IR_TOLERANCESMALL);
    
    IR_SyncLow = (unsigned int) Low;
    IR_SyncHigh = (unsigned int) High;
    
    MSC_BufferCopyIntConst(&PIONEER_PLUS_Timing,&IR_SavedTiming,PIONEER_PLUS_Edges,0); 
    IR_CodeSize = PIONEER_PLUS_Edges;
}

/******************************************************************************/
/* IR_CheckCode
 *
 * The function checks the current IR buffer against the stored code to see if
 *  it is a match.
/******************************************************************************/
unsigned char IR_CheckCode(void)
{   
    unsigned char i;
    double Low = 0.0;
    double High = 0.0;
    
    if(System_State == RUN)
    {
        for(i=0; i<IR_CodeSize;i++)
        {
            if(IR_SavedTiming[i] > 4000)
            {
                Low = (double)IR_SavedTiming[i] * (1.0 - IR_TOLERANCESMALL);
                High = (double)IR_SavedTiming[i] * (1.0 + IR_TOLERANCESMALL);
            }
            else if(IR_SavedTiming[i] <= 4000 && IR_SavedTiming[i] > 1000)
            {
                Low = (double)IR_SavedTiming[i] * (1.0 - IR_TOLERANCEMEDUIM);
                High = (double)IR_SavedTiming[i] * (1.0 + IR_TOLERANCEMEDUIM);
            }
            else
            {
                Low = (double)IR_SavedTiming[i] * (1.0 - IR_TOLERANCELARGE);
                High = (double)IR_SavedTiming[i] * (1.0 + IR_TOLERANCELARGE);
            }

            if((double)IR_DataTiming[i] < Low || (double)IR_DataTiming[i] > High )
            {
                return FALSE;
            }
        }
        return TRUE;
    }
    else
    {
        if(IR_DataPlace >= IR_EDGENUM)
        {
            /* The IR signal is valid for program */
            MSC_BufferCopyInt(&IR_DataTiming,&IR_SavedTiming,IRBUFFERSIZE,0);
            IR_Saved = NEW;
        }
        return TRUE;
    }
}
/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/