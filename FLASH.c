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
/* Contains functions to write to and read from the onboard flash.
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
#include "FLASH.h"
#include "IR.h"
#include "RF.h"
#include "MISC.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned char FlashBuffer[128];
unsigned char Flash_Status = FAIL;

/******************************************************************************/
/* Inline Functions
/******************************************************************************/

/******************************************************************************/
/* FSH_Sequence
 *
 * The function sends the modify flash sequence.
/******************************************************************************/
inline void FSH_Sequence(void)
{
    asm("MOVLW 55h");
    asm("MOVWF EECON2");    // write 55h
    asm("MOVLW 0AAh");
    asm("MOVWF EECON2");     // write 0AAh 
}

/******************************************************************************/
/* Functions
/******************************************************************************/

/******************************************************************************/
/* InitFlash
 *
 * The function initializes the internal flash modification functions.
/******************************************************************************/
void InitFlash(void)
{
    /* Nothing to do here */
    Nop();
}

/******************************************************************************/
/* FSH_EraseBlock
 *
 * The function erases a block of memory from internal flash. Each block is
 *  1024 bytes.
/******************************************************************************/
void FSH_EraseBlock(unsigned long Address)
{
    unsigned char highint = INTCONbits.GIE;
    unsigned char lowint  = INTCONbits.PEIE;
    unsigned char WriteTries;
    unsigned long i;
    
    INTCONbits.GIE = 0;     // Disable high priority interrupts
    INTCONbits.PEIE = 0;    // Disable low priority interrupts
    
    restart:
    FSH_AddressToBlock(Address);  // Load table pointer
    
    WriteTries = 1;
    
    EECON1bits.WRERR = 0;       // clear error
    EECON1bits.WREN = 1;        // Allows write cycles to Flash program
    EECON1bits.FREE = 1;        // Performs an erase operation on the next WR command (cleared by completion of erase operation)
    FSH_Sequence();
    EECON1bits.WR = 1;          // begin erase cycle
    NOP();
    NOP();
    MSC_DelayMS(500);
    
    EECON1bits.WREN = 0;        // Inhibits write cycles to Flash program 
    if(EECON1bits.WRERR)
    {
        WriteTries++;
        if(WriteTries < WRITETRIES)
        {
            goto restart;
        }      
    }
    
    if(highint)
    {
        INTCONbits.GIE = 1;     // Enable high priority interrupts
    }
    if(lowint)
    {
        INTCONbits.PEIE = 1;    // Enable low priority interrupts    
    }
}

/******************************************************************************/
/* FSH_WriteIntArray
 *
 * The function writes 64 bytes of an int array making 32 entries.
/******************************************************************************/
void FSH_WriteIntArray(unsigned int* Array)
{
    unsigned char i;
    
    FSH_AddressToBlock(Array);  // Load table pointer
        
    for(i = 0; i<32; i++)
    {
        /* write the first quarter of the IR code*/
        TABLAT =(Array[i] & 0xFF00) >> 8;
        asm("TBLWT*+"); // TBLPTR is incremented after the read/write
        TABLAT = (Array[i] & 0x00FF);
        asm("TBLWT*+"); // TBLPTR is incremented after the read/write
    }
    EECON1bits.WRERR = 0;       // clear error
    EECON1bits.WREN = 1;        // Allows write cycles to Flash program    
    EECON1bits.FREE = 0;        // Perform write only
    FSH_Sequence();
    EECON1bits.WR = 1;          // begin erase cycle
    while(EECON1bits.WRERR);
    EECON1bits.WREN = 0;        // Inhibits write cycles to Flash program 
}

/******************************************************************************/
/* FSH_VerifyWriteIntArray
 *
 * The function checks the 64 byte write of an int array.
/******************************************************************************/
unsigned char FSH_VerifyWriteIntArray(const unsigned int* ConstArray, unsigned int* Array)
{
    unsigned char i;
        
    for(i = 0; i<32; i++)
    {
        if(ConstArray[i] != Array[i])
        {
            return FAIL;
        }
    }
    return PASS;
}

