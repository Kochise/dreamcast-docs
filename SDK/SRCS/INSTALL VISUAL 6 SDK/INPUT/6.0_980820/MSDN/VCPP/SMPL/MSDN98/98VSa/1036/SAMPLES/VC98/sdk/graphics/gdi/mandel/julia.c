/******************************Module*Header*******************************\
* Module Name: julia.c
*
* Main module for the Mandelbrot Dream
*       contains almost everything; windows procedure + misc stuff
*
* Created: 24-Oct-1991 18:34:08
*
* Copyright (C) 1993-1997 Microsoft Corporation
*
* The Mandelbrot Dream serves to demonstrate the GDI and USER
* functionalities in the setting of fractals.
*
* The Mandelbrot Dream provides the following functions:
*       1.  Drawing the Mandelbrot set and the corresponding julia set
*       2.  Zooming into any of the set
*       3.  MDI fractal drawing windows
*       4.  Floating Point Math/Fix Point Math
*       5.  Shifting color table entries
*       6.  Changing palette entries and animating palatte aka color cycling
*       7.  Loading/Saving bitmap created with special effect
*       8.  Changing bitmap color with flood fill
*       9.  Boundary tracing and creating a clip region out of it for
*           creating special effect
*      10.  Enumerate printers for printing
*      11.  Load RLE (or convert .bmp files to RLE) for playing in viewer
*      12.  Save the RLE in memory to disk.
*
* Note: Users can now draw and saves the julia sets on disk as bmps in
*       the Julia windows.  These bitmaps can then be read into the memory
*       (and converted to RLE format) one by one for displaying in sequence
*       in the viewer window.  Eg Load the julia.rle in the viewer window
*       and select the play or play continuously menu item.     02-Jan-1993
*
* Note2: The fix point math in this sample makes use of the LargeInteger
*        64 bit math library.
*
* Dependencies:
*
*       none
*
\**************************************************************************/
#include <windows.h>
#include <stdlib.h>
#include <commdlg.h>
#include <stdarg.h>
#include <math.h>
#include <stdio.h>
#include <shellapi.h>
#include "julia.h"

//
// For T1 to create all pens in advance.  This is not a good approach
// because pens are per thread basis.  The drawing threads won't be able
// to use them if they are not created in their threads.    18-Sep-1992
//
//#define THRDONE

#define CYCLETHRD

#define PRTTHRD
#define NEWPRTAPI

#ifndef DEBUG
   #undef OutputDebugString
   #define OutputDebugString(LPCSTR)
#endif

//
// Forward declarations.
//
BOOL InitializeApp            (INT*);
LONG APIENTRY MainWndProc     (HWND, UINT, DWORD, LONG);
LONG APIENTRY ChildWndProc    (HWND, UINT, DWORD, LONG);
BOOL CALLBACK About           (HWND, UINT, DWORD, LONG);
LONG APIENTRY TextWndProc     (HWND, UINT, DWORD, LONG);
LONG APIENTRY JuliaWndProc    (HWND, UINT, DWORD, LONG);
LONG APIENTRY ViewerWndProc   (HWND, UINT, DWORD, LONG);
LONG APIENTRY ViewSurfWndProc (HWND, UINT, DWORD, LONG);
BOOL APIENTRY SuspendDrawThrd (HWND, LONG);
BOOL APIENTRY ResumeDrawThrd  (HWND, LONG);
BOOL StartDraw       (PINFO);
BOOL StartDrawFix    (PINFO);
BOOL StartDraw2      (PINFO);
BOOL StartMandelbrot (PINFO);
BOOL StartMandelbrotFix (PINFO);
HBITMAP SaveBitmap   (HWND, HPALETTE);
void DrawBitmap      (HDC, PINFO, int, int, int, int);
BOOL bDrawDIB        (HDC, PINFO, int, int, int, int);
LONG lMul(LONG, LONG);
LONG lDiv(LONG, LONG);
PINFO pGetInfoData(HWND);
BOOL bReleaseInfoData(HWND);
BOOL bCheckMutexMenuItem(PINFO, HMENU, UINT);
VOID vChkMenuItem(PINFO, HMENU, UINT);
BOOL bInitInfo(PINFO);
BOOL bResetGlobal(VOID);
HBRUSH hBrCreateBrush(HDC, DWORD);
BOOL bPrintBmp(PPRTDATA);
BOOL bStoreRleFile(HDC, PINFO, PSTR);
BOOL bFreeRleFile(PINFO);
BOOL bPlayRle(PINFO);
BOOL bSaveRleFile(HDC, PINFO, PSTR);
BOOL bPlayRleCont2(PINFO);
BOOL bSelectDIBPal(HDC, PINFO, LPBITMAPINFO, BOOL);
HBITMAP DIBfromDDB(HDC, HBITMAP, PINFO);


//
// Global variable declarations.
//

HPEN   hpnRed;
HPEN   hpnBlack;
HPEN   hpnGreen;
INT    giPen = 0;

HANDLE ghModule;
HWND   ghwndMain = NULL;
HWND   ghwndClient = NULL;
HANDLE ghAccel;

HMENU  hMenu, hChildMenu, hViewMenu;
HMENU  hViewSubOne, hSubMenuOne, hSubMenuThree;
HMENU  hPrinterMenu;

CHAR   gszFile[20];
CHAR   gszMapName[20];
char   gtext[256];

BOOL   gFloat = TRUE;
LONG   gStep = 1;
LONG   gIteration = 500;
BOOL   gbStretch = TRUE;
INT    giStretchMode = COLORONCOLOR;
INT    giDmOrient = DMORIENT_PORTRAIT;
INT    giNPrinters = 0;

HPALETTE        ghPal, ghPalOld;

double xFrom, xTo, yFrom, yTo, c1, c2;
LONG   lxFrom, lxTo, lyFrom, lyTo, lc1, lc2;




/******************************Public*Routine******************************\
*
* WinMain
*
\**************************************************************************/

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)
{
    MSG    msg;

    ghModule = GetModuleHandle(NULL);
    if (!InitializeApp(&giPen)) 
	{
		OutputDebugString("memory: InitializeApp failure!");
		return 0;
    }

    if (!(ghAccel = LoadAccelerators (ghModule, MAKEINTRESOURCE(ACCEL_ID))))
		OutputDebugString("memory: Load Accel failure!");


    while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator( ghwndMain, ghAccel, &msg) &&
		    !TranslateMDISysAccel( ghwndClient, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
    }


    DeleteObject(ghPal);

    return 1;

    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
}


/***************************************************************************\
* InitializeApp
*
\***************************************************************************/

BOOL InitializeApp(INT *piPen)
{
    WNDCLASS wc;
    HDC      hDC;

#ifdef THRDONE
    INT      iNumClr;
#endif

    wc.style            = CS_OWNDC;
    wc.lpfnWndProc      = (WNDPROC)MainWndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = sizeof(LONG);
    wc.hInstance        = ghModule;
    wc.hIcon            = LoadIcon(ghModule, MAKEINTRESOURCE(APPICON));
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH)(COLOR_APPWORKSPACE);
    wc.lpszMenuName     = "MainMenu";
    wc.lpszClassName    = "MandelClass";

    if (!RegisterClass(&wc))
	return FALSE;

    wc.lpfnWndProc      = (WNDPROC)ChildWndProc;
    wc.hIcon            = LoadIcon(ghModule, MAKEINTRESOURCE(APPICON));
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = "ChildClass";

    if (!RegisterClass(&wc))
	return FALSE;

    wc.lpfnWndProc      = (WNDPROC)ViewerWndProc;
    wc.hIcon            = LoadIcon(ghModule, MAKEINTRESOURCE(VIEWICON));
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = "ViewerClass";

    if (!RegisterClass(&wc))
	return FALSE;

    wc.style            = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = (WNDPROC)TextWndProc;
    wc.hIcon            = NULL;
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH)(COLOR_BTNSHADOW);
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = "Text";

    if (!RegisterClass(&wc))
	    return FALSE;

    wc.style            = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = (WNDPROC)JuliaWndProc;
    wc.hIcon            = NULL;

    //
    // Nope.  Can't have this, screw up my Paint Can cursor
    //
    //wc.hCursor          = LoadCursor(NULL, IDC_ARROW);

    wc.hCursor          = NULL;
    wc.hbrBackground    = (HBRUSH)(COLOR_BACKGROUND);
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = "Julia";

    if (!RegisterClass(&wc))
	    return FALSE;

    wc.style            = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = (WNDPROC)ViewSurfWndProc;
    wc.hIcon            = NULL;
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH)(COLOR_BACKGROUND);
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = "View";

    if (!RegisterClass(&wc))
	    return FALSE;


    //
    // Notice, submenu is zero-based
    //
    hMenu       = LoadMenu(ghModule, "MainMenu");
    hChildMenu  = LoadMenu(ghModule, "ChildMenu");
    hViewMenu   = LoadMenu(ghModule, "ViewMenu");
    hViewSubOne = GetSubMenu(hViewMenu, 1);
    hSubMenuOne = GetSubMenu(hMenu, 1);
    hSubMenuThree = GetSubMenu(hChildMenu, 8);
    hPrinterMenu = GetSubMenu(hChildMenu, 7);

    //
    // Disable color-cycling for display devices that does not support
    // palette like the VGA.  As as 29-May-1992, the MIPS display driver
    // is the only one that supports palette
    //
    hDC = GetDC(NULL);
    if (!((GetDeviceCaps(hDC, RASTERCAPS)) & RC_PALETTE)) {
	EnableMenuItem(hChildMenu, MM_CYCLE, MF_GRAYED);
    }

#ifdef THRDONE

    if ((iNumClr = iCreatePenFrPal(hDC, NULL, 0, &ghPal)) != 0) 
	{
		sprintf( gtext,"iNumClr = %d\n", iNumClr);
		OutputDebugString( gtext);

		if ((pInfo->prghPen = (PVOID*) GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, sizeof(HPEN)*iNumClr)) == NULL) 
		    OutputDebugString ("Failed in Memory Allocation for pInfo->prghPen!");
		else 
			if ((*piPen = iCreatePenFrPal(hDC, pInfo->prghPen, 0, &ghPal)) == 0)
				OutputDebugString("Failed in creating pen!");
    }

#endif
    ReleaseDC(NULL, hDC);

    ghwndMain = CreateWindowEx(0L, "MandelClass", 
							   GetStringRes (IDS_MANDEL_DREAM),

	    WS_OVERLAPPED   | WS_CAPTION     | WS_BORDER       |
	    WS_THICKFRAME   | WS_MAXIMIZEBOX | WS_MINIMIZEBOX  |
	    WS_CLIPCHILDREN | WS_VISIBLE     | WS_SYSMENU,
	    80, 70, 550, 400 /* 550 */,
	    NULL, hMenu, ghModule, NULL);

    if (ghwndMain == NULL)
	return FALSE;

    bInitPrinter(ghwndMain);

    SetWindowLong(ghwndMain, GWL_USERDATA, 0L);

    SetFocus(ghwndMain);    /* set initial focus */

    PostMessage(ghwndMain, WM_COMMAND, MM_MANDEL, 0L);
    PostMessage(ghwndMain, WM_COMMAND, MM_CREATE_MANDEL_THREAD, 0L);

    return TRUE;
}


/******************************Public*Routine******************************\
*
* MainWndProc
*
\**************************************************************************/

long APIENTRY MainWndProc(
    HWND hwnd,
    UINT message,
    DWORD wParam,
    LONG lParam)
{
    static int         iJuliaCount=1;
    static int         iMandelCount=1;
    static int         iViewerCount=1;
    CLIENTCREATESTRUCT clientcreate;
    HWND               hwndChildWindow;
    static FARPROC     lpfnSuspendThrd, lpfnResumeThrd;


    switch (message) {

      case WM_CREATE:
	SetWindowLong(hwnd, 0, (LONG)NULL);

	clientcreate.hWindowMenu  = hSubMenuOne;
	clientcreate.idFirstChild = 1;

	ghwndClient = CreateWindow("MDICLIENT", NULL,
				    WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
				    0,0,0,0,
				    hwnd, NULL, ghModule, (LPVOID)&clientcreate);
	lpfnSuspendThrd = (FARPROC)MakeProcInstance (SuspendDrawThrd, ghModule);
	lpfnResumeThrd  = (FARPROC)MakeProcInstance (ResumeDrawThrd, ghModule);

	return 0L;

      case WM_DESTROY: {
	bCleanupPrinter();
	PostQuitMessage(0);
	return 0L;
      }

      //
      // Wait! User is going to zero out our app's visible region.  This
      // is going to mess up our drawing (we are not keeping any shadow
      // bitmap in this version yet.) So, let's suspend our drawing thread
      // first before user does that.  We will resume after user is done.
      //
      case WM_SYSCOMMAND: {
	LONG        lResult;

	//
	// We'll enumerate our children and suspend their drawing thread.
	//
	EnumChildWindows(ghwndClient, (WNDENUMPROC)lpfnSuspendThrd, lParam);

	//
	// Now, let user does it supposed to do
	//
	lResult = DefFrameProc(hwnd,  ghwndClient, message, wParam, lParam);

	//
	// User's done, we'll resume the suspended threads in our children
	//
	EnumChildWindows(ghwndClient, (WNDENUMPROC)lpfnResumeThrd, lParam);

	return lResult;
	break;
      }
#if 0
      //
      // Our window's size is going to change, we'll make sure the new
      // window is a square.
      //
      case WM_WINDOWPOSCHANGING: {
	    PWINDOWPOS pWndPos;
	    RECT       rect;
	    LONG       lcx, lcy;

	    GetWindowRect(hwnd, &rect);
	    lcx = rect.right-rect.left;
	    lcy = rect.bottom-rect.top;
	    pWndPos = (PWINDOWPOS)lParam;
	    if ((pWndPos->cy > lcy) || (pWndPos->cx > lcx))
		pWndPos->cx =  pWndPos->cy =
		   ((pWndPos->cx > pWndPos->cy) ? pWndPos->cy : pWndPos->cx);
	    else if ((pWndPos->cy < lcy) || (pWndPos->cx < lcx))
		     pWndPos->cx =  pWndPos->cy =
			((pWndPos->cx > pWndPos->cy) ? pWndPos->cy : pWndPos->cx);
	    break;
      }
#endif

      case WM_COMMAND:

	switch (LOWORD(wParam)) {
	    case IDM_TILE:
		SendMessage(ghwndClient, WM_MDITILE, 0L, 0L);
		return 0L;
	    case IDM_CASCADE:
		SendMessage(ghwndClient, WM_MDICASCADE, 0L, 0L);
		return 0L;
	    case IDM_ARRANGE:
		SendMessage(ghwndClient, WM_MDIICONARRANGE, 0L, 0L);
		return 0L;

	    //
	    // Create Julia or Mandelbrot set
	    //
	    case MM_JULIA:
	    case MM_MANDEL: {
		HANDLE hInfo;
		PINFO  pInfo;
		MDICREATESTRUCT mdicreate;

		hInfo = LocalAlloc(LHND, (WORD) sizeof(INFO));
		if (hInfo == NULL) 
		{
		    OutputDebugString("Failed to Allocate Info!");
		    return 0L;
		}
		if ((pInfo = (PINFO)LocalLock(hInfo)) == NULL) 
		{
		    OutputDebugString("Failed in LocalLock, hInfo");
		    return 0L;
		}

		bInitInfo(pInfo);
		wsprintf((LPSTR) &(pInfo->CaptionBarText),
			 (LOWORD(wParam) == MM_JULIA) ? 
			 GetStringRes (IDS_JULIA): 
			 GetStringRes (IDS_MANDELBROT),
			 (LOWORD(wParam) == MM_JULIA) ? iJuliaCount : iMandelCount);
		if (LOWORD(wParam) == MM_JULIA) {
		    c1 = 0.360284;
		    c2 = 0.100376;
		    lc1 = 738;          //.3603515
		    lc2 = 206;          //.1005859
		    pInfo->bMandel = FALSE;
		} else {
		    pInfo->bMandel = TRUE;
		}

		//
		// Fill in the MDICREATE structure for MDI child creation
		//
		mdicreate.szClass = "ChildClass";
		mdicreate.szTitle = (LPTSTR)&(pInfo->CaptionBarText);
		mdicreate.hOwner  = ghModule;
		mdicreate.x       =
		mdicreate.y       = CW_USEDEFAULT;
		mdicreate.cx      = 300;
		mdicreate.cy      = 300;
		mdicreate.style   = 0L;
		mdicreate.lParam  = (LONG) hInfo;

		/*Create Child Window*/
		hwndChildWindow =
		    (HANDLE) SendMessage(ghwndClient, WM_MDICREATE,
				0L,
				(LONG)(LPMDICREATESTRUCT)&mdicreate);

		if (hwndChildWindow == NULL) 
		{
		    OutputDebugString ("Failed in Creating Child Window");
		    return 0L;
		}

		(LOWORD(wParam) == MM_JULIA) ? iJuliaCount++ : iMandelCount++ ;
		LocalUnlock(hInfo);
		return ((LONG)hwndChildWindow);
	    }

	    case MM_RLEVIEWER: {
		HANDLE hInfo;
		PINFO  pInfo;
		MDICREATESTRUCT mdicreate;

		hInfo = LocalAlloc(LHND, (WORD) sizeof(INFO));
		if (hInfo == NULL) 
		{
		    OutputDebugString ("Failed to Allocate Info!");
		    return 0L;
		}
		if ((pInfo = (PINFO)LocalLock(hInfo)) == NULL) 
		{
		    OutputDebugString ("Failed in LocalLock, hInfo");
		    return 0L;
		}

		bInitInfo(pInfo);
		wsprintf((LPSTR) &(pInfo->CaptionBarText), GetStringRes (IDS_VIEWER), iViewerCount );

		//
		// Fill in the MDICREATE structure for MDI child creation
		//
		mdicreate.szClass = "ViewerClass";
		mdicreate.szTitle = (LPTSTR)&(pInfo->CaptionBarText);
		mdicreate.hOwner  = ghModule;
		mdicreate.x       =
		mdicreate.y       = CW_USEDEFAULT;
		mdicreate.cx      = 300;
		mdicreate.cy      = 300;
		mdicreate.style   = 0L;
		mdicreate.lParam  = (LONG) hInfo;

		/*Create Child Window*/
		hwndChildWindow =
		    (HANDLE) SendMessage(ghwndClient, WM_MDICREATE,
				0L,
				(LONG)(LPMDICREATESTRUCT)&mdicreate);

		if (hwndChildWindow == NULL) 
		{
		    OutputDebugString ("Failed in Creating Child Window");
		    return 0L;
		}

		iViewerCount++ ;
		LocalUnlock(hInfo);
		return ((LONG)hwndChildWindow);

	    }

	    case MM_ABOUT:
		if (DialogBox(ghModule, "AboutBox", ghwndMain, (DLGPROC)About) == -1)
		   OutputDebugString ("DEMO: About Dialog Creation Error!");
		return 0L;

	    //
	    // Only my children know how to deal with these messages, so
	    // pass these to children for processing
	    //
	    case MM_CREATE_JULIA_THREAD:
	    case MM_SET_XFORM_ATTR:
	    case MM_CREATE_MANDEL_THREAD:
	    case MM_OPT_4:              // currently not used
	    case MM_DRAW_SET:
	    case MM_SETDIB2DEVICE:
	    case MM_BW:
	    case MM_SHIFT:
	    case MM_CUSTOM:
	    case MM_CYCLE:
	    case MM_TP_IDLE:
	    case MM_TP_LOW:
	    case MM_TP_BELOW_NORMAL:
	    case MM_TP_NORMAL:
	    case MM_TP_ABOVE_NORMAL:
	    case MM_TP_HIGH:
	    case MM_TP_TIME_CRITICAL:
	    case MM_FLOAT:
	    case MM_FIX:
	    case MM_ITERATION_100:
	    case MM_ITERATION_500:
	    case MM_ITERATION_1000:
	    case MM_ITERATION_5000:
	    case MM_ITERATION_DOUBLE:
	    case MM_STEP_ONE:
	    case MM_STEP_TWO:
	    case MM_STEP_THREE:
	    case MM_SAVE:
	    case MM_SAVE_MONO:
	    case MM_LOAD:
	    case MM_STRETCHBLT:
	    case MM_BITBLT:
	    case MM_BLACKONWHITE:
	    case MM_COLORONCOLOR:
	    case MM_WHITEONBLACK:
	    case MM_HALFTONE:
	    case MM_CLIP:
	    case MM_RM_CLIP:
	    case MM_SELCLIPRGN:
	    case MM_ERASE:
	    case MM_PORTRAIT:
	    case MM_LANDSCAPE:
	    case MM_PRINTER:
	    case MM_PRINTER + 1:
	    case MM_PRINTER + 2:
	    case MM_PRINTER + 3:
	    case MM_PRINTER + 4:
	    case MM_PRINTER + 5:
	    case MM_PRINTER + 6:
	    case MM_PRINTER + 7:
	    case MM_PRINTER + 8:
	    case MM_PRINTER + 9:
	    case MM_RLELOAD_DEMO:
	    case MM_RLEPLAYCONT:
	    case MM_RLELOAD:
	    case MM_RLESAVE:
	    case MM_CLEAR:
	    case MM_RLEPLAY:
	    {
		HWND hActiveChild;

		hActiveChild = (HANDLE) SendMessage(ghwndClient, WM_MDIGETACTIVE, 0L, 0L);
		if (hActiveChild)
		    SendMessage(hActiveChild, WM_COMMAND, wParam, lParam);
		return 0L;
	    }

	    default:
		return DefFrameProc(hwnd,  ghwndClient, message, wParam, lParam);
	}
    default:

	return DefFrameProc(hwnd,  ghwndClient, message, wParam, lParam);
    }
}

/***************************************************************************\
* ChildWndProc
*
\***************************************************************************/

