/****************************************************************************
*
*
*    PROGRAM: PropS.c
*
*    PURPOSE: Property Sheet Sample
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <commctrl.h>   // includes the common control header
#include <string.h>
#include "props.h"

HINSTANCE hInst;
HWND hWndSlider;

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
	wcSlider.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(EXE_ICON));
	wcSlider.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcSlider.hbrBackground = GetStockObject(WHITE_BRUSH); 
	wcSlider.lpszMenuName =  "PropSheetMenu";  
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
	char szMsg[64];
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

			hWndSlider  = CreateWindow(
				TRACKBAR_CLASS,
				"",
				WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_TOP | TBS_ENABLESELRANGE,
				10,100,200,20,
				hWnd,         
				(HMENU)11,         
				hInst,
				NULL);
			if (hWndSlider == NULL)
				MessageBox (NULL, "Slider not created!", NULL, MB_OK );

			// set the default range
			SendMessage( hWndSlider, TBM_SETRANGE, TRUE, MAKELONG(1,10));

			// set the selection 
			SendMessage( hWndSlider, TBM_SETSEL, TRUE, MAKELONG(3,5));
			break;

		case WM_HSCROLL:
			bMsg = TRUE;
			switch(wParam)
			{
				case TB_BOTTOM:
					lstrcpy(szMsg,"TB_BOTTOM");
					break;

				case TB_ENDTRACK:
					lstrcpy(szMsg,"TB_ENDTRACK");
					break;

				case TB_LINEDOWN:
					lstrcpy(szMsg,"TB_LINEDOWN");
					break;

				case TB_LINEUP:
					lstrcpy(szMsg,"TB_LINEUP");
					break;

				case TB_PAGEDOWN:
					lstrcpy(szMsg,"TB_PAGEDOWN");
					break;

				case TB_PAGEUP:
					lstrcpy(szMsg,"TB_PAGEUP");
					break;

				case TB_THUMBPOSITION:
					lstrcpy(szMsg,"TB_THUMPOSITION");
					break;

				case TB_THUMBTRACK:
					lstrcpy(szMsg,"TB_THUMBTRACK");
					break;

				default:
					bMsg = FALSE;
					break;

			}
			if (bMsg == TRUE)
			{
				sprintf(szBuf,"Trackbar message: %s",szMsg);
				SendMessage(hWndStatus, SB_SETTEXT, 0, (LPARAM)(LPSTR)szBuf);
			}
			break;

		case WM_COMMAND:

			switch( LOWORD( wParam ))
			{
				case IDM_PROPERTIES:
					CreatePropertySheet(hWnd);
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
	static PROPSHEETPAGE * ps;
	BOOL bErr;
	static UINT uMin, uMax, uMinSave, uMaxSave;

	switch (message)
	{
		case WM_INITDIALOG:	
			// save off the PROPSHEETPAGE information
			ps = (PROPSHEETPAGE *)lParam;
			return (TRUE);

		case WM_NOTIFY:
    		switch (((NMHDR FAR *) lParam)->code) 
    		{

				case PSN_SETACTIVE:
					// initialize the controls
					uMinSave = SendMessage( hWndSlider, TBM_GETRANGEMIN, 0L, 0L);
					uMaxSave = SendMessage( hWndSlider, TBM_GETRANGEMAX, 0L, 0L);
					SetDlgItemInt(hDlg, IDE_MIN, uMinSave, TRUE);
					SetDlgItemInt(hDlg, IDE_MAX, uMaxSave, TRUE);
					break;

				case PSN_APPLY:
					uMin = GetDlgItemInt(hDlg, IDE_MIN, &bErr, TRUE);
					uMax = GetDlgItemInt(hDlg, IDE_MAX, &bErr, TRUE);
					SendMessage( hWndSlider, TBM_SETRANGE, TRUE, 
						MAKELONG(uMin, uMax));
 	           		SetWindowLong(hDlg,	DWL_MSGRESULT, TRUE);
					break;

				case PSN_KILLACTIVE:
	           		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
					return 1;
					break;

				case PSN_RESET:
					// rest to the original values
					SendMessage( hWndSlider, TBM_SETRANGE, TRUE, 
						MAKELONG(uMinSave, uMaxSave));
	           		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
					break;
    	}
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
	static UINT uPage, uPageSave;
	static UINT uLine, uLineSave;
	static PROPSHEETPAGE * ps;

	switch (message)
	{
		case WM_INITDIALOG:
			// save off the PROPSHEETPAGE information
			ps = (PROPSHEETPAGE *)lParam;
			return (TRUE);

		case WM_NOTIFY:
    		switch (((NMHDR FAR *) lParam)->code) 
    		{

				case PSN_SETACTIVE:
					// initialize the controls
					uPageSave = SendMessage( hWndSlider, TBM_GETPAGESIZE, 0L, 0L);
					uLineSave = SendMessage( hWndSlider, TBM_GETLINESIZE, 0L, 0L);
					SetDlgItemInt(hDlg, IDE_LINE, uLineSave, TRUE);
					SetDlgItemInt(hDlg, IDE_PAGE, uPageSave, TRUE);
					break;

				case PSN_APPLY:
					uPage = GetDlgItemInt(hDlg, IDE_PAGE, &bErr, TRUE);
					PostMessage( hWndSlider, TBM_SETPAGESIZE, 0L, uPage);
 					uLine = GetDlgItemInt(hDlg, IDE_LINE, &bErr, TRUE);
					PostMessage( hWndSlider, TBM_SETLINESIZE, 0L, uLine);
 	           		SetWindowLong(hDlg,	DWL_MSGRESULT, TRUE);
					break;

				case PSN_KILLACTIVE:
	           		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
					return 1;
					break;

				case PSN_RESET:
					// rest to the original values
					PostMessage(hWndSlider, TBM_SETPAGESIZE, 0L, uPageSave);
					PostMessage( hWndSlider, TBM_SETLINESIZE, 0L, uLineSave);
	           		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
					break;
    	}
	}
	return (FALSE);   
}

/****************************************************************************
*    FUNCTION: CreatePropertySheet(HWND)
*
*    PURPOSE:  Creates a property sheet
*
****************************************************************************/
int CreatePropertySheet(HWND hwndOwner)
{
    PROPSHEETPAGE psp[2];
    PROPSHEETHEADER psh;

    psp[0].dwSize = sizeof(PROPSHEETPAGE);
    psp[0].dwFlags = PSP_USETITLE;
    psp[0].hInstance = hInst;
    psp[0].pszTemplate = MAKEINTRESOURCE(IDD_RANGE);
    psp[0].pszIcon = NULL;
    psp[0].pfnDlgProc = Range;
    psp[0].pszTitle = "Slider Range";
    psp[0].lParam = 0;

    psp[1].dwSize = sizeof(PROPSHEETPAGE);
    psp[1].dwFlags = PSP_USETITLE;
    psp[1].hInstance = hInst;
    psp[1].pszTemplate = MAKEINTRESOURCE(IDD_PROPS);
    psp[1].pszIcon = NULL;
    psp[1].pfnDlgProc = PageSize;
    psp[1].pszTitle = "Slider Page and Line  Size";
    psp[1].lParam = 0;
    
    psh.dwSize = sizeof(PROPSHEETHEADER);
    psh.dwFlags = PSH_PROPSHEETPAGE;
    psh.hwndParent = hwndOwner;
    psh.hInstance = hInst;
    psh.pszIcon = NULL;
    psh.pszCaption = (LPSTR) "Slider Properties";
    psh.nPages = sizeof(psp) / sizeof(PROPSHEETPAGE);
    psh.ppsp = (LPCPROPSHEETPAGE) &psp;

    return (PropertySheet(&psh));
}

