/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    Dinput.cpp

Abstract:

   This file contains DirectInput functionality for the Desktop Compatibility sample.

-------------------------------------------------------------------*/
#include "DesktopCompat.hpp"




// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
LPDIRECTINPUT g_pdi;                          // The DirectInput object
CController  *g_rgpcont[MAX_CONTROLLERS];     // The list of active input devices
HANDLE        g_hNewDeviceEvent;              // 'New Device' event
int			  g_ndevices = 0;				  // Total number of devices
DWORD		  g_lastTime;				      // last time in milliseconds when 
											  // the devices were enumerated.

											  
											 
											  
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
	HRESULT hr;
    // Create the event that will be triggered whenever a device is added.
    g_hNewDeviceEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("MAPLE_NEW_DEVICE"));
    if (g_hNewDeviceEvent == NULL)
	{
        DebugOutput(TEXT("Error creating new device event.  Closing.\n"));
        return FALSE;
    }

    // Create the global DirectInput object
    hr = DirectInputCreate(g_hinst, DIRECTINPUT_VERSION, &g_pdi, NULL);
   	if(FAILED(hr) || g_pdi == NULL)
	{
		ErrorMessage(NULL, TEXT("Direct Input Create Failed"));
	    if (g_hNewDeviceEvent != NULL)
        {
            CloseHandle(g_hNewDeviceEvent);
            g_hNewDeviceEvent = NULL;
        }
        return FALSE;
    }

    // Initialize the list of devices
    for (i = 0; i < MAX_CONTROLLERS; i++)
        g_rgpcont[i] = NULL;

#ifndef UNDER_CE

	// Since under the desktop, we enumerate every 3 seconds, we need to record 
	// the time we enumerate.  
	g_lastTime = timeGetTime();

#endif 

    
	// EnumDevices is how we determine if there are any controllers plugged in.
    // It will call the DIEnumProc function once for each device.
    // You should do this first one regardless of the state of the 
    // MAPLE_NEW_DEVICE event.  It's possible that something else reset the 
    // event before this app ran.  


  	hr = g_pdi->EnumDevices(0, (LPDIENUMDEVICESCALLBACK)DIEnumProc, NULL, 0);
   	if(FAILED(hr)){
		ErrorMessage(NULL, TEXT("Enumerate Devices"));
		return FALSE;
	}
 

    // Since we just enumerated the devices.  We'll call the Wait once to clear the event.
    WaitForSingleObject(g_hNewDeviceEvent, 0);

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    PollDevices

Description:

    Polls all of the devices

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void
PollDevices()
{
    int iPort;

    for (iPort = 0; iPort < g_nPorts; iPort++)
    {
        CController *pcont = g_rgpcont[iPort];
        if (pcont != NULL)
        {
            // Poll tells the Maple Bus to start getting new data.  Because
            // Maple gets data for all devices at the same time, you only need
            // to call this once to get data for everything.  However, 
            // The maple driver will not get data extraneously if you call it 
            // once for each device.
            if (!pcont->Poll())
            {
                g_rgpcont[iPort] = NULL;
                delete pcont;
            }
        }
    }
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

    CheckNewDevices

Description:

    Checks to see if any new devices have been plugged in

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void
CheckNewDevices()
{
#ifdef UNDER_CE
    // UNder the Dreamcast, the event "MAPLE_NEW_DEVICE" is defined.  Hence, 
	// WaitForSingleObject(g_hNewDeviceEvent, 0) checks automatically for 
	// new decvices
	// If 'WaitForSingleObject returns with WAIT_TIMEOUT, 
	// there are no new devices. Otherwise, there could be new devices.
    
	if (WaitForSingleObject(g_hNewDeviceEvent, 0) != WAIT_TIMEOUT)
        g_pdi->EnumDevices(0, (LPDIENUMDEVICESCALLBACK)DIEnumProc, NULL, 0);
		
#else //Desktop
	// Under the Desktop Environment, we enumerate all devices every 3 seconds.

	if(	DWORD t = timeGetTime() - g_lastTime > 3000){
		g_ndevices = 0;
		g_pdi->EnumDevices(0, (LPDIENUMDEVICESCALLBACK)DIEnumProc, NULL, 0);
		g_lastTime = timeGetTime();
	}
#endif //UNDER_CE
		
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
	HRESULT hr;
    switch (GET_DIDEVICE_TYPE(pdidi->dwDevType))
    {
    case DIDEVTYPE_JOYSTICK:
    case DIDEVTYPE_MOUSE:
	case DIDEVTYPE_KEYBOARD:
        if (IsNewDevice(pdidi->guidInstance))
        {
            // It's a new device!  Create the device
            pcontNew = new CController(pdidi->guidInstance, pdidi->dwDevType);

            // Initialize the device

            hr = (pcontNew->Initialize() != TRUE);
			if(FAILED(hr)){
				ErrorMessage(NULL, TEXT("Initialize Device"));
				delete pcontNew;
				return TRUE;
			}
 
#ifdef UNDER_CE			
            iPort = pcontNew->GetPort();
#else //Desktop
			iPort = g_ndevices++;
#endif //UNDER_CE
            g_rgpcont[iPort] = pcontNew;

            // Output the name of the new device
            if (!_tcscmp(pdidi->tszProductName, TEXT("")))
                DebugOutput(TEXT("Device found on Port %d -- Device name not set\r\n"), iPort);
            else
                DebugOutput(TEXT("Device found on Port %d -- \"%s\"\r\n"), iPort, pdidi->tszProductName);
        }
        break;

    default:
        DebugOutput(TEXT("Enum Devices: Unknown Device type\n"));
        break;
    }
    return TRUE;
}

