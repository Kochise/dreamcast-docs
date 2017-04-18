/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    PlayMultipleSounds.cpp

Abstract:

    PlayMultipleSounds Application

    This sample streams a variety of sounds; up to 16 mono sounds simultaneously
    (the maximum supported by the Dreamcast).  To do this, it creates a separate
    thread which simply plays all of the currently active sounds.  When the user
    presses (X), it adds a random sound to the list of currently playing sounds.
    
-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "PlayMultipleSounds.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR     g_tszAppName[] = TEXT("PlayMultipleSounds");  // The App's Name
HANDLE    g_hPlayingSoundThread;                    // Playing Sounds thread
IDirectSoundBuffer *g_pdsb[4];                      // The sounds to play

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
    g_pdsb[0]->Release();
    g_pdsb[1]->Release();
    g_pdsb[2]->Release();
    g_pdsb[3]->Release();
    
    g_pds->Release();
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
    WNDCLASS cls;          
    DWORD    dwThreadId;

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

    // Initialize DirectSound
    if (!InitDirectSound())
        return FALSE;

    // Initialize DirectInput
    if (!InitDirectInput())
        return FALSE;

    // Load the 4 test sounds into different sound buffers
    g_pdsb[0] = LoadSoundBuffer(TEXT("LEVEL"));
    g_pdsb[1] = LoadSoundBuffer(TEXT("BOUNCE"));
    g_pdsb[2] = LoadSoundBuffer(TEXT("GUNFIRE"));
    g_pdsb[3] = LoadSoundBuffer(TEXT("SHIELD"));
    
    // Create a separate thread which just loops playing any currently playing sounds.
    g_hPlayingSoundThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PlayingSoundThread, NULL, 0, &dwThreadId);

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    HandleInput

Description:

    Checks if any of the buttons are pressed on each controller; if so,
    it starts playing a new sound.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void
HandleInput()
{
    int iPort;

    // Check if a button has been pressed on any controller in any port.
    for (iPort = 0; iPort < g_nPorts; iPort++)
    {
        CController *pcont = g_rgpcont[iPort];

        if (pcont)
        {
            // Verify that there is an 'A' button on the controller
            if (pcont->m_buttonIndices[g_iAButton] != 0xFF)
            {
                if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iAButton]])
                {
                    // The 'A' button's state has changed.  Check if it is now pressed
                    if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iAButton]] & 0x80)
                        AddSound(g_pdsb[0]);
                }
            }

            // Verify that there is an 'B' button on the controller
            if (pcont->m_buttonIndices[g_iBButton] != 0xFF)
            {
                if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iBButton]])
                {
                    // The 'B' button's state has changed.  Check if it is now pressed
                    if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iBButton]] & 0x80)
                        AddSound(g_pdsb[1]);
                }
            }

            // Verify that there is an 'X' button on the controller
            if (pcont->m_buttonIndices[g_iXButton] != 0xFF)
            {
                if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iXButton]])
                {
                    // The 'X' button's state has changed.  Check if it is now pressed
                    if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iXButton]] & 0x80)
                        AddSound(g_pdsb[2]);
                }
            }

            // Verify that there is an 'Y' button on the controller
            if (pcont->m_buttonIndices[g_iYButton] != 0xFF)
            {
                if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iYButton]])
                {
                    // The 'Y' button's state has changed.  Check if it is now pressed
                    if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iYButton]] & 0x80)
                        AddSound(g_pdsb[3]);
                }
            }
        }
    }
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

    RetailOutput(TEXT("\r\nPlease plug in your gamepad, and use the A, B, X, Y \r\n"));
    RetailOutput(TEXT("buttons to play different sounds.\r\n"));

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

            // check if any buttons are pressed; if so, start the associated sound.
            HandleInput();

            // After a reasonable amount of time the data should be ready.  If it's not ready yet, GetData will block until it is.
            GetDeviceData();

            // Check for new devices plugged in.
            CheckNewDevices();
        }
    }

    // When done, delete the PlayingSoundsThread (TODO: Need to wait for sounds to finish?)
    CloseHandle(g_hPlayingSoundThread);

    RetailOutput(TEXT("\r\nApp exited...\r\n"));

    return msg.wParam;
}
