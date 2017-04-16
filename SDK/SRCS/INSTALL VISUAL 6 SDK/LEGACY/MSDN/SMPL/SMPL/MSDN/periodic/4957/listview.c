/**************************************************************************

   File: ListView.c
   
**************************************************************************/

/**************************************************************************
   Include Files
**************************************************************************/

#define STRICT
//#define UNICODE

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include "resource.h"

/**************************************************************************
   Local Function Prototypes
**************************************************************************/

BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
HWND CreateListView(HINSTANCE, HWND);
void ResizeListView(HWND, HWND);
BOOL InitListView(HWND);
LRESULT ListViewNotify(HWND, LPARAM);
void SwitchView(HWND, DWORD);
void AddExStyle(HWND, DWORD);
void RemoveExStyle(HWND, DWORD);
LRESULT HandleCommand(HWND, WPARAM, LPARAM);
BOOL HandleContextMenu(HWND, WPARAM, LPARAM);
void UpdateMenu(HWND, HMENU);
BOOL InsertListViewItems(HWND);

/**************************************************************************
   Global Variables
**************************************************************************/

HANDLE   g_hInst;
TCHAR    szClassName[] = TEXT("ListViewClass");
BOOL     g_bCustomDraw;

#define IDC_LISTVIEW 1000

/******************************************************************************

   WinMain

******************************************************************************/

int PASCAL WinMain(  HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nCmdShow)
{
MSG  msg;
INITCOMMONCONTROLSEX iccex;

//required to use the common controls
iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
iccex.dwICC = ICC_LISTVIEW_CLASSES;
InitCommonControlsEx(&iccex);

g_hInst = hInstance;

if(!hPrevInstance)
   if(!InitApplication(hInstance))
      return FALSE;

/* Perform initializations that apply to a specific instance */

if (!InitInstance(hInstance, nCmdShow))
   return FALSE;

/* Acquire and dispatch messages until a WM_QUIT uMessage is received. */

while(GetMessage(&msg, NULL, 0x00, 0x00))
   {
   TranslateMessage(&msg);
   DispatchMessage(&msg);
   }

return msg.wParam;
}


/******************************************************************************

   InitApplication

******************************************************************************/

BOOL InitApplication(HINSTANCE hInstance)
{
WNDCLASSEX  wcex;
ATOM        aReturn;

wcex.cbSize          = sizeof(WNDCLASSEX);
wcex.style           = 0;
wcex.lpfnWndProc     = (WNDPROC)MainWndProc;
wcex.cbClsExtra      = 0;
wcex.cbWndExtra      = 0;
wcex.hInstance       = hInstance;
wcex.hCursor         = LoadCursor(NULL, IDC_ARROW);
wcex.hbrBackground   = (HBRUSH)(COLOR_WINDOW + 1);
wcex.lpszMenuName    = MAKEINTRESOURCE(IDM_MAIN_MENU);
wcex.lpszClassName   = szClassName;
wcex.hIcon           = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_MAINICON));
wcex.hIconSm         = LoadImage(g_hInst, MAKEINTRESOURCE(IDI_MAINICON), IMAGE_ICON, 16, 16, 0);

aReturn = RegisterClassEx(&wcex);

if(0 == aReturn)
   {
   WNDCLASS wc;

   wc.style          = 0;
   wc.lpfnWndProc    = (WNDPROC)MainWndProc;
   wc.cbClsExtra     = 0;
   wc.cbWndExtra     = 0;
   wc.hInstance      = hInstance;
   wc.hIcon          = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_MAINICON));
   wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
   wc.lpszMenuName   = MAKEINTRESOURCE(IDM_MAIN_MENU);
   wc.lpszClassName  = szClassName;

   aReturn = RegisterClass(&wc);
   }

return aReturn;
}


/******************************************************************************

   InitInstance

******************************************************************************/

