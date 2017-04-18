/*--------------------------------------------------------------------------
  Frame.C --- Cursors main window procedure

  Description:
        This sample is spread across four files, each named for the role
        the contained functions play.  Each file header contains a brief
        description of its purpose and the routines it contains.

        FRAME.C contains those functions used to manage the main frame
        window.  The frame window, created by code in MAIN.C, owns the
        MDI client window, the menu bar, and other major parts of the
        interface.  The functions is contains are:

            AdjustMenus    - Enable/disable menu items given current state
            CloseAll       - Close all child windows
            CloseAllEnum   - Window enumeration callback used by CloseAll
            CloseChild     - Close the currently active child window
            CreateChild    - Create a new child window
            DoConnect      - Connect to a host
            DoDisconnect   - Disconnect from a host
            DoFrameMenu    - Process a menu request
            FrameProc      - Process frame window messages

  This code is furnished on an as-is basis as part of the ODBC SDK and is
  intended for example purposes only.

--------------------------------------------------------------------------*/

/* Includes --------------------------------------------------------------*/
#include    "headers.h"

#include   "resource.h"
#include    "crsrdemo.h"


// Constants ---------------------------------------------------------------
#define fDISABLED   (MF_BYCOMMAND | MF_DISABLED | MF_GRAYED)
#define fENABLED    (MF_BYCOMMAND | MF_ENABLED)


// Prototypes --------------------------------------------------------------
void INTFUNC CloseAll(HWND);
void INTFUNC CloseChild(HWND);
HWND INTFUNC CreateChild(HWND);
BOOL INTFUNC DoConnect(HWND);
void INTFUNC DoDisconnect(void);
BOOL INTFUNC DoFrameMenu(HWND, WPARAM, LPARAM);

BOOL CALLBACK CloseAllEnum(HWND, LPARAM);


/* AdjustMenus -------------------------------------------------------------
    Description: Enable/disable appropriate menu items
    --------------------------------------------------------------------------*/
void INTFUNC AdjustMenus(void)
{
   LRESULT lresult;
   BOOL    fMaximized;
   HWND    hwnd;
   HMENU   hmenu;
   UINT    idMenu;
   UINT    fOption;

   lresult = SendMessage(g_hwndClient, WM_MDIGETACTIVE, 0, 0L);

#ifdef WIN32
   hwnd       = (HWND)lresult;
   fMaximized = GetWindowLong(hwnd, GWL_STYLE) & WS_MAXIMIZE;
#else
   hwnd       = (HWND)(LOWORD(lresult));
   fMaximized = HIWORD(lresult);
#endif

   if( hwnd ) {
      LPCHILD lpchild;

      lpchild = (LPCHILD)GetWindowLong(hwnd, 0);

      idMenu = IDM_FETCH + (fMaximized ? 1 : 0);

      if( lpchild->fResultSetExists ) {
         EnableMenuItem(GetMenu(g_hwnd), idMenu, MF_BYPOSITION |
                        MF_ENABLED);
         fOption = fENABLED;
      }
      else {
         EnableMenuItem(GetMenu(g_hwnd), idMenu, MF_BYPOSITION |
                        MF_DISABLED   |
                        MF_GRAYED);
         fOption = fDISABLED;
      }

      hmenu = GetSubMenu(GetMenu(g_hwnd), idMenu);
      EnableMenuItem(hmenu, IDM_FETCH_FIRST, fOption);
      EnableMenuItem(hmenu, IDM_FETCH_PRIOR,  fOption);
      EnableMenuItem(hmenu, IDM_FETCH_NEXT,   fOption);
      EnableMenuItem(hmenu, IDM_FETCH_LAST,   fOption);
      EnableMenuItem(hmenu, IDM_FETCH_ABSOLUTE, fOption);
      EnableMenuItem(hmenu, IDM_FETCH_RELATIVE, fOption);
#if 0
      EnableMenuItem(hmenu, IDM_FETCH_RESUME, fOption);
#endif  //  0
      if( lpchild->dwOperation != OPER_SELECT ) {
         EnableMenuItem(hmenu, (UINT)IDM_FETCH_DELETEROW, fDISABLED);
         EnableMenuItem(hmenu, (UINT)IDM_FETCH_UPDATEROW, fDISABLED);
      }
      else {
         EnableMenuItem(hmenu, (UINT)IDM_FETCH_DELETEROW, fOption);
         EnableMenuItem(hmenu, (UINT)IDM_FETCH_UPDATEROW, fOption);
      }

      idMenu = IDM_FETCHCHILD + (fMaximized ? 1 : 0);
      if( g_fConnected ) {
         EnableMenuItem(GetMenu(g_hwnd), idMenu, MF_BYPOSITION |
                        MF_ENABLED);
         fOption = fENABLED;
      }
      else {
         EnableMenuItem(GetMenu(g_hwnd), idMenu, MF_BYPOSITION  |
                        MF_DISABLED    |
                        MF_GRAYED);
         fOption = fDISABLED;
      }
   }
   else {
      UINT    wCount;
      
      hmenu = GetMenu(g_hwnd);
      wCount = GetMenuItemCount(hmenu);
      for( idMenu = 0; idMenu < wCount; idMenu++ )
         EnableMenuItem(hmenu, idMenu, MF_BYPOSITION | MF_ENABLED);
   }

   DrawMenuBar(g_hwnd);
   return;
}


