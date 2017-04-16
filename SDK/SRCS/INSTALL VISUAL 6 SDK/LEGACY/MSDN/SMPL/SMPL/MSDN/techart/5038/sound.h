/*==========================================================================
 *
 *  Copyright (C) 1995-1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       sound.h
 *  Content:    DirectSound routines include file
 *
 ***************************************************************************/


#include <dsound.h>

BOOL  InitSound(HWND hwnd, HINSTANCE hinst);
void  CleanupSound(void);
void  Blow(int pan);
void  Boing(BOOL ToggleOn);


