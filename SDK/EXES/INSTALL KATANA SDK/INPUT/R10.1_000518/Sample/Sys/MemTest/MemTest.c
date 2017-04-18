/********************************************************************************************/
/* CONFIDENTIAL AND PROPRIETARY:                                                            */
/*      Copyright 1998, Sega of America.  All rights reserved.                              */
/*      This sample source code is provided for demonstration purposes only.                */
/*      Use and distribution of Sega proprietary material is governed by                    */
/*      developer licensing agreement.                                                      */
/********************************************************************************************/

/********************************************************************************************/
/* Name:     MemTest.c                                                                      */
/* Title:    Memory Allocation Test                                                         */
/* Author:   Gary Lake                                                                      */
/* Created:  February 22, 1999                                                              */
/*                                                                                          */
/* Version:  1.0                                                                            */
/* Platform: Dreamcast | Set5.24 | Shinobi                                                  */
/*                                                                                          */
/* Description:                                                                             */
/*      This testbench utility verifies the functionality of syMalloc() / syFree().         */
/*                                                                                          */
/* History:                                                                                 */
/*      02/22/98 - Program created (Gary Lake).                                             */
/********************************************************************************************/


/********************************************************************************************/
/* Includes                                                                                 */
/********************************************************************************************/

#include <shinobi.h>    /* Shinobi system routines. */
#include <kamui2.h>      /* Kamui low-level graphics HAL. */
#include <sn_fcntl.h>   /* LibCross file types. */
#include <usrsnasm.h>   /* LibCross I/O routines. */
#include <sg_syCbl.h>   /* NTSC/RGB/VGA Cable check interface. */


/********************************************************************************************/
/* Definitions                                                                              */
/********************************************************************************************/

#define STDOUT  1       /* For output to the Codescape log window. */


/********************************************************************************************/
/* Macros                                                                                   */
/********************************************************************************************/

/* Dump the syMalloc() memory statistics to the console. */
#define DumpMallocStats()                                               \
{                                                                       \
    syMallocStat (&FreeBytes, &MaxFreeBlock);                           \
                                                                        \
    sprintf (TmpString, "Free Memory: %d bytes", FreeBytes);            \
    debug_write (SNASM_STDOUT, TmpString, strlen (TmpString));          \
    sprintf (TmpString, "Max Free Block: %d bytes", MaxFreeBlock);      \
    debug_write (SNASM_STDOUT, TmpString, strlen (TmpString));          \
}


/********************************************************************************************/
/* Functions & Procedures                                                                   */
/********************************************************************************************/

void main(void)
{
    char            TmpString[80];
    long            *MemTable[1024];
    unsigned long   FreeBytes, MaxFreeBlock;
    unsigned int    Entries, Block, Size, Total, Padding;
    int             i;

#ifdef __GNUC__
    shinobi_workaround();
#endif
    /* Tell the user about this app. */
    debug_write (SNASM_STDOUT, "MemTest: Test the functionality of syMalloc()/syFree()", 56);

    /* Check the cable for NTSC/PAL or VGA.. works properly for SCART. */
    switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            sbInitSystem (KM_DSPMODE_NTSCNI640x480, KM_DSPBPP_RGB565, 1);
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz). */
            sbInitSystem (KM_DSPMODE_PALNI640x480, KM_DSPBPP_RGB565, 1);
            break;
        case SYE_CBL_VGA:   /* Standard VGA. */
            sbInitSystem (KM_DSPMODE_VGA, KM_DSPBPP_RGB565, 1);
            break;
        default:
            syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}

    DumpMallocStats();

    while (1)
    {
        Size = MaxFreeBlock / 4;
        Entries = (rand() % 1023) + 1;
        Total = 0;
        Padding = 0;
        sprintf (TmpString, "Allocating %d memory regions:", Entries);
        debug_write (SNASM_STDOUT, TmpString, strlen (TmpString));

        for (i = 0; i < Entries; i++)
        {
            if (Size < (Entries * 16))
                Block = 1;
            else
                Block = (rand() % (Size / (Entries - i))) + 1;

            MemTable[i] = syMalloc (Block * 4);
            if (MemTable[i] == NULL)
                debug_write (SNASM_STDOUT, "Error: syMalloc() returned NULL", 31);
            else
                *MemTable[i] = (unsigned long) MemTable[i];
            Size -= Block;

            if ((unsigned long) MemTable[i] & 0x1F)
                debug_write (SNASM_STDOUT, "Error: not 32-byte aligned", 26);

            syMallocStat (&FreeBytes, &MaxFreeBlock);
            Total += (Block * 4);
            Padding += ((Size * 4) - MaxFreeBlock);
            Size = MaxFreeBlock / 4;
        }

        sprintf (TmpString, "%d bytes allocated + %d bytes padding (avg. padding %d bytes)",
            Total, Padding, (Padding / Entries));
        debug_write (SNASM_STDOUT, TmpString, strlen (TmpString));

        DumpMallocStats();

        sprintf (TmpString, "Freeing %d memory regions:", Entries);
        debug_write (SNASM_STDOUT, TmpString, strlen (TmpString));
        for (i = Entries - 1; i >= 0; i--)
        {
            if (*MemTable[i] != (unsigned long) MemTable[i])
                debug_write (SNASM_STDOUT, "Error: Value does not match", 27);
            syFree (MemTable[i]);
        }

        DumpMallocStats();

        debug_write (SNASM_STDOUT, "Done", 4);
    }

    sbExitSystem();
}