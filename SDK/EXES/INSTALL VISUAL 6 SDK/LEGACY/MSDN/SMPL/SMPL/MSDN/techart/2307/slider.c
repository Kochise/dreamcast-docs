/****************************************************************************
*
*
*    PROGRAM: Slider.c
*
*    PURPOSE: Slider for testing
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <commctrl.h>   // includes the common control header
#include <string.h>
#include "slider.h"

HINSTANCE hInst;
HWND hWndSlider1, hWndSlider2, hWndSlider3;

/****************************************************************************
*
*    FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
*
*    PURPOSE: calls initialization function, processes message loop
*
****************************************************************************/

int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
	)
{

	MSG msg;                       

	InitCommonControls();

	if (!InitApplication(hInstance))
		return (FALSE);     

	/* Perform initializations that apply to a specific instance */
	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);

	/* Acquire and dispatch messages until a WM_QUIT message is received. */
	while (GetMessage(&msg,
		NULL,              
		0,                 
		0))                
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
	}
	return (msg.wParam);  
												 
}


/****************************************************************************
*
*    FUNCTION: InitApplication(HANDLE)
*
*    PURPOSE: Initializes window data and registers window class
*
****************************************************************************/

BOOL InitApplication(HANDLE hInstance)       /* current instance             */
{
	WNDCLASS  wcSlider;
	
	/* Fill in window class structure with parameters that describe the       */
	/* main window.                                                           */

	wcSlider.style = 0;                     
	wcSlider.lpfnWndProc = (WNDPROC)MainWndProc; 
	wcSlider.cbClsExtra = 0;              
	wcSlider.cbWndExtra = 0;              
	wcSlider.hInstance = hInstance;       
	wcSlider.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(SLIDER_ICON));
	wcSlider.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcSlider.hbrBackground = GetStockObject(WHITE_BRUSH); 
	wcSlider.lpszMenuName =  "SliderMenu";  
	wcSlider.lpszClassName = "SliderWClass";

	return (RegisterClass(&wcSlider));

}


/****************************************************************************
*
*    FUNCTION:  InitInstance(HANDLE, int)
*
*    PURPOSE:  Saves instance handle and creates main window
*
****************************************************************************/

BOOL InitInstance(
	HANDLE          hInstance,
	int             nCmdShow) 
{
	HWND hWndMain;

	hInst = hInstance;

	hWndMain = CreateWindow(
		"SliderWClass",           
		"Slider Sample", 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,               
		NULL,               
		hInstance,          
		NULL);

	/* If window could not be created, return "failure" */
	if (!hWndMain)
		return (FALSE);

	/* Make the window visible; update its client area; and return "success" */
	ShowWindow(hWndMain, nCmdShow);
	UpdateWindow(hWndMain); 
	return (TRUE);      

}

/****************************************************************************
*
*    FUNCTION: MainWndProc(HWND, unsigned, WORD, LONG)
*
*    PURPOSE:  Processes messages
*
****************************************************************************/

