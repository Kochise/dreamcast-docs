//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   DIALOGS.C
//|      This module contains the dialog procs which are used to display
//|         catalog function arguements and display the results.  Note that
//|         the best way to determine the size of the arguements would be
//|         to use SQLGetInfo, however, due to ease of coding, the values
//|         have been hard-coded to constants.
//*---------------------------------------------------------------------------------
#include <windows.h>
#include "admndemo.h"
#include "dialogs.h"
#include "sql.h"
#include "sqlext.h"
#include "execute.h"
#include "info.h"
#include "results.h"
#include "strings.h"

VSZFile;
#define CHKNULL(str)  (*str ? str : NULL)


//*---------------------------------------------------------------------------------
//|   Local function prototypes
//*---------------------------------------------------------------------------------
BOOL ShowCatalogResults(CHILDINFO FAR * ci, LPSTR szTitle);
BOOL EXTFUN CatalogWndProc(HWND hDlg, unsigned msg, WPARAM wParam, LPARAM lParam);


//*---------------------------------------------------------------------------------
//|   Global variables
//*---------------------------------------------------------------------------------
extern char OutStr[MAXBUFF];


//
// The following set of defines and host vars are used to create a common
// dialog handler for each of the catalog function dialogs.  This makes
// the code size smaller while still handling each catalog functions
// parameters.  It also allows for sharing of values from one function
// to another.
//
#define CAT_LAST         256
#define CAT_QUALIFIER      1
#define CAT_TABLE          2
#define CAT_OWNER          4
#define CAT_TYPE           8
#define CAT_COLUMN        16
#define CAT_QUALIFIER2    32
#define CAT_OWNER2        64
#define CAT_TABLE2       128
#define CAT_PROCS        256
char szQualifierVal[MAX_QUALIFIER];
char szTableVal[MAX_NAME];
char szOwnerVal[MAX_OWNER];
char szTypeVal[MAX_NAME];
char szColumnVal[MAX_NAME];
char szQualifierVal2[MAX_QUALIFIER];
char szOwnerVal2[MAX_OWNER];
char szTableVal2[MAX_NAME];
char szProcsVal[MAX_NAME];

struct {
   int         mMask;                        // Bit mask value
   int         id;                           // Edit control id
   LPSTR       szStr;                        // Buffer location
   int         cbMax;                        // Maximum size
   } CatalogVals[] = {
// mMask                id                      szStr                   cbMax
// -------------------  ---------------------   ----------------------- ------------------------
   CAT_QUALIFIER,       IDE_QUALIFIER,          (LPSTR)szQualifierVal,  MAX_QUALIFIER,
   CAT_TABLE,           IDE_TABLE,              (LPSTR)szTableVal,      MAX_NAME,
   CAT_OWNER,           IDE_OWNER,              (LPSTR)szOwnerVal,      MAX_OWNER,
   CAT_TYPE,            IDE_TYPE,               (LPSTR)szTypeVal,       MAX_NAME,
   CAT_COLUMN,          IDE_COLUMN,             (LPSTR)szColumnVal,     MAX_NAME,
   CAT_QUALIFIER2,      IDE_QUALIFIER2,         (LPSTR)szQualifierVal2, MAX_QUALIFIER,
   CAT_OWNER2,          IDE_OWNER2,             (LPSTR)szOwnerVal2,     MAX_OWNER,
   CAT_TABLE2,          IDE_TABLE2,             (LPSTR)szTableVal2,     MAX_NAME,
   CAT_PROCS,           IDE_PROCEDURE,          (LPSTR)szProcsVal,      MAX_NAME,
   };

dCSEG(char) szTablesTitle[]               =  "Tables";
dCSEG(char) szColumnsTitle[]              =  "Columns";
dCSEG(char) szStatistics[]                =  "Statistics";
dCSEG(char) szPrimaryKeys[]               =  "Primary Keys";
dCSEG(char) szForeignKeys[]               =  "Foreign Keys";
dCSEG(char) szTablePrivs[]                =  "Table Privileges";
dCSEG(char) szColumnPrivs[]               =  "Column Privileges";
dCSEG(char) szSpecialCols[]               =  "Special Columns";
dCSEG(char) szProcsTitle[]                =  "Procedures";
dCSEG(char) szProcCols[]                  =  "Procedure Columns";
dCSEG(char) szCOLON[]                     =  ":";


