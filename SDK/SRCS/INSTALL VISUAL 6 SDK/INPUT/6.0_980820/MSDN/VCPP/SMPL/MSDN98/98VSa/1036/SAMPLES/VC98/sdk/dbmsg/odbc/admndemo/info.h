//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   INFO.H
//|      This file contains the prototypes and defines for executing SQL
//|         statements and displaying their results.
//*---------------------------------------------------------------------------------
#ifndef info_DEFS
#define info_DEFS

#include <windows.h>
#include "standard.h"
#include "errcheck.h"
#include "ctl3d.h"
#include "results.h"
#include "child.h"
#include "execute.h"
#include "stdlib.h"


//*---------------------------------------------------------------------------------
//|   Macros and Defines
//*---------------------------------------------------------------------------------
#define  MAX_QUALIFIER     45
#define  MAX_OWNER         40
#define  MAX_NAME          40
#define  MAX_TYPE          40
#define  MAX_SPEC_VAL      128

#define LIST_ALL        0
#define LIST_TABLES     1
#define LIST_VIEWS      2        
#define  USER_SETCHECKSTATE         WM_USER + 1
#define  USER_SETBUTTONSTATE        WM_USER + 2
#define  USER_RESETLIST             WM_USER + 3
#define  USER_SETSTATES             WM_USER + 4
#define  USER_SETDEFAULTS           WM_USER + 5

#define  IDE_QUALIFIER     151
#define  IDE_OWNER         153
#define  IDE_NAME          155
#define  IDL_LIST          157
#define  IDX_ALL           158
#define  IDX_TABLES        159
#define  IDX_VIEWS         160
#define  IDL_PIPES         162
#define  LIST_WIDTH        184


#define SQL_FN_IDS_BASE 100

