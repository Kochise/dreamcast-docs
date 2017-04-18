/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    JoyCE.cpp

Abstract:

	Dreamcast controller routines which use CController
	class from SDK sample code. 

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCInput.h"
#include "DCGame.h"
#include <dinput.h>
#include <maplusag.h>
#include "CControllerCE.h"

#define MAX_CONTROLLERS 4
#define MAX_BUTTONS (USAGE_LAST_BUTTON - USAGE_FIRST_BUTTON + 1)
#define MAX_AXES 4

#define BUTTON_A		(USAGE_A_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_B		(USAGE_B_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_C		(USAGE_C_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_START	(USAGE_START_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_LA		(USAGE_LA_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_RA		(USAGE_RA_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_DA		(USAGE_DA_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_UA		(USAGE_UA_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_X		(USAGE_X_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_Y		(USAGE_Y_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_Z		(USAGE_Z_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_D		(USAGE_D_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_LB		(USAGE_LB_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_RB		(USAGE_RB_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_DB		(USAGE_DB_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_UB		(USAGE_UB_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_RTRIG	(USAGE_RTRIG_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_LTRIG	(USAGE_LTRIG_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_AN3		(USAGE_AN3_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_AN4		(USAGE_AN4_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_AN5		(USAGE_AN5_BUTTON - USAGE_FIRST_BUTTON)
#define BUTTON_AN6		(USAGE_AN6_BUTTON - USAGE_FIRST_BUTTON)

#define JOY_SENSITIVITY_X	1250
#define JOY_SENSITIVITY_Y	-750

static BOOL		Initialized;
static LPDIRECTINPUT DIInterface;
static HANDLE   NewDeviceEventHandle;
static CController *Controllers[MAX_CONTROLLERS];    // The list of active input devices

// Determines if the controller is a new device.
BOOL IsNewDevice(GUID guidDevice)
{
    UINT iPort;
    CController *pcont;
    
    for (iPort = 0; iPort < MAX_CONTROLLERS; iPort++)
    {
        pcont = Controllers[iPort];
        if (pcont != NULL && guidDevice == pcont->GetGuid())
            return FALSE;
    }

    return TRUE;
}    

// Enumerator for the joystick devices.
BOOL CALLBACK DIEnumProc(LPCDIDEVICEINSTANCE pdidi, LPVOID pvContext)
{
    UINT iPort;
    CController *pcontNew;

    switch (GET_DIDEVICE_TYPE(pdidi->dwDevType))
    {
		case DIDEVTYPE_JOYSTICK:
			if (IsNewDevice(pdidi->guidInstance))
			{
				// It's a new device!  Create the device
				pcontNew = new CController(pdidi->guidInstance, pdidi->dwDevType);

				// Initialize the device
				if (!pcontNew->Initialize(DIInterface))
				{
					delete pcontNew;
					return TRUE;
				}

				iPort = pcontNew->GetPort();
				if (iPort>=MAX_CONTROLLERS)
				{
					delete pcontNew;
					return TRUE;
				}

				Controllers[iPort] = pcontNew;

				// Output the name of the new device
//				if (!_tcscmp(pdidi->tszProductName, TEXT("")))
//					DebugOutput(TEXT("Device found on Port %d -- Device name not set\r\n"), iPort);
//				else
//					DebugOutput(TEXT("Device found on Port %d -- \"%s\"\r\n"), iPort, pdidi->tszProductName);
			}
			break;

		case DIDEVTYPE_KEYBOARD:
			// Don't wan't keyboards.
			// We handle keyboard input via WK_KEYDOWN/UP events to the apps window.
		default:
//			DebugOutput(TEXT("Enum Devices: Unknown Device type\n"));
			break;
    }
    return TRUE;
}

// Polls the devices.
static void PollDevices()
{
    int iPort;

    for (iPort = 0; iPort < MAX_CONTROLLERS; iPort++)
    {
        CController *pcont = Controllers[iPort];
        if (pcont != NULL)
        {
            // Poll tells the Maple Bus to start getting new data.  Because
            // Maple gets data for all devices at the same time, you only need
            // to call this once to get data for everything.  However, 
            // The maple driver will not get data extraneously if you call it 
            // once for each device.
            if (!pcont->Poll())
            {
                Controllers[iPort] = NULL;
                delete pcont;
            }
        }
    }
}

// Gets the device data for the devices.
void GetDeviceData()
{
    int iPort;

    for (iPort = 0; iPort < MAX_CONTROLLERS; iPort++)
    {
        CController *pcont = Controllers[iPort];
        if (pcont != NULL)
        {
            if (!pcont->GetData())
            {
                Controllers[iPort] = NULL;
                delete pcont;
            }
        }
    }
}


// Checks to see if there are any new devices.
void CheckNewDevices()
{
    // If 'WaitForSingleObject returns with WAIT_TIMEOUT, there are no new devices. Otherwise, there could be new devices.
    if (WaitForSingleObject(NewDeviceEventHandle, 0) != WAIT_TIMEOUT)
        DIInterface->EnumDevices(0, (LPDIENUMDEVICESCALLBACK)DIEnumProc, NULL, 0);
}

