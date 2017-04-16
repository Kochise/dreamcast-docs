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
    ddeexec.c

    Bogus DDE Execute demonstration server

    Another fine Herman Rodent production

*/

#include "ddeexec.h"

//
// global data
//

char *szAppName = "DdeExec";        // DDE Server name
HINSTANCE hInst;                    // app instance
HWND hwndMain;                      // main window handle

//
// local functions
//

static void Command(HWND hWnd, WPARAM wParam, LPARAM lParam);
static void Paint(HWND hWnd, HDC hDC);

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
    RECT rc;

    switch(msg) {
    case WM_CREATE:
        break;

    case WM_SIZE:

        //
        // update the rectangle info we keep for painting
        //

        rc.left = rc.top = 0;
        rc.right = LOWORD(lParam) - 1;
        rc.bottom = HIWORD(lParam) * 2 / 3 - 1;

        if (hwndStatus) {

            //
            // The status window occupies the lower half of the
            // main window
            //

            MoveWindow(hwndStatus, 
                       0, rc.bottom + 1,
                       LOWORD(lParam), HIWORD(lParam)/3,
                       TRUE);
            Status("Draw rect: %d,%d,%d,%d", rc.left, rc.top, rc.right, rc.bottom);


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
        Paint(hWnd, ps.hdc);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
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

    default:
        break;
    }
}

//
// Paint the main window 
//

static void Paint(HWND hWnd, HDC hDC)
{
    RECT rc;

    //
    // Just draw a line to separate the status window
    //

    GetClientRect(hWnd, &rc);
    MoveTo(hDC, rc.left, rc.bottom*2/3-1);
    LineTo(hDC, rc.right, rc.bottom*2/3-1);

}
