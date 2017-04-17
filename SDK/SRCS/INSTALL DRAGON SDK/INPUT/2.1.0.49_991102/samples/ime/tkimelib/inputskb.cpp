/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    inputskb.cxx

Abstract:

    This file contains functions which manage input to the soft keyboard window.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/
#include "precomp.hxx"


LPDIRECTINPUTDEVICE2        g_pdidevice2JoystickSKB = NULL;       // joystick



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBReadDirectInputDevices

Description:

    Retrieves the current state of the joystick, and takes the 
    appropriate action for the SKB, based on which buttons are pressed.

Return Value:
    
    None.

-------------------------------------------------------------------*/
void
SKBReadDirectInputDevices
    (
    void
    )
{
    DIJOYSTATE              dijoystate;
    HRESULT                 hr;
    static DWORD            dwTickLastXMovement = 0;
    static DWORD            dwTickLastYMovement = 0;
    DWORD                   dwXRepeatRate;
    DWORD                   dwYRepeatRate;
    WORD                    iKeyCurrent;
    SOFTKEY*                psk;
    static DWORD            dwTickLastJoystick = 0;

    // If there's a joystick, and the current focus is on us, read the joystick's
    // current state, and act appropriately.
    if (g_pdidevice2JoystickSKB)
    {
        // If less than 0.05 seconds have elapsed since a button was last
        // pressed, then don't process further joystick input.  If we
        // don't do this, then pressing a button once will send several
        // WM_KEYDOWN messages.

        dwTickLastJoystick = GetTickCount();
        hr = g_pdidevice2JoystickSKB->GetDeviceState (sizeof(DIJOYSTATE), &dijoystate);

        if (FAILED(hr))
        {
            g_pdidevice2JoystickSKB->Unacquire();
            g_pdidevice2JoystickSKB->Release();
            g_pdidevice2JoystickSKB = NULL;
        }
        if (hr != DI_OK)
            return;

        iKeyCurrent = SKBFindKeyUnderCursor();
        if (iKeyCurrent == 0xffff) 
        {
            psk = NULL;
        } else {
            psk = &g_pskCurrentSKB[iKeyCurrent];
        }

        // Start button exits
        if ((dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_START]] & BUTTON_ON) &&
            (dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_START]] != g_rgiPrevButtons[JOYSTICK_START]))
        {
            PostQuitMessage(0);
        }
        
        if ((dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_A]] & BUTTON_ON) &&
            (dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_A]] != g_rgiPrevButtons[JOYSTICK_A]))
        {
            FillPrevButtons(dijoystate);
            if (psk != NULL) 
            {
#ifndef KANJI
                if (!_tcscmp(psk->szKeyString, US_CAPSLOCK))
                {
                    g_pkeybdstateCurrent->fCapsOn = !g_pkeybdstateCurrent->fCapsOn;
                    SKBRender();
                }
                else
                if (!_tcscmp(psk->szKeyString, US_BACKSPACE))
                {
                    PostMessage(g_hwndApp, WM_KEYDOWN, psk->vkCode, 0);
                }
                else
                if (!_tcscmp(psk->szKeyString, US_SPACE))
                {
                    PostMessage(g_hwndApp, WM_KEYDOWN, psk->vkCode, 0);
                }
                else
                if (!_tcscmp(psk->szKeyString, US_CLOSE))
                {
                    PostMessage(g_hwndApp, WM_KEYDOWN, psk->vkCode, 0);
                }
                else      
#endif  // KANJI
                switch (psk->szKeyString[0])
                {
#ifdef  KANJI
                    case HIRAGANA_SWITCH:
                        // switch to Katakana layout if we're in Hiragana format, 
                        // otherwise just post a keydown message (the key for switching
                        // to Katakana is a valid key on the Katakana keyboard, so we
                        // don't want to switch in that case)
                        if (g_pskCurrentSKB != g_rgskKatakana) 
                        {
                            g_pskCurrentSKB = g_rgskKatakana;
                            g_cCurrentSKBKeys = g_cKatakanaKeys;
                            g_pkeybdstateCurrent->fHalfWidth = FALSE;
                            g_pkeybdstateCurrent->fHalfHeight = FALSE;
                            g_iKeyFocus = 10;   // The 'A' key.
                            g_xCursor = g_pskCurrentSKB[g_iKeyFocus].xGridLocation;
                            g_yCursor = g_pskCurrentSKB[g_iKeyFocus].yGridLocation;
                            SKBRender();
							// send VK_DBE_KATAKANA to the app
							PostMessage(g_hwndApp, WM_KEYDOWN, VK_DBE_KATAKANA, 0);
                        } else {
                            SKBProcessKatakanaKey(psk->szKeyString[0]);
                        }
                        break;
                    case KATAKANA_SWITCH:
                        // switch to Hiragana layout if we're in Katakana format, 
                        // otherwise just post a keydown message (the key for switching
                        // to Hiragana is a valid key on the Hiragana keyboard, so we
                        // don't want to switch in that case)
                        if (g_pskCurrentSKB != g_rgskHiragana)
                        {
                            g_pskCurrentSKB = g_rgskHiragana;
                            g_cCurrentSKBKeys = g_cHiraganaKeys;
                            g_pkeybdstateCurrent->fHalfWidth = FALSE;
                            g_pkeybdstateCurrent->fHalfHeight = FALSE;
                            g_iKeyFocus = 10;   // The 'A' key.
                            g_xCursor = g_pskCurrentSKB[g_iKeyFocus].xGridLocation;
                            g_yCursor = g_pskCurrentSKB[g_iKeyFocus].yGridLocation;
                            SKBRender();
							// send VK_DBE_HIRAGANA to the app
							PostMessage(g_hwndApp, WM_KEYDOWN, VK_DBE_HIRAGANA, 0);
                        } else {
                            SKBProcessHiraganaKey(psk->szKeyString[0]);
                        }
                        break;
                    case KANJI_CLOSE_0:
                        // close the keyboard
                        PostMessage(g_hwndApp, WM_KEYDOWN, psk->vkCode, 0);
                        break;
                    case KANJI_CONFIRM_0:
                        PostMessage(g_hwndApp, WM_KEYDOWN, psk->vkCode, 0);
                        break;
                    case KANJI_CONVERT_0:
                        // unacquire the joystick so that the IME can get it
                        g_pdidevice2JoystickSKB->Unacquire();
                        PostMessage(g_hwndApp, WM_KEYDOWN, psk->vkCode, 0);
                        break;
                    case KANJI_SMALL_0:
                        // swap the half-height state
                        g_pkeybdstateCurrent->fHalfHeight = !g_pkeybdstateCurrent->fHalfHeight;
                        SKBRender();
                        break;
                    case KANJI_CAPSLOCK_0:
                        // caps lock
                        g_pkeybdstateCurrent->fCapsOn = !g_pkeybdstateCurrent->fCapsOn;
                        SKBRender();
                        break;
                    case KANJI_HALF_0:
                        if (g_pskCurrentSKB == g_rgskKatakana) 
                        {
                            // swap the half-width state; only for Katakana
							if (g_pkeybdstateCurrent->fHalfWidth) {
								SendMessage(g_hwndApp, WM_KEYDOWN, VK_DBE_DBCSCHAR, 0);
							} else {
								SendMessage(g_hwndApp, WM_KEYDOWN, VK_DBE_SBCSCHAR, 0);
							}
                            SKBRender();
                        } 
                        else if (g_pskCurrentSKB == g_rgskRomanji) 
                        {
                            // swap the double-width state; only for Katakana
                            g_pkeybdstateCurrent->fDoubleWidth = !g_pkeybdstateCurrent->fDoubleWidth;
                            SKBRender();
                        }

                        break;
                    case KANJI_DELETE_0:
                        PostMessage(g_hwndApp, WM_KEYDOWN, psk->vkCode, 0);
                        break;
                    case KANJI_SYMBOLS_0:
                        // bring up the symbols window
                        g_xSWNDCursor = 0;
                        g_ySWNDCursor = 0;
                        g_iSWNDFocus  = 0;
                        SWNDRender(0);
                        g_bSWNDactive = TRUE;
                        break;
                    case KANJI_ENGLISH_0:
                        // switch to Romanji keyboard
                        g_pskCurrentSKB = g_rgskRomanji;
                        g_cCurrentSKBKeys = g_cRomanjiKeys;
                        g_pkeybdstateCurrent->keyboard = ROMANJI;
                        g_pkeybdstateCurrent->fDoubleWidth = FALSE;
                        g_iKeyFocus = 18;   // The 'A' key
                        g_xCursor = g_pskCurrentSKB[g_iKeyFocus].xGridLocation;
                        g_yCursor = g_pskCurrentSKB[g_iKeyFocus].yGridLocation;
                        SKBRender();
                        break;
                    case KANJI_SPACE_0:
                        // space bar
                        PostMessage(g_hwndApp, WM_KEYDOWN, psk->vkCode, 0);
                        break;
#endif  // KANJI
                    case SYMBOLS_LEFT:
                    case SYMBOLS_RIGHT:
                    case SYMBOLS_UP:
                    case SYMBOLS_DOWN:
                        PostMessage(g_hwndApp, WM_KEYDOWN, psk->vkCode, 0);
                        break;        
                    default:
#ifdef KANJI
                        // just post the KEYDOWN message, in regular, half-width, or
                        // half-height state; also, we need to index into HiraganaMap
                        // or KatakanaMap
                        if (g_pskCurrentSKB == g_rgskHiragana) 
                        {
                            SKBProcessHiraganaKey(psk->szKeyString[0]);
                        } else if (g_pskCurrentSKB == g_rgskKatakana) {
                            SKBProcessKatakanaKey(psk->szKeyString[0]);
                        } else if (g_pskCurrentSKB == g_rgskRomanji) 
#endif  // KANJI
                        {
                            SKBProcessRomanjiKey(psk->szKeyString[0]);
                        }
                        break;
                }
                if (psk->szKeyString[0] != KANJI_SMALL_0)
				{
					if(g_pkeybdstateCurrent->fHalfHeight != FALSE)
					{
	                    g_pkeybdstateCurrent->fHalfHeight = FALSE;  // switch back to full height mode
		                SKBRender();
					}
				}
            }    

        }

        // Y button is used to convert
        if ((dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_Y]] & BUTTON_ON) &&
            (dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_Y]] != g_rgiPrevButtons[JOYSTICK_Y]))
        {
            FillPrevButtons(dijoystate);
            // unacquire the joystick so that the IME can get it
            g_pdidevice2JoystickSKB->Unacquire();
            PostMessage(g_hwndApp, WM_KEYDOWN, VK_CONVERT, 0);
        }

        // X button is used to backspace.
        if ((dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_X]] & BUTTON_ON) &&
            (dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_X]] != g_rgiPrevButtons[JOYSTICK_X]))
        {
            FillPrevButtons(dijoystate);
            PostMessage(g_hwndApp, WM_KEYDOWN, VK_BACK, 0);
        }

        // B button is used to determine the characters.
        if ((dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_B]] & BUTTON_ON) &&
            (dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_B]] != g_rgiPrevButtons[JOYSTICK_B]))
        {
            FillPrevButtons(dijoystate);
            PostMessage(g_hwndApp, WM_KEYDOWN, VK_RETURN, 0);
        }

        if (g_fAnalogJoystick)
        {
            // LA button is used to step left
            if ((dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_LA]] & BUTTON_ON) &&
                (dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_LA]] != g_rgiPrevButtons[JOYSTICK_LA]))
            {
                FillPrevButtons(dijoystate);
                dwTickLastXMovement = GetTickCount ();
                PostMessage(g_hwndApp, WM_KEYDOWN, VK_LEFT, 0);
            }
            // RA button is used to step right
            if ((dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_RA]] & BUTTON_ON) &&
                (dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_RA]] != g_rgiPrevButtons[JOYSTICK_RA]))
            {
                FillPrevButtons(dijoystate);
                dwTickLastXMovement = GetTickCount ();
                PostMessage(g_hwndApp, WM_KEYDOWN, VK_RIGHT, 0);
            }
            // DA button is used to step down
            if ((dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_DA]] & BUTTON_ON) &&
                (dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_DA]] != g_rgiPrevButtons[JOYSTICK_DA]))
            {
                FillPrevButtons(dijoystate);
                dwTickLastYMovement = GetTickCount ();
                PostMessage(g_hwndApp, WM_KEYDOWN, VK_DOWN, 0);
            }
            // UA button is used to step up
            if ((dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_UA]] & BUTTON_ON) &&
                (dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_UA]] != g_rgiPrevButtons[JOYSTICK_UA]))
            {
                FillPrevButtons(dijoystate);
                dwTickLastYMovement = GetTickCount ();
                PostMessage(g_hwndApp, WM_KEYDOWN, VK_UP, 0);
            }
        }
        else
        {
            // LA button is used to step left
            if ((dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_LA]] & BUTTON_ON) &&
                (dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_LA]] != g_rgiPrevButtons[JOYSTICK_LA]))
            {
                FillPrevButtons(dijoystate);
                dwTickLastXMovement = GetTickCount ();
                do
                {
                    psk = SKBProcessXMovement(dijoystate, psk, BACK);
                } while (psk == NULL);
            }
            // RA button is used to step right
            if ((dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_RA]] & BUTTON_ON) &&
                (dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_RA]] != g_rgiPrevButtons[JOYSTICK_RA]))
            {
                FillPrevButtons(dijoystate);
                dwTickLastXMovement = GetTickCount ();
                do
                {
                    psk = SKBProcessXMovement(dijoystate, psk, FORWARD);
                } while (psk == NULL);
            }
            // DA button is used to step down
            if ((dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_DA]] & BUTTON_ON) &&
                (dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_DA]] != g_rgiPrevButtons[JOYSTICK_DA]))
            {
                FillPrevButtons(dijoystate);
                dwTickLastYMovement = GetTickCount ();
                do
                {
                    psk = SKBProcessYMovement(dijoystate, psk, FORWARD);
                } while (psk == NULL);
            }
            // UA button is used to step up
            if ((dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_UA]] & BUTTON_ON) &&
                (dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_UA]] != g_rgiPrevButtons[JOYSTICK_UA]))
            {
                FillPrevButtons(dijoystate);
                dwTickLastYMovement = GetTickCount ();
                do
                {
                    psk = SKBProcessYMovement(dijoystate, psk, BACK);
                } while (psk == NULL);
            }
        }

        dwXRepeatRate = 0;
        dwYRepeatRate = 0;


        // Calculate the repeat rates for + and - X and Y directions --> the further the joystick
        // is pressed in one direction, the less time between successive movements on the 
        // SKB.
        if (dijoystate.lX < -LOWER_JOYSTICK_THRESHOLD)
        {
            dwXRepeatRate = SLOW_REPEAT_RATE - ((-dijoystate.lX) - LOWER_JOYSTICK_THRESHOLD) *
                (SLOW_REPEAT_RATE - FAST_REPEAT_RATE) /
                (UPPER_JOYSTICK_THRESHOLD - LOWER_JOYSTICK_THRESHOLD);
        }
        if (dijoystate.lX > LOWER_JOYSTICK_THRESHOLD)
        {
            dwXRepeatRate = SLOW_REPEAT_RATE - (dijoystate.lX - LOWER_JOYSTICK_THRESHOLD) *
                (SLOW_REPEAT_RATE - FAST_REPEAT_RATE) /
                (UPPER_JOYSTICK_THRESHOLD - LOWER_JOYSTICK_THRESHOLD);
        }

        if (dijoystate.lY < -LOWER_JOYSTICK_THRESHOLD)
        {
            dwYRepeatRate = SLOW_REPEAT_RATE - ((-dijoystate.lY) - LOWER_JOYSTICK_THRESHOLD) *
                (SLOW_REPEAT_RATE - FAST_REPEAT_RATE) /
                (UPPER_JOYSTICK_THRESHOLD - LOWER_JOYSTICK_THRESHOLD);
        }
        if (dijoystate.lY > LOWER_JOYSTICK_THRESHOLD)
        {
            dwYRepeatRate = SLOW_REPEAT_RATE - (dijoystate.lY - LOWER_JOYSTICK_THRESHOLD) *
                (SLOW_REPEAT_RATE - FAST_REPEAT_RATE) /
                (UPPER_JOYSTICK_THRESHOLD - LOWER_JOYSTICK_THRESHOLD);
        }

        if (((GetTickCount () - dwTickLastXMovement) > dwXRepeatRate) && (dwXRepeatRate > 0))
        {
            dwTickLastXMovement = GetTickCount ();
            do 
            {
                psk = SKBProcessXMovement(dijoystate, psk, NONE);
            } while (psk == NULL);
        }            

        if (((GetTickCount () - dwTickLastYMovement) > dwYRepeatRate) && (dwYRepeatRate > 0))
        {
            dwTickLastYMovement = GetTickCount ();
            do
            {
                psk = SKBProcessYMovement(dijoystate, psk, NONE);
            } while (psk == NULL);
        }            

        // Poll the device now, so the data will be ready the next time around.
        FillPrevButtons(dijoystate);
        hr = g_pdidevice2JoystickSKB->Poll ();

        if (FAILED(hr))
        {
            g_pdidevice2JoystickSKB->Unacquire();
            g_pdidevice2JoystickSKB->Release();
            g_pdidevice2JoystickSKB = NULL;
        } 
        if (hr != DI_OK)
            return;
    } else {
        if (GetTickCount() - dwTickLastJoystick > 500)
        {        
            IME_CreateDirectInput(g_hinstApp, g_hwndApp, &g_pdidevice2JoystickSKB);

            if (g_pdidevice2JoystickSKB
#ifdef  KANJI
                 && !g_bKWNDactive
#endif  // KANJI
                )
                AcquireJoystick(&g_pdidevice2JoystickSKB);

            dwTickLastJoystick = GetTickCount();
        }
    }
} // SKBReadDirectInputDevices


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBConvertRomanjiKey

