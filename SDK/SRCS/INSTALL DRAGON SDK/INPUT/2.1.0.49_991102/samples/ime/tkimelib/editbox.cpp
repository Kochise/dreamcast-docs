/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    editbox.cxx

Abstract:

    This file contains functions which manage a very simple output window.

Environment:

    Runs on Dreamcast under Windows CE.


-------------------------------------------------------------------*/


#include "precomp.hxx"


LPDIRECTDRAWSURFACE  g_lpddsEditBox = NULL;                  // editbox's offscreen surface
HWND                 g_hwndEditBox = NULL;                   // editbox's window handle
HFONT                g_hfontEditBox = NULL;
WCHAR                g_wszConverted[EDITBOX_MAXCHARS + 1];
WCHAR                g_wszNonConverted[EDITBOX_MAXCHARS + 1];
WORD                 g_xCandidateList = 0;
WORD                 g_caretpos = 0;
WORD                 g_caretxcoord = 0;
WORD                 g_compositioncaret = 0;


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
    DDSURFACEDESC          ddsd;
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
    int             iTotalSize;
	HDC hdcTarget;
    SIZE sizeConverted, sizeNonConverted, sizeChar;
	HRESULT hr;
	TCHAR wszChar[2];
    HFONT hfontOld;

	// send IME char
	hr = g_lpddsEditBox->GetDC (&hdcTarget);
    if (hr == DD_OK)
	{
	    hfontOld = (HFONT)SelectObject (hdcTarget, g_hfontEditBox);

		GetTextExtentPoint32 (hdcTarget, g_wszNonConverted, _tcslen(g_wszNonConverted),
			&sizeNonConverted);
		GetTextExtentPoint32 (hdcTarget, g_wszConverted, _tcslen(g_wszConverted),
			&sizeConverted);

		wszChar[0] = wParam;
		wszChar[1] = TEXT('\0');

		GetTextExtentPoint32 (hdcTarget, wszChar, _tcslen(wszChar),
			&sizeChar);
    
        SelectObject(hdcTarget, hfontOld);

	    hr = g_lpddsEditBox->ReleaseDC (hdcTarget);

		iTotalSize = sizeConverted.cx + sizeNonConverted.cx + 2 * EDITBOX_MARGIN + CARET_WIDTH + sizeChar.cx;

		if(iTotalSize <= EDITBOX_WIDTH)
		{
		    cChars = _tcslen (g_wszNonConverted);

		    if (cChars < EDITBOX_MAXCHARS)
			{
				if(cChars == 0) // new non converted space
				{
					g_compositioncaret = g_caretpos;
				}

				cChars++;

				memmove (&g_wszNonConverted[g_caretpos - g_compositioncaret + 1], &g_wszNonConverted[g_caretpos - g_compositioncaret],
					(cChars - (g_caretpos - g_compositioncaret)) * sizeof(TCHAR));

				g_wszNonConverted[g_caretpos - g_compositioncaret] = wParam;

				g_caretpos++; // must adjust, based on rkc

#ifdef KANJI
		        if ((g_pkeybdstateCurrent->fRKCOn) && (g_pkeybdstateCurrent->fIMEOn) && 
				    !(g_pkeybdstateCurrent->keyboard == ROMANJI))
		        {
                    int     i;
                    SIZE    sizeKana;
                    WCHAR   wszKana[10];
                    WCHAR   wszKatakana[10];

				    for (i = 0 ; i < cChars ; i++)
		            {
				        if (RKMatch (&g_wszNonConverted[i], wszKana) > 0)
						{
		                    if (g_pkeybdstateCurrent->keyboard == KATAKANA)
				            {
						        ConvertToKatakana (wszKana, wszKatakana);
								_tcscpy (wszKana, wszKatakana);
		                    }

							// must check again to make sure new kana doesn't extend past edit window
							hr = g_lpddsEditBox->GetDC (&hdcTarget);
						    if (hr == DD_OK)
							{
								hfontOld = (HFONT)SelectObject (hdcTarget, g_hfontEditBox);

								GetTextExtentPoint32 (hdcTarget, g_wszNonConverted, i,
									&sizeNonConverted);
								GetTextExtentPoint32 (hdcTarget, g_wszConverted, _tcslen(g_wszConverted),
									&sizeConverted);

								GetTextExtentPoint32 (hdcTarget, wszKana, _tcslen(wszKana),
									&sizeKana);
    
                                SelectObject(hdcTarget, hfontOld);

								hr = g_lpddsEditBox->ReleaseDC (hdcTarget);

								iTotalSize = sizeConverted.cx + sizeNonConverted.cx + 2 * EDITBOX_MARGIN + CARET_WIDTH + sizeKana.cx;

								if(iTotalSize <= EDITBOX_WIDTH)
								{
									_tcscpy (&g_wszNonConverted[i], wszKana);
									g_caretpos = g_compositioncaret + _tcslen (g_wszNonConverted);
								}
							}
						    break;
		                }
				    }
		        }

				EditBoxRender();
#endif  // KANJI
			}
		}
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
#ifdef KANJI
    TCHAR           chDakuten;
#endif

    switch (uMsg) 
    {
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
            // a clear message has been sent
    		IMEProcessVirtualKey(wParam);
            break;

        case WM_CHAR:
#ifdef KANJI
			if (g_bKWNDactive)
			{
                int iKeyCurrent;
                KWNDKEY     *psk;
                SIZE sizeConverted, sizeChar;
                HDC hdcTarget;
                HRESULT hr;
                TCHAR wszChar[2];

				// ASCII '1' to '9' represent Kanji selections in the candidate window
				if(wParam >= L'1' && wParam <= L'9')
				{
					if((iKeyCurrent = g_iKeyTop + wParam - L'1') >= g_cCurrentKWNDKeys)
						break;

					if((psk = &g_pskCurrentKWND[iKeyCurrent]) != NULL)
					{
						// unacquire the joystick
						if (g_pdidevice2JoystickIME)
			                g_pdidevice2JoystickIME->Unacquire();

						// set the SKB back to active
						g_bKWNDactive = FALSE;
						// tell the soft keyboard to reacquire the joystick
						g_bSKBReacquireJoystick = TRUE;

						if(iKeyCurrent == 0)
						{
							// same characters on kwnd key means pass through
					        memmove (&g_wszConverted[g_compositioncaret + _tcslen (g_wszNonConverted)],
								&g_wszConverted[g_compositioncaret],
								(_tcslen (g_wszConverted) - g_compositioncaret + 1) * sizeof(TCHAR));
					        memmove (&g_wszConverted[g_compositioncaret], g_wszNonConverted,
								_tcslen (g_wszNonConverted) * sizeof(TCHAR));

							// clear the IME window
					        g_wszNonConverted[0] = TEXT('\0');
							EditBoxRender();
						}
						else
						{
							// Draw the characters

							// clear the IME window
			                g_wszNonConverted[0] = TEXT('\0');
							g_caretpos = g_compositioncaret;

							// send IME char
							hr = g_lpddsEditBox->GetDC (&hdcTarget);
						    if (hr == DD_OK)
							{
                                HFONT           hfontOld;

							    hfontOld = (HFONT)SelectObject (hdcTarget, g_hfontEditBox);

								GetTextExtentPoint32 (hdcTarget, g_wszConverted, _tcslen(g_wszConverted),
									&sizeConverted);

								wszChar[0] = psk->szKeyString[0];
								wszChar[1] = TEXT('\0');

								GetTextExtentPoint32 (hdcTarget, wszChar, _tcslen(wszChar),
									&sizeChar);
    
                                SelectObject(hdcTarget, hfontOld);

							    hr = g_lpddsEditBox->ReleaseDC (hdcTarget);

								if(sizeConverted.cx + 2 * EDITBOX_MARGIN + CARET_WIDTH + sizeChar.cx <= EDITBOX_WIDTH)
									PostMessage(g_hwndApp, WM_IME_CHAR, psk->szKeyString[0], 0);
							}
						    EditBoxRender();
						}
					}
				}
                break;
			}
#endif  // KANJI

            // a key has been pressed
            cChars = _tcslen (g_wszNonConverted);

            // DEBUGMSG(1, (TEXT("Received WM_CHAR 0x%x\r\n"), wParam));

#ifdef KANJI
            switch (wParam)
            {
                case SYMBOLS_DAKUTEN:
                    // make sure the previous character can have a dakuten
                    if ((cChars != 0) && (g_caretpos > g_compositioncaret) &&
						(chDakuten = DakutenValid(g_wszNonConverted[g_caretpos - g_compositioncaret - 1])))
                    {
                        g_wszNonConverted[g_caretpos - g_compositioncaret - 1] = chDakuten;
						EditBoxRender();
                        //AddNonConvertedCharacter (chDakuten);
                    }
                    else
                        AddNonConvertedCharacter (wParam);

                    break;

                case SYMBOLS_HANDAKUTEN:
                    // make sure the previous character can have a handakuten
                    if ((cChars !=0) && (g_caretpos > g_compositioncaret) &&
						(chDakuten = HandakutenValid(g_wszNonConverted[g_caretpos - g_compositioncaret - 1])))  
                    {
                        g_wszNonConverted[g_caretpos - g_compositioncaret - 1] = chDakuten;
						EditBoxRender();
                        //AddNonConvertedCharacter (chDakuten);
                    }
                    else
                        AddNonConvertedCharacter (wParam);

                    break;

                case SYMBOLS_HW_DAKUTEN:
                    // make sure the previous character can have a dakuten
                    AddNonConvertedCharacter (wParam);
                    break;

                case SYMBOLS_HW_HANDAKUTEN:
                    // make sure the previous character can have a handakuten
                    AddNonConvertedCharacter (wParam);
                    break;

                default:
                    if (wParam > ' ' && wParam != 0x3000) // ignore carriage return, tab, esc, backspace, space, and wide space
                        AddNonConvertedCharacter (wParam);

                    break;
            }
#else
            if (wParam > ' ' && wParam != 0x3000) // ignore carriage return, tab, esc, backspace, space, and wide space
            {
                AddNonConvertedCharacter (wParam);
				// we were on the Romanji keyboard, so just pass these characters through
	            memmove (&g_wszConverted[g_compositioncaret + _tcslen (g_wszNonConverted)],
					&g_wszConverted[g_compositioncaret],
					(_tcslen (g_wszConverted) - g_compositioncaret + 1) * sizeof(TCHAR));
	            memmove (&g_wszConverted[g_compositioncaret], g_wszNonConverted,
					_tcslen (g_wszNonConverted) * sizeof(TCHAR));

                // clear the IME window
                g_wszNonConverted[0] = TEXT('\0');
		        EditBoxRender();
            }

#endif
            if (g_fHardwareKeyboardPresent)
            {
                if (!g_pkeybdstateCurrent->fIMEOn)
                    g_pkeybdstateCurrent->fCapsOn = GetKeyState(VK_CAPITAL) & 0x01;
            }
            break;

        case WM_IME_CHAR:
            // a key has been pressed
            cChars = _tcslen (g_wszConverted);
            if (cChars < EDITBOX_MAXCHARS)
            {
				// change caret
	            memmove (&g_wszConverted[g_caretpos + 1], &g_wszConverted[g_caretpos],
		            (cChars - g_caretpos + 1) * sizeof(TCHAR));
			    g_wszConverted[g_caretpos++] = wParam;
				EditBoxRender();
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
    {
        DestroyWindow(g_hwndEditBox);
        g_hwndEditBox = NULL; 
    }

    // release the offscreen surface
    if (g_lpddsEditBox) 
    {
        g_lpddsEditBox->Release();
        g_lpddsEditBox = NULL;
    }
 
    // destroy the editbox font
    if (g_hfontEditBox) {
        DeleteObject(g_hfontEditBox);
        g_hfontEditBox = NULL;
    }
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
    if (/*!g_fConverting && */((GetTickCount () / 500) % 2))
        DDrawFillRect (lpDDSBack, EDITBOX_LEFTEDGE + g_caretxcoord, EDITBOX_TOPEDGE + 2,
            CARET_WIDTH, EDITBOX_HEIGHT - 2, BLUE);
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
    SIZE                        sizeNonConverted;
    SIZE                        sizeCaretPos;
    HRESULT                     hr;
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

	if(_tcslen(g_wszNonConverted) == 0)
	{
		GetTextExtentPoint32 (hdcTarget, g_wszConverted, _tcslen(g_wszConverted), &sizeConverted);

		ExtTextOut (hdcTarget, EDITBOX_MARGIN, EDITBOX_MARGIN, 0, NULL, g_wszConverted, 
			_tcslen(g_wszConverted), NULL);

		sizeNonConverted.cx = sizeNonConverted.cy = 0;

		GetTextExtentPoint32 (hdcTarget, g_wszConverted, g_caretpos, &sizeCaretPos);
		g_caretxcoord = sizeCaretPos.cx + EDITBOX_MARGIN;

		g_xCandidateList = g_caretxcoord + EDITBOX_LEFTEDGE;
	}
	else
	{
		GetTextExtentPoint32 (hdcTarget, g_wszConverted, g_compositioncaret, &sizeConverted);

		ExtTextOut (hdcTarget, EDITBOX_MARGIN, EDITBOX_MARGIN, 0, NULL, g_wszConverted, 
			g_compositioncaret, NULL);

		GetTextExtentPoint32 (hdcTarget, g_wszNonConverted, _tcslen(g_wszNonConverted), &sizeNonConverted);

		ExtTextOut (hdcTarget, sizeConverted.cx + EDITBOX_MARGIN, EDITBOX_MARGIN, 0, NULL, 
			g_wszNonConverted, _tcslen(g_wszNonConverted), NULL);

		//GetTextExtentPoint32 (hdcTarget, g_wszConverted + g_compositioncaret, _tcslen(g_wszConverted) - g_compositioncaret, &sizeConverted);

		ExtTextOut (hdcTarget, sizeNonConverted.cx + sizeConverted.cx + EDITBOX_MARGIN, EDITBOX_MARGIN, 0,
			NULL, g_wszConverted + g_compositioncaret, _tcslen(g_wszConverted) - g_compositioncaret, NULL);

		GetTextExtentPoint32 (hdcTarget, g_wszNonConverted, g_caretpos - g_compositioncaret, &sizeCaretPos);
		g_caretxcoord = sizeConverted.cx + sizeCaretPos.cx + EDITBOX_MARGIN;

		g_xCandidateList = sizeConverted.cx + EDITBOX_MARGIN + EDITBOX_LEFTEDGE;
	}
    
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
