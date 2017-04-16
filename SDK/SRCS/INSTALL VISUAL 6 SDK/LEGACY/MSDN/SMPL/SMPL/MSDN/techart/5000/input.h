/*==========================================================================
 *
 *  Copyright (C) 1995-1996 Microsoft Corporation. All Rights Reserved.
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
BOOL            ReacquireMouse(void);

#endif // _INPUT_H



