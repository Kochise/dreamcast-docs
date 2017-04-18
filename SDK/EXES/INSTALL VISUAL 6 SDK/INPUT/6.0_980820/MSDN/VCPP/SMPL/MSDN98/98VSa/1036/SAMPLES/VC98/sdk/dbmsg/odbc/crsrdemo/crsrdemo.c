/*--------------------------------------------------------------------------
  Crsrdemo.C --- Cursors main file

  Description:
    This sample is spread across four files, each named for the role
    the contained functions play.  Each file header contains a brief
    description of its purpose and the routines it contains.

    CRSRDEMO.C contains the standard functions used in a Windows program
    (such as, WinMain) plus two functions shared between all the files.
    These functions are:

      DoMessage       - Issue a message
      EndInstance     - Clean up an instance of this program
      InitApplication - Prepare the first instance of this program
      InitInstance    - Prepare an instance of this program
      ODBCError       - Retrieve and display an ODBC error
      WinMain         - Main Windows entry point

    This code is furnished on an as-is basis as part of the ODBC SDK and is
    intended for example purposes only.

--------------------------------------------------------------------------*/

/* Includes --------------------------------------------------------------*/
#include "headers.h"

#pragma warning(disable:4001)
#define  INCL_GLOBAL
#include    "resource.h"
#include "crsrdemo.h"


// Prototypes --------------------------------------------------------------
void INTFUNC EndInstance(void);
BOOL INTFUNC InitApplication(void);
BOOL INTFUNC InitInstance(int);
int  INTFUNC WinMain(HINSTANCE, HINSTANCE, LPSTR, int);


/* DoMessage ---------------------------------------------------------------
   Description: Issue a message
   --------------------------------------------------------------------------*/
void INTFUNC DoMessage(HWND hwnd, UINT id)
{
   char  sz[cbSTRLEN];

   LoadString(g_hinst, id, sz, sizeof(sz));
   MessageBox(hwnd, sz, g_szTITLE, MB_ICONINFORMATION | MB_OK);
   return;
}


/* EndInstance -------------------------------------------------------------
   Description: Free instance related data
   --------------------------------------------------------------------------*/
void INTFUNC EndInstance(void)
{
   if (g_hfontName)  DeleteObject(g_hfontName);
   if (g_hfontData)  DeleteObject(g_hfontData);

   if (g_hbrWin)     DeleteObject(g_hbrWin);
   if (g_hbrBtn)     DeleteObject(g_hbrBtn);
   if (g_hbrScroll)  DeleteObject(g_hbrScroll);

   return;
}


/* InitApplication ---------------------------------------------------------
   Description: Prepare application by registering window classes
   --------------------------------------------------------------------------*/
BOOL INTFUNC InitApplication(void)
{
   WNDCLASS  wc;

   wc.style         = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc   = FrameProc;
   wc.cbClsExtra    = 0;
   wc.cbWndExtra    = 0;
   wc.hInstance     = g_hinst;
   wc.hIcon         = LoadIcon(g_hinst, MAKEINTRESOURCE(IDR_MAIN));
   wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
   wc.lpszMenuName  = NULL;
   wc.lpszClassName = szFRAMECLASS;

   if (!RegisterClass(&wc))
      return FALSE;

   wc.style         = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc   = ChildProc;
   wc.cbClsExtra    = 0;
   wc.cbWndExtra    = sizeof(LPCHILD);
   wc.hInstance     = g_hinst;
   wc.hIcon         = LoadIcon(g_hinst, MAKEINTRESOURCE(IDR_CHILD));
   wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
   wc.lpszMenuName  = NULL;
   wc.lpszClassName = szCHILDCLASS;

   if (!RegisterClass(&wc))
      return FALSE;

   return TRUE;
}


/* InitInstance ------------------------------------------------------------
   Description: Prepare instance by initializing global variables and
                creating main frame window
                --------------------------------------------------------------------------*/
