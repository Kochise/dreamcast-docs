/*****************************************************************************
  Name : D3DTController.h
  Date : May 1999
  Platform : ANSI compatible
 
  Description : Header file of D3DTController.c
				Contains structure definitions and prototypes 
				of all functions in D3DTController.c

  
  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#include <windows.h>

#ifndef __INPUT_H__
#define __INPUT_H__

//******************************************************************************
// Function prototypes
//******************************************************************************

BOOL InitDirectInput(HWND hWnd, HINSTANCE hInstance);
void ReleaseDirectInput(void);

BOOL UpdateJoystick(void);

BOOL IsAKey(void);
BOOL IsBKey(void);
BOOL IsXKey(void);
BOOL IsYKey(void);

BOOL IsLFKey(void);
BOOL IsRFKey(void);

BOOL IsSTARTKey(void);
BOOL IsUPKey(void);
BOOL IsDOWNKey(void);
BOOL IsLEFTKey(void);
BOOL IsRIGHTKey(void);

LONG GetAnalogX(void);
LONG GetAnalogY(void);

#endif //__INPUT_H__
