/****************************************************************************
*
*
*    PROGRAM: ChicoApp.c
*
*    PURPOSE: ChicoApp demonstrates how a new Chicago app will look and run
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <commctrl.h>   // includes the common control header
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cderr.h>      // includes the common dialog error codes
#include "chicoapp.h"

// GLOBALS
// structure containing information about the for sale listing
LISTINFO g_Listing;

// tool bar buttons
TBBUTTON tbButtons[] = {
    { STD_FILENEW, IDM_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { STD_FILEOPEN, IDM_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { STD_FILESAVE, IDM_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
    { VIEW_LARGEICONS, IDM_LARGEICON, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { VIEW_SMALLICONS, IDM_SMALLICON, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { VIEW_LIST, IDM_LISTVIEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { VIEW_DETAILS, IDM_REPORTVIEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
};

// arrays of houses and cities to hold house and city info
HOUSEINFO rgHouses[MAX_HOUSES];
CITYINFO  rgCities[MAX_CITIES];

// File I/o Globals

OPENFILENAME OpenFileName;
char         szDirName[MAX_PATH]   = "";
char         szFile[MAX_PATH]      = "\0";
char         szFileTitle[MAX_PATH];

// Filter specification for the OPENFILENAME struct
// This is portable for i386 and MIPS
// Leaving out the \0 terminator will cause improper DWORD alignment
// and cause a failure under MIPS
char szFilter[] = "Text Files (*.TXT)\0*.TXT\0All Files (*.*)\0*.*\0";
					    
char *lpBufPtr;


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
    WNDCLASS  wcChicoApp;
	
	/* Fill in window class structure with parameters that describe the       */
	/* main window.                                                           */

    wcChicoApp.style = 0;                     
    wcChicoApp.lpfnWndProc = (WNDPROC)MainWndProc; 
    wcChicoApp.cbClsExtra = 0;              
    wcChicoApp.cbWndExtra = 0;              
    wcChicoApp.hInstance = hInstance;       
    wcChicoApp.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(CHICOAPP));
    wcChicoApp.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcChicoApp.hbrBackground = GetStockObject(WHITE_BRUSH); 
    wcChicoApp.lpszMenuName =  "ChicoAppMenu";  
    wcChicoApp.lpszClassName = "ChicoAppWClass";

    return (RegisterClass(&wcChicoApp));

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

    g_Listing.hInst = hInstance;

    g_Listing.hWndMain = CreateWindow(
	"ChicoAppWClass",           
	"ChicoApp Sample", 
	WS_OVERLAPPEDWINDOW,
	50, 50, 500, 400,
	NULL,               
	NULL,               
	g_Listing.hInst,          
	NULL);

	/* If window could not be created, return "failure" */
    if (!g_Listing.hWndMain)
		return (FALSE);

	/* Make the window visible; update its client area; and return "success" */
    ShowWindow(g_Listing.hWndMain, nCmdShow);
    UpdateWindow(g_Listing.hWndMain); 
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
    WORD wCommand;
    static CHAR szBuf[MAX_PATH];
	LPTOOLTIPTEXT lpToolTipText;
    MENUITEMINFO lpMii;
	HMENU hMenu, hMenuTrackPopup;

	switch (message) 
	{

		case WM_CREATE:
            g_Listing.NumCities = 0;
            g_Listing.NumHouses = 0;
            g_Listing.iSelected = -1;
            if (CreateAppWindows(hWnd) == FALSE)
                return FALSE;
			break;

        case WM_SIZE:
            if (!ResizeWindows(hWnd))
                MessageBox(NULL, "Window resizing failed!", NULL, MB_OK);
            break;

		case WM_NOTIFY:
            lpToolTipText = (LPTOOLTIPTEXT)lParam;
            if (lpToolTipText->hdr.code ==  TTN_NEEDTEXT)
            {
                LoadString (g_Listing.hInst, 
                lpToolTipText->hdr.idFrom,    // string ID == cmd ID
                szBuf,
                sizeof(szBuf));
                lpToolTipText->lpszText = szBuf;
            }
            if (TV_NotifyHandler(hWnd, message, wParam, lParam, &g_Listing))
            {
                // update the list view window to reflect the selected cities houses
                UpdateListView(g_Listing.hWndListView, g_Listing.iSelected);

                // update the status bar text
                ChangeSBText(g_Listing.hInst, g_Listing.hWndStatus, g_Listing.iSelected );
            }
			//g_Listing.iSelHouse = LV_NotifyHandler(hWnd, message, wParam, lParam, g_Listing.hInst);
            LV_NotifyHandler(hWnd, message, wParam, lParam, g_Listing.hInst);
			break;

		case WM_COMMAND:

            wCommand = LOWORD(wParam);
			switch( LOWORD( wParam ))
			{
                case IDM_NEW:
                    // initialize the tree view and list view windows
                    InitTreeAndList();
                    // disable the Remove House menu item
                    EnableMenuItem( GetMenu( hWnd ), IDM_REMHOUSE,
                        MF_BYCOMMAND | MF_GRAYED );
                    DrawMenuBar( hWnd);
                    break;

                case IDM_OPEN:
                    if ( OpenNewFile( hWnd ) == TRUE )
                    {
                        // enable the Save As menu item
                        EnableMenuItem( GetMenu( hWnd ), IDM_SAVE,
                            MF_BYCOMMAND | MF_ENABLED );
    
                        // enable the Remove House menu item
                        EnableMenuItem( GetMenu( hWnd ), IDM_REMHOUSE,
                            MF_BYCOMMAND | MF_ENABLED );

                        DrawMenuBar( hWnd);
                        // reset the title in the title bar to reflect the
                        // new open file
						// first strip off the extension, if any
						if (strstr(OpenFileName.lpstrFile, ".txt") != NULL)
							strncpy (szBuf, OpenFileName.lpstrFile, strlen(OpenFileName.lpstrFile)-4);
						else
							lstrcpy(szBuf, OpenFileName.lpstrFile);
                        SetWindowText( hWnd, szBuf );
                        // reset the current color and current font to the
                        // default
                        InvalidateRect( hWnd, NULL, TRUE );
                    }
                    break;

                case IDM_SAVE:
                    OpenFileName.Flags = 0L;
                    SaveToFile( hWnd );
                    break;

                case IDM_SAVEAS:
                    if ( SaveAs( hWnd ) == TRUE )
                    {
                        EnableMenuItem( GetMenu( hWnd ), IDM_SAVE,
                            MF_BYCOMMAND | MF_ENABLED );
                        SetWindowText( hWnd, OpenFileName.lpstrFile );
                        DrawMenuBar( hWnd );
                    }
                    break;

                case IDM_ADDHOUSE:
                    DialogBox(g_Listing.hInst, MAKEINTRESOURCE(IDD_ADDHOUSE), hWnd,
                        (DLGPROC)AddHouse);
                    // if Remove House is disabled, enable it
                    lpMii.fMask = MIIM_STATE;
                    GetMenuItemInfo(GetMenu(hWnd), IDM_REMHOUSE, FALSE,
                        &lpMii);
                    if (lpMii.fState == MFS_GRAYED )
                    {
                        EnableMenuItem( GetMenu( hWnd ), IDM_REMHOUSE,
                            MF_BYCOMMAND | MF_ENABLED );

                        DrawMenuBar( hWnd);
                    }
					break;

                case IDM_REMHOUSE:
                    DialogBox(g_Listing.hInst, MAKEINTRESOURCE(IDD_REMHOUSE), hWnd,
                        (DLGPROC)RemoveHouse);
					break;

                case IDM_ADDCITY:
                    DialogBox(g_Listing.hInst, MAKEINTRESOURCE(IDD_ADDCITY), hWnd,
                        (DLGPROC)AddCity);
					break;

                case IDM_LISTVIEW:
                case IDM_REPORTVIEW:
                case IDM_SMALLICON:
                case IDM_LARGEICON:
                    LV_ChangeView(g_Listing.hWndListView, wCommand);
                    break;

				case IDM_EXIT:
					PostQuitMessage(0);
					break;

				case IDM_ABOUT:
                    DialogBox(g_Listing.hInst, "AboutBox", hWnd, (DLGPROC)About);
					break;

				case IDM_HOUSEPROPS:
					if (CreatePropertySheet(hWnd) == 1)
						InvalidateRect(g_Listing.hWndListView, NULL, TRUE); 
					break;

				default:
					return (DefWindowProc(hWnd, message, wParam, lParam));

            }
            break;

	   case WM_CONTEXTMENU:
	   		// The right mouse button has been clicked.
			if ((HWND)wParam == g_Listing.hWndListView)
			{
			    // Get the context menu from the resource file.
   				hMenu = LoadMenu(g_Listing.hInst, "HousePopupMenu");
   				if (!hMenu)
       				break;;

   				// Get the first item in the menu for TrackPopupMenu(). 
   				hMenuTrackPopup = GetSubMenu(hMenu, 0);

   				// Draw and track the "floating" menu. 
   				TrackPopupMenu(hMenuTrackPopup, 
   					TPM_LEFTALIGN | TPM_RIGHTBUTTON,
       				LOWORD(lParam), HIWORD(lParam), 
       				0, g_Listing.hWndListView, NULL);

			    // Destroy the menu
   				DestroyMenu(hMenu);
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
*    FUNCTION: InitTreeAndList(VOID)
*
*    PURPOSE:  Initializes the tree and list view windows.
*
****************************************************************************/
VOID InitTreeAndList( VOID )
{
    g_Listing.NumCities = 0;
    g_Listing.NumHouses = 0;
    g_Listing.iSelected = -1;
	g_Listing.iSelHouse = -1;
    TV_RemoveAllItems(g_Listing.hWndTreeView);
    LV_RemoveAllItems(g_Listing.hWndListView);
    TV_InitTreeView(g_Listing.hInst, g_Listing.hWndTreeView);

}


/****************************************************************************
*
*    FUNCTION: ResizeWindows(HWND)
*
*    PURPOSE:  Resizes all of the child windows used in ChicoApp
*
****************************************************************************/
BOOL ResizeWindows(HWND hwnd)
{
    RECT rcl;
    HDWP hdwp;

    // Get the client area of the parent window.
    GetClientRect(hwnd, &rcl);

    // You will defer all the application's windows.
    hdwp = BeginDeferWindowPos(NUM_WINDOWS);

    // First, reset the size of the status bar.
    DeferWindowPos(hdwp, g_Listing.hWndStatus, NULL, 0, 0,
	rcl.right - rcl.left, STATUS_BAR_HEIGHT, SWP_NOZORDER | SWP_NOMOVE);

    // Next, reset the size of the toolbar.
    DeferWindowPos(hdwp, g_Listing.hWndToolbar, NULL, 0, 0,
	rcl.right - rcl.left, TOOLBAR_HEIGHT, SWP_NOZORDER | SWP_NOMOVE);

    // Next, reset the size of the tree view control.
    DeferWindowPos(hdwp, g_Listing.hWndTreeView, NULL, 0, 0,
	(rcl.right - rcl.left ) / 4, rcl.bottom - rcl.top - 46,
	SWP_NOZORDER | SWP_NOMOVE);

    // Last, reset the size of the list view control.
    DeferWindowPos(hdwp, g_Listing.hWndListView, NULL,
	(rcl.right - rcl.left ) / 4, 27,
	(rcl.right - rcl.left) - ((rcl.right - rcl.left)/4),
	rcl.bottom - rcl.top - 46,
	SWP_NOZORDER );


    return EndDeferWindowPos(hdwp);
}

/****************************************************************************
*
*    FUNCTION: CreateAppWindows(HWND)
*
*    PURPOSE:  Creates all of the child windows to be used in ChicoApp
*
****************************************************************************/

BOOL CreateAppWindows( HWND hwndParent )
{
    RECT rcl;
    int lpSBParts[2];
    static char szBuf[MAX_PATH];

    // Ensure the common controls are loaded
	InitCommonControls();

	// get the size and position of the parent window
    GetClientRect(hwndParent, &rcl);

    // First, create the status window.
    g_Listing.hWndStatus = CreateStatusWindow( 
	WS_CHILD | WS_BORDER | WS_VISIBLE,  // window styles
	"",                                 // default window text
	hwndParent,                         // parent window
	ID_STATUS);                         // ID

    if (g_Listing.hWndStatus == NULL)
	   MessageBox (NULL, "Status Bar not created!", NULL, MB_OK );

    // Set the status bar to have two parts.
    lpSBParts[0] = (rcl.right - rcl.left) / 2;
    lpSBParts[1] = -1;
    SendMessage( g_Listing.hWndStatus, SB_SETPARTS, (WPARAM)2, (LPARAM)&lpSBParts);

    // set the text for the status bar
    ChangeSBText(g_Listing.hInst, g_Listing.hWndStatus, -1);

    // Next, create the tool bar
	g_Listing.hWndToolbar = CreateTheToolbar(hwndParent);

    if (g_Listing.hWndToolbar == NULL )
		MessageBox (NULL, "Toolbar Bar not created!", NULL, MB_OK );

    // create the list view window
    g_Listing.hWndListView = LV_CreateListView( hwndParent, g_Listing.hInst, g_Listing.NumHouses, &rgHouses[0] );

    if (g_Listing.hWndListView == NULL)
    {
		MessageBox (NULL, "Listview not created!", NULL, MB_OK );
		return FALSE;
    }

    // Create the tree view window and initialize its
    // image list
    g_Listing.hWndTreeView = TV_CreateTreeView( hwndParent, g_Listing.hInst,
	g_Listing.NumCities, rgCities );

    if (g_Listing.hWndTreeView == NULL)
    {
	    MessageBox (NULL, "Tree View not created!", NULL, MB_OK );
	    return FALSE;
    }

    return TRUE;

}

/****************************************************************************
*
*    FUNCTION: CreateTheToolbar(HWND)
*
*    PURPOSE:  Creates the toolbar to be used in ChicoApp using the standard
*			   system-defined bitmaps.
*
****************************************************************************/

HWND CreateTheToolbar(HWND hWndParent)
{
	HWND hWndToolbar;
	TBADDBITMAP tb;
    int index, stdidx;


    hWndToolbar = CreateToolbarEx(hWndParent, 
        WS_CHILD | WS_BORDER | WS_VISIBLE | WS_CHILD | TBSTYLE_TOOLTIPS, 
        ID_TOOLBAR, 11, (HINSTANCE)HINST_COMMCTRL, IDB_STD_SMALL_COLOR, 
        (LPCTBBUTTON)&tbButtons, 4, 0, 0, 100, 30, sizeof(TBBUTTON));

    // Add the system-defined view bitmaps.
	// The hInst == HINST_COMMCTRL
	// The nID == IDB_VIEW_SMALL_COLOR.
	tb.hInst = HINST_COMMCTRL;
	tb.nID = IDB_VIEW_SMALL_COLOR;
	stdidx = SendMessage(hWndToolbar, TB_ADDBITMAP, 12, (LPARAM)&tb);

    // Update the indexes to the bitmaps.
    for (index = 4; index < NUM_BUTTONS; index++)
        tbButtons[index].iBitmap += stdidx;

    // Add the view buttons.
   	SendMessage(hWndToolbar, TB_ADDBUTTONS, 4, (LONG) &tbButtons[4]);

    return (hWndToolbar);
}

/****************************************************************************
*
*    FUNCTION: ChangeSBText(HINSTANCE, HWND, int)
*
*    PURPOSE:  Changes the text in the status bar to reflect the
*              currently selected item.
*
****************************************************************************/
VOID ChangeSBText(HINSTANCE hInst, HWND hwnd, int iNumSelected)
{
    static char szBuf1[MAX_LEN];
    static char szBuf2[MAX_LEN];
    static char szSelected[MAX_LEN];
    char szText[MAX_ITEMLEN];
    int NumHouses;

    if (szBuf1[0] == '\0')
	LoadString (hInst, IDS_SELECTED, szBuf1, sizeof(szBuf1));

    if (szBuf2[0] == '\0')
	LoadString (hInst, IDS_NUMHOUSES, szBuf2, sizeof(szBuf2));

    if (iNumSelected == -1)
    {
	lstrcpy( szSelected, "None");
	NumHouses = 0;
    }
    else
    {
	lstrcpy( szSelected, rgCities[iNumSelected].szCity);
	NumHouses = rgCities[iNumSelected].NumHouses;
    }

    wsprintf(szText, "%s %s", szBuf1, szSelected);
    SendMessage(hwnd, SB_SETTEXT, 0, (LPARAM)szText);

    wsprintf(szText, "%s %d", szBuf2, NumHouses);
    SendMessage(hwnd, SB_SETTEXT, 1, (LPARAM)szText);

}

/****************************************************************************
*
*    FUNCTION: OpenNewFile(HWND)
*
*    PURPOSE:  Invokes common dialog function to open a file and opens it.
*
*    COMMENTS:
*
*        This function initializes the OPENFILENAME structure and calls
*        the GetOpenFileName() common dialog function.  
*
*    RETURN VALUES:
*        TRUE - The file was opened successfully and read into the buffer.
*        FALSE - No files were opened.
*
****************************************************************************/
BOOL OpenNewFile( HWND hWnd )
{
    HANDLE hFile;
    DWORD dwBytesRead;
    DWORD dwFileSize;

    lstrcpy( szFile, "");
    lstrcpy( szFileTitle, "");

    OpenFileName.lStructSize       = sizeof(OPENFILENAME);
    OpenFileName.hwndOwner         = hWnd;
    OpenFileName.hInstance         = (HANDLE) g_Listing.hInst;
    OpenFileName.lpstrFilter       = szFilter;
    OpenFileName.lpstrCustomFilter = (LPTSTR) NULL;
    OpenFileName.nMaxCustFilter    = 0L;
    OpenFileName.nFilterIndex      = 1L;
    OpenFileName.lpstrFile         = szFile;
    OpenFileName.nMaxFile          = sizeof(szFile);
    OpenFileName.lpstrFileTitle    = szFileTitle;
    OpenFileName.nMaxFileTitle     = sizeof(szFileTitle);
    OpenFileName.lpstrInitialDir   = NULL;
    OpenFileName.lpstrTitle        = "Open a File";
    OpenFileName.nFileOffset       = 0;
    OpenFileName.nFileExtension    = 0;
    OpenFileName.lpstrDefExt       = "*.txt";
    OpenFileName.lCustData         = 0;
    OpenFileName.Flags             = OFN_SHOWHELP | OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    if (GetOpenFileName(&OpenFileName))
    {
	if ((hFile = CreateFile((LPCTSTR)OpenFileName.lpstrFile,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			(HANDLE)NULL)) == (HANDLE)-1)
	{
	    MessageBox( hWnd, "File open failed.", NULL, MB_OK );
	    return FALSE;
	}

	// get the size of the file
	dwFileSize = GetFileSize(hFile, NULL);
	if (dwFileSize == 0xFFFFFFFF)
	{
	    MessageBox( NULL, "GetFileSize failed!", NULL, MB_OK);
	    return FALSE;
	}

	// allocate a buffer for the file to be read into
	lpBufPtr = (char *)GlobalAlloc( GMEM_FIXED, dwFileSize );
	if (lpBufPtr == NULL)
	{
	    MessageBox( NULL, "GlobalAlloc failed!", NULL, MB_OK);
	    CloseHandle( hFile );
	    return FALSE;
	}

	// read it's contents into a buffer
	ReadFile(hFile,(LPVOID)lpBufPtr, dwFileSize, &dwBytesRead, NULL);

	if (dwBytesRead == 0)
	{
	    MessageBox( hWnd, "Zero bytes read.", NULL, MB_OK );
	    return FALSE;
	}

	// close the file
	CloseHandle(hFile);

	// Parse the file buffer
	return (ParseFile());
    }
    else
    {
	ProcessCDError(CommDlgExtendedError(), hWnd );
	return FALSE;
    }
}

/****************************************************************************
*
*    FUNCTION: ParseFile()
*
*    PURPOSE:  Parses the current file buffer.
*
*    COMMENTS:
*
*        This function will parse the current file buffer and initialize
*        the global city and house information structures.
*
*        The file is an editable ASCII file and set up as follows:
*           - Number of cities
*           - A string representing each city for # of cities specified above
*           - Number of houses
*           - House information for each house. One line per house.
*             The fields are separated by commas and are in the following
*             order:
*                   Address
*                   City
*                   Price
*                   Bedrooms
*                   Bathrooms
*
*    RETURN VALUES:
*        TRUE - The file was parsed successfully.
*        FALSE - The parsing failed.
*
****************************************************************************/
BOOL ParseFile ( VOID )
{
    int count, result, index;
    char szTemp[MAX_PATH], szBeds[TEMP_LEN], szBaths[TEMP_LEN];
    char * lpSave;
    HTREEITEM hPrev;

    // initialize the tree view and list view windows
    InitTreeAndList();

    lpSave = lpBufPtr;

    // read in the first line to get the number of cities
    sscanf( lpBufPtr, "%s\n", szTemp);
    g_Listing.NumCities = atoi(szTemp);

    // move the buffer pointer
    while (*lpBufPtr != 0x0A)
	lpBufPtr++;
    lpBufPtr++;

    if (g_Listing.NumCities == 0 || g_Listing.NumCities > MAX_CITIES)
    {
	MessageBox(NULL, "Number of cities must be between 1 and 16", NULL, MB_OK);
	GlobalFree(lpBufPtr);
	return FALSE;
    }
     
    // read a city for each line
    for (count= 0; count < g_Listing.NumCities; count++)
    {
	sscanf( lpBufPtr, "%s\n", rgCities[count].szCity);

	// move the buffer pointer
	while (*lpBufPtr != 0x0A)
	    lpBufPtr++;
	lpBufPtr++;

	// Add the city to the tree view
	hPrev = TV_AddOneItem( rgCities[count].szCity, g_Listing.hWndTreeView, count);

    }
	
    // get the number of houses
    sscanf( lpBufPtr, "%s\n", szTemp);
    g_Listing.NumHouses = atoi(szTemp);

    // move the buffer pointer
    while (*lpBufPtr != 0x0A)
	lpBufPtr++;
    lpBufPtr++;

    if (g_Listing.NumHouses == 0 || g_Listing.NumHouses > MAX_HOUSES)
    {
	MessageBox(NULL, "Number of houses must be between 1 and 256", NULL, MB_OK);
	GlobalFree(lpBufPtr);
	return FALSE;
    }

    // Read the house information for each line.
    for (count = 0; count < g_Listing.NumHouses; count++)
    {
	result = sscanf(lpBufPtr, "%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%s", 
	    rgHouses[count].szAddress,
	    rgHouses[count].szCity,
	    szTemp, szBeds, szBaths, 
	    rgHouses[count].szAgent,
	    rgHouses[count].szNumber);

	rgHouses[count].iPrice = atoi(szTemp);
	rgHouses[count].iBeds = atoi(szBeds);
	rgHouses[count].iBaths = atoi(szBaths);

	// move the buffer pointer
	while (*lpBufPtr != 0x0A)
	    lpBufPtr++;
	lpBufPtr++;

	// increment the house count for the city
	for (index=0;index < g_Listing.NumCities; index++)
	{
	    if (lstrcmp(rgHouses[count].szCity, rgCities[index].szCity) == 0)
	    {
		rgCities[index].NumHouses++;
		break;
	    }
	}
    }
    // free up the buffer
    GlobalFree(lpBufPtr);

    // Now, add the cities and houses to the list and tree views

    return TRUE;
}

/****************************************************************************
*
*    FUNCTION: UpdateListView( HWND, int )
*
*    PURPOSE:  Updates the list view to show only the houses for sale
*              in the currently selected city.
*
****************************************************************************/
VOID UpdateListView( HWND hwndLV, int iSelected )
{
    int count, index;

    // Remove the previous items.
    LV_RemoveAllItems(hwndLV);

    // Loop through the house listings.
    for (index = 0, count = 0; count < g_Listing.NumHouses; count++)
    {
	// If the house is listed for the new city...
	if (strcmp(rgHouses[count].szCity, rgCities[iSelected].szCity) == 0)
	{
	    // Add the house to the list view control.
	    if (!LV_AddItem(hwndLV, index, &rgHouses[count]))
		MessageBox(NULL, "LV_AddItem failed!", NULL, MB_OK);
	    index++;
	}
    }
}

/****************************************************************************
*
*    FUNCTION: SaveToFile( HWND )
*
*    PURPOSE:  Saves the current buffer to the current file.
*
*    COMMENTS:
*
*        This function will save the current text buffer into the file
*        specified from the GetSaveFileName() common dialog function.
*
*    RETURN VALUES:
*        TRUE - The file was saved successfully.
*        FALSE - The buffer was not saved to a file.
*
****************************************************************************/
BOOL SaveToFile( HWND hWnd )
{
   HANDLE hFile;
   DWORD dwOpen;
   DWORD dwBytesWritten;
   char buf[MAX_PATH];
   DWORD dwFileSize;

   dwFileSize = GetDataBufferAndSize();
   if (dwFileSize == 0)
   {
	MessageBox(NULL,"GetDataBufferAndSize failed!", NULL, MB_OK);
	return FALSE;
   }

   dwOpen = CREATE_ALWAYS;

   // open the file
   if ((hFile = CreateFile((LPCTSTR)OpenFileName.lpstrFile,
			GENERIC_WRITE,
			FILE_SHARE_WRITE,
			NULL,
			dwOpen,
			FILE_ATTRIBUTE_NORMAL,
			(HANDLE)NULL)) == (HANDLE)-1)

   {                      
      sprintf( buf, "Could not create file %s", OpenFileName.lpstrFile );
      MessageBox( hWnd, buf, NULL, MB_OK );
      return FALSE;
   }

    
   // write it's contents into a file
   if (WriteFile( hFile, (LPCVOID)lpBufPtr, dwFileSize, 
		     &dwBytesWritten, NULL) == FALSE)
   {
      MessageBox( hWnd, "Error writing file.", NULL, MB_OK );
      return FALSE;
   }

   // close the file
   CloseHandle(hFile);

   // free up the file buffer
   GlobalFree(lpBufPtr);

   return TRUE;
}


/****************************************************************************
*
*    FUNCTION: GetDataBufferAndSize()
*
*    PURPOSE:  Saves the current listing info to a buffer.
*
*    COMMENTS:
*
*        The file is an editable ASCII file and set up as follows:
*           - Number of cities
*           - A string representing each city for # of cities specified above
*           - Number of houses
*           - House information for each house. One line per house.
*             The fields are separated by commas and are in the following
*             order:
*                   Address
*                   City
*                   Price
*                   Bedrooms
*                   Bathrooms
*
*    RETURN VALUES:
*        TRUE - The file was parsed successfully.
*        FALSE - The parsing failed.
*
****************************************************************************/
DWORD GetDataBufferAndSize (VOID)
{
    char szTemp[MAX_PATH];
    int count;
    DWORD dwFileSize;

    // calculate the approximate buffer size needed to save the file
    dwFileSize = (g_Listing.NumCities * MAX_CITY) + (g_Listing.NumHouses * MAX_ADDRESS) +
	(g_Listing.NumHouses * MAX_CITY) + (g_Listing.NumHouses * (MAX_PRICE + 2) +
	 (g_Listing.NumHouses * MAX_CITY) + (g_Listing.NumHouses * MAX_CITY));

    lpBufPtr = (char *)GlobalAlloc( GMEM_FIXED, dwFileSize );
    if (lpBufPtr == NULL)
    {
	MessageBox( NULL, "GlobalAlloc failed!", NULL, MB_OK);
	return 0;
    }

    // copy over the number of cities
    wsprintf(lpBufPtr, "%d\n",g_Listing.NumCities);

    // copy a city for each line
    for (count= 0; count < g_Listing.NumCities; count++)
    {
	wsprintf(szTemp, "%s\n", rgCities[count].szCity);
	lstrcat(lpBufPtr, szTemp);
    }

    wsprintf(szTemp, "%d\n", g_Listing.NumHouses);
    lstrcat(lpBufPtr, szTemp);

    // copy house information for each line
    for (count= 0; count < g_Listing.NumHouses; count++)
    {
	wsprintf(szTemp, "%s,%s,%d,%d,%d,%s,%s\n", rgHouses[count].szAddress,
	    rgHouses[count].szCity,rgHouses[count].iPrice,
	    rgHouses[count].iBeds,rgHouses[count].iBaths,
	    rgHouses[count].szAgent,rgHouses[count].szNumber);
	lstrcat(lpBufPtr, szTemp);
    }

    dwFileSize = lstrlen(lpBufPtr);

    return (dwFileSize);
}

/****************************************************************************
*
*    FUNCTION: SaveAs(HWND)
*
*    PURPOSE:  Invokes the common dialog function to save the current
*              buffer to a file.
*    COMMENTS:
*
*        This function initializes the OPENFILENAME structure.
*        It then calls the GetSaveFileName() common dialog function.
*
*    RETURN VALUES:
*        TRUE - The file was saved successfully.
*        FALSE - The buffer was not saved to a file.
*
****************************************************************************/
BOOL SaveAs( HWND hWnd )
{

   lstrcpy( szFile, "");
   lstrcpy( szFileTitle, "");

   OpenFileName.lStructSize       = sizeof(OPENFILENAME);
   OpenFileName.hwndOwner         = hWnd;
   OpenFileName.hInstance         = (HANDLE) g_Listing.hInst;
   OpenFileName.lpstrFilter       = szFilter;
   OpenFileName.lpstrCustomFilter = (LPTSTR) NULL;
   OpenFileName.nMaxCustFilter    = 0L;
   OpenFileName.nFilterIndex      = 1L;
   OpenFileName.lpstrFile         = szFile;
   OpenFileName.nMaxFile          = sizeof(szFile);
   OpenFileName.lpstrFileTitle    = szFileTitle;
   OpenFileName.nMaxFileTitle     = sizeof(szFileTitle);
   OpenFileName.lpstrInitialDir   = NULL;
   OpenFileName.lpstrTitle        = "Save File As";
   OpenFileName.nFileOffset       = 0;
   OpenFileName.nFileExtension    = 0;
   OpenFileName.lpstrDefExt       = "txt";
   OpenFileName.lCustData         = 0;
   OpenFileName.Flags             = 0L;
   OpenFileName.lpfnHook          = (LPOFNHOOKPROC)(FARPROC)NULL;
   OpenFileName.lpTemplateName    = (LPTSTR)NULL;

   if ( GetSaveFileName( &OpenFileName ))
	return(SaveToFile( hWnd ));
   else
   {
	ProcessCDError(CommDlgExtendedError(), hWnd );
	return FALSE;
   }

   return (FALSE);
}

/****************************************************************************
*
*    FUNCTION: AddOneCity(char *)
*
*    PURPOSE:  Adds a city and updates the structures
*
****************************************************************************/
VOID AddOneCity( char * szCity)
{
    // copy the city name
    lstrcpy(rgCities[g_Listing.NumCities].szCity, szCity);

    // initialize the number of houses to zero
    rgCities[g_Listing.NumCities].NumHouses = 0;

    // Add the city to the tree view listing
    rgCities[g_Listing.NumCities].hItem = TV_AddOneItem(szCity, g_Listing.hWndTreeView,
	g_Listing.NumCities);

    // update the global count of cities
    g_Listing.NumCities++;

}


/****************************************************************************
*
*    FUNCTION: AddCity(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for the "Add City" dialog box
*
****************************************************************************/

BOOL APIENTRY AddCity(
	HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
    char szCity[MAX_CITY];

	switch (message)
    {
		case WM_INITDIALOG:
			return (TRUE);

		case WM_COMMAND:              
			if (LOWORD(wParam) == IDOK)
			{
		// get the text for the city
		GetDlgItemText( hDlg, IDE_CITY, szCity, MAX_CITY);

		// add the city to the array
		AddOneCity(szCity);

				EndDialog(hDlg, TRUE);
				return (TRUE);
			}
	    else if (LOWORD(wParam) == IDCANCEL)
		EndDialog(hDlg, FALSE);
			break;
	}
	return (FALSE);   

}

/****************************************************************************
*
*    FUNCTION: AddOneHouse(char *)
*
*    PURPOSE:  Adds a house and updates the structures
*
****************************************************************************/
VOID AddOneHouse( char *szAddress, char *szCity, int iPrice, int iBeds,
    int iBaths)
{
    int index;

    // copy the address
    lstrcpy(rgHouses[g_Listing.NumHouses].szAddress, szAddress);

    // copy the city name
    lstrcpy(rgHouses[g_Listing.NumHouses].szCity, szCity);

    // initialize the price, bedrooms and bathrooms
    rgHouses[g_Listing.NumHouses].iPrice = iPrice;
    rgHouses[g_Listing.NumHouses].iBeds = iBeds;
    rgHouses[g_Listing.NumHouses].iBaths = iBaths;

    // add the house to the list view
    LV_AddItem(g_Listing.hWndListView, g_Listing.NumHouses,
	&rgHouses[g_Listing.NumHouses]);


    // update the global count of houses
    g_Listing.NumHouses++;

    // find the city for the house in the CITY struct and update the number
    // of houses for that city
    for (index =0 ; index < g_Listing.NumCities; index++)
	if (lstrcmp(szCity, rgCities[index].szCity) == 0)
	    break;

    rgCities[index].NumHouses++;

}

/****************************************************************************
*
*    FUNCTION: AddHouse(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "AddHouse" dialog box
*
****************************************************************************/

BOOL APIENTRY AddHouse(
	HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
    char szAddress[MAX_ADDRESS];
    char szCity[MAX_CITY];
    char szTemp[MAX_PRICE];
    int iBeds;
    int iBaths;
    BOOL bErr;
    int index;

	switch (message)
	{
		case WM_INITDIALOG:
	    // Fill in the listbox with the cities 
	    for (index = 0; index < g_Listing.NumCities; index++)
		SendDlgItemMessage( hDlg, IDE_CITY, CB_INSERTSTRING, (WPARAM)(-1),
		    (LPARAM)(rgCities[index].szCity));
			return (TRUE);

		case WM_COMMAND:              
			if (LOWORD(wParam) == IDOK)
			{
		GetDlgItemText( hDlg, IDE_ADDRESS, szAddress, MAX_ADDRESS);
		GetDlgItemText( hDlg, IDE_CITY, szCity, MAX_CITY);
		GetDlgItemText( hDlg, IDE_PRICE, szTemp, MAX_PRICE);
		iBeds = GetDlgItemInt(hDlg, IDE_BEDS, &bErr, TRUE);
		iBaths = GetDlgItemInt(hDlg, IDE_BATHS, &bErr, TRUE);

		AddOneHouse(szAddress, szCity, atoi(szTemp), iBeds, iBaths);
				EndDialog(hDlg, TRUE);
				return (TRUE);
			}
	    else if (LOWORD(wParam) == IDCANCEL)
		EndDialog(hDlg, FALSE);
			break;
	}
	return (FALSE);   

}

/****************************************************************************
*
*    FUNCTION: RemoveOneHouse(int)
*
*    PURPOSE:  Removes a house from the listing book
*
****************************************************************************/
VOID RemoveOneHouse( int index )
{
	int count, idx;		// general purpose counters

    // find the city and decrement its house counter
    rgCities[g_Listing.iSelected].NumHouses--;

	// find the house in the list
	for (count=0, idx=0; count < g_Listing.NumHouses; count++)
	{
		if (lstrcmp( rgCities[g_Listing.iSelected].szCity, rgHouses[count].szCity) == 0)
		{
			if (idx == index)
			{
				// found it -- change .szCity to "deleted"
				lstrcpy(rgHouses[count].szCity, "deleted");
				break;
			}
			else
				idx++;
		}
	}

    // remove the house from the list view
    LV_RemoveOneItem( g_Listing.hWndListView, index);

}

/****************************************************************************
*
*    FUNCTION: RemoveHouse(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "Remove House" dialog box
*
****************************************************************************/

BOOL APIENTRY RemoveHouse(
	HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
    int index;

	switch (message)
	{
		case WM_INITDIALOG:
			// Fill the dialog with only houses listed for the current city
	    	for (index = 0; index < g_Listing.NumHouses; index++)
			{
				if (lstrcmp( rgHouses[index].szCity, rgCities[g_Listing.iSelected].szCity) == 0)
					SendDlgItemMessage( hDlg, IDL_HOUSES, LB_INSERTSTRING,
		    			(WPARAM)(-1),
		    			(LPARAM)(rgHouses[index].szAddress));
			}
			return (TRUE);

		case WM_COMMAND:              
			if (LOWORD(wParam) == IDOK)
			{
				// get the index of the selected house
				index = SendDlgItemMessage( hDlg, IDL_HOUSES, LB_GETCURSEL, 0, 0);
				RemoveOneHouse(index );
				EndDialog(hDlg, TRUE);
				return (TRUE);
			}
	    else if (LOWORD(wParam) == IDCANCEL)
		EndDialog(hDlg, FALSE);
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

/****************************************************************************
*
*    FUNCTION: ProcessCDError(DWORD)
*
*    PURPOSE:  Processes errors from the common dialog functions.
*
*    COMMENTS:
*
*        This function is called whenever a common dialog function
*        fails.  The CommonDialogExtendedError() value is passed to
*        the function which maps the error value to a string table.
*        The string is loaded and displayed for the user.
*
*    RETURN VALUES:
*        void.
*
****************************************************************************/
void ProcessCDError(DWORD dwErrorCode, HWND hWnd)
{
   WORD  wStringID;
   char  buf[MAX_PATH];

   switch(dwErrorCode)
      {
	 case CDERR_DIALOGFAILURE:   wStringID=IDS_DIALOGFAILURE;   break;
	 case CDERR_STRUCTSIZE:      wStringID=IDS_STRUCTSIZE;      break;
	 case CDERR_INITIALIZATION:  wStringID=IDS_INITIALIZATION;  break;
	 case CDERR_NOTEMPLATE:      wStringID=IDS_NOTEMPLATE;      break;
	 case CDERR_NOHINSTANCE:     wStringID=IDS_NOHINSTANCE;     break;
	 case CDERR_LOADSTRFAILURE:  wStringID=IDS_LOADSTRFAILURE;  break;
	 case CDERR_FINDRESFAILURE:  wStringID=IDS_FINDRESFAILURE;  break;
	 case CDERR_LOADRESFAILURE:  wStringID=IDS_LOADRESFAILURE;  break;
	 case CDERR_LOCKRESFAILURE:  wStringID=IDS_LOCKRESFAILURE;  break;
	 case CDERR_MEMALLOCFAILURE: wStringID=IDS_MEMALLOCFAILURE; break;
	 case CDERR_MEMLOCKFAILURE:  wStringID=IDS_MEMLOCKFAILURE;  break;
	 case CDERR_NOHOOK:          wStringID=IDS_NOHOOK;          break;
	 case PDERR_SETUPFAILURE:    wStringID=IDS_SETUPFAILURE;    break;
	 case PDERR_PARSEFAILURE:    wStringID=IDS_PARSEFAILURE;    break;
	 case PDERR_RETDEFFAILURE:   wStringID=IDS_RETDEFFAILURE;   break;
	 case PDERR_LOADDRVFAILURE:  wStringID=IDS_LOADDRVFAILURE;  break;
	 case PDERR_GETDEVMODEFAIL:  wStringID=IDS_GETDEVMODEFAIL;  break;
	 case PDERR_INITFAILURE:     wStringID=IDS_INITFAILURE;     break;
	 case PDERR_NODEVICES:       wStringID=IDS_NODEVICES;       break;
	 case PDERR_NODEFAULTPRN:    wStringID=IDS_NODEFAULTPRN;    break;
	 case PDERR_DNDMMISMATCH:    wStringID=IDS_DNDMMISMATCH;    break;
	 case PDERR_CREATEICFAILURE: wStringID=IDS_CREATEICFAILURE; break;
	 case PDERR_PRINTERNOTFOUND: wStringID=IDS_PRINTERNOTFOUND; break;
	 case CFERR_NOFONTS:         wStringID=IDS_NOFONTS;         break;
	 case FNERR_SUBCLASSFAILURE: wStringID=IDS_SUBCLASSFAILURE; break;
	 case FNERR_INVALIDFILENAME: wStringID=IDS_INVALIDFILENAME; break;
	 case FNERR_BUFFERTOOSMALL:  wStringID=IDS_BUFFERTOOSMALL;  break;

	 case 0:   //User may have hit CANCEL or we got a *very* random error
	    return;

	 default:
	    wStringID=IDS_UNKNOWNERROR;
      }

   LoadString(NULL, wStringID, buf, sizeof(buf));
   MessageBox(hWnd, buf, NULL, MB_OK);
   return;
}

/****************************************************************************
*
*    FUNCTION: CreatePropertySheet(HWND)
*
*    PURPOSE:  Creates a property sheet for listing properties 
*																	
*    COMMENTS:
*
*        This function creates a property sheet for each house.
*
*    RETURN VALUES:
*        void.
*
****************************************************************************/
//
//
int CreatePropertySheet(HWND hwndOwner)
{
    PROPSHEETPAGE psp[2];
    PROPSHEETHEADER psh;

    psp[0].dwSize = sizeof(PROPSHEETPAGE);
    psp[0].dwFlags = PSP_USETITLE;
    psp[0].hInstance = g_Listing.hInst;
    psp[0].pszTemplate = MAKEINTRESOURCE(IDD_HOUSEINFO);
    psp[0].pszIcon = NULL;
    psp[0].pfnDlgProc = HouseInfoDialog;
    psp[0].pszTitle = MAKEINTRESOURCE(IDS_HOUSEINFO);
    psp[0].lParam = 0;

    psp[1].dwSize = sizeof(PROPSHEETPAGE);
    psp[1].dwFlags = PSP_USETITLE;
    psp[1].hInstance = g_Listing.hInst;
    psp[1].pszTemplate = MAKEINTRESOURCE(IDD_AGENTINFO);
    psp[1].pszIcon = NULL;
    psp[1].pfnDlgProc = AgentInfoDialog;
    psp[1].pszTitle = MAKEINTRESOURCE(IDS_AGENTINFO);
    psp[1].lParam = 0;

    psh.dwSize = sizeof(PROPSHEETHEADER);
    psh.dwFlags = PSH_PROPSHEETPAGE;
    psh.hwndParent = hwndOwner;
    psh.hInstance = g_Listing.hInst;
    psh.pszIcon = NULL;
    psh.pszCaption = (LPSTR) "House Listing Properties";
    psh.nPages = sizeof(psp) / sizeof(PROPSHEETPAGE);
    psh.ppsp = (LPCPROPSHEETPAGE) &psp;

    return (PropertySheet(&psh));
}

/****************************************************************************
*
*    FUNCTION: HouseInfoDialog(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "HouseInfoDialog" dialog box
*
****************************************************************************/

BOOL APIENTRY HouseInfoDialog(
	HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
    char szTemp[MAX_ADDRESS];
	static char szAddSave[MAX_ADDRESS];
	static char szCitySave[MAX_CITY];
	static int iPrice, iBeds, iBaths;
    BOOL bErr;
	int index, count;
	LV_ITEM lvItem;

	switch (message)
	{
		case WM_INITDIALOG:	
			// Fill in the list box with the cities.
	    	for (index = 0; index < g_Listing.NumCities; index++)
				SendDlgItemMessage( hDlg, IDE_CITY, CB_INSERTSTRING, (WPARAM)(-1),
		    		(LPARAM)(rgCities[index].szCity));

 			// Get the index to the selected list view item.
   			index = ListView_GetNextItem(g_Listing.hWndListView,
   				 -1, MAKELPARAM(LVNI_SELECTED, 0));

			// Get the house address.
			lvItem.iItem = index;
			lvItem.iSubItem = 0;
			lvItem.mask = LVIF_TEXT;
			lvItem.cchTextMax = sizeof(szAddSave);
			lvItem.pszText = szAddSave;
			ListView_GetItem(g_Listing.hWndListView,&lvItem);

			// Find the house in the list.
			for (count=0; count < g_Listing.NumHouses; count++)
			{
				if (strcmp(lvItem.pszText, rgHouses[count].szAddress) == 0)
					break;
			}
			g_Listing.iSelHouse = count;

			// save the original house property values
			lstrcpy(szAddSave, rgHouses[g_Listing.iSelHouse].szAddress);
			lstrcpy(szCitySave, rgHouses[g_Listing.iSelHouse].szCity);
			iPrice = rgHouses[g_Listing.iSelHouse].iPrice;
			iBeds = rgHouses[g_Listing.iSelHouse].iBeds;
			iBaths = rgHouses[g_Listing.iSelHouse].iBaths;
			return (TRUE);

		case WM_NOTIFY:
    		switch (((NMHDR FAR *) lParam)->code) 
    		{
				case PSN_SETACTIVE:
					// initialize the controls
					SetDlgItemText( hDlg, IDE_ADDRESS, rgHouses[g_Listing.iSelHouse].szAddress);
					SendDlgItemMessage( hDlg, IDE_CITY, CB_SELECTSTRING, 0, (LPARAM)rgHouses[g_Listing.iSelHouse].szCity);
					itoa(rgHouses[g_Listing.iSelHouse].iPrice, szTemp, 10);
					SetDlgItemText( hDlg, IDE_PRICE, szTemp);
					SetDlgItemInt(hDlg, IDE_BEDS, rgHouses[g_Listing.iSelHouse].iBeds, FALSE);
					SetDlgItemInt(hDlg, IDE_BATHS, rgHouses[g_Listing.iSelHouse].iBaths, FALSE);
					break;

				case PSN_APPLY:
				case PSN_KILLACTIVE:
					GetDlgItemText( hDlg, IDE_ADDRESS, rgHouses[g_Listing.iSelHouse].szAddress, MAX_ADDRESS);
					GetDlgItemText( hDlg, IDE_CITY, rgHouses[g_Listing.iSelHouse].szCity, MAX_CITY);
					GetDlgItemText( hDlg, IDE_PRICE, szTemp, MAX_PRICE);
					rgHouses[g_Listing.iSelHouse].iPrice = atoi(szTemp);
					rgHouses[g_Listing.iSelHouse].iBeds = GetDlgItemInt(hDlg, IDE_BEDS, &bErr, TRUE);
					rgHouses[g_Listing.iSelHouse].iBaths = GetDlgItemInt(hDlg, IDE_BATHS, &bErr, TRUE);
            		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
					return 1;
					break;

				case PSN_RESET:
					// rest to the original house property values
					lstrcpy(rgHouses[g_Listing.iSelHouse].szAddress, szAddSave);
					lstrcpy(rgHouses[g_Listing.iSelHouse].szCity, szCitySave);
					rgHouses[g_Listing.iSelHouse].iPrice = iPrice;
					rgHouses[g_Listing.iSelHouse].iBeds = iBeds;
					rgHouses[g_Listing.iSelHouse].iBaths = iBaths;
					break;
    	}
	}
	return (FALSE);   

}

/****************************************************************************
*
*    FUNCTION: AgentInfoDialog(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "AgentInfoDialog" dialog box
*
****************************************************************************/

BOOL APIENTRY AgentInfoDialog(
	HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{			
	static char szAgent[MAX_CITY];
	static char szNumber[MAX_CITY];

	switch (message)
	{

		case WM_INITDIALOG:	
			// save off orginal agent information
			lstrcpy(szAgent, rgHouses[g_Listing.iSelHouse].szAgent);
			lstrcpy(szNumber, rgHouses[g_Listing.iSelHouse].szNumber);
			return (TRUE);

		case WM_NOTIFY:
    		switch (((NMHDR FAR *) lParam)->code) 
    		{
				case PSN_SETACTIVE:
					// initialize the controls
					SetDlgItemText( hDlg, IDE_AGENTNAME, rgHouses[g_Listing.iSelHouse].szAgent);
					SetDlgItemText( hDlg, IDE_AGENTNUM, rgHouses[g_Listing.iSelHouse].szNumber);
					break;

				case PSN_APPLY:
				case PSN_KILLACTIVE:
			 		GetDlgItemText( hDlg, IDE_AGENTNAME, rgHouses[g_Listing.iSelHouse].szAgent, MAX_CITY);
					GetDlgItemText( hDlg, IDE_AGENTNUM, rgHouses[g_Listing.iSelHouse].szNumber, MAX_CITY);
           			SetWindowLong(hDlg, DWL_MSGRESULT, FALSE);
					return 1;
					break;

				case PSN_RESET:
					// rest to the original agent values
					lstrcpy(rgHouses[g_Listing.iSelHouse].szAgent, szAgent);
					lstrcpy(rgHouses[g_Listing.iSelHouse].szNumber, szNumber);
					break;
    	}
	}
	return (FALSE);   

}

