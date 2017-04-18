
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    softkbd.cxx

Abstract:

    This file contains functions which manage the soft keyboard window (SKB).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hxx"


SOFTKEY*             g_pskCurrentSKB = NULL;       // SKB keys
WORD                 g_cCurrentSKBKeys = 0;        // number of SKB keys
WORD                 g_xCursor = 0;                // x cursor position in SKB
WORD                 g_yCursor = 0;                // y cursor position in SKB
WORD                 g_iKeyFocus = 0;              // key which has the focus ring
LPDIRECTDRAWSURFACE g_lpddsSKB = NULL;           // direct draw
HWND                 g_hwndSKB = NULL;             // handle to SKB's window
WORD                 g_iSWNDKeyTop = 0;


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBCreate

Description:

    This function initializes the contents of the SKB, and calls the
    SKBWindowCreate and SKBRenderWindow functions.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
SKBCreate
    (
    KBDLAYOUT               kbdInitial
    )
{
    DDSURFACEDESC      ddsd;
    HRESULT             hr;

    if (!IME_CreateDirectInput (g_hinstApp, g_hwndApp, &g_pdidevice2JoystickSKB))
    {
         // this is not an error; maybe the joystick is unplugged.  the SKB will
        // continuously try to find a joystick.
    }

    // set up the first keyboard layout
    switch (kbdInitial)
    {
#ifdef  KANJI
        case HIRAGANA:
            g_pskCurrentSKB = g_rgskHiragana;
            g_cCurrentSKBKeys = g_cHiraganaKeys;
            g_swkeybdstate.keyboard = HIRAGANA;
            g_iKeyFocus = 10;   // The 'A' key
            g_xCursor = g_pskCurrentSKB[g_iKeyFocus].xGridLocation;
            g_yCursor = g_pskCurrentSKB[g_iKeyFocus].yGridLocation;
            break;
        case KATAKANA:
            g_pskCurrentSKB = g_rgskKatakana;
            g_cCurrentSKBKeys = g_cKatakanaKeys;
            g_swkeybdstate.keyboard = KATAKANA;
            g_iKeyFocus = 10;   // The 'A' key
            g_xCursor = g_pskCurrentSKB[g_iKeyFocus].xGridLocation;
            g_yCursor = g_pskCurrentSKB[g_iKeyFocus].yGridLocation;
            break;
#endif  // KANJI
        case ROMANJI:
            g_pskCurrentSKB = g_rgskRomanji;
            g_cCurrentSKBKeys = g_cRomanjiKeys;
            g_swkeybdstate.keyboard = ROMANJI;
            g_iKeyFocus = 18;   // The 'A' key
            g_xCursor = g_pskCurrentSKB[g_iKeyFocus].xGridLocation;
            g_yCursor = g_pskCurrentSKB[g_iKeyFocus].yGridLocation;
            break;
    }

    // create the SKB's window
    if (!SKBCreateWindow()) {
        return (0);
    }

    // Create offscreen surface.
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.dwWidth = SKB_WIDTH;
    ddsd.dwHeight = SKB_HEIGHT;       
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    hr = g_lpdd->CreateSurface (&ddsd, &g_lpddsSKB, NULL);
    if (hr != DD_OK) {
        OutputDebugString (TEXT("Create offscreen surface failed.\r\n"));
        return FALSE;
    }

#ifdef  KANJI
    // create the special symbols window
    if (!SWNDCreate ())
    {
        return 0;
    }
#endif  // KANJI

    // Acquire the joystick.  This allows us to read its state.
    if (!AcquireJoystick(&g_pdidevice2JoystickSKB))
    {
         // this is not an error; maybe the joystick is unplugged.  the SKB will
        // continuously try to find a joystick.
    }

   if (!SKBRender ()) return (FALSE);

   return (TRUE);

} // SKBCreate

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBWindowProc

Description:

    This is the callback function for messages sent to the SKB.

Return Value:
    0 if message is processed, DefWindowProc's return value otherwise.

-------------------------------------------------------------------*/
LRESULT CALLBACK SKBWindowProc (
  HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
  )
{
    switch (uMsg) 
    {
    case WM_KEYDOWN:
        return(0);
        break;
    case WM_CHAR:
        // symbol was selected in the symbol window; pass this to the app
        PostMessage(g_hwndApp, WM_CHAR, wParam, lParam);
        return(0);
        break;
    }
    return (DefWindowProc(hwnd, uMsg, wParam, lParam));
} // SKBWindowProc




/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBCreateWindow

Description:

    This function registers a window class, and creates a window for
    the SKB.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
