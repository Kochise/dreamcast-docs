/*--------------------------------------------------------------------------
  Child.C --- Cursors child window procedure

  Description:
   This sample is spread across four files, each named for the role
   the contained functions play.  Each file header contains a brief
   description of its purpose and the routines it contains.

   CHILD.C contains those routines which maintain a child window.
   These include most interfaces with ODBC including all data
   retrieval and display.  These functions are:

     AllocChild      - Allocate and prepare child window memory
     AllocClipRgn    - Allocate clip region for painting
     Cancel          - Cancel SQL request
     CancelSQL       - Cancel asynchronous SQL request
     ChildProc       - Process child window messages
     CvtSqlToCType   - Return the default ODBC C type for a SQL type
     DeleteRow       - Build and issue a positioned delete
     DoChildMenu     - Process a menu request
     DoSQL           - Issue SQL statement and prepare all required
                       variables necessary for displaying the data
     Fetch           - Retrieve one row set
     FreeStmt        - Issue ODBC SQLFreeStmt (and adjust child memory)
     GetCurrentValue - Retrieve (in character format) column value
                       from current row (used by DIALOGS.C)
     GetData         - Issue a SQLGetData request
     GetTableName    - Extract table name from SQL
     IsUpdateable    - Check whether a column can be updated
     OnDataRow       - Determine if point is over displayed row of data
     PaintChild      - Paint child window
     ParamValid      - Validate the max column width of lpChild
     SetCurrentValue - Set a column value in the current row
                       (used by DIALOGS.C)
     SetPos          - Set current position in row set
     SetScroll       - Set scroll bar states and ranges
     SizeScroll      - Size and position scroll bars
     UpdateRow       - Build and issue a positioned update request

   This code is furnished on an as-is basis as part of the ODBC SDK and is
   intended for example purposes only.

--------------------------------------------------------------------------*/

/* Includes --------------------------------------------------------------*/
#include "headers.h"

#pragma warning(disable:4001)
#include   "resource.h"
#include   "crsrdemo.h"


// Constants ---------------------------------------------------------------
#define fDISABLED (MF_BYCOMMAND | MF_DISABLED | MF_GRAYED)
#define fENABLED  (MF_BYCOMMAND | MF_ENABLED)
#define NULLIFEMPTY(x) (*x?x:NULL)

const char szDELETE[]       = "DELETE FROM ";
const char szFROM[]         = "FROM";
const char szUPDATE[]       = "UPDATE ";
const char szWHERE[]        = " WHERE CURRENT OF ";
const char szNoDataTitle[]  = "No data to display";
const char szNoData[]       = "The query didn't return any data";
const char szSET[]          = " SET ";
const char szDataAffected[] = "%ld rows were affected";
const char szRowAffected[]  = "%ld row was affected";

const int   cMAXCOLS   = 15;

#define Async(x)     lpChild->fCanceled = FALSE;               \
                     while ((rc = (x)) == SQL_STILL_EXECUTING) \
                     CancelSQL(lpChild);

#define STMTError(x) ODBCError(lpChild->hwnd, SQL_HANDLE_STMT, lpChild->hstmt, (x))


// Prototypes --------------------------------------------------------------
LPCHILD INTFUNC AllocChild(HWND);
void    INTFUNC AllocClipRgn(LPCHILD);
void    INTFUNC Cancel(LPCHILD);
void    INTFUNC CancelSQL(LPCHILD);
SWORD   INTFUNC CvtSqlToCType(SWORD);
void    INTFUNC DeleteRow(LPCHILD);
BOOL    INTFUNC DoChildMenu(LPCHILD, WPARAM, LPARAM);
void    INTFUNC DoSQL(LPCHILD);
void    INTFUNC Fetch(LPCHILD);
void    INTFUNC FreeStmt(UWORD, LPCHILD);
void    INTFUNC GetData(LPCHILD);
void    INTFUNC GetTableName(LPSTR, LPCSTR);
int     INTFUNC OnDataRow(LPCHILD, LPARAM);
void    INTFUNC PaintChild(LPCHILD, HDC, BOOL, BOOL, BOOL);
BOOL    INTFUNC  ParamValid(LPCHILD);
void    INTFUNC SetPos(LPCHILD, UWORD);
void    INTFUNC SetScroll(LPCHILD);
void    INTFUNC SizeScroll(LPCHILD);
void    INTFUNC UpdateRow(LPCHILD);
#ifdef THREAD
void    INTFUNC DeleteRowThread(LPCHILD);
void    INTFUNC DoSQLThread(LPCHILD);
void    INTFUNC FetchThread(LPCHILD);
void    INTFUNC GetDataThread(LPCHILD);
void    INTFUNC UpdateRowThread(LPCHILD);
#endif

/* AllocChild --------------------------------------------------------------
   Description: Allocate and initialize child variables
   --------------------------------------------------------------------------*/
LPCHILD INTFUNC AllocChild(HWND hwnd)
{
   SQLHSTMT hstmt;
   LPCHILD  lpChild;
   char  sz[cbSTRLEN];

   // Allocate ODBC SQLHSTMT and set cursor name
   if (DBCError(hwnd, SQLAllocHandle(SQL_HANDLE_STMT,g_hdbc, &hstmt)))
      return NULL;

#ifdef THREAD
   wsprintf(sz, szTITLEFMT, (LPSTR)g_szDSN, g_cCursor, GetCurrentThreadId());
#else
   wsprintf(sz, szTITLEFMT, (LPSTR)g_szDSN, g_cCursor);
#endif

   SetWindowText(hwnd, sz);

   wsprintf(sz, szCURSORNAME, g_cCursor);
   if (ODBCError(hwnd, SQL_HANDLE_STMT, hstmt,
                 SQLSetCursorName(hstmt, (UCHAR FAR *)sz, SQL_NTS)))
      return NULL;

   // Allocate child window structure and initialize
   lpChild = (LPCHILD)AllocPtr(sizeof(CHILD));

   lpChild->hwnd             = hwnd;
   lpChild->fInSetScroll     = FALSE;
   lpChild->fIsMinimized     = FALSE;
   lpChild->fHaveMouse       = FALSE;
   lpChild->iMouseRow        = -1;
   lpChild->fNoConcurrency   = FALSE;
   lpChild->fNoCursorType    = FALSE;

   lpChild->ccols            = 0;
   lpChild->crowwin          = 0;
   lpChild->ccolwin          = 0;
   lpChild->fVScroll         =
      lpChild->fHScroll         = FALSE;
   lpChild->lpsz             = AllocPtr(cbBUFSIZE);

   lpChild->hrgn             = NULL;

   lpChild->hstmt            = hstmt;
   lpChild->hstmtTmp         = SQL_NULL_HSTMT;

   lpChild->fBindByRow       = IDC_RADIO_BINDROW;
   lpChild->fConcurrency     = SQL_CONCUR_VALUES;
   lpChild->crowKeyset       = SQL_CURSOR_STATIC;
   lpChild->crowRowset       = 10;
   lpChild->fAsync           = FALSE;
   lpChild->irowPos          = 0;
   lpChild->irow             = 0;
   lpChild->cBind            = 0;
   lpChild->fBindAll         = TRUE;
   lpChild->ccolRetrieved    = 0;

   lpChild->arow             = 1;
   lpChild->rrow             = 10;
   lpChild->ccol             = 0;
   lpChild->lpnTabs          = NULL;
   lpChild->lpcol            = NULL;
   lpChild->lpfStatus        = NULL;
   lpChild->fResultSetExists = FALSE;
   lpChild->fDataFetched     = FALSE;
   lpChild->rglpv            = NULL;
   lpChild->crowMaxBind      = DEF_MAXBIND;

   lpChild->lpb              = NULL;
   lpChild->sql              = AllocPtr(cbMAXSQL);
   lpChild->cbrow            = 0;
   lpChild->dwGuiFlags       = GUIF_ALWAYSFETCH;
#ifdef THREAD
   InitializeCriticalSection (&lpChild->ThreadCreation);
#endif

   // Create scroll bars
   lpChild->hwndVScroll = CreateWindow(szSCROLLCLASS, NULL,
                                       WS_CHILD | SBS_VERT,
                                       0, 0, 0, 0,
                                       hwnd, (HMENU)1, g_hinst, NULL);

   lpChild->hwndHScroll = CreateWindow(szSCROLLCLASS, NULL,
                                       WS_CHILD | SBS_HORZ,
                                       0, 0, 0, 0,
                                       hwnd, (HMENU)2, g_hinst, NULL);

   // Load default SQL string
   LoadString(g_hinst, IDS_SQL, sz, cbSTRLEN);
   wsprintf(lpChild->sql, sz, g_szTable);

   return lpChild;
}


/* AllocClipRgn ------------------------------------------------------------
   Description: Allocate child window clip region
   --------------------------------------------------------------------------*/
void INTFUNC AllocClipRgn(LPCHILD lpChild)
{
   RECT  rc;

   // Determine client window size less space for scroll bars
   GetClientRect(lpChild->hwnd, &rc);

   if (lpChild->hrgn) DeleteObject(lpChild->hrgn);

   if (lpChild->fVScroll)
      rc.right -= g_cxVScroll - 1;
   rc.bottom -= g_cyHScroll - 1;

   // Allocate clip region
   lpChild->hrgn = CreateRectRgn(rc.left,
                                 rc.top,
                                 rc.right,
                                 rc.bottom);
   return;
}


/* CancelSQL ---------------------------------------------------------------
   Description: Display message while an async request is executing and
                give the user a chance to cancel the request (if it has
                not already been canceled)
                --------------------------------------------------------------------------*/
void INTFUNC CancelSQL(LPCHILD lpChild)
{
   char  sz[cbSTRLEN];
   int   rc;

   // Display message
   LoadString(g_hinst, IDS_STILLEXEC, sz, sizeof(sz));
   rc = MessageBox(lpChild->hwnd,
                   sz, g_szTITLE,
                   MB_ICONINFORMATION |
                   (lpChild->fCanceled
                    ? MB_OK
                    : MB_OKCANCEL | MB_DEFBUTTON1));

   // If the user requested, cancel the current request
   if (rc == IDCANCEL)
      lpChild->fCanceled = SUCCESS(SQLCancel(lpChild->hstmt));

   return;
}


/* ChildProc ---------------------------------------------------------------
   Description: Child window procedure
   --------------------------------------------------------------------------*/
