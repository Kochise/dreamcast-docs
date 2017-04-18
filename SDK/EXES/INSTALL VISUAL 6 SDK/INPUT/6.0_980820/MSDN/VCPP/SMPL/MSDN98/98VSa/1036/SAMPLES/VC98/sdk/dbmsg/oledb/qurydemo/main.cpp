//-----------------------------------------------------------------------------
// Microsoft OLE DB QURYDEMO Sample
// Copyright (C) 1995-1998 Microsoft Corporation
//
// @doc
//
// @module MAIN.CPP
//
//-----------------------------------------------------------------------------------
/*
	PROGRAM: QURYDEMO
	========

	PURPOSE:
	========	
	demonstrates a simple MDI application that allows a user to
	simultaneously connect to multiple hetrogeneous databases
	and perform SQL queries to get results.

	FUNCTIONS:
	==========
	WinMain() - main routine
	MainWndProc() - processes Main Application Window messages
	MDIChildProc() - processes MDI child window messages
	ToolbarProc() - processes tool bar messages
	StatusbarProc() - processes Status bar messages
	ConnectDlgProc() - processes Connection Dialog box messages
	DisconnectDlgProc() - processes Disconnect Dialog box messages
	AboutDlgProc() - processes messages for About dialog box
	MDIChildDlgProc() - process messages for dummy child dialog box in MDI window
	DrawBitmap() - draws bitmaps for toolbuttons

	COMMENTS:
	=========
	Created by Microsoft Corporation.
*/

#define STRICT

#include <stdio.h>
#include <string.h>
#include <time.h>

#include <windows.h>
#include <windowsx.h>

#ifdef CTL3D
#include "ctl3d.h"
#endif

#include "oledb.h"
#include "oledberr.h"

#include "qurydemo.h"  

// Globals
HWND		hWndFrame;      	// Main Frame Window handle
HWND		hWndCrsrList;   	// hdbc(s) combobox on the tool bar
HWND		hWndStmtList;   	// hstmt(s) combobox on the tool bar
HWND		hWndMDIClient;  	// MDI Client window handle
HWND		hWndActiveChild;	// Current active MDI Child window
HINSTANCE	hAppInstance;   	// Application instance

int			iTimex;         	// Time box (on the status bar) width
int			iDatex;         	// Date box (on the status bar) width
HWND		hWndToolbar;    	// Toolbar window handle
HWND		hWndStatusbar;  	// status bar handle
WORD		wStatusText;    	// Status text state
RECT		rectStatusText; 	// Text box on the status bar

// Locals.
void FillPrompt(HWND hWnd);


/*
	FUNCTION: WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	COMMENTS: Application Entry Routine.
		  Register Classes. Create Main Window and MDI Child Window.
		  Process Main Message Loop.
*/
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG			msg;					//msg structure
	WNDCLASS	wc;						//class structure
    HICON		hMainIcon;				//App Icon
    HICON		hMDIChildIcon;			//MDI Child Icon
	HWND		hWndMDIChild;			//temp MDI Child Window Handle
	char		szBuffer[MAXBUFLEN+1];	//temp string buffer to check class name
	BOOL		bDialogMessage = FALSE;	//temp boolean to check dilogbox msgs
	HACCEL		hAccel;					//accelerator table handle

	hAppInstance = hInstance;

	// Check if application is already running, if
	// so make it active and bring it in focus
	if (hWndFrame = FindWindow(OLEDBFRAMECLASS, NULL))
	{
		hWndFrame = GetLastActivePopup(hWndFrame);
		if (IsIconic(hWndFrame))
			OpenIcon(hWndFrame);
		else
			BringWindowToTop(hWndFrame);
		ACTIVATEWINDOW(hWndFrame);
		return (FALSE);
	}

	// Initialize OLEDB Interface
	if (!InitEnvironment())
	{
		MessageBox(hWndFrame, INITERROR, EXECERROR, MB_OK|MB_ICONHAND);
		return (FALSE);
	}

	// Register window classes for the application - Main Window Class
	wc.style			= 0;
	wc.lpfnWndProc		= MainWndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hAppInstance;
	wc.hIcon			= hMainIcon = LoadIcon(hAppInstance, APPICON);
	wc.hCursor			= LoadCursor((HINSTANCE)NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)(COLOR_APPWORKSPACE+1);
	wc.lpszMenuName		= QURYDEMOMENU;
	wc.lpszClassName	= OLEDBFRAMECLASS;

	if (!RegisterClass(&wc))
	{
		MessageBox(hWndFrame, CLASSERROR, EXECERROR, MB_OK|MB_ICONHAND|MB_TASKMODAL);
		return (FALSE);
	}
        
	// register Toolbar Class
	wc.hIcon			= (HICON)NULL;
	wc.lpszMenuName		=  NULL;
	wc.lpfnWndProc		= ToolbarProc;
	wc.lpszClassName	= OLEDBTOOLCLASS;

	if (!RegisterClass(&wc))
	{
		MessageBox(hWndFrame, CLASSERROR, EXECERROR, MB_OK|MB_ICONHAND|MB_TASKMODAL);
		return (FALSE);
	}
        
	// register Statusbar Class
	wc.lpfnWndProc		= StatusbarProc;
	wc.lpszClassName	= OLEDBSTATUSCLASS;

	if (!RegisterClass(&wc))
	{
		MessageBox(hWndFrame, CLASSERROR, EXECERROR, MB_OK|MB_ICONHAND|MB_TASKMODAL);
		return (FALSE);
	}

	// register MDI Child Window Class
	wc.hIcon 			= hMDIChildIcon = LoadIcon(hAppInstance, QUERYWINDOWICON);
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wc.cbWndExtra		= CBWNDEXTRA;
	wc.lpszClassName	= OLEDBMDICLASS;
	wc.lpfnWndProc		= MDIChildProc;

	if (!RegisterClass(&wc))
	{
		MessageBox(hWndFrame, CLASSERROR, EXECERROR, MB_OK|MB_ICONHAND|MB_TASKMODAL);
		return (FALSE);
	}

	// create Main window and the MDI Client window
	if (!(hWndFrame = CreateWindow(OLEDBFRAMECLASS, APPTITLE, WS_OVERLAPPEDWINDOW, 
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				(HWND)NULL, (HMENU)NULL, hAppInstance, NULL)))
	{
		MessageBox(hWndFrame, CREATEMAINERR, EXECERROR, MB_OK|MB_ICONHAND|MB_TASKMODAL); 
		return (FALSE);
	}

	ShowWindow(hWndFrame, nCmdShow);
	UpdateWindow(hWndFrame);

#ifdef CTL3D
	// register 3D controls
	Ctl3dRegister(hAppInstance);
	Ctl3dAutoSubclass(hAppInstance);
#endif

	// load accelerators
	hAccel = LoadAccelerators(hAppInstance, APPACCELERATOR);
	
	// acquire and dispatch messages until a WM_QUIT message is received
	while (GetMessage(&msg, (HWND)NULL, 0, 0))
	{           
		
		// check for App accelerators
		if (TranslateAccelerator(hWndFrame, hAccel, &msg))
			continue;
			
		// check for MDI accelerators
		if (TranslateMDISysAccel(hWndMDIClient, &msg))
			continue;
                                            
        // each MDI Child has a modeless dialog in its client area
        // to provide tab controls. Check for Modeless Dialog msgs.
		for (hWndMDIChild = GetWindow(hWndMDIClient, GW_CHILD); hWndMDIChild; hWndMDIChild = GetWindow(hWndMDIChild, GW_HWNDNEXT))
		{
			GetClassName(hWndMDIChild, szBuffer, MAXBUFLEN);
			if (strcmp(szBuffer, OLEDBMDICLASS))
				continue;
			if (IsDialogMessage((HWND)GetWindowLong(hWndMDIChild, GWLAPP_HDLG), &msg))
			{
				bDialogMessage = TRUE;
				break;
			}
		}
		
		if (bDialogMessage)
		{
			bDialogMessage = FALSE;
			continue;
        }
                
        // if the message does not need special processing, dispatch it
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

#ifdef CTL3D
	// unregister 3D controls
	Ctl3dUnregister(hAppInstance);
#endif

	// Free memory used by OLEDB interface
	FreeEnvironment();

	// free Icon resources
	if (hMainIcon)
		DestroyIcon(hMainIcon);
	
	if (hMDIChildIcon)
		DestroyIcon(hMDIChildIcon);

	return (msg.wParam);
}