SKBCreateWindow ()
{
    WNDCLASS            wc;

    // Set up and register window class.
    wc.style            = NULL;
    wc.lpfnWndProc      = SKBWindowProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = g_hinstApp;
    wc.hIcon            = NULL;
    wc.hCursor          = NULL;
    wc.hbrBackground    = NULL;
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = TEXT("SKB");
    
    if (!RegisterClass (&wc)) {
        OutputDebugString (TEXT("RegisterClass failed.\r\n"));
        return FALSE;
    }
    
    // Create the main application window.
    g_hwndSKB = CreateWindowEx(
        0,
        TEXT("SKB"),
        TEXT("SKB"),
        WS_VISIBLE,
        0,
        0,
        GetSystemMetrics (SM_CXSCREEN),
        GetSystemMetrics (SM_CYSCREEN),
        NULL,
        NULL,
        g_hinstApp,
        NULL);

    if (!g_hwndSKB) {
        OutputDebugString(TEXT("SKBCreateWindow failed.\r\n"));
        return FALSE;
    }

    // Success!
    return TRUE;

} // SKBCreateWindow



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBDestroy

Description:

    This function cleans up the SKB.

Return Value:

    none

-------------------------------------------------------------------*/
void
SKBDestroy
    (
    void
    )
{
    // destroy the SKB window
    if (g_hwndSKB) 
    {
        DestroyWindow(g_hwndSKB);
        g_hwndSKB = NULL;
    }

    // release the offscreen surface
    if (g_lpddsSKB) 
    {
        g_lpddsSKB->Release();   
        g_lpddsSKB = NULL;
    }

    // Release the SKB joystick
    if (g_pdidevice2JoystickSKB)
    {
        g_pdidevice2JoystickSKB->Unacquire ();
        g_pdidevice2JoystickSKB->Release ();
        g_pdidevice2JoystickSKB = NULL;
    }

#ifdef  KANJI
    // destroy the symbols window
    SWNDDestroy();
#endif  // KANJI

} // SKBDestroy

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBUpdate

Description:

    This function calls a function to read the SKB direct input devices.

Return Value:

    none

-------------------------------------------------------------------*/
void
SKBUpdate
    (
    void
    )
{
    if (g_fHardwareKeyboardPresent)
        return;

#ifdef KANJI
    static BOOL bLastActive = g_bSWNDactive;

    // if the SWND shifted to active or to not active, then reset the iKeyTop to 0
    if (g_bSWNDactive != bLastActive)
    {
        g_iSWNDKeyTop = 0;
        if (bLastActive == TRUE) {
            SKBRender();   // render the SKB
        } else {
            SWNDRender(g_iSWNDKeyTop);
        }
        bLastActive = g_bSWNDactive; 
    }
#endif  // KANJI

    if (g_bSKBReacquireJoystick == TRUE) 
    {
        // the IME gave up control, so we need to reacquire the joystick
        AcquireJoystick(&g_pdidevice2JoystickSKB);
        g_bSKBReacquireJoystick = FALSE;
    }

    // if the KWND is active, then don't read direct input for SKB
#ifdef KANJI
    if (!g_bKWNDactive && !g_bSWNDactive)
    {
        SKBReadDirectInputDevices();
    }

	// if KWND is active, then unacquire the joystick
	if (g_pdidevice2JoystickSKB && g_bKWNDactive)
	{
		g_pdidevice2JoystickSKB->Unacquire();
	}

    if (g_bSWNDactive)
    {
        SWNDReadDirectInputDevices(&g_iSWNDKeyTop);
    }
#else
    SKBReadDirectInputDevices();
#endif  // KANJI
} // SKBUpdate


