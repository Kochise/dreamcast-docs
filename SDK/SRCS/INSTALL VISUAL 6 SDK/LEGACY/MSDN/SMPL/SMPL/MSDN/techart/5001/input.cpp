/********************************************************************
 *  Copyright (C) 1996 Microsoft Corporation.
 *
 *  File:       INPUT.CPP
 *  Content:    DirectInput functionality for DInput sample program
 *  Author:     Peter Donnelly
 *  Tool:       Visual C++ 4.0
 *
 ********************************************************************/


#define BUFFERCOUNT 10                     // elements in keyboard buffer

#include <dinput.h>
#include <stdio.h>
#include "input.h"
#include "output.h"
#include "resource.h"

extern HINSTANCE      hTheInstance;        // program instance
extern HWND           hMainWindow;         // app window handle
extern BOOL           MouseRB;

// the objects
static LPDIRECTINPUT  lpdi;            
LPDIRECTINPUTDEVICE   lpdiMouse;   
LPDIRECTINPUTDEVICE   lpdiKeyboard;   

DIMOUSESTATE          diMouseState;
DIDEVICEOBJECTDATA    KbdBuffer[BUFFERCOUNT];
DIDEVICEOBJECTDATA    MouseBuffer[BUFFERCOUNT];

BOOL                  MouseAcquired; 
BOOL                  KeyboardAcquired;   
static GUID           MouseGUID;
static GUID           KeyboardGUID;
static BOOL           ClickHandled, RClickHandled;
static BOOL           MouseFound;
static BOOL           KeyboardFound;


/* **********************************************************
   DIEnumDevicesProc()
   Callback function required by EnumDevices
*********************************************************** */

BOOL CALLBACK DIEnumDevicesProc(LPCDIDEVICEINSTANCE lpddi, 
                                LPVOID pvRef)
  {
    if (GET_DIDEVICE_TYPE(lpddi->dwDevType) == DIDEVTYPE_MOUSE)
      {
      MouseGUID = lpddi->guidProduct;   
      MouseFound = TRUE;
      }
    if (GET_DIDEVICE_TYPE(lpddi->dwDevType) == DIDEVTYPE_KEYBOARD)
      {  
      KeyboardGUID = lpddi->guidProduct;   
      KeyboardFound = TRUE;
      }
    if (MouseFound && KeyboardFound)
      return DIENUM_STOP;
    else
      return DIENUM_CONTINUE;  
  } // DIEnumDevicesProc



/* **********************************************************
   InitInput()
   Initialize DirectInput objects & devices
************************************************************ */

