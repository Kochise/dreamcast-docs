//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   EXECUTE.C
//|      This file contains the actual code to execute SQL Statements and
//|         display them.  This file is dependent on the SA Tool data structures
//|         and the independent module RESULTS.
//*---------------------------------------------------------------------------------
#include "admndemo.h"
#include "execute.h"
#include "strings.h"

VSZFile;

#define MAXRECORDS 1000



//*---------------------------------------------------------------------------------
//|   Global variables
//*---------------------------------------------------------------------------------
lpRESULTSINFO           lpActiveResults=NULL;         // Tracks the active results window
extern lpCHILDINFO      lpActiveConn;
extern HWND             hwndCurMDIChild;
extern HINSTANCE        hInst;
extern HWND             hwndFrame;

extern char OutStr[MAXBUFF];
extern char szDirName[_MAX_PATH];
extern char szDftFileFilter[MAXBUFF];

dCSEG(char) szNullString[]                =  "<null>";
dCSEG(char) szDash[]                      =  " - ";
dCSEG(char) szResults[]                   =  "Results ";
dCSEG(char) szErrorVal[]                  =  "#Error";
dCSEG(char) sz1000[]                      =  "1000";
dCSEG(char) szDlgTitle[]                  =  "Execute File";


typedef struct tagEXECUTEFILE {
   BOOL        fExecute;                  // TRUE if ok to proceede
   HINSTANCE   hInst;                     // Instance handle
   LPSTR       szFile;                    // File name to execute
   char        szCharacter[4];            // Character to stop on
   int         cbMaxLength;               // Maximum buffer size
   } EXECUTEFILE;


//*---------------------------------------------------------------------------------
//|   Local function prototypes
//*---------------------------------------------------------------------------------
BOOL INTFUN FindTerminator(LPSTR str, LPSTR term, LPSTR * nxtstr);
BOOL INTFUN NotInQuote(LPSTR str, LPSTR tar);
BOOL INTFUN ValidSQLStmt(LPSTR str);
BOOL EXTFUN ExecuteFileWndProc(HWND hDlg, unsigned msg, WPARAM wParam, LPARAM lParam);
void INTFUN InternalDestroyResultsWindow(CHILDINFO FAR * ci, RESULTSSET FAR * rs);
void INTFUN DestroyResultsWindow(CHILDINFO FAR * ci, lpRESULTSINFO lpri);


//*---------------------------------------------------------------------------------
//| ExecuteFile:
//|   This function will open a file and execute each SQL statement in it.
//| Parms:
//|   ci                   CHILDINFO information
//|   hwnd                 Owner window for prompting
//|   szExeFile            If not NULL, then the name of a file to execute, in
//|                           which case the following *are* used
//|   szTerm               Terminator for statement
//|   cbStmt               Max statement size
//| Returns:
//|   Nothing.
//*---------------------------------------------------------------------------------
void ExecuteFile(CHILDINFO FAR * ci, HWND hwnd, LPSTR szExeFile,
      LPSTR szTerm, int cbStmt)
{
   char              szFile[MAXBUFF];
   int               cbRead, cbNextRead;
   HFILE             hf;
   LPSTR             szBuff;
   EXECUTEFILE       ef;
   HWND              fHwnd=GetFocus();


   //
   // Display dialog to get execute parameters
   //
   memset(szFile, 0, MAXBUFF);
   ef.hInst = ci->hInst;
   ef.szFile = szFile;

   // If the caller doesn't supply a file, then ask them for it
   if(!szExeFile) {
      if(-1 == DialogBoxParam(ci->hInst,
                              MAKEINTRESOURCE(IDD_EXECUTE_FILE),
                              hwnd,
                              (DLGPROC) ExecuteFileWndProc, (LPARAM)(EXECUTEFILE FAR *)&ef))
         MessageBox(NULL, "Could not open dialog box.",
                    "Execute File", MB_ICONEXCLAMATION);

      if(fHwnd)
         SetFocus(fHwnd);

      if(!ef.fExecute)
         return;
   }
   // If they do, then grab the options
   else {
      lstrcpy(ef.szFile, szExeFile);
      lstrcpy(ef.szCharacter, szTerm);
      ef.cbMaxLength = cbStmt;
   }

   // Now execute the file
   szBuff = (LPSTR)GetMemory(ef.cbMaxLength);
   if(!szBuff)
      return;

   if((hf = _lopen(ef.szFile, OF_READ)) != HFILE_ERROR) {
      LPSTR nxtstr, nxtread;
      szWrite(ci->hwndOut,
              GetidsString(idsExecutingFile, OutStr, MAXBUFF),
              (LPSTR)ef.szFile);
      nxtread = szBuff;
      cbNextRead = ef.cbMaxLength;
      while((cbRead = _lread(hf, nxtread, cbNextRead)) ||
            *szBuff) {
         if(FindTerminator(szBuff, ef.szCharacter, &nxtstr)) {
            if(ValidSQLStmt(szBuff))
               ExecuteCmds(ci, szBuff);
         }
         else {
            szWrite(ci->hwndOut, GetidsString(idsTerminatorNotFound, OutStr, MAXBUFF));
            goto exit01;
         }
         cbNextRead = ef.cbMaxLength;
         if(nxtstr) {
            lstrcpy(szBuff, nxtstr);
            cbNextRead -= lstrlen(szBuff);
            nxtread = szBuff + lstrlen(szBuff) + 1;
         }
      }
   }
   else {      // Couldn't open file
      szMessageBox(GetActiveWindow(),
                   MB_ICONEXCLAMATION,
                   (LPSTR) szOPENFILE,
                   GetidsString(idsOpenFileFailed, szBuff, ef.cbMaxLength),
                   (LPSTR)ef.szFile);
   }

  exit01:
   _lclose(hf);

   ReleaseMemory(szBuff);
}


