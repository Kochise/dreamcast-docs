//-----------------------------------------------------------------------------
//
//	FILE:		main.c
//
//	DESC:		This has the main function for a VERY abusive Audio64 AM layer
//				sample containing looping/one-shot effects, stream, and MIDI
//				(currently in progress).
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

#include "bpamsetup.h"
#include "bpamstream.h"
#include "bpbuttons.h"
#include "bpprintf.h"
#include "bpamsfx.h"
#include "strsfx.h"

//-----------------------------------------------------------------------------

#define PLAY_LOOPING_EFFECTS
#define PLAY_ONESHOT_EFFECTS
#define PLAY_STREAM
#define PLAY_MIDI

// ----------------MIDI files-------------------------------------------
#include "mpb_bank.h"
#include "mid_bank.h"
#include "bpammidi.h"

#define	INST_BANK_SLOT				0
#define DRUM_BANK_SLOT				1

//-----------------------------------------------------------------------------


#define USE_ACTRANSFER_DMA

#if defined(USE_ACTRANSFER_DMA)
#define TRANSFER_MODE					AC_TRANSFER_DMA
#else
#define TRANSFER_MODE					AC_TRANSFER_CPU
#endif

#ifdef __GNUC__
#define MAINFUNC						int main
#define RETURN							return (0)
#define ABORT							acASEBRK(KTTRUE)
#define SHINOBI_WORKAROUND				shinobi_workaround()
#else
#define MAINFUNC						void main
#define RETURN							return
#define ABORT							acASEBRK(KTTRUE)
#define SHINOBI_WORKAROUND
#endif

//-----------------------------------------------------------------------------
#define TEST_REV_NUMBER		"Lib: 10.1e Drv: 1.90e.1"

#define STREAM_FILE_NAME					"s_hip101.str"

#define STREAM_PLAY_BUFFER_MONO_SIZE		16384
#define STREAM_PLAY_BUFFER_STEREO_SIZE		(STREAM_PLAY_BUFFER_MONO_SIZE * 2)
#define STREAM_TRANSFER_BUFFER_SIZE			(STREAM_PLAY_BUFFER_STEREO_SIZE * 2)

#define MAX_ONE_SHOTS						4

#if defined(PLAY_MIDI)

// MIDI globals

KTS32			drivertype					=	AC_DRIVER_MIDI;
AM_SEQUENCE		theSequence;
AM_SEQUENCE		theSequence1;
AM_SEQUENCE		theSequence2;
AM_SEQUENCE		theSequence3;
AM_SEQUENCE		theSequence4;
AM_SEQUENCE		theSequence5;
AM_SEQUENCE		theSequence6;
AM_SEQUENCE		theSequence7;
AM_SEQUENCE		theSequence8;
AM_SEQUENCE		theSequence9;
AM_SEQUENCE		theSequence10;
AM_SEQUENCE		theSequence11;
AM_SEQUENCE		theSequence12;
AM_SEQUENCE		theSequence13;
AM_SEQUENCE		theSequence14;
AM_SEQUENCE		theSequence15;

KTU32			gVol						=	80;
volatile KTU32	gMidiDone					=	KTTRUE;
volatile KTU32	gMidiDone1					=	KTTRUE;
volatile KTU32	gMidiDone2					=	KTTRUE;
volatile KTU32	gMidiDone3					=	KTTRUE;
volatile KTU32	gMidiDone4					=	KTTRUE;
volatile KTU32	gMidiDone5					=	KTTRUE;
volatile KTU32	gMidiDone6					=	KTTRUE;
volatile KTU32	gMidiDone7					=	KTTRUE;
//volatile KTU32	gMidiDone8					=	KTTRUE;
//volatile KTU32	gMidiDone9					=	KTTRUE;
//volatile KTU32	gMidiDone10					=	KTTRUE;
//volatile KTU32	gMidiDone11					=	KTTRUE;
//volatile KTU32	gMidiDone12					=	KTTRUE;
//volatile KTU32	gMidiDone13					=	KTTRUE;
//volatile KTU32	gMidiDone14					=	KTTRUE;
//volatile KTU32	gMidiDone15					=	KTTRUE;

