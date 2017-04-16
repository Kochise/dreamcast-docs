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

    The initialization and termination routines

*/

#include "dderecon.h"

//
// Initialise the first instance
//

BOOL InitFirstInstance(HANDLE hInstance)
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
    
    return RegisterClass(&wc);
}

//
// Init the current instance
//

BOOL InitCurrentInstance(HANDLE hInstance, int cmdShow)
{
    UINT ui;
    int i;
    char buf[256];

    //
    // Create the main window
    //

    hwndMain = CreateWindow(szAppName,
                            szAppName,
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT,
                            0,
                            GetSystemMetrics(SM_CXSCREEN) / 2,
                            GetSystemMetrics(SM_CYSCREEN) / 4,
                            (HWND)NULL,
                            (HMENU)NULL,
                            hInst,
                            (LPSTR)NULL
                            );
    
    if (!hwndMain) {
        return FALSE;
    }

    //
    // Create the link info window
    //

    hwndLinkInfo = CreateWindow("Static",
                            "",
                            WS_CHILD | WS_VISIBLE | WS_BORDER
                             | SS_LEFTNOWORDWRAP,
                            0,
                            0,
                            0,
                            0,
                            hwndMain,
                            (HMENU)IDC_LINKINFO,
                            hInst,
                            (LPSTR)NULL
                            );

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
                            hInst,
                            (LPSTR)NULL
                            );


    ShowWindow(hwndMain, cmdShow);
    UpdateWindow(hwndMain);

    //
    // Initialize the DDE services
    //

    pfnDDECallback = (PFNCALLBACK) MakeProcInstance((FARPROC) DDECallback, 
                                                    hInstance);

    ui = DdeInitialize(&dwDDEInst,
                       pfnDDECallback,
                       CBF_FAIL_ALLSVRXACTIONS,
                       0l);

    //
    // Nothing fatal from now on
    //

    if (ui != DMLERR_NO_ERROR) {
        Error("Failed to initialize as DDE client. Error %u", ui);
    }

    //
    // Get the saved state of our options
    //

    bAutoConnect = (BOOL) GetProfileInt(szAppName, "AutoConnect", FALSE);
    bShowSysInfo = (BOOL) GetProfileInt(szAppName, "ShowSysInfo", FALSE);

    //
    // See if we have a remote link to re-establish
    //

    GetProfileString(szAppName, "Service", "", szCurrentService, DDENAMESIZE);
    GetProfileString(szAppName, "Topic", "", szCurrentTopic, DDENAMESIZE);
    GetProfileString(szAppName, "Item", "", szCurrentItem, DDENAMESIZE);

    if (lstrlen(szCurrentService) 
    && lstrlen(szCurrentTopic) 
    && lstrlen(szCurrentItem)) {

        //
        // Only ask if not in auto-connect mode
        //

        if (!bAutoConnect) {

            //
            // Ask the user if they want the link brought back up
            //

            wsprintf(buf, 
                     "Re-establish remote link with '%s' on '%s %s'?", 
                     (LPSTR) szCurrentService,
                     (LPSTR) szCurrentTopic,
                     (LPSTR) szCurrentItem);
            i = MessageBox(hwndMain,
                           buf,
                           szAppName,
                           MB_ICONQUESTION | MB_YESNO);

        }

        if (bAutoConnect || (!bAutoConnect && (i == IDYES))) {

            //
            // Try to re-establish the link
            //

            EstablishLink(szCurrentService, szCurrentTopic, szCurrentItem);

        }
    }

    return TRUE;
}

//
// Close down and tidy up
//

void Terminate()
{
    char buf[10];

    //
    // Close down the DDE services
    //

    if (dwDDEInst) {

        //
        // Terminate any current conversation
        //

        if (hconvCurrent) {

            DdeDisconnect(hconvCurrent);

            //
            // Save the conversation parameters so we can reconnect
            //

            WriteProfileString(szAppName, "Service", szCurrentService);
            WriteProfileString(szAppName, "Topic", szCurrentTopic);
            WriteProfileString(szAppName, "Item", szCurrentItem);

        } else {

            WriteProfileString(szAppName, "Service", "");
            WriteProfileString(szAppName, "Topic", "");
            WriteProfileString(szAppName, "Item", "");
        }

        //
        // say we're done with DDEML
        //

        DdeUninitialize(dwDDEInst);

        FreeProcInstance((FARPROC)pfnDDECallback);

        dwDDEInst = 0L;
    }

    //
    // Save our options
    //

    wsprintf(buf, "%u", bAutoConnect);
    WriteProfileString(szAppName, "AutoConnect", buf);
    wsprintf(buf, "%u", bShowSysInfo);
    WriteProfileString(szAppName, "ShowSysInfo", buf);
        
}
