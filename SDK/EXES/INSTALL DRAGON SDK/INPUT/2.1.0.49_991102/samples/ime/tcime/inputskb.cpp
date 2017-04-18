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


LPDIRECTINPUTDEVICE2 g_pdidevice2JoystickSKB = NULL;    // joystick



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
SOFTKEY* SKBProcessXMovement(DIJOYSTATE    dijoystate,
                             SOFTKEY*      psk,
                             STEP_MOVEMENT bStep)
{
    WORD iKeyCurrent;
    WORD iKeyTemp;
    BOOL bChanged = FALSE;
    WORD i, j;


    iKeyCurrent = SKBFindKeyUnderCursor();
    if ((dijoystate.lX < 0) || bStep == BACK) {
        if (psk == NULL) {
            g_xSKBCursor -= 1;
        } else {
            g_xSKBCursor = psk->xGridLocation;
            g_ySKBCursor = psk->yGridLocation;
            do {
                iKeyTemp = iKeyCurrent;
                g_xSKBCursor -= 1;
                iKeyCurrent = SKBFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
            // now search the space to the left of the key until we get to a new key
            for (i = g_xSKBCursor; i >= 0; i--) {
                if (iKeyCurrent != 0xffff || iKeyCurrent == iKeyTemp) break;
                for (j = g_pskCurrentSKB[iKeyTemp].yGridLocation; 
                     j < g_pskCurrentSKB[iKeyTemp].yGridLocation + g_pskCurrentSKB[iKeyTemp].dyRows; j++) {
                    if (iKeyCurrent == 0xffff && iKeyCurrent != iKeyTemp) {
                        g_xSKBCursor = i;
                        g_ySKBCursor = j;
                        iKeyCurrent = SKBFindKeyUnderCursor();
                    }
                }
                if ((i == 0 || i == 0xffff) && iKeyCurrent == 0xffff && iKeyCurrent !=iKeyTemp) {
                    i = g_uSKBColumns; // will be decremented by loop to SKB_COLUMNS - 1
                }
            }
        }    
        bChanged = TRUE;
    } else if ((dijoystate.lX > 0) || bStep == FORWARD)  {
        if (psk == NULL) {
            g_xSKBCursor += 1;
        } else {
            g_xSKBCursor = psk->xGridLocation + psk->dxColumns - 1;
            g_ySKBCursor = psk->yGridLocation;
            // move to the next key
            do {
                iKeyTemp = iKeyCurrent;
                g_xSKBCursor += 1;
                iKeyCurrent = SKBFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
            // now search the space to the right of the key until we get to a new key
            for (i = g_xSKBCursor; i < g_uSKBColumns; ) {
                if (iKeyCurrent != 0xffff || iKeyCurrent == iKeyTemp) break;
                for (j = g_pskCurrentSKB[iKeyTemp].yGridLocation; 
                     j < g_pskCurrentSKB[iKeyTemp].yGridLocation + g_pskCurrentSKB[iKeyTemp].dyRows; j++) {
                    if (iKeyCurrent == 0xffff && iKeyCurrent != iKeyTemp) {
                        g_xSKBCursor = i;
                        g_ySKBCursor = j;
                        iKeyCurrent = SKBFindKeyUnderCursor();
                    }
                }
                if (i == g_uSKBColumns-1 && iKeyCurrent == 0xffff && iKeyCurrent !=iKeyTemp) {
                    i = 0;
                } else {
                    i++;
                }
            }
        }
        bChanged = TRUE;
    }

    if (bChanged) {
        // g_xSKBCursor is unsigned, so if it equals 0xffff then the focus ring has been moved off
        // the screen and we should wrap the focus ring to the opposite side.
        if (g_xSKBCursor == 0xffff) g_xSKBCursor = g_uSKBColumns - 1;
        if (g_xSKBCursor >= g_uSKBColumns) g_xSKBCursor = 0;
        SKBUpdateFocusRect();
    }

    iKeyCurrent = SKBFindKeyUnderCursor();
    if (iKeyCurrent == 0xffff) {
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
SOFTKEY* SKBProcessYMovement(DIJOYSTATE    dijoystate,
                             SOFTKEY*      psk,
                             STEP_MOVEMENT bStep)
{
    WORD iKeyCurrent;
    WORD iKeyTemp;
    BOOL bChanged = FALSE;
    WORD i, j;

    // move the y cursor to the left side of the key

    iKeyCurrent = SKBFindKeyUnderCursor();
    if ((dijoystate.lY < 0) || bStep == BACK) {
        if (psk == NULL) {
            g_ySKBCursor -= 1;
        } else {
            g_xSKBCursor = psk->xGridLocation;
            g_ySKBCursor = psk->yGridLocation;
            do {
                iKeyTemp = iKeyCurrent;
                g_ySKBCursor -= 1;
                iKeyCurrent = SKBFindKeyUnderCursor();
            } while (iKeyCurrent == iKeyTemp);
            // now search the space above the key until we get to a new key
            for (j = g_ySKBCursor; j >= 0; j--) {
                if (iKeyCurrent != 0xffff || iKeyCurrent == iKeyTemp) break;
                for (i = g_pskCurrentSKB[iKeyTemp].xGridLocation; 
                     i < g_pskCurrentSKB[iKeyTemp].xGridLocation + g_pskCurrentSKB[iKeyTemp].dxColumns; i++) {
                    if (iKeyCurrent == 0xffff && iKeyCurrent != iKeyTemp) {
                        g_xSKBCursor = i;
                        g_ySKBCursor = j;
                        iKeyCurrent = SKBFindKeyUnderCursor();
                    }
                }
                if ((j == 0 || j == 0xffff) && iKeyCurrent == 0xffff && iKeyCurrent !=iKeyTemp)
                    j = g_uSKBRows; // will be decremented by loop to SKB_ROWS - 1
            }
        }            
        bChanged = TRUE;
    } else if ((dijoystate.lY > 0) || bStep == FORWARD) {
        if (psk == NULL) {
            g_ySKBCursor += 1;
        } else {
            g_xSKBCursor = psk->xGridLocation;
            g_ySKBCursor = psk->yGridLocation + psk->dyRows - 1;
            // move to the next key
            do {
                iKeyTemp = iKeyCurrent;
                g_ySKBCursor += 1;
                iKeyCurrent = SKBFindKeyUnderCursor();
            } while (iKeyCurrent == iKeyTemp);
            // now search the space below the key until we get to a new key
            for (j = g_ySKBCursor; j < g_uSKBRows; ) {
                if (iKeyCurrent != 0xffff || iKeyCurrent == iKeyTemp) break;
                for (i = g_pskCurrentSKB[iKeyTemp].xGridLocation; 
                     i < g_pskCurrentSKB[iKeyTemp].xGridLocation + g_pskCurrentSKB[iKeyTemp].dxColumns; i++) {
                    if (iKeyCurrent == 0xffff && iKeyCurrent != iKeyTemp) {
                        g_xSKBCursor = i;
                        g_ySKBCursor = j;
                        iKeyCurrent = SKBFindKeyUnderCursor();
                    }
                }
                if (j == g_uSKBRows-1 && iKeyCurrent == 0xffff && iKeyCurrent !=iKeyTemp) {
                    j = 0;
                } else {
                    j++;
                }
            }
        }
        bChanged = TRUE;
    }

    if (bChanged) {
        if (g_ySKBCursor < 0) g_ySKBCursor = g_uSKBRows - 1;
        // g_ySKBCursor is unsigned, so if it equals 0xffff then the focus ring has been moved off
        // the screen and we should wrap the focus ring to the opposite side.
        if (g_ySKBCursor == 0xffff) g_ySKBCursor = g_uSKBRows - 1;
        if (g_ySKBCursor >= g_uSKBRows) g_ySKBCursor = 0;
        SKBUpdateFocusRect();
    }

    iKeyCurrent = SKBFindKeyUnderCursor();
    if (iKeyCurrent == 0xffff) {
        psk = NULL;
    } else {
        psk = &g_pskCurrentSKB[iKeyCurrent];
    }
    return(psk);
} // SKBProcessYMovement

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBReadDirectInputDevices

Description:

    Retrieves the current state of the joystick, and takes the 
    appropriate action for the SKB, based on which buttons are pressed.

Return Value:
    
    None.

-------------------------------------------------------------------*/
void SKBReadDirectInputDevices(void)
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
    if (g_pdidevice2JoystickSKB) {
        // If less than 0.05 seconds have elapsed since a button was last
        // pressed, then don't process further joystick input.  If we
        // don't do this, then pressing a button once will send several
        // WM_KEYDOWN messages.

        dwTickLastJoystick = GetTickCount();
        hr = g_pdidevice2JoystickSKB->GetDeviceState(sizeof(DIJOYSTATE), &dijoystate);

        if (FAILED(hr)) {
            g_pdidevice2JoystickSKB->Unacquire();
            g_pdidevice2JoystickSKB->Release();
            g_pdidevice2JoystickSKB = NULL;
        }
        if (hr != DI_OK)
            return;

        iKeyCurrent = SKBFindKeyUnderCursor();
        if (iKeyCurrent == 0xffff) {
            psk = NULL;
        } else {
            psk = &g_pskCurrentSKB[iKeyCurrent];
        }

        // Start button exits
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_START]] & BUTTON_ON) &&
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_START]] != g_rgiPrevButtons[JOYSTICK_START])) {
			PostQuitMessage(0);
        }
        
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_A]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_A]] != g_rgiPrevButtons[JOYSTICK_A])) {
            FillPrevButtons(dijoystate);
            if (psk != NULL) {
                switch (psk->szKeyString[0]) {
                case KANJI_CLOSE_0: // close the keyboard
                    SendKeyEvents(psk->vkCode, 0, 0);
                    PostQuitMessage(0);
                    break;
                case KANJI_CAPSLOCK_0:
                    // caps lock
                    g_swkeybdstate.fCapsOn = !g_swkeybdstate.fCapsOn;
                    SKBRender();
                    break;
                case KANJI_HALF_0:
                    if (g_pskCurrentSKB == g_rgskRomanji) {
                        // swap the double-width state; only for romanji
                        g_swkeybdstate.fDoubleWidth = !g_swkeybdstate.fDoubleWidth;
                        SKBRender();
                    }
                    break;
                case KANJI_DELETE_0:
                    SendKeyEvents(psk->vkCode, 0, 0);
                    break;
                case KANJI_PHONETIC_0:
                    // switch to Phonetic keyboard
                    SKBSetLayout(PHONETIC);
                    SKBRender();
                    SetIMEState(&g_swkeybdstate);
                    break;
                case KANJI_ENGLISH_0:
                    // switch to Romanji keyboard
                    SKBSetLayout(ROMANJI);
                    SKBRender();
                    SetIMEState(&g_swkeybdstate);
                    if (g_bRWNDactive || g_bCWNDactive) {
                        SendKeyEvents(VK_ESCAPE, 0, 0);
                    }
                    break;
                case KANJI_SYMBOLS_0:
                    // switch to Romanji keyboard
                    SKBSetLayout(SYMBOLS);
                    SKBRender();
                    SetIMEState(&g_swkeybdstate);
                    if (g_bRWNDactive || g_bCWNDactive) {
                        SendKeyEvents(VK_ESCAPE, 0, 0);
                    }
                    break;
                case KANJI_SPACE_0: // space bar
                    SendKeyEvents(psk->vkCode, 1, psk->vkCode);
                    break;        
                case SYMBOL_LEFT_ARROW:
                case SYMBOL_RIGHT_ARROW:
                case SYMBOL_UP_ARROW:
                case SYMBOL_DOWN_ARROW:
                    if (psk->vkCode) {
                        SendKeyEvents(psk->vkCode, 0, 0);
                    } else {
                        if (g_pskCurrentSKB == g_rgskPhonetic) {
                            SKBProcessPhoneticKey(psk->szKeyString[0]);
                        } else if (g_pskCurrentSKB == g_rgskRomanji) {
                            SKBProcessRomanjiKey(psk->szKeyString[0]);
                        } else if (g_pskCurrentSKB == g_rgskSymbol) {
                            SKBProcessSymbolKey(psk->szKeyString[0]);
                        } else {
                        }
                    }
                    break;        
                default:
                    // just post the KEYDOWN message, in regular, half-width, or
                    // half-height state; also, we need to index into KeyMap if it's
                    // necessary
                    if (g_pskCurrentSKB == g_rgskPhonetic) {
                        SKBProcessPhoneticKey(psk->szKeyString[0]);
                    } else if (g_pskCurrentSKB == g_rgskRomanji) {
                        SKBProcessRomanjiKey(psk->szKeyString[0]);
                    } else if (g_pskCurrentSKB == g_rgskSymbol) {
                        SKBProcessSymbolKey(psk->szKeyString[0]);
                    } else {
                    }
                    break;
                }
            }    

        }

        // Y button is used to convert
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_Y]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_Y]] != g_rgiPrevButtons[JOYSTICK_Y])) {
            FillPrevButtons(dijoystate);
            // unacquire the joystick so that the IME can get it
            g_pdidevice2JoystickSKB->Unacquire();
            SendKeyEvents(VK_CONVERT, 0, 0);
        }

        // X button is used to backspace.
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_X]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_X]] != g_rgiPrevButtons[JOYSTICK_X])) {
            FillPrevButtons(dijoystate);
            SendKeyEvents(VK_BACK, 0, 0);
        }

        // B button is used to determine the characters.
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_B]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_B]] != g_rgiPrevButtons[JOYSTICK_B])) {
            FillPrevButtons(dijoystate);
            SendKeyEvents(VK_RETURN, 0, 0);
        }

        if (g_fAnalogJoystick) {
            // LA button is used to step left
            if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_LA]] & BUTTON_ON) && 
                (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_LA]] != g_rgiPrevButtons[JOYSTICK_LA])) {
                FillPrevButtons(dijoystate);
                dwTickLastXMovement = GetTickCount();
                SendKeyEvents(VK_LEFT, 0, 0);
            }
            // RA button is used to step right
            if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_RA]] & BUTTON_ON) && 
                (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_RA]] != g_rgiPrevButtons[JOYSTICK_RA])) {
                FillPrevButtons(dijoystate);
                dwTickLastXMovement = GetTickCount();
                SendKeyEvents(VK_RIGHT, 0, 0);
            }
            // DA button is used to step down
            if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_DA]] & BUTTON_ON) && 
                (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_DA]] != g_rgiPrevButtons[JOYSTICK_DA])) {
                FillPrevButtons(dijoystate);
                dwTickLastYMovement = GetTickCount();
                SendKeyEvents(VK_DOWN, 0, 0);
            }
            // UA button is used to step up
            if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_UA]] & BUTTON_ON) && 
                (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_UA]] != g_rgiPrevButtons[JOYSTICK_UA])) {
                FillPrevButtons(dijoystate);
                dwTickLastYMovement = GetTickCount();
                SendKeyEvents(VK_UP, 0, 0);
            }
        } else {
            // LA button is used to step left
            if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_LA]] & BUTTON_ON) && 
                (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_LA]] != g_rgiPrevButtons[JOYSTICK_LA])) {
                FillPrevButtons(dijoystate);
                dwTickLastXMovement = GetTickCount();
                do {
                    psk = SKBProcessXMovement(dijoystate, psk, BACK);
                } while (psk == NULL);
            }
            // RA button is used to step right
            if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_RA]] & BUTTON_ON) && 
                (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_RA]] != g_rgiPrevButtons[JOYSTICK_RA])) {
                FillPrevButtons(dijoystate);
                dwTickLastXMovement = GetTickCount();
                do {
                    psk = SKBProcessXMovement(dijoystate, psk, FORWARD);
                } while (psk == NULL);
            }
            // DA button is used to step down
            if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_DA]] & BUTTON_ON) && 
                (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_DA]] != g_rgiPrevButtons[JOYSTICK_DA])) {
                FillPrevButtons(dijoystate);
                dwTickLastYMovement = GetTickCount();
                do {
                    psk = SKBProcessYMovement(dijoystate, psk, FORWARD);
                } while (psk == NULL);
            }
            // UA button is used to step up
            if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_UA]] & BUTTON_ON) && 
                (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_UA]] != g_rgiPrevButtons[JOYSTICK_UA])) {
                FillPrevButtons(dijoystate);
                dwTickLastYMovement = GetTickCount();
                do {
                    psk = SKBProcessYMovement(dijoystate, psk, BACK);
                } while (psk == NULL);
            }
        }

        dwXRepeatRate = 0;
        dwYRepeatRate = 0;


        // Calculate the repeat rates for + and - X and Y directions --> the further the joystick
        // is pressed in one direction, the less time between successive movements on the 
        // SKB.
        if (dijoystate.lX < -LOWER_JOYSTICK_THRESHOLD) {
            dwXRepeatRate = SLOW_REPEAT_RATE - ((-dijoystate.lX) - LOWER_JOYSTICK_THRESHOLD) *
                (SLOW_REPEAT_RATE - FAST_REPEAT_RATE) /
                (UPPER_JOYSTICK_THRESHOLD - LOWER_JOYSTICK_THRESHOLD);
        }
        if (dijoystate.lX > LOWER_JOYSTICK_THRESHOLD) {
            dwXRepeatRate = SLOW_REPEAT_RATE - (dijoystate.lX - LOWER_JOYSTICK_THRESHOLD) *
                (SLOW_REPEAT_RATE - FAST_REPEAT_RATE) /
                (UPPER_JOYSTICK_THRESHOLD - LOWER_JOYSTICK_THRESHOLD);
        }

        if (dijoystate.lY < -LOWER_JOYSTICK_THRESHOLD) {
            dwYRepeatRate = SLOW_REPEAT_RATE - ((-dijoystate.lY) - LOWER_JOYSTICK_THRESHOLD) *
                (SLOW_REPEAT_RATE - FAST_REPEAT_RATE) /
                (UPPER_JOYSTICK_THRESHOLD - LOWER_JOYSTICK_THRESHOLD);
        }
        if (dijoystate.lY > LOWER_JOYSTICK_THRESHOLD) {
            dwYRepeatRate = SLOW_REPEAT_RATE - (dijoystate.lY - LOWER_JOYSTICK_THRESHOLD) *
                (SLOW_REPEAT_RATE - FAST_REPEAT_RATE) /
                (UPPER_JOYSTICK_THRESHOLD - LOWER_JOYSTICK_THRESHOLD);
        }

        if (((GetTickCount() - dwTickLastXMovement) > dwXRepeatRate) && (dwXRepeatRate > 0)) {
            dwTickLastXMovement = GetTickCount();
            do {
                psk = SKBProcessXMovement(dijoystate, psk, NONE);
            } while (psk == NULL);
        }            

        if (((GetTickCount() - dwTickLastYMovement) > dwYRepeatRate) && (dwYRepeatRate > 0)) {
            dwTickLastYMovement = GetTickCount();
            do {
                psk = SKBProcessYMovement(dijoystate, psk, NONE);
            } while (psk == NULL);
        }            

        // Poll the device now, so the data will be ready the next time around.
        FillPrevButtons(dijoystate);
        hr = g_pdidevice2JoystickSKB->Poll();

        if (FAILED(hr)) {
            g_pdidevice2JoystickSKB->Unacquire();
            g_pdidevice2JoystickSKB->Release();
            g_pdidevice2JoystickSKB = NULL;
        } 
        if (hr != DI_OK)
            return;
    } else {
        if (GetTickCount() - dwTickLastJoystick > 500) {        
            CreateDirectInput(g_hInstance, g_hwndAPP, &g_pdidevice2JoystickSKB);

            if (g_pdidevice2JoystickSKB && !g_bCWNDactive) 
                AcquireJoystick(&g_pdidevice2JoystickSKB);

            dwTickLastJoystick = GetTickCount();
        }
    }
} // SKBReadDirectInputDevices

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBConvertPhoneticKey

