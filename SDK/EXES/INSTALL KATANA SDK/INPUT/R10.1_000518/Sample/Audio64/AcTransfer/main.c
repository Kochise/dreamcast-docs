//-----------------------------------------------------------------------------
//
//	FILE:		main.c
//
//	DESC:		This has the main function for the acTransfer() sample. The
//				sample is a suggested setup for using AICA DMA for Audio64
//				transfers. The focus here is very specific; this is
//				essentially a DMA sample that happens to access AICA memory
//				and the AICA DMA.
//
//	HISTORY:	2000.01.xx	Reworked samples/boilerplates for R10 release.
//
//-----------------------------------------------------------------------------
//
// COPYRIGHT (C) SEGA OF AMERICA DREAMCAST, INC. 1998, 1999, 2000
// All rights reserved.
//
// Information and source code samples contained herein are  provided "as-is",
// without representations or warranties, and are subject to change without
// notice.
//
// SEGA OF AMERICA DREAMCAST, INC. cannot support modifications or derivative
// works created from the sample source code provided. Developers may use,
// reproduce, and modify portions or entire sections of the sample source code
// for the purposes of creating Dreamcast applications.  
//
// Sample source code contained herein may not be appropriate for use under
// all circumstances. Please consult Developer documentation provided along
// with your Dreamcast unit for additional information and suggestions.
//
//-----------------------------------------------------------------------------

#include <shinobi.h>
#include <ac.h>
#include <a64thunk.h>
#include <am.h>

#include "bpacsetup.h"
#include "bpbuttons.h"
#include "bpprintf.h"

//-----------------------------------------------------------------------------

#ifdef __GNUC__
#define MAINFUNC						int main
#define RETURN							return (0)
#define ABORT							acASEBRK(1)
#define SHINOBI_WORKAROUND				shinobi_workaround()
#else
#define MAINFUNC						void main
#define RETURN							return
#define ABORT							acASEBRK(1)
#define SHINOBI_WORKAROUND
#endif

//-----------------------------------------------------------------------------

void setupNinja(void);

//-----------------------------------------------------------------------------

typedef struct
{
	AC_TRANSFER_REQUEST request;	// <-- required by the AC Transfer Manager
	KTBOOL allocated;
} AC_TRANSFER_POOL;

AC_TRANSFER_POOL ioPool[AC_MAX_TRANSFER_QUEUE];

volatile KTU32 ioPending = 0;
volatile KTU32 ioTotal = 0;

enum { BUFFER_SIZE = 8192 };

KTU32 *sh4Mem = KTNULL;
KTU32 *aicaMem = KTNULL;

//-----------------------------------------------------------------------------

KTBOOL allocBlock(AC_TRANSFER_REQUEST **request)
{
	// simple linear search allocation scheme
	KTU32 i;
	KTU32 imask = acCkset_imask(AC_CRITICAL_IML);
	for (i = 0; i < AC_MAX_TRANSFER_QUEUE; i++)
	{
		if (!ioPool[i].allocated)
		{
			ioPool[i].allocated = KTTRUE;
			*request = (AC_TRANSFER_REQUEST*)&ioPool[i];

			ioPending++;

			set_imask(imask);
			return (KTTRUE);
		}
	}
	set_imask(imask);
	return (KTFALSE);
}

//-----------------------------------------------------------------------------

void freeBlock(AC_TRANSFER_REQUEST *request)
{
	KTU32 imask = acCkset_imask(AC_CRITICAL_IML);

	// a good spot for some form of error checking
	acASEBRK(
		(request->status != AC_TRANSFER_COMPLETE) &&
		(request->status != AC_TRANSFER_QUEUE_FULL));

	request->aicaMem = KTNULL;
	request->sh4Mem = KTNULL;
	request->size = 0;
	request->direction = 0;
	request->status = AC_NO_ERROR;
	request->callback = KTNULL;

	((AC_TRANSFER_POOL*)request)->allocated = KTFALSE;

	ioPending--;
	set_imask(imask);
}

//-----------------------------------------------------------------------------

MAINFUNC(void)
{
	SYS_RTC_DATE start;
	SYS_RTC_DATE current;

	SHINOBI_WORKAROUND;
	setupNinja();
	syRtcGetDate(&start);

	acASEBRK(!bpAcSetup(AC_DRIVER_DA, KTFALSE, KTNULL));
	acASEBRK(!acSetTransferMode(AC_TRANSFER_DMA));

	acASEBRK(!(sh4Mem = (KTU32*)syMalloc(BUFFER_SIZE)));
	memset(sh4Mem, 0, BUFFER_SIZE);

	// allocation assumption valid for this sample
	aicaMem = acSystemGetFirstFreeSoundMemory();
	acG2Fill(aicaMem, 0, BUFFER_SIZE);

	while (KTTRUE)
	{
		KTU32 i;
		KTU32 sh4Data;
		KTU32 aicaData;

		syRtcGetDate(&current);
		sh4Data = *(KTU32*)sh4Mem;
		acASEBRK(!acG2ReadLong(aicaMem, &aicaData));
		acASEBRK(sh4Data != aicaData);

		bpPrintf(INFO_0_X, INFO_0_Y, "Audio64 AC Transfer (DMA) Sample");
		bpPrintf(INFO_1_X, INFO_1_Y, "Start:  %02d/%02d %02d:%02d:%02d",
										start.month,
										start.day,
										start.hour,
										start.minute,
										start.second);
		bpPrintf(INFO_2_X, INFO_2_Y, "Current:%02d/%02d %02d:%02d:%02d",
										current.month,
										current.day,
										current.hour,
										current.minute,
										current.second);
		bpPrintf(INFO_3_X, INFO_3_Y,
							"pending:%08x     total:%08x", ioPending, ioTotal);
		bpPrintf(INFO_4_X, INFO_4_Y,
							" sh4Mem:%08x   sh4Data:%08x", sh4Mem, sh4Data);
		bpPrintf(INFO_5_X, INFO_5_Y,
							"aicaMem:%08x  aicaData:%08x", aicaMem, aicaData);

		for (i = 0; i < AC_MAX_TRANSFER_QUEUE; i++)
		{
			AC_TRANSFER_REQUEST *request;
			if (allocBlock(&request))
			{
				memset(sh4Mem, ioTotal, BUFFER_SIZE);

				request->aicaMem = aicaMem;
				request->sh4Mem = sh4Mem;
				request->size = BUFFER_SIZE;
				// direction (0: SH4->AICA, 1: AICA->SH4)
				request->direction = (ioTotal & 1);
				request->status = AC_NO_ERROR;
				request->callback = freeBlock;

				if (!acTransfer(request))
				{
					freeBlock(request);
					break;
				}

				ioTotal++;
			}
		}
		njWaitVSync();
	}

	//	Shutdown the AC layer
	bpAcShutdown();

	// a chance for one last look around
	ABORT;
}

//-----------------------------------------------------------------------------

void setupNinja(void)
{
	njSetBorderColor(0x00000000);

switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            sbInitSystem (NJD_RESOLUTION_640x480_NTSCNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz). */
            sbInitSystem (NJD_RESOLUTION_640x544_PALNI,NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_VGA:   /* Standard VGA. */
            sbInitSystem (NJD_RESOLUTION_VGA, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        default:
            syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}
	njInitVertexBuffer(20000, 0, 20000, 0, 0);
	njInitPrint(NULL, 0, NJD_TEXFMT_ARGB_1555);
	njSetBackColor(0x00000000, 0x00000000, 0x000000FF);
	njPrintSize(12);	
}
