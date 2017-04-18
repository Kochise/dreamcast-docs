/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    kwnd.cxx

Abstract:

    This file contains functions which manage the kanji selection window (KWND).

Environment:

     Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hpp"


// global variables
KWNDKEY             g_pskCurrentKWND[TOTAL_KWND_KEYS];  // array of KWND keys
WORD                g_cCurrentKWNDKeys = 0;             // number of keys in KWND
WORD                g_xKWNDCursor = 0;                  // x cursor position
WORD                g_yKWNDCursor = 0;                  // y cursor position
HWND                g_hwndKWND = NULL;                  // handle to KWND's window
HFONT               g_hfontKWND = NULL;
WORD                g_iKWNDFocus = 0;                   // index of key which has the focus rect
LPDIRECTDRAWSURFACE g_lpddsKWND = NULL;                 // kwnd's offscreen surface


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    KWNDCreate

Description:

    This function initializes the contents of the KWND, and calls the
    KWNDCreateWindow and KWNDRender functions.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
KWNDCreate
    (
    void
    )
{

    WORD i;
    DDSURFACEDESC       ddsd;
    HRESULT             hr;

    // initialize the KWND to contain only space characters, and to have dimensions of
    // one row by one column
    for (i=0; i<TOTAL_KWND_KEYS; i++) {
        g_pskCurrentKWND[i].szKeyString[1] = '\0';
        g_pskCurrentKWND[i].szKeyString[MAX_CHARS_ON_KEY] = '\0';
        g_pskCurrentKWND[i].dxColumns = 1;
        g_pskCurrentKWND[i].dyRows = 1;
        g_pskCurrentKWND[i].xGridLocation = (BYTE)(i % KWND_COLUMNS);
        g_pskCurrentKWND[i].yGridLocation = (BYTE)(i / KWND_COLUMNS);
    }

    // initialize the cursor to the first position in the KWND
    g_xKWNDCursor = 0;
    g_yKWNDCursor = 0;
    g_iKWNDFocus =  0;

    // create the KWND window
    if (!KWNDCreateWindow()) {
        return(0);
    }

    // Create offscreen surface.
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.dwWidth = KWND_WIDTH;
    ddsd.dwHeight = KWND_HEIGHT;       
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    hr = g_lpdd->CreateSurface (&ddsd, &g_lpddsKWND, NULL);
    if (hr != DD_OK) {
        OutputDebugString (TEXT("Create offscreen surface failed.\r\n"));
        return FALSE;
    }

    // Create the KWND font
    g_hfontKWND = CreateKanaFont(KWND_FONTHEIGHT);

    return(TRUE);


} // KWNDCreate


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    KWNDWindowProc

Description:

    This is the callback function for messages sent to the KWND.

Return Value:
    0 if message is processed, DefWindowProc's return value otherwise.

-------------------------------------------------------------------*/
LRESULT CALLBACK KWNDWindowProc(  HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
  )
{
    if (hwnd == g_hwndKWND) {
        switch (uMsg) 
        {
        case WM_KEYDOWN:
            return(0);
            break;
        case WM_CHAR:
            return(0);
            break;
        }
    }
    return (DefWindowProc(hwnd, uMsg, wParam, lParam));
} // KWNDWindowProc



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    KWNDUpdateFocusRect

Description:

    This function redraws the key that last had a focus rectangle and the
    key which now has a focus rectangle to reflect any change in the location
    of the focus rectangle.  The focus rectangle is the highlighted square 
    surrounding the key which is the current location of the KWND joystick.

Return Value:

    none

-------------------------------------------------------------------*/
void
KWNDUpdateFocusRect
    (
    WORD iKeyTop,
    WORD iKWNDNewFocus   
    )
{
    if (iKWNDNewFocus != 0xffff && iKWNDNewFocus != g_iKWNDFocus)
    {
        if (g_iKWNDFocus != 0xffff)
        {
            // render the key which used to have a focus rectangle
            KWNDRenderKey (g_lpddsKWND, 0, KWND_BORDER_HEIGHT,
                g_iKWNDFocus, FALSE, iKeyTop);
        }

        // put the new focus rectangle location into the global variable which
        // stores the focus rect's location
        g_iKWNDFocus = iKWNDNewFocus;

        // render the key which now has a focus rectangle
        KWNDRenderKey (g_lpddsKWND, 0, KWND_BORDER_HEIGHT,
            g_iKWNDFocus, TRUE, iKeyTop);
    }
} // KWNDUpdateFocusRect



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    KWNDFindKeyUnderCursor

