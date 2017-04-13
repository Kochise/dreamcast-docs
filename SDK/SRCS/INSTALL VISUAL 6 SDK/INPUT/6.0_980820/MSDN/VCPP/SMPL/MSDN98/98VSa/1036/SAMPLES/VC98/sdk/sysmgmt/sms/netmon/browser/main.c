
//=============================================================================
//  MODULE: main.c
//
//  Description:
//
//  Bloodhound parer DLL Browser
//
//  Modification History
//
//
//=============================================================================

#include "browser.h"

extern ENTRYPOINTS BrowserEntryPoints;


extern HPROTOCOL hBrowser;

// question
DWORD Attached = 0;

//=============================================================================
//  FUNCTION: DLLEntry()
//
//  Modification History
//
//
//=============================================================================

BOOL WINAPI DLLEntry(HANDLE hInstance, ULONG Command, LPVOID Reserved)
{
    //=========================================================================
    //  If we are loading!
    //=========================================================================

    if ( Command == DLL_PROCESS_ATTACH )
    {
        if ( Attached++ == 0 )
        {
            hBrowser = CreateProtocol("Browser", &BrowserEntryPoints, ENTRYPOINTS_SIZE);
           
        }
    }

    //=========================================================================
    //  If we are unloading!
    //=========================================================================

    if ( Command == DLL_PROCESS_DETACH )
    {
        if ( --Attached == 0 )
        {
            DestroyProtocol(hBrowser);

        }
    }

    return TRUE;                    //... Bloodhound parsers ALWAYS return TRUE.
}