volatile KTU32	gMidiPlayCount				=	0;
KTU32			gMidiPlayFail				=	0;
extern KTU32	gMidiError;
KTS32				volinc					=	1;
KTS32				vol						=	0;


void ChangeMidiVolume(void);

void midiCallback(KTU32 id)	// the MIDI callback proc.  ID is 16-31 (Digital audio is 0-15)
{
	gMidiPlayCount++;
	switch(id)
	{
	case(16) :
		gMidiDone	=	KTTRUE;
		break;
	case(17) :
		gMidiDone1	=	KTTRUE;
		break;
	case(18) :
		gMidiDone2	=	KTTRUE;
		break;
	case(19) :
		gMidiDone3	=	KTTRUE;
		break;
	case(20) :
		gMidiDone4	=	KTTRUE;
		break;
	case(21) :
		gMidiDone5	=	KTTRUE;
		break;
	case(22) :
		gMidiDone6	=	KTTRUE;
		break;
	case(23) :
		gMidiDone7	=	KTTRUE;
		break;
/*
	case(24) :
		gMidiDone8	=	KTTRUE;
		break;
	case(25) :
		gMidiDone9	=	KTTRUE;
		break;
	case(26) :
		gMidiDone10	=	KTTRUE;
		break;
	case(27) :
		gMidiDone11	=	KTTRUE;
		break;
	case(28) :
		gMidiDone12	=	KTTRUE;
		break;
	case(29) :
		gMidiDone13	=	KTTRUE;
		break;
	case(30) :
		gMidiDone14	=	KTTRUE;
		break;
	case(31) :
		gMidiDone15	=	KTTRUE;
		break;
*/
	}
}

#else

KTS32			drivertype					=	AC_DRIVER_DA;

#endif
	
KTBOOL gStartSound = KTTRUE;

KTU32 gSoundCount = 0;
KTU32 gFailSoundCount = 0;
KTU32 gStreamCount = 0;
KTU32 gFailStreamCount = 0;

KTU32 *gTransferBuffer = KTNULL;
KTU32 gTransferBufferSize = STREAM_TRANSFER_BUFFER_SIZE;
KTU32 *gPlayBuffer = KTNULL;
KTU32 gPlayBufferSize = STREAM_PLAY_BUFFER_STEREO_SIZE;
KTU32 *gHeaderBuffer = KTNULL;

AM_STREAM *gStream = KTNULL;


KTU32 oneShotSounds[MAX_ONE_SHOTS] =
{
	STRSFX_ELEVATOR_WAV,
	STRSFX_GLASS_WAV,
	STRSFX_HONK_WAV,
	STRSFX_PING_WAV
};
KTU32			oneShotIndex					=	0;
AM_BANK_PTR		gBank							=	KTNULL;

KTU32			loopingSoundIndex				=	STRSFX_HELILOOP_WAV;
AM_SOUND *		loopInstance					=	KTNULL;

#if defined(PLAY_ONESHOT_EFFECTS)

KTBOOL gEaseUp = KTFALSE;

enum
{	// change cycle every SECONDS_PER_CYCLE
	SECONDS_PER_CYCLE = 10,
	EASEUP_CYCLE_MAX = (60 * SECONDS_PER_CYCLE)
};

KTU32 gEaseUpCycleCount = 0;

#endif

//-----------------------------------------------------------------------------

void setupNinja(void);
KTBOOL StreamSetup(void);
void TimerCallback( void *foo);
void CycleLoopingVolume(void);
void PlayLotsOfSoundEffects(void);
void ReplayStream(void);

//-----------------------------------------------------------------------------

