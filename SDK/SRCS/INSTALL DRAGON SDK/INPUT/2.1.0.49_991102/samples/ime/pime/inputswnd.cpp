/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    inputswnd.cxx

Abstract:

    This file contains functions which manage input to the symbol window (SWND).

Environment:

    Runs on Dreamcast under Windows CE.


-------------------------------------------------------------------*/


#include "precomp.hpp"


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:
    SWNDProcessXMovement

Description:

    Moves the focus ring along the X direction of the SKB if the joystick
    is pressed along the X-axis.  The SWND "wraps" around the edges, so that
    moving the focus ring off the screen in the +X direction will move the cursor
    to column 0, etc.

Return Value:
    
    The new key which the cursor is moved to.

-------------------------------------------------------------------*/

SWNDKEY*
SWNDProcessXMovement(DIJOYSTATE dijoystate, SWNDKEY* psk, WORD *iKeyTop, STEP_MOVEMENT bStep)
{
    WORD iKeyCurrent;
    WORD iKeyTemp;

    iKeyCurrent = SWNDFindKeyUnderCursor();
    if ((dijoystate.lX < 0) || bStep == BACK) 
    {
        if (psk == NULL)
        {
            g_xSWNDCursor -= 1;
        } else {
            do 
            {
                iKeyTemp = iKeyCurrent;
                g_xSWNDCursor -= 1;
                iKeyCurrent = SWNDFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
        }    
    }
    else if ((dijoystate.lX > 0) || bStep == FORWARD) 
    {
        if (psk == NULL)
        {
            g_xSWNDCursor += 1;
        } else {
            do 
            {
                iKeyTemp = iKeyCurrent;
                g_xSWNDCursor += 1;
                iKeyCurrent = SWNDFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
        }
    }
    // g_xSWNDCursor is unsigned, so if it equals 0xffff then the focus ring has been moved off
    // the screen and we should put the focus ring back on the board
    if (g_xSWNDCursor == 0xffff) g_xSWNDCursor = SWND_COLUMNS - 1;
    if (g_xSWNDCursor >= SWND_COLUMNS) g_xSWNDCursor = 0;
    if (g_xSWNDCursor + g_ySWNDCursor * SWND_COLUMNS >= g_cCurrentSWNDKeys)
        g_xSWNDCursor = g_cCurrentSWNDKeys % SWND_COLUMNS - 1;

    iKeyCurrent = SWNDFindKeyUnderCursor();
    if (iKeyCurrent == 0xffff) 
    {
        psk = NULL;
    } else {
        psk = &g_pskCurrentSWND[iKeyCurrent];
    }

    SWNDUpdateFocusRect (*iKeyTop);

    return(psk);
} // SWNDProcessXMovement          

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SWNDProcessYMovement

Description:

    Moves the focus ring along the Y direction of the SWND if the joystick
    is pressed along the Y-axis.  The SWND scrolls up and down.

Return Value:
    
    The new key which the cursor is moved to.

-------------------------------------------------------------------*/
SWNDKEY*
SWNDProcessYMovement(DIJOYSTATE dijoystate, SWNDKEY* psk, WORD *iKeyTop, STEP_MOVEMENT bStep)
{
    WORD iKeyCurrent;
    WORD iKeyTemp;
    BOOL bChanged = FALSE;     // set to true if the cursor moves in the y-direction

    iKeyCurrent = SWNDFindKeyUnderCursor();
    if ((dijoystate.lY < 0) || bStep == BACK) 
    {
        if (psk == NULL)
        {
            g_ySWNDCursor -= 1;
        } else {
            do 
            {
                iKeyTemp = iKeyCurrent;
                g_ySWNDCursor -= 1;
                iKeyCurrent = SWNDFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
        }
        bChanged = TRUE;
    }
    else if ((dijoystate.lY > 0) || bStep == FORWARD) 
    {
        if (psk == NULL)
        {
            g_ySWNDCursor += 1;
        } else {
            do 
            {
                iKeyTemp = iKeyCurrent;
                g_ySWNDCursor += 1;
                iKeyCurrent = SWNDFindKeyUnderCursor();
            } while ((iKeyCurrent == iKeyTemp) && iKeyCurrent != 0xffff);
        }
        bChanged = TRUE;
    }

    // g_ySWNDCursor is unsigned, so if it equals 0xffff then the focus ring has been moved off
    // the screen.  We _do not_ wrap this window.
    if (bChanged) 
    {
        if (g_ySWNDCursor == 0xffff) g_ySWNDCursor = 0;
        if (g_ySWNDCursor >= g_cCurrentSWNDKeys / SWND_COLUMNS) g_ySWNDCursor = 
            g_cCurrentSWNDKeys / SWND_COLUMNS;
        // make sure we're not in the "dead space" on the last row of keys, which may
        // not be a complete row of keys
        if (g_xSWNDCursor + g_ySWNDCursor * SWND_COLUMNS >= g_cCurrentSWNDKeys) {
            g_ySWNDCursor = g_cCurrentSWNDKeys / SWND_COLUMNS - 1;
            // also, scroll down if we can
            if (g_ySWNDCursor + 1 == *iKeyTop + SWND_ROWS) 
            {
                *iKeyTop += SWND_ROWS - 1;
                SWNDRender(*iKeyTop);
            }
        }

        // determine whether the cursor is scrolling up or down, or neither
        if (g_ySWNDCursor < *iKeyTop) 
        {
            *iKeyTop -= (SWND_ROWS - 1);
            SWNDRender(*iKeyTop);
        } else if (g_ySWNDCursor >= (*iKeyTop + SWND_ROWS)) {
            *iKeyTop += (SWND_ROWS - 1);
            SWNDRender(*iKeyTop);
        }
        SWNDUpdateFocusRect(*iKeyTop);
    }

    iKeyCurrent = SWNDFindKeyUnderCursor();
    if (iKeyCurrent == 0xffff) 
    {
        psk = NULL;
    } else {
        psk = &g_pskCurrentSWND[iKeyCurrent];
    }
    return(psk);
} // SWNDProcessYMovement

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SWNDReadDirectInputDevices

Description:

    Read the joystick and process the result.

Return Value:
    
    TRUE if the user selected a character from the window, FALSE if not.

-------------------------------------------------------------------*/
BOOL
SWNDReadDirectInputDevices(WORD *iKeyTop)
{
    DIJOYSTATE              dijoystate;
    HRESULT                 hr;
    static DWORD            dwTickLastXMovement = 0;
    static DWORD            dwTickLastYMovement = 0;
    DWORD                   dwXRepeatRate;
    DWORD                   dwYRepeatRate;
    WORD                    iKeyCurrent;
    SWNDKEY*                psk;
    static DWORD            dwTickLastJoystick = 0;
    UINT                    ch;
    UINT                    dummy;
    DWORD                   dwConvMode;
    DWORD                   dwSentMode;
    HIMC                    hIMC;

    // If there's a joystick, the joystick's current state, and act appropriately.
    if (g_pdidevice2JoystickSKB)
    {
        dwTickLastJoystick = GetTickCount();
        // If less than 0.05 seconds have elapsed since a button was last
        // pressed, then don't process further joystick input.  If we
        // don't do this, then pressing a button once will send several
        // WM_KEYDOWN messages.
   
        hr = g_pdidevice2JoystickSKB->GetDeviceState (sizeof(DIJOYSTATE), &dijoystate);

        if (FAILED(hr))
        {
            g_pdidevice2JoystickSKB->Unacquire();
            g_pdidevice2JoystickSKB->Release();
            g_pdidevice2JoystickSKB = NULL;
        }
        if (hr != DI_OK)
            return(0);

        iKeyCurrent = SWNDFindKeyUnderCursor();
        if (iKeyCurrent == 0xffff) 
        {
            psk = NULL;
        } else {
            psk = &g_pskCurrentSWND[iKeyCurrent];
        }

        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_X]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_X]] != g_rgiPrevButtons[JOYSTICK_X]))
        {
            FillPrevButtons(dijoystate);
            ch = ' ';
            PostKeybdMessage((HWND) -1, VK_BACK, KeyStateDownFlag, 0, &dummy, &ch);
            return 1;
        }
 
        if (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_START]] & BUTTON_ON)
        {
            PostQuitMessage (0);
            return 1;
        }
 
        // select character
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_A]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_A]] != g_rgiPrevButtons[JOYSTICK_A]))
        {
            FillPrevButtons(dijoystate);
            if (psk != NULL) 
            {
                if (psk->szKeyString[0] == KANJI_REJECT_0)
                {
                    // the user rejected all of the kanji
                    // PostMessage(g_hwndCallingAppSWND, WM_CHAR, REJECT, 0);
		            g_bSWNDactive = FALSE;
                    return(1);
                } else {
                    ch =  psk->szKeyString[0];

                    // Need to temporarily set the IME state to full-width or
                    // half-width Katakana, so it will process the symbols
                    // properly.
                    hIMC = ImmGetContext (g_hwndApp);
                    ImmGetConversionStatus(hIMC, &dwConvMode, &dwSentMode);

                    if ((ch >= 0xff60) && (ch <= 0xff9f))
                        ImmSetConversionStatus (hIMC, IME_CMODE_JAPANESE | IME_CMODE_KATAKANA, dwSentMode);
                    else if ((ch >= 0x3040) && (ch <= 0x309f))
                        ImmSetConversionStatus (hIMC, IME_CMODE_JAPANESE | IME_CMODE_FULLSHAPE, dwSentMode);
                    else
                        ImmSetConversionStatus (hIMC, IME_CMODE_JAPANESE | IME_CMODE_KATAKANA | IME_CMODE_FULLSHAPE, dwSentMode);

                    PostKeybdMessage((HWND) -1, 'A', KeyStateDownFlag, 1, &dummy, &ch);
                    // SendMessage((HWND) g_hwndApp, WM_CHAR, ch, 0);

                    ImmReleaseContext (g_hwndApp, hIMC);

                    return(1);
                }        
            }    
        }


        // B and Y buttons are used as REJECT
        if (((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_Y]] & BUTTON_ON) && 
             (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_Y]] != g_rgiPrevButtons[JOYSTICK_Y])) ||
            ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_B]] & BUTTON_ON) && 
             (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_B]] != g_rgiPrevButtons[JOYSTICK_B]))
           )
        {
            g_bSWNDactive = FALSE;
            // tell the soft keyboard to reacquire the joystick
            FillPrevButtons(dijoystate);
            // the user rejected all of the kanji
            // PostMessage(g_hwndCallingAppSWND, WM_CHAR, REJECT, 0);
            return(1);
        }

        // LA button is used to step left
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_LA]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_LA]] != g_rgiPrevButtons[JOYSTICK_LA]))
        {
            FillPrevButtons(dijoystate);
            dwTickLastXMovement = GetTickCount ();
            do
            {
                psk = SWNDProcessXMovement(dijoystate, psk, iKeyTop, BACK);
            } while (psk == NULL);

        }
        // RA button is used to step right
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_RA]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_RA]] != g_rgiPrevButtons[JOYSTICK_RA]))
        {
            FillPrevButtons(dijoystate);
            dwTickLastXMovement = GetTickCount ();
            do
            {
                psk = SWNDProcessXMovement(dijoystate, psk, iKeyTop, FORWARD);
            } while (psk == NULL);

        }
        // DA button is used to step down
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_DA]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_DA]] != g_rgiPrevButtons[JOYSTICK_DA]))
        {
            FillPrevButtons(dijoystate);
            dwTickLastYMovement = GetTickCount ();
            do
            {
                psk = SWNDProcessYMovement(dijoystate, psk, iKeyTop, FORWARD);
            } while (psk == NULL);
        }
        // UA button is used to step up
        if ((dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_UA]] & BUTTON_ON) && 
            (dijoystate.rgbButtons[g_rgiButtons[JOYSTICK_UA]] != g_rgiPrevButtons[JOYSTICK_UA]))
        {
            FillPrevButtons(dijoystate);
            dwTickLastYMovement = GetTickCount ();
            do
            {
                psk = SWNDProcessYMovement(dijoystate, psk, iKeyTop, BACK);
            } while (psk == NULL);
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
                psk = SWNDProcessXMovement(dijoystate, psk, iKeyTop, NONE);
            } while (psk == NULL);
        }            

        if (((GetTickCount () - dwTickLastYMovement) > dwYRepeatRate) && (dwYRepeatRate > 0))
        {
            dwTickLastYMovement = GetTickCount ();
            do
            {
                psk = SWNDProcessYMovement(dijoystate, psk, iKeyTop, NONE);
            } while (psk == NULL);
        }            

        // Poll the device now, so the data will be ready the next time around.
        FillPrevButtons(dijoystate);
        hr = g_pdidevice2JoystickSKB->Poll ();

        if (FAILED(hr))// && hr != DIERR_NOTACQUIRED) 
        {
            g_pdidevice2JoystickSKB->Unacquire();
            g_pdidevice2JoystickSKB->Release();
            g_pdidevice2JoystickSKB = NULL;
        } 
    } else {
        if (GetTickCount() - dwTickLastJoystick > 500) 
        {
            CreateDirectInput(g_hinstApp, g_hwndApp, &g_pdidevice2JoystickSKB);

            if (g_pdidevice2JoystickSKB && g_bSWNDactive) 
                AcquireJoystick(&g_pdidevice2JoystickSKB);        

            dwTickLastJoystick = GetTickCount();
        }
    }
    return(0);
} // SWNDReadDirectInputDevices