struct {
   int               idMenu;                    // Menu identifier
   int               iDialogName;               // ID of dialog
// DLGWNDPROC        dlgProc;                   // Dialog procedure
   LPSTR             szDlgTitle;                // Title of the dialog
   UINT              mask;                      // Mask for this dialog
   } Dialogs[] = {
// idMenu                  iDialogName                szDlgTitle              mask
// ---------------------   ------------------         ----------------------- -------------------------------------------------
   IDM_TABLES,             IDD_SQLTABLES,             (LPSTR)szTablesTitle,   CAT_QUALIFIER | CAT_OWNER | CAT_TABLE | CAT_TYPE,
   IDM_COLUMNS,            IDD_SQLCOLUMNS,            (LPSTR)szColumnsTitle,  CAT_QUALIFIER | CAT_OWNER | CAT_TABLE | CAT_COLUMN,
   IDM_STATISTICS,         IDD_SQLSTATISTICS,         (LPSTR)szStatistics,    CAT_QUALIFIER | CAT_OWNER | CAT_TABLE,
   IDM_PRIMARY_KEYS,       IDD_SQLPRIMARYKEYS,        (LPSTR)szPrimaryKeys,   CAT_QUALIFIER | CAT_OWNER | CAT_TABLE,
   IDM_FOREIGN_KEYS,       IDD_SQLFOREIGNKEYS,        (LPSTR)szForeignKeys,   CAT_QUALIFIER | CAT_OWNER | CAT_TABLE | CAT_QUALIFIER2 | CAT_OWNER2 | CAT_TABLE2,
   IDM_TABLE_PRIVS,        IDD_SQLTABLEPRIVILEGES,    (LPSTR)szTablePrivs,    CAT_QUALIFIER | CAT_OWNER | CAT_TABLE,
   IDM_COLUMN_PRIVS,       IDD_SQLCOLUMNPRIVILEGES,   (LPSTR)szColumnPrivs,   CAT_QUALIFIER | CAT_OWNER | CAT_TABLE | CAT_COLUMN,
   IDM_SPECIAL_COLUMNS,    IDD_SQLSPECIALCOLUMNS,     (LPSTR)szSpecialCols,   CAT_QUALIFIER | CAT_OWNER | CAT_TABLE,
   IDM_PROCEDURES,         IDD_SQLPROCEDURES,         (LPSTR)szProcsTitle,    CAT_QUALIFIER | CAT_OWNER | CAT_PROCS,
   IDM_PROC_COLUMNS,       IDD_SQLPROCEDURECOLUMNS,   (LPSTR)szProcCols,      CAT_QUALIFIER | CAT_OWNER | CAT_PROCS | CAT_COLUMN,
   };

//
// This structure is used to control the catalog fucntions
//
typedef struct tagCATALOGINFO {
   HINSTANCE         hInst;               // Instance handle for this app
   CHILDINFO FAR *   ci;                  // Child info
   int               id;                  // Dialog id to indicate function
   LPSTR             szDlgTitle;          // Title for the dialog
   UINT              mask;                // Dialog control mask
// For SQLStatistics
   UWORD             fUnique;
   UWORD             fAccuracy;
// For SQLSpecialColumns
   UWORD             fColType;
   UWORD             fScope;
   UWORD             fNullable;
   } CATALOGINFO;

//
// A prototype for radio button controls
//
typedef struct tagIDXINFO {
   int               idxVal;
   int               fType;
   } IDXINFO;

//
// For SQLStatistics, fUnqiue parameter
//
struct {
   int               idxVal;                    // Dialog item number
   int               fType;                     // SQL constant equivalent
   } StatsfUnique[] = {
// idxVal                        fType
// --------------------------    ---------------------------------
   IDX_INDEX_UNIQUE,             SQL_INDEX_UNIQUE,
   IDX_INDEX_ALL,                SQL_INDEX_ALL,
   };

//
// For SQLStatistics, fAccuracy parameter
//
struct {
   int               idxVal;                    // Dialog item number
   int               fType;                     // SQL constant equivalent
   } StatsfAccuracy[] = {
// idxVal                        fType
// --------------------------    ---------------------------------
   IDX_ENSURE,                   SQL_ENSURE,
   IDX_QUICK,                    SQL_QUICK,
   };

//
// For SQLSpecialColumns, fColType parameter
//
struct {
   int               idxVal;                    // Dialog item number
   int               fType;                     // SQL constant equivalent
   } SpecColsfColType[] = {
// idxVal                        fType
// --------------------------    ---------------------------------
   IDX_BEST_ROWID,               SQL_BEST_ROWID,
   IDX_ROWVER,                   SQL_ROWVER,
   };

