/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File: winmain.cpp
 *
 ***************************************************************************/

// Defines....
#define CLASS_NAME                              "RockEm3D_Class"

// Includes....
#include "windows.h"
#include "resource.h"
#include "winmain.h"

#include "directx.h"
#include "rm.h"

#include "control.h"

#include "midi.h"

// Globals....
HINSTANCE       g_hInst = NULL;
HWND            g_hWnd  = NULL;

BOOL            g_bActive       = FALSE;
BOOL            g_bFirstActive  = TRUE;
BOOL            g_bErrorOccured = FALSE;
char            g_sError[2048];
BOOL            g_bShowStats    = FALSE;
BOOL            g_bMusicPaused  = FALSE;
BOOL            g_bSoundPaused  = FALSE;

// Externals....
extern DWORD    g_dwCurrMode; // Defined in DIRECTX.CPP

//------------------------------------------------------------------
// 
// Function     : RegError()
//
// Purpose      : Registers an error
//
//------------------------------------------------------------------

void RegError(char *sErr)
{
    sprintf(g_sError, "%s\r\n", sErr);
    OutputDebugString(g_sError);
    g_bErrorOccured = TRUE;
}


//------------------------------------------------------------------
// 
// Function     : InitClass()
//
// Purpose      : Initialises and registers window class
//
//------------------------------------------------------------------

BOOL InitClass(HINSTANCE hInst)
{
    WNDCLASS    wndClass;

    // Fill out WNDCLASS info
    wndClass.style              = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc        = WndProc;
    wndClass.cbClsExtra         = 0;
    wndClass.cbWndExtra         = 0;
    wndClass.hInstance          = hInst;
    wndClass.hIcon              = LoadIcon(hInst, "ROCKEM3D");
    wndClass.hCursor            = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground      = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wndClass.lpszMenuName       = NULL;
    wndClass.lpszClassName      = CLASS_NAME;
    
    if (!RegisterClass(&wndClass)) return FALSE;

    // Everything's perfect
    return TRUE;
}

//------------------------------------------------------------------
// 
// Function     : InitWindow()
//
// Purpose      : Initialises and creates the main window
//
//------------------------------------------------------------------

BOOL InitWindow(HINSTANCE hInst, int nCmdShow)
{
    // Create a window
    g_hWnd = CreateWindowEx(WS_EX_APPWINDOW,
                            CLASS_NAME, 
                            "RockEm3D Demo",
                            WS_POPUP | WS_SYSMENU,
                            0, 0,
                            GetSystemMetrics(SM_CXSCREEN),
                            GetSystemMetrics(SM_CYSCREEN),
                            NULL,
                            NULL,
                            hInst,
                            NULL);

    // Return false if window creation failed
    if (!g_hWnd) return FALSE;
    
    // Show the window
    ShowWindow(g_hWnd, SW_SHOWNORMAL);

    // Update the window
    UpdateWindow(g_hWnd);
    
    // Everything's perfect
    return TRUE;
}

//------------------------------------------------------------------
// 
// Function     : WndProc()
//
// Purpose      : Windows procedure to handle messages
//
//------------------------------------------------------------------

