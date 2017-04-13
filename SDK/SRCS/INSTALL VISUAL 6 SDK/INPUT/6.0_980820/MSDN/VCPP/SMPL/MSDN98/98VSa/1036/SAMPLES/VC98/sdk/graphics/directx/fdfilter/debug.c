/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:		debug.c
 *  Content:	debug code
 *
 ***************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <stdarg.h>
#include <dsound.h>
#include "debug.h"

#if defined(DEBUG) || defined(_DEBUG)


//
//  since we don't UNICODE our debugging messages, use the ASCII entry
//  points regardless of how we are compiled.
//
#ifdef _WIN32
    #include <wchar.h>
#else
    #define lstrcatA            lstrcat
    #define lstrlenA            lstrlen
    #define GetProfileIntA      GetProfileInt
    #define OutputDebugStringA  OutputDebugString
    #define wsprintfA           wsprintf
    #define MessageBoxA         MessageBox
#endif

//
//
//
BOOL    __gfDbgEnabled          = TRUE;         // master enable
UINT    __guDbgLevel            = 0;            // current debug level


//--------------------------------------------------------------------------;
//  
//  void DbgVPrintF
//  
//  Description:
//  
//  
//  Arguments:
//      LPSTR szFormat:
//  
//      va_list va:
//  
//  Return (void):
//      No value is returned.
//  
//--------------------------------------------------------------------------;

void FAR CDECL DbgVPrintF
(
    LPSTR                   szFormat,
    va_list                 va
)
{
    char                ach[DEBUG_MAX_LINE_LEN];
    BOOL                fDebugBreak = FALSE;
    BOOL                fPrefix     = TRUE;
    BOOL                fCRLF       = TRUE;

    ach[0] = '\0';

    for (;;)
    {
        switch (*szFormat)
        {
            case '!':
                fDebugBreak = TRUE;
                szFormat++;
                continue;

            case '`':
                fPrefix = FALSE;
                szFormat++;
                continue;

            case '~':
                fCRLF = FALSE;
                szFormat++;
                continue;
        }

        break;
    }

    if (fDebugBreak)
    {
        ach[0] = '\007';
        ach[1] = '\0';
    }

    if (fPrefix)
    {
        lstrcatA(ach, DEBUG_MODULE_NAME ": ");
    }

#ifdef _WIN32
    wvsprintfA(ach + lstrlenA(ach), szFormat, va);
#else
    wvsprintf(ach + lstrlenA(ach), szFormat, (LPSTR)va);
#endif

    if (fCRLF)
    {
        lstrcatA(ach, "\r\n");
    }

    OutputDebugStringA(ach);

    if (fDebugBreak)
    {
        DebugBreak();
    }
} // DbgVPrintF()


//--------------------------------------------------------------------------;
//  
//  void dprintf
//  
//  Description:
//      dprintf() is called by the DPF() macro if DEBUG is defined at compile
//      time. It is recommended that you only use the DPF() macro to call
//      this function--so you don't have to put #ifdef DEBUG around all
//      of your code.
//      
//  Arguments:
//      UINT uDbgLevel:
//  
//      LPSTR szFormat:
//  
//  Return (void):
//      No value is returned.
//
//--------------------------------------------------------------------------;

void FAR CDECL dprintf
(
    UINT                    uDbgLevel,
    LPSTR                   szFormat,
    ...
)
{
    va_list va;

    if (!__gfDbgEnabled || (__guDbgLevel < uDbgLevel))
        return;

    va_start(va, szFormat);
    DbgVPrintF(szFormat, va);
    va_end(va);
} // dprintf()


//--------------------------------------------------------------------------;
//  
//  BOOL DbgEnable
//  
//  Description:
//  
//  
//  Arguments:
//      BOOL fEnable:
//  
//  Return (BOOL):
//      Returns the previous debugging state.
//  
//--------------------------------------------------------------------------;

BOOL WINAPI DbgEnable
(
    BOOL                    fEnable
)
{
    BOOL                fOldState;

    fOldState      = __gfDbgEnabled;
    __gfDbgEnabled = fEnable;

    return (fOldState);
} // DbgEnable()


//--------------------------------------------------------------------------;
//  
//  UINT DbgSetLevel
//  
//  Description:
//  
//  
//  Arguments:
//      UINT uLevel:
//  
//  Return (UINT):
//      Returns the previous debugging level.
//  
//--------------------------------------------------------------------------;

UINT WINAPI DbgSetLevel
(
    UINT                    uLevel
)
{
    UINT                uOldLevel;

    uOldLevel    = __guDbgLevel;
    __guDbgLevel = uLevel;

    return (uOldLevel);
} // DbgSetLevel()


//--------------------------------------------------------------------------;
//  
//  UINT DbgGetLevel
//  
//  Description:
//  
//  
//  Arguments:
//      None.
//  
//  Return (UINT):
//      Returns the current debugging level.
//  
//--------------------------------------------------------------------------;

UINT WINAPI DbgGetLevel
(
    void
)
{
    return (__guDbgLevel);
} // DbgGetLevel()