BOOL InitInput(void)
  {
  DIPROPDWORD dipdw;
  HRESULT     hres;

  // try to create DirectInput object
  if(DirectInputCreate(hTheInstance, DIRECTINPUT_VERSION, &lpdi, NULL) != DI_OK)
    {
    OutputDebugString("Failed to create DirectInput object.\n");
    return FALSE;
    }
  
  // enumerate devices so we can get the GUIDs
  if (lpdi->EnumDevices(0, 
                        DIEnumDevicesProc,
                        NULL, 
                        DIEDFL_ATTACHEDONLY) != DI_OK)
    {
    OutputDebugString("Could not enumerate devices.\n");
    return FALSE;
    }
  if (!MouseFound)
    {
    OutputDebugString("Could not find a mouse.\n");
    return FALSE;
    }
  if (!KeyboardFound)
    {
    OutputDebugString("Could not find a keyboard.\n");
    return FALSE;
    }

  // create mouse device
  if(lpdi->CreateDevice(MouseGUID, &lpdiMouse, NULL) !=DI_OK)
    {
    OutputDebugString("Failed to create mouse device.\n");
    return FALSE;
    }

  // set mouse cooperative level. Non-exclusive won't work on NT!
  if (lpdiMouse->SetCooperativeLevel(hMainWindow,
         DISCL_NONEXCLUSIVE | DISCL_FOREGROUND) != DI_OK)
    {
    OutputDebugString("Failed to set mouse cooperative level.\n");
    return FALSE;
    }
  
 // set mouse buffer size
  dipdw.diph.dwSize = sizeof(DIPROPDWORD);
  dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
  dipdw.diph.dwObj = 0;
  dipdw.diph.dwHow = DIPH_DEVICE;
  dipdw.dwData = BUFFERCOUNT;
  hres = lpdiMouse->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
  if (hres != DI_OK) 
  {
    OutputDebugString("Failed to set mouse buffer size.\n");
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

  // try to acquire the mouse
  if (lpdiMouse->Acquire() != DI_OK)
    {
    OutputDebugString("Failed to acquire the mouse.\n");
    return FALSE;
    }

  MouseAcquired = TRUE;


/* The Keyboard */

 // try to create keyboard device
  if(lpdi->CreateDevice(KeyboardGUID, &lpdiKeyboard, NULL) !=DI_OK)
    {
    OutputDebugString("Failed to create keyboard device.\n");
    return FALSE;
    }

  // set kbd cooperative level
  if (lpdiKeyboard->SetCooperativeLevel(hMainWindow,
         DISCL_NONEXCLUSIVE | DISCL_FOREGROUND) != DI_OK)
    {
    OutputDebugString("Failed to set keyboard cooperative level.\n");
    return FALSE;
    }

  // set kbd data format
  if (lpdiKeyboard->SetDataFormat(&c_dfDIKeyboard) != DI_OK)
    {
    OutputDebugString("Failed to set keyboard data format.\n");
    return FALSE;
    }

 // set kbd buffer size
  dipdw.diph.dwSize = sizeof(DIPROPDWORD);
  dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
  dipdw.diph.dwObj = 0;
  dipdw.diph.dwHow = DIPH_DEVICE;
  dipdw.dwData = BUFFERCOUNT; // * sizeof(DIDEVICEOBJECTDATA);
  hres = lpdiKeyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
  if (hres != DI_OK) 
    {
    OutputDebugString("Failed to set keyboard buffer size.\n");
    return FALSE;
    }

  // try to acquire the keyboard
  if (lpdiKeyboard->Acquire() != DI_OK)
    {
    OutputDebugString("Failed to acquire the keyboard.\n");
    return FALSE;
    }

  KeyboardAcquired = TRUE;

  return TRUE;    
  }  // InitInput()


/* **********************************************
   CleanupInput()
   Cleans up DirectInput objects
 ************************************************ */
void CleanupInput(void)
  {
  if(MouseAcquired)
    {
    lpdiMouse->Unacquire();
    MouseAcquired = FALSE;
    }
  if(lpdiMouse != NULL) lpdiMouse->Release();
  
  if(KeyboardAcquired)
    {
    lpdiKeyboard->Unacquire();
    KeyboardAcquired = FALSE;
    }

  if(lpdiKeyboard != NULL) lpdiKeyboard->Release();

  if(lpdi!= NULL) lpdi->Release();
  } // CleanupInput()


/* ********************************************************
   ReacquireInputDevices
   Needs to be called whenever we have lost a device 
   ****************************************************** */

BOOL ReacquireInputDevices(void)
  {
  // try to acquire the Mouse
  if(lpdiMouse != NULL)
    {
    lpdiMouse->Acquire();
    }
  else
    {
    // mouse device has not been created
    return FALSE;
    }
  // if we get here, we are acquired again
  MouseAcquired = TRUE;

// now the keyboard
  if(lpdiKeyboard != NULL)
    {
  //  lpdiKeyboard->Acquire();
    }
  else
    {
    // keyboard device has not been created.
    return FALSE;
    }
  // if we get here, we are acquired again
  KeyboardAcquired = TRUE;

  return TRUE;
  }  // ReacquireInputDevices()



/* **********************************************
   PollMouse()
   Gets the mouse state in real time
 ************************************************ */

BOOL PollMouse(void)

  { 
  static LONG OldMouseX, OldMouseY;
  char z[100];
  
  if (!MouseAcquired) return FALSE;
  if (lpdiMouse->GetDeviceState(sizeof(diMouseState), &diMouseState)
            == DI_OK)
    {
      // right button flushes buffer
        if (diMouseState.rgbButtons[1] & 0x80)
        {
        if (!RClickHandled) FlushMouseBuffer();
        RClickHandled = TRUE;
        } 
      else RClickHandled = FALSE;
      // left button produces message
        if (diMouseState.rgbButtons[0] & 0x80)
      {
        if (!ClickHandled) TextToScreen(hMainWindow, "Left click!");
        ClickHandled = TRUE;  
      }  
      else ClickHandled = FALSE;

      // show absolute axes
      if ((MouseRB == IDC_ABSOLUTE) && 
         ((OldMouseX != diMouseState.lX) || 
          (OldMouseY != diMouseState.lY)))
      {
        sprintf(z, "X = %d, Y = %d", OldMouseX, OldMouseY);
        TextToScreen(hMainWindow, z);
        OldMouseX = diMouseState.lX;
        OldMouseY = diMouseState.lY;  
      }  

      // show relative axes
      else if ((MouseRB == IDC_RELATIVE) && 
               (diMouseState.lX || diMouseState.lY))  
      {
        sprintf(z, "X = %d, Y = %d", diMouseState.lX, diMouseState.lY);
        TextToScreen(hMainWindow, z);
      }
      return TRUE;  // success  
    } 
  return FALSE;
  }   // PollMouse()


/* **********************************************************
   PollKeyboard()
   Reads the keyboard state and acts on some keypresses
  ************************************************************* */  

BOOL PollKeyboard(void)
  {

  BYTE diKeys[256];

  if (lpdiKeyboard->GetDeviceState(256, &diKeys)
            == DI_OK)
    {
    if (diKeys[DIK_ESCAPE] & 0x80) 
          PostMessage(hMainWindow, WM_CLOSE, 0, 0);
    if (diKeys[DIK_F2] & 0x80) 
      {
      MakeAxesAbsolute(TRUE);
      MouseRB = IDC_ABSOLUTE;
      }
    return TRUE;  // success
    }
  return FALSE;
  } // PollKeyboard()

/* **********************************************************
   MakeAxesAbsolute()
   Changes the way the mouse reports its axes
   TRUE = absolute, FALSE = relative
  ************************************************************* */  

void MakeAxesAbsolute(BOOL Absolute)
  {
  HRESULT hres;
  DIPROPDWORD dipdw;

  if (MouseAcquired) lpdiMouse->Unacquire();
  dipdw.diph.dwSize = sizeof(DIPROPDWORD);
  dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
  dipdw.diph.dwObj = 0;
  dipdw.diph.dwHow = DIPH_DEVICE;
  dipdw.dwData = Absolute ? DIPROPAXISMODE_ABS : DIPROPAXISMODE_REL;
  hres = lpdiMouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
  if (hres != DI_OK) 
    OutputDebugString("Failed to set mouse axis mode.\n");
  if (MouseAcquired) lpdiMouse->Acquire();
  }


/* **********************************************************
   SetMouseAccess()
   Changes the cooperative level of the mouse
  ************************************************************* */  

void SetMouseAccess(int Access)
  {
  if (MouseAcquired) lpdiMouse->Unacquire();
  if(lpdiMouse->SetCooperativeLevel(hMainWindow,
         DISCL_NONEXCLUSIVE | Access) != DI_OK)
    {
    OutputDebugString("Failed to set cooperative level.\n");
    }
  if (MouseAcquired) lpdiMouse->Acquire();
  } // SetMouseAccess


/* **********************************************************
   FlushKbdBuffer()
   Flushes and displays the contents of the keyboard buffer
  ************************************************************* */  

HRESULT FlushKbdBuffer(void)
  {
  HRESULT            hres;
  DWORD              dwItems;
  char               szScan[7];
  char               szAge[10];
  char               szOutput[99];
  DWORD              k;
  DIDEVICEOBJECTDATA *lpdidod;

  dwItems = BUFFERCOUNT;
  hres = lpdiKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),
                              KbdBuffer, &dwItems, 0);
  if (!SUCCEEDED(hres))
    {
    TextToScreen(hMainWindow, "Error!");  
    return hres;
    }
  if (!dwItems) 
    TextToScreen(hMainWindow, "Keyboard buffer empty");
  else
    {
    ClearScreen(hMainWindow);
    if (hres == DI_BUFFEROVERFLOW)
       TextToScreen(hMainWindow, "Buffer overflow");
    for (k = 0; k < dwItems; k++)
      {
      lpdidod = &KbdBuffer[k];
      sprintf(szOutput, "%d", lpdidod->dwSequence);
      strcat(szOutput, ". Scan code ");
      sprintf(szScan, "0x%04X", lpdidod->dwOfs);
      strcat(szOutput, szScan);
    
      if (lpdidod->dwData & 0x80) 
        strcat(szOutput, " pressed ");
      else
        strcat(szOutput, " released ");
      sprintf(szAge, ". Age: %d ms", GetTickCount() - lpdidod->dwTimeStamp);
      strcat(szOutput, szAge);
 
      TextToScreen(hMainWindow, szOutput);
      }  // for k
    } // if (dwItems)
  return hres;
  }


