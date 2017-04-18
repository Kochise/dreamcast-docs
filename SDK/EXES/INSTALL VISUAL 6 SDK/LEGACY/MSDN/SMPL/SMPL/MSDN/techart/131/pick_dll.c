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

HINSTANCE hInst ;

int DLL_EXP LibMain (HANDLE hInstance, WORD wDataSeg, WORD wHeapSize,
							 DWORD ignore)
{
	hInst = hInstance ;
	
	if (wHeapSize != 0)
		UnlockData(0);	
	return TRUE ;
}

void DLL_EXP WEP(int bSysExit)
{
	return ;
}
