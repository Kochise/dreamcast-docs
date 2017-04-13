/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       input.c
 *  Content:    DirectInput functionality for Multi-player duel
 *
 *
 ***************************************************************************/


#include "input.h"
#include "gameproc.h"

extern HINSTANCE				ghinst;				// program instance
extern HWND                     ghWndMain;              // app window handle

static LPDIRECTINPUT			lpdi;				// DirectInput interface
static LPDIRECTINPUTDEVICE      lpdiKeyboard;           // keyboard device interface
static BOOL						fKeybdAcquired;		// has the keyboard been acquired?

extern DWORD					gdwKeys;			// gameplay keys

/*
*
* InitInput
*
* Initialize DirectInput objects & devices
*
*/
BOOL InitInput(void)
{
	GUID		guid = GUID_SysKeyboard;
   HRESULT  hRes;

	// try to create di object (DIRECTINPUT_VERSION == DX5)
	if(DirectInputCreate(ghinst, DIRECTINPUT_VERSION, &lpdi, NULL) != DI_OK)
	{
      // creation failed, try DX3 compatibility
      if(DirectInputCreate(ghinst, 0x0300, &lpdi, NULL) != DI_OK)
      {
         ShowError(IDS_DINPUT_ERROR_DIC);
         return FALSE;
      }
	}


	// try to create keyboard device
        if(lpdi->lpVtbl->CreateDevice(lpdi, &guid, &lpdiKeyboard, NULL) !=DI_OK)
	{
		ShowError(IDS_DINPUT_ERROR_CD);
		return FALSE;
	}

        // Tell DirectInput that we want to receive data in keyboard format
        if (lpdiKeyboard->lpVtbl->SetDataFormat(lpdiKeyboard, &c_dfDIKeyboard) != DI_OK)
        {
                ShowError(IDS_DINPUT_ERROR_DF);
                return FALSE;
        }

        // set cooperative level
        if(lpdiKeyboard->lpVtbl->SetCooperativeLevel(lpdiKeyboard, ghWndMain,
                         DISCL_NONEXCLUSIVE | DISCL_FOREGROUND) != DI_OK)
	{
		ShowError(IDS_DINPUT_ERROR_SP);
		return FALSE;
        }

	// try to acquire the keyboard
   hRes = lpdiKeyboard->lpVtbl->Acquire(lpdiKeyboard);
   if(SUCCEEDED(hRes))
   {
      // keyboard was acquired
      fKeybdAcquired = TRUE;
	}
   else
   {
      // keyboard was NOT acquired
      fKeybdAcquired = FALSE;
   }

	// if we get here, all objects were created successfully
	return TRUE;	
		
}


/*
*
* DI_ReadKeys
*
* Use DirectInput to read game-play keys
*
*/
void DI_ReadKeys(void)
{
	BYTE rgbKeybd[256];
   HRESULT hRes;

   hRes = lpdiKeyboard->lpVtbl->GetDeviceState(lpdiKeyboard, sizeof(rgbKeybd), rgbKeybd);
   if(hRes != DI_OK)
	{
      if(hRes == DIERR_INPUTLOST)
      {
         // we lost control of the keyboard, reacquire
         fKeybdAcquired = FALSE;
         if(SUCCEEDED(lpdiKeyboard->lpVtbl->Acquire(lpdiKeyboard)))
         {
            fKeybdAcquired = TRUE;
         }
      }

      // failed to read the keyboard, just return
		return;
	}

	// reset key states
	gdwKeys = gdwKeys ^ gdwKeys;

	// check & update key states
	if(rgbKeybd[DIK_NUMPAD5] & 0x80)
		gdwKeys |= KEY_STOP;

	if((rgbKeybd[DIK_NUMPAD2] & 0x80) || (rgbKeybd[DIK_DOWN] & 0x80))
		gdwKeys |= KEY_DOWN;

	if((rgbKeybd[DIK_NUMPAD4] & 0x80) || (rgbKeybd[DIK_LEFT] & 0x80))
		gdwKeys |= KEY_LEFT;

	if((rgbKeybd[DIK_NUMPAD6] & 0x80) || (rgbKeybd[DIK_RIGHT] & 0x80))
		gdwKeys |= KEY_RIGHT;

	if((rgbKeybd[DIK_NUMPAD8] & 0x80) || (rgbKeybd[DIK_UP] & 0x80))
		gdwKeys |= KEY_UP;

	if(rgbKeybd[DIK_SPACE] & 0x80)
		gdwKeys |= KEY_FIRE;

}

/*
*
* CleanupInput
*
* Cleans up DirectInput objects
*
*/
void CleanupInput(void)
{
	if(fKeybdAcquired)
	{
		lpdiKeyboard->lpVtbl->Unacquire(lpdiKeyboard);
		fKeybdAcquired = FALSE;
	}

	if(lpdiKeyboard != NULL)
		lpdiKeyboard->lpVtbl->Release(lpdiKeyboard);

	if(lpdi!= NULL)
		lpdi->lpVtbl->Release(lpdi);
	
}


/*
*
* ReacquireInputDevices
*
* Reacquires DirectInput devices as needed
*
*/
BOOL ReacquireInputDevices(void)
{
	// try to acquire the keyboard
        if(lpdiKeyboard != NULL)
        {
                lpdiKeyboard->lpVtbl->Acquire(lpdiKeyboard);
	     }
        else
        {
                // keyboard device has not been created.
                fKeybdAcquired = FALSE;
                return FALSE;
        }

        // if we get here, we are acquired again
        fKeybdAcquired = TRUE;
        return TRUE;
}