long APIENTRY ChildWndProc(
    HWND hwnd,
    UINT message,
    DWORD wParam,
    LONG lParam)
{
    static FARPROC     lpfnSuspendThrd, lpfnResumeThrd;
    static BOOL        bDIB2Device = FALSE;

    sprintf( gtext,"message = %lx\n", message);
    OutputDebugString( gtext);

    switch (message) {
	case WM_COMMAND: {
	  PINFO       pInfo;
	  HWND        hTextWnd;

	  switch (LOWORD(wParam)) {
	    //
	    // Create a Julia drawing thread
	    //
	    case MM_CREATE_JULIA_THREAD: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		hTextWnd = pInfo->hTextWnd;
		sprintf( gtext,"(%g, %g) <-> (%g, %g)", pInfo->xFrom, pInfo->yFrom, pInfo->xTo, pInfo->yTo);
		SetWindowText(hTextWnd, gtext);
		sprintf( gtext,"(c1 = %g, c2 = %g)\n\n", pInfo->c1, pInfo->c2);
		OutputDebugString( gtext );

		if (pInfo->hThrd)
		    CloseHandle(pInfo->hThrd);

		pInfo->hThrd = CreateThread(NULL, 0,
				 (gFloat ? (LPTHREAD_START_ROUTINE)StartDraw : (LPTHREAD_START_ROUTINE)StartDrawFix),
				 pInfo,
				 STANDARD_RIGHTS_REQUIRED,
				 &pInfo->dwThreadId );

	       if (pInfo->hThrd && pInfo->bDrawing) 
		   {
		 	  if (!SetThreadPriority(pInfo->hThrd, pInfo->iPriority))
			     OutputDebugString ("Can't set Priority!");
	       }

	       bReleaseInfoData(hwnd);
	       return 0L;
	    }

	    //
	    // Reset pInfo reflecting new transformation
	    //
	    case MM_SET_XFORM_ATTR: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		hTextWnd = pInfo->hTextWnd;
		SetWindowText(hTextWnd, GetStringRes (IDS_CLICK_HERE_VIEW));

		pInfo->xFrom      = xFrom;
		pInfo->xTo        = xTo;
		pInfo->yFrom      = yFrom;
		pInfo->yTo        = yTo;
		pInfo->c1         = c1;
		pInfo->c2         = c2;
		pInfo->lxFrom      = lxFrom;
		pInfo->lxTo        = lxTo;
		pInfo->lyFrom      = lyFrom;
		pInfo->lyTo        = lyTo;
		pInfo->lc1         = lc1;
		pInfo->lc2         = lc2;

	       bReleaseInfoData(hwnd);
	       return 0L;
	    }

	    //
	    // Create a Mandelbrot drawing thread
	    //
	    case MM_CREATE_MANDEL_THREAD: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		hTextWnd = pInfo->hTextWnd;
		sprintf( gtext,"(%g, %g) <-> (%g, %g)", pInfo->xFrom, pInfo->yFrom, pInfo->xTo, pInfo->yTo);
		SetWindowText(hTextWnd, gtext);
		sprintf( gtext,"(c1 = %g, c2 = %g)\n\n", pInfo->c1, pInfo->c2);
		OutputDebugString( gtext );

		if (pInfo->hThrd)
		    CloseHandle(pInfo->hThrd);

		pInfo->hThrd = CreateThread(NULL, 0,
				 (gFloat ? (LPTHREAD_START_ROUTINE)StartMandelbrot : (LPTHREAD_START_ROUTINE)StartMandelbrotFix),
				 pInfo,
				 STANDARD_RIGHTS_REQUIRED,
				 &pInfo->dwThreadId );

	       if (pInfo->hThrd && pInfo->bDrawing) 
		   {
			  if (!SetThreadPriority(pInfo->hThrd, pInfo->iPriority))
			     OutputDebugString ("Can't set Priority!");
	       }


	       bReleaseInfoData(hwnd);
	       return 0L;
	    }

	    //
	    // Create a Julia drawing thread using algorithm StartDraw2
	    // Currently not used
	    //
	    case MM_OPT_4: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		hTextWnd = pInfo->hTextWnd;
		SetWindowText(hTextWnd, "MM_OPT_4");

		sprintf( gtext,"xFrom = %g, xTo = %g, yFrom = %g, yTo = %g\n", pInfo->xFrom, pInfo->xTo, pInfo->yFrom, pInfo->yTo);
		OutputDebugString( gtext );

		if (pInfo->hThrd)
		    CloseHandle(pInfo->hThrd);

		pInfo->hThrd = CreateThread(NULL, 0,
				 (LPTHREAD_START_ROUTINE)StartDraw2,
				 pInfo,
				 STANDARD_RIGHTS_REQUIRED,
				 &pInfo->dwThreadId );

	       if (pInfo->hThrd && pInfo->bDrawing) 
		   {
		      if (!SetThreadPriority(pInfo->hThrd, pInfo->iPriority))
			     OutputDebugString ("Can't set Priority!");
	       }

	       bReleaseInfoData(hwnd);
	       return 0L;
	    }

	    case MM_DRAW_SET: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		PostMessage(hwnd, WM_COMMAND,
		    pInfo->bMandel ? (DWORD)((WORD)MM_CREATE_MANDEL_THREAD) : (DWORD)((WORD)MM_CREATE_JULIA_THREAD),
		    (LONG)0L);

	       bReleaseInfoData(hwnd);
	       return 0L;
	    }

	    {
	    int     iPriority;

		case MM_TP_IDLE:
		    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
			return 0L;
		    }

		    iPriority = THREAD_PRIORITY_IDLE;
		    bCheckMutexMenuItem(pInfo, hChildMenu, MM_TP_IDLE);
		    DrawMenuBar(GetParent(GetParent(hwnd))) ;
		    goto CWP_SET_PRIORITY;

		case MM_TP_LOW:
		    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
			return 0L;
		    }

		    iPriority = THREAD_PRIORITY_LOWEST;
		    bCheckMutexMenuItem(pInfo, hChildMenu, MM_TP_LOW);
		    DrawMenuBar(GetParent(GetParent(hwnd))) ;
		    goto CWP_SET_PRIORITY;

		case MM_TP_BELOW_NORMAL:
		    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
			return 0L;
		    }

		    iPriority = THREAD_PRIORITY_BELOW_NORMAL;
		    bCheckMutexMenuItem(pInfo, hChildMenu, MM_TP_BELOW_NORMAL);
		    DrawMenuBar(GetParent(GetParent(hwnd))) ;
		    goto CWP_SET_PRIORITY;

		case MM_TP_NORMAL:
		    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
			return 0L;
		    }

		    iPriority = THREAD_PRIORITY_NORMAL;
		    bCheckMutexMenuItem(pInfo, hChildMenu, MM_TP_NORMAL);
		    DrawMenuBar(GetParent(GetParent(hwnd))) ;
		    goto CWP_SET_PRIORITY;

		case MM_TP_ABOVE_NORMAL:
		    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
			return 0L;
		    }

		    iPriority = THREAD_PRIORITY_ABOVE_NORMAL;
		    bCheckMutexMenuItem(pInfo, hChildMenu, MM_TP_ABOVE_NORMAL);
		    DrawMenuBar(GetParent(GetParent(hwnd))) ;
		    goto CWP_SET_PRIORITY;

		case MM_TP_HIGH:
		    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
			return 0L;
		    }

		    iPriority = THREAD_PRIORITY_HIGHEST;
		    bCheckMutexMenuItem(pInfo, hChildMenu, MM_TP_HIGH);
		    DrawMenuBar(GetParent(GetParent(hwnd))) ;
		    goto CWP_SET_PRIORITY;

		case MM_TP_TIME_CRITICAL:
		    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
			return 0L;
		    }

		    iPriority = THREAD_PRIORITY_TIME_CRITICAL;
		    bCheckMutexMenuItem(pInfo, hChildMenu, MM_TP_TIME_CRITICAL);
		    DrawMenuBar(GetParent(GetParent(hwnd))) ;

CWP_SET_PRIORITY:
		    {
		       HANDLE       hThrd;

		       hThrd = pInfo->hThrd;
		       pInfo->iPriority = iPriority;

		       if (hThrd && pInfo->bDrawing) 
			   {
			      if (!SetThreadPriority(hThrd, iPriority))
				     OutputDebugString ("Can't set Priority!");
		       }

		    }
		    bReleaseInfoData(hwnd);
		    return 0L;

	    }

	    case MM_FLOAT: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_FLOAT);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		gFloat = TRUE;
		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_FIX: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_FIX);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		gFloat = FALSE;
		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_ITERATION_100: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_ITERATION_100);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		gIteration = 100;
		pInfo->iIteration = 100;
		SetWindowText(pInfo->hTextWnd, GetStringRes (IDS_ITER_100));
		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_ITERATION_500: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL){
		    return 0L;
		}
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_ITERATION_500);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		gIteration = 500;

		pInfo->iIteration = 500;
		SetWindowText(pInfo->hTextWnd, GetStringRes (IDS_ITER_500));
		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_ITERATION_1000: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_ITERATION_1000);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		gIteration = 1000;
		pInfo->iIteration = 1000;
		SetWindowText(pInfo->hTextWnd, GetStringRes (IDS_ITER_1000));
		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_ITERATION_5000: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_ITERATION_5000);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		gIteration = 5000;
		pInfo->iIteration = 5000;
		SetWindowText(pInfo->hTextWnd, GetStringRes (IDS_ITER_5000));
		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_ITERATION_DOUBLE: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_ITERATION_DOUBLE);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		gIteration *= 2;
		pInfo->iIteration = gIteration;
		sprintf( gtext, GetStringRes (IDS_ITERATION), pInfo->iIteration);
		SetWindowText(pInfo->hTextWnd, gtext);
		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_STEP_ONE: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_STEP_ONE);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		gStep = 1;
		pInfo->iStep = 1;

		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_STEP_TWO:  {
		if ((pInfo = pGetInfoData(hwnd)) == NULL){
		    return 0L;
		}
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_STEP_TWO);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		gStep = 2;
		pInfo->iStep = 2;

		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_STEP_THREE: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_STEP_THREE);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		gStep = 3;
		pInfo->iStep = 3;

		bReleaseInfoData(hwnd);
		return 0L;
	    }

	    case MM_LOAD: {
		HDC hDC;
		OPENFILENAME ofn;
		char szDirName[256];
		char szFile[256], szFileTitle[256];
		static char *szFilter;
		RECT    rc;

		if ((pInfo = pGetInfoData(hwnd)) == NULL){
		    return 0L;
		}

		szFilter = GetStringRes (IDS_FILE_LIST1);

		GetSystemDirectory((LPSTR) szDirName, 256);
		strcpy(szFile, "*.bmp\0");
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = pInfo->hwnd;
		ofn.lpstrFilter = szFilter;
		ofn.lpstrCustomFilter = (LPSTR) NULL;
		ofn.nMaxCustFilter = 0L;
		ofn.nFilterIndex = 1;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFileTitle = szFileTitle;
		ofn.nMaxFileTitle = sizeof(szFileTitle);
		ofn.lpstrInitialDir = szDirName;
		ofn.lpstrTitle = (LPSTR) NULL;
		ofn.Flags = 0L;
		ofn.nFileOffset = 0;
		ofn.nFileExtension = 0;
		ofn.lpstrDefExt = "BMP";

		if (!GetOpenFileName(&ofn))
		    return 0L;

		GetClientRect(pInfo->hwnd, &rc);
		hDC = GetDC(pInfo->hwnd);
		if (LoadBitmapFile(hDC, pInfo, szFile))
		  bDrawDIB(hDC, pInfo, 0, 0, rc.right, rc.bottom);
		ReleaseDC(hwnd, hDC);

		bReleaseInfoData(hwnd);

		return 0L;
	    }

	    case MM_SAVE: {
		HDC hDC;
		OPENFILENAME ofn;
		char szDirName[256];
		char szFile[256], szFileTitle[256];
		static char *szFilter;

		szFilter = GetStringRes (IDS_FILE_LIST2);

		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		hDC = GetDC(pInfo->hwnd);
#if 0
		{
		HPALETTE hPalTmp;

		hPalTmp = CopyPalette(pInfo->hPal);
		DeleteObject(pInfo->hPal);
		pInfo->hPal = hPalTmp;
		}
#endif
		//
		// saving special effects user might have created in window
		//
		if (pInfo->hBmpSaved)
		    DeleteObject(pInfo->hBmpSaved);
		pInfo->hBmpSaved = SaveBitmap(pInfo->hwnd, pInfo->hPal);
		pInfo->bUseDIB = FALSE;

		GetSystemDirectory((LPSTR) szDirName, 256);
		strcpy(szFile, "*.bmp\0");
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = pInfo->hwnd;
		ofn.lpstrFilter = szFilter;
		ofn.lpstrCustomFilter = (LPSTR) NULL;
		ofn.nMaxCustFilter = 0L;
		ofn.nFilterIndex = 0L;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFileTitle = szFileTitle;
		ofn.nMaxFileTitle = sizeof(szFileTitle);
		ofn.lpstrInitialDir = szDirName;
		ofn.lpstrTitle = (LPSTR) NULL;
		ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
		ofn.nFileOffset = 0;
		ofn.nFileExtension = 0;
		ofn.lpstrDefExt = (LPSTR)NULL;

		if (!GetSaveFileName(&ofn)) {
		    ReleaseDC(pInfo->hwnd, hDC);
		    bReleaseInfoData(hwnd);
		    return 0L;
		}

		SelectPalette(hDC,
		   ((pInfo->iStretchMode == HALFTONE) ? pInfo->hHTPal : pInfo->hPal),
		   FALSE);
		RealizePalette(hDC);
		UpdateColors(hDC);

		//
		// test
		//
		ghPal = pInfo->hPal;

		SaveBitmapFile(hDC, pInfo->hBmpSaved, szFile);

		ReleaseDC(pInfo->hwnd, hDC);

		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_SAVE_MONO: {
		HDC hDC;
		OPENFILENAME ofn;
		char szDirName[256];
		char szFile[256], szFileTitle[256];
		static char *szFilter;

		if ((pInfo = pGetInfoData(hwnd)) == NULL){
		    return 0L;
		}

		szFilter = GetStringRes (IDS_FILE_LIST2);

		GetSystemDirectory((LPSTR) szDirName, 256);
		strcpy(szFile, "*.bmp\0");
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = pInfo->hwnd;
		ofn.lpstrFilter = szFilter;
		ofn.lpstrCustomFilter = (LPSTR) NULL;
		ofn.nMaxCustFilter = 0L;
		ofn.nFilterIndex = 0L;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFileTitle = szFileTitle;
		ofn.nMaxFileTitle = sizeof(szFileTitle);
		ofn.lpstrInitialDir = szDirName;
		ofn.lpstrTitle = GetStringRes (IDS_SAVING_MONO_BITMAP);
		ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
		ofn.nFileOffset = 0;
		ofn.nFileExtension = 0;
		ofn.lpstrDefExt = (LPSTR)NULL;

		if (!GetSaveFileName(&ofn))
		    return 0L;

		hDC = GetDC(pInfo->hwnd);

		SaveBitmapFile(hDC, pInfo->hBmpMono, szFile);
		ReleaseDC(pInfo->hwnd, hDC);

		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_STRETCHBLT: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL){
		    return 0L;
		}
		gbStretch = TRUE;
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_STRETCHBLT);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		pInfo->bStretch = gbStretch;
		InvalidateRect(pInfo->hwnd, NULL, FALSE);

		bReleaseInfoData(hwnd);
		return 0L;

	    }
	    case MM_BITBLT: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		gbStretch = FALSE;
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_BITBLT);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		pInfo->bStretch = gbStretch;
		InvalidateRect(pInfo->hwnd, NULL, FALSE);

		bReleaseInfoData(hwnd);
		return 0L;

	    }
	    case MM_BLACKONWHITE: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		giStretchMode = BLACKONWHITE;
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_BLACKONWHITE);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		pInfo->iStretchMode = giStretchMode;
		InvalidateRect(pInfo->hwnd, NULL, FALSE);

		bReleaseInfoData(hwnd);
		return 0L;

	    }
	    case MM_COLORONCOLOR: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		giStretchMode = COLORONCOLOR;
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_COLORONCOLOR);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		pInfo->iStretchMode = giStretchMode;
		InvalidateRect(pInfo->hwnd, NULL, FALSE);

		bReleaseInfoData(hwnd);
		return 0L;

	    }
	    case MM_WHITEONBLACK: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		giStretchMode = WHITEONBLACK;
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_WHITEONBLACK);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		pInfo->iStretchMode = giStretchMode;
		InvalidateRect(pInfo->hwnd, NULL, FALSE);

		bReleaseInfoData(hwnd);
		return 0L;

	    }
	    case MM_HALFTONE: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		giStretchMode = HALFTONE;
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_HALFTONE);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		pInfo->iStretchMode = giStretchMode;
		InvalidateRect(pInfo->hwnd, NULL, FALSE);

		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_SETDIB2DEVICE: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		bDIB2Device = (bDIB2Device ? FALSE : TRUE);
		pInfo->bSetDIBsToDevice = bDIB2Device;
		CheckMenuItem(hChildMenu, MM_SETDIB2DEVICE, (bDIB2Device ? MF_CHECKED : MF_UNCHECKED));
		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_BW: {
		HDC hDC;

		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		hDC = GetDC(pInfo->hwnd);
		bChangeDIBColor(hDC, pInfo, MM_BW);
		ReleaseDC(hwnd, hDC);
		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_SHIFT: {
		HDC hDC;

		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		hDC = GetDC(pInfo->hwnd);
		bChangeDIBColor(hDC, pInfo, MM_SHIFT);
		ReleaseDC(hwnd, hDC);
		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_CUSTOM: {
		static DWORD argbCust[16] = {
		    RGB(255, 255, 255), RGB(255, 255, 255),
		    RGB(255, 255, 255), RGB(255, 255, 255),
		    RGB(255, 255, 255), RGB(255, 255, 255),
		    RGB(255, 255, 255), RGB(255, 255, 255),
		    RGB(255, 255, 255), RGB(255, 255, 255),
		    RGB(255, 255, 255), RGB(255, 255, 255),
		    RGB(255, 255, 255), RGB(255, 255, 255),
		    RGB(255, 255, 255), RGB(255, 255, 255)
		};
		CHOOSECOLOR cc;
		BOOL bResult;
		DWORD rgbOld;
		HBRUSH hBrush;
		HDC hDC;

		rgbOld = RGB(255, 255, 255);
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = ghwndMain;
		cc.hInstance = ghModule;
		cc.rgbResult = rgbOld;
		cc.lpCustColors = argbCust;
		cc.Flags = CC_RGBINIT | CC_SHOWHELP;
		cc.lCustData = 0;
		cc.lpfnHook = NULL;
		cc.lpTemplateName = NULL;

		bResult = ChooseColor(&cc);
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		if (bResult) {
		    hDC = GetDC(pInfo->hwnd);
		    hBrush = hBrCreateBrush(hDC, cc.rgbResult);
		    ReleaseDC(pInfo->hwnd, hDC);
		    if (pInfo->hBrush)
			DeleteObject(pInfo->hBrush);
		    pInfo->hBrush = hBrush;
		    pInfo->bFill = TRUE;
		}
		bReleaseInfoData(hwnd);
		return 0L;
		}

#ifndef CYCLETHRD
	    case MM_CYCLE: {
		HDC hDC;

		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		hDC = GetDC(pInfo->hwnd);

		if (pInfo->bClrCycle) {
		    CheckMenuItem(hChildMenu, MM_CYCLE, MF_UNCHECKED);
		    pInfo->bClrCycle = FALSE;
		} else {
		    CheckMenuItem(hChildMenu, MM_CYCLE, MF_CHECKED);
		    pInfo->bClrCycle = TRUE;
		    bChangeDIBColor(hDC, pInfo, MM_CYCLE);
		}

		ReleaseDC(hwnd, hDC);
		bReleaseInfoData(hwnd);
		return 0L;
	    }
#else

	    case MM_CYCLE: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		if (pInfo->bFirstTime) 
		{
		    if (!SetEvent(pInfo->hQuitEvent)) 
			{
				OutputDebugString ("Can't set Quit Event!");
				return 0L;
		    }

		    if (pInfo->hCycleThrd)
			CloseHandle(pInfo->hCycleThrd);

		    pInfo->hCycleThrd = CreateThread(NULL, 0,
				     (LPTHREAD_START_ROUTINE)bCycle,
				     (LPVOID)hwnd,
				     STANDARD_RIGHTS_REQUIRED,
				     &pInfo->dwCycleThrdID );
		    pInfo->bClrCycle = TRUE;
		    pInfo->bFirstTime = FALSE;
		    CheckMenuItem(hChildMenu, MM_CYCLE, MF_CHECKED);
		} else {
		    if (pInfo->bClrCycle) {
			CheckMenuItem(hChildMenu, MM_CYCLE, MF_UNCHECKED);
			pInfo->bClrCycle = FALSE;
			pInfo->dwSuspend = SuspendThread(pInfo->hCycleThrd);
		    } else {
			CheckMenuItem(hChildMenu, MM_CYCLE, MF_CHECKED);
			pInfo->bClrCycle = TRUE;
			pInfo->dwSuspend = ResumeThread(pInfo->hCycleThrd);
		    }
		    if (pInfo->dwSuspend == -1) {
			(pInfo->bClrCycle ?
			 sprintf( gtext,"Error in resuming thread\n") :
			 sprintf( gtext,"Error in suspending thread\n")  );
			OutputDebugString( gtext );
		    }
		}

		bReleaseInfoData(hwnd);
		return 0L;
	    }
#endif
	    case MM_CLIP: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		hTextWnd = pInfo->hTextWnd;
		sprintf( gtext,"(%g, %g) <-> (%g, %g)", pInfo->xFrom, pInfo->yFrom, pInfo->xTo, pInfo->yTo);
		SetWindowText(hTextWnd, gtext);
		sprintf( gtext,"(c1 = %g, c2 = %g)\n\n", pInfo->c1, pInfo->c2);
		OutputDebugString( gtext );
		if (!pInfo->bMandel) 
		{
		    MessageBox(ghwndMain, 
					   GetStringRes (IDS_BOUNDARY),
					   NULL, MB_OK);
		    return 0L;
		}

		if (pInfo->hThrd)
		    CloseHandle(pInfo->hThrd);

		pInfo->hThrd = CreateThread(NULL, 0,
				 (gFloat ? (LPTHREAD_START_ROUTINE)bBoundaryScanFix : (LPTHREAD_START_ROUTINE)bBoundaryScanFix),
				 pInfo,
				 STANDARD_RIGHTS_REQUIRED,
				 &pInfo->dwThreadId );

	       bReleaseInfoData(hwnd);
	       return 0L;
	    }
	    case MM_RM_CLIP: {
		HDC     hDC;

		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		hDC = GetDC(pInfo->hwnd);
		SelectClipRgn(hDC, (HRGN) NULL);
		ReleaseDC(pInfo->hwnd, hDC);
		bReleaseInfoData(hwnd);
		InvalidateRect(pInfo->hwnd, NULL, FALSE);
		return 0L;

	    }
	    case MM_SELCLIPRGN: {
		HDC     hDC;

		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		hDC = GetDC(pInfo->hwnd);

		if (pInfo->hRgnPath != (HRGN) NULL) {
		    SelectClipRgn(hDC, pInfo->hRgnPath);
		}

		ReleaseDC(pInfo->hwnd, hDC);
		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_ERASE: {
		HDC     hDC;
		RECT    rc;

		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}
		hDC = GetDC(pInfo->hwnd);
		if (pInfo->hRgnPath != (HRGN) NULL) {
		    SelectClipRgn(hDC, pInfo->hRgnPath);
		}
		SelectObject(hDC, GetStockObject(WHITE_BRUSH));
		GetClientRect(pInfo->hwnd, &rc);
		PatBlt(hDC, 0, 0, rc.right, rc.bottom, PATCOPY);
		ReleaseDC(pInfo->hwnd, hDC);
		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_PORTRAIT: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		giDmOrient = DMORIENT_PORTRAIT;
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_PORTRAIT);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_LANDSCAPE: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		giDmOrient = DMORIENT_LANDSCAPE;
		bCheckMutexMenuItem(pInfo, hChildMenu, MM_LANDSCAPE);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		bReleaseInfoData(hwnd);
		return 0L;
	    }
	    case MM_PRINTER:
	    case MM_PRINTER + 1:
	    case MM_PRINTER + 2:
	    case MM_PRINTER + 3:
	    case MM_PRINTER + 4:
	    case MM_PRINTER + 5:
	    case MM_PRINTER + 6:
	    case MM_PRINTER + 7:
	    case MM_PRINTER + 8:

#ifdef PRTTHRD
	    case MM_PRINTER + 9: {
		PINFO       pInfo;
		PRTDATA     PrtData, *pPrtData;
		ULONG       sizINFO;
		PBYTE       pjTmpInfo, pjTmp;

		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		if (pInfo->hBmpSaved == NULL) 
		{
		    MessageBox(ghwndMain, 
				       GetStringRes (IDS_NO_SAVED_BITMAP),
					   NULL, MB_OK);
		    return 0L;
		}

		//
		// Copy the info structure to PrtData
		//
		pPrtData = &PrtData;
		pjTmp    = (PBYTE)&(pPrtData->info);
		pjTmpInfo = (PBYTE)pInfo;
		sizINFO = sizeof(INFO);

		while(sizINFO--)
		{
		    *(((PBYTE)pjTmp)++) = *((pjTmpInfo)++);
		}

		PrtData.index = LOWORD(wParam) - MM_PRINTER;

		if (giDmOrient == DMORIENT_PORTRAIT) {
		    PrtData.bUseDefault = TRUE;
		} else {
		    PrtData.bUseDefault = FALSE;
		    PrtData.DevMode.dmSize = sizeof(DEVMODE);
		    PrtData.DevMode.dmDriverExtra = 0;
		    PrtData.DevMode.dmOrientation = DMORIENT_LANDSCAPE;
		    PrtData.DevMode.dmFields = DM_ORIENTATION;
		}

		if (pInfo->hPrtThrd)
		    CloseHandle(pInfo->hPrtThrd);

		pInfo->hPrtThrd = CreateThread(NULL, 0,
				 (LPTHREAD_START_ROUTINE)bPrintBmp,
				 &PrtData,
				 STANDARD_RIGHTS_REQUIRED,
				 &pInfo->dwPrtThrdID );

		bReleaseInfoData(hwnd);
		return 0L;
	    }

#else
	    case MM_PRINTER + 9: {
		HDC         hdcPrinter, hDC;
		int         index;
		DEVMODE     devmode;
		DEVMODE     *pdevmode;
		PINFO       pInfo;
		int         iWidth, iHeight;


		index = LOWORD(wParam) - MM_PRINTER;

		if (giDmOrient == DMORIENT_PORTRAIT)
		    pdevmode = NULL;
		else {
		    pdevmode = &devmode;
		    devmode.dmSize = sizeof(DEVMODE);
		    devmode.dmDriverExtra = 0;
		    devmode.dmOrientation = DMORIENT_LANDSCAPE;
		    devmode.dmFields = DM_ORIENTATION;
		}

		if (!(hdcPrinter = CreateDC( "", gpszPrinterNames[index],
					     "", pdevmode)))
		{
		    return(0L);
		}

		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		iWidth = GetDeviceCaps(hdcPrinter, HORZRES);
		iHeight = GetDeviceCaps(hdcPrinter, VERTRES);

// !!! Why is it necessary to save the image over again?  May not want to
//     do this because user may want to print the nice HT bitmap. So,
//     use the DIB src.
#if 0
		if (pInfo->hBmpSaved)
		    DeleteObject(pInfo->hBmpSaved);

		pInfo->hBmpSaved = SaveBitmap(pInfo->hwnd, pInfo->hPal);
#endif
		Escape(hdcPrinter, STARTDOC, 20, "Mandelbrot", NULL);
		bDrawDIB(hdcPrinter, pInfo, 0, 0, iWidth, iHeight);
		Escape(hdcPrinter, NEWFRAME, 0, NULL, NULL);
		Escape(hdcPrinter, ENDDOC, 0, NULL, NULL);
		ReleaseDC(pInfo->hwnd, hDC);
		bReleaseInfoData(hwnd);
		DeleteDC(hdcPrinter);
		return 0L;
	    }
#endif
	    default:
	       return 0L;

	  }

	}
	case WM_SETFOCUS:
	    break;

	case WM_MDIACTIVATE: {
	    PINFO       pInfo;

	    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		return 0L;
	    }

	    if ((HWND) lParam == hwnd) {                // being activated
		SendMessage(GetParent(hwnd), WM_MDISETMENU,
			    (DWORD)  hChildMenu,
			    (LONG)   hSubMenuThree) ;

		(pInfo->bClrCycle ?
		    CheckMenuItem(hChildMenu, MM_CYCLE, MF_CHECKED) :
		    CheckMenuItem(hChildMenu, MM_CYCLE, MF_UNCHECKED) );

		vChkMenuItem(pInfo, hChildMenu, MF_CHECKED);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
		goto MDI_ACT_EXIT;
	    }

	    if ((HWND) wParam == hwnd) {                // being deactivated

		vChkMenuItem(pInfo, hChildMenu, MF_UNCHECKED);
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
	    }
MDI_ACT_EXIT:
	    bReleaseInfoData(hwnd);
	    return 0L;
	}

	case WM_QUERYNEWPALETTE:
	case WM_PALETTECHANGED: {
	    PINFO       pInfo;

	    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		return 0L;
	    }

	    SendMessage(pInfo->hwnd, message, wParam, lParam);
	    bReleaseInfoData(hwnd);
	    return 0L;
	}

#if 0
	case WM_WINDOWPOSCHANGING: {
	    PWINDOWPOS  pWndPos;
	    PINFO       pInfo;
	    HWND        hTextWnd;
	    int         iCyText, iCxBorder, iCyBorder, iCyCaption;
	    RECT        rect, rcl;
	    LONG        lcx, lcy;

	    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		break;
	    }

	    hTextWnd = pInfo->hTextWnd;

	    bReleaseInfoData(hwnd);

	    iCyText = GetWindowLong(hTextWnd, GWL_USERDATA);
	    iCxBorder = GetSystemMetrics(SM_CXBORDER);
	    iCyBorder = GetSystemMetrics(SM_CYBORDER);
	    iCyCaption = GetSystemMetrics(SM_CYCAPTION) - iCyBorder;
	    GetClientRect(GetParent(hwnd), &rcl);
	    GetWindowRect(hwnd, &rect);
	    lcx = rect.right-rect.left;
	    lcy = rect.bottom-rect.top;
	    pWndPos = (PWINDOWPOS)lParam;
	    if ((pWndPos->cy > lcy) || (pWndPos->cx > lcx)) {
		pWndPos->cx =
		   ((pWndPos->cx > pWndPos->cy) ? pWndPos->cy-iCyText : pWndPos->cx);
		pWndPos->cy = pWndPos->cx + iCyText;
	    } else { if ((pWndPos->cy < lcy) || (pWndPos->cx < lcx)) {
		     pWndPos->cx =
			((pWndPos->cx > pWndPos->cy) ? pWndPos->cy-iCyText : pWndPos->cx);
		     pWndPos->cy = pWndPos->cx + iCyText;
		   }
	    }
	    break;
	}
#endif
	case WM_SIZE: {
	    HANDLE      hThrd;
	    PINFO       pInfo;
	    HWND        hTextWnd, hJulia;
	    BOOL        bMandel;
	    WORD        wCx;
	    int         iCyText;

	    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		break;
	    }

	    hTextWnd = pInfo->hTextWnd;
	    hJulia   = pInfo->hwnd;
	    hThrd    = pInfo->hThrd;
	    bMandel  = pInfo->bMandel;
	    bReleaseInfoData(hwnd);
	    iCyText = GetWindowLong(hTextWnd, GWL_USERDATA);
	    wCx = (WORD) (HIWORD(lParam) - iCyText);

	    MoveWindow(hJulia, 0, 0,
			   LOWORD(lParam),
			   wCx,
			   TRUE);

	    MoveWindow(hTextWnd,
		       0,
		       wCx,
		       LOWORD(lParam),
		       iCyText,
		       TRUE);

	    if (hThrd) {
		TerminateThread(hThrd, (DWORD)0L);
		/*
		PostMessage(hwnd, WM_COMMAND,
		    bMandel ? (DWORD)((WORD)MM_CREATE_MANDEL_THREAD) : (DWORD)((WORD)MM_CREATE_JULIA_THREAD),
		    (LONG)0L);
		  */
	    }

	    break;
	}

	//
	// display info in the status window
	//
	case WM_USER+0xa: {
	    PINFO       pInfo;
	    static ULONG ulClick = 0;
	    HWND        hTextWnd;

	    ulClick++;
	    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		return 0L;
	    }

	    hTextWnd = pInfo->hTextWnd;
	    switch (ulClick % 6) {
		case 0: sprintf( gtext,"%g <= x <= %g, %g <= y <= %g", pInfo->xFrom, pInfo->xTo, pInfo->yTo, pInfo->yFrom);
			break;
		case 1: sprintf( gtext,"c1 = %g, c2 = %g", pInfo->c1, pInfo->c2);
			break;
		case 2: sprintf( gtext,
					     GetStringRes (IDS_ELAPSED_TIME),
						 (ULONG) pInfo->dwElapsed);
			break;
		case 3: sprintf( gtext,
					     GetStringRes (IDS_ITERATION),
						 pInfo->iIteration);
			break;
		case 4:	sprintf( gtext,
						 GetStringRes (IDS_STEP),
						 pInfo->iStep);
			break;
		case 5: 
				(gFloat ? sprintf( gtext, GetStringRes (IDS_FLOATING_PT))
				        : sprintf( gtext, GetStringRes (IDS_FIXED_PT))) ;
			break;

		default: break;
	    }
	    SetWindowText(hTextWnd, gtext);
	    bReleaseInfoData(hwnd);
	    return 0L;
	}

	case WM_SYSCOMMAND: {
	    LONG        lResult;

	    EnumChildWindows(ghwndClient, (WNDENUMPROC)lpfnSuspendThrd, lParam);

	    lResult = DefMDIChildProc(hwnd, message, wParam, lParam);

	    EnumChildWindows(ghwndClient, (WNDENUMPROC)lpfnResumeThrd, lParam);

	    return lResult;
	    break;
	}

	case WM_CREATE: {
	    PINFO           pInfo;
	    HANDLE          hInfo;
	    HWND            hTextWnd, hJulia;
	    RECT            rcl;

	    //
	    // CR! MakeProcInstance is noop!
	    //
	    lpfnSuspendThrd = (FARPROC)MakeProcInstance (SuspendDrawThrd, ghModule);
	    lpfnResumeThrd  = (FARPROC)MakeProcInstance (ResumeDrawThrd, ghModule);

	    hTextWnd = CreateWindow("Text", NULL,
				    WS_BORDER | SS_LEFT | WS_CHILD | WS_VISIBLE,
				    0, 0, 0, 0,
				    hwnd,
				    (HMENU) 2,
				    ghModule,
				    NULL);

	    GetClientRect(hwnd, &rcl);
	    hJulia = CreateWindow("Julia", (LPSTR) NULL,
			  WS_CHILD      | WS_VISIBLE     |
			  WS_BORDER,
			  0,0, rcl.right-rcl.left,
			  rcl.bottom-rcl.top-GetWindowLong(hTextWnd, GWL_USERDATA),
			  hwnd, (HMENU)1, ghModule, (LPVOID)NULL);

	    SetWindowText(hTextWnd, GetStringRes (IDS_SELECT_DRAW_SET));

	    hInfo = (HANDLE) ((LPMDICREATESTRUCT) ((LPCREATESTRUCT) lParam)->lpCreateParams)->lParam ;
	    if (hInfo) {
		if ((pInfo = (PINFO)LocalLock(hInfo)) == NULL) 
		{
		    OutputDebugString ("Failed in LocalLock, hNode");
		    break;
		} 
		else 
		{
		    HDC hDC;

		    if (!GetClientRect(hwnd, &pInfo->rcClient))
				OutputDebugString ("Failed in GetClientRect!");

		    pInfo->hTextWnd = hTextWnd;
		    pInfo->hwnd = hJulia;
		    hDC = GetDC(hJulia);
		    pInfo->hHTPal = CreateHalftonePalette(hDC);
		    ReleaseDC(hJulia, hDC);
#ifdef CYCLETHRD
		    //
		    // Creating a signal quit color cycling event
		    //
		    if ((pInfo->hQuitEvent = CreateEvent(NULL, TRUE, TRUE, NULL)) == NULL)
				OutputDebugString ("Failed in creating Quit Event!");
#endif
		    SetWindowLong(hwnd, 0, (LONG) hInfo);
		    LocalUnlock(hInfo);
		}
	    } 
		else 
		{
			OutputDebugString ("Can't allocate hInfo!");
	    }

#if 0
	    //
	    // Initialize printers here will detect printers availiability
	    // more often, but kind of overkill.
	    //
	    bInitPrinter(hwnd);
#endif
	    break;
	}

	case WM_CLOSE: {
	    SendMessage(GetParent(hwnd), WM_MDISETMENU,
			    (DWORD) hMenu,
			    (LONG)  hSubMenuOne) ;
	    DrawMenuBar(GetParent(GetParent(hwnd))) ;
	    break;
	}

	case WM_DESTROY: {
	    PINFO            pInfo;
	    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		break;
	    }

	    if (pInfo->hThrd) {
		TerminateThread(pInfo->hThrd, (DWORD)0L);
		CloseHandle(pInfo->hThrd);
	    }
	    if (pInfo->hPrtThrd) {
		TerminateThread(pInfo->hPrtThrd, (DWORD)0L);
		CloseHandle(pInfo->hPrtThrd);
	    }
	    if (pInfo->hCycleThrd) {
		TerminateThread(pInfo->hCycleThrd, (DWORD)0L);
		CloseHandle(pInfo->hCycleThrd);
	    }


#ifdef CYCLETHRD
	    //
	    // Cleanup color cycling
	    //
	    if (!ResetEvent(pInfo->hQuitEvent))
			OutputDebugString ("Failed in reseting quit event!");
#endif
	    if (pInfo->hBmpMono)
		DeleteObject(pInfo->hBmpMono);

	    if (pInfo->hBmpSaved)
		DeleteObject(pInfo->hBmpSaved);

	    if (pInfo->hBrush)
		DeleteObject(pInfo->hBrush);

	    bReleaseInfoData(hwnd);
	    LocalFree((HANDLE) GetWindowLong(hwnd, 0));
	    break;
	}

	default:
	    return DefMDIChildProc(hwnd, message, wParam, lParam);

    } //switch
    return DefMDIChildProc(hwnd, message, wParam, lParam);
}

/******************************Public*Routine******************************\
*
* ViewerWndProc
*
* Effects:
*
* Warnings:
*
\**************************************************************************/

LONG APIENTRY ViewerWndProc(
    HWND hwnd,
    UINT message,
    DWORD wParam,
    LONG lParam)
{
    static FARPROC     lpfnSuspendThrd, lpfnResumeThrd;

    switch (message) {
	case WM_COMMAND: {
	  PINFO       pInfo;
	  HWND        hTextWnd;

	  switch (LOWORD(wParam)) {
	    case MM_RLELOAD_DEMO: {
		HDC             hDC;
		char            szDirName[256];
		char            szFile[400];
		HWND            hViewSurf;

		GetCurrentDirectory(256, (LPTSTR) szDirName);

		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		if ((hViewSurf = pInfo->hwnd) == NULL)
		    return 0L;

		hTextWnd = pInfo->hTextWnd;
		sprintf( gtext,"Loading bitmap(s) into memory");
		SetWindowText(hTextWnd, gtext);

		hDC = GetDC(hViewSurf);
		strcpy(szFile, szDirName);
		strcat(szFile, "\\rsc\\julia.rle");

		if (bStoreRleFile(hDC, pInfo, szFile)) {
		    pInfo->RleData.ulFiles++;
		    PostMessage(ghwndMain, WM_COMMAND, MM_RLEPLAYCONT, 0L);
		}

		ReleaseDC(hViewSurf, hDC);

		bReleaseInfoData(hwnd);
		return 0L;

	    }


	    case MM_RLELOAD: {
		HDC             hDC;
		OPENFILENAME    ofn;
		char            szDirName[256];
		char            szFile[256], szFileTitle[256];
		static char     *szFilter;
		RECT            rc;
		HWND            hViewSurf;

		szFilter = GetStringRes (IDS_FILE_LIST1);

		GetSystemDirectory((LPSTR) szDirName, 256);
		strcpy(szFile, "*.bmp\0");
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hwnd;
		ofn.lpstrFilter = szFilter;
		ofn.lpstrCustomFilter = (LPSTR) NULL;
		ofn.nMaxCustFilter = 0L;
		ofn.nFilterIndex = 1;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFileTitle = szFileTitle;
		ofn.nMaxFileTitle = sizeof(szFileTitle);
		ofn.lpstrInitialDir = szDirName;
		ofn.lpstrTitle = (LPSTR) NULL;
		ofn.Flags = 0L;
		ofn.nFileOffset = 0;
		ofn.nFileExtension = 0;
		ofn.lpstrDefExt = "BMP";

		if (!GetOpenFileName(&ofn))
		    return 0L;

		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		if ((hViewSurf = pInfo->hwnd) == NULL)
		    return 0L;

		hTextWnd = pInfo->hTextWnd;
		sprintf( gtext, GetStringRes (IDS_LOADING_BITMAPS));
		SetWindowText(hTextWnd, gtext);

		GetClientRect(hwnd, &rc);
		hDC = GetDC(hViewSurf);
		if (bStoreRleFile(hDC, pInfo, szFile))
		    pInfo->RleData.ulFiles++;
		ReleaseDC(hViewSurf, hDC);

		bReleaseInfoData(hwnd);
		return 0L;

	    }

	    case MM_RLESAVE: {
		HDC             hDC;
		OPENFILENAME    ofn;
		char            szDirName[256];
		char            szFile[256], szFileTitle[256];
		static char     *szFilter;
		HWND            hViewSurf;

		szFilter = GetStringRes (IDS_FILE_LIST3);

		GetSystemDirectory((LPSTR) szDirName, 256);
		strcpy(szFile, "*.rle\0");
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hwnd;
		ofn.lpstrFilter = szFilter;
		ofn.lpstrCustomFilter = (LPSTR) NULL;
		ofn.nMaxCustFilter = 0L;
		ofn.nFilterIndex = 0L;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFileTitle = szFileTitle;
		ofn.nMaxFileTitle = sizeof(szFileTitle);
		ofn.lpstrInitialDir = szDirName;
		ofn.lpstrTitle = GetStringRes(IDS_SAVING_MEMORY_RLE); 
		ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
		ofn.nFileOffset = 0;
		ofn.nFileExtension = 0;
		ofn.lpstrDefExt = (LPSTR)NULL;

		if (!GetSaveFileName(&ofn))
		    return 0L;

		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		if ((hViewSurf = pInfo->hwnd) == NULL)
		    return 0L;

		hTextWnd = pInfo->hTextWnd;
		sprintf( gtext, GetStringRes (IDS_SAVING_LOADED_BMP)); 
		SetWindowText(hTextWnd, gtext);

		hDC = GetDC(hViewSurf);
		bSaveRleFile(hDC, pInfo, szFile);
		ReleaseDC(hViewSurf, hDC);

		bReleaseInfoData(hwnd);
		return 0L;
	    }

	    case MM_CLEAR: {
		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		hTextWnd = pInfo->hTextWnd;
		sprintf( gtext,GetStringRes (IDS_DISCARD_LOADED_BMP));
		SetWindowText(hTextWnd, gtext);

		bFreeRleFile(pInfo);

		bReleaseInfoData(hwnd);
		return 0L;
	    }

	    case MM_RLEPLAY: {
		HDC     hDC;
		HWND    hViewSurf;

		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		if ((hViewSurf = pInfo->hwnd) == NULL)
		    return 0L;

		hTextWnd = pInfo->hTextWnd;
		sprintf( gtext, GetStringRes (IDS_PLAY_LOADED_BMP)); 
		SetWindowText(hTextWnd, gtext);

		hDC = GetDC(hViewSurf);
		EnableMenuItem(hViewSubOne, MM_CLEAR, MF_GRAYED);

		if (pInfo->hThrd0)
		    CloseHandle(pInfo->hThrd0);

		pInfo->hThrd0 = CreateThread(NULL, 0,
			     (LPTHREAD_START_ROUTINE)bPlayRle,
			     pInfo,
			     STANDARD_RIGHTS_REQUIRED,
			     &pInfo->dwThreadId );

		if (pInfo->hThrd0) 
		{
		    if (!SetThreadPriority(pInfo->hThrd0, THREAD_PRIORITY_BELOW_NORMAL))
			   OutputDebugString ("Can't set Priority!");
		}

		//bPlayRle(hDC, pInfo);
		EnableMenuItem(hViewSubOne, MM_CLEAR, MF_ENABLED);
		ReleaseDC(hViewSurf, hDC);

		bReleaseInfoData(hwnd);
		return 0L;
	    }

	    case MM_RLEPLAYCONT: {
		HWND    hViewSurf;

		if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		    return 0L;
		}

		if ((hViewSurf = pInfo->hwnd) == NULL)
		    return 0L;

		hTextWnd = pInfo->hTextWnd;
		sprintf( gtext, GetStringRes (IDS_PLAY_BMP_CONT));
		SetWindowText(hTextWnd, gtext);

		if (pInfo->bFirstTime) 
		{
		    if (!SetEvent(pInfo->hQuitEvent)) 
			{
				OutputDebugString ("Can't set Quit Event!");
			    return 0L;
		    }

		    EnableMenuItem(hViewSubOne, MM_CLEAR, MF_GRAYED);

		    if (pInfo->hThrd)
			CloseHandle(pInfo->hThrd);

		    pInfo->hThrd = CreateThread(NULL, 0,
				 (LPTHREAD_START_ROUTINE)bPlayRleCont2,
				 pInfo,
				 STANDARD_RIGHTS_REQUIRED,
				 &pInfo->dwThreadId );

		    if (pInfo->hThrd) {
			if (!SetThreadPriority(pInfo->hThrd, THREAD_PRIORITY_BELOW_NORMAL))
			     OutputDebugString ("Can't set Priority!");
		    }

		    pInfo->bPlayRleCont = TRUE;
		    pInfo->bFirstTime = FALSE;
		    CheckMenuItem(hViewMenu, MM_RLEPLAYCONT, MF_CHECKED);
		} 
		else 
		{
		    if (pInfo->bPlayRleCont) {
			EnableMenuItem(hViewSubOne, MM_CLEAR, MF_ENABLED);
			CheckMenuItem(hViewMenu, MM_RLEPLAYCONT, MF_UNCHECKED);
			pInfo->bPlayRleCont = FALSE;
			pInfo->dwSuspend = SuspendThread(pInfo->hThrd);
		    } else {
			EnableMenuItem(hViewSubOne, MM_CLEAR, MF_GRAYED);
			CheckMenuItem(hViewMenu, MM_RLEPLAYCONT, MF_CHECKED);
			pInfo->bPlayRleCont = TRUE;
			pInfo->dwSuspend = ResumeThread(pInfo->hThrd);
		    }
		    if (pInfo->dwSuspend == -1) {
			(pInfo->bPlayRleCont ?
			 sprintf( gtext,"Error in resuming thread\n") :
			 sprintf( gtext,"Error in suspending thread\n")  );
			OutputDebugString( gtext );
		    }
		}

		bReleaseInfoData(hwnd);
		return 0L;
	    }

	    default:
	       return 0L;

	  } //switch

	} // WM_COMMAND
	case WM_SETFOCUS:
	    break;

	case WM_MDIACTIVATE: {
	    PINFO       pInfo;

	    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		return 0L;
	    }

	    if ((HWND) lParam == hwnd) {
		SendMessage(GetParent(hwnd), WM_MDISETMENU,
			    (WPARAM)  hViewMenu,
			    (LPARAM)  NULL) ;
		DrawMenuBar(GetParent(GetParent(hwnd))) ;
	    }

	    bReleaseInfoData(hwnd);
	    return 0L;
	}
	case WM_QUERYNEWPALETTE:
	case WM_PALETTECHANGED: {
	    PINFO       pInfo;

	    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		return 0L;
	    }

	    SendMessage(pInfo->hwnd, message, wParam, lParam);
	    bReleaseInfoData(hwnd);
	    return 0L;
	}

	case WM_SIZE: {
	    PINFO       pInfo;
	    HWND        hTextWnd, hView;
	    WORD        wCx;
	    int         iCyText;

	    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		break;
	    }

	    hTextWnd = pInfo->hTextWnd;
	    hView    = pInfo->hwnd;
	    bReleaseInfoData(hwnd);
	    iCyText = GetWindowLong(hTextWnd, GWL_USERDATA);
	    wCx = (WORD) (HIWORD(lParam) - iCyText);

	    MoveWindow(hView, 0, 0,
			   LOWORD(lParam),
			   wCx,
			   TRUE);

	    MoveWindow(hTextWnd,
		       0,
		       wCx,
		       LOWORD(lParam),
		       iCyText,
		       TRUE);

	    break;
	}

	//
	// display info in the status window
	//
	case WM_USER+0xa: {
	    PINFO       pInfo;
	    static ULONG ulClick = 0;
	    HWND        hTextWnd;

	    ulClick++;
	    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		return 0L;
	    }

	    hTextWnd = pInfo->hTextWnd;
	    switch (ulClick % 4) {
		case 0: 
				sprintf( gtext, GetStringRes (IDS_FRAMES)); 
			break;
		case 1: 
				sprintf( gtext, GetStringRes (IDS_FRAMES));
			break;
		case 2: sprintf( gtext, (pInfo->bPlayRleCont ? 
					               GetStringRes (IDS_CONT_PLAY) :
			                       GetStringRes (IDS_SINGLE_PLAY)));
			break;
		case 3: sprintf( gtext,"");
			break;
		default: break;
	    }
	    SetWindowText(hTextWnd, gtext);
	    bReleaseInfoData(hwnd);
	    return 0L;
	}

	case WM_SYSCOMMAND: {
	    LONG        lResult;

	    EnumChildWindows(ghwndClient, (WNDENUMPROC)lpfnSuspendThrd, lParam);

	    lResult = DefMDIChildProc(hwnd, message, wParam, lParam);

	    EnumChildWindows(ghwndClient, (WNDENUMPROC)lpfnResumeThrd, lParam);

	    return lResult;
	    break;
	}

	case WM_CREATE: {
	    PINFO           pInfo;
	    HANDLE          hInfo;
	    HWND            hTextWnd, hView;
	    RECT            rcl;

	    //
	    // CR! MakeProcInstance is noop!
	    //
	    lpfnSuspendThrd = (FARPROC)MakeProcInstance (SuspendDrawThrd, ghModule);
	    lpfnResumeThrd  = (FARPROC)MakeProcInstance (ResumeDrawThrd, ghModule);

	    hTextWnd = CreateWindow("Text", NULL,
				    WS_BORDER | SS_LEFT | WS_CHILD | WS_VISIBLE,
				    0, 0, 0, 0,
				    hwnd,
				    (HMENU) 2,
				    ghModule,
				    NULL);

	    GetClientRect(hwnd, &rcl);
	    hView = CreateWindow("View", (LPSTR) NULL,
			  WS_CHILD      | WS_VISIBLE     |
			  WS_BORDER,
			  0,0, rcl.right-rcl.left,
			  rcl.bottom-rcl.top-GetWindowLong(hTextWnd, GWL_USERDATA),
			  hwnd, (HMENU)1, ghModule, (LPVOID)NULL);

	    SetWindowText(hTextWnd, GetStringRes (IDS_SELECT_DRAW_SET));
	    hInfo = (HANDLE) ((LPMDICREATESTRUCT) ((LPCREATESTRUCT) lParam)->lpCreateParams)->lParam ;
	    if (hInfo) {
		if ((pInfo = (PINFO)LocalLock(hInfo)) == NULL) 
		{
		    OutputDebugString ("Failed in LocalLock, hNode");
		    break;
		} 
		else 
		{
		    HDC hDC;

		    if (!GetClientRect(hwnd, &pInfo->rcClient))
				OutputDebugString ("Failed in GetClientRect!");

		    pInfo->hTextWnd = hTextWnd;
		    pInfo->hwnd = hView;

		    hDC = GetDC(hView);
		    pInfo->hHTPal = CreateHalftonePalette(hDC);
		    ReleaseDC(hView, hDC);

		    //
		    // Creating a signal quit play continuous event
		    //
		    if ((pInfo->hQuitEvent = CreateEvent(NULL, TRUE, TRUE, NULL)) == NULL)
				OutputDebugString ("Failed in creating Quit Event!");

		    SetWindowLong(hwnd, 0, (LONG) hInfo);
		    LocalUnlock(hInfo);
		}
	    } 
		else 
		{
			OutputDebugString ("Can't allocate hInfo!");
	    }

	    break;
	}

	case WM_CLOSE: {
	    SendMessage(GetParent(hwnd), WM_MDISETMENU,
			    (DWORD) hMenu,
			    (LONG)  hSubMenuOne) ;
	    DrawMenuBar(GetParent(GetParent(hwnd))) ;
	    break;
	}

	case WM_DESTROY: {
	    PINFO            pInfo;
	    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
		break;
	    }

	    TerminateThread(pInfo->hThrd, (DWORD)0L);
	    CloseHandle(pInfo->hThrd);

	    //
	    // Cleanup continuous play
	    //
	    if (!ResetEvent(pInfo->hQuitEvent))
			OutputDebugString ("Failed in reseting quit event!");

	    bFreeRleFile(pInfo);
	    bReleaseInfoData(hwnd);
	    LocalFree((HANDLE) GetWindowLong(hwnd, 0));
	    break;
	}

	default:
	    return DefMDIChildProc(hwnd, message, wParam, lParam);

    } //switch
    return DefMDIChildProc(hwnd, message, wParam, lParam);
}