/*
	FUNCTION: MainWndProc(HWND hWnd, UINT 	message, WPARAM wParam, LPARAM lParam)
	COMMENTS: Windows Callback procedure to handle Window messages.
	          Menu Commands and System Command messages are handled by
	          this main window.
*/
long CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	static int	iToolY;         //remember Toolbar height for resize
	static int	iStatusY;       //remember Statusbar height for resize

		case WM_CREATE:
        {
			CLIENTCREATESTRUCT	ccs;		//MDIclient window structure
			HDC					hDC;		//Device Context handle
			SIZE				sizeBar;	//Size of a text bar
			RECT				rectCombo;  //Size of combo box

			// Create child windows
                //1. combobox to display connections - DSN, SESSION
                //2. combobox to display HSTMT on current SESSION
                //3. Toolbar to put toolbuttons
                //4. Statusbat to display current action, date and time
                //5. MDI Client Window to process MDI children
                
			hWndCrsrList = CreateWindow(COMBOBOXCLASS, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS |
				WS_VSCROLL | CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL, 5, 2, 180, 150, hWnd,
				(HMENU)IDW_CRSRLIST, hAppInstance, NULL);

			hWndStmtList = CreateWindow(COMBOBOXCLASS, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS |
				WS_VSCROLL | CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL, 190, 2, 150, 150, hWnd,
				(HMENU)IDW_COMMANDLIST, hAppInstance, NULL);

			hWndToolbar = CreateWindow(OLEDBTOOLCLASS, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
				0, 0, 0, 0, hWnd, (HMENU)IDW_TOOLBAR, hAppInstance, NULL);

			hWndStatusbar = CreateWindow(OLEDBSTATUSCLASS, NULL, WS_CHILD | WS_VISIBLE |
				WS_CLIPSIBLINGS, 0, 0, 0, 0, hWnd, (HMENU)IDW_STATUSBAR, hAppInstance, NULL);

			ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), WINDOWMENUPLACE);
			ccs.idFirstChild = IDM_MDICHILD;

			hWndMDIClient = CreateWindow(MDICLIENTCLASS, NULL, WS_CHILD | WS_CLIPSIBLINGS |
				WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE, 0, 0, 0, 0, hWnd,
				(HMENU)IDW_MDICLIENT, hAppInstance, (LPSTR)&ccs);

			// check to see if any of the above window creation failed
			if (!hWndCrsrList || !hWndStmtList || !hWndToolbar || !hWndStatusbar || !hWndMDIClient)
			{
				MessageBox(hWnd, CREATEMAINERR, EXECERROR, MB_OK|MB_ICONHAND|MB_TASKMODAL); 
				PostMessage(hWnd, WM_CLOSE, 0, 0);
				break;
			}

			// calculate proper text height for tool and status bars
			GetWindowRect(hWndStmtList, &rectCombo);
			iToolY = rectCombo.bottom - rectCombo.top + TOOLBARMARGINY;

			if (hDC = GetDC(hWndStatusbar))
			{
				GetTextExtentPoint(hDC, ALPHABETS, strlen(ALPHABETS), &sizeBar);
				ReleaseDC(hWndStatusbar, hDC);
				iStatusY = sizeBar.cy + STATUSBARMARGINY;
			}
			else
			{
				iStatusY = 0;
				DestroyWindow(hWndStatusbar);
			}
		
			break;
		}
		
		// Limit minimum size of the main window
		case WM_GETMINMAXINFO:
		
			((MINMAXINFO FAR*)lParam)->ptMinTrackSize.x = 
				max(MINWIDTH, rectStatusText.right-rectStatusText.left+iTimex+iDatex+14);
			((MINMAXINFO FAR*)lParam)->ptMinTrackSize.y = MINHEIGHT;
			break;
		
		// Resize children
		case WM_SIZE:
        {
			WORD	wWidth = LOWORD(lParam);	//width of rectangle
			WORD	wHeight = HIWORD(lParam);	//height of rectangle

			MoveWindow(hWndToolbar, 0, 0, wWidth, iToolY, TRUE);
			MoveWindow(hWndStatusbar, 0, wHeight-iStatusY, wWidth, iStatusY, TRUE);
			InvalidateRect(hWndStatusbar, NULL, TRUE);
			MoveWindow(hWndMDIClient, 0, iToolY, wWidth, wHeight-iStatusY-iToolY, TRUE);
			break;
        }
		
#ifdef CTL3D
		// Inform 3D controls of color change                
		case WM_SYSCOLORCHANGE:

			Ctl3dColorChange();
			break;