//*------------------------------------------------------------------------
//| FindTerminator:
//|   Looks for a statement terminator, clears out carriage returns,
//|   and finds the next statement.
//| Parms:
//|   str      Starting location to look
//|   term     The terminator string
//|   nxtstr   The next string if there is one, NULL otherwise
//| Returns:
//|   TRUE if a valid statement was found, FALSE on error
//*------------------------------------------------------------------------
BOOL INTFUN FindTerminator(LPSTR str, LPSTR term, LPSTR * nxtstr)
{
   LPSTR    cstr=str;
   int      len;
   LPSTR    next=*nxtstr;

   next = str;
   while(next) {
      if(!(next = strstr(cstr, term))) {
         *nxtstr = NULL;
         return FALSE;
      }
      if(NotInQuote(cstr, next)) {
         len = lstrlen(term);
         while(len--)
            *next++ = '\0';
         *nxtstr = next;
         return TRUE;
      }
   }

   return FALSE;
}


//*------------------------------------------------------------------------
//| NotInQuote:
//|   Given a starting position and a target, this function determines
//|   if the target is within a quoted string.  If so, then both
//|   pointers are advaned one character after the closing quote.
//| Parms:
//|   str      Starting location to look
//|   tar      Target location
//| Returns:
//|   TRUE if the value is not in a quote, FALSE if it is
//*------------------------------------------------------------------------
BOOL INTFUN NotInQuote(LPSTR str, LPSTR tar)
{
   static char    apost = '\'';
   LPSTR          instr;
   LPSTR          tstr=str;


   while((instr = strchr(tstr, apost))) {
      if(instr < tar) {
         instr = strchr(instr+1, apost);
         if(instr > tar) {
            str = tar = instr + 1;
            return FALSE;        // Target in quoted string
         }
         else
            tstr = instr + 1;
      }
      else
         return TRUE;         // Target not between quotes
   }

   return TRUE;
}


//*------------------------------------------------------------------------
//| ValidSQLStmt:
//|   Takes a buffer and makes sure it is valid.  Essentially it removes
//|   all non-embedded carriage returns and looks for a statement which
//|   has nothing but blanks.
//| Parms:
//|   str      The string to parse
//| Returns:
//|   TRUE if the statement is valid, FALSE otherwise
//*------------------------------------------------------------------------
BOOL INTFUN ValidSQLStmt(LPSTR str)
{
   LPSTR tmpstr=str;

   RemoveCrLf(str);
   while(*tmpstr)
      if(*tmpstr++ != ' ')
         return TRUE;
   return FALSE;
}


