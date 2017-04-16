
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

#define MUTEXNAME "PageTest"

#include <windows.h>

#ifdef DYNACRT
BOOL WINAPI _CRT_INIT(HINSTANCE hDLL, DWORD dwReason,LPVOID lpReserved);
#endif


#ifdef MANYPAGES
#define NAMEENTRIES 100000
LPSTR lpNames[NAMEENTRIES]=
#ifdef FIXUPS
#include "fixups.h"
#else
{NULL};
#endif
#endif

/******************************************************************************\
*
*  FUNCTION:    DllMain
*
*  INPUTS:      hDLL       - handle of DLL
*               dwReason   - indicates why DLL called
*               lpReserved - reserved
*
*  RETURNS:     TRUE (always, in this example.)
*
*               Note that the retuRn value is used only when
*               dwReason = DLL_PROCESS_ATTACH.
*
*               Normally the function would return TRUE if DLL initial-
*               ization succeeded, or FALSE it it failed.
*
*  GLOBAL VARS: ghMod - handle of DLL (initialized when PROCESS_ATTACHes)
*
*  COMMENTS:    The function will display a dialog box informing user of
*               each notification message & the name of the attaching/
*               detaching process/thread. For more information see
*               "DllMain" in the Win32 API reference.
*
\******************************************************************************/
#ifdef STANDARDENTRY
BOOL WINAPI DllMain (HANDLE hDLL, DWORD dwReason, LPVOID lpReserved)
#else
BOOL WINAPI DllNoCRTMain (HANDLE hDLL, DWORD dwReason, LPVOID lpReserved)
#endif
{
#ifdef DYNACRT
 if (!_CRT_INIT(hDLL,dwReason,lpReserved)) return FALSE;
#endif

  switch (dwReason)
  {
    case DLL_PROCESS_ATTACH:
    {
     HANDLE hMutex;
	 hMutex = OpenMutex(SYNCHRONIZE,TRUE,MUTEXNAME);
	 ReleaseMutex(hMutex);
      //
      // DLL is attaching to the address space of the current process.
      //

      break;
    }

    case DLL_THREAD_ATTACH:
      break;

    case DLL_THREAD_DETACH:
      break;

    case DLL_PROCESS_DETACH:
      break;
  }

return
// this code was moved to right after the entry point
/* 
#ifdef DYNACRT
_CRT_INIT(hDLL,dwReason,lpReserved);
#else
TRUE;
#endif
*/
TRUE;
}

#ifdef HASEXPORTS
__declspec (dllexport) void ExportFunc1(int i)
{
 return;
}
#endif

