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

#define IDM_EXIT            0x0105

#define IDM_DEBUG0          0x0800
#define IDM_DEBUG1          (IDM_DEBUG0+1)
#define IDM_DEBUG2          (IDM_DEBUG0+2)
#define IDM_DEBUG3          (IDM_DEBUG0+3)
#define IDM_DEBUG4          (IDM_DEBUG0+4)
#define IDM_DEBUG_DIRTY     (IDM_DEBUG0+5)

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
HWND hwndFlicker;
HWND hwndNoFlicker;
UINT uiTimer;
HFONT hfntBig;

//
// main.c
//

extern LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern UINT cdecl Message(UINT uiBtns, LPSTR lpFormat, ...) ;

//
// init.c
//

extern BOOL InitFirstInstance(HANDLE hInstance);
extern BOOL InitCurrentInstance(HANDLE hInstance, LPSTR lpszCmdLine, int cmdShow);
extern void Terminate(void);

//
// flicker.c
//

extern LRESULT CALLBACK FlickerWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//
// noflick.c
//

extern LRESULT CALLBACK NoFlickerWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
