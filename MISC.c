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
/* Contains Miscellaneous Functions
 *
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include <math.h>        /* For true/false definition */

#include "MISC.h"
#include "SYSTEM.h"
#include "USER.h"

/******************************************************************************/
/* Inline Functions                                                           */
/******************************************************************************/

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

/******************************************************************************/
/* MSC_DelayMS
 * Input the number in milliseconds to be delayed.
 *
 * The function waists loops for the entered number of cycles.
 * The actual delay can be skewed when interrupts are enabled.
/******************************************************************************/
void MSC_DelayMS(long US)
{
    long i;

    for(i=0; i<US; i++)
    {
        MSC_DelayNOP(NOPS_DELAYMS);
    }
}

/******************************************************************************/
/* MSC_DelayNOP
 *
 * The function waists the number of cycles passed into the function.
/******************************************************************************/
void MSC_DelayNOP(unsigned int NOPs)
{
    unsigned int i;
    for(i=0; i<NOPs; i++)
    {
        Nop();
    }
}

/******************************************************************************/
/* MSC_CleanBuffer
 *
 * This function sets an amount of data in the array as 0.
/******************************************************************************/
void MSC_CleanBuffer(unsigned char* data, unsigned int count)
{
    unsigned int i=0;
    for(i=0; i<count;i++)
    {
        data[i]= 0;
    }
}

/******************************************************************************/
/* MSC_CleanBufferInt
 *
 * This function sets an amount of data in the array as 0.
/******************************************************************************/
void MSC_CleanBufferInt(unsigned int* data, unsigned int count)
{
    unsigned int i=0;
    for(i=0; i<count;i++)
    {
        data[i]= 0;
    }
}

/******************************************************************************/
/* MSC_BufferCopy
 *
 * This function copies the 'from' array to the 'to' array.
/******************************************************************************/
void MSC_BufferCopy(unsigned char* from,unsigned char* to, unsigned int count, unsigned int shift)
{
    unsigned int i=0;
    MSC_CleanBuffer(to,count);
    for(i = shift; i>0; i--)
    {
        *to = ' ';
        to++;
    }
    while(*from != 0 && count >0)
    {
        *to = *from;
        from++;
        to++;
        count--;
    }
}

/******************************************************************************/
/* MSC_BufferCopyInt
 *
 * This function copies the 'from' array to the 'to' array.
/******************************************************************************/
void MSC_BufferCopyInt(unsigned int* from,unsigned int* to, unsigned int count, unsigned int shift)
{
    unsigned int i=0;
    MSC_CleanBufferInt(to,count);
    for(i = shift; i>0; i--)
    {
        *to = ' ';
        to++;
    }
    while(*from != 0 && count >0)
    {
        *to = *from;
        from++;
        to++;
        count--;
    }
}

/******************************************************************************/
/* MSC_BufferCopyIntConst
 *
 * This function copies the 'from' array to the 'to' array.
/******************************************************************************/
void MSC_BufferCopyIntConst(const unsigned int* from,unsigned int* to, unsigned int count, unsigned int shift)
{
    unsigned int i=0;
    MSC_CleanBufferInt(to,count);
    for(i = shift; i>0; i--)
    {
        *to = ' ';
        to++;
    }
    while(*from != 0 && count >0)
    {
        *to = *from;
        from++;
        to++;
        count--;
    }
}

/******************************************************************************/
/* MSC_BlinkLED
 *
 * This function blinks the LED a certain number of times.
/******************************************************************************/
void MSC_BlinkLED(unsigned int blink, unsigned int speed)
{
    unsigned int i;
    
    for(i=0;i<(blink<<1);i++)
    {
        MSC_DelayMS(speed);
        MSC_RedLEDTOGGLE();
    }
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/