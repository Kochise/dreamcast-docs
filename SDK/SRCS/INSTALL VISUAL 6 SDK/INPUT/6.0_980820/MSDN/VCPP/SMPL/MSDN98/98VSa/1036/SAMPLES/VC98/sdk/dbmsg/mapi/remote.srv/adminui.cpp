///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      ADMINUI.CPP
//
//  Description
//
//  Author
//      Irving De la Cruz
//
//  Revision: 1.7
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1995-1996 Microsoft Corporation. All rights reserved.
//
#include "ADMIN.H"

#define MAXCOLUMNS        7

extern "C"
{
    void WINAPI InitListViewColumns
                        ();
    BOOL WINAPI CalcStringEllipsis
                        (HDC                        hdc,
                         LPTSTR                     szString,
                         int                        cchMax,
                         UINT                       uColWidth);
    void WINAPI DrawItemColumn
                        (HDC                        hdc,
                         LPTSTR                     szText,
                         LPRECT                     prcClip);
};

UINT g_uColumns[MAXCOLUMNS] =
{
    100,
    125,
    175,
    75,
    175,
    80,
    80
};

void WINAPI InitListViewColumns()
{
    TCHAR achTemp[256];
    LV_COLUMN lvc;
    
    // Initialize the LV_COLUMN structure
    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.fmt = LVCFMT_LEFT;
    lvc.pszText = achTemp;

    // Add the columns
    for (int iCol = 0; iCol < MAXCOLUMNS; iCol++)
    {
        lvc.iSubItem = iCol;
        lvc.cx = g_uColumns[iCol];
        LoadString (ghInstance, IDS_COLUMN1 + iCol, achTemp, sizeof(achTemp));
        ListView_InsertColumn (ghListView, iCol, &lvc);
    }
}

#define TOP_CLEAR               30
#define V_BORDER_SIZE           5
#define H_BORDER_SIZE           3
#define CONTROL_HEIGHT          403
#define TREEVIEW_WIDTH          215
#define TREEVIEW_HEIGHT         CONTROL_HEIGHT
#define LISTVIEW_WIDTH          560
#define LISTVIEW_HEIGHT         CONTROL_HEIGHT

