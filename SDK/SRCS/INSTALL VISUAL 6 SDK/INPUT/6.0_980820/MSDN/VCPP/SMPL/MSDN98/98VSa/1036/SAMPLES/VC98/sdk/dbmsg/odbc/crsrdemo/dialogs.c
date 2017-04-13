/*--------------------------------------------------------------------------
  Dialogs.c -- Cursors dialogs

  Description:
      This sample is spread across four files, each named for the role
      the contained functions play.  Each file header contains a brief
      description of its purpose and the routines it contains.

      DIALOGS.C contains those routines used to display and manage
      dialogs.  Those functions are:

         AddEditControls - Dynamically create edit controls for UPDATE
                        dialog
         AddDlgProc      - Manage add row dialog
         CenterDialog    - Center a dialog over its parent window
         DoDialog        - Display a dialog
         MyCreateDialog - Create a modeless dialog
         GetEditControls - Retrieve values from dynamically created
                        edit controls
         IsMsgWaiting    - Check for waiting messages

         AboutDlgProc    - Manage about box
         AbsDlgProc      - Manage absolute row number dialog
         DataDlgProc     - Manage large data display dialog
         FindDlgProc    - Manager dialog to get text string to find in result set
         RelDlgProc      - Manage relative row number dialog
         StmtDlgProc     - Manage SQL statement dialog
         UpdateDlgProc   - Manage update row dialog
         SqlTablesDlgProc- handle SQLTables-type request
         ClassOnCommand - handle a command message


  This code is furnished on an as-is basis as part of the ODBC SDK and is
  intended for example purposes only.

--------------------------------------------------------------------------*/

// Includes ----------------------------------------------------------------
#include "headers.h"

#include    "resource.h"
#include "crsrdemo.h"



const char szCREATE[] = "CREATE TABLE %s (id int NOT NULL, name char(31) NOT NULL, C3 int)";
const char szDROP[]   = "DROP TABLE %s";
const char szINSERT[] = "INSERT INTO %s VALUES (?, '-FakeTable-FakeTable-FakeTable-', NULL)";

const int   xFIRST = 10;
const int   cxSEP  = 6;
const int   cySEP  = 3;
const int   cxNAME = 35;
const int   cyNAME = 8;
const int   cxEDIT = 180;
const int   cyEDIT = 10;

const DWORD dwDLGSTYLE    = DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU;
const DWORD dwSTATICSTYLE = WS_CHILD | WS_VISIBLE | SS_RIGHT;
const DWORD dwEDITSTYLE   = WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_LEFT;

#define STMTError(x) ODBCError(SQL_NULL_HENV, SQL_NULL_HDBC, lpmtbl->hstmt, (x))

#define  USERDATA GWL_USERDATA


// Types -------------------------------------------------------------------
typedef struct tagMTBL {                  // Make table structure
   SQLHSTMT hstmt;                        //   HSTMT in use
   SDWORD   i;                            //   Rows inserted
} MTBL, FAR *LPMTBL;


// Prototypes --------------------------------------------------------------
void INTFUNC AddEditControls(HWND, LPCHILD);
void INTFUNC CenterDialog(HWND);
BOOL INTFUNC GetEditControls(HWND, LPCHILD);
BOOL INTFUNC IsMsgWaiting(HWND);
BOOL INTFUNC DlgProcFilter(HWND, UINT, WPARAM, LPARAM);


/* AddEditControls ---------------------------------------------------------
   Description: Add one edit control for each updateable bound column to
                the dialog box
                --------------------------------------------------------------------------*/
