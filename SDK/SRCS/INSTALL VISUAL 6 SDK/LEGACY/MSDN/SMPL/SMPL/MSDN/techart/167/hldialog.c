/*    PortTool v2.2     hldialog.c          */

/*    PortTool v2.2     hldialog.c          */

#include "hlsample.h"
#include "hierdraw.h"

#include <math.h>


/*    PortTool v2.2     4/1/1993    1:2          */
/*      Found   : FAR          */
/*      Issue   : Win32 is non-segmented, thus FAR == NEAR == nothing!          */
BOOL FAR PASCAL _export HLDialog_DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);


/*    PortTool v2.2     4/1/1993    1:2          */
/*      Found   : FAR          */
/*      Issue   : Win32 is non-segmented, thus FAR == NEAR == nothing!          */
VOID HLDialog_OnDrawItem(HWND hwnd, DRAWITEMSTRUCT FAR* lpDrawItem);
BOOL HLDialog_OnInitDialog(HWND hwndDlg, HWND hwndFocus, LPARAM lParam);
VOID HLDialog_OnCommand(HWND hwndDlg, UINT id, HWND hwndCtl, UINT code);
VOID ActionItem(HWND hWndList, DWORD dwData, WORD wItemNum);


#define ROWS 4
#define COLS 3

HEIRDRAWSTRUCT HierDrawStruct;

VOID HLSystemColorChange()
{
    HierDraw_DrawInit(_hInstance,     // Instance
                  IDR_LISTICONS,  // Bitmap ID
                  ROWS,           // Rows
                  COLS,           // Columns
                  TRUE,           // Loins
                  &HierDrawStruct,// HierDrawStruct
                  FALSE           // Initialize Open Folders
                  );

}

int HLDialog_Do(HWND hwndOwner)
{
    int result;
    DLGPROC lpfndp;

    //
    // Init the Hier Draw stuff.
    // Need to do this here so we have a value for WM_MEASUREITEM
    // which is sent before the WM_INITDIALOG message
    //
    HierDraw_DrawInit(_hInstance,     // Instance
                      IDR_LISTICONS,  // Bitmap ID
                      ROWS,           // Rows
                      COLS,           // Columns
                      TRUE,           // Loins
                      &HierDrawStruct,// HierDrawStruct
                      TRUE            // Initialize Open Folders
                      );


/*    PortTool v2.2     4/1/1993    1:2          */
/*      Found   : FAR          */
/*      Issue   : Win32 is non-segmented, thus FAR == NEAR == nothing!          */
    lpfndp = (DLGPROC)MakeProcInstance((FARPROC)HLDialog_DlgProc, _hInstance);
 
    result = DialogBox(_hInstance,
            MAKEINTRESOURCE(IDHEIRDLG),
            hwndOwner, lpfndp);


/*    PortTool v2.2     4/1/1993    1:2          */
/*      Found   : FAR          */
/*      Issue   : Win32 is non-segmented, thus FAR == NEAR == nothing!          */
    FreeProcInstance((FARPROC)lpfndp);
    HierDraw_DrawTerm(&HierDrawStruct);

    return result;
}


/*    PortTool v2.2     4/1/1993    1:2          */
/*      Found   : FAR          */
/*      Issue   : Win32 is non-segmented, thus FAR == NEAR == nothing!          */
BOOL FAR PASCAL _export HLDialog_DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_INITDIALOG:
             HLDialog_OnInitDialog(hwndDlg, (HWND)(wParam), lParam);
             return TRUE;
        break;

        case WM_SETFONT:
           {
             //
             // Set the Text Height
             //
             HierDraw_DrawSetTextHeight(GetDlgItem(hwndDlg, IDLIST),
                                        (HFONT)wParam, &HierDrawStruct);

           }
        break;



/*    PortTool v2.2     4/1/1993    1:2          */
/*      Found   : WM_COMMAND          */
/*      Issue   : wParam/lParam repacking, refer to tech. ref. for details          */
        case WM_COMMAND:

/*    PortTool v2.2     4/1/1993    1:2          */
/*      Found   : LOWORD          */
/*      Issue   : Check if LOWORD target is 16- or 32-bit          */
             HLDialog_OnCommand(hwndDlg, (int)(wParam), (HWND)LOWORD(lParam), (UINT)HIWORD(lParam));
             return TRUE;
        break;

        case WM_DRAWITEM:

/*    PortTool v2.2     4/1/1993    1:2          */
/*      Found   : FAR          */
/*      Issue   : Win32 is non-segmented, thus FAR == NEAR == nothing!          */
             HLDialog_OnDrawItem(hwndDlg, (DRAWITEMSTRUCT FAR*)(lParam));
             return TRUE;
        break;

        case WM_MEASUREITEM:

/*    PortTool v2.2     4/1/1993    1:2          */
/*      Found   : FAR          */
/*      Issue   : Win32 is non-segmented, thus FAR == NEAR == nothing!          */
             HierDraw_OnMeasureItem(hwndDlg, (MEASUREITEMSTRUCT FAR*)(lParam), &HierDrawStruct);
             return TRUE;
        break;


/*    PortTool v2.2     4/1/1993    1:2          */
/*      Found   : WM_CHARTOITEM          */
/*      Issue   : wParam/lParam repacking, refer to tech. ref. for details          */
        case WM_CHARTOITEM:
             if ( wParam == VK_RETURN ) {
                WORD   wItemNum;
                DWORD  dwData;
                HWND   hwndCtl;

                hwndCtl = GetDlgItem(hwndDlg, IDLIST);

/*    PortTool v2.2     4/1/1993    1:2          */
/*      Found   : (WORD)          */
/*      Issue   : Check if incorrect cast of 32-bit value          */
/*      Suggest : Replace 16-bit data types with 32-bit types where possible          */
/*      Help available, search for WORD in WinHelp file API32WH.HLP          */
                wItemNum = (WORD)  SendMessage(hwndCtl, LB_GETCURSEL, 0, 0L);
                dwData   = (DWORD) SendMessage(hwndCtl, LB_GETITEMDATA, wItemNum, 0L);
                ActionItem(hwndCtl, dwData, wItemNum);
                return TRUE;
             }
        break;

    }
    return FALSE;
}



/*    PortTool v2.2     4/1/1993    1:2          */
/*      Found   : FAR          */
/*      Issue   : Win32 is non-segmented, thus FAR == NEAR == nothing!          */
VOID HLDialog_OnDrawItem(HWND hwnd, DRAWITEMSTRUCT FAR* lpDrawItem)
{
   char  szText[128];
   DWORD dwData;
   int   nLevel;
   int   nTempLevel;
   int   nRow;
   int   nColumn;
   DWORD dwConnectLevel = 0L;
   DWORD dwMask;
   DWORD dwLevelMask;
   DWORD dwLevelAdd;

   dwData = lpDrawItem->itemData;
   wsprintf(szText,"Item Number: %ld",dwData);


   //
   // Select the correct icon, open folder, closed folder, or document.
   //
   // Can this item be opened ?
   //
   if ( dwData % 10 == 0 ) {
      //
      // Is it open ?
      //
      if ( HierDraw_IsOpened(&HierDrawStruct, dwData) ) {
         nColumn = 1;
      }
      else {
         nColumn = 0;
      }
   }
   else {
      nColumn = 2;
   }

   //
   // Select the correct level/color
   // This sample changes the row ( color ) just because it can.
   //
   if ( dwData % 1000 == 0 ) {
      nLevel = 0;
      nRow = 0;
   }
   else if ( dwData % 100 == 0 ) {
      nLevel = 1;
      nRow = 1;
   }
   else if ( dwData % 10 == 0 ) {
      nLevel = 2;
      nRow = 2;
   }
   else {
      nLevel = 3;
      nRow = 3;
   }

   //
   // Figure out which connecting lines are needed.
   // If this item is the last kid or one it parents
   // is a last kid, then it does not need a connector at that level
   //
   if ( nLevel == 0 ) {
      //
      // Level 0 items never have connectors.
      dwConnectLevel = 0L;
   }
   else {
      //
      // Check parents ( grand, great, ... ) to see it they are last children
      //
      // Start at parent ( 1 level up from here ).
      //
      nTempLevel = nLevel-1;
      
      //
      // First bit to set ( or not );
      //
      dwMask = (DWORD) pow(2,nLevel-1);
      
      //
      // Some stuff just for this example
      //
      dwLevelMask = (DWORD) pow(10,4-nLevel);
      dwLevelAdd  = dwLevelMask / 10;

      //
      // While were are not at level 0
      //
      while ( nTempLevel >= 0 ) {
         //
         // Last kid at this level ?
         //
         // The ugly calculation is just for this sample 
         //
         if ( ((dwData+dwLevelAdd)%dwLevelMask) == 0 ) {
            //
            // Last kid so no connection at this level
            //
            dwConnectLevel &= ~dwMask;
         }
         else {
            //
            // NOT Last kid so connection at this level
            //
            dwConnectLevel |= dwMask;
         }

         //
         // Sutff for this sample, figure out next parent
         dwLevelAdd  *= 10;
         dwLevelMask *= 10;
         dwData = dwData-(dwData%dwLevelAdd);
         
         //
         // Move mask bit over 
         //
         dwMask /= 2;
         
         //
         // Move up level
         //
         nTempLevel--;
      }
   }
   
   //
   // All set to call drawing function.
   // 
   HierDraw_OnDrawItem(hwnd,
                       lpDrawItem,
                       nLevel,
                       dwConnectLevel,
                       szText,
                       nRow,
                       nColumn,
                       &HierDrawStruct);
   return;
}


