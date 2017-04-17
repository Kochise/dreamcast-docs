/********************************************************************
 * input.cpp
 *
 * Description
 *     DInput wrappers and helpers
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include "sound.h"              // sound wrapper prototypes
#include "tkime.h"              // IME class
#include "editbox.h"            // IME editbox

/********************************************************************
 * External global variables
 ********************************************************************/
extern LPDIRECTSOUNDBUFFER g_pSndBufferClick;
extern RECT                g_rcActiveScreen;

/********************************************************************
 * Global variables
 ********************************************************************/
// Array of joystick button indices, arranged by usage.
BYTE  g_rgiButtons[JOYSTICKMAXBUTTONS];
BYTE  g_rgvButtons[JOYSTICKMAXBUTTONS];

// Global DirectInput objects
LPDIRECTINPUT        g_pdinput            = NULL;
LPDIRECTINPUTDEVICE2 g_pdidevice2Joystick = NULL;
HWND                 g_hwndDirectInput    = NULL;
CTkIme              *g_pTkIme             = NULL;
#ifdef USE_FLASH   
DWORD                g_dwButtonsReleased  = 0;
#endif // USE_FLASH

/********************************************************************
 * DIEnumDeviceObjectsProc
 *
 * Description
 *    Call back function called by Direct Input when enumerating 
 *    buttons on a DInput controller. When a button is found, it is
 *    added to a global array of buttons.
 *
 * Parameters
 *    pDIDOI       device data
 *    pvContext    user data (pointer to number of buttons so far)
 * 
 * Returns
 *    TRUE         continue enumerating
 ********************************************************************/
BOOL CALLBACK DIEnumDeviceObjectsProc(LPCDIDEVICEOBJECTINSTANCE pDIDOI, 
                                      LPVOID pvContext)
{
    // validate parameters
    if (!pvContext)
    {
        return FALSE;
    }

    int *pnButtons = (int *)pvContext;

    // store the index in the array, according to its usage.  we can assume
    // that the buttons on a device are enumerated in order, by index.
    if ((pDIDOI->wUsage >= USAGE_FIRST_BUTTON) && 
        (pDIDOI->wUsage <= USAGE_LAST_BUTTON))
    {
        g_rgiButtons[pDIDOI->wUsage - USAGE_FIRST_BUTTON] = (*pnButtons)++;
    }
    else
    {
        g_rgiButtons[*pnButtons] = (*pnButtons)++; 
    }

    return TRUE;
}

/********************************************************************
 * DInputDeviceEnumCallback
 *
 * Description
 *    Call back function called by Direct Input when enumerating 
 *    DInput devices (controllers). When a controller (joystick) is
 *    found, a global variable is set to the first found device.
 *
 * Parameters
 *    pdidi            device data
 *    pvContext        user data (not used for this enumeration 
 *                     callback)
 * 
 * Returns
 *    DIENUM_CONTINUE  continue enumeration
 ********************************************************************/
BOOL CALLBACK DInputDeviceEnumCallback(LPCDIDEVICEINSTANCE pdidi, 
                                       LPVOID pvContext)
{
    HRESULT                 hr;
    LPDIRECTINPUTDEVICE     pdidevice;

    // if this device is a joystick, and we don't already have a joystick
    // device, then create it now.
    if ((pdidi->dwDevType & DIDEVTYPE_JOYSTICK) && (!g_pdidevice2Joystick))
    {
        // create the DirectInputDevice interface to the joystick.
        hr = g_pdinput->CreateDevice(pdidi->guidInstance, &pdidevice, NULL);
        if (hr != DI_OK)
        {
            OutputDebugString(TEXT("Could not create joystick device.\n"));
        }

        // query for the IDirectInputDevice2 interface, because we'll need
        // to use the Poll() method, which is only supported in the version
        // 2 interface.
        hr = pdidevice->QueryInterface (IID_IDirectInputDevice2, 
                                        (LPVOID *) &g_pdidevice2Joystick);
        if (hr != DI_OK)
        {
            OutputDebugString(TEXT("Could not QI the joystick for IDirectInputDevice2.\n"));
        }

        // done with the version 1 interface now.
        pdidevice->Release();
    }

    return DIENUM_CONTINUE;
}