void INTFUNC AddEditControls(HWND hDlg, LPCHILD lpChild)
{
#define DLGX(x)   (((x) * LOWORD(dwBaseUnits)) / 4)
#define DLGY(y)   (((y) * HIWORD(dwBaseUnits)) / 8)

   HWND  hWnd;
   HFONT hfont;
   RECT  rc;
   LPCOL lpcol;
   char  sz[cbMAXSQL];
   char  szFmt[cbSTRLEN];
   DWORD dwBaseUnits;
   UINT  idName, idEdit;
   int      xName, yName;
   int      cxName, cyName;
   int      xEdit, yEdit;
   int      cxEdit, cyEdit;
   int      i;
   HDC   hdc;
   SIZE  size;

   // Determine basic characteristics and start position in dialog
   hfont = (HFONT)SendDlgItemMessage(hDlg, IDC_STATIC1,
                                     WM_GETFONT, 0, 0L);

   dwBaseUnits = GetDialogBaseUnits();

   cxName = DLGX(cxNAME);
   cyName = DLGY(cyNAME);
   cxEdit = DLGX(cxEDIT);
   cyEdit = DLGY(cyEDIT);

   LoadString(g_hinst, IDS_COLNAME, szFmt, sizeof(szFmt));

   // Calculate the size of the largest name label

   hdc = GetDC(NULL);

   if( hdc ) {
      for( i = 0, lpcol = lpChild->lpcol; i < lpChild->ccol; i++, lpcol++ )
         if( IsUpdateable(lpcol->fSqlType) ) {
            wsprintf(sz, szFmt, lpcol->szName);
            GetTextExtentPoint(hdc, sz, lstrlen(sz), &size);
            if( size.cx > cxName )
               cxName = size.cx;
         }
      ReleaseDC(NULL, hdc);
   }

   GetWindowRect(GetDlgItem(hDlg, IDOK), &rc);

   xName = DLGX(xFIRST);
   yName = (4 * DLGY(cySEP)) + (DLGY(cySEP) / 2) + (2 * (rc.bottom - rc.top));

   xEdit = xName + cxName + DLGX(cxSEP);

   idName = stc1;
   idEdit = edt1;

   // For each bound, updateable column, create and add an edit control
   for (i=0, lpcol=lpChild->lpcol; i < lpChild->ccol; i++, lpcol++) {
      if (IsUpdateable(lpcol->fSqlType)) {

         // Create control label
         wsprintf(sz, szFmt, lpcol->szName);

         hWnd = CreateWindow(szSTATICCLASS, sz, dwSTATICSTYLE,
                             xName, yName, cxName, cyName, hDlg,
                             (HMENU)idName, g_hinst, NULL);

         FORWARD_WM_SETFONT(hWnd, hfont, 0, SendMessage);

         // Create (and intialize) edit control
         yEdit = yName - ((cyEDIT - cyNAME) / 2);

         GetCurrentValue(sz, lpcol, lpChild);

         hWnd = CreateWindow(szEDITCLASS, sz, dwEDITSTYLE,
                             xEdit, yEdit, cxEdit, cyEdit, hDlg,
                             (HMENU)idEdit, g_hinst, NULL);

         FORWARD_WM_SETFONT(hWnd, hfont, 0, SendMessage);

         // Limit number of characters user can type to column display size
         Edit_LimitText(hWnd, lpcol->cbc-1);

         yName += cyEdit + DLGY(cySEP);

         idName++;
         idEdit++;
      }
   }

   // Grow dialog so that all controls are visible
   GetClientRect(hDlg, &rc);

   rc.top    = 0;
   rc.bottom = yName + DLGY(cySEP);

   rc.left   = 0;
   rc.right  = (2 * DLGX(xFIRST)) + DLGX(cxNAME) + DLGX(cxEDIT) + DLGX(cxSEP);

   AdjustWindowRect(&rc, dwDLGSTYLE, FALSE);
   MoveWindow(hDlg, 0, 0, rc.right - rc.left, rc.bottom - rc.top, TRUE);

   // Place OK and Cancel buttons appropriately
   GetClientRect(hDlg, &rc);
   {  RECT  rcButton;
      int      x, y;

      GetWindowRect(GetDlgItem(hDlg, IDOK), &rcButton);

      x = rc.right - DLGX(cxSEP) - (rcButton.right - rcButton.left);
      y = DLGY(cySEP);

      MoveWindow(GetDlgItem(hDlg, IDOK),
                 x, y,
                 rcButton.right - rcButton.left,
                 rcButton.bottom - rcButton.top,
                 TRUE);

      y += rcButton.bottom - rcButton.top + (DLGY(cySEP) / 2);

      GetWindowRect(GetDlgItem(hDlg, IDCANCEL), &rcButton);
      MoveWindow(GetDlgItem(hDlg, IDCANCEL),
                 x, y,
                 rcButton.right - rcButton.left,
                 rcButton.bottom - rcButton.top,
                 TRUE);
   }

   return;
}


/* CenterDialog ------------------------------------------------------------
   Description: Center dialog over its owning parent window
                If the entire dialog does not fit on the desktop,
                ensure upper left corner is always visible
                --------------------------------------------------------------------------*/
void INTFUNC CenterDialog(HWND hDlg)
{
   RECT  rcDlg, rcScr, rcParent;
   int      cx, cy;

   GetWindowRect(hDlg, &rcDlg);
   cx = rcDlg.right  - rcDlg.left;
   cy = rcDlg.bottom - rcDlg.top;

   GetWindowRect(GetParent(hDlg), &rcParent);
   rcDlg.top    = rcParent.top +
      (((rcParent.bottom - rcParent.top) - cy) >> 1);
   rcDlg.left   = rcParent.left +
      (((rcParent.right - rcParent.left) - cx) >> 1);
   rcDlg.bottom = rcDlg.top  + cy;
   rcDlg.right  = rcDlg.left + cx;

   GetWindowRect(GetDesktopWindow(), &rcScr);
   if (rcDlg.bottom > rcScr.bottom) {
      rcDlg.bottom = rcScr.bottom;
      rcDlg.top    = rcDlg.bottom - cy;
   }
   if (rcDlg.right  > rcScr.right) {
      rcDlg.right = rcScr.right;
      rcDlg.left  = rcDlg.right - cx;
   }

   if (rcDlg.left < 0) rcDlg.left = 0;
   if (rcDlg.top  < 0) rcDlg.top  = 0;

   MoveWindow(hDlg, rcDlg.left, rcDlg.top, cx, cy, FALSE);
   return;
}


/* DoDialog ----------------------------------------------------------------
   Description: Launch a dialog passing child window variables
   --------------------------------------------------------------------------*/
int INTFUNC DoDialog(HWND    hWndParent,
                     int     nDlgResNum,
                     DLGPROC lpDlgProc)
{
   HWND  hWnd;
   LPCHILD  lpChild;
   int      nRC;

   hWnd    = FORWARD_WM_MDIGETACTIVE(g_hwndClient, SendMessage);
   lpChild = (hWnd
              ? (LPCHILD)GetWindowLong(hWnd, 0)
              : NULL);

   nRC = DialogBoxParam(g_hinst,
                        MAKEINTRESOURCE(nDlgResNum),
                        hWndParent,
                        lpDlgProc,
                        (LONG)lpChild);
   return nRC;
}

/* MyCreateDialog ------------------------------------------------------------
   Description: Launch a  modeless dialog passing child window variables
--------------------------------------------------------------------------*/

HWND INTFUNC MyCreateDialog(HWND    hWndParent,
                            int     nDlgResNum,
                            DLGPROC lpDlgProc)
{
   HWND  hWnd, hWndRet;
   LPCHILD  lpChild;

   hWnd    = FORWARD_WM_MDIGETACTIVE(g_hwndClient, SendMessage);
   lpChild = (hWnd
              ? (LPCHILD)GetWindowLong(hWnd, 0)
              : NULL);

   hWndRet = CreateDialogParam(g_hinst,
                               MAKEINTRESOURCE(nDlgResNum),
                               hWndParent,
                               lpDlgProc,
                               (LPARAM)lpChild);
   return hWndRet;
}

