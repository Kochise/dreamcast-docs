// VBUTIL.H

//@B VBUtil
#ifndef _VBUTIL_H_
#define _VBUTIL_H_

#include <windows.h> 
#include <io.h>
#include <iostream.h>
#include <strstrea.h>
#include "oletype.h"

// Temporary buffer size
const TEMP_MAX = 512;

#define DLLAPI  WINAPI // Currently evaluates to __stdcall

// Make ASSERT statement (fails in expressions where it shouldn't be used)
#if defined(DEBUG)
	#define ASSERT(f) \
		if (f)        \
			NULL;     \
		else          \
			assert(f) 
#else
	#define ASSERT(f) NULL
#endif

void ErrorHandler(Long e);
DWORD HResultToErr(Long e);

#endif // _VBUTIL_H_
//@E VBUtil

