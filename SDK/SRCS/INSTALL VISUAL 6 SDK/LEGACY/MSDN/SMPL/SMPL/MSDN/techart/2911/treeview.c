/****************************************************************************
*
*
*    PROGRAM: TreeView.c
*
*    PURPOSE: Creates and manages the tree view window in ChicoApp
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <commctrl.h>   // includes the common control header
#include <string.h>
#include "Chicoapp.h"
#include "treeview.h"



/****************************************************************************
* 
*    FUNCTION: TV_CreateTreeView(HWND, HINSTANCE, int, CITYINFO *)
*
*    PURPOSE:  Creates the tree view window and initializes it
*
****************************************************************************/
HWND TV_CreateTreeView (HWND hWndParent, HINSTANCE hInst, int NumCities, CITYINFO *pCity)
{
	HWND hwndTree;      // handle to tree view window
	RECT rcl;           // rectangle for setting size of window
	HBITMAP hBmp;       // handle to a bitmap
	HIMAGELIST hIml;    // handle to image list

	// Get the size and position of the parent window.
	GetClientRect(hWndParent, &rcl);

    // Create the tree view window, make it 1/4 the width of the parent
    // window, and account for the status bar and toolbar.
	hwndTree = CreateWindowEx(
        0L,
		WC_TREEVIEW,                // window class
		"",                         // no default text
		WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES |
		   TVS_HASBUTTONS | TVS_LINESATROOT | WS_EX_CLIENTEDGE,
        0, 27,						// x, y
        (rcl.right - rcl.left)/4,	// cx
        rcl.bottom - rcl.top - 45,	// cy
		hWndParent,					// parent
		(HMENU) ID_TREEVIEW,		// ID
		hInst,						// instance
		NULL );

	if (hwndTree == NULL )
    {
        MessageBox(NULL, "CreateWindow of TreeView failed!", NULL, MB_OK);
		return NULL;
    }

	// First create the image list you will need.
	hIml = ImageList_Create( BITMAP_WIDTH, BITMAP_HEIGHT, FALSE, 2, 10 );

    if (hIml == NULL)
        MessageBox(NULL, "ImageList_Create failed!", NULL, MB_OK);

	// Load the bitmaps and add them to the image list.
    hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(FORSALE_BMP));
	idxForSale = ImageList_Add(hIml, hBmp, NULL);
    hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(CITY_BMP));
    idxCity = ImageList_Add(hIml, hBmp, NULL);
    hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(SELCITY_BMP));
    idxSelect = ImageList_Add(hIml, hBmp, NULL);

	// Be sure that all the bitmaps were added.
    if (ImageList_GetImageCount(hIml) != 3)
    {
        MessageBox(NULL, "TreeView image list not loaded!", NULL, MB_OK);
        return FALSE;
    }

	// Associate the image list with the tree view control.
	TreeView_SetImageList(hwndTree, hIml, idxForSale);

    // Initialize the tree view control by adding "Houses For Sale."
    TV_InitTreeView(hInst, hwndTree);

	return hwndTree;
}

/****************************************************************************
* 
*    FUNCTION: TV_InitTreeView(HINSTANCE)
*
*    PURPOSE:  Initializes the tree view window 
*
****************************************************************************/
VOID TV_InitTreeView(HINSTANCE hInst, HWND hwndTree)
{
    char szText[MAX_CITY];

    // Add the root item "Houses for Sale"
	LoadString(hInst, IDS_FORSALE, szText, MAX_LEN);
    hTPrev = (HTREEITEM)TVI_ROOT;
    iImage = idxForSale;
    hParent = (HTREEITEM)NULL;
    iSelect = idxForSale;
    hTRoot = TV_AddOneItem(szText, hwndTree, -1 );

    // reset the previous and image
    hParent = hTRoot;
    hTPrev = (HTREEITEM)TVI_FIRST;
    iImage = idxCity;
    iSelect = idxSelect;
}

/***************************************************************************
* 
*    FUNCTION: TV_AddOneItem(HTREEITEM, LPSTR, HWND)
*
*    PURPOSE: Inserts a tree view item in the specified place. 
*
****************************************************************************/

HTREEITEM TV_AddOneItem( LPSTR szText, HWND hwndTree, int index)
{
	HTREEITEM hItem;
	TV_ITEM tvI;
	TV_INSERTSTRUCT tvIns;

	tvI.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvI.pszText = szText;
	tvI.cchTextMax = lstrlen(szText);
	tvI.iImage = iImage;
    tvI.iSelectedImage = iSelect;
    tvI.lParam = index;             // save the index of the item

	tvIns.item = tvI;
    tvIns.hInsertAfter = hTPrev;
	tvIns.hParent = hParent;
	
	hItem = (HTREEITEM)SendMessage(hwndTree, TVM_INSERTITEM, 0, 
		(LPARAM)(LPTV_INSERTSTRUCT)&tvIns);

    if (hItem == NULL)
        MessageBox(NULL, "TVM_INSERTITEM failed", NULL, MB_OK);

	return (hItem);

}

/***************************************************************************
* 
*    FUNCTION: TV_RemoveAllItems(HWND)
*
*    PURPOSE: Removes all items from a tree view. 
*
****************************************************************************/

VOID TV_RemoveAllItems(HWND hwndTree)
{
    TreeView_DeleteAllItems(hwndTree);
}

/****************************************************************************
* 
*    FUNCTION: TV_NotifyHandler(HWND, UINT, UINT, LONG)
*
*    PURPOSE: This function is the handler for the WM_NOTIFY that is 
*    sent to the parent of the tree view window.
*
****************************************************************************/
LRESULT TV_NotifyHandler( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
    LISTINFO *pList)
{
    static NM_TREEVIEW *pNm;

    pNm = (NM_TREEVIEW *)lParam;

    if (wParam != ID_TREEVIEW)
		return 0L;

    switch(pNm->hdr.code)
	{
        case TVN_SELCHANGED:
            pList->iSelected = (int)(pNm->itemNew.lParam);

            return 1;
            break;

		default:
			break;
	}
	return 0L;
}
