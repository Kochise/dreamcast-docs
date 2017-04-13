/*==========================================================================
 *
 * Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 * File:       input.c
 * Content:    DirectInput functionality for FFDonuts sample
 *
 * Functions:
 * inputInitDirectInput()
 * inputCleanupDirectInput()
 * inputEnumDeviceProc(LPDIDEVICEINSTANCE pdidi, LPVOID pv);
 * inputAcquireDevices(void);
 * inputCreateEffects(void);
 * inputProcessDeviceInput(void);
 * inputPrepareDevice(void);
 * inputPlayEffect(DWORD dwEffectFlag);
 *
 *
 ***************************************************************************/

#include "input.h"
#include "resource.h"

// file global variables
static BOOL                 fIsFFDevice  = FALSE;   // does our device support
                                                    // ForceFeedback
static DWORD                dwGain       = FF_ADULT;// gain selection from user
static LPDIRECTINPUT        gpdi         = NULL;    // base DirectInput object
static LPDIRECTINPUTDEVICE2 gpdiJoystick = NULL;    // DirectInputDevice2 objects
                                                    // support ForceFeedback
static LPDIRECTINPUTEFFECT  gpdieBounce  = NULL;    // effect used when "bouncing"
                                                    // off of the screen edges
static LPDIRECTINPUTEFFECT  gpdieExplode = NULL;    // effect used when the ship
                                                    // explodes
static LPDIRECTINPUTEFFECT  gpdieFire    = NULL;    // effect used when firing

