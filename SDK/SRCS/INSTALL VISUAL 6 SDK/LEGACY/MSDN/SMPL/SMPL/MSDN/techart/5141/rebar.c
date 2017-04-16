/****************************************************************************
*
*
*    PROGRAM: REBAR.c
*
*    PURPOSE: Sample demonstrating the rich edit control
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <commctrl.h>   // includes the common control header
#include <string.h>
#include "REBAR.h"
#include "resource.h"

HINSTANCE hInst;

// Toolbar buttons
TOOLINFO tbToolInfo;

TBBUTTON tbButtons[] = {
	{ 0, IDM_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, IDS_NEW},
	{ 1, IDM_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, IDS_OPEN},
	{ 2, IDM_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, IDS_SAVE},
	{ 3, IDM_CUT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, IDS_CUT},
	{ 4, IDM_COPY, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, IDS_COPY},
	{ 5, IDM_PASTE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, IDS_PASTE},
    { 6, IDM_PRINT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, IDS_PRINT},
    { 7, IDM_ABOUT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, IDS_ABOUT}
};

// global array of cool links
COOLLINKS rgLinks[] = 
{
	{TEXT("Microsoft"),TEXT("http://www.microsoft.com/default.htm"), IDB_MSFT},
	{TEXT("Site Builder"), TEXT("http://www.microsoft.com/workshop/default.htm"), IDB_SB},
	{TEXT("Win32 Development"),TEXT("http://www.microsoft.com/win32dev/default.htm"), IDB_WIN32},
	{TEXT("Interactive Media"),TEXT("http://www.microsoft.com/imedia/default.htm"), IDB_IM},
	{TEXT("Microsoft Developer Network"),TEXT("http://www.microsoft.com/msdn/default.htm"), IDB_MSDN},
	{TEXT("Internet Explorer"),TEXT("http://www.microsoft.com/ie30/default.htm"), IDB_IE}
};

// Window procedure for combo box subclassing
WNDPROC lpfnDefCombo;

// Handles to tool control windows
HWND hWndCombo, hWndToolBar, hWndRebar;

// Image list for combo box
HIMAGELIST hIml;
int idxFirstImage;

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
	WNDCLASS  wcREBAR;
	
	/* Fill out window class structure with parameters that describe the       */
	/* main window.                                                           */
	wcREBAR.style = 0;                     
	wcREBAR.lpfnWndProc = (WNDPROC)MainWndProc; 
	wcREBAR.cbClsExtra = 0;              
	wcREBAR.cbWndExtra = 0;              
	wcREBAR.hInstance = hInstance;       
	wcREBAR.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(REBAR_ICON));
	wcREBAR.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcREBAR.hbrBackground = GetStockObject(WHITE_BRUSH); 
	wcREBAR.lpszMenuName =  TEXT("RebarMenu");  
	wcREBAR.lpszClassName = TEXT("REBARWClass");

	return (RegisterClass(&wcREBAR));

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
		TEXT("REBARWClass"),           
		TEXT("REBAR Sample"), 
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

