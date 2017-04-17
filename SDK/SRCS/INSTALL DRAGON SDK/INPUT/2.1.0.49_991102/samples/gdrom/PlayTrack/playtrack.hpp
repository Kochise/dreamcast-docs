/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    PlayTrack.hpp

Abstract:

   Include file for the PlayTrack sample

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++

#include <tchar.h>
#include <windows.h>
#include <ceddcdrm.h>
#include <segagdrm.h>

// ++++ Enumerated Types ++++++++++++++++++++++++++++++++++++++++++++

// Output types
enum toutputlevel { OUTPUT_ALL = 0, OUTPUT_FAILURESONLY };

// ++++ Types +++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Error type
typedef int terr;

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

// PlayTrack.cpp variables
extern HWND                g_hwndApp;             // HWND of the application
extern HINSTANCE           g_hinst;               // HINSTANCE of the application

// Error.cpp variables
extern toutputlevel        g_outputlevel;         // Amount of detail in error messages
extern terr                g_errLast;             // Error return code of last function

// ++++ Global Functions ++++++++++++++++++++++++++++++++++++++++++++

// GDUtil.cpp functions
BOOL IsCDPlaying(HANDLE hGDROM);
void SetCDVolume(HANDLE hGDROM, UCHAR ucLeftVolume, UCHAR ucRightVolume);
void GetCDVolume(HANDLE hGDROM, UCHAR* pucLeftVolume, UCHAR* pucRightVolume);
void PlayTrack(HANDLE hGDROM, int nStartTrackNumber, int nEndTrackNumber, int nRepeats);

// Error.cpp functions
BOOL CheckError(TCHAR *tszErr);
void RetailOutput(TCHAR *tszErr, ...);
#ifdef DEBUG
void DebugOutput(TCHAR *tszErr, ...);
#else
__inline void DebugOutput(TCHAR *tszErr, ...) {};
#endif