//===========================================================================
// inputInitDirectInput
//
// Creates and initializes DirectInput objects
//
// Parameters:
//
// Returns:
//
//===========================================================================
BOOL inputInitDirectInput(HINSTANCE hInst, HWND hWnd)
{
    HRESULT             hRes;
    LPDIRECTINPUTDEVICE pdiTempDevice       = NULL;
    DIDEVCAPS           didc;
    GUID                guidDevice;
    TCHAR               tszBuf[256];

    // create the base DirectInput object
    hRes = DirectInputCreate(hInst, DIRECTINPUT_VERSION, &gpdi, NULL);
    if(FAILED(hRes))
    {
        wsprintf(tszBuf, TEXT("DirectInputCreate() failed - %08Xh\n\n")
                  TEXT("DirectX 5 or later required."), hRes);
        MessageBox(hWnd, tszBuf, TEXT("Space Donuts - Force Feedback"), MB_OK);
        return FALSE;
    }

    // enumerate for joystick devices
    hRes = gpdi->lpVtbl->EnumDevices(gpdi, DIDEVTYPE_JOYSTICK,
                                    (LPDIENUMDEVICESCALLBACK)inputEnumDeviceProc,
                                    &guidDevice,
                                    DIEDFL_ATTACHEDONLY);
    if(FAILED(hRes))
    {
        wsprintf(tszBuf, TEXT("EnumDevices() failed - %08Xh"), hRes);
        MessageBox(hWnd, tszBuf, TEXT("Space Donuts - Force Feedback"), MB_OK);
        return FALSE;
    }

    // create a temporary "Device 1" object
    hRes = gpdi->lpVtbl->CreateDevice(gpdi, &guidDevice, &pdiTempDevice, NULL);
    if(FAILED(hRes))
    {
        wsprintf(tszBuf, TEXT("CreateDevice() failed - %08Xh\n\n")
                  TEXT("This version of ""Space Donuts"" requires a JOYSTICK device."), hRes);
        MessageBox(hWnd, tszBuf, TEXT("Space Donuts - Force Feedback"), MB_OK);
        return FALSE;
    }

    // get a "Device 2" object
    //
    // this is needed for access to the ForceFeedback functionality
    hRes = pdiTempDevice->lpVtbl->QueryInterface(pdiTempDevice,
                                                &IID_IDirectInputDevice2,
                                                &gpdiJoystick);
    if(FAILED(hRes))
    {
        wsprintf(tszBuf, TEXT("QueryInterface(IID_IDirectInputDevice2) failed - %08Xh"), hRes);
        MessageBox(hWnd, tszBuf, TEXT("Space Donuts - Force Feedback"), MB_OK);
        return FALSE;
    }

    // we no longer need the temporary device, go ahead and release it.
    if(pdiTempDevice)
    {
        pdiTempDevice->lpVtbl->Release(pdiTempDevice);
        pdiTempDevice = NULL;
    }

    // set the device's data format
    //
    // This tells the device object to act like a specific device --
    // in our case, like a joystick
    hRes = gpdiJoystick->lpVtbl->SetDataFormat(gpdiJoystick, &c_dfDIJoystick);
    if(FAILED(hRes))
    {
        wsprintf(tszBuf, TEXT("SetDataFormat(Joystick) failed - %08Xh"), hRes);
        MessageBox(hWnd, tszBuf, TEXT("Space Donuts - Force Feedback"), MB_OK);
        return FALSE;
    }

    // set the device's cooperative level
    //
    // ForceFeedback requires Exclusive access to the device.
    hRes = gpdiJoystick->lpVtbl->SetCooperativeLevel(gpdiJoystick, hWnd,
                                                    DISCL_EXCLUSIVE | DISCL_FOREGROUND);
    if(FAILED(hRes))
    {
        wsprintf(tszBuf, TEXT("SetCooperativeLevel(Exclusive | Foreground) failed - %08Xh"), hRes);
        MessageBox(hWnd, tszBuf, TEXT("Space Donuts - Force Feedback"), MB_OK);
        return FALSE;
    }

    // set joystick parameters (deadzone, etc)
    if(!inputPrepareDevice())
    {
        MessageBox(hWnd, TEXT("Device preparation failed"),
                  TEXT("Space Donuts - Force Feedback"), MB_OK);
        return FALSE;
    }

    // get the device capabilities
    //
    // We're going to check to see if the device we created supports
    // ForceFeedback.  If so, we will create effects, if not, we'll
    // support standard joystick functionality
    fIsFFDevice = FALSE;
    didc.dwSize = sizeof(DIDEVCAPS);
    hRes = gpdiJoystick->lpVtbl->GetCapabilities(gpdiJoystick, &didc);
    if(FAILED(hRes))
    {
        wsprintf(tszBuf, TEXT("GetCapabilities() failed - %08Xh"), hRes);
        MessageBox(hWnd, tszBuf, TEXT("Space Donuts - Force Feedback"), MB_OK);
        return FALSE;
    }
    if(didc.dwFlags & DIDC_FORCEFEEDBACK)
    {
        OutputDebugString("ForceFeedback device found.\n");

        // get the gain level from the user
        DialogBox(hInst, MAKEINTRESOURCE(IDD_FORCE), hWnd, inputForceLevelDlgProc);

        // we're supporting ForceFeedback
        fIsFFDevice = TRUE;
        if(!inputCreateEffect(EF_BOUNCE | EF_FIRE | EF_EXPLODE))
        {
            OutputDebugString("inputCreateEffects() failed - ForceFeedback disabled\n");
        }
    } //** end if(ForceFeedback device)

    // if we get here, we succeeded
    return TRUE;

} //*** end inputInitDirectInput()


//===========================================================================
// inputCleanupDirectInput
//
// Cleans up DirectInput objects
//
// Parameters: none
//
// Returns: nothing
//
//===========================================================================
void inputCleanupDirectInput(void)
{
    OutputDebugString("Cleaning up after DirectInput\n");

    // Release() effect objects
    if(gpdieBounce)
    {
        gpdieBounce->lpVtbl->Release(gpdieBounce);
        gpdieBounce = NULL;
    }
    if(gpdieExplode)
    {
        gpdieExplode->lpVtbl->Release(gpdieExplode);
        gpdieExplode = NULL;
    }
    if(gpdieFire)
    {
        gpdieFire->lpVtbl->Release(gpdieFire);
        gpdieFire = NULL;
    }

    // Unacquire() and Release() device objects
    //
    // It is perfectly safe to call Unacquire() on a device that is not
    // currently acquired.  In fact, it is good practice to call
    // Unacquire() just prior to Release().
    if(gpdiJoystick)
    {
        gpdiJoystick->lpVtbl->Unacquire(gpdiJoystick);
        gpdiJoystick->lpVtbl->Release(gpdiJoystick);
        gpdiJoystick = NULL;
    }

    // Release() base object
    if(gpdi)
    {
        gpdi->lpVtbl->Release(gpdi);
        gpdi = NULL;
    }

} //*** end inputCleanupDirectInput()