///////////////////////////////////////////////////////////////////////////////
//    CreateListView()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
BOOL WINAPI CreateListView (HWND hOwnerWnd, HIMAGELIST hImages)
{
    RECT rc;
    GetClientRect (hOwnerWnd, &rc);
    ghListView = CreateWindowEx (0,
                                 WC_LISTVIEW,
                                 TEXT(""),
                                 WS_VISIBLE | WS_CHILD | WS_BORDER |
                                 LVS_REPORT | LVS_OWNERDRAWFIXED |
                                 LVS_SHOWSELALWAYS | LVS_SINGLESEL |
                                 LVS_SORTASCENDING,
                                 V_BORDER_SIZE + TREEVIEW_WIDTH + V_BORDER_SIZE,
                                 TOP_CLEAR, 
                                 LISTVIEW_WIDTH,
                                 LISTVIEW_HEIGHT,
                                 hOwnerWnd,
                                 (HMENU)IDC_LISTVIEW, 
                                 ghInstance, 
                                 NULL);
    if (ghListView == NULL)
    {
        return FALSE;
    }
    ListView_SetImageList (ghListView, hImages, LVSIL_SMALL);
    InitListViewColumns();
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//    CreateTreeView()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
BOOL WINAPI CreateTreeView (HWND hOwnerWnd, HIMAGELIST hImages)
{
    ghTreeView = CreateWindowEx (0,
                                 WC_TREEVIEW,
                                 TEXT(""),
                                 WS_BORDER | WS_CHILD | WS_VISIBLE |
                                 TVS_HASLINES | TVS_HASBUTTONS |
                                 TVS_LINESATROOT | TVS_SHOWSELALWAYS |
                                 TVS_DISABLEDRAGDROP,
                                 V_BORDER_SIZE,
                                 TOP_CLEAR,
                                 TREEVIEW_WIDTH,
                                 TREEVIEW_HEIGHT,
                                 hOwnerWnd,
                                 (HMENU)IDC_TREEVIEW,
                                 ghInstance,
                                 NULL);
    if (ghTreeView == NULL)
    {
        return FALSE;
    }
    TreeView_SetImageList (ghTreeView, hImages, TVSIL_NORMAL);
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//    CreateStatusBar()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
BOOL WINAPI CreateStatusBar (HWND hOwnerWnd)
{
    ghStatusBar = CreateStatusWindow (WS_BORDER | WS_CHILD | WS_VISIBLE,
                                      TEXT("Ready"),
                                      hOwnerWnd,
                                      IDC_STATUSBAR);
    if (ghStatusBar == NULL)
    {
        return FALSE;
    }
    return TRUE;
}

// Define this enumaration for easier array indexing
enum
{
    SPACE_1,
    ADD_USER,
    ADD_DL,
    SPACE_2,
    SPACE_3,
    DELETE_OBJ,
    SPACE_4,
    SPACE_5,
    STOP_HAND,
    NUMBER_OF_TB_BUTTONS,
    NUMBER_OF_SEPARATORS = 5
};

///////////////////////////////////////////////////////////////////////////////
//    CreateToolBar()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
BOOL WINAPI CreateToolBar (HWND hOwnerWnd)
{
    // Initialize each of the buttons with the appropiate values
    TBBUTTON tbButton[NUMBER_OF_TB_BUTTONS] = { 0 };

    tbButton[SPACE_1].fsStyle   = TBSTYLE_SEP;
    tbButton[SPACE_2].fsStyle   = TBSTYLE_SEP;
    tbButton[SPACE_3].fsStyle   = TBSTYLE_SEP;
    tbButton[SPACE_4].fsStyle   = TBSTYLE_SEP;
    tbButton[SPACE_5].fsStyle   = TBSTYLE_SEP;

    tbButton[ADD_USER].iBitmap   = 0;
    tbButton[ADD_USER].idCommand = IDM_FILE_NEW_MAILBOX;
    tbButton[ADD_USER].fsState   = TBSTATE_ENABLED;
    tbButton[ADD_USER].fsStyle   = TBSTYLE_BUTTON;

    tbButton[ADD_DL].iBitmap      = 1;
    tbButton[ADD_DL].idCommand    = IDM_FILE_NEW_DISTRIBUTIONLIST;
    tbButton[ADD_DL].fsState      = TBSTATE_ENABLED;
    tbButton[ADD_DL].fsStyle      = TBSTYLE_BUTTON;

    tbButton[DELETE_OBJ].iBitmap  = 2;
    tbButton[DELETE_OBJ].idCommand= IDM_FILE_DELETE;
    tbButton[DELETE_OBJ].fsState  = TBSTATE_ENABLED;
    tbButton[DELETE_OBJ].fsStyle  = TBSTYLE_BUTTON;

    tbButton[STOP_HAND].iBitmap  = 3;
    tbButton[STOP_HAND].idCommand= IDC_CANCEL_REMOTE_CALL;
    tbButton[STOP_HAND].fsState  = TBSTATE_INDETERMINATE;
    tbButton[STOP_HAND].fsStyle  = TBSTYLE_BUTTON;

    // Create the toolbar with the most commonly used functions
    ghToolBar = CreateToolbarEx (hOwnerWnd,
                                 WS_VISIBLE | WS_CHILD | WS_BORDER | TBSTYLE_TOOLTIPS,
                                 IDC_TOOLBAR,
                                 // The number of images is the number of
                                 // buttons minus the separators
                                 NUMBER_OF_TB_BUTTONS - NUMBER_OF_SEPARATORS,
                                 ghInstance,
                                 IDB_TOOLBAR,
                                 tbButton,
                                 NUMBER_OF_TB_BUTTONS,
                                 16, 16, 16, 32,
                                 sizeof(TBBUTTON));
    if (NULL == ghToolBar)
    {
        return FALSE;
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//    UpdateHeaderWidth()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
void WINAPI UpdateHeaderWidth (HWND hWndHeader, int iItem)
{
    HD_ITEM hdi;
    // Get the column width from the control
    hdi.mask = HDI_WIDTH;
    if (Header_GetItem (hWndHeader, iItem, &hdi))
    {
        g_uColumns[iItem] = hdi.cxy;
    }
    // Force the ListView control to repaint
    InvalidateRect (ghListView, NULL, TRUE);
}

///////////////////////////////////////////////////////////////////////////////
//    DrawListViewItem()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
void WINAPI DrawListViewItem (LPDRAWITEMSTRUCT pDIS)
{
    TCHAR szBuffer[512];
    LV_ITEM lvi;
    int cxImage = 0, cyImage = 0;
    UINT uFirstColWidth;
    RECT rcClip;
    int iColumn = 1;
    UINT uiFlags = ILD_TRANSPARENT;

    // Get the item image to be displayed
    lvi.mask = LVIF_IMAGE | LVIF_STATE | LVIF_TEXT;
    lvi.iItem = pDIS->itemID;
    lvi.iSubItem = 0;
    lvi.pszText = szBuffer;
    lvi.cchTextMax = 512;
    ListView_GetItem (pDIS->hwndItem, &lvi);

    // Check to see if this item is selected
    if (pDIS->itemState & ODS_SELECTED)
    {
        // Set the text background and foreground colors
        SetTextColor (pDIS->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
        SetBkColor (pDIS->hDC, GetSysColor(COLOR_HIGHLIGHT));

        // Also add the ILD_BLEND50 so the images come out selected
        uiFlags |= ILD_BLEND50;
    }
    else
    {
        // Set the text background and foreground colors to the standard window colors
        SetTextColor (pDIS->hDC, GetSysColor(COLOR_WINDOWTEXT));
        SetBkColor (pDIS->hDC, GetSysColor(COLOR_WINDOW));
    }

    // Get the image list and draw the image
    ImageList_Draw (g_hImages,
                    lvi.iImage,
                    pDIS->hDC,
                    pDIS->rcItem.left,
                    pDIS->rcItem.top,
                    uiFlags);
    // Find out how big the image we just drew was
    ImageList_GetIconSize (g_hImages, &cxImage, &cyImage);
    
    // Calculate the width of the first column after the image width.  If
    // There was no image, then cxImage will be zero.
    uFirstColWidth = g_uColumns[0] - cxImage;

    // Set up the new clipping rect for the first column text and draw it
    rcClip.left = pDIS->rcItem.left + cxImage;
    rcClip.right = pDIS->rcItem.left + g_uColumns[0];
    rcClip.top = pDIS->rcItem.top;
    rcClip.bottom = pDIS->rcItem.bottom;

    DrawItemColumn (pDIS->hDC, szBuffer, &rcClip);
    szBuffer[0] = 0;

    lvi.mask = LVIF_TEXT;
    lvi.iSubItem++;
    ListView_GetItem (pDIS->hwndItem, &lvi);
    rcClip.left = rcClip.right;
    rcClip.right = rcClip.left + g_uColumns[1];
    DrawItemColumn(pDIS->hDC, szBuffer, &rcClip);
    szBuffer[0] = 0;

    rcClip.left = rcClip.right;
    rcClip.right = rcClip.left + g_uColumns[2];
    lvi.iSubItem++;
    ListView_GetItem (pDIS->hwndItem, &lvi);
    DrawItemColumn(pDIS->hDC, szBuffer, &rcClip);
    szBuffer[0] = 0;

    rcClip.left = rcClip.right;
    rcClip.right = rcClip.left + g_uColumns[3];
    lvi.iSubItem++;
    ListView_GetItem (pDIS->hwndItem, &lvi);
    DrawItemColumn(pDIS->hDC, szBuffer, &rcClip);
    szBuffer[0] = 0;

    rcClip.left = rcClip.right;
    rcClip.right = rcClip.left + g_uColumns[4];
    lvi.iSubItem++;
    ListView_GetItem (pDIS->hwndItem, &lvi);
    DrawItemColumn(pDIS->hDC, szBuffer, &rcClip);
    szBuffer[0] = 0;

    rcClip.left = rcClip.right;
    rcClip.right = rcClip.left + g_uColumns[5];
    lvi.iSubItem++;
    ListView_GetItem (pDIS->hwndItem, &lvi);
    DrawItemColumn(pDIS->hDC, szBuffer, &rcClip);
    szBuffer[0] = 0;

    rcClip.left = rcClip.right;
    rcClip.right = rcClip.left + g_uColumns[6];
    lvi.iSubItem++;
    ListView_GetItem (pDIS->hwndItem, &lvi);
    DrawItemColumn(pDIS->hDC, szBuffer, &rcClip);
    szBuffer[0] = 0;

    // If we changed the colors for the selected item, undo it
    if (pDIS->itemState & ODS_SELECTED)
    {
        // Set the text background and foreground colors
        SetTextColor (pDIS->hDC, GetSysColor(COLOR_WINDOWTEXT));
        SetBkColor (pDIS->hDC, GetSysColor(COLOR_WINDOW));
    }

    // If the item is focused, now draw a focus rect around the entire row
    if (pDIS->itemState & ODS_FOCUS)
    {
        // Adjust the left edge to exclude the image
        rcClip = pDIS->rcItem;
        rcClip.left += cxImage;

        // Draw the focus rect
        DrawFocusRect (pDIS->hDC, &rcClip);
    }
}

///////////////////////////////////////////////////////////////////////////////
//    DrawItemColumn()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
void WINAPI DrawItemColumn (HDC hdc, LPTSTR szText, LPRECT prcClip)
{
    TCHAR szString[256];
    // Check to see if the string fits in the clip rect.  If not, truncate
    // the string and add "...".
    lstrcpy(szString, szText);
    CalcStringEllipsis (hdc, szString, 256, prcClip->right - prcClip->left);
    ExtTextOut (hdc,
                prcClip->left + 2,
                prcClip->top + 1,
                ETO_CLIPPED | ETO_OPAQUE,
                prcClip,
                szString,
                lstrlen(szString),
                NULL);
}

///////////////////////////////////////////////////////////////////////////////
//    CalcStringEllipsis()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
BOOL WINAPI CalcStringEllipsis (HDC     hdc,
                                LPTSTR  szString,
                                int     cchMax,
                                UINT    uColWidth)
{
    const TCHAR szEllipsis[] = TEXT("...");
    SIZE   sizeString;
    SIZE   sizeEllipsis;
    int    cbString;
    LPTSTR lpszTemp;
    BOOL   fSuccess = FALSE;
    
    // Adjust the column width to take into account the edges
    uColWidth -= 4;
    __try
    {
        // Allocate a string for us to work with.  This way we can mangle the
        // string and still preserve the return value
        lpszTemp = (LPTSTR)HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, cchMax);
        if (!lpszTemp)
        {
            __leave;
        }
        lstrcpy (lpszTemp, szString);

        // Get the width of the string in pixels
        cbString = lstrlen(lpszTemp);
        if (!GetTextExtentPoint32 (hdc, lpszTemp, cbString, &sizeString))
        {
            __leave;
        }

        // If the width of the string is greater than the column width shave
        // the string and add the ellipsis
        if ((ULONG)sizeString.cx > uColWidth)
        {
            if (!GetTextExtentPoint32 (hdc,
                                       szEllipsis,
                                       lstrlen(szEllipsis),
                                       &sizeEllipsis))
            {
                __leave;
            }

            while (cbString > 0)
            {
                lpszTemp[--cbString] = 0;
                if (!GetTextExtentPoint32 (hdc, lpszTemp, cbString, &sizeString))
                {
                    __leave;
                }

                if ((ULONG)(sizeString.cx + sizeEllipsis.cx) <= uColWidth)
                {
                    // The string with the ellipsis finally fits, now make sure
                    // there is enough room in the string for the ellipsis
                    if (cchMax >= (cbString + lstrlen(szEllipsis)))
                    {
                        // Concatenate the two strings and break out of the loop
                        lstrcat (lpszTemp, szEllipsis);
                        lstrcpy (szString, lpszTemp);
                        fSuccess = TRUE;
                        __leave;
                    }
                }
            }
        }
        else
        {
            // No need to do anything, everything fits great.
            fSuccess = TRUE;
        }
    }
    __finally
    {
        // Free the memory
        HeapFree (GetProcessHeap(), 0, (LPVOID)lpszTemp);
        return fSuccess;
    }
}

///////////////////////////////////////////////////////////////////////////////
//    ErrorHandler()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
void WINAPI ErrorHandler (HWND hOwnerWnd, HRESULT hError)
{
    LPTSTR szSystemMessage = NULL;
    TCHAR achBuffer[1024];
    DWORD dwSystemError;
    // If the facility is RPC remove it before calling FormatMessage(). That
    // Win32 API does not recognizes the facility.
    if (HRESULT_FACILITY(hError) == FACILITY_RPC)
    {
        dwSystemError = LOWORD(hError);
    }
    else
    {
        dwSystemError = hError;
    }
    // Get an error description from the system
    DWORD dwChars = FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 
                                   NULL, 
                                   dwSystemError, 
                                   MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), 
                                   (LPTSTR)&szSystemMessage,
                                   0, 
                                   NULL);
    // Check to see if FormatMessage() returned us an error
    if (0 == dwChars)
    {
        szSystemMessage = TEXT("Generic Error");
    }
    else
    {
        LPTSTR pStr = &szSystemMessage[lstrlen (szSystemMessage)];
        while ('\r' != *pStr)
        {
            pStr--;
        }
        *pStr = 0;
    }
    ASSERT (dwChars < 1024);
    // Add the error code to the string returned and then show it.
    switch (HRESULT_FACILITY(hError))
    {
        case FACILITY_WIN32 :
            wsprintf (achBuffer,
                      TEXT("%s (Win32 Error %d)"),
                      szSystemMessage,
                      LOWORD(hError));
            break;
        case FACILITY_STORAGE :
            wsprintf (achBuffer,
                      TEXT("%s (IStorage Error %08X)"),
                      szSystemMessage,
                      hError);
            break;
        case FACILITY_ITF :
            wsprintf (achBuffer,
                      TEXT("%s (Interface Error %08X)"),
                      szSystemMessage,
                      hError);
            break;
        case FACILITY_RPC :
            wsprintf (achBuffer,
                      TEXT("%s (RPC Error %d - %08X)"),
                      szSystemMessage,
                      LOWORD(hError),
                      hError);
            break;
        default :
            wsprintf (achBuffer,
                      TEXT("%s (Unknown Facility(%d) Error %d - %08X)"),
                      szSystemMessage,
                      HRESULT_FACILITY(hError),
                      hError,
                      hError);
            break;
    }
    if (dwChars)
    {
        LocalFree ((HLOCAL)szSystemMessage);
    }
    MessageBox (hOwnerWnd, achBuffer, TEXT("WINDS Administrator - Error"), MB_ICONSTOP | MB_OK);
}

// End of file for ADMINUI.CPP
