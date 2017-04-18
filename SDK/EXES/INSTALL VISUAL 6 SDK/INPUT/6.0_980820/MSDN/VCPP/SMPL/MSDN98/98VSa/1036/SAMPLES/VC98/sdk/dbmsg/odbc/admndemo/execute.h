//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   EXECUTE.H
//|      This file contains the prototypes and defines for executing SQL
//|         statements and displaying their results.
//*---------------------------------------------------------------------------------
#ifndef execute_DEFS
#define execute_DEFS

#include <windows.h>
#include "menu.h"
#include "admndemo.h"
#include "standard.h"
#include "errcheck.h"
#include "results.h"
#include "ctl3d.h"
#include "ini.h"
#include "sql.h"
#include "sqlext.h"

//*---------------------------------------------------------------------------------
//|   Macros and Defines
//*---------------------------------------------------------------------------------
#define MINSTMTSIZE                           100
#define MAXSTMTSIZE                          9999
#define IDD_EXECUTE_FILE                     3100
#define NO_STOP                              -999
#define IDT_FILE                              500
#define IDB_FILE                              501
#define IDR_CARRIAGE                          502
#define IDR_CHARACTER                         503
#define IDE_CHARACTER                         504
#define IDR_NOSTOP                            505
#define IDR_SQLERROR                          506
#define IDE_MAXLENGTH                         507

#define EXECUTE_DIRECT_SQL_STMT                 1
#define PREPARE_SQL_STMT                        2
#define EXECUTE_SQL_STMT                        3

typedef struct tagRESULTSINFO {
   RESULTSSET FAR *     rs;               // Results set
   CHILDINFO FAR *      ci;               // Child info
   int                  xLeftCol;         // Left column index
   int                  xRightCol;        // Right column index
   int                  dx;               // Client screen width
   int                  dy;               // Client screen height
   RECT                 tRect;            // Client rectangle
   BOOL                 fScrollPresent;   // TRUE if scroll bar is visible
   struct tagRESULTSINFO FAR * next;
   struct tagRESULTSINFO FAR * prev;
   } RESULTSINFO, FAR * lpRESULTSINFO;

#define GETRWPOINTER(hwnd) (lpRESULTSINFO)(GetWindowLong(hwnd, 0))
#define SETRWPOINTER(hwnd, x) SetWindowLong(hwnd, 0, (LONG)(x))


//*---------------------------------------------------------------------------------
//|   Global variables
//*---------------------------------------------------------------------------------
extern HMENU hMenu;

extern dCSEG(char) szResultsClass[];
extern dCSEG(char) szDash[];


//*---------------------------------------------------------------------------------
//|   Function prototypes
//*---------------------------------------------------------------------------------
void ExecuteFile(CHILDINFO FAR * ci, HWND hwnd, LPSTR szExeFile,
      LPSTR szTerm, int cbStmt);
void DoCommitRollback(CHILDINFO FAR * ci, int type);
void ExecuteCmds(CHILDINFO FAR * ci, LPSTR stmt);
void CheckForResults(CHILDINFO FAR * ci);
void FreeConnectWindowResults(CHILDINFO FAR * ci);
lpRESULTSSET GetConnectWindowResultsNode(lpCHILDINFO lpci);
BOOL INTFUN CreateResultsWindow(CHILDINFO FAR * ci, lpRESULTSSET rs);
long FAR PASCAL ResultsWndProc(HWND hwnd, unsigned msg, WPARAM wParam, LPARAM lParam);
BOOL SetMetaDataFromSql(HWND hwndOut, HSTMT hstmt, RESULTSSET FAR * rs, int cbCols);
SDWORD FetchAllRecordsToResults(HWND hwndOut, HSTMT hstmt,
            RESULTSSET FAR * rs, int cbCols, BOOL fFetch);
SDWORD PrintAffectedRows(HSTMT hstmt, HWND hwnd);


#endif
