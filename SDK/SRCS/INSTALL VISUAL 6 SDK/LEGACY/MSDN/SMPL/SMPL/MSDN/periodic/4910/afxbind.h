// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.

// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#ifndef __AFXBIND_H_
#define __AFXBIND_H_

#ifdef _UNICODE
#error ERROR: MFC Active Documents does not yet support Unicode.
#endif


#ifndef _AFX_NOFORCE_LIBS
#ifndef _MAC

#ifdef _AFXDLL
#ifdef _DEBUG
	#ifdef _UNICODE
		#pragma comment(lib, "MFCISUD.lib")
	#else
		#pragma comment(lib, "EAFXADD.lib")
	#endif
#else
	#ifdef _UNICODE
		#pragma comment(lib, "MFCISU.lib")
	#else
		#pragma comment(lib, "EAFXAD.lib")
	#endif // _UNICODE
#endif // _DEBUG
#else
#ifdef _DEBUG
	#ifdef _UNICODE
		#pragma comment(lib, "UAFXISD.lib")
	#else
		#pragma comment(lib, "NAFXADD.lib")
	#endif
#else
	#ifdef _UNICODE
		#pragma comment(lib, "UAFXIS.lib")
	#else
		#pragma comment(lib, "NAFXAD.lib")
	#endif // _UNICODE
#endif // _DEBUG
#endif // _AFXDLL

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "winspool.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "uuid3.lib")

#endif // _MAC
#endif // _AFX_NOFORCE_LIBS

#include <binddoc.h>
#include <bindipfw.h>
#include <binditem.h>
#include <mfcbind.h>

#endif // __AFXBIND_H

