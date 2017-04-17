/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    Input.cpp

Abstract:

    Main input code. Includes the Windows message loop.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"
#include "DCInput.h"
#include "DCGame.h"
#include <dinput.h>

// Platform specific functions in Joy.cpp
BOOL InitJoystick(LPDIRECTINPUT DIInterface);
void ShutdownJoystick();
void ProcessJoystick();
void AcquireJoystick();
void UnacquireJoystick();

#define MOUSE_SENSITIVITY_X	250
#define MOUSE_SENSITIVITY_Y	250

static LPDIRECTINPUT DIInterface=NULL;
static LPDIRECTINPUTDEVICE2 MouseDevice=NULL;
static BOOL MouseAcquired=FALSE;
static BOOL MouseButton1State=FALSE;
static BOOL MouseButton2State=FALSE;
static BOOL MouseButton3State=FALSE;

// Initializes the input code.
BOOL InitInput(HWND AppHWnd)
{
	// Get Direct Input interface.
	if (FAILED(DirectInputCreate(gHInstance,DIRECTINPUT_VERSION,&DIInterface,NULL)))
	{
		SetErrorMessage(IDS_ERROR_DIRECTINPUTCREATE);
		return FALSE;
	}

	// Initialize mouse.
	LPDIRECTINPUTDEVICE TmpDevice;
	if (SUCCEEDED(DIInterface->CreateDevice(GUID_SysMouse,&TmpDevice,NULL)))
	{
		// Get IDirectInputDevice2 interface since we may want to
		// suppport force feedback later.
		if (SUCCEEDED(TmpDevice->QueryInterface(IID_IDirectInputDevice2,
												(LPVOID *)&MouseDevice)))
		{
			// Finish setting up mouse device.
			HRESULT hr;

			hr=MouseDevice->SetDataFormat(&c_dfDIMouse);
			if (SUCCEEDED(hr))
				hr=MouseDevice->SetCooperativeLevel(AppHWnd,DISCL_EXCLUSIVE | DISCL_FOREGROUND);

			if (FAILED(hr))
			{
				MouseDevice->Release();
				MouseDevice=NULL;
			}
		}

		// Don't need this anymore.
		TmpDevice->Release();
	}

	// Init joystick(s).
	BOOL JoyStatus=InitJoystick(DIInterface);

	// We must have some kind of input device.
	if (!MouseDevice && !JoyStatus)
	{
		ShutdownInput(AppHWnd);
		SetErrorMessage(IDS_ERROR_NOINPUTDEVICE);
		return FALSE;
	}

	// Since we will have focus straight away, 
	// we can acquire the input devices now.
	AcquireInput();

	return TRUE;
}

