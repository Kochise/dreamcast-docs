/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    indicate.cxx

Abstract:

Environment:

    Runs on Dreamcast under Windows CE.


-------------------------------------------------------------------*/


#include "precomp.hxx"


LPDIRECTDRAWSURFACE g_lpddsIndicators = NULL;
KeyboardState       g_swkeybdstate;
KeyboardState       g_hwkeybdstate;
KeyboardState      *g_pkeybdstateCurrent = &g_hwkeybdstate;


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SetIMEState

Description:

Return Value:

    None.

-------------------------------------------------------------------*/
void SetIMEState(KeyboardState* pNewKeybdState)
{
    HIMC hIMC;

    if (!(hIMC = ImmGetContext(g_hwndEditBox)))
        return;

    if (pNewKeybdState->fIMEOn != ImmGetOpenStatus(hIMC)) {
        ImmSetOpenStatus(hIMC, pNewKeybdState->fIMEOn);
    }

    ImmReleaseContext(g_hwndEditBox, hIMC);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ResetSoftKeybdState

Description:

Return Value:

    None.

-------------------------------------------------------------------*/
void ResetSoftKeybdState(void)
{
    SKBSetLayout(PHONETIC);
    
    g_swkeybdstate.fIMEOn = TRUE;
    g_swkeybdstate.fCapsOn = FALSE;
    g_swkeybdstate.fDoubleWidth = FALSE;

    SetIMEState(&g_swkeybdstate);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ResetHardKeybdState

Description:

Return Value:

    None.

-------------------------------------------------------------------*/
void ResetHardKeybdState(void)
{
    HIMC hIMC;

    g_hwkeybdstate.keyboard = HARDWARE;

    if (g_bRWNDactive || g_bCWNDactive) {
        g_hwkeybdstate.fIMEOn = TRUE;
    } else {
        g_hwkeybdstate.fIMEOn = FALSE;
    }

    g_hwkeybdstate.fCapsOn = GetKeyState(VK_CAPITAL) & 0x01;

    if (hIMC = ImmGetContext(g_hwndEditBox)) {
        DWORD       dwConvMode;
        DWORD       dwSentenceMode;

        ImmGetConversionStatus(hIMC, &dwConvMode, &dwSentenceMode);
        g_hwkeybdstate.fDoubleWidth = dwConvMode & IME_CMODE_FULLSHAPE;

        ImmReleaseContext(g_hwndEditBox, hIMC);
    } else {
        g_swkeybdstate.fDoubleWidth = FALSE;
    }

    SetIMEState(&g_hwkeybdstate);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IndicatorCreate

Description:

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL IndicatorCreate(void)
{
    g_lpddsIndicators = DDUtilLoadBitmap(g_hInstance, g_lpdd, INDICATOR_BITMAP_NAME);

    if (g_fHardwareKeyboardPresent) {
        ResetHardKeybdState();
        g_pkeybdstateCurrent = &g_hwkeybdstate;
    } else {
        ResetSoftKeybdState();
        g_pkeybdstateCurrent = &g_swkeybdstate;
    }

    return (g_lpddsIndicators != NULL);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IndicatorDestroy

Description:

Return Value:

    none

-------------------------------------------------------------------*/
void IndicatorDestroy(void)
{
    // release the offscreen surface
    if (g_lpddsIndicators) 
        g_lpddsIndicators->Release();
 
} // IndicatorDestroy


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IndicatorBlt

Description:

    This function blits the editbox to the back buffer.

Return Value:

    none

-------------------------------------------------------------------*/
void IndicatorBlt(LPDIRECTDRAWSURFACE lpDDSBack)
{
    RECT            rc;
    KeyboardState   keybdstate;

    keybdstate = *g_pkeybdstateCurrent;

    if (lpDDSBack) {
        // Black border around indicator bar.
        DDrawFillRect(lpDDSBack, INDICATOR_LEFTEDGE - 2, INDICATOR_TOPEDGE - 2,
                      INDICATOR_WIDTH * 3 + 5, INDICATOR_HEIGHT + 4, BLACK);

        rc.top = 0;
        rc.bottom = INDICATOR_HEIGHT;

        // IME On/Off indicator
        rc.left = keybdstate.fIMEOn ? INDICATOR_IMEON : INDICATOR_IMEOFF;
        rc.left *= INDICATOR_WIDTH;
        rc.right = rc.left + INDICATOR_WIDTH;
        lpDDSBack->BltFast(INDICATOR_LEFTEDGE, INDICATOR_TOPEDGE,
            g_lpddsIndicators, &rc, DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);

        // Full/Half shape indicator
        if (keybdstate.fIMEOn) {
            switch(keybdstate.keyboard) {
            case PHONETIC:
            case SYMBOLS:
                rc.left = INDICATOR_FULLSHAPE;
                break;
            case ROMANJI:
            case HARDWARE:
                rc.left = keybdstate.fDoubleWidth ? INDICATOR_FULLSHAPE : INDICATOR_HALFSHAPE;
                break;
            default:
                rc.left = INDICATOR_HALFSHAPE;
                break;
            }
        } else {
            rc.left = INDICATOR_HALFSHAPE;
        }
        rc.left *= INDICATOR_WIDTH;
        rc.right = rc.left + INDICATOR_WIDTH;
        lpDDSBack->BltFast (INDICATOR_LEFTEDGE + INDICATOR_WIDTH, INDICATOR_TOPEDGE,
            g_lpddsIndicators, &rc, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);

        // Caps Lock indicator
        rc.left = keybdstate.fCapsOn ? INDICATOR_CAPSON : INDICATOR_CAPSOFF;
        rc.left *= INDICATOR_WIDTH;
        rc.right = rc.left + INDICATOR_WIDTH;
        lpDDSBack->BltFast (INDICATOR_LEFTEDGE + INDICATOR_WIDTH * 2, INDICATOR_TOPEDGE,
            g_lpddsIndicators, &rc, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
    }
} // IndicatorBlt

