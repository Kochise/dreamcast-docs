/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    StreamingSound.hpp

Abstract:

   Include file for StreamingSound

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++

#include <tchar.h>
#include <windows.h>
#include <dsound.h>

// ++++ Enumerated Types ++++++++++++++++++++++++++++++++++++++++++++

// Output types
enum toutputlevel { OUTPUT_ALL = 0, OUTPUT_FAILURESONLY };

// ++++ Types +++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Error type
typedef int terr;

// ++++ Defines +++++++++++++++++++++++++++++++++++++++++++++++++++++

// DIUtil.cpp defines
#define MAX_CONTROLLERS    4                            // Maximum number of controllers
#define BUFFERSIZE         262144                       // Arbitrary nice large number (must be divisible by 2)

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

// StreamingSound.cpp variables
extern HWND                g_hwndApp;                   // HWND of the application
extern HINSTANCE           g_hinst;                     // HINSTANCE of the application
extern volatile BOOL       g_fPlayBackgroundSound;      // TRUE if the background sound should be played
extern HANDLE              g_hSoundNotifyEvent;         // Notify Event for the background sound buffer
extern HANDLE              g_hSoundDoneEvent;           // End-Of-Playing Event for the background sound buffer
extern HANDLE              g_hSoundFile;                // Handle of the background sound file to play
extern IDirectSoundBuffer  *g_pdsbBackground;           // The background sound buffer
extern BOOL                g_fExiting;                  // TRUE if the app is exiting

// Error.cpp variables
extern toutputlevel g_outputlevel;                      // Amount of detail in error messages
extern terr g_errLast;                                  // Error return code of last function

// DSUtil.cpp variables
extern LPDIRECTSOUND       g_pds;                       // The main DirectSound object

// StreamThread.cpp variables
extern BOOL                g_fDonePlaying;              // Sound has finished playing

// ++++ Global Functions ++++++++++++++++++++++++++++++++++++++++++++

// PlayingSoundThread.cpp functions
BOOL  AddSound(IDirectSoundBuffer *pdsb);
DWORD PlayingSoundThread(int nUnused);

// DSUtil.cpp functions
BOOL InitDirectSound();
IDirectSoundBuffer *CreateSoundBuffer(int nSamplesPerSec, WORD wBitsPerSample, DWORD dwBufferSize);
BOOL PrepareForStreaming(IDirectSoundBuffer *pdsb, DWORD dwBufferSize, HANDLE *phEventNotify, HANDLE *phEventDone);
BOOL ParseWaveFile(void *pvWaveFile, WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData, DWORD *pcbWaveSize);

// StreamThread.cpp functions
DWORD StreamThread(int nUnused);
void WaitUntilSoundDone();

// Error.cpp functions
BOOL CheckError(TCHAR *tszErr);
void RetailOutput(TCHAR *tszErr, ...);
#ifdef DEBUG
void DebugOutput(TCHAR *tszErr, ...);
#else
__inline void DebugOutput(TCHAR *tszErr, ...) {};
#endif
