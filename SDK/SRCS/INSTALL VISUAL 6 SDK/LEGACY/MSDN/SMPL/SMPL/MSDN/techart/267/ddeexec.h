/*
    ddeexec.h

    Header file 

*/

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "stddde.h"

//
// Menu ids
//

#define IDM_EXIT        100

//
// Child windows 
//

#define IDC_STATUS      2
#define IDC_FUN         3

//
// DDE string names for our own service, topics and items
//

#define SZ_SERVICENAME  "DdeExec"
#define SZ_DRAWRECT     "DrawRect"

//
// ddeexec.c
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
extern WORD MyFormats[];

extern void SetupDDE(HINSTANCE hInstance);
extern HDDEDATA MakeCFText(UINT wFmt, LPSTR lpszStr, HSZ hszItem);

//
// execfns.c
//

extern BOOL FAR EllipseFn(PDDETOPICINFO pTopic,
						 LPSTR pszResult,
						 UINT uiResultSize,
						 UINT uiNargs,
						 LPSTR FAR *ppArgs);
extern BOOL FAR RectangleFn(PDDETOPICINFO pTopic,
						 LPSTR pszResult,
						 UINT uiResultSize,
						 UINT uiNargs,
						 LPSTR FAR *ppArgs);
extern BOOL FAR LineFn(PDDETOPICINFO pTopic,
						 LPSTR pszResult,
						 UINT uiResultSize,
						 UINT uiNargs,
						 LPSTR FAR *ppArgs);
extern BOOL FAR EraseFn(PDDETOPICINFO pTopic,
						 LPSTR pszResult,
						 UINT uiResultSize,
						 UINT uiNargs,
						 LPSTR FAR *ppArgs);
extern BOOL FAR PenFn(PDDETOPICINFO pTopic,
						 LPSTR pszResult,
						 UINT uiResultSize,
						 UINT uiNargs,
						 LPSTR FAR *ppArgs);
extern BOOL FAR BrushFn(PDDETOPICINFO pTopic,
						 LPSTR pszResult,
						 UINT uiResultSize,
						 UINT uiNargs,
						 LPSTR FAR *ppArgs);
extern BOOL FAR TextFn(PDDETOPICINFO pTopic,
						 LPSTR pszResult,
						 UINT uiResultSize,
						 UINT uiNargs,
						 LPSTR FAR *ppArgs);
