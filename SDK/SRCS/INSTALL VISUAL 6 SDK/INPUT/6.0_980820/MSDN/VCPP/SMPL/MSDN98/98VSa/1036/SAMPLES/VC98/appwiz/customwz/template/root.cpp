// $$root$$.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "$$root$$.h"
#include "$$filebase$$aw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE $$safe_root$$DLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("$$ROOT$$.AWX Initializing!\n");

		// Extension DLL one-time initialization
		AfxInitExtensionModule($$safe_root$$DLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary($$safe_root$$DLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&$$safe_root$$aw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("$$ROOT$$.AWX Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule($$safe_root$$DLL);
	}
	return 1;   // ok
}