//*------------------------------------------------------------------------
//| ExecuteFileWndProc:
//|   This window procedure is for executing a file.
//| Parms:
//|   in       Standard window parms
//| Returns:
//|   Depends on message
//*------------------------------------------------------------------------
BOOL EXTFUN ExecuteFileWndProc(HWND hDlg, unsigned msg, WPARAM wParam, LPARAM lParam)
{
   static EXECUTEFILE FAR *      ef;

   switch(msg) {
     case WM_INITDIALOG:
      {
         ef = (EXECUTEFILE FAR *)lParam;
         ef->fExecute = FALSE;                           // Assume we close
         CenterDialog(hDlg);
         if(!*szDirName)
            GetWindowsDirectory(szDirName, MAXBUFF);
         SendMessage(GetDlgItem(hDlg, IDE_CHARACTER), EM_LIMITTEXT, 3, 0L);
         SendMessage(GetDlgItem(hDlg, IDE_MAXLENGTH), EM_LIMITTEXT, 4, 0L);
         CheckRadioButton(hDlg, IDR_CARRIAGE,
                          IDR_CHARACTER, IDR_CARRIAGE);
         EnableWindow(GetDlgItem(hDlg, IDE_CHARACTER), FALSE);
         SetWindowText(GetDlgItem(hDlg, IDT_FILE), szDirName);
         SetWindowText(GetDlgItem(hDlg, IDE_MAXLENGTH), (LPSTR)sz1000);
      }
      return TRUE;


     case WM_COMMAND:
      switch(GET_WM_COMMAND_ID(wParam, lParam)) {
         // Handle radio buttons
        case IDR_CARRIAGE:
         EnableWindow(GetDlgItem(hDlg, IDE_CHARACTER), FALSE);
         return TRUE;

        case IDR_CHARACTER:
         EnableWindow(GetDlgItem(hDlg, IDE_CHARACTER), TRUE);
         SetFocus(GetDlgItem(hDlg, IDE_CHARACTER));
         return TRUE;

         // Get file to execute, use last directory name
        case IDB_FILE:
         {
            OPENFILENAME   lpofn;
            char           szFileTitle[MAXBUFF];

            _fmemset(&lpofn, 0, sizeof(OPENFILENAME));
            lpofn.hInstance = ef->hInst;
            lpofn.lStructSize = sizeof(OPENFILENAME);
            lpofn.hwndOwner = hDlg;
            lpofn.lpstrFilter = (LPSTR)szDftFileFilter;
            lpofn.nFilterIndex = 1;
            lpofn.lpstrFile = ef->szFile;
            lpofn.nMaxFile = MAXBUFF;
            lpofn.lpstrFileTitle = szFileTitle;
            lpofn.nMaxFileTitle = sizeof(szFileTitle);
            lpofn.lpstrInitialDir = szDirName;
            lpofn.Flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
            if(GetOpenFileName(&lpofn)) {
               lstrcpy(ef->szFile, lpofn.lpstrFile);
               SetWindowText(GetDlgItem(hDlg, IDT_FILE), ef->szFile);
               GetNewDirectory(szDirName, lpofn.lpstrFile);
            }
         }
         return TRUE;

         // User has clicked OK
        case IDOK:
         {
            char  szNum[5];
            GetText(GetDlgItem(hDlg, IDE_MAXLENGTH), szNum);
            ef->cbMaxLength = atoi(szNum);
            if(ef->cbMaxLength < MINSTMTSIZE) {
               MessageBox(hDlg, GetidsString(idsNumTooSmall, OutStr, MAXBUFF),
                          szDlgTitle, MB_OK);
               SetFocus(GetDlgItem(hDlg, IDE_MAXLENGTH));
               return TRUE;
            }
            GetText(GetDlgItem(hDlg, IDT_FILE), ef->szFile);
            if(IsRadioButtonOn(GetDlgItem(hDlg, IDR_CARRIAGE)))
               lstrcpy((LPSTR)ef->szCharacter, (LPSTR)"\r\n");
            else
               GetText(GetDlgItem(hDlg, IDE_CHARACTER), (LPSTR)ef->szCharacter);
            if(*ef->szCharacter == ' ' ||
               !*ef->szCharacter) {
               MessageBox(GetActiveWindow(),
                          GetidsString(idsInvalidTerminator, OutStr, MAXBUFF),
                          szErrTitle, MB_OK);
               SetFocus(GetDlgItem(hDlg, IDE_CHARACTER));
               return TRUE;
            }
            ef->fExecute = TRUE;
            EndDialog(hDlg, IDOK);
         }
         return TRUE;

        case IDCANCEL:
         ef->fExecute = FALSE;
         EndDialog(hDlg, IDCANCEL);
         return TRUE;
      }
      return TRUE;

     default:
      return FALSE;
   }
   return FALSE;
}


//*---------------------------------------------------------------------------------
//| DoCommitRollback:
//|   This function will use SQLTransact to do either a commit or a rollback
//|   on the current HDBC.
//| Parms:
//|   in       ci                   CHILDINFO information
//|   in       type                 Which action identified by menu item
//| Returns:
//|   Nothing.
//*---------------------------------------------------------------------------------
void DoCommitRollback(CHILDINFO FAR * ci, int type)
{
   RETCODE retcode;

   //-------------------------------------------------------------------------------
   // This tool has only one HSTMT per HDBC, and therefore we need only specify
   // the HDBC we want to COMMIT.  Note that some drivers may allow the user to
   // Execute a COMMIT or ROLLBACK and thereby would not even require a call to
   // this function.
   //-------------------------------------------------------------------------------
   switch(type) {
     case IDM_COMMIT:
      retcode = SQLEndTran(SQL_HANDLE_DBC, ci->hdbc, SQL_COMMIT);
      break;

     case IDM_ROLLBACK:
      retcode = SQLEndTran(SQL_HANDLE_DBC, ci->hdbc, SQL_ROLLBACK);
      break;
   }

   if(retcode != SQL_SUCCESS)
      PrintErrors(ci, SQL_HANDLE_DBC);
   else
      szWrite(ci->hwndOut, GetidsString(idsStmtProcessed, OutStr, MAXBUFF));
}


//*---------------------------------------------------------------------------------
//| ExecuteCmds:
//|   This function will take a command from the given input window and execute
//|      it.  The order of execution is to use the selcted text, and if none
//|      is selected, to use the entire text from the input window.
//| Parms:
//|   ci             CHILDINFO information
//|   stmt           A null-terminated statement to execute, NULL
//|                                    if the value should be taken from input window.
//| Returns:
//|   Nothing.
//*---------------------------------------------------------------------------------
void ExecuteCmds(CHILDINFO FAR * ci, LPSTR stmt)
{
   RETCODE              retcode;
   LPSTR                sqlstmt, tmpstr;
   DWORD                size;
   DWORD                len;


   // The user may pass in their own SQL statement to be executed.  In
   // this case simply do so.
   Busy(TRUE);
   if(stmt)
      sqlstmt = stmt;
   // If stmt is NULL, however, we must get the statement from the input
   // window of the current connection window.
   else {
      len = SendMessage(ci->hwndIn, WM_GETTEXTLENGTH, 0, 0L);
      sqlstmt = (LPSTR)GetMemory(len+1);
      if(!sqlstmt) {
         Busy(FALSE);
         return;
      }
      SendMessage(ci->hwndIn, WM_GETTEXT, (WPARAM)len + 1, (LPARAM)sqlstmt);
      size = SendMessage(ci->hwndIn, EM_GETSEL, 0, 0L);
      if(HIWORD(size) - LOWORD(size) > 0) {        // A selection has been made
         len = HIWORD(size) - LOWORD(size);
         memmove(sqlstmt, &sqlstmt[LOWORD(size)],
                 HIWORD(size) - LOWORD(size));
         tmpstr = sqlstmt + len;
         *tmpstr = '\0';
      }
      RemoveCrLf(sqlstmt);
   }

   // Execute the statement
   SQLFreeStmt(ci->hstmt, SQL_CLOSE);
   retcode = SQLExecDirect(ci->hstmt, sqlstmt, SQL_NTS);
   if(retcode != SQL_SUCCESS) {
      PrintErrors(ci, SQL_HANDLE_STMT);
      Busy(FALSE);
      goto exit00;
   }

   // Check for results
   CheckForResults(ci);

  exit00:
   SQLFreeStmt(ci->hstmt, SQL_CLOSE);
   if(!stmt)
      ReleaseMemory(sqlstmt);
   Busy(FALSE);
}


