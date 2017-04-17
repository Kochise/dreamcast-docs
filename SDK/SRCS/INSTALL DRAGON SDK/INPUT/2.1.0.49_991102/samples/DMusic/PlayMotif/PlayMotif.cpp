/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    PlayMotif.cpp

Abstract:

    PlayMotif Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "PlayMotif.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR     g_tszAppName[] = TEXT("PlayMotif");        // The App's Name
LPDIRECTDRAWSURFACE g_pddsSample;                   // The sample bitmap to display

// ++++ Local Functions +++++++++++++++++++++++++++++++++++++++++++++
static BOOL RenderSceneToBackBuffer();
static BOOL AppInit(HINSTANCE hPrev,int nCmdShow);

// ++++ Macros ++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define IS_SPACE(c)   ((c) == TEXT(' ') || (c) == TEXT('\r') || (c) == TEXT('\n') || (c) == TEXT('\t'))


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

    // And release DirectMusic
    FreeDirectMusic();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CheckButtons

Description:

    Checks if any of the buttons on any controller have been pressed -
    if so, it starts playing the associated Motif.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void
CheckButtons()
{
    int iPort;

    for (iPort = 0; iPort < g_nPorts; iPort++)
    {
        CController *pcont = g_rgpcont[iPort];

        if (pcont)
        {
            // Check if any buttons on this port are pressed.  If so, play the associated Motif.

            if (pcont->m_buttonIndices[g_iAButton] != g_iInvalid && 
                pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iAButton]])
            {
                // The button's state has changed.  If it's now down, then play the motif
                if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iAButton]] & 0x80)
            	    PlayMotif(g_rgtszMotifName[0]);
            }
            if (pcont->m_buttonIndices[g_iBButton] != g_iInvalid && 
                pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iBButton]])
            {
                // The button's state has changed.  If it's now down, then play the motif
                if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iBButton]] & 0x80)
            	    PlayMotif(g_rgtszMotifName[1]);
            }
            if (pcont->m_buttonIndices[g_iXButton] != g_iInvalid && 
                pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iXButton]])
            {
                // The button's state has changed.  If it's now down, then play the motif
                if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iXButton]] & 0x80)
            	    PlayMotif(g_rgtszMotifName[2]);
            }
            if (pcont->m_buttonIndices[g_iYButton] != g_iInvalid && 
                pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iYButton]])
            {
                // The button's state has changed.  If it's now down, then play the motif
                if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iYButton]] & 0x80)
            	    PlayMotif(g_rgtszMotifName[3]);
            }
            if (pcont->m_buttonIndices[g_iZButton] != g_iInvalid &&             
                pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iZButton]])
            {
                // The button's state has changed.  If it's now down, then play the motif
                if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iZButton]] & 0x80)
            	    PlayMotif(g_rgtszMotifName[4]);
            }
            if (pcont->m_buttonIndices[g_iUAButton] != g_iInvalid && 
                pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iUAButton]])
            {
                // The button's state has changed.  If it's now down, then play the motif
                if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iUAButton]] & 0x80)
            	    PlayMotif(g_rgtszMotifName[5]);
            }
            if (pcont->m_buttonIndices[g_iDAButton] != g_iInvalid && 
                pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iDAButton]])
            {
                // The button's state has changed.  If it's now down, then play the motif
                if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iDAButton]] & 0x80)
            	    PlayMotif(g_rgtszMotifName[6]);
            }
            if (pcont->m_buttonIndices[g_iLAButton] != g_iInvalid && 
                pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iLAButton]])
            {
                // The button's state has changed.  If it's now down, then play the motif
                if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iLAButton]] & 0x80)
            	    PlayMotif(g_rgtszMotifName[7]);
            }
            if (pcont->m_buttonIndices[g_iRAButton] != g_iInvalid && 
                pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iRAButton]])
            {
                // The button's state has changed.  If it's now down, then play the motif
                if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iRAButton]] & 0x80)
            	    PlayMotif(g_rgtszMotifName[8]);
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
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR pszCmdLine, int nCmdShow)
{
    MSG msg;
    LPTSTR pszPath = TEXT("\\Windows");
    LPTSTR pszSegment;

    // Store Instance handle for use later...
    g_hinst = hInstance;

    while(*pszCmdLine == TEXT('-'))
	{
        ++pszCmdLine;

        switch(*pszCmdLine)
		{
        case TEXT('P'):
        case TEXT('p'):                 // set the default path
            {
                TCHAR c = *pszCmdLine;

                // Skip over any non-whitespace we ignored from the last token
                while(!IS_SPACE(*pszCmdLine) && (*pszCmdLine != TEXT('\0')))
				{
                    ++pszCmdLine;
				}

                while(IS_SPACE(*pszCmdLine) && (*pszCmdLine != TEXT('\0')))
                {
                    ++pszCmdLine;
                }
                pszPath = pszCmdLine;
                break;
			}
			break;
        case TEXT('?'):
        case TEXT('h'):
        case TEXT('H'):
            {
                RetailOutput(TEXT("Usage: playmotif [-p searchpath] [segment]\r\n")
                             TEXT("       default search path: \\Windows\r\n")
                             TEXT("       default segment: Sample.sgt\r\n\r\n")
                             TEXT("Important: See the readme.txt for this sample for more information.\r\n"));
                return 0;
            }
			break;
        }

        // Skip to next token
		// Skip over any non-whitespace we ignored from the last token
        while(!IS_SPACE(*pszCmdLine) && (*pszCmdLine != TEXT('\0')))
		{
            ++pszCmdLine;
		}
        if(*pszCmdLine == TEXT('\0'))
        {
            break;
        }
        *pszCmdLine++ = TEXT('\0');

        // Skip over white space between tokens
        while(IS_SPACE(*pszCmdLine))
		{
            ++pszCmdLine;
		}
    }

    pszSegment = pszCmdLine;
    if(*pszSegment == TEXT('\0'))
    {
        pszSegment = TEXT("sample.sgt");
    }

    // Call initialization procedure
    if (!AppInit(hPrevInstance,nCmdShow))
        return 0L;

    // Initialize DirectMusic
    if (!InitDirectMusic(pszPath, pszSegment))
    {
        FreeDirectMusic ();
        return 0L;
    }

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

            // Check to see if any buttons are pushed - if so, queue up the appropriate Motif
            CheckButtons();

            // Render the frame here
            // ...

            // After a reasonable amount of time the data should be ready.  If it's not ready yet, GetData will block until it is.
            GetDeviceData();

            // Check for new devices plugged in.
            CheckNewDevices();
        }
    }

    RetailOutput(TEXT("\r\nApp exited...\r\n"));
    return msg.wParam;
}
