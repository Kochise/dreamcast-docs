// util.cpp - Common utilities for printing out messages
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#include <objbase.h>
#include <stdio.h> //sprintf..
#include <stdlib.h>
#include <stdarg.h>

#include "util.h"

/////////////////////////////////////////////////////////////////////////////
//

void ErrorMessage(LPCTSTR message, HRESULT hr)
{
	const char* sz ;
	if (message == NULL)
		sz = "The following error occured." ;
	else
		sz = message;

	void* pMsgBuf;

	::FormatMessage(
		 FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		 NULL,
		 hr,
		 MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		 (LPTSTR) &pMsgBuf,
		 0,
		 NULL
	);

	TCHAR buf[1024];
	wsprintf(buf, "%s\r\nError: (0x%x) - %s", sz, hr, (LPTSTR) pMsgBuf);

	MessageBox(NULL, buf, "Utility Error Message Box.", MB_OK);

	// Free the buffer.
	LocalFree(pMsgBuf);
}

/////////////////////////////////////////////////////////////////////////////
//  Check to see if both interfaces are on the same component.

BOOL InterfacesAreOnSameComponent(IUnknown* p1, IUnknown* p2)
{
	HRESULT hr = S_OK ;

	// Get the real IUnknown for the first interface.
	IUnknown* pReal1 = NULL ;
	hr = p1->QueryInterface(IID_IUnknown, (void**)&pReal1) ;
	assert(SUCCEEDED(hr)) ;

	// Get the real IUnknown for the second interface.
	IUnknown* pReal2 = NULL ;
	hr = p2->QueryInterface(IID_IUnknown, (void**)&pReal2) ;
	assert(SUCCEEDED(hr)) ;

	// Compare the IUnknown pointers.
	BOOL bReturn = (pReal1 == pReal2) ;

	// Cleanup
	pReal1->Release() ;
	pReal2->Release() ;

	// Return the value.
	return bReturn;
}


/////////////////////////////////////////////////////////////////////////////
//  IsValidAddress

BOOL IsValidAddress(const void* lp, UINT nBytes, BOOL bReadWrite)
{
	return (lp != NULL && !::IsBadReadPtr(lp, nBytes) &&
		(!bReadWrite || !::IsBadWritePtr((LPVOID)lp, nBytes)));
}


///////////////////////////////////////////////////////////
//
//  Trace
//
void __cdecl MyTrace(LPCTSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	int nBuf;
	TCHAR szBuffer[512];

	nBuf = _vsnprintf(szBuffer, sizeof(szBuffer)*sizeof(TCHAR), lpszFormat, args);

	// was there an error? was the expanded string too long?
	assert(nBuf > 0);

	OutputDebugString(szBuffer) ;

	va_end(args);
}
