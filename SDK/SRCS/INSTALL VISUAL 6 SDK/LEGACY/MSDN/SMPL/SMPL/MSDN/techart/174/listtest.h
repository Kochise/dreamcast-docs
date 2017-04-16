#include <windows.h>

#include <windowsx.h>
#include "vlist.h"

#ifndef RC_INVOKED
#include <string.h>
#include <stdio.h>
#include <io.h>
#include "stdlib.h"
#endif

#define IDM_DIALOG                1000

#define IDS_ERR_REGISTER_CLASS   1
#define IDS_ERR_CREATE_WINDOW    2

char szString[128];

char szAppName[20];
HWND hInst;          
HWND hWndMain;       

void cwCenter(HWND, int);

LONG FAR PASCAL WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL FAR PASCAL DIALOGSMsgProc(HWND, UINT, WPARAM, LPARAM);
int nCwRegisterClasses(void);
void CwUnRegisterClasses(void);
