//=======================================
// PSAPI Working Set Demo - Matt Pietrek 1996
// Microsoft Systems Journal, November 1996
// FILE: "PSAPIWorkingSetDemo.CPP"
//=======================================
#include <windows.h>
#include <stdlib.h>
#pragma hdrstop
#include "psapi.h"
#include "psapiworkingsetdemo.h"
#include "psapiworkingsetdelta.h"
#include "PSAPIhelper.h"

// Helper function prototypes
void Handle_WM_COMMAND(HWND hDlg, WPARAM wParam, LPARAM lParam);
void Handle_WM_INITDIALOG(HWND hDlg);
void Handle_WM_CLOSE( HWND hDlg );
DWORD GetDlgSelectedItemData( HWND hDlg, int ctlID );
BOOL CALLBACK PSAPIWorkingSetDemDlgProc( HWND, UINT, WPARAM, LPARAM );
void GetSetPositionInfoFromRegistry( BOOL fSave, POINT *lppt );

DWORD g_PageSize = 0x1000;  // We can adjust later for Alpha

// ======================= String literals ===============================
char gszRegistryKey[] = "Software\\WheatyProductions\\PSAPIWorkingSetDemo";

char g_AboutMsgTxt[] =
  "PSAPIWorkingSetDemo shows information obtained about process working sets "
  "obtained with PSAPI.DLL, from the Win32 SDK";

char g_AboutTitleTxt[] = "PSAPIWorkingSetDemo - Matt Pietrek 1996, for MSJ";

// ======================= Start of code ===============================

void AddProcessToList( HWND hWnd, DWORD processID )
{
    //
    // Adds the process name and ID to the top list, then calls
    // AddProcessDetails to fill in the details about the process
    //

    char szProcessName[MAX_PATH] = "unknown";
    char szItemString[MAX_PATH+64];
    
    HANDLE hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION |
                                    PROCESS_VM_READ,
                                    FALSE, processID );

    if ( hProcess )     // Get the name of the executable module
    {
        HMODULE hMod;
        DWORD cbNeeded;
    
        // Get just the first module in the process.  This appears to
        // always be the executable file.    
        if ( EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName,
                                sizeof(szProcessName) );
        }
    }

    // Format the description string for this process
    wsprintf( szItemString, "%s (ID:%u)", szProcessName, processID );

    // Add the string to the process listbox, and associate the PID with it
    long lbIndex = SendMessage( hWnd, LB_ADDSTRING, 0, (LPARAM) szItemString );
                   SendMessage( hWnd, LB_SETITEMDATA, lbIndex, processID );
                    
    if ( hProcess )
        CloseHandle( hProcess );
}

void UpdateProcessList( HWND hDlg )
{
    //
    // Clears the listview, obtains a list of process IDs, and shows them
    //
    
    // Get the process list HWND, then clear it
    HWND hWnd = GetDlgItem( hDlg, IDC_LB_PROCESS_LIST );
    SendMessage( hWnd, LB_RESETCONTENT, 0, 0 );

    // Get the list of process IDs
    DWORD aProcesses[1024], cbNeeded;
    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
        return;
    
    // Calculate how many process IDs were returned
    DWORD cProcesses = cbNeeded / sizeof(DWORD);

    // Spit out the information for each ID
    for ( unsigned i = 0; i < cProcesses; i++ )
        AddProcessToList( hWnd, aProcesses[i] );
}

int CompareDWORDs( const void * a, const void * b )
{
    if ( *(PDWORD)a == *(PDWORD)b )
        return 0;

    return *(PDWORD)a > *(PDWORD)b ? 1 : -1;
}

// Declare a big array of DWORDs to hold the working set information returned
// by QueryWorkingSet().  Since this memory isn't initialized, it doesn't
// affect the size of our executable.
DWORD g_WorkingSetPages[ 1024 * 128 ];

