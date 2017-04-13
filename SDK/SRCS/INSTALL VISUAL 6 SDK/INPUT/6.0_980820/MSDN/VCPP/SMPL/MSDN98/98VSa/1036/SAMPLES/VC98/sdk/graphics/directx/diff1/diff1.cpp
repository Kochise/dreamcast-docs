/**************************************************************************

    DIFF1.CPP - DirectInput simple force feedback sample 1

    Demonstrates an application which plays a force on the joystick
    in response to mouse clicks.

 **************************************************************************/
/**************************************************************************

    (C) Copyright 1997 Microsoft Corp.  All rights reserved.

    You have a royalty-free right to use, modify, reproduce and
    distribute the Sample Files (and/or any modified version) in
    any way you find useful, provided that you agree that
    Microsoft has no warranty obligations or liability for any
    Sample Application Files which are modified.

 **************************************************************************/

#include "diff1.h"
#include <windowsx.h>
#include <dinput.h>
#include <math.h>

/****************************************************************************
 *
 *      Global variables
 *
 ****************************************************************************/

char c_szClassName[] = "DIFF1";

HINSTANCE       g_hinst;                /* My instance handle */
BOOL            g_fPaused = TRUE;       /* Should I be paused? */
int             g_xForce;               /* Coordinates of the active force */
int             g_yForce;
int             g_cxClient;             /* Client window size */
int             g_cyClient;

/****************************************************************************
 *
 *      DirectInput globals
 *
 ****************************************************************************/

LPDIRECTINPUT           g_pdi;
LPDIRECTINPUTDEVICE2    g_pJoystick;
LPDIRECTINPUTEFFECT     g_pEffect;

/****************************************************************************
 *
 *      Complain
 *
 *      Whine and moan.
 *
 ****************************************************************************/

void
Complain(
    HWND hwndOwner,
    HRESULT hr,
    LPCSTR pszMessage
)
{
    MessageBox(hwndOwner, pszMessage, "DirectInput Sample", MB_OK);
}

/****************************************************************************
 *
 *      EnumFFJoysticksCallback
 *
 *      Called once for each enumerated force feedback joystick.
 *
 *      If we find one, create a device interface on it so we can
 *      play with it.
 *
 *      Parameters:
 *
 *          pinst
 *
 *              Pointer to DIDEVICEINSTANCE structure which describes
 *              the device.
 *
 *          lpvContext
 *
 *              The pointer we passed to EnumDevices which we don't
 *              use for anything.
 *
 ****************************************************************************/

BOOL CALLBACK
EnumFFJoysticksCallback(LPCDIDEVICEINSTANCE pinst, LPVOID lpvContext)
{
    HRESULT hr;
    LPDIRECTINPUTDEVICE pdev;
    LPDIRECTINPUTDEVICE2 pdev2;

    /*
     *  Obtain an interface to the enumerated force feedback joystick.
     *
     *  Parameters:
     *
     *      pinst->guidInstance
     *
     *          The instance GUID for the device we wish to access.
     *
     *      &pdev
     *
     *          Receives pointer to the IDirectInputDevice interface
     *          that was created.
     *
     *      NULL
     *
     *          We do not use OLE aggregation, so this parameter
     *          must be NULL.
     *
     */
    hr = g_pdi->CreateDevice(pinst->guidInstance, &pdev, NULL);

    /*
     *  If it failed, then we can't use this joystick for some
     *  bizarre reason.  (Maybe the user unplugged it while we
     *  were in the middle of enumerating it.)
     *
     *  Continue enumerating; maybe we'll have better luck with the
     *  next one.
     */
    if (FAILED(hr)) {
        return DIENUM_CONTINUE;
    }

    /*
     *  We really want to use IDirectInputDevice2, so move there
     *  once and for all.
     *
     *  Parameters:
     *
     *      IID_IDirectInputDevice2
     *
     *          The interface we are requesting.
     *
     *      &pdev2
     *
     *          Receives a pinter to the new interface.
     */

    hr = pdev->QueryInterface(IID_IDirectInputDevice2,
                              (LPVOID *)&pdev2);

    /*
     *  Whether or not the QueryInterface worked, we are finished
     *  with the old interface.
     */
    pdev->Release();

    /*
     *  If the QueryInterface failed, then something weird happened.
     *  Maybe the currently-installed version of DirectInput doesn't
     *  support force feedback.
     *
     *  Continue enumerating; maybe we'll have better luck with the
     *  next one.
     */
    if (FAILED(hr)) {
        return DIENUM_CONTINUE;
    }

    /*
     *  We successfully created an IDirectInputDevice2.
     *
     *  No point in looking for another one.
     */
    g_pJoystick = pdev2;
    return DIENUM_STOP;

}

