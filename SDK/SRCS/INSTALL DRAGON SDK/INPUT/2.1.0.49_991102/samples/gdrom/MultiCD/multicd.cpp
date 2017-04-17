/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    MultiCD.cpp

Abstract:

    MultiCD Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include <tchar.h>
#include <windows.h>
#include <ceddcdrm.h>
#include <segagdrm.h>
#include <dbt.h>

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR     g_tszAppName[] = TEXT("MultiCD");         // The App's Name
HANDLE    g_hGDROM = NULL;                          // Handle of the GDROM device

// ++++ Local Functions +++++++++++++++++++++++++++++++++++++++++++++
static BOOL AppInit(HINSTANCE hPrev,int nCmdShow);

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    RetailOutput

Description:

    Simple Retail Output mechanism.  If the function outputs
    the passed-in String and variables to the debug output stream.

Arguments:

    TCHAR *tszDest       - TEXT String to output

    ... (variable arg)   - List of variable arguments to embed in output
                           (similar to printf format)

Return Value:

    None

-------------------------------------------------------------------*/
void RetailOutput(TCHAR *tszErr, ...)
{
    TCHAR tszErrOut[256];

    va_list valist;

    va_start (valist,tszErr);
    wvsprintf (tszErrOut, tszErr, valist);
    OutputDebugString (tszErrOut);

    va_end (valist);
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
    case WM_DEVICECHANGE:
        // When setup properly (see AppInit), this message is automatically sent
        // by WinCE when the GD-ROM Door is opened or closed.

        // Print a message to the standard output stream notifying that the door
        // status has changed
        switch (wParam)
        {
        case DBT_DEVICEREMOVECOMPLETE:
            RetailOutput(TEXT("GD-ROM drive door has been opened.\r\n"));
            break;

        case DBT_DEVICEARRIVAL:
            RetailOutput(TEXT("GD-ROM drive door has been closed - a valid GD has been inserted.\r\n"));
            break;

        case DBT_DEVICETYPESPECIFIC:
            RetailOutput(TEXT("GD-ROM drive door has been closed - an invalid GD has been inserted.\r\n"));
            break;

        default:
            RetailOutput(TEXT("ERROR: Invalid WM_DEVICECHANGE parameter encountered\r\n"));
            break;
        }
        break;

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
AppInit(HINSTANCE hPrev, int nCmdShow)
{
    SEGACD_DOOR_BEHAVIOR doorbehavior;
    DWORD    dwReturned;
    WNDCLASS cls;

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

    // Set the GD-ROM device to NOTIFY the application when the GD-ROM drive is opened.
    // rather then rebooting (the default behaviour)

    // Create a handle to the GDROM drive.
    g_hGDROM = CreateFile(TEXT("\\Device\\CDROM0"), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL );
    if (g_hGDROM == INVALID_HANDLE_VALUE)
    {
        RetailOutput(TEXT("Error opening GD-ROM\r\n"));
        return FALSE;
    }

    doorbehavior.dwBehavior = SEGACD_DOOR_NOTIFY_APP;
    if(!DeviceIoControl(g_hGDROM, IOCTL_SEGACD_SET_DOOR_BEHAVIOR, &doorbehavior, sizeof(doorbehavior), NULL, 0, &dwReturned, NULL))
    {
		int nError = GetLastError();
		if (nError == ERROR_NO_MEDIA_IN_DRIVE)
			RetailOutput(TEXT("There is no media in the GD-ROM drive.  Please place a CD or GD-ROM in there, and rerun this sample.\r\n"));
		else
			RetailOutput(TEXT("Error setting GD-ROM door behavior (0x%08x).\r\n"),nError);
        return FALSE;
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
extern "C" int APIENTRY 
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    // Store Instance handle for use later...
    g_hinst = hInstance;

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
    }

    // Release the GD-ROM device
    if (g_hGDROM)
        CloseHandle(g_hGDROM);

    RetailOutput(TEXT("\r\nApp exited...\r\n"));

    return msg.wParam;
}