/****************************************************************************
*
*    FUNCTION: MainWndProc(HWND, unsigned, WORD, LONG)
*
*    PURPOSE:  Processes messages for main window
*
****************************************************************************/
LONG APIENTRY MainWndProc(
	HWND hWnd,                /* window handle                   */
	UINT message,             /* type of message                 */
	UINT wParam,              /* additional information          */
	LONG lParam)              /* additional information          */
{

	switch (message) 
	{
 		case WM_CREATE:
		{
			if (!CreateRebar(hWnd))
				MessageBox (NULL, TEXT("Could not create rebar."), NULL, MB_OK );

			ShowWindow(hWnd, SW_SHOW);
		}
        break;

		case WM_COMMAND:
			switch( LOWORD( wParam ))
			{
				case IDM_NEW:
					MessageBox (NULL, TEXT("New"), TEXT("Command"), MB_OK );
					break;

                case IDM_OPEN:
					MessageBox (NULL, TEXT("Open"), TEXT("Command"), MB_OK );
					break;

                case IDM_SAVE:
					MessageBox (NULL, TEXT("Save"), TEXT("Command"), MB_OK );
					break;

                case IDM_CUT:
					MessageBox (NULL, TEXT("Cut"), TEXT("Command"), MB_OK );
					break;

                case IDM_COPY:
					MessageBox (NULL, TEXT("Copy"), TEXT("Command"), MB_OK );
					break;

                case IDM_PASTE:
					MessageBox (NULL, TEXT("Paste"), TEXT("Command"), MB_OK );
					break;

                case IDM_PRINT:
					MessageBox (NULL, TEXT("Print"), TEXT("Command"), MB_OK );
					break;

				case IDM_BARINFO:
					DialogBox(hInst, TEXT("BarInfo"), hWnd, (DLGPROC)BarInfo);
					break;

				case IDM_EXIT:
					SendMessage (hWnd, WM_CLOSE, 0, 0L);
					break;

				case IDM_ABOUT:
					DialogBox(hInst, TEXT("AboutBox"), hWnd, (DLGPROC)About);
					break;

				default:
					return (DefWindowProc(hWnd, message, wParam, lParam));

			}
			break;

		case WM_SIZE:
			MoveWindow(hWndRebar, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE); 
			break;

		case WM_NOTIFY:
			switch (((LPNMHDR)lParam)->code) 
			{
				case TTN_NEEDTEXT:
				{
					LPTOOLTIPTEXT lpToolTipText;
					char szBuf[MAX_PATH];

					// Display the ToolTip text.
					lpToolTipText = (LPTOOLTIPTEXT)lParam;
					LoadString (hInst, 
						lpToolTipText->hdr.idFrom,   // string ID == cmd ID
						szBuf,
						sizeof (szBuf));
					lpToolTipText->lpszText = szBuf;
					break;
				}
				
			}
			break;

		case WM_DESTROY:                  /* message: window being destroyed */
            if (hWndRebar) 
                DestroyWindow(hWndRebar);

            if (hWndToolBar)
                DestroyWindow(hWndToolBar);

            if (hWndCombo)
			{
				ImageList_Destroy(hIml);				
                DestroyWindow(hWndCombo);
			}

			PostQuitMessage(0);
			break;

		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}

/****************************************************************************
*
*    FUNCTION: CreateRebar(HWND)
*
*    PURPOSE:  Creates the rebar
*
****************************************************************************/
UINT CreateRebar(HWND hWndParent)
{
	INITCOMMONCONTROLSEX icex;
	HBITMAP hBmp;
	REBARINFO rbi;

	//This is where we create the rebar control
	// First, we initialize the common controls
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_COOL_CLASSES | ICC_USEREX_CLASSES;	// load the rebar and combo
	InitCommonControlsEx(&icex);

	// create the image list
	hIml = ImageList_Create (
		MIN_COMBOCX,	// width
		MIN_COMBOCY,	// height 
        0,              // creation flags
        NUM_LINKS + 1,		// number of images
        0);             // amount this list can grow

	// Load the bitmap and add it to the image list.
	hBmp = LoadBitmap (hInst, MAKEINTRESOURCE (IDB_SMEAR));
	idxFirstImage = ImageList_Add (hIml,  // handle to image list
                        hBmp,        // handle of bitmap to add
                        NULL);       // handle of bitmap mask

	// Create the REBAR control
	hWndRebar = CreateWindowEx( 
				0L,
				REBARCLASSNAME,
				NULL,
                WS_VISIBLE | WS_BORDER | WS_CHILD | WS_CLIPCHILDREN |
                  WS_CLIPSIBLINGS | CCS_NODIVIDER | CCS_NOPARENTALIGN |
				  RBS_VARHEIGHT | RBS_BANDBORDERS,
				0, 0, 400, 275,
				hWndParent,
				(HMENU)ID_REBAR,
				hInst,
				NULL );

	if (!hWndRebar)
		return 0;

	// Set the image list for the rebar
	rbi.cbSize = sizeof(rbi);
	rbi.fMask = RBIM_IMAGELIST;
	rbi.himl = hIml;
	SendMessage(hWndRebar, RB_SETBARINFO, 0L, (LPARAM)&rbi);

	// Create the combo box
	if ((hWndCombo = CreateComboBox(hWndRebar, hWndParent)) == NULL)
		MessageBox (NULL, TEXT("Could not create the combo box"), NULL, MB_OK );

	// Create the toolbar to be added
	if ((hWndToolBar = CreateTheToolBar(hWndRebar)) == NULL)
		MessageBox (NULL, TEXT("Could not create the toolbar"), NULL, MB_OK );

	return 1;

}
/****************************************************************************
*
*    FUNCTION: CreateComboBox(HWND)
*
*    PURPOSE:  Creates the combo box 
*
****************************************************************************/
HWND CreateComboBox(HWND hWndParent, HWND hWndMain)
{
    int idx, idxImage;
	REBARBANDINFO rbBand;
	COMBOBOXEXITEM cbI;
	HBITMAP	hBmp;


    // create combo box
    hWndCombo = CreateWindowEx ( 
		0,									// extended styles
		"ComboBoxEx32",			                // extended combo box
        TEXT(""),                           // default text
        WS_VISIBLE | WS_CHILD | WS_TABSTOP |
           WS_VSCROLL | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CCS_NORESIZE |
           CBS_AUTOHSCROLL | CBS_DROPDOWNLIST,
        0,0,								// x, y
		MIN_COMBOCX,						// width
		MIN_COMBOCY * NUM_LINKS,			// height
        hWndParent,							// parent window
        (HMENU)ID_COMBO,					// ID
        hInst,								// current instance
        NULL );								// no class data

    if (hWndCombo == NULL)
		return 0;

	// Set the image list for the combo box
	SendMessage( hWndCombo, CBEM_SETIMAGELIST, 0L, (LPARAM)hIml);

	// Add strings to the combo box    
    for (idx=0; idx < NUM_LINKS; idx++)
	{
		// Load the bitmap and add it to the image list.
		hBmp = LoadBitmap (hInst, MAKEINTRESOURCE (rgLinks[idx].iBmp));
		idxImage = ImageList_Add (hIml,  // handle to image list
                            hBmp,        // handle of bitmap to add
                            NULL);       // handle of bitmap mask

		rgLinks[idx].idx = idxImage;

		cbI.mask = CBEIF_TEXT | CBEIF_LPARAM | CBEIF_IMAGE | CBEIF_SELECTEDIMAGE;
		cbI.pszText = rgLinks[idx].szName;
		cbI.cchTextMax = sizeof(rgLinks[idx].szName);
		cbI.lParam = (LPARAM)rgLinks[idx].szURL;
		cbI.iItem = -1;
		cbI.iImage = idxImage;	// Image to display
		cbI.iSelectedImage = idxImage;	// Image to display

		// Add the item to the combo box drop-down list
		SendMessage(hWndCombo, CBEM_INSERTITEM, 0L,(LPARAM)&cbI);
	}

	// Initialize REBARBANDINFO
	rbBand.cbSize = sizeof(REBARBANDINFO);
	rbBand.fMask = RBBIM_COLORS |	// clrFore and clrBack are valid
		RBBIM_CHILD |				// hwndChild is valid
		RBBIM_CHILDSIZE |			// cxMinChild and cyMinChild are valid
		RBBIM_STYLE |				// fStyle is valid
		RBBIM_ID |					// wID is valid
		RBBIM_TEXT |				// lpText is valid
		RBBIM_IMAGE |				// iImage is valid
		RBBIM_BACKGROUND;			// hbmBack is valid
	rbBand.clrFore = GetSysColor(COLOR_BTNTEXT);
	rbBand.clrBack = GetSysColor(COLOR_BTNFACE);
	rbBand.fStyle = RBBS_NOVERT |	// do not display in vertical orientation
		RBBS_CHILDEDGE |
		RBBS_FIXEDBMP;
	rbBand.hbmBack = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BACK));
	rbBand.lpText = TEXT("Cool sites:");
	rbBand.hwndChild = hWndCombo;
	rbBand.cxMinChild = MIN_COMBOCX;
	rbBand.cyMinChild = MIN_CY;
	rbBand.iImage = idxFirstImage;

	// Add the combo box band to the end
	SendMessage(hWndRebar, RB_INSERTBAND, (WPARAM)-1, (LPARAM)&rbBand);

	// Select a default item in the combo box
	SendMessage(hWndCombo, CB_SETCURSEL, (WPARAM)0, 0L);

    // Set the window procedure for the combo box.
    lpfnDefCombo = (WNDPROC)GetWindowLong(hWndCombo, GWL_WNDPROC);
    SetWindowLong(hWndCombo, GWL_WNDPROC, (LONG)ComboWndProc);

    return hWndCombo;
}