//*---------------------------------------------------------------------------------
//| CheckForResults:
//|   Call this function after successful execution of an SQL statement.  This
//|   function will attempt to fetch the results from the statement, if they
//|   exist.  It is not an error if they do not.
//| Parms:
//|   ci             CHILDINFO information
//| Returns:
//|   Nothing.
//*---------------------------------------------------------------------------------
void CheckForResults(CHILDINFO FAR * ci)
{
   RESULTSSET FAR *     rs;
   SWORD                cbCols;
   SDWORD               cbRowCount;
   char                 szStr[MAXBUFF];
   char                 tmpbuff[30];
   RETCODE              retcode;

   //
   // At this point we have executed the statement successfully.  If there is
   // a results set, fetch it to a results window.  Otherwise simply tell the
   // user how many rows were affected, if possible.
   //
   retcode = SQLFetch(ci->hstmt);
   if(retcode == SQL_ERROR) {
      cbRowCount = PrintAffectedRows(ci->hstmt, ci->hwndOut);
      SQLFreeStmt(ci->hstmt, SQL_CLOSE);
      return;
   }
   else if (retcode == SQL_NO_DATA) {
      szWrite(ci->hwndOut, GetidsString(idsNoDataFound, szStr, sizeof(szStr)));
      return;
   }

   //
   // If we made it this far, then we have a results set to work with.  The
   //    following loop will go through each results set (if there are more
   //    than one) and place their contents in a results window.
   //
   while(RC_SUCCESSFUL(retcode)) {
      lstrcpy((LPSTR)szStr, (LPSTR)ci->szClientTitle);
      lstrcat((LPSTR)szStr, (LPSTR)szDash);
      lstrcat((LPSTR)szStr, (LPSTR)szResults);
      wsprintf(tmpbuff, "%u", ++ci->cbResultCount);
      lstrcat((LPSTR)szStr, (LPSTR)tmpbuff);

      if(!(cbCols = GetNumResultsCols(ci->hstmt)))
         return;

      rs = GetConnectWindowResultsNode(ci);
      if(!CreateResultsSet(rs, ci->hwndClient, ci->hInst, cbCols, (LPSTR)szStr))
         return;

      //
      // Set the meta data
      //
      SetMetaDataFromSql(ci->hwndOut, ci->hstmt, rs, cbCols);

      //
      // Now create the MDI child window which will hold the results.
      //
      if(!CreateResultsWindow(ci, rs))
         return;


      //
      // Loop through each data source and add it to the results set.
      //
      cbRowCount = FetchAllRecordsToResults(ci->hwndOut, ci->hstmt, rs, cbCols, FALSE);
      szWrite(ci->hwndOut,
              GetidsString(idsAffectedRows, szStr, sizeof(szStr)),
              cbRowCount);

      //
      // Now see if there are any more results to fetch.
      //
      retcode = SQLMoreResults(ci->hstmt);
      if(RC_SUCCESSFUL(retcode))
         retcode = SQLFetch(ci->hstmt);
   }     // End of loop through results sets

   SQLFreeStmt(ci->hstmt, SQL_CLOSE);

   return;
}



//*---------------------------------------------------------------------------------
//| FreeConnectWindowResults:
//|   This function will free all present results sets (if there are any) and then
//|      free up the memory they occupied.
//| Parms:
//|   in       ci                   Pointer to connection window
//| Returns:
//|   Nothing.
//*---------------------------------------------------------------------------------
void FreeConnectWindowResults(lpCHILDINFO lpci)
{
   while(lpci->lprihead)
      DestroyResultsWindow(lpci,
                           (lpRESULTSINFO)lpci->lprihead);

   return;
}



//*---------------------------------------------------------------------------------
//| GetConnectWindowResultsNode:
//|   This function will return a results set pointer which describes only
//|   the graphical portion of a results set.
//| Parms:
//|   lpci                    Pointer to connection window
//| Returns:
//|   Pointer to Results set
//*---------------------------------------------------------------------------------
lpRESULTSSET GetConnectWindowResultsNode(lpCHILDINFO lpci)
{
   lpRESULTSSET lprs;

   lprs = (lpRESULTSSET)GetMemory(sizeof(RESULTSSET));
   return lprs;
}


