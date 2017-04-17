/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    Common.hpp

Abstract:

   Include file for Common

-------------------------------------------------------------------*/

#ifndef __COMMON_HXX__
#define __COMMON_HXX__

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++

#include <tchar.h>
#include <windows.h>
#include <ddraw.h>
#include <d3d.h>

// ++++ Enumerated Types ++++++++++++++++++++++++++++++++++++++++++++

// Key values
enum toutputlevel { OUTPUT_ALL = 0, OUTPUT_FAILURESONLY };

typedef int terr;

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

extern toutputlevel g_outputlevel;
extern terr g_errLast;             // Error return code of last function

// ++++ Global Functions ++++++++++++++++++++++++++++++++++++++++++++

BOOL CheckError(TCHAR *tszErr);
#ifdef DEBUG
void DebugOutput(TCHAR *tszErr, ...);
#else
__inline void DebugOutput(TCHAR *tszErr, ...) {};
#endif

void RetailOutput(TCHAR *tszErr, ...);

#endif // __COMMON_HXX__
