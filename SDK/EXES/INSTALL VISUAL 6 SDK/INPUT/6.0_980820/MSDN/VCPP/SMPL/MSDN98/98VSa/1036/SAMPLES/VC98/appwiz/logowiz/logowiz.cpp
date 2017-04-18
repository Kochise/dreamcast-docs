// logowiz.cpp : Defines the initialization routines for the DLL.
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include <afxdllx.h>
#include "logowiz.h"
#include "logowaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE logowizDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("LOGOWIZ.AWX Initializing!\n");

		// Extension DLL one-time initialization
		AfxInitExtensionModule(logowizDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(logowizDLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&logowizaw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("LOGOWIZ.AWX Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(logowizDLL);
	}
	return 1;   // ok
}
