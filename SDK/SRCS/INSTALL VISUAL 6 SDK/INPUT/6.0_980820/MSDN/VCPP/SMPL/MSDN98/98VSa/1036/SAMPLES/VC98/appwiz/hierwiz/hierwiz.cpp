// hierwiz.cpp : Defines the initialization routines for the DLL.
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "hierwiz.h"
#include "hierwaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE hierwizDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("HIERWIZ.DLL Initializing!\n");

		// Extension DLL one-time initialization
		AfxInitExtensionModule(hierwizDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(hierwizDLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&hierwizaw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("HIERWIZ.DLL Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(hierwizDLL);
	}
	return 1;   // ok
}