/****************************************************************************
*
*    FUNCTION: ComboWndProc(HWND, UINT, WPARAM, LPARAM)
*
*    PURPOSE:  Get the selected link and send it to IE to display.
*
****************************************************************************/
LRESULT CALLBACK ComboWndProc( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	int iSelect;

	if ((uMessage == WM_COMMAND) && (HIWORD(wParam)==CBN_SELCHANGE))
	{
		// Get the currently selected item
 		iSelect = SendMessage(hWndCombo, CB_GETCURSEL, 0, 0);

		ShellExecute( NULL, TEXT("open"), rgLinks[iSelect].szURL,
			NULL, NULL, SW_SHOWNORMAL );
	}

	return (CallWindowProc(lpfnDefCombo, hWnd, uMessage, wParam, lParam));
}

/****************************************************************************
*
*    FUNCTION: CreateTheToolBar(REBARBANDINFO)
*
*    PURPOSE:  Creates the toolbar
*
****************************************************************************/
HWND CreateTheToolBar (HWND hWndParent)
{
	REBARBANDINFO rbBand;

	hWndToolBar = CreateToolbarEx(hWndParent,
        WS_CHILD | TBSTYLE_LIST | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS | WS_CLIPCHILDREN |
           WS_CLIPSIBLINGS | CCS_NODIVIDER | CCS_NORESIZE | WS_VISIBLE,
        ID_TOOLBAR, 
		NUM_TBBITMAPS, 
		(HINSTANCE)hInst, 
		IDB_TOOLBAR, 
        (LPCTBBUTTON)&tbButtons,
        NUM_TBBUTTONS,
		BMP_CX,BMP_CY,                  // width & height of buttons
		BMP_CX,BMP_CY,                  // width & height of bitmaps
		sizeof(TBBUTTON));

	if (hWndToolBar == NULL )
	{
		MessageBox (NULL, TEXT("Toolbar not created!"), NULL, MB_OK );
		return (HWND)NULL;
	}

	// Initialize REBARBANDINFO for all rebar bands
	rbBand.cbSize = sizeof(REBARBANDINFO);
	rbBand.fMask = RBBIM_COLORS |	// clrFore and clrBack are valid
		RBBIM_CHILD |				// hwndChild is valid
		RBBIM_CHILDSIZE |			// cxMinChild and cyMinChild are valid
		RBBIM_STYLE |				// fStyle is valid
		RBBIM_ID |					// wID is valid
		RBBIM_BACKGROUND;			// hbmBack is valid
	rbBand.clrFore = GetSysColor(COLOR_BTNTEXT);
	rbBand.clrBack = GetSysColor(COLOR_BTNFACE);
	rbBand.fStyle = RBBS_NOVERT |	// do not display in vertical orientation
		RBBS_CHILDEDGE |
		RBBS_FIXEDBMP;
	rbBand.hbmBack = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BACK));
	rbBand.hwndChild = hWndToolBar;
	rbBand.wID = ID_TOOLBAR;
	rbBand.cxMinChild = MIN_TBCX;
	rbBand.cyMinChild = MIN_CY;

	// Insert band into rebar
	SendMessage(hWndRebar, RB_INSERTBAND, (UINT) -1, (LPARAM) (LPREBARBANDINFO) &rbBand);

	return (hWndToolBar);

}

/****************************************************************************
*
*    FUNCTION: BarInfo(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "BarInfo" dialog box
*			   It calls RB_GETBARINFO, RB_GETBANDCOUNT, 
*		       RB_GETROWHEIGHT, and RB_GETROWCOUNT
*			   to get information about the rebar
*			   then displays the information in the dialog box fields.
*
****************************************************************************/
BOOL APIENTRY BarInfo(
	HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
	static UINT uHeight, uRowCount, uBandCount;
	static REBARINFO rbi;

	switch (message)
	{
		case WM_INITDIALOG:
			// get the number of bands
			uBandCount = SendMessage(hWndRebar, RB_GETBANDCOUNT, 0, 0);
			SetDlgItemInt(hDlg, IDC_NUMBANDS, uBandCount, FALSE);
			// get the number of rows
			uRowCount = SendMessage(hWndRebar, RB_GETROWCOUNT, 0, 0);
			SetDlgItemInt(hDlg, IDC_NUMROWS, uRowCount, FALSE);
			// get the row height for the first row
			uHeight = SendMessage(hWndRebar, RB_GETROWHEIGHT, 0, 0);
			SetDlgItemInt(hDlg, IDC_ROWHEIGHT, uHeight, FALSE);
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