/****************************************************************************
 *
 *      DIInit
 *
 *      Initialize the DirectInput variables.
 *
 *      This entails the following four functions:
 *
 *          DirectInputCreate
 *          IDirectInput::EnumDevices           (to find a joystick)
 *          IDirectInputDevice2::SetDataFormat
 *          IDirectInputDevice2::SetCooperativeLevel
 *          IDirectInputDevice2::SetProperty    (to disable auto-center)
 *          IDirectInputDevice2::CreateEffect
 *
 ****************************************************************************/

BOOL
DIInit(HWND hwnd)
{
    HRESULT hr;

    /*
     *  Register with the DirectInput subsystem and get a pointer
     *  to a IDirectInput interface we can use.
     *
     *  Parameters:
     *
     *      g_hinst
     *
     *          Instance handle to our application or DLL.
     *
     *      DIRECTINPUT_VERSION
     *
     *          The version of DirectInput we were designed for.
     *          We take the value from the <dinput.h> header file.
     *
     *      &g_pdi
     *
     *          Receives pointer to the IDirectInput interface
     *          that was created.
     *
     *      NULL
     *
     *          We do not use OLE aggregation, so this parameter
     *          must be NULL.
     *
     */
    hr = DirectInputCreate(g_hinst, DIRECTINPUT_VERSION, &g_pdi, NULL);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "DirectInputCreate");
        return FALSE;
    }

    /*
     *  Look for a force feedback joystick we can use for this
     *  sample program.
     *
     *  Parameters:
     *
     *      DIDEVTYPE_JOYSTICK
     *
     *          Enumerate only joystick devices.
     *
     *      EnumFFJoysticksCallback
     *
     *          Callback function that is called once for
     *          each force feedback joystick found.
     *
     *      NULL
     *
     *          Context which is passed to the callback function.
     *
     *      DIEDFL_ATTACHEDONLY | DIEDFL_FORCEFEEDBACK
     *
     *          Flags that further restrict the enumeration.
     *
     *          We are interested only in attached joysticks
     *          which support force feedback.
     */
    hr = g_pdi->EnumDevices(DIDEVTYPE_JOYSTICK,
                            EnumFFJoysticksCallback,
                            NULL,
                            DIEDFL_ATTACHEDONLY | DIEDFL_FORCEFEEDBACK);

    if (g_pJoystick == NULL) {
        Complain(hwnd, hr, "Couldn't find any force feedback joysticks");
        return FALSE;
    }

    /*
     *  Set the data format to "simple joystick format".
     *
     *  A data format specifies which controls on a device we
     *  are interested in, and how they should be reported.
     *
     *  This tells DirectInput that we will be passing a
     *  DIJOYSTATE structure to IDirectInputDevice2::GetDeviceState.
     *  Even though we won't actually do it in this sample.
     *  But setting the data format is important so that
     *  the DIJOFS_* values work properly.
     *
     *  Parameters:
     *
     *      c_dfDIJoystick
     *
     *          Predefined data format which describes
     *          a DIJOYSTATE structure.
     */
    hr = g_pJoystick->SetDataFormat(&c_dfDIJoystick);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "SetDataFormat");
        return FALSE;
    }


    /*
     *  Set the cooperativity level to let DirectInput know how
     *  this device should interact with the system and with other
     *  DirectInput applications.
     *
     *  Parameters:
     *
     *      DISCL_EXCLUSIVE
     *
     *          Exclusive access is required in order to perform
     *          force feedback.
     *
     *      DISCL_FOREGROUND
     *
     *          If the user switches away from our application,
     *          automatically release the joystick back to the system.
     *
     */
    hr = g_pJoystick->SetCooperativeLevel(hwnd,
                                          DISCL_EXCLUSIVE | DISCL_FOREGROUND);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "SetCooperativeLevel");
        return FALSE;
    }

    /*
     *  Since we will be playing force feedback effects,
     *  we should disable the auto-centering spring.
     *
     *  DIPROPDWORD::diph.dwSize
     *
     *      Must be sizeof(DIPROPDWORD)
     *
     *  DIPROPDWORD::diph.dwHeaderSize
     *
     *      Must be sizeof(DIPROPHEADER)
     *
     *  DIPROPDWORD::diph.dwObj
     *
     *      Must be zero for device properties.
     *
     *  DIPROPDWORD::diph.dwHow
     *
     *      DIPH_DEVICE for device properties.
     *
     *  DIPROPDWORD::dwData
     *
     *      FALSE to disable auto-centering.
     */
    DIPROPDWORD dipdw;
    dipdw.diph.dwSize = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj = 0;
    dipdw.diph.dwHow = DIPH_DEVICE;
    dipdw.dwData = FALSE;

    hr = g_pJoystick->SetProperty(DIPROP_AUTOCENTER, &dipdw.diph);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "SetProperty(Autocenter)");
        return FALSE;
    }

    /*
     *  This application needs only one effect:  Applying raw forces.
     *
     *  DIEFFECT::dwSize
     *
     *          Must be sizeof(DIEFFECT).
     *
     *  DIEFFECT::dwFlags
     *
     *          DIEFF_CARTESIAN because we will be applying X and Y
     *          forces, not angles.
     *
     *          DIEFF_OBJECTOFFSETS because we will be using the
     *          DIJOFS_* macros to specify the axes.
     *
     *  DIEFFECT::dwDuration
     *
     *          INFINITE because we want the force to continue playing
     *          indefinitely until we explicitly change it.
     *
     *  DIEFFECT::dwSamplePeriod
     *
     *          0 means "use default".  Using a custom sample period
     *          is a special effect which we don't particularly care
     *          about.
     *
     *  DIEFFECT::dwGain
     *
     *          DI_FFNOMINALMAX to play all values at exactly the
     *          strength we specify.
     *
     *  DIEFFECT::dwTriggerButton
     *
     *          DIEB_NOTRIGGER because we don't want this effect
     *          to be associated with a trigger.
     *
     *  DIEFFECT::dwTriggerRepeatInterval
     *
     *          0 because there no trigger.
     *
     *  DIEFFECT::cAxes
     *
     *          2 because we have two axes, X and Y.
     *
     *  DIEFFECT::rgdwAxes
     *
     *          Points to an array which identifies the two axes
     *          we want to talk to, namely X and Y.
     *
     *  DIEFFECT::rglDirection
     *
     *          Points to an array which gives the direction in
     *          which the force should be applied.
     *          Nothing yet.
     *
     *  DIEFFECT::lpEnvelope
     *
     *          NULL because we don't want to apply an envelope
     *          to the effect.
     *
     *  DIEFFECT::cbTypeSpecificParameters
     *  DIEFFECT::lpvTypeSpecificParameters
     *
     *          Size of and pointer to type-specific parameters.
     *          For a constant force effect, we need a
     *          DICONSTANTFORCE structure.
     */

    DIEFFECT eff;
    DWORD rgdwAxes[2] = { DIJOFS_X, DIJOFS_Y };
    LONG rglDirection[2] = { 0, 0 };
    DICONSTANTFORCE cf = { 0 };

    eff.dwSize = sizeof(DIEFFECT);
    eff.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
    eff.dwDuration = INFINITE;
    eff.dwSamplePeriod = 0;
    eff.dwGain = DI_FFNOMINALMAX;
    eff.dwTriggerButton = DIEB_NOTRIGGER;
    eff.dwTriggerRepeatInterval = 0;
    eff.cAxes = 2;
    eff.rgdwAxes = rgdwAxes;
    eff.rglDirection = rglDirection;
    eff.lpEnvelope = 0;
    eff.cbTypeSpecificParams = sizeof(DICONSTANTFORCE);
    eff.lpvTypeSpecificParams = &cf;

    /*
     *  Now create this effect we prepared.
     *
     *  Parameters:
     *
     *      GUID_ConstantForce
     *
     *          We are playing a raw force, plain and simple.
     *
     *      &eff
     *
     *          The DIEFFECT structure that describes it.
     *
     *      &g_pEffect
     *
     *          Receives pointer to the IDirectInputEffect interface
     *          that was created.
     *
     *      NULL
     *
     *          We do not use OLE aggregation, so this parameter
     *          must be NULL.
     *
     */
    hr = g_pJoystick->CreateEffect(GUID_ConstantForce,
                                   &eff,
                                   &g_pEffect,
                                   NULL);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "CreateEffect");
        return FALSE;
    }

    return TRUE;

}