/* CloseAll ----------------------------------------------------------------
    Description: Close all child windows
    --------------------------------------------------------------------------*/
void INTFUNC CloseAll(HWND hwnd)
{
   UNREF_PARAM(hwnd);
   if (!g_fConnected)
      return;

   EnumChildWindows(g_hwndClient, CloseAllEnum, 0L);
   return;
}


/* CloseAllEnum ------------------------------------------------------------
    Description: EnumChildWindows procedure, it calls CloseChild for each
                 child window passed
                 --------------------------------------------------------------------------*/
BOOL CALLBACK CloseAllEnum(HWND hwnd, LPARAM lparam)
{
   UNREF_PARAM(lparam);
   if (!GetWindow(hwnd, GW_OWNER))
      CloseChild(hwnd);
   return TRUE;
}


/* CloseChild --------------------------------------------------------------
    Description: Close a child window
    --------------------------------------------------------------------------*/
void INTFUNC CloseChild(HWND hwnd)
{
   // Destroy child window
   FORWARD_WM_MDIDESTROY(g_hwndClient, hwnd, SendMessage);

   // Decrement child count
   g_cChild--;

   // Set appropriate menu bar
   if (!g_cChild)
#ifdef WIN32
      SendMessage(g_hwndClient,WM_MDISETMENU,(WPARAM)g_hmenuFrame,(LPARAM)g_hmenuFrameWindow);
#else
   FORWARD_WM_MDISETMENU(g_hwndClient,
                         0, g_hmenuFrame, g_hmenuFrameWindow, SendMessage);
#endif
   return;
}


/* CreateChild -------------------------------------------------------------
    Description: Create a child window
    --------------------------------------------------------------------------*/
HWND INTFUNC CreateChild(HWND hwnd)
{
   HWND            hwndChild;
   MDICREATESTRUCT mdi;
   int             x, y, cx, cy;

   // Have child fill client area if it is the only child window
   if (!g_cChild) {
      RECT    rc;

      GetClientRect(hwnd, &rc);

      x  = rc.left;
      y  = rc.top;
      cx = rc.right - rc.left;
      cy = rc.bottom - rc.top;
   }

   // Otherwise, accept default placement
   else {
      x  =
         y  =
            cx =
               cy = CW_USEDEFAULT;
   }

   // Increment child count and cursor number
   g_cChild++;
   g_cCursor++;

   // Create child via MDI interface
   mdi.szClass = szCHILDCLASS;
   mdi.szTitle = g_szDSN;
   mdi.hOwner  = g_hinst;
   mdi.x       = x;
   mdi.y       = y;
   mdi.cx      = cx;
   mdi.cy      = cy;
   mdi.style   = 0;
   mdi.lParam  = (LPARAM)NULL;

   hwndChild = FORWARD_WM_MDICREATE(g_hwndClient, ((LPSTR)&mdi), SendMessage);

   if (hwndChild) {
      if (g_cChild == 1)
#ifdef WIN32
         SendMessage(g_hwndClient,WM_MDISETMENU,(WPARAM)g_hmenuChild,(LPARAM)g_hmenuChildWindow);
#else
      FORWARD_WM_MDISETMENU(g_hwndClient,
                            0, g_hmenuChild, g_hmenuChildWindow, SendMessage);
#endif
   }
   else
      g_cChild--;

   return hwndChild;
}


/* DoConnect ---------------------------------------------------------------
    Description: Connect to a data source
    --------------------------------------------------------------------------*/