/* GetEditControls ---------------------------------------------------------
   Description: Get values from edit controls and move to row-set buffers
   --------------------------------------------------------------------------*/
BOOL INTFUNC GetEditControls(HWND hDlg, LPCHILD lpChild)
{
   LPCOL lpcol;
   char  sz[cbMAXSQL];
   UINT  idEdit;
   BOOL  fChangeMade;
   int      i;

   fChangeMade = FALSE;
   idEdit      = edt1;

   // For each bound, updateable column, retrieve the value
   for (i=0, lpcol=lpChild->lpcol; i < lpChild->ccol; i++, lpcol++) {
      if (IsUpdateable(lpcol->fSqlType)) {

         // Get the control value
         SendDlgItemMessage(hDlg, idEdit, WM_GETTEXT,
                            (WPARAM)sizeof(sz), (LPARAM)((LPSTR)sz));

         // Move into row-set buffer
         if (SetCurrentValue(sz, lpcol, lpChild) && !fChangeMade)
            fChangeMade = TRUE;

         idEdit++;
      }
   }

   return fChangeMade;
}


/* IsMsgWaiting ------------------------------------------------------------
   Description: Return TRUE if the Cancel button has been pressed
   --------------------------------------------------------------------------*/
BOOL INTFUNC IsMsgWaiting(HWND hWnd)
{
   MSG   msg;

   UNREF_PARAM (hWnd);

   // Check all waiting messages
   while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

      // Process message
      TranslateMessage(&msg);
      DispatchMessage(&msg);

      // Return TRUE if the Cancel button was pressed
      if ((msg.message == WM_COMMAND
           && GET_WM_COMMAND_ID(msg.wParam, msg.lParam) == IDCANCEL)
          || msg.message == WMU_CANCEL)
         return TRUE;
   }
   return FALSE;
}

/* OptionsDlgProc ----------------------------------------------------------
   Description: handle options dialog
----------------------------------------------------------------------------*/

BOOL EXPFUNC OptionsDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{


   switch (msg) {

     case WM_INITDIALOG:
      CenterDialog(hDlg);

      SetWindowLong(hDlg, USERDATA, (LONG)lParam);
      InitializeDialogControls(hDlg, (LPCHILD) lParam);

      return TRUE;

     case WM_COMMAND:
      (void) HANDLE_WM_COMMAND(hDlg,wParam,lParam,ClassOnCommand);
      break;

      // New option dialog selected

     case WMU_NEWOPTION:
      {
         LPCHILD  lpChild = (LPCHILD) GetWindowLong(hDlg, USERDATA);

         if (g_hwndChildDialog)
            DestroyWindow(g_hwndChildDialog);

         g_hwndChildDialog = MyCreateDialog(hDlg,
                                            (int) lParam,
                                            ChildOptDlgProc);

         SetFocus(GetDlgItem(hDlg, IDC_OPTIONLIST));

         break;
      }


      // Set title of option area


     case WMU_SETSUBTEXT:
      {
         char  szBuffer[1000];

         ListBox_GetText(GetDlgItem(hDlg, wParam),
                         ListBox_GetCurSel(GetDlgItem(hDlg,wParam)),
                         szBuffer);

         Static_SetText( GetDlgItem(hDlg, IDC_OPTIONAREA_TITLE),
                        szBuffer);
         break;

      }

   }

   return DlgProcFilter(hDlg, msg, wParam, lParam);
}

/* ChildOptDlgProc --------------------------------------------------------
   Description: handle generic dialog
----------------------------------------------------------------------------*/

BOOL EXPFUNC ChildOptDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{

   switch (msg) {


     case WM_INITDIALOG:
      SetWindowLong(hDlg, USERDATA, (LONG)lParam);
      InitializeDialogControls(hDlg, (LPCHILD) lParam);

      // Align the window to a hidden static in the parent

      (void) AlignToControl(hDlg, GetParent(hDlg), IDC_OPTION_WINPOS);

      return TRUE;

     case WM_COMMAND:
      return (BOOL)HANDLE_WM_COMMAND(hDlg,wParam,lParam,ClassOnCommand);

   }

   return DlgProcFilter(hDlg, msg, wParam, lParam);
}


/* AboutDlgProc ------------------------------------------------------------
   Description: Display about box
   --------------------------------------------------------------------------*/
BOOL EXPFUNC AboutDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
   UNREF_PARAM (lParam);

   switch (msg) {
     case WM_INITDIALOG:
      CenterDialog(hDlg);
      return TRUE;

     case WM_COMMAND:
      if (GET_WM_COMMAND_ID(wParam, lParam) == IDOK
          || GET_WM_COMMAND_ID(wParam, lParam) == IDCANCEL) {
         EndDialog(hDlg, GET_WM_COMMAND_ID(wParam, lParam));
         return TRUE;
      }
      break;
   }

   return DlgProcFilter(hDlg, msg, wParam, lParam);
}


/* AbsDlgProc --------------------------------------------------------------
   Description: Get absolute row number to fetch
   --------------------------------------------------------------------------*/
