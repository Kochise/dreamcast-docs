//-----------------------------------------------------------------------------
//
//	FILE:		bpamsfx.c
//
//	DESC:		Boilerplate for Audio64 AM layer sound effects.
//
//	HISTORY:	2000.01.xx	Reworked samples/boilerplates for R10 release.
//
//-----------------------------------------------------------------------------
//	COPYRIGHT (C) SEGA OF AMERICA DREAMCAST, INC. 1998, 1999, 2000
//	All rights reserved.
//
//	Information and source code samples contained herein are provided "as-is",
//	without representations or warranties, and are subject to change without
//	notice.
//
//	SEGA OF AMERICA DREAMCAST, INC. cannot support modifications or derivative
//	works created from the sample source code provided. Developers may use,
//	reproduce, and modify portions or entire sections of the sample source
//	code for the purposes of creating Dreamcast applications.
//
//	Sample source code contained herein may not be appropriate for use under
//	all circumstances. Please consult Developer documentation provided along
//	with your Dreamcast unit for additional information and suggestions.
//-----------------------------------------------------------------------------

#include <string.h>

#include "bpamsfx.h"
#include "bpprintf.h"

//-----------------------------------------------------------------------------

#define BPAM_SFX_INSTANCES		AC_TOTAL_VOICES

AM_SOUND sfxInstances[BPAM_SFX_INSTANCES] = { 0 };

//-----------------------------------------------------------------------------
//	KTBOOL bpAmAllocateSfxInstance(AM_SOUND_PTR *theSound)
//-----------------------------------------------------------------------------

KTBOOL bpAmAllocateSfxInstance(AM_SOUND **theSound)
{
	KTU32 i;
	for (i = 0; i < BPAM_SFX_INSTANCES; i++)
	{
		if (!sfxInstances[i].isPlaying)	
		{
			memset(&sfxInstances[i], 0, sizeof(AM_SOUND));
			*theSound = &sfxInstances[i];
			return (KTTRUE);
		}
	}
	*theSound = KTNULL;
	return (KTFALSE);
}

//-----------------------------------------------------------------------------
//	KTBOOL bpAmSoundEffectPlaying(AM_SOUND_PTR theSound)
//-----------------------------------------------------------------------------

KTBOOL bpAmSoundEffectPlaying(AM_SOUND *theSound)
{
	return (amSoundIsPlaying(theSound));
}
 
//-----------------------------------------------------------------------------
//	AM_BANK_PTR bpAmLoadBank(KTSTRING bankFileName)
//-----------------------------------------------------------------------------
 
AM_BANK_PTR bpAmLoadBank(KTSTRING bankFileName)
{
	KTU32 bankSize;
	KTU32 bankImageSize;
	AM_BANK_PTR bankImage;
	KTU32 *aicaBuffer;

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
	if (!amHeapAlloc(&aicaBuffer, bankSize, 32, AM_PURGABLE_MEMORY,KTNULL))
	{
		bpDebugf("amHeapAlloc(&aicaBuffer, ...) failed\n");
		syFree(bankImage);
		return (KTNULL);
	}

	//	transfer the bank from SH4 memory to AICA memory
	if (!amBankTransfer(aicaBuffer, bankImage, bankSize))
	{
		bpDebugf("amBankTransfer(aicaBuffer, ...) failed\n");
		syFree(bankImage);
		return (KTNULL);
	}

	syFree(bankImage);

	return (aicaBuffer);
}

//-----------------------------------------------------------------------------
//	KTBOOL bpAmInstallEffectsPatch(AM_BANK_PTR theBank,
//			KTU32 effectsProgramBankIndex, KTU32 effectsOutputBankIndex)
//-----------------------------------------------------------------------------

KTBOOL bpAmInstallEffectsPatch(AM_BANK_PTR theBank,
	KTU32 effectsProgramBankIndex, KTU32 effectsOutputBankIndex)
{
	if (!amDspFetchProgramBank(theBank, effectsProgramBankIndex))
	{
		bpDebugf("amDspFetchProgramBank(theBank, ...) failed");
		return (KTFALSE);
	}

	if (!amDspFetchOutputBank(theBank, effectsOutputBankIndex))
	{
		bpDebugf("amDspFetchOutputBank(theBank, ...) failed");
		return (KTFALSE);
	}

	return (KTTRUE);
}

//-----------------------------------------------------------------------------
//	KTBOOL bpAmStopSoundEffect(AM_SOUND_PTR theSound)
//-----------------------------------------------------------------------------