void AddWorkingSetInfo( HWND hDlg, DWORD processID )
{
    HANDLE hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION |
                                    PROCESS_VM_READ,
                                    FALSE, processID );

    if ( !hProcess )
        return;

    HWND hWndLb = GetDlgItem( hDlg, IDC_LB_WORKING_SET_DETAILS );

    __try
    {
        SendMessage( hWndLb, WM_SETREDRAW, FALSE, 0 );  // Disable LB updating

        char szBuffer[MAX_PATH * 4];

        if ( !QueryWorkingSet(  hProcess, g_WorkingSetPages,
                                sizeof(g_WorkingSetPages) ) )
            __leave;

        DWORD cPages = g_WorkingSetPages[0];    // First DWORD is page count
        DWORD cPrivatePages = 0;
        DWORD cSharedPages = 0;
        DWORD cPageTablePages = 0;
                
        qsort( &g_WorkingSetPages[1], cPages, sizeof(DWORD), CompareDWORDs );

        for ( DWORD i = 1; i <= cPages; i++ )
        {
            DWORD pageAddr = g_WorkingSetPages[i] & 0xFFFFF000;
            DWORD pageFlags = g_WorkingSetPages[i] & 0x00000FFF;
            DWORD thisPageAddr, nextPageAddr, nextPageFlags;
            DWORD cPagesThisRange = 0;

            // Loop through all subseqent pages that are contiguous in
            // memory and have the same attributes
            while ( i <= cPages )
            {
                cPagesThisRange++;

                if ( i == cPages )  // Break out if its the last page
                    break;

                thisPageAddr = g_WorkingSetPages[i] & 0xFFFFF000;
                nextPageAddr = g_WorkingSetPages[i+1] & 0xFFFFF000;
                nextPageFlags = g_WorkingSetPages[i+1] & 0x00000FFF;

                if ( (nextPageAddr == (thisPageAddr + g_PageSize)) &&
                     (nextPageFlags == pageFlags) )
                {
                     i++;       // Keep going
                }
                else            // Non-contiguous page or different flags
                    break;
            }

            // Is it a page from outside of the "page table" region???
            if ( (pageAddr < 0xC0000000) || (pageAddr > 0xE0000000) )
            {
                if ( pageFlags & 0x100 )            // 0x100 == shared
                    cSharedPages+= cPagesThisRange;
                else                                // 0x000 == private
                    cPrivatePages+= cPagesThisRange;
            }
            else    // It's a page from the page table region
                cPageTablePages += cPagesThisRange;

            PSTR pszBuffCurr = szBuffer;    // ptr to working output string

            pszBuffCurr += wsprintf(pszBuffCurr, "%08X  %4uK",
                                    pageAddr, cPagesThisRange * 4 );

            // 0x100 == not private (i.e., shared)
            pszBuffCurr += wsprintf( pszBuffCurr,
                                    pageFlags & 0x100 ? "  S":  "  P" );

            // 0x01 == ReadOnly
            // 0x04 == Writeable
            // 0x05 == Copy On Write (special case)
            if ( 0x5 == (pageFlags & 0x5) )
                pszBuffCurr += wsprintf( pszBuffCurr, " CW" );
            else if ( pageFlags & 0x1 )
                pszBuffCurr += wsprintf( pszBuffCurr, " RO" );
            else if ( pageFlags & 0x4 )
                pszBuffCurr += wsprintf( pszBuffCurr, " RW" );
            else
                pszBuffCurr += wsprintf( pszBuffCurr, " ??" );

            // 0x02 == Executable
            pszBuffCurr += wsprintf( pszBuffCurr,
                                     pageFlags & 0x2 ? " E  " : "    " );

            char    szMod[MAX_PATH];
            char    szSection[IMAGE_SIZEOF_SHORT_NAME+1];
            DWORD   uSection;
            BOOL    fFoundInfo;

            // Get information (such as the module and section name) for the
            // page that was faulted in
            fFoundInfo = GetModuleNameAndSectionInfo(
                            hProcess,
                            (PVOID)pageAddr,
                            szMod, sizeof(szMod),
                            szSection, sizeof(szSection),
                            &uSection );

            if ( fFoundInfo )   // We found Win32 module info!
            {
                if ( uSection ) // We even know which section!
                {
                    pszBuffCurr += wsprintf(pszBuffCurr,"%s!%s(%u)",
                                            szMod,szSection,uSection);
                }
                else            // We have a module, but no section
                {
                    pszBuffCurr += wsprintf( pszBuffCurr, "%s", szMod );
                }
            }
            else
            {
                // Perhaps it's a memory mapped file!
                char szOwner[MAX_PATH];
                if ( GetMappedFileNameA( hProcess, (PVOID)pageAddr,
                                        szOwner, sizeof(szOwner) )  )
                    pszBuffCurr += wsprintf( pszBuffCurr, "%s", szOwner );
            }

            // Add the output string to the listbox (finally!)
            SendMessage( hWndLb, LB_ADDSTRING, 0, (LPARAM) szBuffer );
        }

        //
        // Fix this!  page size should be determined dynamically!
        //
        wsprintf( szBuffer, "Total: %uK", cPages * 4 );
        SetDlgItemText( hDlg, IDC_TOTAL_MEMORY, szBuffer );
        wsprintf( szBuffer, "Private: %uK", cPrivatePages * 4 );
        SetDlgItemText( hDlg, IDC_PRIVATE_MEMORY, szBuffer );
        wsprintf( szBuffer, "Shared: %uK", cSharedPages * 4 );
        SetDlgItemText( hDlg, IDC_SHARED_MEMORY, szBuffer );
        wsprintf( szBuffer, "Page Tables: %uK", cPageTablePages * 4 );
        SetDlgItemText( hDlg, IDC_PAGE_TABLES, szBuffer );
    }
    __finally
    {
        SendMessage( hWndLb, WM_SETREDRAW, TRUE, 0 );   // Enable LB updating
        CloseHandle( hProcess );
    }
}

