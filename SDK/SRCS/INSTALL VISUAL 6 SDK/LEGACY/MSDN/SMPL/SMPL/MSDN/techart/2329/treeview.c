/****************************************************************************
*
*
*    PROGRAM: TreeView.c
*
*    PURPOSE: Demonstrates the use of the new tree view control in Chicago
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <commctrl.h>   // includes the common control header
#include <string.h>
#include "treeview.h"

// global current instance
HINSTANCE hInst;

// image list indices
int idxForSale, idxRedmond, idxBellevue, idxSeattle;

// Handles to major tree branches
HTREEITEM hTRoot, hTRed, hTBel, hTSea;

// Drag and drop boolean
BOOL g_fDragging = FALSE;

// Houses
HOUSEINFO rgHouseInfo[] = 
{
	{"100 Berry Lane", 0, NULL, NULL },
	{"523 Apple Road", 0, NULL, NULL},
	{"1212 Peach Street", 0, NULL, NULL},
	{"22 Daffodil Lane", 0, NULL, NULL},
	{"33542 Orchid Road", 0, NULL, NULL},
	{"64134 Lily Street", 0, NULL, NULL},
	{"33 Nicholas Lane", 0, NULL, NULL},
	{"555 Tracy Road", 0, NULL, NULL},
	{"446 Jean Street", 0, NULL, NULL}
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
	WNDCLASS  wcTreeView;
	
	/* Fill in window class structure with parameters that describe the       */
	/* main window.                                                           */

	wcTreeView.style = 0;                     
	wcTreeView.lpfnWndProc = (WNDPROC)MainWndProc; 
	wcTreeView.cbClsExtra = 0;              
	wcTreeView.cbWndExtra = 0;              
	wcTreeView.hInstance = hInstance;       
	wcTreeView.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(APP_ICON));
	wcTreeView.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcTreeView.hbrBackground = GetStockObject(WHITE_BRUSH); 
	wcTreeView.lpszMenuName =  "TreeViewMenu";  
	wcTreeView.lpszClassName = "TreeViewWClass";

	return (RegisterClass(&wcTreeView));

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
		"TreeViewWClass",           
		"TreeView Sample", 
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
	static HWND hWndTreeView;   // Handle of the tree window
	TV_HITTESTINFO tvHit;       // Hit test information
	TV_ITEM tvI;                // Item being dragged
	static HTREEITEM hDragItem;
	HTREEITEM hTarget;

	switch (message) 
	{

		case WM_CREATE:
			// Create the tree view window and initialize its
			// image list
			hWndTreeView = CreateTreeView( hWnd );
			if (hWndTreeView == NULL)
				MessageBox (NULL, "Tree View not created!", NULL, MB_OK );
			// Add items to the tree window
			if (!AddTreeViewItems(hWndTreeView))
				MessageBox(NULL, "Items not added", NULL, MB_OK);
			break;          

        case WM_SIZE:
            MoveWindow(hWndTreeView, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
            break;

		case WM_NOTIFY:
			switch( ((LPNMHDR)lParam)->code)
			{
				case TVN_BEGINDRAG:
					// The user wants to drag an item. Call the drag handler.
					BeginDrag(hWndTreeView, (NM_TREEVIEW *)lParam);
					// Save off the dragged item information.
					tvI = ((NM_TREEVIEW *)lParam)->itemNew;

					// Get a handle to the drag object.
					hDragItem = tvI.hItem;

					break;

				default:
					break;
			}
			break;

		case WM_MOUSEMOVE:
			// if dragging, move the image
			if (g_fDragging)
			{
				// drag the item to the current mouse position
				ImageList_DragMove(LOWORD(lParam),HIWORD(lParam));

				// if the cursor is on an item, hilite it as
				// the drop target
				tvHit.pt.x = LOWORD(lParam);
				tvHit.pt.y = HIWORD(lParam);
				if ((hTarget = TreeView_HitTest(hWndTreeView, &tvHit)) != NULL)
					TreeView_SelectDropTarget(hWndTreeView, hTarget);
			}
			break;

		case WM_LBUTTONUP:
			// If dragging, stop it.
			if (g_fDragging)
			{
				// Process the item drop.
				DropItem(hDragItem, hWndTreeView);
				
				// Inform the image list that dragging has stopped.
				ImageList_EndDrag();

				// Release the mouse.
				ReleaseCapture();

				// Show the cursor.
				ShowCursor(TRUE);

				// Reset the global Boolean flag to a nondragging state.
				g_fDragging = FALSE;

				   
			}
			break;

		case WM_COMMAND:

			switch( LOWORD( wParam ))
			{

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
*    FUNCTION: CreateTreeView(HWND)
*
*    PURPOSE:  Creates the tree view window and initializes it
*
****************************************************************************/
HWND CreateTreeView (HWND hWndParent)                                     
{
	HWND hwndTree;      // handle to tree view window
	RECT rcl;           // rectangle for setting size of window
	HBITMAP hBmp;       // handle to a bitmap
	HIMAGELIST hIml;    // handle to image list

	// Ensure that the common control DLL is loaded.
	InitCommonControls();

	// Get the size and position of the parent window.
	GetClientRect(hWndParent, &rcl);

	// Create the tree view window.
	hwndTree = CreateWindowEx( 0L,
		WC_TREEVIEW,						// tree view class
		"",                   		        // no default text
		WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS | 
			TVS_LINESATROOT,
		0, 0,
		rcl.right - rcl.left, rcl.bottom - rcl.top - 15,
		hWndParent,
		(HMENU) ID_TREEVIEW,
		hInst,
		NULL );

	if (hwndTree == NULL )
		return NULL;

	// Initialize the tree view window.
	// First create the image list you will need.
	hIml = ImageList_Create( BITMAP_WIDTH,  // width
	    BITMAP_HEIGHT,                      // height
		0,                                  // creation flags
		NUM_BITMAPS,                        // number of images
		0 );                                // amount this list can grow

	// Load the bitmaps and add them to the image list.
	hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(FORSALE));
	idxForSale = ImageList_Add(hIml,        // handle to imagelist
	                           hBmp,        // handle of bitmap to add
	                           NULL);       // handle of bitmap mask

	DeleteObject((HGDIOBJ)hBmp);

	hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(REDMOND));
	idxRedmond = ImageList_Add(hIml, hBmp, NULL);
	DeleteObject((HGDIOBJ)hBmp);

	hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(BELLEVUE));
	idxBellevue = ImageList_Add(hIml, hBmp, NULL);
	DeleteObject((HGDIOBJ)hBmp);

	hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(SEATTLE));
	idxSeattle = ImageList_Add(hIml, hBmp, NULL);
	DeleteObject((HGDIOBJ)hBmp);

	// Be sure that all the bitmaps were added.
	if (ImageList_GetImageCount(hIml) < NUM_BITMAPS)
		return FALSE;

	// Associate the image list with the tree view control.
	TreeView_SetImageList(hwndTree, hIml, idxForSale);

	return (hwndTree);
}

