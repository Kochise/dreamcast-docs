/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    VibrationPack.cpp

Abstract:

    VibrationPack Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "VibrationPack.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR     g_tszAppName[] = TEXT("VibrationPack");        // The App's Name

// ++++ Local Functions +++++++++++++++++++++++++++++++++++++++++++++
static BOOL AppInit(HINSTANCE hPrev,int nCmdShow);

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CleanUp

Description:

    Cleans up after the application is done.  Frees allocated memory

Arguments:

    None
  
Return Value:

    None

-------------------------------------------------------------------*/
void
CleanUp()
{
    int iPort;

    // Release the device objects that we created
    for (iPort = 0; iPort < g_nPorts; iPort++)
        if (g_rgpcont[iPort])
            delete g_rgpcont[iPort];

    // Release the DI object
    if (g_pdi)
        g_pdi->Release();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CheckVibrate

Description:

    Checks to see if any buttons are pressed; if so, it starts the
    appropriate vibration pack vibrating.

Arguments:

    None
  
Return Value:

    None

-------------------------------------------------------------------*/
void
CheckVibrate()
{
    int iPort;

    for (iPort = 0; iPort < g_nPorts; iPort++)
    {
        CController *pcont = g_rgpcont[iPort];
        if (pcont)
        {
            CVibPack *pvibpack = pcont->GetVibPack();
            if (pvibpack)
            {
                // TODO: For now, just use the 1st source; need to handle multiple sources though (ie Fishing Controller)
                PVIB_INFO pvibinfo = &pvibpack->m_pVibInfoArray[0];
                BOOL      fVibPackPluggedIn = TRUE;

                // Check to see if the 'A' button has been newly pushed
                if (pcont->m_buttonIndices[g_iAButton] != g_iInvalid)
                    if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iAButton]])
                    {
                        // The state of the 'A' button has changed.  Is it now pressed?  If so, do the vibration
                        if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iAButton]] & 0x80)
                        {
                            fVibPackPluggedIn = pvibpack->Vibrate(1, TRUE, VIB_TYPE_CONSTANT, VIB_POWER_MAX,
                                                                  VIB_DIRECTION_FORWARD, pvibinfo->minFrequency, 0);
                        }
                    }

                // Check to see if the 'B' button has been newly pushed
                if (pcont->m_buttonIndices[g_iBButton] != g_iInvalid)
                    if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iBButton]])
                    {
                        // The state of the 'B' button has changed.  Is it now pressed?  If so, do the vibration
                        if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iBButton]] & 0x80)
                        {
                            fVibPackPluggedIn = pvibpack->Vibrate(1, TRUE, VIB_TYPE_CONSTANT, VIB_POWER_MAX,
                                                                  VIB_DIRECTION_FORWARD, pvibinfo->maxFrequency, 0);
                        }
                    }

                // Check to see if the 'X' button has been newly pushed
                if (pcont->m_buttonIndices[g_iXButton] != g_iInvalid)
                    if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iXButton]])
                    {
                        // The state of the 'X' button has changed.  Is it now pressed?  If so, do the vibration
                        if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iXButton]] & 0x80)
                        {
                            BYTE dwDirection;

                            if (pvibinfo->bCaps & VIBCAPS_DIRECTIONAL)
                                dwDirection = VIB_DIRECTION_REVERSE;
                            else
                                dwDirection = VIB_DIRECTION_FORWARD;

                            fVibPackPluggedIn = pvibpack->Vibrate(1, FALSE, VIB_TYPE_CONSTANT, VIB_POWER_MAX,
                                                                  dwDirection, pvibinfo->maxFrequency, 4);
                        }
                    }

                // Check to see if the 'Y' button has been newly pushed
                if (pcont->m_buttonIndices[g_iYButton] != g_iInvalid)
                    if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iYButton]])
                    {
                        // The state of the 'Y' button has changed.  Is it now pressed?  If so, do the vibration
                        if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iYButton]] & 0x80)
                        {
                            BYTE dwVibType;

                            if (pvibinfo->bCaps & VIBCAPS_VARIABLEINTENSITY)
                                dwVibType = VIB_TYPE_DIVERGENT;
                            else
                                dwVibType = VIB_TYPE_CONSTANT;

                            fVibPackPluggedIn = pvibpack->Vibrate(1, TRUE, dwVibType, VIB_POWER_MIN,
                                                                  VIB_DIRECTION_FORWARD, pvibinfo->maxFrequency, 4);
                        }
                    }

                if (!fVibPackPluggedIn)
                {
                    DebugOutput(TEXT("Vibration Pack removed.\r\n"));

                    // The vibration pack was removed 
                    pcont->SetVibPack(NULL);
                }
            }
        }
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WndProc

