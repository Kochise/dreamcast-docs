/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    editbox.cxx

Abstract:

    This file contains functions which manage a very simple output window.

Environment:

    Runs on Dreamcast under Windows CE.


-------------------------------------------------------------------*/


#include "precomp.hpp"


LPDIRECTDRAWSURFACE g_lpddsEditBox = NULL;                  // editbox's offscreen surface
HWND                g_hwndEditBox = NULL;                   // editbox's window handle
HFONT               g_hfontEditBox = NULL;                  // editbox's specified font
WCHAR               g_wszConverted[EDITBOX_MAXCHARS + 1];
BYTE                g_rgbCompositionAttributes[EDITBOX_MAXCHARS + 1];
WCHAR               g_wszNonConverted[EDITBOX_MAXCHARS + 1];
BOOL                g_fConverting;
WORD                g_xCandidateList = 0;
WORD                g_dxCandidateListWidth = 0;
WORD                g_caretpos = 0;
WORD                g_caretxcoord = 0;
DWORD               g_compositioncaret = 0;
WORD                g_totalstringwidth = 0;


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    EditBoxCreate

Description:

    This function initializes the contents of the edit box and renders the
    edit box window.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
EditBoxCreate
    (
    void
    )
{
    DDSURFACEDESC           ddsd;
    HRESULT                 hr;
    HDC                     hdc;

    // initialize the edit box to contain nothing.
    g_wszConverted[0] = TEXT('\0');
    g_wszNonConverted[0] = TEXT('\0');
    g_caretpos = 0;

    // create the editbox window
    if (!EditBoxCreateWindow()) 
        return FALSE;

    // Create offscreen surface.
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.dwWidth = EDITBOX_WIDTH;
    ddsd.dwHeight = EDITBOX_HEIGHT;       
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    hr = g_lpdd->CreateSurface (&ddsd, &g_lpddsEditBox, NULL);
    if (hr != DD_OK) {
        OutputDebugString (TEXT("Create offscreen surface failed.\r\n"));
        return FALSE;
    }

    // Create EditBox font
    g_hfontEditBox = CreateKanaFont(EDITBOX_FONTHEIGHT);

    hr = g_lpddsEditBox->GetDC (&hdc);
    if (hr != DD_OK)
        return FALSE;

    SelectObject (hdc, g_hfontEditBox);
    SetBkMode (hdc, TRANSPARENT);
    SetTextColor (hdc, KEY_TEXT_COLOR);

    hr = g_lpddsEditBox->ReleaseDC (hdc);

    if (!EditBoxRender ()) 
        return FALSE;

    return TRUE;

} // EditBoxCreate


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    AddNonConvertedCharacter

Description:

Return Value:

    None.