MAINFUNC(void)
{
	SYE_CBL_CABLE Cable;
	PDS_PERIPHERAL *	pad;
	KTU32				j								=	0;
	KTBOOL				heliLoopFlag					=	KTFALSE;
	KTBOOL				humLoopFlag						=	KTFALSE;
	KTBOOL				spaceLoopFlag					=	KTFALSE;
	AM_SOUND 			heliLoop;
	AM_SOUND 			humLoop;
	AM_SOUND 			spaceLoop;
	KTU8				myStreamVolume					=	AM_MAX_VOLUME; // AM_MAX_VOLUME = 127
	KTU32 				effectSourceMix					=	100;
	KTU32				driverSize						=	0;
	KTU32 *				driverBuffer					=	KTNULL;
	char *				driverFileName					=	KTNULL;
	KTU32				block							=	0;
	KTU32				heartBeat						=	0;
	KTU32				i								=	0;
	SYS_RTC_DATE		start;
	SYS_RTC_DATE		current;
	KTU32				daCount;
	KTU32				midiCount;
	AC_ERROR_PTR		acErr;
	AM_ERROR *			amErr;

#if defined(PLAY_MIDI)
//---------------MIDI local variables--------------------
	KTU32				sequenceNumber			=	MID_BANK_B3LOOP_MID;  // polka
	KTU32				instrumentBankNumber	=	MPB_BANK_B3_MPB;	// polka bank
	AM_MIDI_CALLBACK	theCallback				=	midiCallback;
	volatile	KTU32	*theMPBBankInSoundram		=	KTNULL;
	volatile	KTU32	*theMidiBankInSoundram		=	KTNULL;
	KTU32				instrumentBankSlot		=	INST_BANK_SLOT;
//-------------------------------------------------
#endif

	SHINOBI_WORKAROUND;
	setupNinja();
	syRtcGetDate(&start);

	// ----------------------------------------------------------------------------------------------
	// Open the AM system
	// ----------------------------------------------------------------------------------------------

	if(!bpAmSetup(drivertype, KTFALSE, KTNULL))
	{
		ABORT;
	}

	(void)acSetTransferMode(TRANSFER_MODE);
		
	acSystemDelay(500000);

	acErr = acErrorGetLast();
	amErr = amErrorGetLast();
		
	// ----------------------------------------------------------------------------------------------
	// Setup the file system
	// ----------------------------------------------------------------------------------------------

	a64FileInit();
	
	// ----------------------------------------------------------------------------------------------
	// Load a bank
	// ----------------------------------------------------------------------------------------------
	
	if((gBank=bpAmLoadBank(STRSFX_FILENAME))==KTNULL)
	{
		ABORT;
	}
	if(drivertype==AC_DRIVER_MIDI)
	{
	// ----------------------------------------------------------------------------------------------
	// Load a midi tonebank
	// ----------------------------------------------------------------------------------------------
		
		if((theMPBBankInSoundram=bpAmLoadBank(MPB_BANK_FILENAME))==KTNULL)
			{
				// MyDebugf("MyLoadBank(0x%x,%s) FAIL",gBank,STRSFX_FILENAME);
				ABORT;
			}
		else
			{
			// MyDebugf("MyLoadBank(0x%x,%s) // load a bank of sounds into sound memory",gBank,STRSFX_FILENAME);
			}
	// ----------------------------------------------------------------------------------------------
	// Load a midi sequence bank
	// ----------------------------------------------------------------------------------------------
		if((theMidiBankInSoundram=bpAmLoadBank(MID_BANK_FILENAME))==KTNULL)
			{
				// MyDebugf("MyLoadBank(0x%x,%s) FAIL",gBank,STRSFX_FILENAME);
				ABORT;
			}
		else
			{
			// MyDebugf("MyLoadBank(0x%x,%s) // load a bank of sounds into sound memory",gBank,STRSFX_FILENAME);
			}
	// ----------------------------------------------------------------------------------------------
	// fetch the instrument tone bank
	// ----------------------------------------------------------------------------------------------
	
		if(amMidiFetchToneBank(theMPBBankInSoundram,instrumentBankNumber,instrumentBankSlot)==KTFALSE)
			{
	//			MyDebugf("amMidiFetchToneBank(0x%x,%u,%d,%u) FAIL\n",theMPBBankInSoundram,instrumentBankNumber,instrumentBankSlot);
				ABORT;
			}
		else
			{
	//		MyDebugf("amMidiFetchToneBank(0x%x,%u,%d,%u) // fetch the instrument tone bank\n",theMPBBankInSoundram,instrumentBankNumber,instrumentBankSlot);
			}	
	}

	// ----------------------------------------------------------------------------------------------
	// Set up the buffers etc for the stream
	// ----------------------------------------------------------------------------------------------

	if(StreamSetup()==KTFALSE)
	{
		ABORT;
	}
			
	// ----------------------------------------------------------------------------------------------
	// Start the stream
	// ----------------------------------------------------------------------------------------------

#if defined(PLAY_STREAM)
	bpAmStreamStart(gStream);
#endif

	// ----------------------------------------------------------------------------------------------
	// Start a looping sound
	// ----------------------------------------------------------------------------------------------
		
#if defined(PLAY_LOOPING_EFFECTS)
	loopInstance = bpAmPlaySoundEffect(gBank, loopingSoundIndex, 0, AM_PAN_CENTER);
	if (!loopInstance)
	{
		ABORT;
	}
#endif

	// ----------------------------------------------------------------------------------------------
	// Main loop
	// ----------------------------------------------------------------------------------------------
		
	syTmrGenSetInt(  TimerCallback, NULL );
	syTmrGenSetCount( -0xffff );
	syTmrGenStart();

	while (KTTRUE)
	{
		pad = (PDS_PERIPHERAL*)pdGetPeripheral(PDD_PORT_A0);

		acDigiPortsAvailable(&daCount, &midiCount);
//		syRtcGetDate(&current);

		bpPrintf(INFO_0_X, INFO_0_Y, "Audio64 AM Abuse Sample");
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
		bpPrintf(INFO_3_X, INFO_3_Y, "Sfx Play:%010u Fail:%010u",
										gSoundCount, gFailSoundCount);
		bpPrintf(INFO_4_X, INFO_4_Y, "Str Play:%010u Fail:%010u",
										gStreamCount, gFailStreamCount);
		bpPrintf(INFO_5_X,INFO_5_Y,"MIDI Play:%010u Fail:%010u",gMidiPlayCount,gMidiPlayFail);

		bpPrintf(INFO_6_X, INFO_6_Y, "AMer:%05u ACer:%05u MidiEr:%5u",
										amErr->number, acErr->number, gMidiError);
		bpPrintf(INFO_7_X, INFO_7_Y, "free:  da:%02u  midi:%02u",
										daCount, midiCount);
		bpPrintf(INFO_8_X, INFO_8_Y, "Mode:%05u Oper:%05u Xfer:%05u",
										gStream->mode,
										gStream->operation,
										gStream->transferCount);

#if defined(PLAY_STREAM)
		bpAmStreamServer();
#endif
		
#if defined(PLAY_STREAM)
		if (bpAmStreamDone(gStream))
		{
			ReplayStream();
		}
#endif

#if defined(PLAY_LOOPING_EFFECTS)
		CycleLoopingVolume();
#endif

#if defined(PLAY_ONESHOT_EFFECTS)
		if ((gEaseUpCycleCount++ == EASEUP_CYCLE_MAX) || (pad->press & PAD_R_TRIGGER))
		{
			gEaseUp = (gEaseUp) ? KTFALSE : KTTRUE;
			gEaseUpCycleCount = 0;
		}

		if (gStartSound)
		{
			gStartSound = KTFALSE;
			if (!gEaseUp)
			{
				PlayLotsOfSoundEffects();	// attempts to play 32 sfx
			}
		}
#endif

#if defined(PLAY_MIDI)
	// ----------------------------------------------------------------------------------------------
	// play the MIDI sequence
	// ----------------------------------------------------------------------------------------------

		if(gMidiDone==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone=KTFALSE;
			}
		}
		
		if(gMidiDone1==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence1,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone1=KTFALSE;
			}
		}
		
		if(gMidiDone2==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence2,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone2=KTFALSE;
			}
		}
		
		if(gMidiDone3==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence3,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone3=KTFALSE;
			}
		}
		
		if(gMidiDone4==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence4,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone4=KTFALSE;
			}
		}
		
		if(gMidiDone5==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence5,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone5=KTFALSE;
			}
		}
		
		if(gMidiDone6==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence6,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone6=KTFALSE;
			}
		}
		
		if(gMidiDone7==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence7,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone7=KTFALSE;
			}
		}
