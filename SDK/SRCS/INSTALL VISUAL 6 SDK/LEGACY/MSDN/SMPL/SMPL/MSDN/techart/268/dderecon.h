/*
    dderecon.h

    Header file 

*/

#include <windows.h>
#include <ddeml.h>
#include "dialogs.h"

//
// Menu ids
//

#define IDM_EXIT        100
#define IDM_CONNECT     200
#define IDM_DISCONNECT  201
#define IDM_AUTO        300
#define IDM_SYSINFO     301

//
// general constants
//

#define MAXLISTLINES    100     // max list lines we keep
#define DDENAMESIZE     128

//
// Child windows 
//

#define IDC_LINKINFO    1
#define IDC_STATUS      2

//
// dderecon.c
//

extern char *szAppName;
extern HINSTANCE hInst;
extern DWORD dwDDEInst;
extern HWND hwndMain;
extern HWND hwndLinkInfo;
extern BOOL bAutoConnect;
extern BOOL bShowSysInfo;
extern PFNCALLBACK pfnDDECallback;

extern LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern HDDEDATA CALLBACK DDECallback(UINT wType, 
                              UINT wFmt, 
                              HCONV hConv,
                              HSZ hsz1, 
                              HSZ hsz2, 
                              HDDEDATA hData, 
                              DWORD dwData1, 
                              DWORD dwData2);

extern void cdecl Status(LPSTR lpFormat, ...);
extern void cdecl Error(LPSTR lpFormat, ...);

//
// Connect.c
//

extern BOOL ConnectDlg(HWND hwndParent, BOOL bSysInfo);

//
// Link.c
//

extern char szCurrentService[];
extern char szCurrentTopic[];
extern char szCurrentItem[];
extern HCONV hconvCurrent;

extern void EstablishLink(LPSTR lpszService, LPSTR lpszTopic, LPSTR lpszItem);

//
// init.c
//

extern BOOL InitFirstInstance(HANDLE hInstance);
extern BOOL InitCurrentInstance(HANDLE hInstance, int cmdShow);
extern void Terminate(void);


//
// status.c
//

extern HWND hwndStatus;

extern void cdecl Status(LPSTR lpFormat, ...);
extern void DrawStatusItem(HWND hWnd, LPDRAWITEMSTRUCT lpDI);
extern void MeasureStatusItem(HWND hWnd, LPMEASUREITEMSTRUCT lpMIS);
