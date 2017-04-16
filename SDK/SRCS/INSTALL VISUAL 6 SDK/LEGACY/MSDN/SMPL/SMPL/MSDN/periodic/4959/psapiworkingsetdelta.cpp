//=======================================
// PSAPI Working Set Demo - Matt Pietrek 1996
// Microsoft Systems Journal, November 1996
// FILE: "PSAPIWorkingSetDelta.CPP"
//=======================================
#include <windows.h>
#include <stdlib.h>
#pragma hdrstop
#include "psapi.h"
#include "psapiworkingsetdelta.h"
#include "PSAPIhelper.h"

void Handle_Delta_WM_COMMAND( HWND hDlg, WPARAM wParam, LPARAM lParam )
{
    HWND hwndCtl = (HWND)lParam;

    switch ( LOWORD(wParam) )
    {
        case IDOK: EndDialog( hDlg, 0 ); break;
    }
}

#define MAX_WS_DELTA_PAGES 0x4000

static HANDLE   g_WorkingSetHProcess = 0;
static PSAPI_WS_WATCH_INFORMATION g_WorkingSetChanges[MAX_WS_DELTA_PAGES];

void FillDeltaListbox( HWND hWndLb )
{
    // Create a pointer to the g_WorkingSetChanges array
    PPSAPI_WS_WATCH_INFORMATION pWSDelta
                        = (PPSAPI_WS_WATCH_INFORMATION) g_WorkingSetChanges;

    SendMessage( hWndLb, WM_SETREDRAW, FALSE, 0 );  // Disable LB updating

    // Loop through each entry in the array until we find an element that
    // has both the FaultingPC and FaultingVA set to 0.  This indicates the
    // end of the array.

    while ( pWSDelta->FaultingPc || pWSDelta->FaultingVa )
    {
        // Skip over entries above 2GB.  They can't (easily) be mapped to
        // module names, and the user can't do any about them anyway
        if ( pWSDelta->FaultingPc >= (PVOID)0x80000000 )
        {
            pWSDelta++;
            continue;
        }
            
        //
        // Warning!!! If a long period transpires between the start and end of
        // the WorkingSetDelta, or if memory is extremely low, it's possible
        // to have multiple entries here with the same address.
        //
        char szOutBuffer[ MAX_PATH * 4 ];
        PSTR pszBuffCurr = szOutBuffer;

        pszBuffCurr += wsprintf( pszBuffCurr, "%08X  %08X  ",
                                 pWSDelta->FaultingVa, pWSDelta->FaultingPc );

        char    szMod[MAX_PATH];
        char    szSection[IMAGE_SIZEOF_SHORT_NAME+1];
        DWORD   uSection;
        BOOL    fFoundInfo;

        // Get information (such as the module and section name) for the
        // page that was faulted in
        fFoundInfo = 
            GetModuleNameAndSectionInfo(
                                        g_WorkingSetHProcess,
                                        pWSDelta->FaultingVa,
                                        szMod, sizeof(szMod),
                                        szSection, sizeof(szSection),
                                        &uSection );

        if ( fFoundInfo )   // The address is within a loaded Win32 module
        {
            if ( uSection )
                pszBuffCurr += wsprintf( pszBuffCurr, "%s!%s(%u)",
                                         szMod, szSection, uSection);
            else
                pszBuffCurr += wsprintf( pszBuffCurr, "%s", szMod);
        }
        else    // Not an address in a Win32 module
        {
            // Could be a stack page, a heap page, or whatever!
            pszBuffCurr += wsprintf( pszBuffCurr, "???" );
        }

        // Get information (such as the module and section name) for the
        // page that caused the fault
        fFoundInfo = 
            GetModuleNameAndSectionInfo(
                                        g_WorkingSetHProcess,
                                        pWSDelta->FaultingPc,
                                        szMod, sizeof(szMod),
                                        szSection, sizeof(szSection),
                                        &uSection );

        if ( fFoundInfo )   // The address is within a loaded Win32 module
        {
            if ( uSection )
                pszBuffCurr += wsprintf( pszBuffCurr, " via %s!%s(%u)",
                                         szMod, szSection, uSection);
        }

        // Dump everything out the listbox (finally!)
        SendMessage( hWndLb, LB_ADDSTRING, 0, (LPARAM)szOutBuffer );

        pWSDelta++;     // Advance to next page which was faulted in
    }

    SendMessage( hWndLb, WM_SETREDRAW, TRUE, 0 );   // Enable LB updating
}

void Handle_Delta_WM_INITDIALOG( HWND hDlg )
{
    FillDeltaListbox( GetDlgItem(hDlg, IDC_LB_DELTA) );
}

void Handle_Delta_WM_CLOSE( HWND hDlg )
{
    EndDialog( hDlg, 0 );
}

BOOL CALLBACK DeltaDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    //
    // The dialog procedure for the main window
    //
    switch ( msg )
    {
        case WM_COMMAND:
            Handle_Delta_WM_COMMAND( hDlg, wParam, lParam ); return TRUE;
        case WM_INITDIALOG:
            Handle_Delta_WM_INITDIALOG( hDlg ); return TRUE;
        case WM_CLOSE:
            Handle_Delta_WM_CLOSE( hDlg ); break;
        // let everything else fall through
    }
    return FALSE;
}

BOOL StartWorkingSetDelta( DWORD pid )
{
    // Open a process handle, and store it in (Eeek!) a Global variable
    g_WorkingSetHProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pid );

    if ( !g_WorkingSetHProcess )
        return FALSE;

    if ( !InitializeProcessForWsWatch( g_WorkingSetHProcess ) )
    {
        CloseHandle( g_WorkingSetHProcess );
        g_WorkingSetHProcess = 0;
        return FALSE;
    }

    // Warning!  This function can "fail" (return FALSE) if there aren't
    // any new WS pages to report.  It can also fail if you pass it in
    // a bogus HPROCESS.  Unfortunately, there's no way to tell the two
    // situations apart.
    GetWsChanges( g_WorkingSetHProcess, g_WorkingSetChanges,
                        sizeof(g_WorkingSetChanges) );

    return TRUE;
}

void EndWorkingSetDelta( HWND hWndOwner )
{
    if ( !g_WorkingSetHProcess )
        return;

    if ( GetWsChanges(  g_WorkingSetHProcess, g_WorkingSetChanges,
                        sizeof(g_WorkingSetChanges) ) )
    {
        // We got 1 or more WS changes.  Report it
        DialogBox(  GetModuleHandle(0),
                    MAKEINTRESOURCE(IDD_PSAPIWorkingSetDelta),
                    hWndOwner,
                    (DLGPROC)DeltaDlgProc );
    }
    else
    {
        MessageBox( hWndOwner,
                    "No working set changes, or error",
                    "Working set delta",
                    MB_OK );
    }

    CloseHandle( g_WorkingSetHProcess );
    g_WorkingSetHProcess = 0;
}
