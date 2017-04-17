/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    winmain.cxx

Abstract:

    A sample application which uses the software keyboard and the 
    input method editor.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hpp"


// Global variables and constants
DWORD                       g_dwScreenWidth;            // screen width
DWORD                       g_dwScreenHeight;           // screen height
HINSTANCE                   g_hinstApp;                 // application's HINSTANCE
HWND                        g_hwndApp;                  // application's window handle
HWND                        g_hwndappSKB;               // SKB's window handle
HWND                        g_hwndappKWND;              // KWND's window handle
LPDIRECTDRAW                g_lpdd;                     // pointer to direct draw
LPDIRECTDRAWSURFACE         g_lpddsPrimary;             // primary buffer
LPDIRECTDRAWSURFACE         g_lpddsBack;                // back buffer
LPDIRECTINPUTDEVICE2        g_pdidevice2JoystickApp;


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CreateApplicationWindow

Description:

    This function registers a window class, and creates a window for
    the application.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
CreateApplicationWindow 
    (
    void
    )
{
    WNDCLASS            wc;

    // Set up and register window class.
    wc.style            = NULL;
    wc.lpfnWndProc      = EditBoxWindowProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = g_hinstApp;
    wc.hIcon            = NULL;
    wc.hCursor          = NULL;
    wc.hbrBackground    = NULL;
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = TEXT("imesamp");
    
    if (!RegisterClass (&wc)) {
        OutputDebugString (TEXT("RegisterClass failed.\r\n"));
        return FALSE;
    }
    
    // Create the main application window.
    g_hwndApp = CreateWindowEx(
        0,
        TEXT("imesamp"),
        TEXT("imesamp"),
        WS_VISIBLE,
        0,
        0,
        GetSystemMetrics (SM_CXSCREEN),
        GetSystemMetrics (SM_CYSCREEN),
        NULL,
        NULL,
        g_hinstApp,
        NULL);

    if (!g_hwndApp) {
        OutputDebugString(TEXT("CreateWindow failed.\r\n"));
        return FALSE;
    }

    // Success!
    return TRUE;

} // CreateApplicationWindow


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    DestroyApplicationWindow

Description:

Return Value:

    None.

