/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    DirectSound3D.hpp

Abstract:

   Include file for DirectSound3D

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

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

// DirectSound3D.cpp variables
extern HWND                g_hwndApp;                   // HWND of the application
extern HINSTANCE           g_hinst;                     // HINSTANCE of the application

// Error.cpp variables
extern toutputlevel g_outputlevel;                      // Amount of detail in error messages
extern terr g_errLast;                                  // Error return code of last function

// DSUtil.cpp variables
extern LPDIRECTSOUND           g_pds;                   // The main DirectSound object
extern LPDIRECTSOUNDBUFFER     g_pdsbListener;
extern LPDIRECTSOUND3DLISTENER g_pds3dl;

// ++++ Global Functions ++++++++++++++++++++++++++++++++++++++++++++

// DSUtil.cpp functions
BOOL InitDirectSound();
BOOL InitDirectSound3D();
IDirectSoundBuffer   *LoadSoundBuffer(LPCTSTR lpName);
BOOL Load3DSoundBuffer(LPCTSTR tszName, IDirectSoundBuffer **ppdsb, IDirectSound3DBuffer **ppds3db);

// Error.cpp functions
BOOL CheckError(TCHAR *tszErr);
void RetailOutput(TCHAR *tszErr, ...);
#ifdef DEBUG
void DebugOutput(TCHAR *tszErr, ...);
#else
__inline void DebugOutput(TCHAR *tszErr, ...) {};
#endif