//===========================================================================
// inputEnumDeviceProc
//
// Enumerates DirectInput devices of type specified in call to
//  IDirectInput::EnumDevices()
//
// Parameters:
//
// Returns:
//
//===========================================================================
BOOL CALLBACK inputEnumDeviceProc(LPDIDEVICEINSTANCE pdidi, LPVOID pv)
{
    GUID *pguidDevice = NULL;

    // validate pv
    // BUGBUG

    // report back the instance guid of the device we enumerated
    if(pv)
    {

        pguidDevice = (GUID *)pv;

        *pguidDevice = pdidi->guidInstance;

    }

    // BUGBUG for now, stop after the first device has been found
    return DIENUM_STOP;

} //*** end inputEnumDeviceProc()


//===========================================================================
// inputEnumEffectTypeProc
//
// Enumerates ForceFeedback effect types (ie "Constant Force").
//
// Parameters:
//
// Returns:
//
//===========================================================================
BOOL CALLBACK inputEnumEffectTypeProc(LPCDIEFFECTINFO pei, LPVOID pv)
{
    GUID *pguidEffect = NULL;

    // validate pv
    // BUGBUG

    // report back the guid of the effect we enumerated
    if(pv)
    {

        pguidEffect = (GUID *)pv;

        *pguidEffect = pei->guid;

    }

    // BUGBUG - look at this some more....
    return DIENUM_STOP;

} //*** end inputEnumEffectTypeProc()


//===========================================================================
// inputAcquireDevices
//
// Acquires the input device(s).
//
// Parameters:
//
// Returns:
//
//===========================================================================
BOOL inputAcquireDevices(void)
{
    if(!gpdiJoystick)
    {
        return FALSE;
    }

    // reacquire the device
    if(SUCCEEDED(gpdiJoystick->lpVtbl->Acquire(gpdiJoystick)))
    {


        // DirectInput automatically resets the device whenever
        // ownership changes, so we can assume we've got a device
        // unsullied by its previous owner.
        inputCreateEffect(EF_BOUNCE | EF_FIRE | EF_EXPLODE);

        return TRUE;
    }
    // if we get here, we did >not< acquire the device
    return FALSE;

} //*** end inputAcquireDevices()