/****************************************************************************
 *
 *      DITerm
 *
 *      Terminate our usage of DirectInput.
 *
 ****************************************************************************/

void
DITerm(void)
{

    /*
     *  Destroy any lingering IDirectInputEffect object.
     */
    if (g_pEffect) {

        g_pEffect->Release();
        g_pEffect = NULL;
    }

    /*
     *  Destroy any lingering IDirectInputDevice object.
     */
    if (g_pJoystick) {

        /*
         *  Cleanliness is next to godliness.  Unacquire the device
         *  one last time just in case we got really confused and tried
         *  to exit while the device is still acquired.
         */
        g_pJoystick->Unacquire();

        g_pJoystick->Release();
        g_pJoystick = NULL;
    }

    /*
     *  Destroy any lingering IDirectInput object.
     */
    if (g_pdi) {
        g_pdi->Release();
        g_pdi = NULL;
    }

}

/****************************************************************************
 *
 *      joySetForcesXY
 *
 *      Apply the X and Y forces to the effect we prepared.
 *
 *      Parameters:
 *
 *          peff
 *
 *              Pointer to a constant-force LPDIRECTINPUEFFECT
 *              which we will push in the appropriate direction
 *              with the appropriate amount of force.
 *
 *          x, y
 *
 *              X and Y forces to apply, respectively, in the
 *              range -DI_FFNOMINALMAX to +DI_FFNOMINALMAX.
 *
 ****************************************************************************/

