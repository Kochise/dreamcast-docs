/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    DIUtil.cpp

Abstract:

   This file contains DirectInput functionality for the VMU_Flash sample.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "SaveGame.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
LPDIRECTINPUT g_pdi;                          // The DirectInput object
CController   *g_rgpcont[MAX_CONTROLLERS];    // The list of active input devices

// ++++ Local Functions +++++++++++++++++++++++++++++++++++++++++++++

// Device enumeration functions
BOOL CALLBACK DIEnumProc(LPCDIDEVICEINSTANCE pdidi, LPVOID pvContext);
BOOL CALLBACK FlashEnumProc(LPCMAPLEDEVICEINSTANCE pmdi, LPVOID pvContext);

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitDirectInput

Description:

    Initializes the DirectInput object

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
InitDirectInput()
{
    int i;

    // Create the events that will be triggered whenever a device is added and removed.
    g_hDeviceEvent[NEW_DEVICE] = CreateEvent(NULL, FALSE, FALSE, TEXT("MAPLE_NEW_DEVICE"));
    if (g_hDeviceEvent[NEW_DEVICE] == NULL)
    {
        RetailOutput(TEXT("Error creating new device event."));
        return FALSE;
    }

    g_hDeviceEvent[DEVICE_REMOVED] = CreateEvent(NULL, FALSE, FALSE, TEXT("MAPLE_DEVICE_REMOVED"));
    if (g_hDeviceEvent[DEVICE_REMOVED] == NULL)
    {
        RetailOutput(TEXT("Error creating device removed event."));
        return FALSE;
    }

    // Create the global DirectInput object
    g_errLast = DirectInputCreate(g_hinst, DIRECTINPUT_VERSION, &g_pdi, NULL);
    if (CheckError(TEXT("DirectInputCreate")) || g_pdi == NULL)
    {
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
        return FALSE;
    }

    // Initialize the list of devices
    for (i = 0; i < MAX_CONTROLLERS; i++)
        g_rgpcont[i] = NULL;

    // EnumDevices is how we determine if there are any controllers plugged in.
    // It will call the DIEnumProc function once for each device.
    // You should do this first one regardless of the state of the 
    // MAPLE_NEW_DEVICE event.  It's possible that something else reset the 
    // event before this app ran.  
    g_errLast = g_pdi->EnumDevices(0, (LPDIENUMDEVICESCALLBACK)DIEnumProc, NULL, 0);
    if (CheckError(TEXT("Enumerate Devices")))
        return FALSE;

    // Check to see if there are any flash devices currently attached.  If so, then the 
    // Flash device will be attached to the appropriate port's controller object.
    MapleEnumerateDevices(MDT_STORAGE, FlashEnumProc, NULL, 0);

    // Since we just enumerated the devices.  We'll call the Wait once to clear the event.
    WaitForSingleObject(g_hDeviceEvent[NEW_DEVICE], 0);

    return TRUE;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetDeviceData

Description:

    Populates the device's data structures

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void
GetDeviceData()
{
    int iPort;

    for (iPort = 0; iPort < g_nPorts; iPort++)
    {
        CController *pcont = g_rgpcont[iPort];
        if (pcont != NULL)
        {
            if (!pcont->GetData())
            {
                g_rgpcont[iPort] = NULL;
                delete pcont;
            }
        }
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CheckDevices

Description:

    Check that all devices are still there

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void 
CheckDevices()
{
    int iPort;

    for (iPort = 0; iPort < g_nPorts; iPort++)
    {
        CController *pcont = g_rgpcont[iPort];
        if (pcont != NULL)
        {
            if (!pcont->GetData())
            {
                g_rgpcont[iPort] = NULL;
                delete pcont;
            }
			else
			{
				g_rgpcont[iPort]->CheckFlashes();
			}
        }
    }
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CheckNewDevices

Description:

    Checks to see if any new devices have been plugged in or any 
	devices removed.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void
CheckNewDevices()
{
    // If WaitForSingleObject returns with WAIT_TIMEOUT, no devices were removed. 
	// Otherwise, some devices may have been removed.
    if (WaitForSingleObject( g_hDeviceEvent[DEVICE_REMOVED], 0) != WAIT_TIMEOUT)
	{
		CheckDevices();
	}

    // If WaitForSingleObject returns with WAIT_TIMEOUT, there are no new devices. 
	// Otherwise, there could be new devices.
    if (WaitForSingleObject( g_hDeviceEvent[NEW_DEVICE], 0) != WAIT_TIMEOUT)
    {
		g_pdi->EnumDevices(0, (LPDIENUMDEVICESCALLBACK)DIEnumProc, NULL, 0);

		// Enumerate all of the Flash devices
		MapleEnumerateDevices(MDT_STORAGE, FlashEnumProc, NULL, 0);

		// If we do not have access to a VMU, try to find one
		if ( g_pFlash == NULL )
		{
			PostMessage( g_hwndApp, WM_INITVMU, 0,0 );
		}
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IsNewDevice

Description:

    Checks if the specified device guid has already been added.

Arguments:

    GUID guidDevice - The guid of the device we're checking

Return Value:

    TRUE if the device wasn't previously connected.

-------------------------------------------------------------------*/
BOOL
IsNewDevice(GUID guidDevice)
{
    UINT iPort;
    CController *pcont;
    
    for (iPort = 0; iPort < g_nPorts; iPort++)
    {
        pcont = g_rgpcont[iPort];
        if (pcont != NULL && guidDevice == pcont->GetGuid())
            return FALSE;
    }

    return TRUE;
}    

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    DIEnumProc

Description:

    Direct Input will call this function after we call EnumDevices.  It will 
    call this once for every controller currently plugged in.

Arguments:

    LPCDIDEVICEINSTANCE pdidi      - The device being enumerated
    
    LPVOID              pvContext  - User-defined data

Return Value:

    TRUE to continue enumerating, FALSE to stop

-------------------------------------------------------------------*/
BOOL CALLBACK
DIEnumProc(LPCDIDEVICEINSTANCE pdidi, LPVOID pvContext)
{
    UINT iPort;
    CController *pcontNew;

    switch (GET_DIDEVICE_TYPE(pdidi->dwDevType))
    {
    case DIDEVTYPE_JOYSTICK:
    case DIDEVTYPE_KEYBOARD:
        if (IsNewDevice(pdidi->guidInstance))
        {
            // It's a new device!  Create the device
            pcontNew = new CController(pdidi->guidInstance, pdidi->dwDevType);

            // Initialize the device
            g_errLast = (pcontNew->Initialize() != TRUE);
            if (CheckError(TEXT("Initialize Device")))
            {
                delete pcontNew;
                return TRUE;
            }

            iPort = pcontNew->GetPort();

			// If we already have a device there, delete it
			if ( g_rgpcont[iPort] )
			{
				delete g_rgpcont[iPort];
				g_rgpcont[iPort] = NULL;
			}

            g_rgpcont[iPort] = pcontNew;
        }
        break;

    default:
        DebugOutput(TEXT("Enum Devices: Unknown Device type\n"));
        break;
    }
    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    FlashEnumProc

Description:

    Direct Input will call this function after we call EnumerateMapleDevices.
    It will call this once for every device currently plugged in.

Arguments:

    LPCMAPLEDEVICEINSTANCE pmdi       - The Maple device being enumerated
    
    LPVOID                 pvContext  - User-defined data

Return Value:

    TRUE to continue enumerating, FALSE to stop

-------------------------------------------------------------------*/
BOOL CALLBACK
FlashEnumProc(LPCMAPLEDEVICEINSTANCE pmdi, LPVOID pvContext)
{
    DWORD dwPort = pmdi->dwPort;
    if (pmdi->devType == MDT_STORAGE && g_rgpcont[dwPort] != NULL)
	{
        g_rgpcont[dwPort]->FlashExists(pmdi->guidDevice, pmdi->dwDevNum);
	}

    return(TRUE);
}
