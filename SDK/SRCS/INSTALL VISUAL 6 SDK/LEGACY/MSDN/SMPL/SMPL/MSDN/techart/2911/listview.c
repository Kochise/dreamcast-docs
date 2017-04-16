/****************************************************************************
*
*
*    PROGRAM: ListView.c
*
*    PURPOSE: Creates and manages the list view control for ChicoApp
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <commctrl.h>   // includes the common control header
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "chicoapp.h"
#include "listview.h"


 
/****************************************************************************
* 
*    FUNCTION: LV_CreateListView(HWND, HINSTANCE, int, HOUSEINFO *)
*
*    PURPOSE:  Creates the list view window and initializes it
*
****************************************************************************/
HWND LV_CreateListView (HWND hWndParent, HINSTANCE hInst, int NumHouses,
    HOUSEINFO *pHouse)
{
	HWND hWndList;      // handle to list view window
	RECT rcl;           // rectangle for setting size of window
	HICON hIcon;        // handle to an icon
	int index;          // index used in for loops
	HIMAGELIST hSmall, hLarge; // handles to image lists
	LV_COLUMN lvC;      // list view column structure
	char szText[MAX_ITEMLEN];    // place to store some text
    int iWidth;         // column width

	// Get the size and position of the parent window.
	GetClientRect(hWndParent, &rcl);

    iWidth = (rcl.right - rcl.left) - ((rcl.right - rcl.left)/4);

    // Create the list view window, make it 3/4 the width of the
    // parent window and account for the status bar and toolbar.
	hWndList = CreateWindowEx( 0L,
		WC_LISTVIEW,                // list view class
		"",                         // no default text
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | WS_EX_CLIENTEDGE,
        (rcl.right - rcl.left)/4, 27,
        iWidth, rcl.bottom - rcl.top - 42,
		hWndParent,
		(HMENU) ID_LISTVIEW,
		hInst,
		NULL );

	if (hWndList == NULL )
		return NULL;

	// First, initialize the image lists you will need.
    // Create image lists for the small and the large icons.
    // TRUE specifies small icons; FALSE specifies large.
	hSmall = ImageList_Create( BITMAP_WIDTH, BITMAP_HEIGHT, TRUE, 1, 0 );
	hLarge = ImageList_Create( LG_BITMAP_WIDTH, LG_BITMAP_HEIGHT, FALSE, 1, 0 );

 	// Load the icons and add them to the image lists
    hIcon = LoadIcon ( hInst, MAKEINTRESOURCE(HOUSE_ICON));
    if ((ImageList_AddIcon(hSmall, hIcon) == -1) ||
        (ImageList_AddIcon(hLarge, hIcon) == -1))
    {
        MessageBox(NULL, "ImageList_AddIcon failed!", NULL, MB_OK);
        return NULL;
    }

	// Associate the image lists with the list view.
	ListView_SetImageList(hWndList, hSmall, LVSIL_SMALL);
	ListView_SetImageList(hWndList, hLarge, LVSIL_NORMAL);

	// Initialize the LV_COLUMN structure.
	// The mask specifies that the fmt, cx, pszText, and isubitem
	// members of the structure are valid.
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align column
    lvC.cx = iWidth / NUM_COLUMNS + 1;            // width of column in pixels
	lvC.pszText = szText;

	// Add the columns.
    for (index = 0; index < NUM_COLUMNS; index++)
	{
		lvC.iSubItem = index;
		LoadString( hInst, 
					IDS_ADDRESS + index,
					szText,
					sizeof(szText));
		if (ListView_InsertColumn(hWndList, index, &lvC) == -1)
			return NULL;
	}

	return hWndList;
}

/****************************************************************************
*
*    FUNCTION: LV_AddOneItem(HWND, int, HOUSEINFO *)
*
*    PURPOSE: Inserts a list view item
*
****************************************************************************/
BOOL LV_AddItem(HWND hWndList, int index, HOUSEINFO *pHouse )
{
	LV_ITEM lvI;        // List view item structure
	int iSubItem;       // index for inserting sub items

    // Fill in the LV_ITEM structure 
	// The mask specifies the the pszText, iImage, lParam and state
	// members of the LV_ITEM structure are valid.
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
    lvI.state = 0;      
    lvI.stateMask = 0;  
    lvI.iItem = index;
    lvI.iSubItem = 0;

    // The parent window is responsible for storing the text. The List view
    // window will send a LVN_GETDISPINFO when it needs the text to display/
    lvI.pszText = LPSTR_TEXTCALLBACK; 
    lvI.cchTextMax = MAX_ITEMLEN;
    lvI.iImage = 0;
    lvI.lParam = (LPARAM)pHouse;

    if (ListView_InsertItem(hWndList, &lvI) == -1)
        return FALSE;

    // set the text for each of the columns for report view
    for (iSubItem = 1; iSubItem < NUM_COLUMNS; iSubItem++)
    {
        ListView_SetItemText( hWndList,
				index,
				iSubItem,
				LPSTR_TEXTCALLBACK);
	}
    return TRUE;
}

