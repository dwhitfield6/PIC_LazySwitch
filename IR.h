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
/* Files to Include                                                           */
/******************************************************************************/
#ifndef IR_H
#define	IR_H

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
/* Default IR code

 *
 * This sets the timings for the default IR code. The default is the the + sign
 *  on the pioneer cxc3173 controller. 
 *
 * Settings:
/******************************************************************************/
/* Sync bit */
#define PIONEER_PLUS_Sync 8800
/* this is the number of edges for one code cycle */
#define PIONEER_PLUS_Edges 67

/******************************************************************************/
/* IR_TOLERANCE

 *
 * This sets the window tolerance for a matching IR code. Small is for the
 *  sync bit or any other long timing portions and Large is for short timing
 *  portions.
/******************************************************************************/
#define IR_TOLERANCELARGE    1.1
#define IR_TOLERANCEMEDUIM   0.75
#define IR_TOLERANCESMALL    0.2

/******************************************************************************/
/* IR_PROGRAMSYNCLOW

 *
 * This sets the noise floor for a program IR signal sync bit.
/******************************************************************************/
#define IR_PROGRAMSYNCLOW    2000

/******************************************************************************/
/* IR_PROGRAMSYNCHIGH

 *
 * This sets the timeout of an IR signal during program.
/******************************************************************************/
#define IR_PROGRAMSYNCHIGH   16000

/******************************************************************************/
/* IR_EDGENUM

 *
 * This sets the minimum number of edges for an IR code.
/******************************************************************************/
#define IR_EDGENUM   40

/******************************************************************************/
/* IRBUFFERSIZE
 *
 * This sets the size of the IR buffer.
/******************************************************************************/
#define IRBUFFERSIZE    80

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Default IR code timing (Pioneer CXC3173 plus button)                       */
/******************************************************************************/
const unsigned int PIONEER_PLUS_Timing[PIONEER_PLUS_Edges] = {                        
                                                    8600,    //    [    0    ]
                                                    4200,    //    [    1    ]
                                                    450,    //    [    2    ]
                                                    1200,    //    [    3    ]
                                                    450,    //    [    4    ]
                                                    450,    //    [    5    ]
                                                    450,    //    [    6    ]
                                                    1200,    //    [    7    ]
                                                    450,    //    [    8    ]
                                                    1200,    //    [    9    ]
                                                    450,    //    [    10    ]
                                                    450,    //    [    11    ]
                                                    450,    //    [    12    ]
                                                    1200,    //    [    13    ]
                                                    450,    //    [    14    ]
                                                    450,    //    [    15    ]
                                                    450,    //    [    16    ]
                                                    1200,    //    [    17    ]
                                                    450,    //    [    18    ]
                                                    450,    //    [    19    ]
                                                    450,    //    [    20    ]
                                                    1200,    //    [    21    ]
                                                    450,    //    [    22    ]
                                                    450,    //    [    23    ]
                                                    450,    //    [    24    ]
                                                    450,    //    [    25    ]
                                                    450,    //    [    26    ]
                                                    1200,    //    [    27    ]
                                                    450,    //    [    28    ]
                                                    450,    //    [    29    ]
                                                    450,    //    [    30    ]
                                                    1200,    //    [    31    ]
                                                    450,    //    [    32    ]
                                                    450,    //    [    33    ]
                                                    450,    //    [    34    ]
                                                    450,    //    [    35    ]
                                                    450,    //    [    36    ]
                                                    1200,    //    [    37    ]
                                                    450,    //    [    38    ]
                                                    450,    //    [    39    ]
                                                    450,    //    [    40    ]
                                                    1200,    //    [    41    ]
                                                    450,    //    [    42    ]
                                                    450,    //    [    43    ]
                                                    450,    //    [    44    ]
                                                    450,    //    [    45    ]
                                                    450,    //    [    46    ]
                                                    450,    //    [    47    ]
                                                    450,    //    [    48    ]
                                                    450,    //    [    49    ]
                                                    450,    //    [    50    ]
                                                    1200,    //    [    51    ]
                                                    450,    //    [    52    ]
                                                    450,    //    [    53    ]
                                                    450,    //    [    54    ]
                                                    1200,    //    [    55    ]
                                                    450,    //    [    56    ]
                                                    450,    //    [    57    ]
                                                    450,    //    [    58    ]
                                                    1200,    //    [    59    ]
                                                    450,    //    [    60    ]
                                                    1200,    //    [    61    ]
                                                    450,    //    [    62    ]
                                                    1200,    //    [    63    ]
                                                    450,    //    [    64    ]
                                                    1200,    //    [    65    ]
                                                    450    //    [    66    ]
};

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern volatile unsigned char IR_Data;
extern unsigned int IR_DataTiming[IRBUFFERSIZE];
extern unsigned int IR_SavedTiming[IRBUFFERSIZE];
extern unsigned char IR_DataPlace;
extern unsigned char IRStarted;
extern unsigned int IR_SyncLow;
extern unsigned int IR_SyncHigh;
extern unsigned char IR_Saved;
extern unsigned char IR_CodeSize;
extern unsigned char IRValue_prev;
extern unsigned char IRChange;

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitIR(void);
unsigned char IR_ReadReceiver(void);
void IR_ResetData(void);
void IR_CalculateNewCode(void);
void IR_LoadDefaultCode(void);
unsigned char IR_CheckCode(void);
void IR_CleanBuffer(void);

#endif	/* IR_H */