HRESULT
joySetForcesXY(LPDIRECTINPUTEFFECT peff, int x, int y)
{
    HRESULT hres;

    /*
     *  Modifying an effect is basically the same as creating
     *  a new one, except you need only specify the parameters
     *  you are modifying; the rest are left alone.
     *
     *  DIEFFECT::dwSize
     *
     *          Must be sizeof(DIEFFECT).
     *
     *  DIEFFECT::dwFlags
     *
     *          DIEFF_CARTESIAN because we will be applying X and Y
     *          forces, not angles.
     *
     *          DIEFF_OBJECTOFFSETS because we used the
     *          DIJOFS_* macros to specify the axes.
     *
     *  DIEFFECT::cAxes
     *
     *          2 because we have two axes, X and Y.
     *
     *  DIEFFECT::rglDirection
     *
     *          Points to an array which gives the direction in
     *          which the force should be applied.
     *
     *          We use the x and y values directly to specify
     *          the direction.  Note that DirectInput currently
     *          uses these values to specify direction only, not
     *          magnitude.  Magnitude needs to be specified
     *          elsewhere.  (See below.)
     *
     *  DIEFFECT::cbTypeSpecificParameters
     *  DIEFFECT::lpvTypeSpecificParameters
     *
     *          Size of and pointer to type-specific parameters.
     *          For a constant force effect, we need a
     *          DICONSTANTFORCE structure.
     *
     *  DICONSTANTFORCE::lMagnitude
     *
     *          The total magnitude of the force, which is
     *          the hypotenuse of x and y.
     */

    LONG rglDirection[2] = { x, y };

    DICONSTANTFORCE cf;
    cf.lMagnitude = (DWORD)sqrt((double)x * (double)x +
                                (double)y * (double)y);

    DIEFFECT eff;
    eff.dwSize = sizeof(DIEFFECT);
    eff.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
    eff.cAxes = 2;
    eff.rglDirection = rglDirection;
    eff.lpEnvelope = 0;
    eff.cbTypeSpecificParams = sizeof(DICONSTANTFORCE);
    eff.lpvTypeSpecificParams = &cf;

    /*
     *  Now set the new parameters and start the effect immediately.
     *
     *  Parameters:
     *
     *      &eff
     *
     *          The DIEFFECT structure that describes the new parameters.
     *
     *      DIEP_DIRECTION
     *      DIEP_TYPESPECIFICPARAMS
     *
     *          We want to change the direction and the DICONSTANTFORCE.
     *
     *      DIEP_START
     *
     *          Start the effect as soon as the parameters are downloaded.
     */
    hres = peff->SetParameters(&eff, DIEP_DIRECTION |
                                     DIEP_TYPESPECIFICPARAMS |
                                     DIEP_START);

    return hres;
}