/* **********************************************************
   FlushMouseBuffer()
   Flushes and displays the contents of the mouse buffer
  ************************************************************* */  
HRESULT FlushMouseBuffer(void)      
  {
  HRESULT  hres;
  DWORD    dwItems;
  char     szKind[99];
  char     szAxis[99];
  char     szAge[99];
  char     szOutput[99];
  DWORD    k;
  DIDEVICEOBJECTDATA *lpdidod;

  dwItems = BUFFERCOUNT;
  hres = lpdiMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),
                              MouseBuffer, &dwItems, 0);
  if (!SUCCEEDED(hres))
    {
    TextToScreen(hMainWindow, "Error!");  
    return hres;
    }
  if (dwItems) 
    {
    ClearScreen(hMainWindow);
    if (hres == DI_BUFFEROVERFLOW)
       TextToScreen(hMainWindow, "Buffer overflow!");
    for (k = 0; k < dwItems; k++)
      {
      lpdidod = &MouseBuffer[k];
      sprintf(szOutput, "%d", lpdidod->dwSequence);

      switch (lpdidod->dwOfs)
        {
          case DIMOFS_BUTTON0:
            strcpy(szKind, ". Button 0 ");
            break;

          case DIMOFS_BUTTON1:
            strcpy(szKind, ". Button 1 ");
            break;

          case DIMOFS_BUTTON2:
            strcpy(szKind, ". Button 2 ");
            break;

          case DIMOFS_BUTTON3:
            strcpy(szKind, ". Button 3 ");
            break;

          case DIMOFS_X:
            strcpy(szKind, ". X ");
            break;

          case DIMOFS_Y:
            strcpy(szKind, ". Y ");
            break;

          case DIMOFS_Z:
            strcpy(szKind, ". Z ");
            break;
        }  // switch


      if (((int)lpdidod->dwOfs == DIMOFS_BUTTON0) ||
          ((int)lpdidod->dwOfs == DIMOFS_BUTTON1) ||
          ((int)lpdidod->dwOfs == DIMOFS_BUTTON2) ||
          ((int)lpdidod->dwOfs == DIMOFS_BUTTON3))
        {
        if (lpdidod->dwData & 0x80) 
              strcat(szKind, "pressed ");
        else strcat(szKind, "released ");
        }
      else
        {
        strcat(szKind, "changed to ");
        sprintf(szAxis, "%d", lpdidod->dwData);
        strcat(szKind, szAxis);
        } 

      strcat(szOutput, szKind);
      sprintf(szAge, ". Age: %d ms", GetTickCount() - lpdidod->dwTimeStamp);
      strcat(szOutput, szAge);
 
      TextToScreen(hMainWindow, szOutput);
      }  // for k
    } // if dwItems
  return hres;
  }