Description:

    Convert romaji key based on SKB state.

Return Value:
    
    None.

-------------------------------------------------------------------*/
TCHAR 
SKBConvertRomanjiKey
    (
    TCHAR wcCharacter
    )
{
    switch(wcCharacter) // must account for hard-coded skb "function keys"
    {
#ifdef KANJI
        case HIRAGANA_SWITCH:
        case KATAKANA_SWITCH:
        case KANJI_CLOSE_0:
        case KANJI_CONFIRM_0:
        case KANJI_CONVERT_0:
        case KANJI_SMALL_0:
        case KANJI_CAPSLOCK_0:
        case KANJI_HALF_0:
        case KANJI_DELETE_0:
        case KANJI_SYMBOLS_0:
        case KANJI_ENGLISH_0:
        case KANJI_SPACE_0:
#endif  // KANJI
		case SYMBOLS_LEFT:
		case SYMBOLS_RIGHT:
		case SYMBOLS_UP:
		case SYMBOLS_DOWN:
			return 0;
	}

    if ((wcCharacter >= ROMAN_A) && (wcCharacter <= ROMAN_Z))
    {
        if (!g_pkeybdstateCurrent->fCapsOn)
            wcCharacter += ROMAN_ALPHABET_GAP;
    }

/*    if ((wcCharacter >= ROMAN_START) && (wcCharacter <= ROMAN_END))
    {
        if (g_pkeybdstateCurrent->fDoubleWidth)
            wcCharacter += ROMAN_DOUBLEWIDTH_OFFSET;
    }*/
    if (g_pkeybdstateCurrent->fDoubleWidth)
	{
        if ((wcCharacter >= ROMAN_START) && (wcCharacter <= ROMAN_END))
            wcCharacter += ROMAN_DOUBLEWIDTH_OFFSET;
	}
	else
	{
        if (wcCharacter == SYMBOLS_YEN)
            wcCharacter = SYMBOLS_YEN_HW;
        else if (wcCharacter == SYMBOLS_JAPANESE_LEFT_PAREN)
            wcCharacter = SYMBOLS_JAPANESE_LEFT_PAREN_HW;
        else if (wcCharacter == SYMBOLS_JAPANESE_RIGHT_PAREN)
            wcCharacter = SYMBOLS_JAPANESE_RIGHT_PAREN_HW;
        else if (wcCharacter == SYMBOLS_IDEO_COMMA)
            wcCharacter = SYMBOLS_IDEO_COMMA_HW;
        else if (wcCharacter == SYMBOLS_IDEO_PERIOD)
            wcCharacter = SYMBOLS_IDEO_PERIOD_HW;
	}

    return wcCharacter;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBProcessRomanjiKey

Description:

    Send a WM_CHAR message for a romnaji key.

Return Value:
    
    None.

-------------------------------------------------------------------*/
void 
SKBProcessRomanjiKey
    (
    TCHAR wcCharacter
    )
{
    TCHAR wcConvertedChar = SKBConvertRomanjiKey(wcCharacter);

    if(wcConvertedChar)
    {
        PostMessage(g_hwndApp, WM_CHAR, wcConvertedChar, 0);
#ifndef KANJI
        PostMessage(g_hwndApp, WM_KEYDOWN, VK_NOCONVERT, 0);
#endif
    }
	else
		// Beep!
		;
}


#ifdef KANJI
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBConvertHiraganaKey

Description:

    Convert hiragana key based on SKB state (could be half-height
    character, full-height character, or non-hiragana key).

Return Value:
    
    None.

-------------------------------------------------------------------*/
TCHAR 
SKBConvertHiraganaKey
    (
    TCHAR wcCharacter
    )
{
    switch(wcCharacter) // must account for hard-coded skb "function keys"
    {
		case HIRAGANA_SWITCH:
		//case KATAKANA_SWITCH:
		case KANJI_CLOSE_0:
		case KANJI_CONFIRM_0:
		case KANJI_CONVERT_0:
		case KANJI_SMALL_0:
		case KANJI_CAPSLOCK_0:
		case KANJI_HALF_0:
		case KANJI_DELETE_0:
		case KANJI_SYMBOLS_0:
		case KANJI_ENGLISH_0:
        case KANJI_SPACE_0:
		case SYMBOLS_LEFT:
		case SYMBOLS_RIGHT:
		case SYMBOLS_UP:
		case SYMBOLS_DOWN:
			return 0;
	}

    if (g_pkeybdstateCurrent->fHalfHeight)
	{
        if ((wcCharacter >= FIRST_HIRAGANA) && (wcCharacter <= LAST_HIRAGANA))
		{
            if(g_rgHiraganaMap[wcCharacter - FIRST_HIRAGANA].wcHalfHeight)
                wcCharacter = g_rgHiraganaMap[wcCharacter - FIRST_HIRAGANA].wcHalfHeight;
		}
    }

    if ((wcCharacter >= ROMAN_START) && (wcCharacter <= ROMAN_END))
        wcCharacter += ROMAN_DOUBLEWIDTH_OFFSET;

    return wcCharacter;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBProcessHiraganaKey

Description:

    Send a WM_CHAR message for a hiragana key.

Return Value:
    
    None.

-------------------------------------------------------------------*/
void 
SKBProcessHiraganaKey
    (
    TCHAR wcCharacter
    )
{
    TCHAR wcConvertedChar = SKBConvertHiraganaKey(wcCharacter);

	if(wcConvertedChar)
		PostMessage(g_hwndApp, WM_CHAR, wcConvertedChar, 0);                            
	else
		// Beep!
		;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBConvertKatakanaKey

Description:

    Convert katakana key based on SKB state (could be half-height
    character, full-height character, or non-Katakana key).

Return Value:
    
    None.
-------------------------------------------------------------------*/
TCHAR 
SKBConvertKatakanaKey
    (
    TCHAR wcCharacter
    )
{
    switch(wcCharacter) // must account for hard-coded skb "function keys"
	{
		//case HIRAGANA_SWITCH:
        case KATAKANA_SWITCH:
		case KANJI_CLOSE_0:
		case KANJI_CONFIRM_0:
		case KANJI_CONVERT_0:
		case KANJI_SMALL_0:
		case KANJI_CAPSLOCK_0:
		case KANJI_HALF_0:
		case KANJI_DELETE_0:
		case KANJI_SYMBOLS_0:
		case KANJI_ENGLISH_0:
        case KANJI_SPACE_0:
		case SYMBOLS_LEFT:
		case SYMBOLS_RIGHT:
		case SYMBOLS_UP:
		case SYMBOLS_DOWN:
			return 0;
	}

    if ((wcCharacter >= FIRST_KATAKANA) && (wcCharacter <= LAST_KATAKANA))
    {
        if ((g_pkeybdstateCurrent->fHalfHeight) && (g_pkeybdstateCurrent->fHalfWidth))
		{
            if(g_rgKatakanaMap[wcCharacter - FIRST_KATAKANA].wcHalfWidthHalfHeight)
                wcCharacter = g_rgKatakanaMap[wcCharacter - FIRST_KATAKANA].wcHalfWidthHalfHeight;
            else if(g_rgKatakanaMap[wcCharacter - FIRST_KATAKANA].wcHalfWidth)
                wcCharacter = g_rgKatakanaMap[wcCharacter - FIRST_KATAKANA].wcHalfWidth;
		}
        else if (g_pkeybdstateCurrent->fHalfHeight)
		{
            if(g_rgKatakanaMap[wcCharacter - FIRST_KATAKANA].wcHalfHeight)
                wcCharacter = g_rgKatakanaMap[wcCharacter - FIRST_KATAKANA].wcHalfHeight;
		}
        else if (g_pkeybdstateCurrent->fHalfWidth)
		{
            if(g_rgKatakanaMap[wcCharacter - FIRST_KATAKANA].wcHalfWidth)
                wcCharacter = g_rgKatakanaMap[wcCharacter - FIRST_KATAKANA].wcHalfWidth;
		}
    }
    else if (g_pkeybdstateCurrent->fHalfWidth)
	{
        if (wcCharacter == SYMBOLS_YEN)
            wcCharacter = SYMBOLS_YEN_HW;
        else if (wcCharacter == SYMBOLS_JAPANESE_LEFT_PAREN)
            wcCharacter = SYMBOLS_JAPANESE_LEFT_PAREN_HW;
        else if (wcCharacter == SYMBOLS_JAPANESE_RIGHT_PAREN)
            wcCharacter = SYMBOLS_JAPANESE_RIGHT_PAREN_HW;
        else if (wcCharacter == SYMBOLS_IDEO_COMMA)
            wcCharacter = SYMBOLS_IDEO_COMMA_HW;
        else if (wcCharacter == SYMBOLS_IDEO_PERIOD)
            wcCharacter = SYMBOLS_IDEO_PERIOD_HW;
        else if (wcCharacter == SYMBOLS_DAKUTEN)
            wcCharacter = SYMBOLS_HW_DAKUTEN;
        else if (wcCharacter == SYMBOLS_HANDAKUTEN)
            wcCharacter = SYMBOLS_HW_HANDAKUTEN;
	}
	else
	{
        if ((wcCharacter >= ROMAN_START) && (wcCharacter <= ROMAN_END))
            wcCharacter += ROMAN_DOUBLEWIDTH_OFFSET;
	}
/*    if ((wcCharacter >= FIRST_KATAKANA) && (wcCharacter <= LAST_KATAKANA))
    {
        if ((g_pkeybdstateCurrent->fHalfHeight) && (g_pkeybdstateCurrent->fHalfWidth))
			wcCharacter = g_rgKatakanaMap[wcCharacter - FIRST_KATAKANA].wcHalfWidthHalfHeight;
        else if (g_pkeybdstateCurrent->fHalfHeight)
			wcCharacter = g_rgKatakanaMap[wcCharacter - FIRST_KATAKANA].wcHalfHeight;
        else if (g_pkeybdstateCurrent->fHalfWidth)
			wcCharacter = g_rgKatakanaMap[wcCharacter - FIRST_KATAKANA].wcHalfWidth;
    }
    else if (wcCharacter == SYMBOLS_DAKUTEN)
    {
        if (g_pkeybdstateCurrent->fHalfWidth)
            wcCharacter = SYMBOLS_HW_DAKUTEN;                            
    }            
    else if (wcCharacter == SYMBOLS_HANDAKUTEN)
    {
        if (g_pkeybdstateCurrent->fHalfWidth)
            wcCharacter = SYMBOLS_HW_HANDAKUTEN;                            
    }            */

    return wcCharacter;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBProcessKatakanaKey

Description:

    Send a WM_CHAR message for a Katakana key.

Return Value:
    
    None.
-------------------------------------------------------------------*/
void 
SKBProcessKatakanaKey
    (
    TCHAR wcCharacter
    )
{
    TCHAR wcConvertedChar = SKBConvertKatakanaKey(wcCharacter);

	if(wcConvertedChar)
		PostMessage(g_hwndApp, WM_CHAR, wcConvertedChar, 0);                            
	else
		// Beep!
		;
}
#endif  // KANJI


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBProcessXMovement

Description:

    Moves the focus ring along the X direction of the SKB if the joystick
    is pressed along the X-axis.  The SKB "wraps" around the edges, so that
    moving the focus ring off the screen in the +X direction will move the cursor
    to column 0, etc.

Return Value:
    The new key which the cursor is moved to.

-------------------------------------------------------------------*/

SOFTKEY*
SKBProcessXMovement(DIJOYSTATE dijoystate, SOFTKEY* psk, STEP_MOVEMENT bStep)
{
    WORD iKeyCurrent;
    WORD iKeyTemp;
    BOOL bChanged = FALSE;
    WORD i, j;


    iKeyCurrent = SKBFindKeyUnderCursor();
    if ((dijoystate.lX < 0) || bStep == BACK) 
    {

        if (psk == NULL)
        {
            g_xCursor -= 1;
        }
        else
        {
            g_xCursor = psk->xGridLocation;
            g_yCursor = psk->yGridLocation;
            do 
            {
                iKeyTemp = iKeyCurrent;
                g_xCursor -= 1;
                iKeyCurrent = SKBFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
            // now search the space to the left of the key until we get to a new key
            for (i = g_xCursor; i >= 0; i--)
            {
                if (iKeyCurrent != 0xffff || iKeyCurrent == iKeyTemp) break;
                for (j = g_pskCurrentSKB[iKeyTemp].yGridLocation; 
                     j < g_pskCurrentSKB[iKeyTemp].yGridLocation + g_pskCurrentSKB[iKeyTemp].dyRows; j++)
                {
                    if (iKeyCurrent == 0xffff && iKeyCurrent != iKeyTemp)
                    {
                        g_xCursor = i;
                        g_yCursor = j;
                        iKeyCurrent = SKBFindKeyUnderCursor();
                    }
                }
                if ((i == 0 || i == 0xffff) && iKeyCurrent == 0xffff && iKeyCurrent !=iKeyTemp) {
                    i = SKB_COLUMNS; // will be decremented by loop to SKB_COLUMNS - 1
                }
            }
        }    
        bChanged = TRUE;
    }
    else if ((dijoystate.lX > 0) || bStep == FORWARD) 
    {

        if (psk == NULL)
        {
            g_xCursor += 1;
        } else {
            g_xCursor = psk->xGridLocation + psk->dxColumns - 1;
            g_yCursor = psk->yGridLocation;
            // move to the next key
            do
            {
                iKeyTemp = iKeyCurrent;
                g_xCursor += 1;
                iKeyCurrent = SKBFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
            // now search the space to the right of the key until we get to a new key
            for (i = g_xCursor; i < SKB_COLUMNS; )
            {
                if (iKeyCurrent != 0xffff || iKeyCurrent == iKeyTemp) break;
                for (j = g_pskCurrentSKB[iKeyTemp].yGridLocation; 
                     j < g_pskCurrentSKB[iKeyTemp].yGridLocation + g_pskCurrentSKB[iKeyTemp].dyRows; j++)
                {
                    if (iKeyCurrent == 0xffff && iKeyCurrent != iKeyTemp)
                    {
                        g_xCursor = i;
                        g_yCursor = j;
                        iKeyCurrent = SKBFindKeyUnderCursor();
                    }
                }
                if (i == SKB_COLUMNS-1 && iKeyCurrent == 0xffff && iKeyCurrent !=iKeyTemp)
                {
                    i = 0;
                } else {
                    i++;
                }
            }
        }
        bChanged = TRUE;
    }
    if (bChanged)
    {
        // g_xCursor is unsigned, so if it equals 0xffff then the focus ring has been moved off
        // the screen and we should wrap the focus ring to the opposite side.
        if (g_xCursor == 0xffff) g_xCursor = SKB_COLUMNS - 1;
        if (g_xCursor >= SKB_COLUMNS) g_xCursor = 0;
        SKBUpdateFocusRect();
    }

    iKeyCurrent = SKBFindKeyUnderCursor();
    if (iKeyCurrent == 0xffff) 
    {
        psk = NULL;
    } else {
        psk = &g_pskCurrentSKB[iKeyCurrent];
    }
    return(psk);
} // SKBProcessXMovement          

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBProcessYMovement

Description:

    Moves the focus ring along the Y direction of the SKB if the joystick
    is pressed along the Y-axis.  The SKB "wraps" around the edges, so that
    moving the focus ring off the screen in the +Y direction will move the cursor
    to row 0, etc.

Return Value:
    
    The new key which the cursor is moved to.

-------------------------------------------------------------------*/
SOFTKEY*
SKBProcessYMovement(DIJOYSTATE dijoystate, SOFTKEY* psk, STEP_MOVEMENT bStep)
{
    WORD iKeyCurrent;
    WORD iKeyTemp;
    BOOL bChanged = FALSE;
    WORD i, j;

    // move the y cursor to the left side of the key

    iKeyCurrent = SKBFindKeyUnderCursor();
    if ((dijoystate.lY < 0) || bStep == BACK) 
    {

        if (psk == NULL)
        {
            g_yCursor -= 1;
        }
        else
        {
            g_xCursor = psk->xGridLocation;
            g_yCursor = psk->yGridLocation;
            do 
            {
                iKeyTemp = iKeyCurrent;
                g_yCursor -= 1;
                iKeyCurrent = SKBFindKeyUnderCursor();
            } while (iKeyCurrent == iKeyTemp);
            // now search the space above the key until we get to a new key
            for (j = g_yCursor; j >= 0; j--)
            {
                if (iKeyCurrent != 0xffff || iKeyCurrent == iKeyTemp) break;
                for (i = g_pskCurrentSKB[iKeyTemp].xGridLocation; 
                     i < g_pskCurrentSKB[iKeyTemp].xGridLocation + g_pskCurrentSKB[iKeyTemp].dxColumns; i++)
                {
                    if (iKeyCurrent == 0xffff && iKeyCurrent != iKeyTemp)
                    {
                        g_xCursor = i;
                        g_yCursor = j;
                        iKeyCurrent = SKBFindKeyUnderCursor();
                    }
                }
                if ((j == 0 || j == 0xffff) && iKeyCurrent == 0xffff && iKeyCurrent !=iKeyTemp)
                {
                    j = SKB_ROWS; // will be decremented by loop to SKB_ROWS - 1
                }
            }
        }            
        bChanged = TRUE;
    }
    else if ((dijoystate.lY > 0) || bStep == FORWARD) 
    {
        if (psk == NULL)
        {
            g_yCursor += 1;
        }
        else
        {
            g_xCursor = psk->xGridLocation;
            g_yCursor = psk->yGridLocation + psk->dyRows - 1;
            // move to the next key
            do
            {
                iKeyTemp = iKeyCurrent;
                g_yCursor += 1;
                iKeyCurrent = SKBFindKeyUnderCursor();
            } while (iKeyCurrent == iKeyTemp);
            // now search the space below the key until we get to a new key
            for (j = g_yCursor; j < SKB_ROWS; )
            {
                if (iKeyCurrent != 0xffff || iKeyCurrent == iKeyTemp) break;
                for (i = g_pskCurrentSKB[iKeyTemp].xGridLocation; 
                     i < g_pskCurrentSKB[iKeyTemp].xGridLocation + g_pskCurrentSKB[iKeyTemp].dxColumns; i++)
                {
                    if (iKeyCurrent == 0xffff && iKeyCurrent != iKeyTemp)
                    {
                        g_xCursor = i;
                        g_yCursor = j;
                        iKeyCurrent = SKBFindKeyUnderCursor();
                    }
                }
                if (j == SKB_ROWS-1 && iKeyCurrent == 0xffff && iKeyCurrent !=iKeyTemp)
                {
                    j = 0;
                }
                else
                {
                    j++;
                }
            }
        }
        bChanged = TRUE;
    }

    if (bChanged)
    {
        if (g_yCursor < 0) g_yCursor = SKB_ROWS - 1;
        // g_yCursor is unsigned, so if it equals 0xffff then the focus ring has been moved off
        // the screen and we should wrap the focus ring to the opposite side.
        if (g_yCursor == 0xffff) g_yCursor = SKB_ROWS - 1;
        if (g_yCursor >= SKB_ROWS) g_yCursor = 0;
        SKBUpdateFocusRect();
    }

    iKeyCurrent = SKBFindKeyUnderCursor();
    if (iKeyCurrent == 0xffff) 
    {
        psk = NULL;
    }
    else
    {
        psk = &g_pskCurrentSKB[iKeyCurrent];
    }
    return(psk);
} // SKBProcessYMovement
