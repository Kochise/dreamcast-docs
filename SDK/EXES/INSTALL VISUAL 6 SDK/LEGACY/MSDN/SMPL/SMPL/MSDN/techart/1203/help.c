/*
    help.c

    Support for the HELP menu items

*/

#include "global.h"
#include <stdlib.h>

void Help(HWND hWnd, WORD wParam)
{
    char szHelpFileName[_MAX_PATH];

    lstrcpy(szHelpFileName, szAppName);
    lstrcat(szHelpFileName, ".HLP");

    switch (wParam) {
    case IDM_HELPCONTENTS:
        WinHelp(hWnd, szHelpFileName, HELP_CONTENTS, (DWORD)0);
        break;

    default:
        break;

    }
}

//
// About box dialog procedure
//

int CALLBACK AboutDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_INITDIALOG:
        break;

    case WM_COMMAND:
        switch (wParam) {
        case IDOK:
            EndDialog(hDlg, TRUE);
            break;
        default:
            break;
        }
        break;

    default:
        return FALSE; // say we didn't handle it
        break;
    }

    return TRUE; // say we handled it
}

//
// Show the about box
//

void About(HWND hWnd)
{
    FARPROC fpDlg;

    fpDlg = MakeProcInstance((FARPROC)AboutDlgProc, hAppInstance);
    DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_ABOUT), hWnd, (DLGPROC)fpDlg);
    FreeProcInstance(fpDlg);
}
