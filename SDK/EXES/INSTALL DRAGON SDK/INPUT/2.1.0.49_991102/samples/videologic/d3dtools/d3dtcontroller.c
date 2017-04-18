/*****************************************************************************
  Name : D3DTController.c
  Date : May 1999
  Platform : ANSI compatible
 
  $Revision: 1.0 $

  * Description : 
  Set of functions used for controlling the Dreamcast Pad.

  Note: Code based in Microsoft's SDK  

  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#ifndef INITGUID
#define INITGUID			/* Must be set up before everything */
#endif

#include <windows.h>
#include <dinput.h>

#ifdef UNDER_CE
#include <maplusag.h>
#endif

#include "D3DTController.h"

//******************************************************************************
// Preprocessor definitions
//******************************************************************************
#ifndef DD_OK  
#define DD_OK  0
#endif

#ifndef DIERR_UNPLUGGED
#define DIERR_UNPLUGGED         DIERR_INPUTLOST
#endif

#define WCE_DEBUG(x) OutputDebugString((unsigned short *)x);

#define NJD_DGT_TA  1
#define NJD_DGT_TB  2
#define NJD_DGT_TX  4
#define NJD_DGT_TY  8
#define NJD_DGT_TL  16
#define NJD_DGT_TR  32
#define NJD_DGT_ST  64
#define NJD_DGT_KU  128
#define NJD_DGT_KD  256
#define NJD_DGT_KL  512
#define NJD_DGT_KR  1024

#ifdef UNDER_CE
#define JOYSTICK_NUMBUTTONS     18
#define JOYSTICK_A              (USAGE_A_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_B              (USAGE_B_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_C              (USAGE_C_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_START          (USAGE_START_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_LA             (USAGE_LA_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_RA             (USAGE_RA_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_DA             (USAGE_DA_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_UA             (USAGE_UA_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_X              (USAGE_X_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_Y              (USAGE_Y_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_Z              (USAGE_Z_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_D              (USAGE_D_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_LB             (USAGE_LB_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_RB             (USAGE_RB_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_DB             (USAGE_DB_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_UB             (USAGE_UB_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_LTRIG          (USAGE_LTRIG_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_RTRIG          (USAGE_RTRIG_BUTTON - USAGE_FIRST_BUTTON)


#else

#define JOYSTICK_NUMBUTTONS     18
#define JOYSTICK_A              0
#define JOYSTICK_B              1
#define JOYSTICK_C              2 
#define JOYSTICK_START          3
#define JOYSTICK_LA             4 
#define JOYSTICK_RA             5
#define JOYSTICK_DA             6
#define JOYSTICK_UA             7
#define JOYSTICK_X              8
#define JOYSTICK_Y              9
#define JOYSTICK_Z              10
#define JOYSTICK_D              11
#define JOYSTICK_LB             12
#define JOYSTICK_RB             13
#define JOYSTICK_DB             14
#define JOYSTICK_UB             15
#define JOYSTICK_LTRIG          16
#define JOYSTICK_RTRIG          17

#endif // UNDER_CE

//******************************************************************************
// Local function prototypes
//******************************************************************************

static LPDIRECTINPUTDEVICE2     CreateDevice(UINT uPort);
static BOOL						GetJoystickState(LPDIJOYSTATE lpJoystickState);

//******************************************************************************
// Globals
//******************************************************************************

static HWND                     g_hWindow = NULL;
LPDIRECTINPUT                   g_lpDirectInput;
LPDIRECTINPUTDEVICE2            g_lpDirectInputDevice;
BYTE                            bControllerButtons[JOYSTICK_NUMBUTTONS];
LONG							bControllerAnalog[2];
DWORD							dwState;