BOOL INTFUNC DoConnect(HWND hwnd)
{
   HCURSOR   hcur;
   char      sz[cbMAXSQL];
   SWORD     cb;
   SQLRETURN rc;

   // If already connected, close all children and disconnect
   if (g_fConnected) {
      LoadString(g_hinst, IDS_CONWARN, sz, sizeof(sz));
      rc = MessageBox(hwnd,
                      sz, g_szTITLE,
                      MB_ICONQUESTION | MB_OKCANCEL | MB_DEFBUTTON2);
      if (rc == IDCANCEL)
         return FALSE;
      CloseAll(hwnd);
      DoDisconnect();
   }

   hcur = SetCursor(LoadCursor(NULL, IDC_WAIT));

   // Call SQLDriverConnect
   rc = SQLDriverConnect(g_hdbc, g_hwnd, NULL, 0,
                         (UCHAR FAR *)sz, sizeof(sz), &cb, SQL_DRIVER_COMPLETE);

   // If successfully connected, get data source attributes
   if (SUCCESS(rc)) {
      LPSTR    lpszS, lpszD;
      SQLHSTMT hstmt;

      // Mark as connected
      g_fConnected = TRUE;

      // Extract and save data source name
      lpszS = _fstrstr(sz, szDSNKEY);

      if (lpszS) {
         lpszS = _fstrstr(sz, szDSNKEY) + lstrlen(szDSNKEY);
         lpszD = g_szDSN;
         while (*lpszS && *lpszS != ';') *lpszD++ = *lpszS++;
         *lpszD = '\0';
      }
      else
         LoadString(g_hinst, IDS_NODSN, g_szDSN, sizeof(g_szDSN));

      // Change to the appropriate menu bar
#ifdef WIN32
      SendMessage(g_hwndClient,WM_MDISETMENU,(WPARAM)g_hmenuFrame,(LPARAM)g_hmenuFrameWindow);
#else
      FORWARD_WM_MDISETMENU(g_hwndClient,
                            0, g_hmenuFrame, g_hmenuFrameWindow, SendMessage);
#endif

      // Get maximum column name length
      if (DBCError(hwnd, SQLGetInfo(g_hdbc, SQL_MAX_COLUMN_NAME_LEN,
                                    &g_cbName, sizeof(g_cbName), NULL)))
         g_cbName = 32;

      // Get identifier quote character
      if (DBCError(hwnd, SQLGetInfo(g_hdbc, SQL_IDENTIFIER_QUOTE_CHAR,
                                    g_szQuoteChar, sizeof(g_szQuoteChar), NULL)))
         *g_szQuoteChar = ' ';

      // Determine if async support is available
      rc = SQLAllocHandle(SQL_HANDLE_STMT,g_hdbc, &hstmt);
      if (!SUCCESS(rc))
         g_fAsyncSupported = FALSE;

      else {
         g_fAsyncSupported = SUCCESS(SQLSetStmtAttr(hstmt,
                                                    SQL_ATTR_ASYNC_ENABLE,
                                                    (SQLPOINTER) 1,
                                                    SQL_IS_INTEGER));
         SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
      }
   }
   else if (rc != SQL_NO_DATA)
      DBCError(hwnd, rc);

   SetCursor(hcur);
   return SUCCESS(rc);
}


/* DoDisconnect ------------------------------------------------------------
    Description: Drop ODBC connection
    --------------------------------------------------------------------------*/
void INTFUNC DoDisconnect(void)
{
   // Change to the appropriate menu bar
#ifdef WIN32
   SendMessage(g_hwndClient,WM_MDISETMENU,(WPARAM)g_hmenuInit,(LPARAM)g_hmenuInitWindow);
#else
   FORWARD_WM_MDISETMENU(g_hwndClient,
                         0, g_hmenuInit, g_hmenuInitWindow, SendMessage);
#endif

   // If not fully connected, return immediately
   if (!g_fConnected)
      return;

   // Disconnect with ODBC
   SQLDisconnect(g_hdbc);

   // Reset connection related variables
   g_cbName     = 0;
   g_fConnected = FALSE;
   g_szDSN[0]   = '\0';
   g_cChild     = 0;
   g_cCursor    = 0;
   return;
}


/* DoFrameMenu -------------------------------------------------------------
    Description: Respond to a request from the frame window menu
    --------------------------------------------------------------------------*/