long FAR PASCAL WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// D3DVECTOR used for 3D position of sound
	static D3DVECTOR d3dvPos= {D3DVAL(0), D3DVAL(0), D3DVAL(0)};
	
    // Handle messages
    switch (message)
    {
        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                {                                                       
                    // Time to quit....
                    PostMessage(g_hWnd, WM_CLOSE ,0 ,0);
                }
                break;

                case VK_F5:
                {
                    // Toggle stats
                    g_bShowStats = !g_bShowStats;
                }
                break;

                case 'M':
                {
                    // Toggle music
                    if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
                    {
                        if (!g_bMusicPaused)
                        {
                            PauseMidi();
                        }
                        else
                        {
                            ResumeMidi();
                        }
                        g_bMusicPaused = !g_bMusicPaused;
                    }
                }
                break;
                
                case 'S':
                {
                    // Toggle sound
                    if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
                    {
                        g_bSoundPaused = !g_bSoundPaused;

                        if (g_bSoundPaused)
                        {
                            // Kill all the sound effects
                            StopAllSounds();
                        }
                        else
                        {
                            // Start the crowd noise looping
                         PlaySoundDS(CROWD_LOOP,d3dvPos, DSBPLAY_LOOPING);
                        }
                    }
                }
                break;

                case VK_F6 :
                {
                    // Go up a video mode
                    if(!EnterNextVideoMode()) 
						PostMessage(g_hWnd, WM_CLOSE ,0 ,0);
                }
                break;

                case VK_F7 :
                {
                    // Go down a video mode
                    if(!EnterPrevVideoMode())
						PostMessage(g_hWnd, WM_CLOSE ,0 ,0);
                }
                break;

                case VK_END :
                {
                    // Go to highest video mode
                    if(!EnterLowestVideoMode())
						PostMessage(g_hWnd, WM_CLOSE ,0 ,0);
                }
                break;

                case VK_HOME :
                {
                    // Go to lowest video mode
                    if(!EnterHighestVideoMode()) 
						PostMessage(g_hWnd, WM_CLOSE ,0 ,0);
                }
                break;
            }
        }
        break;

        case WM_SYSCOMMAND:
        {
            switch (wParam)
            {
                // Trap ALT so it doesn't pause the app
                case SC_KEYMENU :
                {
                    return 0;
                }
                break;
            }
        }       
        
        case WM_ACTIVATEAPP:
        {
            // Determine whether app is being activated or not
            g_bActive = (BOOL)wParam ? TRUE : FALSE;

            if (g_bActive)
            {
                while (ShowCursor(FALSE) > 0) { };
                if (!g_bMusicPaused) ResumeMidi();
            }
            else
            {
                ShowCursor(TRUE);
                PauseMidi();
            }
        }
        break;
        
        case WM_CLOSE:
        {                       
            DestroyWindow(g_hWnd);
        }
        break;

        case WM_DESTROY:
        {                       
            // Stop midi music
            StopMidi();

            // Destroy scene
            TermScene();
            
            // Terminate all the DirectX objects, surfaces devices etc
            TermDirectX();

            // Show the mouse
            ShowCursor(TRUE);

            // Time to leave this mortal coil
            PostQuitMessage(0);
        }
        break;
        
        case MCI_NOTIFY:
        {
            if (wParam == MCI_NOTIFY_SUCCESSFUL)
            {
                ReplayMidi();
            }
        }
        break;
    }
    
    return DefWindowProc(hWnd, message, wParam, lParam);
}

//------------------------------------------------------------------
// 
// Function     : WinMain()
//
// Purpose      : Entry point to application
//
//------------------------------------------------------------------

int FAR PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    // Set global handle
    g_hInst = hInst;    

    // Initialise window class
    if (!InitClass(hInst)) return 1;

    // Initialise window
    if (!InitWindow(hInst, nCmdShow)) return 1;

    // Initialise DirectX objects (Termination is handled in WM_DESTROY)
    if (!InitDirectX())
    {
            DestroyWindow(g_hWnd);
            return 1;
    }

    // Show the splash screen
    DoSplashScreen(2000);

    // Load the scene
    if (!InitScene()) 
    {
            DestroyWindow(g_hWnd);
            return 1;
    }

    // Release the splash screen
    ReleaseSplashScreen();

    // Set DirectDraw exclusive mode here so that the splash could stay
    // up during initialisation if we are using a different DirectDraw device
    // that could not support 640x480x8 for hardware rendering.
    if (!SetDirectDrawExclusiveMode())
    {
            RegError("Could not set exclusive mode!");
            return FALSE;
    }

    // Hide the mouse
    ShowCursor(FALSE);

    // Enter video mode set in g_dwCurMode
    if (!EnterVideoMode(g_dwCurrMode))
    {
            DestroyWindow(g_hWnd);
            return 1;
    }

    // Load accelerators
    HACCEL hAccel = LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_ACCEL));

    // Start the music!
    PlayMidi("RockEm3D.mid");

    // Pump messages via a PeekMessage loop
    while (TRUE)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {                                                           
                PostQuitMessage(msg.wParam);
                return 1;
            }

            if (hAccel && (msg.hwnd == g_hWnd))
            {
                TranslateAccelerator(g_hWnd, hAccel, &msg);
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Perform any neccessary updating during idle time
        if (g_bActive)
        {
            // Update everything
            CheckInputAndUpdate();
            
            // Render the current scene
            if (!RenderScene())
            {
                DestroyWindow(g_hWnd);
                return 1;
            }
        }
    }

    // Exit WinMain and terminate the app....
    return msg.wParam;
}