/****************************************************************************
*
*    FUNCTION: LV_RemoveOneItem(HWND, int)
*
*    PURPOSE: Removes one list view item
*
****************************************************************************/
VOID LV_RemoveOneItem(HWND hwndList, int index)
{

    ListView_DeleteItem( hwndList, index);
}


/****************************************************************************
*
*    FUNCTION: LV_RemoveAllItems(HWND)
*
*    PURPOSE: Removes all items in a list view 
*
****************************************************************************/
VOID LV_RemoveAllItems( HWND hwndList)
{
    ListView_DeleteAllItems( hwndList);
}

/****************************************************************************
*
*    FUNCTION: ChangeView(HWND, WORD)
*
*    PURPOSE:  Changes the current view for the list view window
*
****************************************************************************/
VOID LV_ChangeView( HWND hwndLV, WORD wCommand)
{
    DWORD dwStyle;

    switch (wCommand)
    {
        case IDM_LARGEICON:
            dwStyle = GetWindowLong(hwndLV, GWL_STYLE);
					
            if ((dwStyle & LVS_TYPEMASK) != LVS_ICON)
                SetWindowLong(hwndLV, GWL_STYLE,  
                   (dwStyle & ~LVS_TYPEMASK) | LVS_ICON);
            break;


        case IDM_SMALLICON:
            dwStyle = GetWindowLong(hwndLV, GWL_STYLE);
                
            if ((dwStyle & LVS_TYPEMASK) != LVS_SMALLICON)
                SetWindowLong(hwndLV, GWL_STYLE,
                   (dwStyle & ~LVS_TYPEMASK) | LVS_SMALLICON);
            break;

        case IDM_LISTVIEW:
            dwStyle = GetWindowLong(hwndLV, GWL_STYLE);

            if ((dwStyle & LVS_TYPEMASK) != LVS_LIST)
                SetWindowLong(hwndLV, GWL_STYLE,
                   (dwStyle & ~LVS_TYPEMASK) | LVS_LIST);
            break;

        case IDM_REPORTVIEW:
            dwStyle = GetWindowLong(hwndLV, GWL_STYLE);

            if ((dwStyle & LVS_TYPEMASK) != LVS_REPORT)
                SetWindowLong(hwndLV, GWL_STYLE,
                   (dwStyle & ~LVS_TYPEMASK) | LVS_REPORT);
            break;
    }
}

/****************************************************************************
* 
*    FUNCTION: LV_NotifyHandler(HWND, UINT, UINT, LONG)
*
*    PURPOSE: This function is the handler for the WM_NOTIFY that is 
*    sent to the parent of the list view window.
*
****************************************************************************/
LRESULT LV_NotifyHandler( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
	HINSTANCE hInst)
{
	LV_DISPINFO *pLvdi = (LV_DISPINFO *)lParam;
	NM_LISTVIEW *pNm = (NM_LISTVIEW *)lParam;
	HOUSEINFO *pHouse = (HOUSEINFO *)(pLvdi->item.lParam);
	static char szText[TEMP_LEN];

	if (wParam != ID_LISTVIEW)
		return 0L;

	switch(pLvdi->hdr.code)
	{

		case LVN_GETDISPINFO:
			switch (pLvdi->item.iSubItem)
			{
				case 0:     // address
					pLvdi->item.pszText = pHouse->szAddress;
					break;

				case 1:     // city
					pLvdi->item.pszText = pHouse->szCity;
					break;

				case 2:     // price
					sprintf(szText, "$%u", pHouse->iPrice);
					pLvdi->item.pszText = szText;
					break;

				case 3:     // number of bedrooms
					sprintf(szText, "%u", pHouse->iBeds);
					pLvdi->item.pszText = szText;
					break;

				case 4:     // number of bathrooms
					sprintf(szText, "%u", pHouse->iBaths);
					pLvdi->item.pszText = szText;
					break;

				default:
					break;
			}
			break;

		case LVN_COLUMNCLICK:
			// The user clicked a column header; sort by this criterion.
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
				iResult = lstrcmpi(lpStr1, lpStr2);
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