BOOL INTFUNC DoFrameMenu(HWND  hwnd, WPARAM  wparam, LPARAM  lparam)
{
   HWND    hwndChild;

   hwndChild = FORWARD_WM_MDIGETACTIVE(g_hwndClient, SendMessage);

   switch (GET_WM_COMMAND_ID(wparam, lparam)) {

     case IDM_STMT_ADDDSN:
      SQLCreateDataSource(hwnd, NULL);
      break;

     case IDM_STMT_DISCONNECT:
      if (g_cChild)
         CloseAll(hwnd);
      DoDisconnect();
      break;

     case IDM_STMT_CONNECT:
      if (!DoConnect(hwnd))
         break;

     case IDM_STMT_NEW:
      hwndChild = CreateChild(hwnd);
      break;

     case IDM_STMT_CLOSE:
      CloseChild(hwndChild);
      break;

     case IDM_STMT_CLOSEALL:
      CloseAll(hwnd);
      break;

     case IDM_STMT_EXIT:
      PostMessage(hwnd, WM_CLOSE, 0, 0L);
      break;

     case IDM_WINDOW_ARRANGE:
      FORWARD_WM_MDIICONARRANGE(g_hwndClient, SendMessage);
      break;

     case IDM_WINDOW_CASCADE:
      FORWARD_WM_MDICASCADE(g_hwndClient, 0, SendMessage);
      break;

     case IDM_WINDOW_TILEH:
     case IDM_WINDOW_TILEV: {
        WPARAM  fTile;

        fTile = (GET_WM_COMMAND_ID(wparam, lparam) == IDM_WINDOW_TILEH
                 ? MDITILE_HORIZONTAL
                 : MDITILE_VERTICAL);
        FORWARD_WM_MDITILE(g_hwndClient, fTile, SendMessage);
        break;
     }

     case IDM_HELP_ABOUT:
      DoDialog(g_hwnd, IDD_ABOUTBOX, AboutDlgProc);
      break;
	  
     case IDM_HELP_HELP:
      WinHelp(g_hwnd, szHELPFILE, HELP_KEY ,(DWORD)(LPTSTR)szKeyword );
		break;
	


     default:
      // Pass unrecognized request to the current child
      SendMessage(hwndChild, WM_COMMAND, wparam, lparam);
      return FALSE;
   }

   // Adjust menu state
   AdjustMenus();
   return TRUE;
}


/* FrameProc ---------------------------------------------------------------
    Description: Frame window procedure
    --------------------------------------------------------------------------*/
LRESULT EXPFUNC FrameProc(HWND    hwnd,
                          UINT   msg,
                          WPARAM wparam,
                          LPARAM lparam)
{
   switch (msg) {

      // Create MDI client window
     case WM_CREATE: {
        CLIENTCREATESTRUCT  client;

        client.hWindowMenu  = g_hmenuInitWindow;
        client.idFirstChild = IDM_FIRSTCHILD;

        g_hwndClient = CreateWindow(szMDICLIENT, NULL,
                                    WS_CHILD        |
                                    WS_CLIPCHILDREN |
                                    WS_VISIBLE,
                                    0, 0, 0, 0, hwnd, (HMENU)1, g_hinst,
                                    &client);
        break;
     }

      // Refresh brushes when colors change
     case WM_SYSCOLORCHANGE:
      if (g_hbrWin)    DeleteObject(g_hbrWin);
      if (g_hbrBtn)    DeleteObject(g_hbrBtn);
      if (g_hbrScroll) DeleteObject(g_hbrScroll);

      g_hbrWin    = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
      g_hbrBtn    = CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
      g_hbrScroll = CreateSolidBrush(GetSysColor(COLOR_SCROLLBAR));
      break;

      // Close all children, drop connection, and close frame window
     case WM_CLOSE:
      CloseAll(hwnd);
      DoDisconnect();
      DestroyWindow(hwnd);
      break;

      // Destroy menus not attached to the window and drop ODBC handles
     case WM_DESTROY: {
        HMENU   hmenu;

        hmenu = GetMenu(hwnd);

        if (g_hmenuInit  != hmenu) DestroyMenu(g_hmenuInit);
        if (g_hmenuFrame != hmenu) DestroyMenu(g_hmenuFrame);
        if (g_hmenuChild != hmenu) DestroyMenu(g_hmenuChild);

        if (g_hdbc)
           SQLFreeHandle(SQL_HANDLE_DBC,g_hdbc);

        if (g_henv)
           SQLFreeHandle(SQL_HANDLE_ENV,g_henv);

        g_hwnd = NULL;

        WinHelp(hwnd, szHELPFILE, HELP_QUIT, 0L);
        PostQuitMessage(0);
        break;
     }

      // Pass menu commands to handler routine
     case WM_COMMAND:
      if (DoFrameMenu(hwnd, wparam, lparam))
         break;

      // All other requests go to default MDI frame procedure
     default:
      return DefFrameProc(hwnd, g_hwndClient, msg, wparam, lparam);
   }

   return (LRESULT)NULL;
}
