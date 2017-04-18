/*
    PROGRAM: QURYDEMO
    ========

    PURPOSE:
    ========
    demonstrates a simple MDI (Multiple Document Interface)application
    that allows a user to simultaneously connect to multiple
    hetrogeneous databases and perform SQL queries to get results.

    FUNCTIONS:
    ==========
    InitSQLEnvironment() - Initialize ODBC library
    DisplayDatabases() - Display available Data Sources
    ConnectDatabase() - Connect to a specific data source
    DriverConnectDatabase() - Connect through driver specific dialogs
    DisplayConnections() - Display List of made connections
    DisplayQueries() - Display list of Query Handles (hstmts)
    NewQueryWindow() - Open a new hstmt and update displays
    ChangeCurrentCursor() - Change current cursor display
    ChangeCurrentQuery() - Change current query display
    DisplayNewCrsrAndStmt() - update cusor & query displays
    FreeConnect() - free a connection
    FreeQuery() - free a query handle
    CloseQueryWindow() - close a query window
    ExecuteQuery() - execute a user specified query
    CloseDatabases() - check if all connections are closed
    FreeSQLEnvironment() - free ODBC library
    DisplayError() - displays SQL Error and Warnings

    COMMENTS:
    =========
    Created by Microsoft Corporation.

    The application uses MDI Child Window Titles to store values of
    connected SQLHDBCs and SQLHSTMTs. These values are also stored in the
    comboboxes that are displayed on the toolbar.

*/

#include <stdio.h>
#include <string.h>

#include <windows.h>

#include "sql.h"
#include "sqlext.h"
#include "qurydemo.h"

/*
    FUNCTION: InitSQLEnvironment()
    COMMENTS: Allocate an environment handle for ODBC function calls.
*/

BOOL FAR PASCAL InitSQLEnvironment()
{
   // reset child window count
   nChildCount = 0;

   // Allocate an Environment Handle
   if (SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&henv) != SQL_SUCCESS)
      return FALSE;

   return (SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,
                         (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER) == SQL_SUCCESS);
}

/*
    FUNCTION: DisplayDatabases(HWND hWnd)
    COMMENTS: Display a list of available data sources. Use
          SQLDataSources function call.
*/

void FAR PASCAL DisplayDatabases(HWND hWnd)
{
   SWORD     nDirection;                             //fetch direction
   SWORD     nDataSourceNameLength;                  //DSN str length
   SWORD     nSourceDescriptionLength;               //Driver Description str length
   char      szDataSourceName[MAXBUFLEN+1];          //DSN string
   char      szSourceDescription[MAXBUFLEN+1];       //Driver Description string
   SQLRETURN nResult;                                //Return Code

   //Call SQLDataSources, first with SQL_FETCH_FIRST and from then on
   //with SQL_FETCH_NEXT until it returns SQL_NO_DATA. Add
   //all returned DSNs in the provided combo box for display.
   SendMessage(hWnd, CB_RESETCONTENT, 0, 0);
   for (nDirection = SQL_FETCH_FIRST;
        (nResult = SQLDataSources(henv, nDirection, szDataSourceName, MAXBUFLEN,
                                  &nDataSourceNameLength, szSourceDescription, MAXBUFLEN, &nSourceDescriptionLength)) !=
        SQL_NO_DATA &&
        nResult != SQL_ERROR;
        nDirection = SQL_FETCH_NEXT
        )
      SendMessage(hWnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szDataSourceName);
   SendMessage(hWnd, CB_SETCURSEL, 0, 0);
}

/*
    FUNCTION: ConnectDatabase(HWND hWnd)
    COMMENTS: Connect to a DSN.
*/

