// GLlib.cpp : Defines the initialization routines for the DLL.
//
#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE GLlibDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("GLLIB.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(GLlibDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(GLlibDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("GLLIB.DLL Terminating!\n");
	}
	return 1;   // ok
}

