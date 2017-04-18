// ------------------------------------------------------------------------------------------------
// MyMidi.c
//
// This has some higher level stream functions
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
// Tabs:	4
//
// Rev:		05/27/99	File Originated
// ------------------------------------------------------------------------------------------------

#include <ac.h>
#include <a64thunk.h>
#include <am.h>
#include "bpprintf.h"

KTU32 gMidiError	=	0;

KTBOOL MyMidiStop(AM_SEQUENCE *theSequence)
{
extern KTU32	gMidiPlayFail;

	if(amMidiStop(theSequence)==KTFALSE)
		{
		bpDebugf("amMidiStop(0x%x) FAIL\n",&theSequence);
		gMidiPlayFail++;
		gMidiError = 10;
		return KTFALSE;
		}
	else
		bpDebugf("amMidiStop(0x%x) // stop the sequence\n",&theSequence);


return KTTRUE;
}


KTBOOL MyMidiPlay(AM_BANK_PTR theBank,AM_SEQUENCE *theSequence,KTU32 theAssetNumber,AM_MIDI_CALLBACK theCallback)
{
extern KTU32	gMidiPlayFail;
extern KTU32	gVol;
	// ----------------------------------------------------------------------------------------------
	// fetch a sequence
	// ----------------------------------------------------------------------------------------------
	
	if(amMidiFetchSequence(theBank,theAssetNumber,theSequence)==KTFALSE)
		{
		bpDebugf("amMidiFetchSequence(0x%x,%u,0x%x) FAIL\n",theBank,theAssetNumber,theSequence);
		gMidiPlayFail++;
		gMidiError = 1;
		return KTFALSE;
		}
	else
		bpDebugf("amMidiFetchSequence(0x%x,%u,0x%x) // fetch a sequence\n",theBank,theAssetNumber,theSequence);
	
	// ----------------------------------------------------------------------------------------------
	// install a callback proc
	// ----------------------------------------------------------------------------------------------
	
	if(amMidiInstallCallback(theSequence,theCallback)==KTFALSE)
		{
		bpDebugf("amMidiInstallCallback(0x%x,0x%x) FAIL\n",theSequence,theCallback);
		gMidiPlayFail++;
		gMidiError = 2;
		return KTFALSE;
		}
	else
		bpDebugf("amMidiInstallCallback(0x%x) // install a sequence callback\n",theSequence);
	
	// ----------------------------------------------------------------------------------------------
	// get a port assignment
	// ----------------------------------------------------------------------------------------------
	
	if(amMidiAllocateSequencePort(theSequence)==KTFALSE)
		{
		bpDebugf("amMidiAllocateSequencePort(0x%x) FAIL\n",theSequence);
		gMidiPlayFail++;
		gMidiError = 3;
		return KTFALSE;
		}
	else
		bpDebugf("amMidiAllocateSequencePort(0x%x) // get a port\n",theSequence);
	
	// ----------------------------------------------------------------------------------------------
	// play the sequence
	// ----------------------------------------------------------------------------------------------
	
	if(amMidiPlay(theSequence)==KTFALSE)
		{
		bpDebugf("amMidiPlay(0x%x) FAIL\n",theSequence);
		gMidiPlayFail++;
		gMidiError = 4;

		amVoiceFree(theSequence->midiPort + AC_FIRST_MIDI_VOICE);		// 11/24/99 add offset back in
		theSequence->midiPort		=	AM_UNINITIALIZED_VOICE_CHANNEL;
		theSequence->voiceChannel	=	AM_UNINITIALIZED_VOICE_CHANNEL;

		return KTFALSE;
		}
	else
		bpDebugf("amMidiPlay(0x%x) // play the sequence\n",theSequence);

	// ----------------------------------------------------------------------------------------------
	// drop the sequence volume
	// ----------------------------------------------------------------------------------------------
/*	
	if(amMidiSetVolume(theSequence,gVol)==KTFALSE)
		{
		bpDebugf("amMidiPlay(0x%x) FAIL\n",theSequence);
		gMidiPlayFail++;
		gMidiError = 5;
		return KTFALSE;
		}

*/
return KTTRUE;
}
