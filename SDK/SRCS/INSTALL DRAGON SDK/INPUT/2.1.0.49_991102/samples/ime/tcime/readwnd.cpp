/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    READWND.cxx

Abstract:

    This file contains functions which manage the reading string window (RWND).

Environment:

     Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hxx"

LRESULT CALLBACK RWNDWndProc(HWND, UINT, WPARAM, LPARAM);
void RWNDRender(void);

// global variables
HWND                g_hwndRWND = NULL;                      // handle to RWND's window
BOOL                g_bRWNDactive = FALSE;                  // is the RWND active
BOOL                g_bRWNDIncorrect = FALSE;               // There is an incorrect input
WORD                g_wRWNDXCoord = 0;
WORD                g_wReadStrLen = 0;                      // The length of reading string
WCHAR               g_wszReadStr[RWND_MAXREADING + 1] = {0};// The buffer for reading string
LPDIRECTDRAWSURFACE g_lpddsRWND = NULL;                     // RWND's offscreen surface


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDCreate

Description:

    This function initializes the contents of the CWND, and calls the
    CWNDCreateWindow and CWNDRender functions.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL RWNDCreate(void)
{
    DDSURFACEDESC       ddsd;
    HRESULT             hr;

    // create the CWND window
    if (!RWNDCreateWindow()) {
        return(0);
    }

    // Create offscreen surface.
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.dwWidth = RWND_WIDTH;
    ddsd.dwHeight = RWND_HEIGHT;       
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    hr = g_lpdd->CreateSurface (&ddsd, &g_lpddsRWND, NULL);
    if (hr != DD_OK) {
        OutputDebugString (TEXT("Create offscreen surface failed.\r\n"));
        return FALSE;
    }

    g_wReadStrLen = 0;
    memset(g_wszReadStr, 0, sizeof(g_wszReadStr));

    g_bRWNDIncorrect = FALSE;

    RWNDRender();

    return(TRUE);
} // RWNDCreate


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    RWNDCreateWindow

Description:

    This function registers a window class, and creates a window for
    the RWND.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL RWNDCreateWindow(void)
{
    WNDCLASS            wc;

    // Set up and register window class.
    wc.style            = NULL;
    wc.lpfnWndProc      = DefWindowProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = g_hInstance;
    wc.hIcon            = NULL;
    wc.hCursor          = NULL;
    wc.hbrBackground    = NULL;
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = TEXT("RWND");
    
    if (!RegisterClass(&wc)) {
        OutputDebugString(TEXT("RegisterClass failed.\r\n"));
        return FALSE;
    }
    
    // Create the RWND window.
    g_hwndRWND = CreateWindowEx(0,
                                TEXT("RWND"),
                                TEXT("RWND"),
                                WS_VISIBLE,
                                0,
                                0,
                                GetSystemMetrics(SM_CXSCREEN),
                                GetSystemMetrics(SM_CYSCREEN),
                                NULL,
                                NULL,
                                g_hInstance,
                                NULL);

    if (!g_hwndRWND) {
        OutputDebugString(TEXT("CWNDCreateWindow failed.\r\n"));
        return FALSE;
    }

    // Success!
    return TRUE;

} // RWNDRreateWindow


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    RWNDDestroy

Description:

    This function cleans up the RWND.
    
Return Value:

    none

-------------------------------------------------------------------*/
void RWNDDestroy(void)
{
    // destroy the kanji window
    if (g_hwndRWND) 
        DestroyWindow(g_hwndRWND);

    // release the offscreen surface
    if (g_lpddsRWND) 
        g_lpddsRWND->Release();

} // RWNDDestroy


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    RWNDBlt

Description:

    This function renders the RWND.

Return Value:

    none

