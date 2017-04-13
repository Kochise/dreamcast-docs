/**************************************************************************

    DIEX4.CPP - DirectInput simple sample 4

    Demonstrates an application which retrieves buffered keyboard data
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

#include "diex4.h"

/****************************************************************************
 *
 *      Global Parameters
 *
 ****************************************************************************/

#define DINPUT_BUFFERSIZE       16      /* Number of buffer elements */

/****************************************************************************
 *
 *      Global variables
 *
 ****************************************************************************/

char c_szClassName[] = "DIEX4";

HINSTANCE       g_hinst;                /* My instance handle */
BOOL            g_fPaused = TRUE;       /* Should I be paused? */

/****************************************************************************
 *
 *      DirectInput globals
 *
 ****************************************************************************/

LPDIRECTINPUT           g_pdi;
LPDIRECTINPUTDEVICE     g_pKeyboard;
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
 *      Reading buffered data requires another function:
 *
 *          IDirectInputDevice::SetProperty(DIPROP_BUFFERSIZE)
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
     *  Obtain an interface to the system keyboard device.
     *
     *  Parameters:
     *
     *      GUID_SysKeyboard
     *
     *          The instance GUID for the device we wish to access.
     *          GUID_SysKeyboard is a predefined instance GUID that
     *          always refers to the system keyboard device.
     *
     *      &g_pKeyboard
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
    hr = g_pdi->CreateDevice(GUID_SysKeyboard, &g_pKeyboard, NULL);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "CreateDevice");
        return FALSE;
    }

    /*
     *  Set the data format to "keyboard format".
     *
     *  A data format specifies which controls on a device we
     *  are interested in, and how they should be reported.
     *
     *  This tells DirectInput that we are interested in all keys
     *  on the device, and they should be reported as DirectInput
     *  DIK_* codes.
     *
     *  Parameters:
     *
     *      c_dfDIKeyboard
     *
     *          Predefined data format which describes
     *          an array of 256 bytes, one per scancode.
     */
    hr = g_pKeyboard->SetDataFormat(&c_dfDIKeyboard);

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
     *          Retrieve keyboard data when acquired, not interfering
     *          with any other applications which are reading keyboard
     *          data.
     *
     *      DISCL_FOREGROUND
     *
     *          If the user switches away from our application,
     *          automatically release the keyboard back to the system.
     *
     */
    hr = g_pKeyboard->SetCooperativeLevel(hwnd,
                                       DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "SetCooperativeLevel");
        return FALSE;
    }

    /*
     *  IMPORTANT STEP IF YOU WANT TO USE BUFFERED DEVICE DATA!
     *
     *  DirectInput uses unbuffered I/O (buffer size = 0) by default.
     *  If you want to read buffered data, you need to set a nonzero
     *  buffer size.
     *
     *  Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
     *
     *  The buffer size is a DWORD property associated with the device.
     */
    DIPROPDWORD dipdw =
        {
            {
                sizeof(DIPROPDWORD),        // diph.dwSize
                sizeof(DIPROPHEADER),       // diph.dwHeaderSize
                0,                          // diph.dwObj
                DIPH_DEVICE,                // diph.dwHow
            },
            DINPUT_BUFFERSIZE,              // dwData
        };

    hr = g_pKeyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "Set buffer size");
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
    if (g_pKeyboard) {

        /*
         *  Cleanliness is next to godliness.  Unacquire the device
         *  one last time just in case we got really confused and tried
         *  to exit while the device is still acquired.
         */
        g_pKeyboard->Unacquire();

        g_pKeyboard->Release();
        g_pKeyboard = NULL;
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
 *      Display the current keyboard state.
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
 *      Our "game" consists entirely of reading keyboard data
 *      and displaying it.
 *
 ****************************************************************************/

void
Ex_OneFrame(HWND hwnd)
{

    if (g_pKeyboard) {

        DIDEVICEOBJECTDATA rgod[DINPUT_BUFFERSIZE]; /* Receives buffered data */
        DWORD cod;
        HRESULT hr;

    again:;
        cod = DINPUT_BUFFERSIZE;
        hr = g_pKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),
                                        rgod, &cod, 0);
        if (hr != DI_OK) {
            /*
             *  We got an error or we got DI_BUFFEROVERFLOW.
             *
             *  Either way, it means that continuous contact with the
             *  device has been lost, either due to an external
             *  interruption, or because the buffer overflowed
             *  and some events were lost.
             *
             *  Consequently, if a button was pressed at the time
             *  the buffer overflowed or the connection was broken,
             *  the corresponding "up" message might have been lost.
             *
             *  But since our simple sample doesn't actually have
             *  any state associated with button up or down events,
             *  there is no state to reset.  (In a real game, ignoring
             *  the buffer overflow would result in the game thinking
             *  a key was held down when in fact it isn't; it's just
             *  that the "up" event got lost because the buffer
             *  overflowed.)
             *
             *  If we want to be cleverer, we could do a
             *  GetDeviceState() and compare the current state
             *  against the state we think the device is in,
             *  and process all the states that are currently
             *  different from our private state.
             *
             */

            /* << insert recovery code here if you need any >> */

            if (hr == DIERR_INPUTLOST) {
                hr = g_pKeyboard->Acquire();
                if (SUCCEEDED(hr)) {
                    goto again;
                }
            }
        }

        /*
         *  In order for it to be worth our while to parse the
         *  buffer elements, the GetDeviceData must have succeeded,
         *  and we must have received some data at all.
         */
        if (SUCCEEDED(hr) && cod > 0) {
            char szBuf[1024];
            DWORD iod;

            /*
             *  Study each of the buffer elements and process them.
             *
             *  Since we really don't do anything, our "processing"
             *  consists merely of squirting the name into our
             *  local buffer.
             */
            for (iod = 0; iod < cod; iod++) {
                wsprintf(szBuf, "%02x was %s",
                         rgod[iod].dwOfs,
                         (rgod[iod].dwData & 0x80) ? "pressed" : "released");
            }

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
 *      Acquire or unacquire the keyboard, depending on the the g_fPaused
 *      flag.  This synchronizes the device with our internal view of
 *      the world.
 *
 ****************************************************************************/

void
Ex_SyncAcquire(HWND hwnd)
{
    if (g_fPaused) {
        if (g_pKeyboard) g_pKeyboard->Unacquire();
    } else {
        if (g_pKeyboard) g_pKeyboard->Acquire();
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
     *      want non-exclusive access to the keyboard.
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
                    "DIEX4 - Alt+F4 to exit",       // Caption
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