#endif		
		// Close comboboxes if dropped down
		case WM_SYSCOMMAND:

			SendMessage(hWndCrsrList, CB_SHOWDROPDOWN, (WPARAM)FALSE, 0);
			SendMessage(hWndStmtList, CB_SHOWDROPDOWN, (WPARAM)FALSE, 0);
			return (DefFrameProc(hWnd, hWndMDIClient, message, wParam, lParam));
		
		// Initialize popup menus
		case WM_INITMENUPOPUP:
        {
	        int	iMenuId;		//Menu ID being processed
			int	nItems;         //# of menu items
			int	nPos;           //Menu Position

	        // Ignore the msg if it is for a system menu
			if (HIWORD(lParam))
				break;
			
			// Go through the menu items for current popup menu
			// and enable/disable menu item, if required
			nItems = GetMenuItemCount((HMENU)wParam);
			for (nPos = 0; nPos < nItems; nPos++)
				switch (iMenuId = GetMenuItemID((HMENU)wParam, nPos))
				{
					case IDM_DISCONNECT:
					case IDM_NEW:
			
						EnableMenuItem( (HMENU)wParam, iMenuId, MF_BYCOMMAND|
										((SendMessage(hWndCrsrList, CB_GETCOUNT, 0, 0) > 0)?
										MF_ENABLED:MF_GRAYED) );
						break;
			
					case IDM_QUERY:
					case IDM_TILE:
					case IDM_CASCADE:
					case IDM_ICONS:
					case IDM_CLOSEALL:

					case IDM_ASSERTIONS:
					case IDM_CATALOGS:
					case IDM_CHARACTER_SETS:
					case IDM_CHECK_CONSTRAINTS:
					case IDM_COLLATIONS:
					case IDM_COLUMN_DOMAIN_USAGE:
					case IDM_COLUMN_PRIVILEGES:
					case IDM_COLUMNS:
					case IDM_CONSTRAINT_COLUMN_USAGE:
					case IDM_CONSTRAINT_TABLE_USAGE:
					case IDM_FOREIGN_KEYS:
					case IDM_INDEXES:
					case IDM_KEY_COLUMN_USAGE:
					case IDM_PRIMARY_KEYS:
					case IDM_PROCEDURE_COLUMNS:
					case IDM_PROCEDURE_PARAMETERS:
					case IDM_PROCEDURES:
					case IDM_PROVIDER_TYPES:
					case IDM_REFERENTIAL_CONSTRAINTS:
					case IDM_SCHEMATA:
					case IDM_SQL_LANGUAGES:
					case IDM_STATISTICS:
					case IDM_TABLE_CONSTRAINTS:
					case IDM_TABLE_PRIVILEGES:
					case IDM_TABLES:
					case IDM_TRANSLATIONS:
					case IDM_USAGE_PRIVILEGES:
					case IDM_VIEW_COLUMN_USAGE:
					case IDM_VIEW_TABLE_USAGE:
					case IDM_VIEWS:

						EnableMenuItem( (HMENU)wParam, iMenuId, MF_BYCOMMAND|
										(GetWindow(hWndMDIClient, GW_CHILD)?
										MF_ENABLED:MF_GRAYED) );
						break;
			
					default:
						break;
				}
			break;
		}
		
		// Update status bar to reflect menu selection
		case WM_MENUSELECT:
		{
            int		iMenuFlag;				 //Check menu type
            HMENU	hMenu;          		 //Menu Handle
            char	szMenuName[MAXBUFLEN+1]; //Menu Name 

            // store Menuitem ID as a state value for text display
			wStatusText = GET_WM_MENUSELECT_CMD(wParam, lParam);

			// process popup menus ie non menuitem selections
			iMenuFlag = GET_WM_MENUSELECT_FLAGS(wParam, lParam);

			// if the selected menu is a system popup menu
	        // else if the selected menu is a popup menu check menu names
	        // OR check if it is a control popup menu of maximized MDI Child window
	        if (wStatusText && (iMenuFlag & MF_SYSMENU) && (iMenuFlag & MF_POPUP))
				wStatusText = IDM_POPUPAPPSYS;
			else if (wStatusText && (iMenuFlag & MF_POPUP))
			{
				hMenu = (HMENU)wStatusText;
				GetMenuString(hMenu, 0, szMenuName, MAXBUFLEN, MF_BYPOSITION);
				if (!strcmp(szMenuName, MENUITEMCONNECT))
					wStatusText = IDM_POPUPLOGIN;
				else if (!strcmp(szMenuName, MENUITEMQUERY))
					wStatusText = IDM_POPUPQUERY;
				else if (!strcmp(szMenuName, MENUITEMTILE))
					wStatusText = IDM_POPUPSCHEMA;
				else if (!strcmp(szMenuName, MENUITEMTYPES))
					wStatusText = IDM_POPUPWINDOW;
				else if (!strcmp(szMenuName, MENUITEMAPPHELP))
					wStatusText = IDM_POPUPHELP;
				else if (GetMenuString(hMenu, SC_NEXTWINDOW, szMenuName, MAXBUFLEN, MF_BYCOMMAND)>0)
					wStatusText = IDM_POPUPMDISYS;
	            else
	                wStatusText = 0;
	        }

			// invalidate status bar for repaint
			InvalidateRect(hWndStatusbar, &rectStatusText, TRUE);
			break;
		}
		
		// Process menu commands
		case WM_COMMAND:

		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
			case IDM_INITIALIZE: // bring up connect dialog & do connect processing
				DialogBox(hAppInstance, INITDIALOG, hWnd, ConnectDlgProc);
				break;
                                                
			case IDM_DISCONNECT: // bringup disconnect dlg and do disconnects
				DialogBox(hAppInstance, DISCONNECTDIALOG, hWnd, DisconnectDlgProc);
				break;

			case IDM_QUERY: // process execute query request
			
				ExecuteQuery();
				break;

			case IDM_ASSERTIONS: // Execute DBSCHEMA_ASSERTIONS request
			
				GetSchemaRowset(DBSCHEMA_ASSERTIONS);
				break;

			case IDM_CATALOGS: // Execute DBSCHEMA_CATALOGS request
			
				GetSchemaRowset(DBSCHEMA_CATALOGS);
				break;

			case IDM_CHARACTER_SETS: // Execute DBSCHEMA_CHARACTER_SETS request
			
				GetSchemaRowset(DBSCHEMA_CHARACTER_SETS);
				break;

			case IDM_CHECK_CONSTRAINTS: // Execute DBSCHEMA_CHECK_CONSTRAINTS request
			
				GetSchemaRowset(DBSCHEMA_CHECK_CONSTRAINTS);
				break;

			case IDM_COLLATIONS: // Execute DBSCHEMA_COLLATIONS request
			
				GetSchemaRowset(DBSCHEMA_COLLATIONS);
				break;

			case IDM_COLUMN_DOMAIN_USAGE: // Execute DBSCHEMA_COLUMN_DOMAIN_USAGE request
			
				GetSchemaRowset(DBSCHEMA_COLUMN_DOMAIN_USAGE);
				break;

			case IDM_COLUMN_PRIVILEGES: // Execute DBSCHEMA_COLUMN_PRIVELEGES request
			
				GetSchemaRowset(DBSCHEMA_COLUMN_PRIVILEGES);
				break;

			case IDM_COLUMNS: // Execute DBSCHEMA_COLUMNS request
			
				GetSchemaRowset(DBSCHEMA_COLUMNS);
				break;

			case IDM_CONSTRAINT_COLUMN_USAGE: // Execute DBSCHEMA_CONSTRAINT_COLUMN_USAGE request
			
				GetSchemaRowset(DBSCHEMA_CONSTRAINT_COLUMN_USAGE);
				break;

			case IDM_CONSTRAINT_TABLE_USAGE: // Execute DBSCHEMA_CONSTRAINT_TABLE_USAGE request
			
				GetSchemaRowset(DBSCHEMA_CONSTRAINT_TABLE_USAGE);
				break;

			case IDM_FOREIGN_KEYS: // Execute DBSCHEMA_FOREIGN_KEYS request
			
				GetSchemaRowset(DBSCHEMA_FOREIGN_KEYS);
				break;

			case IDM_INDEXES: // Execute DBSCHEMA_INDEXES request
				
				GetSchemaRowset(DBSCHEMA_INDEXES);
				break;

			case IDM_KEY_COLUMN_USAGE: // Execute DBSCHEMA_KEY_COLUMN_USAGE request
				
				GetSchemaRowset(DBSCHEMA_KEY_COLUMN_USAGE);
				break;

			case IDM_PRIMARY_KEYS: // Execute DBSCHEMA_PRIMARY_KEYS request
			
				GetSchemaRowset(DBSCHEMA_PRIMARY_KEYS);
				break;

			case IDM_PROCEDURE_COLUMNS: // Execute DBSCHEMA_PROCEDURE_COLUMNS request
			
				GetSchemaRowset(DBSCHEMA_PROCEDURE_COLUMNS);
				break;

			case IDM_PROCEDURE_PARAMETERS: // Execute DBSCHEMA_PROCEDURE_PARAMETERS request
			
				GetSchemaRowset(DBSCHEMA_PROCEDURE_PARAMETERS);
				break;

			case IDM_PROCEDURES: // Execute DBSCHEMA_PROCEDURES request
			
				GetSchemaRowset(DBSCHEMA_PROCEDURES);
				break;

			case IDM_PROVIDER_TYPES: // Execute DBSCHEMA_TYPES request
			
				GetSchemaRowset(DBSCHEMA_PROVIDER_TYPES);
				break;

			case IDM_REFERENTIAL_CONSTRAINTS: // Execute DBSCHEMA_REFERENTIAL_CONSTRAINTS request
			
				GetSchemaRowset(DBSCHEMA_REFERENTIAL_CONSTRAINTS);
				break;

			case IDM_SCHEMATA: // Execute DBSCHEMA_SCHEMATA request
			
				GetSchemaRowset(DBSCHEMA_SCHEMATA);
				break;

			case IDM_SQL_LANGUAGES: // Execute DBSCHEMA_SQL_LANGUAGES request
			
				GetSchemaRowset(DBSCHEMA_SQL_LANGUAGES);
				break;

			case IDM_STATISTICS: // Execute DBSCHEMA_STATISTICS request
			
				GetSchemaRowset(DBSCHEMA_STATISTICS);
				break;

			case IDM_TABLE_CONSTRAINTS: // Execute DBSCHEMA_TABLE_CONSTRAINTS request
			
				GetSchemaRowset(DBSCHEMA_TABLE_CONSTRAINTS);
				break;

			case IDM_TABLE_PRIVILEGES: // Execute DBSCHEMA_TABLE_PRIVILEGES request
			
				GetSchemaRowset(DBSCHEMA_TABLE_PRIVILEGES);
				break;

			case IDM_TABLES: // Execute DBSCHEMA_TABLES request
			
				GetSchemaRowset(DBSCHEMA_TABLES);
				break;

			case IDM_TRANSLATIONS: // Execute DBSCHEMA_TRANSLATIONS request
			
				GetSchemaRowset(DBSCHEMA_TRANSLATIONS);
				break;

			case IDM_USAGE_PRIVILEGES: // Execute DBSCHEMA_USAGE_PRIVILEGES request
			
				GetSchemaRowset(DBSCHEMA_USAGE_PRIVILEGES);
				break;

			case IDM_VIEW_COLUMN_USAGE: // Execute DBSCHEMA_VIEW_COLUMN_USAGE request
			
				GetSchemaRowset(DBSCHEMA_VIEW_COLUMN_USAGE);
				break;

			case IDM_VIEW_TABLE_USAGE: // Execute DBSCHEMA_VIEW_TABLE_USAGE request
			
				GetSchemaRowset(DBSCHEMA_VIEW_TABLE_USAGE);
				break;

			case IDM_VIEWS: // Execute DBSCHEMA_VIEWS request
			
				GetSchemaRowset(DBSCHEMA_VIEWS);
				break;

			case IDM_EXIT: // process exit request

				SendMessage(hWndFrame, WM_CLOSE, 0, 0);
				break;

			case IDM_NEW: // create a new query window on current connect

				NewICommandWindow();
				break;

			case IDM_TILE: // let MDI Client tile the MDI children

				SendMessage(hWndMDIClient, WM_MDITILE, 0, 0);
				break;

			case IDM_CASCADE: // let MDI Client cascade MDI children

				SendMessage(hWndMDIClient, WM_MDICASCADE, 0, 0);
				break;

			case IDM_ICONS: // let MDI Client arrange iconic MDI children

				SendMessage(hWndMDIClient, WM_MDIICONARRANGE, 0, 0);
				break;

			case IDM_CLOSEALL: // Close all open windows and free hstmts
            {
				HWND	hWndTemp;	//temp window handle

				// hide MDI Client Windows to avoid repaints
				ShowWindow(hWndMDIClient,SW_HIDE);
				while (hWndTemp = GetWindow(hWndMDIClient, GW_CHILD))
					SendMessage(hWndMDIClient, WM_MDIDESTROY, (WPARAM)hWndTemp, 0);
				ShowWindow(hWndMDIClient, SW_SHOW);
				break;
			}
				
			case IDM_ABOUT: // bringup About dialog
				DialogBox(hAppInstance, ABOUTDIALOG, hWnd, AboutDlgProc);
				break;

			case IDW_CRSRLIST: // change current cursor ?

				if (GET_WM_COMMAND_CMD(wParam, lParam) == CBN_SELCHANGE)
					ChangeCurrentCursor(GET_WM_COMMAND_HWND(wParam, lParam));
				else if (GET_WM_COMMAND_CMD(wParam, lParam) == CBN_KILLFOCUS)
					PostMessage(GET_WM_COMMAND_HWND(wParam, lParam), CB_SHOWDROPDOWN,
						(WPARAM)FALSE, 0);
				else
					DefFrameProc(hWnd, hWndMDIClient, WM_COMMAND, wParam, lParam);
				break;

			case IDW_COMMANDLIST: // change current Command ?

				if (GET_WM_COMMAND_CMD(wParam, lParam) == CBN_SELCHANGE)
					ChangeCurrentICommand(GET_WM_COMMAND_HWND(wParam, lParam));
				else if (GET_WM_COMMAND_CMD(wParam, lParam) == CBN_KILLFOCUS)
					PostMessage(GET_WM_COMMAND_HWND(wParam, lParam), CB_SHOWDROPDOWN,
						(WPARAM)FALSE, 0);
				else
					DefFrameProc(hWnd, hWndMDIClient, WM_COMMAND, wParam, lParam);
				break;

			default:

				DefFrameProc(hWnd, hWndMDIClient, WM_COMMAND, wParam, lParam);
				break;
		}
		break;

		case WM_CLOSE: //close all MDI windows, hdbcs & hstmts, else fail

			return (CloseIDBCreateCommand() ? DefFrameProc(hWnd, hWndMDIClient, message, wParam, lParam) : FALSE);

		case WM_DESTROY:

			PostQuitMessage(0);
			break;

		default:
			return (DefFrameProc(hWnd, hWndMDIClient, message, wParam, lParam));
	}
	return (0);
}