Description:

    This function searches the KWND array to find which index of this array
    corresponds to the current location of the x and y KWND cursors.

Return Value:

    Index of current key if one is found, 0xffff otherwise.

-------------------------------------------------------------------*/
WORD
KWNDFindKeyUnderCursor
    (
    void
    )
{

    WORD            iKeyCurrent;
    KWNDKEY*        psk;

    // loop through the KWND
    for (iKeyCurrent = 0 ; iKeyCurrent < g_cCurrentKWNDKeys ; iKeyCurrent++)
    {
        psk = &g_pskCurrentKWND[iKeyCurrent];
        // find out if x and y cursors fall in the boundaries of this key
        if ((psk->xGridLocation <= g_xKWNDCursor) &&
            (g_xKWNDCursor < (psk->xGridLocation + psk->dxColumns)) &&
            (psk->yGridLocation <= g_yKWNDCursor) &&
            (g_yKWNDCursor < (psk->yGridLocation + psk->dyRows)))
        {
            return iKeyCurrent;
        }
    }

    return 0xffff;
} // KWNDFindKeyUnderCursor



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    KWNDCreateWindow

Description:

    This function registers a window class, and creates a window for
    the KWND.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
KWNDCreateWindow ()
{
    WNDCLASS            wc;

    // Set up and register window class.
    wc.style            = NULL;
    wc.lpfnWndProc      = KWNDWindowProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = g_hinstApp;
    wc.hIcon            = NULL;
    wc.hCursor          = NULL;
    wc.hbrBackground    = NULL;
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = TEXT("KWND");
    
    if (!RegisterClass (&wc)) {
        OutputDebugString (TEXT("RegisterClass failed.\r\n"));
        return FALSE;
    }
    
    // Create the KWND window.
    g_hwndKWND = CreateWindowEx(
        0,
        TEXT("KWND"),
        TEXT("KWND"),
        WS_VISIBLE,
        0,
        0,
        GetSystemMetrics (SM_CXSCREEN),
        GetSystemMetrics (SM_CYSCREEN),
        NULL,
        NULL,
        g_hinstApp,
        NULL);

    if (!g_hwndKWND) {
        OutputDebugString(TEXT("KWNDCreateWindow failed.\r\n"));
        return FALSE;
    }

    // Success!
    return TRUE;

} // KWNDCreateWindow



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    KWNDDestroy

Description:

    This function cleans up the KWND.
Return Value:

    none

-------------------------------------------------------------------*/
void
KWNDDestroy
    (
    void
    )
{
    // destroy the kanji window
    if (g_hwndKWND) 
        DestroyWindow(g_hwndKWND);

    // release the offscreen surface
    if (g_lpddsKWND) 
        g_lpddsKWND->Release();

    // destroy the KWND font
    if (g_hfontKWND) {
        DeleteObject(g_hfontKWND);
    }

} // KWNDDestroy

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    KWNDBlt

Description:

    This function renders the KWND.

Return Value:

    none

-------------------------------------------------------------------*/
void
KWNDBlt
    (
    LPDIRECTDRAWSURFACE lpDDSBack
    )
{
    RECT rc;
    rc.left = 0;
    rc.top = 0;
    rc.right = KWND_WIDTH;
    rc.bottom = KWND_HEIGHT;

    if (lpDDSBack)
    {
        if (g_xCandidateList > (EDITBOX_LEFTEDGE + EDITBOX_WIDTH - KWND_WIDTH))
            g_xCandidateList = (EDITBOX_LEFTEDGE + EDITBOX_WIDTH - KWND_WIDTH);

        lpDDSBack->BltFast (g_xCandidateList, KWND_TOPEDGE, g_lpddsKWND, &rc, 
            DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
    }
} // KWNDUpdate