-------------------------------------------------------------------*/
void
DestroyApplicationWindow 
    (
    void
    )
{
    if (g_hwndApp) 
        DestroyWindow (g_hwndApp);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitializeDirectDraw

Description:

    Creates a DirectDraw object, sets the display mode, creates a primary 
    surface and back buffer, creates an offscreen surface to hold the bitmap,
    and other miscellaneous DirectDraw initialization tasks.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
InitializeDirectDraw 
    (
    void
    )
{
    DDSURFACEDESC       ddsd;
    DDSCAPS             ddscaps;
    HRESULT             hr;

    // Create the main DirectDraw interface.
    hr = DirectDrawCreate (NULL, &g_lpdd, NULL);
    if (hr != DD_OK ) {
        OutputDebugString (TEXT("DirectDrawCreate failed.\r\n"));
        return FALSE;
    }

    // Obtain full-screen exclusive mode.
    hr = g_lpdd->SetCooperativeLevel (g_hwndApp, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
    if (hr != DD_OK) {
        OutputDebugString (TEXT("SetCooperativeLevel failed.\r\n"));
        return FALSE;
    }

    // Set the video mode.
    hr = g_lpdd->SetDisplayMode (g_dwScreenWidth, g_dwScreenHeight, 16);
    if (hr != DD_OK) {
        OutputDebugString (TEXT("SetDisplayMode failed.\r\n"));
        return FALSE;
    }

    // Create the primary surface with 1 back buffer
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
    ddsd.dwBackBufferCount = 1;
    hr = g_lpdd->CreateSurface (&ddsd, &g_lpddsPrimary, NULL);
    if (hr != DD_OK) {
        OutputDebugString (TEXT("Create primary surface failed.\r\n"));
        return FALSE;
    }

    // Get pointer to the back buffer.
    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    hr = g_lpddsPrimary->GetAttachedSurface (&ddscaps, &g_lpddsBack);
    if (hr != DD_OK) {
        OutputDebugString (TEXT("GetAttachedSurface failed.\r\n"));
        return FALSE;
    }
    
    // Success!
    return TRUE;

} // InitializeDirectDraw


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    DestroyDirectDraw

Description:

Return Value:

    None.

-------------------------------------------------------------------*/
void 
DestroyDirectDraw 
    (
    void
    )
{
    if (g_lpddsPrimary) 
        g_lpddsPrimary->Release();

    if (g_lpdd) 
        g_lpdd->Release ();
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CreateApp

Description:

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CreateApp 
    (
    void
    )
{
    HKEY            hkey;

	if ((ERROR_SUCCESS == RegOpenKeyEx (HKEY_LOCAL_MACHINE, 
        TEXT("System\\CurrentControlSet\\Control\\Layouts\\e0010411"), 0, 0, &hkey)) ||
        (ERROR_SUCCESS == RegOpenKeyEx (HKEY_LOCAL_MACHINE, 
        TEXT("System\\CurrentControlSet\\Control\\Layouts\\e0010404"), 0, 0, &hkey))) {

        OutputDebugString(TEXT("TKIME: ERROR: Another IME (Pocket IME or Chinese IME) is currently active.\r\n"));
        OutputDebugString(TEXT("TKIME: To fix this, use the Configuration Tool to turn on the \"Tankanji IME\"\r\n"));
        OutputDebugString(TEXT("TKIME: and \"Japanese font\", and then rebuild the image.  \r\n\r\n"));
        OutputDebugString(TEXT("TKIME: Alternatively, from the WinCE command window, type \"set IMGTKIME=1\", \r\n"));
        OutputDebugString(TEXT("TKIME: and then run \"makeimg\".\r\n"));
        RegCloseKey (hkey);
        return FALSE;
    }

    if (!CreateApplicationWindow ())
        return FALSE;

    if (!InitializeDirectDraw ())
        return FALSE;

    if (!CreateSharedResources ())
        return FALSE;

    // create a window for the softkbd, and initialize the softkbd to its original layout
    if (!SKBCreate (HIRAGANA)) 
    {
        OutputDebugString(TEXT("Soft Keyboard could not be created.\r\n"));
        return FALSE;
    }

    // Create a window for the edit control, and initialize it to be empty.
    if (!EditBoxCreate ())
    {
        OutputDebugString(TEXT("Output Window could not be created.\r\n"));
        return FALSE;
    } 

    // create a window for the IME, and initialize the IME to be empty
    if (!IMECreate ())
    {
        OutputDebugString(TEXT("Input Method Editor could not be created.\r\n"));
        return FALSE;
    }

    // create a window for the IME, and initialize the IME to be empty
    if (!IndicatorCreate ())
    {
        OutputDebugString(TEXT("Indicator Bar could not be created.\r\n"));
        return FALSE;
    }

    return TRUE;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    DestroyApp

Description:

    This function cleans up the app before exiting.

Return Value:

    None.

-------------------------------------------------------------------*/
void DestroyApp
    (
    void
    )
{
    IndicatorDestroy ();
    IMEDestroy ();
    EditBoxDestroy ();
    SKBDestroy ();
    DestroySharedResources ();
    DestroyDirectDraw ();
    DestroyApplicationWindow ();
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WinMain

Description:

    This is the main function for the sample softkbd and IME.

Return Value:

    This function never actually returns, since the process is killed
    before it gets a chance.

-------------------------------------------------------------------*/
extern "C" int APIENTRY
WinMain
    (
    IN  HINSTANCE hinst,            // handle to current instance
    IN  HINSTANCE hinstPrev,        // handle to previous instance
    IN  TCHAR     *szCommandLine,   // pointer to command line string
    IN  int       nCmdShow          // show state of window
    )
{
    MSG             msg;
    RECT            rc;
    HRESULT         hr;
    DDBLTFX         ddbltfx;

    // Store the hinst in a global, for later use.
    g_hinstApp = hinst;
 
    // Determine current screen resolution.
    g_dwScreenWidth = GetSystemMetrics (SM_CXSCREEN);
    g_dwScreenHeight = GetSystemMetrics (SM_CYSCREEN);

    if (!CreateApp ()) {
        DestroyApp();
        return 0;
    }

	SetFocus(g_hwndApp);

    rc.left = rc.top = 0;
    rc.right = GetSystemMetrics (SM_CXSCREEN);
    rc.bottom = GetSystemMetrics (SM_CYSCREEN);

    // the background will be a white screen
    memset (&ddbltfx, 0, sizeof(ddbltfx));
    ddbltfx.dwSize = sizeof(ddbltfx);
    ddbltfx.dwFillColor = WHITE;

    while (TRUE) 
    {
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)) 
        {
            if (msg.message == WM_QUIT)
                break;

            /*
            if (msg.message == WM_KEYDOWN)
                DEBUGMSG(1, (TEXT("Received WM_KEYDOWN hwnd=%x wparam=%x lparam=%x\r\n"), msg.hwnd, msg.wParam, msg.lParam));
            if (msg.message == WM_SYSKEYDOWN)
                DEBUGMSG(1, (TEXT("Received WM_SYSKEYDOWN hwnd=%x wparam=%x lparam=%x\r\n"), msg.hwnd, msg.wParam, msg.lParam));
            if (msg.message == WM_KEYUP)
                DEBUGMSG(1, (TEXT("Received WM_KEYUP hwnd=%x wparam=%x lparam=%x\r\n"), msg.hwnd, msg.wParam, msg.lParam));
            if (msg.message == WM_SYSKEYUP)
                DEBUGMSG(1, (TEXT("Received WM_SYSKEYUP hwnd=%x wparam=%x lparam=%x\r\n"), msg.hwnd, msg.wParam, msg.lParam));
            if (msg.message == WM_CHAR)
                DEBUGMSG(1, (TEXT("Received WM_CHAR hwnd=%x wparam=%x lparam=%x\r\n"), msg.hwnd, msg.wParam, msg.lParam));
            */

			if(msg.message == WM_KEYDOWN && g_bKWNDactive && msg.wParam >= L'1' && msg.wParam <= L'9')
				PostMessage(g_hwndApp, WM_CHAR, msg.wParam, 0);
			else
	            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } 
        else 
        {
            // Check for the existence of a hardware keyboard, once every
            // 500 milliseconds.
            CheckForHardwareKeyboard ();

            // update SKB and IME by reading and processing input from the joystick;
            // also, update the offscreen surfaces for the SKB, IME, SWND, EditBox, and KWND
            SKBUpdate ();              
            IMEUpdate ();

            // clear the screen
            hr = g_lpddsBack->Blt (&rc, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);

            // Blit from the EditBox, SKB, and IME offscreen surfaces to the back buffer.
            // All blits to back buffer must occur as a block, without any blits to 
            // offscreen surfaces in between blits to the back buffer.
            EditBoxBlt (g_lpddsBack);
            SKBBlt (g_lpddsBack);
            IndicatorBlt (g_lpddsBack);
            IMEBlt (g_lpddsBack);
            CaretBlt (g_lpddsBack);

            g_lpddsPrimary->Flip (NULL, DDFLIP_WAIT);
        }
    } // while (TRUE)

    // clear the screen
    hr = g_lpddsBack->Blt (&rc, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
    hr = g_lpddsPrimary->Blt (&rc, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
    hr = g_lpddsPrimary->Flip (NULL, DDFLIP_WAIT);

    DestroyApp();

    OutputDebugString (TEXT("Exiting IME sample.\r\n"));

    return 0;
}