/*
	FUNCTION: MDIChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	COMMENTS: Window Procedure for MDI Child windows
*/
long CALLBACK MDIChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HWND	hWndTemp;	//temporary window handle
	
		case WM_CREATE:

		// create child windows
		// 1. Modeless Dialog box in the background to process tabs
		// 2. Static Text to display prompt
		// 3. Edit Control to type SQL text
		// 4. List Box to display results
		// store dialog handle for future reference
		// set focus to edit control
		
		// if create failed due to low system resources
		if (!hWnd)
			break;
			
		hWndActiveChild = hWnd;
		hWndTemp = CreateDialog(hAppInstance, MDICHILDDIALOG, hWndActiveChild, MDIChildDlgProc);
		
		// check to see if the dialog was created?, if not destroy this window
		if (!hWndTemp)
		{
			return (-1);
		}

		SetWindowLong(hWnd, GWLAPP_HDLG, (LONG)hWndTemp);
		SetFocus(GetDlgItem(hWndTemp, IDTEXT_SQL));
		break;

		case WM_SIZE:
                {
		WORD	wWidth;					//New Width of MDI Child
		WORD	wHeight;				//New Height of MDI Child
		HDC		hDC;					//Device Context
		char	szBuffer[MAXBUFLEN+1];	//Static Control Text
		int		nStrLen;				//Buffer Length
		SIZE	size;					//Screen size for text display
                
		// call default procedure first, to let MDI position the child & then move its children
		DefMDIChildProc(hWnd, message, wParam, lParam);
	        
	    // move child windows with proper screen size for text display
		wWidth = LOWORD(lParam);
		wHeight = HIWORD(lParam);
		hWndTemp = (HWND)GetWindowLong(hWnd, GWLAPP_HDLG);

		nStrLen = GetWindowText(GetDlgItem(hWndTemp, IDTEXT_PRMPT), szBuffer, MAXBUFLEN);
		hDC = GetDC(hWnd);
		GetTextExtentPoint(hDC, szBuffer, nStrLen, &size);
		ReleaseDC(hWnd, hDC);
                
        MoveWindow(hWndTemp, 0, 0, wWidth, wHeight, TRUE);
		MoveWindow(GetDlgItem(hWndTemp, IDTEXT_PRMPT), 0, 0, size.cx+2, size.cy+2, TRUE);
		MoveWindow(GetDlgItem(hWndTemp, IDTEXT_SQL), size.cx+3, 0, wWidth - (size.cx+2), size.cy+2, TRUE);
		MoveWindow(GetDlgItem(hWndTemp, IDLIST_RSLT), 0, size.cy+3, wWidth, wHeight - (size.cy+2), TRUE);
		break;
                }
                
		case WM_MENUSELECT: // update status bar to reflect menu selection
                {
                int	iMenuFlag;		//Check menu type
                
		// store the Menu Item Id as a state value for text display
		wStatusText = GET_WM_MENUSELECT_CMD(wParam, lParam);

		// if none of the menuitems was selected, check if
		// the control popup menu is selected.
		iMenuFlag = GET_WM_MENUSELECT_FLAGS(wParam, lParam);

		// if the selected menu is a system popup menu
		if (wStatusText && (iMenuFlag & MF_SYSMENU) && (iMenuFlag & MF_POPUP))
			wStatusText = IDM_POPUPMDISYS;

		// invalidate status bar for repaint
		InvalidateRect(hWndStatusbar, &rectStatusText, TRUE);
		break;
		}

		case WM_MDIACTIVATE:

		// check if the display of comboboxes require a change
		if (GET_WM_MDIACTIVATE_FACTIVATE(hWnd, wParam, lParam) &&
			(hWndActiveChild) && (hWndActiveChild != hWnd))
		{
			hWndActiveChild = hWnd;
			DisplayNewCrsrAndICommand();
		}
		break;
		
		case WM_MOUSEACTIVATE:
		
        // current window has changed, update comboboxes.
		hWndActiveChild = hWnd;
		DisplayNewCrsrAndICommand();
		break;
		
		case WM_SETFOCUS:
		
		// pass on the focus to the edit box for user to type in SQL
		SetFocus(GetDlgItem((HWND)GetWindowLong(hWnd, GWLAPP_HDLG), IDTEXT_SQL));
		break;
		
		case WM_DESTROY:

        // check if the window was being destroyed while creation failed
        if (!hWnd)
			break;
			                
		// close the window and free instance thunk for modeless dialog
		CloseICommandWindow(hWnd);
		DestroyWindow((HWND)GetWindowLong(hWnd, GWLAPP_HDLG));

		if (hWnd == hWndActiveChild)
			hWndActiveChild = (HWND)NULL;
		break;

		default:
			return (DefMDIChildProc(hWnd, message, wParam, lParam));
	}
	return (0);
}

