/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    imeui.cxx

Abstract:

    This file contains functions which manage the Input Method Editor (IME)
    user interface window.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hxx"


#ifdef KANJI
HTK                 g_htk = NULL;                  // handle to tankanji library
TCHAR               g_szKanji[MAX_KANJI+1];        // string for kana-kanji translation
TCHAR               g_szHiragana[256];             // string for kana-kanji translation
unsigned short		g_iKeyTop = 0;				   // the top displayed row of the scrolling
                                                   // kanji selection window
#endif  // KANJI

#include "inputkwnd.h"


#ifdef KANJI
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IMECreate

Description:

    This function initializes the contents of the IME, creates the direct 
    input for the IME, creates the kanji selection window, and renders the
    IME window.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
IMECreate
    (
    void
    )
{
    // open tankanji library

    // the following lines of code provide examples of how to load the dictionary from
    // either the image, the cd-rom, or the resources.  the default uncommented line loads
    // the dictionary as a resource.

    // load tankanji dictionary as a file from the image
    // g_htk = TKOpen(L"\\windows\\tankanji.dic");

    // load tankanji dictionary as a file from the cd-rom
    // g_htk = TKOpen(L"\\cd-rom\\tankanji.dic");

    // load tankanji dictionary as a resource
    g_htk = TKOpen(TANKANJI_DICTIONARY_NAME);

    if (!g_htk) {
        OutputDebugString (TEXT("Open Tankanji library failed.\r\n"));
        OutputDebugString (TEXT("Make sure the dictionary file \"tankanji.dic\" is in the image.\r\n"));
        OutputDebugString (TEXT("To do this, type 'set IMGTKIME=1', then run 'dragimg'.\r\n"));
        return(0);
    }

    // create the direct input but don't acquire it
    if (!IME_CreateDirectInput(g_hinstApp, g_hwndApp, &g_pdidevice2JoystickIME)) 
    {
        // this is not an error; maybe the joystick is unplugged.  the IME will
        // continuously try to find a joystick.
    }

    // create the kanji window
    if (!KWNDCreate ())
    {
        return 0;
    }

    if (!EditBoxRender ())
    {
        return(FALSE);
    }

    return(TRUE);

} // IMECreate
#endif  // KANJI


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IMEProcessVirtualKey

Description:

    This function processes a virtual key message.

Return Value:
    none.

