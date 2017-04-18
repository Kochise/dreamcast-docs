// OneWndWz.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "OneWndWz.h"
#include "OneWndWzaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE OneWndWzDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("ONEWNDWZ.AWX Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(OneWndWzDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(OneWndWzDLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&OneWndWzaw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("ONEWNDWZ.AWX Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(OneWndWzDLL);
	}
	return 1;   // ok
}
