//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   DIALOGS.H
//|      This file contains all of the constant definitions for the 
//|      dialogs used for the lists.
//*---------------------------------------------------------------------------------
#ifndef dialogs_DEFS
#define dialogs_DEFS

#include <windows.h>
#include "standard.h"
#include "child.h"


//*---------------------------------------------------------------------------------
//|   Macros and Defines
//*---------------------------------------------------------------------------------
#define  IDD_SQLTABLES              3000
#define  IDD_SQLCOLUMNS             3001
#define  IDD_SQLSPECIALCOLUMNS      3002
#define  IDD_SQLSTATISTICS          3003
#define  IDD_SQLPRIMARYKEYS         3004
#define  IDD_SQLFOREIGNKEYS         3005
#define  IDD_SQLTABLEPRIVILEGES     3006
#define  IDD_SQLCOLUMNPRIVILEGES    3007
#define  IDD_SQLPROCEDURES          3008
#define  IDD_SQLPROCEDURECOLUMNS    3009

#define  IDT_TABLE                  301
#define  IDT_TYPE                   303
#define  IDT_COLUMN                 304

#define  IDE_TABLE                  331
#define  IDE_TYPE                   333
#define  IDE_COLUMN                 334

#define  IDX_BEST_ROWID             340
#define  IDX_ROWVER                 341
#define  IDX_NO_NULLS               342
#define  IDX_NULLABLE               343
#define  IDX_SCOPE_CURROW           344
#define  IDX_SCOPE_TRANSACTION      345
#define  IDX_SCOPE_SESSION          346

#define  IDX_INDEX_UNIQUE           360
#define  IDX_INDEX_ALL              361
#define  IDX_ENSURE                 362
#define  IDX_QUICK                  363

#define  IDT_QUALIFIER2             365
#define  IDT_OWNER2                 366
#define  IDT_TABLE2                 367
#define  IDE_QUALIFIER2             368
#define  IDE_OWNER2                 369
#define  IDE_TABLE2                 370

#define  IDT_PROCEDURE              375
#define  IDE_PROCEDURE              376


typedef BOOL (FAR PASCAL *DLGWNDPROC) (HWND hDlg, unsigned msg, WORD wParam, LONG lParam);



//*---------------------------------------------------------------------------------
//|   Function prototypes
//*---------------------------------------------------------------------------------
void DoList(CHILDINFO FAR * ci, int idMenuSelection);

#endif
