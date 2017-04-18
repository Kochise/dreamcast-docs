/***
*dllmain.c - Dummy DllMain for user DLLs that have no notification handler
*
*       Copyright (c) 1993-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This object goes into LIBC.LIB and LIBCMT.LIB and MSVCRT.LIB for use
*       when linking a DLL with one of the three models of C run-time library.
*       If the user does not provide a DllMain notification routine, this
*       dummy handler will be linked in.  It always returns TRUE (success).
*
******************************************************************************/

#ifdef _WIN32

#include <oscalls.h>
#define _DECL_DLLMAIN   /* include prototype of _pRawDllMain */
#include <process.h>

/***
*DllMain - dummy version DLLs linked with all 3 C Run-Time Library models
*
*Purpose:
*       The routine DllMain is always called by _DllMainCrtStartup.  If
*       the user does not provide a routine named DllMain, this one will
*       get linked in so that _DllMainCRTStartup has something to call.
*
*       For the LIBC.LIB and MSVCRT.LIB models, the CRTL does not need
*       per-thread notifications so if the user is ignoring them (default
*       DllMain and _pRawDllMain == NULL), just turn them off.  (WIN32-only)
*
*Entry:
*
*Exit:
*
*Exceptions:
*
******************************************************************************/

BOOL WINAPI DllMain(
        HANDLE  hDllHandle,
        DWORD   dwReason,
        LPVOID  lpreserved
        )
{
#if !defined (_MT) || defined (CRTDLL)
        if ( dwReason == DLL_PROCESS_ATTACH && ! _pRawDllMain )
                DisableThreadLibraryCalls(hDllHandle);
#endif  /* !defined (_MT) || defined (CRTDLL) */
        return TRUE ;
}

#else  /* _WIN32 */

#include <cruntime.h>
#include <macos\types.h>
#include <macos\fragload.h>

/***
*_DllInit - dummy version DLLs linked with all 2 C Run-Time Library models
*
*Purpose:
*       The routine _DllInit is always called by _DllMainCrtStartup.  If
*       the user does not provide a routine named _DllInit, this one will
*       get linked in so that _DllMainCRTStartup has something to call.
*
*Entry:
*
*Exit:
*
*Exceptions:
*
******************************************************************************/

OSErr _DllInit(InitBlockPtr pinitBlk)
{
        return noErr ;
}


#endif  /* _WIN32 */