-------------------------------------------------------------------*/
void
AddNonConvertedCharacter 
    (
    WPARAM          wParam
    )
{
    int             cChars;
    WCHAR           wszKana[10];
    int             i;

    cChars = _tcslen (g_wszNonConverted);
    if (cChars < EDITBOX_MAXCHARS)
    {
        g_wszNonConverted[cChars] = wParam;
        g_wszNonConverted[cChars + 1] = TEXT('\0');

        if ((g_pkeybdstateCurrent->fRKCOn) && (g_pkeybdstateCurrent->fIMEOn) && 
            !(g_pkeybdstateCurrent->keyboard == ROMANJI))
        {
            for (i = 0 ; i <= cChars ; i++)
            {
                if (RKMatch (&g_wszNonConverted[i], wszKana) > 0)
                {
                    _tcscpy (&g_wszNonConverted[i], wszKana);
                    break;
                }
            }
        }

        EditBoxRender();
    }
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    EditBoxWindowProc

Description:

    This is the callback function for messages sent to the EditBox.

Return Value:

    0 if message is processed, DefWindowProc's return value otherwise.

-------------------------------------------------------------------*/
LRESULT CALLBACK 
EditBoxWindowProc
    (
    HWND            hwnd,       // handle to window
    UINT            uMsg,       // message identifier
    WPARAM          wParam,     // first message parameter
    LPARAM          lParam      // second message parameter
    )
{
    int             cChars;
//    TCHAR           chDakuten;
    HIMC            hIMC;
    DWORD           dwConvMode;
    DWORD           dwSentMode;
    DWORD           dwBufLen;
    HDC             hdcTarget;
    DWORD           i;
    BOOL            fOpen;
    LPCANDIDATELIST lpCandList;
    LPTSTR          lpStr;
    WORD            iKWNDNewFocus;
    SIZE            sizeString;
    static BOOL     fLeftCtrlPressed = FALSE;
    static BOOL     fRightCtrlPressed = FALSE;

    switch (uMsg) 
    {
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
            if (wParam == VK_CONTROL)
            {
                if (lParam & 0x1000)
                    fRightCtrlPressed = TRUE;
                else
                    fLeftCtrlPressed = TRUE;
            }

            // a clear message has been sent
    		IMEProcessVirtualKey(wParam, fLeftCtrlPressed | fRightCtrlPressed);
            break;

        case WM_KEYUP:
            if (wParam == VK_CONTROL)
            {
                if (lParam & 0x1000)
                    fRightCtrlPressed = FALSE;
                else
                    fLeftCtrlPressed = FALSE;
            }
            break;

        case WM_IME_ENDCOMPOSITION:
            memset (g_wszNonConverted, 0, sizeof(g_wszNonConverted));
            memset (g_rgbCompositionAttributes, 0, sizeof(g_rgbCompositionAttributes));
            break;

        case WM_IME_COMPOSITION:
            //DEBUGMSG(1,(L"WM_IME_COMPOSITION\r\n"));

            //
            // If fail to get input context handle then do nothing.
            // Applications should call ImmGetContext API to get
            // input context handle.
            //

            if (!(hIMC = ImmGetContext (hwnd)))
                return 0;

            memset (g_wszNonConverted, 0, sizeof(g_wszNonConverted));
            memset (g_rgbCompositionAttributes, 0, sizeof(g_rgbCompositionAttributes));

            //
            // Reads in the composition string.
            //
            if (lParam & GCS_COMPSTR)
            {
                ImmGetCompositionString( hIMC, GCS_COMPSTR, g_wszNonConverted, EDITBOX_MAXCHARS);

                if (lParam & GCS_COMPATTR)
                    ImmGetCompositionString (hIMC, GCS_COMPATTR, g_rgbCompositionAttributes, EDITBOX_MAXCHARS);
            }

            g_compositioncaret = 0xFFFF & ImmGetCompositionString( hIMC, GCS_CURSORPOS, NULL, 0);

            ImmReleaseContext (hwnd, hIMC);

            EditBoxRender();

            break;


        case WM_IME_NOTIFY:

            //DEBUGMSG(1,(L"WM_IME_NOTIFY %x\r\n",wParam));
            #if 0
            if (IMN_CLOSESTATUSWINDOW == wParam) DEBUGMSG(1,(L"IMN_CLOSESTATUSWINDOW %x\r\n",lParam));
            if (IMN_OPENSTATUSWINDOW == wParam) DEBUGMSG(1,(L"IMN_OPENSTATUSWINDOW %x\r\n",lParam));
            if (IMN_CHANGECANDIDATE == wParam) DEBUGMSG(1,(L"IMN_CHANGECANDIDATE %x\r\n",lParam));
            if (IMN_CLOSECANDIDATE == wParam) DEBUGMSG(1,(L"IMN_CLOSECANDIDATE %x\r\n",lParam));
            if (IMN_OPENCANDIDATE == wParam) DEBUGMSG(1,(L"IMN_OPENCANDIDATE %x\r\n",lParam));
            if (IMN_SETCONVERSIONMODE == wParam) DEBUGMSG(1,(L"IMN_SETCONVERSIONMODE %x\r\n",lParam));
            if (IMN_SETSENTENCEMODE == wParam) DEBUGMSG(1,(L"IMN_SETSENTENCEMODE %x\r\n",lParam));
            if (IMN_SETOPENSTATUS == wParam) DEBUGMSG(1,(L"IMN_SETOPENSTATUS %x\r\n",lParam));
            if (IMN_SETCANDIDATEPOS == wParam) DEBUGMSG(1,(L"IMN_SETCANDIDATEPOS %x\r\n",lParam));
            if (IMN_SETCOMPOSITIONFONT == wParam) DEBUGMSG(1,(L"IMN_SETCOMPOSITIONFONT %x\r\n",lParam));
            if (IMN_SETCOMPOSITIONWINDOW == wParam) DEBUGMSG(1,(L"IMN_SETCOMPOSITIONWINDOW %x\r\n",lParam));
            if (IMN_SETSTATUSWINDOWPOS == wParam) DEBUGMSG(1,(L"IMN_SETSTATUSWINDOWPOS %x\r\n",lParam));
            if (IMN_GUIDELINE == wParam) DEBUGMSG(1,(L"IMN_GUIDELINE %x\r\n",lParam));
            if (IMN_PRIVATE == wParam) DEBUGMSG(1,(L"IMN_PRIVATE %x\r\n",lParam));
            #endif

            switch (wParam)
            {
                case IMN_SETCONVERSIONMODE:
                case IMN_SETOPENSTATUS:
                    if (!(hIMC = ImmGetContext (hwnd)))
                        return 0;

                    fOpen = ImmGetOpenStatus(hIMC);
                    if (fOpen)
                    {
                        ImmGetConversionStatus(hIMC, &dwConvMode, &dwSentMode);
                        //DEBUGMSG(1,(L"ImmGetConversionStatus %x\r\n",dwConvMode));

                        g_pkeybdstateCurrent->fIMEOn = TRUE;
                        g_pkeybdstateCurrent->fRKCOn = dwConvMode & IME_CMODE_ROMAN;
                        g_pkeybdstateCurrent->keyboard = (dwConvMode & IME_CMODE_JAPANESE) ?
                            ((dwConvMode & IME_CMODE_KATAKANA) ? KATAKANA : HIRAGANA) : 
                            ROMANJI;
                        if (g_pkeybdstateCurrent->keyboard != ROMANJI)
                            g_pkeybdstateCurrent->fHalfWidth = !(dwConvMode & IME_CMODE_FULLSHAPE);
                        if (g_pkeybdstateCurrent->keyboard == ROMANJI)
                            g_pkeybdstateCurrent->fDoubleWidth = (dwConvMode & IME_CMODE_FULLSHAPE);

                        #if 0
                        if (dwConvMode == 0x19) DEBUGMSG(1, (TEXT("Roman Full Hiragana\r\n")));
                        if (dwConvMode == 0x1b) DEBUGMSG(1, (TEXT("Roman Full Katakana\r\n")));
                        if (dwConvMode == 0x18) DEBUGMSG(1, (TEXT("Roman Full Alph/Num\r\n")));
                        if (dwConvMode == 0x13) DEBUGMSG(1, (TEXT("Roman Half Katatana\r\n")));
                        if (dwConvMode == 0x10) DEBUGMSG(1, (TEXT("Roman Half Alph/Num\r\n")));
                        if (dwConvMode == 0x09) DEBUGMSG(1, (TEXT("Kana Full Hiragana\r\n")));
                        if (dwConvMode == 0x0b) DEBUGMSG(1, (TEXT("Kana Full Katakana\r\n")));
                        if (dwConvMode == 0x08) DEBUGMSG(1, (TEXT("Kana Full Alph/Num\r\n")));
                        if (dwConvMode == 0x03) DEBUGMSG(1, (TEXT("Kana Half Katakana\r\n")));
                        if (dwConvMode == 0x00) DEBUGMSG(1, (TEXT("Kana Half Alph/Num\r\n")));
                        #endif
                    }
                    else
                    {
                        g_pkeybdstateCurrent->fIMEOn = FALSE;
                    }

                    ImmReleaseContext (hwnd, hIMC);
                    break;

                case IMN_OPENCANDIDATE:

                    if (!(hIMC = ImmGetContext (hwnd)))
                        return 0;

                    if (dwBufLen = ImmGetCandidateList (hIMC, 0, NULL, 0))
                    {
                        HFONT hfontOld;

                        lpCandList = (LPCANDIDATELIST) LocalAlloc(LPTR, dwBufLen);
                        ImmGetCandidateList (hIMC, 0, lpCandList, dwBufLen);

                        #if 0
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList %x\r\n",lpCandList));
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList->dwSize %x\r\n",lpCandList->dwSize));
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList->dwStyle %x\r\n",lpCandList->dwStyle));
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList->dwCount %x\r\n",lpCandList->dwCount));
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList->dwSelection %x\r\n",lpCandList->dwSelection));
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList->dwPageStart %x\r\n",lpCandList->dwPageStart));
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList->dwPageSize %x\r\n",lpCandList->dwPageSize));
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList->dwOffset[0] %x\r\n",lpCandList->dwOffset[0]));
                        #endif

                        g_iKWNDFocus = (WORD) lpCandList->dwSelection;
                        g_cCurrentKWNDKeys = (WORD) lpCandList->dwCount;
                        g_bKWNDactive = TRUE;   // the KWND is now active
                        g_iKeyTop = (WORD) lpCandList->dwPageStart;

                        g_lpddsEditBox->GetDC (&hdcTarget);
                        hfontOld = (HFONT)SelectObject (hdcTarget, g_hfontEditBox);
                        g_dxCandidateListWidth = KWND_COLWIDTH;

                        // g_dwSelection = lpCandList->dwSelection - lpCandList->dwPageStart;
                        // g_dwCount = lpCandList->dwCount - lpCandList->dwPageStart;
                        for (i = 0; i < lpCandList->dwCount ; i++)
                        {
                            lpStr = (LPTSTR)((BYTE*) lpCandList + lpCandList->dwOffset[i]);
                            _tcsncpy (g_pskCurrentKWND[i].szKeyString, lpStr, MAX_CHARS_ON_KEY);
                            g_pskCurrentKWND[i].szKeyString[MAX_CHARS_ON_KEY] = TEXT('\0');

                            GetTextExtentPoint32 (hdcTarget, lpStr, _tcslen(lpStr), &sizeString);
                            if (sizeString.cx > g_dxCandidateListWidth)
                                g_dxCandidateListWidth = (WORD) sizeString.cx;
                        }

                        g_dxCandidateListWidth += (50 + KWND_SCROLLBARWIDTH);
                        if (g_dxCandidateListWidth > EDITBOX_WIDTH)
                            g_dxCandidateListWidth = EDITBOX_WIDTH;

                        SelectObject(hdcTarget, hfontOld);

                        g_lpddsEditBox->ReleaseDC (hdcTarget);

                        KWNDRender (g_iKeyTop);

                        LocalFree ((HANDLE)lpCandList);
                    }

                    break;

                case IMN_CHANGECANDIDATE:

                    if (!(hIMC = ImmGetContext (hwnd)))
                        return 0;

                    if (dwBufLen = ImmGetCandidateList (hIMC, 0, NULL, 0))
                    {
                        lpCandList = (LPCANDIDATELIST) LocalAlloc(LPTR, dwBufLen);
                        ImmGetCandidateList (hIMC, 0, lpCandList, dwBufLen);

                        #if 0
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList %x\r\n",lpCandList));
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList->dwSize %x\r\n",lpCandList->dwSize));
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList->dwStyle %x\r\n",lpCandList->dwStyle));
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList->dwCount %x\r\n",lpCandList->dwCount));
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList->dwSelection %x\r\n",lpCandList->dwSelection));
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList->dwPageStart %x\r\n",lpCandList->dwPageStart));
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList->dwPageSize %x\r\n",lpCandList->dwPageSize));
                        RETAILMSG(1,(L"ImmGetCandidateList lpCandList->dwOffset[0] %x\r\n",lpCandList->dwOffset[0]));
                        #endif

                        iKWNDNewFocus = (WORD) lpCandList->dwSelection;

                        if (g_iKeyTop != (WORD) lpCandList->dwPageStart)
                        {
                            g_iKeyTop = (WORD) lpCandList->dwPageStart;
                            g_iKWNDFocus = iKWNDNewFocus;
                            KWNDRender (g_iKeyTop);
                        }
                        else
                        {
                            KWNDUpdateFocusRect (g_iKeyTop, iKWNDNewFocus);   
                            g_iKWNDFocus = iKWNDNewFocus;
                        }

                        LocalFree ((HANDLE)lpCandList);
                    }

                    break;

                case IMN_CLOSECANDIDATE:
                    // unacquire the joystick
                    if (g_pdidevice2JoystickIME)
                        g_pdidevice2JoystickIME->Unacquire();

                    // set the SKB back to active
                    g_bKWNDactive = FALSE;
                    // tell the soft keyboard to reacquire the joystick
                    g_bSKBReacquireJoystick = TRUE;
                    break;
            }

            break;


/*
        case WM_IME_CHAR:

			if (g_bKWNDactive) 
                break;

            // a key has been pressed
            cChars = _tcslen (g_wszNonConverted);

            // DEBUGMSG(1, (TEXT("Received WM_CHAR 0x%x\r\n"), wParam));

            switch (wParam)
            {
                case SYMBOLS_DAKUTEN:
                    // make sure the previous character can have a dakuten
                    if ((cChars != 0) && (chDakuten = DakutenValid(g_wszNonConverted[cChars - 1])))
                    {
                        g_wszNonConverted[cChars - 1] = TEXT('\0');
                        AddNonConvertedCharacter (chDakuten);
                    }
                    else
                        // Beep!
                        ;

                    break;

                case SYMBOLS_HANDAKUTEN:
                    // make sure the previous character can have a handakuten
                    if ((cChars !=0) && (chDakuten = HandakutenValid(g_wszNonConverted[cChars - 1])))  
                    {
                        g_wszNonConverted[cChars - 1] = TEXT('\0');
                        AddNonConvertedCharacter (chDakuten);
                    }
                    else
                        // Beep!
                        ;

                    break;

                case SYMBOLS_HW_DAKUTEN:
                    // make sure the previous character can have a dakuten
                    if ((cChars != 0) && (chDakuten = DakutenValid(g_wszNonConverted[cChars - 1])))
                        AddNonConvertedCharacter (wParam);
                    else
                        // Beep!
                        ;

                    break;

                case SYMBOLS_HW_HANDAKUTEN:
                    // make sure the previous character can have a handakuten
                    if ((cChars !=0) && (chDakuten = HandakutenValid(g_wszNonConverted[cChars - 1])))  
                        AddNonConvertedCharacter (wParam);
                    else
                        // Beep!
                        ;

                    break;

                default:
                    
                    if ((wParam != 13) && (wParam != ' ')) // ignore carriage returns and spaces
                        AddNonConvertedCharacter (wParam);

                    break;
            }

            break;
*/

        case WM_CHAR:
            // a key has been pressed
            if (wParam >= TEXT(' ')) // Filter out the non printing chars.
            {
                cChars = _tcslen (g_wszConverted);
                if (cChars < EDITBOX_MAXCHARS)
                {
                    memmove (&g_wszConverted[g_caretpos + 1], &g_wszConverted[g_caretpos], 
                        (cChars - g_caretpos + 1) * sizeof(TCHAR));
                    g_wszConverted[g_caretpos++] = wParam;

                    EditBoxRender();
                }

                if (g_fHardwareKeyboardPresent)
                {
                    if (!g_pkeybdstateCurrent->fIMEOn || g_pkeybdstateCurrent->keyboard == ROMANJI)
                        g_pkeybdstateCurrent->fCapsOn = GetKeyState(VK_CAPITAL) & 0x01;
                }
            }
            break;
    }

    return (DefWindowProc(hwnd, uMsg, wParam, lParam));

}   // EditBoxWindowProc


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    EditBoxCreateWindow

Description:

    This function registers a window class, and creates a window for
    the editbox.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
EditBoxCreateWindow ()
{
    WNDCLASS            wc;

    // Set up and register window class.
    wc.style            = NULL;
    wc.lpfnWndProc      = EditBoxWindowProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = g_hinstApp;
    wc.hIcon            = NULL;
    wc.hCursor          = NULL;
    wc.hbrBackground    = NULL;
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = TEXT("editbox");
    
    if (!RegisterClass (&wc)) {
        OutputDebugString (TEXT("RegisterClass failed.\r\n"));
        return FALSE;
    }
    
    // Create the editbox window.
    g_hwndEditBox = CreateWindowEx(
        0,
        TEXT("editbox"),
        TEXT("editbox"),
        WS_VISIBLE,
        0,
        0,
        GetSystemMetrics (SM_CXSCREEN),
        GetSystemMetrics (SM_CYSCREEN),
        NULL,
        NULL,
        g_hinstApp,
        NULL);

    if (!g_hwndEditBox) {
        OutputDebugString(TEXT("EditBoxCreateWindow failed.\r\n"));
        return FALSE;
    }

    // Success!
    return TRUE;

} // EditBoxCreateWindow


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    EditBoxDestroy

Description:

    This function cleans up the editbox.

Return Value:

    none

-------------------------------------------------------------------*/
void
EditBoxDestroy
    (
    void
    )
{
    // destroy the editbox window
    if (g_hwndEditBox) 
        DestroyWindow(g_hwndEditBox);

    // release the offscreen surface
    if (g_lpddsEditBox) 
        g_lpddsEditBox->Release();

    // destroy the editbox font
    if (g_hfontEditBox)
        DeleteObject(g_hfontEditBox);
 
} // EditBoxDestroy


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    EditBoxBlt

Description:

    This function blits the editbox to the back buffer.

Return Value:

    none

-------------------------------------------------------------------*/
void
EditBoxBlt
    (
    LPDIRECTDRAWSURFACE lpDDSBack
    )
{

    RECT rc;

    rc.left = 0;
    rc.top = 0;
    rc.right = EDITBOX_WIDTH;
    rc.bottom = EDITBOX_HEIGHT;

    if (lpDDSBack)
    {
        lpDDSBack->BltFast (EDITBOX_LEFTEDGE, EDITBOX_TOPEDGE,
            g_lpddsEditBox, &rc, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
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
void
CaretBlt
    (
    LPDIRECTDRAWSURFACE lpDDSBack
    )
{
    if (g_caretxcoord < EDITBOX_WIDTH)
    {
        if (!g_fConverting && ((GetTickCount () / 500) % 2))
            DDrawFillRect (lpDDSBack, EDITBOX_LEFTEDGE + g_caretxcoord, EDITBOX_TOPEDGE + 2, 
                2, EDITBOX_HEIGHT - 2, BLUE);
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
BOOL
EditBoxRender
    (
    void
    )
{  
    HDC                         hdcTarget;
    SIZE                        sizeConverted;
    SIZE                        sizeConvertedTotal;
    SIZE                        sizeNonConverted;
    HRESULT                     hr;
    WORD                        curpos;
    SIZE                        sizeOneChar;
    int                         ich;
    UINT                        ch;
    UINT                        dummy;
    HFONT                       hfontOld;

    // Render the InWindow background.
    if (!DDrawFillRect (g_lpddsEditBox, 0, 0, 
        EDITBOX_WIDTH, EDITBOX_HEIGHT, EDITBOX_BKGNDCOLOR))
        return FALSE;

    // Draw the key
    if (!RenderBlankKey (g_lpddsEditBox, 0, 0, EDITBOX_WIDTH, EDITBOX_HEIGHT))
        return FALSE;

    // Draw the characters
    hr = g_lpddsEditBox->GetDC (&hdcTarget);
    if (hr != DD_OK)
        return FALSE;

    hfontOld = (HFONT)SelectObject (hdcTarget, g_hfontEditBox);
    SetBkMode (hdcTarget, TRANSPARENT);

    GetTextExtentPoint32 (hdcTarget, g_wszConverted, g_caretpos, &sizeConverted);
    GetTextExtentPoint32 (hdcTarget, g_wszConverted, _tcslen(g_wszConverted), &sizeConvertedTotal);
    GetTextExtentPoint32 (hdcTarget, g_wszNonConverted, _tcslen(g_wszNonConverted), &sizeNonConverted);

    // Don't let the user type more than the editbox can hold.
    // Backspace the last character typed.
    if (sizeConvertedTotal.cx + sizeNonConverted.cx > EDITBOX_WIDTH)
    {
        ch = ' ';
        PostKeybdMessage((HWND) -1, VK_BACK, KeyStateDownFlag, 0, &dummy, &ch);
    }

    ExtTextOut (hdcTarget, EDITBOX_MARGIN, EDITBOX_MARGIN, 0, NULL, g_wszConverted, 
        g_caretpos, NULL);

    SetBkMode (hdcTarget, OPAQUE);
    curpos = sizeConverted.cx + EDITBOX_MARGIN;
    g_caretxcoord = curpos;
    g_fConverting = (g_wszNonConverted[0] > 0);
    g_xCandidateList = 0;
    for (ich = 0 ; g_wszNonConverted[ich] ; ich++)
    {
        if ((DWORD) ich == g_compositioncaret)
            g_caretxcoord = curpos;

        switch (g_rgbCompositionAttributes[ich])
        {
            case ATTR_INPUT:
                g_fConverting = FALSE;
                SetBkColor(hdcTarget, RGB( 192, 192, 192));
                break;
            case ATTR_TARGET_CONVERTED:
                if (g_xCandidateList == 0)
                    g_xCandidateList = curpos + EDITBOX_LEFTEDGE;
                SetBkColor(hdcTarget, RGB(  0, 255,   0));
                break;
            case ATTR_CONVERTED:
                SetBkColor(hdcTarget, RGB(  0, 255, 255));
                break;
            case ATTR_TARGET_NOTCONVERTED:
                g_fConverting = FALSE;
                SetBkColor(hdcTarget, RGB(255, 255,   0));
                break;
            case ATTR_INPUT_ERROR:
                SetBkColor(hdcTarget, RGB(255,   0,   0));
                break;
        }

        ExtTextOut (hdcTarget, curpos, EDITBOX_MARGIN, 0, NULL, 
            &g_wszNonConverted[ich], 1, NULL);
        GetTextExtentPoint32 (hdcTarget, &g_wszNonConverted[ich], 1, &sizeOneChar);
        curpos += (WORD) sizeOneChar.cx;
    }
    
    if (_tcslen(g_wszNonConverted) == g_compositioncaret)
        g_caretxcoord = curpos;

    SetBkMode (hdcTarget, TRANSPARENT);
    ExtTextOut (hdcTarget, curpos, EDITBOX_MARGIN, 0, NULL, &g_wszConverted[g_caretpos], 
        _tcslen(g_wszConverted) - g_caretpos, NULL);

    SelectObject(hdcTarget, hfontOld);

    hr = g_lpddsEditBox->ReleaseDC (hdcTarget);

    // Draw the underline.
    if ((sizeConverted.cx < EDITBOX_WIDTH - 2*EDITBOX_MARGIN) && (sizeNonConverted.cx > 0))
    {
        // Make sure we don't draw past the right edge of the edit box.
        if ((sizeConverted.cx + sizeNonConverted.cx) > EDITBOX_WIDTH - 2*EDITBOX_MARGIN)
            sizeNonConverted.cx = EDITBOX_WIDTH - 2*EDITBOX_MARGIN - sizeConverted.cx;

        if (!DDrawFillRect (g_lpddsEditBox, sizeConverted.cx + EDITBOX_MARGIN, EDITBOX_HEIGHT - 5, 
            sizeNonConverted.cx, 1, BLUE))
            return FALSE;
    }

    return TRUE;

} // EditBoxRender
