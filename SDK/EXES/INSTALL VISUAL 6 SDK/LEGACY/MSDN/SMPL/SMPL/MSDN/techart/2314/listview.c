/****************************************************************************
*
*
*    PROGRAM: ListView.c
*
*    PURPOSE: Demonstrates the use of the new list view control in Chicago
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <commctrl.h>   // includes the common control header
#include <stdio.h>
#include <string.h>
#include "listview.h"

// global current instance
HINSTANCE hInst;

// global array of houses
HOUSEINFO rgHouseInfo[] = 
{
	{"100 Main Street", "Redmond", 175000, 3, 2 },
	{"523 Pine Lake Road", "Redmond", 125000, 4, 2},
	{"1212 112th Place SE", "Redmond",200000, 4, 3},
	{"22 Lake Washington Blvd", "Bellevue", 2500000, 4, 4},
	{"33542 116th Ave. NE", "Bellevue", 180000, 3, 2},
	{"64134 Nicholas Lane", "Bellevue", 250000, 4, 3},
	{"33 Queen Anne Hill", "Seattle", 350000, 3, 2},
	{"555 SE Fifth St", "Seattle", 140000, 3, 2},
	{"446 Mariners Way", "Seattle", 225000, 4, 3}
};


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
	WNDCLASS  wcListview;
	
	/* Fill in window class structure with parameters that describe the       */
	/* main window.                                                           */

	wcListview.style = 0;                     
	wcListview.lpfnWndProc = (WNDPROC)MainWndProc; 
	wcListview.cbClsExtra = 0;              
	wcListview.cbWndExtra = 0;              
	wcListview.hInstance = hInstance;       
	wcListview.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(APP_ICON));
	wcListview.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcListview.hbrBackground = GetStockObject(WHITE_BRUSH); 
	wcListview.lpszMenuName =  "ListviewMenu";  
	wcListview.lpszClassName = "ListviewWClass";

	return (RegisterClass(&wcListview));

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
		"ListviewWClass",
		"Listview Sample", 
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
	static HWND hWndListView;
	DWORD dwStyle;

	switch (message) 
	{

		case WM_CREATE:

			hWndListView = CreateListView( hWnd );
			if (hWndListView == NULL)
				MessageBox (NULL, "Listview not created!", NULL, MB_OK );
		 
			break;

		case WM_NOTIFY:
			return( NotifyHandler(hWnd, message, wParam, lParam));
			break;

		case WM_COMMAND:

			switch( LOWORD( wParam ))
			{

				case IDM_LARGEICON:
					dwStyle = GetWindowLong(hWndListView, GWL_STYLE);
					
					if ((dwStyle & LVS_TYPEMASK) != LVS_ICON)
						SetWindowLong(hWndListView, GWL_STYLE,
							(dwStyle & ~LVS_TYPEMASK) | LVS_ICON);
					break;

				case IDM_SMALLICON:
					dwStyle = GetWindowLong(hWndListView, GWL_STYLE);
					
					if ((dwStyle & LVS_TYPEMASK) != LVS_SMALLICON)
						SetWindowLong(hWndListView, GWL_STYLE,
							(dwStyle & ~LVS_TYPEMASK) | LVS_SMALLICON);
					break;

				case IDM_LISTVIEW:
					dwStyle = GetWindowLong(hWndListView, GWL_STYLE);

					if ((dwStyle & LVS_TYPEMASK) != LVS_LIST)
						SetWindowLong(hWndListView, GWL_STYLE,
							(dwStyle & ~LVS_TYPEMASK) | LVS_LIST);
					break;

				case IDM_REPORTVIEW:
					dwStyle = GetWindowLong(hWndListView, GWL_STYLE);

					if ((dwStyle & LVS_TYPEMASK) != LVS_REPORT)
						SetWindowLong(hWndListView, GWL_STYLE,
							(dwStyle & ~LVS_TYPEMASK) | LVS_REPORT);
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

		case WM_SIZE:
            MoveWindow(hWndListView, 0, 0, LOWORD(lParam),HIWORD(lParam),TRUE);
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
*    FUNCTION: CreateListView(HWND)
*
*    PURPOSE:  Creates the list view window and initializes it
*
****************************************************************************/
HWND CreateListView (HWND hWndParent)                                     
{
	HWND hWndList;      // Handle to the list view window
	RECT rcl;           // Rectangle for setting the size of the window
	HICON hIcon;        // Handle to an icon
	int index;          // Index used in for loops
	HIMAGELIST hSmall, hLarge; // Handles to image lists for large and small icons
	LV_COLUMN lvC;      // List View Column structure
	char szText[MAX_PATH];    // Place to store some text
	LV_ITEM lvI;        // List view item structure
	int iSubItem;       // Index for inserting sub items

	// Ensure that the common control DLL is loaded.
	InitCommonControls();

	// Get the size and position of the parent window
	GetClientRect(hWndParent, &rcl);

	// Create the list view window that starts out in report view
    // and allows label editing.
	hWndList = CreateWindowEx( 0L,
		WC_LISTVIEW,                // list view class
		"",                         // no default text
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT |
		    LVS_EDITLABELS | WS_EX_CLIENTEDGE,
		0, 0,
		rcl.right - rcl.left, rcl.bottom - rcl.top,
		hWndParent,
		(HMENU) ID_LISTVIEW,
		hInst,
		NULL );

	if (hWndList == NULL )
		return NULL;


	// initialize the list view window
	// First, initialize the image lists we will need
        // create an image list for the small and large icons
        // FALSE specifies large icons - TRUE specifies small

	hSmall = ImageList_Create( BITMAP_WIDTH, BITMAP_HEIGHT,
		FALSE, 3, 0 );

	hLarge = ImageList_Create( LG_BITMAP_WIDTH, LG_BITMAP_HEIGHT,FALSE, 3, 0 );

 	// load the icons and add them to the image lists
	for (index = REDMOND; index <= SEATTLE ; index++)
	{
		hIcon = LoadIcon ( hInst, MAKEINTRESOURCE(index));
		// there are 3 of each type of icon here, so add 3 at a time.
		for (iSubItem = 0; iSubItem < 3; iSubItem++)
		{
			if ((ImageList_AddIcon(hSmall, hIcon) == -1) ||
				(ImageList_AddIcon(hLarge, hIcon) == -1))
				return NULL;
		}
	}
	
	// Make sure that all of the icons were added
	if (ImageList_GetImageCount(hSmall) < 3)
		return FALSE;

	// Make sure that all of the icons were added
	if (ImageList_GetImageCount(hLarge) < 3)
		return FALSE;

	// Associate the image list with the list view
	ListView_SetImageList(hWndList, hSmall, LVSIL_SMALL);

	ListView_SetImageList(hWndList, hLarge, LVSIL_NORMAL);

	// Now initialize the columns we will need
	// Initialize the LV_COLUMN structure
	// the mask specifies that the .fmt, .ex, width, and .subitem members 
	// of the structure are valid,
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left align the column
	lvC.cx = 75;            // width of the column, in pixels
	lvC.pszText = szText;

	// Add the columns.
	for (index = 0; index <= NUM_COLUMNS; index++)
	{
		lvC.iSubItem = index;
		LoadString( hInst, 
					IDS_ADDRESS + index,
					szText,
					sizeof(szText));
		if (ListView_InsertColumn(hWndList, index, &lvC) == -1)
			return NULL;
	}

	// Finally, let's add the actual items to the control
	// Fill in the LV_ITEM structure for each of the items to add
	// to the list.
	// The mask specifies the the .pszText, .iImage, .lParam and .state
	// members of the LV_ITEM structure are valid.
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	lvI.state = 0;      //
	lvI.stateMask = 0;  //

	for (index = 0; index < NUM_ITEMS; index++)
	{
		lvI.iItem = index;
		lvI.iSubItem = 0;
		// The parent window is responsible for storing the text. The List view
		// window will send a LVN_GETDISPINFO when it needs the text to display/
		lvI.pszText = LPSTR_TEXTCALLBACK; 
		lvI.cchTextMax = MAX_ITEMLEN;
		lvI.iImage = index;
		lvI.lParam = (LPARAM)&rgHouseInfo[index];

		if (ListView_InsertItem(hWndList, &lvI) == -1)
			return NULL;

		for (iSubItem = 1; iSubItem < NUM_COLUMNS; iSubItem++)
		{
			ListView_SetItemText( hWndList,
				index,
				iSubItem,
				LPSTR_TEXTCALLBACK);
		}
	}
	return (hWndList);
}



/****************************************************************************
* 
*    FUNCTION: NotifyHandler(HWND, UINT, UINT, LONG)
*
*    PURPOSE: This function is the handler for the WM_NOTIFY that is 
*    sent to the parent of the list view window.
*
****************************************************************************/
LRESULT NotifyHandler( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LV_DISPINFO *pLvdi = (LV_DISPINFO *)lParam;
	NM_LISTVIEW *pNm = (NM_LISTVIEW *)lParam;
	HOUSEINFO *pHouse = (HOUSEINFO *)(pLvdi->item.lParam);
	static TCHAR szText[10];

	if (wParam != ID_LISTVIEW)
		return 0L;

	switch(pLvdi->hdr.code)
	{
		case LVN_GETDISPINFO:

			switch (pLvdi->item.iSubItem)
			{
				case 0:     // Address
					pLvdi->item.pszText = pHouse->szAddress;
					break;

				case 1:     // City
					pLvdi->item.pszText = pHouse->szCity;
					break;

				case 2:     // Price
					sprintf(szText, "$%u", pHouse->iPrice);
					pLvdi->item.pszText = szText;
					break;

				case 3:     // Number of bedrooms
					sprintf(szText, "%u", pHouse->iBeds);
					pLvdi->item.pszText = szText;
					break;

				case 4:     // Number of bathrooms
					sprintf(szText, "%u", pHouse->iBaths);
					pLvdi->item.pszText = szText;
					break;

				default:
					break;
			}
			break;

        case LVN_BEGINLABELEDIT:
            {
                HWND hWndEdit;

                // Get the handle to the edit box.
                hWndEdit = (HWND)SendMessage(hWnd, LVM_GETEDITCONTROL, 
                    0, 0);
                // Limit the amount of text that can be entered.
                SendMessage(hWndEdit, EM_SETLIMITTEXT, (WPARAM)20, 0);
            }
            break;

        case LVN_ENDLABELEDIT:
            // Save the new label information
            if ((pLvdi->item.iItem != -1) && 
                (pLvdi->item.pszText != NULL))
			    lstrcpy(pHouse->szAddress, pLvdi->item.pszText);
            break;

		case LVN_COLUMNCLICK:
			// The user clicked on one of the column headings - sort by
			// this column.
			ListView_SortItems( pNm->hdr.hwndFrom,
								ListViewCompareProc,
								(LPARAM)(pNm->iSubItem));
			break;

		default:
			break;
	}
	return 0L;
}

/****************************************************************************
* 
*    FUNCTION: ListViewCompareProc(LPARAM, LPARAM, LPARAM)
*
*    PURPOSE: Callback function that sorts depending on the column click 
*
****************************************************************************/
int CALLBACK ListViewCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	HOUSEINFO *pHouse1 = (HOUSEINFO *)lParam1;
	HOUSEINFO *pHouse2 = (HOUSEINFO *)lParam2;
	LPSTR lpStr1, lpStr2;
	int iResult;


	if (pHouse1 && pHouse2)
	{
		switch( lParamSort)
		{
			case 0:     // sort by Address
				lpStr1 = pHouse1->szAddress;
				lpStr2 = pHouse2->szAddress;
				iResult = strcmpi(lpStr1, lpStr2);
				break;

			case 1:     // sort by City
				lpStr1 = pHouse1->szCity;
				lpStr2 = pHouse2->szCity;
				iResult = lstrcmpi(lpStr1, lpStr2);
				break;

			case 2:     // sort by Price
				iResult = pHouse1->iPrice - pHouse2->iPrice;
				break;

			case 3:     // sort by the number of bedrooms
				iResult = pHouse1->iBeds - pHouse2->iBeds;
				break;

			case 4:     // sort by the number of bathrooms
				iResult = pHouse1->iBaths - pHouse2->iBaths;
				break;

			default:
				iResult = 0;
				break;

		}

	}
	return(iResult);
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