/******************************Public*Routine******************************\
*
* ViewSurfWndProc
*
* Effects:
*
* Warnings:
*
\**************************************************************************/

LONG APIENTRY ViewSurfWndProc (HWND hwnd, UINT message, DWORD wParam, LONG lParam)
{
    switch (message)
    {
       case WM_CREATE: {
	    break;
       }

       case WM_DESTROY: {
	    break;
       }

       case WM_QUERYNEWPALETTE: {
	     HWND        hParent;
	     PINFO       pInfo;
	     HDC         hDC;
	     UINT        i;
	     HPALETTE    hOldPal;

	     if ((hParent=GetParent(hwnd)) == NULL) 
		 {
			OutputDebugString ("Can't get hParent!");
			return 0L;
	     }
	     if ((pInfo = pGetInfoData(hParent)) == NULL) {
		  return 0L;
	     }

	     // If palette realization causes a palette change,
	     // we need to do a full redraw.

	     hDC = GetDC (hwnd);

	     hOldPal = SelectPalette (hDC,
		       pInfo->RleData.hPal,
		       0);

	     i = RealizePalette(hDC);

	     SelectPalette (hDC, hOldPal, 0);
	     ReleaseDC (hwnd, hDC);
	     bReleaseInfoData(hParent);

	     if (i) {
		 InvalidateRect (hwnd, (LPRECT) (NULL), TRUE);
		 return TRUE;
	     } else
		 return FALSE;

       }
       case WM_PALETTECHANGED: {
	     HWND        hParent;
	     PINFO       pInfo;
	     HDC         hDC;
	     UINT        i;
	     HPALETTE    hOldPal;

	     if ((hParent=GetParent(hwnd)) == NULL) {
		 MessageBox(ghwndMain, "Can't get hParent!", "Error", MB_OK);
		 return 0L;
	     }
	     if ((pInfo = pGetInfoData(hParent)) == NULL) {
		  return 0L;
	     }

	     // if we were not responsible for palette change and if
	     // palette realization causes a palette change, do a redraw.

	     if ((HWND)wParam != hwnd){
		hDC = GetDC (hwnd);

		hOldPal = SelectPalette (hDC,
			pInfo->RleData.hPal,
			0);

		i = RealizePalette (hDC);

		if (i){
		    UpdateColors (hDC);
		}
		SelectPalette (hDC, hOldPal, 0);
		ReleaseDC (hwnd, hDC);
	    }
	    bReleaseInfoData(hParent);
	    break;
       }

       case WM_PAINT:
	 {
	     PAINTSTRUCT ps;
	     HDC         hDC;
	     RECT        rc;

	     GetClientRect(hwnd,&rc);
	     hDC = BeginPaint(hwnd, &ps);
	     EndPaint(hwnd, &ps);
	     return 0L;
	 }

    } // switch
    return DefWindowProc(hwnd, message, wParam, lParam);
}

/***************************************************************************\
* About
*
* About dialog proc.
*
\***************************************************************************/

BOOL CALLBACK About(
    HWND hDlg,
    UINT message,
    DWORD wParam,
    LONG lParam)
{
    switch (message) {
    case WM_INITDIALOG:
	return TRUE;

    case WM_COMMAND:
	if (wParam == IDOK)
	    EndDialog(hDlg, wParam);
	break;
    }

    return FALSE;

    UNREFERENCED_PARAMETER(lParam);
    UNREFERENCED_PARAMETER(hDlg);
}

/*************************************************************************
*
* TextWndProc
*
* Text Window proc.
*
\***************************************************************************/

LONG APIENTRY TextWndProc (HWND hwnd, UINT message, DWORD wParam, LONG lParam)
{
    static HFONT hFont = (HFONT) NULL;

    switch (message)
    {
    case WM_CREATE:
	{
	    LOGFONT    lf;
	    HDC        hDC;
	    HFONT      hOldFont;
	    TEXTMETRIC tm;
	    RECT       rect;
	    LONG       lHeight;

	    SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(lf), (PVOID) &lf, FALSE);

	    hDC = GetDC(hwnd);
	    // this is the height for 8 point size font in pixels
	    lf.lfHeight = 8 * GetDeviceCaps(hDC, LOGPIXELSY) / 72;

	    hFont = CreateFontIndirect(&lf);
	    hOldFont = SelectObject(hDC, hFont);
	    GetTextMetrics(hDC, &tm);
	    GetClientRect(GetParent(hwnd), &rect);

	    // base the height of the window on size of text
	    lHeight = tm.tmHeight+6*GetSystemMetrics(SM_CYBORDER)+2;
	    // saved the height for later reference
	    SetWindowLong(hwnd, GWL_USERDATA, lHeight);
	    SetWindowPos(hwnd, NULL,
		    0,
		    rect.bottom-lHeight,
		    rect.right-rect.left,
		    lHeight,
		    SWP_NOZORDER | SWP_NOMOVE);

	    ReleaseDC(hwnd, hDC);
	    break;
	}

    case WM_LBUTTONDOWN: {
	PostMessage(GetParent(hwnd), WM_USER+0xa, (DWORD)0L, (LONG)0L);
	break;
    }

    case WM_DESTROY:
	    if (hFont)
		DeleteObject(hFont);
	    break;

    case WM_SETTEXT:
	    DefWindowProc(hwnd, message, wParam, lParam);
	    InvalidateRect(hwnd,NULL,TRUE);
	    UpdateWindow(hwnd);
	    return 0L;

    case WM_PAINT:
	{
	    PAINTSTRUCT ps;
	    RECT   rc;
	    char   ach[128];
	    int    len, nxBorder, nyBorder;
	    HFONT  hOldFont = NULL;

	    BeginPaint(hwnd, &ps);

	    GetClientRect(hwnd,&rc);

	    nxBorder = GetSystemMetrics(SM_CXBORDER);
	    rc.left  += 9*nxBorder;
	    rc.right -= 9*nxBorder;

	    nyBorder = GetSystemMetrics(SM_CYBORDER);
	    rc.top    += 3*nyBorder;
	    rc.bottom -= 3*nyBorder;

	    // 3D Text
	    len = GetWindowText(hwnd, ach, sizeof(ach));
	    SetBkColor(ps.hdc, GetSysColor(COLOR_BTNFACE));

	    SetBkMode(ps.hdc, TRANSPARENT);
	    SetTextColor(ps.hdc, RGB(64,96,96));
	    if (hFont)
		hOldFont = SelectObject(ps.hdc, hFont);
	    ExtTextOut(ps.hdc, rc.left+2*nxBorder+2, rc.top+2, ETO_OPAQUE | ETO_CLIPPED,
			&rc, ach, len, NULL);

	    SetTextColor(ps.hdc, RGB(128,128,128));
	    if (hFont)
		hOldFont = SelectObject(ps.hdc, hFont);
	    ExtTextOut(ps.hdc, rc.left+2*nxBorder+1, rc.top+1, ETO_CLIPPED,
			&rc, ach, len, NULL);

	    SetTextColor(ps.hdc, RGB(255,255,255));
	    if (hFont)
		hOldFont = SelectObject(ps.hdc, hFont);
	    ExtTextOut(ps.hdc, rc.left+2*nxBorder, rc.top, ETO_CLIPPED,
			&rc, ach, len, NULL);

	    SetBkMode(ps.hdc, OPAQUE);

	    if (hOldFont)
		SelectObject(ps.hdc, hOldFont);

	    EndPaint(hwnd, &ps);
	    return 0L;
	}
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}


/**************************************************************************\
*
* JuliaWndProc
*
\**************************************************************************/

LONG APIENTRY JuliaWndProc (HWND hwnd, UINT message, DWORD wParam, LONG lParam)
{
    //
    // These statics are shared by all the Julia windows.  But, this is
    // fine because only one Julia window is tracking at any one time.
    // Ideally, we should place this in the per-window INFO data structure.
    // But, this is not necessary.
    //
    static BOOL    bTrack = FALSE;
    static int     OrgX, OrgY;
    static int     PrevX, PrevY;
    static HDC     hDC;
    static HCURSOR hCurArrow, hCurPaintCan;

    switch (message)
    {
       case WM_CREATE: {

	    hpnRed     = CreatePen(PS_SOLID, 0, RGB(0xFF, 0,    0));
	    hpnGreen   = CreatePen(PS_SOLID, 0, RGB(0,    0xFF, 0));
	    hpnBlack   = CreatePen(PS_SOLID, 0, RGB(0,    0,    0));

	    hCurPaintCan = LoadCursor(ghModule, MAKEINTRESOURCE(PAINTCURSOR));
	    hCurArrow = LoadCursor(NULL, IDC_ARROW);
	    break;
       }

       case WM_DESTROY: {
	    HWND        hParent;
	    PINFO       pInfo;

	    DeleteObject(hpnRed);
	    DeleteObject(hpnGreen);
	    DeleteObject(hpnBlack);

	    if ((hParent=GetParent(hwnd)) == NULL) 
		{
			OutputDebugString ("Can't get hParent!");
			break;
	    }
	    if ((pInfo = pGetInfoData(hParent)) == NULL) {
		break;
	    }

	    // we might have open resource if we ever load bitmap in this wnd.
	    bFreeRleFile(pInfo);
	    bReleaseInfoData(hParent);
	    break;
       }

       case WM_QUERYNEWPALETTE: {
	     HWND        hParent;
	     PINFO       pInfo;
	     HDC         hDC;
	     UINT        i;
	     HPALETTE    hOldPal;

	     if ((hParent=GetParent(hwnd)) == NULL) 
		 {
			OutputDebugString ("Can't get hParent!");
			return 0L;
	     }
	     if ((pInfo = pGetInfoData(hParent)) == NULL) {
		  return 0L;
	     }

	     // If palette realization causes a palette change,
	     // we need to do a full redraw.

	     hDC = GetDC (hwnd);

	     hOldPal = SelectPalette (hDC,
		       ((pInfo->iStretchMode == HALFTONE) ? pInfo->hHTPal : pInfo->hPal),
		       0);

	     i = RealizePalette(hDC);
	     SelectPalette (hDC, hOldPal, 0);
	     ReleaseDC (hwnd, hDC);
	     bReleaseInfoData(hParent);

	     if (i) {
		 InvalidateRect (hwnd, (LPRECT) (NULL), TRUE);
		 return TRUE;
	     } else
		 return FALSE;

       }
       case WM_PALETTECHANGED: {
	     HWND        hParent;
	     PINFO       pInfo;
	     HDC         hDC;
	     UINT        i;
	     HPALETTE    hOldPal;

	     if ((hParent=GetParent(hwnd)) == NULL) {
			OutputDebugString ("Can't get hParent!");
			return 0L;
	     }
	     if ((pInfo = pGetInfoData(hParent)) == NULL) {
		  return 0L;
	     }

	     // if we were not responsible for palette change and if
	     // palette realization causes a palette change, do a redraw.

	     if ((HWND)wParam != hwnd){
		hDC = GetDC (hwnd);

		hOldPal = SelectPalette (hDC,
		       ((pInfo->iStretchMode == HALFTONE) ? pInfo->hHTPal : pInfo->hPal),
			0);

		i = RealizePalette (hDC);

		if (i){
		    UpdateColors (hDC);
		}
		SelectPalette (hDC, hOldPal, 0);
		ReleaseDC (hwnd, hDC);
	    }
	    bReleaseInfoData(hParent);
	    break;
       }

       case WM_PAINT:
	 {
	     PAINTSTRUCT ps;
	     HWND        hParent;
	     PINFO       pInfo;
	     HDC         hDC;
	     RECT        rc;

	     GetClientRect(hwnd,&rc);
	     hDC = BeginPaint(hwnd, &ps);
	     EndPaint(hwnd, &ps);
	     if ((hParent=GetParent(hwnd)) == NULL) {
			OutputDebugString ("Can't get hParent!");
			return 0L;
	     }
	     if ((pInfo = pGetInfoData(hParent)) == NULL) {
		  return 0L;
		}

	     if (pInfo->hBmpSaved) {
		hDC = GetDC(hwnd);
		bDrawDIB(hDC, pInfo, 0, 0, rc.right, rc.bottom);
		ReleaseDC(hwnd, hDC);
	     }
	     bReleaseInfoData(hParent);

	     //EndPaint(hwnd, &ps);
	     return 0L;
	 }

       case WM_RBUTTONDOWN: {
	 RECT   rc;
	 HANDLE hParent;
	 PINFO  pInfo;
	 int    x, y;
	 HWND   hJulia;
	 HANDLE hTextWnd;

	 x = (int) LOWORD(lParam);
	 y = (int) HIWORD(lParam);
	 if ((hParent=GetParent(hwnd)) == NULL) {
	     OutputDebugString ("Can't get hParent!");
	     break;
	 }

	 if ((pInfo = pGetInfoData(hParent)) == NULL) {
	     break;
	 }

	 hTextWnd = pInfo->hTextWnd;

	 if (GetWindowLong(GetParent(hwnd), GWL_STYLE) & WS_MAXIMIZE) {
	     GetClientRect(ghwndMain, &rc);
	     rc.bottom -= GetWindowLong(hTextWnd,GWL_USERDATA);
	 } else {
	     GetClientRect(hwnd, &rc);
	 }

	 if (pInfo->bMandel) {

	     hJulia = (HWND) SendMessage(ghwndMain, WM_COMMAND,
					 (DWORD)((WORD)MM_JULIA), 0L);
	     if (hJulia) {
		 //GetClientRect(hwnd, &rc);
		 //
		 // calculate the c value corresponding to the point
		 //
		 c1 = Xform((double) x, 0.0, (double) rc.right, pInfo->xFrom, pInfo->xTo);
		 c2 = Xform((double) y, 0.0, (double) rc.bottom, pInfo->yFrom, pInfo->yTo);
		 lc1 = XformFix(x, 0, rc.right, pInfo->lxFrom, pInfo->lxTo);
		 lc2 = XformFix(y, 0, rc.bottom, pInfo->lyFrom, pInfo->lyTo);

		sprintf( gtext,"(c1 = %g, c2 = %g)\n", c1, c2);
		OutputDebugString( gtext );

		 //
		 // Reset globals to default values for creating Julia set
		 // (Entire set, not zoom in)
		 //
		 bResetGlobal();
		 PostMessage(hJulia, WM_COMMAND, (DWORD)((WORD) MM_SET_XFORM_ATTR), 0L);
	     } else {
		 OutputDebugString ("Can't create hJulia!");
	     }
	 }
	 bReleaseInfoData(hParent);
	 break;
       }
       case WM_LBUTTONDOWN: {
	 HANDLE hParent;
	 PINFO  pInfo;
	 int    x, y;
	 DWORD  dwRGB;
	 HBRUSH hBrOld;

	 x = (int) LOWORD(lParam);
	 y = (int) HIWORD(lParam);
	 if ((hParent=GetParent(hwnd)) == NULL) {
	     OutputDebugString ("Can't get hParent!");
	     break;
	 }

	 if ((pInfo = pGetInfoData(hParent)) == NULL) {
	     break;
	 }

	 if (pInfo->bFill) {
	    hDC = GetDC(hwnd);
	    hBrOld = SelectObject(hDC, pInfo->hBrush);

	    dwRGB = GetPixel(hDC, x, y);

	    ExtFloodFill(hDC, x, y, (COLORREF)dwRGB, FLOODFILLSURFACE);
	    SelectObject(hDC, hBrOld);
	    ReleaseDC(hwnd, hDC);
	    pInfo->bFill = FALSE;

	    if (pInfo->hBmpSaved)
		DeleteObject(pInfo->hBmpSaved);

	    pInfo->hBmpSaved = SaveBitmap(hwnd, pInfo->hPal);
	    pInfo->bUseDIB = FALSE;


	    SetCursor(hCurArrow);
	 } else {
	    bTrack = TRUE;
	    OrgX = PrevX = x = LOWORD(lParam);
	    OrgY = PrevY = y = HIWORD(lParam);

	    hDC = GetDC(hwnd);
	    SetCapture(hwnd);
	 }
	 bReleaseInfoData(hParent);
	 break;
       }
       case WM_MOUSEMOVE: {
	 RECT rectClient;
	 int NextX;
	 int NextY;
	 HANDLE hParent;
	 PINFO  pInfo;

	 if ((hParent=GetParent(hwnd)) == NULL) {
	     OutputDebugString ("Can't get hParent!");
	     break;
	 }

	 if ((pInfo = pGetInfoData(hParent)) == NULL) {
	     break;
	 }

	 if (pInfo->bFill) {
		 SetCursor(hCurPaintCan);
	 } else {
		 SetCursor(hCurArrow);
	 }

	 bReleaseInfoData(hParent);

	 // Update the selection region
	 if (bTrack) {
	     NextX = (SHORT) LOWORD(lParam);
	     NextY = (SHORT) HIWORD(lParam);

	     // Do not draw outside the window's client area

	     GetClientRect (hwnd, &rectClient);
	     if (NextX < rectClient.left) {
		 NextX = rectClient.left;
	     } else if (NextX >= rectClient.right) {
		 NextX = rectClient.right - 1;
	     }
	     if (NextY < rectClient.top) {
		 NextY = rectClient.top;
	     } else if (NextY >= rectClient.bottom) {
		 NextY = rectClient.bottom - 1;
	     }
	     if ((NextX != PrevX) || (NextY != PrevY)) {
		SetROP2(hDC, R2_NOT);           // Erases the previous box

		MoveToEx(hDC, OrgX, OrgY, NULL);
		LineTo(hDC, OrgX, PrevY);
		LineTo(hDC, PrevX, PrevY);
		LineTo(hDC, PrevX, OrgY);
		LineTo(hDC, OrgX, OrgY);
	     // Get the current mouse position

		PrevX = NextX;
		PrevY = NextY;
		MoveToEx(hDC, OrgX, OrgY, NULL);   // Draws the new box
		LineTo(hDC, OrgX, PrevY);
		LineTo(hDC, PrevX, PrevY);
		LineTo(hDC, PrevX, OrgY);
		LineTo(hDC, OrgX, OrgY);
	     }
	 }
	 break;

       }

       case WM_LBUTTONUP: {
	 RECT rc;
	 HANDLE hParent;
	 PINFO  pInfo;
	 int NextX;
	 int NextY;
	 int iDistX, iDistY, iAbsDstX, iAbsDstY;
	 HWND hZoom;
	 HANDLE hTextWnd;

	 if (!bTrack)
	    break;

	 // End the selection
	    ReleaseCapture();
	    bTrack = FALSE;

	    MoveToEx(hDC, OrgX, OrgY, NULL);   // Erases the box
	    LineTo(hDC, OrgX, PrevY);
	    LineTo(hDC, PrevX, PrevY);
	    LineTo(hDC, PrevX, OrgY);
	    LineTo(hDC, OrgX, OrgY);

	    NextX = LOWORD(lParam);
	    NextY = HIWORD(lParam);

	    iDistX = NextX - OrgX;
	    iDistY = NextY - OrgY;
	    iAbsDstX = (iDistX > 0 ? iDistX : -iDistX);
	    iAbsDstY = (iDistY > 0 ? iDistY : -iDistY);
	    if (iAbsDstX > iAbsDstY) {
		NextY = OrgY + (iDistY > 0 ? iAbsDstX : -iAbsDstX);
	    } else if (iAbsDstX < iAbsDstY) {
			NextX = OrgX + (iDistX > 0 ? iAbsDstY : -iAbsDstY);
	    }

	    MoveToEx(hDC, OrgX, OrgY, NULL);   // Draws the new box
	    LineTo(hDC, OrgX, NextY);
	    LineTo(hDC, NextX, NextY);
	    LineTo(hDC, NextX, OrgY);
	    LineTo(hDC, OrgX, OrgY);

	    SetROP2(hDC, R2_COPYPEN);

	    ReleaseDC(hwnd, hDC);
	    if ((hParent=GetParent(hwnd)) == NULL) {
		OutputDebugString ("Can't get hParent!");
		break;
	    }

	    if ((pInfo = pGetInfoData(hParent)) == NULL) {
		break;
	    }

	    hTextWnd = pInfo->hTextWnd;
	    sprintf(gtext, GetStringRes (IDS_MOUSE), OrgX, OrgY, NextX, NextY);

	    //SetWindowText(hTextWnd, gtext);
	    OutputDebugString(gtext);


	    if (GetWindowLong(GetParent(hwnd), GWL_STYLE) & WS_MAXIMIZE) {

		GetClientRect(ghwndMain, &rc);
		rc.bottom -= GetWindowLong(hTextWnd,GWL_USERDATA);
		sprintf(gtext, "(%d, %d), (%d, %d)\n", rc.left, rc.top, rc.right, rc.bottom);
		//SetWindowText(hTextWnd, gtext);
		OutputDebugString(gtext);

	    } else {
		GetClientRect(hwnd, &rc);
	    }

	    if ((OrgX == NextX) && (OrgY == NextY)) {
		bReleaseInfoData(hParent);
		break;
	    }

	    hZoom = (HWND) SendMessage(ghwndMain, WM_COMMAND,
		       pInfo->bMandel ? (DWORD)((WORD)MM_MANDEL) : (DWORD)((WORD)MM_JULIA),
		       0L);
	    if (hZoom) {
		//GetClientRect(hwnd, &rc);
		xFrom = Xform((double) OrgX, 0.0, (double) rc.right, pInfo->xFrom, pInfo->xTo);
		xTo   = Xform((double) NextX, 0.0, (double) rc.right, pInfo->xFrom, pInfo->xTo);
		yFrom = Xform((double) OrgY, 0.0, (double) rc.bottom, pInfo->yFrom, pInfo->yTo);
		yTo   = Xform((double) NextY, 0.0, (double) rc.bottom, pInfo->yFrom, pInfo->yTo);
		lxFrom = XformFix(OrgX, 0, rc.right, pInfo->lxFrom, pInfo->lxTo);
		lxTo   = XformFix(NextX, 0, rc.right, pInfo->lxFrom, pInfo->lxTo);
		lyFrom = XformFix(OrgY, 0, rc.bottom, pInfo->lyFrom, pInfo->lyTo);
		lyTo   = XformFix(NextY, 0, rc.bottom, pInfo->lyFrom, pInfo->lyTo);
		if (!pInfo->bMandel) {
		    c1 = pInfo->c1;
		    c2 = pInfo->c2;
		    lc1 = pInfo->lc1;
		    lc2 = pInfo->lc2;
		}
		PostMessage(hZoom, WM_COMMAND, (DWORD)((WORD) MM_SET_XFORM_ATTR), 0L);
	    } else {
		OutputDebugString ("Can't create hZoom!");
	    }
	 bReleaseInfoData(hParent);
	 break;
       } // case WM_LBUTTONUP
    } // switch
    return DefWindowProc(hwnd, message, wParam, lParam);
}


