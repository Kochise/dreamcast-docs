//*------------------------------------------------------------------------
//|	File:			DLLSTUB.C
//|
//|	Purpose:		This is a generic module which contains the entry points
//|						required to compile a DLL.
//*------------------------------------------------------------------------
#include <windows.h>
#include "autotest.h"

HINSTANCE		hLoadedInst;



//-------------------------------------------------------------------------
//	For WIN32 programs, there is only one entry point which takes care of
//		everything.  For 16 bit apps, however, there are two entry points,
//		LibMain which is called upon initialization, and WEP which is the
//		windows exit procedure.
//-------------------------------------------------------------------------


#ifdef WIN32
#include <winnt.h>

int EXTFUN TstLibMain(HANDLE hInst, DWORD fdwReason, LPVOID lpReserved)
{
	BOOL WINAPI _CRT_INIT(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpReserved);

	switch(fdwReason) {
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
			hLoadedInst = hInst;
			if(!hLoadedInst || !(_CRT_INIT(hInst, fdwReason, lpReserved)))
				return FALSE;
			break;
			
		case DLL_PROCESS_DETACH:
		case DLL_THREAD_DETACH:
			if(!(_CRT_INIT(hInst, fdwReason, lpReserved)))
				return FALSE;
			break;
		}

	return TRUE;
}

#else


//*---------------------------------------------------------------------------------
//| LibMain:
//|	This entry point will simply take care of our data segment.
//| Parms:
//|	in			hInst						Current hInstance (data segment)
//|	in			wDataSeg					
//|	in			cbHeapSize
//|	in			szCmdLine				Command line arguments
//| Returns:
//|	TRUE if successful, FALSE on a failure
//*---------------------------------------------------------------------------------
int EXTFUN LibMain(HINSTANCE hInst, WORD wDataSeg, WORD cbHeapSize, LPSTR szCmdLine)
{
	if(cbHeapSize != 0)
		UnlockData(0);

	hLoadedInst = hInst;

	return TRUE;
}



//*---------------------------------------------------------------------------------
//| WEP:
//|	This is the windows exit procedure.  We will be passed a flag which
//|		tells us if we are being unloaded by a normal Unload call or if
//|		the system is shutting down.
//| Parms:
//|	int		fParm						What type of unload?
//| Returns:
//|	TRUE always
//*---------------------------------------------------------------------------------
int EXTFUN WEP(int fParm)
{
	switch (fParm) {
		case WEP_SYSTEM_EXIT:
		case WEP_FREE_DLL:
		default:
			return TRUE;
	}
}



#endif