//===========================================================================
// inputCreateEffect
//
// Creates the DirectInputEffect object(s) used by the application
//
// Parameters:
//
// Returns:
//
//===========================================================================
BOOL inputCreateEffect(DWORD dwEffectFlags)
{
    HRESULT         hRes;
    GUID            guidEffect;
    DIEFFECT        diEffect;
    DIENVELOPE      diEnvelope;
    DWORD           rgdwAxes[2];
    LONG            rglDirections[2];
    DICONSTANTFORCE dicf;
    DIPERIODIC      dipf;
    TCHAR           tszBuf[256];

    // make sure that we have a non-NULL device object
    if(!gpdiJoystick)
    {
        return FALSE;
    }

    // initialize DIEFFECT and DIENVELOPE structures
    ZeroMemory(&diEffect, sizeof(DIEFFECT));
    ZeroMemory(&diEnvelope, sizeof(DIENVELOPE));

    // these fields are the same for all effects we will be creating
    diEffect.dwSize                     = sizeof(DIEFFECT);
    diEffect.dwSamplePeriod             = 0; // use default sample period
    diEffect.dwTriggerButton            = DIEB_NOTRIGGER;
    diEffect.dwTriggerRepeatInterval    = 0;
    diEffect.rgdwAxes                   = rgdwAxes;
    diEffect.rglDirection               = rglDirections;
    diEffect.dwGain                     = dwGain; // gain selected by user

    // enumerate for a constant force effect
    //
    // both the "bounce" and "fire" effects will be based on the first
    // constant force effect enumerated
    if((dwEffectFlags & EF_BOUNCE) || (dwEffectFlags & EF_FIRE))
    {
        hRes = gpdiJoystick->lpVtbl->EnumEffects(gpdiJoystick,
                                                (LPDIENUMEFFECTSCALLBACK)inputEnumEffectTypeProc,
                                                &guidEffect, DIEFT_CONSTANTFORCE);
        if(FAILED(hRes))
        {
            OutputDebugString("EnumEffects(Constant Force) failed\n");
            return FALSE;
        }
    }

    // create "bounce" effect
    if(dwEffectFlags & EF_BOUNCE)
    {
        // if we have already created this effect...
        //
        // Call Release() before recreating it
        if(gpdieBounce)
        {
            gpdieBounce->lpVtbl->Release(gpdieBounce);
            gpdieBounce = NULL;
        }

        // prepare the DICONSTANTFORCE structure
        //
        // this is the type-specific data for this force
        dicf.lMagnitude                     = 10000;

        // what axes and directions to use?
        // (directions do not matter at this point, set them to 0)
        rgdwAxes[0]                         = DIJOFS_X;
        rgdwAxes[1]                         = DIJOFS_Y;
        rglDirections[0]                    = 0;
        rglDirections[1]                    = 0;

        // prepare the DIEFFECT structure
        //
        // fill in the force-specific values
        diEffect.dwFlags                    = DIEFF_OBJECTOFFSETS | DIEFF_POLAR;
        diEffect.dwDuration                 = 200000;
        diEffect.cAxes                      = 2;
        diEffect.lpEnvelope                 = NULL;
        diEffect.cbTypeSpecificParams       = sizeof(DICONSTANTFORCE);
        diEffect.lpvTypeSpecificParams      = &dicf;

        // call CreateEffect()
        hRes = gpdiJoystick->lpVtbl->CreateEffect(gpdiJoystick, &guidEffect,
                                                    &diEffect, &gpdieBounce,
                                                    NULL);
        if(FAILED(hRes))
        {
            wsprintf(tszBuf, "CreateEffect(Bounce) failed - %08Xh\n", hRes);
            OutputDebugString(tszBuf);
            return FALSE;
        }

    } //** end if(bounce effect)

    // create "fire" effect
    if(dwEffectFlags & EF_FIRE)
    {
        // if we have already created this effect...
        //
        // Call Release() before recreating it
        if(gpdieFire)
        {
            gpdieFire->lpVtbl->Release(gpdieFire);
            gpdieFire = NULL;
        }

        // prepare the DICONSTANTFORCE structure
        //
        // this is the type-specific data for this force
        dicf.lMagnitude                     = 10000;

        // what axes and directions to use?
        rgdwAxes[0]                         = DIJOFS_Y;
        rglDirections[0]                    = 1;

        // prepare the DIEFFECT structure
        //
        // fill in the force-specific values
        diEffect.dwFlags                    = DIEFF_OBJECTOFFSETS | DIEFF_CARTESIAN;
        diEffect.dwDuration                 = 20000;
        diEffect.cAxes                      = 1;
        diEffect.lpEnvelope                 = NULL;
        diEffect.cbTypeSpecificParams       = sizeof(DICONSTANTFORCE);
        diEffect.lpvTypeSpecificParams      = &dicf;

        // call CreateEffect()
        hRes = gpdiJoystick->lpVtbl->CreateEffect(gpdiJoystick, &guidEffect,
                                                    &diEffect, &gpdieFire,
                                                    NULL);
        if(FAILED(hRes))
        {
            wsprintf(tszBuf, "CreateEffect(Fire) failed - %08Xh\n", hRes);
            OutputDebugString(tszBuf);
            return FALSE;
        }

    } //** end if(fire effect)

    // enumerate for a periodic effect
    //
    // the "explode" effect will be based on the first
    // periodic effect enumerated
    if((dwEffectFlags & EF_EXPLODE))
    {
        hRes = gpdiJoystick->lpVtbl->EnumEffects(gpdiJoystick,
                                                (LPDIENUMEFFECTSCALLBACK)inputEnumEffectTypeProc,
                                                &guidEffect, DIEFT_PERIODIC);
        if(FAILED(hRes))
        {
            OutputDebugString("EnumEffects(Periodic Force) failed\n");
            return FALSE;
        }
    }
    // create "explode" effect
    if(dwEffectFlags & EF_FIRE)
    {
        // if we have already created this effect...
        //
        // Call Release() before recreating it
        if(gpdieExplode)
        {
            gpdieExplode->lpVtbl->Release(gpdieExplode);
            gpdieExplode = NULL;
        }

        // prepare the DIENVELOPE structure
        //
        // We want to shape the explode effect so that it starts
        // at it's peak and then fades out
        diEnvelope.dwSize                   = sizeof(DIENVELOPE);
        diEnvelope.dwAttackLevel            = 0;
        diEnvelope.dwAttackTime             = 0;
        diEnvelope.dwFadeLevel              = 0;
        diEnvelope.dwFadeTime               = 1000000;

        // prepare the DIPERIODIC structure
        //
        // this is the type-specific data for this force
        dipf.dwMagnitude                    = 10000;
        dipf.lOffset                        = 0;
        dipf.dwPhase                        = 0;
        dipf.dwPeriod                       = 100000;

        // what axes and directions to use?
        rgdwAxes[0]                         = DIJOFS_X;
        rglDirections[0]                    = 0;

        // prepare the DIEFFECT structure
        //
        // fill in the force-specific values
        diEffect.dwFlags                    = DIEFF_OBJECTOFFSETS | DIEFF_CARTESIAN;
        diEffect.dwDuration                 = 1000000;
        diEffect.cAxes                      = 1;
        diEffect.lpEnvelope                 = &diEnvelope;
        diEffect.cbTypeSpecificParams       = sizeof(DIPERIODIC);
        diEffect.lpvTypeSpecificParams      = &dipf;

        // call CreateEffect()
        hRes = gpdiJoystick->lpVtbl->CreateEffect(gpdiJoystick, &guidEffect,
                                                    &diEffect, &gpdieExplode,
                                                    NULL);
        if(FAILED(hRes))
        {
            wsprintf(tszBuf, "CreateEffect(Explode) failed - %08Xh\n", hRes);
            OutputDebugString(tszBuf);
            return FALSE;
        }

    } //** end if(explode effect)

    return TRUE;

} //*** end inputCreateEffects()


