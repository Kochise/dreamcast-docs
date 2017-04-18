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
// T.P.M.	02/17/00	Revised for R10
// ------------------------------------------------------------------------------------------------


//#include <am.h>

#include <string.h>

#include "bpprintf.h"

//-----------------------------------------------------------------------------
//	AM_BANK_PTR bpAmLoadBank(KTSTRING bankFileName)
//-----------------------------------------------------------------------------
 
AM_BANK_PTR bpAmLoadBank(KTSTRING bankFileName)
{
	KTU32 bankSize;
	KTU32 bankImageSize;
	AM_BANK_PTR bankImage;
	extern KTU32 *gAicaBank;

	//	get the size of the bank file
	if (!amBankGetSize(bankFileName, &bankSize))
	{
		bpDebugf("amBankGetSize(bankFileName, ...) failed\n");
		return (KTNULL);
	}
	//	align for GD-ROM reading
	bankImageSize = SECTOR_ALIGN(bankSize);

	//	get a buffer in SH4 memory (using aligned size)
	bankImage = (AM_BANK_PTR)syMalloc(bankImageSize);
	if (!bankImage)
	{
		bpDebugf("syMalloc(bankSize) failed\n");
		return (KTNULL);
	}

	//	load the bank
	if (!amBankLoad(bankFileName, bankImage, bankImageSize))
	{
		bpDebugf("amBankLoad(bankFileName, ...) failed\n");
		return (KTNULL);
	}

	//	get a buffer in sound memory (using actual size)
	if (!amHeapAlloc(&gAicaBank, bankSize, 32, AM_PURGABLE_MEMORY,KTNULL))
	{
		bpDebugf("amHeapAlloc(&aicaBuffer, ...) failed\n");
		syFree(bankImage);
		return (KTNULL);
	}

	//	transfer the bank from SH4 memory to AICA memory
	if (!amBankTransfer(gAicaBank, bankImage, bankSize))
	{
		bpDebugf("amBankTransfer(gAicaBank, ...) failed\n");
		syFree(bankImage);
		return (KTNULL);
	}

	syFree(bankImage);

	return (gAicaBank);
}


KTBOOL bpAmMidiStop(AM_SEQUENCE *theSequence)
{
	if(amMidiStop(theSequence)==KTFALSE)
		{
	//	MyDebugf("amMidiStop(0x%x) FAIL\n",&theSequence);
		return KTFALSE;
		}
	else
	//	MyDebugf("amMidiStop(0x%x) // stop the sequence\n",&theSequence);


return KTTRUE;
}


KTBOOL bpAmMidiPlay(AM_BANK_PTR theBank,AM_SEQUENCE *theSequence,KTU32 theAssetNumber,AM_MIDI_CALLBACK theCallback)
{
	// ----------------------------------------------------------------------------------------------
	// fetch a sequence
	// ----------------------------------------------------------------------------------------------
	
	if(amMidiFetchSequence(theBank,theAssetNumber,theSequence)==KTFALSE)
		{
	//	MyDebugf("amMidiFetchSequence(0x%x,%u,0x%x) FAIL\n",theBank,theAssetNumber,theSequence);
		return KTFALSE;
		}
	else
	//	MyDebugf("amMidiFetchSequence(0x%x,%u,0x%x) // fetch a sequence\n",theBank,theAssetNumber,theSequence);
	
	
	// ----------------------------------------------------------------------------------------------
	// install a callback proc
	// ----------------------------------------------------------------------------------------------
	
	if(amMidiInstallCallback(theSequence,theCallback)==KTFALSE)
		{
	//	MyDebugf("amMidiInstallCallback(0x%x,0x%x) FAIL\n",theSequence,theCallback);
		return KTFALSE;
		}
	else
	//	MyDebugf("amMidiInstallCallback(0x%x) // install a sequence callback\n",theSequence);
	
	// ----------------------------------------------------------------------------------------------
	// get a port assignment
	// ----------------------------------------------------------------------------------------------
	
	if(amMidiAllocateSequencePort(theSequence)==KTFALSE)
		{
	//	MyDebugf("amMidiAllocateSequencePort(0x%x) FAIL\n",theSequence);
		return KTFALSE;
		}
	else
	//	MyDebugf("amMidiAllocateSequencePort(0x%x) // get a port\n",theSequence);
	
	// ----------------------------------------------------------------------------------------------
	// play the sequence
	// ----------------------------------------------------------------------------------------------
	
	if(amMidiPlay(theSequence)==KTFALSE)
		{
	//	MyDebugf("amMidiPlay(0x%x) FAIL\n",theSequence);
		return KTFALSE;
		}
	else
	//	MyDebugf("amMidiPlay(0x%x) // play the sequence\n",theSequence);


return KTTRUE;
}