/*		
		if(gMidiDone8==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence8,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone8=KTFALSE;
			}
		}
		
		if(gMidiDone9==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence9,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone9=KTFALSE;
			}
		}
		
		if(gMidiDone10==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence10,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone10=KTFALSE;
			}
		}
		
		if(gMidiDone11==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence11,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone11=KTFALSE;
			}
		}
		
		if(gMidiDone12==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence12,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone12=KTFALSE;
			}
		}
		
		if(gMidiDone13==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence13,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone13=KTFALSE;
			}
		}
		
		if(gMidiDone14==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence14,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone14=KTFALSE;
			}
		}
		
		if(gMidiDone15==KTTRUE)
		{
			if(MyMidiPlay(theMidiBankInSoundram,&theSequence15,sequenceNumber,midiCallback)==KTTRUE)
			{
			gMidiDone15=KTFALSE;
			}
		}
		
*/
		ChangeMidiVolume();
#endif

		//	if the callback has set the end timer, diff the two and reset
		njWaitVSync();
	}
	
	// ----------------------------------------------------------------------------------------------
	// Shutdown the am library
	// ----------------------------------------------------------------------------------------------

	bpAmShutdown();

	// a chance for one last look around
	ABORT;
}

//-----------------------------------------------------------------------------

