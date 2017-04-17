/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    input.cxx

Abstract:

    This module contains all functions related to receiving input 
    from joysticks via DirectInput.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hxx"


// Array of joystick button indices, arranged by usage.
BYTE                            g_rgiIMEButtons[JOYSTICKMAXBUTTONS];
// Array of previous joystick button states
BYTE                            g_rgiPrevButtons[JOYSTICKMAXBUTTONS];

// Global DirectInput objects
LPDIRECTINPUT                   g_pIMEdinput = NULL;
HWND                            g_hwndIMEDirectInput;

#ifdef KANJI
// is the KWND active?  if so, then the SKB is not active
BOOL                            g_bKWNDactive = FALSE;

// is the SWND active?  if so, then the SKB is not active
BOOL                            g_bSWNDactive = FALSE;
#endif  // KANJI

// this flag allows the IME to communicate to the softkbd that it should reacquire the joystick
BOOL                            g_bSKBReacquireJoystick = FALSE;
BOOL                            g_fHardwareKeyboardPresent = TRUE;
BOOL                            g_fAnalogJoystick = TRUE;


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IME_DIEnumDeviceObjectsProc

Description:

    This function is the enumeration callback for the objects (buttons,
    axes, etc.) on a given DirectInput device (e.g. joystick).  For each
    of the buttons, we store away the index of the button, in an array
    which can be looked up based on the usage of the button (for example,
    Start button, A button, etc.)

Return Value:
    
    TRUE.

-------------------------------------------------------------------*/
BOOL CALLBACK
IME_DIEnumDeviceObjectsProc
    (
    LPCDIDEVICEOBJECTINSTANCE pDIDOI,
    LPVOID pButtons
    )
{

    BYTE*    cButtons = (BYTE *)pButtons;

    // Store the index in the array, according to its usage.  We can
    // assume that the buttons on a device are enumerated in order,
    // by index.
    if ((pDIDOI->wUsage >= USAGE_FIRST_BUTTON) && (pDIDOI->wUsage <= USAGE_LAST_BUTTON))
        g_rgiIMEButtons[pDIDOI->wUsage - USAGE_FIRST_BUTTON] = (*cButtons)++;
    else
        g_rgiIMEButtons[(*cButtons)] = (*cButtons)++;

    return TRUE;
} // IME_DIEnumDeviceObjectsProc


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitJoystickToSKBMapping

Description:

    This function initializes the global arrays for the joystick buttons.
    One array is the mapping from the joystick button label to the DInput
    button index.  The second array is a mapping of the joystick button
    to the SKB key which it simulates.

Return Value:
    
    DIENUM_CONTINUE to continue the enumeration.

-------------------------------------------------------------------*/
void
InitJoystickToSKBMapping
    (
    void
    )
{
    int             i;

    for (i = 0 ; i < JOYSTICKMAXBUTTONS ; i++)
    {
        g_rgiIMEButtons[i] = INVALID_INDEX;
    }

} // InitJoystickToSKBMapping


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IME_DInputDeviceEnumCallback

Description:

    This function is the enumeration callback for DirectInput devices.
    If a joystick is installed and attached to the system, then 
    this function will get called by DirectInput.  We then create the 
    device only if a similar device has not already been created.

Return Value:
    
    DIENUM_CONTINUE to continue the enumeration.

-------------------------------------------------------------------*/
BOOL CALLBACK
IME_DInputDeviceEnumCallback
    (
    LPCDIDEVICEINSTANCE     pdidi,
    LPVOID                  pv
    )
{
    HRESULT                 hr;
    LPDIRECTINPUTDEVICE     pdidevice;

    // If this device is a joystick, and we don't already have a joystick
    // device, then create it now.
    if ((pdidi->dwDevType & DIDEVTYPE_JOYSTICK) && (!(*((LPDIRECTINPUTDEVICE *)pv))))
    {
        // Create the DirectInputDevice interface to the joystick.
        hr = g_pIMEdinput->CreateDevice (pdidi->guidInstance, &pdidevice, NULL);
        if (hr != DI_OK)
            OutputDebugString (TEXT("Could not create joystick device.\r\n"));

        // Query for the IDirectInputDevice2 interface, because we'll need
        // to use the Poll() method, which is only supported in the version
        // 2 interface.
        hr = pdidevice->QueryInterface (IID_IDirectInputDevice2, (LPVOID *) pv);
        if (hr != DI_OK)
            OutputDebugString (TEXT("Could not QI the joystick for IDirectInputDevice2.\r\n"));

        // We're done with the version 1 interface now.
        pdidevice->Release();
    }

    if (pdidi->dwDevType & DIDEVTYPE_KEYBOARD)
        g_fHardwareKeyboardPresent = TRUE;

    return DIENUM_CONTINUE;
} // IME_DInputDeviceEnumCallback


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IME_CreateDirectInput

