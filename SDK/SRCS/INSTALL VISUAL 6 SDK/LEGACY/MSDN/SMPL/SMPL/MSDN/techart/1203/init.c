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
    wc.style            = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
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
                            0,
                            0,
                            GetSystemMetrics(SM_CXSCREEN),
                            GetSystemMetrics(SM_CYSCREEN) * 3 / 4,
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
    // Register our private clipboard format
    //

    uiCfSprite = RegisterClipboardFormat(SZ_SPRITE);

#ifdef DEBUG

    //
    // Show what the screen device driver supports
    //

    {

        HDC hDC;
        WORD wCaps;

        hDC = GetDC(hwndMain);
        wCaps = GetDeviceCaps(hDC, RASTERCAPS);
        if (wCaps & RC_DI_BITMAP) {
            dprintf3("Screen DC supports GetDIBits and SetDIBits");
        } else {
            dprintf3("Screen DC doesn't support GetDIBits or SetDIBits");
        }
        if (wCaps & RC_DIBTODEV) {
            dprintf3("Screen DC supports SetDIBitsToDevice");
        } else {
            dprintf3("Screen DC doesn't support SetDIBitsToDevice");
        }
        if (wCaps & RC_STRETCHDIB) {
            dprintf3("Screen DC supports StretchDIBits");
        } else {
            dprintf3("Screen DC doesn't support StretchDIBits");
        }
        wCaps = GetDeviceCaps(hDC, CAPS1);
        if (wCaps & C1_TRANSPARENT) {
            dprintf3("Screen DC supports transparency");
        } else {
            dprintf3("Screen DC doesn't support transparency");
        }


        ReleaseDC(hwndMain, hDC);
    }

#endif // DEBUG

    //
    // If a command line arg was supplied then use that as
    // the INI file
    //

    if (lstrlen(lpszCmdLine)) {

        lstrcpy(szIniFile, lpszCmdLine);
        LoadScene(szIniFile);

    }

#ifdef DEBUG

    //
    // Set up the debug menu state
    //

    SetDebugLevel(__iDebugLevel);   // set menu state

#endif

    dprintf2("started");

#ifdef TIMER_TICKS
    //
    // Start the update timer
    //

    uiTimer = SetTimer(hwndMain, 1, 500, NULL);
#endif

    return TRUE;
}

//
// Close down and tidy up
//

void Terminate()
{
    char buf[256];

#ifdef TIMER_TICKS
    //
    // Stop the update timer
    //

    if (uiTimer) KillTimer(hwndMain, uiTimer);
#endif

    //
    // Delete the DIB driver DC
    //

    if (hdcOffScreen) {
        DeleteDC(hdcOffScreen);
        hdcOffScreen = NULL;
    }

    if (pdibOffScreen) {
        DeleteDIB(pdibOffScreen);
        pdibOffScreen = NULL;
    }

    //
    // Delete the background DIB
    //

    if (pdibBkGnd) {
        DeleteDIB(pdibBkGnd);
        pdibBkGnd = NULL;
    }

    //
    // Delete any sprites
    //

    DeleteSpriteList();

    //
    // Delete the palette
    //

    if (hpalCurrent) DeleteObject(hpalCurrent);


#ifdef DEBUG

    //
    // Save the debug level
    //

    wsprintf(buf, "%d", __iDebugLevel);
    WriteProfileString(szAppName, "debug", buf);
    dprintf2("ended");

#endif // DEBUG
        
}

//
// Read the INI file to set the initial state
//

void LoadScene(LPSTR pFileName)
{
    char szFile[_MAX_PATH];
    char szDIB[_MAX_PATH];
    char szSprites[512];
    LPSTR p;
    PSPRITE pSprite;

    dprintf2("LoadScene(%s)", pFileName ? pFileName : (LPSTR)"(NULL)");

    if (!pFileName || !lstrlen(pFileName)) {

        //
        // Show the file open dialog
        //

        if (!PromptForFileName(hwndMain, 
                               hAppInstance, 
                               szFile,
                               sizeof(szFile), 
                               "Open Scene", 
                               szIniFilter,
                               "ini",
                               PFFN_OPENFILE | PFFN_UPPERCASE)) {
            return;
        }

    } else {

        lstrcpy(szFile, pFileName);

    }

    //
    // Get the name of the background dib
    //

    dprintf3(" Getting bkgnd dib");
    GetPrivateProfileString("Background",
                            "dib",
                            "",
                            szDIB,
                            sizeof(szDIB),
                            szFile);

    if (lstrlen(szDIB) > 0) {
        LoadBackground(szDIB, NO_UPDATE);
    }

    //
    // Get the list of sprites
    //

    dprintf3(" Getting sprite list");
    GetPrivateProfileString("Sprites",
                            NULL,
                            "",
                            szSprites,
                            sizeof(szSprites),
                            szFile);


    //
    // Read each sprite entry and create the sprite
    //

    p = szSprites;
    while (*p) {

        //
        // Load the sprite
        //

        dprintf3("  Sprite: %s", p);
        GetPrivateProfileString(p,
                            "dib",
                            "",
                            szDIB,
                            sizeof(szDIB),
                            szFile);
        if (!lstrlen(szDIB)) {

            dprintf1("No DIB= entry for sprite");

        } else {

            pSprite = LoadSprite(szDIB, NO_UPDATE);
            if (pSprite) {

                //
                // get any other info
                //

                SetSpritePosition(pSprite,
                                  GetPrivateProfileInt(p,
                                                       "x",
                                                       pSprite->x,
                                                       szFile),
                                  GetPrivateProfileInt(p,
                                                       "y",
                                                       pSprite->y,
                                                       szFile),
                                  NO_UPDATE);

                SetSpriteZOrder(pSprite,
                                GetPrivateProfileInt(p,
                                                     "z",
                                                     pSprite->z,
                                                     szFile),
                                NO_UPDATE);


                pSprite->vx = GetPrivateProfileInt(p,
                                                  "vx",
                                                  pSprite->vx,
                                                  szFile);


                pSprite->vy = GetPrivateProfileInt(p,
                                                  "vy",
                                                  pSprite->vy,
                                                  szFile);
 
                pSprite->bSelectable = GetPrivateProfileInt(p,
                                                  "selectable",
                                                  pSprite->bSelectable,
                                                  szFile);

                dprintf3("  Sprite: %s, x:%u, y:%u, z:%u, vx:%u, vy:%u",
                         (LPSTR)szDIB,
                         pSprite->x,
                         pSprite->y,
                         pSprite->z,
                         pSprite->vx,
                         pSprite->vy);

            }
        }

        p += lstrlen(p) + 1;

    }

    //
    // Redraw the lot
    //

    Redraw(NULL, UPDATE_SCREEN);

    //
    // Start the update mechanism
    //

    bAutoUpdate = TRUE;
}
