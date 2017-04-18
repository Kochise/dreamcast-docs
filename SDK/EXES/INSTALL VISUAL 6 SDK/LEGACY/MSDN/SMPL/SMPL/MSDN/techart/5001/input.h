/*==========================================================================
 *
 *  Copyright (C) 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       input.h
 *  Content:    input routines include file
 *
 *
 ***************************************************************************/

#ifndef _INPUT_H
#define _INPUT_H

#include <dinput.h>

BOOL            InitInput(void);
BOOL CALLBACK   DI_EnumDevProc(LPDIDEVICEINSTANCE lpdidi, LPVOID lpv);
void            CleanupInput(void);
BOOL            ReacquireInputDevices(void);

BOOL            PollMouse(void);
BOOL            PollKeyboard(void);
void            MakeAxesAbsolute(BOOL Absolute);
void            SetMouseAccess(int Access);
HRESULT         FlushKbdBuffer(void);
HRESULT         FlushMouseBuffer(void);     

#endif // _INPUT_H