//*---------------------------------------------------------------------------------
//| AddResultsInfoNode:
//|   Associate a child MDI window structure with a results set.
//| Parms:
//|   lpci                    Pointer to connection window
//|   lprs                    The results set to put into a window
//| Returns:
//|   Pointer to Results set
//*---------------------------------------------------------------------------------
lpRESULTSINFO AddResultsInfoNode(lpCHILDINFO lpci, lpRESULTSSET lprs)
{
   lpRESULTSINFO     lpri;
   lpRESULTSINFO     head=(lpRESULTSINFO)lpci->lprihead;
   lpRESULTSINFO     tail=(lpRESULTSINFO)lpci->lpritail;

   lpri = (lpRESULTSINFO)GetMemory(sizeof(RESULTSINFO));
   if(!lpri)
      return NULL;

   if(!head) {
      lpci->lprihead = lpri;
      lpri->next =
         lpri->prev = NULL;
   }
   else {
      tail->next = lpri;
      lpri->prev = tail;
      lpri->next = NULL;
   }
   lpci->lpritail = lpri;
   ++lpci->cbResults;

   return lpri;
}



//*---------------------------------------------------------------------------------
//| CreateResultsWindow:
//|   This function will create an MDI client window of type Results which can
//|      be used to display a results set.  Call this function with a CHILDINFO
//|      structure which is the owner.  A spot will be found in the array of
//|      results a child can hold.  FIFO is used if there are no empty array
//|      locations.
//| Parms:
//|   cs                   Pointer to connection window
//|   rs                   Pointer to the results set to use for creation
//| Returns:
//|   TRUE on success, FALSE on failure
//*---------------------------------------------------------------------------------
BOOL INTFUN CreateResultsWindow(CHILDINFO FAR * ci, lpRESULTSSET rs)
{
   MDICREATESTRUCT            mdicreate;
   lpRESULTSINFO              lpri;


   //
   // Allocate memory for the RESULTSINFO which holds all the control
   //    structures needed for creating a window.
   //
   lpri = AddResultsInfoNode(ci, rs);
   if(!lpri)
      return FALSE;
   lpri->ci = ci;
   lpri->rs = rs;


   //
   //  User must have a valid pointer to a results set which was create via
   //    CreateResultsSet.  This function will simply create a results set window
   //    for the user based on this value.
   //
   mdicreate.szClass = szResultsClass;
   mdicreate.szTitle = (LPSTR)rs->szTitle;
   mdicreate.hOwner  = rs->hInst;
   mdicreate.x       = CW_USEDEFAULT;
   mdicreate.y       = CW_USEDEFAULT;
   mdicreate.cx      = CW_USEDEFAULT;
   mdicreate.cy      = CW_USEDEFAULT;
   mdicreate.style   = (hwndCurMDIChild) ? ((IsZoomed(hwndCurMDIChild)) ? WS_MAXIMIZE : 0) : 0;
   mdicreate.lParam  = (LPARAM)lpri;
   if(SendMessage(rs->hwndClient, WM_MDICREATE, 0,
                  (LONG)(LPMDICREATESTRUCT)&mdicreate))
      return TRUE;
   else
      return FALSE;
}




//*---------------------------------------------------------------------------------
//| DestroyResultsWindow:
//|   This function will free all memory for a specified results set.  It must
//|      remove the results set from the array of results sets and collapse the
//|      array to maintain FIFO order.
//| Parms:
//|   lpci                 Pointer to Child info
//|   lpri                 The results to drop
//| Returns:
//|   Nothing.
//*---------------------------------------------------------------------------------
void INTFUN DestroyResultsWindow(lpCHILDINFO lpci, lpRESULTSINFO lpri)
{
   //
   // First destroy the contents of the results set, then the memory for
   //    the results set itself.
   //
   SendMessage(lpri->rs->hwndList, LB_RESETCONTENT, 0, 0L);
   SendMessage(lpci->hwndClient, WM_MDIDESTROY,
               (WPARAM)(HWND)lpri->rs->hwndResults, 0L);
   FreeResultsSet(lpri->rs);

   if(lpci->lprihead == lpri)
      lpci->lprihead = lpri->next;
   if(lpci->lpritail == lpri)
      lpci->lpritail = lpri->prev;
   if(lpri->next)
      lpri->next->prev = lpri->prev;
   if(lpri->prev)
      lpri->prev->next = lpri->next;

   --lpci->cbResults;
}