-------------------------------------------------------------------*/
void 
IMEProcessVirtualKey
    (
    TCHAR wcKey
    )
{
    WORD       nNCCaretPos;
#ifdef KANJI
	DIJOYSTATE dijoystate;  // a dummy dijoystate to pass to the KWNDProcessXMovement and
							// KWNDProcessYMovement functions if arrow keys are pressed
    KWNDKEY		*psk;	    // also for ProcessMovement functions
    SWNDKEY		*psk2;	    // also for ProcessMovement functions
    int iKeyCurrent;
#endif  // KANJI
    int cChars;
	HDC hdcTarget;
	SIZE sizeConverted, sizeChar;
	HRESULT hr;
	TCHAR wszChar[2];

    switch (wcKey)
    {
        case VK_END:
#ifdef KANJI
			if (g_bKWNDactive)
			{
				// if the user presses "End" with the candidate list window open,
				// the list will look the same as if they had arrowed to the bottom
				if(g_cCurrentKWNDKeys - 2 < 0)
					g_iKeyTop = 0;
				else
					g_iKeyTop = ((g_cCurrentKWNDKeys - 2) / 8) * 8;

				g_yKWNDCursor = g_iKWNDFocus = g_cCurrentKWNDKeys - 1;
				KWNDRender(g_iKeyTop);
			}
            else
#endif  // KANJI
			{
				if(_tcslen (g_wszNonConverted) == 0)
				{
					g_caretpos = _tcslen (g_wszConverted);
				}
				else
				{
					g_caretpos = g_compositioncaret + _tcslen (g_wszNonConverted);
				}
				EditBoxRender();
			}
            break;

        case VK_HOME:
#ifdef KANJI
			if (g_bKWNDactive)
			{
				g_iKeyTop = g_yKWNDCursor = g_iKWNDFocus = 0;
				KWNDRender(g_iKeyTop);
			}
            else
#endif  // KANJI
			{
				if(_tcslen (g_wszNonConverted) == 0)
				{
		            g_caretpos = 0;
				}
				else
				{
					g_caretpos = g_compositioncaret;
				}
	            EditBoxRender();
			}
            break;

        case VK_BACK:
#ifdef KANJI
			if (g_bKWNDactive) 
			{
				// unacquire the joystick
				if (g_pdidevice2JoystickIME)
                    g_pdidevice2JoystickIME->Unacquire();

				// set the SKB back to active
				g_bKWNDactive = FALSE;
				// tell the soft keyboard to reacquire the joystick
				g_bSKBReacquireJoystick = TRUE;

				// the user rejected all of the kanji
				// PostMessage(g_hwndApp, WM_IME_CHAR, REJECT, 0);
			}	
            else
#endif  // KANJI
			{
	            // delete the character before the caret, move the caret back
	            if (_tcslen (g_wszNonConverted) == 0)
		        {
					if (g_caretpos > 0)
					{
						memmove (&g_wszConverted[g_caretpos - 1], &g_wszConverted[g_caretpos], 
							(_tcslen(g_wszConverted) - g_caretpos + 1) * sizeof(TCHAR));
						g_caretpos--;
						EditBoxRender();
					}
				}
	            else
		        {
					if(g_caretpos > g_compositioncaret)
					{
						nNCCaretPos = g_caretpos - g_compositioncaret;
						memmove (&g_wszNonConverted[nNCCaretPos - 1], &g_wszNonConverted[nNCCaretPos], 
							(_tcslen(g_wszNonConverted) - nNCCaretPos + 1) * sizeof(TCHAR));
				        g_caretpos--;
					    EditBoxRender();
					}
				}
			}
            break;

        case VK_DELETE:
#ifdef KANJI
            if (!g_bKWNDactive)
#endif  // KANJI
			{
	            // delete the character at the caret
		        DEBUGMSG(1, (TEXT("Received VK_BACK")));
			    if (_tcslen (g_wszNonConverted) == 0)
				{
					if (g_caretpos < _tcslen(g_wszConverted))
					{
						memmove (&g_wszConverted[g_caretpos], &g_wszConverted[g_caretpos + 1], 
							(_tcslen(g_wszConverted) - g_caretpos) * sizeof(TCHAR));
						EditBoxRender();
					}
				}
				else
				{
					if ((nNCCaretPos = g_caretpos - g_compositioncaret) < _tcslen(g_wszNonConverted))
					{
						memmove (&g_wszNonConverted[nNCCaretPos], &g_wszNonConverted[nNCCaretPos + 1], 
							(_tcslen(g_wszNonConverted) - nNCCaretPos) * sizeof(TCHAR));
						EditBoxRender();
					}
				}
			}
            break;

        case VK_CLEAR:
#ifdef KANJI
            if (!g_bKWNDactive)
#endif  // KANJI
			{
	            g_wszConverted[0] = TEXT('\0');
		        g_wszNonConverted[0] = TEXT('\0');
			    g_caretpos = 0;

				EditBoxRender ();
			}
            break;

        case VK_NOCONVERT:
#ifdef KANJI
            if (!g_bKWNDactive)
#endif  // KANJI
			{
	            // we don't want to convert to kanji, just pass through the characters
		        memmove (&g_wszConverted[g_compositioncaret + _tcslen (g_wszNonConverted)],
					&g_wszConverted[g_compositioncaret],
					(_tcslen (g_wszConverted) - g_compositioncaret + 1) * sizeof(TCHAR));
	            memmove (&g_wszConverted[g_compositioncaret], g_wszNonConverted,
					_tcslen (g_wszNonConverted) * sizeof(TCHAR));

			    // clear the IME window
				g_wszNonConverted[0] = TEXT('\0');
			    EditBoxRender();
			}
            break;

        case VK_ESCAPE:
#ifdef KANJI
			if (g_bKWNDactive) 
			{
				// unacquire the joystick
				if (g_pdidevice2JoystickIME)
                    g_pdidevice2JoystickIME->Unacquire();

				// set the SKB back to active
				g_bKWNDactive = FALSE;
				// tell the soft keyboard to reacquire the joystick
				g_bSKBReacquireJoystick = TRUE;

				// the user rejected all of the kanji
				// PostMessage(g_hwndApp, WM_IME_CHAR, REJECT, 0);
			}	
			else if (g_bSWNDactive)
			{
				// close swnd
	            g_bSWNDactive = FALSE;
			}
            else
#endif  // KANJI
            {
    			PostQuitMessage(0);
            }	
			break;

        case VK_RETURN:
#ifdef KANJI
			if (g_bKWNDactive)
			{
				iKeyCurrent = KWNDFindKeyUnderCursor();

				if (iKeyCurrent == 0xffff) 
				{
					psk = NULL;
				} else {
					psk = &g_pskCurrentKWND[iKeyCurrent];
				}
 
				if (psk != NULL) 
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
						// clear the IME window
			            g_wszNonConverted[0] = TEXT('\0');
						g_caretpos = g_compositioncaret;

						// send IME char
						hr = g_lpddsEditBox->GetDC (&hdcTarget);
					    if (hr == DD_OK)
						{
                            HFONT hfontOld;

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
			else if (g_bSWNDactive)
			{
				// select symbol
		        iKeyCurrent = SWNDFindKeyUnderCursor();
				if (iKeyCurrent == 0xffff) 
		        {
				    psk2 = NULL;
		        } else {
				    psk2 = &g_pskCurrentSWND[iKeyCurrent];
		        }

	            if (psk2 != NULL) 
		        {
                    // this hack is ok, since we won't be using char KANJI_REJECT_0 in the SWND
                            if (psk2->szKeyString[0] == KANJI_REJECT_0)
					{
						// the user rejected all of the kanji
	                    // PostMessage(g_hwndCallingAppSWND, WM_CHAR, REJECT, 0);
		                // close swnd
			            g_bSWNDactive = FALSE;
					} else {
						PostMessage(g_hwndApp, WM_CHAR, psk2->szKeyString[0], 0); 
		            }        
			    }    
			}
            else    // KWND is not active
            {
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
#endif  // KANJI
            break;

        case VK_SPACE:
#ifdef KANJI
            if (g_bKWNDactive)
			{
				// same as VK_DOWN
				// init dijoystate
				dijoystate.lX = 0; dijoystate.lY = 0;
				psk = NULL;
				do
	            {
		            psk = KWNDProcessYMovement(dijoystate, psk, &g_iKeyTop, FORWARD);
			    } while (psk == NULL);
				break;
			}
            else
#endif  // KANJI
            {
				if (_tcslen(g_wszNonConverted) == 0)
				{
					// insert a space into the IME
					hr = g_lpddsEditBox->GetDC (&hdcTarget);
				    if (hr == DD_OK)
					{
                        HFONT hfontOld;

					    hfontOld = (HFONT)SelectObject (hdcTarget, g_hfontEditBox);

						GetTextExtentPoint32 (hdcTarget, g_wszConverted, _tcslen(g_wszConverted),
							&sizeConverted);
                                                
                        if (g_pkeybdstateCurrent->fDoubleWidth || !g_pkeybdstateCurrent->fHalfWidth)
                                                {
                                                        wszChar[0] = 0x3000;    //Double Width Space
                                                }
                                                else 
                                                {
                                 			wszChar[0] = wcKey;     //Single Width Space
                                                }
						wszChar[1] = TEXT('\0');

						GetTextExtentPoint32 (hdcTarget, wszChar, _tcslen(wszChar),
							&sizeChar);
    
                        SelectObject(hdcTarget, hfontOld);

					    hr = g_lpddsEditBox->ReleaseDC (hdcTarget);

						if(sizeConverted.cx + 2 * EDITBOX_MARGIN + CARET_WIDTH + sizeChar.cx <= EDITBOX_WIDTH)
						{
							cChars = _tcslen(g_wszConverted);
							memmove (&g_wszConverted[g_caretpos + 1], &g_wszConverted[g_caretpos],
								(cChars - g_caretpos + 1) * sizeof(TCHAR));
							g_wszConverted[g_caretpos++] = wcKey;
							EditBoxRender();
						}
					}
					break;
				}
			}

#ifdef KANJI
        case VK_CONVERT:
			if (!g_bKWNDactive)
            {
	            // The Tankanji IME engine requires the string passed in to be
		        // Hiragana only.
			    ConvertToHiragana (g_wszNonConverted, g_szHiragana);

				if (IsHiragana (g_szHiragana)) 
	            {
					if((cChars = _tcslen(g_wszNonConverted)) > MAX_IMECHARS_ON_KEY)
						cChars = MAX_IMECHARS_ON_KEY;

					memmove(g_pskCurrentKWND[0].szKeyString, g_wszNonConverted, cChars * sizeof(TCHAR));
					g_pskCurrentKWND[0].szKeyString[cChars] = TEXT('\0');

                    // Special case for period, comma and dash
                    cChars = _tcslen (g_wszNonConverted);

                    if (cChars == 1 && g_szHiragana[0] == SYMBOLS_IDEO_PERIOD) {
                        g_szKanji[0] = SYMBOLS_FW_PERIOD;
                        g_szKanji[1] = '\0';
                    } else if (cChars == 1 && g_szHiragana[0] == SYMBOLS_IDEO_COMMA) {
                        g_szKanji[0] = SYMBOLS_FW_COMMA;
                        g_szKanji[1] = '\0';
                    } else if (cChars == 1 && g_szHiragana[0] == SYMBOLS_JAPANESE_DASH) {
                        g_szKanji[0] = SYMBOLS_FW_DASH;
                        g_szKanji[1] = '\0';
                    } else {
	                    // convert the inputted kana into tankanji
                        g_szKanji[0] = '\0';
                        TKMatch(g_htk, g_szHiragana, MAX_KANJI, g_szKanji);
                    }

				    // put the returned kanji characters into the KWND
                    WORD i=0;
	                while (g_szKanji[i] != '\0')
		            {
			            g_pskCurrentKWND[i + 1].szKeyString[0] = g_szKanji[i];
				        g_pskCurrentKWND[i + 1].szKeyString[1] = '\0';
					    i++;
	                }

		            // calculate number of active keys in kanji selection window
			        g_cCurrentKWNDKeys = _tcslen(g_szKanji) + 1;

				    // reset the kanji selection window cursor to 0
					g_xKWNDCursor = 0;
	                g_yKWNDCursor = 0;
		            g_iKWNDFocus = 0;
			        g_bKWNDactive = TRUE;   // the KWND is now active

	                // Acquire the joystick.  This allows us to read its state.
		            if (!AcquireJoystick(&g_pdidevice2JoystickIME))
			        {
				        return;
					}
	            }
		        else
#endif  // KANJI
			    { 
				    // the kana wasn't all hiragana, so just send a separate WM_IME_CHAR
					// message for every character in the string
		            memmove (&g_wszConverted[g_compositioncaret + _tcslen (g_wszNonConverted)],
						&g_wszConverted[g_compositioncaret],
						(_tcslen (g_wszConverted) - g_compositioncaret + 1) * sizeof(TCHAR));
				    memmove (&g_wszConverted[g_compositioncaret], g_wszNonConverted,
						_tcslen (g_wszNonConverted) * sizeof(TCHAR));

                    // clear the IME window
	                g_wszNonConverted[0] = TEXT('\0');
			        EditBoxRender();

	                // let the SKB know that it should reacquire the joystick, since we don't
		            // need it
			        g_bSKBReacquireJoystick = TRUE;
                }
#ifdef KANJI
            }
#endif  // KANJI

            break;      

        case VK_LEFT:
#ifdef KANJI
			// don't process the arrow keys if the ime is not active
			if (g_bKWNDactive)
			{
				// init dijoystate
				dijoystate.lX = 0; dijoystate.lY = 0;
				psk = NULL;
	            do
		        {
			        psk = KWNDProcessXMovement(dijoystate, psk, &g_iKeyTop, BACK);
				} while (psk == NULL);
			}
			else if (g_bSWNDactive)
			{
				// init dijoystate
				dijoystate.lX = 0; dijoystate.lY = 0;
				psk2 = NULL;
	            do
		        {
			        psk2 = SWNDProcessXMovement(dijoystate, psk2, &g_iSWNDKeyTop, BACK);
				} while (psk2 == NULL);
			}
            else
#endif  // KANJI
            {
	            if (_tcslen (g_wszNonConverted) == 0)
		        {
					if (g_caretpos > 0)
						g_caretpos--;
				}
				else
				{
					if (g_caretpos > g_compositioncaret)
						g_caretpos--;
				}
				EditBoxRender();
			}
			break;

        case VK_RIGHT:
#ifdef KANJI
			// don't process the arrow keys if the ime is not active
			if (g_bKWNDactive)
			{
				// init dijoystate
				dijoystate.lX = 0; dijoystate.lY = 0;
				psk = NULL;
				do
	            {
		            psk = KWNDProcessXMovement(dijoystate, psk, &g_iKeyTop, FORWARD);
			    } while (psk == NULL);
			}
			else if (g_bSWNDactive)
			{
				// init dijoystate
				dijoystate.lX = 0; dijoystate.lY = 0;
				psk2 = NULL;
	            do
		        {
	                psk2 = SWNDProcessXMovement(dijoystate, psk2, &g_iSWNDKeyTop, FORWARD);
				} while (psk2 == NULL);
			}
            else
#endif  // KANJI
			{
	            if (_tcslen (g_wszNonConverted) == 0)
		        {
					if (g_caretpos < _tcslen (g_wszConverted))
						g_caretpos++;
				}
				else
				{
					if (g_caretpos < g_compositioncaret + _tcslen (g_wszNonConverted))
						g_caretpos++;
				}
			    EditBoxRender();
			}
			break;

        case VK_DOWN:
#ifdef KANJI
			// don't process the arrow keys if the ime is not active
			if (g_bKWNDactive)
			{
				// init dijoystate
				dijoystate.lX = 0; dijoystate.lY = 0;
				psk = NULL;
				do
	            {
		            psk = KWNDProcessYMovement(dijoystate, psk, &g_iKeyTop, FORWARD);
			    } while (psk == NULL);
			}
			else if (g_bSWNDactive)
			{
				// init dijoystate
				dijoystate.lX = 0; dijoystate.lY = 0;
				psk2 = NULL;
	            do
		        {
	                psk2 = SWNDProcessYMovement(dijoystate, psk2, &g_iSWNDKeyTop, FORWARD);
				} while (psk2 == NULL);
            }
#endif  // KANJI
			break;

        case VK_UP:
#ifdef KANJI
			// don't process the arrow keys if the ime is not active
			if (g_bKWNDactive)
			{
				// init dijoystate
				dijoystate.lX = 0; dijoystate.lY = 0;
				psk = NULL;
				do
	            {
		            psk = KWNDProcessYMovement(dijoystate, psk, &g_iKeyTop, BACK);
			    } while (psk == NULL);
			}
			else if (g_bSWNDactive)
			{
				// init dijoystate
				dijoystate.lX = 0; dijoystate.lY = 0;
				psk2 = NULL;
	            do
		        {
	                psk2 = SWNDProcessYMovement(dijoystate, psk2, &g_iSWNDKeyTop, BACK);
				} while (psk2 == NULL);
            }
#endif  // KANJI
			break;

		case VK_DBE_SBCSCHAR:
            if (g_pkeybdstateCurrent->keyboard != ROMANJI)
            {
                g_pkeybdstateCurrent->keyboard = KATAKANA;
			    g_pkeybdstateCurrent->fHalfWidth = TRUE;
            }
            g_pkeybdstateCurrent->fDoubleWidth = FALSE;
			break;

		case VK_DBE_DBCSCHAR:
            if (g_pkeybdstateCurrent->keyboard != ROMANJI)
            {
                g_pkeybdstateCurrent->keyboard = KATAKANA;
			    g_pkeybdstateCurrent->fHalfWidth = FALSE;
            }
            g_pkeybdstateCurrent->fDoubleWidth = TRUE;
			break;

		case VK_DBE_HIRAGANA:
            //OutputDebugString(TEXT("H"));
			g_pkeybdstateCurrent->keyboard = HIRAGANA;
		    g_pkeybdstateCurrent->fHalfWidth = FALSE;
			break;

		case VK_DBE_KATAKANA:
            //OutputDebugString(TEXT("K"));
			g_pkeybdstateCurrent->keyboard = KATAKANA;
			break;

        case VK_DBE_ALPHANUMERIC:
            g_pkeybdstateCurrent->keyboard = ROMANJI;
            break;

		case VK_DBE_NOROMAN:
            //OutputDebugString(TEXT("N"));
			g_pkeybdstateCurrent->fRKCOn = FALSE;
			break;	

		case VK_DBE_ROMAN:
            //OutputDebugString(TEXT("R"));
			g_pkeybdstateCurrent->fRKCOn = TRUE;
			break;	

        case VK_CAPITAL:
            if (g_fHardwareKeyboardPresent)
            {
                if (!g_pkeybdstateCurrent->fIMEOn || g_pkeybdstateCurrent->keyboard == ROMANJI)
                    g_pkeybdstateCurrent->fCapsOn = GetKeyState(VK_CAPITAL) & 0x01;
            }
            else
                g_pkeybdstateCurrent->fCapsOn = !g_pkeybdstateCurrent->fCapsOn;

            break;

#ifdef KANJI
		case VK_KANJI:
			g_pkeybdstateCurrent->fIMEOn = !g_pkeybdstateCurrent->fIMEOn;
            break;
#endif

        default:
            break;
    }

} // IMEProcessVirtualKey


#ifdef KANJI
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    DakutenValid

Description:

    This function determines whether a character can have a dakuten.

Return Value:

    TRUE if the character can have a dakuten, FALSE otherwise.

-------------------------------------------------------------------*/
TCHAR DakutenValid (TCHAR wcKey)
{
    WORD i;

    if ((wcKey >= FIRST_HIRAGANA) && (wcKey <= LAST_HIRAGANA))

        return (g_rgHiraganaMap[wcKey - FIRST_HIRAGANA].wcDakuten);

    else if ((wcKey >= FIRST_KATAKANA) && (wcKey <= LAST_KATAKANA))

        return (g_rgKatakanaMap[wcKey - FIRST_KATAKANA].wcDakuten);

    else if ((wcKey >= FIRST_HW_KATAKANA) && (wcKey <= LAST_HW_KATAKANA))
    {
        // is this a hiragana characters?
        for (i = 0; i <= LAST_KATAKANA - FIRST_KATAKANA; i++)
        {
            // find out if this is a half-width katakana character
            if (g_rgKatakanaMap[i].wcHalfWidth == wcKey)
                return (g_rgKatakanaMap[i].wcDakuten);
        }   
    }

    return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    HandakutenValid

Description:

    This function determines whether a character can have a handakuten.

Return Value:

    TRUE if the character can have a handakuten, FALSE otherwise.

-------------------------------------------------------------------*/
TCHAR HandakutenValid(TCHAR wcKey)
{
    WORD i;

    if ((wcKey >= FIRST_HIRAGANA) && (wcKey <= LAST_HIRAGANA))

        return (g_rgHiraganaMap[wcKey - FIRST_HIRAGANA].wcHandakuten);

    else if ((wcKey >= FIRST_KATAKANA) && (wcKey <= LAST_KATAKANA))

        return (g_rgKatakanaMap[wcKey - FIRST_KATAKANA].wcHandakuten);

    else if ((wcKey >= FIRST_HW_KATAKANA) && (wcKey <= LAST_HW_KATAKANA))
    {
        // is this a hiragana characters?
        for (i = 0; i <= LAST_KATAKANA - FIRST_KATAKANA; i++)
        {
            // find out if this is a half-width katakana character
            if (g_rgKatakanaMap[i].wcHalfWidth == wcKey)
                return (g_rgKatakanaMap[i].wcHandakuten);
        }   
    }

    return 0;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IsHiragana

Description:

    This function determines whether a string contains only Hiragana,
    dakuten and handakuten characters.

Return Value:

    TRUE if this is a Hiragana string, FALSE otherwise.

-------------------------------------------------------------------*/
BOOL
IsHiragana(TCHAR *szIn)
{
    WORD i = 0;

    // check for empty string
    if (*szIn == '\0') return FALSE;

    while (szIn[i] != '\0') 
    {
        if ((szIn[i] < FIRST_HIRAGANA || szIn[i] > LAST_HIRAGANA)   &&
            (szIn[i] != SYMBOLS_HANDAKUTEN)                         &&
            (szIn[i] != SYMBOLS_DAKUTEN)                            &&
            (szIn[i] != SYMBOLS_IDEO_PERIOD)                        &&
            (szIn[i] != SYMBOLS_IDEO_COMMA)                         &&
            (szIn[i] != SYMBOLS_JAPANESE_DASH))
        {
            return FALSE;
        }

        i++;
    }

    return TRUE;  // it's Hiragana
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IsKana

Description:

    This function determines whether a string contains only Hiragana,
    Katakana, dakuten and handakuten characters.

Return Value:

    TRUE if this is a pure kana string, FALSE otherwise.

-------------------------------------------------------------------*/
BOOL
IsKana
    (
    TCHAR           *szIn
    )
{
    WORD i = 0;

    // check for empty string
    if (*szIn == '\0') return FALSE;

    while (szIn[i] != '\0') 
    {
        if ((szIn[i] < FIRST_HIRAGANA ||  szIn[i] > LAST_HIRAGANA)          &&
            (szIn[i] < FIRST_KATAKANA ||  szIn[i] > LAST_KATAKANA)          &&
            (szIn[i] < FIRST_HW_KATAKANA || szIn[i] > LAST_HW_KATAKANA)     &&
            (szIn[i] < FIRST_HHHW_KATAKANA || szIn[i] > LAST_HHHW_KATAKANA) &&
            (szIn[i] != SYMBOLS_HANDAKUTEN)                                 &&
            (szIn[i] != SYMBOLS_DAKUTEN))                                
        {
            return FALSE;
        }

        i++;
    }

    return TRUE;  // it's kana.
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IsKatakana

Description:

    This function determines whether a string contains only Katakana,
    dakuten and handakuten characters.

Return Value:

    TRUE if this is a Katakana string, FALSE otherwise.

-------------------------------------------------------------------*/
BOOL
IsKatakana(TCHAR *szIn)
{
    WORD i = 0;

    // check for empty string
    if (*szIn == '\0') return FALSE;

    while (szIn[i] != '\0') 
    {
        if ((szIn[i] < FIRST_KATAKANA || szIn[i] > LAST_KATAKANA)           &&
            (szIn[i] < FIRST_HW_KATAKANA || szIn[i] > LAST_HW_KATAKANA)     &&
            (szIn[i] < FIRST_HHHW_KATAKANA || szIn[i] > LAST_HHHW_KATAKANA) &&
            (szIn[i] != SYMBOLS_HANDAKUTEN)                                 &&
            (szIn[i] != SYMBOLS_DAKUTEN))
        {
            return FALSE;
        }

        i++;
    }

    return TRUE;  // it's Katakana
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ConvertToHiragana

Description:

Return Value:

    None.

-------------------------------------------------------------------*/
void
ConvertToHiragana
    (
    TCHAR*          szInput,
    TCHAR*          szHiragana
    )
{
    TCHAR           chInput;
    WORD            i;

    do
    {   
        chInput = *szInput;

        if ((chInput >= FIRST_KATAKANA) && (chInput <= LAST_KATAKANA))
            *szHiragana = chInput - 0x60;

        else if (((chInput >= FIRST_HW_KATAKANA) && (chInput <= LAST_HW_KATAKANA)) ||
                 ((chInput >= FIRST_HHHW_KATAKANA) && (chInput <= LAST_HHHW_KATAKANA)))
        {
            if (chInput == KATAKANA_DAKUTEN)
                *szHiragana = SYMBOLS_DAKUTEN;
            else if (chInput == KATAKANA_HANDAKUTEN)
                *szHiragana = SYMBOLS_HANDAKUTEN;
            else {
                *szHiragana = chInput;
                for (i = 0 ; i <= LAST_KATAKANA - FIRST_KATAKANA ; i++)
                {
                    if ((g_rgKatakanaMap[i].wcHalfWidth == chInput) ||
                        (g_rgKatakanaMap[i].wcHalfWidthHalfHeight == chInput)) {

                        if (*(szInput + 1) && *(szInput + 1) == KATAKANA_DAKUTEN &&
                            g_rgKatakanaMap[i].wcDakuten) {
                            *szHiragana = g_rgKatakanaMap[i].wcDakuten - FIRST_KATAKANA + FIRST_HIRAGANA;
                            szInput++;
                        } else if (*(szInput + 1) && *(szInput + 1) == KATAKANA_HANDAKUTEN &&
                                   g_rgKatakanaMap[i].wcHandakuten) {
                            *szHiragana = g_rgKatakanaMap[i].wcHandakuten - FIRST_KATAKANA + FIRST_HIRAGANA;
                            szInput++;
                        } else {
                            *szHiragana = i + FIRST_KATAKANA - 0x60;
                        }
                        break;
                    }
                }
            }
        }
        else
            *szHiragana = chInput;

        szInput++;
        szHiragana++;

    } while (chInput);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ConvertToKatakana

Description:

Return Value:

    None.

-------------------------------------------------------------------*/
void
ConvertToKatakana
    (
    TCHAR*          szInput,
    TCHAR*          szKatakana
    )
{
    TCHAR           chInput;

    do
    {   
        chInput = *szInput;

        if ((chInput >= FIRST_HIRAGANA) && (chInput <= LAST_HIRAGANA))
            *szKatakana = chInput + 0x60;

        else
            *szKatakana = chInput;

        szInput++;
        szKatakana++;

    } while (chInput);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IMEDestroy

Description:

    This function cleans up the IME.
Return Value:

    none

-------------------------------------------------------------------*/
void
IMEDestroy
    (
    void
    )
{
    // Destroy Tankanji Library
    if (g_htk) TKClose(g_htk);

    // destroy the kanji window
    KWNDDestroy();  

    // Release the IME joystick
    if (g_pdidevice2JoystickIME)
    {
        g_pdidevice2JoystickIME->Unacquire ();
        g_pdidevice2JoystickIME->Release ();
        g_pdidevice2JoystickIME = NULL;
    }

} // IMEDestroy


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IMEUpdate

Description:

    This function re-renders the IME.

Return Value:

    none

-------------------------------------------------------------------*/
void
IMEUpdate
    (
    void
    )
{
    static BOOL bLastActive = g_bKWNDactive;
    
    // if the KWND shifted to active or to not active, then reset the iKeyTop to 0
    if (g_bKWNDactive != bLastActive)
    {
        g_iKeyTop = 0;
        if (bLastActive == TRUE) {
            EditBoxRender();   // render the cleared IME
        } else {
            KWNDRender(g_iKeyTop);
        }
        bLastActive = g_bKWNDactive; 
    }

    if (g_bKWNDactive)
    {
        KWNDReadDirectInputDevices(&g_iKeyTop);
    }

} // IMEUpdate


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IMEBlt

Description:

    This function blits the IME to the back buffer.

Return Value:

    none

-------------------------------------------------------------------*/
void IMEBlt(LPDIRECTDRAWSURFACE lpDDSBack)
{
    if (g_bKWNDactive)
    {
        KWNDBlt(lpDDSBack);
    }
}
#endif  // KANJI
