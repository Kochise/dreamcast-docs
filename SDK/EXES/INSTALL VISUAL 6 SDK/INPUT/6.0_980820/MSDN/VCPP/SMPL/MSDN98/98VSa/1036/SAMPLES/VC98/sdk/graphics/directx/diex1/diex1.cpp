/**************************************************************************

    DIEX1.CPP - DirectInput simple sample 1

    Demonstrates an application which receives relative mouse data
    in non-exclusive mode via a game loop.

 **************************************************************************/
/**************************************************************************

    (C) Copyright 1997 Microsoft Corp.  All rights reserved.

    You have a royalty-free right to use, modify, reproduce and
    distribute the Sample Files (and/or any modified version) in
    any way you find useful, provided that you agree that
    Microsoft has no warranty obligations or liability for any
    Sample Application Files which are modified.

 **************************************************************************/

#include <windows.h>
#include <dinput.h>

#include "diex1.h"

/****************************************************************************
 *
 *      Global variables
 *
 ****************************************************************************/

char c_szClassName[] = "DIEX1";

HINSTANCE       g_hinst;                /* My instance handle */
BOOL            g_fPaused = TRUE;       /* Should I be paused? */

/****************************************************************************
 *
 *      DirectInput globals
 *
 ****************************************************************************/

LPDIRECTINPUT           g_pdi;
LPDIRECTINPUTDEVICE     g_pMouse;
char                    g_szText[1024]; /* What we display in client area */

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
 *      DIInit
 *
 *      Initialize the DirectInput variables.
 *
 *      This entails the following four functions:
 *
 *          DirectInputCreate
 *          IDirectInput::CreateDevice
 *          IDirectInputDevice::SetDataFormat
 *          IDirectInputDevice::SetCooperativeLevel
 *
 ****************************************************************************/

BOOL
DIInit(
    HWND hwnd
)
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
     *  Obtain an interface to the system mouse device.
     *
     *  Parameters:
     *
     *      GUID_SysMouse
     *
     *          The instance GUID for the device we wish to access.
     *          GUID_SysMouse is a predefined instance GUID that
     *          always refers to the system mouse device.
     *
     *      &g_pMouse
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
    hr = g_pdi->CreateDevice(GUID_SysMouse, &g_pMouse, NULL);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "CreateDevice");
        return FALSE;
    }

    /*
     *  Set the data format to "mouse format".
     *
     *  A data format specifies which controls on a device we
     *  are interested in, and how they should be reported.
     *
     *  This tells DirectInput that we will be passing a
     *  DIMOUSESTATE structure to IDirectInputDevice::GetDeviceState.
     *
     *  Parameters:
     *
     *      c_dfDIMouse
     *
     *          Predefined data format which describes
     *          a DIMOUSESTATE structure.
     */
    hr = g_pMouse->SetDataFormat(&c_dfDIMouse);

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
     *      DISCL_NONEXCLUSIVE
     *
     *          Retrieve mouse data when acquired, not interfering
     *          with any other applications which are reading mouse
     *          data.
     *
     *      DISCL_FOREGROUND
     *
     *          If the user switches away from our application,
     *          automatically release the mouse back to the system.
     *
     */
    hr = g_pMouse->SetCooperativeLevel(hwnd,
                                       DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "SetCooperativeLevel");
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
     *  Destroy any lingering IDirectInputDevice object.
     */
    if (g_pMouse) {

        /*
         *  Cleanliness is next to godliness.  Unacquire the device
         *  one last time just in case we got really confused and tried
         *  to exit while the device is still acquired.
         */
        g_pMouse->Unacquire();

        g_pMouse->Release();
        g_pMouse = NULL;
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
 *      Ex_OnPaint
 *
 *      Display the current mouse position and button state.
 *
 ****************************************************************************/

LRESULT
Ex_OnPaint(
    HWND hwnd
)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    if (hdc) {

        ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &ps.rcPaint, g_szText,
                   lstrlen(g_szText), NULL);

        EndPaint(hwnd, &ps);
    }

    return 0;
}

/****************************************************************************
 *
 *      Ex_OneFrame
 *
 *      The game plays here.
 *
 *      Our "game" consists entirely of reading mouse data
 *      and displaying it.
 *
 ****************************************************************************/

void
Ex_OneFrame(HWND hwnd)
{

    if (g_pMouse) {

        DIMOUSESTATE dims;          /* DirectInput mouse state structure */
        HRESULT hr;

    again:;
        hr = g_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &dims);
        if (hr == DIERR_INPUTLOST) {
            /*
             *  DirectInput is telling us that the input stream has
             *  been interrupted.  We aren't tracking any state
             *  between polls, so we don't have any special reset
             *  that needs to be done.  We just re-acquire and
             *  try again.
             */
            hr = g_pMouse->Acquire();
            if (SUCCEEDED(hr)) {
                goto again;
            }
        }

        if (SUCCEEDED(hr)) {
            char szBuf[1024];

            /*
             *  Build the new status string.
             *
             *  Display mouse coordinates (x, y, z) and buttons.
             */
            wsprintf(szBuf, "(%d, %d, %d) %c %c %c %c",
                     dims.lX, dims.lY, dims.lZ,
                     (dims.rgbButtons[0] & 0x80) ? '0' : ' ',
                     (dims.rgbButtons[1] & 0x80) ? '1' : ' ',
                     (dims.rgbButtons[2] & 0x80) ? '2' : ' ',
                     (dims.rgbButtons[3] & 0x80) ? '3' : ' ');

            /*
             *  Trigger a repaint only if the status string changed.
             *  This avoids flicker.
             */
            if (lstrcmp(g_szText, szBuf)) {
                lstrcpy(g_szText, szBuf);
                InvalidateRect(hwnd, NULL, TRUE);
            }
        }
    }

    /*
     *  Sleep for a few milliseconds to simulate a 30fps frame rate.
     */
    Sleep(1000 / 30);

}

/****************************************************************************
 *
 *      Ex_SyncAcquire
 *
 *      Acquire or unacquire the mouse, depending on the the g_fPaused
 *      flag.  This synchronizes the device with our internal view of
 *      the world.
 *
 ****************************************************************************/

void
Ex_SyncAcquire(HWND hwnd)
{
    if (g_fPaused) {
        if (g_pMouse) g_pMouse->Unacquire();
    } else {
        if (g_pMouse) g_pMouse->Acquire();
    }
}

/****************************************************************************
 *
 *      Ex_WndProc
 *
 *      Window procedure for simple sample.
 *
 ****************************************************************************/

LRESULT CALLBACK
Ex_WndProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
)
{

    switch (msg) {

    case WM_PAINT:      return Ex_OnPaint(hwnd);

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
     *      want non-exclusive access to the mouse.
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
    wc.hbrBackground  = 0;
    wc.hInstance      = hinst;
    wc.style          = 0;
    wc.lpfnWndProc    = Ex_WndProc;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0;

    if (!RegisterClass(&wc)) {
        return NULL;
    }

    HWND hwnd = CreateWindow(
                    c_szClassName,                  // Class name
                    "DIEX1 - Alt+F4 to exit",       // Caption
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
         *  Standard game loop.
         */
        for (;;) {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

                /* If it's a quit message, we're outta here */
                if (msg.message == WM_QUIT) {
                    break;
                } else {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            } else if (g_fPaused) {
                WaitMessage();
            } else {
                Ex_OneFrame(hwnd);
            }
        }
    }

    DITerm();

    return msg.wParam;

}
