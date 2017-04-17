/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    JoyPC.cpp

Abstract:

    PC joystick routines. Just a dummy file to use in place of
	the Dreamcast joystick code (JoyCE.cpp).

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCInput.h"
#include <dinput.h>

// Initializes joystick(s).
BOOL InitJoystick(LPDIRECTINPUT DIInterface)
{

	return FALSE;
}

// Shuts down joystick(s).
void ShutdownJoystick()
{

}

// Processes joystick(s).
void ProcessJoystick()
{

}

// Acquire joystick(s).
void AcquireJoystick()
{

}

// Unacquire joystick(s).
void UnacquireJoystick()
{


}
