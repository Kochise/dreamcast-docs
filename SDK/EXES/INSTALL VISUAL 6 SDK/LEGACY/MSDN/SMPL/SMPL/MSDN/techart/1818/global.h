/*
    global.h

    Main application header file

*/

#include <windows.h>
#include <stdlib.h>
#include <memory.h>

//
// resource ids
//

#define IDI_APP             10

//
// Menu ids
//

#define IDM_EXIT			105

#define IDM_PEEKLOOP		200
#define IDM_TIMER			201
#define IDM_HOG 			202
#define IDM_HOGSLEEP		203
#define IDM_HOGPEEK 		204
#define IDM_HOGTHREAD		205
#define IDM_RESET			206

#define ID_HOGTHREADDONE	WM_USER+999

//
// Child window ids
//

#define IDC_FLICKER         1
#define IDC_NOFLICKER       2

//
// global data
//

char *szAppName;                    // App name
HINSTANCE hAppInstance;             // app instance
HWND hwndMain;                      // main window handle
TEXTMETRIC tmSysFont;               // system font metrics
HANDLE hAccTable;                   // accelerator table
HWND hwndFilter;
HWND hwndNoFilter;
UINT uiTimer;
HFONT hfntBig;

//
// main.c
//

extern LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, UINT uParam, LPARAM lParam);

//
// init.c
//

extern BOOL Init(HANDLE hInstance, int cmdShow);
extern void Terminate(void);

//
// flicker.c
//

extern LRESULT CALLBACK FlickerWndProc(HWND hWnd, UINT msg, UINT uParam, LPARAM lParam);

//
// noflick.c
//

extern LRESULT CALLBACK NoFlickerWndProc(HWND hWnd, UINT msg, UINT uParam, LPARAM lParam);
void NoFlickUpdate(HWND hWnd);
