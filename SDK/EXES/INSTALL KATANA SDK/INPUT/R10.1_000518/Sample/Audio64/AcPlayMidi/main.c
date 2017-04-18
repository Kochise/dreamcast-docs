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

//-------------------------- The Assets ---------------------------------------------------

#define MIDI_FILE						"B3.mid"		// standard MIDI Format 0 file
#define MIDI_INSTRUMENT_FILE			"B3.mpb"		// tonebank from Mac tools or dls2tb.exe

#define DIGITAL_VOICES_OFFSET			16			// 0-15 are for digital audio, 16-31 are for MIDI
#define MTHDHEADER_AND_MTRKLITERAL_AND_LENGTH	22	//	14 bytes of MIDI track Header plus 4 bytes of "Mtrk" literal + 4 length

//--------------------- Globals --------------------------------------------------------

KTBOOL loadBank(KTU32 *aica, KTSTRING name, KTU32 *size);
void setupNinja(void);
void changeVolume(char * statusMessage,KTU32 midiPort, KTS32 direction);
volatile KTS32	midiVolume = 64;
volatile KTU32 midiPort	=	0;
volatile char statusMessage[80]				= {""};
KTBOOL	fadeseq		=		KTFALSE;		// enable midi fading if true
KTBOOL	midiPlaying					=	KTFALSE;

//--------------------- The callback to determine end of sequence play -------------------------------------------------------
void soundCallback(KTU32 id)			// the MIDI callback proc
{
	if (id == (midiPort + DIGITAL_VOICES_OFFSET))
	{
		midiPlaying = KTFALSE;
		strcpy(statusMessage,"MIDI callback received");
	}
}

//-----------------------------------------------------------------------------

