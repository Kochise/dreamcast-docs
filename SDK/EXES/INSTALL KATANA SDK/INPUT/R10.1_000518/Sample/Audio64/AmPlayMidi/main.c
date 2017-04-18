// ------------------------------------------------------------------------------------------------
// main.c
//
// This has the main function for the str_sfx testbed.
//
// COPYRIGHT (C) SEGA OF AMERICA, INC. 1998
// All rights reserved.
//
// Information and source code samples contained herein are 
// provided "as-is", without representations or warranties, and 
// are subject to change without notice.
//
// SEGA OF AMERICA, INC. cannot support modifications or 
// derivative works created from the sample source code provided. 
// Developers may use, reproduce, and modify portions or entire 
// sections of the sample source code for the purposes of creating
// Dreamcast applications.  
//
// Sample source code contained herein may not be appropriate 
// for use under all circumstances.  Please consult Developer 
// documentation provided along with your Dreamcast unit for
// additional information and suggestions.
//
//
// Author: Ralph "Cooksey" Thomas
//
// Tabs: 4
//
// Rev:			04/05/99	File Originated
// T.P.M.		02/17/00	Modified for R10
// ------------------------------------------------------------------------------------------------

#include <shinobi.h>
#include <ac.h>
#include <a64thunk.h>
#include <am.h>

#include "bpamsetup.h"
#include "bpbuttons.h"
#include "bpprintf.h"

#include "amPlayMidi.h"
#include "PlayMidi.h"

//-----------------------------------------------------------------------------

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


#define INST_BANK_SLOT				0
#define DRUM_BANK_SLOT				1

volatile KTBOOL gMidiDone	=	KTFALSE;
volatile KTBOOL gBpCallBackReceived	=	KTFALSE;	//	callback status

void TimerCallback( void *foo);
void setupNinja(void);
void changeVolume(char *,AM_SEQUENCE foo );
volatile KTU32	gCount	=	0;

void midiCallback(KTU32 id)			// the MIDI callback proc
{
gBpCallBackReceived	=	KTTRUE;
gMidiDone	=	KTTRUE;	
gCount++;
}

AM_BANK_PTR gAicaBank	=	KTNULL;

KTU32				sequenceNumber			=	PLAYMIDI_B3_MID;  // polka
KTU32				instrumentBankNumber	=	PLAYMIDI_B3_MPB;
KTU32				instrumentBankSlot		=	INST_BANK_SLOT;
//KTU32				drumBankSlot			=	DRUM_BANK_SLOT;


