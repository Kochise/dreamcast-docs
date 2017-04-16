#ifndef _INC_PICK_DLL
#define _INC_PICK_DLL
// Internal declarations for the Picker DLL

#include <windows.h>
#include <windowsx.h>
#include "picker.h"
#include "pick_dlg.h"
#include "pick_mem.h"

extern HINSTANCE hInst ;


BOOL DLL_ENT Picker_OldDlgProc(HWND hwndDlg, UINT msg, 
											WPARAM wParam, LPARAM lParam);
										
//DLL Stuff
void DLL_EXP WEP(int bSysExit);
int  DLL_EXP LibMain (HANDLE hInstance, WORD wDataSeg, WORD wHeapSize,
							 DWORD ignore);
#endif // !_INC_PICK_DLL