LRESULT EXPFUNC ChildProc(HWND    hwnd,
                          UINT   msg,
                          WPARAM wparam,
                          LPARAM lparam)
{
   LPCHILD  lpChild;

   // Get access to child variables and set current window handle
   lpChild = (LPCHILD)GetWindowLong(hwnd, 0);

   switch (msg) {

      // Allocate child variables and save pointer
     case WM_CREATE:
      lpChild = AllocChild(hwnd);

      SetWindowLong(hwnd, 0, (LONG)lpChild);

      if (!lpChild)
         return -1;
      break;

      // Paint child window (active or inactive)
     case WM_PAINT: {
        PAINTSTRUCT ps;
        BOOL     fActive;

        fActive = (hwnd ==
                   FORWARD_WM_MDIGETACTIVE(g_hwndClient, SendMessage));

        BeginPaint(hwnd, &ps);
        PaintChild(lpChild, ps.hdc, TRUE, FALSE, fActive);
        EndPaint(hwnd, &ps);
        break;
     }

      // Trap mouse if over a rowset row
     case WM_LBUTTONDOWN:
      lpChild->iMouseRow = OnDataRow(lpChild, lparam);
      if (lpChild->iMouseRow >= 0) {
         lpChild->fHaveMouse = TRUE;
         SetCapture(hwnd);
      }
      break;

      // Make row current row (if mouse is still on the row)
     case WM_LBUTTONUP:
      if (!lpChild->fHaveMouse)
         break;

      ReleaseCapture();
      lpChild->fHaveMouse = FALSE;

      if (lpChild->fDataFetched                         &&
          lpChild->fConcurrency != SQL_CONCUR_READ_ONLY &&
          lpChild->crowKeyset != SQL_CURSOR_FORWARD_ONLY &&
          lpChild->iMouseRow    == OnDataRow(lpChild, lparam)) {
         RECT  rc;
         int   y;

         GetClientRect(hwnd, &rc);

         y = (int)HIWORD(lparam) - rc.top - g_cy;

         SetPos(lpChild,
                (UWORD)(GetScrollPos(lpChild->hwndVScroll, SB_CTL) + (y / g_cy) + 1));
      }
      break;

      // Convert keyboard requests to scroll and change window requests
     case WM_KEYDOWN:
      if (wparam == VK_TAB) {
         FORWARD_WM_MDINEXT(g_hwndClient, hwnd,
                            (GetKeyState(VK_BACK) & 0x1000 ? TRUE :FALSE),
                            SendMessage);
         break;
      }

      else if (wparam == VK_DOWN || wparam == VK_UP) {

         msg    = WM_VSCROLL;
         GET_WM_VSCROLL_CODE(wparam, lparam) =
            (wparam == VK_DOWN
             ? SB_LINEDOWN
             : SB_LINEUP);
      }
      else if (wparam == VK_LEFT || wparam == VK_RIGHT) {
         if (!lpChild->fHScroll)
            break;

         msg    = WM_HSCROLL;
         GET_WM_HSCROLL_CODE(wparam, lparam) =
            (wparam == VK_RIGHT
             ? SB_LINEDOWN
             : SB_LINEUP);
      }
      else
         break;

      // Scroll window
     case WM_HSCROLL:
     case WM_VSCROLL: {
        HWND  hwndCtl;
        int   cInc;
        int   iPos;
        int   cPage;
        int   nPos;
        int   iOrig;
        int   nMin, nMax;

        if (!lpChild->fDataFetched)
           break;

        // Determine scroll direction and distance
        hwndCtl = (msg == WM_HSCROLL
                   ? lpChild->hwndHScroll
                   : lpChild->hwndVScroll);
        cInc    = (msg == WM_HSCROLL ? 1 : 1);
        cPage   = (msg == WM_HSCROLL
                   ? lpChild->ccolwin
                   : lpChild->crowwin - 1);
        nPos    = GET_WM_HSCROLL_POS(wparam, lparam);
        iPos    =
           iOrig   = GetScrollPos(hwndCtl, SB_CTL);

        GetScrollRange(hwndCtl, SB_CTL, &nMin, &nMax);
        switch (GET_WM_HSCROLL_CODE(wparam, lparam)) {
          case SB_BOTTOM:        iPos = nMax;  break;
          case SB_LINEDOWN:      iPos+= cInc;  break;
          case SB_LINEUP:        iPos-= cInc;  break;
          case SB_PAGEDOWN:      iPos+= cPage; break;
          case SB_PAGEUP:        iPos-= cPage; break;
          case SB_TOP:           iPos = nMin;  break;
          case SB_THUMBPOSITION: iPos = nPos;  break;
        }

        // For updateable cursors, vertical scroll requests move the
        // current row scroll the window only as needed to keep the
        // current row visible
        if (msg == WM_VSCROLL &&
            lpChild->crowKeyset != SQL_CURSOR_FORWARD_ONLY &&
            lpChild->fConcurrency != SQL_CONCUR_READ_ONLY) {
           int   delta;

           if (GET_WM_HSCROLL_CODE(wparam, lparam) == SB_LINEDOWN)
              delta = cInc;
           else if (GET_WM_HSCROLL_CODE(wparam, lparam) == SB_LINEUP)
              delta = -cInc;
           else if (GET_WM_HSCROLL_CODE(wparam, lparam) == SB_PAGEDOWN) {
              if (iPos <= nMax)
                 delta = cPage;
              else
                 delta = lpChild->crowRowset - lpChild->irowPos;
           }
           else if (GET_WM_HSCROLL_CODE(wparam, lparam) == SB_PAGEUP) {
              if (iPos >= nMin)
                 delta = -cPage;
              else
                 delta = 1 - lpChild->irowPos;
           }
           else if (GET_WM_HSCROLL_CODE(wparam, lparam) == SB_BOTTOM)
              delta = lpChild->crowRowset - lpChild->irowPos;
           else if (GET_WM_HSCROLL_CODE(wparam, lparam) == SB_TOP)
              delta = 1 - lpChild->irowPos;
           else if (GET_WM_HSCROLL_CODE(wparam, lparam) == SB_THUMBPOSITION) {
              if (lpChild->irowPos > (UWORD)iPos &&
                  lpChild->irowPos < (UWORD)(iPos+lpChild->crowwin))
                 delta = 0;
              else if (iPos == nMin)
                 delta = 1 - lpChild->irowPos;
              else if (iPos == nMax)
                 delta = lpChild->crowRowset - lpChild->irowPos;
              else if (iPos <= iOrig)
                 delta = iPos + lpChild->crowwin - 1 - lpChild->irowPos;
              else
                 delta = iPos - lpChild->irowPos + 1;
           }
           else
              break;

           SetPos(lpChild, (UWORD)(lpChild->irowPos + delta));

           if ((GET_WM_HSCROLL_CODE(wparam, lparam) == SB_LINEDOWN ||
                GET_WM_HSCROLL_CODE(wparam, lparam) == SB_LINEUP) &&
               lpChild->irowPos > (UWORD)iOrig                &&
               lpChild->irowPos < (UWORD)(iOrig+lpChild->crowwin))
              break;
        }

        // Pin scroll requests within scroll boundaries
        if (iPos < nMin)
           iPos = nMin;
        else if (iPos > nMax)
           iPos = nMax;

        // Scroll the window if movement has occurred
        if (iPos != iOrig) {
           HDC      hdc;
           BOOL  fTitle;

           hdc = GetDC(hwnd);

           SetScrollPos(hwndCtl, SB_CTL, iPos, TRUE);

           fTitle = (msg == WM_HSCROLL);

           PaintChild(lpChild, hdc, fTitle, FALSE, TRUE);

           ReleaseDC(hwnd, hdc);
        }
        break;
     }

      // Activate the child window
     case WM_MDIACTIVATE: {
        HDC   hdc;

        AdjustMenus();

        hdc = GetDC(hwnd);

        PaintChild(lpChild, hdc, TRUE, TRUE,
                   GET_WM_MDIACTIVATE_FACTIVATE(lpChild->hwnd, wparam, lparam));

        ReleaseDC(lpChild->hwnd, hdc);
        break;
     }

      // Free all child memory
     case WM_DESTROY:
      if (lpChild) {
         FreeStmt(SQL_DROP, lpChild);

         FreePtr(lpChild->lpsz);
         FreePtr(lpChild->sql);
#ifdef THREAD
         DeleteCriticalSection (&lpChild->ThreadCreation);
#endif
         FreePtr(lpChild);

         SetWindowLong(hwnd, 0, 0L);
      }
      break;

      // Close the window
     case WM_CLOSE:
      g_cChild--;

      if( !g_cChild )
#ifdef WIN32
         SendMessage(g_hwndClient, WM_MDISETMENU,
                     (WPARAM)g_hmenuFrame,
                     (LPARAM)g_hmenuFrameWindow);
#else
      FORWARD_WM_MDISETMENU(g_hwndClient, 0, g_hmenuFrame,
                            g_hmenuFrameWindow, SendMessage);
#endif

      // Destroy child window
      FORWARD_WM_MDIDESTROY(g_hwndClient, hwnd, SendMessage);
      AdjustMenus();
      break;

      // Pass all other messages (eventually) to the MDI window procedure
     default:

      // Reset scroll bars (if needed) when the window is resized
      if (msg == WM_SIZE) {

         if (wparam == SIZE_MINIMIZED)
            lpChild->fIsMinimized = TRUE;

         else {
            if (lpChild->fIsMinimized)
               lpChild->fIsMinimized = FALSE;

            SizeScroll(lpChild);

            if (lpChild->fDataFetched) {
               int   row;

               SetScroll(lpChild);

               row = GetScrollPos(lpChild->hwndVScroll, SB_CTL);

               if (lpChild->fConcurrency != SQL_CONCUR_READ_ONLY &&
                   lpChild->irowPos >= (UWORD)(row+lpChild->crowwin))
                  if (lpChild->crowwin > 1)
                     SetScrollPos(lpChild->hwndVScroll,
                                  SB_CTL,
                                  lpChild->irowPos-lpChild->crowwin+1,
                                  TRUE);
                  else
                     SetScrollPos(lpChild->hwndVScroll,
                                  SB_CTL,
                                  lpChild->irowPos-lpChild->crowwin,
                                  TRUE);
            }

            AllocClipRgn(lpChild);
         }

         InvalidateRect(hwnd, NULL, TRUE);
      }

      // Handle child window menu requests
      else if (msg == WM_COMMAND)
         DoChildMenu(lpChild, wparam, lparam);

      // Pass message on to the MDI window procedure
      return DefMDIChildProc(hwnd, msg, wparam, lparam);
   }

   return (LRESULT)NULL;
}


/* CvtSqlToCType -----------------------------------------------------------
   Description: Determine the default ODBC C type for a given SQL type
   --------------------------------------------------------------------------*/
SWORD INTFUNC CvtSqlToCType(SWORD fSqlType)
{
   switch (fSqlType) {
     case SQL_CHAR:
     case SQL_VARCHAR:
     case SQL_LONGVARCHAR:
     case SQL_DECIMAL:
     case SQL_NUMERIC:
     case SQL_BIGINT:           return SQL_C_CHAR;

     case SQL_BIT:              return SQL_C_BIT;
     case SQL_TINYINT:
     case SQL_SMALLINT:         return SQL_C_SHORT;
     case SQL_INTEGER:          return SQL_C_LONG;
     case SQL_REAL:             return SQL_C_FLOAT;

     case SQL_FLOAT:
     case SQL_DOUBLE:           return SQL_C_DOUBLE;

     case SQL_BINARY:
     case SQL_VARBINARY:
     case SQL_LONGVARBINARY:    return SQL_C_BINARY;

     case SQL_TYPE_DATE:        return SQL_C_TYPE_DATE;
     case SQL_TYPE_TIME:        return SQL_C_TYPE_TIME;
     case SQL_TYPE_TIMESTAMP:   return SQL_C_TYPE_TIMESTAMP;

     case SQL_DATE:             return SQL_C_DATE;
     case SQL_TIME:             return SQL_C_TIME;
     case SQL_TIMESTAMP:        return SQL_C_TIMESTAMP;
   }

   return SQL_C_CHAR;
}


/* DeleteRow ---------------------------------------------------------------
   Description: Delete the current (positioned) row
   --------------------------------------------------------------------------*/