void ReplayStream(void)
{
	if (!bpAmStreamDestroy(gStream))
	{
		++gFailStreamCount;
		return;
	}

	gStream = bpAmStreamPrepareFile(STREAM_FILE_NAME, 127,
		AM_PAN_CENTER, gHeaderBuffer, gTransferBuffer, gTransferBufferSize,
		gPlayBuffer, gPlayBufferSize, KTNULL);
	if (!gStream)
	{
		++gFailStreamCount;
		return;
	}
		
	if (!bpAmStreamStart(gStream))
	{
		++gFailStreamCount;
		return;
	}

	++gStreamCount;
}

//-----------------------------------------------------------------------------

void CycleLoopingVolume(void)
{
	static KTS32 volinc = 1;
	static KTS32 vol = 0;
	KTU32 i;
	// jam the driver queue
	vol += volinc;
	if (vol == 126)
	{
		volinc = -1;
	}
	if (vol == 0)
	{
		volinc = 1;
	}
	for (i = 0; i < 3; i++)
	{
		if (!amSoundSetVolume(loopInstance, vol))
		{
			++gFailSoundCount;				
		}
	}
}

//-----------------------------------------------------------------------------

void PlayLotsOfSoundEffects(void)
{
	KTU32 i;
	// play some sounds
	for (i = 0; i < 32; i++)
	{
		AM_SOUND *oneShot = bpAmPlaySoundEffect(gBank,
							oneShotSounds[oneShotIndex], 100, AM_PAN_CENTER);
		if (oneShot)
		{
			if (++oneShotIndex >= MAX_ONE_SHOTS)
			{
				oneShotIndex = 0;
			}
			++gSoundCount;
		}
		else
		{
			++gFailSoundCount;				
		}
	}
}

//-----------------------------------------------------------------------------

void TimerCallback(void *foo)
{
	gStartSound = TRUE;
	syTmrGenSetInt(TimerCallback, KTNULL);
	syTmrGenSetCount(-0xffff);
	syTmrGenStart();
}

//-----------------------------------------------------------------------------

KTBOOL StreamSetup(void)
{
	// get the necessary buffers lined up for the stream
	//
	// allocate memory for the play buffers.
	//
	// play buffer MUST! be in aica memory and 32 byte aligned.

	if (!amHeapAlloc(&gPlayBuffer, gPlayBufferSize, 32,
												AM_PURGABLE_MEMORY,KTNULL))
	{
		return (KTFALSE);
	}

	// allocate memory for the transfer buffers.
	//
	// transfer buffer MUST! be in sh4 memory and 32 byte aligned or file
	// reads will fail with the GDFS file system.

	gTransferBuffer = (KTU32*)syMalloc(gTransferBufferSize);
	if (!gTransferBuffer)
	{
		return (KTFALSE);
	}

	// allocate memory for the header buffers.
	//
	// header buffer MUST! be in sh4 memory and 32 byte aligned or file
	// reads will fail with the GDFS file system.

	gHeaderBuffer = (KTU32*)syMalloc(AM_FILE_BLOCK_SIZE);
	if (!gHeaderBuffer)
	{
		return (KTFALSE);
	}

	// prepare the stream

	gStream = bpAmStreamPrepareFile(STREAM_FILE_NAME, 127,
		AM_PAN_CENTER, gHeaderBuffer, gTransferBuffer, gTransferBufferSize,
		gPlayBuffer, gPlayBufferSize, KTNULL);
	if (!gStream)
	{
		return (KTFALSE);
	}

	return (KTTRUE);
}

