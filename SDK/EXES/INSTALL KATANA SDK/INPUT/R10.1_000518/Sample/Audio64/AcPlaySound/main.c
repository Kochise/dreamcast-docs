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

//-----------------------------------------------------------------------------

KTBOOL loadBank(KTU32 *aica, KTSTRING name, KTU32 *size);
void setupNinja(void);

KTU32 voiceChannel					=		10;
volatile char statusMessage[80]				= {""};
//-----------------------------------------------------------------------------
void soundCallback(KTU32 id)			// the MIDI callback proc
{
	if(voiceChannel==id)
	{
/* optional for R10
		if(!acDigiStop(voiceChannel))	// if return fails
		{
			strcpy(statusMessage,"Unable to stop voice channel");
			return;
		} 
		if(!acDigiClose(voiceChannel))	// if return fails
		{
			strcpy(statusMessage,"Unable to close voice channel");
			return;
		}
*/
		strcpy(statusMessage,"Voice channel callback received");
	} else {
		switch(id)	
		{
		case 100:
			strcpy(statusMessage,"Voice playback commands processed");
			break;
		case 101:	strcpy(statusMessage,"Filter playback commands processed");
			break;
		case 102:	strcpy(statusMessage,"Amplitude playback commands processed");
			break;
		case 103:	strcpy(statusMessage,"LFO playback commands processed");
			break;
		default:	strcpy(statusMessage,"Message ID not recognized");
			break;
		}
	}
}

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

	KTU32 filterOn						=		1; 		// 	1 for filter on, 0 for off
	KTU32 filterQ 						=		0x10;	//	0x1f is +20.25 db gain, 0 is -3 db decrement, steps in .75
	KTU32 filterValue0 					=		500;		//	cuttoff freq at start attack (13 bits of resolution)
	KTU32 filterValue1 					=		8000;	//	freq at env stage 1
	KTU32 filterValue2					=		4000;	//	freq at env stage 2
	KTU32 filterValue3 					=		6000;	//	freq at env stage 3 (max)
	KTU32 filterValue4 					=		8000;	//	freq at release
	KTU32 filterAttackRate	 			=		24;		//	shortest attack is 31, longest is 0
	KTU32 filterDecayRate1				=		20;
	KTU32 filterDecayRate2 				=		23;
	KTU32 filterReleaseRate				=		20;

	KTU32 ampAttackRate 				=		10;		//	0-31 longest to shortest
	KTU32 ampDecayRate1 				=		10;
	KTU32 ampDecayRate2 				=		10;
	KTU32 ampReleaseRate 				=		10;
	KTU32 ampDecayLevel					=		0;		//	?  amplitude level
	KTU32 ampKeyRateScaling 			=		15;		//	0-14, min to max, 15 is off
	KTU32 ampLoopStartLink				=		00;		// loop start link on
		
	KTU32 lfoReset 						=		0x00;	//	0: don't reset, 1: reset
	KTU32 lfoFrequency 					=		0x14;	//	3.31
	KTU32 pitchLfoWaveShape 			=		0x02;	//	select triangle
	KTU32 pitchLfoDepth 				=		0x07;	//	maximum effect
	KTU32 ampLfoWaveShape				=		0x01;	//	select triangle
	KTU32 ampLfoDepth					=		0x03;

	KTU32 sampleRate					=		22050;	//  adjust length of play

	SHINOBI_WORKAROUND;
	setupNinja();
	syRtcGetDate(&start);

	//	Init the AC layer
	if (!bpAcSetup(AC_DRIVER_DA, KTFALSE, (AC_CALLBACK_HANDLER)soundCallback))
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
/*
	//	RAW_SOUND_BANK: Open the voice channel(s)
	if (!acDigiOpen(voiceChannel, (KTU32)nextFree, size, AC_16BIT, sampleRate))
	{
		ABORT;
	}
	//	RAW_SOUND_BANK: Set the volume(s)
	if (!acDigiSetVolume(voiceChannel, 255))
	{
		ABORT;
	}
*/
	while (KTTRUE)
	{
		PDS_PERIPHERAL *pad = (PDS_PERIPHERAL*)njGetPeripheral(NJD_PORT_A0);

		syRtcGetDate(&current);
		acDigiPortsAvailable(&daCount, &midiCount);

		bpPrintf(INFO_0_X, INFO_0_Y, "Audio64 AC Play Sound Sample");
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
		bpPrintf(INFO_5_X, INFO_5_Y, "B     : Play Sound + Filter");
		bpPrintf(INFO_6_X, INFO_6_Y, "X     : Play Sound + Amplitude Envelope");
		bpPrintf(INFO_7_X, INFO_7_Y, "Y     : Play Sound + LFO");
		bpPrintf(INFO_8_X, INFO_8_Y, "START : Exit");
		bpPrintf(INFO_9_X, INFO_9_Y, "Sound Status: %s",statusMessage);

		if (pad->press & NJD_DGT_TA)
		{
			if (!acDigiOpen(voiceChannel, (KTU32)nextFree, size, AC_16BIT, sampleRate))
				{
					strcpy(statusMessage,"Unable to open voice channel");
				}
			if (!acDigiRequestEvent(voiceChannel, (size >> 1) - 1 ) )
				{
					strcpy(statusMessage,"Unable to send event request for callback");
				}
			if (!acDigiPlay(voiceChannel, 0, AC_LOOP_OFF))
				{
					strcpy(statusMessage,"Unable to play voice channel");
				}
			else
				{
					strcpy(statusMessage,"Playing voice channel");
				}
			if (!acSystemRequestArmInterrupt(100))
				{
					strcpy(statusMessage,"Unable to send Arm Interrupt request");
				}
		}
		if (pad->press & NJD_DGT_TB)
		{
			if (!acDigiOpen(voiceChannel, (KTU32)nextFree, size, AC_16BIT, sampleRate))
				{
					strcpy(statusMessage,"Unable to open voice channel");
				}
			if(acDigiSetFilterEnvelope(voiceChannel,filterOn,filterQ,filterValue0,filterValue1,filterValue2,
								filterValue3,filterValue4,filterAttackRate,filterDecayRate1,
									filterDecayRate2,filterReleaseRate)==KTFALSE)
				{					
					strcpy(statusMessage,"Unable to set filter envelope");
				}
			if (!acDigiRequestEvent(voiceChannel, (size >> 1) - 1 ) )
				{
					strcpy(statusMessage,"Unable to send event request for callback");
				}
			if (!acDigiPlay(voiceChannel, 0, AC_LOOP_OFF))
				{
				strcpy(statusMessage,"Unable to play voice channel");
				}
			else
				{
					strcpy(statusMessage,"Playing voice channel");
				}
			if (!acSystemRequestArmInterrupt(101))
				{
					strcpy(statusMessage,"Unable to send Arm Interrupt request");
				}
		}
		if (pad->press & NJD_DGT_TX)
		{
			if (!acDigiOpen(voiceChannel, (KTU32)nextFree, size, AC_16BIT, sampleRate))
				{
					strcpy(statusMessage,"Unable to open voice channel");
				}
			if(acDigiSetAmplitudeEnvelope(voiceChannel, ampAttackRate, ampDecayRate1, ampDecayRate2, ampReleaseRate, ampDecayLevel,
								ampKeyRateScaling, ampLoopStartLink)==KTFALSE)
				{					
					strcpy(statusMessage,"Unable to set amplitude envelope");
				}
			if (!acDigiRequestEvent(voiceChannel, (size >> 1)-1))
				{
					strcpy(statusMessage,"Unable to send event request for callback");
				}
			if (!acDigiPlay(voiceChannel, 0, AC_LOOP_OFF))
				{
					strcpy(statusMessage,"Unable to play voice channel");
				}
			else
				{
					strcpy(statusMessage,"Playing voice channel");
				}
			if (!acSystemRequestArmInterrupt(102))
				{
					strcpy(statusMessage,"Unable to send Arm Interrupt request");
				}
		}
		if (pad->press & NJD_DGT_TY)
		{
			if (!acDigiOpen(voiceChannel, (KTU32)nextFree, size, AC_16BIT, sampleRate))
			{
				strcpy(statusMessage,"Unable to open voice channel");
			}
			if(acDigiSetLfoRegisters(voiceChannel, lfoReset, lfoFrequency, pitchLfoWaveShape, pitchLfoDepth, ampLfoWaveShape,
								ampLfoDepth)==KTFALSE)
			{					
				ABORT;
			}
			if (!acDigiRequestEvent(voiceChannel, (size >> 1) -1 ))
			{
				strcpy(statusMessage,"Unable to send event request for callback");
			}
			if (!acDigiPlay(voiceChannel, 0, AC_LOOP_OFF))
			{
				strcpy(statusMessage,"Unable to play voice channel");
			} else
			{
				strcpy(statusMessage,"Playing voice channel");
			}
			if (!acSystemRequestArmInterrupt(103))
				{
					strcpy(statusMessage,"Unable to send Arm Interrupt request");
				}
		}
		if (pad->press & NJD_DGT_ST)
		{
			break;
		}

		njWaitVSync();
	}

	if (!acDigiStop(voiceChannel) || !acDigiClose(voiceChannel))
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
	// Check the cable for NTSC/PAL/VGA; works properly for SCART.
	switch (syCblCheck())
	{
		// Initialize the display device and set the frame buffer based on
		// the video mode.
		case SYE_CBL_NTSC:	// 60Hz - US/North America NTSC, Brazil PAL-M
			sbInitSystem(NJD_RESOLUTION_640x480_NTSCNI,
											NJD_FRAMEBUFFER_MODE_RGB565, 1);
			break;
		case SYE_CBL_PAL:	// 50Hz - Europe PAL, Argentina PAL-N
			sbInitSystem(NJD_RESOLUTION_640x544_PALNI,
											NJD_FRAMEBUFFER_MODE_RGB565, 1);
			break;
		case SYE_CBL_VGA:	// Standard VGA
			sbInitSystem(NJD_RESOLUTION_VGA, NJD_FRAMEBUFFER_MODE_RGB565, 1);
			break;
		default:
            syBtExit();     // Unknown video type, return to Dreamcast BootROM.
			break;
	}
	njSetBorderColor(0x00000000);
	njInitVertexBuffer(10000, 0, 10000, 0, 0);
	njInitPrint(NULL, 0, NJD_TEXFMT_ARGB_1555);
	njSetBackColor(0x00000000, 0x00000000, 0x000000FF);
	njPrintSize(12);	
}