/******************************Public*Routine******************************\
*
* SuspendDrawThrd
*
* Effects: Enumerates all the MDI children.  Suspending the drawing thread
*          in those windows, if any.
*
* Warnings: assumes the MDI children has class name "ChildClass."
*
\**************************************************************************/


BOOL APIENTRY SuspendDrawThrd (HWND hwnd, LONG lParam) {
   HANDLE      hThrd;
   PINFO       pInfo;
   DWORD       dwSuspend;
   BOOL        bDrawing;
   char        sz[30];

   GetClassName(hwnd, sz, 15);
   if (strcmp(sz, "ChildClass") != 0)
	return 1L;
       if ((pInfo = pGetInfoData(hwnd)) == NULL) {
	   return 1L;
       }

       bDrawing = pInfo->bDrawing;
       hThrd    = pInfo->hThrd;
       bReleaseInfoData(hwnd);

       if (hThrd && bDrawing) {
	   dwSuspend = SuspendThread(hThrd);
	   sprintf( gtext,"\nSuspend: dwSuspend = %d, dwSuspend = %g\n", dwSuspend, dwSuspend);
	   OutputDebugString( gtext );

	   if (dwSuspend == -1) {
	       sprintf( gtext,"Error in suspending thread\n");
	       OutputDebugString( gtext );
	   }
       }
   return 1L;
   UNREFERENCED_PARAMETER(lParam);
}


/******************************Public*Routine******************************\
*
* ResumeDrawThrd
*
* Effects: Enumerates all the MDI children.  Resuming the drawing thread
*          in those windows, if any.
*
* Warnings: Assumes the MDI children has class name "ChildClass." Also,
*           assumes the drawing has been suspended by SuspendDrawThrd.
*
\**************************************************************************/


BOOL APIENTRY ResumeDrawThrd  (HWND hwnd, LONG lParam) {
   HANDLE      hThrd;
   PINFO       pInfo;
   DWORD       dwSuspend;
   BOOL        bDrawing;
   char        sz[30];

   GetClassName(hwnd, sz, 15);
   if (strcmp(sz, "ChildClass") != 0)
	return 1L;
      if ((pInfo = pGetInfoData(hwnd)) == NULL) {
	  return 1L;
      }

      bDrawing = pInfo->bDrawing;
      hThrd    = pInfo->hThrd;
      bReleaseInfoData(hwnd);

      if (hThrd && bDrawing) {
	  dwSuspend = ResumeThread(hThrd);
	  sprintf( gtext,"Resume: dwSuspend = %d, dwSuspend = %g\n", dwSuspend, dwSuspend);
	  OutputDebugString( gtext );

	  if (dwSuspend == -1) {
	      sprintf( gtext,"Error in resuming thread\n");
	      OutputDebugString( gtext );
	  }
      }
   return 1L;
   UNREFERENCED_PARAMETER(lParam);
}


/******************************Public*Routine******************************\
*
* lMul
*
* Effects: Fix point multiplication
*
* Warnings: 9.23 fix point representation used. This is only good for
*           multiplication in a limited range.  Will overflow.
*           CR! Will be implemented as macros in the future
*
\**************************************************************************/

LONG lMul(LONG l1, LONG l2)
{
    LONGLONG   lliTmp;
    LONG       lReturn;

    lliTmp = l1;
    lliTmp *= l2;
    lReturn = (LONG)(lliTmp >> 23);

    return(lReturn);
}

/******************************Public*Routine******************************\
*
* lDiv
*
* Effects: fix point division
*
* Warnings: 9.23 fix point representation used. This is only good for
*           division in a limited range.  Will overflow.
*           CR! Will be implemented as macros in the future
*
\**************************************************************************/

LONG lDiv(long l1, long l2)
{
    LONGLONG   lliTmp;
    LONG       lReturn;



    lliTmp  = (LONGLONG)l1;
    lliTmp  <<= 23;

    lReturn = (LONG)(lliTmp / (LONGLONG)l2);
    return (lReturn);
}


/**************************************************************************\
*
* StartDrawFix
*                                            2
* Effects: Draw'g the Julia Set for Q (z) = z  + c, where z, c are complex
*                                    c
*          Fact:   |Q (0)| = |c| > 2, the orbit of 0 escapes immediately
*                    c
*          claim:  |z| >= |c| = 2 + l, l > 0 escapes under Q
*                                                           c
*          The Julia Set: Basin Boundaries algorithm.
*
* Warnings:
*
\**************************************************************************/
BOOL StartDrawFix(PINFO pInfo)
{
   DWORD       dwTick1;
   HDC         hDC;
   RECT        rc;

   int m, n, i, iPrev;
   int xCurr, yCurr;
   int iPen;

   LONG c1, c2;
   LONG x0, y0, x1, y1, x, y, z;

   int  iBand=1;
   int  iScan=0;
   int  iDiff=0;

#ifndef THRDONE
   INT      iNumClr;
#endif

   HDC          hDCMem;
   HBITMAP      hBitmap, hOldBitmap;

   iPen = pInfo->iPen + 1;
   iPrev = FIRST_PIXEL;    // a big value to signal the first pixel
   //iPrev = pInfo->iIteration + FIRST_PIXEL;
   c1 = pInfo->lc1;
   c2 = pInfo->lc2;

   pInfo->bMandel = FALSE;
   pInfo->bDrawing = TRUE;
   hDC = GetDC(pInfo->hwnd);

#ifndef THRDONE
    if ((iNumClr = iCreatePenFrPal(hDC, NULL, 0, &(pInfo->hPal))) != 0) {
	sprintf( gtext,"iNumClr = %d\n", iNumClr);
	OutputDebugString( gtext);

	if ((pInfo->prghPen = (PVOID*) GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, sizeof(HPEN)*iNumClr)) == NULL) {
	    OutputDebugString ("Failed in Memory Allocation for pInfo->prghPen!");
	} else {
	    if ((pInfo->iPen = iCreatePenFrPal(hDC, pInfo->prghPen, 0, &(pInfo->hPal))) == 0)
		OutputDebugString ("Failed in creating pen!");
	}
    }

   hDCMem = CreateCompatibleDC(hDC);

   SelectPalette(hDCMem, pInfo->hPal, FALSE);
   SelectPalette(hDC,    pInfo->hPal, FALSE);
   RealizePalette(hDC);
   iPen = pInfo->iPen + 1;
#endif

   GetClientRect(pInfo->hwnd, &rc);
   hBitmap = CreateCompatibleBitmap(hDC, (int)rc.right, (int)rc.bottom);
   hOldBitmap = SelectObject(hDCMem, hBitmap);
   yCurr = rc.top;

   dwTick1 = GetTickCount();
   iScan = (((iScan = BATCH / rc.right) == 0) ? 1 : iScan);

   for (n=rc.top; n<=rc.bottom; n+=pInfo->iStep, yCurr+=pInfo->iStep, iPrev = FIRST_PIXEL) {
       xCurr = rc.left;               // since LineTo excludes last point
       MoveToEx(hDCMem, 0, yCurr, NULL);
       y0 = XformFix(n, rc.top, rc.bottom, pInfo->lyFrom, pInfo->lyTo);

       for (m=rc.left; m<=rc.right; m++, xCurr++) {
	   x0 = XformFix(m, rc.left, rc.right, pInfo->lxFrom, pInfo->lxTo);
	   x = x0;
	   y = y0;

	   for (i=1; i<=pInfo->iIteration; i++) {
	       x1 = lMul(x - y, x + y) + c1;    // Z = x1 + i x2

	       y1 = (lMul(x, y) * 2) + c2;
	       x = x1;
	       y = y1;                          //    2       2     2 1/2     2
	       z = lMul(x, x) + lMul(y, y);     // |Z|  = ((x1  + x2 )   ) > 2

	       if (z > 33554432)
		    break;
	   }

	   if (i != iPrev)
	   {
	      if (iPrev != FIRST_PIXEL)
	      {
		switch(iPrev)
		{
		   case 1:
			   if (pInfo->prghPen)
				  SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[0]);
			   break;
		   default:

		       if (iPrev >= pInfo->iIteration) 
			   {
			       SelectObject(hDCMem, hpnBlack);
			       break;
		       }
			   if (pInfo->prghPen)
				   SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[iPrev % iPen]);
		       break;
		}
		iPrev = i;
		LineTo(hDCMem,xCurr,yCurr);
	      }
	      else
		 iPrev = i;     // remember the color for the first pixel
	   }
       }
       switch(i) {
	   case 1:
		  if (pInfo->prghPen)
			  SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[0]);
		  break;
	   default:
	      if (iPrev >= pInfo->iIteration) {
		      SelectObject(hDCMem, hpnBlack);
		      break;
	      }
		  if (pInfo->prghPen)
			 SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[i % iPen]);
	      break;
       }

       LineTo(hDCMem,xCurr,yCurr);

       sprintf(gtext, GetStringRes (IDS_DRAWING), ((FLOAT)n/(FLOAT)rc.bottom)*100);

       SetWindowText(pInfo->hTextWnd, gtext);

       if (n >= iScan * iBand) {
	    BitBlt(hDC, 0, iScan * (iBand-1), rc.right, iScan, hDCMem, 0, iScan * (iBand-1), SRCCOPY);
	    iBand++;
       }
   }

   if ((iDiff = iScan * iBand - rc.bottom) != 0) {
	BitBlt(hDC, 0, iScan * (iBand-1), rc.right, iScan-iDiff, hDCMem, 0, iScan * (iBand-1), SRCCOPY);
   }

   sprintf(gtext, GetStringRes (IDS_DRAWING_DONE));

   SetWindowText(pInfo->hTextWnd, gtext);

   ReleaseDC(pInfo->hwnd, hDC);

   pInfo->dwElapsed = GetTickCount() - dwTick1;

   if (pInfo->hBmpSaved)
       DeleteObject(pInfo->hBmpSaved);

   pInfo->hBmpSaved = SelectObject(hDCMem, hOldBitmap);
   pInfo->bDrawing = FALSE;
#ifndef THRDONE
   if (pInfo->prghPen != NULL) {
       for (i = 0; i <= pInfo->iPen; i++) {
	   DeleteObject((HPEN) (pInfo->prghPen)[i]);
       }
       GlobalFree(pInfo->prghPen);
   }
#endif
   DeleteDC(hDCMem);
   ExitThread(0);
   return TRUE;
}

/**************************************************************************\
*
* StartDraw
*                                            2
* Effects: Draw'g the Julia Set for Q (z) = z  + c, where z, c are complex
*                                    c
*          Fact:   |Q (0)| = |c| > 2, the orbit of 0 escapes immediately
*                    c
*          claim:  |z| >= |c| = 2 + l, l > 0 escapes under Q
*                                                           c
*          The Julia Set: Basin Boundaries algorithm.
*
* Warnings:
*
\**************************************************************************/
BOOL StartDraw(PINFO pInfo)
{
   DWORD       dwTick1;
   HDC         hDC;
   RECT        rc;

   int m, n, i, iPrev;
   int xCurr, yCurr;
   int iPen;

   double c1, c2;
   double x0, y0, x1, y1, x, y, z;

   int  iBand=1;
   int  iScan=0;
   int  iDiff=0;


   HDC          hDCMem;
   HBITMAP      hBitmap, hOldBitmap;

#ifndef THRDONE
   INT      iNumClr;
#endif

   iPen = pInfo->iPen + 1;
   iPrev = FIRST_PIXEL;    // a big value to signal the first pixel
   //iPrev = pInfo->iIteration + FIRST_PIXEL;
   c1 = pInfo->c1;
   c2 = pInfo->c2;

   pInfo->bMandel = FALSE;
   pInfo->bDrawing = TRUE;
   hDC = GetDC(pInfo->hwnd);

#ifndef THRDONE
    if ((iNumClr = iCreatePenFrPal(hDC, NULL, 0, &(pInfo->hPal))) != 0) {
	sprintf( gtext,"iNumClr = %d\n", iNumClr);
	OutputDebugString( gtext);

	if ((pInfo->prghPen = (PVOID*) GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, sizeof(HPEN)*iNumClr)) == NULL) {
	    OutputDebugString ("Failed in Memory Allocation for pInfo->prghPen!");
	} else {
	    if ((pInfo->iPen = iCreatePenFrPal(hDC, pInfo->prghPen, 0, &(pInfo->hPal))) == 0)
		   OutputDebugString ("Failed in creating pen!");
	}
    }

   hDCMem = CreateCompatibleDC(hDC);

   SelectPalette(hDCMem, pInfo->hPal, FALSE);
   SelectPalette(hDC,    pInfo->hPal, FALSE);
   RealizePalette(hDC);
   iPen = pInfo->iPen + 1;
#endif

   GetClientRect(pInfo->hwnd, &rc);
   hBitmap = CreateCompatibleBitmap(hDC, (int)rc.right, (int)rc.bottom);
   hOldBitmap = SelectObject(hDCMem, hBitmap);
   yCurr = rc.top;

   dwTick1 = GetTickCount();

   iScan = (((iScan = BATCH / rc.right) == 0) ? 1 : iScan);

   for (n=rc.top; n<=rc.bottom; n+=pInfo->iStep, yCurr+=pInfo->iStep, iPrev = FIRST_PIXEL) {
       xCurr = rc.left;               // since LineTo excludes last point
       MoveToEx(hDCMem, 0, yCurr, NULL);
       y0 = Xform((double) n, 0.0, (double) rc.bottom, pInfo->yFrom, pInfo->yTo);

       for (m=rc.left; m<=rc.right; m++, xCurr++) {
	   x0 = Xform((double) m, 0.0, (double) rc.right, pInfo->xFrom, pInfo->xTo);
	   x = x0;
	   y = y0;

	   for (i=1; i<=pInfo->iIteration; i++) {
	       x1 = (x - y) * (x + y) + c1;     // Z = x1 + i x2

	       y1 = 2 * x * y + c2;
	       x = x1;
	       y = y1;                          //    2       2     2 1/2     2
	       z = x * x + y * y;               // |Z|  = ((x1  + x2 )   ) > 2

	       if (z > 4.0)
		    break;
	   }

	   if (i != iPrev)
	   {
	      if (iPrev != FIRST_PIXEL)
	      {
		switch(iPrev)
		{
		   case 1:
			   if (pInfo->prghPen)
				  SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[0]);
			   break;
		   default:

		       if (iPrev >= pInfo->iIteration) {
			       SelectObject(hDCMem, hpnBlack);
			       break;
		       }
			   if(pInfo->prghPen)
		           SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[iPrev % iPen]);
		       break;
		}
		iPrev = i;
		LineTo(hDCMem,xCurr,yCurr);
	      }
	      else
		 iPrev = i;     // remember the color for the first pixel
	   }
       }
       switch(i) {
	  case 1:
		  SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[0]);
		  break;
	  default:
	      if (iPrev >= pInfo->iIteration) {
		     SelectObject(hDCMem, hpnBlack);
		     break;
	      }
		  if (pInfo->prghPen)
	          SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[i % iPen]);
	      break;
       }

       LineTo(hDCMem,xCurr,yCurr);

       sprintf(gtext, GetStringRes (IDS_DRAWING), ((FLOAT)n/(FLOAT)rc.bottom)*100);
       SetWindowText(pInfo->hTextWnd, gtext);

       if (n >= iScan * iBand) {
	    BitBlt(hDC, 0, iScan * (iBand-1), rc.right, iScan, hDCMem, 0, iScan * (iBand-1), SRCCOPY);
	    iBand++;
       }
   }

   if ((iDiff = iScan * iBand - rc.bottom) != 0) {
	BitBlt(hDC, 0, iScan * (iBand-1), rc.right, iScan-iDiff, hDCMem, 0, iScan * (iBand-1), SRCCOPY);
   }

   sprintf(gtext, GetStringRes(IDS_DRAWING_DONE));

   SetWindowText(pInfo->hTextWnd, gtext);

   ReleaseDC(pInfo->hwnd, hDC);

   pInfo->dwElapsed = GetTickCount() - dwTick1;

   if (pInfo->hBmpSaved)
       DeleteObject(pInfo->hBmpSaved);

   pInfo->hBmpSaved = SelectObject(hDCMem, hOldBitmap);
   pInfo->bDrawing = FALSE;