void UpdateWorkingSetInfo( HWND hDlg, DWORD processID )
{
    // Clear out the text summary fields
    SetDlgItemText( hDlg, IDC_TOTAL_MEMORY, "" );
    SetDlgItemText( hDlg, IDC_PRIVATE_MEMORY, "" );
    SetDlgItemText( hDlg, IDC_SHARED_MEMORY, "" );
    SetDlgItemText( hDlg, IDC_PAGE_TABLES, "" );

    // Clear out the listbox     
    SendDlgItemMessage( hDlg, IDC_LB_WORKING_SET_DETAILS, LB_RESETCONTENT, 0, 0 );

    AddWorkingSetInfo( hDlg, processID );
}

void EmptyProcessWorkingSet( HWND hDlg, DWORD processID )
{
    HANDLE hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION |
                                    PROCESS_VM_READ | PROCESS_SET_QUOTA,
                                    FALSE, processID );

    if ( !hProcess )
    {
        MessageBox( hDlg, "Unable to open this process", 0, MB_OK );
        return;
    }

    SetProcessWorkingSetSize( hProcess, 0xFFFFFFFF, 0xFFFFFFFF );
      
    UpdateWorkingSetInfo( hDlg, processID );    
}

void RefreshViews( HWND hDlg )
{
    UpdateProcessList( hDlg );  // Should be self-explanatory!

    // Clear the working set LB HWND
    SendDlgItemMessage(hDlg, IDC_LB_WORKING_SET_DETAILS, LB_RESETCONTENT,0,0);
}

// ======================= Start of UI code ===============================

int PASCAL WinMain( HANDLE hInstance, HANDLE hPrevInstance,
                    PSTR lpszCmdLine, int nCmdShow )
{
    // Bring up the user interface (A dialog box?  What a surprise!)
    DialogBox(  hInstance, MAKEINTRESOURCE(IDD_PSAPIWorkingSetDemo),
                0, (DLGPROC)PSAPIWorkingSetDemDlgProc );
    return 0;
}

BOOL CALLBACK PSAPIWorkingSetDemDlgProc(HWND hDlg, UINT msg,
                                        WPARAM wParam, LPARAM lParam)
{
    //
    // The dialog procedure for the main window
    //
    switch ( msg )
    {
        case WM_COMMAND:
            Handle_WM_COMMAND( hDlg, wParam, lParam ); return TRUE;
        case WM_INITDIALOG:
            Handle_WM_INITDIALOG( hDlg ); return TRUE;
        case WM_CLOSE:
            Handle_WM_CLOSE( hDlg ); break;
        // let everything else fall through
    }
    return FALSE;
}

