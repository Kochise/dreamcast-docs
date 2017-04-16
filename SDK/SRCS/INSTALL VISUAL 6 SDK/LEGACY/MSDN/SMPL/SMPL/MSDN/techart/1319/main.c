/*
    main.c

    A sample Windows application

    Another fine Herman Rodent production

*/

#include "global.h"

//
// local data
//

UINT uiCount;

//
// local functions
//

static void Create(HWND hWnd, LPCREATESTRUCT lpCI);
static void Size(HWND hWnd, UINT uiX, UINT uiY);
static void Command(HWND hWnd, WPARAM wParam, LPARAM lParam);
static void MeasureItem(HWND hWnd, UINT uiCtl, LPMEASUREITEMSTRUCT lpMI);
static void DrawItem(HWND hWnd, UINT uiCtl, LPDRAWITEMSTRUCT lpDI);
static void InitMenuPopup(HMENU hMenu, UINT uiIndex, BOOL bSystem);
static void Paint(HWND hWnd, LPPAINTSTRUCT lpPS);

//
// Entry point
//

int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int cmdShow)
{
    MSG msg;

    hAppInstance = hInstance;
    szAppName = "FLICKER";

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

    if (!InitCurrentInstance(hInstance, lpszCmdLine, cmdShow)) {
        return 1;
    }

    //
    // Check for messages from Windows and process them.
    // If we have nothing else to do, maybe perform some idle function
    // 

    do {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

            //
            // got a message to process
            //

            if (msg.message == WM_QUIT) break;

            //
            // Do the accelerator thing
            //

            if (!TranslateAccelerator(hwndMain, hAccTable, &msg)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

        } else {

            //
            // perform some idle routine or just give up so Windows
            // can run till our next message.
            //

            WaitMessage();
        }
    } while (1);

    return (msg.wParam);
}
    
//
// main window message handler
//

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    char buf[16];

    switch(msg) {
    case WM_CREATE:
        Create(hWnd, (LPCREATESTRUCT)lParam);
        break;

    case WM_SIZE:
        Size(hWnd, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_COMMAND:
        Command(hWnd, wParam, lParam); 
        break;

    case WM_TIMER:

        //
        // Update the counter and set the new window text
        //

        uiCount = (uiCount + 1) % 1000;
        wsprintf(buf, "%u", uiCount);
        SetWindowText(hwndFlicker, buf);
        SetWindowText(hwndNoFlicker, buf);
        break;

    case WM_MEASUREITEM:
        MeasureItem(hWnd, (UINT)wParam, (LPMEASUREITEMSTRUCT)lParam);
        return (LRESULT) TRUE;

    case WM_DRAWITEM:
        DrawItem(hWnd, (UINT)wParam, (LPDRAWITEMSTRUCT) lParam);
        break;

    case WM_PAINT:
        BeginPaint(hWnd, &ps);
        Paint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_INITMENUPOPUP:
        InitMenuPopup((HMENU)wParam, LOWORD(lParam), (BOOL)HIWORD(lParam));
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

//
// Process WM_CREATE message
//

static void Create(HWND hWnd, LPCREATESTRUCT lpCI)
{
    //
    // Create the two child windows
    //

    hwndFlicker = CreateWindow("Flickering",
                            "",
                            WS_CHILD | WS_VISIBLE,
                            0, 0,
                            0, 0,
                            hWnd,
                            (HMENU)IDC_FLICKER,
                            hAppInstance,
                            (LPSTR)NULL
                            );

    hwndNoFlicker = CreateWindow("NoFlickering",
                            "",
                            WS_CHILD | WS_VISIBLE,
                            0, 0,
                            0, 0,
                            hWnd,
                            (HMENU)IDC_NOFLICKER,
                            hAppInstance,
                            (LPSTR)NULL
                            );

}

//
// Process WM_SIZE message
//

static void Size(HWND hWnd, UINT uiX, UINT uiY)
{
    //
    // Create a new big font the right size
    //

    if (hfntBig) {
        DeleteObject(hfntBig);
        hfntBig = NULL;
    }
    hfntBig = CreateFont(
                uiY / 2, 0,
                0, 0,
                700, // weight
                0, 0, 0,
                ANSI_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                PROOF_QUALITY,
                DEFAULT_PITCH | FF_ROMAN,
                "");
    SendMessage(hwndFlicker, WM_SETFONT, (WPARAM)hfntBig, 0);
    SetWindowPos(hwndFlicker, NULL, 0, 0, uiX, uiY / 2, SWP_NOACTIVATE);
    SendMessage(hwndNoFlicker, WM_SETFONT, (WPARAM)hfntBig, 0);
    SetWindowPos(hwndNoFlicker, NULL, 0, uiY / 2, uiX, uiY / 2, SWP_NOACTIVATE);
}

//
// Process WM_COMMAND messages
//

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
// Process WM_DRAWITEM and WM_MEASUREITEM messages
//

static void MeasureItem(HWND hWnd, UINT uiCtl, LPMEASUREITEMSTRUCT lpMI)
{
    switch (uiCtl) {

    default:

        //
        // Return the height of the system font
        //

        lpMI->itemHeight = tmSysFont.tmHeight;
        break;
    }
}

static void DrawItem(HWND hWnd, UINT uiCtl, LPDRAWITEMSTRUCT lpDI)
{
    switch (uiCtl) {

    default:
        break;
    }
}

//
// Process WM_PAINT messages
//

static void Paint(HWND hWnd, LPPAINTSTRUCT lpPS)
{


}

//
// Process WM_INITMENUPOPUP messages
//

static void InitMenuPopup(HMENU hmenuPopup, UINT uiIndex, BOOL bSystem)
{
    //
    // See if there is anything in the clipboard which
    // we should enable the Paste item for
    //

}

//
// Show a message box
//

UINT cdecl Message(UINT uiBtns, LPSTR lpFormat, ...) 
{
    char buf[256];

    wvsprintf(buf, lpFormat, (LPSTR)(&lpFormat+1));
    MessageBeep(uiBtns ? uiBtns : MB_ICONEXCLAMATION);
    return (UINT) MessageBox(hwndMain, 
                             buf, 
                             szAppName, 
                             uiBtns ? uiBtns : MB_OK|MB_ICONEXCLAMATION);
}