//*---------------------------------------------------------------------------------
//| ResultsWndProc:
//|   This function will handle all messages which are received by a results
//|      window.
//| Parms:
//|   in       hwnd                 Window to work with
//|   in       msg                  Message we need to handle
//|   in       wParam               First param
//|   in       lParam               Second param
//| Returns:
//|   Depends on message.
//*---------------------------------------------------------------------------------
long EXTFUN ResultsWndProc(HWND hwnd, unsigned msg, WPARAM wParam, LPARAM lParam)
{
   switch(msg) {
      //
      // WM_CREATE is received when the new window is created.  We need to create
      //    the listbox for the results set when this message is received.
      //
     case WM_CREATE:
      //
      // First get information on the font being used for the display.  Declare
      //    all variables which are only needed once on stack for this message only.
      //
      {
         CREATESTRUCT FAR *      cs;
         MDICREATESTRUCT FAR *   mdi;
         lpRESULTSINFO           rwi;
         lpRESULTSSET            rs;


         cs = (CREATESTRUCT FAR *)lParam;
         mdi = (MDICREATESTRUCT FAR *)cs->lpCreateParams;
         lpActiveResults = rwi = (lpRESULTSINFO)mdi->lParam;
         rs = rwi->rs;

         SETRWPOINTER(hwnd, lpActiveResults);
         CreateResultsFont(rs, hwnd, NULL);

         //
         // Now get the window handle values and then create the components of the
         //    results window.  These include the title which has the column names,
         //    and the actual owner drawn list box which has the results set in it.
         //
         rs->hwndResults = hwnd;
         rs->hwndClient = GetParent(hwnd);
         if(!(rs->hwndList = CreateWindow("listbox", NULL,
                                          WS_CHILD | WS_VISIBLE | WS_VSCROLL |
                                          LBS_MULTIPLESEL | LBS_OWNERDRAWFIXED |
                                          LBS_NOTIFY | LBS_EXTENDEDSEL | LBS_NOINTEGRALHEIGHT,
                                          0, 0, 0, 0,
                                          hwnd, (HMENU)(2), hInst, NULL)))
            return -1;
         if(!(rs->hwndHScroll = CreateWindow("scrollbar", NULL,
                                             WS_CHILD | WS_VISIBLE,
                                             0, 0, 0, 0,
                                             hwnd, (HMENU)(3), hInst, NULL)))
            return -1;

         //
         // Get scroll bar stats and set scroll range
         //
         SetScrollRange(rs->hwndHScroll, SB_CTL, 0, rs->cbColumns - 1, TRUE);
      }
      return 0;


      //
      // When WM_SIZE is received, we need to move the child windows including the
      //    title information and the listbox to fit the new area.  If all of the
      //    columns will fit in one display, hide our horizontal scroll bar.
      // NOTE:  We must break to return DefMDIWndProc in order for the menu to
      //    be redrawn when we maximize the child window.
      //
     case WM_SIZE:
      {
         lpRESULTSINFO        rwi = GETRWPOINTER(hwnd);
         lpRESULTSSET         rs=rwi->rs;
         int                  cScroll, dex;

         rwi->dx = LOWORD(lParam);
         rwi->dy = HIWORD(lParam);
         rwi->xRightCol = FindRightCol(rs, rwi->xLeftCol, rwi->dx);
         for(cScroll=0, dex=rwi->xLeftCol;  dex<=rwi->xRightCol;  dex++)
            cScroll += rs->md[dex].cColWidth;
         rwi->fScrollPresent = FALSE;
         if(cScroll > rwi->dx) {
            rwi->fScrollPresent = TRUE;
            MoveWindow(rs->hwndHScroll, 0, rwi->dy - GetSystemMetrics(SM_CYHSCROLL),
                       rwi->dx - GetSystemMetrics(SM_CXVSCROLL), GetSystemMetrics(SM_CYHSCROLL), TRUE);
         }
         MoveWindow(rs->hwndList, 0, rs->cTitleHeight, rwi->dx,
                    (rwi->fScrollPresent) ? rwi->dy - rs->cTitleHeight - GetSystemMetrics(SM_CYHSCROLL) : rwi->dy - rs->cTitleHeight, TRUE);
         ShowWindow(rs->hwndHScroll, (rwi->fScrollPresent) ? SW_SHOW : SW_HIDE);
         rwi->tRect.left = rwi->tRect.top = 0;
         rwi->tRect.bottom = rs->cTitleHeight;
         rwi->tRect.right = min(rwi->dx, cScroll);
      }
      break;


      //
      // Hande the WM_INITMENUPOPUP message so that when the user selects
      //    a menu, we enable/disable each item based on our current state.
      //
     case WM_INITMENUPOPUP:
      if(!(BOOL)HIWORD(lParam))        // Not the system menu
         ResetMenu((HMENU)wParam, (int)LOWORD(lParam));
      break;


      //
      // A WM_HSCROLL message is received when the user does something with our
      //    scroll bar.  We must handle horizontal scroll since a listbox does
      //    does inherintly support it.
      //
     case WM_HSCROLL:
      {
         lpRESULTSINFO  rwi = GETRWPOINTER(hwnd);
         lpRESULTSSET         rs=rwi->rs;

         HandleHScroll(wParam, rs, hwnd, rs->hwndHScroll, &rwi->xLeftCol, &rwi->xRightCol,
                       rs->hwndList, rs->cbColumns, rwi->dx, &rwi->tRect);
      }
      return 0;


      // In order to enable the keyboard to run the scroll bars (for those users
      //    without a mouse), we must look for the cursor keys etc... and cause
      //    them to do scrolling.
     case WM_KEYDOWN:
      {
         lpRESULTSINFO  rwi = GETRWPOINTER(hwnd);
         lpRESULTSSET         rs=rwi->rs;

         HandleVirtualHScroll(wParam, rs->hwndList, rs->hwndResults);
      }
      break;                              // Let it pass through to the app


      //
      // WM_MEASUREITEM is received when the listbox is first being drawn.  We tell
      //    Windows what each row is going to look like.
      //
     case WM_MEASUREITEM:
      {
         MEASUREITEMSTRUCT FAR * ms;
         lpRESULTSINFO  rwi = GETRWPOINTER(hwnd);
         lpRESULTSSET         rs=rwi->rs;

         if((int)wParam != 2)                   // Not our list box
            return FALSE;
         ms = (MEASUREITEMSTRUCT FAR *)lParam;
         ms->itemHeight = rs->cTitleHeight;
      }
      return TRUE;


      //
      // WM_DRAWITEM is received whenever we must draw a record in the results set
      //    list box.  We will recieve a pointer to the ROWDATA structure.
      //
     case WM_DRAWITEM:
      {
         DRAWITEMSTRUCT FAR * dwitem;
         lpRESULTSINFO  rwi = GETRWPOINTER(hwnd);
         lpRESULTSSET         rs=rwi->rs;

         dwitem = (DRAWITEMSTRUCT FAR *)lParam;
         DrawRowData(rs, dwitem, rwi->xLeftCol, rwi->xRightCol);
      }
      return TRUE;


      //
      // The WM_DELETEITEM message is received whenever a row is to be
      //    deleted from the listbox.  We will take the opportunity to
      //    free the storage for the row.
      //
     case WM_DELETEITEM:
      {
         DELETEITEMSTRUCT FAR *  dlt;
         lpRESULTSINFO  rwi = GETRWPOINTER(hwnd);
         lpRESULTSSET         rs=rwi->rs;
         ROWDATA FAR *        rd;

         dlt = (DELETEITEMSTRUCT FAR *)lParam;
         rd = (ROWDATA FAR *)dlt->itemData;
         FreeRowData(rs, rd);
      }
      return 0;


      //
      // WM_PAINT means it's time for us to paint our columns titles which are
      //    simply drawn in the client area for speed.
      //
     case WM_PAINT:
      {
         HDC            hdc;
         PAINTSTRUCT    ps;
         lpRESULTSINFO  rwi = GETRWPOINTER(hwnd);
         lpRESULTSSET   rs=rwi->rs;

         hdc = BeginPaint(hwnd, &ps);
         if(hdc) {
            DrawColumnTitles(hdc, rs, &rwi->tRect, rwi->xLeftCol, rwi->xRightCol);
            if(rwi->fScrollPresent) {
               RECT           rct;
               rct.left = rwi->dx - GetSystemMetrics(SM_CXVSCROLL);
               rct.top = rwi->dy - GetSystemMetrics(SM_CYHSCROLL);
               rct.right = rwi->dx;
               rct.bottom = rwi->dy;
               MoveTo(hdc, rct.left, rct.top);
               LineTo(hdc, rct.right, rct.top);
               ++rct.top;
               FillRect(hdc, &rct, GetStockObject(LTGRAY_BRUSH));
            }
            EndPaint(hwnd, &ps);
         }
      }
      break;

      //
      // All messages are handled in the main wnd proc, so pass them back
      //
     case WM_COMMAND:
      {
         UINT        id=GET_WM_COMMAND_ID(wParam, lParam);

         if(id >= IDM_CONNECT &&
            id <= IDM_MOVE_WINDOW)
            SendMessage(hwndFrame, WM_COMMAND, wParam, lParam);
      }
      break;


      //
      // The WM_MDIACTIVATE message is received first by the child window
      //    which is losing focus, then by the window which is receiving
      //    focus. If we're changing windows, get the RESULTSSET.
      //
     case WM_MDIACTIVATE:
      {
#ifndef WIN32
         if(wParam) {
            lpActiveResults = GETRWPOINTER((HWND)LOWORD(lParam));
         }
#else
         if((HWND)lParam == hwnd) {
            lpActiveResults = GETRWPOINTER((HWND)lParam);
         }
#endif
         else
            lpActiveResults = NULL;

         if(lpActiveResults) {
            RECT     rect;

            hwndCurMDIChild = lpActiveResults->rs->hwndResults;
            lpActiveConn = lpActiveResults->ci;
            GetClientRect(hwndCurMDIChild, &rect);
            InvalidateRect(hwndCurMDIChild, &rect, TRUE);
         }
      }
      return 0;


      //
      // If the user selects close from the system menu for the window, we need
      //    to be able to backtrack and delete our results set.  Since our
      //    list of results set is not kept by us, we will pass in our rs
      //    pointer and let InternalDestroyResultsWindow find the correct
      //    node to destroy.
      //
     case WM_SYSCOMMAND:
      {
         lpRESULTSINFO  rwi = lpActiveResults;

         if(wParam == SC_CLOSE)
            DestroyResultsWindow(lpActiveConn, rwi);
      }
      break;

     default:
      break;
   }

   //
   // If we haven't already processed the message, do default behavior.
   //
   return DefMDIChildProc(hwnd, msg, wParam, lParam);
}


