//-----------------------------------------------------------------------------
//
//	FILE:		main.c
//
//	DESC:		This has the main function for the AcDsp testbed. In the
//				sample the AC layer is used to play a raw sound file, sound
//				memory is manually allocated by the numbers.
//
//				In the example's output bank the output assignments are
//				channel 0 Reverb, channels 12-15 are 4 channels of Q Sound,
//				and the remainder of the channels are unassigned.
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
#define MAINFUNC					int main
#define RETURN						return (0)
#define ABORT						acASEBRK(KTTRUE)
#define SHINOBI_WORKAROUND			shinobi_workaround()
#else
#define MAINFUNC					void main
#define RETURN						return
#define ABORT						acASEBRK(KTTRUE)
#define SHINOBI_WORKAROUND
#endif

//-----------------------------------------------------------------------------

#define RAW_SOUND_BANK				"glass.pcm"
#define DSP_PROGRAM_BANK			"rvbqsnd.fpb"
#define DSP_OUTPUT_BANK				"rvbqsnd.fob"

#define VOICE_ONLY					0
#define VOICE_FX					1

//-----------------------------------------------------------------------------

KTBOOL loadBank(KTU32 *aica, KTSTRING name, KTU32 *size);
void setupNinja(void);

//-----------------------------------------------------------------------------

MAINFUNC(void)
{
	KTU32 *nextFree = KTNULL;
	KTU32 *image = KTNULL;
	KTU32 imageSize = 0;
	KTU32 size = 0;
	SYS_RTC_DATE start;
	SYS_RTC_DATE current;
	KTU32 daCount;
	KTU32 midiCount;

	SHINOBI_WORKAROUND;
	setupNinja();
	syRtcGetDate(&start);

	//	Init the AC layer
	if (!bpAcSetup(AC_DRIVER_DA, KTFALSE, KTNULL))
	{
		ABORT;
	}
	
	//	Get the beginning of free sound (AICA) memory
	nextFree = acSystemGetFirstFreeSoundMemory();

	//	RAW_SOUND_BANK: Load the sound
	if (!loadBank(nextFree, RAW_SOUND_BANK, &size))
	{
		ABORT;
	}
	//	RAW_SOUND_BANK: Open the voice channel(s)
	if ((!acDigiOpen(VOICE_ONLY, (KTU32)nextFree, size, AC_16BIT, 44100))
	|| (!acDigiOpen(VOICE_FX, (KTU32)nextFree, size, AC_16BIT, 44100)))
	{
		ABORT;
	}
	//	RAW_SOUND_BANK: Set the volume(s)
	if ((!acDigiSetVolume(VOICE_ONLY, 255))
	|| (!acDigiSetVolume(VOICE_FX, 255)))
	{
		ABORT;
	}

	//	Increment to the next free AICA memory
	nextFree = (KTU32*)((KTU32)nextFree + ALIGN(size, 4));

	//	DSP_PROGRAM_BANK: Load the FX program bank (*.fpb)
	if (!loadBank(nextFree, DSP_PROGRAM_BANK, &size))
	{
		ABORT;
	}
	//	DSP_PROGRAM_BANK: Install the FX program bank
	if (!acDspInstallProgram((KTU32)nextFree, size))
	{
		ABORT;
	}

	//	Increment to the next free AICA memory
	nextFree = (KTU32*)((KTU32)nextFree + ALIGN(size, 4));

	//	DSP_OUTPUT_BANK: Load the FX output bank (*.fob)
	if (!loadBank(nextFree, DSP_OUTPUT_BANK, &size))
	{
		ABORT;
	}
	//	DSP_OUTPUT_BANK: Install the FX output bank
	if (!acDspInstallOutputMixer((KTU32)nextFree, size))
	{
		ABORT;
	}
	//	DSP_OUTPUT_BANK: Effects mix for VOICE_FX voice only
	if (!acDspSetMixerChannel(VOICE_FX, 0, 15, 15))
	{
		ABORT;
	}

	while (KTTRUE)
	{
		PDS_PERIPHERAL *pad = (PDS_PERIPHERAL*)njGetPeripheral(NJD_PORT_A0);

		syRtcGetDate(&current);
		acDigiPortsAvailable(&daCount, &midiCount);

		bpPrintf(INFO_0_X, INFO_0_Y, "Audio64 AC DSP Sample");
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
		bpPrintf(INFO_3_X, INFO_3_Y, "free:  da:%02u  midi:%02u", daCount, midiCount);
		bpPrintf(INFO_4_X, INFO_4_Y, "A     : Play Sound");
		bpPrintf(INFO_5_X, INFO_5_Y, "B     : Play Sound + Effect");
		bpPrintf(INFO_6_X, INFO_6_Y, "START : Exit");

		if (pad->press & NJD_DGT_TA)
		{
			if (!acDigiPlay(VOICE_ONLY, 0, AC_LOOP_OFF))
			{
				ABORT;
			}
		}
		if (pad->press & NJD_DGT_TB)
		{
			if (!acDigiPlay(VOICE_FX, 0, AC_LOOP_OFF))
			{
				ABORT;
			}
		}
		if (pad->press & NJD_DGT_ST)
		{
			// End the program by jumping to the Boot ROM
			sbExitSystem();
			syBtExit();
		}

		njWaitVSync();
	}

	if ((!acDigiStop(VOICE_ONLY) || !acDigiClose(VOICE_ONLY))
	|| (!acDigiStop(VOICE_FX) || !acDigiClose(VOICE_FX)))
	{
		ABORT;
	}

	//	Shutdown the AC layer
	bpAcShutdown();

	// a chance for one last look around
	ABORT;
}

//-----------------------------------------------------------------------------

KTBOOL loadBank(KTU32 *aica, KTSTRING name, KTU32 *size)
{
	KTU32 *image = KTNULL;
	KTU32 imageSize = 0;

	//	Get the size of the bank to be loaded
	if (!a64FileGetSize(name, size))
	{
		return (KTFALSE);
	}

	//	Align for loading from GD-ROM
	imageSize = ALIGN(*size, SECTOR_SIZE);
	
	//	Allocate a loading buffer in SH4 memory (using aligned size)
	image = (KTU32*)syMalloc(imageSize);
	if (!image)
	{
		return (KTFALSE);
	}
	
	//	Load the bank (using aligned size)
	if (!a64FileLoad(name, image, imageSize))
	{
		return (KTFALSE);
	}
	
	//	Copy to AICA memory (using actual size)
	acG2Write(aica, image, *size);	

	//	Free the loading buffer
	syFree(image);

	return (KTTRUE);
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