//-----------------------------------------------------------------------------
#if defined(PLAY_MIDI)

void ChangeMidiVolume(void)
{
static KTFLOAT	nextInc = 0;

	nextInc	+= 0.03;
	
	if(nextInc > 1.0)
	{
		nextInc = 0.0;
		gVol += volinc;
		if(gVol == 100)
			volinc = -1;
		if(gVol == 0)
			volinc = 1;

		if(gMidiDone==KTFALSE)	// sequence playing?
		{
			if(amMidiSetVolume(&theSequence,gVol)==KTFALSE)
				{
					gMidiPlayFail++;
					gMidiError = 6;
				}
		}
		if(gMidiDone1==KTFALSE)	// sequence playing?
		{
			if(amMidiSetVolume(&theSequence1,gVol)==KTFALSE)
				{
					gMidiPlayFail++;
					gMidiError = 6;
				}
		}
		if(gMidiDone2==KTFALSE)	// sequence playing?
		{
			if(amMidiSetVolume(&theSequence2,gVol)==KTFALSE)
				{
					gMidiPlayFail++;
					gMidiError = 6;
				}
		}
		if(gMidiDone3==KTFALSE)	// sequence playing?
		{
			if(amMidiSetVolume(&theSequence3,gVol)==KTFALSE)
				{
					gMidiPlayFail++;
					gMidiError = 6;
				}
		}
		if(gMidiDone4==KTFALSE)	// sequence playing?
		{
			if(amMidiSetVolume(&theSequence4,gVol)==KTFALSE)
				{
					gMidiPlayFail++;
					gMidiError = 6;
				}
		}
		if(gMidiDone5==KTFALSE)	// sequence playing?
		{
			if(amMidiSetVolume(&theSequence5,gVol)==KTFALSE)
				{
					gMidiPlayFail++;
					gMidiError = 6;
				}
		}
		if(gMidiDone6==KTFALSE)	// sequence playing?
		{
			if(amMidiSetVolume(&theSequence6,gVol)==KTFALSE)
				{
					gMidiPlayFail++;
					gMidiError = 6;
				}
		}
		if(gMidiDone7==KTFALSE)	// sequence playing?
		{
			if(amMidiSetVolume(&theSequence7,gVol)==KTFALSE)
				{
					gMidiPlayFail++;
					gMidiError = 6;
				}
		}
/*
		if(gMidiDone8==KTFALSE)	// sequence playing?
		{
			if(amMidiSetVolume(&theSequence8,gVol)==KTFALSE)
				{
					gMidiPlayFail++;
					gMidiError = 6;
				}
		}
		if(gMidiDone9==KTFALSE)	// sequence playing?
		{
			if(amMidiSetVolume(&theSequence9,gVol)==KTFALSE)
				{
					gMidiPlayFail++;
					gMidiError = 6;
				}
		}

		if(gMidiDone10==KTFALSE)	// sequence playing?
		{
			if(amMidiSetVolume(&theSequence10,gVol)==KTFALSE)
				{
					gMidiPlayFail++;
					gMidiError = 6;
				}
		}
		if(gMidiDone11==KTFALSE)	// sequence playing?
		{
			if(amMidiSetVolume(&theSequence11,gVol)==KTFALSE)
				{
					gMidiPlayFail++;
					gMidiError = 6;
				}
		}
		if(gMidiDone12==KTFALSE)	// sequence playing?
		{
			if(amMidiSetVolume(&theSequence12,gVol)==KTFALSE)
				{
					gMidiPlayFail++;
					gMidiError = 6;
				}
		}
*/

	}
}

#endif

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