//===========================================================================
// inputProcessDeviceInput
//
// Processes data from the input device.  Uses GetDeviceState().
//
// Parameters:
//
// Returns:
//
//===========================================================================
DWORD inputProcessDeviceInput(void)
{
    HRESULT     hRes;
    DIJOYSTATE  dijs;
    DWORD       dwInput = 0;

    // poll the joystick to read the current state
    hRes = gpdiJoystick->lpVtbl->Poll(gpdiJoystick);

    // read the device state
    hRes = gpdiJoystick->lpVtbl->GetDeviceState(gpdiJoystick, sizeof(DIJOYSTATE),
                                                &dijs);
    if(FAILED(hRes))
    {
        if((hRes == DIERR_INPUTLOST))
        {
            inputAcquireDevices();
        }

        // we did not read anything, return no motion
        return 0;
    }

    // process device state
    //
    // to preserve as much of the existing input handling code from the
    // original space donuts sample, we will be converting the joystick data to
    // "keyboard" input

    //* x-axis (left)
    if(dijs.lX < 0)
    {
        dwInput |= KEY_LEFT;
    }
    //* x-axis (right)
    if(dijs.lX > 0)
    {
        dwInput |= KEY_RIGHT;
    }
    //* y-axis (forward)
    if(dijs.lY < 0)
    {
        dwInput |= KEY_UP;
    }
    //* y-axis (backward)
    if(dijs.lY > 0)
    {
        dwInput |= KEY_DOWN;
    }
    //* button 0 (fire)
    if(dijs.rgbButtons[0] & 0x80)
    {
        dwInput |= KEY_FIRE;
    }
    //* button 1 (shield)
    if(dijs.rgbButtons[1] & 0x80)
    {
        dwInput |= KEY_SHIELD;
    }
    //* button 2 (stop) - requires a joystick with more than 2 buttons
    if(dijs.rgbButtons[2] & 0x80)
    {
        dwInput |= KEY_STOP;
    }

    // return the new device state
    return dwInput;

} //*** end inputProcessDeviceInput()


