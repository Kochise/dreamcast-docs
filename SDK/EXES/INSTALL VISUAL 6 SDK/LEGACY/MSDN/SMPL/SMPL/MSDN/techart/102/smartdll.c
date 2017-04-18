// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.
//
#include <windows.h>
#include <windowsx.h>
#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>
#include "smart.h"

void CDECL trace(LPCSTR pszFormat, ...);


HGLOBAL WINAPI EXPORTED xGlobalFree(HGLOBAL hglb)
{
	trace("GlobalFree(%#x)\r\n", (UINT)hglb) ;
	return GlobalFree(hglb) ;
}

HGLOBAL WINAPI EXPORTED xGlobalReAlloc(HGLOBAL hglb, DWORD dwNewSize, UINT flags)
{
	trace("GlobalReAlloc(%#x, %lu, %u)\r\n",
			 (UINT) hglb, (DWORD)dwNewSize, (UINT)flags) ;
	return GlobalReAlloc(hglb, dwNewSize, flags) ;
}

HGLOBAL WINAPI EXPORTED xGlobalAlloc(UINT flags, DWORD dwSize)
{
	trace("GlobalAlloc(%u, %ld)\r\n",(UINT) flags, (DWORD) dwSize) ;
	return GlobalAlloc(flags, dwSize) ;
}

/////////////////////////////////////////////////////////////////////////
//
// Memory Allocation Functions
//
void * EXPORTED DllMalloc(HWND hwnd, DWORD size, UINT options) 
{
	// Program is compiled large model to get _fmalloc 
	if( size > _HEAP_MAXREQ )
	{
		MessageBox(hwnd, "Cannot allocate memory block this large.",
					  "Smart Alloc",MB_OK | MB_ICONEXCLAMATION ) ;
		MessageBeep(0) ;
		return NULL ;
	}
	else
		return malloc((size_t)size) ;	
}

void * EXPORTED DllGalloc(HWND hwnd, DWORD size, UINT options)
{
	return GlobalAllocPtr(options,size) ;
}

/////////////////////////////////////////////////////////////////////////
//
// Free Functions
//
void EXPORTED DllMfree(void * ptr) 
{
	free(ptr) ;
}

void EXPORTED DllGfree(void * ptr) 
{
	// See Windowsx.h for GlobalFreePtr Definition
	GlobalFreePtr(ptr) ;
}

///////////////////////////////////////////////////////////////////////
//
// trace() - does a printf to the debug monitor
//
#define nLocalBuf 512

void CDECL trace(LPCSTR pszFormat, ...)
{
	int nBuf ;
	char szBuffer[nLocalBuf] ;
	
	va_list args ;
	va_start(args, pszFormat) ;
	
	nBuf = vsprintf(szBuffer, pszFormat, args) ;
	
	OutputDebugString(szBuffer) ;
}


///////////////////////////////////////////////////////////////////////						
//
// The environment is not used.  Suppress these functions which use the 
//	environment. _setenvp allocates space with malloc()..
//
void _setargv() {} ;
void _setenvp() {} ;
