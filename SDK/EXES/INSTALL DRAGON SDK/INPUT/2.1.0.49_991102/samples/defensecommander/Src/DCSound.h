/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCSound.h

Abstract:

   Sound routines. 

-------------------------------------------------------------------*/

BOOL InitSound(HWND Window);
void ShutdownSound(HWND Window);
BOOL LoadSounds();
void UnloadSounds();

HANDLE GetSoundHandleFromName(TCHAR *Name);
void GetAllSoundIDs(void (*Callback)(TCHAR *Name, int SoundID));
int GetSoundID(HANDLE Sound);
void SetSoundID(HANDLE Sound, int ID);
HANDLE GetSoundHandleFromID(int ID);

void PlaySound(HANDLE Sound, float Volume);

// Equation is 10^(0.5f*log(Vol)/log(2))
#define QUARTER_VOLUME 0.1f
#define HALF_VOLUME 0.316f
#define THREE_QUARTER_VOLUME 0.620f
#define FULL_VOLUME 1.0f
