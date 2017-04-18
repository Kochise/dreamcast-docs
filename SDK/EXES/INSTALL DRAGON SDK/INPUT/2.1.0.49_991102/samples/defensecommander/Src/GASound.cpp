/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    GASound.cpp

Abstract:

    Game management - intermediate handling for playing sounds.
	Calls Sound.cpp.	                  

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCSound.h"

#define PEAK_DIST 500.0f

void GameClass::PlaySound(HANDLE Sound, DCVector *Loc, BOOL SendToClients, float Volume)
{
	if (Sound && !IsTimeDemo())
	{
		// Scale volume according to distance from observer.
		float PlayVolume=Volume;
		DCVector VLoc,VRot;
		GetViewerCoords(&VLoc,&VRot);
		// Cheating a bit here. Attenuation should really be proportional to Dist^2
		// but this gives a more usable result.
		float Dist=Loc->FastDist(VLoc);
		if (Dist > PEAK_DIST)
			PlayVolume*=PEAK_DIST/Dist;
				
		// Play the sound.
		::PlaySound(Sound,PlayVolume);

		// Send to clients if necessary.
		if (ClientCount && SendToClients)
			SendPlaySound(GetSoundID(Sound), Loc, Volume);
	}
}

void GameClass::PlaySoundNoAttenuate(HANDLE Sound, BOOL SendToClients, float Volume)
{
	if (Sound && !IsTimeDemo())
	{
		// Play the sound.
		::PlaySound(Sound,Volume);

		// Send to clients if necessary.
		if (ClientCount && SendToClients)
			SendPlaySoundNoAttenuate(GetSoundID(Sound), Volume);
	}
}