/****************************************************************************
 *
 *      Ex_SyncAcquire
 *
 *      Acquire or unacquire the joystick, depending on the the g_fPaused
 *      flag.  This synchronizes the device with our internal view of
 *      the world.
 *
 ****************************************************************************/

void
Ex_SyncAcquire(HWND hwnd)
{
    if (g_fPaused) {
        if (g_pJoystick) {
            g_pJoystick->Unacquire();
        }
    } else {
        if (g_pJoystick) g_pJoystick->Acquire();
        if (g_pEffect) {
            g_pEffect->Start(1, 0);
        }
    }
}

/****************************************************************************
 *
 *      Ex_OnSize
 *
 *      The window client size changed.  Remember the new size.
 *
 ****************************************************************************/

void
Ex_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
    g_cxClient = cx;
    g_cyClient = cy;
}

/****************************************************************************
 *
 *      Ex_OnPaint
 *
 *      Paint our little target area thingie.
 *
 *      We draw a small crosshairs at the center (so the user knows
 *      where the center is)
 *
 ****************************************************************************/

void
Ex_OnPaint(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    if (hdc) {

        HPEN hpenOld, hpenBlack;
        HBRUSH hbrOld, hbrBlack;
        int x, y;

        /*
         *  Everything is scaled to the size of the window.
         */

        hpenBlack = GetStockPen(BLACK_PEN);
        hpenOld = SelectPen(hdc, hpenBlack);

        x = g_cxClient / 2;
        y = g_cyClient / 2;

        MoveToEx(hdc, x, y - 10, NULL);
        LineTo(hdc, x, y + 10 + 1);

        MoveToEx(hdc, x - 10, y, NULL);
        LineTo(hdc, x + 10 + 1, y);

        hbrBlack = GetStockBrush(BLACK_BRUSH);
        hbrOld = SelectBrush(hdc, hbrBlack);

        x = MulDiv(g_cxClient, g_xForce + DI_FFNOMINALMAX, 2 * DI_FFNOMINALMAX);
        y = MulDiv(g_cyClient, g_yForce + DI_FFNOMINALMAX, 2 * DI_FFNOMINALMAX);

        Ellipse(hdc, x-5, y-5, x+6, y+6);

        SelectBrush(hdc, hbrOld);
        SelectPen(hdc, hpenOld);

        EndPaint(hwnd, &ps);
    }

}

/****************************************************************************
 *
 *      Ex_CoordToForce
 *
 *      Convert a coordinate 0 <= x <= cx to a force value
 *      in the range -DI_FFNOMINALMAX to +DI_FFNOMINALMAX.
 *
 ****************************************************************************/

int
Ex_CoordToForce(int x, int cx)
{
    x = MulDiv(x, 2 * DI_FFNOMINALMAX, cx) - DI_FFNOMINALMAX;
    if (x < -DI_FFNOMINALMAX) {
        x = -DI_FFNOMINALMAX;
    }
    if (x > +DI_FFNOMINALMAX) {
        x = +DI_FFNOMINALMAX;
    }
    return x;
}

/****************************************************************************
 *
 *      Ex_OnMouseMove
 *
 *      If the mouse button is down, then change the direction of
 *      the force to match the new location.
 *
 ****************************************************************************/

void
Ex_OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
    if (keyFlags & MK_LBUTTON) {
        g_xForce = Ex_CoordToForce(x, g_cxClient);
        g_yForce = Ex_CoordToForce(y, g_cyClient);

        InvalidateRect(hwnd, 0, TRUE);
        UpdateWindow(hwnd);

        joySetForcesXY(g_pEffect, g_xForce, g_yForce);

    }
}