//
// For SQLSpecialColumns, fNullable parameter
//
struct {
   int               idxVal;                    // Dialog item number
   int               fType;                     // SQL constant equivalent
   } SpecColsfNullable[] = {
// idxVal                        fType
// --------------------------    ---------------------------------
   IDX_NO_NULLS,                 SQL_NO_NULLS,
   IDX_NULLABLE,                 SQL_NULLABLE,
   };

//
// For SQLSpecialColumns, fScope parameter
//
struct {
   int               idxVal;                    // Dialog item number
   int               fType;                     // SQL constant equivalent
   } SpecColsfScope[] = {
// idxVal                        fType
// --------------------------    ---------------------------------
   IDX_SCOPE_CURROW,             SQL_SCOPE_CURROW,
   IDX_SCOPE_TRANSACTION,        SQL_SCOPE_TRANSACTION,
   IDX_SCOPE_SESSION,            SQL_SCOPE_SESSION,
   };




//*---------------------------------------------------------------------------------
//| GetRadioValue:
//|   This function will examine a group of radio buttons based on the control
//|   structure and see which is checked.  When found, that value is returned.
//| Parms:
//|   hDlg           Window handle of dialog with control
//|   stct           Radio control structure
//|   cbNum          How many items in control structure
//| Returns:
//|   The value for the item checked
//*---------------------------------------------------------------------------------
int GetRadioValue(HWND hDlg, IDXINFO FAR * stct, int cbNum)
{
   int   dex;
   for(dex=0;  dex<cbNum;  dex++)
      if(IsDlgButtonChecked(hDlg, stct[dex].idxVal))
         return(stct[dex].fType);
   return 0;
}


//*---------------------------------------------------------------------------------
//| ShowCatalogResults:
//|   This function will display the results set returned by a catalog
//|   function.
//| Parms:
//|   in       ci                   CHILDINFO information
//|   in       szTitle              Title for the results set
//| Returns:
//|   Nothing.
//*---------------------------------------------------------------------------------
BOOL ShowCatalogResults(CHILDINFO FAR * ci, LPSTR szTitle)
{
   RESULTSSET FAR *  rs;
   int               cbCols;

   if(!(cbCols = GetNumResultsCols(ci->hstmt)))
      return TRUE;
   if(cbCols == 0) {
      szWrite(ci->hwndOut, GetidsString(idsNoDataFound, OutStr, sizeof(OutStr)));
      return TRUE;
   }
   rs = GetConnectWindowResultsNode(ci);
   if(!CreateResultsSet(rs, ci->hwndClient, ci->hInst,
                        cbCols, szTitle))
      return TRUE;
   SetMetaDataFromSql(ci->hwndOut, ci->hstmt, rs, cbCols);
   if(!CreateResultsWindow(ci, rs))
      return TRUE;
   FetchAllRecordsToResults(ci->hwndOut, ci->hstmt, rs, cbCols, TRUE);
   SQLFreeStmt(ci->hstmt, SQL_CLOSE);

   return FALSE;
}


//*---------------------------------------------------------------------------------
//| DoList:
//|   This function will display a selection dialog for the catalog functions
//|   then process the request.
//| Parms:
//|   in       ci                   CHILDINFO information
//|   in       idMenuSelection      Menu value
//| Returns:
//|   Nothing.
//*---------------------------------------------------------------------------------
void DoList(CHILDINFO FAR * ci, int idMenuSelection)
{
   static BOOL             fInit;            // Have we called before
   CATALOGINFO             cati;
   CATALOGINFO FAR *       lpcati=&cati;
   int                     dex;
   HWND                    fHwnd=GetFocus();

   // Clean up all buffers on first catalog function
   if(!fInit) {
      for(dex=0;  dex<NumItems(CatalogVals);  dex++)
         memset(CatalogVals[dex].szStr, 0, CatalogVals[dex].cbMax);
      fInit = TRUE;
   }

   // Find the dialog
   for(dex=0;  dex<NumItems(Dialogs) &&
       Dialogs[dex].idMenu != idMenuSelection;  dex++);

   // Collect information for the dialog proc
   cati.hInst = ci->hInst;
   cati.id = idMenuSelection;
   cati.ci = ci;
   cati.szDlgTitle = Dialogs[dex].szDlgTitle;
   cati.mask = Dialogs[dex].mask;

   // Display the dialog
   if(-1 == DialogBoxParam(cati.hInst,
                           MAKEINTRESOURCE(Dialogs[dex].iDialogName),
                           ci->hwnd,
                           (DLGPROC) CatalogWndProc, (LPARAM)(CATALOGINFO FAR *)lpcati))
      MessageBox(NULL, "Could not open dialog box.",
                 "DoList", MB_ICONEXCLAMATION);

   if(fHwnd)
      SetFocus(fHwnd);
}