BOOL INTFUNC InitInstance(int nCmdShow)
{
   RECT     rc;
   HDC         hdc;
   HFONT    hfont;
   TEXTMETRIC  tm;
   char     sz[cbSTRLEN];
   SIZE        size;

   // Initialize global variables
   g_hwnd       =
      g_hwndClient = NULL;

   g_haccel     = NULL;

   g_hmenuInit        =
      g_hmenuInitWindow  =
         g_hmenuFrame       =
            g_hmenuFrameWindow =
               g_hmenuChild       =
                  g_hmenuChildWindow = NULL;

   g_hfontName =
      g_hfontData = NULL;

   g_hbrWin    =
      g_hbrBtn    =
         g_hbrScroll = NULL;

   g_henv = SQL_NULL_HENV;
   g_hdbc = SQL_NULL_HDBC;

   g_haccel = LoadAccelerators(g_hinst, MAKEINTRESOURCE(IDR_MAIN));

   g_hmenuInit  = LoadMenu(g_hinst, MAKEINTRESOURCE(IDR_INIT));
   g_hmenuFrame = LoadMenu(g_hinst, MAKEINTRESOURCE(IDR_MAIN));
   g_hmenuChild = LoadMenu(g_hinst, MAKEINTRESOURCE(IDR_CHILD));

   g_hmenuInitWindow  = GetSubMenu(g_hmenuInit,  IDM_WINDOWINIT);
   g_hmenuFrameWindow = GetSubMenu(g_hmenuFrame, IDM_WINDOWFRAME);
   g_hmenuChildWindow = GetSubMenu(g_hmenuChild, IDM_WINDOWCHILD);

   g_cxVScroll = GetSystemMetrics(SM_CXVSCROLL);
   g_cyHScroll = GetSystemMetrics(SM_CYHSCROLL);

   LoadString(g_hinst, IDS_TABLE,      g_szTable,      sizeof(g_szTable));
   LoadString(g_hinst, IDR_MAIN,       g_szTITLE,      sizeof(g_szTITLE));
   LoadString(g_hinst, IDS_NOROW,      g_szNoRow,      sizeof(g_szNoRow));
   LoadString(g_hinst, IDS_ROWERROR,   g_szRowError,  sizeof(g_szRowError));
   LoadString(g_hinst, IDS_NULL,       g_szNull,       sizeof(g_szNull));
   LoadString(g_hinst, IDS_ROWDELETED, g_szRowDeleted, sizeof(g_szRowDeleted));
   LoadString(g_hinst, IDS_UNKNOWN,    g_szUnknown,    sizeof(g_szUnknown));

   // Create main window in upper 3/4 of desktop
   GetWindowRect(GetDesktopWindow(), &rc);

   g_hwnd = CreateWindow(szFRAMECLASS,
                         g_szTITLE,
                         WS_OVERLAPPEDWINDOW,
                         rc.left,
                         rc.top,
                         rc.right - rc.left,
                         ((rc.bottom - rc.top) / 4) * 3,
                         HWND_DESKTOP,
                         g_hmenuInit,
                         g_hinst,
                         NULL);
   if (!g_hwnd)
      return FALSE;

   // Create fonts used in painting child windows
   hdc = GetDC(g_hwnd);

   g_hfontName = CreateFont((GetDeviceCaps(hdc, LOGPIXELSY) * cPOINTS) / 72,
                            0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0,
                            szFONT);

   hfont = SelectObject(hdc, g_hfontName);

   GetTextMetrics(hdc, &tm);
   g_cx = tm.tmMaxCharWidth;
   g_cy = tm.tmHeight + tm.tmInternalLeading;

   g_hfontData = CreateFont((GetDeviceCaps(hdc, LOGPIXELSY) * cPOINTS) / 72,
                            0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0,
                            szFONT);

   SelectObject(hdc, g_hfontData);

   // Determine font size characteristics
   GetTextMetrics(hdc, &tm);
   g_cx = max(g_cx, tm.tmMaxCharWidth);
   g_cy = max(g_cy, tm.tmHeight + tm.tmInternalLeading);

   GetTextExtentPoint(hdc, szRECORD, lstrlen(szRECORD), &size);
   g_cxRecord = size.cx;

   wsprintf(sz, szRECNUM, 999999);

   GetTextExtentPoint(hdc, sz, lstrlen(sz), &size);
   g_cxRecnum = size.cx;

   SelectObject(hdc, hfont);

   ReleaseDC(g_hwnd, hdc);

   // Allocate brushes
   g_hbrWin    = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
   g_hbrBtn    = CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
   g_hbrScroll = CreateSolidBrush(GetSysColor(COLOR_SCROLLBAR));

   // Allocate ODBC environment and connection handles; register as a 3.0 app
   if (ENVError(g_hwnd, SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HENV,&g_henv)))
      return FALSE;
   if (ENVError(g_hwnd, SQLSetEnvAttr(g_henv, SQL_ATTR_ODBC_VERSION,
                                      (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER)))
      return FALSE;
   if (ENVError(g_hwnd, SQLAllocHandle(SQL_HANDLE_DBC,g_henv, &g_hdbc)))
      return FALSE;

   // Always use the cursor library
   if (DBCError(g_hwnd, SQLSetConnectAttr(   g_hdbc,
                                          SQL_ATTR_ODBC_CURSORS,
                                          (void *)SQL_CUR_USE_ODBC,0))) {
      return FALSE;
   }




   // Complete variable initialization
   g_cbName          = 0;
   g_fConnected      = FALSE;
   g_fAsyncSupported = FALSE;
   g_szDSN[0]        = '\0';
   g_cChild          = 0;
   g_cCursor         = 0;

   g_mrows      = 1000;

   g_hwndClient = GetWindow(g_hwnd, GW_CHILD);

   // Set initial menu state
   AdjustMenus();

   // Show frame window
   ShowWindow(g_hwnd, nCmdShow);
   UpdateWindow(g_hwnd);
   return TRUE;
}