/*******************************************************************************
 * Function Name  : 
 * Inputs		  : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
static BOOL CALLBACK DIDeviceEnumCallback(LPCDIDEVICEINSTANCE lpDIDeviceInstance, LPVOID pvContext) 
{
LPDIRECTINPUTDEVICE     lpDIDevice;
LPDIRECTINPUTDEVICE2*   lpDIDevice2 = (LPDIRECTINPUTDEVICE2*)pvContext;
UINT*                   puPort = (UINT*)pvContext;
HRESULT                 hr;

    if (!g_lpDirectInput || !puPort)    return DIENUM_STOP;
    
#ifdef UNDER_CE
    // Is this the joystick we're looking for?
    if ((UINT)(lpDIDeviceInstance->guidInstance.Data4[7] & 0x03) != *puPort) 
	{
        // No, keep looking
        return DIENUM_CONTINUE;
    }
#else
    // Since we don't really have the concept of a port on Win95, we'll
    // use the port number to decide which enumerated joystick to choose
    // (port 0 will yield the first joystick enumerated, port 1 will yield
    // the second, etc.)
    if (*puPort > 0) 
	{
        *puPort--;
        return DIENUM_CONTINUE;
    }
#endif // UNDER_CE

    // Sanity check: Is this device a joystick?
    if (DIDFT_GETTYPE(lpDIDeviceInstance->dwDevType) != DIDEVTYPE_JOYSTICK)
    {
    	WCE_DEBUG(TEXT("Warning: Joystick enumeration callback enumerated \n"));
		WCE_DEBUG(TEXT("a device not identified as a joystick\n"));
    }

    // Attempt to create the device
    hr = g_lpDirectInput->lpVtbl->CreateDevice(g_lpDirectInput, &lpDIDeviceInstance->guidInstance, &lpDIDevice, NULL);
    if (hr!=DD_OK)
	{
		WCE_DEBUG(TEXT("IDirectInput::CreateDevice failed\n"));
	}

    // Get the IDirectInputDevice2 interface
    hr = lpDIDevice->lpVtbl->QueryInterface(lpDIDevice,&IID_IDirectInputDevice2, (LPVOID*)lpDIDevice2);
	if (hr!=DD_OK)
	{
		WCE_DEBUG(TEXT("IDirectInputDevice::QueryInterface failed\n"));
   	}
    lpDIDevice->lpVtbl->Release(lpDIDevice);
    
    return DIENUM_STOP;
}

/*******************************************************************************
 * Function Name  : 
 * Inputs		  : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
static BOOL CALLBACK DIObjectsEnumCallback(LPCDIDEVICEOBJECTINSTANCE lpDIDeviceObjectInstance,  LPVOID pvContext) 
{
UINT*   puButtons = (UINT*)pvContext;

    // Store the index in the array, according to its usage.  We can
    // assume that the buttons on a device are enumerated in order,
    // by index.
#ifdef UNDER_CE
    bControllerButtons[lpDIDeviceObjectInstance->wUsage - USAGE_FIRST_BUTTON] = (*puButtons)++;
#else
    bControllerButtons[*puButtons] = (*puButtons)++;
#endif // UNDER_CE

    return DIENUM_CONTINUE;
}

/*******************************************************************************
 * Function Name  : 
 * Inputs		  : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
BOOL InitDirectInput(HWND hWnd, HINSTANCE hInstance) 
{
HRESULT hr;

    if (!hWnd || !hInstance) 
	{
        return FALSE;
    }

    g_hWindow = hWnd;

    hr = DirectInputCreate(hInstance, DIRECTINPUT_VERSION, &g_lpDirectInput, NULL);
    if (hr!=DD_OK)
	{
		WCE_DEBUG(TEXT("DirectInputCreate failed\n"));
		return FALSE;
	}

    // Create a joystick device for the first joystick port
    g_lpDirectInputDevice = CreateDevice(0);

    return TRUE;
}
/*******************************************************************************
 * Function Name  : 
 * Inputs		  : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
static LPDIRECTINPUTDEVICE2 CreateDevice(UINT uPort) 
{
LPDIRECTINPUTDEVICE2    pDevice = NULL;
UINT                    uNumButtons = 0;
HRESULT                 hr;

    if (!g_lpDirectInput)   return NULL;
    
    pDevice = (LPDIRECTINPUTDEVICE2)uPort;

    hr = g_lpDirectInput->lpVtbl->EnumDevices(g_lpDirectInput, DIDEVTYPE_JOYSTICK, DIDeviceEnumCallback, 
									  (LPVOID)&pDevice, DIEDFL_ATTACHEDONLY);

	if (hr!=DD_OK)
	{
		WCE_DEBUG(TEXT("IDirectInput::EnumDevices failed\n"));
	    return NULL;
	}


    // Return FALSE if the joystick is not currently attached, or no such
    // port exists
    if (!pDevice) return NULL;
    
    // Enumerate the buttons that are available with the joystick
    hr = pDevice->lpVtbl->EnumObjects(pDevice, DIObjectsEnumCallback, &uNumButtons, DIDFT_BUTTON);
    if (hr!=DD_OK)
	{
		WCE_DEBUG(TEXT("IDirectInputDevice2::EnumObjects failed\n"));
		pDevice->lpVtbl->Release(pDevice);
	    
		return NULL;
	}

    // Set the data format for the joystick
    hr = pDevice->lpVtbl->SetDataFormat(pDevice, &c_dfDIJoystick);
    if (hr!=DD_OK)
	{
		WCE_DEBUG(TEXT("IDirectInputDevice::SetDataFormat failed\n"));
		pDevice->lpVtbl->Release(pDevice);
	    
		return NULL;
	}

    // Set the cooperative level
    hr = pDevice->lpVtbl->SetCooperativeLevel(pDevice, g_hWindow, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if (hr!=DD_OK)
	{
		WCE_DEBUG(TEXT("IDirectInputDevice::SetCooperativeLevel failed\n"));
		pDevice->lpVtbl->Release(pDevice);
	    
		return NULL;
	}

    // Acquire the joystick
    hr = pDevice->lpVtbl->Acquire(pDevice);
   	if (hr!=DD_OK)
	{
		WCE_DEBUG(TEXT("IDirectInputDevice::Acquire failed\n"));
		pDevice->lpVtbl->Release(pDevice);
	    
		return NULL;
	}


    // Initiate a poll to prepare data for the first GetDeviceState call
    hr = pDevice->lpVtbl->Poll(pDevice);
	if (hr!=DD_OK)
	{
		WCE_DEBUG(TEXT("IDirectInputDevice::Acquire failed\n"));
		pDevice->lpVtbl->Release(pDevice);
	    
		return NULL;
	}


    // We're now connected and ready to go
    return pDevice;
}
/*******************************************************************************
 * Function Name  : 
 * Inputs		  : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
void ReleaseDirectInput(void) 
{
    if (g_lpDirectInputDevice) 
	{
        g_lpDirectInputDevice->lpVtbl->Release(g_lpDirectInputDevice);
        g_lpDirectInputDevice = NULL;
    }

    if (g_lpDirectInput) 
	{
        g_lpDirectInput->lpVtbl->Release(g_lpDirectInput);
        g_lpDirectInput = NULL;
    }
}
/*******************************************************************************
 * Function Name  : 
 * Inputs		  : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
BOOL GetJoystickState(LPDIJOYSTATE lpJoystickState) 
{
HRESULT hr;

    if (!lpJoystickState) 
	{
        return FALSE;
    }

    if (!g_lpDirectInputDevice) 
	{
#ifdef UNDER_CE
        // Check to see if the joystick has been plugged in since we last checked
        g_lpDirectInputDevice = CreateDevice(0);
        if (!g_lpDirectInputDevice) 
		{
            return FALSE;
        }
#else
        return FALSE;
#endif // UNDER_CE
    }

    memset(lpJoystickState, 0, sizeof(DIJOYSTATE));

    // Get the joystick data
    hr = g_lpDirectInputDevice->lpVtbl->GetDeviceState(g_lpDirectInputDevice, sizeof(DIJOYSTATE), lpJoystickState);
    if (FAILED(hr)) {
        if (hr == DIERR_UNPLUGGED) 
		{
            // The joystick has been unplugged, delete the device since
            // we'll have to recreate it once the joystick is plugged
            // back in
            g_lpDirectInputDevice->lpVtbl->Release(g_lpDirectInputDevice);
            g_lpDirectInputDevice = NULL;
            return GetJoystickState(lpJoystickState);
        }
		if (hr!=DD_OK)
		{
			WCE_DEBUG(TEXT("IDirectInputDevice::GetDeviceState failed\n"));
		}
        return FALSE;
    }

    // Update the joystick for next time
    hr = g_lpDirectInputDevice->lpVtbl->Poll(g_lpDirectInputDevice);
    if (hr == DIERR_UNPLUGGED) 
	{
        g_lpDirectInputDevice->lpVtbl->Release(g_lpDirectInputDevice);
        g_lpDirectInputDevice = NULL;
        return GetJoystickState(lpJoystickState);
    }
    else if (hr == DIERR_INPUTLOST) 
	{
        hr = g_lpDirectInputDevice->lpVtbl->Acquire(g_lpDirectInputDevice);
       	if (hr!=DD_OK)
		{
			WCE_DEBUG(TEXT("IDirectInputDevice::Acquire failed\n"));
			return FALSE;
		}
    }
    else
	{
   		if (hr!=DD_OK)
		{
			WCE_DEBUG(TEXT("IDirectInputDevice::Poll failed\n"));
			return FALSE;
		}
    }

    return TRUE;
}
/*******************************************************************************
 * Function Name  : 
 * Inputs		  : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
BOOL UpdateJoystick(void) 
{
DIJOYSTATE          dijsNext;
static DIJOYSTATE   dijsLast = {0};

	dwState = 0;

    // Poll the joystick
    if (GetJoystickState(&dijsNext)) 
	{
		// START Button
        if (dijsNext.rgbButtons[bControllerButtons[JOYSTICK_START]] != 
			dijsLast.rgbButtons[bControllerButtons[JOYSTICK_START]]) 
			{
				dwState |= NJD_DGT_ST;
            }

       // X Button
        if (dijsNext.rgbButtons[bControllerButtons[JOYSTICK_X]] != 
			dijsLast.rgbButtons[bControllerButtons[JOYSTICK_X]]) 
			{
				dwState |= NJD_DGT_TX;
            }
	   // Y Button
        if (dijsNext.rgbButtons[bControllerButtons[JOYSTICK_Y]] != 
			dijsLast.rgbButtons[bControllerButtons[JOYSTICK_Y]]) 
			{
				dwState |= NJD_DGT_TY;
            }

	   // A Button
        if (dijsNext.rgbButtons[bControllerButtons[JOYSTICK_A]] != 
			dijsLast.rgbButtons[bControllerButtons[JOYSTICK_A]]) 
			{
				dwState |= NJD_DGT_TA;
            }

	   // B Button
        if (dijsNext.rgbButtons[bControllerButtons[JOYSTICK_B]] != 
			dijsLast.rgbButtons[bControllerButtons[JOYSTICK_B]]) 
			{
				dwState |= NJD_DGT_TB;
            }

		// Left Trigger
        if (dijsNext.rgbButtons[bControllerButtons[JOYSTICK_LTRIG]] != 
			dijsLast.rgbButtons[bControllerButtons[JOYSTICK_LTRIG]]) 
			{
				dwState |= NJD_DGT_TL;
            }

		// Right Trigger
        if (dijsNext.rgbButtons[bControllerButtons[JOYSTICK_RTRIG]] != 
			dijsLast.rgbButtons[bControllerButtons[JOYSTICK_RTRIG]]) 
			{
				dwState |= NJD_DGT_TR;
            }

		// Up
        if (dijsNext.rgbButtons[bControllerButtons[JOYSTICK_UA]] != 
			dijsLast.rgbButtons[bControllerButtons[JOYSTICK_UA]]) 
			{
				dwState |= NJD_DGT_KU;
            }

		// Down
        if (dijsNext.rgbButtons[bControllerButtons[JOYSTICK_DA]] != 
			dijsLast.rgbButtons[bControllerButtons[JOYSTICK_DA]] ) 
			{
				dwState |= NJD_DGT_KD;
            }

		// Left 
        if (dijsNext.rgbButtons[bControllerButtons[JOYSTICK_LA]] != 
			dijsLast.rgbButtons[bControllerButtons[JOYSTICK_LA]]) 
			{
				dwState |= NJD_DGT_KL;
            }

		// Right
        if (dijsNext.rgbButtons[bControllerButtons[JOYSTICK_RA]] != 
			dijsLast.rgbButtons[bControllerButtons[JOYSTICK_RA]]) 
			{
				dwState |= NJD_DGT_KR;
            }

		// Analog Controler
		bControllerAnalog[0] = dijsNext.lX;
		bControllerAnalog[1] = dijsNext.lY;


    }

    return TRUE;
}
/*******************************************************************************
 * Function Name  : 
 * Inputs		  : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
BOOL IsAKey(void) { return ((dwState & NJD_DGT_TA) ? TRUE : FALSE); }
BOOL IsBKey(void) { return ((dwState & NJD_DGT_TB) ? TRUE : FALSE); }
BOOL IsXKey(void) { return ((dwState & NJD_DGT_TX) ? TRUE : FALSE); }
BOOL IsYKey(void) { return ((dwState & NJD_DGT_TY) ? TRUE : FALSE); }

BOOL IsLFKey(void) { return ((dwState & NJD_DGT_TL) ? TRUE : FALSE); }
BOOL IsRFKey(void) { return ((dwState & NJD_DGT_TR) ? TRUE : FALSE); }

BOOL IsSTARTKey(void) { return ((dwState & NJD_DGT_ST) ? TRUE : FALSE); }
BOOL IsUPKey(void)	  { return ((dwState & NJD_DGT_KU) ? TRUE : FALSE); }
BOOL IsDOWNKey(void)  { return ((dwState & NJD_DGT_KD) ? TRUE : FALSE); }
BOOL IsLEFTKey(void)  { return ((dwState & NJD_DGT_KL) ? TRUE : FALSE); }
BOOL IsRIGHTKey(void) { return ((dwState & NJD_DGT_KR) ? TRUE : FALSE); }

LONG GetAnalogX(void) { return bControllerAnalog[0]; }
LONG GetAnalogY(void) { return bControllerAnalog[1]; }