/****************************************************************************
 *
 *      Ex_OnLButtonDown
 *
 *      Capture the mouse so we can follow it, and start updating the
 *      force information.
 *
 ****************************************************************************/

void
Ex_OnLButtonDown(HWND hwnd, BOOL fDblClk, int x, int y, UINT keyFlags)
{
    SetCapture(hwnd);
    Ex_OnMouseMove(hwnd, x, y, MK_LBUTTON);
}

/****************************************************************************
 *
 *      Ex_OnLButtonUp
 *
 *      Stop capturing the mouse when the button goes up.
 *
 ****************************************************************************/

void
Ex_OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
    ReleaseCapture();
}

/****************************************************************************
 *
 *      Ex_WndProc
 *
 *      Window procedure for simple force feedback sample.
 *
 ****************************************************************************/

LRESULT CALLBACK
Ex_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch (msg) {

    HANDLE_MSG(hwnd, WM_PAINT, Ex_OnPaint);
    HANDLE_MSG(hwnd, WM_MOUSEMOVE, Ex_OnMouseMove);
    HANDLE_MSG(hwnd, WM_LBUTTONDOWN, Ex_OnLButtonDown);
    HANDLE_MSG(hwnd, WM_LBUTTONUP, Ex_OnLButtonUp);
    HANDLE_MSG(hwnd, WM_SIZE, Ex_OnSize);

    /*
     *  WM_ACTIVATE
     *
     *      Windows sends this message when the window becomes
     *      the active window or stops being the active window.
     *
     *      wParam = WA_INACTIVE if window is no longer active
     *
     *      wParam = WA_ACTIVE or WA_CLICKACTIVE if window is now active
     *
     *      If we are losing activation, then pause.
     *
     *      If we are gaining activation, then unpause.
     *
     *      After deciding whether we are paused or unpaused,
     *      tell DirectInput that we don't (paused) or do (unpaused)
     *      want access to the joystick.
     *
     */
    case WM_ACTIVATE:
        g_fPaused = wParam == WA_INACTIVE;
        Ex_SyncAcquire(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

/****************************************************************************
 *
 *      AppInit
 *
 *      Set up everything the application needs to get started.
 *
 ****************************************************************************/

HWND
AppInit(
    HINSTANCE hinst,
    int nCmdShow
)
{

    /*
     *  Save instance handle for future reference.
     */
    g_hinst = hinst;

    /*
     *  Set up the window class.
     */
    WNDCLASS wc;

    wc.hCursor        = LoadCursor(0, IDC_ARROW);
    wc.hIcon          = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
    wc.lpszMenuName   = NULL;
    wc.lpszClassName  = c_szClassName;
    wc.hbrBackground  = GetStockBrush(WHITE_BRUSH);
    wc.hInstance      = hinst;
    wc.style          = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc    = Ex_WndProc;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0;

    if (!RegisterClass(&wc)) {
        return NULL;
    }

    HWND hwnd = CreateWindow(
                    c_szClassName,                  // Class name
                    "DIFF1 - Click in target to change force value", // Caption
                    WS_OVERLAPPEDWINDOW,            // Style
                    CW_USEDEFAULT, CW_USEDEFAULT,   // Position
                    CW_USEDEFAULT, CW_USEDEFAULT,   // Size
                    NULL,                           // No parent
                    NULL,                           // No menu
                    g_hinst,                        // inst handle
                    0                               // no params
                    );

    if (!DIInit(hwnd)) {
        DestroyWindow(hwnd);
        return NULL;
    }

    ShowWindow(hwnd, nCmdShow);

    return hwnd;
}

/****************************************************************************
 *
 *      WinMain
 *
 *      Application entry point.
 *
 ****************************************************************************/

int PASCAL
WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR szCmdLine, int nCmdShow)
{
    MSG msg;
    msg.wParam = 0;         /* In case something goes horribly wrong */

    HWND hwnd = AppInit(hinst, nCmdShow);

    if (hwnd) {

        /*
         *  Standard message loop.
         */
        while (GetMessage(&msg, NULL, 0, 0)) {

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    DITerm();

    return msg.wParam;

}