void INTFUNC DeleteRow(LPCHILD lpChild)
{
   HCURSOR  hcur;
   LPSTR    lpsz;
   LPSTR    lpszT;
   SWORD    cb;

   // Ensure the delete request is valid
   if (!lpChild->fDataFetched) {
      DoMessage(lpChild->hwnd, IDS_NODATAFETCHED);
      return;
   }

   if (*(lpChild->lpfStatus + lpChild->irowPos - 1) == SQL_ROW_NOROW) {
      DoMessage(lpChild->hwnd, IDS_NOROWDELETE);
      return;
   }

   if (*(lpChild->lpfStatus + lpChild->irowPos - 1) == SQL_ROW_ERROR) {
      DoMessage(lpChild->hwnd, IDS_ERRORROWDELETE);
      return;
   }

   if (*(lpChild->lpfStatus + lpChild->irowPos - 1) == SQL_ROW_DELETED) {
      DoMessage(lpChild->hwnd, IDS_DELROWDELETE);
      return;
   }

   if (lpChild->fConcurrency == SQL_CONCUR_READ_ONLY) {
      DoMessage(lpChild->hwnd, IDS_NOUPDATE);
      return;
   }

   lpsz  = AllocPtr(2 * cbMAXSQL);
   lpszT = lpsz + cbMAXSQL;

   // Verify the request and allocate a new (temporary) SQLHSTMT for the delete
   LoadString(g_hinst, IDS_DELETEROW, lpsz, cbMAXSQL);
   if (IDYES == MessageBox(lpChild->hwnd, lpsz,
                           g_szTITLE, MB_ICONQUESTION | MB_YESNO) &&
       !DBCError(lpChild->hwnd, SQLAllocHandle(SQL_HANDLE_STMT,g_hdbc, &lpChild->hstmtTmp))) {

      // Build DELETE <table> WHERE CURRENT OF <cursor> statement
      lstrcpy(lpsz, szDELETE);

      GetTableName(lpszT, lpChild->sql);
      lstrcat(lpsz, lpszT);

      lstrcat(lpsz, szWHERE);

      lpszT = lpsz + lstrlen(lpsz);

      hcur = SetCursor(LoadCursor(NULL, IDC_WAIT));

      if (!STMTError(SQLGetCursorName(lpChild->hstmt, (UCHAR FAR *)lpszT,
                                      cbMAXSQL, &cb))) {

         // Issue the request via SQLPrepare/SQLExecute
         if (!ODBCError(lpChild->hwnd, SQL_HANDLE_STMT, lpChild->hstmtTmp,
                        SQLPrepare(lpChild->hstmtTmp, (UCHAR FAR *)lpsz, SQL_NTS)) &&
             !ODBCError(lpChild->hwnd, SQL_HANDLE_STMT, lpChild->hstmtTmp,
                        SQLExecute(lpChild->hstmtTmp)) ) {
            UWORD irowPos;

            irowPos = lpChild->irowPos;

            // Completely refresh local rowset buffer
            lpChild->rrow = 0;
            lpChild->FetchOP = SQL_FETCH_RELATIVE;
            Fetch(lpChild);

            // Reset current position (fetching sets it to the first row)
            SetPos(lpChild, irowPos);

            // Repaint window
            InvalidateRect(lpChild->hwnd, NULL, FALSE);
         }
      }

      DBCError(lpChild->hwnd, SQLFreeHandle(SQL_HANDLE_STMT,lpChild->hstmtTmp));
      lpChild->hstmtTmp = SQL_NULL_HSTMT;

      SetCursor(hcur);

   }

   FreePtr(lpsz);

   return;
}


/* DoChildMenu -------------------------------------------------------------
   Description: Respond to a request from the child window menu
   --------------------------------------------------------------------------*/
BOOL INTFUNC DoChildMenu(LPCHILD lpChild, WPARAM  wParam, LPARAM  lParam)
{
   UNREF_PARAM (lParam);
   switch (GET_WM_COMMAND_ID(wParam, lparam)) {

     case IDM_STMT_SEND:
      if (IDOK == DoDialog(lpChild->hwnd, IDD_STATEMENT, StmtDlgProc))
#ifdef THREAD
         DoSQLThread(lpChild);
#else
      DoSQL(lpChild);
#endif
      break;

     case IDM_STMT_TABLE:
      if (IDOK == DoDialog(lpChild->hwnd, IDD_TABLE_INFO, SQLTablesDlgProc))
#ifdef THREAD
         DoSQLThread(lpChild);
#else
      DoSQL(lpChild);
#endif
      break;

     case IDM_STMT_TYPE:
      lpChild->dwOperation = OPER_TYPES;
#ifdef THREAD
      DoSQLThread(lpChild);
#else
      DoSQL(lpChild);
#endif
      break;



     case IDM_STMT_OPTIONS:     // general
      {
         CHILD    ChildOld;

         // save old values (only works because no pointers
         // get modified in options)

         memcpy(&ChildOld, lpChild, sizeof(ChildOld));
         // no modification on those option values yet
         lpChild->fBind =
            lpChild->fMaxBind =
               lpChild->fRowset = FALSE;

         if (IDOK == DoDialog(lpChild->hwnd, IDD_OPTION_DIALOG,
                              OptionsDlgProc) && ParamValid(lpChild)) {
            if (lpChild->fDataFetched) {
               FreeStmt(SQL_CLOSE,  lpChild);
               FreeStmt(SQL_UNBIND, lpChild);
            }
         }
         else {
            // restore previous state
            memcpy(lpChild, &ChildOld, sizeof(ChildOld));
         }
         break;
      }

     case IDM_STMT_CANCEL:      // general
      Cancel(lpChild);
      break;

     case IDM_FETCH_FIRST:
      lpChild->FetchOP = SQL_FETCH_FIRST;
#ifdef THREAD
      FetchThread(lpChild);
#else
      Fetch(lpChild);
#endif
      break;

     case IDM_FETCH_PRIOR:
      lpChild->FetchOP = SQL_FETCH_PRIOR;
#ifdef THREAD
      FetchThread(lpChild);
#else
      Fetch(lpChild);
#endif
      break;

     case IDM_FETCH_NEXT:
      lpChild->FetchOP = SQL_FETCH_NEXT;
#ifdef THREAD
      FetchThread(lpChild);
#else
      Fetch(lpChild);
#endif
      break;

     case IDM_FETCH_LAST:
      lpChild->FetchOP = SQL_FETCH_LAST;
#ifdef THREAD
      FetchThread(lpChild);
#else
      Fetch(lpChild);
#endif
      break;

     case IDM_FETCH_ABSOLUTE:
      if (IDOK == DoDialog(lpChild->hwnd, IDD_ABSOLUTE, AbsDlgProc)) {
         lpChild->FetchOP = SQL_FETCH_ABSOLUTE;
#ifdef THREAD
         FetchThread(lpChild);
#else
         Fetch(lpChild);
#endif
      }
      break;

     case IDM_FETCH_RELATIVE:
      if (IDOK == DoDialog(lpChild->hwnd, IDD_RELATIVE, RelDlgProc)) {
         lpChild->FetchOP = SQL_FETCH_RELATIVE;
#ifdef THREAD
         FetchThread(lpChild);
#else
         Fetch(lpChild);
#endif
      }
      break;

     case IDM_FETCH_GET:
#ifdef THREAD
      GetDataThread(lpChild);
#else
      GetData(lpChild);
#endif
      break;

     case IDM_FETCH_DELETEROW:
#ifdef THREAD
      DeleteRowThread(lpChild);
#else
      DeleteRow(lpChild);
#endif
      break;

     case IDM_FETCH_UPDATEROW:
#ifdef THREAD
      UpdateRowThread(lpChild);
#else
      UpdateRow(lpChild);
#endif
      break;
     default:
      return FALSE;
   }

   AdjustMenus();
   return TRUE;
}

#ifdef THREAD
void INTFUNC DoSQLThread(LPCHILD lpChild)
{
   DWORD dwThreadId;

   EnterCriticalSection (&lpChild->ThreadCreation);
   lpChild->hThread = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)DoSQL,
                                    (LPVOID)lpChild, 0, &dwThreadId);
   LeaveCriticalSection (&lpChild->ThreadCreation);
}

void INTFUNC FetchThread(LPCHILD lpChild)
{
   DWORD dwThreadId;

   EnterCriticalSection (&lpChild->ThreadCreation);
   lpChild->hThread = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)Fetch,
                                    (LPVOID)lpChild, 0, &dwThreadId);
   LeaveCriticalSection (&lpChild->ThreadCreation);
}

void INTFUNC GetDataThread(LPCHILD lpChild)
{
   DWORD dwThreadId;

   EnterCriticalSection (&lpChild->ThreadCreation);
   lpChild->hThread = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)GetData,
                                    (LPVOID)lpChild, 0, &dwThreadId);
   LeaveCriticalSection (&lpChild->ThreadCreation);
}

void INTFUNC UpdateRowThread(LPCHILD lpChild)
{
   DWORD dwThreadId;

   EnterCriticalSection (&lpChild->ThreadCreation);
   lpChild->hThread = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)UpdateRow,
                                    (LPVOID)lpChild, 0, &dwThreadId);
   LeaveCriticalSection (&lpChild->ThreadCreation);
}

void INTFUNC DeleteRowThread(LPCHILD lpChild)
{
   DWORD dwThreadId;

   EnterCriticalSection (&lpChild->ThreadCreation);
   lpChild->hThread = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)DeleteRow,
                                    (LPVOID)lpChild, 0, &dwThreadId);
   LeaveCriticalSection (&lpChild->ThreadCreation);
}
#endif


/* DoSQL -------------------------------------------------------------------
   Description: Issue a SQL statement and prepare for fetching data
   --------------------------------------------------------------------------*/
void INTFUNC DoSQL(LPCHILD lpChild)
{
   SQLRETURN rc;

   // Prepare the statement

   if (PrepareStmt(lpChild) == SQL_ERROR)
      return;

   switch(lpChild->dwOperation) {
     case  OPER_SELECT:
      // Issue the request via SQLExecDirect
      Async(SQLExecDirect(lpChild->hstmt,
                          (UCHAR FAR *)lpChild->sql,
                          lstrlen(lpChild->sql)));
      break;

     case  OPER_TYPES:
      // Issue a GetTypeInfo request
      Async(SQLGetTypeInfo(lpChild->hstmt, SQL_ALL_TYPES));
      break;


     case  IDC_TABLE_RAD_TABLE:
      if (!*lpChild->szTable &&
          ((!*lpChild->szUser && strcmp(lpChild->szQualifier, "%") == 0)||
           (!*lpChild->szQualifier && strcmp(lpChild->szUser, "%") == 0))) {  // Special qualifier enumeration
         Async(SQLTables(lpChild->hstmt,
                         lpChild->szQualifier, SQL_NTS,
                         lpChild->szUser, SQL_NTS,
                         lpChild->szTable, SQL_NTS,
                         lpChild->szType,  SQL_NTS));
      }
      else
         {  // Normal SQLTables call
            Async(SQLTables(lpChild->hstmt,
                            NULLIFEMPTY(lpChild->szQualifier), SQL_NTS,
                            NULLIFEMPTY(lpChild->szUser), SQL_NTS,
                            NULLIFEMPTY(lpChild->szTable),  SQL_NTS,
                            NULLIFEMPTY(lpChild->szType),  SQL_NTS));
         }
      break;

     case  IDC_TABLE_RAD_PRIV:
      Async(SQLTablePrivileges(lpChild->hstmt,
                               NULLIFEMPTY(lpChild->szQualifier), SQL_NTS,
                               NULLIFEMPTY(lpChild->szUser), SQL_NTS,
                               NULLIFEMPTY(lpChild->szTable),  SQL_NTS));

      break;

     case  IDC_TABLE_RAD_STATISTICS:
      Async(SQLStatistics(lpChild->hstmt,
                          NULLIFEMPTY(lpChild->szQualifier), SQL_NTS,
                          NULLIFEMPTY(lpChild->szUser), SQL_NTS,
                          NULLIFEMPTY(lpChild->szTable),  SQL_NTS,
                          SQL_INDEX_ALL,      // XXX
                          SQL_QUICK));     // XXX
      break;



     case  IDC_TABLE_RAD_PROC:
      Async(SQLProcedures(lpChild->hstmt,
                          NULLIFEMPTY(lpChild->szQualifier), SQL_NTS,
                          NULLIFEMPTY(lpChild->szUser), SQL_NTS,
                          NULLIFEMPTY(lpChild->szTable),  SQL_NTS));

      break;

     case  IDC_TABLE_RAD_COLUMN:
      Async(SQLColumns(lpChild->hstmt,
                       NULLIFEMPTY(lpChild->szQualifier), SQL_NTS,
                       NULLIFEMPTY(lpChild->szUser), SQL_NTS,
                       NULLIFEMPTY(lpChild->szTable),  SQL_NTS,
                       NULLIFEMPTY(lpChild->szColName), SQL_NTS));

   }

   if (STMTError(rc))
      return;

   if (ProcessResults(lpChild)) {

      if (lpChild->dwGuiFlags & GUIF_ALWAYSFETCH) {
         lpChild->FetchOP = SQL_FETCH_NEXT;
         Fetch(lpChild);
      }
   }

   AdjustMenus();
   return;

}