void Handle_WM_COMMAND( HWND hDlg, WPARAM wParam, LPARAM lParam )
{
    HWND hwndCtl = (HWND)lParam;

    switch ( LOWORD(wParam) )
    {
        case IDC_BUTTON_REFRESH_PROCESS_LIST:
            RefreshViews( hDlg );
            break;

        case IDC_LB_PROCESS_LIST:
            if ( LBN_SELCHANGE == HIWORD(wParam) )
            {
                // Was an item selected in the process list?  If so, get the
                // associated itemdata (really a PID), and refresh the working
                // set information for the process
                DWORD pid = GetDlgSelectedItemData(hDlg, IDC_LB_PROCESS_LIST);          
                UpdateWorkingSetInfo( hDlg, pid );
            }
            break;

        case IDC_BUTTON_EMPTY_WORKING_SET:
            {
                DWORD pid = GetDlgSelectedItemData(hDlg, IDC_LB_PROCESS_LIST);
                EmptyProcessWorkingSet( hDlg, pid );
            }
            break;

        case IDC_BUTTON_START_DELTA:
            {
                DWORD pid = GetDlgSelectedItemData(hDlg, IDC_LB_PROCESS_LIST);
                if ( StartWorkingSetDelta( pid ) )
                {
                    // Disable the "Start Delta" button and enable the
                    // "end delta" button
                    EnableWindow( GetDlgItem(hDlg, IDC_BUTTON_START_DELTA),
                                    FALSE );
                    EnableWindow(   GetDlgItem(hDlg, IDC_BUTTON_END_DELTA),
                                    TRUE );
                    SetFocus( GetDlgItem(hDlg,IDC_BUTTON_END_DELTA) ); 
                }
                else
                    MessageBox(hDlg, "Unable to monitor working set", 0,MB_OK);
            }
            break;

        case IDC_BUTTON_END_DELTA:
            EndWorkingSetDelta( hDlg );

            // Enable the "Start Delta" button and disable the "end delta"
            EnableWindow( GetDlgItem(hDlg, IDC_BUTTON_END_DELTA), FALSE );
            EnableWindow( GetDlgItem(hDlg, IDC_BUTTON_START_DELTA), TRUE );
            SetFocus( GetDlgItem(hDlg, IDC_BUTTON_START_DELTA) );
            break;

        case IDC_BUTTON_ABOUT:
            MessageBox( hDlg, g_AboutMsgTxt, g_AboutTitleTxt, MB_OK );
            break;
    }
}

void Handle_WM_INITDIALOG(HWND hDlg)
{
    // Get the window coordinates where the program was last running,
    // and move the window to that spot.
    POINT pt;
    GetSetPositionInfoFromRegistry( FALSE, &pt );
    SetWindowPos(hDlg, 0, pt.x, pt.y, 0, 0,
                 SWP_NOSIZE | SWP_NOREDRAW | SWP_NOZORDER | SWP_NOACTIVATE);

    // Disable the "End Delta" button
    EnableWindow( GetDlgItem( hDlg, IDC_BUTTON_END_DELTA ), FALSE );

    RefreshViews( hDlg );   // Fill treeviews with initial values
}

void Handle_WM_CLOSE( HWND hDlg )
{
    // Save off the window's X,Y coordinates for next time
    RECT rect;
    if ( !IsIconic(hDlg) && GetWindowRect(hDlg, &rect) )
        GetSetPositionInfoFromRegistry( TRUE, (LPPOINT)&rect );
    EndDialog( hDlg, 0 );
}

// Returns the DWORD of "item data" associated with the currently selected
// item in the listbox specified by the ctlID param
DWORD GetDlgSelectedItemData( HWND hDlg, int ctlID )
{
    LONG lbIndex = SendDlgItemMessage( hDlg, ctlID, LB_GETCURSEL, 0, 0 );
    return SendDlgItemMessage(hDlg, ctlID, LB_GETITEMDATA, lbIndex, 0 );
}

void GetSetPositionInfoFromRegistry( BOOL fSave, POINT *lppt )
{
    //
    // Function that saves or restores the coordinates of a dialog box
    // in the system registry.  Handles the case where there's nothing there.
    //
    HKEY hKey;
    DWORD dataSize, err, disposition;
    char szKeyName[] = "DlgCoordinates";
    
    if ( !fSave )               // In case the key's not there yet, we'll
        lppt->x = lppt->y = 0;  // return 0,0 for the coordinates

    // Open the registry key (or create it if the first time being used)
    err = RegCreateKeyEx( HKEY_CURRENT_USER, gszRegistryKey, 0, 0,
                         REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                         0, &hKey, &disposition );
    if ( ERROR_SUCCESS != err )
        return;

    if ( fSave )            // Save out coordinates
    {
        RegSetValueEx(hKey,szKeyName, 0, REG_BINARY,(PBYTE)lppt,sizeof(*lppt));
    }
    else                    // read in coordinates
    {
        dataSize = sizeof(*lppt);
        RegQueryValueEx( hKey, szKeyName, 0, 0, (PBYTE)lppt, &dataSize );
    }

    RegCloseKey( hKey );
}
