//-----------------------------------------------------------------------------
//
//	FILE:		main.c
//
//	DESC:		This has the main function for the a64Thunk sample. The focus
//				of the sample is to describe the thunking interface layer that
//				Audio64 uses to support alternate libraries in place of the
//				default (e.g., Shinobi.lib).
//
//				This scaffolding is a statically bound mechanism. (It replaces
//				the previous dynamically bound setup.) The change streamline
//				internal library operation and is more palatable should
//				changes ever be required.
//
//				The default source/headers define AUDIO64_THUNKS_SHINOBI that
//				compiles the default functions contained in the Audio64
//				library.
//
//					a64chain.h		a64dma.h	a64file.h	a64thunk.h
//					a64chain.c		a64dma.c	a64file.c
//
//				To make changes, compile the source module (e.g., a64file.c)
//				as part of your application. When the linker attemps to
//				resolve references to the public/exported functions/data,
//				the "local" copy will override the library copy.
//
//				CAUTION:	Keep in mind that any changes will affect the
//							manner that your application works with the
//							Audio64 library. The existing functions and data
//							must be preserved, otherwise the linker will fail
//							with "duplicate symbols" errors.
//
//	HISTORY:	2000.01.xx	Reworked samples/boilerplates for R10 release.
//
//-----------------------------------------------------------------------------
//
// COPYRIGHT (C) SEGA OF AMERICA, INC. 1998, 1999, 2000
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

MAINFUNC(void)
{
	SYS_RTC_DATE start;
	SYS_RTC_DATE current;

	SHINOBI_WORKAROUND;
	setupNinja();
	syRtcGetDate(&start);

	//	Calling bpAcSetup(...), the following thunks will be invoked:
	//
	//		a64ChainAddHandler(...)
	//		a64DmaSuspendAll(...)
	//		a64DmaResumeAll(...)
	//		a64FileInit(...)
	//		a64FileOpen(...)
	//		a64FileClose(...)
	//		a64FileRead(...)
	//		a64FileGetSize(...)
	//		a64FileLoad(...)

	acASEBRK(!bpAcSetup(AC_DRIVER_DA, KTFALSE, KTNULL));

	while (KTTRUE)
	{
		syRtcGetDate(&current);

		bpPrintf(INFO_0_X, INFO_0_Y, "Audio64 A64 Thunk Sample");
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
 	/* Check the cable for NTSC/PAL or VGA.. works properly for SCART. */
    switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            sbInitSystem (NJD_RESOLUTION_640x480_NTSCNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz). */
            sbInitSystem (NJD_RESOLUTION_640x544_PALNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
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