#ifndef THRDONE
   if (pInfo->prghPen != NULL) {
       for (i = 0; i <= pInfo->iPen; i++) {
	   DeleteObject((HPEN) (pInfo->prghPen)[i]);
       }
       GlobalFree(pInfo->prghPen);
   }
#endif
   DeleteDC(hDCMem);

   ExitThread(0);
   return TRUE;
}

/**************************************************************************\
*
* StartDraw2
*                                            2
* Effects: Draw'g the Julia Set for Q (z) = z  + c, where z, c are complex
*
*          The Julia Set: Backward iteration algorithm.
*
* Warnings:
*
\**************************************************************************/

BOOL StartDraw2(PINFO pInfo)
{
   HDC         hDC;
   RECT        rc;
   int         m, n, i;
   double      c1, c2;
   double      x0, y0, w0, w1, pi, theta, r;

   pi = 22.0/7.0;
   c1 = 0.360284;
   c2 = 0.100376;
   x0 = 1.5;
   y0 = 1.5;

   hDC = GetDC(pInfo->hwnd);

   GetClientRect(pInfo->hwnd, &rc);
   for (i=0; i<=15000; i++) {
    w0 = x0 - c1;
    w1 = y0 - c2;
    sprintf( gtext,"w(%g, %g) xy(%g, %g)\n", w0, w1, x0, y0);
    OutputDebugString( gtext );

    if (w0 == 0.0) {
	theta = pi/2;
	sprintf( gtext,"(w0 == 0.0) theta = %g\n\n", theta);
	OutputDebugString( gtext );

    } else {
	if (w0 > 0.0) {
	    theta = atan(w1/w0);
	    sprintf( gtext,"(w0 > 0.0) theta = %g\n\n", theta);
	    OutputDebugString( gtext );

	} else { // w0 < 0.0
	    theta = pi + atan(w1/w0);
	    sprintf( gtext,"(w0 < 0.0) theta = %g\n\n", theta);
	    OutputDebugString( gtext );
	}
    }
    r = sqrt(w0 * w0 + w1 + w1);
    //theta = theta/2.0 + ((int) ((2.0*rand()/(RAND_MAX+1.0)))*pi);
    //theta = theta/2.0 + ((2.0*rand()/((double)RAND_MAX+1.0))*pi);
    r = sqrt(r);
    x0 = r*cos(theta);
    y0 = r*sin(theta);
    if (i > 50) {
	m = Xform2(x0, pInfo->xFrom, pInfo->xTo, 0.0, (double) rc.right);
	n = Xform2(y0, pInfo->yFrom, pInfo->yTo, 0.0, (double) rc.bottom);
	SetPixel(hDC, m, n, 0x000000ff);
    }
   }

   ReleaseDC(pInfo->hwnd, hDC);

   ExitThread(0);
   return TRUE;
}

/**************************************************************************\
*
* StartMandelbrotFix
*                                            2
* Effects: Draw'g the Mandelbrot Set for Q (z) = z  + c, where z, c complex
*
* Warnings:
\**************************************************************************/
BOOL StartMandelbrotFix(PINFO pInfo)
{
   DWORD       dwTick1;
   HDC         hDC;
   RECT        rc;
   int         m, n, i, iPrev;
   int         xCurr, yCurr;
   int         iPen;

   LONG c1, c2;
   LONG x1, y1, x, y, r;
#ifndef THRDONE
   INT      iNumClr;
#endif

   HDC          hDCMem;
   HBITMAP      hBitmap, hOldBitmap;

   int  iBand=1;
   int  iScan=0;
   int  iDiff=0;

   iPen = pInfo->iPen + 1;
   pInfo->bMandel = TRUE;
   pInfo->bDrawing = TRUE;
   hDC = GetDC(pInfo->hwnd);

#ifndef THRDONE
    if ((iNumClr = iCreatePenFrPal(hDC, NULL, 0, &(pInfo->hPal))) != 0) {
	sprintf( gtext,"iNumClr = %d\n", iNumClr);
	OutputDebugString( gtext);

	if ((pInfo->prghPen = (PVOID*) GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, sizeof(HPEN)*iNumClr)) == NULL) {
	    OutputDebugString ("Failed in Memory Allocation for pInfo->prghPen!");
	} else {
	    if ((pInfo->iPen = iCreatePenFrPal(hDC, pInfo->prghPen, 0, &(pInfo->hPal))) == 0)
		OutputDebugString ("Failed in creating pen!");
	}
    }

   hDCMem = CreateCompatibleDC(hDC);

   SelectPalette(hDCMem, pInfo->hPal, FALSE);
   SelectPalette(hDC,    pInfo->hPal, FALSE);
   RealizePalette(hDC);
   iPen = pInfo->iPen + 1;
#endif

   GetClientRect(pInfo->hwnd, &rc);

   hBitmap = CreateCompatibleBitmap(hDC, (int)rc.right, (int)rc.bottom);
   hOldBitmap = SelectObject(hDCMem, hBitmap);

   dwTick1 = GetTickCount();
   yCurr = rc.top;

   iScan = (((iScan = BATCH / rc.right) == 0) ? 1 : iScan);

   for (n=rc.top; n<=rc.bottom; n+=pInfo->iStep, yCurr+=pInfo->iStep, iPrev = FIRST_PIXEL) {
       xCurr = rc.left;                   // since LineTo excludes last point
       MoveToEx(hDCMem, 0, yCurr, NULL);
       c2 = XformFix(n, rc.top, rc.bottom, pInfo->lyFrom, pInfo->lyTo);

       for (m=rc.left; m<=rc.right; m++, xCurr++) {
	   c1 = XformFix(m, rc.left, rc.right, pInfo->lxFrom, pInfo->lxTo);
	   x = c1;
	   y = c2;

	   for (i=1; i<=pInfo->iIteration; i++) {
	       x1 = lMul(x - y, x + y) + c1;
	       y1 = (lMul(x, y) * 2) + c2;
	       r = lMul(x1, x1) + lMul(y1, y1);
	       x = x1;
	       y = y1;
	       if (r > 33554432) {
		   break;
	       }
	   }

	   if (i != iPrev) {
	       if (iPrev != FIRST_PIXEL) {
		 switch(iPrev) {
		   case 1:
			   SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[0]); break;
		   default:
		       if (iPrev >= pInfo->iIteration) {
			    SelectObject(hDCMem, hpnBlack);
			    break;
		       }
		       SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[iPrev % iPen]);
		       break;
		 }
		 iPrev = i;
		 LineTo(hDCMem, xCurr, yCurr);
	       }
	       else
		  iPrev = i;    // remember the color for the first pixel
	   }
       }

       switch(i) {
	   case 1:
	       SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[0]);
	       break;
	   default:
	       if (i >= pInfo->iIteration) {
		    SelectObject(hDCMem, hpnBlack);
		    break;
	       }
	       SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[i % iPen]);
	       break;
       }
       LineTo(hDCMem,xCurr,yCurr);

       sprintf(gtext, GetStringRes (IDS_DRAWING), ((FLOAT)n/(FLOAT)rc.bottom)*100);

       SetWindowText(pInfo->hTextWnd, gtext);

       if (n >= iScan * iBand) {
	    BitBlt(hDC, 0, iScan * (iBand-1), rc.right, iScan, hDCMem, 0, iScan * (iBand-1), SRCCOPY);
	    iBand++;
       }

   }

   if ((iDiff = iScan * iBand - rc.bottom) != 0) {
	BitBlt(hDC, 0, iScan * (iBand-1), rc.right, iScan-iDiff, hDCMem, 0, iScan * (iBand-1), SRCCOPY);
   }

   sprintf(gtext, GetStringRes (IDS_DRAWING_DONE));

   SetWindowText(pInfo->hTextWnd, gtext);

   ReleaseDC(pInfo->hwnd, hDC);

   pInfo->dwElapsed = GetTickCount() - dwTick1;

   if (pInfo->hBmpSaved)
       DeleteObject(pInfo->hBmpSaved);

   pInfo->hBmpSaved = SelectObject(hDCMem, hOldBitmap);
   pInfo->bDrawing = FALSE;

#ifndef THRDONE
   if (pInfo->prghPen != NULL) {
       for (i = 0; i <= pInfo->iPen; i++) {
	   DeleteObject((HPEN) (pInfo->prghPen)[i]);
       }
       GlobalFree(pInfo->prghPen);
   }
#endif

   DeleteDC(hDCMem);

   ExitThread(0);
   return TRUE;
}

/**************************************************************************\
*
* StartMandelbrot
*                                            2
* Effects: Draw'g the Mandelbrot Set for Q (z) = z  + c, where z, c complex
*
* Warnings:
*
\**************************************************************************/
BOOL StartMandelbrot(PINFO pInfo)
{
   DWORD       dwTick1;
   HDC         hDC;
   RECT        rc;
   int         m, n, i, iPrev;
   int         xCurr, yCurr;
   int         iPen;

#ifndef THRDONE
   INT      iNumClr;
   char     text[256];
#endif

   double c1, c2;
   double x1, y1, x, y, r;

   HDC          hDCMem;
   HBITMAP      hBitmap, hOldBitmap;

   int  iBand=1;
   int  iScan=0;
   int  iDiff=0;

   iPrev = 0;
   iPen = pInfo->iPen + 1;
   pInfo->bMandel = TRUE;
   pInfo->bDrawing = TRUE;
   hDC = GetDC(pInfo->hwnd);

#ifndef THRDONE
    if ((iNumClr = iCreatePenFrPal(hDC, NULL, 0, &(pInfo->hPal))) != 0) {
	sprintf( gtext,"iNumClr = %d\n", iNumClr);
	OutputDebugString( gtext);

	if ((pInfo->prghPen = (PVOID*) GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, sizeof(HPEN)*iNumClr)) == NULL) {
	    OutputDebugString ("Failed in Memory Allocation for pInfo->prghPen!");
	} else {
	    if ((pInfo->iPen = iCreatePenFrPal(hDC, pInfo->prghPen, 1, &(pInfo->hPal))) == 0)
		OutputDebugString ("Failed in creating pen!");
	}
    }

   hDCMem = CreateCompatibleDC(hDC);

   SelectPalette(hDCMem, pInfo->hPal, FALSE);
   SelectPalette(hDC,    pInfo->hPal, FALSE);
   RealizePalette(hDC);
   iPen = pInfo->iPen + 1;
   wsprintf(text, "iPen = %d\n", iPen);
   //MessageBox(ghwndMain, text, "Error", MB_OK);
#endif

   GetClientRect(pInfo->hwnd, &rc);

   hBitmap = CreateCompatibleBitmap(hDC, (int)rc.right, (int)rc.bottom);
   hOldBitmap = SelectObject(hDCMem, hBitmap);

#if 0
 {
   int iWidth, i, j;

   iWidth = rc.right/iNumClr;

   for (i = 0; i < iNumClr; i++) {
       SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[i % iNumClr]);
       for (j = 0; j < iWidth; j++) {
	    MoveToEx(hDCMem, i*iWidth+j, 0, NULL);
	    LineTo(hDCMem, i*iWidth+j, rc.bottom);
       }

   }
 }
#endif

   dwTick1 = GetTickCount();

   iScan = (((iScan = BATCH / rc.right) == 0) ? 1 : iScan);

   yCurr = rc.top;
   for (n=rc.top; n<=rc.bottom; n+=pInfo->iStep, yCurr+=pInfo->iStep, iPrev = FIRST_PIXEL) {
       xCurr = rc.left;                   // since LineTo excludes last point
       MoveToEx(hDCMem, 0, yCurr, NULL);
       c2 = Xform((double) n, 0.0, (double) rc.bottom, pInfo->yFrom, pInfo->yTo);

       for (m=rc.left; m<=rc.right; m++, xCurr++) {
	   c1 = Xform((double) m, 0.0, (double) rc.right, pInfo->xFrom, pInfo->xTo);
	   x = c1;
	   y = c2;

	   for (i=1; i<=pInfo->iIteration; i++) {
	       x1 = (x - y) * (x + y) + c1;
	       y1 = 2 * x * y + c2;
	       r = x1 * x1 + y1 * y1;
	       x = x1;
	       y = y1;
	       if (r > 4.0) {
		   break;
	       }
	   }

	   if (i != iPrev) {
	       if (iPrev != FIRST_PIXEL) {
		 switch(iPrev) {
		   case 1:
			   SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[0]);
		    break;
		   default:
		       if (iPrev >= pInfo->iIteration) {
			    SelectObject(hDCMem, hpnBlack);
			    break;
		       }
		       SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[iPrev % iPen]);
		       break;
		 }
		 iPrev = i;
		 LineTo(hDCMem, xCurr, yCurr);
	       }
	       else
		  iPrev = i;    // remember the color for the first pixel
	   }
       }

       switch(i) {
	      case 1:
		      SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[0]);
	       break;
	      default:
		  if (i >= pInfo->iIteration) {
		       SelectObject(hDCMem, hpnBlack);
		       break;
		  }
		  SelectObject(hDCMem, (HPEN)(pInfo->prghPen)[i % iPen]);
		  break;
       }

       LineTo(hDCMem,xCurr,yCurr);

       sprintf(gtext, GetStringRes (IDS_DRAWING), ((FLOAT)n/(FLOAT)rc.bottom)*100);

       SetWindowText(pInfo->hTextWnd, gtext);

       if (n >= iScan * iBand) {
	    BitBlt(hDC, 0, iScan * (iBand-1), rc.right, iScan, hDCMem, 0, iScan * (iBand-1), SRCCOPY);
	    iBand++;
       }
   }

   if ((iDiff = iScan * iBand - rc.bottom) != 0) {
	BitBlt(hDC, 0, iScan * (iBand-1), rc.right, iScan-iDiff, hDCMem, 0, iScan * (iBand-1), SRCCOPY);
   }

   sprintf(gtext, GetStringRes (IDS_DRAWING_DONE));

   SetWindowText(pInfo->hTextWnd, gtext);

   ReleaseDC(pInfo->hwnd, hDC);

   pInfo->dwElapsed = GetTickCount() - dwTick1;

   if (pInfo->hBmpSaved)
       DeleteObject(pInfo->hBmpSaved);

   pInfo->hBmpSaved = SelectObject(hDCMem, hOldBitmap);
   pInfo->bDrawing = FALSE;
#ifndef THRDONE
   if (pInfo->prghPen != NULL) {
       for (i = 0; i <= pInfo->iPen; i++) {
	   DeleteObject((HPEN) (pInfo->prghPen)[i]);
       }
       GlobalFree(pInfo->prghPen);
   }
#endif

   DeleteDC(hDCMem);

   ExitThread(0);
   return TRUE;
}


/******************************Public*Routine******************************\
*
* Xform
*
* Effects: Given m, find x.
*
*          Xform(Pt) : Src |--> Dest
* eg.
*          Src |----|--------|      |-->   Dest |----|--------|
*              -2   x        2                  0    m       320
*
*          x = (m - 0)/(320 - 0) * (2 - -2) + -2
*
* Warnings: 1. This will become a macro in the future for speed.  For now,
*              it is here for debugging purposes.
*
\**************************************************************************/
#if 0
double Xform(
   double Pt,
   double SrcFrom,
   double SrcTo,
   double DestFrom,
   double DestTo)
{
 //sprintf( gtext,"%g = Xform(%g, %g, %g, %g, %g)\n", ((Pt-SrcFrom)/(SrcTo-SrcFrom)*(DestTo-DestFrom))+DestFrom, Pt, SrcFrom, SrcTo, DestFrom, DestTo);
 //OutputDebugString( gtext );
 return(((Pt-SrcFrom)/(SrcTo-SrcFrom)*(DestTo-DestFrom))+DestFrom);
}
#endif

/******************************Public*Routine******************************\
*
* Xform2
*
* Effects: Given x, find m.
*
*          Xform(Pt) : Src |--> Dest
* eg.
*          Src |----|--------|      |-->   Dest |----|--------|
*              -2   x        2                  0    m       320
*
*          m = (x - -2)/(2 - -2) * 320
*
* Warnings: 1. This will become a macro in the future for speed.  For now,
*              it is here for debugging purposes.
*
\**************************************************************************/
#if 0
int Xform2(
   double Pt,
   double SrcFrom,
   double SrcTo,
   double DestFrom,
   double DestTo)
{
 //sprintf( gtext,"%g = Xform(%g, %g, %g, %g, %g)\n", ((Pt-SrcFrom)/(SrcTo-SrcFrom)*(DestTo-DestFrom))+DestFrom, Pt, SrcFrom, SrcTo, DestFrom, DestTo);
 //OutputDebugString( gtext );
 return((int) ((Pt-SrcFrom)/(SrcTo-SrcFrom)*(DestTo-DestFrom)+DestFrom));
}
#endif

/******************************Public*Routine******************************\
*
* SaveBitmap
*
* Effects:  Returns the handle of a bitmap corresponding to the window.
*           using utilizing BitBlt.
*
* Warnings:
*   // should we set the dirty flag here?
*
*
\**************************************************************************/

HBITMAP SaveBitmap(HWND hWnd, HPALETTE hPal) {
    HDC     hdcMem, hDC;
    HBITMAP hBitmap, hOldBitmap;
    RECT    rc;
    HPALETTE hPalOld, hPalMemOld;
    int     ii;

    hDC = GetDC(hWnd);
    GetClientRect(hWnd, &rc);

    if (hPal) {

	hPalOld = SelectPalette(hDC, hPal, FALSE);
	ii=RealizePalette(hDC);
	if (ii){
	    UpdateColors (hDC);
	}

    }

    hdcMem = CreateCompatibleDC(hDC);

    if (hPal) {

	hPalMemOld = SelectPalette(hdcMem, hPal, FALSE);
	RealizePalette(hdcMem);
    }

    hBitmap = CreateCompatibleBitmap(hDC, (int)rc.right-rc.left, (int)rc.bottom-rc.top);

    hOldBitmap = SelectObject(hdcMem, hBitmap);


    BitBlt(hdcMem, 0, 0, (int)rc.right-rc.left, (int)rc.bottom-rc.top, hDC, 0, 0, SRCCOPY);
    hBitmap = SelectObject(hdcMem, hOldBitmap);

    DeleteDC(hdcMem);
    ReleaseDC(hWnd, hDC);

    return(hBitmap);

}

/******************************Public*Routine******************************\
*
* DrawBitmap
*
* Effects:
*
* Warnings:
*
\**************************************************************************/

void DrawBitmap(HDC hdc, PINFO pInfo, int xStart, int yStart, int cx, int cy) {
    BITMAP bm;
    HDC    hdcMem;
    POINT  ptSize, ptOrg;
    HPALETTE hPalOld, hPalMemOld;
    char    text[128];

    if ((pInfo->hPal) && !(pInfo->bUseMono)) {

	hPalOld = SelectPalette(hdc,
	     ((pInfo->iStretchMode == HALFTONE) ? pInfo->hHTPal : pInfo->hPal),
	     FALSE);
	//RealizePalette(hdc);

	wsprintf(text, "Realized Palette = %d", RealizePalette(hdc));

	OutputDebugString (text);


	UpdateColors (hdc);
    }

    hdcMem = CreateCompatibleDC(hdc);

    if ((pInfo->hPal) && !(pInfo->bUseMono)) {

	hPalMemOld = SelectPalette(hdcMem,
	     ((pInfo->iStretchMode == HALFTONE) ? pInfo->hHTPal : pInfo->hPal),
	      FALSE);
	//RealizePalette(hdcMem);
	wsprintf(text, "Realized Palette = %d", RealizePalette(hdcMem));
	OutputDebugString (text);


	UpdateColors (hdcMem);



    }

    SelectObject(hdcMem, (pInfo->bUseMono ? pInfo->hBmpMono : pInfo->hBmpSaved));
    SetMapMode(hdcMem, GetMapMode(hdc));

    GetObject((pInfo->bUseMono ? pInfo->hBmpMono : pInfo->hBmpSaved), sizeof(BITMAP), (LPSTR)&bm);
    ptSize.x = bm.bmWidth;
    ptSize.y = bm.bmHeight;
    DPtoLP(hdc, &ptSize, 1);

    ptOrg.x = 0;
    ptOrg.y = 0;
    DPtoLP(hdcMem, &ptOrg, 1);

    if (pInfo->bStretch) {
	SetStretchBltMode(hdc, pInfo->iStretchMode);
	// cx+1 and cy+1: temporary work around for a bug!
	StretchBlt(hdc, xStart, yStart, cx+1, cy+1,
	       hdcMem, ptOrg.x, ptOrg.y, ptSize.x, ptSize.y,SRCCOPY);
    } else {
	BitBlt(hdc, xStart, yStart, ptSize.x, ptSize.y,
	       hdcMem, xStart, yStart, SRCCOPY);
    }

    if (pInfo->bUseMono)
	pInfo->bUseMono = FALSE;

    DeleteDC(hdcMem);
    UNREFERENCED_PARAMETER(cx);
    UNREFERENCED_PARAMETER(cy);
}

/******************************Public*Routine******************************\
*
* bDrawDIB
*
* Effects:
*
* Warnings:
*
\**************************************************************************/

