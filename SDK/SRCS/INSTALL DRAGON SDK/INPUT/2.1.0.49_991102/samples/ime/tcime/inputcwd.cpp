/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    inputcwd.cpp

Abstract:

    This file contains functions which manage input to the kanji selection window (CWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hxx"


LPDIRECTINPUTDEVICE2    g_pdidevice2JoystickCWND = NULL;   // joystick


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:
    CWNDProcessXMovement

Description:

    In candidate window, it will be page down or up when the joystick
    is pressed along the X-axis.

Return Value:
    
    The new key which the cursor is moved to.

-------------------------------------------------------------------*/
CWNDKEY* CWNDProcessXMovement(DIJOYSTATE    dijoystate,
                              CWNDKEY*      psk,
                              WORD*         puKeyTop,
                              STEP_MOVEMENT bStep)
{
    WORD iKeyCurrent;       // row which is currently the top displayed row
    WORD iKeyTemp;
    BOOL bChanged = FALSE;  // set to true if the cursor moves in the x-direction

    iKeyCurrent = CWNDFindKeyUnderCursor();
    if ((dijoystate.lX < 0) || bStep == BACK) {
        if (psk == NULL) {
            if (g_yCWNDCursor < CWND_ROWS) {
                g_yCWNDCursor = 0xffff;
            } else {
                g_yCWNDCursor -= CWND_ROWS;
            }
        } else {
            do {
                iKeyTemp = iKeyCurrent;
                if (g_yCWNDCursor < CWND_ROWS) {
                    g_yCWNDCursor = 0xffff;
                } else {
                    g_yCWNDCursor -= CWND_ROWS;
                }
                iKeyCurrent = CWNDFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
        }
        bChanged = TRUE;
    } else if ((dijoystate.lX > 0) || bStep == FORWARD) {
        if (psk == NULL) {
            g_yCWNDCursor += CWND_ROWS;
        } else {
            do {
                iKeyTemp = iKeyCurrent;
                g_yCWNDCursor += CWND_ROWS;
                iKeyCurrent = CWNDFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
        }
        bChanged = TRUE;
    }

    // g_yCWNDCursor is unsigned, so if it equals 0xffff then the focus ring has been moved off
    // the screen.  We _do not_ wrap this window.
    if (bChanged) {
        if (g_yCWNDCursor == 0xffff) g_yCWNDCursor = 0;
        if (g_yCWNDCursor >= g_cCurrentCWNDKeys / CWND_COLUMNS)
            g_yCWNDCursor = g_cCurrentCWNDKeys / CWND_COLUMNS;
        // make sure we're not in the "dead space" on the last row of keys, which may
        // not be a complete row of keys
        if (g_xCWNDCursor + g_yCWNDCursor * CWND_COLUMNS >= g_cCurrentCWNDKeys) {
            g_yCWNDCursor = g_cCurrentCWNDKeys / CWND_COLUMNS - 1;
            // also, scroll down if we can scroll down
            if (g_yCWNDCursor >= *puKeyTop + CWND_ROWS) {
                *puKeyTop += CWND_ROWS;
                g_uFocusCWNDKey = 0xffff;
                CWNDRender(*puKeyTop);
            }
        }

        // determine whether the cursor is scrolling up or down, or neither
        if (g_yCWNDCursor < *puKeyTop) {
            *puKeyTop -= CWND_ROWS;
            g_uFocusCWNDKey = 0xffff;
            CWNDRender(*puKeyTop);
        } else if (g_yCWNDCursor >= (*puKeyTop + CWND_ROWS)) {
            *puKeyTop += CWND_ROWS;
            g_uFocusCWNDKey = 0xffff;
            CWNDRender(*puKeyTop);
        }
        CWNDUpdateFocusRect(*puKeyTop, CWNDFindKeyUnderCursor());
    }

    iKeyCurrent = CWNDFindKeyUnderCursor();
    if (iKeyCurrent == 0xffff) {
        psk = NULL;
    } else {
        psk = &g_pskCurrentCWND[iKeyCurrent];
    }

    return(psk);
} // CWNDProcessXMovement          

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDProcessYMovement

Description:

    Moves the focus ring along the Y direction of the CWND if the joystick
    is pressed along the Y-axis.  The CWND scrolls up and down.

Return Value:
    
    The new key which the cursor is moved to.

-------------------------------------------------------------------*/
CWNDKEY* CWNDProcessYMovement(DIJOYSTATE    dijoystate,
                              CWNDKEY*      psk,
                              WORD*         puKeyTop,
                              STEP_MOVEMENT bStep)
{
    WORD iKeyCurrent;           // row which is currently the top displayed row
    WORD iKeyTemp;
    BOOL bChanged = FALSE;     // set to true if the cursor moves in the y-direction

    iKeyCurrent = CWNDFindKeyUnderCursor();
    if ((dijoystate.lY < 0) || bStep == BACK) {
        if (psk == NULL) {
            g_yCWNDCursor -= 1;
        } else {
            do {
                iKeyTemp = iKeyCurrent;
                g_yCWNDCursor -= 1;
                iKeyCurrent = CWNDFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
        }
        bChanged = TRUE;
    } else if ((dijoystate.lY > 0) || bStep == FORWARD) {
        if (psk == NULL) {
            g_yCWNDCursor += 1;
        } else {
            do {
                iKeyTemp = iKeyCurrent;
                g_yCWNDCursor += 1;
                iKeyCurrent = CWNDFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
        }
        bChanged = TRUE;
    }

    // g_yCWNDCursor is unsigned, so if it equals 0xffff then the focus ring has been moved off
    // the screen.  We _do not_ wrap this window.
    if (bChanged) {
        if (g_yCWNDCursor == 0xffff) g_yCWNDCursor = 0;
        if (g_yCWNDCursor >= g_cCurrentCWNDKeys / CWND_COLUMNS)
            g_yCWNDCursor = g_cCurrentCWNDKeys / CWND_COLUMNS;
        // make sure we're not in the "dead space" on the last row of keys, which may
        // not be a complete row of keys
        if (g_xCWNDCursor + g_yCWNDCursor * CWND_COLUMNS >= g_cCurrentCWNDKeys) {
            g_yCWNDCursor = g_cCurrentCWNDKeys / CWND_COLUMNS - 1;
            // also, scroll down if we can scroll down
            if ((g_yCWNDCursor + 1 == *puKeyTop + CWND_ROWS) &&
                (*puKeyTop + CWND_ROWS < g_cCurrentCWNDKeys)) {
                *puKeyTop += CWND_ROWS;
                g_uFocusCWNDKey = 0xffff;
                CWNDRender(*puKeyTop);
            }
        }

        // determine whether the cursor is scrolling up or down, or neither
        if ((g_yCWNDCursor < *puKeyTop) && (*puKeyTop > 0)) {
            *puKeyTop -= CWND_ROWS;
            g_uFocusCWNDKey = 0xffff;
            CWNDRender(*puKeyTop);
        } else if ((g_yCWNDCursor >= *puKeyTop + CWND_ROWS) &&
                   (*puKeyTop + CWND_ROWS < g_cCurrentCWNDKeys)) {
            *puKeyTop += CWND_ROWS;
            g_uFocusCWNDKey = 0xffff;
            CWNDRender(*puKeyTop);
        }
        CWNDUpdateFocusRect(*puKeyTop, CWNDFindKeyUnderCursor());
    }

    iKeyCurrent = CWNDFindKeyUnderCursor();
    if (iKeyCurrent == 0xffff) {
        psk = NULL;
    } else {
        psk = &g_pskCurrentCWND[iKeyCurrent];
    }
    return(psk);
} // CWNDProcessYMovement

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDReadDirectInputDevices

Description:

    Read the joystick and process the result.

Return Value:
    
    TRUE if the user selected a character from the window, FALSE if not.

-------------------------------------------------------------------*/
BOOL CWNDReadDirectInputDevices(WORD* puKeyTop)
{
    DIJOYSTATE      dijoystate;
    HRESULT         hr;
    static DWORD    dwTickLastXMovement = 0;
    static DWORD    dwTickLastYMovement = 0;
    DWORD           dwXRepeatRate;
    DWORD           dwYRepeatRate;
    WORD            iKeyCurrent;
    CWNDKEY*        psk;
    static DWORD    dwTickLastJoystick = 0;

    // If there's a joystick, the joystick's current state, and act appropriately.
    if (g_pdidevice2JoystickCWND) {
        dwTickLastJoystick = GetTickCount();
        // If less than 0.05 seconds have elapsed since a button was last
        // pressed, then don't process further joystick input.  If we
        // don't do this, then pressing a button once will send several
        // WM_KEYDOWN messages.
   
        hr = g_pdidevice2JoystickCWND->GetDeviceState(sizeof(DIJOYSTATE), &dijoystate);

        if (FAILED(hr)) {
            g_pdidevice2JoystickCWND->Unacquire();
            g_pdidevice2JoystickCWND->Release();
            g_pdidevice2JoystickCWND = NULL;
        }
        if (hr != DI_OK)
            return(0);

        iKeyCurrent = CWNDFindKeyUnderCursor();
        if (iKeyCurrent == 0xffff) {
            psk = NULL;
        } else {
            psk = &g_pskCurrentCWND[iKeyCurrent];
        }

        if (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_START]] & BUTTON_ON) {
            PostQuitMessage(0);
            return 1;
        }
 
        // X button is no function
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_X]] & BUTTON_ON) &&
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_X]] != g_rgiPrevButtons[JOYSTICK_X])) {
            FillPrevButtons(dijoystate);
            // unacquire the joystick
            g_pdidevice2JoystickCWND->Unacquire();
            // tell the soft keyboard to reacquire the joystick
            g_bSKBReacquireJoystick = TRUE;
            // the user rejected all of the kanji
            SendKeyEvents(VK_ESCAPE, 0, 0);
            return 1;
        }
 
        // A button is selecting character
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_A]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_A]] != g_rgiPrevButtons[JOYSTICK_A])) {
            FillPrevButtons(dijoystate);
            if (psk != NULL) {
                // unacquire the joystick
	            g_pdidevice2JoystickCWND->Unacquire();
		        // set the SKB back to active
			    g_bCWNDactive = FALSE;
                // tell the soft keyboard to reacquire the joystick
				g_bSKBReacquireJoystick = TRUE;
                SendKeyEvents(VK_PROCESSKEY, 1, psk->szKeyString[0]);
            }
            return 1;
        }

        // Y button is used as REJECT
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_Y]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_Y]] != g_rgiPrevButtons[JOYSTICK_Y])) {
            FillPrevButtons(dijoystate);
            if (psk != NULL) {
                // unacquire the joystick
	            g_pdidevice2JoystickCWND->Unacquire();
		        // set the SKB back to active
			    g_bCWNDactive = FALSE;
                // tell the soft keyboard to reacquire the joystick
				g_bSKBReacquireJoystick = TRUE;
                SendKeyEvents(VK_PROCESSKEY, 1, psk->szKeyString[0]);
            }
            return 1;
        }

        // B button is no function
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_B]] & BUTTON_ON) &&
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_B]] != g_rgiPrevButtons[JOYSTICK_B])) {
            FillPrevButtons(dijoystate);
            // unacquire the joystick
            g_pdidevice2JoystickCWND->Unacquire();
            // tell the soft keyboard to reacquire the joystick
            g_bSKBReacquireJoystick = TRUE;
            // the user rejected all of the kanji
            SendKeyEvents(VK_ESCAPE, 0, 0);
            return 1;
        }

        // LA button is used to step left
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_LA]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_LA]] != g_rgiPrevButtons[JOYSTICK_LA])) {
            FillPrevButtons(dijoystate);
            dwTickLastXMovement = GetTickCount();
            do {
                psk = CWNDProcessXMovement(dijoystate, psk, puKeyTop, BACK);
            } while (psk == NULL);
        }
        // RA button is used to step right
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_RA]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_RA]] != g_rgiPrevButtons[JOYSTICK_RA])) {
            FillPrevButtons(dijoystate);
            dwTickLastXMovement = GetTickCount();
            do {
                psk = CWNDProcessXMovement(dijoystate, psk, puKeyTop, FORWARD);
            } while (psk == NULL);
        }
        // DA button is used to step down
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_DA]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_DA]] != g_rgiPrevButtons[JOYSTICK_DA])) {
            FillPrevButtons(dijoystate);
            dwTickLastYMovement = GetTickCount();
            do {
                psk = CWNDProcessYMovement(dijoystate, psk, puKeyTop, FORWARD);
            } while (psk == NULL);
        }
        // UA button is used to step up
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_UA]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_UA]] != g_rgiPrevButtons[JOYSTICK_UA])) {
            FillPrevButtons(dijoystate);
            dwTickLastYMovement = GetTickCount();
            do {
                psk = CWNDProcessYMovement(dijoystate, psk, puKeyTop, BACK);
            } while (psk == NULL);
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
#if 0   // We don't do the XMovement in this action. i.e. PageUp/PageDn.
            dwTickLastXMovement = GetTickCount();
            do {
                psk = CWNDProcessXMovement(dijoystate, psk, puKeyTop, NONE);
            } while (psk == NULL);
#endif
        }            

        if (((GetTickCount() - dwTickLastYMovement) > dwYRepeatRate) && (dwYRepeatRate > 0)) {
            dwTickLastYMovement = GetTickCount();
            do {
                psk = CWNDProcessYMovement(dijoystate, psk, puKeyTop, NONE);
            } while (psk == NULL);
        }            

        // Poll the device now, so the data will be ready the next time around.
        FillPrevButtons(dijoystate);
        hr = g_pdidevice2JoystickCWND->Poll();
        if (FAILED(hr)) {
            g_pdidevice2JoystickCWND->Unacquire();
            g_pdidevice2JoystickCWND->Release();
            g_pdidevice2JoystickCWND = NULL;
        } 
    } else {
        if (GetTickCount() - dwTickLastJoystick > 500) {
            CreateDirectInput(g_hInstance, g_hwndAPP, &g_pdidevice2JoystickCWND);

            if (g_pdidevice2JoystickCWND && g_bCWNDactive) 
                AcquireJoystick(&g_pdidevice2JoystickCWND);        

            dwTickLastJoystick = GetTickCount();
        }
    }
    return(0);
} // CWNDReadDirectInputDevices
