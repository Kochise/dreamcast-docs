// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.

#include "pick_dll.h"
// Pick_Mem :
//
// Purpose  :
//		This module manages the local memory structure for the Picker DLL.
//
//

NP_GLOBAL_PICKER GLOBAL allocMem(HWND hwnd,LP_PICKER_STRUCT lpPicker)
{
	// Allocs Fixed memory so return is a near pointer.
	NP_GLOBAL_PICKER g = (NP_GLOBAL_PICKER)LocalAlloc(LPTR, sizeof(GLOBAL_PICKER));
	g->lpPicker = lpPicker ;
	SetProp(hwnd,"!",(HANDLE)g);
	return g ;
}

// Memory management functions
NP_GLOBAL_PICKER GLOBAL getMem(HWND hwnd)
{
	return (NP_GLOBAL_PICKER) GetProp(hwnd,"!");
}

void GLOBAL freeMem(HWND hwnd)
{
	NP_GLOBAL_PICKER g =	(NP_GLOBAL_PICKER) RemoveProp(hwnd,"!");
	if (g)
	{
		LocalFree((HLOCAL)g);
	}
}