LONG APIENTRY MainWndProc(
	HWND hWnd,                /* window handle                   */
	UINT message,             /* type of message                 */
	UINT wParam,              /* additional information          */
	LONG lParam)              /* additional information          */
{
	static HWND hWndStatus;
	char *pMsg = NULL;
	char szBuf[64]; 
	BOOL bMsg;

	switch (message) 
	{

		case WM_CREATE:

			hWndStatus = CreateWindow(
				STATUSCLASSNAME,           
				"", 
				WS_CHILD | WS_BORDER | WS_VISIBLE,
				-100,-100,10,10,
				hWnd,               
				(HMENU)100,               
				hInst,          
				NULL);

			hWndSlider1  = CreateWindow(
				TRACKBAR_CLASS,
				"",
				WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
				10,50,200,20,
				hWnd,         
				(HMENU)10,         
				hInst,
				NULL);
			
			if (hWndSlider1 == NULL)
				MessageBox (NULL, "Slider1 not created!", NULL, MB_OK );
		 
			hWndSlider2  = CreateWindow(
				TRACKBAR_CLASS,
				"",
				WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_TOP | TBS_ENABLESELRANGE,
				10,100,200,20,
				hWnd,         
				(HMENU)11,         
				hInst,
				NULL);
			if (hWndSlider2 == NULL)
				MessageBox (NULL, "Slider2 not created!", NULL, MB_OK );

			hWndSlider3  = CreateWindow(
				TRACKBAR_CLASS,
				"",
				WS_CHILD | WS_VISIBLE | TBS_VERT | TBS_LEFT | TBS_AUTOTICKS,
				10,150,20,100,
				hWnd,         
				(HMENU)12,         
				hInst,
				NULL);
			if (hWndSlider3 == NULL)
				MessageBox (NULL, "Slider3 not created!", NULL, MB_OK );

			// set the default range
			SendMessage( hWndSlider1, TBM_SETRANGE, TRUE, MAKELONG(1,10));
			SendMessage( hWndSlider2, TBM_SETRANGE, TRUE, MAKELONG(1,10));
			SendMessage( hWndSlider3, TBM_SETRANGE, TRUE, MAKELONG(1,10));

			// set the selection 
			SendMessage( hWndSlider2, TBM_SETSEL, TRUE, MAKELONG(3,5));
			break;

		case WM_VSCROLL:
		case WM_HSCROLL:
            bMsg = TRUE;
			switch(wParam)
			{
				case TB_BOTTOM:
					pMsg = "TB_BOTTOM";
					break;
	
				case TB_ENDTRACK:
					pMsg = "TB_ENDTRACK";
					break;

				case TB_LINEDOWN:
					pMsg = "TB_LINEDOWN";
					break;

				case TB_LINEUP:
					pMsg = "TB_LINEUP";
					break;

				case TB_PAGEDOWN:
					pMsg = "TB_PAGEDOWN";
					break;

				case TB_PAGEUP:
					pMsg = "TB_PAGEUP";
					break;

				case TB_THUMBPOSITION:
					pMsg = "TB_THUMPOSITION";
					break;

				case TB_THUMBTRACK:
					pMsg = "TB_THUMBTRACK";
					break;

				default:
					bMsg = FALSE;
					break;

			}

			if (bMsg == TRUE)
			{
				wsprintf(szBuf,"Trackbar message: %s",pMsg);
				SendMessage(hWndStatus, SB_SETTEXT, 0, (LPARAM)(LPSTR)szBuf);
			}
			break;

		case WM_COMMAND:

			switch( LOWORD( wParam ))
			{
				case IDM_SETRANGE:
					DialogBox(hInst, "SetRange", hWnd, (DLGPROC)Range);
					break;

				case IDM_SETFREQ:
					DialogBox(hInst, "SetFreq", hWnd, (DLGPROC)Frequency);
					break;

				case IDM_SETPAGE:
					DialogBox(hInst, "SetPage", hWnd, (DLGPROC)PageSize);
					break;

				case IDM_SETLINE:
					DialogBox(hInst, "SetLine", hWnd, (DLGPROC)LineSize);
					break;

				case IDM_EXIT:
					PostQuitMessage(0);
					break;

				case IDM_ABOUT:
					DialogBox(hInst, "AboutBox", hWnd, (DLGPROC)About);
					break;

				default:
					return (DefWindowProc(hWnd, message, wParam, lParam));

		}
		break;

		case WM_DESTROY:                  /* message: window being destroyed */
			PostQuitMessage(0);
			break;

		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}


/****************************************************************************
*
*    FUNCTION: About(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "About" dialog box
*
****************************************************************************/

BOOL APIENTRY About(
   HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
	switch (message)
	{
	   case WM_INITDIALOG:
		  return (TRUE);

	   case WM_COMMAND:              
		  if (LOWORD(wParam) == IDOK)
		 {
			  EndDialog(hDlg, TRUE);
			  return (TRUE);
		  }
		  break;
	}
	return (FALSE);   

}


/****************************************************************************
* 
*    FUNCTION: Range(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "SetRange" dialog box
*
****************************************************************************/

BOOL APIENTRY Range(
	HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
	BOOL bErr;
	UINT uMin, uMax;
	HWND hWndCurrent;
	int iWhichBar;

	switch (message)
	{
		case WM_INITDIALOG:
			return (TRUE);

		case WM_COMMAND:              
			if (LOWORD(wParam) == IDOK)
			{
				iWhichBar = GetDlgItemInt(hDlg, IDE_BAR, &bErr, TRUE);
				if (iWhichBar == 1)
					hWndCurrent = hWndSlider1;
				else if (iWhichBar == 2)
					hWndCurrent = hWndSlider2;
				else if (iWhichBar == 3)
					hWndCurrent = hWndSlider3;
				else
				{
					MessageBox(NULL, "Slider number must be from 1 to 3", NULL, MB_OK);
					break;
				}

				uMin = GetDlgItemInt(hDlg, IDE_MIN, &bErr, TRUE);
				uMax = GetDlgItemInt(hDlg, IDE_MAX, &bErr, TRUE);
				SendMessage( hWndCurrent, TBM_SETRANGE, TRUE, 
					MAKELONG(uMax,uMin));
				EndDialog(hDlg, TRUE);
				return (TRUE);
			}
			break;
	}
	return (FALSE);   

}
/****************************************************************************
* 
*    FUNCTION: Frequency(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "SetFreq" dialog box
*
****************************************************************************/

BOOL APIENTRY Frequency(
	HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
	BOOL bErr;
	UINT uFreq;
	int iWhichBar;
	HWND hWndSend;

	switch (message)
	{
		case WM_INITDIALOG:
			return (TRUE);

		case WM_COMMAND:              
			if (LOWORD(wParam) == IDOK)
			{
				uFreq = GetDlgItemInt(hDlg, IDE_FREQ, &bErr, TRUE);
				iWhichBar = GetDlgItemInt(hDlg, IDE_BAR, &bErr, TRUE);
				if (iWhichBar == 1)
					hWndSend = hWndSlider1;
				else if (iWhichBar == 2)
					hWndSend = hWndSlider2;
				else if (iWhichBar == 3)
					hWndSend = hWndSlider3;
				else
				{
					MessageBox(NULL, "Slider number must be from 1 to 3", NULL, MB_OK);
					break;
				}
				PostMessage( hWndSend, TBM_SETTICFREQ, uFreq, 0L);
				EndDialog(hDlg, TRUE);
				return (TRUE);
			}
			break;
	}
	return (FALSE);   

}
/****************************************************************************
* 
*    FUNCTION: PageSize(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "PageSize" dialog box
*
****************************************************************************/

BOOL APIENTRY PageSize(
	HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
	BOOL bErr;
	UINT uPage;
	int iWhichBar;
	HWND hWndSend;

	switch (message)
	{
		case WM_INITDIALOG:
			return (TRUE);

		case WM_COMMAND:              
			if (LOWORD(wParam) == IDOK)
			{
				uPage = GetDlgItemInt(hDlg, IDE_PAGE, &bErr, TRUE);
				iWhichBar = GetDlgItemInt(hDlg, IDE_BAR, &bErr, TRUE);
				if (iWhichBar == 1)
					hWndSend = hWndSlider1;
				else if (iWhichBar == 2)
					hWndSend = hWndSlider2;
				else if (iWhichBar == 3)
					hWndSend = hWndSlider3;
				else
				{
					MessageBox(NULL, "Slider number must be from 1 to 3", NULL, MB_OK);
					break;
				}
				PostMessage( hWndSend, TBM_SETPAGESIZE, 0L, uPage);
				EndDialog(hDlg, TRUE);
				return (TRUE);
			}
			break;
	}
	return (FALSE);   

}
/****************************************************************************
* 
*    FUNCTION: LineSize(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "LineSize" dialog box
*
****************************************************************************/

BOOL APIENTRY LineSize(
	HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
	BOOL bErr;
	UINT uLine;
	int iWhichBar;
	HWND hWndSend;

	switch (message)
	{
		case WM_INITDIALOG:
			return (TRUE);

		case WM_COMMAND:              
			if (LOWORD(wParam) == IDOK)
			{
				uLine = GetDlgItemInt(hDlg, IDE_LINE, &bErr, TRUE);
				iWhichBar = GetDlgItemInt(hDlg, IDE_BAR, &bErr, TRUE);
				if (iWhichBar == 1)
					hWndSend = hWndSlider1;
				else if (iWhichBar == 2)
					hWndSend = hWndSlider2;
				else if (iWhichBar == 3)
					hWndSend = hWndSlider3;
				else
				{
					MessageBox(NULL, "Slider number must be from 1 to 3", NULL, MB_OK);
					break;
				}
				PostMessage( hWndSend, TBM_SETLINESIZE, 0L, uLine);
				EndDialog(hDlg, TRUE);
				return (TRUE);
		  }
		  break;
	}
	return (FALSE);   

}
