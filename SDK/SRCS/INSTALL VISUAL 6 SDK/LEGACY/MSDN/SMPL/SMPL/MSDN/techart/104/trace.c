#include <windows.h>
#include <stdio.h>  //DER -- This include was missing in first version
#include <stdarg.h>
#include "trace.h"

///////////////////////////////////////////////////////////////////////
//
// TRACE() - does a printf to the debug monitor
// -------
//
#define nLocalBuf 512

void __export FAR CDECL trace(LPCSTR pszFormat, ...)
{
	int nBuf ;
	char szBuffer[nLocalBuf] ;
	
	va_list args ;
	va_start(args, pszFormat) ;
	
	nBuf = vsprintf(szBuffer, pszFormat, args) ;
	
	OutputDebugString(szBuffer) ;	
}