BOOL InitInstance(   HINSTANCE hInstance,
                     int nCmdShow)
{
HWND  hWnd;

g_hInst = hInstance;

/* Create a main window for this application instance.  */

hWnd = CreateWindowEx(  0,
                        szClassName,
                        TEXT("Windows 95 List View Sample Application"),
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

/* If window could not be created, return "failure" */

if (!hWnd)
   return FALSE;

/* Make the window visible; update its client area; and return "success" */

ShowWindow(hWnd, nCmdShow);
UpdateWindow(hWnd);
return TRUE;

}

/******************************************************************************

   MainWndProc

******************************************************************************/

LRESULT CALLBACK MainWndProc( HWND hWnd,
                              UINT uMessage,
                              WPARAM wParam,
                              LPARAM lParam)
{
switch (uMessage)
   {
   case WM_CREATE:
      {
      HWND  hwndListView;
      
      g_bCustomDraw = FALSE;
      
      // create the TreeView control
      hwndListView = CreateListView(g_hInst, hWnd);
      
      //initialize the TreeView control
      InitListView(hwndListView);
      }
      break;

   case WM_NOTIFY:
      return ListViewNotify(hWnd, lParam);
   
   case WM_SIZE:
      ResizeListView(GetDlgItem(hWnd, IDC_LISTVIEW), hWnd);
      break;

   case WM_INITMENUPOPUP:
      UpdateMenu(GetDlgItem(hWnd, IDC_LISTVIEW), GetMenu(hWnd));
      break;
   
   case WM_CONTEXTMENU:
      if(HandleContextMenu(hWnd, wParam, lParam))
         return FALSE;
      break;
   
   case WM_COMMAND:
      return HandleCommand(hWnd, wParam, lParam);

   case WM_DESTROY:
      PostQuitMessage(0);
      break;

   default:
      break;
   }
return DefWindowProc(hWnd, uMessage, wParam, lParam);
}


/******************************************************************************

   AboutDlgProc

******************************************************************************/

BOOL CALLBACK AboutDlgProc(   HWND hDlg, 
                              UINT uMessage, 
                              WPARAM wParam, 
                              LPARAM lParam)
{
switch (uMessage)
   {
   case WM_INITDIALOG:
      return TRUE;
      
   case WM_COMMAND:
      switch(wParam)
         {
         case IDOK:
            EndDialog(hDlg, IDOK);
            break;

         case IDCANCEL:
            EndDialog(hDlg, IDOK);
            break;
         }
      return TRUE;
    } 
    
return FALSE;
}

/******************************************************************************

   CreateListView

******************************************************************************/

HWND CreateListView(HINSTANCE hInstance, HWND hwndParent)
{
DWORD       dwStyle;
HWND        hwndListView;
HIMAGELIST  himlSmall;
HIMAGELIST  himlLarge;
SHFILEINFO  sfi;
BOOL        bSuccess = TRUE;

dwStyle =   WS_TABSTOP | 
            WS_CHILD | 
            WS_BORDER | 
            LVS_AUTOARRANGE |
            LVS_REPORT | 
            LVS_EDITLABELS |
            LVS_SHAREIMAGELISTS |
            WS_VISIBLE;
            
hwndListView = CreateWindowEx(   WS_EX_CLIENTEDGE,          // ex style
                                 WC_LISTVIEW,               // class name - defined in commctrl.h
                                 NULL,                      // window text
                                 dwStyle,                   // style
                                 0,                         // x position
                                 0,                         // y position
                                 0,                         // width
                                 0,                         // height
                                 hwndParent,                // parent
                                 (HMENU)IDC_LISTVIEW,       // ID
                                 g_hInst,                   // instance
                                 NULL);                     // no extra data

if(!hwndListView)
   return NULL;

ResizeListView(hwndListView, hwndParent);

//set the large and small icon image lists
himlSmall = (HIMAGELIST)SHGetFileInfo( TEXT("C:\\"), 
                                       0,
                                       &sfi, 
                                       sizeof(SHFILEINFO), 
                                       SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

himlLarge = (HIMAGELIST)SHGetFileInfo( TEXT("C:\\"), 
                                       0,
                                       &sfi, 
                                       sizeof(SHFILEINFO), 
                                       SHGFI_SYSICONINDEX | SHGFI_LARGEICON);

if (himlSmall && himlLarge)
   {
   SendMessage(hwndListView, LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)himlSmall);
   SendMessage(hwndListView, LVM_SETIMAGELIST, (WPARAM)LVSIL_NORMAL, (LPARAM)himlLarge);
   }

return hwndListView;
}

/******************************************************************************

   ResizeListView

******************************************************************************/

void ResizeListView(HWND hwndListView, HWND hwndParent)
{
RECT  rc;

GetClientRect(hwndParent, &rc);

MoveWindow( hwndListView, 
            rc.left,
            rc.top,
            rc.right - rc.left,
            rc.bottom - rc.top,
            TRUE);

}

/******************************************************************************

   InitListView

******************************************************************************/

BOOL InitListView(HWND hwndListView)
{
LV_COLUMN   lvColumn;
int         i;
TCHAR       szString[5][20] = {  TEXT("Image Number"), 
                                 TEXT("Left"), 
                                 TEXT("Top"), 
                                 TEXT("Right"), 
                                 TEXT("Bottom")};

//initialize the columns
lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
lvColumn.fmt = LVCFMT_LEFT;
lvColumn.cx = 100;
for(i = 0; i < 5; i++)
   {
   //make the secondary columns smaller
   if(i)
      lvColumn.cx = 50;

   lvColumn.pszText = szString[i];
   SendMessage(hwndListView, LVM_INSERTCOLUMN, (WPARAM)i, (LPARAM)&lvColumn);
   }

InsertListViewItems(hwndListView);

return TRUE;
}

/******************************************************************************

   InsertListViewItems

******************************************************************************/

BOOL InsertListViewItems(HWND hwndListView)
{
LV_ITEM     lvItem;
int         i,
            nIndex,
            nImageCount;
TCHAR       szString[MAX_PATH];
HIMAGELIST  himl;
IMAGEINFO   ii;

SendMessage(hwndListView, WM_SETREDRAW, FALSE, 0);

//empty the list
SendMessage(hwndListView, LVM_DELETEALLITEMS, 0, 0);

//get the number of icons in the image list
himl = (HIMAGELIST)SendMessage(hwndListView, LVM_GETIMAGELIST, (WPARAM)LVSIL_SMALL, 0);
nImageCount = ImageList_GetImageCount(himl);

for(i = 0; i < nImageCount; i++)
   {
   wsprintf(szString, TEXT("Image #%d"), i);
   
   //fill in the LV_ITEM structure for the first item
   lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
   lvItem.pszText = szString;
   lvItem.iImage = i;
   lvItem.iItem = SendMessage(hwndListView, LVM_GETITEMCOUNT, 0, 0);
   lvItem.iSubItem = 0;

   //add the item - get the index in case the ListView is sorted
   nIndex = SendMessage(hwndListView, LVM_INSERTITEM, (WPARAM)0, (LPARAM)&lvItem);

   //set the text and images for the sub-items
   ImageList_GetImageInfo(himl, i, &ii);
   wsprintf(szString, TEXT("%d"), ii.rcImage.left);
   lvItem.iSubItem = 1;
   SendMessage(hwndListView, LVM_SETITEM, 0, (LPARAM)&lvItem);

   wsprintf(szString, TEXT("%d"), ii.rcImage.top);
   lvItem.iSubItem = 2;
   SendMessage(hwndListView, LVM_SETITEM, 0, (LPARAM)&lvItem);

   wsprintf(szString, TEXT("%d"), ii.rcImage.right);
   lvItem.iSubItem = 3;
   SendMessage(hwndListView, LVM_SETITEM, 0, (LPARAM)&lvItem);

   wsprintf(szString, TEXT("%d"), ii.rcImage.bottom);
   lvItem.iSubItem = 4;
   SendMessage(hwndListView, LVM_SETITEM, 0, (LPARAM)&lvItem);
   }

SendMessage(hwndListView, WM_SETREDRAW, TRUE, 0);
UpdateWindow(hwndListView);

return TRUE;
}

/**************************************************************************

   ListViewNotify()

**************************************************************************/

LRESULT ListViewNotify(HWND hWnd, LPARAM lParam)
{
LPNMHDR  lpnmh = (LPNMHDR) lParam;
HWND     hwndListView = GetDlgItem(hWnd, IDC_LISTVIEW);

switch(lpnmh->code)
   {
   case NM_CUSTOMDRAW:
      {
      LPNMLVCUSTOMDRAW  lplvcd = (LPNMLVCUSTOMDRAW)lParam;

      /*
      CDDS_PREPAINT is sent when the control is about to paint itself. You 
      implement custom draw by returning the proper value to this 
      notification.
      */
      if(lplvcd->nmcd.dwDrawStage == CDDS_PREPAINT)
         {
         if(g_bCustomDraw)
            {
            //tell the control we want pre-paint notifications for each item
            return CDRF_NOTIFYITEMDRAW;
            }
         //tell the control that we won't be doing any custom drawing
         return CDRF_DODEFAULT;
         }

      /*
      CDDS_ITEMPREPAINT is sent when the control is about to paint an item. 
      You will only get these if you returned CDRF_NOTIFYITEMDRAW in 
      response to CDDS_PREPAINT.
      */
      if(lplvcd->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
         {
         LRESULT  lReturn = CDRF_DODEFAULT;
         /*
         For the ListView, the index of the item being drawn is stored in the 
         dwItemSpec member of the NMCUSTOMDRAW structure. In this example, only 
         the odd items will be drawn using the bold font.
         */
         if(lplvcd->nmcd.dwItemSpec & 0x01)
            {
            HFONT    hFont;
            LOGFONT  lf;

            //get the existing font
            hFont = (HFONT)SendMessage(hwndListView, WM_GETFONT, 0, 0);

            //now get the font's information
            GetObject(hFont, sizeof(lf), &lf);

            //make this font bold
            lf.lfWeight = FW_BOLD;

            //create the new font
            hFont = CreateFontIndirect(&lf);

            /*
            To change the font, just select the desired font into the HDC 
            provided.
            */
            SelectObject(lplvcd->nmcd.hdc, hFont);

            /*
            To change the text and background colors in a ListView, set the 
            clrText and clrTextBk members of the NMLVCUSTOMDRAW structure to 
            the desired color. This is different than most other controls that 
            support custom draw. To change the text and background colors in 
            the others, you just call SetTextColor and SetBkColor on the HDC 
            provided. 
            */
            lplvcd->clrText = RGB(255, 0, 0);
            lplvcd->clrTextBk = RGB(255, 255, 255);

            /*
            If you change the font, return CDRF_NEWFONT so the control can 
            recalculate the extent of the text. Returning CDRF_NOTIFYPOSTPAINT 
            causes the control to send us notifications with CDDS_ITEMPOSTPAINT.
            */
            lReturn = CDRF_NEWFONT | CDRF_NOTIFYPOSTPAINT;
            }
         else
            {
            lplvcd->clrText = RGB(0, 0, 255);
            lplvcd->clrTextBk = RGB(255, 255, 255);
            }

         return lReturn;
         }

      if(lplvcd->nmcd.dwDrawStage == CDDS_ITEMPOSTPAINT)
         {
         HFONT hFont = GetStockObject(DEFAULT_GUI_FONT);

         //clean up stuff here
         hFont = SelectObject(lplvcd->nmcd.hdc, hFont);

         DeleteFont(hFont);
         
         return CDRF_DODEFAULT;
         }
      }
      return CDRF_DODEFAULT;
   
   }

return 0;
}

/**************************************************************************

   SwitchView()

**************************************************************************/

void SwitchView(HWND hwndListView, DWORD dwView)
{
DWORD dwStyle = GetWindowLong(hwndListView, GWL_STYLE);

SetWindowLong(hwndListView, GWL_STYLE, (dwStyle & ~LVS_TYPEMASK) | dwView);
ResizeListView(hwndListView, GetParent(hwndListView));
}

/**************************************************************************

   AddExStyle()

**************************************************************************/

void AddExStyle(HWND hwndListView, DWORD dwNewStyle)
{
DWORD dwStyle = SendMessage(hwndListView, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);
dwStyle |= dwNewStyle;
SendMessage(hwndListView, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
}

/**************************************************************************

   RemoveExStyle()

**************************************************************************/

void RemoveExStyle(HWND hwndListView, DWORD dwNewStyle)
{
DWORD dwStyle = SendMessage(hwndListView, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);
dwStyle &= ~dwNewStyle;
SendMessage(hwndListView, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
}

/**************************************************************************

   HandleCommand()

**************************************************************************/

LRESULT HandleCommand(  HWND hWnd, 
                        WPARAM wParam, 
                        LPARAM lParam)
{
switch (GET_WM_COMMAND_ID(wParam, lParam))
   {
   case IDM_LARGEICONS:
      SwitchView(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_ICON);
      break;
   
   case IDM_SMALLICONS:
      SwitchView(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_SMALLICON);
      break;
   
   case IDM_LIST:
      SwitchView(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_LIST);
      break;
   
   case IDM_REPORT:
      SwitchView(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_REPORT);
      break;
   
   case IDM_EXIT:
      DestroyWindow(hWnd);
      break;
   
   case IDM_ABOUT:
      DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUT), hWnd, AboutDlgProc);
      break;   

   case IDM_INDENT:
      {
      LV_ITEM  lvItem;
      int      i,
               nItemCount;

      ZeroMemory(&lvItem, sizeof(lvItem));

      nItemCount = (int)SendDlgItemMessage(hWnd, IDC_LISTVIEW, LVM_GETITEMCOUNT, 0, 0);

      //run through the list, indenting the selected items
      for(i = 0; i < nItemCount; i++)
         {
         lvItem.mask = LVIF_STATE | LVIF_INDENT;
         lvItem.iItem = i;
         lvItem.stateMask = LVIS_SELECTED;
         SendDlgItemMessage(hWnd, IDC_LISTVIEW, LVM_GETITEM, 0, (LPARAM)&lvItem);

         if(lvItem.state & LVIS_SELECTED)
            {
            lvItem.mask = LVIF_INDENT;
            lvItem.iIndent++;
            SendDlgItemMessage(hWnd, IDC_LISTVIEW, LVM_SETITEM, 0, (LPARAM)&lvItem);
            }
         }
      }
      break;
   
   case IDM_UNINDENT:
      {
      LV_ITEM  lvItem;
      int      i,
               nItemCount;

      ZeroMemory(&lvItem, sizeof(lvItem));

      nItemCount = (int)SendDlgItemMessage(hWnd, IDC_LISTVIEW, LVM_GETITEMCOUNT, 0, 0);

      //run through the list, unindenting the selected items
      for(i = 0; i < nItemCount; i++)
         {
         lvItem.mask = LVIF_STATE | LVIF_INDENT;
         lvItem.iItem = i;
         lvItem.stateMask = LVIS_SELECTED;
         SendDlgItemMessage(hWnd, IDC_LISTVIEW, LVM_GETITEM, 0, (LPARAM)&lvItem);

         if(lvItem.state & LVIS_SELECTED)
            {
            lvItem.mask = LVIF_INDENT;
            if(lvItem.iIndent)
               {
               lvItem.iIndent--;
               SendDlgItemMessage(hWnd, IDC_LISTVIEW, LVM_SETITEM, 0, (LPARAM)&lvItem);
               }
            }
         }
      }
      break;
   
   case IDM_CUSTOMDRAW:
      //toggle the custom draw flag
      g_bCustomDraw = !g_bCustomDraw;

      //force the control to redraw itself
      InvalidateRect(GetDlgItem(hWnd, IDC_LISTVIEW), NULL, TRUE);
      break;
   
   case IDM_CHECKBOXES:
      if(LVS_EX_CHECKBOXES & (DWORD)SendDlgItemMessage(hWnd, IDC_LISTVIEW, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0))
         RemoveExStyle(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_EX_CHECKBOXES);
      else
         AddExStyle(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_EX_CHECKBOXES);
      break;

   case IDM_HOVERSELECT:
      if(LVS_EX_TRACKSELECT & (DWORD)SendDlgItemMessage(hWnd, IDC_LISTVIEW, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0))
         RemoveExStyle(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_EX_TRACKSELECT);
      else
         AddExStyle(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_EX_TRACKSELECT);
      break;

   case IDM_GRIDLINES:
      if(LVS_EX_GRIDLINES & (DWORD)SendDlgItemMessage(hWnd, IDC_LISTVIEW, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0))
         RemoveExStyle(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_EX_GRIDLINES);
      else
         AddExStyle(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_EX_GRIDLINES);
      break;

   case IDM_FULLROWSELECT:
      if(LVS_EX_FULLROWSELECT & (DWORD)SendDlgItemMessage(hWnd, IDC_LISTVIEW, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0))
         RemoveExStyle(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_EX_FULLROWSELECT);
      else
         AddExStyle(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_EX_FULLROWSELECT);
      break;

   case IDM_HEADERDRAGDROP:
      if(LVS_EX_HEADERDRAGDROP & (DWORD)SendDlgItemMessage(hWnd, IDC_LISTVIEW, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0))
         RemoveExStyle(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_EX_HEADERDRAGDROP);
      else
         AddExStyle(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_EX_HEADERDRAGDROP);
      break;

   case IDM_SUBITEMIMAGES:
      if(LVS_EX_SUBITEMIMAGES & (DWORD)SendDlgItemMessage(hWnd, IDC_LISTVIEW, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0))
         RemoveExStyle(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_EX_SUBITEMIMAGES);
      else
         AddExStyle(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_EX_SUBITEMIMAGES);
      
      InvalidateRect(GetDlgItem(hWnd, IDC_LISTVIEW), NULL, TRUE);
      UpdateWindow(GetDlgItem(hWnd, IDC_LISTVIEW));
      break;

   }

return 0;
}

/**************************************************************************

   HandleContextMenu()

**************************************************************************/

BOOL HandleContextMenu( HWND hWnd, 
                        WPARAM wParam, 
                        LPARAM lParam)
{
HMENU hMenuLoad,
      hMenu;

if((HWND)wParam != GetDlgItem(hWnd, IDC_LISTVIEW))
   return FALSE;

hMenuLoad = LoadMenu(g_hInst, MAKEINTRESOURCE(IDM_CONTEXT_MENU));
hMenu = GetSubMenu(hMenuLoad, 0);

UpdateMenu(GetDlgItem(hWnd, IDC_LISTVIEW), hMenu);

TrackPopupMenu(   hMenu,
                  TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                  LOWORD(lParam),
                  HIWORD(lParam),
                  0,
                  hWnd,
                  NULL);

DestroyMenu(hMenuLoad);

return TRUE;
}

/**************************************************************************

   UpdateMenu()

**************************************************************************/

void UpdateMenu(HWND hwndListView, HMENU hMenu)
{
UINT  uID;
DWORD dwStyle;

//uncheck all of these guys
CheckMenuItem(hMenu, IDM_LARGEICONS,  MF_BYCOMMAND | MF_UNCHECKED);
CheckMenuItem(hMenu, IDM_SMALLICONS,  MF_BYCOMMAND | MF_UNCHECKED);
CheckMenuItem(hMenu, IDM_LIST,  MF_BYCOMMAND | MF_UNCHECKED);
CheckMenuItem(hMenu, IDM_REPORT,  MF_BYCOMMAND | MF_UNCHECKED);

CheckMenuItem(hMenu, IDM_CUSTOMDRAW,  MF_BYCOMMAND | MF_UNCHECKED);
CheckMenuItem(hMenu, IDM_CHECKBOXES,  MF_BYCOMMAND | MF_UNCHECKED);
CheckMenuItem(hMenu, IDM_HOVERSELECT,  MF_BYCOMMAND | MF_UNCHECKED);
CheckMenuItem(hMenu, IDM_GRIDLINES,  MF_BYCOMMAND | MF_UNCHECKED);
CheckMenuItem(hMenu, IDM_FULLROWSELECT,  MF_BYCOMMAND | MF_UNCHECKED);
CheckMenuItem(hMenu, IDM_HEADERDRAGDROP,  MF_BYCOMMAND | MF_UNCHECKED);
CheckMenuItem(hMenu, IDM_SUBITEMIMAGES,  MF_BYCOMMAND | MF_UNCHECKED);

//check the appropriate view menu item
dwStyle = GetWindowLong(hwndListView, GWL_STYLE);
switch(dwStyle & LVS_TYPEMASK)
   {
   case LVS_ICON:
      uID = IDM_LARGEICONS;
      break;
      
   case LVS_SMALLICON:
      uID = IDM_SMALLICONS;
      break;
      
   case LVS_LIST:
      uID = IDM_LIST;
      break;
   
   case LVS_REPORT:
      uID = IDM_REPORT;
      break;
   }
CheckMenuRadioItem(hMenu, IDM_LARGEICONS, IDM_REPORT, uID,  MF_BYCOMMAND | MF_CHECKED);

//check the appropriate extended style items
dwStyle = (DWORD)SendMessage(hwndListView, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);

//only update and enable grid lines, full row select, header drag drop, and sub-item images items if in report view
if(uID == IDM_REPORT)
   {
   EnableMenuItem(hMenu, IDM_GRIDLINES, MF_BYCOMMAND | MF_ENABLED);
   EnableMenuItem(hMenu, IDM_FULLROWSELECT, MF_BYCOMMAND | MF_ENABLED);
   EnableMenuItem(hMenu, IDM_HEADERDRAGDROP, MF_BYCOMMAND | MF_ENABLED);
   EnableMenuItem(hMenu, IDM_SUBITEMIMAGES, MF_BYCOMMAND | MF_ENABLED);

   //can we indent or unindent?
   if(SendMessage(hwndListView, LVM_GETSELECTEDCOUNT, 0, 0))
      {
      EnableMenuItem(hMenu, IDM_INDENT, MF_BYCOMMAND | MF_ENABLED);
      EnableMenuItem(hMenu, IDM_UNINDENT, MF_BYCOMMAND | MF_ENABLED);
      }
   else
      {
      EnableMenuItem(hMenu, IDM_INDENT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
      EnableMenuItem(hMenu, IDM_UNINDENT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
      }

   if(dwStyle & LVS_EX_GRIDLINES)
      {
      CheckMenuItem(hMenu, IDM_GRIDLINES, MF_BYCOMMAND | MF_CHECKED);
      }

   if(dwStyle & LVS_EX_FULLROWSELECT)
      {
      CheckMenuItem(hMenu, IDM_FULLROWSELECT, MF_BYCOMMAND | MF_CHECKED);
      }

   if(dwStyle & LVS_EX_HEADERDRAGDROP)
      {
      CheckMenuItem(hMenu, IDM_HEADERDRAGDROP, MF_BYCOMMAND | MF_CHECKED);
      }

   if(dwStyle & LVS_EX_SUBITEMIMAGES)
      {
      CheckMenuItem(hMenu, IDM_SUBITEMIMAGES, MF_BYCOMMAND | MF_CHECKED);
      }
   }
else
   {
   EnableMenuItem(hMenu, IDM_INDENT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
   EnableMenuItem(hMenu, IDM_UNINDENT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
   EnableMenuItem(hMenu, IDM_GRIDLINES, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
   EnableMenuItem(hMenu, IDM_FULLROWSELECT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
   EnableMenuItem(hMenu, IDM_HEADERDRAGDROP, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
   EnableMenuItem(hMenu, IDM_SUBITEMIMAGES, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
   }

//is custom drawing turned on?
if(g_bCustomDraw)
   {
   CheckMenuItem(hMenu, IDM_CUSTOMDRAW,  MF_BYCOMMAND | MF_CHECKED);
   }

//are checkboxes turned on?
if(dwStyle & LVS_EX_CHECKBOXES)
   {
   CheckMenuItem(hMenu, IDM_CHECKBOXES,  MF_BYCOMMAND | MF_CHECKED);
   }

//is hover select turned on?
if(dwStyle & LVS_EX_TRACKSELECT )
   {
   CheckMenuItem(hMenu, IDM_HOVERSELECT,  MF_BYCOMMAND | MF_CHECKED);
   }

}