BOOL FAR PASCAL ConnectDatabase(HWND hWnd)
{
   char      szBuffer[MAXBUFLEN+1];  // buffer to display successful connection on hdbc combo-box
   char      szDBName[MAXBUFLEN+1];  // DSN sting
   char      szUserName[MAXBUFLEN+1];// User name
   char      szPassword[MAXBUFLEN+1];// Password
   SQLHDBC   hdbc;                   // hdbc
   SQLRETURN nResult;                // Result code

   // check if enough windows are already open, refuse connection

   if (nChildCount >= MAXCHILDWNDS) {
      MessageBox(hWndFrame, MAXCHILDEXCEEDED, MAXCHLDERR, MB_OK | MB_ICONHAND);
      return (FALSE);
   }


   // retrieve DSN, UID and PWD values from the connect dialog box

   GetDlgItemText(hWnd, IDCOMBO_DATASOURCE, szDBName, MAXBUFLEN);
   GetDlgItemText(hWnd, IDTEXT_USERNAME, szUserName, MAXBUFLEN);
   GetDlgItemText(hWnd, IDTEXT_PASSWORD, szPassword, MAXBUFLEN);

   // Allocate a new SQLHDBC. If successful then call SQLConnect using the
   // allocated hdbc and supplied connection information.
   if ((nResult = SQLAllocHandle(SQL_HANDLE_DBC,henv, (SQLHDBC FAR *)&hdbc)) != SQL_SUCCESS) {
      DisplayError(nResult, hWnd, SQL_HANDLE_ENV, henv);
      return (FALSE);
   }

   nResult = SQLConnect(hdbc,(LPSTR)szDBName,SQL_NTS,(LPSTR)szUserName,SQL_NTS,(LPSTR)szPassword,SQL_NTS);

   // if failed to connect, free the allocated hdbc before return
   if (nResult != SQL_SUCCESS && nResult != SQL_SUCCESS_WITH_INFO) {
      DisplayError(nResult, hWnd, SQL_HANDLE_DBC, hdbc);
      SQLFreeHandle(SQL_HANDLE_DBC,hdbc);
      return (FALSE);
   }

   // display any connection information if driver returns SQL_SUCCESS_WITH_INFO
   if (nResult == SQL_SUCCESS_WITH_INFO)
      DisplayError(nResult, hWnd, SQL_HANDLE_DBC, hdbc);

   // update the hdbc(s) combo-box and create a new hstmt and its
   // associated window.
   wsprintf(szBuffer, DSN_HDBC_FORMAT, (LPSTR)szDBName, hdbc);
   nResult = (UINT)SendMessage(hWndCrsrList, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
   SendMessage(hWndCrsrList, CB_SETCURSEL, (WPARAM)nResult, 0);
   SendMessage(hWndCrsrList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);
   ChangeCurrentCursor(hWndCrsrList);
   NewQueryWindow();
   return (TRUE);
}

/*
    FUNCTION: DriverConnectDatabase(HWND hWnd)
    COMMENTS: Connect to a DSN using SQLDriverConnect function call. It
          allows driver manager and drivers to interact with the user
          directly to prompt for connection information.
*/

BOOL FAR PASCAL DriverConnectDatabase(HWND hWnd)
{
   char      szBuffer[MAXBUFLEN+1];  //display successful connection info on hdbc(s) combo-box
   char      szDBName[MAXBUFLEN+1];  //DSN string
   SWORD     swStrLen;               //String length
   SQLHDBC   hdbc;                   //hdbc
   SQLRETURN nResult;                //result code

   // Allocate a new Connection Handle.
   if ((nResult = SQLAllocHandle(SQL_HANDLE_DBC,henv, (SQLHDBC FAR *)&hdbc)) != SQL_SUCCESS) {
      DisplayError(nResult, hWnd, SQL_HANDLE_ENV, henv);
      return (FALSE);
   }

   // Call SQLDriverConnect to make a connection request. Provide SQL_DRIVER_COMPLETE_REQUIRED
   // flag sothat driver manager and driver can ask for connection information
   // If failed to connect, free the allocated hdbc in previous step.
   nResult = SQLDriverConnect(hdbc, hWnd, "", 0, szBuffer,  MAXBUFLEN, &swStrLen, SQL_DRIVER_COMPLETE_REQUIRED);
	

   if (nResult != SQL_SUCCESS && nResult != SQL_SUCCESS_WITH_INFO) {
      SQLFreeHandle(SQL_HANDLE_DBC,hdbc);
      return (FALSE);
   }

   // If driver returns additional information with SQL_SUCCESS_WITH_INFO
   // flag, display the information
   if (nResult == SQL_SUCCESS_WITH_INFO)
      DisplayError(nResult, hWnd, SQL_HANDLE_DBC, hdbc);

   // Call SQLGetInfo to find out the DSN name for the above connection.
   // Note, application should not depend upon the DSN name being present
   // in the returned connection string.
   strcpy(szDBName, DEFDBNAME); // initialize the string value


   SQLGetInfo(hdbc, SQL_DATA_SOURCE_NAME, (PTR)szDBName, MAXBUFLEN+1, &swStrLen);
	if( !*szDBName)
		strcpy(szDBName,"nameless");

   // Display the new connection information in the hdbc(s) combo-box.
   // Create a new hstmt and its associated window.
   wsprintf(szBuffer, DSN_HDBC_FORMAT, (LPSTR)szDBName, hdbc);
   nResult = (UINT)SendMessage(hWndCrsrList, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
   SendMessage(hWndCrsrList, CB_SETCURSEL, (WPARAM)nResult, 0);
   SendMessage(hWndCrsrList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);
   ChangeCurrentCursor(hWndCrsrList);
   NewQueryWindow();
   return (TRUE);
}

/*
    FUNCTION: DisplayConnections(HWND hWndhdbc)
    COMMENTS: Display list of available hdbc(s) in the given list box.
*/

void FAR PASCAL DisplayConnections(HWND hWndhdbc)
{
   int  nConnects;      // # of connections
   int  nIndex;                 // counter
   char szBuffer[MAXBUFLEN+1];  // string buffer

   // read the information from the hdbc(s) combo-box in the tool bar
   // and feed it in the given list box.

   SendMessage(hWndhdbc, LB_RESETCONTENT, 0, 0);
   nConnects = (int) SendMessage(hWndCrsrList, CB_GETCOUNT, 0, 0);
   for (nIndex = 0; nIndex < nConnects; nIndex++) {
      SendMessage(hWndCrsrList, CB_GETLBTEXT, nIndex, (LPARAM)(LPSTR)szBuffer);
      SendMessage(hWndhdbc, LB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
   }
   SendMessage(hWndhdbc, LB_SETCURSEL, 0, 0);
}

/*
    FUNCTION: DisplayQueries(HWND hWndhstmt int nCrsrIndex)
    COMMENTS: Display list of hstmt(s) for the currently selected hdbc
          in the given listbox.
*/

void FAR PASCAL DisplayQueries(HWND hWndhstmt, HWND hWndhdbc, int nCrsrIndex)
{
   char  szBuffer[MAXBUFLEN+1];  // MDI child window title
   HWND  hWndChild;              // MDI child window handle
   SQLHDBC  hdbc1;               // hdbc in the window title
   SQLHDBC  hdbc2;               // selected hdbc in the list box
   SQLHSTMT hstmt;               // hstmt in the window title

   // reset the hstmt list box in the disconnect dialog box

   SendMessage(hWndhstmt, LB_RESETCONTENT, 0, 0);

   // go through all available MDI child windows and check if the
   // hdbc in the title matches the one selected in the list box.
   // if they match, use the hstmt in the window title to create
   // a new entry in the hstmt(s) list box.

   for (hWndChild=GetWindow(hWndMDIClient, GW_CHILD); hWndChild; hWndChild=GetWindow(hWndChild, GW_HWNDNEXT)) {
      // Class name check is necessary as some of MDI child
      // windows may be iconized by the user and MDIClient
      // in such cases create additional windows (such as
      // icon titles).

      GetClassName(hWndChild, szBuffer, MAXBUFLEN);
      if (strcmp(szBuffer, ODBCMDICLASS))
         continue;

      GetWindowText(hWndChild, szBuffer, MAXBUFLEN);
      sscanf(szBuffer, SCANHDBCHSTMT_FORMAT, &hdbc1, &hstmt);

      SendMessage(hWndhdbc, LB_GETTEXT, (WPARAM)nCrsrIndex, (LPARAM)(LPSTR)szBuffer);
      sscanf(szBuffer, SCANHDBC_FORMAT, &hdbc2);

      if (hdbc1 != hdbc2)
         continue;

      wsprintf(szBuffer, ((hWndChild == hWndActiveChild) ?  CURQUERY_STRING:    QUERY_STRING), hstmt);
      SendMessage(hWndhstmt, LB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
   }
   SendMessage(hWndhstmt, LB_SETSEL, TRUE, 0);
}

/*
    FUNCTION: NewQueryWindow()
    COMMENTS: Create a new hstmt on current hdbc and its associated window
*/

void FAR PASCAL NewQueryWindow()
{
   int              nCurrenthdbc;           // current selection in the hdbc combobox
   char             szBuffer[MAXBUFLEN+1];  // string in the hdbc combobox on the toolbar
   char             szDBName[MAXBUFLEN+1];  // DSN string
   SQLHDBC          hdbc;                   // hdbc value in the combobox
   SQLHSTMT         hstmt;                  // hstmt
   MDICREATESTRUCT  mcs;                    // MDI child window create structure
   SQLRETURN        nResult;                // Result code

   szDBName[0]='\0';
	szBuffer[0]= '\0';
	
	// check if there is hdbc selected in the combobox

	if ((nCurrenthdbc = (int)SendMessage(hWndCrsrList, CB_GETCURSEL, 0, 0)) == CB_ERR) {
      MessageBox(hWndFrame, MAKECONNECT, NOHDBCERROR, MB_OK | MB_ICONHAND);
      return;
   }

   // check if the number of windows exceeds MAXCHILDWNDS

   if (nChildCount >= MAXCHILDWNDS) {
      MessageBox(hWndFrame, MAXCHILDEXCEEDED, MAXCHLDERR, MB_OK | MB_ICONHAND);
      return;
   }

   // Scan DSN string and hdbc value from the combo-box
   SendMessage(hWndCrsrList, CB_GETLBTEXT, (WPARAM)nCurrenthdbc, (LPARAM)(LPSTR)szBuffer);
   sscanf(szBuffer, SCANDSNHDBC_FORMAT, szDBName, &hdbc);


   // Allocate a new Statement Handle on the scanned hdbc
   if ((nResult = SQLAllocHandle(SQL_HANDLE_STMT,hdbc, &hstmt)) != SQL_SUCCESS) {
      DisplayError(nResult, hWndFrame, SQL_HANDLE_DBC, hdbc);
      return;
   }

   // create a new MDI client window. maximized, if the previous is so.
   mcs.szClass = ODBCMDICLASS;
   mcs.szTitle = UNTITLED;
   mcs.hOwner  = hAppInstance;
   mcs.style   = hWndActiveChild && IsZoomed(hWndActiveChild) ? WS_MAXIMIZE : 0;
   mcs.x = mcs.cx = mcs.y = mcs.cy = CW_USEDEFAULT;
   hWndActiveChild = (HWND)(UINT)SendMessage(hWndMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);

   // check if it was created, if it wasn't free up resource and flag warning
   if (!hWndActiveChild) {
      MessageBox(hWndFrame, CREATECHILDERR, EXECERROR, MB_OK|MB_ICONEXCLAMATION|MB_TASKMODAL);
      SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
      return;
   }

   // display the DSN string, SQLHDBC and SQLHSTMT in the title of newly
   // created window. Increment the child window counter
   wsprintf(szBuffer, QUERY_STRING, hstmt);
   SendMessage(hWndStmtList, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
   SendMessage(hWndStmtList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);
   wsprintf(szBuffer, DSN_HDBC_HSTMT_FORMAT, (LPSTR)szDBName, hdbc, hstmt);
   SetWindowText(hWndActiveChild, szBuffer);
   nChildCount++;

   // update the hstmt(s) combo-box in the tool bar.
   ChangeCurrentQuery(hWndStmtList);
}

/*
    FUNCTION: ChangeCurrentCursor(HWND hWndCrsrList)
    COMMENTS: Change the displayed hdbc in the hdbc(s) combobox
          Also activate the appropriate MDI child window that
          has the same hdbc as the new hdbc in the combobox.
*/

void FAR PASCAL ChangeCurrentCursor(HWND hWndCrsrList)
{
   int      nNewhdbc;               //new hdbc position
   int      nConnects;              //# of connections
   int      nIndex;                 //counter
   char     szBuffer[MAXBUFLEN+1];  //string buffer
   BOOL     bChangedFocus;          //Activate a different MDI child?
   HWND     hWndChild;              //MDI Child window
   SQLHDBC  hdbc1;                  //hdbc in the window title
   SQLHDBC  hdbc2;                  //hdbc in the combobox
   SQLHSTMT hstmt;                  //hstmt in the window title

   // check to see if the current selection in the combo-box
   // differs from the previous selection, if it is the same then
   // simply return. Check is made by searching a marked string
   // in the hdbc(s) combobox.
   nNewhdbc = (int)SendMessage(hWndCrsrList, CB_GETCURSEL, 0, 0);
   nConnects = (int)SendMessage(hWndCrsrList, CB_GETCOUNT, 0, 0);

   for(nIndex = 0; nIndex < nConnects; nIndex++) {
      SendMessage(hWndCrsrList, CB_GETLBTEXT, nIndex, (LPARAM)(LPSTR)szBuffer);
      if (strstr(szBuffer, CUR_MARK))
         break;
   }

   if (nIndex == nNewhdbc)
      return;

   // if there was a current marked hdbc in the combobox, remove the
   // mark from the string and replace it in the combobox.
   if (nIndex != nConnects) {
      SendMessage(hWndCrsrList, CB_GETLBTEXT, nIndex, (LPARAM)(LPSTR)szBuffer);
      szBuffer[strlen(szBuffer)-2] = '\0';
      SendMessage(hWndCrsrList, CB_INSERTSTRING, nIndex, (LPARAM)(LPSTR)szBuffer);
      SendMessage(hWndCrsrList, CB_DELETESTRING, nIndex+1, 0);
   }

   // Create a new marked string with currently selected hdbc string in
   // the combobox and replace it with the original.
   SendMessage(hWndCrsrList, CB_GETLBTEXT, nNewhdbc, (LPARAM)(LPSTR)szBuffer);
   strcat(szBuffer, CUR_MARK);
   SendMessage(hWndCrsrList, CB_INSERTSTRING, nNewhdbc, (LPARAM)(LPSTR)szBuffer);
   SendMessage(hWndCrsrList, CB_DELETESTRING, nNewhdbc+1, 0);
   SendMessage(hWndCrsrList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);

   // reset the hstmt(s) combobox. Search through the MDI child windows
   // and collect all hstmt(s) from window titles that have the same
   // hdbc value as the newly selected hdbc in the hdbc(s) combo-box above.
   SendMessage(hWndStmtList, CB_RESETCONTENT, 0, 0);
   for (bChangedFocus=FALSE, hWndChild=GetWindow(hWndMDIClient, GW_CHILD);  hWndChild; hWndChild = GetWindow(
                                                                                                             hWndChild, GW_HWNDNEXT)) {
      // check class name to skip iconized titles or other
      // such non MDI Child windows
      GetClassName(hWndChild, szBuffer, MAXBUFLEN);
      if (strcmp(szBuffer, ODBCMDICLASS))
         continue;

      GetWindowText(hWndChild, szBuffer, MAXBUFLEN);
      sscanf(szBuffer, SCANHDBCHSTMT_FORMAT, &hdbc1, &hstmt);

      SendMessage(hWndCrsrList, CB_GETLBTEXT, (WPARAM)nNewhdbc, (LPARAM)(LPSTR)szBuffer);
      sscanf(szBuffer, SCANHDBC_FORMAT, &hdbc2);

      if (hdbc1 != hdbc2)
         continue;

      if (!bChangedFocus) {
         // If the first match is found, change the active window
         // and update the hstmt(s) combobox with a new entry that
         // has hstmt marked with current marker.
         bChangedFocus = TRUE;
         hWndActiveChild = hWndChild;
         SendMessage(hWndMDIClient, WM_MDIACTIVATE, (WPARAM)hWndChild, 0);
         wsprintf(szBuffer, CURQUERY_STRING, hstmt);
         SendMessage(hWndStmtList, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
         SendMessage(hWndStmtList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);
      }
      else {
         // simply add the hstmt in the hstmt(s) combobox.
         wsprintf(szBuffer, QUERY_STRING, hstmt);
         SendMessage(hWndStmtList, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
      }
   }
}

/*
    FUNCTION: ChangeCurrentQuery(HWND hWndStmtList)
    COMMENTS: Change the current selection in the hstmt(s) combobox.
          Update the current marker in the combobox and activate
          proper MDI Child window.
*/

void FAR PASCAL ChangeCurrentQuery(HWND hWndStmtList)
{
   int      nNewhstmt;              //new selection in combobox
   int      nStmts;                 //# of hstmts
   int      nIndex;                 //counter
   char     szBuffer[MAXBUFLEN+1];  //string buffer to update displays
   HWND     hWndChild;              //MDI child window handle
   SQLHDBC  hdbc1 = NULL;                  //hdbc in hdbc(s) combobox
   SQLHDBC  hdbc2 = NULL;                  //hdbc in child window title
   SQLHSTMT hstmt1 = NULL;                 //newly selected hstmt
   SQLHSTMT hstmt2 = NULL;                 //hstmt in child window title

   // find the index of new selection and total number of hstmt(s)
   nNewhstmt = (int)SendMessage(hWndStmtList, CB_GETCURSEL, 0, 0);
   nStmts = (int)SendMessage(hWndStmtList, CB_GETCOUNT, 0, 0);

   // check if the current selection is same as previous one, if
   // so simply return. Check for marker to determine previous selection
   for(nIndex = 0; nIndex < nStmts; nIndex++) {
      SendMessage(hWndStmtList, CB_GETLBTEXT, nIndex, (LPARAM)(LPSTR)szBuffer);
      if (strstr(szBuffer, CUR_MARK))
         break;
   }

   if (nIndex == nNewhstmt)
      return;

   // if a previous selection was found, remove current marker
   // and update it in the hstmt(s) combobox.
   if (nIndex != nStmts) {
      SendMessage(hWndStmtList, CB_GETLBTEXT, nIndex, (LPARAM)(LPSTR)szBuffer);
      szBuffer[strlen(szBuffer)-2] = '\0';
      SendMessage(hWndStmtList, CB_INSERTSTRING, nIndex, (LPARAM)(LPSTR)szBuffer);
      SendMessage(hWndStmtList, CB_DELETESTRING, nIndex+1, 0);
   }

   // mark the current selection and update it in the hstmt(s) combobox
   SendMessage(hWndStmtList, CB_GETLBTEXT, nNewhstmt, (LPARAM)(LPSTR)szBuffer);
   strcat(szBuffer, CUR_MARK);
   SendMessage(hWndStmtList, CB_INSERTSTRING, nNewhstmt, (LPARAM)(LPSTR)szBuffer);
   SendMessage(hWndStmtList, CB_DELETESTRING, nNewhstmt+1, 0);
   SendMessage(hWndStmtList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);

   // scan hstmt value and hdbc value from current selection in
   // hdbc(s) and hstmt(s) comboboxes.
   sscanf(szBuffer, QUERY_STRING, &hstmt1);

   SendMessage(hWndCrsrList, CB_GETLBTEXT, (UINT)SendMessage(hWndCrsrList, CB_GETCURSEL, 0, 0),
               (LPARAM)(LPSTR)szBuffer);
   sscanf(szBuffer, SCANHDBC_FORMAT, &hdbc1);
	

   // go through list of MDI Child windows and match the hstmt and hdbc
   // values. If a match if found (must be), activate the window
   for (hWndChild=GetWindow(hWndMDIClient, GW_CHILD); hWndChild; hWndChild=GetWindow(hWndChild, GW_HWNDNEXT)) {
      // ignore non MDI child windows
      GetClassName(hWndChild, szBuffer, MAXBUFLEN);
      if (strcmp(szBuffer, ODBCMDICLASS))
         continue;

      GetWindowText(hWndChild, szBuffer, MAXBUFLEN);
      sscanf(szBuffer, SCANHDBCHSTMT_FORMAT, &hdbc2, &hstmt2);

      if (hdbc1 == hdbc2 && hstmt1 == hstmt2) {
         hWndActiveChild = hWndChild;
         SendMessage(hWndMDIClient, WM_MDIACTIVATE, (WPARAM)hWndChild, 0);
         break;
      }
   }
}

/*
    FUNCTION: DisplayNewCrsrAndStmt()
    COMMENTS: If user changes currently active MDI Child Window, both
          hstmt(s) and hdbc(s) comboboxes need to be updated to
          reflect currently selected MDI child. match the hstmt and
          hdbc value in the title of MDI child to those on display
          in hstmt(s) and hdbc(s) comboboxes respectively.
*/

void FAR PASCAL DisplayNewCrsrAndStmt()
{
   int      nConnects;              // # of hdbc(s)
   int      nStmts;                 // # of hstmt(s)
   int      nOldhdbc;               // prev selection in hdbc combobox
   int      nOldhstmt;              // prev selection in hstmt combobox
   int      nIndex;                 // counter
   char     szBuffer[MAXBUFLEN+1];  // display buffer
   HWND     hWndChild;              // MDI Child window
   SQLHDBC  hdbc1;                  // hdbc in window title
   SQLHDBC  hdbc2;                  // hdbc in hdbc(s) combobox
   SQLHSTMT hstmt1;                 // hstmt in window title
   SQLHSTMT hstmt2;                 // hstmt in hstmt(s) combobox

   // scan hdbc and hstmt values from newly selected window
   GetWindowText(hWndActiveChild, szBuffer, MAXBUFLEN);
   sscanf(szBuffer, SCANHDBCHSTMT_FORMAT, &hdbc1, &hstmt1);

   // search through list of hdbc(s) in hdbc combobox and find
   // matching hdbc. remove marker from prev selection and add
   // marker to the new selection. update combobox accordingly.
   nConnects = (int)SendMessage(hWndCrsrList, CB_GETCOUNT, 0, 0);
   nOldhdbc = (int)SendMessage(hWndCrsrList, CB_GETCURSEL, 0, 0);

   for(hdbc2 = (SQLHDBC)(nIndex = 0); hdbc1 != hdbc2; nIndex++) {
      SendMessage(hWndCrsrList, CB_GETLBTEXT, nIndex, (LPARAM)(LPSTR)szBuffer);
      sscanf(szBuffer, SCANHDBC_FORMAT, &hdbc2);
   }

   if (--nIndex != nOldhdbc) // change in hdbc combobox required.
      {
         SendMessage(hWndCrsrList, CB_GETLBTEXT, nOldhdbc, (LPARAM)(LPSTR)szBuffer);
         szBuffer[strlen(szBuffer)-2] = '\0';
         SendMessage(hWndCrsrList, CB_INSERTSTRING, nOldhdbc, (LPARAM)(LPSTR)szBuffer);
         SendMessage(hWndCrsrList, CB_DELETESTRING, nOldhdbc+1, 0);

         SendMessage(hWndCrsrList, CB_GETLBTEXT, nIndex, (LPARAM)(LPSTR)szBuffer);
         strcat(szBuffer, CUR_MARK);
         SendMessage(hWndCrsrList, CB_INSERTSTRING, nIndex, (LPARAM)(LPSTR)szBuffer);
         SendMessage(hWndCrsrList, CB_DELETESTRING, nIndex+1, 0);
         SendMessage(hWndCrsrList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);

         // reset the hstmt(s) combobox, search through the list
         // of MDI child windows and find all hstmt(s) associated to
         // new hdbc. Build the new list of hstmt(s) for the hstmt
         // combobox. Mark the one hstmt that matches the currently
         // activated MDI child window.
         SendMessage(hWndStmtList, CB_RESETCONTENT, 0, 0);
         for (hWndChild=GetWindow(hWndMDIClient,GW_CHILD);hWndChild;hWndChild=GetWindow(hWndChild,GW_HWNDNEXT)) {
            GetClassName(hWndChild, szBuffer, MAXBUFLEN);
            if (strcmp(szBuffer, ODBCMDICLASS))
               continue;

            GetWindowText(hWndChild, szBuffer, MAXBUFLEN);
            sscanf(szBuffer, SCANHDBCHSTMT_FORMAT, &hdbc2, &hstmt2);

            if (hdbc1 != hdbc2)
               continue;

            if (hWndActiveChild == hWndChild) {
               wsprintf(szBuffer, CURQUERY_STRING, hstmt2);
               SendMessage(hWndStmtList, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
               SendMessage(hWndStmtList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);
            }
            else {
               wsprintf(szBuffer, QUERY_STRING, hstmt2);
               SendMessage(hWndStmtList, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
            }
         }
      }
   else // no change in hdbc combobox required
      {
         // go through the list of hstmt(s) in hstmt combobox.
         // find the one that matches the currently activated MDI
         // child window.
         nOldhstmt = (int)SendMessage(hWndStmtList, CB_GETCURSEL, 0, 0);
         nStmts = (int)SendMessage(hWndStmtList, CB_GETCOUNT, 0, 0);

         for(hstmt2 = (SQLHDBC)(nIndex = 0); hstmt1 != hstmt2; nIndex++) {
            SendMessage(hWndStmtList, CB_GETLBTEXT, nIndex, (LPARAM)(LPSTR)szBuffer);
            sscanf(szBuffer, QUERY_STRING, &hstmt2);
         }

         if (--nIndex != nOldhstmt) // new index in hstmt differs from previous selection
            {
               // remove the marker from previous selection. Add
               // it to the new string and update the combobox display
               SendMessage(hWndStmtList, CB_GETLBTEXT, nOldhstmt, (LPARAM)(LPSTR)szBuffer);
               szBuffer[strlen(szBuffer)-2] = '\0';
               SendMessage(hWndStmtList, CB_INSERTSTRING, nOldhstmt, (LPARAM)(LPSTR)szBuffer);
               SendMessage(hWndStmtList, CB_DELETESTRING, nOldhstmt+1, 0);

               SendMessage(hWndStmtList, CB_GETLBTEXT, nIndex, (LPARAM)(LPSTR)szBuffer);
               strcat(szBuffer, CUR_MARK);
               SendMessage(hWndStmtList, CB_INSERTSTRING, nIndex, (LPARAM)(LPSTR)szBuffer);
               SendMessage(hWndStmtList, CB_DELETESTRING, nIndex+1, 0);
               SendMessage(hWndStmtList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);
            }
      }
}

/*
    FUNCTION: FreeConnect(HWND hWndhdbc)
    COMMENTS: Disconnect and Free the currently selected hdbc in
          the hdbc listbox in disconnect dialog. Call SQLDisconnect
          and SQLFreeConnect to free the hdbc. Close all MDI
          child windows associated with this hdbc. That will
          automatically free associated hstmt(s).
*/

void FAR PASCAL FreeConnect(HWND hWndhdbc)
{
   int     nIndex;                 // current selection in the listbox of disconnect dlg
   int     nCurrent;               // current selection in hdbc(s) combobox
   char    szBuffer[MAXBUFLEN+1];  // display buffer
   char    szSelect[MAXBUFLEN+1];  // original selection in hdbc(s) combobox
   char    szDBName[MAXBUFLEN+1];  // DSN string
   HWND    hWndChild;              // MDI Child window
   SQLHDBC hdbc1 = NULL;                  // hdbc in the list box of disconnect dlg
   SQLHDBC hdbc2 = NULL;                  // hdbc in the MDI child window title

   szDBName[0]='\0';
	// check current selection in the list box of disconnect dialog. scan
   // hdbc value from the current selection.
   if ((nIndex = (int)SendMessage(hWndhdbc, LB_GETCURSEL, 0, 0)) == LB_ERR)
      return;

   SendMessage(hWndhdbc, LB_GETTEXT, (WPARAM)nIndex, (LPARAM)(LPSTR)szBuffer);
   sscanf(szBuffer, SCANDSNHDBC_FORMAT, szDBName, &hdbc1);
	

   // go through the list of MDI child windows and find matching hdbc(s)
   // close all children who have the same hdbc value. Closing them
   // automatically frees associated hstmts. see CloseQueryWindow.
   for(hWndChild = GetWindow(hWndMDIClient, GW_CHILD); hWndChild; ) {
      // store next window handle before destroying the currentone
      HWND hWndTemp = GetWindow(hWndChild, GW_HWNDNEXT);

      // ignore non MDI child windows
      GetClassName(hWndChild, szBuffer, MAXBUFLEN);
      if (!strcmp(szBuffer, ODBCMDICLASS)) {
         GetWindowText(hWndChild, szBuffer, MAXBUFLEN);
         sscanf(szBuffer, SCANHDBC_TITLEFORMAT, &hdbc2);
			
         if (hdbc1 == hdbc2) {
            // destroy the window and restart search
            SendMessage(hWndMDIClient, WM_MDIDESTROY, (WPARAM)hWndChild, 0);
            hWndTemp = GetWindow(hWndMDIClient, GW_CHILD);
         }
      }
      hWndChild = hWndTemp;
   }

   // call SQLDisconnect and SQLFreeConnect to disconnect and free hdbc
   SQLDisconnect(hdbc1);
   SQLFreeHandle(SQL_HANDLE_DBC,hdbc1);

   // update the hdbc(s) combobox display by removing the deleted hdbc
   // from the list and reselecting the previous selection
   wsprintf(szBuffer, DSN_HDBC_FORMAT, (LPSTR)szDBName, hdbc1);
   nCurrent = (int)SendMessage(hWndCrsrList, CB_GETCURSEL, 0, 0);
   SendMessage(hWndCrsrList, CB_GETLBTEXT, nCurrent, (LPARAM)(LPSTR)szSelect);
   nIndex = (int)SendMessage(hWndCrsrList, CB_FINDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
   SendMessage(hWndCrsrList, CB_DELETESTRING, (WPARAM)nIndex, 0);
   SendMessage(hWndCrsrList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szSelect);

   // if there is no query window open and the current selected SQLHDBC
   // was deleted, make sure to make the next available SQLHDBC as current
   if (SendMessage(hWndCrsrList, CB_GETCOUNT, 0, 0) &&
       !GetWindow(hWndMDIClient, GW_CHILD) && (nCurrent == nIndex)) {
      if ((nCurrent = (int)SendMessage(hWndCrsrList, CB_GETCURSEL, 0, 0))!=CB_ERR)
         return;
      SendMessage(hWndCrsrList, CB_GETLBTEXT, 0, (LPARAM)(LPSTR)szSelect);
      strcat(szSelect, CUR_MARK);
      SendMessage(hWndCrsrList, CB_INSERTSTRING, 0, (LPARAM)(LPSTR)szSelect);
      SendMessage(hWndCrsrList, CB_DELETESTRING, 1, 0);
      SendMessage(hWndCrsrList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szSelect);
   }
}

/*
    FUNCTION: FreeQuery(HWND hWndhstmt, HWND hWndhdbc, int nIndex)
    COMMENTS: Free a query window based upon current selection in
          hstmt list box in the disconnect dialog.
*/

void FAR PASCAL FreeQuery(HWND hWndhstmt, HWND hWndhdbc, int nIndex)
{
   char     szBuffer[MAXBUFLEN+1];  // display buffer
   HWND     hWndChild;      // MDI child window
   SQLHDBC  hdbc1;          // hdbc in the hdbc listbox of disconnect dlg
   SQLHDBC  hdbc2;          // hdbc in the MDI child window title
   SQLHSTMT hstmt1;         // hstmt in the hstmt listbox of disconnect dlg
   SQLHSTMT hstmt2;         // hstmt in the MDI child window title

   // scan the hstmt and hdbc values from the current selections in
   // respective listboxes of disconnect dialog box.
   SendMessage(hWndhstmt, LB_GETTEXT, nIndex, (LPARAM)(LPSTR)szBuffer);
   sscanf(szBuffer, QUERY_STRING, &hstmt1);
   SendMessage(hWndhdbc, LB_GETTEXT, (UINT)SendMessage(hWndhdbc, LB_GETCURSEL,  0, 0), (LPARAM)(LPSTR)szBuffer);
   sscanf(szBuffer, SCANHDBC_FORMAT, &hdbc1);

   // go through the list of MDI child windows and find matching window
   // that has same values for hdbc and hstmt. Destroy the matching window.
   // that will call CloseQueryWindow and thus free up associated hstmt.
   for(hWndChild=GetWindow(hWndMDIClient, GW_CHILD); hWndChild; hWndChild=GetWindow(hWndChild, GW_HWNDNEXT)) {
      // ignore non MDI child windows
      GetClassName(hWndChild, szBuffer, MAXBUFLEN);
      if (strcmp(szBuffer, ODBCMDICLASS))
         continue;
      GetWindowText(hWndChild, szBuffer, MAXBUFLEN);
      sscanf(szBuffer, SCANHDBCHSTMT_FORMAT, &hdbc2, &hstmt2);
      if (hdbc1 == hdbc2 && hstmt1 == hstmt2)
         break;
   }
   SendMessage(hWndMDIClient, WM_MDIDESTROY, (WPARAM)hWndChild, 0);
}

/*
    FUNCTION: CloseQueryWindow(HWND hWnd)
    COMMENTS: Close a Query window. Call SQLFreeHandle to free
          associated hstmt.
*/

void FAR PASCAL CloseQueryWindow(HWND hWnd)
{
   char szBuffer[MAXBUFLEN+1];  // display buffer
   char szSelect[MAXBUFLEN+1];  // current selection in hstmt(s) combobox
   SQLHSTMT hstmt;              // hstmt value in window title

   // scan the hstmt value from the window title
   GetWindowText(hWnd, szBuffer, MAXBUFLEN);
   sscanf(szBuffer, SCANHSTMT_TITLEFORMAT, &hstmt);

   // Drop the current Statement Handle
   SQLFreeHandle(SQL_HANDLE_STMT,hstmt);

   // find the matching hstmt in the hstmt(s) combobox and remove it
   // from the list. Closure of a MDI child window will cause MDIClient
   // to automatically activate a different child window if available.
   // that will automatically refresh the hstmt and hdbc displays. See
   // DisplayNewCrsrAndStmt function.
   wsprintf(szBuffer, QUERY_STRING, hstmt);
   SendMessage(hWndStmtList, CB_GETLBTEXT, (WPARAM)SendMessage(hWndStmtList, CB_GETCURSEL, 0, 0), (LPARAM)(LPSTR)szSelect);
   SendMessage(hWndStmtList, CB_DELETESTRING, (WPARAM)SendMessage(hWndStmtList, CB_FINDSTRING, 0,
                                                                  (LPARAM)(LPSTR)szBuffer), 0);
   SendMessage(hWndStmtList, CB_SELECTSTRING, (WPARAM)-1, (LPARAM)(LPSTR)szSelect);

   // decrement the child window counter.
   nChildCount--;
}

/*
    FUNCTION: ExecuteQuery()
    COMMENTS: Execute the user typed SQL Statements in the currently
          active MDI child window. If successful, then prepare
          the list of results and display it in the child listbox.
          Display errors in the ODBC function(s) failed.
*/

void FAR PASCAL ExecuteQuery()
{
   char      szBuffer[MAXBUFLEN+1];      // display buffer
   HWND      hList;                      // result listbox handle
   SQLHDBC   hdbc;                       // hdbc
   SQLHSTMT  hstmt;                      // hstmt
   SWORD     nCols = 0;                  // # of result columns
   SWORD     nCount;                     // index
   SWORD     swColType;                  // column data type
   SWORD     swColScale;                 // column scale
   SWORD     swColNull;                  // nullable column ?
   SWORD     swColLength = MAXDATALEN;   // column data length
   DWORD     dwText;                     // tab stop for listbox
   UDWORD    udwColDef;                  // precision on the column
   SQLRETURN nReturn;                    // return code
   HCURSOR   hOldCursor;                 // default cursor handle
   int       nRows;                      // # of result rows

   // check if there is an active window available
   if (!hWndActiveChild) {
      MessageBox(hWndFrame, ((SendMessage(hWndCrsrList, CB_GETCOUNT, 0, 0) <=0) ?
                             MAKECONNECT : OPENWINDOW ), NOHSTMTERROR, MB_OK | MB_ICONHAND);
      return;
   }

   // change cursor shape to hour glass
   hOldCursor = SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));

   // initialize column data and column data length arrays
   for (nCount = 0; nCount < MAX_COL; nCount++) {
      dwDataLen[nCount] = 0;
      rgbData[nCount][0] = '\0';
   }

   // scan hdbc, hstmt values
   GetWindowText(hWndActiveChild, szBuffer, MAXBUFLEN);
   sscanf(szBuffer, SCANHDBCHSTMT_FORMAT, &hdbc, &hstmt);

   // get the user typed SQL
   GetWindowText(GetDlgItem((HWND)GetWindowLong(hWndActiveChild, GWLAPP_HDLG), IDTEXT_SQL), szBuffer, MAXBUFLEN);

   // execute SQL and process errors if any
   // call SQLExecDirect to execute the SQL statement
   nReturn = SQLExecDirect(hstmt, szBuffer, SQL_NTS);
   if (nReturn != SQL_SUCCESS) {
      DisplayError(nReturn, hWndActiveChild, SQL_HANDLE_STMT, hstmt);

      // if the return value was just information, carry on
      if (nReturn != SQL_SUCCESS_WITH_INFO) {
         // Close the open result set.
         SQLCloseCursor(hstmt);
         SetCursor(hOldCursor);
         return;
      }
   }

   // call SQLNumResultCols to calculate the number of columns in
   // the result set, if more than the MAX_COL (the array boundary)
   // limit the number to MAX_COL and display truncation warning.
   // if it is 0, the statement probably was a non-SELECT simply return
   nReturn = SQLNumResultCols(hstmt, &nCols);
   if (nCols >= MAX_COL) {
      nCols = MAX_COL;
      wsprintf(szDispBuffer, COLTRUNC_WARNG, MAX_COL);
      MessageBox(hWndFrame, szDispBuffer, TRUNCERR, MB_OK | MB_ICONINFORMATION);
   }
   else if (nCols == 0) {
      // Close the open result set.
      SQLCloseCursor(hstmt);
      SetCursor(hOldCursor);
      return;
   }

   // call SQLBindCol to bind column data array and column data length
   // array to the result set
   for(nCount=0; nCount<nCols; nCount++)
      SQLBindCol(hstmt, (UWORD)(nCount+1), SQL_C_CHAR, rgbData[nCount], MAXDATALEN, &dwDataLen[nCount]);

   // reset the display in the list box. Set tabstops to display
   // multiple columns in the list box separated by tabs.
   hList = GetDlgItem((HWND)GetWindowLong(hWndActiveChild, GWLAPP_HDLG), IDLIST_RSLT);

   SendMessage(hList, LB_RESETCONTENT, 0, 0);
   SendMessage(hList, WM_SETREDRAW, FALSE, 0);
   dwText = LISTTABSTOP;
   SendMessage(hList, LB_SETTABSTOPS, (WPARAM)1, (LPARAM)(LPINT)&dwText);

   // call SQLDescribeCol to get description of each column in the
   // result set. Store the column name in the display buffer and
   // make it the first entry in the results list box of the MDI
   // child window.
   for(nCount=1, szDispBuffer[0]='\0'; nCount <= nCols; nCount++) {
      SQLDescribeCol(hstmt, nCount, szBuffer, MAXDATALEN, &swColLength, &swColType, &udwColDef,
                     &swColScale, &swColNull);
      strcat(szDispBuffer, szBuffer);
      dwText = strlen(szDispBuffer);
      szDispBuffer[dwText++] = '\t';
      szDispBuffer[dwText] = '\0';
   }
   if (*szDispBuffer)
      szDispBuffer[strlen(szDispBuffer)-1]='\0';
   SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)(LPSTR)szDispBuffer);

   // call SQLFetch to fetch each row of the result set. Extract data
   // value and store it in the display buffer, separated by tabs.
   // continue until SQLFetch fails.
   for(nRows = 0; (nReturn = SQLFetch(hstmt))==SQL_SUCCESS || nReturn==SQL_SUCCESS_WITH_INFO;) {
      if (nReturn != SQL_SUCCESS)
         DisplayError(nReturn, hWndActiveChild, SQL_HANDLE_STMT, hstmt);
      for(nCount=0, szDispBuffer[0]='\0'; nCount<nCols; nCount++) {
         // check if the column is a null value?
         strcat(szDispBuffer, (dwDataLen[nCount]==SQL_NULL_DATA)?NULLDATASTRING:rgbData[nCount]);
         dwText = strlen(szDispBuffer);
         szDispBuffer[dwText++] = '\t';
         szDispBuffer[dwText] = '\0';
      }
      if (*szDispBuffer)
         szDispBuffer[strlen(szDispBuffer)-1]='\0';
      else
         break;
      SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)(LPSTR)szDispBuffer);
      if (++nRows == MAX_ROW) {
         wsprintf(szDispBuffer, ROWTRUNC_WARNG, MAX_ROW);
         MessageBox(hWndFrame, szDispBuffer, TRUNCERR, MB_OK | MB_ICONINFORMATION);
         break;
      }
   }

   // set the horizontal scroll extent in the list box and ask for repaint.
   SendMessage(hList, LB_SETHORIZONTALEXTENT, (WPARAM)(nCols*LISTHORZSCROLL+LISTHORZEXT), 0);
   SendMessage(hList, WM_SETREDRAW, TRUE, 0);

   // if there was any error returned by SQLFetch, display it
   if (nReturn == SQL_ERROR)
      DisplayError(nReturn, hWndActiveChild, SQL_HANDLE_STMT, hstmt);

   // Close the open result set.
   // Unbind all bound columns.
   SQLCloseCursor(hstmt);
   SQLFreeStmt(hstmt, SQL_UNBIND);

   // restore the cursor to default value
   SetCursor(hOldCursor);
}

/*
    FUNCTION: CloseDatabases()
    COMMENTS: Go through all open connections (hdbcs) and hstmt(s)
          and close them one by one.
*/

BOOL FAR PASCAL CloseDatabases()
{
   int     nIndex;                 // index
   int     nCount;                 // # of connected hdbc(s)
   char    szBuffer[MAXBUFLEN+1];  // display string buffer
   HWND    hWndChild;              // MDI Child Window
   SQLHDBC hdbc1;                  // hdbc value in the hdbc(s) combobox
   SQLHDBC hdbc2;                  // hdbc value in the MDI Child window title

   // get count of connected hdbc(s) from the hdbc(s) combobox on the toolbar
   if (!(nCount = (int)SendMessage(hWndCrsrList, CB_GETCOUNT, 0, 0)))
      return (TRUE);

   // go through all available MDI child windows and for each hdbc,
   // find the matching MDI child window and ask it for closure, thereby
   // freeing the associated hstmt (see CloseQueryWindow). Once all
   // associated hstmt(s) are freed, free the hdbc
   for (nIndex = 0; nIndex < nCount; nIndex++) {
      // scan current indexed hdbc from hdbc(s) combobox
      SendMessage(hWndCrsrList, CB_GETLBTEXT, (WPARAM)nIndex, (LPARAM)(LPSTR)szBuffer);
      sscanf(szBuffer, SCANHDBC_FORMAT, &hdbc1);

      // search through the list of MDI Child Windows
      for(hWndChild = GetWindow(hWndMDIClient, GW_CHILD); hWndChild; ) {
         // store the next child, before destroying the current
         HWND hWndTemp = GetWindow(hWndChild, GW_HWNDNEXT);

         // ignore non MDI child windows
         GetClassName(hWndChild, szBuffer, MAXBUFLEN);
         if (!strcmp(szBuffer, ODBCMDICLASS)) {
            GetWindowText(hWndChild, szBuffer, MAXBUFLEN);
            sscanf(szBuffer, SCANHDBC_TITLEFORMAT, &hdbc2);
            if (hdbc1 == hdbc2) {
               // destroy the window and restart search
               SendMessage(hWndMDIClient, WM_MDIDESTROY, (WPARAM)hWndChild, 0);
               hWndTemp = GetWindow(hWndMDIClient, GW_CHILD);
            }
         }
         hWndChild = hWndTemp;
      }

      // call SQLDisconnect and SQLFreeConnect to disconnect and
      // free the curren hdbc resource
      SQLDisconnect(hdbc1);
      SQLFreeHandle(SQL_HANDLE_DBC,hdbc1);
   }

   // reset the hdbc(s) combobox display and display all connections
   // closed message. return success to let application exit.
   SendMessage(hWndCrsrList, CB_RESETCONTENT, 0, 0);
   MessageBox(hWndFrame, CLOSEALLHDBC, LOGOUTINFO,  MB_OK | MB_ICONINFORMATION);
   return (TRUE);
}

/*
    FUNCTION: FreeSQLEnvironment()
    COMMENTS: Free the ODBC environment.
*/

BOOL FAR PASCAL FreeSQLEnvironment()
{
   // Free up all ODBC related resources
   return (SQLFreeHandle(SQL_HANDLE_ENV,henv) == SQL_SUCCESS);
}

/*
    FUNCTION: DisplayError(SQLRETURN nResult, HWND hWnd, SWORD fHandleType, SQLHANDLE handle)
    COMMENTS: Format and display errors or warnings.
*/

void FAR PASCAL DisplayError(SQLRETURN nResult, HWND hWnd, SWORD fHandleType, SQLHANDLE handle)
{
   UCHAR    szErrState[SQL_SQLSTATE_SIZE+1];    // SQL Error State string
   UCHAR    szErrText[SQL_MAX_MESSAGE_LENGTH+1];    // SQL Error Text string
   char szBuffer[SQL_SQLSTATE_SIZE+SQL_MAX_MESSAGE_LENGTH+MAXBUFLEN+1];
   // formatted Error text Buffer
   SWORD    wErrMsgLen;             // Error message length
   UDWORD   dwErrCode;              // Native Error code
   int  iSize;                      // Display Error Text size
   SQLRETURN  nErrResult;             // Return Code from SQLGetDiagRec
   SWORD sMsgNum = 1;
   SWORD fFirstRun = TRUE;

   szBuffer[0] = '\0';

   do
      {
         // continue to bring messageboxes till all errors are displayed.
         // more than one message box may be reqd. as err text has fixed
         // string size.

         // initialize display buffer with the string in error text buffer
         strcpy(szDispBuffer, szBuffer);

         // call SQLGetDiagRec function with proper ODBC handles, repeatedly until
         // function returns SQL_NO_DATA. Concatenate all error strings
         // in the display buffer and display all results.
         while ((nErrResult = SQLGetDiagRec(fHandleType, handle, sMsgNum++,
                                            szErrState, &dwErrCode, szErrText,
                                            SQL_MAX_MESSAGE_LENGTH-1, &wErrMsgLen))
                != SQL_NO_DATA) {

				
				if(nErrResult == SQL_ERROR || nErrResult == SQL_INVALID_HANDLE)
					break;

            wsprintf(szBuffer, SQLERR_FORMAT, (LPSTR)szErrState, dwErrCode, (LPSTR)szErrText);
            iSize = strlen(szDispBuffer);
            if (iSize && (iSize+strlen(szBuffer)+1) >= MAXDISPLAYSIZE)
               break;
            if (iSize)
               strcat(szDispBuffer, "\n");
            strcat(szDispBuffer, szBuffer);
         }

         // display proper ERROR or WARNING message with proper title
			
         if (nResult == SQL_SUCCESS_WITH_INFO)
            MessageBox(hWnd, szDispBuffer, (fFirstRun? SQLWRNMSGTITLE : SQLWRNCNTDTITLE),
                       MB_OK | MB_ICONINFORMATION);
         else
            MessageBox(hWnd, szDispBuffer, (fFirstRun? SQLERRMSGTITLE : SQLERRCNTDTITLE),
                       MB_OK | MB_ICONEXCLAMATION);

         if (fFirstRun)
            fFirstRun = FALSE;
      }
   while (!(nErrResult == SQL_NO_DATA || nErrResult == SQL_ERROR || nErrResult == SQL_INVALID_HANDLE));
}
/********************************************* END OF FILE **************************************************/
