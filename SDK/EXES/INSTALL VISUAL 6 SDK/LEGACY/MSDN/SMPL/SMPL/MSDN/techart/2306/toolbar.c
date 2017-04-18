/****************************************************************************
*
*
*    PROGRAM: Toolbar.c
*
*    PURPOSE: Toolbar for testing
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <commctrl.h>   // includes the common control header
#include <string.h>
#include "toolbar.h"
#include "resource.h"

HINSTANCE hInst;
HWND hWndToolBar;
// Window procedures for combo box subclassing
WNDPROC lpfnDefCombo;

TBBUTTON tbButtons[] = {
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, IDM_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 1, IDM_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 2, IDM_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 3, IDM_CUT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{4, IDM_COPY, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 5, IDM_PASTE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 6, IDM_PRINT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
    { 7, IDM_ABOUT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0}
};

TOOLINFO tbToolInfo;

char *szStrings[] = { "Nancy", "Dale", "Dennis", "Herman", "Ken", "Kyle", "Nigel", "Renan", "Ruediger"};


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

	// Ensure that common control DLL is loaded
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
	WNDCLASS  wcToolbar;
	
	/* Fill in window class structure with parameters that describe the       */
	/* main window.                                                           */

	wcToolbar.style = 0;                     
	wcToolbar.lpfnWndProc = (WNDPROC)MainWndProc; 
	wcToolbar.cbClsExtra = 0;              
	wcToolbar.cbWndExtra = 0;              
	wcToolbar.hInstance = hInstance;       
	wcToolbar.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(TOOLBAR_ICON));
	wcToolbar.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcToolbar.hbrBackground = GetStockObject(WHITE_BRUSH); 
	wcToolbar.lpszMenuName =  "ToolbarMenu";  
	wcToolbar.lpszClassName = "ToolbarWClass";

	return (RegisterClass(&wcToolbar));

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
	HWND            hWnd;

	hInst = hInstance;

	hWnd = CreateWindow(
		"ToolbarWClass",           
		"Toolbar Sample", 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 
        CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,               
		NULL,               
		hInstance,          
		NULL);

	/* If window could not be created, return "failure" */
	if (!hWnd)
		return (FALSE);

	/* Make the window visible; update its client area; and return "success" */
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); 
	return (TRUE);      

}
//
// This function relays the mouse messages from the combo box
// in order to get tool tips to work.
//
LRESULT CALLBACK ComboWndProc( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
  switch (uMessage)
  {
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    {
        MSG msg;
        HWND hWndTT;
        msg.lParam = lParam;
        msg.wParam = wParam;
        msg.message = uMessage;
        msg.hwnd = hWnd;
        hWndTT = (HWND)SendMessage(hWndToolBar, TB_GETTOOLTIPS, 0,0);
        SendMessage(hWndTT, TTM_RELAYEVENT, 0, (LPARAM)(LPMSG)&msg);
        break;
    }
  }
  return (CallWindowProc(lpfnDefCombo, hWnd, uMessage, wParam, lParam));
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
	static HWND hWndToolbar;      
    static HWND hWndCombo;
    static HWND hWndTT;
	HDC hdc;
	PAINTSTRUCT ps;
	static CHAR szBuf[128];
	LPTOOLTIPTEXT lpToolTipText;
    int idx;
    TOOLINFO lpToolInfo;
    RECT rcl = {0,0,100,30};

	switch (message) 
	{
 		case WM_CREATE:
			// create toolbar control
			hWndToolBar = CreateToolbarEx( 
				hWnd,                   // parent
				WS_CHILD | WS_BORDER | WS_VISIBLE | TBSTYLE_TOOLTIPS | CCS_ADJUSTABLE,   // style
				ID_TOOLBAR,             // toolbar id
				8,                      // number of bitmaps
				hInst,                  // mod instance
				IDB_TOOLBAR,            // resource id for the bitmap
				(LPCTBBUTTON)&tbButtons,// address of buttons
				24,                     // number of buttons
				16,16,                  // width & height of the buttons
				16,16,                  // width & height of the bitmaps
				sizeof(TBBUTTON));      // structure size

			if (hWndToolBar == NULL )
			{
				MessageBox (NULL, "Toolbar Bar not created!", NULL, MB_OK );
				break;
			}

             // Create the combo box and add it to the toolbar.
            hWndCombo = CreateWindowEx ( 0L,   // No extended styles.
                "COMBOBOX",                    // Class name.
                "",                            // Default text.
                WS_CHILD | WS_BORDER | WS_VISIBLE |
                    CBS_HASSTRINGS | CBS_DROPDOWN,    // Styles and defaults.
                0, 0, 100, 250,                // Size and position.
                hWndToolBar,                   // Parent window.
                (HMENU)IDM_COMBO,              // ID.
                hInst,                         // Current instance.
                NULL );                        // No class data.
            if (hWndCombo)
            {
                //Add strings to combo box    
                for (idx=0; idx < 9; idx++)
                    SendMessage(hWndCombo, CB_INSERTSTRING,(WPARAM)-1, (LPARAM)szStrings[idx]);
            }
            // Set the window procedure for the combo box.
            lpfnDefCombo = (WNDPROC)GetWindowLong(hWndCombo, GWL_WNDPROC);
            SetWindowLong(hWndCombo, GWL_WNDPROC, (LONG)ComboWndProc);

            // Get the handle to the tooltip window.
            hWndTT = (HWND)SendMessage(hWndToolBar, TB_GETTOOLTIPS, 0, 0);

            if (hWndTT)
            {
                // Fill in the TOOLINFO structure.
                lpToolInfo.cbSize = sizeof(lpToolInfo);
                lpToolInfo.uFlags = TTF_IDISHWND | TTF_CENTERTIP;
                lpToolInfo.lpszText = (LPSTR)IDM_COMBO;
                lpToolInfo.hwnd = hWnd;
                lpToolInfo.uId = (UINT)hWndCombo;
                lpToolInfo.hinst = hInst;
                // Set up tooltips for the combo box.
                SendMessage(hWndTT, TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO)&lpToolInfo);
            }
            else
                MessageBox(NULL, "Could not get tooltip window handle.",NULL, MB_OK);
			break;

		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			TextOut(hdc, 20, 10, hello, lstrlen(hello));      
			EndPaint(hWnd, &ps);
		}
		break;
	 
        case WM_SIZE:
            // Tell the toolbar to resize itself to fill the top of the window.
            SendMessage(hWndToolBar, TB_AUTOSIZE, 0L, 0L);
            break;

		case WM_COMMAND:

			switch( LOWORD( wParam ))
			{
				case IDM_NEW:
                case IDM_OPEN:
                case IDM_SAVE:
                case IDM_CUT:
                case IDM_COPY:
                case IDM_PASTE:
                case IDM_PRINT:
					MessageBox (NULL, "Not implemented in this sample.", "Command", MB_OK );
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

        case WM_LBUTTONDBLCLK:
            // Double-click on the toolbar -- display the customization dialog.
            SendMessage(hWndToolBar, TB_CUSTOMIZE, 0L , 0L );
            break;
	  
		case WM_NOTIFY:
            switch (((LPNMHDR) lParam)->code) 
            {
                case TTN_NEEDTEXT:    
                    // Display tool tip text.
			        lpToolTipText = (LPTOOLTIPTEXT)lParam;
    				LoadString (hInst, 
	    				lpToolTipText->hdr.idFrom,    // string ID == cmd ID
		    			szBuf,
			    		sizeof(szBuf));
				    	lpToolTipText->lpszText = szBuf;
			        break;

                case TBN_QUERYDELETE:
                    // Toolbar customization -- can we delete this button?
                    return TRUE;
                    break;

                case TBN_GETBUTTONINFO:
                    // The toolbar needs information about a button.
                    return FALSE;
                    break;

                case TBN_QUERYINSERT:
                    // Can this button be inserted? Just say yo.
                    return TRUE;
                    break;

                case TBN_CUSTHELP:
                    // Need to display custom help.
                    MessageBox(hWnd, "This help is custom.",NULL, MB_OK);
                    break;

                case TBN_TOOLBARCHANGE:
                    // Done dragging a bitmap to the toolbar.
                    SendMessage(hWndToolBar, TB_AUTOSIZE, 0L, 0L);
                    break;

                default:
                    return TRUE;
                    break;
            }
			return 0L;
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