BOOL HLDialog_OnInitDialog(HWND hwndDlg, HWND hwndFocus, LPARAM lParam)
{
    int  i;
    HWND hwndList = GetDlgItem(hwndDlg, IDLIST);

    for ( i = 1000; i < 9000; i+=1000 ) {
       SendMessage(hwndList, LB_ADDSTRING, 0, (LONG)i);
    }

    return TRUE;
}

VOID HLDialog_OnCommand(HWND hwndDlg, UINT id, HWND hwndCtl, UINT code)
{
    HWND hwndOK     = GetDlgItem(hwndDlg, IDOK);
    HWND hwndCancel = GetDlgItem(hwndDlg, IDCANCEL);
    WORD   wItemNum;
    DWORD  dwData;

    if (id == IDLIST && code == LBN_DBLCLK) {

/*    PortTool v2.2     4/1/1993    1:3          */
/*      Found   : (WORD)          */
/*      Issue   : Check if incorrect cast of 32-bit value          */
/*      Suggest : Replace 16-bit data types with 32-bit types where possible          */
/*      Help available, search for WORD in WinHelp file API32WH.HLP          */
       wItemNum = (WORD)  SendMessage(hwndCtl, LB_GETCURSEL, 0, 0L);
       dwData   = (DWORD) SendMessage(hwndCtl, LB_GETITEMDATA, wItemNum, 0L);

       ActionItem(hwndCtl, dwData, wItemNum);
    }
    if (id == IDOK && code == BN_CLICKED)
    {
        EndDialog(hwndDlg, TRUE);
    }
    else if (id == IDCANCEL && code == BN_CLICKED)
    {
        EndDialog(hwndDlg, FALSE);
    }
}



VOID ActionItem(HWND hWndList, DWORD dwData, WORD wItemNum)
{
   DWORD dwAddItem;
   DWORD dwIncr;
   WORD  wCount;
   WORD  wItem;

   // 
   // Is this an item or folder
   //
   if ( (dwData % 10) ) {
      //
      // Not a folder ... Just pop a box
      //
      MessageBox(hWndList, "Do something with this", "Simon Says", MB_OK);
   }
   else {
      // 
      // It's a folder, Set up some junk for this sample app.
      //
      if ( dwData % 1000 == 0 ) {
         dwAddItem = dwData + 1000;
      }
      else if ( dwData % 100 == 0 ) {
         dwAddItem = dwData + 100;
      }
      else if ( dwData % 10 == 0 ) {
         dwAddItem = dwData + 10;
      }
      
      // 
      // Is it open ?
      //
      if ( HierDraw_IsOpened(&HierDrawStruct, dwData) ) {
         //
         // It's open ... Close it
         //
         HierDraw_CloseItem(&HierDrawStruct, dwData);


         //
         // Remove the child items. Close any children that are 
         // open on the way.
         //
         // No need for recursion. We just close everything along 
         // the way and remove
         // items until we reach the next sibling to the current 
         // item.
         //
         wItemNum++;
         dwIncr = SendMessage(hWndList, LB_GETITEMDATA, wItemNum, 0L);
         while ( dwIncr < dwAddItem ) {
            if ( (dwIncr % 10) == 0 &&
                  HierDraw_IsOpened(&HierDrawStruct, dwIncr)) {
               HierDraw_CloseItem(&HierDrawStruct, dwIncr);
            }
            SendMessage(hWndList, LB_DELETESTRING, wItemNum, 0L);
            dwIncr = SendMessage(hWndList, LB_GETITEMDATA, wItemNum, 0L);
         }
      }
      else {
         //
         // It's closed ... Open it
         //
         HierDraw_OpenItem(&HierDrawStruct, dwData);
         if ( dwData % 1000 == 0 ) {
            dwIncr = 100;
         }
         else if ( dwData % 100 == 0 ) {
            dwIncr = 10;
         }
         else if ( dwData % 10 == 0 ) {
            dwIncr = 1;
         }
         SendMessage(hWndList, WM_SETREDRAW, FALSE, 0L);   // Disable redrawing.

         for ( wItem = wItemNum, dwAddItem = dwData+dwIncr, wCount = 0, wItem++;
               wCount < 9; wItem++, wCount++, dwAddItem+=dwIncr ) {
             SendMessage(hWndList, LB_INSERTSTRING, wItem, dwAddItem);
         }
         //
         // Make sure as many child items as possible are showing
         //
         HierDraw_ShowKids(&HierDrawStruct, hWndList, wItemNum, 9 );

         SendMessage(hWndList, WM_SETREDRAW, TRUE, 0L);   // Enable redrawing.
         InvalidateRect(hWndList, NULL, TRUE);            // Force redraw
      }
   }
}
