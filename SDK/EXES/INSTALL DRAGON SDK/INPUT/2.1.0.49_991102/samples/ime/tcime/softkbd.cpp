
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


// global variables
HWND                g_hwndSKB = NULL;             // handle to SKB's window
RECT                g_rcSKB;
WORD                g_uSKBColumns = 0;
WORD                g_uSKBRows = 0;
SOFTKEY*            g_pskCurrentSKB = NULL;       // SKB keys
WORD                g_cCurrentSKBKeys = 0;        // number of SKB keys
WORD                g_uFocusSKBKey = 0;           // key which has the focus ring
WORD                g_xSKBCursor = 0;             // x cursor position in SKB
WORD                g_ySKBCursor = 0;             // y cursor position in SKB

LPDIRECTDRAWSURFACE g_lpddsSKB = NULL;            // direct draw


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBWindowProc

Description:

    This is the callback function for messages sent to the SKB.

Return Value:
    0 if message is processed, DefWindowProc's return value otherwise.

-------------------------------------------------------------------*/
LRESULT CALLBACK SKBWindowProc(HWND hwnd,      // handle to window
                               UINT uMsg,      // message identifier
                               WPARAM wParam,  // first message parameter
                               LPARAM lParam)  // second message parameter
{
    switch (uMsg) {
    case WM_KEYDOWN:
        return(0);
        break;
    case WM_CHAR:
        // symbol was selected in the symbol window; pass this to the app
        PostMessage(g_hwndAPP, WM_CHAR, wParam, lParam);
        return(0);
        break;
    }
    return (DefWindowProc(hwnd, uMsg, wParam, lParam));
} // SKBWindowProc


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBCreate

Description:

    This function initializes the contents of the SKB, and calls the
    SKBWindowCreate and SKBRenderWindow functions.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL SKBCreate(KBDLAYOUT kbdInitial)
{
    DDSURFACEDESC       ddsd;
    HRESULT             hr;

    if (!CreateDirectInput(g_hInstance, g_hwndAPP, &g_pdidevice2JoystickSKB)) {
        // this is not an error; maybe the joystick is unplugged.  the SKB will
        // continuously try to find a joystick.
    }

    // set up the first keyboard layout
    switch (kbdInitial) {
    case PHONETIC:
        SKBSetLayout(PHONETIC);
        g_swkeybdstate.fIMEOn = TRUE;
        g_swkeybdstate.fDoubleWidth = TRUE;
        g_swkeybdstate.fCapsOn = FALSE;
        SetIMEState(&g_swkeybdstate);
        break;
    case ROMANJI:
        SKBSetLayout(ROMANJI);
        g_swkeybdstate.fIMEOn = TRUE;
        g_swkeybdstate.fDoubleWidth = FALSE;
        g_swkeybdstate.fCapsOn = FALSE;
        SetIMEState(&g_swkeybdstate);
        break;
    case SYMBOLS:
        SKBSetLayout(SYMBOLS);
        g_swkeybdstate.fIMEOn = TRUE;
        g_swkeybdstate.fDoubleWidth = TRUE;
        g_swkeybdstate.fCapsOn = FALSE;
        SetIMEState(&g_swkeybdstate);
        break;
    }

    // create the SKB's window
    WNDCLASS            wc;

    // Set up and register window class.
    wc.style            = NULL;
    wc.lpfnWndProc      = SKBWindowProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = g_hInstance;
    wc.hIcon            = NULL;
    wc.hCursor          = NULL;
    wc.hbrBackground    = NULL;
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = TEXT("SKB");
    
    if (!RegisterClass(&wc)) {
        DEBUGMSG(1, (TEXT("RegisterClass failed.\n")));
        return FALSE;
    }
    
    // Create the main application window.
    g_hwndSKB = CreateWindowEx(0,
                               TEXT("SKB"),
                               TEXT("SKB"),
                               WS_VISIBLE,
                               0,
                               0,
                               GetSystemMetrics(SM_CXSCREEN),
                               GetSystemMetrics(SM_CYSCREEN),
                               NULL,
                               NULL,
                               g_hInstance,
                               NULL);

    if (!g_hwndSKB) {
        DEBUGMSG(1, (TEXT("SKBCreateWindow failed.\n")));
        return FALSE;
    }

    // Create offscreen surface.
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.dwWidth = SKB_WIDTH;
    ddsd.dwHeight = SKB_HEIGHT;       
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    hr = g_lpdd->CreateSurface(&ddsd, &g_lpddsSKB, NULL);
    if (hr != DD_OK) {
        OutputDebugString(TEXT("Create offscreen surface failed.\r\n"));
        return FALSE;
    }

    // Acquire the joystick.  This allows us to read its state.
    if (!AcquireJoystick(&g_pdidevice2JoystickSKB)) {
        // this is not an error; maybe the joystick is unplugged.  the SKB will
        // continuously try to find a joystick.
    }

    if (!SKBRender()) return (FALSE);

    return TRUE;

} // SKBCreate


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBDestroy

Description:

    This function cleans up the SKB.

Return Value:

    none

-------------------------------------------------------------------*/
void SKBDestroy(void)
{
    // destroy the SKB window
    if (g_hwndSKB) 
        DestroyWindow(g_hwndSKB);

    // release the offscreen surface
    if (g_lpddsSKB) 
        g_lpddsSKB->Release();   

    // Release the SKB joystick
    if (g_pdidevice2JoystickSKB) {
        g_pdidevice2JoystickSKB->Unacquire();
        g_pdidevice2JoystickSKB->Release();
        g_pdidevice2JoystickSKB = NULL;
    }

    return;
} // SKBDestroy

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBUpdate

Description:

    This function calls a function to read the SKB direct input devices.

Return Value:

    none

-------------------------------------------------------------------*/
void SKBSetLayout(KBDLAYOUT kbdLayout)
{
    switch (kbdLayout) {
    case PHONETIC:
        g_swkeybdstate.keyboard = PHONETIC;
        g_pskCurrentSKB = g_rgskPhonetic;
        g_cCurrentSKBKeys = g_cPhoneticKeys;
        g_uFocusSKBKey = 0;
        g_xSKBCursor = g_pskCurrentSKB[g_uFocusSKBKey].xGridLocation;
        g_ySKBCursor = g_pskCurrentSKB[g_uFocusSKBKey].yGridLocation;
        g_uSKBColumns = SKB_PHON_COLUMNS;
        g_uSKBRows = SKB_PHON_ROWS;
        g_rcSKB.left = SKB_PHON_LEFTEDGE;
        g_rcSKB.top = SKB_PHON_TOPEDGE;
        g_rcSKB.right = SKB_PHON_WIDTH;
        g_rcSKB.bottom = SKB_PHON_HEIGHT;
        break;
    case ROMANJI:
        g_swkeybdstate.keyboard = ROMANJI;
        g_pskCurrentSKB = g_rgskRomanji;
        g_cCurrentSKBKeys = g_cRomanjiKeys;
        g_uFocusSKBKey = 18;   // The 'A' key
        g_xSKBCursor = g_pskCurrentSKB[g_uFocusSKBKey].xGridLocation;
        g_ySKBCursor = g_pskCurrentSKB[g_uFocusSKBKey].yGridLocation;
        g_uSKBColumns = SKB_ENG_COLUMNS;
        g_uSKBRows = SKB_ENG_ROWS;
        g_rcSKB.left = SKB_ENG_LEFTEDGE;
        g_rcSKB.top = SKB_ENG_TOPEDGE;
        g_rcSKB.right = SKB_ENG_WIDTH;
        g_rcSKB.bottom = SKB_ENG_HEIGHT;
        break;
    case SYMBOLS:
        g_swkeybdstate.keyboard = SYMBOLS;
        g_pskCurrentSKB = g_rgskSymbol;
        g_cCurrentSKBKeys = g_cSymbolKeys;
        g_uFocusSKBKey = 0;
        g_xSKBCursor = g_pskCurrentSKB[g_uFocusSKBKey].xGridLocation;
        g_ySKBCursor = g_pskCurrentSKB[g_uFocusSKBKey].yGridLocation;
        g_uSKBColumns = SKB_SYM_COLUMNS;
        g_uSKBRows = SKB_SYM_ROWS;
        g_rcSKB.left = SKB_SYM_LEFTEDGE;
        g_rcSKB.top = SKB_SYM_TOPEDGE;
        g_rcSKB.right = SKB_SYM_WIDTH;
        g_rcSKB.bottom = SKB_SYM_HEIGHT;
        break;
    default:
        return;
    }

    return;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBUpdate

Description:

    This function calls a function to read the SKB direct input devices.

Return Value:

    none

-------------------------------------------------------------------*/
void SKBUpdate(void)
{
    static BOOL bLastActive = FALSE;

    if (g_fHardwareKeyboardPresent) {
        if (bLastActive)
            bLastActive = FALSE;

        return;
    }

    if (!bLastActive) {
        SKBRender();
        bLastActive = TRUE;
    }

    if (g_bSKBReacquireJoystick == TRUE) {
        // the IME gave up control, so we need to reacquire the joystick
        AcquireJoystick(&g_pdidevice2JoystickSKB);
        g_bSKBReacquireJoystick = FALSE;
    }

    // if the CWND is active, then don't read direct input for SKB
    if (!g_bCWNDactive) {
        SKBReadDirectInputDevices();
    }

	// if CWND is active, then unacquire the joystick
	if (g_pdidevice2JoystickSKB && g_bCWNDactive) {
		g_pdidevice2JoystickSKB->Unacquire();
	}
} // SKBUpdate


void SKBBlt(LPDIRECTDRAWSURFACE lpDDSBack)
{
    RECT rc;

    if (g_fHardwareKeyboardPresent)
        return;

    rc.left = 0;
    rc.top = 0;
    rc.right = g_rcSKB.right;
    rc.bottom = g_rcSKB.bottom;

    if (lpDDSBack) {
        lpDDSBack->BltFast(g_rcSKB.left, g_rcSKB.top, g_lpddsSKB, 
                           &rc, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
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
WORD SKBFindKeyUnderCursor(void)
{
    WORD            iKeyCurrent;
    SOFTKEY*        psk;

    // search through all the keys until you find the key which occupies
    // the space where the cursor is
    for (iKeyCurrent = 0 ; iKeyCurrent < g_cCurrentSKBKeys ; iKeyCurrent++) {
        psk = &g_pskCurrentSKB[iKeyCurrent]; 
        if ((psk->xGridLocation <= g_xSKBCursor) &&
            (g_xSKBCursor < (psk->xGridLocation + psk->dxColumns)) &&
            (psk->yGridLocation <= g_ySKBCursor) &&
            (g_ySKBCursor < (psk->yGridLocation + psk->dyRows))) {
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
    surrounding the key which is the current location of the CWND joystick.

Return Value:

    none

-------------------------------------------------------------------*/
void SKBUpdateFocusRect(void)
{
    WORD            iKeyNewFocus;
	TCHAR           wcTransChar, wszTransChar[2], *pszTextOverride = NULL;

    iKeyNewFocus = SKBFindKeyUnderCursor();

    if (iKeyNewFocus != 0xffff) {
        if (g_uFocusSKBKey != 0xffff) {
            if (g_pskCurrentSKB == g_rgskPhonetic) {
				wcTransChar = SKBConvertPhoneticKey(g_pskCurrentSKB[g_uFocusSKBKey].szKeyString[0]);
			} else if (g_pskCurrentSKB == g_rgskRomanji) {
				wcTransChar = SKBConvertRomanjiKey(g_pskCurrentSKB[g_uFocusSKBKey].szKeyString[0]);
			} else if (g_pskCurrentSKB == g_rgskSymbol) {
				wcTransChar = SKBConvertSymbolKey(g_pskCurrentSKB[g_uFocusSKBKey].szKeyString[0]);
            } else {
            }


			pszTextOverride = NULL;

			if (wcTransChar) {
				wszTransChar[0] = wcTransChar;
				wszTransChar[1] = L'\0';
				pszTextOverride = wszTransChar;
			}

            // render the key which used to contain the focus rect
            SKBRenderKey(g_lpddsSKB, &g_pskCurrentSKB[g_uFocusSKBKey], FALSE, pszTextOverride);
        }
    
        // store the new focus rect in the global variable which holds this location
        g_uFocusSKBKey = iKeyNewFocus;
        if (g_pskCurrentSKB == g_rgskPhonetic) {
			wcTransChar = SKBConvertPhoneticKey(g_pskCurrentSKB[g_uFocusSKBKey].szKeyString[0]);
		} else if (g_pskCurrentSKB == g_rgskRomanji) {
			wcTransChar = SKBConvertRomanjiKey(g_pskCurrentSKB[g_uFocusSKBKey].szKeyString[0]);
		} else if (g_pskCurrentSKB == g_rgskSymbol) {
			wcTransChar = SKBConvertSymbolKey(g_pskCurrentSKB[g_uFocusSKBKey].szKeyString[0]);
		} else {
        }

		pszTextOverride = NULL;

		if(wcTransChar) {
			wszTransChar[0] = wcTransChar;
			wszTransChar[1] = L'\0';
			pszTextOverride = wszTransChar;
		}

        // render the key which now contains the focus rect
        SKBRenderKey(g_lpddsSKB, &g_pskCurrentSKB[g_uFocusSKBKey], TRUE, pszTextOverride);
    }
} // SKBUpdateFocusRect