//===========================================================================
// inputPrepareDevice
//
// Performs device preparation by setting the device's parameters (ie
// deadzone).
//
// Parameters:
//
// Returns:
//
//===========================================================================
BOOL inputPrepareDevice(void)
{
    HRESULT       hRes;
    DIPROPRANGE   dipr;
    DIPROPDWORD   dipdw;


    // quick check to make sure that the object pointer is non-NULL
    if(!gpdiJoystick)
    {
        return FALSE;
    }

    // call Unacquire() on the device
    //
    // SetParameter() will fail if a device is currently acquired, we are
    // doing this here in case we get careless and forget to call this
    // function either before we call Acquire() or after we call Unacquire().
    gpdiJoystick->lpVtbl->Unacquire(gpdiJoystick);

    // set the axis ranges for the device
    //
    // We will use the same range for the X and Y axes.  We are setting them
    // fairly low since we are not concerned with anything other than
    // "left", "right", "forward", "backward" and "centered"
	//* prepare DIPROPRANGE structure
    dipr.diph.dwSize        = sizeof(DIPROPRANGE);
	dipr.diph.dwHeaderSize  = sizeof(dipr.diph);
	dipr.diph.dwHow         = DIPH_BYOFFSET;
	dipr.lMin               = RANGE_MIN;  // negative to the left/top
	dipr.lMax               = RANGE_MAX;  // positive to the right/bottom
    //* x-axis
    dipr.diph.dwObj         = DIJOFS_X;
    //* set the x-axis range property
    hRes = gpdiJoystick->lpVtbl->SetProperty(gpdiJoystick, DIPROP_RANGE, &dipr.diph);
    if(FAILED(hRes))
    {
        OutputDebugString("SetProperty(RANGE, X-Axis) failed.\n");
        return FALSE;
    }
    //* y-axis
    dipr.diph.dwObj         = DIJOFS_Y;
    hRes = gpdiJoystick->lpVtbl->SetProperty(gpdiJoystick, DIPROP_RANGE, &dipr.diph);
    if(FAILED(hRes))
    {
        OutputDebugString("SetProperty(RANGE, Y-Axis) failed.\n");
        return FALSE;
    }

    // set the deadzone for the device
    //
    // We will use the same deadzone percentage for the X and Y axes.
    // This call uses a symbolic constant for the deadzone percentage so that
    // it is easy to change if we decide we don't like it.
	//* prepare DIPROPDWORD structure
	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwHow        = DIPH_BYOFFSET;
	dipdw.dwData            = DEADZONE;
    //* set the x-axis range property
    dipdw.diph.dwObj         = DIJOFS_X;
    hRes = gpdiJoystick->lpVtbl->SetProperty(gpdiJoystick, DIPROP_DEADZONE, &dipdw.diph);
    if(FAILED(hRes))
    {
        OutputDebugString("SetProperty(DEADZONE, X-Axis) failed.\n");
        return FALSE;
    }
    //* y-axis
    dipdw.diph.dwObj         = DIJOFS_Y;
    hRes = gpdiJoystick->lpVtbl->SetProperty(gpdiJoystick, DIPROP_DEADZONE, &dipdw.diph);
    if(FAILED(hRes))
    {
        OutputDebugString("SetProperty(DEADZONE, Y-Axis) failed.\n");
        return FALSE;
    }

    // set the ForceFeedback gain
    //
    // If the device supports feedback, use the user selected gain level
    // to scale the strength of the forces applied to the stick.  We do this
    // so that if a small child is playing the game, the stick does not jerk
    // hard enough to hurt them, yet an adult can have a stronger force
    // experience
    if(fIsFFDevice)
    {
        // BUGBUG get setting from user (done somewhere else)
        dwGain = FF_ADULT;
    }

    // Acquire the device(s)
    //
    // This is being done as a convenience since we unacquired earlier in
    // this function.  This does not guarantee that the device will be
    // acquired at the time we return from the function (in other words, we
    // are not going to spin here until we get a succeessful acquisition).
    inputAcquireDevices();

    // we've actually done somthing here
    return TRUE;

} //** end inputPrepareDevice()