#define idsSQLAllocConnect      SQL_FN_IDS_BASE+1
#define idsSQLAllocEnv          SQL_FN_IDS_BASE+2
#define idsSQLAllocHandle       SQL_FN_IDS_BASE+3
#define idsSQLAllocStmt         SQL_FN_IDS_BASE+4
#define idsSQLBindCol           SQL_FN_IDS_BASE+5
#define idsSQLBindParam         SQL_FN_IDS_BASE+6
#define idsSQLBindParameter     SQL_FN_IDS_BASE+7
#define idsSQLBrowseConnect     SQL_FN_IDS_BASE+8
#define idsSQLBulkOperations    SQL_FN_IDS_BASE+9
#define idsSQLCancel            SQL_FN_IDS_BASE+10
#define idsSQLCloseCursor       SQL_FN_IDS_BASE+11
#define idsSQLColAttribute      SQL_FN_IDS_BASE+12
#define idsSQLColAttributes     SQL_FN_IDS_BASE+13
#define idsSQLColumnPrivileges  SQL_FN_IDS_BASE+14
#define idsSQLColumns           SQL_FN_IDS_BASE+15
#define idsSQLConnect           SQL_FN_IDS_BASE+16
#define idsSQLCopyDesc          SQL_FN_IDS_BASE+17
#define idsSQLDataSources       SQL_FN_IDS_BASE+18
#define idsSQLDescribeCol       SQL_FN_IDS_BASE+19
#define idsSQLDescribeParam     SQL_FN_IDS_BASE+20
#define idsSQLDisconnect        SQL_FN_IDS_BASE+21
#define idsSQLDriverConnect     SQL_FN_IDS_BASE+22
#define idsSQLEndTran           SQL_FN_IDS_BASE+23
#define idsSQLError             SQL_FN_IDS_BASE+24
#define idsSQLExecDirect        SQL_FN_IDS_BASE+25
#define idsSQLExecute           SQL_FN_IDS_BASE+26
#define idsSQLExtendedFetch     SQL_FN_IDS_BASE+27
#define idsSQLFetch             SQL_FN_IDS_BASE+28
#define idsSQLFetchScroll       SQL_FN_IDS_BASE+29
#define idsSQLForeignKeys       SQL_FN_IDS_BASE+30
#define idsSQLFreeConnect       SQL_FN_IDS_BASE+31
#define idsSQLFreeEnv           SQL_FN_IDS_BASE+32
#define idsSQLFreeHandle        SQL_FN_IDS_BASE+33
#define idsSQLFreeStmt          SQL_FN_IDS_BASE+34
#define idsSQLGetConnectAttr    SQL_FN_IDS_BASE+35
#define idsSQLGetConnectOption  SQL_FN_IDS_BASE+36
#define idsSQLGetCursorName     SQL_FN_IDS_BASE+37
#define idsSQLGetData           SQL_FN_IDS_BASE+38
#define idsSQLGetDescField      SQL_FN_IDS_BASE+39
#define idsSQLGetDescRec        SQL_FN_IDS_BASE+40
#define idsSQLGetDiagField      SQL_FN_IDS_BASE+41
#define idsSQLGetDiagRec        SQL_FN_IDS_BASE+42
#define idsSQLGetEnvAttr        SQL_FN_IDS_BASE+43
#define idsSQLGetFunctions      SQL_FN_IDS_BASE+44
#define idsSQLGetInfo           SQL_FN_IDS_BASE+45
#define idsSQLGetStmtAttr       SQL_FN_IDS_BASE+46
#define idsSQLGetStmtOption     SQL_FN_IDS_BASE+47
#define idsSQLGetTypeInfo       SQL_FN_IDS_BASE+48
#define idsSQLMoreResults       SQL_FN_IDS_BASE+49
#define idsSQLNativeSQL         SQL_FN_IDS_BASE+50
#define idsSQLNumParams         SQL_FN_IDS_BASE+51
#define idsSQLNumResultCols     SQL_FN_IDS_BASE+52
#define idsSQLParamOptions      SQL_FN_IDS_BASE+53
#define idsSQLPrepare           SQL_FN_IDS_BASE+54
#define idsSQLPrimaryKeys       SQL_FN_IDS_BASE+55
#define idsSQLProcedureColumns  SQL_FN_IDS_BASE+56
#define idsSQLProcedures        SQL_FN_IDS_BASE+57
#define idsSQLPutData           SQL_FN_IDS_BASE+58
#define idsSQLRowCount          SQL_FN_IDS_BASE+59
#define idsSQLSetConnectAttr    SQL_FN_IDS_BASE+60
#define idsSQLSetConnectOption  SQL_FN_IDS_BASE+61
#define idsSQLSetCursorName     SQL_FN_IDS_BASE+62
#define idsSQLSetDescField      SQL_FN_IDS_BASE+63
#define idsSQLSetDescRec        SQL_FN_IDS_BASE+64
#define idsSQLSetEnvAttr        SQL_FN_IDS_BASE+65
#define idsSQLSetParam          SQL_FN_IDS_BASE+66
#define idsSQLSetPos            SQL_FN_IDS_BASE+67
#define idsSQLSetScrollOptions  SQL_FN_IDS_BASE+68
#define idsSQLSetStmtAttr       SQL_FN_IDS_BASE+69
#define idsSQLSetStmtOption     SQL_FN_IDS_BASE+70
#define idsSQLSpecialColumns    SQL_FN_IDS_BASE+71
#define idsSQLStatistics        SQL_FN_IDS_BASE+72
#define idsSQLTablePrivileges   SQL_FN_IDS_BASE+73
#define idsSQLTables            SQL_FN_IDS_BASE+74
#define idsSQLTransact          SQL_FN_IDS_BASE+75



#define IDD_EDIT_PIPE                             700
#define IDC_NAME                                  701
#define IDB_NEW                                   702
#define IDB_DELETE                                703
#define IDE_SQL                                   704
#define IDR_VALUE                                 705
#define IDR_ADDRESS                               706
#define IDE_PARMS                                 707
#define IDX_DELETE                                708

#define IDD_NEW_PIPE                              730
#define IDD_DO_PIPE                               750


//*---------------------------------------------------------------------------------
//|   Global variables
//*---------------------------------------------------------------------------------
extern dCSEG(char) szResultsClass[];
extern dCSEG(char) szODBCFunctions[];

//*---------------------------------------------------------------------------------
//|   Function prototypes
//*---------------------------------------------------------------------------------
void EditPipe(CHILDINFO FAR * ci);
BOOL DisplayGetInfo(CHILDINFO FAR * ci);
BOOL DisplayODBCFunctions(CHILDINFO FAR * ci);
BOOL DisplayODBCDataSources(CHILDINFO FAR * ci);
BOOL DisplayODBCDataTypes(CHILDINFO FAR * ci);
void INTFUN HandlePipe(lpCHILDINFO lpci, lpRESULTSINFO lpri);



#endif
