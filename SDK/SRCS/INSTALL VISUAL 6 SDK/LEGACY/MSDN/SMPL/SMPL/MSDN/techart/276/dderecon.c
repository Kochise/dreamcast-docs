// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.
//
/*
    dderecon.c

    DDE Client demonstration app

    Another fine Herman Rodent production

*/

#include "dderecon.h"

//
// global data
//

char *szAppName = "DDERecon";       // App name
HINSTANCE hInst;                    // app instance
HWND hwndMain;                      // main window handle
DWORD dwDDEInst = 0;                // DDE Instance value
HWND hwndLinkInfo;                  // link info window handle
PFNCALLBACK pfnDDECallback;         // pointer to our DDE Callback function
DWORD dwDDEInst;                    // our DDE instance handle
BOOL bAutoConnect = FALSE;          // don't ask user
BOOL bShowSysInfo = FALSE;          // show system topics in connect dlg

//
// local functions
//

static void Command(HWND hWnd, WPARAM wParam, LPARAM lParam);
static void DrawItem(HWND hWnd, LPDRAWITEMSTRUCT lpDrawItem);
BOOL InitFirstInstance(HANDLE hInstance);
BOOL InitCurrentInstance(HANDLE hInstance, int cmdShow);

//
// Entry point
//

int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int cmdShow)
{
    MSG msg;

    hInst = hInstance;

    //
    // We allow multiple instances
    //

    if (!hPrevInstance) {

        if (!InitFirstInstance(hInstance)) {
            return 1;
        }
    }

    //
    // Do the per instance initialization
    //

    if (!InitCurrentInstance(hInstance, cmdShow)) {
        return 1;
    }

    //
    // Check for messages from Windows and process them.
    // 

    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (msg.wParam);
}
    
//
// main window message handler
//

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    int h;

    switch(msg) {
    case WM_CREATE:
        break;

    case WM_SIZE:

        if (hwndLinkInfo) {
            h = GetSystemMetrics(SM_CYMENU);
            MoveWindow(hwndLinkInfo, 0, 0, LOWORD(lParam), h, TRUE);
        } else {
            h = 0;
        }

        if (hwndStatus) {
            MoveWindow(hwndStatus, 0, h, LOWORD(lParam), HIWORD(lParam)-h, TRUE);
        }
        break;

    case WM_COMMAND:
        Command(hWnd, wParam, lParam); 
        break;

    case WM_MEASUREITEM:
        MeasureStatusItem(hWnd, (LPMEASUREITEMSTRUCT)lParam);
        return (LRESULT) TRUE;

    case WM_DRAWITEM:
        DrawStatusItem(hWnd, (LPDRAWITEMSTRUCT) lParam);
        break;

    case WM_PAINT:
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_INITMENUPOPUP:

        //
        // See if we have a current conversation and if so
        // enable the delete link item, otherwise disable it.
        //

        EnableMenuItem((HMENU)wParam,
                       IDM_DISCONNECT,
                       hconvCurrent ? MF_BYCOMMAND | MF_ENABLED
                                    : MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

        //
        // Show what options are currently selected
        //

        CheckMenuItem((HMENU)wParam,
                      IDM_AUTO,
                      bAutoConnect ? MF_BYCOMMAND | MF_CHECKED
                                   : MF_BYCOMMAND | MF_UNCHECKED);
        CheckMenuItem((HMENU)wParam,
                      IDM_SYSINFO,
                      bShowSysInfo ? MF_BYCOMMAND | MF_CHECKED
                                   : MF_BYCOMMAND | MF_UNCHECKED);

        break;

    case WM_DESTROY:

        Terminate();

        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
        break;
    }
    return NULL;
}

static void Command(HWND hWnd, WPARAM wParam, LPARAM lParam) 
{
    switch (wParam) {
    case IDM_EXIT:
        PostMessage(hWnd, WM_CLOSE, 0, 0l);
        break;

    case IDM_CONNECT:
        ConnectDlg(hWnd, bShowSysInfo);
        break;

    case IDM_DISCONNECT:
        if (hconvCurrent) {
            DdeDisconnect(hconvCurrent);
            hconvCurrent = NULL;
            SetWindowText(hwndLinkInfo, "(no link)");
        }
        break;

    case IDM_AUTO:
        bAutoConnect = !bAutoConnect;
        break;

    case IDM_SYSINFO:
        bShowSysInfo = !bShowSysInfo;
        break;

    default:
        break;
    }
}


//
// Show an error message box
//

void cdecl Error(LPSTR lpFormat, ...) 
{
    char buf[256];

    wvsprintf(buf, lpFormat, (LPSTR)(&lpFormat+1));
    MessageBeep(MB_ICONEXCLAMATION);
    MessageBox(hwndMain, buf, szAppName, MB_OK|MB_ICONEXCLAMATION);
}

//
// Callback function for DDE messages
// Note that this is a rather simplistic version.  We only
// ever have one conversation.
//

HDDEDATA CALLBACK DDECallback(UINT wType, 
                              UINT wFmt, 
                              HCONV hConv,
                              HSZ hsz1, 
                              HSZ hsz2, 
                              HDDEDATA hDDEData, 
                              DWORD dwData1, 
                              DWORD dwData2)
{
    BYTE FAR *pData;
    DWORD dwLength;

    switch (wType) {
    case XTYP_ADVDATA:

        //
        // Some data for us
        //

        pData = DdeAccessData(hDDEData, &dwLength);

        if (pData) {

            //
            // Just show it
            //

            Status("%s", pData);
        }

        //
        // Done with the data. We don't need to free the data handle
        //

        DdeUnaccessData(hDDEData);
        return (HDDEDATA) DDE_FACK;

    case XTYP_DISCONNECT:

        Status("Server disconnected conversation");
        SetWindowText(hwndLinkInfo, "(no link)");
        hconvCurrent = NULL;
        return (HDDEDATA) NULL;

    default:
        return NULL;
        break;
    }
}