//*---------------------------------------------------------------------------------
//| DoCatalogFunction:
//|   The caller should have prepared all the information we need, so we will
//|   simply invoke the function they want to run.
//|
//| Parms:
//|   cati     CATALOGINFO
//| Returns:
//|   Nothing
//*---------------------------------------------------------------------------------
void DoCatalogFunction(CATALOGINFO FAR * cati)
{
   char                 szTitle[MAXBUFF];
   RETCODE              retcode;
   CHILDINFO FAR *      ci=cati->ci;

   SQLFreeStmt(ci->hstmt, SQL_CLOSE);

   switch(cati->id) {
     case IDM_TABLES:
      if (!*szTableVal &&
          ((!*szOwnerVal && strcmp(szQualifierVal, "%") == 0)||
           (!*szQualifierVal && strcmp(szOwnerVal, "%") == 0)))
         retcode = SQLTables(ci->hstmt,
                             szQualifierVal, SQL_NTS,
                             szOwnerVal, SQL_NTS,
                             szTableVal, SQL_NTS,
                             szTypeVal, SQL_NTS);
      else
         retcode = SQLTables(ci->hstmt,
                             CHKNULL(szQualifierVal), SQL_NTS,
                             CHKNULL(szOwnerVal), SQL_NTS,
                             CHKNULL(szTableVal), SQL_NTS,
                             CHKNULL(szTypeVal), SQL_NTS);
      break;

     case IDM_COLUMNS:
      retcode = SQLColumns(ci->hstmt,
                           CHKNULL(szQualifierVal), SQL_NTS,
                           CHKNULL(szOwnerVal), SQL_NTS,
                           CHKNULL(szTableVal), SQL_NTS,
                           CHKNULL(szColumnVal), SQL_NTS);
      break;

     case IDM_STATISTICS:
      retcode = SQLStatistics(ci->hstmt,
                              CHKNULL(szQualifierVal), SQL_NTS,
                              CHKNULL(szOwnerVal), SQL_NTS,
                              CHKNULL(szTableVal), SQL_NTS,
                              cati->fUnique,
                              cati->fAccuracy);
      break;

     case IDM_PRIMARY_KEYS:
      retcode = SQLPrimaryKeys(ci->hstmt,
                               CHKNULL(szQualifierVal), SQL_NTS,
                               CHKNULL(szOwnerVal), SQL_NTS,
                               CHKNULL(szTableVal), SQL_NTS);
      break;

     case IDM_FOREIGN_KEYS:
      retcode = SQLForeignKeys(ci->hstmt,
                               CHKNULL(szQualifierVal), SQL_NTS,
                               CHKNULL(szOwnerVal), SQL_NTS,
                               CHKNULL(szTableVal), SQL_NTS,
                               CHKNULL(szQualifierVal2), SQL_NTS,
                               CHKNULL(szOwnerVal2), SQL_NTS,
                               CHKNULL(szTableVal2), SQL_NTS);
      break;

     case IDM_TABLE_PRIVS:
      retcode = SQLTablePrivileges(ci->hstmt,
                                   CHKNULL(szQualifierVal), SQL_NTS,
                                   CHKNULL(szOwnerVal), SQL_NTS,
                                   CHKNULL(szTableVal), SQL_NTS);
      break;

     case IDM_COLUMN_PRIVS:
      retcode = SQLColumnPrivileges(ci->hstmt,
                                    CHKNULL(szQualifierVal), SQL_NTS,
                                    CHKNULL(szOwnerVal), SQL_NTS,
                                    CHKNULL(szTableVal), SQL_NTS,
                                    CHKNULL(szColumnVal), SQL_NTS);
      break;

     case IDM_SPECIAL_COLUMNS:
      retcode = SQLSpecialColumns(ci->hstmt,
                                  cati->fColType,
                                  CHKNULL(szQualifierVal), SQL_NTS,
                                  CHKNULL(szOwnerVal), SQL_NTS,
                                  CHKNULL(szTableVal), SQL_NTS,
                                  cati->fScope,
                                  cati->fNullable);
      break;

     case IDM_PROCEDURES:
      retcode = SQLProcedures(ci->hstmt,
                              CHKNULL(szQualifierVal), SQL_NTS,
                              CHKNULL(szOwnerVal), SQL_NTS,
                              CHKNULL(szProcsVal), SQL_NTS);
      break;

     case IDM_PROC_COLUMNS:
      retcode = SQLProcedureColumns(ci->hstmt,
                                    CHKNULL(szQualifierVal), SQL_NTS,
                                    CHKNULL(szOwnerVal), SQL_NTS,
                                    CHKNULL(szProcsVal), SQL_NTS,
                                    CHKNULL(szColumnVal), SQL_NTS);
      break;

     default:
      break;
   }

   if(retcode != SQL_SUCCESS) {
      PrintErrors(ci, SQL_HANDLE_STMT);
      return;
   }

   lstrcpy((LPSTR)szTitle, (LPSTR)ci->szClientTitle);
   lstrcat((LPSTR)szTitle, (LPSTR)szCOLON);
   lstrcat((LPSTR)szTitle, (LPSTR)cati->szDlgTitle);
   if(ShowCatalogResults(ci, (LPSTR)szTitle))
      return;
}


