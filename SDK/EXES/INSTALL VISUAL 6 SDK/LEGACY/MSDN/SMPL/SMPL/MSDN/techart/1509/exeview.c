#include "exeview.h"
#include "pefile.h"
#include <stdlib.h>

#define MAX_DRIVES    26    /* maximum number of logical drives */

/* system constants used externally */
int		     xChar,
		     yChar,
		     xScreen,
		     yScreen,
		     yFrame,
		     xFrame,
		     yCaption,
		     xVScrollBar;
HFONT		     hFont;
HWND		     hMemWnd;


BOOL WINAPI InitEnvironment (HANDLE, int, char	*);



/* entry point of this executable */
int WINAPI WinMain (hInstance, hPrevInstance, lpCmdLine, nCmdShow)
    HINSTANCE hInstance;
    HINSTANCE hPrevInstance;
    LPSTR     lpCmdLine;
    int       nCmdShow;
{
    MSG      msg;
    char     *lpszCmdLine = NULL;
    char     *lpCL;
    BOOL     bSwitch;

    // parse and copy command line parameters to local memory
    lpCL = GetCommandLine ();
    if (lpszCmdLine = (char *)LocalAlloc (LPTR, strlen (lpCL) + 1))
	GetCmdLine (lpCL, lpszCmdLine, &bSwitch);

    /* start window environment */
    if (!InitEnvironment (hInstance, nCmdShow, IsValidFile (lpszCmdLine) ? lpszCmdLine : NULL))
	return FALSE;

    /* free memory allocated for lpCmdLine */
    if (lpszCmdLine)
	LocalFree ((HLOCAL)lpszCmdLine);

    /* main window message loop */
    while (GetMessage (&msg, NULL, 0, 0))
	{
	TranslateMessage (&msg);
	DispatchMessage (&msg);
	}

    /* return success of application */
    return TRUE;
}