Description:

    Window message processing routine for the main application window.
    The main purpose of this function is to exit the app when the user
    presses <Escape> or <F12>.

Arguments:

    HWND hWnd           - Window handle

    UINT uMessage       - Message identifier
  
    WPARAM wParam       - First message parameter
    
    LPARAM lParam       - Second message parameter
  
Return Value:

    Zero if the message was processed.  The return value from 
    DefWindowProc otherwise.

-------------------------------------------------------------------*/
LRESULT CALLBACK
WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    switch (uMessage)
    {
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
        case VK_F12:
            DestroyWindow(hWnd);
            return 0;

        } // switch (wParam)
        break;

    case WM_DESTROY:
        // Cleanup DirectX structures
        CleanUp();

        PostQuitMessage(0);
        return 0L;

    } // switch (message)

    return DefWindowProc (hWnd, uMessage, wParam, lParam);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    AppInit

Description:

    This function registers a window class, and creates a window for
    the application.

Arguments:

    hPrev               - Hinstance of another process running the program

    nCmdShow            - Whether the app should be shown (ignored)

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
AppInit(HINSTANCE hPrev, int nCmdShow)
{
    WNDCLASS  cls;          

    if (!hPrev)
    {
        //  Register a class for the main application window
        cls.hCursor        = NULL;
        cls.hIcon          = NULL;
        cls.lpszMenuName   = NULL;
        cls.hbrBackground  = NULL;
        cls.hInstance      = g_hinst;
        cls.lpszClassName  = g_tszAppName;
        cls.lpfnWndProc    = (WNDPROC)WndProc;
        cls.style          = 0;
        cls.cbWndExtra     = 0;
        cls.cbClsExtra     = 0;

        if (!RegisterClass(&cls))
            return FALSE;
    }

    g_hwndApp = CreateWindowEx (0, g_tszAppName, g_tszAppName, WS_VISIBLE, 0, 0, 640, 480, NULL, NULL, g_hinst, NULL);

    // Initialize DirectInput
    if (!InitDirectInput())
        return FALSE;

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WinMain

Description:

    This is the entrypoint for this sample app.  It creates an app
    window and then enters a message loop.

Arguments:

    hInstance           - HInstance of the process

    hPrev               - HInstance of another process running the program

    LPTSTR lpCmdLine    - Pointer to command line string

    nCmdShow            - Whether the app should be shown (ignored)

Return Value:

    We normally return the wParam value from the WM_QUIT message.  If
    there's a failure upon initialization, we just return 0.

-------------------------------------------------------------------*/
extern "C" int APIENTRY 
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    // Store Instance handle for use later...
    g_hinst = hInstance;

    RetailOutput(TEXT("\r\nPlease plug in a vibration device, and use the A, B, X, Y \r\n"));
    RetailOutput(TEXT("buttons to cause different types of vibrations.\r\n"));

    // Call initialization procedure
    if (!AppInit(hPrevInstance,nCmdShow))
        return 0L;

    // Main Message loop
    while (TRUE)
    {
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            // There's a message waiting in the queue for us.  Retrieve
            // it and dispatch it, unless it's a WM_QUIT.
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg); 
            DispatchMessage(&msg);
        }
        else
        {
            // If no messages pending, then update the frame.

            // Poll for data
            PollDevices();

            // Now, while the poll is happening in the background, do game-related calculation (physics, AI, etc).

            // ...

            // Render the frame
            // ...

            // Check if any buttons are newly pressed; if so, start the appropriate vibration pack vibrating
            CheckVibrate();

            // After a reasonable amount of time the data should be ready.  If it's not ready yet, GetData will block until it is.
            GetDeviceData();

            // Check for new devices plugged in.
            CheckNewDevices();
        }
    }

    RetailOutput(TEXT("\r\nApp exited...\r\n"));

    return msg.wParam;
}