Description:

    Creates the DirectInput object and attempts to create a 
    joystick device.

Return Value:
    
    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
IME_CreateDirectInput
    (
    HINSTANCE               hinstApp,
    HWND                    hwndApp,
    LPDIRECTINPUTDEVICE2*   pdidevice2Joystick
    )
{
    HRESULT             hr;
    DIPROPRANGE         diproprange;
    DIJOYSTATE          dijoystate;
    BYTE                cButtons = 0;   // Each time we enumerate the buttons, we
                                        // pass to the enumerating function a new
                                        // counter which starts at 0.  This allows
                                        // multiple enumerations of the buttons.

    g_hwndIMEDirectInput = hwndApp;

    // Create the global DirectInput interface object.
    if (!g_pIMEdinput)
    {
        hr = DirectInputCreate (hinstApp, DIRECTINPUT_VERSION, &g_pIMEdinput, NULL);
        if (hr != DI_OK)
        {
            OutputDebugString (TEXT("Could not create DirectInput object.\r\n"));
            return FALSE;
        }
        InitializePrevButtons();
    }

    // Enumerate all the DirectInput devices attached to the system.  
    // The callback function will create a joystick device if one is found.
    g_fHardwareKeyboardPresent = FALSE;
    hr = g_pIMEdinput->EnumDevices (0, IME_DInputDeviceEnumCallback, pdidevice2Joystick,
        DIEDFL_ATTACHEDONLY);
    if (hr != DI_OK)
    {
        OutputDebugString (TEXT("Could not enumerate DirectInput devices.\r\n"));
        return FALSE;
    }

    // If a joystick was not found, then we have no use
    // for DirectInput.  We'll just have to suffice with SKB input
    // via WM_KEYDOWN messages.
    if (!(*pdidevice2Joystick) && !g_fHardwareKeyboardPresent)
    {
        OutputDebugString (TEXT("Error:  Could not find any DirectInput joystick or keyboard devices.\r\n"));
        return FALSE;
    }

    // Initialize joystick, if one exists.
    if (*pdidevice2Joystick)
    {
        // Set the cooperative level for the joystick to be exclusive,
        // and only when our app is in the foreground.  This is the only
        // mode supported on Dragon.
        hr = (*pdidevice2Joystick)->SetCooperativeLevel (g_hwndIMEDirectInput,
            DISCL_EXCLUSIVE | DISCL_FOREGROUND);
        if (hr != DI_OK)
        {
            OutputDebugString (TEXT("Could not set cooperative level for joystick.\r\n"));
            return FALSE;
        }

        // Initialize global arrays, before enumerating objects on the joystick.
        InitJoystickToSKBMapping ();

        // Enumerate all objects (buttons, axes, etc.) on the joystick, so
        // we have a mapping of usage (Start button, A button, etc.) to the
        // button index.
        hr = (*pdidevice2Joystick)->EnumObjects (IME_DIEnumDeviceObjectsProc, &cButtons, DIDFT_BUTTON);

        // Set the data format for the joystick.
        hr = (*pdidevice2Joystick)->SetDataFormat (&c_dfDIJoystick);
        if (hr != DI_OK)
        {
            DEBUGMSG(1, (TEXT("Could not set data format for joystick.  hr=0x%08x\r\n"), hr));
            return FALSE;
        }

        // Set the range for the X-axis of the joystick.
        diproprange.diph.dwSize = sizeof(DIPROPRANGE);
        diproprange.diph.dwHeaderSize = sizeof(DIPROPHEADER);
        diproprange.diph.dwObj = (BYTE *) &dijoystate.lX - (BYTE *) &dijoystate;
        diproprange.diph.dwHow = DIPH_BYOFFSET;
        diproprange.lMin = -JOYSTICKRANGE;
        diproprange.lMax = +JOYSTICKRANGE;

        g_fAnalogJoystick = TRUE;

        hr = (*pdidevice2Joystick)->SetProperty (DIPROP_RANGE, &diproprange.diph);
        if (hr != DI_OK)
            g_fAnalogJoystick = FALSE;

        // Set the range for the Y-axis of the joystick.
        diproprange.diph.dwSize = sizeof(DIPROPRANGE);
        diproprange.diph.dwHeaderSize = sizeof(DIPROPHEADER);
        diproprange.diph.dwObj = (BYTE *) &dijoystate.lY - (BYTE *) &dijoystate;
        diproprange.diph.dwHow = DIPH_BYOFFSET;
        diproprange.lMin = -JOYSTICKRANGE;
        diproprange.lMax = +JOYSTICKRANGE;

        hr = (*pdidevice2Joystick)->SetProperty (DIPROP_RANGE, &diproprange.diph);
        if (hr != DI_OK)
            g_fAnalogJoystick = FALSE;
    }

    return TRUE;

} // IME_CreateDirectInput


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IME_DestroyDirectInput