void ProcessControllerState(CController* pcont)
{
    unsigned int iButton, iAxis;
	static int LastLeftTrigger=0,LastRightTrigger=0;

    // First, handle each of the buttons.  
    for (iButton = 0; iButton < g_nMaxButtons; iButton++)
    {
        if (pcont->m_buttonIndices[iButton] != g_iInvalid)
        {
            // This button exists.
			if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[iButton]])
			{
				// Button has changed so send button state.
				int Event=(pcont->m_curButtonValues[pcont->m_buttonIndices[iButton]]) ? 1 : 0;

				switch (iButton)
				{
					case BUTTON_A:
						break;
					case BUTTON_B:
						gGame.InputEvent(INPUT_FIRE3,Event);
						break;
					case BUTTON_C:
						break;
					case BUTTON_START:
						gGame.InputEvent(INPUT_STARTBUTTON,Event);
						break;
					case BUTTON_LA:
						gGame.InputEvent(INPUT_LEFTSTRAFE,Event);
						break;
					case BUTTON_RA:
						gGame.InputEvent(INPUT_RIGHTSTRAFE,Event);
						break;
					case BUTTON_DA:
						gGame.InputEvent(INPUT_BACKWARD,Event);
						break;
					case BUTTON_UA:
						gGame.InputEvent(INPUT_FORWARD,Event);
						break;
					case BUTTON_X:
						gGame.InputEvent(INPUT_FIRE1,Event);
						break;
					case BUTTON_Y:
						gGame.InputEvent(INPUT_FIRE2,Event);
						break;
					case BUTTON_Z:
						break;
					case BUTTON_D:
						break;
					case BUTTON_LB:
						break;
					case BUTTON_RB:
						break;
					case BUTTON_DB:
						break;
					case BUTTON_UB:
						break;
					case BUTTON_RTRIG:
						// Convert analog trigger value into an on or off value.
						// Analog range is 0-255.
						Event=(pcont->m_curButtonValues[pcont->m_buttonIndices[iButton]] > 64) ? 1 : 0;
						if (Event!=LastRightTrigger)
						{
							LastRightTrigger=Event;
							gGame.InputEvent(INPUT_PAUSETIME,Event);
						}
						break;
					case BUTTON_LTRIG:
						// Convert analog trigger value into an on or off value.
						// Analog range is 0-255.
						Event=(pcont->m_curButtonValues[pcont->m_buttonIndices[iButton]] > 64) ? 1 : 0;
						if (Event!=LastLeftTrigger)
						{
							LastLeftTrigger=Event;
							gGame.InputEvent(INPUT_OBSERVERTOGGLE,Event);
						}
						break;
					case BUTTON_AN3:
						break;
					case BUTTON_AN4:
						break;
					case BUTTON_AN5:
						break;
					case BUTTON_AN6:
						break;
				}
			}
		}
	}

    // Next, handle each of the axes
    for (iAxis=0;iAxis<MAX_AXES;iAxis++)
    {
        if (pcont->m_axisIndices[iAxis].iAxis != g_iInvalid)
        {
            // This axis exists so send value.
			int Event=(int)pcont->m_curAxisValues[pcont->m_axisIndices[iAxis].iAxis] - 127;

			switch (pcont->m_axisIndices[iAxis].eaxis)
			{
			    case eXAxis:
					gGame.InputEvent(INPUT_JOYX,Event*JOY_SENSITIVITY_X);
					break;
			    case eYAxis:
					gGame.InputEvent(INPUT_JOYY,Event*JOY_SENSITIVITY_Y);
					break;
			}
        }
    }
}
// Initializes joystick(s).
BOOL InitJoystick(LPDIRECTINPUT DIInterfaceIn)
{
    // Store of the DirectInput interface as we'll need it.
	DIInterface=DIInterfaceIn;

	// Create the event that will be triggered whenever a device is added.
    NewDeviceEventHandle=CreateEvent(NULL, FALSE, FALSE, TEXT("MAPLE_NEW_DEVICE"));
	if (NewDeviceEventHandle==NULL)
	{
        SetErrorMessage(IDS_ERROR_JOYSTICK);
		return FALSE;
	}

    // Initialize the list of devices
    for (int i=0;i<MAX_CONTROLLERS;i++)
        Controllers[i]=NULL;

    // EnumDevices is how we determine if there are any controllers plugged in.
    // It will call the DIEnumProc function once for each device.
    // You should do this first one regardless of the state of the 
    // MAPLE_NEW_DEVICE event.  It's possible that something else reset the 
    // event before this app ran.  
    if (FAILED(DIInterface->EnumDevices(0, (LPDIENUMDEVICESCALLBACK)DIEnumProc, NULL, 0)))
	{
        SetErrorMessage(IDS_ERROR_JOYSTICK);
        return FALSE;
	}

    // Since we just enumerated the devices.  We'll call the Wait once to clear the event.
    WaitForSingleObject(NewDeviceEventHandle, 0);

	// Poll the devices so the game has something to start with.
	PollDevices();

	Initialized=TRUE;
	return TRUE;
}

// Shuts down joystick(s).
void ShutdownJoystick()
{
	// Delete any controller objects.
    for (int i=0;i<MAX_CONTROLLERS;i++)
	{
		if (Controllers[i])
		{
			delete Controllers[i];
			Controllers[i]=NULL;
		}
	}

	// Kill off the event.
	CloseHandle(NewDeviceEventHandle);
}

// Processes joystick(s).
void ProcessJoystick()
{
	// Read the devices.
	GetDeviceData();

	// Send the controller(s) state(s).
	// We'll let all controllers control at the same time.
	for (int i=0;i<MAX_CONTROLLERS;i++)
		if (Controllers[i])
	        ProcessControllerState(Controllers[i]);

	// See if we have any new devices.
	CheckNewDevices();

	// Start the devices polling again.
	PollDevices();
}

// Acquire joystick(s).
void AcquireJoystick()
{
	// Don't need to bother with this - devices are always acquired.
}

// Unacquire joystick(s).
void UnacquireJoystick()
{


}
