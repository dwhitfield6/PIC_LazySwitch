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
/* IR_TOLERANCE

 *
 * This sets the window tolerance for a matching IR code. Small is for the
 *  sync bit or any other long timing portions and Large is for short timing
 *  portions.
/******************************************************************************/
#define IR_TOLERANCELARGE    1.1
#define IR_TOLERANCEMEDUIM   0.75
#define IR_TOLERANCESMALL    0.3

/******************************************************************************/
/* IR_SYNCLOWBOUND

 *
 * This sets the noise floor for a program IR signal sync bit.
/******************************************************************************/
#define IR_SYNCLOWBOUND    6000

/******************************************************************************/
/* IR_SYNCHIGHBOUND

 *
 * This sets the timeout of an IR signal during program.
/******************************************************************************/
#define IR_SYNCHIGHBOUND   10000

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
#define IRBUFFERSIZE    96

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Default IR codes                                                           */
/******************************************************************************/
/*~~~~~~~~~~~~~~ Pioneer CXC3173 plus button ~~~~~~~~~~~~~~~~~~~~~~~~*/
const unsigned int IR_SavedTiming0[IRBUFFERSIZE] __at(0x2400)= {                        
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
                                                    450,    //    [    66    ]
                                                    0,    //    [    67    ]
                                                    0,    //    [    68    ]
                                                    0,    //    [    69    ]
                                                    0,    //    [    70    ]
                                                    0,    //    [    71    ]
                                                    0,    //    [    72    ]
                                                    0,    //    [    73    ]
                                                    0,    //    [    74    ]
                                                    0,    //    [    75    ]
                                                    0,    //    [    76    ]
                                                    0,    //    [    77    ]
                                                    0,    //    [    78    ]
                                                    0,    //    [    79    ]
                                                    0,    //    [    80    ]
                                                    0,    //    [    81    ]
                                                    0,    //    [    82    ]
                                                    0,    //    [    83    ]
                                                    0,    //    [    84    ]
                                                    0,    //    [    85    ]
                                                    0,    //    [    86    ]
                                                    0,    //    [    87    ]
                                                    0,    //    [    88    ]
                                                    0,    //    [    89    ]
                                                    0,    //    [    90    ]
                                                    0,    //    [    91    ]
                                                    0,    //    [    92    ]
                                                    0,    //    [    93    ]
                                                    0,    //    [    94    ]
                                                    0    //    [    95    ]
};

/*~~~~~~~~~~~~~~ Sanyo tv up channel button ~~~~~~~~~~~~~~~~~~~~~~~~*/
const unsigned int IR_SavedTiming1[IRBUFFERSIZE] __at(0x24C0)= {                        
                                                    8600,    //    [    0    ]
                                                    4200,    //    [    1    ]
                                                    450,    //    [    2    ]
                                                    450,    //    [    3    ]
                                                    450,    //    [    4    ]
                                                    450,    //    [    5    ]
                                                    450,    //    [    6    ]
                                                    450,    //    [    7    ]
                                                    450,    //    [    8    ]
                                                    1200,    //    [    9    ]
                                                    450,    //    [    10    ]
                                                    1200,    //    [    11    ]
                                                    450,    //    [    12    ]
                                                    1200,    //    [    13    ]
                                                    450,    //    [    14    ]
                                                    450,    //    [    15    ]
                                                    450,    //    [    16    ]
                                                    450,    //    [    17    ]
                                                    450,    //    [    18    ]
                                                    1200,    //    [    19    ]
                                                    450,    //    [    20    ]
                                                    1200,    //    [    21    ]
                                                    450,    //    [    22    ]
                                                    1200,    //    [    23    ]
                                                    450,    //    [    24    ]
                                                    450,    //    [    25    ]
                                                    450,    //    [    26    ]
                                                    450,    //    [    27    ]
                                                    450,    //    [    28    ]
                                                    450,    //    [    29    ]
                                                    450,    //    [    30    ]
                                                    1200,    //    [    31    ]
                                                    450,    //    [    32    ]
                                                    1200,    //    [    33    ]
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
                                                    450,    //    [    66    ]
                                                    0,    //    [    67    ]
                                                    0,    //    [    68    ]
                                                    0,    //    [    69    ]
                                                    0,    //    [    70    ]
                                                    0,    //    [    71    ]
                                                    0,    //    [    72    ]
                                                    0,    //    [    73    ]
                                                    0,    //    [    74    ]
                                                    0,    //    [    75    ]
                                                    0,    //    [    76    ]
                                                    0,    //    [    77    ]
                                                    0,    //    [    78    ]
                                                    0,    //    [    79    ]
                                                    0,    //    [    80    ]
                                                    0,    //    [    81    ]
                                                    0,    //    [    82    ]
                                                    0,    //    [    83    ]
                                                    0,    //    [    84    ]
                                                    0,    //    [    85    ]
                                                    0,    //    [    86    ]
                                                    0,    //    [    87    ]
                                                    0,    //    [    88    ]
                                                    0,    //    [    89    ]
                                                    0,    //    [    90    ]
                                                    0,    //    [    91    ]
                                                    0,    //    [    92    ]
                                                    0,    //    [    93    ]
                                                    0,    //    [    94    ]
                                                    0    //    [    95    ]
};

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern volatile unsigned char IR_Data;
extern unsigned int IR_DataTiming[IRBUFFERSIZE];
extern unsigned int IR_DataHolder1[IRBUFFERSIZE];
extern unsigned char IR_DataPlace;
extern unsigned char IRStarted;
extern unsigned int IR_SyncLow;
extern unsigned int IR_SyncHigh;
extern unsigned char IR_Saved;
extern unsigned char IR_CodeSize;
extern unsigned char IRValue_prev;
extern unsigned char IRChange;
extern unsigned char IRProgramCodeNumber;

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitIR(void);
unsigned char IR_ReadReceiver(void);
void IR_ResetData(void);
void IR_LoadCode(void);
unsigned char IR_CalculateCodesize(const unsigned int* Code);
unsigned char IR_CheckCode(void);
void IR_CleanBuffer(void);

#endif	/* IR_H */