/********************************************************************
 * CreateDirectInputJoystick
 *
 * Description
 *    Finds a controller and creates a Direct Input object for it. It
 *    finds the first available controller.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    TRUE     controller (joystick) object created successfully
 *    FALSE    controller not found or object not created
 ********************************************************************/
BOOL CreateDirectInputJoystick(void)
{
    memset(g_rgvButtons, 0, sizeof(g_rgvButtons));

    // destroy existing joystick
    if (g_pdidevice2Joystick)
    {
        g_pdidevice2Joystick->Unacquire();
        g_pdidevice2Joystick->Release();
        g_pdidevice2Joystick = NULL;
    }

    // enumerate all the DirectInput devices attached to the system.  
    // the callback function will create a joystick device if one is found.
    HRESULT hr = g_pdinput->EnumDevices(0, DInputDeviceEnumCallback, 0,
                                        DIEDFL_ATTACHEDONLY);
    if (hr != DI_OK)
    {
        OutputDebugString(TEXT("Could not enumerate DirectInput devices.\n"));
        return FALSE;
    }

    // if a joystick was not found, then we have no use for DirectInput.  
    if (!g_pdidevice2Joystick)
    {
        // OutputDebugString(TEXT("No joysticks were found.\n"));
        return FALSE;
    }

    // initialize joystick, if one exists.
    if (g_pdidevice2Joystick)
    {
        // set the cooperative level for the joystick to be exclusive,
        // and only when our app is in the foreground.  this is the only
        // mode supported on Dragon.
        hr = g_pdidevice2Joystick->SetCooperativeLevel(g_hwndDirectInput,
                                   DISCL_EXCLUSIVE | DISCL_FOREGROUND);
        if (hr != DI_OK)
        {
            OutputDebugString(TEXT("Could not set cooperative level for joystick.\n"));
            return FALSE;
        }

        // enumerate all objects (buttons, axes, etc.) on the joystick, so
        // we have a mapping of usage (Start button, A button, etc.) to the
        // button index.

        int nContext = 0;
        hr = g_pdidevice2Joystick->EnumObjects(DIEnumDeviceObjectsProc, 
                                               (LPVOID)(&nContext), DIDFT_BUTTON);

        for (int iButton = 0; iButton < JOYSTICKMAXBUTTONS; iButton++)
        {
            g_rgvButtons[iButton] = 0;
        }

        // set the data format for the joystick.
        hr = g_pdidevice2Joystick->SetDataFormat(&c_dfDIJoystick);
        if (hr != DI_OK)
        {
            OutputDebugString(TEXT("Could not set data format for joystick.\n"));
            return FALSE;
        }

        // acquire the joystick.  This allows us to read its state.
        hr = g_pdidevice2Joystick->Acquire();
        if (hr != DI_OK)
        {
            OutputDebugString(TEXT("Could not acquire joystick.\n"));
            return FALSE;
        }

        // do an initial Poll, so that the data will be ready the first time
        // we call GetDeviceState later.
        g_pdidevice2Joystick->Poll();
    }

    return TRUE;
}

/********************************************************************
 * CreateDirectInput
 *
 * Description
 *    Creates the Direct Input object, the controller (joystick)
 *    object, and the IME object.
 *
 * Parameters
 *    hinstApp instance handle of the application
 *    hwndApp  main application window
 * 
 * Returns
 *    TRUE     Direct Input created 
 *    FALSE    Direct Input not created
 ********************************************************************/