/******************************************************************************/
/* FSH_WriteBlock
 *
 * The function writes to a block of memory from the ram. Each writes is
 *  128 bytes.
/******************************************************************************/
unsigned char FSH_Write_IR_RF(void)
{
    unsigned int i;
    unsigned char j;
    unsigned char highint = INTCONbits.GIE;
    unsigned char lowint  = INTCONbits.PEIE;
    unsigned char WriteTries;
    unsigned char status = FAIL;
    unsigned int FlashWasteindex = 0;
    
    INTCONbits.GIE = 0;     // Disable high priority interrupts
    INTCONbits.PEIE = 0;    // Disable low priority interrupts
    
    if(IR_Saved == NEW && RF_Saved == NEW)
    {
        /* both are trying to be saved which should be impossible */
        IR_Saved = OLD;
        RF_Saved = OLD;
        goto END;
    }
    else if(IR_Saved != NEW && RF_Saved != NEW)
    {
        /* nothing is new */
        IR_Saved = OLD;
        RF_Saved = OLD;
        goto END;
    }
        
    if(IR_Saved == NEW)
    {
        /* the IR code is new so load the old RF code for reflash */
        RF_ResetData();
        MSC_BufferCopyIntConst(&RF_SavedTiming,&RF_DataTiming, RFBUFFERSIZE, 0);
    }
    else
    {
        /* the RF code is new so load the old IR code for reflash */
        IR_ResetData();
        MSC_BufferCopyIntConst(&IR_SavedTiming,&IR_DataTiming, IRBUFFERSIZE, 0);
    }
    
    FSH_EraseBlock(&IR_SavedTiming);
    
    /* the write is 64 bytes at a time so this occurs in 16 different phases */
    
    /*~~~~~~~~~~~~~~~~~~~~ write 1 of 16 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    WriteTries = 1;
    
    REDO1:
    /* write array */
    FSH_WriteIntArray(&IR_SavedTiming[0]);
        
    /* Verify write */
    if(!FSH_VerifyWriteIntArray(&IR_SavedTiming[0],&IR_DataTiming[0]))
    {
        WriteTries++;
        if(WriteTries > WRITETRIES)
        {
            status = FAIL;
            goto END;
        }
        else
        {
            goto REDO1;
        }
    }
    
    /*~~~~~~~~~~~~~~~~~~~~ write 2 of 16 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    WriteTries = 1;
    
    REDO2:
    /* write array */
    FSH_WriteIntArray(&IR_SavedTiming[32]);
        
    /* Verify write */
    if(!FSH_VerifyWriteIntArray(&IR_SavedTiming[32],&IR_DataTiming[32]))
    {
        WriteTries++;
        if(WriteTries > WRITETRIES)
        {
            status = FAIL;
            goto END;
        }
        else
        {
            goto REDO2;
        }
    }
    
    /*~~~~~~~~~~~~~~~~~~~~ write 3 of 16 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    WriteTries = 1;
    
    REDO3:
    /* write array */
    FSH_WriteIntArray(&IR_SavedTiming[64]);
        
    /* Verify write */
    if(!FSH_VerifyWriteIntArray(&IR_SavedTiming[64],&IR_DataTiming[64]))
    {
        WriteTries++;
        if(WriteTries > WRITETRIES)
        {
            status = FAIL;
            goto END;
        }
        else
        {
            goto REDO3;
        }
    }
    
    /*~~~~~~~~~~~~~~~~~~~~ write 4 of 16 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    WriteTries = 1;
    
    REDO4:
    /* write array */
    FSH_WriteIntArray(&IR_SavedTiming[96]);
        
    /* Verify write */
    if(!FSH_VerifyWriteIntArray(&IR_SavedTiming[96],&IR_DataTiming[96]))
    {
        WriteTries++;
        if(WriteTries > WRITETRIES)
        {
            status = FAIL;
            goto END;
        }
        else
        {
            goto REDO4;
        }
    }
    
    /*~~~~~~~~~~~~~~~~~~~~ write 5 of 16 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    WriteTries = 1;
    
    REDO5:
    /* write array */
    FSH_WriteIntArray(&RF_SavedTiming[0]);
        
    /* Verify write */
    if(!FSH_VerifyWriteIntArray(&RF_SavedTiming[0],&RF_DataTiming[0]))
    {
        WriteTries++;
        if(WriteTries > WRITETRIES)
        {
            status = FAIL;
            goto END;
        }
        else
        {
            goto REDO5;
        }
    }
    
    /*~~~~~~~~~~~~~~~~~~~~ write 6 of 16 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    WriteTries = 1;
    
    REDO6:
    /* write array */
    FSH_WriteIntArray(&RF_SavedTiming[32]);
        
    /* Verify write */
    if(!FSH_VerifyWriteIntArray(&RF_SavedTiming[32],&RF_DataTiming[32]))
    {
        WriteTries++;
        if(WriteTries > WRITETRIES)
        {
            status = FAIL;
            goto END;
        }
        else
        {
            goto REDO6;
        }
    }
    
    /*~~~~~~~~~~~~~~~~~~~~ write 7 of 16 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    WriteTries = 1;
    
    REDO7:
    /* write array */
    FSH_WriteIntArray(&RF_SavedTiming[64]);
        
    /* Verify write */
    if(!FSH_VerifyWriteIntArray(&RF_SavedTiming[64],&RF_DataTiming[64]))
    {
        WriteTries++;
        if(WriteTries > WRITETRIES)
        {
            status = FAIL;
            goto END;
        }
        else
        {
            goto REDO7;
        }
    }
    
    /*~~~~~~~~~~~~~~~~~~~~ write 8 of 16 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    WriteTries = 1;
    
    REDO8:
    /* write array */
    FSH_WriteIntArray(&RF_SavedTiming[96]);
        
    /* Verify write */
    if(!FSH_VerifyWriteIntArray(&RF_SavedTiming[96],&RF_DataTiming[96]))
    {
        WriteTries++;
        if(WriteTries > WRITETRIES)
        {
            status = FAIL;
            goto END;
        }
        else
        {
            goto REDO8;
        }
    }
        
    /*~~~~~~~~~~~~~~~~~~~~ write 9 through 16 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(j=8;j<16;j++)
    {
        WriteTries = 1;

        REDO9:
        i=0;
        FlashWasteindex = i + 64*(j-8);
        FSH_AddressToBlock(&FlashWaste[FlashWasteindex]);  // Load table pointer
        for(i = 0; i<64; i++)
        {
            /* write the first half of the IR code*/
            TABLAT = WASTEFLAG;
            asm("TBLWT*+"); // TBLPTR is incremented after the read/write
        }
        EECON1bits.WREN = 1;        // Allows write cycles to Flash program    
        EECON1bits.FREE = 0;        // Perform write only
        FSH_Sequence();
        EECON1bits.WR = 1;          // begin erase cycle
        EECON1bits.WREN = 1;        // Inhibits write cycles to Flash program 
        
        /* Verify write */
        for(i=0; i<64;i++)
        {            
            if(FlashWaste[FlashWasteindex] != WASTEFLAG)
            {
                WriteTries++;
                if(WriteTries > WRITETRIES)
                {
                    status = FAIL;
                    goto END;
                }
                else
                {
                    goto REDO9;
                }
            }
            FlashWasteindex++;
        }
    }
    status = PASS;
    
    END:
    if(highint)
    {
        INTCONbits.GIE = 1;     // Enable high priority interrupts
    }
    if(lowint)
    {
        INTCONbits.PEIE = 1;    // Enable low priority interrupts    
    }
    return status;
}

/******************************************************************************/
/* FSH_BlockToAddress
 *
 * The function erases a block of memory from internal flash. Each block is
 *  1024 bytes.
/******************************************************************************/
void FSH_AddressToBlock(unsigned long Address)
{    
    TBLPTRU = (Address & 0x002F0000) >> 16;
    TBLPTRH = (Address & 0x0000FF00) >> 8;
    TBLPTRL = (Address & 0x000000FF);
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/