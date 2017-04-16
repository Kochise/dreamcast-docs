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
    ddeserv.c

    Sample DDE Server skeleton application

    Another fine Herman Rodent production

    This sample has 4 steps of implementation which follow
    the text of the "Quick and Easy DDE Server" article.

    You can enable each step by uncommenting the STEP_ defines
    below.

*/

#include "ddeserv.h"

// #define STEP_1           // Initialization and termination
// #define STEP_2           // Topic/Item pairs
// #define STEP_3           // Additional System topic items
   #define STEP_4           // Execute commands

#ifdef STEP_4
#define STEP_3
#endif
#ifdef STEP_3
#define STEP_2
#endif
#ifdef STEP_2
#define STEP_1
#endif

//
// global data
//

char *szAppName = "DdeServ";    // App name
HINSTANCE ghInstance;           // App instance
HWND ghwndMain;                 // main window handle

//
// Various defines and globals used in each step of the implementation
//

#ifdef STEP_1
#define SZ_SERVICENAME  "DdeServ"   // service name
DWORD dwDDEInst = 0;                // DDE Instance value
#endif // STEP_1

#ifdef STEP_2
#define SZ_INFO         "Info"      // topic name
#define SZ_VALUE        "Value"     // item name

int giValue;                        // 'value' item

WORD MyFormats[] = {                // Format list
    CF_TEXT,
    NULL};

HDDEDATA ValueRequest(UINT wFmt, HSZ hszTopic, HSZ hszItem);
#endif // STEP_2

#ifdef STEP_4
#define SZ_CMDTOPIC     "Actions"   // Command topic name
#endif // STEP_4

//
// Local functions
//

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL Init(HANDLE hInstance, int cmdShow);
void Command(HWND hWnd, WPARAM wParam, LPARAM lParam);

#ifdef STEP_1
void SetupDDE(HINSTANCE hInstance);
#endif // STEP_1

#ifdef STEP_2
HDDEDATA MakeCFText(UINT wFmt, LPSTR lpszStr, HSZ hszItem);
BOOL ValuePoke(UINT wFmt, HSZ hszTopic, HSZ hszItem, HDDEDATA hData);
#endif // STEP_2

#ifdef STEP_3
HDDEDATA SysHelpRequest(UINT wFmt, HSZ hszTopic, HSZ hszItem);
#endif // STEP_3

#ifdef STEP_4
BOOL FAR TextFn(PDDETOPICINFO pTopic,
				 LPSTR pszResult,
				 UINT uiResultSize,
				 UINT uiNargs,
				 LPSTR FAR *ppArgs);
#endif // STEP_4

//
// Entry point
//

int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int cmdShow)
{
    MSG msg;

    ghInstance = hInstance;

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
        break;

    case WM_COMMAND:
        Command(hWnd, wParam, lParam); 
        break;

    case WM_PAINT:
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
#ifdef STEP_1
        UninitializeDDE();
#endif // STEP_1
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
        break;
    }
    return NULL;
}

void Command(HWND hWnd, WPARAM wParam, LPARAM lParam) 
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

    ghwndMain = CreateWindow(szAppName,
                            szAppName,
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT,
                            0,
                            GetSystemMetrics(SM_CXSCREEN) / 3,
                            GetSystemMetrics(SM_CYSCREEN) / 4,
                            (HWND)NULL,
                            (HMENU)NULL,
                            hInstance,
                            (LPSTR)NULL
                            );
    
    if (!ghwndMain) {
        return FALSE;
    }

    ShowWindow(ghwndMain, cmdShow);
    UpdateWindow(ghwndMain);

#ifdef STEP_1
    //
    // Initialize us as a DDE server
    //

    SetupDDE(hInstance);
#endif // STEP_1

    return TRUE;
}

//
// Startup our DDE services
//

#ifdef STEP_1
void SetupDDE(HINSTANCE hInstance)
{
    //
    // Do the basic initialization
    //

    InitializeDDE(hInstance,
                  SZ_SERVICENAME,
                  &dwDDEInst, 
                  NULL,
                  0);

#ifdef STEP_2
    //
    // Add each topic/item pair we support
    //

    AddDDEItem(SZ_INFO, 
               SZ_VALUE,
               MyFormats,
               ValueRequest,
               ValuePoke);

#endif // STEP_2

#ifdef STEP_3
    //
    // Add each system/item pair we support
    //

    AddDDEItem(SZDDESYS_TOPIC, 
               SZDDESYS_ITEM_HELP,
               MyFormats,
               SysHelpRequest,
               NULL);
#endif // STEP_3

#ifdef STEP_4
    //
    // Add the commands for this execute set
    //

    AddDDEExecCmd(SZ_CMDTOPIC,  "Text",  TextFn,  3,  3);
#endif // STEP_4

}
#endif // STEP_1

#ifdef STEP_1
//
// Return a string in CF_TEXT format
//

HDDEDATA MakeCFText(UINT wFmt, LPSTR lpszStr, HSZ hszItem)
{
    if (wFmt != CF_TEXT) return NULL;

    return DdeCreateDataHandle(dwDDEInst,
                               lpszStr,
                               lstrlen(lpszStr)+1,
                               0,
                               hszItem,
                               CF_TEXT,
                               NULL);
}
#endif // STEP_1

#ifdef STEP_2

//
// Return the current value of the 'value' item
//

HDDEDATA ValueRequest(UINT wFmt, HSZ hszTopic, HSZ hszItem)
{
    char buf[40];

    wsprintf(buf, "%d", giValue);
    return MakeCFText(wFmt, buf, hszItem);
}

//
// Set the current value of the 'value' item
//

BOOL ValuePoke(UINT wFmt, HSZ hszTopic, HSZ hszItem, HDDEDATA hData)
{
    LPSTR p;
    char buf[40];

    //
    // Access the global DDE data object
    //

    p = DdeAccessData(hData, NULL);
    if (!p) return FALSE;

    //
    // Copy it to a local piece of memory so we can
    // use a simple C run-time fn on it
    //

    lstrcpy(buf, p);
    giValue = atoi(buf);

    //
    // Done with DDE object
    //

    DdeUnaccessData(hData);

    return TRUE;
}

#endif // STEP_2

#ifdef STEP_3
//
// Return the Help info
//

HDDEDATA SysHelpRequest(UINT wFmt, HSZ hszTopic, HSZ hszItem)
{
    static char sz[] = "A helpful message.";

    return MakeCFText(wFmt, sz, hszItem);
}
#endif // STEP_3

#ifdef STEP_4
// Text(left,top,text)
//

BOOL FAR TextFn(PDDETOPICINFO pTopic,
				 LPSTR pszResult,
				 UINT uiResultSize,
				 UINT uiNargs,
				 LPSTR FAR *ppArgs)
{
    HDC hDC;
    int x, y;
    char buf[32];

    //
    // Get the co-ordinates
    //

    _fstrncpy(buf, ppArgs[0], sizeof(buf)-1);
    x = atoi(buf);
    _fstrncpy(buf, ppArgs[1], sizeof(buf)-1);
    y = atoi(buf);

    hDC = GetDC(ghwndMain);

    TextOut(hDC, x, y, ppArgs[2], _fstrlen(ppArgs[2]));

    ReleaseDC(ghwndMain, hDC);

    return TRUE;
}
#endif // STEP_4