//*------------------------------------------------------------------------
//| CatalogWndProc:
//|   This windows procedure handles all of the catalog function messages.
//|   Many things such as setting/getting text values are table driven.
//|   This reduces overall code size significantly.
//| Parms:
//|   in       Standard window parms
//| Returns:
//|   Depends on message
//*------------------------------------------------------------------------
BOOL EXTFUN CatalogWndProc(HWND hDlg, unsigned msg, WPARAM wParam, LPARAM lParam)
{
   static CATALOGINFO FAR *   cati;
   int                        dex;

   switch(msg) {
     case WM_INITDIALOG:
      cati = (CATALOGINFO FAR *)lParam;
      CenterDialog(hDlg);

      // Set all default values for edit controls
      for(dex=0;  dex<NumItems(CatalogVals);  dex++)
         if(cati->mask & CatalogVals[dex].mMask) {
            SetWindowText(GetDlgItem(hDlg, CatalogVals[dex].id),
                          CatalogVals[dex].szStr);
            SendMessage(GetDlgItem(hDlg, CatalogVals[dex].id), EM_LIMITTEXT,
                        CatalogVals[dex].cbMax, 0L);
         }
      // Special case for dialogs with options
      if(cati->id == IDM_STATISTICS) {
         CheckRadioButton(hDlg, IDX_INDEX_UNIQUE, IDX_INDEX_ALL, IDX_INDEX_UNIQUE);
         CheckRadioButton(hDlg, IDX_ENSURE, IDX_QUICK, IDX_ENSURE);
      }
      else if(cati->id == IDM_SPECIAL_COLUMNS) {
         CheckRadioButton(hDlg, IDX_BEST_ROWID, IDX_ROWVER, IDX_BEST_ROWID);
         CheckRadioButton(hDlg, IDX_NO_NULLS, IDX_NULLABLE, IDX_NO_NULLS);
         CheckRadioButton(hDlg, IDX_SCOPE_CURROW, IDX_SCOPE_SESSION, IDX_SCOPE_CURROW);
      }

      return TRUE;


     case WM_COMMAND:
      switch(GET_WM_COMMAND_ID(wParam, lParam)) {
        case IDOK:
         {
            Busy(TRUE);
            for(dex=0;  dex<NumItems(CatalogVals);  dex++)
               if(cati->mask & CatalogVals[dex].mMask)
                  GetText(GetDlgItem(hDlg, CatalogVals[dex].id),
                          CatalogVals[dex].szStr);
            // Special case for dialogs with options
            if(cati->id == IDM_STATISTICS) {
               cati->fUnique = GetRadioValue(hDlg, (IDXINFO FAR *)StatsfUnique, NumItems(StatsfUnique));
               cati->fAccuracy = GetRadioValue(hDlg, (IDXINFO FAR *)StatsfAccuracy, NumItems(StatsfAccuracy));
            }
            else if(cati->id == IDM_SPECIAL_COLUMNS) {
               cati->fColType = GetRadioValue(hDlg, (IDXINFO FAR *)SpecColsfColType,
                                              NumItems(SpecColsfColType));
               cati->fScope = GetRadioValue(hDlg, (IDXINFO FAR *)SpecColsfScope,
                                            NumItems(SpecColsfScope));
               cati->fNullable = GetRadioValue(hDlg, (IDXINFO FAR *)SpecColsfNullable,
                                               NumItems(SpecColsfNullable));
            }
            DoCatalogFunction(cati);

            Busy(FALSE);
            EndDialog(hDlg, IDOK);
         }
         return TRUE;

        case IDCANCEL:
         SendMessage(hDlg, WM_CLOSE, 0, 0L);
         EndDialog(hDlg, IDCANCEL);
         return TRUE;
      }
      return TRUE;

     default:
      return FALSE;
   }
   return FALSE;
}

