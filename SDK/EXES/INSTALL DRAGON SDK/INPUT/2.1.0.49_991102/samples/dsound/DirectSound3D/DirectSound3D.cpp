/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    DirectSound3D.cpp

Abstract:

    DirectSound3D Application. Play a sound in the 8 corners defining
    a cube around the listener's head.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "DirectSound3D.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR     g_tszAppName[] = TEXT("DirectSound3D");        // The App's Name
LPDIRECTSOUNDBUFFER g_pdsbTest;
LPDIRECTSOUND3DBUFFER g_pds3dbTest;

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
    // release the test sound
    if (g_pdsbTest)
        g_pdsbTest->Release();

    if (g_pds3dbTest)
        g_pds3dbTest->Release();

    // Release the IDirectSound3DListener interface
    if (g_pds3dl)
        g_pds3dl->Release();

    // Release the IDirectSound interface
    if (g_pds)
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
AppInit(HINSTANCE hPrev, int nCmdShow, LPTSTR lpCmdLine)
{
    WNDCLASS  cls;          
    TCHAR szFile[MAX_PATH];
    DWORD dwAttributes;

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
    {
        RetailOutput(TEXT("Unable to Initialize DirectSound\r\n"));
        return FALSE;
    }

    // Initialize DirectSound3D
    if (!InitDirectSound3D())
    {
        RetailOutput(TEXT("Unable to Initialize DirectSound3D\r\n"));
        return FALSE;
    }

    // Get the desired filename from the command line
    if (*lpCmdLine == NULL)
    {
        // The user must specify a filename
        RetailOutput(TEXT("Error:  Filename not specified.\r\n"));
        RetailOutput(TEXT("File must either be specified with full path, or must reside in\r\n"));
        RetailOutput(TEXT("your <WCEDreamcastSDK>\\release\\(retail,debug)\\Samples directory.\r\n\r\n"));

        RetailOutput(TEXT("Usage:   s DirectSound3D <WAV filename>\r\n\r\n"));

        RetailOutput(TEXT("Example: s DirectSound3D jump.wav\r\n"));
        RetailOutput(TEXT("Example: s DirectSound3D \\PC\\Samples\\jump.wav\r\n"));
        return FALSE;
    }
    
    lstrcpy(szFile, lpCmdLine);

    // Check to see if the file is specified using the full path (ie "\windows\test.mpg")
    dwAttributes = GetFileAttributes(szFile);
    if (dwAttributes == 0xFFFFFFFF || dwAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        // The file was not specifies using the full path; check to see if the filename
        // specified exists in the Flat Release directory
        lstrcpy(szFile, TEXT("\\PC\\Samples\\"));
        lstrcat(szFile, lpCmdLine);
        dwAttributes = GetFileAttributes(szFile);
        if (dwAttributes == 0xFFFFFFFF || dwAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            // The file wasn't there either - this sample doesn't support loading from other
            // default directories, so report usage and exit
            RetailOutput(TEXT("Error:  Specified media file (%s) not found.\r\n"), szFile);
            RetailOutput(TEXT("File must either be specified with full path, or must reside in\r\n"));
            RetailOutput(TEXT("your <WCEDreamcastSDK>\\release\\(retail,debug)\\Samples directory.\r\n\r\n"));

            RetailOutput(TEXT("Usage:   s DirectSound3D <WAV filename>\r\n\r\n"));

            RetailOutput(TEXT("Example: s DirectSound3D jump.wav\r\n"));
            RetailOutput(TEXT("Example: s DirectSound3D \\PC\\Samples\\jump.wav\r\n"));
            return FALSE;
        }
    }    

    // Load the test sound
    if (!Load3DSoundBuffer(szFile, &g_pdsbTest, &g_pds3dbTest))
    {
        RetailOutput(TEXT("Unable to load wave file\r\n"));
        return 1;
    }

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
#include <math.h>
extern "C" int APIENTRY 
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    MSG    msg;
    int    i   = 0;
    float  r   = 0.0f;
    float  rX  = 0.0f, rY = 0.0f, rZ = 0.0f; 
    float  rVX = 0.0f, rVY = 0.0f, rVZ = 0.0f; ;

    // Store Instance handle for use later...
    g_hinst = hInstance;

    // Call initialization procedure
    if (!AppInit(hPrevInstance, nCmdShow, lpCmdLine))
        goto done;

    // Begin playing the sound
    g_errLast = g_pdsbTest->Play(0, 0, DSBPLAY_LOOPING);

    while (TRUE)
    {
        rVX = (float)sin(r) - rX;
        rX  = (float)sin(r);
        rVY = (float)-sin(r) - rY;
        rY  = (float)-sin(r);
        rVZ = (float)cos(r) - rZ;
        rZ  = (float)cos(r);

        g_pds3dbTest->SetPosition( rX * 2.0f,  rY * 2.0f,  rZ * 2.0f, DS3D_IMMEDIATE);
        g_pds3dbTest->SetVelocity(rVX * 2.0f, rVY * 2.0f, rVZ * 2.0f, DS3D_IMMEDIATE);
        r += .001f;

        // Check for keyboard input
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            // There's a message waiting in the queue for us.  Retrieve
            // it and dispatch it, unless it's a WM_QUIT.
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg); 
            DispatchMessage(&msg);
        }
    }

done:

    CleanUp();

    RetailOutput(TEXT("\r\nApp exited...\r\n"));

    return msg.wParam;
}