/*
	FUNCTION: ToolbarProc(HWND hWnd, UINT   message, WPARAM wParam, LPARAM lParam)
	COMMENTS: callback window procedure for toolbar window.
		  Handle pain and mouse messages to paint the toolbar and
		  provide default button behaviour for toolbar buttons.
*/
long CALLBACK ToolbarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	static HBITMAP	hbmpNewQuery;				//btn1 bitmap handle
	static HBITMAP	hbmpRunQuery;				//btn2 bitmap handle
	static RECT		stNewQuery;					//btn1 rectangle
	static RECT		stRunQuery;                 //btn2 rectangle
	POINT			stMousePosition;			//current mouse pos
	BOOL			bButtonPosition;			//mouse pos flag
	static BOOL		bNewQueryBtnDown;			//was btn1 down before?
	static BOOL		bRunQueryBtnDown;			//was btn2 down before?
	static int		nLastButtonDown;			//Which btn was down before?

		bNewQueryBtnDown = FALSE;
		bRunQueryBtnDown = FALSE;
		nLastButtonDown  = 0;

		case WM_CREATE:

		// load bitmaps for buttons
		// initialize static rectangles for button positions on toolbar
		// initialize state variable for status text display
		hbmpNewQuery = LoadBitmap(hAppInstance, BMP_NEWQUERY);
		hbmpRunQuery = LoadBitmap(hAppInstance, BMP_RUNQUERY);
		
		stNewQuery.left   = BTTNX;
		stNewQuery.right  = BTTNX+BTTNWIDTH+1;
		stNewQuery.top    = BTTNY;
		stNewQuery.bottom = BTTNY+BTTNHEIGHT+1;
		
        stRunQuery.left   = BTTNX+BTTNWIDTH+BTTNMARGIN;
        stRunQuery.right  = BTTNX+BTTNWIDTH+BTTNMARGIN+BTTNWIDTH+1;
        stRunQuery.top    = BTTNY;
        stRunQuery.bottom = BTTNY+BTTNHEIGHT+1;
                
		wStatusText = 0;
		break;

		case WM_DESTROY:

		// delete bitmap handles
		if (hbmpNewQuery)
			DeleteObject(hbmpNewQuery);
		if (hbmpRunQuery)
			DeleteObject(hbmpRunQuery);
		break;

		case WM_LBUTTONDOWN:

		// Check if the mouse key lies on any one of the buttons
		// if so, set state variable to reflect that button and
		// invalidate proper regions on tool & status bars for update.
		// set capture on mouse movements till the mouse key is
		// released.
		stMousePosition.x = LOWORD(lParam);
		stMousePosition.y = HIWORD(lParam);
		
		if (PtInRect(&stNewQuery, stMousePosition))
		{
			bNewQueryBtnDown = TRUE;
			wStatusText = nLastButtonDown = IDM_NEW;
			SetCapture(hWnd);
			InvalidateRect(hWnd, &stNewQuery, TRUE);
			InvalidateRect(hWndStatusbar, &rectStatusText, TRUE);
		}
		else if (PtInRect(&stRunQuery, stMousePosition))
		{
			bRunQueryBtnDown = TRUE;
			wStatusText = nLastButtonDown = IDM_QUERY;
			SetCapture(hWnd);
			InvalidateRect(hWnd, &stRunQuery, TRUE);
			InvalidateRect(hWndStatusbar, &rectStatusText, TRUE);
		}
		break;

		case WM_LBUTTONUP:

		// check if the mouse movements from key down movements
		// were captured, if so process the key release state.
		// if the key was released in the same button where it
		// was pressed, it is equivalent to a button click.
		if (hWnd != GetCapture())
			break;

		stMousePosition.x = LOWORD(lParam);
		stMousePosition.y = HIWORD(lParam);

		if (bNewQueryBtnDown && PtInRect(&stNewQuery, stMousePosition))
		{
			bNewQueryBtnDown = FALSE;
			nLastButtonDown = 0;
			InvalidateRect(hWnd, &stNewQuery, TRUE);
			PostMessage(hWndFrame, WM_COMMAND, GET_WM_COMMAND_MPS(IDM_NEW, 0, 0));
			SendMessage(hWndCrsrList, CB_SHOWDROPDOWN, (WPARAM)FALSE, 0);
			SendMessage(hWndStmtList, CB_SHOWDROPDOWN, (WPARAM)FALSE, 0);
		}
		else if (bRunQueryBtnDown && PtInRect(&stRunQuery, stMousePosition))
		{
			bRunQueryBtnDown = FALSE;
			nLastButtonDown = 0;
			InvalidateRect(hWnd, &stRunQuery, TRUE);
			PostMessage(hWndFrame, WM_COMMAND, GET_WM_COMMAND_MPS(IDM_QUERY, 0, 0));
			SendMessage(hWndCrsrList, CB_SHOWDROPDOWN, (WPARAM)FALSE, 0);
			SendMessage(hWndStmtList, CB_SHOWDROPDOWN, (WPARAM)FALSE, 0);
                }

		ReleaseCapture();
		wStatusText = 0;
		InvalidateRect(hWndStatusbar, &rectStatusText, TRUE);
		break;

		case WM_MOUSEMOVE:
                
        // process mouse movement only if the mouse key was pressed
        // down and its movements were being captured. If the mouse
        // moves outside of the currently depressed button, it needs
        // to be drawn again with normal state.
		if (hWnd != GetCapture())
			break;

		stMousePosition.x = LOWORD(lParam);
		stMousePosition.y = HIWORD(lParam);

		if (nLastButtonDown == IDM_NEW)
		{
			bButtonPosition = PtInRect(&stNewQuery, stMousePosition);
			if (bNewQueryBtnDown != bButtonPosition)
			{
				bNewQueryBtnDown = bButtonPosition;
				InvalidateRect(hWnd, &stNewQuery, TRUE);
			}
		}
		else if (nLastButtonDown == IDM_QUERY)
		{
			bButtonPosition = PtInRect(&stRunQuery, stMousePosition);
			if (bRunQueryBtnDown != bButtonPosition)
			{
				bRunQueryBtnDown = bButtonPosition;
				InvalidateRect(hWnd, &stRunQuery, TRUE);
			}
		}
		break;

		case WM_PAINT:
                {
		PAINTSTRUCT	ps;			//paint structure
		RECT		rect;		//rectangle for tool bar
		HDC			hDC;		//device context handle
		int			iWidth;		//tool bar width
		int			iHeight;	//tool bar height
		HPEN		hLtGrayPen;	//buttonface color pen
		HPEN		hGrayPen;	//buttonshadow color pen
		int			btnx;		//button x coordinate position
                                
		if (!(hDC = BeginPaint(hWnd, &ps)))
			break;

		GetClientRect(hWnd, &rect);
		iWidth = rect.right;
		iHeight = rect.bottom;

		hLtGrayPen = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_BTNFACE));
		hGrayPen = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));
                
        // draw background and border
		SelectObject(hDC, GetStockObject(LTGRAY_BRUSH));
		SelectObject(hDC, hLtGrayPen);
		Rectangle(hDC, 0, 0, iWidth, iHeight);

		SelectObject(hDC, GetStockObject(BLACK_PEN));
		MoveToEx(hDC, 0, iHeight-1, NULL);
		LineTo(hDC, iWidth, iHeight-1);

		SelectObject(hDC, GetStockObject(WHITE_PEN));
		MoveToEx(hDC, 0, 0, NULL);
		LineTo(hDC, iWidth, 0);

		// draw tool bar buttons (new query, run query)
        // check state variables to draw proper button state
		btnx = BTTNX;
		SelectObject(hDC, GetStockObject(BLACK_PEN));
		DRAWBTTNRECT(hDC, btnx, BTTNY, BTTNWIDTH, BTTNHEIGHT);
		DrawBitmap(hDC, (bNewQueryBtnDown?btnx+3:btnx+2), (bNewQueryBtnDown?BTTNY+3:BTTNY+2), hbmpNewQuery);
		SelectObject(hDC, (bNewQueryBtnDown ? hGrayPen : GetStockObject(WHITE_PEN)));
		DRAWBTTNLIFT1(hDC, btnx, BTTNY, BTTNWIDTH, BTTNHEIGHT);
		SelectObject(hDC, (bNewQueryBtnDown ? hLtGrayPen : hGrayPen));
		DRAWBTTNLIFT2(hDC, btnx, BTTNY, BTTNWIDTH, BTTNHEIGHT);

		btnx += BTTNWIDTH+BTTNMARGIN;
		SelectObject(hDC, GetStockObject(BLACK_PEN));
		DRAWBTTNRECT(hDC, btnx, BTTNY, BTTNWIDTH, BTTNHEIGHT);
		DrawBitmap(hDC, (bRunQueryBtnDown?btnx+3:btnx+2), (bRunQueryBtnDown?BTTNY+3:BTTNY+2), hbmpRunQuery);
		SelectObject(hDC, (bRunQueryBtnDown ? hGrayPen : GetStockObject(WHITE_PEN)));
		DRAWBTTNLIFT1(hDC, btnx, BTTNY, BTTNWIDTH, BTTNHEIGHT);
		SelectObject(hDC, (bRunQueryBtnDown ? hLtGrayPen : hGrayPen));
		DRAWBTTNLIFT2(hDC, btnx, BTTNY, BTTNWIDTH, BTTNHEIGHT);

		SelectObject(hDC, GetStockObject(WHITE_PEN));
		EndPaint(hWnd, &ps);
		
		// delete create objects
		if (hLtGrayPen)
			DeleteObject(hLtGrayPen);
		if (hGrayPen)
			DeleteObject(hGrayPen);
		break;
                }
                
		default:

		return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}

