
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    displayskb.cxx

Abstract:

    This file contains functions which display the software keyboard (SKB).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hpp"


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBRender

Description:

    This function displays the keyboard background and each individual
    key of the SKB.
Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
SKBRender 
    (
    void
    )
{
    WORD                iKey;
	TCHAR               wcTransChar, wszTransChar[2], *pszTextOverride;

    // Render the keyboard background.
    if (!DDrawFillRect (g_lpddsSKB, 0, 0, SKB_WIDTH, SKB_HEIGHT, SKB_BKGNDCOLOR))
    {
        OutputDebugString (TEXT("Big fill failed.\r\n"));
        return FALSE;
    }


    // Render each of the individual keys on the keyboard.
    for (iKey = 0 ; iKey < g_cCurrentSKBKeys ; iKey++)
    {
		if(g_pskCurrentSKB == g_rgskHiragana)
		{
			wcTransChar = SKBConvertHiraganaKey(g_pskCurrentSKB[iKey].szKeyString[0]);
		}
		else if(g_pskCurrentSKB == g_rgskKatakana)
		{
			wcTransChar = SKBConvertKatakanaKey(g_pskCurrentSKB[iKey].szKeyString[0]);
		}
		else if(g_pskCurrentSKB == g_rgskRomanji)
		{
			wcTransChar = SKBConvertRomanjiKey(g_pskCurrentSKB[iKey].szKeyString[0]);
		}

		pszTextOverride = NULL;

		if(wcTransChar)
		{
			wszTransChar[0] = wcTransChar;
			wszTransChar[1] = L'\0';
			pszTextOverride = wszTransChar;
		}

        if (!SKBRenderKey (g_lpddsSKB, &g_pskCurrentSKB[iKey], iKey == g_iKeyFocus, pszTextOverride))
        {
            return FALSE;
        }
    } 
    return TRUE;
} // SKBRender

  
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBRenderKey

Description:

    This function draws a single keyboard key.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
SKBRenderKey
    (
    LPDIRECTDRAWSURFACE         pddsTarget,
    SOFTKEY*                    psk,
    BOOL                        fFocus,
	TCHAR*                      pszTextOverride
    )
{
    WORD                xKeyLeftEdge;
    WORD                yKeyTopEdge;
    WORD                dxKeyWidth;
    WORD                dyKeyHeight;

    xKeyLeftEdge = psk->xGridLocation * SKB_COLWIDTH + SKB_BORDERTHICKNESS;
    yKeyTopEdge = psk->yGridLocation * SKB_ROWHEIGHT + SKB_BORDERTHICKNESS;
    dxKeyWidth = SKB_COLWIDTH * psk->dxColumns;
    dyKeyHeight = SKB_ROWHEIGHT * psk->dyRows;

    if (!RenderBlankKey (pddsTarget, xKeyLeftEdge, yKeyTopEdge, dxKeyWidth,
        dyKeyHeight))
    {
        return FALSE;
    }
 

    if (!RenderCharacters (pddsTarget, pszTextOverride ? pszTextOverride : psk->szKeyString,
		xKeyLeftEdge, yKeyTopEdge, dxKeyWidth, dyKeyHeight, CENTER_JUSTIFY, NULL))
    {
        return FALSE;
    }


    if (fFocus)
    {
        if (!RenderFocusRing (pddsTarget, xKeyLeftEdge, yKeyTopEdge, dxKeyWidth,
            dyKeyHeight, KEY_BORDER_COLOR))
        {
            return FALSE;
        }
    }

    return TRUE;
} // SKBRenderKey