BOOL CreateDirectInput(HINSTANCE hinstApp, HWND hwndApp)
{
    HRESULT             hr;

    g_hwndDirectInput = hwndApp;

    // create the global DirectInput interface object.
    hr = DirectInputCreate(hinstApp, DIRECTINPUT_VERSION, &g_pdinput, NULL);
    if (hr != DI_OK)
    {
        OutputDebugString(TEXT("Could not create DirectInput object.\n"));
        return FALSE;
    }

    BOOL b = CreateDirectInputJoystick();

    // create the IME
    if (b)
    {
        g_pTkIme = new CTkIme(g_hInstance, g_pDD, g_pDDSPrimary, g_pDDSBack);
    }

    return b;
}

/********************************************************************
 * DestroyDirectInput
 *
 * Description
 *    Destroys the IME object, the Joystick object, the main Direct 
 *    Input object.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void DestroyDirectInput(void)
{
    // destroy the IME
    if (g_pTkIme)
    {
        delete g_pTkIme;
        g_pTkIme = NULL;
    }

    // release the global joystick device interface object.
    if (g_pdidevice2Joystick)
    {
        g_pdidevice2Joystick->Unacquire();
        g_pdidevice2Joystick->Release();
        g_pdidevice2Joystick = NULL;
    }

    // release the global DirectInput interface object.
    if (g_pdinput)
    {
        g_pdinput->Release();
        g_pdinput = NULL;
    }
}

/********************************************************************
 * Global variables
 ********************************************************************/
BOOL        g_bBusy = FALSE;    // allow only one joystick msg at a time
DWORD       g_dwButtons[2];     // joystick message data
extern BOOL g_bLockScreen;      // flag for screen locked

/********************************************************************
 * ReadDirectInputDevices
 *
 * Description
 *    Reads the button states off of the controller and formats them
 *    into flags for which buttons are newly pressed and which are
 *    still pressed. Also determines the position of the "cursor" 
 *    when the joystick is moved.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    flags for which buttons were just pushed
 ********************************************************************/
