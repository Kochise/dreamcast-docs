/*
    stocksrv.h

    Header file 

*/

#include <windows.h>
#include "stddde.h"

//
// Menu ids
//

#define IDM_EXIT        100
#define IDM_PAUSE       200
#define IDM_COPY        300
#define IDM_BREAD       400
#define IDM_MILK        401
#define IDM_MSFT        402

//
// Child windows 
//

#define IDC_STATUS      2

//
// stocksrv.c
//

extern HINSTANCE hInst;
extern HWND hwndMain;
extern char *szAppName;

extern LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//
// init.c
//

extern BOOL Init(HANDLE hInstance, int cmdShow);

//
// status.c
//

extern HWND hwndStatus;

extern void cdecl Status(LPSTR lpFormat, ...);
extern void DrawStatusItem(HWND hWnd, LPDRAWITEMSTRUCT lpDI);
extern void MeasureStatusItem(HWND hWnd, LPMEASUREITEMSTRUCT lpMIS);

//
// dde.c
//

extern DWORD dwDDEInst;
extern BOOL bMilkActive;
extern BOOL bBreadActive;
extern BOOL bMSFTActive;

extern void SetupDDE(HINSTANCE hInstance);
extern void UpdateDDEInfo(void);
extern void CopyDDEInfo(HWND hWnd);
extern void ChangeActiveItemStatus(WPARAM wParam);
