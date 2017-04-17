/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    displaykwnd.cxx

Abstract:

    This file contains functions which display the kanji selection window (KWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hpp"


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    KWNDRender

Description:

    This function displays the keyboard background and each individual
    key of the KWND.
Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
KWNDRender
    (
    WORD iKeyTop
    )
{
    WORD                iKey;    
    int                 topkey;
    int                 bottomkey;
    int                 totalkeys;

    // Render the KWND background.
    if (!DDrawFillRect (g_lpddsKWND, 0, KWND_BORDER_HEIGHT, 
        g_dxCandidateListWidth, KWND_KEYS_HEIGHT, KWND_BKGNDCOLOR))
    {
        OutputDebugString (TEXT("Big fill failed.\r\n"));
        return FALSE;
    }

    // Print out the kanji on each key
    for (iKey=0; iKey<MAX_KANJI_DISPLAYED; iKey++) 
    {
        if (iKey + iKeyTop * KWND_COLUMNS < g_cCurrentKWNDKeys)
        {
            if (!KWNDRenderKey (g_lpddsKWND, 0, KWND_BORDER_HEIGHT,
                    iKey + iKeyTop * KWND_COLUMNS, 
                    ((iKey + iKeyTop * KWND_COLUMNS) == g_iKWNDFocus),
                    iKeyTop)
                )
            {
                return FALSE;
            }
        } 
    }

    // Draw the scroll bar.
    totalkeys = g_cCurrentKWNDKeys;
    topkey = iKeyTop;
    bottomkey = iKeyTop + KWND_ROWS;
    if (bottomkey > g_cCurrentKWNDKeys)
        bottomkey = g_cCurrentKWNDKeys;

    if (!RenderBlankKey (g_lpddsKWND, g_dxCandidateListWidth - KWND_SCROLLBARWIDTH, 
        topkey * KWND_HEIGHT / totalkeys, 
        KWND_SCROLLBARWIDTH, 
        (bottomkey - topkey) * KWND_HEIGHT / totalkeys))
    {
        return FALSE;
    }

    return TRUE;
} // KWNDRender

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    KWNDRenderKey

Description:

    This function draws a single keyboard key.
Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
KWNDRenderKey
    (
    LPDIRECTDRAWSURFACE         pddsTarget,
    WORD                        xKWNDLeftEdge,
    WORD                        yKWNDTopEdge,
    WORD                        iKey,
    BOOL                        fFocus,
    WORD                        iKeyTop
    )
{
    WORD                xKeyLeftEdge;
    WORD                yKeyTopEdge;
    WORD                dxKeyWidth;
    WORD                dyKeyHeight;
    TCHAR               wszNumber[4];
    KWNDKEY*            psk = &g_pskCurrentKWND[iKey];

    xKeyLeftEdge = xKWNDLeftEdge + psk->xGridLocation * (g_dxCandidateListWidth - KWND_SCROLLBARWIDTH);
    yKeyTopEdge = yKWNDTopEdge + (psk->yGridLocation - iKeyTop) * KWND_ROWHEIGHT;
    dxKeyWidth = (g_dxCandidateListWidth - KWND_SCROLLBARWIDTH) * psk->dxColumns;
    dyKeyHeight = KWND_ROWHEIGHT * psk->dyRows;

    // draw the key background
    if (!RenderBlankKey (pddsTarget, xKeyLeftEdge, yKeyTopEdge, dxKeyWidth,
        dyKeyHeight))
    {
        return FALSE;
    }

    // draw the number on the key
    wsprintf(wszNumber, TEXT("%d."), iKey - iKeyTop + 1);
    if (!RenderCharacters (pddsTarget, wszNumber, xKeyLeftEdge + 3, yKeyTopEdge, 
        dxKeyWidth, dyKeyHeight, LEFT_JUSTIFY, g_hfontKWND))
    {
        return FALSE;
    }

    // draw the character on the key
    if (!RenderCharacters (pddsTarget, psk->szKeyString, xKeyLeftEdge + 30, yKeyTopEdge, 
        dxKeyWidth, dyKeyHeight, LEFT_JUSTIFY, g_hfontKWND))
    {
        return FALSE;
    }

    // if this key has a focus rectangle, draw it
    if (fFocus)
    {
        if (!RenderFocusRing (pddsTarget, xKeyLeftEdge, yKeyTopEdge, dxKeyWidth,
            dyKeyHeight, KEY_BORDER_COLOR))
        {
            return FALSE;
        }
    }

    return TRUE;
} // KWNDRenderKey