-------------------------------------------------------------------*/
void RWNDBlt(LPDIRECTDRAWSURFACE lpDDSBack)
{
    if (!g_bRWNDactive) {
        return;
    }

    RECT rc;
    rc.left = 0;
    rc.top = 0;
    rc.right = RWND_WIDTH;
    rc.bottom = RWND_HEIGHT;

    if ((g_wCaretXCoord + RWND_WIDTH) > EDITBOX_WIDTH) {
        g_wRWNDXCoord = EDITBOX_LEFTEDGE + EDITBOX_WIDTH - RWND_WIDTH - EDITBOX_MARGIN;
    } else {
        g_wRWNDXCoord = EDITBOX_LEFTEDGE + g_wCaretXCoord;
    }

    if (lpDDSBack) {
        lpDDSBack->BltFast(g_wRWNDXCoord, RWND_TOPEDGE, g_lpddsRWND, &rc,
                           DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
    }
} // RWNDBlt


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    RWNDRender

Description:

    This function displays the keyboard background and the single
    key of the editbox.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
void RWNDRender(void)
{  
    HDC             hdcTarget;
    HFONT           hfontOld;
    HRESULT         hr;

    // Render the InWindow background.
    if (!DDrawFillRect(g_lpddsRWND, 0, 0, RWND_WIDTH, RWND_HEIGHT, RWND_BKGNDCOLOR))
        return;

    // Draw the key
    if (!RenderBlankKey(g_lpddsRWND, 0, 0, RWND_WIDTH, RWND_HEIGHT))
        return;

    // Draw the incorrect tone
    if (g_bRWNDIncorrect && g_wReadStrLen == RWND_MAXREADING) {
        DDrawFillRect(g_lpddsRWND, RWND_MARGIN + DEFAULT_FONTSIZE * (RWND_MAXREADING - 1) + 1,
                      RWND_MARGIN + 1, DEFAULT_FONTSIZE - 2, DEFAULT_FONTSIZE - 2, RWND_BKGNDINCORRECT);
    }

    if (g_wReadStrLen == 0)
        return;

    // Draw the characters
    hr = g_lpddsRWND->GetDC(&hdcTarget);
    if (hr != DD_OK)
        return;

    hfontOld = (HFONT)SelectObject(hdcTarget, g_hfontDefault);
    SetBkMode(hdcTarget, TRANSPARENT);

    if (g_bRWNDIncorrect && g_wReadStrLen == RWND_MAXREADING) {
        ExtTextOut(hdcTarget, RWND_MARGIN, RWND_MARGIN, 0, NULL,
           g_wszReadStr, g_wReadStrLen - 1, NULL);

        SetTextColor(hdcTarget, 0x000000FF);
        ExtTextOut(hdcTarget, RWND_MARGIN + DEFAULT_FONTSIZE * (RWND_MAXREADING - 1),
                   RWND_MARGIN, 0, NULL, &g_wszReadStr[RWND_MAXREADING - 1], 1, NULL);
    } else {
        ExtTextOut(hdcTarget, RWND_MARGIN, RWND_MARGIN, 0, NULL,
           g_wszReadStr, g_wReadStrLen, NULL);
    }

    SelectObject(hdcTarget, hfontOld);

    hr = g_lpddsRWND->ReleaseDC(hdcTarget);
    
    return;

} // RWNDRender


/********************************************************************

Function:

    RWNDUpdateStr

********************************************************************/
void RWNDUpdateStr(void)
{
    HIMC    hIMC;
    WORD    wLen;

    if (g_bRWNDIncorrect) {
        g_bRWNDIncorrect = FALSE;
    }

    hIMC = (HIMC)ImmGetContext(g_hwndEditBox);
    if (!hIMC) return;

    wLen = (WORD)ImmGetCompositionString(hIMC, GCS_COMPSTR,
                                         g_wszReadStr, sizeof(g_wszReadStr));

    g_wReadStrLen = wLen / sizeof(WCHAR);
    
    ImmReleaseContext(g_hwndEditBox, hIMC);

    RWNDRender();

    return;
}


/********************************************************************

Function:

    RWNDCleanStr

********************************************************************/
void RWNDCleanStr(void)
{
    if (g_bRWNDIncorrect) {
        g_bRWNDIncorrect = FALSE;
    }

    if (g_wReadStrLen == 0)
        return;

    memset(g_wszReadStr, 0, sizeof(g_wszReadStr));

    g_wReadStrLen = 0;

    RWNDRender();

    return;
}


/********************************************************************

Function:

    RWNDIncorrectInput

********************************************************************/
void RWNDIncorrectInput(void)
{
    g_bRWNDIncorrect = TRUE;

    RWNDRender();

    return;
}