//--------------------------------------------------------------------------;
//  
//  UINT DbgInitialize
//  
//  Description:
//  
//  
//  Arguments:
//      BOOL fEnable:
//  
//  Return (UINT):
//      Returns the debugging level that was set.
//  
//--------------------------------------------------------------------------;

UINT WINAPI DbgInitialize
(
    BOOL                    fEnable
)
{
    UINT                uLevel;

    uLevel = GetProfileIntA(DEBUG_SECTION, DEBUG_MODULE_NAME, (UINT)-1);
    if ((UINT)-1 == uLevel)
    {
        //
        //  if the debug key is not present, then force debug output to
        //  be disabled. this way running a debug version of a component
        //  on a non-debugging machine will not generate output unless
        //  the debug key exists.
        //
        uLevel  = 0;
        fEnable = FALSE;
    }

    DbgSetLevel(uLevel);
    DbgEnable(fEnable);

    return (__guDbgLevel);
} // DbgInitialize()


void WINAPI DbgDumpWFX( int nLevel, PWAVEFORMATEX pwfx )
    {
    DPF( nLevel, "Dumping WAVEFORMATEX at 0x%08lX", pwfx );
    DPF( nLevel, "wFormatTag = %u, nChannels = %u, nSamplesPerSec = %lu",
		pwfx->wFormatTag, pwfx->nChannels, pwfx->nSamplesPerSec );
    DPF( nLevel, "nAvgBytesPerSec = %lu, nBlockAlign = %u, wBitsPerSample = %lu",
		pwfx->nAvgBytesPerSec, pwfx->nBlockAlign, pwfx->wBitsPerSample );
    DPF( nLevel, "cbSize = %u",pwfx->cbSize );
    }


//--------------------------------------------------------------------------;
//  
//  void _Assert
//  
//  Description:
//      This routine is called if the ASSERT macro (defined in debug.h)
//      tests and expression that evaluates to FALSE.  This routine 
//      displays an "assertion failed" message box allowing the user to
//      abort the program, enter the debugger (the "retry" button), or
//      ignore the assertion and continue executing.  The message box
//      displays the file name and line number of the _Assert() call.
//  
//  Arguments:
//      char *  szFile: Filename where assertion occurred.
//      int     iLine:  Line number of assertion.
//  
//--------------------------------------------------------------------------;

#ifndef _WIN32
#pragma warning(disable:4704)
#endif

void WINAPI _Assert
(
    char *  szFile,
    int     iLine
)
{
    static char     ach[300];       // debug output (avoid stack overflow)
    int	            id;
#ifndef _WIN32
    int             iExitCode;
#endif

    wsprintfA(ach, "Assertion failed in file %s, line %d.  [Press RETRY to debug.]", (LPSTR)szFile, iLine);

    id = MessageBoxA(NULL, ach, "Assertion Failed",
            MB_SYSTEMMODAL | MB_ICONHAND | MB_ABORTRETRYIGNORE );

	switch (id)
	{

	case IDABORT:               // Kill the application.
#ifndef _WIN32
        iExitCode = 0;
        _asm
        {
	        mov	ah, 4Ch
	        mov	al, BYTE PTR iExitCode
	        int     21h
        }
#else
        FatalAppExit(0, TEXT("Good Bye"));
#endif // WIN16
		break;

	case IDRETRY:               // Break into the debugger.
		DebugBreak();
		break;

	case IDIGNORE:              // Ignore assertion, continue executing.
		break;
	}
} // _Assert

#ifndef _WIN32
#pragma warning(default:4704)
#endif

#endif // #if defined(DEBUG) || defined(_DEBUG)

// Silly little function gives meaningful error messages from HRESULT's
LPSTR TranslateDSError( HRESULT hr )
    {
    switch( hr )
	{
	case DSERR_ALLOCATED:
	    return "DSERR_ALLOCATED";

	case DSERR_CONTROLUNAVAIL:
	    return "DSERR_CONTROLUNAVAIL";

	case DSERR_INVALIDPARAM:
	    return "DSERR_INVALIDPARAM";

	case DSERR_INVALIDCALL:
	    return "DSERR_INVALIDCALL";

	case DSERR_GENERIC:
	    return "DSERR_GENERIC";

	case DSERR_PRIOLEVELNEEDED:
	    return "DSERR_PRIOLEVELNEEDED";

	case DSERR_OUTOFMEMORY:
	    return "DSERR_OUTOFMEMORY";

	case DSERR_BADFORMAT:
	    return "DSERR_BADFORMAT";

	case DSERR_UNSUPPORTED:
	    return "DSERR_UNSUPPORTED";

	case DSERR_NODRIVER:
	    return "DSERR_NODRIVER";

	case DSERR_ALREADYINITIALIZED:
	    return "DSERR_ALREADYINITIALIZED";

	case DSERR_NOAGGREGATION:
	    return "DSERR_NOAGGREGATION";

	case DSERR_BUFFERLOST:
	    return "DSERR_BUFFERLOST";

	case DSERR_OTHERAPPHASPRIO:
	    return "DSERR_OTHERAPPHASPRIO";

	case DSERR_UNINITIALIZED:
	    return "DSERR_UNINITIALIZED";

	default:
	    return "Unknown HRESULT";
	}
    }


