/*
    init.c

    The initialization and termination routines

*/

#include "global.h"

//
// local data
//

static BOOL bOleInit = FALSE;



//
// Initialise the first instance
//

BOOL InitFirstInstance(HANDLE hInstance)
{
    WNDCLASS wc;

    
    //
    // define the class of window we want to register
    //

    wc.lpszClassName    = gszAppName;
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

#ifdef DEBUG

    wc.lpszClassName    = "Debug";
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = LoadIcon(hInstance,"Icon");
    wc.lpszMenuName     = NULL;
    wc.hbrBackground    = GetStockObject(WHITE_BRUSH);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = DebugWndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    
    return RegisterClass(&wc);

#endif // DEBUG

}

//
// Init the current instance
//

BOOL InitCurrentInstance(HANDLE hInstance, LPSTR lpszCmdLine, int cmdShow)
{
    HDC hDC;
    DWORD dwOleVer;

    //
    // Get any system metrics we use a lot
    //

    hDC = GetDC(NULL);  // get a DC
    GetTextMetrics(hDC, &gtmSysFont);
    ReleaseDC(NULL, hDC);

    //
    // Create any GDI objects we use a lot
    //





    //
    // Create the main window
    //

    ghwndMain = CreateWindow(gszAppName,
                            gszAppName,
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
    
    if (!ghwndMain) {
        return FALSE;
    }

    ShowWindow(ghwndMain, cmdShow);
    UpdateWindow(ghwndMain);

    //
    // Load the accelerator table
    //

    ghAccTable = LoadAccelerators(hInstance, "AccTable");
    if (!ghAccTable) {
        return FALSE;
    }

    //
    // Register our own private clipboard formats
    //

    gcfTextBoxObject = RegisterClipboardFormat(CF_TEXTBOXOBJECT);

    //
    // Create a new (empty) document
    //

    FileNew(FILE_DONT_PROMPT_FOR_SAVE | FILE_UPDATE_CAPTION);

    //
    // Open any file given in the command line
    //

    if (lpszCmdLine && lstrlen(lpszCmdLine)) {
        dprintf2("CmdLine: %s", lpszCmdLine);
        FileOpen(lpszCmdLine);
    }

    //
    // Say we do drag and drop
    //

    DragAcceptFiles(ghwndMain, TRUE);

    //
    // Check the OLE version is ok and if it is initialize the 
    // libraries we want to use
    //

    dwOleVer = CoBuildVersion();
    dprintf3("OLE ver %u.%u", HIWORD(dwOleVer), LOWORD(dwOleVer));
    if (HIWORD(dwOleVer) < 20) {

        Message(0, "This application requires OLE Version 2.x");
        return FALSE;

    }

    if (CoInitialize(NULL) != S_OK) {

        Message(0, "Failed to initialize the OLE libraries");
        return FALSE;
    }

    bOleInit = TRUE;

#ifdef DEBUG

    //
    // Set up the debug menu state
    //

    SetDebugLevel(__iDebugLevel);   // set menu state

#endif

    dprintf2("started");

    return TRUE;
}

//
// Close down and tidy up
//

void Terminate()
{
    char buf[256];

    //
    // Say we don't drag and drop any more
    //

    DragAcceptFiles(ghwndMain, FALSE);

    //
    // Finish with any OLE libraries we used
    //

    if (bOleInit) {

        CoUninitialize();
    }

    //
    // Delete any GDI objects
    //



#ifdef DEBUG

    //
    // Save the debug level
    //

    wsprintf(buf, "%d", __iDebugLevel);
    WriteProfileString(gszAppName, "debug", buf);
    dprintf2("ended");

#endif // DEBUG
        
}
