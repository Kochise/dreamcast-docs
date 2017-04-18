
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    inputkwnd.cxx

Abstract:

    This file contains functions which manage input to the kanji selection window (KWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hpp"


LPDIRECTINPUTDEVICE2            g_pdidevice2JoystickIME = NULL;   // joystick


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:
    KWNDProcessXMovement

Description:

    Moves the focus ring along the X direction of the SKB if the joystick
    is pressed along the X-axis.  

Return Value:
    
    The new key which the cursor is moved to.

-------------------------------------------------------------------*/

KWNDKEY*
KWNDProcessXMovement(DIJOYSTATE dijoystate, KWNDKEY* psk, WORD *iKeyTop, STEP_MOVEMENT bStep)
{
    WORD iKeyCurrent;        // row which is currently the top displayed row
    WORD iKeyTemp;

    iKeyCurrent = KWNDFindKeyUnderCursor();
    if ((dijoystate.lX < 0) || bStep == BACK) 
    {
        if (psk == NULL)
        {
            g_xKWNDCursor -= 1;
        } else {
            do 
            {
                iKeyTemp = iKeyCurrent;
                g_xKWNDCursor -= 1;
                iKeyCurrent = KWNDFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
        }    
        KWNDUpdateFocusRect (*iKeyTop, KWNDFindKeyUnderCursor());
    }
    else if ((dijoystate.lX > 0) || bStep == FORWARD) 
    {
        if (psk == NULL)
        {
            g_xKWNDCursor += 1;
        } else {
            do 
            {
                iKeyTemp = iKeyCurrent;
                g_xKWNDCursor += 1;
                iKeyCurrent = KWNDFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
        }
        KWNDUpdateFocusRect (*iKeyTop, KWNDFindKeyUnderCursor());    
    }
    // g_xKWNDCursor is unsigned, so if it equals 0xffff then the focus ring has been moved off
    // the screen and we should put the focus ring back on the board
    if (g_xKWNDCursor == 0xffff) g_xKWNDCursor = 0;
    if (g_xKWNDCursor >= KWND_COLUMNS) g_xKWNDCursor = KWND_COLUMNS - 1;
    if (g_xKWNDCursor + g_yKWNDCursor * KWND_COLUMNS >= g_cCurrentKWNDKeys)
        g_xKWNDCursor = g_cCurrentKWNDKeys % KWND_COLUMNS - 1;

    iKeyCurrent = KWNDFindKeyUnderCursor();
    if (iKeyCurrent == 0xffff) 
    {
        psk = NULL;
    } else {
        psk = &g_pskCurrentKWND[iKeyCurrent];
    }

    return(psk);
} // KWNDProcessXMovement          

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    KWNDProcessYMovement

Description:

    Moves the focus ring along the Y direction of the KWND if the joystick
    is pressed along the Y-axis.  The KWND scrolls up and down.

Return Value:
    
    The new key which the cursor is moved to.

-------------------------------------------------------------------*/
KWNDKEY*
KWNDProcessYMovement(DIJOYSTATE dijoystate, KWNDKEY* psk, WORD *iKeyTop, STEP_MOVEMENT bStep)
{
    WORD iKeyCurrent;           // row which is currently the top displayed row
    WORD iKeyTemp;
    BOOL bChanged = FALSE;     // set to true if the cursor moves in the y-direction

    iKeyCurrent = KWNDFindKeyUnderCursor();
    if ((dijoystate.lY < 0) || bStep == BACK) 
    {
        if (psk == NULL)
        {
            g_yKWNDCursor -= 1;
        } else {
            do 
            {
                iKeyTemp = iKeyCurrent;
                g_yKWNDCursor -= 1;
                iKeyCurrent = KWNDFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
        }
        bChanged = TRUE;
    }
    else if ((dijoystate.lY > 0) || bStep == FORWARD) 
    {
        if (psk == NULL)
        {
            g_yKWNDCursor += 1;
        } else {
            do 
            {
                iKeyTemp = iKeyCurrent;
                g_yKWNDCursor += 1;
                iKeyCurrent = KWNDFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
        }
        bChanged = TRUE;
    }

    // g_yKWNDCursor is unsigned, so if it equals 0xffff then the focus ring has been moved off
    // the screen.  We _do not_ wrap this window.
    if (bChanged) 
    {
        if (g_yKWNDCursor == 0xffff) g_yKWNDCursor = 0;
        if (g_yKWNDCursor >= g_cCurrentKWNDKeys / KWND_COLUMNS) g_yKWNDCursor = 
            g_cCurrentKWNDKeys / KWND_COLUMNS;
        // make sure we're not in the "dead space" on the last row of keys, which may
        // not be a complete row of keys
        if (g_xKWNDCursor + g_yKWNDCursor * KWND_COLUMNS >= g_cCurrentKWNDKeys) {
            g_yKWNDCursor = g_cCurrentKWNDKeys / KWND_COLUMNS - 1;
            // also, scroll down if we can scroll down
            if (g_yKWNDCursor + 1 == *iKeyTop + KWND_ROWS) 
            {
                *iKeyTop += KWND_ROWS - 1;
                KWNDRender(*iKeyTop);
            }
        }

        // determine whether the cursor is scrolling up or down, or neither
        if (g_yKWNDCursor < *iKeyTop) 
        {
            *iKeyTop -= (KWND_ROWS - 1);
            KWNDRender(*iKeyTop);
        } else if (g_yKWNDCursor >= (*iKeyTop + KWND_ROWS)) {
            *iKeyTop += (KWND_ROWS - 1);
            KWNDRender(*iKeyTop);
        }
        KWNDUpdateFocusRect(*iKeyTop, KWNDFindKeyUnderCursor());
    }

    iKeyCurrent = KWNDFindKeyUnderCursor();
    if (iKeyCurrent == 0xffff) 
    {
        psk = NULL;
    } else {
        psk = &g_pskCurrentKWND[iKeyCurrent];
    }
    return(psk);
} // KWNDProcessYMovement

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    KWNDReadDirectInputDevices

Description:

    Read the joystick and process the result.

Return Value:
    
    TRUE if the user selected a character from the window, FALSE if not.

-------------------------------------------------------------------*/
BOOL
KWNDReadDirectInputDevices(WORD *iKeyTop)
{
    DIJOYSTATE              dijoystate;
    HRESULT                 hr;
    static DWORD            dwTickLastXMovement = 0;
    static DWORD            dwTickLastYMovement = 0;
    DWORD                   dwXRepeatRate;
    DWORD                   dwYRepeatRate;
    WORD                    iKeyCurrent;
    KWNDKEY*                psk;
    static DWORD            dwTickLastJoystick = 0;
    UINT                    ch;
    UINT                    dummy;

    // If there's a joystick, the joystick's current state, and act appropriately.
    if (g_pdidevice2JoystickIME)
    {
        dwTickLastJoystick = GetTickCount();
        // If less than 0.05 seconds have elapsed since a button was last
        // pressed, then don't process further joystick input.  If we
        // don't do this, then pressing a button once will send several
        // WM_KEYDOWN messages.
   
        hr = g_pdidevice2JoystickIME->GetDeviceState (sizeof(DIJOYSTATE), &dijoystate);

        if (FAILED(hr))
        {
            g_pdidevice2JoystickIME->Unacquire();
            g_pdidevice2JoystickIME->Release();
            g_pdidevice2JoystickIME = NULL;
        }
        if (hr != DI_OK)
            return(0);

        iKeyCurrent = KWNDFindKeyUnderCursor();
        if (iKeyCurrent == 0xffff) 
        {
            psk = NULL;
        } else {
            psk = &g_pskCurrentKWND[iKeyCurrent];
        }

        if (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_START]] & BUTTON_ON)
        {
            PostQuitMessage (0);
            return 1;
        }
 
        if (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_X]] & BUTTON_ON)
        {
            FillPrevButtons(dijoystate);
            // the user rejected all of the kanji
            // PostMessage(g_hwndApp, WM_IME_CHAR, REJECT, 0);
            ch = ' ';
            PostKeybdMessage((HWND) -1, VK_LEFT, KeyStateDownFlag, 0, &dummy, &ch);
            return(1);
        }
 
        // select character (A button)
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_A]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_A]] != g_rgiPrevButtons[JOYSTICK_A]))
        {
            FillPrevButtons(dijoystate);
            // the user rejected all of the kanji
            // PostMessage(g_hwndApp, WM_IME_CHAR, REJECT, 0);
            ch = ' ';
            PostKeybdMessage((HWND) -1, VK_RIGHT, KeyStateDownFlag, 0, &dummy, &ch);
            return(1);
        }


        // Y button is used as REJECT
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_Y]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_Y]] != g_rgiPrevButtons[JOYSTICK_Y]))
        {
            FillPrevButtons(dijoystate);
            // the user rejected all of the kanji
            // PostMessage(g_hwndApp, WM_IME_CHAR, REJECT, 0);
            ch = ' ';
            PostKeybdMessage((HWND) -1, VK_ESCAPE, KeyStateDownFlag, 0, &dummy, &ch);
            return(1);
        }


        // B button is used as CONFIRM (no convert)
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_B]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_B]] != g_rgiPrevButtons[JOYSTICK_B]))
        {
            FillPrevButtons(dijoystate);
            // the user rejected all of the kanji
            // PostMessage(g_hwndApp, WM_IME_CHAR, REJECT, 0);
            ch = ' ';
            PostKeybdMessage((HWND) -1, VK_RIGHT, KeyStateDownFlag, 0, &dummy, &ch);
            return(1);
        }

        // LA button is used to step left
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_LA]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_LA]] != g_rgiPrevButtons[JOYSTICK_LA]))
        {
            FillPrevButtons(dijoystate);
            dwTickLastXMovement = GetTickCount ();
            ch = ' ';
            PostKeybdMessage((HWND) -1, VK_LEFT, KeyStateDownFlag, 0, &dummy, &ch);
            return(1);
        }
        // RA button is used to step right
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_RA]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_RA]] != g_rgiPrevButtons[JOYSTICK_RA]))
        {
            FillPrevButtons(dijoystate);
            dwTickLastXMovement = GetTickCount ();
            ch = ' ';
            PostKeybdMessage((HWND) -1, VK_RIGHT, KeyStateDownFlag, 0, &dummy, &ch);
            return(1);
        }
        // DA button is used to step down
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_DA]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_DA]] != g_rgiPrevButtons[JOYSTICK_DA]))
        {
            FillPrevButtons(dijoystate);
            dwTickLastYMovement = GetTickCount ();
            ch = ' ';
            PostKeybdMessage((HWND) -1, VK_DOWN, KeyStateDownFlag, 0, &dummy, &ch);
            return(1);
        }
        // UA button is used to step up
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_UA]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_UA]] != g_rgiPrevButtons[JOYSTICK_UA]))
        {
            FillPrevButtons(dijoystate);
            dwTickLastYMovement = GetTickCount ();
            ch = ' ';
            PostKeybdMessage((HWND) -1, VK_UP, KeyStateDownFlag, 0, &dummy, &ch);
            return(1);
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

        //if (((GetTickCount () - dwTickLastXMovement) > dwXRepeatRate) && (dwXRepeatRate > 0))
        //{
        //    dwTickLastXMovement = GetTickCount ();
        //    ch = ' ';
        //    PostKeybdMessage((HWND) -1, (dijoystate.lX < 0) ? VK_LEFT : VK_RIGHT, KeyStateDownFlag, 0, &dummy, &ch);
        //}            

        if (((GetTickCount () - dwTickLastYMovement) > dwYRepeatRate) && (dwYRepeatRate > 0))
        {
            dwTickLastYMovement = GetTickCount ();
            ch = ' ';
            PostKeybdMessage((HWND) -1, (dijoystate.lY < 0) ? VK_UP : VK_DOWN, KeyStateDownFlag, 0, &dummy, &ch);
        }            

        // Poll the device now, so the data will be ready the next time around.
        FillPrevButtons(dijoystate);
        hr = g_pdidevice2JoystickIME->Poll ();
        if (FAILED(hr))
        {
            g_pdidevice2JoystickIME->Unacquire();
            g_pdidevice2JoystickIME->Release();
            g_pdidevice2JoystickIME = NULL;
        } 
    } else {
        if (GetTickCount() - dwTickLastJoystick > 500) 
        {
            CreateDirectInput(g_hinstApp, g_hwndApp, &g_pdidevice2JoystickIME);

            if (g_pdidevice2JoystickIME && g_bKWNDactive) 
                AcquireJoystick(&g_pdidevice2JoystickIME);        

            dwTickLastJoystick = GetTickCount();
        }
    }
    return(0);
} // KWNDReadDirectInputDevices