/* ProcessResults---------------------------------------------------------------
   Description: Process the results from a query or statement
   --------------------------------------------------------------------------*/
BOOL INTFUNC ProcessResults(LPCHILD lpChild)
{
   LPINT     lptab;
   LPCOL     lpcol;
   LPBYTE    lpb;
   SDWORD    cbMsg;
   SDWORD    cbNull;
   int       nLastTab;
   SWORD     i;
   SQLRETURN rc;


   // Retrieve number of columns in the result set
   Async(SQLNumResultCols(lpChild->hstmt, &i));
   if (STMTError(rc))
      return FALSE;
   lpChild->ccol = ((UWORD)i < lpChild->cBind || lpChild->fBindAll
                    ? i
                    : lpChild->cBind);

   // If a result set exists, continue; otherwise, return immediately
   if (lpChild->ccol)
      lpChild->fResultSetExists = TRUE;
   else
      return FALSE;

   // Allocate painting related storage and row status array

   lpChild->rglpv     = (char *)AllocPtr(sizeof(char *) * lpChild->ccol);
   lpChild->lpnTabs   = (LPINT)AllocPtr(sizeof(int) * (lpChild->ccol+1));
   lpChild->lpcol     = (LPCOL)AllocPtr(sizeof(COL) * lpChild->ccol);
   lpChild->lpfStatus = (LPUWORD)AllocPtr((DWORD) sizeof(UWORD)
                                          * lpChild->crowRowset);

   for (i=1, lpcol=lpChild->lpcol; i <= lpChild->ccol; i++, lpcol++) {
      lpcol->lpb  = NULL;
      lpcol->lpcb = NULL;
   }

   cbMsg  = lstrlen(g_szRowDeleted);
   cbNull = lstrlen(g_szNull);
   cbMsg  = max(cbMsg, lstrlen(g_szNoRow));
   cbMsg  = max(cbMsg, cbNull);

   // Initialize row width (in bytes) and total number of characters per line
   lpChild->cbrow = 0;
   lpChild->ccols = 0;

   lpcol = lpChild->lpcol;
   lptab = lpChild->lpnTabs;

   nLastTab =
      *lptab++ = cxBORDER;

   // For each bound column
   //   a) Get column attributes (e.g., name, size, data type)
   //   b) Add column to physical and display row widths
   //   c) Determine tab location
   for (i=1; i <= lpChild->ccol; i++, lpcol++, lptab++) {

      // Get column name
      Async(SQLColAttribute(lpChild->hstmt, i,
                            SQL_DESC_NAME,
                            lpcol->szName, sizeof(lpcol->szName), NULL,
                            NULL));
      if (STMTError(rc)) {
         FreeStmt(SQL_DROP, lpChild);
         return FALSE;
      }

      // Get actual column length (number of physical data bytes)
		// if the sample were to be used with a 3.0 driver only SQLColAttribute
		// with fattribute of SQL_DESC_OCTECT_LENGTH could be called instead.
		 Async(SQLColAttributes(lpChild->hstmt, i,
                            SQL_COLUMN_LENGTH,
                            NULL, 0, NULL,
                            &lpcol->cb));


      if (STMTError(rc)) {
         FreeStmt(SQL_DROP, lpChild);
         return FALSE;
      }

      // Get display width
      Async(SQLColAttribute(lpChild->hstmt, i,
                            SQL_DESC_DISPLAY_SIZE,
                            NULL, 0, NULL,
                            &lpcol->cbc));
      if (STMTError(rc)) {
         FreeStmt(SQL_DROP, lpChild);
         return FALSE;
      }


      // if the display size is too big, force to the the maximum
      if (lpcol->cbc > lpChild->crowMaxBind)
         lpcol->cbc = lpChild->crowMaxBind;

      // Ensure display width is wide enough for:
      //   a) Column name
      //   b) Null string
      //   c) Row status (for the first column only)
      if (lpcol->cbc < cbMsg)
         lpcol->cbc = cbMsg;

      if (lstrlen(lpcol->szName) > lpcol->cbc)
         lpcol->cbc = lstrlen(lpcol->szName);

      lpcol->cbc++;

      // Get column SQL type
      Async(SQLColAttribute(lpChild->hstmt, i,
                            SQL_DESC_CONCISE_TYPE,
                            NULL, 0, NULL,
                            (SDWORD FAR*) &lpcol->fSqlType));
      if (STMTError(rc)) {
         FreeStmt(SQL_DROP, lpChild);
         return FALSE;
      }

      // Determine target C type
      lpcol->fCType = CvtSqlToCType(lpcol->fSqlType);

      // For hard to handle C types, let the driver convert to character
      if (lpcol->fCType == SQL_C_BIT    ||
          lpcol->fCType == SQL_C_BINARY ||
          lpcol->fCType == SQL_C_DATE   ||
          lpcol->fCType == SQL_C_TIME   ||
          lpcol->fCType == SQL_C_TIMESTAMP ||
          lpcol->fCType == SQL_C_TYPE_DATE   ||
          lpcol->fCType == SQL_C_TYPE_TIME   ||
          lpcol->fCType == SQL_C_TYPE_TIMESTAMP) {
         lpcol->fCType = SQL_C_CHAR;
         lpcol->cb = lpcol->cbc;
      }

      // Determine next column tab (based on column width plus border)
      nLastTab =
         *lptab    = nLastTab + ((int)lpcol->cbc * g_cx) + (2 * cxBORDER);

      // Set maximum column length for character data
      if( lpcol->cb > lpChild->crowMaxBind &&
         lpcol->fCType == SQL_C_CHAR )
         lpcol->cb = lpChild->crowMaxBind;

      if( lpcol->fCType == SQL_C_CHAR )
         lpcol->cb++;

      // Increment total phsyical row width and display width
      lpChild->cbrow += lpcol->cb;
      lpChild->ccols += (int)lpcol->cbc;

      cbMsg = cbNull;
   }

   // Include a count field for each bound column in physical row width
   lpChild->cbrow += lpChild->ccol * sizeof(SDWORD);

   // Add intra-column border amounts to total character width
   lpChild->ccols += (lpChild->ccol * (2 * cxBORDER)) / g_cx;

   // For each column, include an element in the format string
   lpb  = (LPBYTE)lpChild->szFmt;
   for (i=0, lpcol=lpChild->lpcol; i < lpChild->ccol; i++, lpcol++) {
      *(lpb++) = '\t';
      *(lpb++) = '%';
      *(lpb++) = 's';
   }
   *lpb = 0;

   // If row-wise binding, allocate a buffer; switch to column-wise
   // if the entire row-set cannot fit into 64K minus cursor library
   // headers
   lpb = NULL;
   if (ROW_BINDING(lpChild)) {
      if ((lpChild->cbrow * lpChild->crowRowset) > 65500L) {
         DoMessage(lpChild->hwnd, IDS_BIGROWSET);
         lpChild->fBindByRow = IDC_RADIO_BINDCOL ;
      }
      else {
         lpb          =
            lpChild->lpb = (LPBYTE)AllocPtr(lpChild->cbrow *
                                            lpChild->crowRowset);
      }
   }

   // Set binding type
   if (STMTError(SQLSetStmtAttr(lpChild->hstmt,
                                SQL_ATTR_ROW_BIND_TYPE,
                                (SQLPOINTER) (ROW_BINDING(lpChild)
                                              ? lpChild->cbrow
                                              : SQL_BIND_BY_COLUMN),
                                SQL_IS_INTEGER)))
      return FALSE;

   // Finally, for each bound column, bind the data value
   for (i=1, lpcol=lpChild->lpcol; i <= lpChild->ccol; i++, lpcol++) {
      if (!ROW_BINDING(lpChild)) {
         lpcol->lpb  = (LPBYTE)AllocPtr(lpcol->cb * lpChild->crowRowset);
         lpcol->lpcb = (LPSDWORD)AllocPtr((DWORD) sizeof(SDWORD) *
                                          lpChild->crowRowset);
      }
      else {
         lpcol->lpb  = (LPBYTE)lpb;
         lpcol->lpcb = (LPSDWORD)(lpb + lpcol->cb);
         lpb += lpcol->cb + sizeof(SDWORD);
      }

      if (STMTError(SQLBindCol(lpChild->hstmt, i, (SWORD)lpcol->fCType,
                               (PTR)(lpcol->lpb),
                               lpcol->cb,
                               lpcol->lpcb)))
         return FALSE;
   }

   return TRUE;
}


/* PrepareStmt -------------------------------------------------------------
   Description: Prepare a statement for future processing

   Returns: SQL_ERROR if an error occurs
   --------------------------------------------------------------------------*/
SQLRETURN INTFUNC PrepareStmt(LPCHILD lpChild)
{

   // Close the statement and drop bindings
   FreeStmt(SQL_CLOSE,  lpChild);
   FreeStmt(SQL_UNBIND, lpChild);

   // Set scroll options
   if (!(SUCCESS(SQLSetStmtAttr(lpChild->hstmt,
                                SQL_ATTR_CURSOR_TYPE,
                                (SQLPOINTER) lpChild->crowKeyset,
                                SQL_IS_INTEGER))))
      lpChild->fNoCursorType = TRUE;

   if (!(SUCCESS(SQLSetStmtAttr(lpChild->hstmt,
                                SQL_ATTR_CONCURRENCY,
                                (SQLPOINTER) lpChild->fConcurrency,
                                SQL_IS_INTEGER))))
      lpChild->fNoConcurrency = TRUE;


   if (STMTError(SQLSetStmtAttr(lpChild->hstmt,
                                SQL_ATTR_ROW_ARRAY_SIZE,
                                (SQLPOINTER) lpChild->crowRowset,
                                SQL_IS_INTEGER)))
      return SQL_ERROR;

   // Set async mode (if supported by the driver)
   if (g_fAsyncSupported &&
       STMTError(SQLSetStmtAttr(lpChild->hstmt,
                                SQL_ATTR_ASYNC_ENABLE,
                                (SQLPOINTER) (lpChild->fAsync ? 1 : 0),
                                SQL_IS_INTEGER)))
      return SQL_ERROR;



   return FALSE;

}

/* Cancel -------------------------------------------------------------------
   Description: Issue cancel request
   --------------------------------------------------------------------------*/
void INTFUNC Cancel(LPCHILD lpChild)
{
   SQLRETURN rc;

   // Call SQLCancel
   if (lpChild->hstmtTmp != SQL_NULL_HSTMT) {
      rc = SQLCancel(lpChild->hstmtTmp);  // Cancel temp hstmt
      STMTError(rc);
   }
   else {
      rc = SQLCancel(lpChild->hstmt);
      STMTError(rc);
      FreeStmt(SQL_CLOSE,  lpChild);   // Cleanup statement
   }

   return;
}


/* Fetch -------------------------------------------------------------------
   Description: Issue fetch request
   --------------------------------------------------------------------------*/
