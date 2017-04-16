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
    init.c

    Initialization and termination code
*/

#include "ddeexec.h"

//
// Initialise the app
//

BOOL Init(HANDLE hInstance, int cmdShow)
{
    WNDCLASS wc;

    
    //
    // define the class of window we want to register
    //

    wc.lpszClassName    = szAppName;
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = LoadIcon(hInstance,"Icon");
    wc.lpszMenuName     = "Menu";
    wc.hbrBackground    = GetStockObject(WHITE_BRUSH);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = MainWndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    
    if (!RegisterClass(&wc)) {
        return FALSE;
    }

    //
    // Create the main window
    //

    hwndMain = CreateWindow(szAppName,
                            szAppName,
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT,
                            0,
                            GetSystemMetrics(SM_CXSCREEN) / 2,
                            GetSystemMetrics(SM_CYSCREEN),
                            (HWND)NULL,
                            (HMENU)NULL,
                            hInstance,
                            (LPSTR)NULL
                            );
    
    if (!hwndMain) {
        return FALSE;
    }

    //
    // Create the status listbox
    //

    hwndStatus = CreateWindow("Listbox",
                            "",
                            WS_CHILD | WS_VISIBLE | WS_VSCROLL
                             | LBS_DISABLENOSCROLL
                             | LBS_HASSTRINGS | LBS_OWNERDRAWFIXED
                             | LBS_NOINTEGRALHEIGHT,
                            0,
                            0,
                            0,
                            0,
                            hwndMain,
                            (HMENU)IDC_STATUS,
                            hInstance,
                            (LPSTR)NULL
                            );


    ShowWindow(hwndMain, cmdShow);
    UpdateWindow(hwndMain);

    //
    // Initialize us as a DDE server
    //

    SetupDDE(hInstance);

    Status("Ready oh master.");

    return TRUE;
}