BOOL EXPFUNC AbsDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
   LPCHILD  lpChild;
   char  sz[11];
   char  *EndPtr;
   SDWORD   arow;

   lpChild = (LPCHILD)GetWindowLong(hDlg, USERDATA);

   switch (msg) {
     case WM_INITDIALOG:
      CenterDialog(hDlg);

      lpChild = (LPCHILD)lParam;

      SetWindowLong(hDlg, USERDATA, (LONG)lpChild);
      wsprintf(sz, "%ld", lpChild->arow);
      SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), sz);
      SendDlgItemMessage(hDlg, IDC_EDIT1,
                         EM_LIMITTEXT, sizeof(sz)-1, 0L);
      return TRUE;

     case WM_COMMAND:
      switch (GET_WM_COMMAND_ID(wParam, lParam)) {
        case IDOK:
         GetWindowText(GetDlgItem(hDlg, IDC_EDIT1), sz, sizeof(sz));
         arow = strtol((char*) sz, &EndPtr, 10);
         for (; *EndPtr &&
              ISWHITE(*EndPtr); EndPtr = AnsiNext(EndPtr));
         // the number inputed is within '0' to '9' or + or -
         if (*EndPtr != '\0') {
            MessageBox(hDlg,
                       "Invalid absolute row number",
                       NULL,
                       MB_ICONSTOP);
            return TRUE;
         }
         lpChild->arow = arow;

        case IDCANCEL:
         EndDialog(hDlg, GET_WM_COMMAND_ID(wParam, lParam));
         return TRUE;
      }
      break;
   }

   return DlgProcFilter(hDlg, msg, wParam, lParam);
}


/* DataDlgProc -------------------------------------------------------------
   Description: Display large data value (retrieved via SQLGetData)
   --------------------------------------------------------------------------*/
BOOL EXPFUNC DataDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
   switch (msg) {
     case WM_INITDIALOG: {
        LPBIGCOL  lpbc;
        char      sz[cbSTRLEN];
        char      szNum[cbSTRLEN];
        char      szFmt[cbSTRLEN];

        CenterDialog(hDlg);

        lpbc = (LPBIGCOL)lParam;

        if (lpbc->cb == SQL_NULL_DATA) {
           lstrcpy(lpbc->lpsz, g_szNull);
           lpbc->cb = 0;
           _ltoa(0, szNum, 10);
        }
        else if (lpbc->cb == SQL_NO_TOTAL)
           lstrcpy(szNum, g_szUnknown);
        else
           _ltoa(lpbc->cb, szNum, 10);

        LoadString(g_hinst, IDS_DATADLG, szFmt, sizeof(szFmt));
        wsprintf(sz, szFmt, lpbc->szName, szNum);
        SetWindowText(GetDlgItem(hDlg, IDC_TEXT1), sz);

        SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), lpbc->lpsz);
        return TRUE;
     }

     case WM_COMMAND:
      switch (GET_WM_COMMAND_ID(wParam, lParam)) {
        case IDOK:
        case IDCANCEL:
         EndDialog(hDlg, GET_WM_COMMAND_ID(wParam, lParam));
         return TRUE;
      }
      break;
   }

   return DlgProcFilter(hDlg, msg, wParam, lParam);
}


/* RelDlgProc --------------------------------------------------------------
   Description: Get relative row offset to fetch
   --------------------------------------------------------------------------*/
BOOL EXPFUNC RelDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
   LPCHILD  lpChild;
   char  sz[7];

   lpChild = (LPCHILD)GetWindowLong(hDlg, USERDATA);

   switch (msg) {
     case WM_INITDIALOG:
      CenterDialog(hDlg);

      lpChild = (LPCHILD)lParam;
      SetWindowLong(hDlg, USERDATA, (LONG)lpChild);

      wsprintf(sz, "%ld", lpChild->rrow);
      SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), sz);
      SendDlgItemMessage(hDlg, IDC_EDIT1,
                         EM_LIMITTEXT, sizeof(sz)-1, 0L);
      return TRUE;

     case WM_COMMAND:
      switch (GET_WM_COMMAND_ID(wParam, lParam)) {
        case IDOK: {
           SDWORD rrow;
           char   *EndPtr;

           GetWindowText(GetDlgItem(hDlg, IDC_EDIT1), sz, sizeof(sz));
           rrow = strtol((char*) sz, &EndPtr, 10);
           for (; *EndPtr &&
                ISWHITE(*EndPtr); EndPtr = AnsiNext(EndPtr));
           // the number inputed is within '0' to '9' or + or -
           if (*EndPtr != '\0' || rrow < -100000 || rrow > 100000) {
              MessageBox(hDlg,
                         "Step amount must be between -100,000 and 100,000",
                         NULL,
                         MB_ICONSTOP);
              return TRUE;
           }
           lpChild->rrow = rrow;
        }

        case IDCANCEL:
         EndDialog(hDlg, GET_WM_COMMAND_ID(wParam, lParam));
         return TRUE;
      }
      break;
   }

   return DlgProcFilter(hDlg, msg, wParam, lParam);
}


/* StmtDlgProc -------------------------------------------------------------
   Description: Get SQL statement to execute
   --------------------------------------------------------------------------*/
BOOL EXPFUNC StmtDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
   LPCHILD  lpChild;

   lpChild = (LPCHILD)GetWindowLong(hDlg, USERDATA);

   switch (msg) {
     case WM_INITDIALOG:
      CenterDialog(hDlg);

      lpChild = (LPCHILD)lParam;
      SetWindowLong(hDlg, USERDATA, (LONG)lpChild);

      SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), lpChild->sql);
      SendDlgItemMessage(hDlg, IDC_EDIT1, EM_LIMITTEXT, cbMAXSQL-1, 0L);
      return TRUE;

     case WM_COMMAND:
      switch (GET_WM_COMMAND_ID(wParam, lParam)) {
        case IDOK:
         GetWindowText(GetDlgItem(hDlg, IDC_EDIT1),
                       lpChild->sql, cbMAXSQL);

         lpChild->dwOperation = OPER_SELECT;


        case IDCANCEL:
         EndDialog(hDlg, wParam);
         return TRUE;
      }
      break;
   }

   return DlgProcFilter(hDlg, msg, wParam, lParam);
}


