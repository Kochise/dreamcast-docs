/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    Format1.hpp

Abstract:

   Include file for Format1

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++

#include <tchar.h>
#include <windows.h>
#include <mmsystem.h>

// ++++ Enumerated Types ++++++++++++++++++++++++++++++++++++++++++++

// Output types
enum toutputlevel { OUTPUT_ALL = 0, OUTPUT_FAILURESONLY };

// ++++ Types +++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Error type
typedef int terr;

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

// Format1.cpp variables
extern HINSTANCE    g_hinstApp;                         // HINSTANCE of the application

// Error.cpp variables
extern toutputlevel g_outputlevel;                      // Amount of detail in error messages
extern terr         g_errLast;                          // Error return code of last function

// ++++ Global Functions ++++++++++++++++++++++++++++++++++++++++++++

// MIDIUtil.cpp functions
BYTE *AllocAligned(DWORD cb, DWORD cbAlign);
void FreeAligned(BYTE *pbyData);
BOOL LoadSequence(MIDIHDR *pmh, TCHAR *pszFilename, WORD *ptd, DWORD dwTempo);
void FreeSequence(BYTE *pbSequence);
BOOL LoadTonebank(TCHAR *tszName, MIDIHDR *pmh);

// Error.cpp functions
BOOL CheckError(TCHAR *tszErr);
void RetailOutput(TCHAR *tszErr, ...);
#ifdef DEBUG
void DebugOutput(TCHAR *tszErr, ...);
#else
__inline void DebugOutput(TCHAR *tszErr, ...) {};
#endif