Description:

    Releases all DirectInput devices and objects. 

Return Value:
    
    None.

-------------------------------------------------------------------*/
void
IME_DestroyDirectInput
    (
    void
    )
{
    // Release the global DirectInput interface object.
    if (g_pIMEdinput)
    {
        g_pIMEdinput->Release ();
        g_pIMEdinput = NULL;
    }

} // IME_DestroyDirectInput


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    FillPrevButtons

Description:

    Copy the current button state into the PrevButtons array.

Return Value:
    
    None.

-------------------------------------------------------------------*/
void 
FillPrevButtons
    (
    DIJOYSTATE dijoystate
    )
{
    g_rgiPrevButtons[JOYSTICK_A]     = dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_A]];
    g_rgiPrevButtons[JOYSTICK_B]     = dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_B]];
    g_rgiPrevButtons[JOYSTICK_X]     = dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_X]];
    g_rgiPrevButtons[JOYSTICK_Y]     = dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_Y]];
    g_rgiPrevButtons[JOYSTICK_LA]    = dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_LA]];
    g_rgiPrevButtons[JOYSTICK_RA]    = dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_RA]];
    g_rgiPrevButtons[JOYSTICK_DA]    = dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_DA]];
    g_rgiPrevButtons[JOYSTICK_UA]    = dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_UA]];
    g_rgiPrevButtons[JOYSTICK_START] = dijoystate.rgbButtons[g_rgiIMEButtons[JOYSTICK_START]];

} // FillPrevButtons



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitializePrevButtons

Description:

    Initialize the array which holds the button states before the last polling
    to 0 (unpressed).

Return Value:
    
    None.

-------------------------------------------------------------------*/
void 
InitializePrevButtons()
{
    WORD i;

    for (i=0; i<JOYSTICKMAXBUTTONS; i++) 
    {
        g_rgiPrevButtons[i] = 0;
    }
} // InitializePrevButtons



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    AcquireJoystick

Description:

    Acquire the direct input joystick.

Return Value:
    
    TRUE if successful, FALSE otherwise.

-------------------------------------------------------------------*/
BOOL  AcquireJoystick(LPDIRECTINPUTDEVICE2 *pdidevice2Joystick)
{
    HRESULT hr;

    if (!pdidevice2Joystick || !*pdidevice2Joystick)
        return FALSE;
    hr = (*pdidevice2Joystick)->Acquire ();
    if (hr != DI_OK)
    {
        DEBUGMSG(1, (TEXT("Could not acquire joystick.  hr=0x%08x\r\n"), hr));
        return FALSE;
    }
    g_pdidevice2JoystickAcquired = *pdidevice2Joystick;

    // Do an initial Poll, so that the data will be ready the first time
    // we call GetDeviceState later.
    (*pdidevice2Joystick)->Poll ();

    return TRUE;
} // AcquireJoystick


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CheckForHardwareKeyboard

Description:

Return Value:
    
    TRUE if successful, FALSE otherwise.

-------------------------------------------------------------------*/
BOOL
CheckForHardwareKeyboard 
    (
    void
    )
{
    static DWORD                    dwLastEnum = 0;
    BOOL                            fHWKeybdWasPresent;

    if ((GetTickCount () - dwLastEnum) > 500)
    {
        fHWKeybdWasPresent = g_fHardwareKeyboardPresent;

        IME_CreateDirectInput (g_hinstApp, g_hwndApp, &g_pdidevice2JoystickApp);
        dwLastEnum = GetTickCount ();

		if (g_fHardwareKeyboardPresent && g_pdidevice2JoystickSKB)
            g_pdidevice2JoystickSKB->Unacquire();

        if (!fHWKeybdWasPresent && g_fHardwareKeyboardPresent)
            // The hardware keyboard wasn't present before, but is present
            // now.  So it was just now connected.  So reset the state, because
            // that's what the keyboard driver is doing as well, and we must
            // stay in sync with it.
            ResetHardKeybdState ();

        if (fHWKeybdWasPresent && !g_fHardwareKeyboardPresent)
            ResetSoftKeybdState ();

        g_pkeybdstateCurrent = g_fHardwareKeyboardPresent ? &g_hwkeybdstate : &g_swkeybdstate;
    }

    return TRUE;
}