void SKBBlt(LPDIRECTDRAWSURFACE lpDDSBack)
{
    RECT rc;

    if (g_fHardwareKeyboardPresent)
        return;

    rc.left = 0;
    rc.top = 0;
    rc.right = SKB_WIDTH;
    rc.bottom = SKB_HEIGHT;

    if (lpDDSBack)
    {
#ifdef KANJI
        if (g_bSWNDactive)
        {
            SWNDBlt (lpDDSBack);
        }
        else
#endif  // KANJI
        {
            lpDDSBack->BltFast (SKB_LEFTEDGE, SKB_TOPEDGE, g_lpddsSKB, 
                    &rc, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
        }
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 
Function: 

    SKBFindKeyUnderCursor

Description:

    This function searches the SKB array to find which index of this array
    corresponds to the current location of the x and y SKB cursors.

Return Value:

    Index of current key if one is found, 0xffff otherwise.

-------------------------------------------------------------------*/
WORD
SKBFindKeyUnderCursor
    (
    void
    )
{
    WORD            iKeyCurrent;
    SOFTKEY*        psk;

    // search through all the keys until you find the key which occupies
    // the space where the cursor is
    for (iKeyCurrent = 0 ; iKeyCurrent < g_cCurrentSKBKeys ; iKeyCurrent++)
    {
        psk = &g_pskCurrentSKB[iKeyCurrent]; 
        if ((psk->xGridLocation <= g_xCursor) &&
            (g_xCursor < (psk->xGridLocation + psk->dxColumns)) &&
            (psk->yGridLocation <= g_yCursor) &&
            (g_yCursor < (psk->yGridLocation + psk->dyRows)))
        {
            return iKeyCurrent;
        }
    }

    return 0xffff;
} // SKBFindKeyUnderCursor

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBUpdateFocusRect

Description:

    This function redraws the key that last had a focus rectangle and the
    key which now has a focus rectangle to reflect any change in the location
    of the focus rectangle.  The focus rectangle is the highlighted square 
    surrounding the key which is the current location of the KWND joystick.

Return Value:

    none

-------------------------------------------------------------------*/
void
SKBUpdateFocusRect
    (
    void
    )
{
    WORD            iKeyNewFocus;
	TCHAR           wcTransChar, wszTransChar[2], *pszTextOverride = NULL;

    iKeyNewFocus = SKBFindKeyUnderCursor ();

    if (iKeyNewFocus != 0xffff)
    {
        if (g_iKeyFocus != 0xffff)
        {
#ifdef KANJI
			if(g_pskCurrentSKB == g_rgskHiragana)
			{
                wcTransChar = SKBConvertHiraganaKey(g_pskCurrentSKB[g_iKeyFocus].szKeyString[0]);
			}
			else if(g_pskCurrentSKB == g_rgskKatakana)
			{
                wcTransChar = SKBConvertKatakanaKey(g_pskCurrentSKB[g_iKeyFocus].szKeyString[0]);
			}
            else if(g_pskCurrentSKB == g_rgskRomanji)
			{
                wcTransChar = SKBConvertRomanjiKey(g_pskCurrentSKB[g_iKeyFocus].szKeyString[0]);
			}
#else
            if (g_pskCurrentSKB[g_iKeyFocus].szKeyString[1])
            {
                wcTransChar = 0;
            }
            else
            {
                wcTransChar = SKBConvertRomanjiKey(g_pskCurrentSKB[g_iKeyFocus].szKeyString[0]);
            }
#endif  // KANJI

			pszTextOverride = NULL;

			if(wcTransChar)
			{
				wszTransChar[0] = wcTransChar;
				wszTransChar[1] = L'\0';
				pszTextOverride = wszTransChar;
			}

            // render the key which used to contain the focus rect
            SKBRenderKey (g_lpddsSKB, &g_pskCurrentSKB[g_iKeyFocus], FALSE, pszTextOverride);
        }
    
        // store the new focus rect in the global variable which holds this location
        g_iKeyFocus = iKeyNewFocus;

#ifdef KANJI
		if(g_pskCurrentSKB == g_rgskHiragana)
		{
            wcTransChar = SKBConvertHiraganaKey(g_pskCurrentSKB[g_iKeyFocus].szKeyString[0]);
		}
		else if(g_pskCurrentSKB == g_rgskKatakana)
		{
            wcTransChar = SKBConvertKatakanaKey(g_pskCurrentSKB[g_iKeyFocus].szKeyString[0]);
		}
        else if(g_pskCurrentSKB == g_rgskRomanji)
		{
            wcTransChar = SKBConvertRomanjiKey(g_pskCurrentSKB[g_iKeyFocus].szKeyString[0]);
		}
#else 
            if (g_pskCurrentSKB[g_iKeyFocus].szKeyString[1])
            {
                wcTransChar = 0;
            }
            else
            {
                wcTransChar = SKBConvertRomanjiKey(g_pskCurrentSKB[g_iKeyFocus].szKeyString[0]);
            }
#endif  // KANJI

		pszTextOverride = NULL;

		if(wcTransChar)
		{
			wszTransChar[0] = wcTransChar;
			wszTransChar[1] = L'\0';
			pszTextOverride = wszTransChar;
		}

        // render the key which now contains the focus rect
        SKBRenderKey (g_lpddsSKB, &g_pskCurrentSKB[g_iKeyFocus], TRUE, pszTextOverride);
    }
} // SKBUpdateFocusRect