Description:

    Convert phonetic key based on SKB state (could be half-height
    character, full-height character, or non-Phonetic key).

Return Value:
    
    None.
-------------------------------------------------------------------*/
TCHAR SKBConvertPhoneticKey(TCHAR wcCharacter)
{
	switch(wcCharacter) { // must account for hard-coded skb "function keys"
    case KANJI_CLOSE_0:
    case KANJI_CAPSLOCK_0:
    case KANJI_HALF_0:
    case KANJI_DELETE_0:
    case KANJI_PHONETIC_0:
    case KANJI_ENGLISH_0:
    case KANJI_SYMBOLS_0:
    case KANJI_SPACE_0:
    case SYMBOL_LEFT_ARROW:
    case SYMBOL_RIGHT_ARROW:
    case SYMBOL_UP_ARROW:
    case SYMBOL_DOWN_ARROW:
        return 0;
    default:
        break;
	}

    if ((wcCharacter >= FIRST_PHONETIC) && (wcCharacter <= LAST_PHONETIC)) {
        return wcCharacter;
    } else if ((wcCharacter >= ROMAN_START) && (wcCharacter <= ROMAN_END)) {
        return wcCharacter + ROMAN_DOUBLEWIDTH_OFFSET;
	} else if ((wcCharacter == PHON_TONE0) || (wcCharacter == PHON_TONE2) ||
               (wcCharacter == PHON_TONE3) || (wcCharacter == PHON_TONE4)) {
        return wcCharacter;
    } else {
	}

	return wcCharacter;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBProcessPhoneticKey

Description:

    Send a WM_CHAR message for a phonetic key.

Return Value:
    
    None.
-------------------------------------------------------------------*/
void SKBProcessPhoneticKey(TCHAR wcCharacter)
{
	UINT uConvertedChar = (UINT)SKBConvertPhoneticKey(wcCharacter);

	if (uConvertedChar) {
        SendKeyEvents(VK_PROCESSKEY, 1, uConvertedChar);
    } else {
		// Beep!
		;
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBConvertRomanjiKey

Description:

    Convert romaji key based on SKB state.

Return Value:
    
    None.

-------------------------------------------------------------------*/
TCHAR SKBConvertRomanjiKey(TCHAR wcCharacter)
{
	switch(wcCharacter) { // must account for hard-coded skb "function keys"
    case KANJI_CLOSE_0:
    case KANJI_CAPSLOCK_0:
    case KANJI_HALF_0:
    case KANJI_DELETE_0:
    case KANJI_PHONETIC_0:
    case KANJI_ENGLISH_0:
    case KANJI_SYMBOLS_0:
    case KANJI_SPACE_0:
    case SYMBOL_LEFT_ARROW:
    case SYMBOL_RIGHT_ARROW:
    case SYMBOL_UP_ARROW:
    case SYMBOL_DOWN_ARROW:
        return 0;
	}

    if ((wcCharacter >= ROMAN_A) && (wcCharacter <= ROMAN_Z)) {
        if (!g_swkeybdstate.fCapsOn)
            wcCharacter += ROMAN_ALPHABET_GAP;
    }

    if (g_swkeybdstate.fDoubleWidth) {
		if ((wcCharacter >= ROMAN_START) && (wcCharacter <= ROMAN_END))
			wcCharacter += ROMAN_DOUBLEWIDTH_OFFSET;
	} else {
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
void SKBProcessRomanjiKey(TCHAR wcCharacter)
{
	TCHAR wcConvertedChar = SKBConvertRomanjiKey(wcCharacter);

	if(wcConvertedChar)
		SendKeyEvents(VK_PROCESSKEY, 1, wcConvertedChar);                            
	else
		// Beep!
		;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBConvertSymbolKey

Description:

    Convert symbol key based on SKB state (could be half-height
    character, full-height character, or non-Phonetic key).

Return Value:
    
    None.
-------------------------------------------------------------------*/
TCHAR SKBConvertSymbolKey(TCHAR wcCharacter)
{
	switch(wcCharacter) { // must account for hard-coded skb "function keys"
    case KANJI_CLOSE_0:
    case KANJI_CAPSLOCK_0:
    case KANJI_HALF_0:
    case KANJI_DELETE_0:
    case KANJI_PHONETIC_0:
    case KANJI_ENGLISH_0:
    case KANJI_SYMBOLS_0:
    case KANJI_SPACE_0:
        return 0;
    default:
        break;
	}

    if ((wcCharacter >= ROMAN_START) && (wcCharacter <= ROMAN_END)) {
        wcCharacter += ROMAN_DOUBLEWIDTH_OFFSET;
	} else {
	}

	return wcCharacter;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SKBProcessSymbolKey

Description:

    Send a WM_CHAR message for a symbol key.

Return Value:
    
    None.
-------------------------------------------------------------------*/
void SKBProcessSymbolKey(TCHAR wcCharacter)
{
	UINT uConvertedChar = (UINT)SKBConvertSymbolKey(wcCharacter);

	if (uConvertedChar) {
        SendKeyEvents(VK_PROCESSKEY, 1, uConvertedChar);
    } else {
		// Beep!
		;
    }
}