void main(void)
{
	SYE_CBL_CABLE Cable;
	PDS_PERIPHERAL *	pad;
	KTU32 				instanceNumber					=	0;	
	AM_BANK_PTR			myBank							=	KTNULL;
	char 				midiStatusMessage[80]				= {"Playing"};
	KTS32				gmMode					=	AC_GM_ON;
//	KTS8				gmMode					=	AC_GM_ON;
	KTU32				alignment				=	32;
	AM_MIDI_CALLBACK	theCallback				=	midiCallback;
	KTU32				i						=	0;
	AM_SEQUENCE			theSequence;
	KTU32				midiVolume				=	80;
	KTS32				callVolumeCount			=	0;
	extern AM_BANK_PTR		gAicaBank;

	AC_ERROR	*acErr;
	AM_ERROR	*amErr;
	SYS_RTC_DATE		start;
	SYS_RTC_DATE		current;

	SHINOBI_WORKAROUND;
	setupNinja();
	syRtcGetDate(&start);

	// ----------------------------------------------------------------------------------------------
	// Open the AM system
	// ----------------------------------------------------------------------------------------------

	if(!bpAmSetup(AC_DRIVER_MIDI, KTFALSE, KTNULL))
	{
		ABORT;
	}

	acSystemDelay(500000);

	acErr = acErrorGetLast();
	amErr = amErrorGetLast();
		
	// ----------------------------------------------------------------------------------------------
	// Setup the file system
	// ----------------------------------------------------------------------------------------------

	a64FileInit();
	
	// ----------------------------------------------------------------------------------------------
	// load the .KAT bank which contains everything (midi files & tonebanks
	// ----------------------------------------------------------------------------------------------
	
	if((gAicaBank=bpAmLoadBank((KTSTRING)PLAYMIDI_FILENAME))==KTNULL)
	{
		strcpy(midiStatusMessage,"Unable to load MIDI bankfile");
		ABORT;
	}

	
	if(amMidiFetchToneBank(gAicaBank,instrumentBankNumber,instrumentBankSlot)==KTFALSE)
		{
		strcpy(midiStatusMessage,"Unable to fetch Tonebank data from soundram");
		ABORT;
		}
	// ----------------------------------------------------------------------------------------------
	// fetch the drum tone bank
	// ----------------------------------------------------------------------------------------------
/*	
	if(amMidiFetchToneBank(theBankInSoundram,drumBankNumber,drumBankSlot)==KTFALSE)
		{
		MyDebugf("amMidiFetchToneBank(0x%x,%u,%d,%u) FAIL\n",theBank,drumBankNumber,drumBankSlot);
		return;
		}
	else
		MyDebugf("amMidiFetchToneBank(0x%x,%u,%d,%u) // fetch the drum tone bank\n",theBank,drumBankNumber,drumBankSlot);
*/	

	// ----------------------------------------------------------------------------------------------
	// play the sequence
	// ----------------------------------------------------------------------------------------------

	memset(&theSequence,0x00,sizeof(AM_SEQUENCE));

	if(bpAmMidiPlay(gAicaBank,&theSequence,sequenceNumber,midiCallback)==KTFALSE)
		{
			strcpy(midiStatusMessage,"Unable to play sequence file");
			ABORT;
		}
		else
		{
			gMidiDone=KTFALSE;
			gBpCallBackReceived=KTFALSE;
			strcpy(midiStatusMessage,"Playing");
		}	
	// ----------------------------------------------------------------------------------------------
	// Main loop
	// ----------------------------------------------------------------------------------------------
		
	syTmrGenSetInt(  TimerCallback, NULL );
	syTmrGenSetCount( -0xffff );
	syTmrGenStart();

	while (KTTRUE)
	{
		pad = (PDS_PERIPHERAL*)pdGetPeripheral(PDD_PORT_A0);

		syRtcGetDate(&current);

		bpPrintf(INFO_0_X, INFO_0_Y, "Audio64 AM Play Midi Sample");
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
		bpPrintf(INFO_3_X, INFO_3_Y, "Press Trigger L=Stop, R=Start, X=Pause, Y=Resume Midi play");
		bpPrintf(INFO_4_X, INFO_4_Y, "Stream Status: %s",midiStatusMessage);
		bpPrintf(INFO_5_X, INFO_5_Y, "Am Error Number: %d",acErr->number);
		bpPrintf(INFO_6_X, INFO_6_Y, "Ac Error Number: %d",acErr->number);
		bpPrintf(INFO_7_X, INFO_7_Y, "Play Count: %d",gCount);


	
	
		if(gBpCallBackReceived==KTTRUE)
			{
			strcpy(midiStatusMessage,"MIDI Callback received");
			}

		if(pad->press & PAD_L_TRIGGER)
		{
			// ----------------------------------------------------------------------------------------------
			// stop the sequence
			// ----------------------------------------------------------------------------------------------

			if(bpAmMidiStop(&theSequence)==KTFALSE)
				{
					gMidiDone	=	KTTRUE;	
					strcpy(midiStatusMessage,"Sequence stop failed");
				} else {
					gMidiDone	=	KTTRUE;	
					strcpy(midiStatusMessage,"Sequence stopped");
				}
		} else if((pad->press & PAD_R_TRIGGER) && (gMidiDone == KTTRUE))
			{
			if(bpAmMidiPlay(gAicaBank,&theSequence,sequenceNumber,midiCallback)==KTTRUE)
				{
				gMidiDone=KTFALSE;
				gBpCallBackReceived=KTFALSE;
				strcpy(midiStatusMessage,"Playing");
				}
			}
		if(pad->press & PAD_X_BUTTON)
		{
			if(amMidiPause(&theSequence)==KTFALSE)
			{
				strcpy(midiStatusMessage,"Sequence pause failed");
			} else {
				strcpy(midiStatusMessage,"Sequence paused");
			}
		}

		if(pad->press & PAD_Y_BUTTON)
		{
			if(amMidiResume(&theSequence)==KTFALSE)
			{
				strcpy(midiStatusMessage,"Sequence resume failed");
			} else {
				strcpy(midiStatusMessage,"Sequence resumed");
			}
		}
			
		if(gMidiDone==KTFALSE)	// sample playing?
		{
			callVolumeCount++;
			if(callVolumeCount==3)
			{
				callVolumeCount=0;
				changeVolume(midiStatusMessage,theSequence);
			}
		}
		/*
		if(pad->press & PAD_MOVE_UP)
		{
			if(midiVolume < 127)
				midiVolume++;
				
			if(amMidiSetVolume(&theSequence,midiVolume)==KTFALSE)				
			{
				strcpy(midiStatusMessage,"Unable to set MIDI volume");
			}
		}
			if(pad->press & PAD_MOVE_DOWN)
		{
			if(midiVolume > 0)
				midiVolume--;
				
			if(amMidiSetVolume(&theSequence,midiVolume)==KTFALSE)				
			{
				strcpy(midiStatusMessage,"Unable to set MIDI volume");
			}
		}
		*/
	// ----------------------------------------------------------------------------------------------
	// restart the MIDI sequence if done playing 
	// (only needed for callback test.  If you want to loop playback set sequence to loop in script .oss) 
	// ----------------------------------------------------------------------------------------------

	
		njWaitVSync();
		}
	
	// ----------------------------------------------------------------------------------------------
	// Shutdown the am library
	// ----------------------------------------------------------------------------------------------
	
	amShutdown();
}


void changeVolume(char * midiStatusMessage,AM_SEQUENCE theSequence)
{
	static	KTS32	inc	=	1;
	static	KTU32	midiVolume;

	midiVolume += inc;
	if(midiVolume==127)
		inc = -1;
	if(midiVolume==0)
		inc = 1;


	if(amMidiSetChannelPan(theSequence.midiPort,1,midiVolume)==KTFALSE)				
	{
		strcpy(midiStatusMessage,"Unable to set MIDI Channel pan");
	}


/*
	//	For MIDI Channel Fading:
	if(amMidiSetChannelVolume(theSequence.midiPort,1,midiVolume)==KTFALSE)				
	{
		strcpy(midiStatusMessage,"Unable to set MIDI Channel volume");
	}
*/
/*
//	For Sequence Fading:			
	if(amMidiSetVolume(&theSequence,midiVolume)==KTFALSE)				
	{
		strcpy(midiStatusMessage,"Unable to set MIDI Sequence volume");
	}
*/
}

//-----------------------------------------------------------------------------

void TimerCallback(void *foo)
{
	syTmrGenSetInt(TimerCallback, KTNULL);
	syTmrGenSetCount(-0xffff);
	syTmrGenStart();
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