/****************************************************************************
* 
*    FUNCTION: AddTreeViewItems(HWND)
*
*    PURPOSE: Fills in the tree view list. 
*
****************************************************************************/

BOOL AddTreeViewItems( HWND hwndTree )
{
	static HTREEITEM hPrev;
	char szText[MAX_LEN];
	int index;

	// First add the root item "Houses for Sale."
	LoadString(hInst, IDS_FORSALE, szText, MAX_LEN);
	hTRoot = AddOneItem((HTREEITEM)NULL, szText, (HTREEITEM)TVI_ROOT, idxForSale, hwndTree);

	// Now add the cities.
	LoadString(hInst, IDS_REDMOND, szText, MAX_LEN);
	hTRed = AddOneItem(hTRoot, szText, (HTREEITEM)TVI_FIRST, idxRedmond, hwndTree);

	LoadString(hInst, IDS_BELLEVUE, szText, MAX_LEN);
	hTBel = AddOneItem(hTRoot, szText, hTRed, idxBellevue, hwndTree);

	LoadString(hInst, IDS_SEATTLE, szText, MAX_LEN);
	hTSea = AddOneItem(hTRoot, szText, hTBel, idxSeattle, hwndTree);

	// Fill in the structure for each house.
	FillInStruct(hTRed, idxRedmond, 0, 3);
	FillInStruct(hTBel, idxBellevue, 3, 6);
	FillInStruct(hTSea, idxSeattle, 6, 9);

	// Add the houses for each city.
	hPrev = hTSea;
	for (index = 0; index < NUM_HOUSES; index++)
	{
		hPrev = AddOneItem(rgHouseInfo[index].hParent, 
						rgHouseInfo[index].szAddress,
						hPrev,
						rgHouseInfo[index].iImage,
						hwndTree);
		rgHouseInfo[index].hItem = hPrev;
	}
	return TRUE;
}


