/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CustomDSP.hpp

Abstract:

   Include file for CustomDSP

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

// CustomDSP.cpp variables
extern HWND             g_hwndApp;                   // HWND of the application
extern HINSTANCE        g_hinst;                     // HINSTANCE of the application

// Error.cpp variables
extern toutputlevel     g_outputlevel;               // Amount of detail in error messages
extern terr             g_errLast;                   // Error return code of last function

// DSUtil.cpp variables
extern LPDIRECTSOUND    g_pds;                       // The main DirectSound object

// ++++ Global Functions ++++++++++++++++++++++++++++++++++++++++++++

// DSUtil.cpp functions
BOOL InitDirectSound();
IDirectSoundBuffer *LoadSoundBuffer(LPCTSTR lpName);

// DSPUtil.cpp functions
BOOL LoadDSPFiles(TCHAR *tszDSPCodeFile, TCHAR *tszMixerFile, PBYTE *ppbFile1, DWORD *pcbFile1, PBYTE *ppbFile2, DWORD *pcbFile2);

// Error.cpp functions
BOOL CheckError(TCHAR *tszErr);
void RetailOutput(TCHAR *tszErr, ...);
#ifdef DEBUG
void DebugOutput(TCHAR *tszErr, ...);
#else
__inline void DebugOutput(TCHAR *tszErr, ...) {};
#endif