DWORD ReadDirectInputDevices(void)
{
    // don't bother if something else owns the screen now
    if (g_bLockScreen)
    {
        return 0;
    }
 
    DWORD dwButtons = 0;

#ifdef USE_FLASH
    g_dwButtonsReleased = 0;
#endif // USE_FLASH
    if (g_bBusy)
    {
        return dwButtons;
    }

    static BYTE aiButtonList[] = {
                                    JOYSTICK_IDX_A,
                                    JOYSTICK_IDX_B,
                                    JOYSTICK_IDX_START,
                                    JOYSTICK_IDX_LA,
                                    JOYSTICK_IDX_RA,
                                    JOYSTICK_IDX_DA,
                                    JOYSTICK_IDX_UA,
                                    JOYSTICK_IDX_X,
                                    JOYSTICK_IDX_Y,
                                    JOYSTICK_IDX_RTRIG,
                                    JOYSTICK_IDX_LTRIG
                                 };

    // if there's a joystick, read it's current state, and act appropriately.
    if (g_pdidevice2Joystick)
    {
        POINT ptCursor = QueryCurrentScreenCursorPos();
        DIJOYSTATE  dijoystate;
        HRESULT     hr;

        hr = g_pdidevice2Joystick->GetDeviceState(sizeof(DIJOYSTATE), &dijoystate);
        if (hr == DIERR_INPUTLOST)
        {
	    memset(g_rgvButtons, 0, sizeof(g_rgvButtons));
            hr = g_pdidevice2Joystick->Acquire();
            if (SUCCEEDED(hr))
            {
                g_pdidevice2Joystick->Poll();
            }
            return dwButtons;
        }
        else if (hr != DI_OK)
        {
            CreateDirectInputJoystick();
            return dwButtons;
        }

        // poll the device now, so the data will be ready the next time around.
        g_pdidevice2Joystick->Poll();

        BOOL   bHolds        = FALSE;
        DWORD  dwButtonsHeld = 0;

        // set joystick resolution to 16 X 16 matrix
        static short nDelta[16] = { -12, -8, -4, -2, -2, -1, -1, 0,
                                     0,  1,  1,  2,  2,  4,  8, 12 };

        short dx = dijoystate.lX / 16;
        short dy = dijoystate.lY / 16;

        // constrain cursor position to visible screen area
        if (dx || dy)
        {
            short xNew     = (short)ptCursor.x + nDelta[dx];
            short yNew     = (short)ptCursor.y + nDelta[dy];

            if (xNew < g_rcActiveScreen.left)
            {
                xNew = (short)g_rcActiveScreen.left;
            }
            else if (xNew >= g_rcActiveScreen.right)
            {
                xNew = (short)(g_rcActiveScreen.right - 1);
            }
            if (yNew < g_rcActiveScreen.top)
            {
                yNew = (short)g_rcActiveScreen.top;
            }
            else if (yNew >= g_rcActiveScreen.bottom)
            {
                yNew = (short)(g_rcActiveScreen.bottom - 1);
            }

            if (xNew != ptCursor.x || yNew != ptCursor.y)
            {
                ptCursor.x = xNew;
                ptCursor.y = yNew;
                 
                dwButtons |= JOYSTICK_POS;
                dwButtonsHeld |= JOYSTICK_POS;
                bHolds = TRUE;
            }
        }

        // check for buttons held or pressed
        for (int iCheck = 0; iCheck < sizeof(aiButtonList)/sizeof(BYTE); iCheck++)
        {
            int  iButton    = aiButtonList[iCheck];
            BYTE bValuePrev = g_rgvButtons[iButton];
            BYTE bValue     = dijoystate.rgbButtons[g_rgiButtons[iButton]];

            // check if control value is changed
            if (ISDOWN(bValue))
            {
                dwButtonsHeld |= (1 << iButton);

                if (!ISDOWN(bValuePrev))
                {
                    dwButtons |= (1 << iButton);
                }
            }
#ifdef USE_FLASH
            else
            {
                if (ISDOWN(bValuePrev))
                {
                    g_dwButtonsReleased |= (1 << iButton);
                }
            }
#endif // USE_FLASH

            g_rgvButtons[iButton] = bValue;
        }

        // send message if something interesting has happended
#ifdef USE_FLASH
        if (dwButtons || bHolds || g_dwButtonsReleased)
#else  // USE_FLASH
        if (dwButtons || bHolds)
#endif // USE_FLASH
        {
            g_bBusy = TRUE;
            g_dwButtons[0] = dwButtons;
            g_dwButtons[1] = dwButtonsHeld;

            if ((dwButtons & (~JOYSTICK_POS)) && g_pSndBufferClick)
            {
                g_pSndBufferClick->Play(0, 0, 0);
            }

            PostMessage(g_hwndDirectInput, WM_JOYSTICK, (WPARAM)g_dwButtons,
                        MAKELPARAM(ptCursor.x, ptCursor.y));
        }
    }
    else
    {
        // problem with the controller. try again
        CreateDirectInputJoystick();
    }

    return dwButtons;
}

/********************************************************************
 * GetIMEInput
 *
 * Description
 *    Locks the screen for exclusive use by the IME and calls the 
 *    IME to get text input.
 *
 * Parameters
 *    pszText      Text to initially display in IME and where to 
 *                 return user entered text (must be large enough 
 *                 buffer).
 * 
 * Returns
 *    S_OK         IME sucessfully called
 *    E_INVALIDARG NULL pszText
 *    E_FAIL       no IME object instantiated
 ********************************************************************/
HRESULT GetIMEInput(LPTSTR pszText)
{
    // validate parameters
    if (!pszText)
    {
        return E_INVALIDARG;
    }

    // make sure we have an IME
    if (!g_pTkIme)
    {
        return E_FAIL;
    }

    // lock out other screen functions
    LockScreen();

    // call IME
    g_pTkIme->GetImeInput(pszText, g_pdidevice2Joystick, g_rgvButtons);

    // allow other screen functions again
    UnlockScreen();

    return S_OK;
}