/* UpdateDlgProc -----------------------------------------------------------
   Description: Get new values with which to update the current row
   --------------------------------------------------------------------------*/
BOOL EXPFUNC UpdateDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
   LPCHILD  lpChild;

   lpChild = (LPCHILD)GetWindowLong(hDlg, USERDATA);

   switch (msg) {

      // Build dialog dynamically, adding appropriate edit controls
     case WM_INITDIALOG:
      lpChild = (LPCHILD)lParam;

      SetWindowLong(hDlg, USERDATA, (LONG)lpChild);
      AddEditControls(hDlg, lpChild);
      SendDlgItemMessage(hDlg,edt1,EM_SETSEL,GET_EM_SETSEL_MPS(0, -1));

      CenterDialog(hDlg);
      SetFocus(GetDlgItem(hDlg, edt1));
      return FALSE;

      // Close dialog updating row-set buffer (if OK) with new values
     case WM_COMMAND:
      switch (GET_WM_COMMAND_ID(wParam, lParam)) {
        case IDOK:
         if (!GetEditControls(hDlg, lpChild))
            GET_WM_COMMAND_ID(wParam, lParam) = IDCANCEL;

        case IDCANCEL:
         EndDialog(hDlg, GET_WM_COMMAND_ID(wParam, lParam));
         return TRUE;
      }
      break;
   }

   return DlgProcFilter(hDlg, msg, wParam, lParam);
}


/* FindDlgProc -------------------------------------------------------------
   Description: Get text string to find in result set
   --------------------------------------------------------------------------*/
BOOL EXPFUNC FindDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
   LPCHILD  lpChild;

   lpChild = (LPCHILD)GetWindowLong(hDlg, USERDATA);

   switch (msg) {
     case WM_INITDIALOG:
      CenterDialog(hDlg);

      lpChild = (LPCHILD)lParam;
      SetWindowLong(hDlg, USERDATA, (LONG)lpChild);

      SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), lpChild->sql);
      SendDlgItemMessage(hDlg, IDC_EDIT1, EM_LIMITTEXT, cbMAXSQL-1, 0L);
      return TRUE;

     case WM_COMMAND:
      switch (GET_WM_COMMAND_ID(wParam, lParam)) {
        case IDOK:
         GetWindowText(GetDlgItem(hDlg, IDC_EDIT1),
                       lpChild->sql, cbMAXSQL);

        case IDCANCEL:
         EndDialog(hDlg, wParam);
         return TRUE;
      }
      break;
   }

   return DlgProcFilter(hDlg, msg, wParam, lParam);
}

/*---------------------------------------------------------------------------
** SQLTablesDlgProc -- get information for SQLTables and similar functions
----------------------------------------------------------------------------*/
BOOL EXPFUNC SQLTablesDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
   LPCHILD  lpChild;

   lpChild = (LPCHILD)GetWindowLong(hDlg, USERDATA);

   switch (msg) {
     case WM_INITDIALOG:
      CenterDialog(hDlg);

      lpChild = (LPCHILD)lParam;
      SetWindowLong(hDlg, USERDATA, (LONG)lpChild);

      // Set the default button
      if (!(lpChild->dwGuiFlags & GUIF_TABLES_RADIO)) {
         lpChild->dwOperation = IDC_TABLE_RAD_TABLE;
         lpChild->dwRadioButton = IDC_TABLE_RAD_TABLE;
      }

      // Set the dialog up

      ControlValue(  lpChild,
                   hDlg,
                   GetDlgItem(hDlg,lpChild->dwRadioButton),
                   lpChild->dwRadioButton,
                   ACT_INIT);

      ControlValue(  lpChild,
                   hDlg,
                   GetDlgItem(hDlg,lpChild->dwRadioButton),
                   lpChild->dwRadioButton,
                   ACT_TRIGGER);

      ControlValue(  lpChild,
                   hDlg,
                   GetDlgItem(hDlg,IDC_TABLEINFO_QUALIFIER),
                   IDC_TABLEINFO_QUALIFIER,
                   ACT_INIT);

      ControlValue(  lpChild,
                   hDlg,
                   GetDlgItem(hDlg,IDC_TABLEINFO_NAME),
                   IDC_TABLEINFO_NAME,
                   ACT_INIT);

      ControlValue(  lpChild,
                   hDlg,
                   GetDlgItem(hDlg,IDC_TABLEINFO_OWNER),
                   IDC_TABLEINFO_OWNER,
                   ACT_INIT);

      ControlValue(  lpChild,
                   hDlg,
                   GetDlgItem(hDlg,IDC_TABLEINFO_TYPE),
                   IDC_TABLEINFO_TYPE,
                   ACT_INIT);

      ControlValue(  lpChild,
                   hDlg,
                   GetDlgItem(hDlg,IDC_TABLEINFO_COLNAME),
                   IDC_TABLEINFO_COLNAME,
                   ACT_INIT);
      return TRUE;

     case WM_COMMAND:
      return (BOOL)HANDLE_WM_COMMAND(hDlg, wParam, lParam, ClassOnCommand);
      break;

   }

   return DlgProcFilter(hDlg, msg, wParam, lParam);

}

/*---ClassCommand---------------------------------------------------------
   Filters commands for dialogs.   Forwards those messages that we think
   are interesting to a handler that processes the events.
---------------------------------------------------------------------------*/

