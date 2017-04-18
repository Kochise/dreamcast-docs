/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    display.cxx

Abstract:

    This file contains functions for displaying soft keyboard, IME, and kanji
    selection windows.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hpp"


// handle to kana font
HFONT               g_hfontKana = NULL;


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    DDrawFillRect

Description:

    Fills a rectangle with a solid color on a DirectDraw surface.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
DDrawFillRect (
    LPDIRECTDRAWSURFACE     pdds,
    DWORD                   dwX,
    DWORD                   dwY,
    DWORD                   dwWidth,
    DWORD                   dwHeight,
    DWORD                   dwColor
    )
{
    HRESULT         hr;
    DDBLTFX         ddbltfx;
    RECT            rcDest;

    rcDest.left = dwX;
    rcDest.top = dwY;
    rcDest.right = dwX + dwWidth;
    rcDest.bottom = dwY + dwHeight;

    memset (&ddbltfx, 0, sizeof(ddbltfx));
    ddbltfx.dwSize = sizeof(ddbltfx);
    ddbltfx.dwFillColor = dwColor;

    hr = pdds->Blt (&rcDest, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);


    return (hr == DD_OK);
} // DDrawFillRect


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    DDrawOutlineRect

Description:

    Outlines a rectangle on a DirectDraw surface.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
DDrawOutlineRect (
    LPDIRECTDRAWSURFACE     pdds,
    DWORD                   dwX,
    DWORD                   dwY,
    DWORD                   dwWidth,
    DWORD                   dwHeight,
    DWORD                   dwColor
    )
{
    // Left edge.
    if (!DDrawFillRect (pdds, dwX, dwY, 1, dwHeight, dwColor))
        return FALSE;

    // Top edge.
    if (!DDrawFillRect (pdds, dwX, dwY, dwWidth, 1, dwColor))
        return FALSE;

    // Right edge.
    if (!DDrawFillRect (pdds, dwX+dwWidth-1, dwY, 1, dwHeight, dwColor))
        return FALSE;

    // Bottom edge.
    if (!DDrawFillRect (pdds, dwX, dwY+dwHeight-1, dwWidth, 1, dwColor))
        return FALSE;

    return TRUE;
} // DDrawOutlineRect


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    RenderCharacters

Description:

    Draws a string of characters on a key.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
RenderCharacters 
    (
    LPDIRECTDRAWSURFACE         pddsTarget, 
    TCHAR                       *wc,                         // MUST be NULL terminated
    WORD                        xKeyLeftEdge, 
    WORD                        yKeyTopEdge, 
    WORD                        dxKeyWidth,
    WORD                        dyKeyHeight,
    JUSTIFY                     eCenter,                     // justify?
    HFONT                       hfontSpecify
    )
{
    HRESULT             hr;
    HDC                 hdcTarget;
    DWORD               error;
    SIZE                size;
    HFONT               hfontOld;

    hr = pddsTarget->GetDC (&hdcTarget);
    if (hr != DD_OK)
        return FALSE;

    if (hfontSpecify) {
        hfontOld = (HFONT)SelectObject (hdcTarget, hfontSpecify);
    } else {
        hfontOld = (HFONT)SelectObject (hdcTarget, g_hfontKana);
    }
    SetBkMode (hdcTarget, TRANSPARENT);

    if (eCenter == CENTER_JUSTIFY) 
    {
        // center justify
        GetTextExtentPoint32(hdcTarget, wc, _tcslen(wc), &size);
        if (size.cx > dxKeyWidth)
            size.cx = dxKeyWidth;

        if (!ExtTextOut (hdcTarget, xKeyLeftEdge + (dxKeyWidth - size.cx)/2, 
                yKeyTopEdge + (dyKeyHeight - size.cy)/2 - 1,  // subtract 1 so we don't conflict
                                                              // with the shadows on the keys
                0, NULL, wc, _tcslen(wc), NULL))
        {
            error = GetLastError();
            hr = pddsTarget->ReleaseDC (hdcTarget);
            return FALSE;
        }
    } else {
        // Left justify
        if (!ExtTextOut (hdcTarget, xKeyLeftEdge, yKeyTopEdge, 0, NULL, 
            wc, _tcslen(wc), NULL))
        {
            error = GetLastError();
            hr = pddsTarget->ReleaseDC (hdcTarget);
            return FALSE;
        }
    }       

    SelectObject(hdcTarget, hfontOld);

    hr = pddsTarget->ReleaseDC (hdcTarget);

    return TRUE;

} // RenderCharacters


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    RenderFocusRing

Description:

    Outlines a highlighted ring around a rectangle on a DirectDraw surface.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
RenderFocusRing
    (
    LPDIRECTDRAWSURFACE         pddsTarget, 
    WORD                        xKeyLeftEdge, 
    WORD                        yKeyTopEdge, 
    WORD                        dxKeyWidth,
    WORD                        dyKeyHeight,
    WORD                        dwKeyBorderColor
    )
{
    DDrawOutlineRect (pddsTarget, xKeyLeftEdge, yKeyTopEdge, dxKeyWidth, dyKeyHeight, 
        dwKeyBorderColor);
    DDrawOutlineRect (pddsTarget, xKeyLeftEdge + 1, yKeyTopEdge + 1, dxKeyWidth - 2, dyKeyHeight - 2, 
        dwKeyBorderColor);

    return TRUE;
} // RenderFocusRing


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    RenderBlankKey

Description:

    This function draws the background of a single key
Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
RenderBlankKey
    (
    LPDIRECTDRAWSURFACE         pddsTarget,
    WORD                        xLeftEdge,
    WORD                        yTopEdge,
    WORD                        dxWidth,
    WORD                        dyHeight
    )
{
    // Fill the center of the button.
    DDrawFillRect (pddsTarget, xLeftEdge, yTopEdge, dxWidth, dyHeight, KEY_FILL_COLOR);

    // Shadows
    DDrawFillRect (pddsTarget, xLeftEdge, yTopEdge, dxWidth,
        KEY_SHADOW_THICKNESS, KEY_SHADOW_LIGHT_COLOR);
    DDrawFillRect (pddsTarget, xLeftEdge, yTopEdge,
        KEY_SHADOW_THICKNESS, dyHeight, KEY_SHADOW_LIGHT_COLOR);
    DDrawFillRect (pddsTarget, xLeftEdge + dxWidth - KEY_SHADOW_THICKNESS,
        yTopEdge + KEY_SHADOW_THICKNESS, KEY_SHADOW_THICKNESS,
        dyHeight - KEY_SHADOW_THICKNESS, KEY_SHADOW_DARK_COLOR);
    DDrawFillRect (pddsTarget, xLeftEdge, yTopEdge + dyHeight - KEY_SHADOW_THICKNESS,
        dxWidth, KEY_SHADOW_THICKNESS, KEY_SHADOW_DARK_COLOR);

    return TRUE;
} // RenderBlankKey