/*
	FUNCTION: StatusbarProc(HWND hWnd, UINT   message, WPARAM wParam, LPARAM lParam)
	COMMENTS: callback window procedure for status bar.
		  process paint messages and timer messages to update current
		  state, date and time
*/
long CALLBACK StatusbarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	static RECT DateTimeRect; // remember for frequent updates
	
		case WM_CREATE:
                {
		HDC		hDC;			// device context
		SIZE	sizeText;       // size of status text box
		SIZE	sizeTime;       // size of time display box
		SIZE	sizeDate;       // size of date display box
                
        // start a timer for periodic updates to date and time display
        // find out width of status text, date and time display boxes
		SetTimer(hWnd,  (UINT)IDT_STATUSTIMER, (UINT)TIMERDELAY, NULL);

		iTimex = iDatex = 0;
		rectStatusText.left = 2;
		rectStatusText.top = 3;

		if (hDC = GetDC(hWnd))
		{
			GetTextExtentPoint(hDC, STATUSCONSTRAINT_COLUMN_USAGE, strlen(STATUSCONSTRAINT_COLUMN_USAGE), &sizeText);
			GetTextExtentPoint(hDC, TIMETEXT, strlen(TIMETEXT), &sizeTime);
			GetTextExtentPoint(hDC, DATETEXT, strlen(DATETEXT), &sizeDate);
			ReleaseDC(hWnd, hDC);
			rectStatusText.right = sizeText.cx + rectStatusText.left;
			iTimex = sizeTime.cx;
			iDatex = sizeDate.cx;
		}
		break;
                }
                
		case WM_TIMER:
		
		// invalidate only the date&time area for update
	 	InvalidateRect(hWnd, &DateTimeRect, TRUE);
		break;

		case WM_PAINT:
                {
		HDC			hDC;				//device context
		PAINTSTRUCT	ps;					//paint structure
		RECT		rect;               //status bar rect
		int			iWidth;             //status bar width
		int			iHeight;            //status bar height
		HPEN		hLtGrayPen;         //btnface color pen
		HPEN		hGrayPen;           //btnshadow color pen
		char		szText[MAXBUFLEN];  //text buffer for display
		time_t		tCurrentTime;       //current date&time
		struct tm	stTime;             //date&time structure

		if (!(hDC = BeginPaint(hWnd, &ps)))
			break;

		GetClientRect(hWnd, &rect);
		iWidth = rect.right;
		iHeight = rect.bottom;
		rectStatusText.bottom = iHeight-2;
		
		hLtGrayPen = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_BTNFACE));
		hGrayPen = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));

		// paint background and border
		SelectObject(hDC, GetStockObject(LTGRAY_BRUSH));
		SelectObject(hDC, hLtGrayPen);
		Rectangle(hDC, 0, 0, iWidth, iHeight);

		SelectObject(hDC, GetStockObject(BLACK_PEN));
		MoveToEx(hDC, 0, 0, NULL);
		LineTo(hDC, iWidth, 0);
		SelectObject(hDC, GetStockObject(WHITE_PEN));
		MoveToEx(hDC, 0, 1, NULL);
		LineTo(hDC, iWidth, 1);
                
        // draw text boxes for status, time and date display
        SelectObject(hDC, hGrayPen);
        MoveToEx(hDC, rectStatusText.left, rectStatusText.bottom, NULL);
        LineTo(hDC, rectStatusText.left, rectStatusText.top);
        LineTo(hDC, rectStatusText.right, rectStatusText.top);
        SelectObject(hDC, GetStockObject(WHITE_PEN));
        LineTo(hDC, rectStatusText.right, rectStatusText.bottom);
        LineTo(hDC, rectStatusText.left, rectStatusText.bottom);
        
        SelectObject(hDC, hGrayPen);
        MoveToEx(hDC, iWidth-2, 3, NULL);
        LineTo(hDC, iWidth-iDatex-2, 3);
        LineTo(hDC, iWidth-iDatex-2, iHeight-2);
        SelectObject(hDC, GetStockObject(WHITE_PEN));
        LineTo(hDC, iWidth-2, iHeight-2);
        LineTo(hDC, iWidth-2, 3);
        
        SelectObject(hDC, hGrayPen);
        MoveToEx(hDC, iWidth-iDatex-6, 3, NULL);
        LineTo(hDC, iWidth-iTimex-iDatex-6, 3);
        LineTo(hDC, iWidth-iTimex-iDatex-6, iHeight-2);
        SelectObject(hDC, GetStockObject(WHITE_PEN));
        LineTo(hDC, iWidth-iDatex-6, iHeight-2);
        LineTo(hDC, iWidth-iDatex-6, 3);

		// draw status text in the display box based on current
		// value of wStatusText global flag
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, GetSysColor(COLOR_BTNTEXT));

		switch (wStatusText)
		{
			case IDM_POPUPAPPSYS:
			
			strcpy(szText, STATUSPOPUPAPPSYS);
			break;
			
			case IDM_POPUPMDISYS:
			
			strcpy(szText, STATUSPOPUPMDISYS);
			break;
			
			case SC_RESTORE:
			
			strcpy(szText, STATUSRESTORE);
			break;
			
			case SC_MOVE:
			
			strcpy(szText, STATUSMOVE);
			break;
			
			case SC_SIZE:
			
			strcpy(szText, STATUSSIZE);
			break;
			
			case SC_MINIMIZE:
			
			strcpy(szText, STATUSMINIMIZE);
			break;
			
			case SC_MAXIMIZE:
			
			strcpy(szText, STATUSMAXIMIZE);
			break;
			
			case SC_CLOSE:
			
			strcpy(szText, STATUSCLOSE);
			break;
			
			case SC_NEXTWINDOW:
			
			strcpy(szText, STATUSNEXTWINDOW);
			break;
			
			case SC_PREVWINDOW:
			
			strcpy(szText, STATUSPREVWINDOW);
			break;
			
			case SC_TASKLIST:
			
			strcpy(szText, STATUSTASKLIST);
			break;
			
			case IDM_POPUPLOGIN:
			
			strcpy(szText, STATUSPOPUPLOGIN);
			break;
			
			case IDM_INITIALIZE:
			
			strcpy(szText, STATUSCONNECT);
			break;
			
			case IDM_DISCONNECT:
			
			strcpy(szText, STATUSDISCONNECT);
			break;
			
			case IDM_EXIT:
			
			strcpy(szText, STATUSEXIT);
			break;
			
			case IDM_POPUPQUERY:
			
			strcpy(szText, STATUSPOPUPQUERY);
			break;
			
	        case IDM_QUERY:
	        	
	        strcpy(szText, STATUSQUERY);
	        break;

			case IDM_NEW:
	        	
	        	strcpy(szText, STATUSNEW);
			break;

			case IDM_POPUPSCHEMA:
			
			strcpy(szText, STATUSPOPUPSCHEMA);
			break;
			
			case IDM_POPUPWINDOW:
			
			strcpy(szText, STATUSPOPUPWINDOW);
			break;
			
			case IDM_TILE:
			
			strcpy(szText, STATUSTILE);
			break;
			
			case IDM_CASCADE:
			
			strcpy(szText, STATUSCASCADE);
			break;
			
			case IDM_ICONS:
			
			strcpy(szText, STATUSICONS);
			break;
			
			case IDM_CLOSEALL:
			
			strcpy(szText, STATUSCLOSEALL);
			break;
			
			case IDM_POPUPHELP:
			
			strcpy(szText, STATUSPOPUPHELP);
			break;
			
			case IDM_APPHELP:
			
			strcpy(szText, STATUSAPPHELP);
			break;
			
			case IDM_ABOUT:
			
			strcpy(szText, STATUSABOUT);
			break;
			
			case IDM_ASSERTIONS: 
			
			strcpy(szText, STATUSASSERTIONS);
			break;

			case IDM_CATALOGS: 
			
			strcpy(szText, STATUSCATALOGS);
			break;

			case IDM_CHARACTER_SETS: 
			
			strcpy(szText, STATUSCHARACTER_SETS);	
			break;

			case IDM_CHECK_CONSTRAINTS:
			
			strcpy(szText, STATUSCHECK_CONSTRAINTS);	
			break;

			case IDM_COLLATIONS: 
			
			strcpy(szText, STATUSCOLLATIONS);	
			break;

			case IDM_COLUMN_DOMAIN_USAGE: 
			
			strcpy(szText, STATUSCOLUMN_DOMAIN_USAGE);	
			break;

			case IDM_COLUMN_PRIVILEGES: 
			
			strcpy(szText, STATUSCOLUMN_PRIVILEGES);	
			break;

			case IDM_COLUMNS: 
			
			strcpy(szText, STATUSCOLUMNS);	
			break;

			case IDM_CONSTRAINT_COLUMN_USAGE: 
			
			strcpy(szText, STATUSCONSTRAINT_COLUMN_USAGE);	
			break;

			case IDM_CONSTRAINT_TABLE_USAGE: 
			
			strcpy(szText, STATUSCONSTRAINT_TABLE_USAGE);	
			break;

			case IDM_FOREIGN_KEYS: 
			
			strcpy(szText, STATUSFOREIGN_KEYS);	
			break;

			case IDM_INDEXES: 
				
			strcpy(szText, STATUSINDEXES);	
			break;

			case IDM_KEY_COLUMN_USAGE: 
				
			strcpy(szText, STATUSKEY_COLUMN_USAGE);	
			break;

			case IDM_PRIMARY_KEYS: 
			
			strcpy(szText, STATUSPRIMARY_KEYS);	
			break;

			case IDM_PROCEDURE_COLUMNS: 
			
			strcpy(szText, STATUSPROCEDURE_COLUMNS);	
			break;

			case IDM_PROCEDURE_PARAMETERS: 
			
			strcpy(szText, STATUSPROCEDURE_PARAMETERS);	
			break;

			case IDM_PROCEDURES: 
			
			strcpy(szText, STATUSPROCEDURES);	
			break;

			case IDM_PROVIDER_TYPES: 
			
			strcpy(szText, STATUSPROVIDER_TYPES);	
			break;

			case IDM_REFERENTIAL_CONSTRAINTS: 
			
			strcpy(szText, STATUSREFERENTIAL_CONSTRAINTS);	
			break;

			case IDM_SCHEMATA: 
			
			strcpy(szText, STATUSSCHEMATA);	
			break;

			case IDM_SQL_LANGUAGES: 
			
			strcpy(szText, STATUSSQL_LANGUAGES);	
			break;

			case IDM_STATISTICS: 
			
			strcpy(szText, STATUSSTATISTICS);	
			break;

			case IDM_TABLE_CONSTRAINTS: 
			
			strcpy(szText, STATUSTABLE_CONSTRAINTS);	
			break;

			case IDM_TABLE_PRIVILEGES: 
			
			strcpy(szText, STATUSTABLE_PRIVILEGES);
			break;

			case IDM_TABLES: 
			
			strcpy(szText, STATUSTABLES);	
			break;

			case IDM_TRANSLATIONS: 
			
			strcpy(szText, STATUSTRANSLATIONS);	
			break;

			case IDM_USAGE_PRIVILEGES: 
			
			strcpy(szText, STATUSUSAGE_PRIVILEGES);	
			break;

			case IDM_VIEW_COLUMN_USAGE: 
			
			strcpy(szText, STATUSVIEW_COLUMN_USAGE);	
			break;

			case IDM_VIEW_TABLE_USAGE: 
			
			strcpy(szText, STATUSVIEW_TABLE_USAGE);	
			break;

			case IDM_VIEWS: 
			
			strcpy(szText, STATUSVIEWS);	
			break;

			default:
                        
            if (wStatusText >= IDM_MDICHILD)
            	sprintf(szText, STATUSMDICHILD, wStatusText-IDM_MDICHILD+1);
            else	
        	strcpy(szText, STATUSDEFAULT);
			break;
		}
		
		DrawText(hDC, szText, strlen(szText), &rectStatusText, DT_LEFT);
                
	    // get current date and time and display time in time box
		time(&tCurrentTime);
		stTime = *localtime(&tCurrentTime);
		strftime(szText, MAXBUFLEN, TIMEFORMAT, &stTime);
		rect.top = rectStatusText.top;
		rect.bottom = rectStatusText.bottom;
		rect.left  = iWidth-iTimex-iDatex-6;
		rect.right = iWidth-iDatex-6;
		DrawText(hDC, szText, strlen(szText), &rect, DT_LEFT);
		
		// display date in date box
		strftime(szText, MAXBUFLEN, DATEFORMAT, &stTime);
		rect.left  = iWidth-iDatex-2;
		rect.right = iWidth-2;
		DrawText(hDC, szText, strlen(szText), &rect, DT_LEFT);

		// remember the date&time rectangle to minimize painting
		DateTimeRect.left   = iWidth-iTimex-iDatex-6;
		DateTimeRect.right  = iWidth-2;
		DateTimeRect.top    = rect.top;
		DateTimeRect.bottom = rect.bottom;
		
		EndPaint(hWnd, &ps);

		// delete created objects
		if (hLtGrayPen)
			DeleteObject(hLtGrayPen);
		if (hGrayPen)
			DeleteObject(hGrayPen);
		break;
                }
                
		default:

		return (DefWindowProc(hWnd, message, wParam, lParam));
		break;
	}
	return (0);
}