void INTFUNC Fetch(LPCHILD lpChild)
{
   SQLRETURN rc;
   UDWORD    crow;
   HCURSOR   hcur;
   SDWORD    sdwIrowLast = lpChild->irow;
   SDWORD    sdwRowsAffected;
   SDWORD    irow;
   UWORD     fFetchType;

   static UWORD   fFetchTypeLast = SQL_FETCH_NEXT;

   fFetchType = lpChild->FetchOP;
   if (fFetchType == SQL_FETCH_ABSOLUTE)
      irow = lpChild->arow;
   else if (fFetchType == SQL_FETCH_RELATIVE)
      irow = lpChild->rrow;
   else
      irow = 0;
   if (!(lpChild->fResultSetExists)) {
      STMTError(SQLRowCount(lpChild->hstmt, &sdwRowsAffected));

      if (sdwRowsAffected > -1) {
         UCHAR szBuffer[200];
         wsprintf(szBuffer,
                  (sdwRowsAffected == 1) ? szRowAffected:szDataAffected,
                  sdwRowsAffected);

         MessageBox(lpChild->hwnd,
                    szBuffer,
                    szNoDataTitle,
                    MB_ICONINFORMATION);
      }
      else
         {
            MessageBox( lpChild->hwnd,
                       szNoDataTitle,
                       szNoData,
                       MB_ICONINFORMATION);
         }
      return;
   }

   hcur = SetCursor(LoadCursor(NULL, IDC_WAIT));

   SQLSetStmtAttr(lpChild->hstmt, SQL_ATTR_ROWS_FETCHED_PTR,
                  &crow, SQL_IS_POINTER);
   SQLSetStmtAttr(lpChild->hstmt, SQL_ATTR_ROW_STATUS_PTR,
                  lpChild->lpfStatus, SQL_IS_POINTER);

   // Call SQLFetchScroll
   Async(SQLFetchScroll(lpChild->hstmt, fFetchType, irow));

   if ((rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) &&
       lpChild->irowPos > crow) {
      SetPos(lpChild, (UWORD) crow);
   }

   if (!STMTError(rc) && rc != SQL_NO_DATA) {

      // Reset columns retrieved count
      lpChild->ccolRetrieved = (UWORD)lpChild->ccol;

      // If this is the first fetch, initialize child variables
      if (!lpChild->fDataFetched) {

         lpChild->fDataFetched = TRUE;

         lpChild->irow    = -((SDWORD)lpChild->crowRowset);
         lpChild->irowPos = 1;

         SetScrollPos(lpChild->hwndVScroll, SB_CTL, 0, FALSE);
         SetScrollPos(lpChild->hwndHScroll, SB_CTL, 0, FALSE);

         SetScroll(lpChild);
         AllocClipRgn(lpChild);
      }

      // Otherwise, maintain current row position in the row-set
      else if (lpChild->fConcurrency != SQL_CONCUR_READ_ONLY &&
               lpChild->crowKeyset != SQL_CURSOR_FORWARD_ONLY)
         SetPos(lpChild, lpChild->irowPos);

      // if (fFetchType == SQL_FETCH_RESUME)
      //    fFetchType = fFetchTypeLast;

      // Adjust absolute row number by fetch amount
      switch (fFetchType) {
        case SQL_FETCH_FIRST:
         lpChild->irow = 1;
         break;

        case SQL_FETCH_PRIOR:
         lpChild->irow -= crow;
         if (lpChild->irow < 1)
            lpChild->irow = 1;
         break;

        case SQL_FETCH_NEXT:
         lpChild->irow += lpChild->crowCurrent;  // Previous RS
         break;

        case SQL_FETCH_LAST: {
           SDWORD iRowT;   // scratch variable

           if (STMTError(SQLGetStmtAttr(lpChild->hstmt,
                                        SQL_ATTR_ROW_NUMBER,
                                        &iRowT,
                                        SQL_IS_INTEGER,
                                        NULL))) {
              // the cursor library does not support SQL_ROW_NUMBER,
              // so use the following calculation. The  result might
              // be incorrect
              STMTError(SQLRowCount(lpChild->hstmt, &iRowT));
              lpChild->irow += (iRowT - crow);
              if (lpChild->irow < 1) lpChild->irow = 1;

           }
           else {    // the cursor library supports SQL_ROW_NUMBER
              lpChild->irow = iRowT;
           }
        }
         break;

        case SQL_FETCH_RELATIVE:
         lpChild->irow += irow;
         if (lpChild->irow < 1)
            lpChild->irow = 1;
         break;

        case SQL_FETCH_ABSOLUTE:
         if (irow > 0)
            lpChild->irow = irow;
         else {
            STMTError(SQLRowCount(lpChild->hstmt, &lpChild->irow));
            lpChild->irow = lpChild->irow + irow + 1;
            if (lpChild->irow < 1) lpChild->irow = 1;
         }
         break;
      }

      // Repaint window
      InvalidateRect(lpChild->hwnd, NULL, FALSE);

      lpChild->crowCurrent = crow;
   }

   fFetchTypeLast = fFetchType;

   AdjustMenus();
   SetCursor(hcur);
   return;
}


/* FreeStmt ----------------------------------------------------------------
   Description: Free SQLHSTMT and reset associated variables of a child window
                NOTE: Only SQL_CLOSE, SQL_DROP, and SQL_UNBIND are valid
                --------------------------------------------------------------------------*/
void INTFUNC FreeStmt(UWORD fOption, LPCHILD lpChild)
{
   SWORD i;
   LPCOL lpcol;

   if (!lpChild->hstmt)
      return;

   // Issue the real SQLFreeStmt call
   if (fOption == SQL_DROP) {
      if (STMTError(SQLFreeHandle(SQL_HANDLE_STMT, lpChild->hstmt)))
         return;
   }
   else {
      if (STMTError(SQLFreeStmt(lpChild->hstmt, fOption)))
         return;
   }

   // Drop data buffers for SQL_DROP and SQL_UNBIND requests
   if (fOption == SQL_DROP || fOption == SQL_UNBIND) {
      if (!ROW_BINDING(lpChild)) {
         for (i=0, lpcol=lpChild->lpcol; i < lpChild->ccol; i++, lpcol++) {
            FreePtr(lpcol->lpb);  lpcol->lpb  = NULL;
            FreePtr(lpcol->lpcb); lpcol->lpcb = NULL;
         }
      }
      else if (lpChild->lpb) {
         FreePtr(lpChild->lpb);
         lpChild->lpb = NULL;
      }
   }

   // Only drop memory for SQL_UNBIND requests
   if (fOption == SQL_UNBIND)
      return;

   // Clear SQLHSTMT handle for SQL_DROP
   if (fOption == SQL_DROP)
      lpChild->hstmt = SQL_NULL_HSTMT;

   // Always reset and free result set related variables
   lpChild->fResultSetExists = FALSE;
   lpChild->ccol         = 0;
   lpChild->fDataFetched = FALSE;
   lpChild->cbrow        = 0;
   lpChild->ccols        = 0;


   FreePtr(lpChild->rglpv);     lpChild->rglpv     = NULL;
   FreePtr(lpChild->lpnTabs);   lpChild->lpnTabs   = NULL;
   FreePtr(lpChild->lpcol);     lpChild->lpcol     = NULL;
   FreePtr(lpChild->lpfStatus); lpChild->lpfStatus = NULL;

   if (lpChild->hrgn) {
      DeleteObject(lpChild->hrgn);
      lpChild->hrgn = NULL;
   }

   if (lpChild->hwnd) {
      lpChild->fVScroll = FALSE;
      lpChild->fHScroll = FALSE;

      ShowWindow(lpChild->hwndVScroll, SW_HIDE);
      ShowWindow(lpChild->hwndHScroll, SW_HIDE);
      InvalidateRect(lpChild->hwnd, NULL, FALSE);
   }
   return;
}


/* GetCurrentValue ---------------------------------------------------------
   Description: Convert to character and return column data from current
                row
--------------------------------------------------------------------------*/
#pragma optimize("ceglntw", off)
void INTFUNC GetCurrentValue(LPSTR lpsz, LPCOL lpcol, LPCHILD lpChild)
{
   LPBYTE      lpb;
   SDWORD FAR  *lpcb;
   UWORD       irowPos;

   irowPos = lpChild->irowPos - 1;

   // Get data and count field pointers based on binding type
   if (ROW_BINDING(lpChild)) {
      lpb  = lpcol->lpb + (irowPos * lpChild->cbrow);
      lpcb = (LPSDWORD)(lpb + lpcol->cb);
   }
   else {
      lpb  = lpcol->lpb + (irowPos * lpcol->cb);
      lpcb = lpcol->lpcb + irowPos;
   }

   // Convert column data to character using the supplied buffer
   if (*lpcb == SQL_NULL_DATA) {
      lstrcpy(lpsz, g_szNull);
      return;
   }

   switch (lpcol->fSqlType) {

     case SQL_CHAR:
     case SQL_VARCHAR:
      lstrcpy(lpsz, (LPSTR)lpb);
      break;

     case SQL_INTEGER:
     case SQL_SMALLINT:
     case SQL_TINYINT: {
        long  l;

        l = (lpcol->fSqlType == SQL_INTEGER
             ? *((DWORD FAR *)lpb)
             : lpcol->fSqlType == SQL_SMALLINT
             ? *((WORD FAR *)lpb)
             : *((UCHAR FAR *)lpb));

        _ltoa(l, lpsz, 10);
        break;
     }

     case SQL_REAL:
     case SQL_FLOAT:
     case SQL_DOUBLE: {
        double   d;

        d = (lpcol->fSqlType == SQL_REAL
             ? *((float FAR *)lpb)
             : *((double FAR *)lpb));

        _gcvt(d, 15, lpsz);
        break;
     }

     default:
      *lpsz = '\0';
      break;
   }

   return;
}
#pragma optimize("ceglntw", on)


/* GetData -----------------------------------------------------------------
   Description: Retrieve the next unbound column and display the data
   --------------------------------------------------------------------------*/
void INTFUNC GetData(LPCHILD lpChild)
{
   HCURSOR   hcur;
   BIGCOL    bcol;
   UWORD     icol;
   SQLRETURN rc;

   // Prevent Cancel from closing statement
   lpChild->hstmtTmp = lpChild->hstmt;

   // Determine next unbound column index
   icol = lpChild->ccolRetrieved + 1;

   hcur = SetCursor(LoadCursor(NULL, IDC_WAIT));

   // Get column name
   Async(SQLColAttribute(lpChild->hstmt, icol,
                         SQL_DESC_NAME,
                         bcol.szName, sizeof(bcol.szName), NULL,
                         NULL));

   SetCursor(hcur);

   if (STMTError(rc)) {
      lpChild->hstmtTmp = SQL_NULL_HSTMT;
      return;
   }

   bcol.lpsz = lpChild->lpsz;

   hcur = SetCursor(LoadCursor(NULL, IDC_WAIT));

   // Get the data converting it to character
   Async(SQLGetData(lpChild->hstmt, icol, SQL_C_CHAR,
                    bcol.lpsz, cbBUFSIZE-1, &bcol.cb));

   SetCursor(hcur);

   lpChild->hstmtTmp = SQL_NULL_HSTMT;

   if (STMTError(rc) || rc == SQL_NO_DATA)
      return;

   // Display the retrieved data
   DialogBoxParam(g_hinst,
                  MAKEINTRESOURCE(IDD_DATADLG),
                  lpChild->hwnd,
                  DataDlgProc,
                  (LPARAM)((LPSTR)&bcol));

   lpChild->ccolRetrieved = icol;
   return;
}


/* GetTableName ------------------------------------------------------------
   Description: Extract table name from a SELECT statement
   --------------------------------------------------------------------------*/
