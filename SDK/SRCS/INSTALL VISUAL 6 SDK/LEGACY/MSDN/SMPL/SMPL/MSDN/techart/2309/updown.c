/****************************************************************************
*
*
*    PROGRAM: UpDown.c
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <commctrl.h>   // includes the common control header
#include <string.h>
#include "updown.h"

HINSTANCE hInst;
HWND hWndMain;
int iNumLines;

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
	WNDCLASS  wcUpDown;
	
	/* Fill in window class structure with parameters that describe the       */
	/* main window.                                                           */

	wcUpDown.style = 0;                     
	wcUpDown.lpfnWndProc = (WNDPROC)MainWndProc; 
	wcUpDown.cbClsExtra = 0;              
	wcUpDown.cbWndExtra = 0;              
	wcUpDown.hInstance = hInstance;       
	wcUpDown.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(UPDOWN_ICON));
	wcUpDown.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcUpDown.hbrBackground = GetStockObject(WHITE_BRUSH); 
	wcUpDown.lpszMenuName =  "UpDownMenu";  
	wcUpDown.lpszClassName = "UpDownWClass";

	return (RegisterClass(&wcUpDown));

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

	hInst = hInstance;

	hWndMain = CreateWindow(
		"UpDownWClass",           
		"UpDown Sample", 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,               
		NULL,               
		hInstance,          
		NULL);

	/* If window could not be created, return "failure" */
	if (!hWndMain)
		return (FALSE);

	// set the initial number of lines to one
	iNumLines = 1;

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
	HDC hdc;
	PAINTSTRUCT ps;
	int idx;

	switch (message) 
	{
	
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			for (idx = 1; idx <= iNumLines; idx++)
			{
				TextOut(hdc, 20, 5 + (idx * 16), 
					szWelcome, lstrlen(szWelcome));      
			}
			EndPaint(hWnd, &ps);
			break;

		case WM_COMMAND:
			switch( LOWORD( wParam ))
			{

				case IDM_SPIN:
					DialogBox(hInst, "SpinBox", hWnd, (DLGPROC)Spin);
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
*    FUNCTION: Spin(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "Spin" dialog box
*
****************************************************************************/

BOOL APIENTRY Spin(
	HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
	static HWND hWndUpDown, hWndBuddy;
	BOOL bErr;

	switch (message)
	{
		case WM_INITDIALOG:
			// get a handle to the edit "buddy" control
			hWndBuddy = GetDlgItem(hDlg, IDE_BUDDY);

			// create up-down control
			hWndUpDown = CreateWindowEx( 
				0L,
				UPDOWN_CLASS,
				"",
				WS_CHILD | WS_BORDER | WS_VISIBLE | UDS_WRAP | UDS_ARROWKEYS |
				UDS_ALIGNRIGHT | UDS_SETBUDDYINT,
				0, 0, 8, 8,
				hDlg,
				(HMENU)ID_UPDOWN,
				hInst,
				NULL );

			// set the buddy window
			SendMessage( hWndUpDown, UDM_SETBUDDY, (LONG)hWndBuddy, 0L );

			// set the range
			SendMessage( hWndUpDown, UDM_SETRANGE, 0L, MAKELONG (MAX_SPIN, MIN_SPIN));

			// set the deafult value in the edit box
			SetDlgItemInt( hDlg, IDE_BUDDY, 1, FALSE);
			return (TRUE);

		case WM_COMMAND:              
			switch (LOWORD(wParam))
			{
				case IDOK:
					iNumLines = (int)GetDlgItemInt(hDlg, IDE_BUDDY, 
						&bErr, FALSE );
					InvalidateRect(hWndMain, NULL, TRUE); 

				case IDCANCEL:
					EndDialog(hDlg, TRUE);
					break;
				
			}
			break;
	
	}
	return (FALSE);   

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

