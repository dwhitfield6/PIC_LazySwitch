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
/* Default RF code

 *
 * This sets the timings for the default RF code. THe default is the Westek 
 * RFA-108 channel E. This device:
 *
 * 315MHz transmission
 *
 * Settings:
/******************************************************************************/
/* Sync bit/pause */
/* Nominal 4096 cycles or about 7.680mS*/
#define CONF1_ChanE_Sync 850
/* this is the number of edges for one code cycle */
#define CONF1_ChanE_Edges 50

/******************************************************************************/
/* RF_TOLERANCE

 *
 * This sets the window tolerance for a matching RF code. Small is for the
 *  sync bit or any other long timing portions and Large is for short timing
 *  portions.
/******************************************************************************/
#define RF_TOLERANCELARGE    0.5
#define RF_TOLERANCESMALL    0.05

/******************************************************************************/
/* RF_PROGRAMSYNCLOW

 *
 * This sets the noise floor for a program RF signal sync bit.
/******************************************************************************/
#define RF_PROGRAMSYNCLOW    400

/******************************************************************************/
/* RF_PROGRAMSYNCHIGH

 *
 * This sets the timeout of an RF signal during program.
/******************************************************************************/
#define RF_PROGRAMSYNCHIGH   1000

/******************************************************************************/
/* RF_EDGENUM

 *
 * This sets the minimum number of edges for an RF code.
/******************************************************************************/
#define RF_EDGENUM   20

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
#define EMPTY   92

/******************************************************************************/
/* RFBUFFERSIZE
 *
 * This sets the size of the RF buffer.
/******************************************************************************/
#define RFBUFFERSIZE    120

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Default Rf code timing                                                     */
/******************************************************************************/
const unsigned int CONF1_ChanE_Sync_Timing[CONF1_ChanE_Edges] = {                        
                                                                        834,
                                                                        21,
                                                                        80,
                                                                        22,
                                                                        80,
                                                                        21,
                                                                        78,
                                                                        79,
                                                                        26,
                                                                        22,
                                                                        78,
                                                                        78,
                                                                        27,
                                                                        21,
                                                                        79,
                                                                        76,
                                                                        25,
                                                                        23,
                                                                        79,
                                                                        75,
                                                                        27,
                                                                        21,
                                                                        81,
                                                                        75,
                                                                        25,
                                                                        22,
                                                                        81,
                                                                        22,
                                                                        79,
                                                                        22,
                                                                        80,
                                                                        24,
                                                                        79,
                                                                        77,
                                                                        25,
                                                                        76,
                                                                        27,
                                                                        21,
                                                                        80,
                                                                        21,
                                                                        81,
                                                                        21,
                                                                        80,
                                                                        22,
                                                                        80,
                                                                        22,
                                                                        81,
                                                                        22,
                                                                        79,
                                                                        22
};



/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern volatile unsigned char RF_Data;
extern unsigned int RF_DataTiming[RFBUFFERSIZE];
extern unsigned int RF_SavedTiming[RFBUFFERSIZE];
extern unsigned char RF_DataPlace;
extern unsigned char RFStarted;
extern unsigned int RF_SyncLow;
extern unsigned int RF_SyncHigh;
extern unsigned char RF_Saved;
extern unsigned char RF_CodeSize;

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitRF(void);
inline unsigned char RF_ReadReceiver(void);
inline void RF_DataInt(unsigned char state);
inline void RF_Receiver(unsigned char state);
inline void RF_SetBandwidth(unsigned char band);
inline void RF_SetSquelch(unsigned char state);
void RF_ResetRFData(void);
void RF_CalculateNewCode(void);
void TMR_LoadDefaultCode(void);
unsigned char RF_CheckCode(void);

#endif	/* RF_H */