void ShutdownInput(HWND AppHWnd)
{
	// Shutdown joysick(s).
	ShutdownJoystick();

	// Release mouse device.
	if (MouseDevice)
	{
		MouseDevice->SetCooperativeLevel(AppHWnd,DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		MouseDevice->Release();
		MouseDevice=NULL;
	}

	// Release DirectDraw interface.
	if (DIInterface)
	{
		DIInterface->Release();
		DIInterface=NULL;
	}
}

// Processes pending Windows messages.
static void ProcessMessages(void)
{
	HWND Window=gGraphics.GetAppWindow();
	MSG  Msg;

	// Read all messages in the message queue and dispatch them.
	while (1)
	{
		BOOL Status=PeekMessage(&Msg,Window,0,0,PM_NOREMOVE);
		
		if (!Status && !gAppPaused)
			return; // No message, so let app continue.

		// Get message.
		Status=GetMessage(&Msg,Window,0,0);
		if (!Status || Status==-1)
		{
			DC_WARNING(("Application window destroyed.\n"));
			gAppExit=TRUE;
			return;
		}

		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

static void HandleMouseButtonInput(BOOL *CurrentState, BOOL NewState, GameInputControl Control)
{
	// See if anything changed.
	if (*CurrentState!=NewState)
	{
		*CurrentState=NewState;
		gGame.InputEvent(Control,(NewState) ? 1 : 0);
	}
}

// Processes mouse input.
static void ProcessMouse(void)
{
	if (MouseDevice)
	{
		DIMOUSESTATE dims;
		HRESULT hr;

        // Get the input's device state, and put the state in dims.
        hr = MouseDevice->GetDeviceState( sizeof(DIMOUSESTATE), &dims );

		// If input lost, try and acquire it.
		if (hr == DIERR_INPUTLOST)
		{
			hr = MouseDevice->Acquire();
			if (SUCCEEDED(hr))
		        hr = MouseDevice->GetDeviceState( sizeof(DIMOUSESTATE), &dims );
		}
		if (SUCCEEDED(hr))
		{
			// Have data from the mouse, so process it.
			// Axes.
			if (dims.lX)
				gGame.InputEvent(INPUT_MOUSEX,dims.lX*MOUSE_SENSITIVITY_X);
			if (dims.lY)
				gGame.InputEvent(INPUT_MOUSEY,dims.lY*MOUSE_SENSITIVITY_Y);
			// Buttons.
			HandleMouseButtonInput(&MouseButton1State,(dims.rgbButtons[0] & 0x80)!=0,INPUT_FIRE1);
			HandleMouseButtonInput(&MouseButton2State,(dims.rgbButtons[1] & 0x80)!=0,INPUT_FIRE2);
			HandleMouseButtonInput(&MouseButton3State,(dims.rgbButtons[2] & 0x80)!=0,INPUT_FIRE3);
		}
	}
}

// Processes all types of input.
void ProcessInput(void)
{
	ProcessMessages();
	if (gAppExit)
		return;	// App quiting.
	ProcessMouse();
	ProcessJoystick();
}

// Acquires our input devices.
void AcquireInput(void)
{
	HRESULT hr;

	// Acquire mouse if necessary.
	if (MouseDevice && !MouseAcquired)
	{
		if (SUCCEEDED(hr=MouseDevice->Acquire()))
			MouseAcquired=TRUE;
	}

	// Acquire joystick.
	AcquireJoystick();
}

// Unacquires our input devices so other apps can use them.
void UnacquireInput(void)
{
	// Unacquire mouse if necessary.
	if (MouseDevice && MouseAcquired)
	{
		MouseDevice->Unacquire();
		MouseAcquired=FALSE;
	}
	// Unacquire joystick.
	UnacquireJoystick();
}

// Handles a windows key event.
void KeyEvent(int Key, BOOL Down)
{
	static BOOL AltState=FALSE;
	int Event=(Down!=0) ? 1 : 0;

	// Handle events.
	switch (Key)
	{
		case VK_F1:
			gGame.InputEvent(INPUT_HELP,Event);
			break;
		case VK_F2:
			gGame.InputEvent(INPUT_OBSERVERTOGGLE,Event);
			break;
		case VK_F3:
			gGame.InputEvent(INPUT_PAUSETIME,Event);
			break;
		case VK_F4:
			// See if Alt-F4'ing.
			if (Down && AltState)
				gAppExit=TRUE;
			else if (Down)
				// Toggle stats.
				gDisplayStats=(gDisplayStats) ? FALSE : TRUE;
			break;
		case VK_F5:
// Don't want this in release Dreamcast builds as it will exceed the vertex
// buffers, resulting in the rendering not updating.
#if defined(_DEBUG) || !defined(DREAMCAST)
			if (Down)
			{
				// Toggle "show triangles".
				if (gGraphics.GetShowTriangles())
					gGraphics.DisableShowTriangles();
				else
					gGraphics.EnableShowTriangles();
			}
#endif
			break;
		case VK_F6:
			gGame.InputEvent(INPUT_GODMODETOGGLE,Event);
			break;
#ifndef DREAMCAST
		case VK_F7:
			gGame.InputEvent(INPUT_START_DEMO_RECORD,Event);
			break;
		case VK_F8:
			gGame.InputEvent(INPUT_END_DEMO_RECORD,Event);
			break;
#endif
		case VK_F9:
			gGame.InputEvent(INPUT_TIMEDEMO,Event);
			break;
		case VK_F10:
			// F10 is quit.
			if (Down)
				gAppExit=TRUE;
			break;
		case VK_F11:
			// F11 is "screen shot".
			if (Down)
				gGraphics.DumpScreenShot();
			break;
		case VK_F12:
			// F12 is for temporary stuff.
#if 0
			if (Down)
				gCreateFishEyeView=TRUE;
#elif 0
			if (Down)
				gGraphics.DumpDepthBufferShot();
			break;
#endif
		case VK_CONTROL:
			// Ctrl is fire 1.
			gGame.InputEvent(INPUT_FIRE1,Event);
			break;
		case (VK_CONTROL+1):
			// Hang onto alt state.
			AltState=Down;
			// Alt is fire 2.
			gGame.InputEvent(INPUT_FIRE2,Event);
			break;
		case VK_SPACE:
			// Alt is fire 3.
			gGame.InputEvent(INPUT_FIRE3,Event);
			break;
		case VK_RETURN:
			// Enter is start game.
			gGame.InputEvent(INPUT_STARTGAME,Event);
			break;
		case VK_ESCAPE:
			// Esc key is end game.
			gGame.InputEvent(INPUT_ENDGAME,Event);
			break;
		case VK_LEFT:
		case VK_NUMPAD4:
		case 'Q':
		case 'A':
			gGame.InputEvent(INPUT_LEFTSTRAFE,Event);
			break;		
		case VK_RIGHT:
		case VK_NUMPAD6:
		case 'D':
			gGame.InputEvent(INPUT_RIGHTSTRAFE,Event);
			break;
		case VK_UP:
		case VK_NUMPAD8:
		case 'W':
			gGame.InputEvent(INPUT_FORWARD,Event);
			break;
		case VK_DOWN:
		case VK_NUMPAD2:
		case 'S':
			gGame.InputEvent(INPUT_BACKWARD,Event);
			break;
	}
}
