/*
    init.c

    The initialization and termination routines

*/

#include "global.h"

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
    wc.hIcon            = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_APP));
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
    // define the flickering class
    //

    wc.lpszClassName    = "Flickering";
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = NULL;
    wc.lpszMenuName     = NULL;
    wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = FlickerWndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    
    if (!RegisterClass(&wc)) {
        return FALSE;
    }

    //
    // define the noflickering class
    //

    wc.lpszClassName    = "NoFlickering";
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = NULL;
    wc.lpszMenuName     = NULL;
    wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = NoFlickerWndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    
    if (!RegisterClass(&wc)) {
        return FALSE;
    }

}

//
// Init the current instance
//

BOOL InitCurrentInstance(HANDLE hInstance, LPSTR lpszCmdLine, int cmdShow)
{
    HDC hDC;

    //
    // Get any system metrics we use a lot
    //

    hDC = GetDC(NULL);  // get a DC
    GetTextMetrics(hDC, &tmSysFont);
    ReleaseDC(NULL, hDC);

    //
    // Create any GDI objects we use a lot
    //





    //
    // Create the main window
    //

    hwndMain = CreateWindow(szAppName,
                            szAppName,
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT,
                            0,
                            GetSystemMetrics(SM_CXSCREEN) / 2,
                            GetSystemMetrics(SM_CYSCREEN) / 2,
                            (HWND)NULL,
                            (HMENU)NULL,
                            hInstance,
                            (LPSTR)NULL
                            );
    
    if (!hwndMain) {
        return FALSE;
    }

    ShowWindow(hwndMain, cmdShow);
    UpdateWindow(hwndMain);

    //
    // Load the accelerator table
    //

    hAccTable = LoadAccelerators(hInstance, "AccTable");
    if (!hAccTable) {
        return FALSE;
    }

    //
    // Start the update timer
    //

    uiTimer = SetTimer(hwndMain, 1, 100, NULL);

    return TRUE;
}

//
// Close down and tidy up
//

void Terminate()
{

    //
    // Nuke the timer
    //

    if (uiTimer) KillTimer(hwndMain, uiTimer);



    //
    // Delete any GDI objects
    //

    if (hfntBig) DeleteObject(hfntBig);


}