VOID INTFUNC ClassOnCommand(HWND hWnd, int iId, HWND hWndCtl, UINT uNotify)
{
   LPCHILD  lpChild;

   lpChild = (LPCHILD)GetWindowLong(hWnd,USERDATA);

   if (!(lpChild))
      return;

   switch (uNotify) {

     case   BN_CLICKED:       // button control selected
     case   EN_UPDATE:        // edit box has been updated
     case   LBN_SELCHANGE:       // listbox has gotten a message
      ControlValue(lpChild, hWnd, hWndCtl, iId, ACT_TRIGGER);
      break;

   }
}


/*
 ** ControlValue -- Initialize a control's value from the child's state, or
 **               set the child's state from the control.   All control-
 **               specific logic should go here.
 **
 ** Parameters:
 **      lpChild  -- child state
 **      hDlg  --  id of the active dialog
 **      hCtl  --  control's window
 **      iId      --  control's id
 **      iAction  -- Action to take -- ACT_INIT or ACT_TRIGGER
 **
 ** No return value
 */

VOID INTFUNC ControlValue (LPCHILD     lpChild,
                           HWND     hDlg,
                           HWND     hCtl,
                           int         iId,
                           int         iAction)
{
   int      iLbSelection;
   DWORD dwListData;
   BOOL  fTemp;
   UCHAR szBuffer[MAXNAME];

   const DIALOG_PAIR dpOptList[] = {
      {"Binding",          IDD_BIND_OPTIONS},
      {"General options",     IDD_GENERAL_OPTIONS},
      {"Scrolling Options",   IDD_SCROLLING_OPTIONS},
      {"Concurrency Options", IDD_CONCURRENCY_OPTIONS}};

   switch (iId) {

     case   IDOK:                   // generic OK
     case   IDCANCEL:                  // generic CANCEL
      if (iAction == ACT_TRIGGER) {
         if (g_hwndChildDialog) {
            g_hwndChildDialog = NULL;
         }
         EndDialog(hDlg, iId);
      }
      break;

     case IDC_RADIO_BINDROW:
     case IDC_RADIO_BINDCOL:
      if (SetOrGetCheck(hCtl, iAction, (iId == lpChild->fBindByRow))) {
         lpChild->fBindByRow = iId;
      }
      break;

     case IDC_RADIO_READONLY:
      if (SetOrGetCheck(hCtl, iAction,
                        (lpChild->fConcurrency == SQL_CONCUR_READ_ONLY))) {
         lpChild->fConcurrency = SQL_CONCUR_READ_ONLY;
      }
      break;
     case IDC_RADIO_LOCKING:
      if (SetOrGetCheck(hCtl, iAction,
                        (lpChild->fConcurrency == SQL_CONCUR_LOCK))) {
         lpChild->fConcurrency = SQL_CONCUR_LOCK;
      }
      break;
     case IDC_RADIO_OPTIMISTIC:
      if (SetOrGetCheck(hCtl, iAction,
                        (lpChild->fConcurrency == SQL_CONCUR_ROWVER))) {
         lpChild->fConcurrency = SQL_CONCUR_ROWVER;
      }
      break;
     case IDC_RADIO_OPTIMVALUE:
      if (SetOrGetCheck(hCtl, iAction,
                        (lpChild->fConcurrency == SQL_CONCUR_VALUES))) {
         lpChild->fConcurrency = SQL_CONCUR_VALUES;
      }
      break;

     case IDC_RADIO_FORWARD:
      if (SetOrGetCheck(hCtl, iAction,
                        (lpChild->crowKeyset == SQL_CURSOR_FORWARD_ONLY))) {
         lpChild->crowKeyset = SQL_CURSOR_FORWARD_ONLY;
      }
      break;
     case IDC_RADIO_SNAPSHOT:
      if (SetOrGetCheck(hCtl, iAction,
                        (lpChild->crowKeyset == SQL_CURSOR_STATIC))) {
         lpChild->crowKeyset = SQL_CURSOR_STATIC;
      }
      break;
     case IDC_RADIO_KEYSET:
      if (SetOrGetCheck(hCtl, iAction,
                        (lpChild->crowKeyset == SQL_CURSOR_KEYSET_DRIVEN))) {
         lpChild->crowKeyset = SQL_CURSOR_KEYSET_DRIVEN;
      }
      break;
     case IDC_RADIO_DYNAMIC:
      if (SetOrGetCheck(hCtl, iAction,
                        (lpChild->crowKeyset == SQL_CURSOR_DYNAMIC))) {
         lpChild->crowKeyset = SQL_CURSOR_DYNAMIC;
      }
      break;

     case IDC_CHECK_BINDALL:
      fTemp = SetOrGetCheck(hCtl,iAction, (lpChild->fBindAll));
      lpChild->fBindAll = fTemp;
      Edit_Enable(GetDlgItem(hDlg,IDC_EDIT_BIND), !(fTemp));
      Static_Enable(GetDlgItem(hDlg, IDC_STATIC_NBIND), !(fTemp));
      break;

     case IDC_EDIT_BIND:
      if (lpChild->fBind)
         wsprintf((LPSTR)szBuffer,"%s", lpChild->szBind);
      else  wsprintf((LPSTR)szBuffer,"%u", lpChild->cBind);
      SetOrGetEditArray(hCtl, szBuffer, iAction);
      if (iAction == ACT_TRIGGER) {
         lpChild->fBind = TRUE;
         strncpy(lpChild->szBind, szBuffer, cbINTLEN);
         lpChild->szBind[cbINTLEN-1] = '\0';
      }
      break;

     case IDC_EDIT_ROWSETSIZE:
      if (lpChild->fRowset)
         wsprintf((LPSTR)szBuffer,"%s", lpChild->szRowset);
      else wsprintf((LPSTR)szBuffer,"%u", lpChild->crowRowset);
      SetOrGetEditArray(hCtl, szBuffer, iAction);
      if (iAction == ACT_TRIGGER) {
         lpChild->fRowset = TRUE;
         strncpy(lpChild->szRowset, szBuffer, cbINTLEN);
         lpChild->szRowset[cbINTLEN-1] = '\0';
      }
      break;

     case IDC_MAXCOL:
      if (lpChild->fMaxBind)
         wsprintf((LPSTR)szBuffer, "%s", lpChild->szMaxBind);
      else wsprintf((LPSTR)szBuffer, "%ld", lpChild->crowMaxBind);
      SetOrGetEditArray(hCtl, szBuffer, iAction);
      if (iAction == ACT_TRIGGER) {
         lpChild->fMaxBind = TRUE;
         strncpy(lpChild->szMaxBind, szBuffer, cbINTLEN);
         lpChild->szMaxBind[cbINTLEN-1] = '\0';
      }
      break;

     case IDC_TABLE_RAD_STATISTICS:       // TABLEINFO->STATSTICS
     case IDC_TABLE_RAD_COLUMN:           // TABLEINFO->COLUMNS
     case IDC_TABLE_RAD_PRIV:          // TABLEINFO->PRIVILEGES
     case IDC_TABLE_RAD_PROC:          // TABLEINFO->PROCEDURES
     case IDC_TABLE_RAD_TABLE:            // TABLEINFO->TABLES

      // Initialize the button, or set iAction to its value
      // Hide any fields not related to the button, show fields related

      if( SetOrGetCheck(hCtl, iAction,
                        (iId == (int)lpChild->dwRadioButton)) )
         lpChild->dwOperation = (UWORD) iId;

      if (iAction == ACT_TRIGGER) {
         lpChild->dwGuiFlags |= GUIF_TABLES_RADIO;
         lpChild->dwRadioButton = iId;
         (void) SetHiddenFields(hDlg, iId);
      }
      break;

     case IDC_CHECK_FETCH:
      if (SetOrGetCheck(hCtl, iAction, (int)IS_ALLWFETCH(lpChild)))
         lpChild->dwGuiFlags |= GUIF_ALWAYSFETCH;
      else
         lpChild->dwGuiFlags &= ~GUIF_ALWAYSFETCH;

      break;

     case IDC_CHECK_ASYNC:
      lpChild->fAsync = SetOrGetCheck(hCtl,iAction,lpChild->fAsync);
      break;

     case IDC_TABLEINFO_QUALIFIER:        // TABLEINFO->QUALIFIER
      SetOrGetEditArray(hCtl, lpChild->szQualifier, iAction);
      break;

     case IDC_TABLEINFO_NAME:          // TABLEINFO->NAME
      SetOrGetEditArray(hCtl, lpChild->szTable, iAction);
      break;

     case IDC_TABLEINFO_OWNER:            // TABLEINFO->OWNER
      SetOrGetEditArray(hCtl, lpChild->szUser, iAction);
      break;

     case IDC_TABLEINFO_TYPE:          // TABLEINFO->TYPE
      SetOrGetEditArray(hCtl, lpChild->szType, iAction);
      break;

     case IDC_TABLEINFO_COLNAME:          // TABLEINFO->COLUMN NAME
      SetOrGetEditArray(hCtl, lpChild->szColName, iAction);
      break;

     case IDC_OPTIONLIST:              // OPTIONS->options
      {

         if (iAction == ACT_INIT) {
            InitializeListBox(hDlg,
                              IDC_OPTIONLIST,
                              &dpOptList[0],
                              sizeof(dpOptList) / sizeof(DIALOG_PAIR),
                              IDD_GENERAL_OPTIONS);
         }

         // Get the title and data for the currently-selected list box

         iLbSelection = ListBox_GetCurSel(hCtl);
         dwListData   = ListBox_GetItemData(hCtl, iLbSelection);

         SendMessage(hDlg,WMU_NEWOPTION, iLbSelection,(LPARAM)dwListData);
         SendMessage(hDlg,WMU_SETSUBTEXT,iId, 0);

         break;
      }

   }
}

