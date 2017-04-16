
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/
//
// number of points for the polylines
//
#define NUMPOINTS 10
//
// ID numbers for pen list buttons
//
#define IDC_FIRST   (500)
#define IDC_LAST    (501)
#define IDC_PREV    (502)
#define IDC_NEXT    (503)
//
// node for linked list of pens
//
typedef struct tagPENRECORD  {
        DWORD      dwPenType;
        POINT      PtsToDraw[NUMPOINTS];
		DWORD      dwPenStyle;
		DWORD      dwJoinStyle;
		DWORD      dwEndCapStyle;
		DWORD      dwWidth;
		LOGBRUSH   lb;
		XFORM      xf;
		int        nPickPriority;
		struct     tagPENRECORD *next;
		struct     tagPENRECORD *prev;
} PENRECORD, *PPENRECORD, FAR *LPPENRECORD; 

#define MAXFILTERLEN 256

#if defined(MAIN)
RECT grWorkRect;
RECT grJoinCapRect;
RECT grButtonRect;
CHOOSECOLOR cc; 
COLORREF clr;
COLORREF aclrCust[256];
HCURSOR  hCur, hOldCur;
HBITMAP  hBitmap;
HBITMAP  hPatBitmap;
BOOL  bInHitArea;
UINT  uiNumPenRecs = 0;


HINSTANCE hInst;
HWND hwndMain;
char szAppName[] = "W32PEN";   
char szTitle[]   = "Win 32 Pens"; 
PENRECORD   PenRecord;
PPENRECORD  pPenList	= NULL;;
PPENRECORD	pPenCurrent = NULL;
HANDLE      hPenHeap	= NULL;
OPENFILENAME OpenFileName;
#else

extern RECT grWorkRect;
extern RECT grJoinCapRect;
extern CHOOSECOLOR cc; 
extern COLORREF clr;
extern COLORREF aclrCust[];
extern HCURSOR  hCur, hOldCur;
extern HBITMAP  hBitmap;
extern HBITMAP  hPatBitmap;
extern BOOL  bInHitArea;
extern UINT  uiNumPenRecs;

extern HINSTANCE hInst;
extern HWND hwndMain;
extern char szAppName[];   
extern char szTitle[]; 
extern PENRECORD	PenRecord;
extern PPENRECORD	pPenList;
extern PPENRECORD	pPenCurrent;	
extern HANDLE      	hPenHeap;
extern OPENFILENAME OpenFileName;

#endif


BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK About  (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK JunkProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SetPenAttr(HWND hwndDlg, UINT uMsg, UINT wParam, LONG lParam);
LRESULT CALLBACK XformDlgProc(HWND hwndDlg, UINT uMsg, UINT wParam, LONG lParam);
void DrawRndLine(HDC hdc, PPENRECORD pPenRecord);
void DrawJoinCap(HDC hdc, PPENRECORD pPenRecord);
BOOL DrawWorkSpace(HWND hwnd, HDC hdc);
BOOL CenterWindow (HWND hwndChild, HWND hwndParent);
BOOL SaveAs(HWND hWnd);
BOOL ClearWorkAreas(HWND hWnd, LPRECT lprcWork, LPRECT lprcJoinCap);
void ComposeXForm(PXFORM xf1, PXFORM xf2, PXFORM xfProd);


HPEN GetPen(PPENRECORD pPenRecord);
