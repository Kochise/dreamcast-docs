//-----------------------------------------------------------------------------
//
//	FILE:		bpamsfx.h
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

#if !defined(_BPAMSFX_H_)
#define _BPAMSFX_H_

#include <ac.h>
#include <a64thunk.h>
#include <am.h>

#ifdef __cplusplus
extern "C" {
#endif

extern KTU32 gQSoundChannel;

#define BPAM_SFX_REVERB_CHANNEL			0
#define BPAM_SFX_QSOUND_CHANNEL			12
#define BPAM_SFX_NUMBER_OF_Q_CHANNELS	4

AM_BANK_PTR bpAmLoadBank(KTSTRING bankFileName);

KTBOOL bpAmAllocateSfxInstance(AM_SOUND **theSound);
KTBOOL bpAmInstallEffectsPatch(AM_BANK_PTR theBank,
	KTU32 effectsProgramBankIndex, KTU32 effectsOutputBankIndex);

AM_SOUND *bpAmPlaySoundEffect(AM_BANK_PTR theBank, KTU32 soundNumber,
	KTU32 volume, KTU32 pan);
AM_SOUND *bpAmPlaySoundEffectFx(AM_BANK_PTR theBank, KTU32 soundNumber,
	KTU32 volume, KTU32 pan, KTU32 effectSourceMix, KTBOOL qSoundOnOrOff);

KTBOOL bpAmStopSoundEffect(AM_SOUND *theSound);

KTBOOL bpAmSoundEffectIsPlaying(AM_SOUND *theSound);

#ifdef __cplusplus
}
#endif

#endif	//	_BPAMSFX_H_