/*  start app */
BOOL WINAPI InitEnvironment (
    HANDLE    hInstance,
    int       nCmdShow,
    char      *lpszCmdLine)
    {
    WNDCLASS   wc;
    char       szClass[MAX_PATH];
    char       szTitle[MAX_PATH];
    HWND       hWnd;


    /* register the memory viewer window class */
    LoadString (hInstance, IDS_MEMVIEWCLASS, szClass, sizeof (szClass));
    wc.style	     = 0;
    wc.lpfnWndProc   = (WNDPROC)MemWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = VIEWWXB;
    wc.hInstance     = hInstance;
    wc.hIcon	     = LoadIcon (hInstance, MAKEINTRESOURCE (IDR_MAINICON));
    wc.hCursor	     = LoadCursor (0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = szClass;
    if (!RegisterClass (&wc) )
	return FALSE;

    /* register the main frame window class */
    LoadString (hInstance, IDS_EXEVIEWCLASS, szClass, sizeof (szClass));
    wc.style	     = 0;
    wc.lpfnWndProc   = (WNDPROC)ExeViewWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon	     = LoadIcon (hInstance, MAKEINTRESOURCE (IDR_MAINICON));
    wc.hCursor	     = LoadCursor (0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = MAKEINTRESOURCE (IDR_EXEVIEWMENU);
    wc.lpszClassName = szClass;
    if (!RegisterClass (&wc) )
	return FALSE;

    /* create window caption */
    LoadString (hInstance, IDS_CAPTION, szTitle, sizeof (szTitle));

    /* create main frame window */
    hWnd = CreateWindow (szClass,
			 szTitle,
			 WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
			 CW_USEDEFAULT,
			 0,
			 CW_USEDEFAULT,
			 0,
			 NULL,
			 NULL,
			 hInstance,
			 (lpszCmdLine != NULL) ? lpszCmdLine : NULL);

    if (!hWnd)
	return 0;

    ShowWindow (hWnd, nCmdShow);
    UpdateWindow (hWnd);
}


/* main window procedure */
LONG WINAPI ExeViewWndProc (
    HWND    hWnd,
    UINT    uMsg,
    WPARAM  wParam,
    LPARAM  lParam)
{
       LONG    lRet = 1;
static LOGFONT lf_Font = {
			 -10, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET,
			 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			 DEFAULT_QUALITY, FIXED_PITCH | FF_DONTCARE,
                         "Courier",
			 };

    switch (uMsg)
	{
	case WM_CREATE:
	    {
	    HCURSOR	  hOldCursor;
	    HDC 	  hDC;
	    TEXTMETRIC	  tm;
	    LPCREATESTRUCT    lpcs = (LPCREATESTRUCT)lParam;

	    /* put hourglass cursor up */
	    hOldCursor = (HCURSOR)SetClassLong (hWnd, GCL_HCURSOR, 0);
	    SetCursor (LoadCursor (0, IDC_WAIT));

	    hDC = GetDC (hWnd);

	    /* want a font with point size of 10 (smallest size it comes in) */
	    lf_Font.lfHeight = -(10 * GetDeviceCaps(hDC, LOGPIXELSY)/72);
	    hFont = CreateFontIndirect(&lf_Font);
            SelectObject(hDC, hFont);

	    /* initialize system constants */
	    GetTextMetrics(hDC, &tm);
	    yChar = tm.tmHeight;
	    xChar = tm.tmAveCharWidth;
	    xScreen = GetSystemMetrics(SM_CXSCREEN);
	    yScreen = GetSystemMetrics(SM_CYSCREEN);
	    yFrame = GetSystemMetrics(SM_CYFRAME);
	    xFrame = GetSystemMetrics(SM_CXFRAME);
	    yCaption = GetSystemMetrics(SM_CYCAPTION);
	    xVScrollBar = GetSystemMetrics(SM_CXVSCROLL);

            SelectObject(hDC, GetStockObject(SYSTEM_FONT));
            ReleaseDC(hWnd, hDC);

	    /* if command line parameter, load initial exe */
	    if (lpcs->lpCreateParams != NULL)
		ViewExe (hWnd, lpcs->lpCreateParams);

	    /* remove hourglass cursor */
	    SetClassLong (hWnd, GCL_HCURSOR, (LONG)hOldCursor);
	    SetCursor (hOldCursor);
	    }
	    break;

	case WM_COMMAND:
	    switch (LOWORD (wParam))
		{
		case IDM_EXIT:
		    SendMessage (hWnd, WM_CLOSE, 0, 0);
		    break;

		case IDM_CLOSE:
		    break;

		case IDM_OPEN:
		    {
		    char      szFilePath[MAX_PATH];
		    HWND      hViewWnd = NULL;

		    /* call open file dialog to get filename of exe, and validate */
		    *szFilePath = 0;
		    if (GetFileName (hWnd, szFilePath, NULL) &&
			IsValidFile (szFilePath))
			ViewExe (hWnd, szFilePath);
		    }
		    break;
		}
	    break;

	case WM_CLOSE:
	    /* destroy this window */
	    DestroyWindow (hWnd);
	    break;

	case WM_DESTROY:
	    PostQuitMessage (0);
	    break;

	default:
	    /* pass all unhandled messages to DefWindowProc */
	    lRet = DefWindowProc (hWnd, uMsg, wParam, lParam);
	    break;
	}

    /* return 1 if handled message, 0 if not */
    return lRet;
}




/* generic message notification */
int WINAPI NotifyUser (
    HWND    hWndParent,
    int     nTitle,
    int     nError,
    char    *lpszAppend,
    UINT    uFlags)
{
    char    szError[MAX_PATH];
    char    szTitle[MAX_PATH];

    LoadString (GetModuleHandle (NULL), nTitle, szTitle, MAX_PATH);
    LoadString (GetModuleHandle (NULL), nError, szError, MAX_PATH);

    if (lpszAppend != NULL && *lpszAppend != 0)
	strcat (szError, lpszAppend);

    if (!uFlags)
	uFlags = MB_ICONSTOP | MB_OK | MB_TASKMODAL | MB_SETFOREGROUND;

    /* return message box response */
    return (MessageBox (hWndParent, szError, szTitle, uFlags));
}




void   WINAPI ReportError (
    int     nIDS_CAPTION)
{
    char    *lpszError;
    char    szText[MAX_PATH];

    /* get formatted error message from system */
    if (!FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			GetLastError (),
			MAKELONG (MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), 0),
			(LPTSTR)&lpszError,
			0,
			NULL))
	return;

    /* if resource string provided, load caption string */
    if (nIDS_CAPTION)
	LoadString (GetModuleHandle (NULL), nIDS_CAPTION, szText, MAX_PATH);
    else
	strcpy (szText, "Error");

    MessageBox (NULL,
		lpszError,
		szText,
		MB_ICONSTOP | MB_OK | MB_TASKMODAL | MB_SETFOREGROUND);
}