void INTFUNC GetTableName(LPSTR lpszTable, LPCSTR szSql)
{
   LPCSTR   lpsz;
   int      cp;
   int      cb;

   cb = lstrlen(szFROM);

   for (lpsz=szSql, cp=0; *lpsz; ) {

      while (*lpsz && ISWHITE(*lpsz)) lpsz++;

      if (!cp && !_fstrnicmp(lpsz, szFROM, cb) && ISWHITE(*(lpsz+cb)))
         break;

      if (ISLPAREN(*lpsz))
         cp++;
      else if (ISRPAREN(*lpsz))
         cp--;

      while (*lpsz && !ISWHITE(*lpsz)) lpsz++;
   }

   while (*lpsz && !ISWHITE(*lpsz)) lpsz++;
   while (*lpsz && ISWHITE(*lpsz))  lpsz++;

   if (*lpsz == *g_szQuoteChar) {
      *lpszTable++ = *lpsz++; // Copy beginning quote
      while (*lpsz && *lpsz != *g_szQuoteChar) *lpszTable++ = *lpsz++;
      *lpszTable++ = *lpsz++; // Copy ending quote
   }
   else  // Not a quoted identifier
      while (*lpsz && !ISCOMMA(*lpsz) && !ISWHITE(*lpsz)) *lpszTable++ = *lpsz++;

   *lpszTable = '\0';

   return;
}


/* IsUpdateable ------------------------------------------------------------
   Description: Return TRUE if this app supports updating the particular
                SQL data type (due to limited conversion support)
                --------------------------------------------------------------------------*/
BOOL INTFUNC IsUpdateable(SDWORD fSqlType)
{
   switch (fSqlType) {
     case SQL_CHAR:
     case SQL_VARCHAR:
     case SQL_SMALLINT:
     case SQL_INTEGER:
     case SQL_REAL:
     case SQL_FLOAT:
     case SQL_DOUBLE:
     case SQL_TINYINT:
      return TRUE;

     default:
      return FALSE;
   }
}


/* OnDataRow ---------------------------------------------------------------
   Description: Return 0 or greater if the mouse coordinates in lparam are
                over a valid data row, Otherwise return -1
                --------------------------------------------------------------------------*/
int INTFUNC OnDataRow(LPCHILD lpChild, LPARAM lparam)
{
   RECT  rc;
   int   row;

   if (!(lpChild->hrgn))
      return -1;

   GetRgnBox(lpChild->hrgn, &rc);

   row = (int)HIWORD(lparam) - g_cy;

   if (row < 0)
      return FALSE;

   row /= g_cy;

   if (row >= 0                        &&
       (UWORD)row < lpChild->crowRowset )
      return row;
   else
      return -1;
}