//*------------------------------------------------------------------------
//| SetMetaDataFromSql:
//|   This function will walk through the columns of a results set and
//|      set the meta data accordingly.  If the caller so chooses, they
//|      may update the default values after calling this function.
//| Parms:
//|   in       hwndOut              Where to write output
//|   in       hstmt                Statement handle with results set
//|   in       rs                   Pointer to results set
//|   in       cbCols               Number of results cols
//| Returns:
//|   TRUE if successful, FALSE otherwise
//*------------------------------------------------------------------------
BOOL SetMetaDataFromSql(HWND hwndOut, HSTMT hstmt, RESULTSSET FAR * rs, int cbCols)
{
   int         dex;
   char        szColumnName[MAXBUFF];
   SWORD       fSqlType;
   UDWORD      precision;
   SWORD       scale;
   SWORD       fNullable;
   RETCODE     retcode;

   for(dex=0;  dex<cbCols;  dex++) {
      retcode = SQLDescribeCol(hstmt,
                               (UWORD)(dex+1), (LPSTR)szColumnName,
                               sizeof(szColumnName),
                               NULL,
                               &fSqlType, &precision, &scale, &fNullable);
      if(!*szColumnName)         // Some drivers don't return names for computed columns
         wsprintf(szColumnName, GetidsString(idsExpression, OutStr, MAXBUFF), dex);
      if(retcode != SQL_SUCCESS)
         PrintErrorsHwnd(hwndOut, SQL_HANDLE_STMT, hstmt);
      else
         SetMetaDataColumn(rs, dex, (LPSTR)szColumnName,
                           GetTypeName(SQL_TYPE, fSqlType), fSqlType,
                           (UDWORD)precision, (SWORD)scale,
                           (int)(min(MAXBYTES, precision)), TA_LEFT);
   }
   return TRUE;
}