MAINFUNC(void)
{
	KTU32 *nextFree						=	KTNULL;

	KTU32 *midiSequenceAddress			=	KTNULL;	// here we use a pointer to read sequence info from soundram 
	KTU32 sequenceStartAddress			=	KTNULL;	// this value is passed to driver
	KTU32 sequenceSize;

	KTU32 midiBankAddress;
	KTU32 pulsesPerQuarterNote			=	KTNULL;	// dword aligned read from soundram
	KTU32 pulsesPerQuarterNoteWord		=	KTNULL;	// MIDI sequence resolution (ppqn) is word sized
	
//	KTU8  bankSlot						=	0;		// this actually bombs the binary in codescape
	KTU32 bankSlot						=	0;

	KTU32 gmMode						=	KTFALSE;

//	KTS16 loopMode						=	KTFALSE;	// this alignment also causes a problem
	KTS32 loopMode						=	KTFALSE;

	KTU32 *image = KTNULL;
	KTU32 imageSize = 0;
	KTU32 size = 0;
	SYS_RTC_DATE start;
	SYS_RTC_DATE current;
	KTU32 daCount;
	KTU32 midiCount;

	KTS32	direction					=	1;	// volume fading
	KTU32	callVolumeCount				=	0;	// only fade volume at a rate of 20 times/sec

extern	AC_ERROR_PTR bpAcError;

	


	SHINOBI_WORKAROUND;
	setupNinja();
	syRtcGetDate(&start);

	//	Init the AC layer
	if (!bpAcSetup(AC_DRIVER_MIDI, KTFALSE, soundCallback))
	{
		ABORT;
	}
	
	//	Get the beginning of free sound (AICA) memory
	nextFree = acSystemGetFirstFreeSoundMemory();

	//	RAW_MIDI_FILE: Load the MIDI sequence
	if (!loadBank(nextFree, MIDI_FILE, &size))
	{
		ABORT;
	}
	midiSequenceAddress = nextFree;						// save location for MIDI sequence reads

	sequenceStartAddress = (KTU32)midiSequenceAddress;	// move to unsigned int for number foo
	sequenceStartAddress += MTHDHEADER_AND_MTRKLITERAL_AND_LENGTH;	// point past MIDI header info and MTRK literal in SMF
	sequenceStartAddress &= (KTU32)0x007fffff;			// remove memory mapped part of address for driver address
	sequenceSize = size - MTHDHEADER_AND_MTRKLITERAL_AND_LENGTH;		// save size of sequence MINUS the Mthd (MIDI track header) and Mtrk literal

	if(!acG2ReadLong(midiSequenceAddress + 3,&pulsesPerQuarterNote)) // we need to read the quarternote resolution from MIDI sequence 
	{
		ABORT;
	}

	pulsesPerQuarterNoteWord = (KTU16)(pulsesPerQuarterNote & 0x000000ff) << 8;		// shift word to big Endian format
	pulsesPerQuarterNoteWord|= (KTU16)(pulsesPerQuarterNote & 0x0000ff00) >> 8;

	nextFree += (size + 0x03) & 0xfffffffc;		// get past MIDI file to load instrument bank file (dword align!)

	midiBankAddress	= (KTU32)nextFree;	
	midiBankAddress &= 0x007fffff;	// clear memory mapped upper address
	
		//	RAW_MIDI_FILE: Load the MIDI sequence
	if (!loadBank(nextFree, MIDI_INSTRUMENT_FILE, &size))
	{
		ABORT;
	}

	if (!acMidiSetTonebank(bankSlot, AC_MELODIC_BANK, (KTU32)midiBankAddress, size, KTNULL)) // register the tonebank to the driver
	{														// bankslot is 0-15, must match midi sequence bank nbr (CC 32 slotnbr),
								// melodic or drum bank type, address in soundram, size, midi translate table (not yet implemented)
		ABORT;
	}
	
		if(!acMidiOpen(midiPort,gmMode,sequenceStartAddress,sequenceSize,(KTU32)pulsesPerQuarterNoteWord))	// open with pointer to 1st valid sequence data
	{
		ABORT;
	}

		if(!acMidiRequestEvent(midiPort,(sequenceStartAddress + sequenceSize-8)))
	{
		ABORT;
	}
	
	if(!acMidiPlay(midiPort,0,loopMode))	// kick off the sequence
	{
		ABORT;
	} else
	{
		midiPlaying = KTTRUE;
	}
	

	strcpy(statusMessage,"MIDI sequence started");

	while (KTTRUE)
	{
		PDS_PERIPHERAL *pad = (PDS_PERIPHERAL*)njGetPeripheral(NJD_PORT_A0);

		syRtcGetDate(&current);
		acDigiPortsAvailable(&daCount, &midiCount);

		bpPrintf(INFO_0_X, INFO_0_Y, "Audio64 AC Play MIDI Sample");
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
		bpPrintf(INFO_3_X, INFO_3_Y, "Right trigger to play sequence");
		bpPrintf(INFO_4_X, INFO_4_Y, "Left trigger to stop sequence");
		bpPrintf(INFO_5_X, INFO_5_Y, "A to pause, B to resume Sequence");
		bpPrintf(INFO_6_X, INFO_6_Y, "X to fade up, Y to fade down Sequence");
		bpPrintf(INFO_7_X, INFO_7_Y, "START : Exit");
		bpPrintf(INFO_8_X, INFO_8_Y, "Sound Status: %s",statusMessage);

		if (pad->press & PAD_A_BUTTON)
		{
			if(!acMidiPause(midiPort))	// pause the sequence
			{
				strcpy(statusMessage,bpAcError->message);
				//				ABORT;		// bomb out if you want to
			} else
			{
				strcpy(statusMessage,"MIDI sequence paused");
				midiPlaying = KTFALSE;
			}
		}
		if (pad->press & PAD_B_BUTTON)
		{
			if(!acMidiResume(midiPort))	// resume the sequence
			{
				strcpy(statusMessage,bpAcError->message);
				//				ABORT;		// bomb out if you want to
			} else
			{
				strcpy(statusMessage,"MIDI sequence resumed");
				midiPlaying = KTTRUE;
			}

		}
		if (pad->press & PAD_X_BUTTON)
		{
			fadeseq	=	KTTRUE;
			direction = 1;
		}
		if (pad->press & PAD_Y_BUTTON)
		{
			fadeseq = KTTRUE;
			direction = -1;
		}
		if (pad->press & PAD_R_TRIGGER)
		{
			if(midiPlaying==KTFALSE)
			{
				if(!acMidiOpen(midiPort,gmMode,sequenceStartAddress,sequenceSize,(KTU32)pulsesPerQuarterNoteWord))	// open with pointer to 1st valid sequence data
				{
					ABORT;
				}

				if(!acMidiPlay(midiPort,0,loopMode))	// start the sequence
				{
					strcpy(statusMessage,bpAcError->message);
					//				ABORT;		// bomb out if you want to
				} else
				{
					strcpy(statusMessage,"MIDI sequence started");
					midiPlaying = KTTRUE;
				}
				if(!acMidiRequestEvent(midiPort,sequenceStartAddress + sequenceSize-8))
				{
					ABORT;
				}

				fadeseq = KTFALSE;
				midiVolume = 64;

				if(acMidiSetVolume(midiPort,midiVolume)==KTFALSE)				
				{
					strcpy(statusMessage,"Unable to set MIDI Sequence volume");
				}
			}
		}
		if (pad->press & PAD_L_TRIGGER)
		{
			if(midiPlaying==KTTRUE)
			{
				if(!acMidiStop(midiPort))	// stop the sequence
				{
					strcpy(statusMessage,bpAcError->message);
					//				ABORT;		// bomb out if you want to
				} else
				{
					strcpy(statusMessage,"MIDI sequence stopped");
					midiPlaying = KTFALSE;
				}

				if(!acMidiReset(midiPort))	// reset port to known default
				{
					strcpy(statusMessage,bpAcError->message);
				}

				if(!acMidiClose(midiPort))	// stop monitoring port
				{
					strcpy(statusMessage,bpAcError->message);
				}

			}
		}
		if (pad->press & PAD_START_BUTTON)
		{
			break;
		}

		if(fadeseq==KTTRUE)
		{
			if(midiPlaying==KTTRUE)	// sample playing?
			{
				callVolumeCount++;
				if(callVolumeCount==3)	// fade up or down gradually
				{
					callVolumeCount=0;
					changeVolume(statusMessage,midiPort,direction);
				}
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

KTBOOL loadBank(KTU32 *aica, KTSTRING name, KTU32 *size)
{
	KTU32 *image = KTNULL;
	KTU32 imageSize = 0;

	//	Get the size of the bank to be loaded
	if (!a64FileGetSize(name, size))
	{
		return (KTFALSE);
	}
	
	// IMPORTANT!  DWORD ALIGN RAW MIDI FILES, SINCE THEY ARE A BYTE FORMAT!!!

	*size = ((*size + 3) & 0xfffffffc);	//	ALIGN!!!!!

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

void changeVolume(char * midiStatusMessage, KTU32 midiPort, KTS32 direction)
{

	midiVolume += direction;

	if(midiVolume>126)
	{
		fadeseq = KTFALSE;
		return;
	}
	if(midiVolume<0)
	{
		fadeseq = KTFALSE;
		return;
	}

//	For Sequence Fading:			
	if(acMidiSetVolume(midiPort,midiVolume)==KTFALSE)				
	{
		strcpy(statusMessage,"Unable to set MIDI Sequence volume");
	}

// Panning and individual channel volume is done with the
//
//		acMidiSendMessage(KTU32 port,KTU32 channel,KTU32 command,KTU32 value1,KTU32 value2); 
//
// command, and is done for each active midi channel of the sequence (volume is CC 07, panning is CC 10)
	
}

//-----------------------------------------------------------------------------

void setupNinja(void)
{
	njSetBorderColor(0x00000000);
	switch (syCblCheckCable())
	{
		case SYE_CBL_CABLE_VGA:
			sbInitSystem(NJD_RESOLUTION_VGA, NJD_FRAMEBUFFER_MODE_RGB565, 1);
			break;
		default:
		case SYE_CBL_CABLE_NTSC:
			sbInitSystem(NJD_RESOLUTION_640x480_NTSCNI,
											NJD_FRAMEBUFFER_MODE_RGB565, 1);
			break;
	}
	njInitVertexBuffer(20000, 0, 20000, 0, 0);
	njInitPrint(NULL, 0, NJD_TEXFMT_ARGB_1555);
	njSetBackColor(0x00000000, 0x00000000, 0x000000FF);
	njPrintSize(12);	
}