/*
** SetOrGetCheck      -- set a value based upon a button action, or set a
**                 check button if the action is equal to a value
**                 Also used for radios
**
** Parameters:
**    hCtl     -- control handle
**    iAction     -- ACT_INIT or ACT_TRIGGER
**    bEqual      -- Initialization -- should value be set?
**
** Returns:
**    TRUE if checkbox is now set
*/
INLINE BOOL SetOrGetCheck(
                          HWND   hCtl,
                          int    iAction,
                          BOOL   bEqual)
{
   if (iAction == ACT_INIT) {
      Button_SetCheck(hCtl, bEqual);
      return bEqual;
   }

   if (iAction == ACT_TRIGGER) {
      Button_SetCheck(hCtl, Button_GetCheck(hCtl));
      return Button_GetCheck(hCtl);
   }

   return FALSE;
}


/*
** SetOrGetEditArray -- set the value of an array from an edit control, or
**                set the edit control from the array  (inline)
**
** Parameters:
**    hCtl  -- control
**    lpStr -- string
**    iAction  -- ACT_INIT or ACT_TRIGGER
**
** Notes:   Assumes lpStr is MAXNAME bytes long
*/
INLINE VOID SetOrGetEditArray(
                              HWND  hCtl,
                              UCHAR FAR *lpStr,
                              int      iAction)
{
   if (iAction == ACT_INIT)
      Edit_SetText(hCtl, (LPSTR)lpStr);
   else
      if (iAction == ACT_TRIGGER)
         Edit_GetText(hCtl, (LPSTR)lpStr, MAXNAME - 1);
}

