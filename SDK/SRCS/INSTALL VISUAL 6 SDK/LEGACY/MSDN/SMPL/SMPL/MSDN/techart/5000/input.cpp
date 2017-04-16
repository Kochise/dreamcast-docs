/*==========================================================================
 *  Copyright (C) 1996 Microsoft Corporation.
 *
 *  File:       input.cpp
 *  Content:    DirectInput functionality for Moby Dick
 *
 ***************************************************************************/

//#define USE_DIRECTINPUT // For conditional compilation.
                        //   When using DirectInput you need to link DXGUID.LIB
                        //   and have DINPUT.DLL available at runtime 

#include <dinput.h>
#include "input.h"

extern HINSTANCE   hTheInstance;           // program instance
extern HWND        hMainWindow;            // app window handle
extern BOOL        MouseAcquired;    

#ifdef USE_DIRECTINPUT
extern LPDIRECTINPUTDEVICE   lpdiMouse;    // mouse device interface
#else
LPDIRECTINPUTDEVICE   lpdiMouse;           // not used; just for compilation
#endif

static LPDIRECTINPUT         lpdi;         // DirectInput interface
GUID               MouseGUID;


/* **********************************************************
   DIEnumDevicesProc()
   Callback function required by EnumDevices
*********************************************************** */

BOOL CALLBACK DIEnumDevicesProc(LPCDIDEVICEINSTANCE lpddi, 
                                LPVOID pvRef)
  {
    MouseGUID = lpddi->guidProduct;   
    // how to do this using pvRef as a pointer to MouseGUID ??????

    
    return DIENUM_CONTINUE;
  } // DIEnumDevicesProc



/* **********************************************************
   InitInput()
   Initialize DirectInput objects & devices
************************************************************ */
BOOL InitInput(void)
  {
  static GUID  DefaultGUID = GUID_SysMouse;

  // try to create DirectInput object
  if(DirectInputCreate(hTheInstance, DIRECTINPUT_VERSION, &lpdi, NULL) != DI_OK)
    {
    OutputDebugString("Failed to create DirectInput object.\n");
    return FALSE;
    }
  
  // enumerate devices so we can get the Mouse GUID
  if (lpdi->EnumDevices(DIDEVTYPE_MOUSE, 
                        DIEnumDevicesProc,
                        &MouseGUID, 
                        DIEDFL_ATTACHEDONLY) != DI_OK)
    {
    OutputDebugString("Could not enumerate mouse devices.\n");
//  return FALSE;
    }

  // try to create mouse device
  if(lpdi->CreateDevice(MouseGUID, &lpdiMouse, NULL) !=DI_OK)
    {
   if (lpdi->CreateDevice(DefaultGUID, &lpdiMouse, NULL) != DI_OK)
      {
        OutputDebugString("Failed to create mouse device.\n");
        return FALSE;
      }
    }

  // set cooperative level
  if(lpdiMouse->SetCooperativeLevel(hMainWindow,
         DISCL_NONEXCLUSIVE | DISCL_FOREGROUND) != DI_OK)
    {
    OutputDebugString("Failed to set cooperative level.\n");
    return FALSE;
    }
  
  // Set data format. Must be done before mouse can be acquired.
  //   Note: c_dfDIMouse is an external DIDATAFORMAT structure supplied
  //   by DirectInput. Default values are:
  //          dwSize      24
  //          dwObjSize   16
  //          dwFlags      2    = DIDF_RELAXIS
  //          dwDataSize  16
  //          dwNumObjs    7    (3 axes and 4 buttons)

  if (lpdiMouse->SetDataFormat(&c_dfDIMouse) != DI_OK)
    {
    OutputDebugString("Failed to set mouse data format.\n");
    return FALSE;
    }

  /* This is how to change the mouse coordinates from relative to absolute. */
  /*
  DIPROPDWORD dipdw;
  HRESULT hres;
  dipdw.diph.dwSize = sizeof(DIPROPDWORD);
  dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
  dipdw.diph.dwObj = 0;
  dipdw.diph.dwHow = DIPH_DEVICE;
  dipdw.dwData = DIPROPAXISMODE_ABS;
  hres = lpdiMouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
  if (hres != DI_OK) 
    OutputDebugString("Failed to set mouse axis mode.\n");
  */

  // try to acquire the mouse
  if (lpdiMouse->Acquire() != DI_OK)
    {
    OutputDebugString("Failed to acquire the mouse.\n");
    return FALSE;
    }
 

  MouseAcquired = TRUE;
  return TRUE;    
  }  // InitInput()


/*
*
* CleanupInput
*
* Cleans up DirectInput objects
*
*/
void CleanupInput(void)
{
        if(MouseAcquired)
        {
                lpdiMouse->Unacquire();
                MouseAcquired = FALSE;
        }

        if(lpdiMouse != NULL)
                lpdiMouse->Release();

        if(lpdi!= NULL)
                lpdi->Release();
        
}


/* ******************************************************************
   ReacquireInputDevices
   Needs to be called whenever we have lost the mouse because e.g. 
   a dialog box was opened. Typically called in response to a 
   WM_ACTIVATE message.
   ****************************************************************** */
BOOL ReacquireMouse(void)
{
        // try to acquire the Mouse
        if(lpdiMouse != NULL)
        {
                lpdiMouse->Acquire();
             }
        else
        {
                // Mouse device has not been created.
                return FALSE;
        }

        // if we get here, we are acquired again
        MouseAcquired = TRUE;
        return TRUE;
}