//===========================================================================
// inputPlayEffect
//
// Plays specified effect object.
//
// Parameters:
//
// Returns:
//
//===========================================================================
BOOL inputPlayEffect(DWORD dwEffectFlags, LONG lDirection)
{
    HRESULT         hRes;
    DIEFFECT        diEffect;
    LONG            rglDirections[2] = { 0, 0 };

    // initialize DIEFFECT structure
    ZeroMemory(&diEffect, sizeof(DIEFFECT));
    diEffect.dwSize = sizeof(DIEFFECT);

    // play "bounce" effect?
    if(dwEffectFlags & EF_BOUNCE)
    {
        if(gpdieBounce)
        {
            // set the direction
            //
            // since this is a polar coordinate effect, we will pass the angle
            // in as the direction relative to the x-axis, and will leave 0
            // for the y-axis direction
            //
            // Direction is passed in in degrees, we convert to 100ths
            // of a degree to make it easier for the caller.
            rglDirections[0]        = lDirection * 100;
            diEffect.dwFlags        = DIEFF_OBJECTOFFSETS | DIEFF_POLAR;
            diEffect.cAxes          = 2;
            diEffect.rglDirection   = rglDirections;
            hRes = gpdieBounce->lpVtbl->SetParameters(gpdieBounce,
                                                        &diEffect,
                                                        DIEP_DIRECTION);
            if(FAILED(hRes))
            {
                OutputDebugString("SetParameters(Bounce effect) failed\n");
                return FALSE;
            }

            // play the effect
            hRes = gpdieBounce->lpVtbl->Start(gpdieBounce, 1, 0);
            if(FAILED(hRes))
            {
                OutputDebugString("Start(Bounce effect) failed\n");
                return FALSE;
            }

        }

    } //** end if(play bounce)

    // play "fire" effect?
    if(dwEffectFlags & EF_FIRE)
    {
        if(gpdieFire)
        {
            // play the effect
            hRes = gpdieFire->lpVtbl->Start(gpdieFire, 1, 0);
            if(FAILED(hRes))
            {
                OutputDebugString("Start(Fire effect) failed\n");
                return FALSE;
            }
        }
    } //** end if(play fire)

    // play "explode" effect?
    if(dwEffectFlags & EF_EXPLODE)
    {
        if(gpdieExplode)
        {
            // BUGBUG how many iterations of the effect??
            hRes = gpdieExplode->lpVtbl->Start(gpdieExplode, 1, 0);
            if(FAILED(hRes))
            {
                OutputDebugString("Start(Explode effect) failed\n");
                return FALSE;
            }
        }
    } //** end if(play explode)

    return TRUE;

} //*** end inputPlayEffect()


//===========================================================================
// inputForceLevelDlgProc
//
// Dialog proceedure for handling the Force Level dialog box.
//
// Parameters:
//
// Returns:
//
//===========================================================================
BOOL CALLBACK inputForceLevelDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                                    LPARAM lParam)
{
    int nSelection = 0;

    switch(uMsg)
    {
        case WM_INITDIALOG:
             // select default / current setting
             switch(dwGain)
             {
                case FF_CHILD:
                     nSelection = IDC_CHILD;
                     break;

                case FF_BODYBUILDER:
                     nSelection = IDC_BODYBUILDER;
                     break;

                case FF_ADULT:
                default:
                     nSelection = IDC_ADULT;
                     break;
             }
             CheckRadioButton(hWnd, IDC_CHILD, IDC_BODYBUILDER, nSelection);
             return TRUE;

        case WM_COMMAND:
             {
                switch(LOWORD(wParam))
                {
                    case IDOK:
                         // get user's force level selection
                         // BUGBUG
                         if(IsDlgButtonChecked(hWnd, IDC_CHILD))
                         {
                            OutputDebugString("Child level\n");
                            dwGain = FF_CHILD;
                         }
                         else if(IsDlgButtonChecked(hWnd, IDC_BODYBUILDER))
                         {
                            OutputDebugString("Bodybuilder level\n");
                            dwGain = FF_BODYBUILDER;
                         }
                         else
                         {
                            OutputDebugString("Adult level (Default)\n");
                            dwGain = FF_ADULT;
                         }
                         EndDialog(hWnd, 0);
                         break;
                }

             }
             break;

    }

    return FALSE;
}
