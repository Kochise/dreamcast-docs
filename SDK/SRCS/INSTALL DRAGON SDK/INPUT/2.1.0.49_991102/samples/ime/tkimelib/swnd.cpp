
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    swnd.cxx

Abstract:

    This file contains functions which manage the symbol window (SWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hxx"


#ifdef KANJI
// global variables
SWNDKEY             *g_pskCurrentSWND;                    // array of SWND keys                                                        
WORD                 g_cCurrentSWNDKeys = 0;               // number of SWND keys
WORD                 g_xSWNDCursor = 0;                    // x cursor position in SWND
WORD                 g_ySWNDCursor = 0;                    // y cursor position in SWND
HWND                 g_hwndSWND = NULL;                    // handle to SWND's window
WORD                 g_iSWNDFocus = 0;                     // index of key which has the focus rect
LPDIRECTDRAWSURFACE g_lpddsSWND = NULL;                  // SWND's offscreen surface


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SWNDCreate

Description:

    This function initializes the contents of the SWND, and calls the
    SWNDCreateWindow and SWNDRender functions.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
SWNDCreate
    (
    void
    )
{

    WORD i;
    DDSURFACEDESC      ddsd;
    HRESULT             hr;

    g_pskCurrentSWND = new SWNDKEY[g_cSpecialKeys + SWND_SPECIAL_KEYS]; 
    if (!g_pskCurrentSWND) return FALSE;
    // initialize the SWND to contain only space characters, and to have dimensions of
    // one row by one column
    for (i=0; i<g_cSpecialKeys; i++) {
        g_pskCurrentSWND[i].szKeyString[0] = g_rgcSpecialKeys[i];
        g_pskCurrentSWND[i].szKeyString[1] = '\0';
        g_pskCurrentSWND[i].szKeyString[MAX_CHARS_ON_KEY] = '\0';
        g_pskCurrentSWND[i].dxColumns = 1;
        g_pskCurrentSWND[i].dyRows = 1;
        g_pskCurrentSWND[i].xGridLocation = (BYTE)i % SWND_COLUMNS;
        g_pskCurrentSWND[i].yGridLocation = (BYTE)i / SWND_COLUMNS;
    }

    // add in the reject key
    _tcscpy( g_pskCurrentSWND[g_cSpecialKeys].szKeyString, KANJI_REJECT );
    g_pskCurrentSWND[g_cSpecialKeys].dxColumns = 1;
    g_pskCurrentSWND[g_cSpecialKeys].dyRows = 1;
    g_pskCurrentSWND[g_cSpecialKeys].xGridLocation = (BYTE)g_cSpecialKeys % SWND_COLUMNS;
    g_pskCurrentSWND[g_cSpecialKeys].yGridLocation = (BYTE)g_cSpecialKeys / SWND_COLUMNS;
    g_cSpecialKeys++;



    // initialize the cursor to the first position in the SWND
    g_xSWNDCursor = 0;
    g_ySWNDCursor = 0;
    g_iSWNDFocus =  0;
    g_cCurrentSWNDKeys = g_cSpecialKeys;

    // create the SWND window
    if (!SWNDCreateWindow()) {
        return(0);
    }

    // Create offscreen surface.
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.dwWidth = SWND_WIDTH;
    ddsd.dwHeight = SWND_HEIGHT;       
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    hr = g_lpdd->CreateSurface (&ddsd, &g_lpddsSWND, NULL);
    if (hr != DD_OK) {
        OutputDebugString (TEXT("Create offscreen surface failed.\r\n"));
        return FALSE;
    }

    // load the arrow bitmaps
    g_lpddsSWNDUpArrow = DDUtilLoadBitmap (g_hinstApp, g_lpdd, SWND_UPBITMAP_NAME);
    g_lpddsSWNDDownArrow = DDUtilLoadBitmap (g_hinstApp, g_lpdd, SWND_DOWNBITMAP_NAME);
    if (!g_lpddsSWNDUpArrow || !g_lpddsSWNDDownArrow)  // arrow cannot be loaded, this is an error
    {
        OutputDebugString (TEXT("SWND: Arrow bitmap could not be loaded."));
        return FALSE;
    }

    return(TRUE);


} // SWNDCreate


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SWNDWindowProc

Description:

    This is the callback function for messages sent to the SWND.

Return Value:
    0 if message is processed, DefWindowProc's return value otherwise.

-------------------------------------------------------------------*/
LRESULT CALLBACK SWNDWindowProc(  HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
  )
{
    if (hwnd == g_hwndSWND) {
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
} // SWNDWindowProc



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SWNDUpdateFocusRect

Description:

    This function redraws the key that last had a focus rectangle and the
    key which now has a focus rectangle to reflect any change in the location
    of the focus rectangle.  The focus rectangle is the highlighted square 
    surrounding the key which is the current location of the SWND joystick.

Return Value:

    none

-------------------------------------------------------------------*/
void
SWNDUpdateFocusRect
    (
    WORD iKeyTop
    )
{
    WORD            iSWNDNewFocus;

    iSWNDNewFocus = SWNDFindKeyUnderCursor ();

    if (iSWNDNewFocus != 0xffff && iSWNDNewFocus != g_iSWNDFocus)
    {
        if (g_iSWNDFocus != 0xffff)
        {
            // render the key which used to have a focus rectangle
            SWNDRenderKey (g_lpddsSWND, 0, SWND_BORDER_HEIGHT,
                &g_pskCurrentSWND[g_iSWNDFocus], FALSE, iKeyTop);
        }

        // put the new focus rectangle location into the global variable which
        // stores the focus rect's location
        g_iSWNDFocus = iSWNDNewFocus;

        // render the key which now has a focus rectangle
        SWNDRenderKey (g_lpddsSWND, 0, SWND_BORDER_HEIGHT,
            &g_pskCurrentSWND[g_iSWNDFocus], TRUE, iKeyTop);
    }
} // SWNDUpdateFocusRect



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SWNDFindKeyUnderCursor

Description:

    This function searches the SWND array to find which index of this array
    corresponds to the current location of the x and y SWND cursors.

Return Value:

    Index of current key if one is found, 0xffff otherwise.

-------------------------------------------------------------------*/
WORD
SWNDFindKeyUnderCursor
    (
    void
    )
{

    WORD            iKeyCurrent;
    SWNDKEY*        psk;

    // loop through the SWND
    for (iKeyCurrent = 0 ; iKeyCurrent < g_cCurrentSWNDKeys ; iKeyCurrent++)
    {
        psk = &g_pskCurrentSWND[iKeyCurrent];
        // find out if x and y cursors fall in the boundaries of this key
        if ((psk->xGridLocation <= g_xSWNDCursor) &&
            (g_xSWNDCursor < (psk->xGridLocation + psk->dxColumns)) &&
            (psk->yGridLocation <= g_ySWNDCursor) &&
            (g_ySWNDCursor < (psk->yGridLocation + psk->dyRows)))
        {
            return iKeyCurrent;
        }
    }

    return 0xffff;
} // SWNDFindKeyUnderCursor



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SWNDCreateWindow

Description:

    This function registers a window class, and creates a window for
    the SWND.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
SWNDCreateWindow ()
{
    WNDCLASS            wc;

    // Set up and register window class.
    wc.style            = NULL;
    wc.lpfnWndProc      = SWNDWindowProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = g_hinstApp;
    wc.hIcon            = NULL;
    wc.hCursor          = NULL;
    wc.hbrBackground    = NULL;
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = TEXT("SWND");
    
    if (!RegisterClass (&wc)) {
        OutputDebugString (TEXT("RegisterClass failed.\r\n"));
        return FALSE;
    }
    
    // Create the SWND window.
    g_hwndSWND = CreateWindowEx(
        0,
        TEXT("SWND"),
        TEXT("SWND"),
        WS_VISIBLE,
        0,
        0,
        GetSystemMetrics (SM_CXSCREEN),
        GetSystemMetrics (SM_CYSCREEN),
        NULL,
        NULL,
        g_hinstApp,
        NULL);

    if (!g_hwndSWND) {
        OutputDebugString(TEXT("SWNDCreateWindow failed.\r\n"));
        return FALSE;
    }

    // Success!
    return TRUE;

} // SWNDCreateWindow



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SWNDDestroy

Description:

    This function cleans up the SWND.
Return Value:

    none

-------------------------------------------------------------------*/
void
SWNDDestroy
    (
    void
    )
{
    // destroy the kanji window
    if (g_hwndSWND) 
    {
        DestroyWindow(g_hwndSWND);
        g_hwndSWND = NULL;
    }

    // release the offscreen surface
    if (g_lpddsSWND) 
    {
        g_lpddsSWND->Release();
        g_lpddsSWND = NULL;
    }

    // release the arrow surfaces
    if (g_lpddsSWNDUpArrow) 
    {
        g_lpddsSWNDUpArrow->Release();
        g_lpddsSWNDUpArrow = NULL;
    }

    if (g_lpddsSWNDDownArrow) 
    {
        g_lpddsSWNDDownArrow->Release();
        g_lpddsSWNDDownArrow = NULL;
    }

    delete [] g_pskCurrentSWND;
    g_pskCurrentSWND = NULL;

} // SWNDDestroy

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SWNDBlt

Description:

    This function blits the SWND.

Return Value:

    none

-------------------------------------------------------------------*/
void
SWNDBlt
    (
    LPDIRECTDRAWSURFACE lpDDSBack
    )
{
    RECT rc;
    rc.left = 0;
    rc.top = 0;
    rc.right = SWND_WIDTH;
    rc.bottom = SWND_HEIGHT;

    if (lpDDSBack) 
    {
        lpDDSBack->BltFast (SWND_LEFTEDGE, SWND_TOPEDGE, g_lpddsSWND, &rc, 
            DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
    }
} // SWNDUpdate
#endif  // KANJI
