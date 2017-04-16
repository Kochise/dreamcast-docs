/**************************************************************************

   File: VListVw.c
   
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

int PASCAL WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
HWND CreateListView(HINSTANCE, HWND);
void ResizeListView(HWND, HWND);
BOOL InitListView(HWND);
LRESULT ListViewNotify(HWND, LPARAM);
void SwitchView(HWND, DWORD);
LRESULT HandleCommand(HWND, WPARAM, LPARAM);
BOOL HandleContextMenu(HWND, WPARAM, LPARAM);
void UpdateMenu(HWND, HMENU);
BOOL InsertListViewItems(HWND);

/**************************************************************************
   Global Variables
**************************************************************************/

HANDLE   g_hInst;
TCHAR    g_szClassName[] = TEXT("VListVwClass");

#define ITEM_COUNT   100000000
#define IDC_LISTVIEW 2000

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
while(GetMessage( &msg, NULL, 0x00, 0x00))
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
wcex.lpszClassName   = g_szClassName;
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
   wc.lpszClassName  = g_szClassName;

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
HWND     hWnd;
TCHAR    szTitle[MAX_PATH];

g_hInst = hInstance;

LoadString(g_hInst, IDS_APPTITLE, szTitle, sizeof(szTitle));

/* Create a main window for this application instance.  */
hWnd = CreateWindowEx(  0,
                        g_szClassName,
                        szTitle,
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
BOOL        bSuccess = TRUE;

dwStyle =   WS_TABSTOP | 
            WS_CHILD | 
            WS_BORDER | 
            WS_VISIBLE |
            LVS_AUTOARRANGE |
            LVS_REPORT | 
            LVS_OWNERDATA;
            
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

//set the image lists
himlSmall = ImageList_Create(16, 16, ILC_COLORDDB | ILC_MASK, 1, 0);
himlLarge = ImageList_Create(32, 32, ILC_COLORDDB | ILC_MASK, 1, 0);

if (himlSmall && himlLarge)
   {
   HICON hIcon;

   //set up the small image list
   hIcon = LoadImage(g_hInst, MAKEINTRESOURCE(IDI_DISK), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
   ImageList_AddIcon(himlSmall, hIcon);

   //set up the large image list
   hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_DISK));
   ImageList_AddIcon(himlLarge, hIcon);

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
TCHAR       szString[5][20] = {  TEXT("Main Column"), 
                                 TEXT("Column 1"), 
                                 TEXT("Column 2"), 
                                 TEXT("Column 3"), 
                                 TEXT("Column 4")};

//initialize the columns
lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
lvColumn.fmt = LVCFMT_LEFT;
lvColumn.cx = 120;
for(i = 0; i < 5; i++)
   {
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
//empty the list
SendMessage(hwndListView, LVM_DELETEALLITEMS, 0, 0);

//set the number of items in the list
SendMessage(hwndListView, LVM_SETITEMCOUNT, (WPARAM)ITEM_COUNT, (LPARAM)LVSICF_NOINVALIDATEALL);

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
   case LVN_GETDISPINFO:
      {
      LV_DISPINFO *lpdi = (LV_DISPINFO *)lParam;
      TCHAR szString[MAX_PATH];

      if(lpdi->item.iSubItem)
         {
         if(lpdi->item.mask & LVIF_TEXT)
            {
            wsprintf(szString, TEXT("Item %d - Column %d"), lpdi->item.iItem + 1, lpdi->item.iSubItem);
            lstrcpyn(lpdi->item.pszText, szString, lpdi->item.cchTextMax);
            }
         }
      else
         {
         if(lpdi->item.mask & LVIF_TEXT)
            {
            wsprintf(szString, TEXT("Item %d"), lpdi->item.iItem + 1);
            lstrcpyn(lpdi->item.pszText, szString, lpdi->item.cchTextMax);
            }

         if(lpdi->item.mask & LVIF_IMAGE)
            {
            lpdi->item.iImage = 0;
            }

         if(lpdi->item.mask & LVIF_INDENT)
            {
            lpdi->item.iIndent = 0;
            }
         }
      }
      return 0;

   case LVN_ODCACHEHINT:
      {
      LPNMLVCACHEHINT   lpCacheHint = (LPNMLVCACHEHINT)lParam;
      /*
      This sample doesn't use this notification, but this is sent when the 
      ListView is about to ask for a range of items. On this notification, 
      you should load the specified items into your local cache. It is still 
      possible to get an LVN_GETDISPINFO for an item that has not been cached, 
      therefore, your application must take into account the chance of this 
      occurring.
      */
      }
      return 0;

   case LVN_ODFINDITEM:
      {
      LPNMLVFINDITEM lpFindItem = (LPNMLVFINDITEM)lParam;
      /*
      This sample doesn't use this notification, but this is sent when the 
      ListView needs a particular item. Return -1 if the item is not found.
      */
      }
      return 0;
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

   HandleContextMenu()

**************************************************************************/

LRESULT HandleCommand(  HWND hWnd, 
                        WPARAM wParam, 
                        LPARAM lParam)
{
switch (GET_WM_COMMAND_ID(wParam, lParam))
   {
   case IDM_LARGE_ICONS:
      SwitchView(GetDlgItem(hWnd, IDC_LISTVIEW), LVS_ICON);
      break;
   
   case IDM_SMALL_ICONS:
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
CheckMenuItem(hMenu, IDM_LARGE_ICONS,  MF_BYCOMMAND | MF_UNCHECKED);
CheckMenuItem(hMenu, IDM_SMALL_ICONS,  MF_BYCOMMAND | MF_UNCHECKED);
CheckMenuItem(hMenu, IDM_LIST,  MF_BYCOMMAND | MF_UNCHECKED);
CheckMenuItem(hMenu, IDM_REPORT,  MF_BYCOMMAND | MF_UNCHECKED);

//check the appropriate view menu item
dwStyle = GetWindowLong(hwndListView, GWL_STYLE);
switch(dwStyle & LVS_TYPEMASK)
   {
   case LVS_ICON:
      uID = IDM_LARGE_ICONS;
      break;
      
   case LVS_SMALLICON:
      uID = IDM_SMALL_ICONS;
      break;
      
   case LVS_LIST:
      uID = IDM_LIST;
      break;
   
   case LVS_REPORT:
      uID = IDM_REPORT;
      break;
   }
CheckMenuRadioItem(hMenu, IDM_LARGE_ICONS, IDM_REPORT, uID,  MF_BYCOMMAND | MF_CHECKED);

}
