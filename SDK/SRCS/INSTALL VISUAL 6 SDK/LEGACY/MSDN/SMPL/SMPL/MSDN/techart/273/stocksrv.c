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
    stocksrv.c

    Bogus Stock Price DDE Server

    Another fine Herman Rodent production

*/

#include "stocksrv.h"

//
// global data
//

char *szAppName = "StockSrv";       // DDE Server name
HINSTANCE hInst;                    // app instance
HWND hwndMain;                      // main window handle
UINT uiTimerId;
BOOL bPaused = FALSE;


//
// local functions
//

static void Command(HWND hWnd, WPARAM wParam, LPARAM lParam);

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
    // We only allow one instance
    //

    if (hPrevInstance) {

        BringWindowToTop(FindWindow(szAppName, NULL));
        return 1;
    }

    //
    // Do the initialization
    //

    if (!Init(hInstance, cmdShow)) {
        return 1;
    }

    //
    // Check for messages from Windows and process them.
    // If no messages, perform some idle function
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

    switch(msg) {
    case WM_CREATE:

        //
        // Start the time we will use to generate the random events
        //

        uiTimerId = SetTimer(hWnd, 1, 2500, NULL);
        break;

    case WM_SIZE:
        if (hwndStatus) {
            MoveWindow(hwndStatus, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
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

    case WM_TIMER:

        if (!bPaused) {

            UpdateDDEInfo();

        }
        break;

    case WM_PAINT:
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_INITMENUPOPUP:

        //
        // Show whatever options we have set
        //

        ModifyMenu((HMENU)wParam, 
                   IDM_PAUSE, 
                   MF_BYCOMMAND | MF_STRING,
                   IDM_PAUSE,
                   bPaused ? "Continue" : "Pause");

        CheckMenuItem((HMENU)wParam,
                      IDM_BREAD,
                      bBreadActive ? MF_CHECKED : MF_UNCHECKED);

        CheckMenuItem((HMENU)wParam,
                      IDM_MILK,
                      bMilkActive ? MF_CHECKED : MF_UNCHECKED);

        CheckMenuItem((HMENU)wParam,
                      IDM_MSFT,
                      bMSFTActive ? MF_CHECKED : MF_UNCHECKED);

        break;

    case WM_DESTROY:
        if (uiTimerId) KillTimer(hWnd ,uiTimerId);
        UninitializeDDE();
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

    case IDM_COPY:

        //
        // Copy our current info to the clipboard
        //

        CopyDDEInfo(hWnd);

        break;

    case IDM_PAUSE:
        bPaused = ! bPaused;
        break;

    case IDM_BREAD:
    case IDM_MILK:
    case IDM_MSFT:
        ChangeActiveItemStatus(wParam);
        break;

    default:
        break;
    }
}

