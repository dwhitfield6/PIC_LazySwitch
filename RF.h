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
#ifndef RF_H
#define	RF_H

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
/* RF_TOLERANCE

 *
 * This sets the window tolerance for a matching RF code. Small is for the
 *  sync bit or any other long timing portions and Large is for short timing
 *  portions.
/******************************************************************************/
#define RF_TOLERANCELARGE    0.5
#define RF_TOLERANCESMALL    0.02

/******************************************************************************/
/* RF_PROGRAMSYNCLOW

 *
 * This sets the noise floor for a program RF signal sync bit.
/******************************************************************************/
#define RF_PROGRAMSYNCLOW    300

/******************************************************************************/
/* RF_PROGRAMSYNCHIGH

 *
 * This sets the timeout of an RF signal during program.
/******************************************************************************/
#define RF_PROGRAMSYNCHIGH   1400

/******************************************************************************/
/* RF_EDGENUM

 *
 * This sets the minimum number of edges for an RF code.
/******************************************************************************/
#define RF_EDGENUM   20

/******************************************************************************/
/* RFBUFFERSIZE
 *
 * This sets the size of the RF buffer.
/******************************************************************************/
#define RFBUFFERSIZE    64

/******************************************************************************/
/* Baud Rates
 *
 * This sets up the baud rate by modifying the sel0 and sel1 pins. This is
 *  turn configures the programmable low-pass-filter.
/******************************************************************************/
#define VERYSLOW    0
#define SLOW        1
#define FAST        2
#define VERYFAST    3

/******************************************************************************/
/* Status of saved codes
 *
 * This contains the status of the saved codes.
/******************************************************************************/
#define NEW     90
#define OLD     91

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Default RF code timing (Westek RFA-108 channel code E)                     */
/******************************************************************************/
const unsigned int RF_SavedTiming[RFBUFFERSIZE] __at(0x2580) = {                        
                                                834,    //    [    0    ]
                                                21,    //    [    1    ]
                                                80,    //    [    2    ]
                                                22,    //    [    3    ]
                                                80,    //    [    4    ]
                                                21,    //    [    5    ]
                                                78,    //    [    6    ]
                                                79,    //    [    7    ]
                                                26,    //    [    8    ]
                                                22,    //    [    9    ]
                                                78,    //    [    10    ]
                                                78,    //    [    11    ]
                                                27,    //    [    12    ]
                                                21,    //    [    13    ]
                                                79,    //    [    14    ]
                                                76,    //    [    15    ]
                                                25,    //    [    16    ]
                                                23,    //    [    17    ]
                                                79,    //    [    18    ]
                                                75,    //    [    19    ]
                                                27,    //    [    20    ]
                                                21,    //    [    21    ]
                                                81,    //    [    22    ]
                                                75,    //    [    23    ]
                                                25,    //    [    24    ]
                                                22,    //    [    25    ]
                                                81,    //    [    26    ]
                                                22,    //    [    27    ]
                                                79,    //    [    28    ]
                                                22,    //    [    29    ]
                                                80,    //    [    30    ]
                                                24,    //    [    31    ]
                                                79,    //    [    32    ]
                                                77,    //    [    33    ]
                                                25,    //    [    34    ]
                                                76,    //    [    35    ]
                                                27,    //    [    36    ]
                                                21,    //    [    37    ]
                                                80,    //    [    38    ]
                                                21,    //    [    39    ]
                                                81,    //    [    40    ]
                                                21,    //    [    41    ]
                                                80,    //    [    42    ]
                                                22,    //    [    43    ]
                                                80,    //    [    44    ]
                                                22,    //    [    45    ]
                                                81,    //    [    46    ]
                                                22,    //    [    47    ]
                                                79,    //    [    48    ]
                                                22,    //    [    49    ]
};

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern volatile unsigned char RF_Data;
extern unsigned int RF_DataTiming[RFBUFFERSIZE];
extern unsigned char RF_DataPlace;
extern unsigned char RFStarted;
extern unsigned int RF_SyncLow;
extern unsigned int RF_SyncHigh;
extern unsigned char RF_Saved;
extern unsigned char RF_CodeSize;
extern double Rail_RSSI;

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitRF(void);
unsigned char RF_ReadReceiver(void);
void RF_DataInt(unsigned char state);
void RF_Receiver(unsigned char state);
void RF_SetBandwidth(unsigned char band);
void RF_SetSquelch(unsigned char state);
void RF_ResetData(void);
void RF_LoadCode(void);
unsigned char RF_CalculateCodesize(void);
unsigned char RF_CheckCode(void);
void RF_Disable(void);
void RF_Enable(void);

#endif	/* RF_H */