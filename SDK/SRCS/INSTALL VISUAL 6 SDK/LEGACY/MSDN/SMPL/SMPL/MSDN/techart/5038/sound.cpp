/*==========================================================================
 *  Copyright (C) 1996 Microsoft Corporation.
 *
 *  File:       sound.cpp
 *  Content:    DirectSound functionality for Moby Dick
 *
 ***************************************************************************/

//#ifdef USE_DIRECTSOUND
#include "sound.h"
#include "wave.h"
#include "resource.h"

extern HINSTANCE   hTheInstance;           // program instance

LPDIRECTSOUND      lpds;
LPDIRECTSOUNDBUFFER  lpDSB_Blow, lpDSB_Boing;


/* **********************************************************
   InitSound()
   Initialize DirectSound objects & devices
************************************************************ */
BOOL InitSound(HWND hwnd, HINSTANCE hinst)
  {
  if (DirectSoundCreate(NULL, &lpds, NULL) == DS_OK) 
    {
    // Creation succeeded.
    lpds->SetCooperativeLevel(hwnd, DSSCL_NORMAL);
    LoadWave(hinst, IDR_WAVE_BLOW, lpDSB_Blow);
    LoadWave(hinst, IDR_WAVE_BOING, lpDSB_Boing);
    return TRUE;
    } 
  else 
    {
    return FALSE;
    }
  }  // InitSound()


/* **********************************************************
   CleanupSound()
   Cleans up DirectSound objects
************************************************************ */
void CleanupSound(void)
  {
    if(lpds!= NULL) lpds->Release();  // this releases buffers as well
  }


void Blow(int pan)
  {
    lpDSB_Blow->SetPan(pan);
    if (lpDSB_Blow)
      lpDSB_Blow->Play(0, 0, 0);
  }


void Boing(BOOL ToggleOn)
  {

  if (lpDSB_Boing)
    {
    if (ToggleOn)    
      lpDSB_Boing->Play(0, 0, DSBPLAY_LOOPING);
    else 
      lpDSB_Boing->Stop();
    }
  }

//#endif // USE_DIRECTSOUND