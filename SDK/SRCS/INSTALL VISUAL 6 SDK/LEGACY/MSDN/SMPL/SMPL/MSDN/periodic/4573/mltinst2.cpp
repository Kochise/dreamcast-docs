//==================================
// MULTINST.C - Matt Pietrek 1993
//==================================
#include <windows.h>
#include <string.h>
#include <ctype.h>
#pragma hdrstop
#include "prochook.h"
#include "mltinst2.h"

#define MAX_PATH 260    // This really should be in WINDOWS.H, but is
                        // inexplicably hard-coded into the data structures

//########################################################################
// Prototypes for functions
//########################################################################                          

BOOL CALLBACK _export MultInstDlgProc(HWND hWndDlg, UINT msg,
                                      WPARAM wParam, LPARAM lParam);
int MungeModuleHeader( HINSTANCE hInstance, BOOL fMunge );
BOOL SetupMultInst95( HINSTANCE hInstance );
BOOL ShutdownMultInst95(void);

HINSTANCE HInstance;
int far MyUselessVariable;  // Far data induces multiple data segments

//########################################################################
// Start of user interface code
//########################################################################                          

int PASCAL WinMain( HANDLE hInstance, HANDLE hPrevInstance,
                    LPSTR lpszCmdLine, int nCmdShow )
{
    HInstance = hInstance;
    MyUselessVariable = 0;  // Reference the far variable (just in case)

    FARPROC mpiDialog = MakeProcInstance((FARPROC)MultInstDlgProc, hInstance);
    DialogBox( hInstance, "MultInstDlg", 0, (DLGPROC)mpiDialog );

    return 0;
}

//
// Dialog procedure for the main dialog
//
BOOL CALLBACK __export MultInstDlgProc(HWND hWndDlg, UINT msg,
                                      WPARAM wParam, LPARAM lParam)
{
    char buffer[128];
    
    if ( msg == WM_INITDIALOG )
    {
        wsprintf(buffer, "My hInstance is %04X", HInstance);
        SetDlgItemText(hWndDlg, IDC_TEXT_HINSTANCE, buffer);
    }
    else if ( msg == WM_COMMAND )
    {
        if ( wParam == IDC_BUTTON_INVOKE_ANOTHER )
        {   // Try to invoke another instance of the program
            GetModuleFileName(HInstance, buffer, sizeof(buffer));
            if ( WinExec( buffer, SW_NORMAL ) < 32 )
                MessageBox(hWndDlg, "Unable to exec program", 0, MB_OK);
        }
        else if ( wParam == IDC_BUTTON_ALLOW_ANOTHER )
        {
            SetupMultInst95( HInstance );
            EnableWindow( LOWORD(lParam), FALSE );
        }
    }
    else if ( msg == WM_CLOSE )
    {
        ShutdownMultInst95();
        EndDialog(hWndDlg, 0); return FALSE;
    }
    
    return FALSE;
}

//########################################################################
// Code that does the real work
//########################################################################                          

//
// Central function that modifies a module table to trick the loader
// into letting a second instance of a multiple data segment program run.
//
int MungeModuleHeader( HINSTANCE hInstance, BOOL fMunge )
{ 
    HMODULE hModuleSel;
    LPSTR lpszModName, lpszFileName;
    BYTE cbModuleName;
    static BOOL fResidentNamesMunged = FALSE;
    
    hModuleSel = SELECTOROF(    // Convert the HINSTANCE to an HMODULE
        GlobalLock(GetModuleHandle((LPSTR)MAKELP(0,hInstance))));

    if ( hModuleSel == 0 )      // Make sure we succeeded.
        return 0;

    //
    // First, we'll take care of the resident names table
    //
    if ( FALSE == fResidentNamesMunged )
    {
        // Make pointers to the module name in the resident names table
        lpszModName = (LPSTR)MAKELP(hModuleSel,
                                    *(WORD FAR *)MAKELP(hModuleSel, 0x26) );

        // Get the module name length, and advance to the actual string
        cbModuleName = *lpszModName++;   // First byte is a length byte
    
        // Convert the first uppercase letter of the modulename to lowercase
        while ( cbModuleName )
        {
            if ( isupper(*lpszModName) )
            {
                *lpszModName = tolower(*lpszModName); break;
            }
            cbModuleName--; lpszModName++;
        }

        if ( cbModuleName == 0 )    // Make sure we succeeded
            return 0;

        // Remember that we've done this, so that we don't bother doing
        // it in the future.
        fResidentNamesMunged = TRUE;
    }

    //
    // Now, we'll turn our attention to the module file name in the OFSTRUCT
    //
    lpszFileName = (LPSTR)MAKELP(hModuleSel,
                                 *(WORD FAR *)MAKELP(hModuleSel, 0x0A));

    // Position to the end of the filename. First byte is a length byte
    lpszFileName += *lpszFileName - 1;

    // If we're munging, added 0x30 to the last character value, otherwise
    // subtract 0x30.  0x30 is chosen completely at random.
    if ( fMunge )
        *lpszFileName += 0x30;
    else
        *lpszFileName -= 0x30;
    
    return 1;
}

//########################################################################
// This section watches calls to LoadModule and munges the EXE's module
// database as needed.
//########################################################################

NPHOOKCHILD npHookLoadModule = 0;
char szOurFileName[MAX_PATH];

HINSTANCE
WINAPI
__export MultInst95LoadModule( LPCSTR lpszModuleName,
                               LPVOID lpvParameterBlock )
{
    HINSTANCE retValue;

    // Uppercase the name of the module name that was passed to LoadModule
    char szNewFileName[MAX_PATH];
    lstrcpy( szNewFileName, lpszModuleName );
    strupr( szNewFileName );

    // Compare the incoming filename to our EXE's module name.  If they
    // don't match, we don't need to bother munging the module database
    BOOL fSecondInstance = strstr(szOurFileName, szNewFileName) ? TRUE:FALSE;

    // Unhook our LoadModule hook so that we can call the real LoadModule
    ProcUnhook( npHookLoadModule );

    // Munge module database if needed
    if ( fSecondInstance )
        MungeModuleHeader( HInstance, TRUE );

    // Call the original LoadModule code
    retValue = LoadModule( lpszModuleName, lpvParameterBlock );

    // Unmunge module database if needed
    if ( fSecondInstance )
        MungeModuleHeader( HInstance, FALSE );

    // Reinstall our LoadModule hook so that we see future loads
    ProcHook( npHookLoadModule );
    
    return retValue;
}

BOOL SetupMultInst95( HINSTANCE hInstance )
{
    if ( npHookLoadModule )
        return TRUE;

    // Get the EXE's filename into a global string variable and uppercase it
    GetModuleFileName( hInstance, szOurFileName, sizeof(szOurFileName) );
    strupr( szOurFileName );

    // Create a MakeProcInstance thunk so that our callback function
    // will always be using the correct DS selector
    FARPROC lpfnMPI
        = MakeProcInstance( (FARPROC)MultInst95LoadModule, hInstance );

    if ( !lpfnMPI )
        return FALSE;

    // Call PROCHOOK.DLL to hook calls to LoadModule
    npHookLoadModule = SetProcAddress(  (FARPROC)LoadModule,
                                        lpfnMPI, FALSE );
    
    return (BOOL)npHookLoadModule;
}

BOOL ShutdownMultInst95(void)
{
    if ( !npHookLoadModule )
        return FALSE;

    SetProcRelease( npHookLoadModule );
    npHookLoadModule = 0;
    
    return TRUE;
}

