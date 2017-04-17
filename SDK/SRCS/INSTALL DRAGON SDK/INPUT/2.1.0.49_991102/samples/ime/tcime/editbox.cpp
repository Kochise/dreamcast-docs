#include "precomp.hxx"


LRESULT CALLBACK EditWndProc(HWND, UINT, WPARAM, LPARAM);

void EditBoxRender(void);

void ShowIMEMsg(UINT, WPARAM, LPARAM);


HWND        g_hwndEditBox = NULL;
HFONT       g_hfontEditBox = NULL;
WORD        g_wStartPos = 0;
WORD        g_wCaretPos = 0;
WORD        g_wCaretXCoord = 0;
WORD        g_wEditStrLen = 0;
WCHAR       g_wszEditStr[EDITBOX_MAXCHARS + 1] = {0};

LPDIRECTDRAWSURFACE g_lpddsEditBox = NULL;  // editbox's offscreen surface


/********************************************************************

Function:

    EditBoxCreate

********************************************************************/
void EditBoxCreate(void)
{
    DDSURFACEDESC           ddsd;
    HRESULT                 hr;
    
    if (g_hwndEditBox) { return; }

    // create the SKB's window
    WNDCLASS            wc;

    // Set up and register window class.
    wc.style            = NULL;
    wc.lpfnWndProc      = EditWndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = g_hInstance;
    wc.hIcon            = NULL;
    wc.hCursor          = NULL;
    wc.hbrBackground    = NULL;
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = TEXT("EDITBOX");
    
    if (!RegisterClass(&wc)) {
        DEBUGMSG(1, (TEXT("RegisterClass failed.\n")));
        return;
    }
    
    // Create the main application window.
    g_hwndEditBox = CreateWindowEx(0,
                                   TEXT("EDITBOX"),
                                   TEXT("EDITBOX"),
                                   WS_VISIBLE,
                                   0,
                                   0,
                                   GetSystemMetrics(SM_CXSCREEN),
                                   GetSystemMetrics(SM_CYSCREEN),
                                   NULL,
                                   NULL,
                                   g_hInstance,
                                   NULL);

    if (!g_hwndEditBox) {
        DEBUGMSG(1, (TEXT("EditBox Create Window failed.\n")));
        return;
    }

    // Create offscreen surface.
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.dwWidth = EDITBOX_WIDTH;
    ddsd.dwHeight = EDITBOX_HEIGHT;       
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    hr = g_lpdd->CreateSurface(&ddsd, &g_lpddsEditBox, NULL);
    if (hr != DD_OK) {
        DEBUGMSG(1, (TEXT("EDITBOX: Create offscreen surface failed.\r\n")));
        return;
    }

    if (g_hfontEditBox == NULL) {
        g_hfontEditBox = CreateChineseFont(EDITBOX_FONTSIZE);
        if (g_hfontEditBox == NULL) {
            g_hfontEditBox = g_hfontDefault;
        }
    }

    g_wStartPos = 0;
    g_wCaretPos = 0;
    g_wCaretXCoord = 0;
    g_wEditStrLen = 0;
    memset(g_wszEditStr, 0, sizeof(g_wszEditStr));

    EditBoxRender();

    return;
}


