/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    dspcwnd.cpp

Abstract:

    This file contains functions which display the candidate selection window (CWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hxx"


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDRender

Description:

    This function displays the keyboard background and each individual
    key of the CWND.
Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL CWNDRender(WORD iKeyTop)
{
    WORD                iKey;    
    int                 topkey;
    int                 bottomkey;
    int                 totalkeys;

    // Render the CWND border.
    if (!DDrawFillRect(g_lpddsCWND, 0, 0, CWND_WIDTH, CWND_HEIGHT,
                       CWND_BORDER_COLOR)) {
        OutputDebugString (TEXT("Render CWND border failed.\r\n"));
        return FALSE;
    }

    // Render the keys area background.
    if (!DDrawFillRect(g_lpddsCWND,
                       CWND_BORDER_THICKNESS,
                       CWND_BORDER_THICKNESS,
                       CWND_KEYS_WIDTH,
                       CWND_KEYS_HEIGHT,
                       CWND_KEYS_BKGNDCOLOR)) {
        OutputDebugString (TEXT("Render keys area background failed.\r\n"));
        return FALSE;
    }

    // Render the scroll bar background.
    if (!DDrawFillRect(g_lpddsCWND,
                       CWND_BORDER_THICKNESS + CWND_KEYS_WIDTH,
                       CWND_BORDER_THICKNESS,
                       CWND_SCROLL_WIDTH,
                       CWND_SCROLL_HEIGHT,
                       CWND_SCROLL_BKGNDCOLOR)) {
        OutputDebugString (TEXT("Render keys area background failed.\r\n"));
        return FALSE;
    }

    // Print out the candidate on each key
    for (iKey=0; iKey < MAX_CAND_DISPLAYED; iKey++) {
        if (iKey + iKeyTop * CWND_COLUMNS < g_cCurrentCWNDKeys) {
            if (!CWNDRenderKey(g_lpddsCWND,
                               iKey + iKeyTop * CWND_COLUMNS,
                               ((iKey + iKeyTop * CWND_COLUMNS) == g_uFocusCWNDKey),
                               iKeyTop)) {
                return FALSE;
            }
        } 
    }

    // Draw the scroll bar.
    totalkeys = g_cCurrentCWNDKeys;
    topkey = iKeyTop;
    bottomkey = iKeyTop + CWND_ROWS;
    if (bottomkey > g_cCurrentCWNDKeys)
        bottomkey = g_cCurrentCWNDKeys;

    if (!RenderBlankKey(g_lpddsCWND,
                        CWND_WIDTH - CWND_SCROLL_WIDTH - CWND_BORDER_THICKNESS,
                        topkey * CWND_SCROLL_HEIGHT / totalkeys + CWND_BORDER_THICKNESS,
                        CWND_SCROLL_WIDTH,
                        (bottomkey - topkey) * CWND_SCROLL_HEIGHT / totalkeys)) {
        return FALSE;
    }

    return TRUE;
} // CWNDRender

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDRenderKey

Description:

    This function draws a single keyboard key.
Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL CWNDRenderKey(LPDIRECTDRAWSURFACE pddsTarget,
                   WORD                iKey,
                   BOOL                fFocus,
                   WORD                iKeyTop)
{
    WORD                xKeyLeftEdge;
    WORD                yKeyTopEdge;
    WORD                dxKeyWidth;
    WORD                dyKeyHeight;
    TCHAR               wszNumber[4];
    CWNDKEY*            psk = &g_pskCurrentCWND[iKey];

    xKeyLeftEdge = psk->xGridLocation * CWND_COLWIDTH + CWND_BORDER_THICKNESS;
    yKeyTopEdge = (psk->yGridLocation - iKeyTop) * CWND_ROW_HEIGHT + CWND_BORDER_THICKNESS;
    dxKeyWidth = CWND_COLWIDTH * psk->dxColumns;
    dyKeyHeight = CWND_ROW_HEIGHT * psk->dyRows;

    // draw the key background
    if (!RenderBlankKey (pddsTarget, xKeyLeftEdge, yKeyTopEdge, dxKeyWidth,
        dyKeyHeight)) {
        return FALSE;
    }

    // draw the number on the key
    wsprintf(wszNumber, TEXT("%d."), iKey - iKeyTop + 1);
    if (!RenderCharacters (pddsTarget, wszNumber, xKeyLeftEdge + 3, yKeyTopEdge, 
        dxKeyWidth, dyKeyHeight, LEFT_JUSTIFY, g_hfontCWND)) {
        return FALSE;
    }

    // draw the character on the key
    if (!RenderCharacters (pddsTarget, psk->szKeyString, xKeyLeftEdge, yKeyTopEdge, 
        dxKeyWidth, dyKeyHeight, CENTER_JUSTIFY, g_hfontCWND)) {
        return FALSE;
    }

    // if this key has a focus rectangle, draw it
    if (fFocus) {
        if (!RenderFocusRing (pddsTarget, xKeyLeftEdge, yKeyTopEdge, dxKeyWidth,
            dyKeyHeight, KEY_BORDER_COLOR)) {
            return FALSE;
        }
    }

    return TRUE;
} // CWNDRenderKey

