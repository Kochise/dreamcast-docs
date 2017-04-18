/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    VMU_Flash.cpp

Abstract:

    VMU_Flash Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "SaveGame.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application
HANDLE	  g_hDeviceEvent[MAX_DEVICE_EVENT];			// NEW_DEVICE and DEVICE_ROMOVED
HANDLE	  g_hGDROM;									// HANDLE to the GDRom
CFlash	  *g_pFlash;								// Pointer to the VMU that is currently 
													// selected as the saving device
BOOL      g_bDoorOpened = FALSE;					// GDRom door opening flag
TCHAR	  g_tszAppName[16] = _T("SaveGame");		
BOOL	  g_bChoose = FALSE;						// Flag to display the menu ( choose a slot )

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ChangeRebootType

Description:

    Set WinCE to either reboot Automatically when the door is opened or to 
    notify the app when the door is opened.
    
Arguments:

    BOOL    bReboot if TRUE, reboot automatically when the device is opened,
            if FALSE, just notify.

Return Value:

    None

-------------------------------------------------------------------*/

void
ChangeRebootType(
    BOOL bReboot)
{
    SEGACD_DOOR_BEHAVIOR doorbehavior;
    DWORD dwReturned;

    if (g_hGDROM == NULL)
    {
        RetailOutput(TEXT("Error, tried to set the reboot type before connecting to the GD-ROM\r\n"));
        return;
    }

    if (bReboot)
    {
        doorbehavior.dwBehavior = SEGACD_DOOR_REBOOT;
    }
    else
    {
        doorbehavior.dwBehavior = SEGACD_DOOR_NOTIFY_APP;
    }
    
    if(!DeviceIoControl(g_hGDROM, IOCTL_SEGACD_SET_DOOR_BEHAVIOR, &doorbehavior, sizeof(doorbehavior), NULL, 0, &dwReturned, NULL))
    {
		int nError = GetLastError();
		if (nError == ERROR_NO_MEDIA_IN_DRIVE)
			RetailOutput(TEXT("There is no media in the GD-ROM drive.  Please place a CD or GD-ROM in there, and rerun this sample.\r\n"));
		else
			RetailOutput(TEXT("Error setting GD-ROM door behavior (0x%08x).\r\n"),nError);
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
	case WM_INITVMU:
		// Try to initialize a VMU
		if ( InitVMU() )
		{
			PostMessage( hWnd, WM_CHOSSESAVESLOT, 0, 0 );
		}
		break;

	// Display the slot selection menu
	case WM_CHOSSESAVESLOT:
		ChooseSaveSlot();
		break;

	// If we receive a number from 0..9 we may want to save the game into that slot
	case WM_CHAR:
		if ( wParam >= '0' && wParam <= '9')
			Save( wParam - '0' );
		break;

    case WM_FINISHED_WRITING:
        // We sent this message to ourselves when we finished writing.
        // If the door had been opened during the write, the WM_DEVICECHANGE
        // message was in the message queue BEFORE this one.  So we can check
        // the g_bDoorOpened Flag and reboot if it is true.
        if (g_bDoorOpened)
        {
            RetailOutput(TEXT("Rebooting after notification\r\n"));
            ResetToFirmware();                
        }            
        break;        
    
    case WM_DEVICECHANGE:
        // When set for notification this message is automatically sent
        // by WinCE when the GD-ROM Door is opened or closed.

        // We only turn on notification while we're saving to a VMU.  The rest
        // of the time, we're set to reboot automatically.  
        switch (wParam)
        {
        case DBT_DEVICEREMOVECOMPLETE:
            RetailOutput(TEXT("GD-ROM drive door has been opened.\r\n"));
            g_bDoorOpened = TRUE;
            break;
        }
        break;

	case WM_KEYDOWN:

		switch ( wParam )
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

    // Create a handle to the GDROM drive.
    g_hGDROM = CreateFile(TEXT("\\Device\\CDROM0"), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL );
    if (g_hGDROM == INVALID_HANDLE_VALUE)
    {
        RetailOutput(TEXT("Error opening GD-ROM\r\n"));
        return FALSE;
    }

    return TRUE;
}

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

	// Release Events Handles
    if (g_hDeviceEvent[NEW_DEVICE] != NULL)
    {
        CloseHandle(g_hDeviceEvent[NEW_DEVICE]);
        g_hDeviceEvent[NEW_DEVICE] = NULL;
    }

    if (g_hDeviceEvent[DEVICE_REMOVED] != NULL)
    {
        CloseHandle(g_hDeviceEvent[DEVICE_REMOVED]);
        g_hDeviceEvent[DEVICE_REMOVED] = NULL;
    }

    if (g_hGDROM != NULL)
    {
        CloseHandle(g_hGDROM);
        g_hGDROM = NULL;
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitVMU

Description:

    Find the first VMU and mark it as the Game Saving device

Arguments:

    None
  
Return Value:

    BOOL : VMU found or not

-------------------------------------------------------------------*/

BOOL 
InitVMU()
{
	TCHAR szBuf[256];
	DWORD device = 1;
    // Examine each of the ports - if there is a controller attached to
    // the port then continue on
    for (int i = 0; i < g_nPorts; i++)
    {
        if (g_rgpcont[i] != NULL)
        {
            // There is a controller attached to Port #'i'.  Check to see if
            // it has a Flash devices attached to it.  If so, use it as the save device
            g_pFlash = g_rgpcont[i]->GetFlash(0);
            if (!g_pFlash)
            {
                g_pFlash = g_rgpcont[i]->GetFlash(1);
                if (!g_pFlash)
                {
					continue;
                }
				device = 2;
            }
 		    wsprintf( szBuf, _T("\nUsing VMU on port %i device %i\r\n"), i, device);
			RetailOutput(szBuf);
			// We found a VMU
			return TRUE;
        }
    }
    RetailOutput(TEXT("\r\nNo VMUs found.  Please Insert one...\r\n"));
	return FALSE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ChooseSaveSlot

Description:

    Display the current state of the savegame slots and enable saving

Arguments:

    None
  
Return Value:

    None

-------------------------------------------------------------------*/

void 
ChooseSaveSlot()
{
	g_pFlash->PrintFiles();
    RetailOutput(TEXT("Please choose a save file number where you want to save: \r\n"));
	g_bChoose = TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    Save

Description:

    Save the game information to the VMU

Arguments:

    None
  
Return Value:

    None

-------------------------------------------------------------------*/

void 
Save( DWORD in_dwSlot )
{
	TCHAR   szBuf[128];
	HRESULT l_hr;

	// If we are not in file selection mode, do nothing
	if ( !g_bChoose )
		return;
	g_bChoose = FALSE;

	wsprintf( szBuf, _T("\nSaving in slot %i...\n"), in_dwSlot);
    RetailOutput(szBuf);

	if ( FAILED ( l_hr=g_pFlash->Save( in_dwSlot ) ))
	{
		wsprintf( szBuf, _T("\nSave failed, hr=0x%x...\n"), l_hr);
		RetailOutput(szBuf);
	}

	// Reprint the new file list
	PostMessage( g_hwndApp, WM_CHOSSESAVESLOT, 0, 0 );
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
    RetailOutput(TEXT("\r\nApp starting...\r\n"));

    // Store Instance handle for use later...
    g_hinst = hInstance;

	if (!AppInit( hPrevInstance, nCmdShow ))
		return 0;

    // Initialize DirectInput.  This will populate the g_rgpcont array,
    // which describes which controllers are in each port.
    if (!InitDirectInput())
        return FALSE;


	PostMessage( g_hwndApp, WM_INITVMU, NULL, NULL );

    // Main Message loop
    while (TRUE)
    {
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            // There's a message waiting in the queue for us.  Retrieve
            // it and dispatch it, unless it's a WM_QUIT.
            if (msg.message == WM_QUIT )
                break;

            TranslateMessage(&msg); 
            DispatchMessage(&msg);
        }  
		else
		{
			// Check for device change ( device added or removed )
			CheckNewDevices();
		}

    }

    CleanUp();

    RetailOutput(TEXT("\r\nApp exited...\r\n"));

    return 0;
}
