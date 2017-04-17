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


#include "precomp.hxx"

// Global variables and constants
HINSTANCE                   g_hinstApp;                 // application's HINSTANCE
HWND                        g_hwndApp;                  // application's window handle
HWND                        g_hwndappSKB;               // SKB's window handle
HWND                        g_hwndappKWND;              // KWND's window handle
LPDIRECTDRAW                g_lpdd;                     // pointer to direct draw
LPDIRECTDRAWSURFACE         g_lpddsPrimary;             // primary buffer
LPDIRECTDRAWSURFACE         g_lpddsBack;                // back buffer
LPDIRECTINPUTDEVICE2        g_pdidevice2JoystickApp;
LPDIRECTINPUTDEVICE2        g_pdidevice2JoystickAcquired = NULL;

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
    WNDCLASS wc;
    TCHAR    achAppName[] = TEXT("TkImeLib");

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
    wc.lpszClassName    = achAppName;
    
    if (!RegisterClass (&wc)) {
        OutputDebugString (TEXT("RegisterClass failed.\r\n"));
        return FALSE;
    }
    
    // Create the main application window.
    g_hwndApp = CreateWindowEx(
        0,
        achAppName,
        achAppName,
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
    {
        DestroyWindow (g_hwndApp);
        g_hwndApp = NULL;
    }
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
    if (!CreateApplicationWindow ())
        return FALSE;

    if (!CreateSharedResources ())
        return FALSE;

    // create a window for the softkbd, and initialize the softkbd to its original layout
#ifdef  KANJI
    if (!SKBCreate (HIRAGANA))
#else
    if (!SKBCreate (ROMANJI))
#endif
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

#ifdef KANJI
    // create a window for the IME, and initialize the IME to be empty
    if (!IMECreate ())
    {
        OutputDebugString(TEXT("Input Method Editor could not be created.\r\n"));
        return FALSE;
    }
#endif

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
#ifdef KANJI
    IMEDestroy ();
#endif  // KANJI
    EditBoxDestroy ();
    SKBDestroy ();
    DestroySharedResources ();
    DestroyApplicationWindow ();
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CTkIme

Description:

    Initial TKIME Lib

Return Value:

-------------------------------------------------------------------*/

CTkIme::CTkIme( HINSTANCE            hInst,
                LPDIRECTDRAW        lpDD,
                LPDIRECTDRAWSURFACE lpDDSPrimary,
                LPDIRECTDRAWSURFACE lpDDSBack )
{
    if ( hInst && lpDD && lpDDSPrimary && lpDDSBack )
    {
        // Store the hinst in a global, for later use.
        g_hinstApp     = hInst;
        g_lpdd         = lpDD;
        g_lpddsPrimary = lpDDSPrimary;
        g_lpddsBack    = lpDDSBack;

        if ( !CreateApp() )
        {
            DestroyApp();
            fInit = FALSE;
        }
        else
        {
            fInit = TRUE;
        }
    }
    else
    {
        fInit = FALSE;
    }
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ~CTkIme

Description:

    Cleanup TKIME Lib

Return Value:

-------------------------------------------------------------------*/

CTkIme::~CTkIme( void )
{
    if ( fInit )
    {
        DestroyApp();
        fInit = FALSE;
    }
}


/********************************************************************
 * GetImeInput
 *
 * Description
 *    Get text input via IME
 *
 * Parameters
 *    hWndEdit - Text window handle
 *
 * Result
 *    S_OK           Success.
 *    E_FAIL         Cancel.
 ********************************************************************/
HRESULT CTkIme::GetImeInput( LPTSTR               lpBuffer,
                             LPDIRECTINPUTDEVICE2 pdidevice2JoystickCaller,
                             BYTE                *prgvButtonsCaller         )
{
    MSG             msg;
    RECT            rc;
    HRESULT         hr = S_OK;
    DDBLTFX         ddbltfx;

    if ( !fInit )
    {
        return E_FAIL;
    }

    HWND hwndFocusPrev = SetFocus(g_hwndApp);
    SetRect( &rc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) );

    // the background will be a white screen
    memset (&ddbltfx, 0, sizeof(ddbltfx));
    ddbltfx.dwSize = sizeof(ddbltfx);
    ddbltfx.dwFillColor = LIGHTGRAY;

    if ( pdidevice2JoystickCaller )
    {
        pdidevice2JoystickCaller->Unacquire();

        for ( short i = 0; i < JOYSTICKMAXBUTTONS; i++ )
        {
             g_rgiPrevButtons[i] = *(prgvButtonsCaller+i);
        }
    }
    if ( g_pdidevice2JoystickAcquired )
    {
        AcquireJoystick( &g_pdidevice2JoystickAcquired );
    }

    // Initial EditBox Buffer
    //
    _tcscpy( g_wszConverted, lpBuffer );
    g_wszNonConverted[0] = TEXT('\0');
    g_caretpos = g_compositioncaret = _tcslen( g_wszConverted );
    EditBoxRender();

    while (TRUE) 
    {
        if (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE)) 
        {
            if (!GetMessage (&msg, NULL, 0, 0))
                break;

#ifdef KANJI
            if(msg.message == WM_KEYDOWN
            && g_bKWNDactive
            && msg.wParam >= L'1' && msg.wParam <= L'9')
            {
                PostMessage(g_hwndApp, WM_CHAR, msg.wParam, 0);
            }
            else
#endif  // KANJI
            {
                TranslateMessage(&msg);
            }
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
#ifdef KANJI
            IMEUpdate ();
#endif  // KANJI

            // clear the screen
            hr = g_lpddsBack->Blt (&rc, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);

            // Blit from the EditBox, SKB, and IME offscreen surfaces to the back buffer.
            // All blits to back buffer must occur as a block, without any blits to 
            // offscreen surfaces in between blits to the back buffer.
            EditBoxBlt (g_lpddsBack);
            SKBBlt (g_lpddsBack);
            IndicatorBlt (g_lpddsBack);
#ifdef KANJI
            IMEBlt (g_lpddsBack);
#endif  // KANJI
            CaretBlt (g_lpddsBack);

            g_lpddsPrimary->Flip (NULL, DDFLIP_WAIT);
        }
    } // while (TRUE)

    // Return IME Edit Text to caller
    //
    _tcscpy( lpBuffer, g_wszConverted );

    if ( g_pdidevice2JoystickAcquired )
    {
        g_pdidevice2JoystickAcquired->Unacquire();
    }
    if ( pdidevice2JoystickCaller )
    {
        pdidevice2JoystickCaller->Acquire();

        for ( short i = 0; i < JOYSTICKMAXBUTTONS; i++ )
        {
            *(prgvButtonsCaller+i) = g_rgiPrevButtons[i];
        }
    }

    // clear the screen
    hr = g_lpddsBack->Blt (&rc, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
    hr = g_lpddsPrimary->Blt (&rc, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
    hr = g_lpddsPrimary->Flip (NULL, DDFLIP_WAIT);

    if (hwndFocusPrev)
    {
        SetFocus(hwndFocusPrev);
    }
    return hr;
}