/*
	FUNCTION: ConnectDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	COMMENTS: Callback dialog box procedure for connect menu command
		  displays a list of available data sources, asks for user
		  name and password to pass default connection parameters
		  for a data source connection
*/
BOOL CALLBACK ConnectDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	HCURSOR	hOldCursor;	// Default Cursor Shape

		case WM_INITDIALOG:
                
        // display list of available providers
		hOldCursor = SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
		DisplayProviders(GetDlgItem(hWnd, IDCOMBO_PROVIDER));
//		DisplayDataSource(hWnd);	
		FillPrompt(GetDlgItem(hWnd, IDCOMBO_PROMPT));
		SetCursor(hOldCursor);
		break;
		
		case WM_COMMAND:

		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
			// Make a connection using the supplied values
			case IDOK:
				hOldCursor = SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
	            // Check if a DSO was provided for connection
				if( ConnectDatabase(hWnd) )
					EndDialog(hWnd, TRUE);
				SetCursor(hOldCursor);
			break;

			case IDCANCEL:
				EndDialog(hWnd, FALSE);
			break;

			default:

			return (FALSE);
			break;
		}
		break;
		
		default:
		
		return (FALSE);
		break;
	}
	return (TRUE);
}

/*
	FUNCTION: DisconnectDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	COMMENTS: Callback dialog box procedure for disconnect dialog.
		  provides a list of available SESSIONs and a list of HSTMTs
		  for currently selected SESSION. Allows closure of all SESSIONs
		  and HSTMTs one by one or in groups.
*/
BOOL CALLBACK DisconnectDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	static HWND	hListhdbc;		//listbox that displays hdbc(s)
	static HWND	hListstmt;      //listbox that displays hstmt(s)
	static HWND	hPushOk;        //pushbutton to free hdbc
	static HWND	hPushClose;     //pushbutton to free hstmt
	static HWND	hPushCancel;    //pushbutton to close dialog

		case WM_INITDIALOG:

		// store handles for future reference
		hListhdbc = GetDlgItem(hWnd, IDLIST_SESSION);
		hListstmt = GetDlgItem(hWnd, IDLIST_COMMAND);
		hPushOk = GetDlgItem(hWnd, IDDISCONNECT);
		hPushCancel = GetDlgItem(hWnd, IDCANCEL);
		hPushClose = GetDlgItem(hWnd, IDCLOSE_ACTVTY);

		// display connected database handles and statements
		DisplayConnections(hListhdbc);
		DisplayICommands(hListstmt, hListhdbc, 0);

		// enable or disable pushbuttons & listboxes to match available hdbc & hstmt
		if (SendMessage(hListhdbc, LB_GETCOUNT, 0, 0)>0)
		{
			EnableWindow(hPushOk, TRUE);
			if (SendMessage(hListstmt, LB_GETCOUNT, 0, 0)>0)
			{
				EnableWindow(hPushClose, TRUE);
				SetFocus(hPushClose);
				SendMessage(hPushClose, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
			}
			else
			{
				EnableWindow(hListstmt, FALSE);
				EnableWindow(hPushClose, FALSE);
				SetFocus(hPushOk);
				SendMessage(hPushOk, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
			}
		}
		else
		{
			EnableWindow(hListhdbc, FALSE);
			EnableWindow(hListstmt, FALSE);
			EnableWindow(hPushOk, FALSE);
			SetFocus(hPushCancel);
			SendMessage(hPushCancel, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
		}
		
		// return FALSE to prevent default focus.
		return (FALSE);

		case WM_COMMAND:

		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
			case IDDISCONNECT:
                        
            // Free current hdbc, display available hdbc(s)
			FreeConnect(hListhdbc);
			SendMessage(hListstmt, LB_RESETCONTENT, 0, 0);
			DisplayConnections(hListhdbc);
                        
            // update displayed hstmt(s) for current hdbc
            // enable or disable pushbuttons to match available
            // hdbc(s) and hstmt(s) for closure
			if (SendMessage(hListhdbc, LB_GETCOUNT, 0, 0) > 0)
			{
				SendMessage(hListhdbc, LB_SETCURSEL, 0, 0);
				EnableWindow(hListstmt, TRUE);
				DisplayICommands(hListstmt, hListhdbc, 0);
				if (SendMessage(hListstmt, LB_GETCOUNT, 0, 0)>0)
				{
					EnableWindow(hPushClose, TRUE);
					SetFocus(hPushClose);
					SendMessage(hPushClose, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
				}
				else
				{
					EnableWindow(hListstmt, FALSE);
					EnableWindow(hPushClose, FALSE);
					SetFocus(hPushOk);
					SendMessage(hPushOk, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
				}
			}
			else
			{
				EnableWindow(hListhdbc, FALSE);
				EnableWindow(hPushOk, FALSE);
				EnableWindow(hPushClose, FALSE);
				SetFocus(hPushCancel);
				SendMessage(hPushCancel, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
			}
			break;

			case IDCANCEL:

			// close dialog
			EndDialog(hWnd, FALSE);
			break;

			case IDCLOSE_ACTVTY:
                        {
			int	nIndex;	// counter to search for selected hstmt(s)
			
			// go through all displayed hstmt(s) and free all highlighted ones
			for (nIndex = (int)SendMessage(hListstmt, LB_GETCOUNT, 0, 0)-1;
				nIndex >= 0; nIndex--)
				if (SendMessage(hListstmt, LB_GETSEL, nIndex, 0))
					FreeICommand(hListstmt, hListhdbc, nIndex);

			// reset both hdbc(s) and hstmt(s) display
			nIndex = (int)SendMessage(hListhdbc, LB_GETCURSEL, 0, 0);
			DisplayConnections(hListhdbc);
			SendMessage(hListhdbc, LB_SETCURSEL, nIndex, 0);
			DisplayICommands(hListstmt, hListhdbc, nIndex);
			
			// enable or disable pushbuttons to match available
			// hdbc(s) and hstmt(s) for closure
			if (SendMessage(hListstmt, LB_GETCOUNT, 0, 0)>0)
			{
				EnableWindow(hPushClose, TRUE);
				SetFocus(hPushClose);
				SendMessage(hPushClose, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
			}
			else
			{
				EnableWindow(hListstmt, FALSE);
				EnableWindow(hPushClose, FALSE);
				SetFocus(hPushOk);
				SendMessage(hPushOk, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
			}
			break;
                        }
                        
			case IDLIST_SESSION:
			// If the current selection in hdbc(s) has changed
			// update the list of hstmt(s) to match the new hdbc
			if (GET_WM_COMMAND_CMD(wParam, lParam) == LBN_SELCHANGE)
				DisplayICommands(hListstmt, hListhdbc,
				(UINT)SendMessage(GET_WM_COMMAND_HWND(wParam, lParam), LB_GETCURSEL, 0, 0));

            // Enable or disable hstmt listbox and close pushbutton accordingly
			EnableWindow(hListstmt, (SendMessage(hListstmt, LB_GETCOUNT, 0, 0)>0));
			EnableWindow(hPushClose, (SendMessage(hListstmt, LB_GETCOUNT, 0, 0)>0));
			break;

			default:

			return (FALSE);
		}
		break;

		default:

		return (FALSE);
	}
	
	return (TRUE);
}

/*
	FUNCTION: AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	COMMENTS: Callback dialog box procedure for About dialog box
		  displays the about information and closes upon selection of
		  ok button
*/
BOOL CALLBACK AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_COMMAND)
	{
		EndDialog(hWnd, TRUE);
		return (TRUE);
	}
	else
		return (FALSE);
}

/*
	FUNCTION: MDIChildDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	COMMENTS: Callback dialog box procedure for modeless child dialog box
		  in each MDI Child Window. This dialog box simply processes
		  the tab messages (by default) to allow switching from edit
		  control (SQL Text) to list box control (Query results).
*/
BOOL CALLBACK MDIChildDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return (FALSE);
}

/*
	FUNCTION: DrawBitmap(HDC hDC, int iLeft, int iTop, HBITMAP hBitmap
	COMMENTS: Draws a bitmap on given Device context with given bitmap
		  handle at given location
*/

VOID FAR PASCAL DrawBitmap(HDC hDC, int iLeft, int iTop, HBITMAP hBitmap)
{
	HDC		hMemDC;		// Device Context in Memory
	POINT	stPoint;    // point structure for conversion from device to logical units
	BITMAP	stBitmap;
    HGDIOBJ hObject;
        
    // create a compatible device context in memory and select the bitmap
    // in to it.
	if (!(hMemDC = CreateCompatibleDC(hDC))) return;

	hObject = SelectObject(hMemDC, hBitmap);
	SetMapMode(hMemDC, GetMapMode(hDC));

	// Get bitmap size and convert it to logical units from device units.
	GetObject(hBitmap, sizeof(BITMAP), &stBitmap);
	stPoint.x = stBitmap.bmWidth;
	stPoint.y = stBitmap.bmHeight;
	DPtoLP(hDC, &stPoint, 1);

	// bit block transfer the bitmap from memory device context to given
	// device context at specified location
	BitBlt(hDC, iLeft, iTop, stPoint.x, stPoint.y, hMemDC, 0, 0, SRCCOPY);
        
    // select original object in the memory device context and destroy it
	SelectObject(hMemDC, hObject);
	DeleteDC(hMemDC);
}


void FillPrompt(HWND hWnd)
{
	const static LPCTSTR rgPrompts[] =
	{	
		//The order is the same as the Actual DBPROMPT Values
		"Not Set",			// 0
		"PROMPT",			// 1 == DBPROMPT_PROMPT
		"COMPLETE",			// 2 == DBPROMPT_COMPLETE
		"COMPLETEREQUIRED",	// 3 == DBPROMPT_COMPLETEREQUIRED
		"NOPROMPT"			// 4 == DBPROMPT_NOPROMPT
	};

	for (int i=0;  i<sizeof(rgPrompts) / sizeof(rgPrompts[0]); i++)
		SendMessage(hWnd, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR) rgPrompts[i]);
	SendMessage(hWnd, CB_SETCURSEL, (WPARAM) DBPROMPT_COMPLETE, 0L);
}

/********************************************* END OF FILE **************************************************/