//*------------------------------------------------------------------------
//| FetchAllRecordsToResults:
//|   This function will fetch each row, convert it to char, then add it
//|      to the results set we're querying.
//| Parms:
//|   in       hwnd                 Where to write output
//|   in       hstmt                Statement handle with results set
//|   in       rs                   Pointer to results set
//|   in       cbCols               Number of columns
//|   in       fFetch               TRUE if need to fetch first record
//| Returns:
//|   Number of records which were fetched.
//*------------------------------------------------------------------------
SDWORD FetchAllRecordsToResults(HWND hwndOut, HSTMT hstmt,
            RESULTSSET FAR * rs, int cbCols, BOOL fFetch)
{
#define MAXRSLTSIZE 65535
   int                  dex;
   ROWDATA FAR *        rd;
   LPSTR                inbuff, outbuff;
   SDWORD               cNull;
   RETCODE              retcode;
   SDWORD               cnt=0;
   COLORREF             rgbDft=GetDefaultRGB();

   //
   // First get some memory to work with
   //
   inbuff = (LPSTR)GetMemory(MAXRSLTSIZE);
   outbuff = (LPSTR)GetMemory(MAXRSLTSIZE);
   if(!inbuff ||
      !outbuff)
      return FALSE;

   //
   // Now fetch each row, do a getdata on each column, convert it to char, then
   //    add it to the results set.  The caller has the option of fetching the
   //    first row.  This is required, as the caller may have needed to find
   //    out if there was a results set.
   //
   if(fFetch)
      retcode = SQLFetch(hstmt);
   else
      retcode = SQL_SUCCESS;
   while(retcode != SQL_NO_DATA) {
      // Increment count and enforce max records
      if(cnt > MAXRECORDS) {
         szMessageBox(hwndOut,
                      MB_ICONEXCLAMATION + MB_OK,
                      "Limit",
                      GetidsString(idsMaxRecords, OutStr, MAXBUFF),
                      MAXRECORDS);
         SQLFreeStmt(hstmt, SQL_CLOSE);
         goto exit00;
      }
      ++cnt;

      if(retcode != SQL_SUCCESS)
         PrintErrorsHwnd(hwndOut, SQL_HANDLE_STMT, hstmt);
      else {
         //
         // Loop through each column and retrieve it's value
         //
         rd = AllocateRowData(rs, rgbDft, RDATA_DEFAULT_BKGRND);
         for(dex=0;  dex<cbCols;  dex++) {
            retcode = SQLGetData(hstmt, (UWORD)(dex+1),
                                 SQL_C_DEFAULT,
                                 (PTR)inbuff,
                                 rs->md[dex].precision + 1,
                                 &cNull);
            if(retcode != SQL_SUCCESS) {
               PrintErrorsHwnd(hwndOut, SQL_HANDLE_STMT, hstmt);
               SetColumnData(dex, rd, (LPSTR)szErrorVal);
            }
            else {
               if(cNull != SQL_NULL_DATA)
                  ConvertSqlTypeToChar(rs, dex, inbuff, outbuff, cNull);
               SetColumnData(dex, rd,
                             (cNull == SQL_NULL_DATA) ? (LPSTR)szNullString : outbuff);
            }
         }     // End of loop through columns
         if(AddRowData(rs, rd) == LB_ERRSPACE)
            goto exit00;
      }

      retcode = SQLFetch(hstmt);
   }           // End of fetch loop

  exit00:
   ReleaseMemory(inbuff);
   ReleaseMemory(outbuff);

   return cnt;
}


//*------------------------------------------------------------------------
//| PrintAffectedRows:
//|   This function will print out the "Affected rows" message based on
//|   row count.
//| Parms:
//|   in       hstmt                Statement handle to use
//|   in       hwnd                 Where to write output
//| Returns:
//|   Number of records which were affected
//*------------------------------------------------------------------------
SDWORD PrintAffectedRows(HSTMT hstmt, HWND hwnd)
{
   SDWORD   cbRowCount;
   RETCODE  retcode;

   //
   // Use SQLRowCount to see how many rows were affected.  It is possible
   //    that the driver does not know, in which case -1 will be returned.
   //    in this case, we assume success.
   //
   retcode = SQLRowCount(hstmt, &cbRowCount);
   if(cbRowCount > 0)
      szWrite(hwnd,
              GetidsString(idsAffectedRows, OutStr, MAXBUFF),
              cbRowCount);
   else
      szWrite(hwnd, GetidsString(idsStmtProcessed, OutStr, MAXBUFF));

   return cbRowCount;
}
