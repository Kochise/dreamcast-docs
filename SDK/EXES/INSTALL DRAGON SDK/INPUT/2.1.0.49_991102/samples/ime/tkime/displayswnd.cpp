/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    displayswnd.cxx

Abstract:

    This file contains functions which display the symbol window (SWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hpp"


// offscreen surfaces for up and down scrolling arrows in SWND
LPDIRECTDRAWSURFACE    g_lpddsSWNDDownArrow = NULL;
LPDIRECTDRAWSURFACE    g_lpddsSWNDUpArrow = NULL;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SWNDRender

Description:

    This function displays the keyboard background and each individual
    key of the SWND.
Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
SWNDRender
    (
    WORD iKeyTop
    )
{
    WORD                iKey;    
    RECT rc;

    rc.left = rc.top = 0;
    rc.right = SWND_BITMAP_WIDTH;
    rc.bottom = SWND_BITMAP_HEIGHT;
 
    // Render the SWND background.
    if (!DDrawFillRect (g_lpddsSWND, 0, SWND_BORDER_HEIGHT, 
        SWND_WIDTH, SWND_KEYS_HEIGHT, SWND_BKGNDCOLOR))
    {
        OutputDebugString (TEXT("Big fill failed.\r\n"));
        return FALSE;
    }
 

    // Render the top border
    if (!DDrawFillRect (g_lpddsSWND, 0, 0,
        SWND_WIDTH, SWND_BORDER_HEIGHT, SWND_BORDER_COLOR))
    {
        OutputDebugString (TEXT("Big fill failed.\r\n"));
        return FALSE;
    }

    // Render the top arrow, if we can scroll up
    if (iKeyTop != 0)
    {
        g_lpddsSWND->BltFast (0, 0, g_lpddsSWNDUpArrow, &rc, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);    
    }


    // Render the bottom border
    if (!DDrawFillRect (g_lpddsSWND, 0, SWND_BORDER_HEIGHT + SWND_KEYS_HEIGHT,
        SWND_WIDTH, SWND_BORDER_HEIGHT, SWND_BORDER_COLOR))
    {
        OutputDebugString (TEXT("Big fill failed.\r\n"));
        return FALSE;
    }

    // Render the bottom arrow, if we can scroll down
    if ((iKeyTop + SWND_ROWS) * SWND_COLUMNS < g_cCurrentSWNDKeys)
    {
        g_lpddsSWND->BltFast (0, SWND_KEYS_HEIGHT + SWND_BORDER_HEIGHT, g_lpddsSWNDDownArrow, &rc, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
    }    

    // Print out the kanji on each key
    for (iKey=0; iKey<MAX_SWND_DISPLAYED; iKey++) 
    {
        if (iKey + iKeyTop * SWND_COLUMNS < g_cCurrentSWNDKeys)
        {
            if (!SWNDRenderKey (g_lpddsSWND, 0, SWND_BORDER_HEIGHT,
                    &g_pskCurrentSWND[iKey + iKeyTop * SWND_COLUMNS], 
                    ((iKey + iKeyTop * SWND_COLUMNS) == g_iSWNDFocus),
                    iKeyTop)
                )
            {
                return FALSE;
            }
        } 
    }

    return TRUE;
} // SWNDRender

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SWNDRenderKey

Description:

    This function draws a single keyboard key.
Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
SWNDRenderKey
    (
    LPDIRECTDRAWSURFACE         pddsTarget,
    WORD                        xSWNDLeftEdge,
    WORD                        ySWNDTopEdge,
    SWNDKEY*                    psk,
    BOOL                        fFocus,
    WORD                        iKeyTop
    )
{
    WORD                xKeyLeftEdge;
    WORD                yKeyTopEdge;
    WORD                dxKeyWidth;
    WORD                dyKeyHeight;

    xKeyLeftEdge = xSWNDLeftEdge + psk->xGridLocation * SWND_COLWIDTH;
    yKeyTopEdge = ySWNDTopEdge + (psk->yGridLocation - iKeyTop) * SWND_ROWHEIGHT;
    dxKeyWidth = SWND_COLWIDTH * psk->dxColumns;
    dyKeyHeight = SWND_ROWHEIGHT * psk->dyRows;

    // draw the key background
    if (!RenderBlankKey (pddsTarget, xKeyLeftEdge, yKeyTopEdge, dxKeyWidth,
        dyKeyHeight))
    {
        return FALSE;
    }

    // draw the character on the key
    if (!RenderCharacters (pddsTarget, psk->szKeyString, xKeyLeftEdge, yKeyTopEdge, 
        dxKeyWidth, dyKeyHeight, CENTER_JUSTIFY, NULL))
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
} // SWNDRenderKey