// This function saves the current image and the handle to the
// parent of the tree view item.
VOID FillInStruct(HTREEITEM hParent, int iImage, int index, int iMax)
{
	for (;index < iMax; index++)
	{
		rgHouseInfo[index].iImage = iImage;
		rgHouseInfo[index].hParent = hParent;
	}
}

/***************************************************************************
* 
*    FUNCTION: AddOneItem(HTREEITEM, LPSTR, HTREEITEM, int)
*
*    PURPOSE: Inserts a tree view item in the specified place. 
*
****************************************************************************/

// This function fills out the TV_ITEM and TV_INSERTSTRUCT structures
// and adds the item to the tree view control.
HTREEITEM AddOneItem( HTREEITEM hParent, LPSTR szText, HTREEITEM hInsAfter, 
	int iImage, HWND hwndTree)
{
	HTREEITEM hItem;
	TV_ITEM tvI;
	TV_INSERTSTRUCT tvIns;

	// The pszText, iImage, and iSelectedImage are filled out.
	tvI.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvI.pszText = szText;
	tvI.cchTextMax = lstrlen(szText);
	tvI.iImage = iImage;
	tvI.iSelectedImage = iImage;

	tvIns.item = tvI;
	tvIns.hInsertAfter = hInsAfter;
	tvIns.hParent = hParent;
	
	// Insert the item into the tree.
	hItem = (HTREEITEM)SendMessage(hwndTree, TVM_INSERTITEM, 0, 
		(LPARAM)(LPTV_INSERTSTRUCT)&tvIns);

	return (hItem);

}

/****************************************************************************
* 
*    FUNCTION: BeginDrag(HWND, NM_TREEVIEW *)
*
*    PURPOSE: This function proceeses the beginning of a drag operation. 
*
****************************************************************************/
VOID BeginDrag(HWND hwndTree, NM_TREEVIEW *lItem)
{
	HIMAGELIST hIml;
	RECT rcl;
	
	// Create an image to use for dragging.
	hIml = TreeView_CreateDragImage(hwndTree, lItem->itemNew.hItem);

	// Get the bounding rectangle of the item being dragged.
	TreeView_GetItemRect(hwndTree, lItem->itemNew.hItem, &rcl, TRUE);

	// Start dragging the image.
	ImageList_BeginDrag(hIml, 0, lItem->ptDrag.x, lItem->ptDrag.y);

	// Hide the cursor.
	ShowCursor(FALSE);

	// Capture the mouse.
	SetCapture(GetParent(hwndTree));

	// Set a global flag that tells whether dragging is occurring.
	g_fDragging = TRUE;
}

/****************************************************************************
* 
*    FUNCTION: DropItem(HTREEITEM, HWND)
*
*    PURPOSE: This function proceeses the drop consequences. 
*
****************************************************************************/
VOID DropItem(HTREEITEM hDragItem, HWND hwnd)
{
	HTREEITEM hParent, hTarget;
	TV_ITEM tvTarget;
	int index;

	// Get the handle to the drop target.
	hTarget = TreeView_GetDropHilight(hwnd);
					
	// Get the parent of the drop target.
	hParent = TreeView_GetParent(hwnd, hTarget);

	// Get the image information.
	tvTarget.hItem = hTarget;
	tvTarget.mask = TVIF_IMAGE;
	TreeView_GetItem(hwnd, &tvTarget);
		
	// Get the index into the structure containing the text for the items.
	for (index = 0; index < NUM_HOUSES; index++)
	{
		if (rgHouseInfo[index].hItem == hDragItem)
			break;
	}

	if (index == NUM_HOUSES)
		index--;

	// Insert the new item back in.
	rgHouseInfo[index].hItem = AddOneItem( hParent, rgHouseInfo[index].szAddress, hTarget, 
						tvTarget.iImage, hwnd);

	// Delete the dragged item.
	TreeView_DeleteItem(hwnd, hDragItem);

	// Reset the drop target to NULL.
	TreeView_SelectDropTarget(hwnd, (HTREEITEM)NULL);
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