BOOL bDrawDIB(HDC hDC, PINFO pInfo, int xStart, int yStart, int cx, int cy)
{
    HBITMAP     hBmpOld, hBmp;
    BOOL        bSuccess;
    PBITMAPINFO pbmi;
    HDC         hdcMem;
    BITMAP      bm;

    bSuccess = TRUE;
    if (pInfo->bUseMono) {
	DrawBitmap(hDC, pInfo, xStart, yStart, cx, cy);
	return bSuccess;
    }

    if ((hBmp = pInfo->hBmpSaved) == NULL) {

		MessageBox(ghwndMain, GetStringRes (IDS_NO_BITMAP_TO_DRAW), 
			       NULL, MB_OK);
		return FALSE;
    }

    if (pInfo->bStretch) {
	SetStretchBltMode(hDC, pInfo->iStretchMode);

	if (pInfo->bUseDIB) { // this'll give a src for halftone...
	    pbmi = (PBITMAPINFO) (pInfo->RleData.rgpbmi[0]);

	    // Select and realize the appropriate palette to destination DC
	    if ((pInfo->iStretchMode == HALFTONE) && (pInfo->hHTPal)) {
		SelectPalette(hDC, pInfo->hHTPal, FALSE);
		RealizePalette(hDC);
	    } else {
		if ((pInfo->iStretchMode != HALFTONE) && (pInfo->hPal)) {
		    SelectPalette(hDC, pInfo->hPal, FALSE);
		    RealizePalette(hDC);
		}
	    }
	    if (pInfo->bCoreHdr) {
		StretchDIBits(hDC, xStart, yStart, cx, cy,
			  0, 0, ((LPBITMAPCOREINFO)pbmi)->bmciHeader.bcWidth,
				((LPBITMAPCOREINFO)pbmi)->bmciHeader.bcHeight,
			  (LPSTR)pInfo->RleData.rgpjFrame[0], pbmi, DIB_RGB_COLORS, SRCCOPY);
	    } else {
		StretchDIBits(hDC, xStart, yStart, cx, cy,
			  0, 0, pbmi->bmiHeader.biWidth, pbmi->bmiHeader.biHeight,
			  (LPSTR)pInfo->RleData.rgpjFrame[0], pbmi, DIB_RGB_COLORS, SRCCOPY);
	    }
	} else { // image is dirty or created on this device

	    HBITMAP     hDIB;

	    //
	    // Get the source DIB info from the DDB for halftoning
	    //
	    hDIB = DIBfromDDB(hDC, hBmp, pInfo);

	    hdcMem = CreateCompatibleDC(hDC);
	    hBmpOld = SelectObject(hdcMem, hDIB);

	    if ((pInfo->iStretchMode == HALFTONE) && (pInfo->hHTPal)) {
		SelectPalette(hDC, pInfo->hHTPal, FALSE);
		RealizePalette(hDC);
	    } else {
		if ((pInfo->iStretchMode != HALFTONE) && (pInfo->hPal)) {
		    SelectPalette(hDC, pInfo->hPal, FALSE);
		    RealizePalette(hDC);
		}
	    }

	    //
	    // Use StretchBlt here instead of StretchDIBits just for
	    // demonstrating using the API with halftone
	    //
	    GetObject(hDIB, sizeof(BITMAP), (LPSTR)&bm);
	    StretchBlt(hDC, xStart, yStart, cx, cy, hdcMem,
			  0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

	    DeleteDC(hdcMem);

	}
	return bSuccess;
    }

    //
    // Not stretching...No halftone
    //

    GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);

    // Select and realize the appropriate palette to destination DC
    if (pInfo->hPal) {
	SelectPalette(hDC, pInfo->hPal, FALSE);
	RealizePalette(hDC);
    }

    if (pInfo->bUseDIB) { // this'll give a src
	pbmi = (PBITMAPINFO) (pInfo->RleData.rgpbmi[0]);

	// default to use SetDIBitsToDevice
	SetDIBitsToDevice(hDC, xStart, yStart, bm.bmWidth, bm.bmHeight,
		      0, 0, 0, bm.bmHeight, pInfo->RleData.rgpjFrame[0],
		      pbmi, DIB_RGB_COLORS);
    } else { // image is dirty or created on this device

	hdcMem = CreateCompatibleDC(hDC);
	hBmpOld = SelectObject(hdcMem, hBmp);

	BitBlt(hDC, xStart, yStart, bm.bmWidth, bm.bmHeight,
	       hdcMem, 0, 0, SRCCOPY);

	DeleteDC(hdcMem);
    }

    return bSuccess;
}

/******************************Public*Routine******************************\
*
* pGetInfoData(HWND hwnd)
*
* Effects:  calls LocalLock, returning pointer to Info structure.
*           assumes hwnd contains handle to Info structure at index 0.
*           should call bReleaseInfoData when done.
*           Global alert: ghwndMain used.
*
* Warnings:
*
\**************************************************************************/

PINFO pGetInfoData(HWND hwnd)
{
    HANDLE hInfo;
    PINFO  pInfo;

    hInfo = (HANDLE) GetWindowLong(hwnd, 0);
    if (hInfo == NULL) {
	OutputDebugString ("Null Info handle retrieved - GetInfo");
	return NULL;
    }

    if ((pInfo = (PINFO)LocalLock(hInfo)) == NULL) {
	return NULL;
    }

    return pInfo;
}

/******************************Public*Routine******************************\
*
* bReleaseInfoData(HWND hwnd)
*
* Effects: calls LocalUnlock.  Returns whatever LocalUnlock returns.
*
* Warnings: assumes LocalLock was called previously.
*           assumes hwnd contains handle to Info structure at index 0.
*           Global alert: ghwndMain used.
*
\**************************************************************************/

BOOL bReleaseInfoData(HWND hwnd)
{
    HANDLE hInfo;

    hInfo = (HANDLE) GetWindowLong(hwnd, 0);
    if (hInfo == NULL) {
	OutputDebugString ("Null Info handle retrieved - ReleaseInfo");
	return FALSE;
    }

    return (LocalUnlock(hInfo));
}


/******************************Public*Routine******************************\
*
* bCheckMutexMenuItem
*
* Effects: Put a check mark on uiCheckItem in the hMenu.  Remove previous
*          check mark, if any, on items in the same group.  Returns TRUE
*          if successful, FALSE otherwise (item not exists).
*
* Warnings:
*
\**************************************************************************/

BOOL bCheckMutexMenuItem(PINFO pInfo, HMENU hMenu, UINT uiCheckItem)
{

    switch(uiCheckItem) {
	case MM_TP_IDLE:
	case MM_TP_LOW:
	case MM_TP_BELOW_NORMAL:
	case MM_TP_NORMAL:
	case MM_TP_ABOVE_NORMAL:
	case MM_TP_HIGH:
	case MM_TP_TIME_CRITICAL:
	    switch (pInfo->iPriority) {
		case THREAD_PRIORITY_IDLE:
		    CheckMenuItem(hMenu, MM_TP_IDLE, MF_UNCHECKED);
		    break;
		case THREAD_PRIORITY_LOWEST:
		    CheckMenuItem(hMenu, MM_TP_LOW, MF_UNCHECKED);
		    break;
		case THREAD_PRIORITY_BELOW_NORMAL:
		    CheckMenuItem(hMenu, MM_TP_BELOW_NORMAL, MF_UNCHECKED);
		    break;
		case THREAD_PRIORITY_NORMAL:
		    CheckMenuItem(hMenu, MM_TP_NORMAL, MF_UNCHECKED);
		    break;
		case THREAD_PRIORITY_ABOVE_NORMAL:
		    CheckMenuItem(hMenu, MM_TP_ABOVE_NORMAL, MF_UNCHECKED);
		    break;
		case THREAD_PRIORITY_HIGHEST:
		    CheckMenuItem(hMenu, MM_TP_HIGH, MF_UNCHECKED);
		    break;
		case THREAD_PRIORITY_TIME_CRITICAL:
		    CheckMenuItem(hMenu, MM_TP_TIME_CRITICAL, MF_UNCHECKED);
		    break;
		default:
		    break;
	    }
	    break;
	case MM_FLOAT:
	case MM_FIX:
	    CheckMenuItem(hMenu, MM_FLOAT, MF_UNCHECKED);
	    CheckMenuItem(hMenu, MM_FIX,   MF_UNCHECKED);
	    break;
	case MM_ITERATION_100:
	case MM_ITERATION_500:
	case MM_ITERATION_1000:
	case MM_ITERATION_5000:
	case MM_ITERATION_DOUBLE:
	    switch (pInfo->iIteration) {
		case 100:
		    CheckMenuItem(hMenu, MM_ITERATION_100, MF_UNCHECKED);
		    break;
		case 500:
		    CheckMenuItem(hMenu, MM_ITERATION_500, MF_UNCHECKED);
		    break;
		case 1000:
		    CheckMenuItem(hMenu, MM_ITERATION_1000, MF_UNCHECKED);
		    break;
		case 5000:
		    CheckMenuItem(hMenu, MM_ITERATION_5000, MF_UNCHECKED);
		    break;
		default:
		    CheckMenuItem(hMenu, MM_ITERATION_DOUBLE, MF_UNCHECKED);
		    break;
	    }
	    break;
	case MM_STEP_ONE:
	case MM_STEP_TWO:
	case MM_STEP_THREE:
	    switch (pInfo->iStep) {
		case 1:
		    CheckMenuItem(hMenu, MM_STEP_ONE, MF_UNCHECKED);
		    break;
		case 2:
		    CheckMenuItem(hMenu, MM_STEP_TWO, MF_UNCHECKED);
		    break;
		default:
		    CheckMenuItem(hMenu, MM_STEP_THREE, MF_UNCHECKED);
		    break;
	    }
	    break;
	case MM_STRETCHBLT:
	case MM_BITBLT:
		CheckMenuItem(hMenu, MM_STRETCHBLT,   MF_UNCHECKED);
		CheckMenuItem(hMenu, MM_BITBLT,       MF_UNCHECKED);
	    break;
	case MM_BLACKONWHITE:
	case MM_COLORONCOLOR:
	case MM_WHITEONBLACK:
	case MM_HALFTONE:
	    switch (pInfo->iStretchMode) {
		case BLACKONWHITE:
		    CheckMenuItem(hMenu, MM_BLACKONWHITE, MF_UNCHECKED);
		    break;
		case COLORONCOLOR:
		    CheckMenuItem(hMenu, MM_COLORONCOLOR, MF_UNCHECKED);
		    break;
		case WHITEONBLACK:
		    CheckMenuItem(hMenu, MM_WHITEONBLACK, MF_UNCHECKED);
		    break;
		case HALFTONE:
		    CheckMenuItem(hMenu, MM_HALFTONE, MF_UNCHECKED);
		    break;
		default:
		    break;
	    }
	    break;
	case MM_PORTRAIT:
	case MM_LANDSCAPE:
		CheckMenuItem(hMenu, MM_PORTRAIT,   MF_UNCHECKED);
		CheckMenuItem(hMenu, MM_LANDSCAPE,  MF_UNCHECKED);
	    break;
	default:
	    return FALSE;
    }
    CheckMenuItem(hMenu, uiCheckItem, MF_CHECKED);
    return TRUE;
}


/******************************Public*Routine******************************\
*
* vChkMenuItem
*
* Effects:  Helper function for checking or unchecking menu items based on
*           values set in the pInfo.  Gets called when processing
*           WM_MDIACTIVATE
*
* Warnings:
*
\**************************************************************************/

VOID vChkMenuItem(PINFO pInfo, HMENU hMenu, UINT uiFlag)
{
    (pInfo->bStretch ?
	CheckMenuItem(hMenu, MM_STRETCHBLT, uiFlag) :
	CheckMenuItem(hMenu, MM_BITBLT, uiFlag) );

    switch (pInfo->iPriority) {
	case THREAD_PRIORITY_IDLE:
	    CheckMenuItem(hMenu, MM_TP_IDLE, uiFlag);
	    break;
	case THREAD_PRIORITY_LOWEST:
	    CheckMenuItem(hMenu, MM_TP_LOW, uiFlag);
	    break;
	case THREAD_PRIORITY_BELOW_NORMAL:
	    CheckMenuItem(hMenu, MM_TP_BELOW_NORMAL, uiFlag);
	    break;
	case THREAD_PRIORITY_NORMAL:
	    CheckMenuItem(hMenu, MM_TP_NORMAL, uiFlag);
	    break;
	case THREAD_PRIORITY_ABOVE_NORMAL:
	    CheckMenuItem(hMenu, MM_TP_ABOVE_NORMAL, uiFlag);
	    break;
	case THREAD_PRIORITY_HIGHEST:
	    CheckMenuItem(hMenu, MM_TP_HIGH, uiFlag);
	    break;
	case THREAD_PRIORITY_TIME_CRITICAL:
	    CheckMenuItem(hMenu, MM_TP_TIME_CRITICAL, uiFlag);
	    break;
	default:
	    break;
    }

    switch (pInfo->iStretchMode) {
	case BLACKONWHITE:
	    CheckMenuItem(hMenu, MM_BLACKONWHITE, uiFlag);
	    break;
	case COLORONCOLOR:
	    CheckMenuItem(hMenu, MM_COLORONCOLOR, uiFlag);
	    break;
	case WHITEONBLACK:
	    CheckMenuItem(hMenu, MM_WHITEONBLACK, uiFlag);
	    break;
	case HALFTONE:
	    CheckMenuItem(hMenu, MM_HALFTONE, uiFlag);
	    break;
	default:
	    break;
    }

    switch (pInfo->iStep) {
	case 1:
	    CheckMenuItem(hMenu, MM_STEP_ONE, uiFlag);
	    break;
	case 2:
	    CheckMenuItem(hMenu, MM_STEP_TWO, uiFlag);
	    break;
	default:
	    CheckMenuItem(hMenu, MM_STEP_THREE, uiFlag);
	    break;
    }

    switch (pInfo->iIteration) {
	case 100:
	    CheckMenuItem(hMenu, MM_ITERATION_100, uiFlag);
	    break;
	case 500:
	    CheckMenuItem(hMenu, MM_ITERATION_500, uiFlag);
	    break;
	case 1000:
	    CheckMenuItem(hMenu, MM_ITERATION_1000, uiFlag);
	    break;
	case 5000:
	    CheckMenuItem(hMenu, MM_ITERATION_5000, uiFlag);
	    break;
	default:
	    CheckMenuItem(hMenu, MM_ITERATION_DOUBLE, uiFlag);
	    break;
    }
    return;
}

/******************************Public*Routine******************************\
*
* bInitInfo
*
* Effects: Initialize the Info data structure
*
* Warnings:
*
\**************************************************************************/

BOOL bInitInfo(PINFO pInfo)
{
    pInfo->hParent      = ghwndClient;
    pInfo->xFrom        = -2.0;
    pInfo->xTo          = 1.0;
    pInfo->yFrom        = 1.5;
    pInfo->yTo          = -1.5;
    pInfo->lxFrom       = -16777216;                 // 9.23 fix point
    pInfo->lxTo         =  8388608;                  // representation of
    pInfo->lyFrom       =  12582912;                 // -2, 1.0, 1.5, and -1.5
    pInfo->lyTo         = -12582912;                 //
    pInfo->iIteration   = gIteration;
    pInfo->iStep        = gStep;
    pInfo->bStretch     = gbStretch;
    pInfo->iStretchMode = giStretchMode;
    wsprintf((LPSTR) &(pInfo->CaptionBarText), "");
    pInfo->hwnd         = NULL;
    pInfo->hTextWnd     = NULL;
    pInfo->rcClient.top    = 0;
    pInfo->rcClient.left   = 0;
    pInfo->rcClient.bottom = 0;
    pInfo->rcClient.right  = 0;
    pInfo->hdcClient    = NULL;
    pInfo->hRgnPath     = NULL;
    pInfo->hThrd0       = NULL;
    pInfo->hThrd        = NULL;
    pInfo->bDrawing     = FALSE;
    pInfo->dwThreadId   = 0;
    pInfo->dwElapsed    = 0L;
    pInfo->c1           = 0.0;
    pInfo->c2           = 0.0;
    pInfo->lc1          = 0L;
    pInfo->lc2          = 0L;
    pInfo->hBmpSaved    = NULL;
    pInfo->bSizeChng    = FALSE;
    pInfo->bMandel      = TRUE;
    pInfo->bSetDIBsToDevice = FALSE;
    pInfo->bFill        = FALSE;
    pInfo->hBrush       = NULL;
    pInfo->hQuitEvent   = NULL;
    pInfo->hCycleThrd   = NULL;
    pInfo->dwCycleThrdID = 0;
    pInfo->bClrCycle    = FALSE;
    pInfo->bFirstTime   = TRUE;
    pInfo->dwSuspend    = 0;
    pInfo->hBmpMono     = NULL;
    pInfo->bUseMono     = FALSE;
    pInfo->hPrtThrd     = NULL;
    pInfo->dwPrtThrdID  = 0;
    pInfo->hPal         = NULL;
    pInfo->hCyclePal    = NULL;
    pInfo->RleData.ulFiles  = 0;
    pInfo->RleData.ulFrames = 0;
    pInfo->bPlayRleCont = FALSE;
    pInfo->prghPen      = NULL;
    pInfo->iPen         = 0;
    pInfo->iPriority    = THREAD_PRIORITY_NORMAL;
    pInfo->bUseDIB      = FALSE;
    pInfo->bCoreHdr     = FALSE;

    return TRUE;
}

/******************************Public*Routine******************************\
*
* bResetGlobal
*
* Effects: Set (l) x/y From/To to their default values
*          Used for Julia set
*
* Warnings:
*
\**************************************************************************/

BOOL bResetGlobal(VOID)
{
    xFrom  =  -2.0;
    xTo    =   2.0;
    yFrom  =   2.0;
    yTo    =  -2.0;
    lxFrom =  -16777216;
    lxTo   =   16777216;
    lyFrom =   16777216;
    lyTo   =  -16777216;
    return TRUE;
}

/******************************Public*Routine******************************\
*
* hBrCreateBrush
*
* Effects: Creates a brush with the specified RGB
*
* Warnings:
*
\**************************************************************************/

HBRUSH hBrCreateBrush(HDC hDC, DWORD dwRGB)
{
    HDC hdcMem;
    HBRUSH hbr;
    HBRUSH hbrOld;
    HBITMAP hbmPat;
    HBITMAP hbmOld;

    hbr = CreateSolidBrush(dwRGB);
    hdcMem = CreateCompatibleDC(hDC);

    //
    // Minimum size for a bitmap to be used in a fill pattern is 8x8
    //
    hbmPat = CreateCompatibleBitmap(hDC, 8, 8);

    hbmOld = SelectObject(hdcMem, hbmPat);
    hbrOld = SelectObject(hdcMem, hbr);
    PatBlt(hdcMem, 0, 0, 8, 8, PATCOPY);

    //
    // Deselect hbmPat and hbr
    //
    SelectObject(hdcMem, hbmOld);
    SelectObject(hdcMem, hbrOld);

    DeleteDC(hdcMem);
    DeleteObject(hbr);

    hbr = CreatePatternBrush(hbmPat);

    DeleteObject(hbmPat);

    return hbr;
}


/******************************Public*Routine******************************\
*
* bPrintBmp
*
* Effects: A Thread routine for printing bitmap
*
* Warnings:
*
\**************************************************************************/

BOOL bPrintBmp(PPRTDATA pPrtData) {
    HDC         hdcPrinter;
    int         iWidth, iHeight;

#ifdef NEWPRTAPI
    DOCINFO     DocInfo;
#endif

    if (pPrtData->bUseDefault) {
	  hdcPrinter = CreateDC( "", gpszPrinterNames[pPrtData->index],
				 "", NULL);
    } else {
	  hdcPrinter = CreateDC( "", gpszPrinterNames[pPrtData->index],
				 "", &(pPrtData->DevMode));
    }

    if (!hdcPrinter)
    {
	ExitThread(0);
	return(FALSE);
    }

    iWidth = GetDeviceCaps(hdcPrinter, HORZRES);
    iHeight = GetDeviceCaps(hdcPrinter, VERTRES);

#ifdef NEWPRTAPI

    memset(&DocInfo, 0, sizeof(DOCINFO));
    DocInfo.cbSize      = sizeof(DOCINFO);
    DocInfo.lpszDocName = pPrtData->info.CaptionBarText;
    DocInfo.lpszOutput   = NULL;
    StartDoc(hdcPrinter, &DocInfo);
    StartPage(hdcPrinter);
    bDrawDIB(hdcPrinter, &(pPrtData->info), 0, 0, iWidth, iHeight);
    EndPage(hdcPrinter);
    EndDoc(hdcPrinter);

#else

    Escape(hdcPrinter, STARTDOC, 20, "Mandelbrot", NULL);
    bDrawDIB(hdcPrinter, &(pPrtData->info), 0, 0, iWidth, iHeight);
    Escape(hdcPrinter, NEWFRAME, 0, NULL, NULL);
    Escape(hdcPrinter, ENDDOC, 0, NULL, NULL);

#endif

    DeleteDC(hdcPrinter);
    ExitThread(0);
    return(TRUE);

}



/******************************Public*Routine******************************\
*
* StoreRleFile
*
* Effects:
*
* Warnings:
*
\**************************************************************************/