/* PaintChild --------------------------------------------------------------
   Description: Paint child window
--------------------------------------------------------------------------*/
void INTFUNC PaintChild(LPCHILD  lpChild,
                        HDC      hdc,
                        BOOL  fTitle,
                        BOOL  fRefresh,
                        BOOL  fActive)
{
   RECT  rc;

   GetClientRect(lpChild->hwnd, &rc);

   // If no data exists, just erase the window
   if (!lpChild->fDataFetched)
      FillRect(hdc, &rc, g_hbrWin);

   // Otherwise paint the data in a simple scrollable grid
   else {
      HRGN     hrgn;
      HFONT    hfontOld;
      HBRUSH   hbrOld;
      UWORD    ir;
      int      ic;
      int      icFirst, icLast;
      LPCOL    lpcol;
      UWORD    row;
      int      col;
      int      cx, cy;
      LPINT    lpnTab;
      LPSTR    lpszValues;
      LPSTR    lpsz;
      LPUWORD  lpfStatus;
      UWORD    irowLast;
      UWORD    irowPos;
      COLORREF clrfTxt;
      COLORREF clrfBkg;
      char     szFmt[cbSTRLEN];

      // Prepare the device context
      SetBkColor(hdc, GetSysColor(COLOR_WINDOW));

      clrfTxt = GetTextColor(hdc);
      clrfBkg = GetBkColor(hdc);

      // Determine first (row,col) and corresponding (x,y) offset
      row = (UWORD)GetScrollPos(lpChild->hwndVScroll, SB_CTL);
      col = GetScrollPos(lpChild->hwndHScroll, SB_CTL);

      cx = col * g_cx;
      cy = row * g_cy;

      // Determine last row to be painted
      irowLast = (UWORD)row + ((UWORD)lpChild->crowwin < lpChild->crowRowset
                               ? lpChild->crowwin
                               : lpChild->crowRowset);
      if (irowLast > lpChild->crowRowset)
         irowLast--;

      // Get current row number as a zero based index
      irowPos  = lpChild->irowPos - 1;

      // Determine which columns will be painted
      lpnTab = lpChild->lpnTabs;
      for (icFirst=0;
           icFirst < (lpChild->ccol-1) && (cx + cxBORDER) > *(lpnTab+1);
           icFirst++, lpnTab++);
      for (icLast=icFirst+1;
           icLast < lpChild->ccol &&
           (cx + cxBORDER + (lpChild->ccolwin * g_cx)) > *lpnTab;
           icLast++, lpnTab++);

      // Offset the device context to appropriate position in the rowset
      SetWindowOrgEx(hdc, cx, cy, NULL);

      // Set the clip region (to keep from erasing scroll bars, etc.)

      if (!(lpChild->hrgn))
         return;

      SelectClipRgn(hdc, lpChild->hrgn);

      // Allocate working buffer to converted data values
      lpszValues = AllocPtr((DWORD) lpChild->ccol * cbSTRLEN);

      // If requested, paint column titles
      if (fTitle) {

         // Prepare device context
         SetBkColor(hdc, GetSysColor(COLOR_BTNFACE));
         hfontOld = SelectObject(hdc, g_hfontName);

         // Determine bounding rectangle in logical coordinates
         rc.top    = cy;
         rc.bottom = rc.top + g_cy;
         rc.left   = *(lpChild->lpnTabs + icFirst) - cxBORDER;
         rc.right  = *(lpChild->lpnTabs + icLast)  - cxBORDER;

         // Fill rectangle with appropriate color
         FillRect(hdc, &rc, g_hbrBtn);

         // Paint white bar across the top
         PatBlt(hdc, 0, rc.top, rc.right, 1, WHITENESS);

         // For each visible (or partially visible) column, paint
         // separating lines and column name
         lpcol  = lpChild->lpcol   + icFirst;
         lpnTab = lpChild->lpnTabs + icFirst + 1;

         for (ic=icFirst; ic < icLast; ic++, lpcol++, lpnTab++) {

            PatBlt(hdc, rc.left, rc.top, 1, g_cy, WHITENESS);

            rc.right = *lpnTab - cxBORDER + 1;

            DrawText(hdc, lpcol->szName, lstrlen(lpcol->szName),
                     &rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

            rc.left = rc.right;

            PatBlt(hdc, rc.left-1, rc.top, 1, g_cy, BLACKNESS);
         }

         // Paint black line across the bottom
         PatBlt(hdc, 1, rc.bottom-1, rc.right-1, 1, BLACKNESS);

         // Reset device context
         SelectObject(hdc, hfontOld);
         SetBkColor(hdc, clrfBkg);
      }

      // Determine bounding rectangle for first row to be painted
      rc.top    = cy + g_cy;
      rc.bottom = rc.top + g_cy - 1;
      rc.left   = *(lpChild->lpnTabs + icFirst) - cxBORDER;
      rc.right  = *(lpChild->lpnTabs + icLast)  - cxBORDER;

      // Make format string from the whole format string created earlier
#ifdef WIN32
      _fstrncpy(szFmt, lpChild->szFmt+(icFirst*3), ((icLast-icFirst)*3)+1);
#else
      lstrcpyn(szFmt, lpChild->szFmt+(icFirst*3), ((icLast-icFirst)*3)+1);
#endif
      szFmt[((icLast-icFirst)*3)+1] = '\0';

      // Offset into the row status array
      lpfStatus = lpChild->lpfStatus + row;

      // Prepare device context
      hfontOld = SelectObject(hdc, g_hfontData);
      hbrOld   = SelectObject(hdc, g_hbrBtn);

      // Paint each row
      for (ir=row; ir < irowLast; ir++) {

         // Erase row if requested (i.e., !fRefresh) or if just
         // painting the row is insufficient to remove old data
         if (!fRefresh                   ||
             (ir == irowPos && !fActive) ||
             *lpfStatus == SQL_ROW_NOROW ||
             *lpfStatus == SQL_ROW_ERROR ||
             *lpfStatus == SQL_ROW_DELETED)
            FillRect(hdc, &rc, g_hbrWin);

         // For an empty row, write the empty row string
         if (*lpfStatus == SQL_ROW_NOROW) {
            if (icFirst)
               *lpChild->lpsz = '\0';
            else
               lstrcpy(lpChild->lpsz, g_szNoRow);
         }

         // For a deleted row, write the deleted row string
         else if (*lpfStatus == SQL_ROW_DELETED) {
            if (icFirst)
               *lpChild->lpsz = '\0';
            else
               lstrcpy(lpChild->lpsz, g_szRowDeleted);
         }

         // For an error row, write the error row string
         else if (*lpfStatus == SQL_ROW_ERROR) {
            if (icFirst)
               *lpChild->lpsz = '\0';
            else
               lstrcpy(lpChild->lpsz, g_szRowError);
         }

         // For all other rows, build a string of data values
         else {
            LPSTR FAR   *lplpsz;
            LPBYTE      lpb;
            LPSDWORD lpcb;
       

            // Paint updated rows in RED
            if (*lpfStatus == SQL_ROW_UPDATED)
               SetTextColor(hdc, RGB(255,0,0));

                               
            lplpsz = (LPSTR FAR *)lpChild->rglpv;
                               
            lpsz   = lpszValues;

            lpcol  = lpChild->lpcol   + icFirst;
            lpnTab = lpChild->lpnTabs + icFirst;

            // Convert each column to character data
            for (ic=icFirst; ic < icLast; ic++, lpcol++) {

               lpb  = lpcol->lpb  + (ir * (ROW_BINDING(lpChild)
                                           ? lpChild->cbrow
                                           : lpcol->cb));
               lpcb = (ROW_BINDING(lpChild)
                       ? (LPSDWORD)(lpb + lpcol->cb)
                       : lpcol->lpcb + ir);

               if (*lpcb == SQL_NULL_DATA)
                  *lplpsz++ = g_szNull;

               else if (lpcol->fCType == SQL_C_CHAR)
                  *lplpsz++ = (LPSTR)lpb;

               else {

                  if (lpcol->fCType == SQL_C_FLOAT ||
                      lpcol->fCType == SQL_C_DOUBLE ) {
                     double   d;

                     d = (lpcol->fCType == SQL_C_FLOAT
                          ? *((float FAR *)lpb)
                          : *((double FAR *)lpb));

                     _gcvt(d, 15, lpsz);
                  }

                  else {
                     long  l;

                     l = ( lpcol->fCType == SQL_C_SHORT
                          ? *((short FAR *)lpb)
                          : lpcol->fCType == SQL_C_LONG
                          ? *((long FAR *)lpb)
                          : *((signed char FAR *)lpb));

                     _ltoa(l, lpsz, 10);
                  }

                  *lplpsz++ = lpsz;
                  lpsz += cbSTRLEN;
               }
            }

            // Combine all columns into one string (with tab markers)
				Print(lpChild->lpsz, szFmt, lpChild->rglpv );

				
				
         }

         // Paint the row
         TabbedTextOut(hdc,
                       rc.left, rc.top,
                       lpChild->lpsz, lstrlen(lpChild->lpsz),
                       icLast - icFirst, lpnTab, 0);

         // Paint bottom separator
         PatBlt(hdc, 0, rc.bottom, rc.right, 1, PATCOPY);

         // Paint inter-column separators
         lpnTab = lpChild->lpnTabs + icFirst + 1;
         for (ic=icFirst+1; ic < (icLast+1); ic++, lpnTab++)
            PatBlt(hdc, *lpnTab-cxBORDER, rc.top, 1, g_cy, PATCOPY);

         // Reset text color (if it was changed)
         if (*lpfStatus == SQL_ROW_UPDATED)
            SetTextColor(hdc, clrfTxt);

         // Hilite the current row
         if (ir == irowPos                                 &&
             lpChild->fConcurrency != SQL_CONCUR_READ_ONLY &&
             fActive                                        ) {
            RECT  rcTemp, rcInvert;

            GetClipBox(hdc, &rcTemp);

            IntersectRect(&rcInvert, &rc, &rcTemp);

            GetClientRect(lpChild->hwnd, &rcTemp);

            if( rcInvert.top == rc.top )
               rcInvert.top++;

            if( rcInvert.bottom == rc.bottom )
               rcInvert.bottom--;

            if( rcInvert.left == rcTemp.left )
               rcInvert.left++;

            if( rcInvert.right == rcTemp.right ||
               rcInvert.right == rc.right )
               rcInvert.right--;

            InvertRect(hdc, &rcInvert);
         }

         // Advance row rectangle and status array offset
         rc.top    += g_cy;
         rc.bottom += g_cy;
         lpfStatus++;
      }

      // Erase any partial row which may be displayed after the last
      // row of the row-set has been painted
      if (ir == lpChild->crowRowset)
         FillRect(hdc, &rc, g_hbrWin);

      // Erase any partial column which may be displayed after the last
      // column has been painted
      if (icLast == lpChild->ccol) {
         GetClipBox(hdc, &rc);
         rc.left = *(lpChild->lpnTabs + icLast) - cxBORDER + 1;
         FillRect(hdc, &rc, g_hbrWin);
      }

      FreePtr(lpszValues);

      // Reset clip region to paint areas outside data grid
      GetClientRect(lpChild->hwnd, &rc);

      hrgn = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

      SelectClipRgn(hdc, hrgn);

      OffsetRect(&rc, cx, cy);

      // Paint bottom record display bar and/or the corner box
      // between the scroll bars
      rc.top = rc.bottom - g_cyHScroll + 1;

      PatBlt(hdc, rc.left, rc.top, rc.right, 1, BLACKNESS);

      SelectObject(hdc, g_hbrScroll);

      rc.top++;

      cx = (2 * cxBORDER) + g_cxRecord + g_cxRecnum + 2;

      if (lpChild->fHScroll) {
         if (lpChild->fVScroll)
            PatBlt(hdc,
                   rc.right - g_cxVScroll + 2, rc.top,
                   g_cxVScroll, g_cyHScroll,
                   PATCOPY);
      }
      else
         PatBlt(hdc,
                rc.left + cx, rc.top,
                rc.right - rc.left, g_cyHScroll,
                PATCOPY);

      rc.right = rc.left + cx;

      PatBlt(hdc, rc.right, rc.top, 1, rc.bottom, BLACKNESS);

      rc.right--;

      // Paint current row number
      if (fRefresh)
         FillRect(hdc, &rc, g_hbrWin);

      rc.left += cxBORDER;

      TextOut(hdc, rc.left, rc.top, szRECORD, lstrlen(szRECORD));

      rc.left += g_cxRecord + 2;

      FillRect(hdc, &rc, g_hbrWin);

      wsprintf(lpChild->lpsz, szRECNUM, lpChild->irow-1 + lpChild->irowPos);

      TextOut(hdc, rc.left, rc.top, lpChild->lpsz, lstrlen(lpChild->lpsz));

      DeleteObject(hrgn);

      // Reset device context
      SelectObject(hdc, hbrOld);

      SelectObject(hdc, hfontOld);
   }

   return;
}



/* SetCurrentValue ---------------------------------------------------------
   Description: Set a column value from the user buffer
--------------------------------------------------------------------------*/
#pragma optimize("ceglntw", off)
BOOL INTFUNC SetCurrentValue(LPSTR lpsz, LPCOL lpcol, LPCHILD lpChild)
{
   LPBYTE   lpb;
   LPSDWORD lpcb;
   BOOL     fNew;
   UWORD    irowPos;

   irowPos = lpChild->irowPos - 1;

   // Get data and count field pointers based on binding type
   if (ROW_BINDING(lpChild)) {
      lpb  = lpcol->lpb + (irowPos * lpChild->cbrow);
      lpcb = (LPSDWORD)(lpb + lpcol->cb);
   }
   else {
      lpb  = lpcol->lpb + (irowPos * lpcol->cb);
      lpcb = lpcol->lpcb + irowPos;
   }

   // If the data is NULL, just set the count field to SQL_NULL_DATA
   if (!lstrcmpi(lpsz, g_szNull)) {
      if (*lpcb != SQL_NULL_DATA) {
         *lpcb = SQL_NULL_DATA;
         fNew  = TRUE;
      }
   }

   // Otherwise, convert the character data back to the appropriate type
   else switch (lpcol->fSqlType) {

     case SQL_CHAR:
     case SQL_VARCHAR:
      if (lstrcmp(lpsz, (LPSTR)lpb)) {
         lstrcpy((LPSTR)lpb, lpsz);
         *lpcb = lstrlen(lpsz);
         fNew  = TRUE;
      }
      break;

     case SQL_INTEGER:
     case SQL_SMALLINT:
     case SQL_TINYINT: {
        long  lNew, lCur;
        char  *EndPtr;

        lNew = strtol(lpsz, &EndPtr, 10);
        for (; *EndPtr && ISWHITE(*EndPtr); EndPtr = AnsiNext(EndPtr));
        if (*EndPtr)  { // check to see if there exists non-numeric chars
           UCHAR szBuffer[128];

           LoadString(g_hinst, IDS_BADNUMERIC, szBuffer, sizeof(szBuffer));
           MessageBox(lpChild->hwnd,
                      szBuffer, NULL, MB_ICONSTOP);
           fNew = FALSE;
           break;
        }

        lCur = (lpcol->fSqlType == SQL_INTEGER
                ? *((DWORD FAR *)lpb)
                : lpcol->fSqlType == SQL_SMALLINT
                ? *((WORD FAR *)lpb)
                : *((UCHAR FAR *)lpb));

        if (lNew != lCur) {

           switch (lpcol->fSqlType) {
             case SQL_INTEGER:
              *((DWORD FAR *)lpb) = lNew;
              *lpcb = sizeof(DWORD);
              break;

             case SQL_SMALLINT:
              *((WORD FAR *)lpb) = (WORD)lNew;
              *lpcb = sizeof(WORD);
              break;

             case SQL_TINYINT:
              *((UCHAR FAR *)lpb) = (UCHAR)lNew;
              *lpcb = sizeof(UCHAR);
              break;
           }

           fNew = TRUE;
        }
        break;
     }

     case SQL_REAL:
     case SQL_FLOAT:
     case SQL_DOUBLE: {
        double   dNew, dCur;
        char  *EndPtr;

        dNew = strtod(lpsz, &EndPtr);
        for (; *EndPtr && ISWHITE(*EndPtr); EndPtr = AnsiNext(EndPtr));
        if (*EndPtr)  { // check to see if there exists non-numeric chars
           UCHAR szBuffer[128];

           LoadString(g_hinst, IDS_BADNUMERIC, szBuffer, sizeof(szBuffer));
           MessageBox(lpChild->hwnd,
                      szBuffer, NULL, MB_ICONSTOP);
           fNew = FALSE;
           break;
        }

        dCur = (lpcol->fSqlType == SQL_REAL
                ? *((float FAR *)lpb)
                : *((double FAR *)lpb));

        if (dNew != dCur) {

           switch (lpcol->fSqlType) {
             case SQL_REAL:
              *((float FAR *)lpb) = (float)dNew;
              *lpcb = sizeof(float);
              break;

             case SQL_FLOAT:
             case SQL_DOUBLE:
              *((double FAR *)lpb) = dNew;
              *lpcb = sizeof(double);
              break;
           }

           fNew = TRUE;
        }
        break;
     }
   }

   return fNew;
}
#pragma optimize("ceglntw", on)


/* SetPos ------------------------------------------------------------------
   Description: Set current row, de-hilite last current row and hilite
                new current row
                --------------------------------------------------------------------------*/
void INTFUNC SetPos(LPCHILD lpChild, UWORD irowPos)
{
   HDC      hdc;
   HFONT    hfont;
   RECT     rc, rcClip, rcInvert;
   int      row, col;
   int      cx, cy;

   if (!(lpChild->hrgn))
      return ;

   if (irowPos < 1)
      irowPos = 1;

   else if (irowPos > lpChild->crowRowset)
      irowPos = lpChild->crowRowset;

   // Call SQLSetPos to set current row in the row-set
   if (STMTError(SQLSetPos(lpChild->hstmt, irowPos, SQL_POSITION,
                           SQL_LOCK_NO_CHANGE)))
      return;

   // Reset number of columns retrieved
   lpChild->ccolRetrieved = (UWORD)lpChild->ccol;

   // Obtain a device context for painting
   hdc = GetDC(lpChild->hwnd);

   row = GetScrollPos(lpChild->hwndVScroll, SB_CTL);
   col = GetScrollPos(lpChild->hwndHScroll, SB_CTL);

   cx  = col * g_cx;
   cy  = row * g_cy;

   SetWindowOrgEx(hdc, cx, cy, NULL);

   GetClientRect(lpChild->hwnd, &rc);
   GetRgnBox(lpChild->hrgn, &rcClip);
   OffsetRect(&rcClip, cx, cy);

   rcClip.top += g_cy;

   // Offset to last current row
   rc.top    = ((lpChild->irowPos - 1) * g_cy) + g_cy;
   rc.bottom = rc.top + g_cy - 1;
   rc.left   = 0;
   rc.right  = *(lpChild->lpnTabs + lpChild->ccol) - cxBORDER;

   // De-hilite last current row
   IntersectRect(&rcInvert, &rc, &rcClip);
   InflateRect(&rcInvert, -1, -1);
   InvertRect(hdc, &rcInvert);

   // Save new current row
   lpChild->irowPos = irowPos;

   // Offset to new current row
   rc.top    = ((lpChild->irowPos - 1) * g_cy) + g_cy;
   rc.bottom = rc.top + g_cy - 1;

   // Hilite current row (if visible)
   if (lpChild->irowPos > (UWORD)row) {

      IntersectRect(&rcInvert, &rc, &rcClip);
      InflateRect(&rcInvert, -1, -1);
      InvertRect(hdc, &rcInvert);
   }

   // Update record number
   GetClientRect(lpChild->hwnd, &rc);
   OffsetRect(&rc, cx, cy);

   rc.left += cxBORDER + g_cxRecord + 2;
   rc.top   = rc.bottom - g_cyHScroll + 2;
   rc.right = rc.left + g_cxRecnum;

   FillRect(hdc, &rc, g_hbrWin);

   wsprintf(lpChild->lpsz, szRECNUM, lpChild->irow-1 + lpChild->irowPos);

   hfont = SelectObject(hdc, g_hfontData);

   TextOut(hdc, rc.left, rc.top, lpChild->lpsz, lstrlen(lpChild->lpsz));

   SelectObject(hdc, hfont);

   // Release device context
   ReleaseDC(lpChild->hwnd, hdc);

   return;
}


/* SetScroll ---------------------------------------------------------------
   Description: Determine if scroll bars are required and their ranges
   --------------------------------------------------------------------------*/
void INTFUNC SetScroll(LPCHILD lpChild)
{
   RECT  rc;
   int   cx, cy;
   int   row, col;

   // Use the fInSetScroll flag to prevent recursion due WM_SIZE messages
   if (lpChild->fInSetScroll)
      return;

   lpChild->fInSetScroll = TRUE;

   // Save current scroll positions
   row = GetScrollPos(lpChild->hwndVScroll, SB_CTL);
   col = GetScrollPos(lpChild->hwndHScroll, SB_CTL);

   // Get window dimensions
   GetClientRect(lpChild->hwnd, &rc);
   cx = rc.right - rc.left;
   cy = rc.bottom - rc.top - g_cy - g_cyHScroll;

   // Assume no scrolling is required
   lpChild->fHScroll =
      lpChild->fVScroll = FALSE;

   // Include a vertical scroll bar if all rows do not fit
   lpChild->crowwin = cy / g_cy;
   if ((UWORD)lpChild->crowwin < lpChild->crowRowset) {
      lpChild->fVScroll = TRUE;
      cx -= g_cxVScroll;
   }

   // Include a horizontal scroll bar if all columns do not fit
   lpChild->ccolwin = cx / g_cx;
   if (lpChild->ccolwin < lpChild->ccols)
      lpChild->fHScroll = TRUE;

   // Reset scroll positions if no scrolling is necessary
   if (!lpChild->fVScroll) row = 0;
   if (!lpChild->fHScroll) col = 0;

   // Set scroll ranges, positions, and scroll bar visibility
   SetScrollRange(lpChild->hwndVScroll, SB_CTL, 0, lpChild->crowRowset - lpChild->crowwin, TRUE);
   SetScrollRange(lpChild->hwndHScroll, SB_CTL, 0, lpChild->ccols - lpChild->ccolwin,      TRUE);

   SetScrollPos(lpChild->hwndVScroll, SB_CTL, row, TRUE);
   SetScrollPos(lpChild->hwndHScroll, SB_CTL, col, TRUE);

   ShowWindow(lpChild->hwndVScroll, (lpChild->fVScroll ? SW_SHOW : SW_HIDE));
   ShowWindow(lpChild->hwndHScroll, (lpChild->fHScroll ? SW_SHOW : SW_HIDE));

   // Add one extra to window depth so no white space is left between
   // the last full row and bottom record display bar
   lpChild->crowwin++;

   // Size and position scroll bars
   SizeScroll(lpChild);

   lpChild->fInSetScroll = FALSE;

   return;
}


/* SizeScroll --------------------------------------------------------------
   Description: Size and position scroll bars
   --------------------------------------------------------------------------*/
void INTFUNC SizeScroll(LPCHILD lpChild)
{
   RECT  rc;
   int   cxRecord;

   GetClientRect(lpChild->hwnd, &rc);

   // Place vertical scroll bar
   MoveWindow(lpChild->hwndVScroll,
              rc.right - g_cxVScroll + 1,
              rc.top,
              g_cxVScroll,
              rc.bottom - g_cyHScroll + 2,
              TRUE);

   // Place horizontal scroll bar
   cxRecord = (2 * cxBORDER) + g_cxRecord + g_cxRecnum + 2;

   MoveWindow(lpChild->hwndHScroll,
              rc.left + cxRecord,
              rc.bottom - g_cyHScroll + 1,
              (lpChild->fVScroll
               ? rc.right - g_cxVScroll + 2 - cxRecord
               : rc.right + 2 - cxRecord),
              g_cyHScroll,
              TRUE);

   return;
}


/* UpdateRow ---------------------------------------------------------------
   Description: Update current (positioned) row
   --------------------------------------------------------------------------*/
void INTFUNC UpdateRow(LPCHILD lpChild)
{
   HCURSOR  hcur;
   LPSTR    lpsz;
   LPSTR    lpszT;
   SWORD    cb;
   LPCOL    lpcol;
   int      cCtls;
   UWORD    irowPos;
   int      i;

   // Ensure the update request is valid
   if (!lpChild->fDataFetched) {
      DoMessage(lpChild->hwnd, IDS_NODATAFETCHED);
      return;
   }

   if (*(lpChild->lpfStatus + lpChild->irowPos - 1) == SQL_ROW_NOROW) {
      DoMessage(lpChild->hwnd, IDS_NOROWUPDATE);
      return;
   }

   if (*(lpChild->lpfStatus + lpChild->irowPos - 1) == SQL_ROW_ERROR) {
      DoMessage(lpChild->hwnd, IDS_ERRORROWUPDATE);
      return;
   }

   if (*(lpChild->lpfStatus + lpChild->irowPos - 1) == SQL_ROW_DELETED) {
      DoMessage(lpChild->hwnd, IDS_DELROWUPDATE);
      return;
   }

   if (lpChild->fConcurrency == SQL_CONCUR_READ_ONLY) {
      DoMessage(lpChild->hwnd, IDS_NOUPDATE);
      return;
   }

   // Count number of updateable columns
   for (cCtls=0, i=0, lpcol=lpChild->lpcol; i < lpChild->ccol; i++, lpcol++)
      if (IsUpdateable(lpcol->fSqlType))
         cCtls++;

   // Ensure a valid number of updateable columns exist
   if (cCtls > cMAXCOLS) {
      DoMessage(lpChild->hwnd, IDS_TOOMANYCOLS);
      return;
   }

   if (!cCtls) {
      DoMessage(lpChild->hwnd, IDS_CANNOTUPDATE);
      return;
   }

   hcur = SetCursor(LoadCursor(NULL, IDC_WAIT));

   lpsz  = AllocPtr(2 * cbMAXSQL);
   lpszT = lpsz + cbMAXSQL;

   // Build and display update dialog to get new values, then issue update
   // (use a temporary SQLHSTMT for the update request)
   if (IDOK == DoDialog(lpChild->hwnd, IDD_UPDATEROW, UpdateDlgProc) &&
       !DBCError(lpChild->hwnd, SQLAllocHandle(SQL_HANDLE_STMT,g_hdbc, &lpChild->hstmtTmp))) {

      // Build UPDATE <table> WHERE CURRENT OF <cursor name> statement
      lstrcpy(lpsz, szUPDATE);

      GetTableName(lpszT, lpChild->sql);
      lstrcat(lpsz, lpszT);

      // Build the Set Clause
      lstrcat(lpsz, szSET);
      for (lpcol = lpChild->lpcol, i = 0; i < lpChild->ccol; i++, lpcol++) {
         if (IsUpdateable(lpcol->fSqlType)) {
            LPSDWORD lpcb;
            LPBYTE   lpb;

            if (i == 0) wsprintf(lpszT, "%s=?", lpcol->szName);
            else wsprintf(lpszT, ",%s=?", lpcol->szName);
            lstrcat(lpsz, lpszT);

            irowPos = lpChild->irowPos - 1;

            // Get data and count field pointers based on binding type
            if (ROW_BINDING(lpChild)) {
               lpb  = lpcol->lpb + (irowPos * lpChild->cbrow);
               lpcb = (LPSDWORD)(lpb + lpcol->cb);
            }
            else {
               lpb  = lpcol->lpb + (irowPos * lpcol->cb);
               lpcb = lpcol->lpcb + irowPos;
            }

            // set parameter
            ODBCError(lpChild->hwnd, SQL_HANDLE_STMT, lpChild->hstmtTmp,
                      SQLSetParam(lpChild->hstmtTmp, (UWORD) (i+1), lpcol->fCType,
                                  lpcol->fSqlType, (UDWORD) lpcol->cb, (SWORD) 0,
                                  lpb, lpcb));
         }
      }

      lstrcat(lpsz, szWHERE);

      lpszT = lpsz + lstrlen(lpsz);

      if (!STMTError(SQLGetCursorName(lpChild->hstmt, (UCHAR FAR *)lpszT,
                                      cbMAXSQL, &cb))) {

         // Issue update request via SQLExecDirect
         ODBCError(lpChild->hwnd, SQL_HANDLE_STMT, lpChild->hstmtTmp,
                   SQLExecDirect(lpChild->hstmtTmp, (UCHAR FAR *)lpsz, SQL_NTS));
      }

      DBCError(lpChild->hwnd, SQLFreeHandle(SQL_HANDLE_STMT,lpChild->hstmtTmp));
      lpChild->hstmtTmp = SQL_NULL_HSTMT;

   }

   // Refresh entire row-set buffer (saving current row position)
   irowPos = lpChild->irowPos;

   lpChild->FetchOP = SQL_FETCH_RELATIVE;
   lpChild->rrow = 0;
   Fetch(lpChild);

   SetPos(lpChild, irowPos);

   // Repaint the row-set
   InvalidateRect(lpChild->hwnd, NULL, FALSE);

   FreePtr(lpsz);

   SetCursor(hcur);

   return;
}

/*--------------------------------------------------------------------
Input:  lpChild
Output: TRUE if the option parameters are valid, FALSE otherwise
--------------------------------------------------------------------*/
BOOL INTFUNC ParamValid(LPCHILD lpChild)
{
   char szBuffer[128]; // error message
   char *EndMaxBind, *EndRowset, *EndBind;

   // the maximum column width
   wsprintf((LPSTR) szBuffer,
            "Maximum column width must be at least 1 and at most %d",
            MAX_MAXBIND);

   if (lpChild->fMaxBind) { // it's been changed
      lpChild->crowMaxBind =
         (SDWORD) strtol((char*) lpChild->szMaxBind, &EndMaxBind, 10);
      for (; *EndMaxBind && ISWHITE(*EndMaxBind);
           EndMaxBind = AnsiNext(EndMaxBind));
   }

   if (lpChild->fBind) {  // cBind has been changed
      lpChild->cBind =  (UWORD) strtol((char*) lpChild->szBind, &EndBind, 10);
      for (; *EndBind && ISWHITE(*EndBind); EndBind = AnsiNext(EndBind));
   }

   if (lpChild->fRowset) { // rowset has been changed
      lpChild->crowRowset =
         (UWORD) strtol((char*) lpChild->szRowset, &EndRowset, 10);
      for (; *EndRowset && ISWHITE(*EndRowset);
           EndRowset = AnsiNext(EndRowset));
   }

   while (lpChild->fMaxBind && *EndMaxBind  ||
          lpChild->crowMaxBind < 1 ||
          lpChild->crowMaxBind > MAX_MAXBIND ||
          lpChild->fRowset && *EndRowset ||
          lpChild->crowRowset < 1 ||
          lpChild->crowRowset > 4096 ||
          lpChild->fBind && *EndBind) {

      // the maximum column width
      if (lpChild->crowMaxBind < 1 || lpChild->crowMaxBind > MAX_MAXBIND
          || lpChild->fMaxBind && *EndMaxBind)
         MessageBox(lpChild->hwnd,  szBuffer, NULL, MB_ICONSTOP);

      // the rowset size
      if (lpChild->crowRowset < 1 || lpChild->crowRowset > 4096
          || lpChild->fRowset && *EndRowset) {
         char szBuffer[128];

         LoadString(g_hinst, IDS_BADROWSET, szBuffer, sizeof(szBuffer));
         MessageBox(lpChild->hwnd, szBuffer, NULL, MB_ICONSTOP);
      }

      // number of bound columns
      if (lpChild->fBind && *EndBind)
         MessageBox(lpChild->hwnd,
                    "Invalid number of bound columns", NULL, MB_ICONSTOP);

      if (IDOK != DoDialog(lpChild->hwnd, IDD_OPTION_DIALOG, OptionsDlgProc))
         return FALSE;

      if (lpChild->fMaxBind) { // it's been changed
         lpChild->crowMaxBind =
            (SDWORD) strtol((char*) lpChild->szMaxBind, &EndMaxBind, 10);
         for (; *EndMaxBind && ISWHITE(*EndMaxBind);
              EndMaxBind = AnsiNext(EndMaxBind));
      }

      if (lpChild->fBind) {  // cBind has been changed
         lpChild->cBind =
            (UWORD) strtol((char*) lpChild->szBind, &EndBind, 10);

         for (; *EndBind && ISWHITE(*EndBind); EndBind = AnsiNext(EndBind));
      }

      if (lpChild->fRowset) { // rowset has been changed
         lpChild->crowRowset =
            (UWORD) strtol((char*) lpChild->szRowset, &EndRowset, 10);
         for (; *EndRowset && ISWHITE(*EndRowset);
              EndRowset = AnsiNext(EndRowset));
      }
   }

   return TRUE;

}