/*
** SetHiddenFields -- show or hide hidden fields in a dialog box, depending
**               upon the action taken.
**
** Parameters:
**    hDlg  -- dialog we are dealing with
**    iAct  -- action
**
*/
BOOL    INTFUNC SetHiddenFields(
                                HWND   hWnd,
                                int    iAct)
{
   HWND  hTTag, hCol;
   HWND  hType, hCTag;

   // Get handles for all of the windows we want to deal with

   hTTag = GetDlgItem(hWnd, IDC_TYPETAG);
   hCol  = GetDlgItem(hWnd, IDC_COLTAG);

   hType = GetDlgItem(hWnd, IDC_TABLEINFO_TYPE);
   hCTag = GetDlgItem(hWnd, IDC_TABLEINFO_COLNAME);

   if (hType) {
      Edit_Enable(hType, (iAct == IDC_TABLE_RAD_TABLE)  ? 1 : 0);
      ShowWindow(hType,  (iAct == IDC_TABLE_RAD_TABLE)  ? SW_SHOW : SW_HIDE);
      ShowWindow(hTTag,  (iAct == IDC_TABLE_RAD_TABLE)  ? SW_SHOW : SW_HIDE);

      Edit_Enable(hCTag, (iAct == IDC_TABLE_RAD_COLUMN) ? 1 : 0);
      ShowWindow(hCol,   (iAct == IDC_TABLE_RAD_COLUMN) ? SW_SHOW : SW_HIDE);
      ShowWindow(hCTag,  (iAct == IDC_TABLE_RAD_COLUMN) ? SW_SHOW : SW_HIDE);

      return TRUE;
   }

   return FALSE;
}

/*
 **   InitializeListBox -- initialize a listbox from a DIALOG_PAIR
 **                     structure.
 **
 **  Parameters:
 **      hWnd     --  window the list box lives in
 **      lbId     --  resource id of the list box
 **      dpOptList   --  pointer to option list structure
 **      iEntries --  number of entries in the list box
 **      iDefId      --  default to select
 **
 **
 **  Returns:  FALSE
 **
 */

BOOL INTFUNC InitializeListBox(
   HWND                    hWnd,
   int                     lbId,
   const DIALOG_PAIR FAR   *dpOptList  ,
   int                     iEntries,
   int                     iDefId)
{

   int            iDlg, iIndex;
   HWND        hOptionBox;
   LPSTR       szDefaultTitle;
   hOptionBox  =  GetDlgItem(hWnd, lbId);


   for (iDlg = 0; iDlg < iEntries; iDlg++) {
      iIndex = ListBox_AddString(hOptionBox,
                                 dpOptList[iDlg].szDlgPairTitle);

      ListBox_SetItemData(hOptionBox,
                          iIndex,
                          dpOptList[iDlg].iDlgPairDlgId);


      if (iDefId == dpOptList[iDlg].iDlgPairDlgId) {
         szDefaultTitle = dpOptList[iDlg].szDlgPairTitle;
      }

   }

   ListBox_SetCurSel(hOptionBox,
                     ListBox_FindStringExact(hOptionBox, 0, szDefaultTitle));

   return FALSE;
}

/*
** InitializeDialogControls   -- Initialize all of the controls in a dialog
**                      from the lpchild structure.   Callback function.
**
** Parameters:
**    hDlg     -- dialog handle
**    lpChild     -- state structure
**
*/

VOID INTFUNC InitializeDialogControls(
                                      HWND   hDlg,
                                      LPCHILD   lpChild)
{
   FARPROC     ControlInstance = MakeProcInstance((FARPROC)InitControlCallback,
                                                  g_hinst);

   EnumChildWindows(hDlg, (WNDENUMPROC)ControlInstance, (LPARAM)lpChild);
   FreeProcInstance(ControlInstance);

}



/*
** InitControlCallback  -- callback function for initializing controls
**
** Parameters:
**    hwndChild   -- child window handle
**    lParam      -- lparam (lpChild from EnumChildProc
*/

BOOL CALLBACK InitControlCallback(
                                  HWND hwndChild,
                                  LPARAM  lParam)
{
   int      iControl= GetDlgCtrlID(hwndChild);

   if (iControl) {
      ControlValue((LPCHILD) lParam,
                   GetParent(hwndChild),
                   hwndChild,
                   iControl,
                   ACT_INIT);

   }
   return TRUE;
}



BOOL INTFUNC DlgProcFilter(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{

   switch (msg) {
     case WM_SETTEXT:
     case WM_NCPAINT:
     case WM_NCACTIVATE:
      SetWindowLong(hDlg, DWL_MSGRESULT,0L);
      return TRUE;
   }
   return FALSE;
}

/*
** AlignToControl -- align a window to a control in a dialog
**
** Parameters:
**    hWnd  -- window to align
**    hParent -- parent dialog
**    iCtlId   -- control Id
**
** Returns: BOOL that moveWindow returns
*/

BOOL INTFUNC AlignToControl(
                            HWND hWnd,
                            HWND hParent,
                            int     iCtlId)
{
   HWND  hwndDrawArea;
   RECT  rcDrawArea, rcChildWnd;
   POINT ptPoint;


   hwndDrawArea = GetDlgItem(hParent, iCtlId);
   GetWindowRect(hwndDrawArea, &rcDrawArea);
   GetWindowRect(hWnd, &rcChildWnd);

   ptPoint.x = rcDrawArea.left;
   ptPoint.y = rcDrawArea.top;

   ScreenToClient(hWnd, &ptPoint);

   return (MoveWindow(  hWnd,
                      ptPoint.x,
                      ptPoint.y,
                      rcChildWnd.right- rcChildWnd.left,
                      rcChildWnd.bottom - rcChildWnd.top,
                      FALSE));
}