/* ODBCError ---------------------------------------------------------------
   Description: Fetch and display an ODBC error message
                NOTE: SQL_NO_DATA and SQL_STILL_EXECUTING are
                      not considered errors
                      --------------------------------------------------------------------------*/
BOOL INTFUNC ODBCError(HWND hwnd, SWORD fHandleType, SQLHANDLE handle, SQLRETURN rc)
{
   if (rc == SQL_SUCCESS)
      return FALSE;

   if (rc == SQL_NO_DATA) {
      DoMessage(hwnd, IDS_NODATAFOUND);
      return FALSE;
   }

   if (rc == SQL_STILL_EXECUTING) {
      DoMessage(hwnd, IDS_STILLEXEC);
      return FALSE;
   }

   {
      SDWORD   fNative;
      SWORD cbError;
      LPSTR lpszFmt;
      LPSTR lpszSQLState;
      LPSTR lpszError;
      LPSTR lpsz;
      SWORD sMsgNum = 1;

      // Allocate storage
      lpsz = AllocPtr(1024 + cbSTRLEN + 6 + SQL_MAX_MESSAGE_LENGTH);

      lpszFmt      = lpsz + 1024;
      lpszSQLState = lpszFmt + cbSTRLEN;
      lpszError    = lpszSQLState + 6;
      LoadString(g_hinst, IDS_MSGFMT, lpszFmt, cbSTRLEN);

      // sometimes handle comes in as NULL
      if (handle) {
         // Retrieve and display errors until there are no more
         while (SQLGetDiagRec(fHandleType, handle, sMsgNum++,
                              (UCHAR FAR *)lpszSQLState,
                              &fNative,
                              (UCHAR FAR *)lpszError,
                              SQL_MAX_MESSAGE_LENGTH-1,
                              &cbError) != SQL_NO_DATA) {
            if (lstrcmpi(lpszSQLState, szDATATRUNC)) {
               wsprintf(lpsz, lpszFmt, lpszSQLState, fNative, lpszError);

               MessageBox(hwnd, lpsz, g_szTITLE,
                          strncmp(lpszSQLState, "01", 2)
                          ? MB_ICONSTOP | MB_OK
                          : MB_ICONINFORMATION | MB_OK);
            }
         }
      }
      else {
         MessageBox(hwnd, "Invalid handle", g_szTITLE,
                    MB_ICONSTOP | MB_OK);
      }

      // Free storage
      FreePtr(lpsz);
   }

   return (!SUCCESS(rc));
}


/* WinMain -----------------------------------------------------------------
   Description: Standard WinMain function
   --------------------------------------------------------------------------*/
int INTFUNC WinMain(HINSTANCE   hinstCur,
                    HINSTANCE   hinstPrev,
                    LPSTR       lpszCmdLine,
                    int         nCmdShow)
{
   MSG msg;

   UNREF_PARAM(lpszCmdLine);
   g_hinst = hinstCur;

   if (!hinstPrev)
      if (!InitApplication())
         return (FALSE);

   if (!InitInstance(nCmdShow)) {
      EndInstance();
      return (FALSE);
   }

   while (GetMessage(&msg, (HWND)NULL, (UINT)NULL, (UINT)NULL))
      if (!TranslateMDISysAccel(g_hwndClient, &msg) &&
          !TranslateAccelerator(g_hwnd, g_haccel, &msg) &&
          (!(g_hwndChildDialog) || (!IsDialogMessage(g_hwndChildDialog, &msg)))) {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }

   EndInstance();

   return msg.wParam;
}