KTBOOL bpAmStopSoundEffect(AM_SOUND *theSound)
{
	return (amSoundStop(theSound));
}

//-----------------------------------------------------------------------------
//	AM_SOUND_PTR bpAmPlaySoundEffect(AM_BANK_PTR theBank, KTU32 soundNumber,
//		KTU32 volume, KTU32 pan)
//-----------------------------------------------------------------------------

AM_SOUND *bpAmPlaySoundEffect(AM_BANK_PTR theBank, KTU32 soundNumber,
	KTU32 volume, KTU32 pan)
{
	AM_SOUND *theSound;

	// allocate a sound instance
	if (!bpAmAllocateSfxInstance(&theSound))
	{
		return (KTNULL);
	}

	//	fetch a pointer to the data 
	if (!amSoundFetchSample((KTU32*)theBank, soundNumber, theSound))
	{
		return (KTNULL);
	}

	//	NOTE:	Once the voice is allocated to a sound object the sound either
	//			must be submitted to the play call or have the voice released
	//			via amSoundReleaseVoiceChannel() as demonstrated below.
	//
	//			If the amSoundPlay() call fails it will release the voice from
	//			the sound.
	//
	//			If your application wants to abort the building of a sound,
	//			post the call to amSoundReleaseVoiceChannel().

	//	get a voice channel
	if (!amSoundAllocateVoiceChannel(theSound))
	{
		return (KTNULL);
	}
	//	set the initial volume
	if (!amSoundSetVolume(theSound, volume))
	{
		amSoundReleaseVoiceChannel(theSound);
		return (KTNULL);
	}
	//	set the initial pan
	if (!amSoundSetPan(theSound, pan))
	{
		amSoundReleaseVoiceChannel(theSound);
		return (KTNULL);
	}
	//	make it play
	if (!amSoundPlay(theSound))
	{
		return (KTNULL);
	}

	return (theSound);
}

//-----------------------------------------------------------------------------
//	AM_SOUND_PTR bpAmPlaySoundEffectFx(AM_BANK_PTR theBank, KTU32 soundNumber,
//		KTU32 volume, KTU32 pan, KTU32 effectSourceMix, KTBOOL qSoundOnOrOff)
//-----------------------------------------------------------------------------

AM_SOUND *bpAmPlaySoundEffectFx(AM_BANK_PTR theBank, KTU32 soundNumber,
	KTU32 volume, KTU32 pan, KTU32 effectSourceMix, KTBOOL qSoundOnOrOff)
{
	KTU32 dspMixerChannel	=	0;
	AM_SOUND *theSound;

	//	allocate a sound instance
	if (!bpAmAllocateSfxInstance(&theSound))
	{
		return (KTNULL);
	}

	//	determine which mixer channel to use
	dspMixerChannel =
		(qSoundOnOrOff) ? BPAM_SFX_QSOUND_CHANNEL : BPAM_SFX_REVERB_CHANNEL;
		
	//	fetch a pointer to the data 
	if (!amSoundFetchSample((KTU32*)theBank, soundNumber, theSound))
	{
		return (KTNULL);
	}

	//	NOTE:	Once the voice is allocated to a sound object the sound either
	//			must be submitted to the play call or have the voice released
	//			via amSoundReleaseVoiceChannel() as demonstrated below.
	//
	//			If the amSoundPlay() call fails it will release the voice from
	//			the sound.
	//
	//			If your application wants to abort the building of a sound,
	//			post the call to amSoundReleaseVoiceChannel().

	//	get a voice channel
	if (!amSoundAllocateVoiceChannel(theSound))
	{
		return (KTNULL);
	}
	//	set the initial volume (sound mix volume is derived from this volume)
	if (!amSoundSetVolume(theSound, volume))
	{
		amSoundReleaseVoiceChannel(theSound);
		return (KTNULL);
	}
	//	set the initial pan
	if (!amSoundSetPan(theSound, pan))
	{
		amSoundReleaseVoiceChannel(theSound);
		return (KTNULL);
	}
	//	set the effect source mix and bus
	if (!amSoundSetEffectsBus(theSound, dspMixerChannel, effectSourceMix))
	{
		amSoundReleaseVoiceChannel(theSound);
		return (KTNULL);
	}
	//	make it play
	if (!amSoundPlay(theSound))
	{
		return (KTNULL);
	}
		
	return (theSound);
}