BOOL bStoreRleFile(HDC hDC, PINFO pInfo, PSTR pszFileName)
{
  BOOL                bSuccess;
  HANDLE              hFile, hMapFile;
  LPVOID              pMapFile;
  LPBITMAPINFOHEADER  pbmh;
  LPBITMAPINFO        pbmi;
  PBYTE               pjTmp, pjDIBits, pjRleBits;
  ULONG               sizBMI, sizImage, ulfSize;
  DWORD               dwOffBits;
  LONG                lScan;
  INT                 iNumClr;
  ULONG               ulFrames, ulFiles, ulOffset;
  PFILEINFO           pFileInfo;
  DWORD               dwFileSizeLow, dwFileSizeHigh;
  WORD                wBitCount;
  BOOL                bCoreHdr;

  bSuccess = TRUE;

  if ((hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
	  OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL)) == (HANDLE)-1) {
      bSuccess = FALSE;
      goto ErrExit1;
  }

  dwFileSizeLow = GetFileSize(hFile, &dwFileSizeHigh);
  if ((dwFileSizeLow == 0xFFFFFFFF) && (GetLastError() != NO_ERROR)) {
      bSuccess = FALSE;
      goto ErrExit2;
  }

  //
  // Create a map file of the opened file
  //
  if ((hMapFile = CreateFileMapping(hFile, NULL,
			   PAGE_READONLY, 0, 0, NULL)) == (HANDLE)-1) {
      bSuccess = FALSE;
      goto ErrExit2;
  }

  //
  // Map a view of the whole file
  //
  if ((pMapFile = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0)) == NULL) {
      bSuccess = FALSE;
      goto ErrExit3;
  }

  ulFiles = pInfo->RleData.ulFiles;
  pFileInfo = &(pInfo->RleData.rgFileInfo[ulFiles]);
  pFileInfo->hFile = hFile;
  pFileInfo->hMapFile = hMapFile;
  pFileInfo->lpvMapView = pMapFile;

  ulFrames = pInfo->RleData.ulFrames;
  ulOffset = 0;

  while (TRUE) {
    //
    // First check that it is a bitmap file
    //
    if (*((PWORD)pMapFile) != 0x4d42) {              // 'BM'
	OutputDebugString ("This is not a DIB bitmap file!");
	bSuccess = FALSE;
	goto ErrExit3;
    }
#ifdef DEBUG
    {
    static ULONG ulCnt=0;
    char buf[128];

    ulCnt++;
    wsprintf(buf, "ulCnt = %ld", ulCnt);
    OutputDebugString (buf);
    }
#endif
    //
    // Saving the bfSize field in the BITMAPFILEHEADER for incrementing to the
    // next frame.  bfSize does not start at DWORD boundary...
    //
    {
      PBYTE   pjTmp;
      FILEHDR fHdr, *pfHdr;
      ULONG   ulSiz;

      pjTmp = (PBYTE)pMapFile+2;
      pfHdr = &fHdr;

      ulSiz = sizeof(FILEHDR);
      while (ulSiz--) {
	  *(((PBYTE)pfHdr)++) = *(((PBYTE)pjTmp)++);
      }
      ulfSize = fHdr.bfSize;
      dwOffBits = fHdr.bfOffbits;
    }

    //
    // advance pMapFile to point pass BITMAPFILEHEADER
    //
    //pMapFile = (PBYTE)pMapFile + sizeof(BITMAPFILEHEADER);

    //
    // Since the file header doesn't end on DWORD boundary...
    //
    pbmh = (LPBITMAPINFOHEADER)((PBYTE)pMapFile + sizeof(BITMAPFILEHEADER));

    {
	BITMAPCOREHEADER bmch, *pbmch;
	BITMAPINFOHEADER bmih, *pbmih;
	PBYTE            pjTmp;
	ULONG            ulSiz;

	pbmch = &bmch;
	pbmih = &bmih;

	pjTmp = (PBYTE)pbmh;
	ulSiz = sizeof(BITMAPCOREHEADER);
	while (ulSiz--) {
	    *(((PBYTE)pbmch)++) = *(((PBYTE)pjTmp)++);
	}

	pjTmp = (PBYTE)pbmh;
	ulSiz = sizeof(BITMAPINFOHEADER);
	while (ulSiz--) {
	    *(((PBYTE)pbmih)++) = *(((PBYTE)pjTmp)++);
	}

	//
	// Use the size to determine if it is a BitmapCoreHeader or
	// BitmapInfoHeader
	//
	if (bmch.bcSize == sizeof(BITMAPCOREHEADER))
	{
	    wBitCount = bmch.bcBitCount;
	    iNumClr = ((wBitCount == 24) ? 0 : (1 << wBitCount));
	    sizBMI = sizeof(BITMAPCOREHEADER)+sizeof(RGBTRIPLE)*iNumClr;
	    bCoreHdr = TRUE;
	}
	else            // BITMAPINFOHEADER
	{
	    wBitCount = bmih.biBitCount;
	    switch (wBitCount) {
		case 16:
		case 32:
		    sizBMI = sizeof(BITMAPINFOHEADER)+sizeof(DWORD)*3;
		    break;
		case 24:
		    sizBMI = sizeof(BITMAPINFOHEADER);
		    break;
		default:
		    iNumClr = (1 << wBitCount);
		    sizBMI = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*iNumClr;
		    break;
	    }
	    bCoreHdr = FALSE;
	}
    }

    if ((pbmi = (LPBITMAPINFO) LocalAlloc(LMEM_FIXED,sizBMI)) == NULL) {
		bSuccess = FALSE;
		goto ErrExit3;
    }

    //
    // Make sure we pass in a DWORD aligned BitmapInfo to CreateDIBitmap
    // Otherwise, exception on the MIPS platform
    // CR!!!  Equivalent to memcpy
    //
    pjTmp = (PBYTE)pbmi;

    while(sizBMI--)
    {
	*(((PBYTE)pjTmp)++) = *(((PBYTE)pbmh)++);
    }

    //
    // assuming CreateDIBitmap() is doing a byte fetch...
    //
    pjDIBits = (PBYTE)pMapFile + dwOffBits;

    if (pbmi->bmiHeader.biCompression == BI_RGB)
    {
    //
    // Converting to RLE bits...
    //

	OutputDebugString ("Converting to RLE format!");
	lScan = pbmi->bmiHeader.biHeight;
	sizImage = pbmi->bmiHeader.biSizeImage;

	//
	// select the palette into the DC first...
	//
	bSelectDIBPal(hDC, pInfo, pbmi, bCoreHdr);
	if ((pInfo->hBmpSaved = CreateDIBitmap(hDC, (LPBITMAPINFOHEADER)pbmi,
			    CBM_INIT, pjDIBits, pbmi, DIB_RGB_COLORS)) == NULL) {
	    bSuccess = FALSE;
	    goto ErrExit4;
	}

	// We want to retrieve the RLE format...
	pbmi->bmiHeader.biCompression = ((wBitCount==4) ? BI_RLE4 : BI_RLE8);

	pbmi->bmiHeader.biSizeImage = 0;
	pbmi->bmiHeader.biXPelsPerMeter = 0;
	pbmi->bmiHeader.biYPelsPerMeter = 0;
	pbmi->bmiHeader.biClrUsed = 0;
	pbmi->bmiHeader.biClrImportant = 0;

	if (GetDIBits(hDC, pInfo->hBmpSaved, 0, lScan, NULL, pbmi,
	    DIB_RGB_COLORS) == 0) {
	     OutputDebugString ("Not all scans are converted!");
	     bSuccess = FALSE;
	     goto ErrExit4;
	}

	if (pbmi->bmiHeader.biSizeImage == 0) {
	    if (sizImage == 0) {
		OutputDebugString ("biSizeImage == 0!");
		bSuccess = FALSE;
		goto ErrExit4;
	    }
	    OutputDebugString ("Engine returns zero image size, making one up!");
	    sizImage = (sizImage *3)/2;
	} else {
	    sizImage = pbmi->bmiHeader.biSizeImage;
	}

	if ((pjRleBits = (PBYTE) LocalAlloc(LMEM_FIXED, sizImage)) == NULL) {
	     bSuccess = FALSE;
	     goto ErrExit4;
	}

	pbmi->bmiHeader.biSizeImage = sizImage;
	if (GetDIBits(hDC, pInfo->hBmpSaved, 0, lScan, pjRleBits, pbmi,
	    DIB_RGB_COLORS) < lScan) {
	     bSuccess = FALSE;
	     goto ErrExit5;
	}

	SetDIBitsToDevice(hDC, 0, 0, pbmi->bmiHeader.biWidth, pbmi->bmiHeader.biHeight,
		      0, 0, 0, lScan, pjRleBits, pbmi, DIB_RGB_COLORS);

	pInfo->RleData.rgpjFrame[ulFrames] = pjRleBits;
    } else {
	bSelectDIBPal(hDC, pInfo, pbmi, bCoreHdr);
	lScan = pbmi->bmiHeader.biHeight;
	if (bCoreHdr) {
	   lScan = ((LPBITMAPCOREINFO)pbmi)->bmciHeader.bcHeight;
	   SetDIBitsToDevice(hDC, 0, 0, ((LPBITMAPCOREINFO)pbmi)->bmciHeader.bcWidth, ((LPBITMAPCOREINFO)pbmi)->bmciHeader.bcHeight,
		      0, 0, 0, lScan, pjDIBits, pbmi, DIB_RGB_COLORS);
	} else {
	   lScan = pbmi->bmiHeader.biHeight;
	   SetDIBitsToDevice(hDC, 0, 0, pbmi->bmiHeader.biWidth, pbmi->bmiHeader.biHeight,
		      0, 0, 0, lScan, pjDIBits, pbmi, DIB_RGB_COLORS);
	}
	pInfo->RleData.rgpjFrame[ulFrames] = pjDIBits;
    }

    pInfo->RleData.ulSize[ulFrames] = sizImage;
    pInfo->RleData.rgpbmi[ulFrames] = pbmi;

    //
    // Go to next frame
    //
    pMapFile = (PBYTE)pMapFile + ulfSize;
    ulOffset += ulfSize;
    ulFrames++;

    //
    // end condition
    //
    if (ulOffset >= dwFileSizeLow) {
	break;
    }

  }

    //
    // set pbmi to the very first bmi
    //
    pInfo->RleData.pbmi = pInfo->RleData.rgpbmi[0];

    pInfo->RleData.hPal = pInfo->hPal;
    pInfo->RleData.ulFrames = ulFrames;
    return (bSuccess);

ErrExit5:
    LocalFree(pjRleBits);
ErrExit4:
    LocalFree(pbmi);
ErrExit3:
    CloseHandle(pFileInfo->hMapFile);
ErrExit2:
    CloseHandle(pFileInfo->hFile);
ErrExit1:
    return (bSuccess);

}

/******************************Public*Routine******************************\
*
* bSelectDIBPal
*
* Effects: Creates a logical palette from the DIB and select it into the DC
*          and realize the palette. Saving the hPal in the pInfo->hPal
*
* Warnings: Based on Windows NT DIB support.  If PM support 16,24,32 bpp
*           we need to modify this routine.
*
\**************************************************************************/

BOOL bSelectDIBPal(HDC hDC, PINFO pInfo, LPBITMAPINFO pbmi, BOOL bCoreHdr)
{
  LOGPALETTE    *plogPal;
  UINT          uiSizPal;
  INT           i, iNumClr;
  WORD          wBitCount;

  if (bCoreHdr) {
    wBitCount = ((LPBITMAPCOREINFO)pbmi)->bmciHeader.bcBitCount;
  } else {
    wBitCount = pbmi->bmiHeader.biBitCount;
  }

  switch (wBitCount) {
    case 16:
    case 24:
    case 32:                            // Does PM supports these?
	return FALSE;
    default:
	iNumClr = (1 << wBitCount);
	break;
  }

  uiSizPal = sizeof(WORD)*2 + sizeof(PALETTEENTRY)*iNumClr;
  if ((plogPal = (LOGPALETTE *) LocalAlloc(LMEM_FIXED,uiSizPal)) == NULL) {
      pInfo->hPal = NULL;
      return FALSE;
  }

  plogPal->palVersion = 0x300;
  plogPal->palNumEntries = (WORD) iNumClr;

  if (bCoreHdr) {
    for (i=0; i<iNumClr; i++) {
	plogPal->palPalEntry[i].peRed   = ((LPBITMAPCOREINFO)pbmi)->bmciColors[i].rgbtRed;
	plogPal->palPalEntry[i].peGreen = ((LPBITMAPCOREINFO)pbmi)->bmciColors[i].rgbtGreen;
	plogPal->palPalEntry[i].peBlue  = ((LPBITMAPCOREINFO)pbmi)->bmciColors[i].rgbtBlue;
	plogPal->palPalEntry[i].peFlags = PC_RESERVED;
    }
  } else {
    for (i=0; i<iNumClr; i++) {
	plogPal->palPalEntry[i].peRed   = pbmi->bmiColors[i].rgbRed;
	plogPal->palPalEntry[i].peGreen = pbmi->bmiColors[i].rgbGreen;
	plogPal->palPalEntry[i].peBlue  = pbmi->bmiColors[i].rgbBlue;
	plogPal->palPalEntry[i].peFlags = PC_RESERVED;
    }
  }

  DeleteObject(pInfo->hPal);
  pInfo->hPal = CreatePalette((LPLOGPALETTE)plogPal);
  if ((pInfo->hPal) == NULL) {
      return FALSE;
  }

  if ((GetDeviceCaps(hDC, RASTERCAPS)) & RC_PALETTE) {
    SelectPalette(hDC, pInfo->hPal, FALSE);
    RealizePalette(hDC);
  }

  GlobalFree(plogPal);

  return TRUE;
}

/******************************Public*Routine******************************\
*
* bFreeRleFile
*
* Effects:
*
* Warnings:
*
\**************************************************************************/

BOOL bFreeRleFile(PINFO pInfo)
{
    ULONG               ulFiles;
    ULONG               ulFrames;
    ULONG               i;
    PFILEINFO           pFileInfo;

    ulFiles = pInfo->RleData.ulFiles;
    ulFrames = pInfo->RleData.ulFrames;

    for (i = 0; i < ulFrames; i++) {
	LocalFree(pInfo->RleData.rgpjFrame[i]);
	LocalFree(pInfo->RleData.rgpbmi[i]);
    }

    for (i = 0; i < ulFiles; i++) {
	pFileInfo = &(pInfo->RleData.rgFileInfo[i]);
	CloseHandle(pFileInfo->hFile);
	CloseHandle(pFileInfo->hMapFile);
	UnmapViewOfFile(pFileInfo->lpvMapView);
    }

    pInfo->RleData.ulFiles = 0;
    pInfo->RleData.ulFrames = 0;
    return TRUE;
}

/******************************Public*Routine******************************\
*
* bPlayRle
*
* Effects:
*
* Warnings:
*
\**************************************************************************/

BOOL bPlayRle(PINFO pInfo)
{
    ULONG               ulFrames;
    ULONG               i;
    LPBITMAPINFO        pbmi;
    HDC                 hDC;
    HWND                hViewSurf;
    int                 ii;

//    RECT                rc;

    hDC = GetDC(hViewSurf=pInfo->hwnd);

    SelectPalette(hDC, pInfo->RleData.hPal, FALSE);
    ii=RealizePalette(hDC);
    if (ii){
	UpdateColors (hDC);
    }

    ulFrames = pInfo->RleData.ulFrames;

    for (i = 0; i < ulFrames; i++) {
	pbmi = pInfo->RleData.rgpbmi[i];
	SetDIBitsToDevice(hDC,
		  0, 0, pbmi->bmiHeader.biWidth, pbmi->bmiHeader.biHeight,
		  0, 0, 0, pbmi->bmiHeader.biHeight,
		  pInfo->RleData.rgpjFrame[i], pbmi, DIB_RGB_COLORS);

#if 0
	GetClientRect(pInfo->hwnd, &rc);
	StretchDIBits(hDC,
	       0, 0, rc.right, rc.bottom,
	       0, 0, pbmi->bmiHeader.biWidth, pbmi->bmiHeader.biHeight,
	       (LPSTR)pInfo->RleData.rgpjFrame[i], pbmi, DIB_RGB_COLORS,
	       SRCCOPY);
#endif
    }

    ReleaseDC(hViewSurf, hDC);

    return TRUE;
}


/******************************Public*Routine******************************\
*
* bSaveRleFile
*
* Effects:
*
* Warnings:
*
\**************************************************************************/

BOOL bSaveRleFile(HDC hDC, PINFO pInfo, PSTR pszFileName)
{
    int                 hFile;
    OFSTRUCT            ofReOpenBuff;
    BOOL                bSuccess;
    BITMAPFILEHEADER    bfh;
    ULONG               ulFrames;
    ULONG               i;
    LPBITMAPINFO        pbmi;
    ULONG               ulNumClr;
    ULONG               ulSize;

    bSuccess = TRUE;
    ulFrames = pInfo->RleData.ulFrames;

    if (ulFrames == 0) {
	MessageBox(GetFocus(), GetStringRes (IDS_NO_RLE_TO_SAVE),
	           NULL, MB_OK);
	return FALSE;
    }

    // Let's open the file and get ready for writing
    if ((hFile = OpenFile(pszFileName, (LPOFSTRUCT)&ofReOpenBuff,
		 OF_CREATE | OF_WRITE)) == -1) {
	OutputDebugString ("Failed in OpenFile!");
	return FALSE;
    }

    for (i = 0; i < ulFrames; i++) {

	pbmi = pInfo->RleData.rgpbmi[i];

	switch(pbmi->bmiHeader.biBitCount) {
	    case 24:
		ulSize = 0;
		break;
	    case 16:
	    case 32:
		ulSize = sizeof(DWORD)*3;
		break;
	    default:
		ulNumClr = 1<<pbmi->bmiHeader.biBitCount;
		ulSize = sizeof(RGBQUAD)*ulNumClr;
		break;
	}
#if 0
	ulNumClr = ((pbmi->bmiHeader.biBitCount == 24)
		       ? 0
		       : (1<<pbmi->bmiHeader.biBitCount));
#endif
	// fill in the info for the BitmapFileHeader
	bfh.bfType    = 0x4D42;                            // 'BM'
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+
			ulSize;
			//sizeof(RGBQUAD)*ulNumClr;
	bfh.bfSize    = bfh.bfOffBits + pbmi->bmiHeader.biSizeImage;
	bfh.bfReserved1 =
	bfh.bfReserved2 = 0;

	// Write out the file header now
	if (_lwrite(hFile, (LPSTR)&bfh, sizeof(BITMAPFILEHEADER)) == -1) {
	    bSuccess = FALSE;
	    goto ErrExit1;
	}

	// Now write out the BitmapInfoHeader and color table, if any
	if (_lwrite(hFile, (LPSTR)pbmi, sizeof(BITMAPINFOHEADER) +
					ulSize) == -1) {
					//sizeof(RGBQUAD)*ulNumClr) == -1) {
	    bSuccess = FALSE;
	    goto ErrExit1;
	}

	// write the bits also
	if (_lwrite(hFile, (LPSTR)pInfo->RleData.rgpjFrame[i],
			   pbmi->bmiHeader.biSizeImage) == -1) {
	    bSuccess = FALSE;
	    goto ErrExit1;
	}

    }

ErrExit1:
    _lclose(hFile);
    return bSuccess;
}


/******************************Public*Routine******************************\
*
* bPlayRleCont
*
* Effects:
*
* Warnings:
*
\**************************************************************************/

BOOL bPlayRleCont(HDC hDC, PINFO pInfo)
{
    BOOL    bQuit;
    MSG     msg;
    int     ii;

    bQuit = FALSE;

    SelectPalette(hDC, pInfo->RleData.hPal, FALSE);
    ii=RealizePalette(hDC);
    if (ii){
	UpdateColors (hDC);
    }

    while (TRUE && !bQuit) {

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

	    if ((msg.message == WM_QUIT) || (msg.message == WM_CLOSE) ||
		((msg.message == WM_SYSCOMMAND) && (msg.wParam == SC_CLOSE))) {
		bQuit = TRUE;
		PostMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
	    } else {
		if (!TranslateAccelerator(msg.hwnd, ghAccel, &msg)) {
		    TranslateMessage(&msg);
		    DispatchMessage(&msg);
		}
	   }
	}

	if (!pInfo->bPlayRleCont) {
	    bQuit = TRUE;
	}

	if (!bQuit) {
	    bPlayRle(pInfo);
	}

    }
    return TRUE;
}


/******************************Public*Routine******************************\
*
* bPlayRleCont2
*
* Effects:
*
* Warnings:
*
\**************************************************************************/

BOOL bPlayRleCont2(PINFO pInfo)
{
    HDC             hDC;
    HWND            hViewSurf;
    DWORD           dwWait;
    BOOL            bQuit;
    int             ii;

    hDC = GetDC(hViewSurf=pInfo->hwnd);

    SelectPalette(hDC, pInfo->RleData.hPal, FALSE);
    ii=RealizePalette(hDC);
    if (ii){
	UpdateColors (hDC);
    }

    bQuit = FALSE;
    while (TRUE) {
	//
	// If parent gets a WM_CLOSE, we will return
	//
	dwWait = WaitForSingleObject(pInfo->hQuitEvent, 0);
	if (dwWait == WAIT_TIMEOUT) {
		MessageBox(ghwndMain,
		           GetStringRes (IDS_PLAY_THREAD_END),
		           GetStringRes (IDS_PLAY_THREAD),
		           MB_OK);
	    break;
	}

	if (!pInfo->bPlayRleCont) {
	    bQuit = TRUE;
	}

	if (!bQuit)
	    bPlayRle(pInfo);
    }

    ReleaseDC(hViewSurf, hDC);

    ExitThread(0);
    return TRUE;

}


/******************************Public*Routine******************************\
*
* DIBfromDDB
*
* Effects:  Call GetDIBits to retrieve the DIB info from DDB
*
* Warnings:
*
\**************************************************************************/

HBITMAP DIBfromDDB(HDC hDC, HBITMAP hBmp, PINFO pInfo)
{
    LPBITMAPINFO        pbmi;
    HBITMAP             hDIB;
    INT                 iBitCount, iNumClr;
    BITMAP              bm;
    DWORD               sizImage;
    PBYTE               pjBits;
    ULONG               sizBMI;
    LONG                lScan;

    iBitCount = GetDeviceCaps(hDC, BITSPIXEL);
    switch (iBitCount) {
	case 16:
	case 32:
	    sizBMI = sizeof(BITMAPINFOHEADER)+sizeof(DWORD)*3;
	    break;
	case 24:
	    sizBMI = sizeof(BITMAPINFOHEADER);
	    break;
	default:
	    iNumClr = (1 << iBitCount);
	    sizBMI = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*iNumClr;
	    break;
    }

    if ((pbmi = (LPBITMAPINFO) LocalAlloc(LMEM_FIXED,sizBMI)) == NULL) {
	goto ErrExit1;
    }

    pbmi->bmiHeader.biSize = 0x28;              // GDI need this to work
    pbmi->bmiHeader.biBitCount = 0;             // don't get the color table
    pbmi->bmiHeader.biCompression = BI_RGB;
    pbmi->bmiHeader.biSizeImage = 0;
    pbmi->bmiHeader.biXPelsPerMeter = 0;
    pbmi->bmiHeader.biYPelsPerMeter = 0;
    pbmi->bmiHeader.biClrUsed = 0;
    pbmi->bmiHeader.biClrImportant = 0;

    GetObject(hBmp, sizeof(BITMAP), &bm);

    //
    // Important!  Select the correct palette corresponding to the DDB
    //
    SelectPalette(hDC, pInfo->hPal, FALSE);
    if (GetDIBits(hDC, hBmp, 0, bm.bmHeight, NULL, pbmi,
	DIB_RGB_COLORS) == 0) {
	 goto ErrExit2;
    }

    sizImage = pbmi->bmiHeader.biSizeImage;
    if (sizImage == 0) {
	goto ErrExit2;
    }

    if ((pjBits = (PBYTE) LocalAlloc(LMEM_FIXED, sizImage)) == NULL) {
	 goto ErrExit2;
    }

    lScan = pbmi->bmiHeader.biHeight;

    if (GetDIBits(hDC, pInfo->hBmpSaved, 0, lScan, pjBits, pbmi,
	DIB_RGB_COLORS) < lScan) {
	 goto ErrExit3;
    }

    //
    // Saving the DIB...free memory when the windows is closed.
    //
    pInfo->RleData.rgpjFrame[0] = pjBits;
    pInfo->RleData.rgpbmi[0]    = pbmi;
    pInfo->RleData.pbmi         = (PBITMAPINFO) &(pInfo->RleData.rgpbmi[0]);
    pInfo->RleData.ulFrames     = 1;
    pInfo->RleData.ulFiles      = 1;

    // set flag to use original DIB as source for blting so HT can be done
    pInfo->bUseDIB = TRUE;

    pInfo->bCoreHdr = FALSE;

    // hDIB = CreateDIBitmap(hDC, NULL, CBM_INIT, pjBits, pbmi, DIB_RGB_COLORS);
    hDIB = CreateDIBSection(hDC, pbmi, DIB_RGB_COLORS, &pjBits, NULL, 0);

    return hDIB;

ErrExit3:
    LocalFree(pjBits);
ErrExit2:
    LocalFree(pbmi);
ErrExit1:
    return ((HBITMAP)NULL);
}


//---------------------------------------------------------------------------
//
// FUNCTION:    GetStringRes (int id INPUT ONLY)
//
// COMMENTS:    Load the resource string with the ID given, and return a
//              pointer to it.  Notice that the buffer is common memory so
//              the string must be used before this call is made a second time.
//
//---------------------------------------------------------------------------

LPTSTR GetStringRes (int id)
{
  static TCHAR buffer[MAX_PATH];

  buffer[0]=0;
  LoadString (GetModuleHandle (NULL), id, buffer, MAX_PATH);
  return buffer;
}