/********************************************************************

Function:

    DestroyEditBox

********************************************************************/
void EditBoxDestroy(void)
{
    if (g_hwndEditBox) {
        DestroyWindow(g_hwndEditBox);
        g_hwndEditBox = NULL;
    }


    if (g_lpddsEditBox) {
        g_lpddsEditBox->Release();
        g_lpddsEditBox = NULL;
    }

    if (g_hfontEditBox && g_hfontEditBox != g_hfontDefault) {
        DeleteObject(g_hfontEditBox);
        g_hfontEditBox = NULL;
    }

    return;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    EditBoxBlt

Description:

    This function blits the editbox to the back buffer.

Return Value:

    none

-------------------------------------------------------------------*/
void EditBoxBlt(LPDIRECTDRAWSURFACE lpDDSBack)
{

    RECT rc;

    rc.left = 0;
    rc.top = 0;
    rc.right = EDITBOX_WIDTH;
    rc.bottom = EDITBOX_HEIGHT;

    if (lpDDSBack) {
        lpDDSBack->BltFast(EDITBOX_LEFTEDGE, EDITBOX_TOPEDGE,
                           g_lpddsEditBox, &rc,
                           DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
    }
} // EditBoxBlt


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CaretBlt

Description:

    This function blits the caret to the back buffer.

Return Value:

    none

-------------------------------------------------------------------*/
void CaretBlt(LPDIRECTDRAWSURFACE lpDDSBack)
{
    if (((GetTickCount() / 500) % 2)) {
        DDrawFillRect (lpDDSBack,
                       EDITBOX_LEFTEDGE + g_wCaretXCoord,
                       EDITBOX_TOPEDGE + EDITBOX_MARGIN,
                       CARET_WIDTH,
                       EDITBOX_FONTSIZE,
                       BLUE);
    }
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    EditBoxRender

Description:

    This function displays the keyboard background and the single
    key of the editbox.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
void EditBoxRender(void)
{  
    // Render the InWindow background.
    if (!DDrawFillRect(g_lpddsEditBox, 0, 0, EDITBOX_WIDTH, EDITBOX_HEIGHT, EDITBOX_BKGNDCOLOR))
        return;

    // Draw the key
    if (!RenderBlankKey(g_lpddsEditBox, 0, 0, EDITBOX_WIDTH, EDITBOX_HEIGHT))
        return;

    // Draw the characters
    if (g_wEditStrLen == 0) {
        g_wCaretXCoord = (WORD)EDITBOX_MARGIN;
        return;
    }
    
    SIZE        sizeCaretPos;
    HRESULT     hr;
    HDC         hdcTarget;
    HFONT       hfontOld;
    
    hr = g_lpddsEditBox->GetDC(&hdcTarget);
    if (hr != DD_OK)
        return;

    hfontOld = (HFONT)SelectObject(hdcTarget, g_hfontEditBox);

    SetBkMode(hdcTarget, TRANSPARENT);

    if (g_wCaretPos > g_wStartPos) {
        GetTextExtentPoint32(hdcTarget, &g_wszEditStr[g_wStartPos], g_wCaretPos - g_wStartPos, &sizeCaretPos);
        while (sizeCaretPos.cx > EDITBOX_CLIENTWIDTH) {
            if (g_wCaretPos == g_wEditStrLen) {
                g_wStartPos++;
            } else if ((g_wEditStrLen - g_wCaretPos) < EDITBOX_BLOCKCHARS) {
                g_wStartPos += (g_wEditStrLen - g_wCaretPos);
            } else {
                g_wStartPos += EDITBOX_BLOCKCHARS;
            }

            GetTextExtentPoint32(hdcTarget, &g_wszEditStr[g_wStartPos], g_wCaretPos - g_wStartPos, &sizeCaretPos);
        }
    } else {
        if (g_wStartPos >= EDITBOX_BLOCKCHARS) {
            g_wStartPos -= EDITBOX_BLOCKCHARS;
        } else {
            g_wStartPos = 0;
        }
        GetTextExtentPoint32(hdcTarget, &g_wszEditStr[g_wStartPos], g_wCaretPos - g_wStartPos, &sizeCaretPos);
    }

    ExtTextOut(hdcTarget, EDITBOX_MARGIN, EDITBOX_MARGIN, 0, NULL,
               &g_wszEditStr[g_wStartPos], g_wEditStrLen - g_wStartPos, NULL);

    SelectObject(hdcTarget, hfontOld);

    hr = g_lpddsEditBox->ReleaseDC(hdcTarget);

    g_wCaretXCoord = (WORD)sizeCaretPos.cx + EDITBOX_MARGIN;

    return;
} // EditBoxRender


/********************************************************************

Function:

    EditBoxMoveCaret

********************************************************************/
void EditBoxMoveCaret(WORD wVkKey)
{
    switch(wVkKey) {
    case VK_LEFT:
        if (g_wCaretPos == 0)
            return;
        g_wCaretPos--;
        break;
    case VK_RIGHT:
        if (g_wCaretPos == g_wEditStrLen)
            return;
        g_wCaretPos++;
        break;
    default:
        return;
    }
    
    EditBoxRender();

    return;
}


/********************************************************************

Function:

    EditBoxBackKey

********************************************************************/
void EditBoxBackKey(void)
{
    if (g_wCaretPos == 0)
        return;

    g_wszEditStr[g_wCaretPos - 1] = 0;

    if (g_wCaretPos < g_wEditStrLen) {
        memmove(&g_wszEditStr[g_wCaretPos - 1],
                &g_wszEditStr[g_wCaretPos],
                (g_wEditStrLen - g_wCaretPos) * sizeof(WCHAR));
    }

    g_wCaretPos--;
    g_wEditStrLen--;

    EditBoxRender();

    return;
}

/********************************************************************

Function:

    EditBoxDeleteKey

********************************************************************/
void EditBoxDeleteKey(void)
{
    if (g_wCaretPos == g_wEditStrLen)
        return;

    if ((g_wCaretPos + 1) < g_wEditStrLen) {
        memmove(&g_wszEditStr[g_wCaretPos],
                &g_wszEditStr[g_wCaretPos + 1],
                (g_wEditStrLen - g_wCaretPos - 1) * sizeof(WCHAR));
    }

    g_wszEditStr[g_wEditStrLen] = 0;

    g_wEditStrLen--;

    EditBoxRender();

    return;
}

/********************************************************************

Function:

    EditBoxAddChar

********************************************************************/
void EditBoxAddChar(WCHAR wChar)
{
    if (g_wEditStrLen >= EDITBOX_MAXCHARS)
        return;

    if (g_wCaretPos < g_wEditStrLen) {
        memmove(&g_wszEditStr[g_wCaretPos + 1],
                &g_wszEditStr[g_wCaretPos],
                (g_wEditStrLen - g_wCaretPos) * sizeof(WCHAR));
    }

    g_wszEditStr[g_wCaretPos] = wChar;

    g_wCaretPos++;
    g_wEditStrLen++;

    EditBoxRender();

    if (g_fHardwareKeyboardPresent) {
        g_hwkeybdstate.fCapsOn = GetKeyState(VK_CAPITAL) & 0x01;
    }

    return;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IndicatorChangeOpenStatus

Description:

Return Value:

    none

-------------------------------------------------------------------*/
void SetIMEStatus(void)
{
    HIMC            hIMC;

    if (!(hIMC = ImmGetContext(g_hwndEditBox)))
        return;

    g_hwkeybdstate.fIMEOn = ImmGetOpenStatus(hIMC);

    ImmReleaseContext(g_hwndEditBox, hIMC);
} // SetIMEStatus


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ChangeConvMode

Description:

Return Value:

    none

-------------------------------------------------------------------*/
void SetConvMode(void)
{
    HIMC            hIMC;
    DWORD           dwConvMode;
    DWORD           dwSentenceMode;

    if (!(hIMC = ImmGetContext(g_hwndEditBox)))
        return;

    ImmGetConversionStatus(hIMC, &dwConvMode, &dwSentenceMode);

    g_hwkeybdstate.fDoubleWidth = dwConvMode & IME_CMODE_FULLSHAPE;
    
    ImmReleaseContext(g_hwndEditBox, hIMC);
} // SetConvMode


/********************************************************************

Function:

    EditWndProc

Description:

    The edit box for testing IME.

********************************************************************/
LRESULT CALLBACK EditWndProc(HWND   hwnd,
                             UINT   message,
                             WPARAM wParam,
                             LPARAM lParam)
{
//    ShowIMEMsg(message, wParam, lParam);

    switch(message) {
    case WM_KEYDOWN:
        switch(wParam) {
        case VK_ESCAPE:
            if (!g_bCWNDactive && !g_bRWNDactive) {
                PostQuitMessage(0);
            }
            break;
        case VK_BACK:
            if (!g_bCWNDactive) {
                EditBoxBackKey();
            }
            break;
        case VK_DELETE:
            if (!g_bRWNDactive && !g_bCWNDactive) {
                EditBoxDeleteKey();
            }
            break;
        case VK_LEFT:
        case VK_RIGHT:
            if (g_bCWNDactive || g_bRWNDactive) {
                SendKeyEvents(VK_ESCAPE, 0, 0);
            }
            EditBoxMoveCaret(wParam);
            break;
        case VK_CAPITAL:
            g_hwkeybdstate.fCapsOn = GetKeyState(VK_CAPITAL) & 0x01;
            break;
        default:
            break;
        }
        break;
    case WM_CHAR:
    case WM_IME_CHAR:
        if (GetKeyState(VK_CONTROL) & 0x80) {
            return 0L;
        }

        switch(wParam) {
        case VK_BACK:
        case VK_RETURN:
        case VK_CONVERT:
            // We don't add this kind of character here.
            break;
        default:
            EditBoxAddChar((WCHAR)wParam);
            break;
        }
        return 1L;
    case WM_IME_STARTCOMPOSITION:
        g_bRWNDactive = TRUE;
        break;
    case WM_IME_ENDCOMPOSITION:
        g_bRWNDactive = FALSE;
        RWNDCleanStr();
        break;
    case WM_IME_COMPOSITION:
        if (g_bRWNDactive && (lParam & GCS_COMPSTR)) {
            RWNDUpdateStr();
        }
        break;
    case WM_IME_NOTIFY:
        switch(wParam) {
        case IMN_SETOPENSTATUS:
            SetIMEStatus();
            break;
        case IMN_SETCONVERSIONMODE:
            SetConvMode();
            break;
        case IMN_OPENCANDIDATE:
            if (CWNDGetData()) {
                g_bCWNDactive = TRUE;
                return 0L;
            }
            break;
        case IMN_CHANGECANDIDATE:
            if (g_bCWNDactive) {
                CWNDGetChange();
            }
            return 0L;
        case IMN_CLOSECANDIDATE:
            g_bCWNDactive = FALSE;
            return 0L;
        case IMN_PRIVATE:
            // This is for the incorrect spelling. In the other word,
            //   we need to show the incorrect reading string here.
            if (lParam == (DWORD)-1) {
                if (g_bRWNDactive) {
                    RWNDIncorrectInput();
                }
            }
        default:
            break;
        }
        break;
    default:
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}


/********************************************************************

Function:

    ShowIMEMsg

Description:

    Show the IME messages.

********************************************************************/
_inline
void ShowIMEMsg(UINT   message,
                WPARAM wParam,
                LPARAM lParam)
{
#ifdef DEBUG
    switch(message) {
    case WM_IME_STARTCOMPOSITION:
        DEBUGMSG(1,
            (TEXT("EDITBOX: WM_IME_STARTCOMPOSITION, wParam=0x%x, lParam=0x%x\n"),
            wParam, lParam));
        break;
    case WM_IME_ENDCOMPOSITION:
        DEBUGMSG(1,
            (TEXT("EDITBOX: WM_IME_ENDCOMPOSITION, wParam=0x%x, lParam=0x%x\n"),
            wParam, lParam));
        break;
    case WM_IME_COMPOSITION:
        DEBUGMSG(1,
            (TEXT("EDITBOX: WM_IME_COMPOSITION, wParam=0x%x, lParam=0x%x\n"),
            wParam, lParam));
        break;
    case WM_IME_CHAR:
        DEBUGMSG(1,
            (TEXT("EDITBOX: WM_IME_CHAR, wParam=0x%x, lParam=0x%x\n"),
            wParam, lParam));
        break;
    case WM_IME_SETCONTEXT:
        DEBUGMSG(1,
            (TEXT("EDITBOX: WM_IME_SETCONTEXT, wParam=0x%x,"), wParam));
        switch(lParam) {
        case ISC_SHOWUICANDIDATEWINDOW:
            DEBUGMSG(1, (TEXT(" ISC_SHOWUICANDIDATEWINDOW\n")));
            break;
        case ISC_SHOWUICOMPOSITIONWINDOW:
            DEBUGMSG(1, (TEXT(" ISC_SHOWUICANDIDATEWINDOW\n")));
            break;
        case ISC_SHOWUIGUIDELINE:
            DEBUGMSG(1, (TEXT(" ISC_SHOWUICANDIDATEWINDOW\n")));
            break;
        case ISC_SHOWUIALLCANDIDATEWINDOW:
            DEBUGMSG(1, (TEXT(" ISC_SHOWUICANDIDATEWINDOW\n")));
            break;
        case ISC_SHOWUIALL:
            DEBUGMSG(1, (TEXT(" ISC_SHOWUICANDIDATEWINDOW\n")));
            break;
        default:
            DEBUGMSG(1, (TEXT(" lParam=0x%lx\n"), lParam));
            break;
        }
        break;
    case WM_IME_NOTIFY:
        DEBUGMSG(1, (TEXT("EDITBOX: WM_IME_NOTIFY,")));
        switch(wParam) {
        case IMN_CLOSESTATUSWINDOW:
            DEBUGMSG(1, (TEXT(" IMN_CLOSESTATUSWINDOW,")));
            break;
        case IMN_OPENSTATUSWINDOW:
            DEBUGMSG(1, (TEXT(" IMN_OPENSTATUSWINDOW,")));
            break;
        case IMN_CHANGECANDIDATE:
            DEBUGMSG(1, (TEXT(" IMN_CHANGECANDIDATE,")));
            break;
        case IMN_CLOSECANDIDATE:
            DEBUGMSG(1, (TEXT(" IMN_CLOSECANDIDATE,")));
            break;
        case IMN_OPENCANDIDATE:
            DEBUGMSG(1, (TEXT(" IMN_OPENCANDIDATE,")));
            break;
        case IMN_SETCONVERSIONMODE:
            DEBUGMSG(1, (TEXT(" IMN_SETCONVERSIONMODE,")));
            break;
        case IMN_SETSENTENCEMODE:
            DEBUGMSG(1, (TEXT(" IMN_SETSENTENCEMODE,")));
            break;
        case IMN_SETOPENSTATUS:
            DEBUGMSG(1, (TEXT(" IMN_SETOPENSTATUS,")));
            break;
        case IMN_SETCANDIDATEPOS:
            DEBUGMSG(1, (TEXT(" IMN_SETCANDIDATEPOS,")));
            break;
        case IMN_SETCOMPOSITIONFONT:
            DEBUGMSG(1, (TEXT(" IMN_SETCOMPOSITIONFONT,")));
            break;
        case IMN_SETCOMPOSITIONWINDOW:
            DEBUGMSG(1, (TEXT(" IMN_SETCOMPOSITIONWINDOW,")));
            break;
        case IMN_SETSTATUSWINDOWPOS:
            DEBUGMSG(1, (TEXT(" IMN_SETSTATUSWINDOWPOS,")));
            break;
        case IMN_GUIDELINE:
            DEBUGMSG(1, (TEXT(" IMN_GUIDELINE,")));
            break;
        case IMN_PRIVATE:
            DEBUGMSG(1, (TEXT(" IMN_PRIVATE,")));
            break;
        default:
            DEBUGMSG(1, (TEXT(" wParam=0x%x,"), wParam));
            break;
        }
        DEBUGMSG(1, (TEXT(" lParam=0x%lx\n"), lParam));
        break;
    default:
        break;
    }
#endif // DEBUG
}

