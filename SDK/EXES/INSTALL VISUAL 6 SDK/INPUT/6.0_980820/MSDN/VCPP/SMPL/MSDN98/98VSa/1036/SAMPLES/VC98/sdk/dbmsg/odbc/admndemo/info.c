//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   INFO.C
//|      This module contains the functions which handle the Info menu items.
//|         This module relies on RESULTS and EXECUTE to 
//|      This file contains the actual code to execute SQL Statements and
//|         display them.  This file is dependent on the SA Tool data structures
//|         and the independent module RESULTS.
//|
//|      NOTE:  Due to the timing of this sample, only the 1.0 GetInfo constants
//|         are shown.  To see all GetInfo constants for a 2.0 driver, use the
//|         ODBC Test Tool which comes with this SDK.
//*---------------------------------------------------------------------------------
#include "info.h"
#include "ini.h"
#include "sql.h"
#include "sqlext.h"
#include "stdlib.h"
#include "strings.h"
VSZFile;

//*---------------------------------------------------------------------------------
//|   Defines and macros
//*---------------------------------------------------------------------------------
#define MAXNAME            35
#define MAXPARMS           18
#define MAXSQL             300

#define szCOMMA            ","
#define szBLANK            " "

typedef struct tagNEWPIPE {
   HWND        hwnd;
   HINSTANCE   hInst;
   char        szName[MAXNAME];
   BOOL        fSuccess;
} NEWPIPE;

//*---------------------------------------------------------------------------------
//|   Local Function Prototypes
//*---------------------------------------------------------------------------------
BOOL EXTFUN EditPipeWndProc(HWND hDlg, unsigned msg, WPARAM wParam, LPARAM lParam);
void NewPipe(NEWPIPE FAR * np);
BOOL EXTFUN NewPipeWndProc(HWND hDlg, unsigned msg, WPARAM wParam, LPARAM lParam);
BOOL EXTFUN DoPipeWndProc(HWND hDlg, unsigned msg, WPARAM wParam, LPARAM lParam);
void DoPipe(RESULTSSET FAR * rs, CHILDINFO FAR * ci, LPSTR szPipeName,
         int FAR xPipes[], int cbCnt);
void DoPipeByValue(RESULTSSET FAR * rs, CHILDINFO FAR * ci, LPSTR sqlpsql,
      LPSTR szparms, int FAR xPipes[], int cbCnt, LPSTR szPipeName);
void PrepareParmList(LPSTR str);
SDWORD RefreshList(HWND hDlg, RESULTSSET FAR * rs, CHILDINFO FAR * ci, int state, 
         LPSTR szQual, LPSTR szOwner, LPSTR szName, int cbCols);
SDWORD RefreshPipeList(HWND hDlg);


//*---------------------------------------------------------------------------------
//|   Global variables
//*---------------------------------------------------------------------------------
extern dCSEG(char) szMSSansSerif[];
extern dCSEG(char) szPIPES[];
extern dCSEG(char) szFONT[];
extern char        OutStr[MAXBUFF];
extern dCSEG(char) szVALUE[];

dCSEG(char) szISO92[]            =  "ISO 92";
dCSEG(char) szXOpen[]            =  "X/Open";
dCSEG(char) szODBC[]             =  "ODBC";
dCSEG(char) szDepr[]             =  "Deprecated";

dCSEG(char) szCore[]             =  "Core";
dCSEG(char) szLvl1[]             =  "Level 1";
dCSEG(char) szLvl2[]             =  "Level 2";

dCSEG(char) szYes[]              =  "Yes";
dCSEG(char) szNo[]               =  "No";

dCSEG(char) szODBCFunctions[]    =  "Functions";
dCSEG(char) szODBCDataSources[]  =  "Data Sources";
dCSEG(char) szODBCDataTypes[]    =  "Data Types";
dCSEG(char) szGetInfoTitle[]     =  "Get Info";
dCSEG(char) szQualifier[]        =  "Qualifier";
dCSEG(char) szOwner[]            =  "Owner";
dCSEG(char) szName[]             =  "Name";
dCSEG(char) szType[]             =  "Type";
dCSEG(char) szSQL[]              =  "Sql";
dCSEG(char) szPARMS[]            =  "Parms";
dCSEG(char) szPARMOPT[]          =  "ParmOpt";
dCSEG(char) szDELETEOPT[]        =  "Delete";
dCSEG(char) szBothTypes[]        =  "'%s','%s'";
dCSEG(char) szOneType[]          =  "'%s'";
dCSEG(char) szBlank[]            =  " ";
dCSEG(char) szTABLETYPE[]        =  "TABLE";
dCSEG(char) szVIEWTYPE[]         =  "VIEW";
dCSEG(char) szVALUE[]            =  "value";
dCSEG(char) szADDRESS[]          =  "address";
dCSEG(char) szDeletePipe[]       =  "Delete pipe %s?";
dCSEG(char) szEditPipe[]         =  "Edit Pipe";
dCSEG(char) szDuplicatePipe[]    =  "Pipe already exists";
dCSEG(char) szInstalled[]        =  "Installed";
dCSEG(char) szDROPPROCSEMI[]     =  "Drop Procedure (with semi-colon)";

static char szErrorMsgTitle[]    =  "Error";



struct {
   UWORD          fFunction;                 // Identifier for SQLGetFunctions
   LPSTR          szLevel;                   // Conformance Level
   int            idFunction;                // String table identifier for function name
   } ODBCFunctions[] = {

// fFunction                        szLevel           idFunction
// -------------------------------  ---------------   --------------------------------

// ---- ISO 92 Conformance -----------------------------------
   {SQL_API_SQLALLOCHANDLE,          (LPSTR)szISO92,    idsSQLAllocHandle},
   {SQL_API_SQLBINDCOL,              (LPSTR)szISO92,    idsSQLBindCol},
   {SQL_API_SQLCANCEL,               (LPSTR)szISO92,    idsSQLCancel},
   {SQL_API_SQLCLOSECURSOR,          (LPSTR)szISO92,    idsSQLCloseCursor},
   {SQL_API_SQLCOLATTRIBUTE,         (LPSTR)szISO92,    idsSQLColAttribute},
   {SQL_API_SQLCONNECT,              (LPSTR)szISO92,    idsSQLConnect},
   {SQL_API_SQLCOPYDESC,             (LPSTR)szISO92,    idsSQLCopyDesc},
   {SQL_API_SQLDATASOURCES,          (LPSTR)szISO92,    idsSQLDataSources},
   {SQL_API_SQLDESCRIBECOL,          (LPSTR)szISO92,    idsSQLDescribeCol},
   {SQL_API_SQLDISCONNECT,           (LPSTR)szISO92,    idsSQLDisconnect},
   {SQL_API_SQLENDTRAN,              (LPSTR)szISO92,    idsSQLEndTran},
   {SQL_API_SQLEXECDIRECT,           (LPSTR)szISO92,    idsSQLExecDirect},
   {SQL_API_SQLEXECUTE,              (LPSTR)szISO92,    idsSQLExecute},
   {SQL_API_SQLFETCH,                (LPSTR)szISO92,    idsSQLFetch},
   {SQL_API_SQLFETCHSCROLL,          (LPSTR)szISO92,    idsSQLFetchScroll},
   {SQL_API_SQLFREEHANDLE,           (LPSTR)szISO92,    idsSQLFreeHandle},
   {SQL_API_SQLFREESTMT,             (LPSTR)szISO92,    idsSQLFreeStmt},
   {SQL_API_SQLGETCONNECTATTR,       (LPSTR)szISO92,    idsSQLGetConnectAttr},
   {SQL_API_SQLGETCURSORNAME,        (LPSTR)szISO92,    idsSQLGetCursorName},
   {SQL_API_SQLGETDATA,              (LPSTR)szISO92,    idsSQLGetData},
   {SQL_API_SQLGETDESCFIELD,         (LPSTR)szISO92,    idsSQLGetDescField},
   {SQL_API_SQLGETDESCREC,           (LPSTR)szISO92,    idsSQLGetDescRec},
   {SQL_API_SQLGETDIAGFIELD,         (LPSTR)szISO92,    idsSQLGetDiagField},
   {SQL_API_SQLGETDIAGREC,           (LPSTR)szISO92,    idsSQLGetDiagRec},
   {SQL_API_SQLGETFUNCTIONS,         (LPSTR)szISO92,    idsSQLGetFunctions},
   {SQL_API_SQLGETINFO,              (LPSTR)szISO92,    idsSQLGetInfo},
   {SQL_API_SQLGETSTMTATTR,          (LPSTR)szISO92,    idsSQLGetStmtAttr},
   {SQL_API_SQLGETTYPEINFO,          (LPSTR)szISO92,    idsSQLGetTypeInfo},
   {SQL_API_SQLGETSTMTATTR,          (LPSTR)szISO92,    idsSQLGetStmtAttr},
   {SQL_API_SQLNUMRESULTCOLS,        (LPSTR)szISO92,    idsSQLNumResultCols},
   {SQL_API_SQLPREPARE,              (LPSTR)szISO92,    idsSQLPrepare},
   {SQL_API_SQLPUTDATA,              (LPSTR)szISO92,    idsSQLPutData},
   {SQL_API_SQLROWCOUNT,             (LPSTR)szISO92,    idsSQLRowCount},
   {SQL_API_SQLSETCONNECTATTR,       (LPSTR)szISO92,    idsSQLGetConnectAttr},
   {SQL_API_SQLSETCURSORNAME,        (LPSTR)szISO92,    idsSQLSetCursorName},
   {SQL_API_SQLSETDESCFIELD,         (LPSTR)szISO92,    idsSQLSetDescField},
   {SQL_API_SQLSETDESCREC,           (LPSTR)szISO92,    idsSQLSetDescRec},
   {SQL_API_SQLSETENVATTR,           (LPSTR)szISO92,    idsSQLSetEnvAttr},
   {SQL_API_SQLSETSTMTATTR,          (LPSTR)szISO92,    idsSQLSetStmtAttr},

   //---- X/Open Conformance -----------------------------------  
   {SQL_API_SQLCOLUMNS,              (LPSTR)szXOpen,   idsSQLColumns},
   {SQL_API_SQLGETENVATTR,           (LPSTR)szXOpen,   idsSQLGetEnvAttr},
   {SQL_API_SQLSPECIALCOLUMNS,       (LPSTR)szXOpen,   idsSQLSpecialColumns},
   {SQL_API_SQLSTATISTICS,           (LPSTR)szXOpen,   idsSQLStatistics},
   {SQL_API_SQLTABLES,               (LPSTR)szXOpen,   idsSQLTables},

   //---- ODBC Conformance -------------------------------------
   {SQL_API_SQLBINDPARAMETER,        (LPSTR)szODBC,    idsSQLBindParameter},
   {SQL_API_SQLBROWSECONNECT,        (LPSTR)szODBC,    idsSQLBrowseConnect},
   {SQL_API_SQLBULKOPERATIONS,       (LPSTR)szODBC,    idsSQLBulkOperations},
   {SQL_API_SQLCOLUMNPRIVILEGES,     (LPSTR)szODBC,    idsSQLColumnPrivileges},
   {SQL_API_SQLDESCRIBEPARAM,        (LPSTR)szODBC,    idsSQLDescribeParam},
   {SQL_API_SQLDRIVERCONNECT,        (LPSTR)szODBC,    idsSQLDriverConnect},
   {SQL_API_SQLFOREIGNKEYS,          (LPSTR)szODBC,    idsSQLForeignKeys},
   {SQL_API_SQLMORERESULTS,          (LPSTR)szODBC,    idsSQLMoreResults},
   {SQL_API_SQLNATIVESQL,            (LPSTR)szODBC,    idsSQLNativeSQL},
   {SQL_API_SQLNUMPARAMS,            (LPSTR)szODBC,    idsSQLNumParams},
   {SQL_API_SQLPRIMARYKEYS,          (LPSTR)szODBC,    idsSQLPrimaryKeys},
   {SQL_API_SQLPROCEDURECOLUMNS,     (LPSTR)szODBC,    idsSQLProcedureColumns},
   {SQL_API_SQLPROCEDURES,           (LPSTR)szODBC,    idsSQLProcedures},
   {SQL_API_SQLSETPOS,               (LPSTR)szODBC,    idsSQLSetPos},
   {SQL_API_SQLTABLEPRIVILEGES,      (LPSTR)szODBC,    idsSQLTablePrivileges},

   //---- Deprecated ----------------------------------------
   {SQL_API_SQLALLOCCONNECT,         (LPSTR)szDepr,    idsSQLAllocConnect},
   {SQL_API_SQLALLOCENV,             (LPSTR)szDepr,    idsSQLAllocEnv},
   {SQL_API_SQLALLOCSTMT,            (LPSTR)szDepr,    idsSQLAllocStmt},
   {SQL_API_SQLBINDPARAM,            (LPSTR)szDepr,    idsSQLBindParam},
   {SQL_API_SQLCOLATTRIBUTES,        (LPSTR)szDepr,    idsSQLColAttributes},
   {SQL_API_SQLERROR,                (LPSTR)szDepr,    idsSQLError},
   {SQL_API_SQLEXTENDEDFETCH,        (LPSTR)szDepr,    idsSQLExtendedFetch},
   {SQL_API_SQLFREECONNECT,          (LPSTR)szDepr,    idsSQLFreeConnect},
   {SQL_API_SQLFREEENV,              (LPSTR)szDepr,    idsSQLFreeEnv},
   {SQL_API_SQLGETCONNECTOPTION,     (LPSTR)szDepr,    idsSQLGetConnectOption},
   {SQL_API_SQLGETSTMTOPTION,        (LPSTR)szDepr,    idsSQLGetStmtOption},
   {SQL_API_SQLPARAMOPTIONS,         (LPSTR)szDepr,    idsSQLParamOptions},
   {SQL_API_SQLSETCONNECTOPTION,     (LPSTR)szDepr,    idsSQLSetConnectOption},
   {SQL_API_SQLSETPARAM,             (LPSTR)szDepr,    idsSQLSetParam},
   {SQL_API_SQLSETSCROLLOPTIONS,     (LPSTR)szDepr,    idsSQLSetScrollOptions},
   {SQL_API_SQLSETSTMTOPTION,        (LPSTR)szDepr,    idsSQLSetStmtOption},
   {SQL_API_SQLTRANSACT,             (LPSTR)szDepr,    idsSQLTransact},
   };


//
// Generic prototype for bitmap and value lists
// 
// This structure is used for to locate both bitmap and enumeration values.
// Values may appear in the list in any order.  If a value is aliased, the
// second value in an enumeration list will not be found; however, a bitmap
// entry would show both aliases as being set.
//
typedef struct tagINFOSTRUCT {
   UDWORD         fVal;                      // Which constant
   LPSTR          szStr;                     // Print String
   } INFOSTRUCT;
typedef INFOSTRUCT FAR * lpINFOSTRUCT;

//
// This macro is used to build rows of the INFOSTRUCT arrays
// guaranteeing that the "print" string is the same as the
// INFO manifest constant.
//
#define INFO_VALUE_ROW(tag) {tag, #tag}



//
// Structure for SQL_ALTER_DOMAIN
//
static INFOSTRUCT GetInfoAlterDomain[] = {
INFO_VALUE_ROW( SQL_AD_ADD_DOMAIN_CONSTRAINT               ),
INFO_VALUE_ROW( SQL_AD_DROP_DOMAIN_CONSTRAINT              ),
INFO_VALUE_ROW( SQL_AD_ADD_DOMAIN_DEFAULT                  ),
INFO_VALUE_ROW( SQL_AD_DROP_DOMAIN_DEFAULT                 ),
INFO_VALUE_ROW( SQL_AD_ADD_CONSTRAINT_INITIALLY_DEFERRED   ),
INFO_VALUE_ROW( SQL_AD_ADD_CONSTRAINT_INITIALLY_IMMEDIATE  ),
INFO_VALUE_ROW( SQL_AD_ADD_CONSTRAINT_DEFERRABLE           ),
INFO_VALUE_ROW( SQL_AD_ADD_CONSTRAINT_NON_DEFERRABLE       ),
};

//
// Structure for SQL_ALTER_TABLE
//
static INFOSTRUCT GetInfoAlterTable[] = {
INFO_VALUE_ROW( SQL_AT_ADD_COLUMN_SINGLE                   ),
INFO_VALUE_ROW( SQL_AT_ADD_CONSTRAINT                      ),
INFO_VALUE_ROW( SQL_AT_ADD_COLUMN_DEFAULT                  ),
INFO_VALUE_ROW( SQL_AT_ADD_COLUMN_COLLATION                ),
INFO_VALUE_ROW( SQL_AT_SET_COLUMN_DEFAULT                  ),
INFO_VALUE_ROW( SQL_AT_DROP_COLUMN_DEFAULT                 ),
INFO_VALUE_ROW( SQL_AT_DROP_COLUMN_CASCADE                 ),
INFO_VALUE_ROW( SQL_AT_DROP_COLUMN_RESTRICT                ),
INFO_VALUE_ROW( SQL_AT_ADD_TABLE_CONSTRAINT                ),
INFO_VALUE_ROW( SQL_AT_DROP_TABLE_CONSTRAINT_CASCADE       ),
INFO_VALUE_ROW( SQL_AT_DROP_TABLE_CONSTRAINT_RESTRICT      ),
INFO_VALUE_ROW( SQL_AT_CONSTRAINT_NAME_DEFINITION          ),
INFO_VALUE_ROW( SQL_AT_CONSTRAINT_INITIALLY_DEFERRED       ),
INFO_VALUE_ROW( SQL_AT_CONSTRAINT_INITIALLY_IMMEDIATE      ),
INFO_VALUE_ROW( SQL_AT_CONSTRAINT_DEFERRABLE               ),
INFO_VALUE_ROW( SQL_AT_CONSTRAINT_NON_DEFERRABLE           ),
};

//
// Structure for SQL_ANSI_ASYNC_MODE
//
static INFOSTRUCT GetInfoAsyncMode[] = {
INFO_VALUE_ROW( SQL_AM_NONE                                ),
INFO_VALUE_ROW( SQL_AM_CONNECTION                          ),
INFO_VALUE_ROW( SQL_AM_STATEMENT                           ),
};



//
// Structure for SQL_BATCH_ROW_COUNT
//
static INFOSTRUCT GetInfoBatchRowCount[] = {
INFO_VALUE_ROW( SQL_BRC_ROLLED_UP                          ),
INFO_VALUE_ROW( SQL_BRC_PROCEDURES                         ),
INFO_VALUE_ROW( SQL_BRC_EXPLICIT                           ),
};

//
// Structure for SQL_BATCH_SUPPORT
//
static INFOSTRUCT GetInfoBatchSupport[] = {
INFO_VALUE_ROW( SQL_BS_SELECT_EXPLICIT                     ),
INFO_VALUE_ROW( SQL_BS_ROW_COUNT_EXPLICIT                  ),
INFO_VALUE_ROW( SQL_BS_SELECT_PROC                         ),
INFO_VALUE_ROW( SQL_BS_ROW_COUNT_PROC                      ),
};

//
// Structure for SQL_BOOKMARK_PERSISTENCE
//
static INFOSTRUCT GetInfoBookmarkPersist[] = {
INFO_VALUE_ROW( SQL_BP_CLOSE                               ),
INFO_VALUE_ROW( SQL_BP_DELETE                              ),
INFO_VALUE_ROW( SQL_BP_DROP                                ),
INFO_VALUE_ROW( SQL_BP_TRANSACTION                         ),
INFO_VALUE_ROW( SQL_BP_UPDATE                              ),
INFO_VALUE_ROW( SQL_BP_OTHER_HSTMT                         ),
};

//
// Structure for SQL_CATALOG_LOCATION
//
static INFOSTRUCT GetInfoCatLocation[] = {
INFO_VALUE_ROW( SQL_CL_START                               ),
INFO_VALUE_ROW( SQL_CL_END                                 ),
};



//
// Structure for SQL_CATALOG_USAGE
//
static INFOSTRUCT GetInfoCatUsage[] = {
INFO_VALUE_ROW( SQL_CU_DML_STATEMENTS                      ),
INFO_VALUE_ROW( SQL_CU_PROCEDURE_INVOCATION                ),
INFO_VALUE_ROW( SQL_CU_TABLE_DEFINITION                    ),
INFO_VALUE_ROW( SQL_CU_INDEX_DEFINITION                    ),
INFO_VALUE_ROW( SQL_CU_PRIVILEGE_DEFINITION                ),
};

//
// Structure for SQL_CONCAT_NULL_BEHAVIOR
//
static INFOSTRUCT GetInfoConcat[] = {
INFO_VALUE_ROW( SQL_CB_NULL                                ),
INFO_VALUE_ROW( SQL_CB_NON_NULL                            ),
};

//
// Structure for SQL_CONVERT_xxxx
//
static INFOSTRUCT GetInfoConvertTypes[] = {
INFO_VALUE_ROW( SQL_CVT_BIGINT                             ),
INFO_VALUE_ROW( SQL_CVT_BINARY                             ),
INFO_VALUE_ROW( SQL_CVT_BIT                                ),
INFO_VALUE_ROW( SQL_CVT_CHAR                               ),
INFO_VALUE_ROW( SQL_CVT_DATE                               ),
INFO_VALUE_ROW( SQL_CVT_DECIMAL                            ),
INFO_VALUE_ROW( SQL_CVT_DOUBLE                             ),
INFO_VALUE_ROW( SQL_CVT_FLOAT                              ),
INFO_VALUE_ROW( SQL_CVT_INTEGER                            ),
INFO_VALUE_ROW( SQL_CVT_INTERVAL_YEAR_MONTH                ),
INFO_VALUE_ROW( SQL_CVT_INTERVAL_DAY_TIME                  ),
INFO_VALUE_ROW( SQL_CVT_LONGVARBINARY                      ),
INFO_VALUE_ROW( SQL_CVT_LONGVARCHAR                        ),
INFO_VALUE_ROW( SQL_CVT_NUMERIC                            ),
INFO_VALUE_ROW( SQL_CVT_REAL                               ),
INFO_VALUE_ROW( SQL_CVT_SMALLINT                           ),
INFO_VALUE_ROW( SQL_CVT_TIME                               ),
INFO_VALUE_ROW( SQL_CVT_TIMESTAMP                          ),
INFO_VALUE_ROW( SQL_CVT_TINYINT                            ),
INFO_VALUE_ROW( SQL_CVT_VARBINARY                          ),
INFO_VALUE_ROW( SQL_CVT_VARCHAR                            ),
INFO_VALUE_ROW( SQL_CVT_WCHAR                              ),
INFO_VALUE_ROW( SQL_CVT_WLONGVARCHAR                       ),
INFO_VALUE_ROW( SQL_CVT_WVARCHAR                           ),
};

//
// Structure for SQL_CONVERT_FUNCTIONS
//
static INFOSTRUCT GetInfoConvertFunctions[] = {
INFO_VALUE_ROW( SQL_FN_CVT_CAST                            ),
INFO_VALUE_ROW( SQL_FN_CVT_CONVERT                         ),
};

//
// Structure for SQL_CORRELATION_NAME
//
static INFOSTRUCT GetInfoCorrelationName[] = {
INFO_VALUE_ROW( SQL_CN_NONE                                ),
INFO_VALUE_ROW( SQL_CN_DIFFERENT                           ),
INFO_VALUE_ROW( SQL_CN_ANY                                 ),
};

//
// Structure for SQL_CREATE_ASSERTION
//
static INFOSTRUCT GetInfoCreateAssertion[] = {
INFO_VALUE_ROW( SQL_CA_CREATE_ASSERTION                    ),
INFO_VALUE_ROW( SQL_CA_CONSTRAINT_INITIALLY_DEFERRED       ),
INFO_VALUE_ROW( SQL_CA_CONSTRAINT_INITIALLY_IMMEDIATE      ),
INFO_VALUE_ROW( SQL_CA_CONSTRAINT_DEFERRABLE               ),
INFO_VALUE_ROW( SQL_CA_CONSTRAINT_NON_DEFERRABLE           ),
};

//
// Structure for SQL_CREATE_CHARACTER_SET
//
static INFOSTRUCT GetInfoCreateCharset[] = {
INFO_VALUE_ROW( SQL_CCS_CREATE_CHARACTER_SET               ),
INFO_VALUE_ROW( SQL_CCS_COLLATE_CLAUSE                     ),
INFO_VALUE_ROW( SQL_CCS_LIMITED_COLLATION                  ),
};

//
// Structure for SQL_CREATE_COLLATION
//
static INFOSTRUCT GetInfoCreateCollation[] = {
INFO_VALUE_ROW( SQL_CCOL_CREATE_COLLATION                  ),
};

//
// Structure for SQL_CREATE_DOMAIN
//
static INFOSTRUCT GetInfoCreateDomain[] = {
INFO_VALUE_ROW( SQL_CDO_CREATE_DOMAIN                      ),
INFO_VALUE_ROW( SQL_CDO_CONSTRAINT                         ),
INFO_VALUE_ROW( SQL_CDO_DEFAULT                            ),
INFO_VALUE_ROW( SQL_CDO_COLLATION                          ),
INFO_VALUE_ROW( SQL_CDO_CONSTRAINT_NAME_DEFINITION         ),
INFO_VALUE_ROW( SQL_CDO_CONSTRAINT_INITIALLY_DEFERRED      ),
INFO_VALUE_ROW( SQL_CDO_CONSTRAINT_INITIALLY_IMMEDIATE     ),
INFO_VALUE_ROW( SQL_CDO_CONSTRAINT_DEFERRABLE              ),
INFO_VALUE_ROW( SQL_CDO_CONSTRAINT_NON_DEFERRABLE          ),
};

//
// Structure for SQL_CREATE_SCHEMA
//
static INFOSTRUCT GetInfoCreateSchema[] = {
INFO_VALUE_ROW( SQL_CS_CREATE_SCHEMA                       ),
INFO_VALUE_ROW( SQL_CS_AUTHORIZATION                       ),
INFO_VALUE_ROW( SQL_CS_DEFAULT_CHARACTER_SET               ),
};

//
// Structure for SQL_CREATE_TABLE
//
static INFOSTRUCT GetInfoCreateTable[] = {
INFO_VALUE_ROW( SQL_CT_COMMIT_PRESERVE                     ),
INFO_VALUE_ROW( SQL_CT_COMMIT_DELETE                       ),
INFO_VALUE_ROW( SQL_CT_GLOBAL_TEMPORARY                    ),
INFO_VALUE_ROW( SQL_CT_LOCAL_TEMPORARY                     ),
INFO_VALUE_ROW( SQL_CT_CONSTRAINT_INITIALLY_DEFERRED       ),
INFO_VALUE_ROW( SQL_CT_CONSTRAINT_INITIALLY_IMMEDIATE      ),
INFO_VALUE_ROW( SQL_CT_CONSTRAINT_DEFERRABLE               ),
INFO_VALUE_ROW( SQL_CT_CONSTRAINT_NON_DEFERRABLE           ),
};

//
// Structure for SQL_CREATE_TRANSLATION
//
static INFOSTRUCT GetInfoCreateXlation[] = {
INFO_VALUE_ROW( SQL_CTR_CREATE_TRANSLATION                 ),
};

//
// Structure for SQL_CREATE_VIEW
//
static INFOSTRUCT GetInfoCreateView[] = {
INFO_VALUE_ROW( SQL_CV_CREATE_VIEW                         ),
INFO_VALUE_ROW( SQL_CV_CHECK_OPTION                        ),
INFO_VALUE_ROW( SQL_CV_CASCADED                            ),
INFO_VALUE_ROW( SQL_CV_LOCAL                               ),
};

//
// Structure for SQL_CURSOR_COMMIT_BEHAVIOR,
//               SQL_CURSOR_ROLLBACK_BEHAVIOR
//
static INFOSTRUCT GetInfoCommit[] = {
INFO_VALUE_ROW( SQL_CB_DELETE                              ),
INFO_VALUE_ROW( SQL_CB_CLOSE                               ),
INFO_VALUE_ROW( SQL_CB_PRESERVE                            ),
};

//
// Structure for SQL_CURSOR_SENSITIVITY
//
static INFOSTRUCT GetInfoCursorSensitiv[] = {
INFO_VALUE_ROW( SQL_INSENSITIVE                            ),
INFO_VALUE_ROW( SQL_UNSPECIFIED                            ),
INFO_VALUE_ROW( SQL_SENSITIVE                              ),
};

//
// Structure for SQL_DEFAULT_TXN_ISOLATION
//
static INFOSTRUCT GetInfoTXNIsolation[] = {
INFO_VALUE_ROW( SQL_TXN_READ_UNCOMMITTED                   ),
INFO_VALUE_ROW( SQL_TXN_READ_COMMITTED                     ),
INFO_VALUE_ROW( SQL_TXN_REPEATABLE_READ                    ),
INFO_VALUE_ROW( SQL_TXN_SERIALIZABLE                       ),
};

//
// Structure for SQL_*_CURSOR_ATTRIBUTES1
//
static INFOSTRUCT GetInfoCurAttrs1[] = {
INFO_VALUE_ROW( SQL_CA1_NEXT                               ),
INFO_VALUE_ROW( SQL_CA1_ABSOLUTE                           ),
INFO_VALUE_ROW( SQL_CA1_RELATIVE                           ),
INFO_VALUE_ROW( SQL_CA1_BOOKMARK                           ),
INFO_VALUE_ROW( SQL_CA1_LOCK_NO_CHANGE                     ),
INFO_VALUE_ROW( SQL_CA1_LOCK_UNLOCK                        ),
INFO_VALUE_ROW( SQL_CA1_POS_POSITION                       ),
INFO_VALUE_ROW( SQL_CA1_POS_UPDATE                         ),
INFO_VALUE_ROW( SQL_CA1_POS_DELETE                         ),
INFO_VALUE_ROW( SQL_CA1_POS_REFRESH                        ),
INFO_VALUE_ROW( SQL_CA1_POSITIONED_UPDATE                  ),
INFO_VALUE_ROW( SQL_CA1_POSITIONED_DELETE                  ),
INFO_VALUE_ROW( SQL_CA1_SELECT_FOR_UPDATE                  ),
INFO_VALUE_ROW( SQL_CA1_BULK_ADD                           ),
INFO_VALUE_ROW( SQL_CA1_BULK_UPDATE_BY_BOOKMARK            ),
INFO_VALUE_ROW( SQL_CA1_BULK_DELETE_BY_BOOKMARK            ),
INFO_VALUE_ROW( SQL_CA1_BULK_FETCH_BY_BOOKMARK             ),
};

//
// Structure for SQL_*_CURSOR_ATTRIBUTES2
//
static INFOSTRUCT GetInfoCurAttrs2[] = {
INFO_VALUE_ROW( SQL_CA2_READ_ONLY_CONCURRENCY              ),
INFO_VALUE_ROW( SQL_CA2_LOCK_CONCURRENCY                   ),
INFO_VALUE_ROW( SQL_CA2_OPT_ROWVER_CONCURRENCY             ),
INFO_VALUE_ROW( SQL_CA2_OPT_VALUES_CONCURRENCY             ),
INFO_VALUE_ROW( SQL_CA2_SENSITIVITY_ADDITIONS              ),
INFO_VALUE_ROW( SQL_CA2_SENSITIVITY_DELETIONS              ),
INFO_VALUE_ROW( SQL_CA2_SENSITIVITY_UPDATES                ),
INFO_VALUE_ROW( SQL_CA2_MAX_ROWS_SELECT                    ),
INFO_VALUE_ROW( SQL_CA2_MAX_ROWS_INSERT                    ),
INFO_VALUE_ROW( SQL_CA2_MAX_ROWS_UPDATE                    ),
INFO_VALUE_ROW( SQL_CA2_MAX_ROWS_DELETE                    ),
INFO_VALUE_ROW( SQL_CA2_MAX_ROWS_CATALOG                   ),
INFO_VALUE_ROW( SQL_CA2_MAX_ROWS_AFFECTS_ALL               ),
INFO_VALUE_ROW( SQL_CA2_CRC_EXACT                          ),
INFO_VALUE_ROW( SQL_CA2_CRC_APPROXIMATE                    ),
INFO_VALUE_ROW( SQL_CA2_SIMULATE_NON_UNIQUE                ),
INFO_VALUE_ROW( SQL_CA2_SIMULATE_TRY_UNIQUE                ),
INFO_VALUE_ROW( SQL_CA2_SIMULATE_UNIQUE                    ),
};

//
// Structure for SQL_DATETIME_LITERALS
//
static INFOSTRUCT GetInfoSQLDateLit[] = {
INFO_VALUE_ROW( SQL_DL_SQL92_DATE                          ),
INFO_VALUE_ROW( SQL_DL_SQL92_TIME                          ),
INFO_VALUE_ROW( SQL_DL_SQL92_TIMESTAMP                     ),
INFO_VALUE_ROW( SQL_DL_SQL92_INTERVAL_YEAR                 ),
INFO_VALUE_ROW( SQL_DL_SQL92_INTERVAL_MONTH                ),
INFO_VALUE_ROW( SQL_DL_SQL92_INTERVAL_DAY                  ),
INFO_VALUE_ROW( SQL_DL_SQL92_INTERVAL_HOUR                 ),
INFO_VALUE_ROW( SQL_DL_SQL92_INTERVAL_MINUTE               ),
INFO_VALUE_ROW( SQL_DL_SQL92_INTERVAL_SECOND               ),
INFO_VALUE_ROW( SQL_DL_SQL92_INTERVAL_YEAR_TO_MONTH        ),
INFO_VALUE_ROW( SQL_DL_SQL92_INTERVAL_DAY_TO_HOUR          ),
INFO_VALUE_ROW( SQL_DL_SQL92_INTERVAL_DAY_TO_MINUTE        ),
INFO_VALUE_ROW( SQL_DL_SQL92_INTERVAL_DAY_TO_SECOND        ),
INFO_VALUE_ROW( SQL_DL_SQL92_INTERVAL_HOUR_TO_MINUTE       ),
INFO_VALUE_ROW( SQL_DL_SQL92_INTERVAL_HOUR_TO_SECOND       ),
INFO_VALUE_ROW( SQL_DL_SQL92_INTERVAL_MINUTE_TO_SECOND     ),
};

//
// Structure for SQL_DROP_ASSERTION
//
static INFOSTRUCT GetInfoDropAssertion[] = {
INFO_VALUE_ROW( SQL_DA_DROP_ASSERTION                      ),
};

//
// Structure for SQL_DROP_CHARACTER_SET
//
static INFOSTRUCT GetInfoDropCharset[] = {
INFO_VALUE_ROW( SQL_DCS_DROP_CHARACTER_SET                 ),
};

//
// Structure for SQL_DROP_COLLATION
//
static INFOSTRUCT GetInfoDropCollation[] = {
INFO_VALUE_ROW( SQL_DC_DROP_COLLATION                      ),
};

//
// Structure for SQL_DROP_DOMAIN
//
static INFOSTRUCT GetInfoDropDomain[] = {
INFO_VALUE_ROW( SQL_DD_DROP_DOMAIN                         ),
INFO_VALUE_ROW( SQL_DD_CASCADE                             ),
INFO_VALUE_ROW( SQL_DD_RESTRICT                            ),
};

//
// Structure for SQL_DROP_SCHEMA
//
static INFOSTRUCT GetInfoDropSchema[] = {
INFO_VALUE_ROW( SQL_DS_DROP_SCHEMA                         ),
INFO_VALUE_ROW( SQL_DS_CASCADE                             ),
INFO_VALUE_ROW( SQL_DS_RESTRICT                            ),
};

//
// Structure for SQL_DROP_TABLE
//
static INFOSTRUCT GetInfoDropTable[] = {
INFO_VALUE_ROW( SQL_DT_DROP_TABLE                          ),
INFO_VALUE_ROW( SQL_DT_CASCADE                             ),
INFO_VALUE_ROW( SQL_DT_RESTRICT                            ),
};

//
// Structure for SQL_DROP_TRANSLATION
//
static INFOSTRUCT GetInfoDropXlation[] = {
INFO_VALUE_ROW( SQL_DTR_DROP_TRANSLATION                   ),
};

//
// Structure for SQL_DROP_VIEW
//
static INFOSTRUCT GetInfoDropView[] = {
INFO_VALUE_ROW( SQL_DV_DROP_VIEW                           ),
INFO_VALUE_ROW( SQL_DV_CASCADE                             ),
INFO_VALUE_ROW( SQL_DV_RESTRICT                            ),
};

//
// Structure for SQL_FILE_USAGE
//
static INFOSTRUCT GetInfoFileUsage[] = {
INFO_VALUE_ROW( SQL_FILE_NOT_SUPPORTED                     ),
INFO_VALUE_ROW( SQL_FILE_TABLE                             ),
INFO_VALUE_ROW( SQL_FILE_CATALOG                           ),
};

//
// Structure for SQL_GETDATA_EXTENSIONS
//
static INFOSTRUCT GetInfoGetdataExt[] = {
INFO_VALUE_ROW( SQL_GD_ANY_COLUMN                          ),
INFO_VALUE_ROW( SQL_GD_ANY_ORDER                           ),
INFO_VALUE_ROW( SQL_GD_BLOCK                               ),
INFO_VALUE_ROW( SQL_GD_BOUND                               ),
};

//
// Structure for SQL_GROUP_BY
//
static INFOSTRUCT GetInfoGroupBy[] = {
INFO_VALUE_ROW( SQL_GB_NOT_SUPPORTED                       ),
INFO_VALUE_ROW( SQL_GB_GROUP_BY_EQUALS_SELECT              ),
INFO_VALUE_ROW( SQL_GB_GROUP_BY_CONTAINS_SELECT            ),
INFO_VALUE_ROW( SQL_GB_NO_RELATION                         ),
INFO_VALUE_ROW( SQL_GB_COLLATE                             ),
};

//
// Structure for SQL_INDEX_KEYWORDS
//
static INFOSTRUCT GetInfoIndexKeywords[] = {
INFO_VALUE_ROW( SQL_IK_NONE                                ),
INFO_VALUE_ROW( SQL_IK_ASC                                 ),
INFO_VALUE_ROW( SQL_IK_DESC                                ),
INFO_VALUE_ROW( SQL_IK_ALL                                 ),
};

//
// Structure for SQL_INFO_SCHEMA_VIEWS
//
static INFOSTRUCT GetInfoInfoSchemaViews[] = {
INFO_VALUE_ROW( SQL_ISV_ASSERTIONS                         ),
INFO_VALUE_ROW( SQL_ISV_CHARACTER_SETS                     ),
INFO_VALUE_ROW( SQL_ISV_CHECK_CONSTRAINTS                  ),
INFO_VALUE_ROW( SQL_ISV_COLLATIONS                         ),
INFO_VALUE_ROW( SQL_ISV_COLUMN_DOMAIN_USAGE                ),
INFO_VALUE_ROW( SQL_ISV_COLUMN_PRIVILEGES                  ),
INFO_VALUE_ROW( SQL_ISV_COLUMNS                            ),
INFO_VALUE_ROW( SQL_ISV_CONSTRAINT_COLUMN_USAGE            ),
INFO_VALUE_ROW( SQL_ISV_CONSTRAINT_TABLE_USAGE             ),
INFO_VALUE_ROW( SQL_ISV_ASSERTIONS                         ),
INFO_VALUE_ROW( SQL_ISV_DOMAIN_CONSTRAINTS                 ),
INFO_VALUE_ROW( SQL_ISV_DOMAINS                            ),
INFO_VALUE_ROW( SQL_ISV_KEY_COLUMN_USAGE                   ),
INFO_VALUE_ROW( SQL_ISV_REFERENTIAL_CONSTRAINTS            ),
INFO_VALUE_ROW( SQL_ISV_SQL_LANGUAGES                      ),
INFO_VALUE_ROW( SQL_ISV_TABLE_CONSTRAINTS                  ),
INFO_VALUE_ROW( SQL_ISV_TABLE_PRIVILEGES                   ),
INFO_VALUE_ROW( SQL_ISV_TABLES                             ),
INFO_VALUE_ROW( SQL_ISV_TRANSLATIONS                       ),
INFO_VALUE_ROW( SQL_ISV_USAGE_PRIVILEGES                   ),
INFO_VALUE_ROW( SQL_ISV_VIEW_COLUMN_USAGE                  ),
INFO_VALUE_ROW( SQL_ISV_VIEW_TABLE_USAGE                   ),
INFO_VALUE_ROW( SQL_ISV_VIEWS                              ),
};

//
// Structure for SQL_NON_NULLABLE_COLUMNS
//
static INFOSTRUCT GetInfoNonNullCols[] = {
INFO_VALUE_ROW( SQL_NNC_NULL                               ),
INFO_VALUE_ROW( SQL_NNC_NON_NULL                           ),
};

//
// Structure for SQL_NULL_COLLATION
//
static INFOSTRUCT GetInfoNullCollation[] = {
INFO_VALUE_ROW( SQL_NC_END                                 ),
INFO_VALUE_ROW( SQL_NC_HIGH                                ),
INFO_VALUE_ROW( SQL_NC_LOW                                 ),
INFO_VALUE_ROW( SQL_NC_START                               ),
};

//
// Structure for SQL_PARAM_ARRAY_ROW_COUNTS
//
static INFOSTRUCT GetInfoParamRowCounts[] = {
INFO_VALUE_ROW( SQL_PARC_BATCH                             ),
INFO_VALUE_ROW( SQL_PARC_NO_BATCH                          ),
};

//
// Structure for SQL_PARAM_ARRAY_SELECTS
//
static INFOSTRUCT GetInfoParamSelects[] = {
INFO_VALUE_ROW( SQL_PAS_BATCH                              ),
INFO_VALUE_ROW( SQL_PAS_NO_BATCH                           ),
INFO_VALUE_ROW( SQL_PAS_NO_SELECT                          ),
};

//
// Structure for SQL_SCHEMA_USAGE
//
static INFOSTRUCT GetInfoSchemaUsage[] = {
INFO_VALUE_ROW( SQL_SU_DML_STATEMENTS                      ),
INFO_VALUE_ROW( SQL_SU_PROCEDURE_INVOCATION                ),
INFO_VALUE_ROW( SQL_SU_TABLE_DEFINITION                    ),
INFO_VALUE_ROW( SQL_SU_INDEX_DEFINITION                    ),
INFO_VALUE_ROW( SQL_SU_PRIVILEGE_DEFINITION                ),
};

//
// Structure for SQL_SCROLL_OPTIONS
//
static INFOSTRUCT GetInfoScrollOptions[] = {
INFO_VALUE_ROW( SQL_SO_FORWARD_ONLY                        ),
INFO_VALUE_ROW( SQL_SO_KEYSET_DRIVEN                       ),
INFO_VALUE_ROW( SQL_SO_DYNAMIC                             ),
INFO_VALUE_ROW( SQL_SO_MIXED                               ),
};

//
// Structure for SQL_SQL_CONFORMANCE
//
static INFOSTRUCT GetInfoSQLConform[] = {
INFO_VALUE_ROW( SQL_SC_SQL92_ENTRY                         ),
INFO_VALUE_ROW( SQL_SC_FIPS127_2_TRANSITIONAL              ),
INFO_VALUE_ROW( SQL_SC_SQL92_FULL                          ),
INFO_VALUE_ROW( SQL_SC_SQL92_INTERMEDIATE                  ),
};

//
// Structure for SQL_SQL92_DATETIME_FUNCTIONS
//
static INFOSTRUCT GetInfoS92DatetimeFns[] = {
INFO_VALUE_ROW( SQL_SDF_CURRENT_DATE                       ),
INFO_VALUE_ROW( SQL_SDF_CURRENT_TIME                       ),
INFO_VALUE_ROW( SQL_SDF_CURRENT_TIMESTAMP                  ),
};

//
// Structure for SQL_SQL92_FOREIGN_KEY_DELETE_RULE
//
static INFOSTRUCT GetInfoS92FKeyDelRule[] = {
INFO_VALUE_ROW( SQL_SFKD_CASCADE                           ),
INFO_VALUE_ROW( SQL_SFKD_NO_ACTION                         ),
INFO_VALUE_ROW( SQL_SFKD_SET_DEFAULT                       ),
INFO_VALUE_ROW( SQL_SFKD_SET_NULL                          ),
};

//
// Structure for SQL_SQL92_FOREIGN_KEY_UPDATE_RULE
//
static INFOSTRUCT GetInfoS92FKeyUpdRule[] = {
INFO_VALUE_ROW( SQL_SFKU_CASCADE                           ),
INFO_VALUE_ROW( SQL_SFKU_NO_ACTION                         ),
INFO_VALUE_ROW( SQL_SFKU_SET_DEFAULT                       ),
INFO_VALUE_ROW( SQL_SFKU_SET_NULL                          ),
};

//
// Structure for SQL_SQL92_GRANT
//
static INFOSTRUCT GetInfoS92Grant[] = {
INFO_VALUE_ROW( SQL_SG_USAGE_ON_DOMAIN                     ),
INFO_VALUE_ROW( SQL_SG_USAGE_ON_CHARACTER_SET              ),
INFO_VALUE_ROW( SQL_SG_USAGE_ON_COLLATION                  ),
INFO_VALUE_ROW( SQL_SG_USAGE_ON_TRANSLATION                ),
INFO_VALUE_ROW( SQL_SG_WITH_GRANT_OPTION                   ),
};

//
// Structure for SQL_NUMERIC_FUNCTIONS
//
static INFOSTRUCT GetInfoNumeric[] = {
INFO_VALUE_ROW( SQL_FN_NUM_ABS                             ),
INFO_VALUE_ROW( SQL_FN_NUM_ACOS                            ),
INFO_VALUE_ROW( SQL_FN_NUM_ASIN                            ),
INFO_VALUE_ROW( SQL_FN_NUM_ATAN                            ),
INFO_VALUE_ROW( SQL_FN_NUM_ATAN2                           ),
INFO_VALUE_ROW( SQL_FN_NUM_CEILING                         ),
INFO_VALUE_ROW( SQL_FN_NUM_COS                             ),
INFO_VALUE_ROW( SQL_FN_NUM_COT                             ),
INFO_VALUE_ROW( SQL_FN_NUM_EXP                             ),
INFO_VALUE_ROW( SQL_FN_NUM_FLOOR                           ),
INFO_VALUE_ROW( SQL_FN_NUM_LOG                             ),
INFO_VALUE_ROW( SQL_FN_NUM_MOD                             ),
INFO_VALUE_ROW( SQL_FN_NUM_RAND                            ),
INFO_VALUE_ROW( SQL_FN_NUM_PI                              ),
INFO_VALUE_ROW( SQL_FN_NUM_SIGN                            ),
INFO_VALUE_ROW( SQL_FN_NUM_SIN                             ),
INFO_VALUE_ROW( SQL_FN_NUM_SQRT                            ),
INFO_VALUE_ROW( SQL_FN_NUM_TAN                             ),
};

//
// Structure for SQL_SQL92_NUMERIC_VALUE_FUNCTIONS
//
static INFOSTRUCT GetInfoS92NumValFns[] = {
INFO_VALUE_ROW( SQL_SNVF_BIT_LENGTH                        ),
INFO_VALUE_ROW( SQL_SNVF_CHAR_LENGTH                       ),
INFO_VALUE_ROW( SQL_SNVF_CHARACTER_LENGTH                  ),
INFO_VALUE_ROW( SQL_SNVF_EXTRACT                           ),
INFO_VALUE_ROW( SQL_SNVF_OCTET_LENGTH                      ),
INFO_VALUE_ROW( SQL_SNVF_POSITION                          ),
};

//
// Structure for SQL_SQL92_PREDICATES
//
static INFOSTRUCT GetInfoS92Predicates[] = {
INFO_VALUE_ROW( SQL_SP_EXISTS                              ),
INFO_VALUE_ROW( SQL_SP_ISNOTNULL                           ),
INFO_VALUE_ROW( SQL_SP_ISNULL                              ),
INFO_VALUE_ROW( SQL_SP_MATCH_FULL                          ),
INFO_VALUE_ROW( SQL_SP_MATCH_PARTIAL                       ),
INFO_VALUE_ROW( SQL_SP_MATCH_UNIQUE_FULL                   ),
INFO_VALUE_ROW( SQL_SP_MATCH_UNIQUE_PARTIAL                ),
INFO_VALUE_ROW( SQL_SP_OVERLAPS                            ),
INFO_VALUE_ROW( SQL_SP_UNIQUE                              ),
INFO_VALUE_ROW( SQL_SP_LIKE                                ),
INFO_VALUE_ROW( SQL_SP_IN                                  ),
INFO_VALUE_ROW( SQL_SP_BETWEEN                             ),
INFO_VALUE_ROW( SQL_SP_COMPARISON                          ),
INFO_VALUE_ROW( SQL_SP_QUANTIFIED_COMPARISON               ),
};

//
// Structure for SQL_SQL92_RELATIONAL_JOIN_OPERATORS
//
static INFOSTRUCT GetInfoS92RelJoinOps[] = {
INFO_VALUE_ROW( SQL_SRJO_CORRESPONDING_CLAUSE              ),
INFO_VALUE_ROW( SQL_SRJO_CROSS_JOIN                        ),
INFO_VALUE_ROW( SQL_SRJO_EXCEPT_JOIN                       ),
INFO_VALUE_ROW( SQL_SRJO_FULL_OUTER_JOIN                   ),
INFO_VALUE_ROW( SQL_SRJO_INNER_JOIN                        ),
INFO_VALUE_ROW( SQL_SRJO_INTERSECT_JOIN                    ),
INFO_VALUE_ROW( SQL_SRJO_LEFT_OUTER_JOIN                   ),
INFO_VALUE_ROW( SQL_SRJO_NATURAL_JOIN                      ),
INFO_VALUE_ROW( SQL_SRJO_RIGHT_OUTER_JOIN                  ),
INFO_VALUE_ROW( SQL_SRJO_UNION_JOIN                        ),
};

//
// Structure for SQL_SQL92_REVOKE
//
static INFOSTRUCT GetInfoS92Revoke[] = {
INFO_VALUE_ROW( SQL_SR_USAGE_ON_DOMAIN                     ),
INFO_VALUE_ROW( SQL_SR_USAGE_ON_CHARACTER_SET              ),
INFO_VALUE_ROW( SQL_SR_USAGE_ON_COLLATION                  ),
INFO_VALUE_ROW( SQL_SR_USAGE_ON_TRANSLATION                ),
INFO_VALUE_ROW( SQL_SR_GRANT_OPTION_FOR                    ),
};

//
// Structure for SQL_SQL92_ROW_VALUE_CONSTRUCTOR
//
static INFOSTRUCT GetInfoS92RowValConstr[] = {
INFO_VALUE_ROW( SQL_SRVC_VALUE_EXPRESSION                  ),
INFO_VALUE_ROW( SQL_SRVC_NULL                              ),
INFO_VALUE_ROW( SQL_SRVC_DEFAULT                           ),
INFO_VALUE_ROW( SQL_SRVC_ROW_SUBQUERY                      ),
};

//
// Structure for SQL_SQL92_STRING_FUNCTIONS
//
static INFOSTRUCT GetInfoS92StringFns[] = {
INFO_VALUE_ROW( SQL_SSF_CONVERT                            ),
INFO_VALUE_ROW( SQL_SSF_LOWER                              ),
INFO_VALUE_ROW( SQL_SSF_UPPER                              ),
INFO_VALUE_ROW( SQL_SSF_SUBSTRING                          ),
INFO_VALUE_ROW( SQL_SSF_TRANSLATE                          ),
INFO_VALUE_ROW( SQL_SSF_TRIM_BOTH                          ),
INFO_VALUE_ROW( SQL_SSF_TRIM_LEADING                       ),
INFO_VALUE_ROW( SQL_SSF_TRIM_TRAILING                      ),
};

//
// Structure for SQL_SQL92_VALUE_EXPRESSIONS
//
static INFOSTRUCT GetInfoS92ValueExprs[] = {
INFO_VALUE_ROW( SQL_SVE_CASE                               ),
INFO_VALUE_ROW( SQL_SVE_CAST                               ),
INFO_VALUE_ROW( SQL_SVE_COALESCE                           ),
INFO_VALUE_ROW( SQL_SVE_NULLIF                             ),
};

//
// Structure for SQL_SQL92_STANDARD_CLI_CONFORMANCE
//
static INFOSTRUCT GetInfoS92StdCLIConf[] = {
INFO_VALUE_ROW( SQL_SCC_XOPEN_CLI_VERSION1                 ),
INFO_VALUE_ROW( SQL_SCC_ISO92_CLI                          ),
};

//
// Structure for SQL_SUBQUERUIES
//
static INFOSTRUCT GetInfoSubqueries[] = {
INFO_VALUE_ROW( SQL_SQ_CORRELATED_SUBQUERIES               ),
INFO_VALUE_ROW( SQL_SQ_COMPARISON                          ),
INFO_VALUE_ROW( SQL_SQ_EXISTS                              ),
INFO_VALUE_ROW( SQL_SQ_IN                                  ),
INFO_VALUE_ROW( SQL_SQ_QUANTIFIED                          ),
};

//
// Structure for SQL_STRING_FUNCTIONS
//
static INFOSTRUCT GetInfoStrings[] = {
INFO_VALUE_ROW( SQL_FN_STR_ASCII                                         ),
INFO_VALUE_ROW( SQL_FN_STR_CHAR                            ),
INFO_VALUE_ROW( SQL_FN_STR_CONCAT                          ),
INFO_VALUE_ROW( SQL_FN_STR_INSERT                          ),
INFO_VALUE_ROW( SQL_FN_STR_LCASE                           ),
INFO_VALUE_ROW( SQL_FN_STR_LEFT                            ),
INFO_VALUE_ROW( SQL_FN_STR_LENGTH                          ),
INFO_VALUE_ROW( SQL_FN_STR_LOCATE                          ),
INFO_VALUE_ROW( SQL_FN_STR_LTRIM                           ),
INFO_VALUE_ROW( SQL_FN_STR_REPEAT                          ),
INFO_VALUE_ROW( SQL_FN_STR_REPLACE                         ),
INFO_VALUE_ROW( SQL_FN_STR_RIGHT                           ),
INFO_VALUE_ROW( SQL_FN_STR_RTRIM                           ),
INFO_VALUE_ROW( SQL_FN_STR_SUBSTRING                       ),
INFO_VALUE_ROW( SQL_FN_STR_UCASE                           ),
};

//
// Structure for SQL_SYSTEM_FUNCTIONS
//
static INFOSTRUCT GetInfoSystem[] = {
INFO_VALUE_ROW( SQL_FN_SYS_DBNAME                          ),
INFO_VALUE_ROW( SQL_FN_SYS_IFNULL                          ),
INFO_VALUE_ROW( SQL_FN_SYS_USERNAME                        ),
};

//
// Structure for SQL_TIMEDATE_FUNCTIONS
//
static INFOSTRUCT GetInfoTimeDate[] = {
INFO_VALUE_ROW( SQL_FN_TD_CURDATE                          ),
INFO_VALUE_ROW( SQL_FN_TD_CURRENT_DATE                     ),
INFO_VALUE_ROW( SQL_FN_TD_CURRENT_TIME                     ),
INFO_VALUE_ROW( SQL_FN_TD_CURRENT_TIMESTAMP                ),
INFO_VALUE_ROW( SQL_FN_TD_CURTIME                          ),
INFO_VALUE_ROW( SQL_FN_TD_DAYOFMONTH                       ),
INFO_VALUE_ROW( SQL_FN_TD_DAYOFWEEK                        ),
INFO_VALUE_ROW( SQL_FN_TD_DAYOFYEAR                        ),
INFO_VALUE_ROW( SQL_FN_TD_EXTRACT                          ),
INFO_VALUE_ROW( SQL_FN_TD_HOUR                             ),
INFO_VALUE_ROW( SQL_FN_TD_MINUTE                           ),
INFO_VALUE_ROW( SQL_FN_TD_MONTH                            ),
INFO_VALUE_ROW( SQL_FN_TD_NOW                              ),
INFO_VALUE_ROW( SQL_FN_TD_QUARTER                          ),
INFO_VALUE_ROW( SQL_FN_TD_SECOND                           ),
INFO_VALUE_ROW( SQL_FN_TD_WEEK                             ),
INFO_VALUE_ROW( SQL_FN_TD_YEAR                             ),
};

//
// Structure for SQL_TIMEDATE_ADD_INTERVALS,
//               SQL_TIMEDATE_DIFF_INTERVALS,
//
static INFOSTRUCT GetInfoTimeDateIvls[] = {
INFO_VALUE_ROW( SQL_FN_TSI_FRAC_SECOND                     ),
INFO_VALUE_ROW( SQL_FN_TSI_SECOND                          ),
INFO_VALUE_ROW( SQL_FN_TSI_MINUTE                          ),
INFO_VALUE_ROW( SQL_FN_TSI_HOUR                            ),
INFO_VALUE_ROW( SQL_FN_TSI_DAY                             ),
INFO_VALUE_ROW( SQL_FN_TSI_WEEK                            ),
INFO_VALUE_ROW( SQL_FN_TSI_MONTH                           ),
INFO_VALUE_ROW( SQL_FN_TSI_QUARTER                         ),
INFO_VALUE_ROW( SQL_FN_TSI_YEAR                            ),
};

//
// Structure for SQL_ODBC_API_CONFORMANCE
//
static INFOSTRUCT GetInfoAPIConform[] = {
INFO_VALUE_ROW( SQL_OIC_CORE                               ),
INFO_VALUE_ROW( SQL_OIC_LEVEL1                             ),
INFO_VALUE_ROW( SQL_OIC_LEVEL2                             ),
};

//
// Structure for SQL_ODBC_SQL_CONFORMANCE
//
static INFOSTRUCT GetInfoODBCSQL[] = {
INFO_VALUE_ROW( SQL_OSC_MINIMUM                            ),
INFO_VALUE_ROW( SQL_OSC_CORE                               ),
INFO_VALUE_ROW( SQL_OSC_EXTENDED                           ),
};

//
// Structure for SQL_IDENTIFIER_CASE
//
static INFOSTRUCT GetInfoIDCase[] = {
INFO_VALUE_ROW( SQL_IC_UPPER                               ),
INFO_VALUE_ROW( SQL_IC_LOWER                               ),
INFO_VALUE_ROW( SQL_IC_SENSITIVE                           ),
INFO_VALUE_ROW( SQL_IC_MIXED                               ),
};

//
// Structure for SQL_TXN_CAPABLE
//
static INFOSTRUCT GetInfoTxnCapable[] = {
INFO_VALUE_ROW( SQL_TC_NONE                                ),
INFO_VALUE_ROW( SQL_TC_DML                                 ),
INFO_VALUE_ROW( SQL_TC_DDL_COMMIT                          ),
INFO_VALUE_ROW( SQL_TC_DDL_IGNORE                          ),
INFO_VALUE_ROW( SQL_TC_ALL                                 ),
};

//
// Structure for SQL_TXN_ISOLATION_OPTIONS
//
static INFOSTRUCT GetInfoTxnIsoOptions[] = {
INFO_VALUE_ROW( SQL_TXN_READ_UNCOMMITTED                   ),
INFO_VALUE_ROW( SQL_TXN_READ_COMMITTED                     ),
INFO_VALUE_ROW( SQL_TXN_REPEATABLE_READ                    ),
INFO_VALUE_ROW( SQL_TXN_SERIALIZABLE                       ),
};

//
// Structure for SQL_UNION
//
static INFOSTRUCT GetInfoUnion[] = {
INFO_VALUE_ROW( SQL_U_UNION                                ),
INFO_VALUE_ROW( SQL_U_UNION_ALL                            ),
};


//
// The following structure is used to retrieve information about the driver.  There
//    are 5 types of GetInfo structures:
//          INT16       16-bit value
//          INT32       32-bit value
//          STRVAL      String value
//          DEXVAL      Indexed item (eg: 0-x)
//          BITVAL      Bit-mask value
//
char           szGetInfo[MAXBUFF];
UWORD          cb16;
UDWORD         cb32;
#define        INT16             1
#define        INT32             2
#define        STRVAL            3
#define        DEXVAL            4
#define        BITVAL            5

#define INFOROW(name, string, type, addr, varsize, ptr, size) {name, string, type, addr, varsize, ptr, size}

#define INT16_ITEM(name)        INFOROW(name, #name, INT16,  &cb16,      sizeof(cb16), NULL, 0)
#define INT32_ITEM(name)        INFOROW(name, #name, INT32,  &cb32,      sizeof(cb32), NULL, 0)
#define STRNG_ITEM(name)        INFOROW(name, #name, STRVAL, szGetInfo,  sizeof(szGetInfo), NULL, 0)
#define BIT32_ITEM(name, list)  INFOROW(name, #name, BITVAL, &cb32,      sizeof(cb32), list, NumItems(list))
#define DEX32_ITEM(name, list)  INFOROW(name, #name, DEXVAL, &cb32,      sizeof(cb32), list, NumItems(list))


struct {

   UWORD          fInfoType;                 // What we're looking for
   LPSTR          szInfoName;                // Print name of the GetInfo item
   int            fOutType;                  // string, 16-bit or 32-bit
   PTR            rgbInfoValue;              // Output buffer
   SWORD          cbInfoMax;                 // Size of output buffer
   void FAR *     ptr;                       // Generic constant structure
   int            cbNum;                     // Count of items in ptr

} GetInfo[] = {


   // Out Type  fInfoType                          List of Values
   // --------  -------------------------          ---------------------------
   STRNG_ITEM(  SQL_ACCESSIBLE_PROCEDURES                                      ),
   STRNG_ITEM(  SQL_ACCESSIBLE_TABLES                                          ),
   INT16_ITEM(  SQL_ACTIVE_ENVIRONMENTS                                        ),
   BIT32_ITEM(  SQL_ALTER_DOMAIN,                  GetInfoAlterDomain          ),
   BIT32_ITEM(  SQL_ALTER_TABLE,                   GetInfoAlterTable           ),
   DEX32_ITEM(  SQL_ASYNC_MODE,                    GetInfoAsyncMode            ),

   BIT32_ITEM(  SQL_BATCH_ROW_COUNT,               GetInfoBatchRowCount        ),
   BIT32_ITEM(  SQL_BATCH_SUPPORT,                 GetInfoBatchSupport         ),
   BIT32_ITEM(  SQL_BOOKMARK_PERSISTENCE,          GetInfoBookmarkPersist      ),

   DEX32_ITEM(  SQL_CATALOG_LOCATION,              GetInfoCatLocation          ),
   STRNG_ITEM(  SQL_CATALOG_NAME                                               ),
   STRNG_ITEM(  SQL_CATALOG_NAME_SEPARATOR                                     ),
   STRNG_ITEM(  SQL_CATALOG_TERM                                               ),
   BIT32_ITEM(  SQL_CATALOG_USAGE,                 GetInfoCatUsage             ),
   STRNG_ITEM(  SQL_COLLATION_SEQ                                              ),
   STRNG_ITEM(  SQL_COLUMN_ALIAS                                               ),
   DEX32_ITEM(  SQL_CONCAT_NULL_BEHAVIOR,          GetInfoConcat               ),
   BIT32_ITEM(  SQL_CONVERT_BIGINT,                GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_BINARY,                GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_BIT,                   GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_CHAR,                  GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_DATE,                  GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_DECIMAL,               GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_DOUBLE,                GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_FLOAT,                 GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_FUNCTIONS,             GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_INTEGER,               GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_LONGVARBINARY,         GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_LONGVARCHAR,           GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_NUMERIC,               GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_REAL,                  GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_SMALLINT,              GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_TIME,                  GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_TIMESTAMP,             GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_TINYINT,               GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_VARBINARY,             GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_VARCHAR,               GetInfoConvertTypes         ),
   BIT32_ITEM(  SQL_CONVERT_FUNCTIONS,             GetInfoConvertFunctions     ),
   BIT32_ITEM(  SQL_CORRELATION_NAME,              GetInfoCorrelationName      ),
   BIT32_ITEM(  SQL_CREATE_ASSERTION,              GetInfoCreateAssertion      ),
   BIT32_ITEM(  SQL_CREATE_CHARACTER_SET,          GetInfoCreateCharset        ),
   BIT32_ITEM(  SQL_CREATE_COLLATION,              GetInfoCreateCollation      ),
   BIT32_ITEM(  SQL_CREATE_DOMAIN,                 GetInfoCreateDomain         ),
   BIT32_ITEM(  SQL_CREATE_SCHEMA,                 GetInfoCreateSchema         ),
   BIT32_ITEM(  SQL_CREATE_TABLE,                  GetInfoCreateTable          ),
   BIT32_ITEM(  SQL_CREATE_TRANSLATION,            GetInfoCreateXlation        ),
   BIT32_ITEM(  SQL_CREATE_VIEW,                   GetInfoCreateView           ),
   DEX32_ITEM(  SQL_CURSOR_COMMIT_BEHAVIOR,        GetInfoCommit               ),
   DEX32_ITEM(  SQL_CURSOR_ROLLBACK_BEHAVIOR,      GetInfoCommit               ),
   DEX32_ITEM(  SQL_CURSOR_SENSITIVITY,            GetInfoCursorSensitiv       ),

   STRNG_ITEM(  SQL_DATA_SOURCE_NAME                                           ),
   STRNG_ITEM(  SQL_DATA_SOURCE_READ_ONLY                                      ),
   STRNG_ITEM(  SQL_DATABASE_NAME                                              ),
   BIT32_ITEM(  SQL_DATETIME_LITERALS,             GetInfoSQLDateLit           ),
   STRNG_ITEM(  SQL_DBMS_NAME                                                  ),
   STRNG_ITEM(  SQL_DBMS_VER                                                   ),
   BIT32_ITEM(  SQL_DEFAULT_TXN_ISOLATION,         GetInfoTXNIsolation         ),
   STRNG_ITEM(  SQL_DESCRIBE_PARAMETER                                         ),
   INT32_ITEM(  SQL_DRIVER_HDBC                                                ),
   INT32_ITEM(  SQL_DRIVER_HENV                                                ),
   INT32_ITEM(  SQL_DRIVER_HLIB                                                ),
   INT32_ITEM(  SQL_DRIVER_HSTMT                                               ),
   STRNG_ITEM(  SQL_DRIVER_NAME                                                ),
   STRNG_ITEM(  SQL_DRIVER_ODBC_VER                                            ),
   STRNG_ITEM(  SQL_DRIVER_VER                                                 ),
   BIT32_ITEM(  SQL_DROP_ASSERTION,                GetInfoDropAssertion        ),
   BIT32_ITEM(  SQL_DROP_CHARACTER_SET,            GetInfoDropCharset          ),
   BIT32_ITEM(  SQL_DROP_COLLATION,                GetInfoDropCollation        ),
   BIT32_ITEM(  SQL_DROP_DOMAIN,                   GetInfoDropDomain           ),
   BIT32_ITEM(  SQL_DROP_SCHEMA,                   GetInfoDropSchema           ),
   BIT32_ITEM(  SQL_DROP_TABLE,                    GetInfoDropTable            ),
   BIT32_ITEM(  SQL_DROP_TRANSLATION,              GetInfoDropXlation          ),
   BIT32_ITEM(  SQL_DROP_VIEW,                     GetInfoDropView             ),
   BIT32_ITEM(  SQL_DYNAMIC_CURSOR_ATTRIBUTES1,    GetInfoCurAttrs1            ),
   BIT32_ITEM(  SQL_DYNAMIC_CURSOR_ATTRIBUTES2,    GetInfoCurAttrs2            ),

   STRNG_ITEM(  SQL_EXPRESSIONS_IN_ORDERBY                                     ),

   DEX32_ITEM(  SQL_FILE_USAGE,                    GetInfoFileUsage            ),
   BIT32_ITEM(  SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES1, GetInfoCurAttrs1          ),
   BIT32_ITEM(  SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES2, GetInfoCurAttrs2          ),

   BIT32_ITEM(  SQL_GETDATA_EXTENSIONS,            GetInfoGetdataExt           ),
   BIT32_ITEM(  SQL_GROUP_BY,                      GetInfoGroupBy              ),

   DEX32_ITEM(  SQL_IDENTIFIER_CASE,               GetInfoIDCase               ),
   INT16_ITEM(  SQL_IDENTIFIER_QUOTE_CHAR                                      ),
   BIT32_ITEM(  SQL_INDEX_KEYWORDS,                GetInfoIndexKeywords        ),
   BIT32_ITEM(  SQL_INFO_SCHEMA_VIEWS,             GetInfoInfoSchemaViews      ),
   STRNG_ITEM(  SQL_INTEGRITY                                                  ),

   BIT32_ITEM(  SQL_KEYSET_CURSOR_ATTRIBUTES1,     GetInfoCurAttrs1            ),
   BIT32_ITEM(  SQL_KEYSET_CURSOR_ATTRIBUTES2,     GetInfoCurAttrs2            ),
   STRNG_ITEM(  SQL_KEYWORDS                                                   ),

   STRNG_ITEM(  SQL_LIKE_ESCAPE_CLAUSE                                         ),

   INT32_ITEM(  SQL_MAX_ASYNC_CONCURRENT_STATEMENTS                            ),
   INT32_ITEM(  SQL_MAX_BINARY_LITERAL_LEN                                     ),
   INT16_ITEM(  SQL_MAX_CATALOG_NAME_LEN                                       ),
   INT32_ITEM(  SQL_MAX_CHAR_LITERAL_LEN                                       ),
   INT16_ITEM(  SQL_MAX_COLUMN_NAME_LEN                                        ),
   INT16_ITEM(  SQL_MAX_COLUMNS_IN_GROUP_BY                                    ),
   INT16_ITEM(  SQL_MAX_COLUMNS_IN_INDEX                                       ),
   INT16_ITEM(  SQL_MAX_COLUMNS_IN_ORDER_BY                                    ),
   INT16_ITEM(  SQL_MAX_COLUMNS_IN_SELECT                                      ),
   INT16_ITEM(  SQL_MAX_COLUMNS_IN_TABLE                                       ),
   INT16_ITEM(  SQL_MAX_CONCURRENT_ACTIVITIES                                  ),
   INT16_ITEM(  SQL_MAX_CURSOR_NAME_LEN                                        ),
   INT16_ITEM(  SQL_MAX_DRIVER_CONNECTIONS                                     ),
   INT16_ITEM(  SQL_MAX_IDENTIFIER_LEN                                         ),
   INT32_ITEM(  SQL_MAX_INDEX_SIZE                                             ),
   INT16_ITEM(  SQL_MAX_PROCEDURE_NAME_LEN                                     ),
   INT32_ITEM(  SQL_MAX_ROW_SIZE                                               ),
   STRNG_ITEM(  SQL_MAX_ROW_SIZE_INCLUDES_LONG                                 ),
   INT16_ITEM(  SQL_MAX_SCHEMA_NAME_LEN                                        ),
   INT16_ITEM(  SQL_MAX_STATEMENT_LEN                                          ),
   INT16_ITEM(  SQL_MAX_TABLE_NAME_LEN                                         ),
   INT16_ITEM(  SQL_MAX_TABLES_IN_SELECT                                       ),
   INT16_ITEM(  SQL_MAX_USER_NAME_LEN                                          ),
   STRNG_ITEM(  SQL_MULTIPLE_ACTIVE_TXN                                        ),
   STRNG_ITEM(  SQL_MULT_RESULT_SETS                                           ),

   STRNG_ITEM(  SQL_NEED_LONG_DATA_LEN                                         ),
   DEX32_ITEM(  SQL_NON_NULLABLE_COLUMNS,          GetInfoNonNullCols          ),
   DEX32_ITEM(  SQL_NULL_COLLATION,                GetInfoNullCollation        ),
   BIT32_ITEM(  SQL_NUMERIC_FUNCTIONS,             GetInfoNumeric              ),

   DEX32_ITEM(  SQL_ODBC_INTERFACE_CONFORMANCE,    GetInfoAPIConform           ),
   DEX32_ITEM(  SQL_ODBC_SQL_CONFORMANCE,          GetInfoODBCSQL              ),
   STRNG_ITEM(  SQL_ODBC_VER                                                   ),
   STRNG_ITEM(  SQL_ORDER_BY_COLUMNS_IN_SELECT                                 ),
   STRNG_ITEM(  SQL_OUTER_JOINS                                                ),

   DEX32_ITEM(  SQL_PARAM_ARRAY_ROW_COUNTS,        GetInfoParamRowCounts       ),
   DEX32_ITEM(  SQL_PARAM_ARRAY_SELECTS,           GetInfoParamSelects         ),
   STRNG_ITEM(  SQL_PROCEDURES                                                 ),
   STRNG_ITEM(  SQL_PROCEDURE_TERM                                             ),

   DEX32_ITEM(  SQL_QUOTED_IDENTIFIER_CASE,        GetInfoIDCase               ),

   STRNG_ITEM(  SQL_ROW_UPDATES                                                ),

   STRNG_ITEM(  SQL_SCHEMA_TERM                                                ),
   BIT32_ITEM(  SQL_SCHEMA_USAGE,                  GetInfoSchemaUsage          ),
   BIT32_ITEM(  SQL_SCROLL_OPTIONS,                GetInfoScrollOptions        ),
   STRNG_ITEM(  SQL_SEARCH_PATTERN_ESCAPE                                      ),
   STRNG_ITEM(  SQL_SERVER_NAME                                                ),
   STRNG_ITEM(  SQL_SPECIAL_CHARACTERS                                         ),
   BIT32_ITEM(  SQL_SQL_CONFORMANCE,               GetInfoSQLConform           ),
   BIT32_ITEM(  SQL_SQL92_DATETIME_FUNCTIONS,      GetInfoS92DatetimeFns       ),
   BIT32_ITEM(  SQL_SQL92_FOREIGN_KEY_DELETE_RULE, GetInfoS92FKeyDelRule       ),
   BIT32_ITEM(  SQL_SQL92_FOREIGN_KEY_UPDATE_RULE, GetInfoS92FKeyUpdRule       ),
   BIT32_ITEM(  SQL_SQL92_GRANT,                   GetInfoS92Grant             ),
   BIT32_ITEM(  SQL_SQL92_NUMERIC_VALUE_FUNCTIONS, GetInfoS92NumValFns         ),
   BIT32_ITEM(  SQL_SQL92_PREDICATES,              GetInfoS92Predicates        ),
   BIT32_ITEM(  SQL_SQL92_RELATIONAL_JOIN_OPERATORS, GetInfoS92RelJoinOps      ),
   BIT32_ITEM(  SQL_SQL92_REVOKE,                  GetInfoS92Revoke            ),
   BIT32_ITEM(  SQL_SQL92_ROW_VALUE_CONSTRUCTOR,   GetInfoS92RowValConstr      ),
   BIT32_ITEM(  SQL_SQL92_STRING_FUNCTIONS,        GetInfoS92StringFns         ),
   BIT32_ITEM(  SQL_SQL92_VALUE_EXPRESSIONS,       GetInfoS92ValueExprs        ),
   BIT32_ITEM(  SQL_STANDARD_CLI_CONFORMANCE,      GetInfoS92StdCLIConf        ),
   BIT32_ITEM(  SQL_STATIC_CURSOR_ATTRIBUTES1,     GetInfoCurAttrs1            ),
   BIT32_ITEM(  SQL_STATIC_CURSOR_ATTRIBUTES2,     GetInfoCurAttrs2            ),
   BIT32_ITEM(  SQL_STRING_FUNCTIONS,              GetInfoStrings              ),
   BIT32_ITEM(  SQL_SUBQUERIES,                    GetInfoSubqueries           ),
   BIT32_ITEM(  SQL_SYSTEM_FUNCTIONS,              GetInfoSystem               ),

   STRNG_ITEM(  SQL_TABLE_TERM                                                 ),
   BIT32_ITEM(  SQL_TIMEDATE_ADD_INTERVALS,        GetInfoTimeDateIvls         ),
   BIT32_ITEM(  SQL_TIMEDATE_DIFF_INTERVALS,       GetInfoTimeDateIvls         ),
   BIT32_ITEM(  SQL_TIMEDATE_FUNCTIONS,            GetInfoTimeDate             ),
   DEX32_ITEM(  SQL_TXN_CAPABLE,                   GetInfoTxnCapable           ),
   BIT32_ITEM(  SQL_TXN_ISOLATION_OPTION,          GetInfoTxnIsoOptions        ),

   BIT32_ITEM(  SQL_UNION,                         GetInfoUnion                ),
   STRNG_ITEM(  SQL_USER_NAME                                                  ),

   STRNG_ITEM(  SQL_XOPEN_CLI_YEAR                                             ),
};
   
   
//*---------------------------------------------------------------------------------
//| GetBitVal:
//|   Call this function to retrieve the string values for all items which meet
//|   the bitwise and condition.
//| Parms:
//|   in       rs                   Pointer to the results set
//|   in       szInfoName           The info value being retrieved
//|   in       is                   Structure with resource ids and values
//|   in       maxdex               Number of items in struct
//|   in       mask                 The value to compare against
//|   in       szOut                Output buffer for retrieval
//|   in       cbOut                Size of output buffer
//| Returns:              
//|   Nothing
//*---------------------------------------------------------------------------------
BOOL GetBitVal
   (RESULTSSET FAR * rs,
    LPSTR szInfoName,
    lpINFOSTRUCT is,
    int maxdex,
    UDWORD mask,
    LPSTR szVal,
    int cbVal)
{
   int            tdex;
   ROWDATA FAR *  rd;
   COLORREF       rgbDft=GetDefaultRGB();

   if (mask != 0) {
      for(tdex=0;  tdex<maxdex;  tdex++) 
         if(is[tdex].fVal & mask) {
            rd = AllocateRowData(rs, rgbDft, RDATA_DEFAULT_BKGRND);
            SetColumnData(0, rd, szInfoName);
            SetColumnData(1, rd, is[tdex].szStr);
            if(AddRowData(rs, rd) == LB_ERRSPACE)
               return FALSE;
         }
   }
   else {
      rd = AllocateRowData(rs, rgbDft, RDATA_DEFAULT_BKGRND);
      SetColumnData(0, rd, szInfoName);
      SetColumnData(1, rd, "0");
      if(AddRowData(rs, rd) == LB_ERRSPACE)
         return FALSE;
   }

   return TRUE;
}

   
//*---------------------------------------------------------------------------------
//| GetIndexVal:
//|   Call this function to retrieve the string value for a constant.
//| Parms:
//|   in       rs                   Pointer to the results set
//|   in       szInfoName           The info value being retrieved
//|   in       is                   Structure with resource ids and values
//|   in       maxdex               Number of items in struct
//|   in       dex                  String index value 
//|   in       szOut                Output buffer for retrieval
//|   in       cbOut                Size of output buffer
//| Returns:              
//|   FALSE if there is an error
//| No error is posted if matching value is not found.
//*---------------------------------------------------------------------------------
BOOL GetIndexVal
   (RESULTSSET FAR * rs,
    LPSTR szInfoName, 
    lpINFOSTRUCT is,
    int maxdex,
    int dex,
    LPSTR szOut,
    int cbOut)
{
   int tdex;
   ROWDATA FAR *  rd;
   COLORREF       rgbDft=GetDefaultRGB();

   for (tdex = 0; tdex<maxdex; tdex++)
      if (is[tdex].fVal == (UDWORD) dex) {
         rd = AllocateRowData(rs, rgbDft, RDATA_DEFAULT_BKGRND);
         SetColumnData(0, rd, szInfoName);
         SetColumnData(1, rd, is[tdex].szStr);
         if(AddRowData(rs, rd) == LB_ERRSPACE)
            return FALSE;
      }

   return TRUE;
}

   
//*---------------------------------------------------------------------------------
//| DisplayGetInfo:
//|   This function goes through all of the SQLGetInfo constants defined in the
//|   ODBC reference guide and displays them in a results set.
//| Parms:
//|   in       ci                   CHILDINFO information
//| Returns:              
//|   TRUE if successful,
//|   FALSE on error
//*---------------------------------------------------------------------------------
BOOL DisplayGetInfo(CHILDINFO FAR * ci)
{
   char                 szTitle[MAXBUFF];
   char                 szVal[MAXBUFF];
   int                  dex;
   lpINFOSTRUCT         lpINFS;
   RESULTSSET FAR *     rs;
   ROWDATA FAR *        rd;
   RETCODE              retcode;
   COLORREF             rgbDft=GetDefaultRGB();

   //
   // Create a hard coded results set with 2 columns
   //
   lstrcpy((LPSTR)szTitle, (LPSTR)ci->szClientTitle);
   lstrcat((LPSTR)szTitle, (LPSTR)szDash);
   lstrcat((LPSTR)szTitle, (LPSTR)szGetInfoTitle);
   rs = GetConnectWindowResultsNode(ci);
   if(!CreateResultsSet(rs, ci->hwndClient, ci->hInst, 2, (LPSTR)szTitle))
      return FALSE;  

   //
   // Set the meta data
   //
   SetMetaDataColumn(rs, 0, (LPSTR)"fInfoType", 
                     GetTypeName(SQL_TYPE, SQL_CHAR), SQL_CHAR, 40, 0,
                     45, TA_LEFT);
   SetMetaDataColumn(rs, 1, (LPSTR)"Value", 
                     GetTypeName(SQL_TYPE, SQL_CHAR), SQL_CHAR, 70, 0,
                     70, TA_LEFT);

   //
   // Now create the MDI child window which will hold the results.
   //
   if(!CreateResultsWindow(ci, rs)) 
      goto exit00;

   
   //
   // Loop through the control structure and check each fInfoType.  Certain
   //    types require extra processing.
   //
   Busy(TRUE);
   for(dex=0;  dex<NumItems(GetInfo);  dex++) {
      if(GetInfo[dex].fInfoType == SQL_DRIVER_HSTMT)           // Input arg also
         *(HSTMT FAR *)GetInfo[dex].rgbInfoValue = ci->hstmt;

      memset(GetInfo[dex].rgbInfoValue, 0, GetInfo[dex].cbInfoMax);

      retcode = SQLGetInfo(ci->hdbc, 
                           GetInfo[dex].fInfoType, 
                           GetInfo[dex].rgbInfoValue, 
                           GetInfo[dex].cbInfoMax, 
                           NULL);
      if(retcode != SQL_SUCCESS)
         PrintErrors(ci, SQL_HANDLE_DBC);

      switch(GetInfo[dex].fInfoType) {
        case SQL_DRIVER_HENV:
        case SQL_DRIVER_HDBC:
        case SQL_DRIVER_HSTMT:
         rd = AllocateRowData(rs, rgbDft, RDATA_DEFAULT_BKGRND);
         SetColumnData(0, rd, GetInfo[dex].szInfoName);
         wsprintf(szVal, "%04X:%04X", HIWORD(cb32), LOWORD(cb32));
         SetColumnData(1, rd, (LPSTR)szVal);
         if(AddRowData(rs, rd) == LB_ERRSPACE)
            goto exit00;
         break;
         
         //
         // The default action is taken when we only need to display the
         //    value as is.  We can use the structure to figure out what
         //    format it is in.
         //
        default:
         rd = AllocateRowData(rs, rgbDft, RDATA_DEFAULT_BKGRND);
         SetColumnData(0, rd, GetInfo[dex].szInfoName);
         switch(GetInfo[dex].fOutType) {
           case INT16:
            wsprintf(szVal, "%d", cb16);
            SetColumnData(1, rd, (LPSTR)szVal);
            if(AddRowData(rs, rd) == LB_ERRSPACE)
               goto exit00;
            break;
            
           case INT32:
            wsprintf(szVal, "%ld", cb32);
            SetColumnData(1, rd, (LPSTR)szVal);
            if(AddRowData(rs, rd) == LB_ERRSPACE)
               goto exit00;
            break;

           case DEXVAL:
            lpINFS = (lpINFOSTRUCT)GetInfo[dex].ptr;
            if(!GetIndexVal(rs, GetInfo[dex].szInfoName,
                            lpINFS, GetInfo[dex].cbNum,
                            cb32,
                            (LPSTR)szVal, sizeof(szVal)))
               goto exit00;
            break;
            
           case BITVAL:
            lpINFS = (lpINFOSTRUCT)GetInfo[dex].ptr;
            if(!GetBitVal(rs, GetInfo[dex].szInfoName,
                          lpINFS, GetInfo[dex].cbNum,
                          cb32,
                          (LPSTR)szVal, sizeof(szVal)))
               goto exit00;
            break;
            
           default: 
            szGetInfo[69] = '\0'; // truncate long string...
            SetColumnData(1, rd, (LPSTR)GetInfo[dex].rgbInfoValue);
            if(AddRowData(rs, rd) == LB_ERRSPACE)
               goto exit00;
            break;
         }
      }
      
   }
   
   Busy(FALSE);
   return TRUE;
   
  exit00:
   Busy(FALSE);
   return FALSE;
}

   
//*---------------------------------------------------------------------------------
//| DisplayODBCFunctions:
//|   This function will enumerate all of the ODBC functions in a results set
//|      and indicate which ones are supported.  The results set is attatched
//|      as a valid results window on the current child.
//| Parms:
//|   in       ci                   CHILDINFO information
//| Returns:              
//|   TRUE if successful,
//|   FALSE on error
//*---------------------------------------------------------------------------------
BOOL DisplayODBCFunctions(CHILDINFO FAR * ci)
{
   UWORD                fSupport;
   char                 szFuncName[35];
   char                 szTitle[MAXBUFF];
   int                  dex;
   RESULTSSET FAR *     rs;
   ROWDATA FAR *        rd;
   RETCODE              retcode;
   COLORREF             rgbDft=GetDefaultRGB();
   //
   // Create a hard coded results set with 3 columns
   //
   lstrcpy((LPSTR)szTitle, (LPSTR)ci->szClientTitle);
   lstrcat((LPSTR)szTitle, (LPSTR)szDash);
   lstrcat((LPSTR)szTitle, (LPSTR)szODBCFunctions);
   rs = GetConnectWindowResultsNode(ci);
   if(!CreateResultsSet(rs, ci->hwndClient, ci->hInst, 3, (LPSTR)szTitle))
      return FALSE;  

   //
   // Set the meta data
   //
   SetMetaDataColumn(rs, 0, (LPSTR)"Function", 
                     GetTypeName(SQL_TYPE, SQL_CHAR), SQL_CHAR, 20, 0,
                     25, TA_LEFT);
   SetMetaDataColumn(rs, 1, (LPSTR)"Conformance", 
                     GetTypeName(SQL_TYPE, SQL_CHAR), SQL_CHAR, 10, 0,
                     10, TA_LEFT);
   SetMetaDataColumn(rs, 2, (LPSTR)"Supported", 
                     GetTypeName(SQL_TYPE, SQL_CHAR), SQL_CHAR, 10, 0,
                     10, TA_LEFT);

   //
   // Now create the MDI child window which will hold the results.
   //
   if(!CreateResultsWindow(ci, rs)) 
      goto exit00;

   
   //
   // Loop through the control structure and check each function.  For each row
   //    add a record with the function name, conformance level, and Yes if
   //    supported, No if not.
   //
   for(dex=0;  dex<NumItems(ODBCFunctions);  dex++) {
      retcode = SQLGetFunctions(ci->hdbc, 
                                ODBCFunctions[dex].fFunction, &fSupport);
      if(retcode != SQL_SUCCESS)
         PrintErrors(ci, SQL_HANDLE_DBC);
      iLoadString(ODBCFunctions[dex].idFunction, (LPSTR)szFuncName, sizeof(szFuncName));
      rd = AllocateRowData(rs, rgbDft, RDATA_DEFAULT_BKGRND);
      SetColumnData(0, rd, szFuncName);
      SetColumnData(1, rd, ODBCFunctions[dex].szLevel);
      SetColumnData(2, rd, (fSupport) ? (LPSTR)szYes : (LPSTR)szNo);
      AddRowData(rs, rd);
   }
   
   return TRUE;
   
  exit00:
   SQLFreeStmt(ci->hstmt, SQL_CLOSE);
   return FALSE;
}


//*---------------------------------------------------------------------------------
//| DisplayODBCDataSources:
//|   This function will enumerate all of the ODBC Data sources.
//| Parms:
//|   in       ci                   CHILDINFO information
//| Returns:              
//|   TRUE if successful,
//|   FALSE on error
//*---------------------------------------------------------------------------------
BOOL DisplayODBCDataSources(CHILDINFO FAR * ci)
{  
   HENV                 henv;
   RESULTSSET FAR *     rs;
   ROWDATA FAR *        rd;
   RETCODE              retcode;
   char                 szDSN[SQL_MAX_DSN_LENGTH + 1];
   char                 szDesc[MAXBUFF];
   char                 szTitle[MAXBUFF];
   COLORREF             rgbDft=GetDefaultRGB();

   //
   // Create a hard coded results set with 2 columns
   //
   lstrcpy((LPSTR)szTitle, (LPSTR)ci->szClientTitle);
   lstrcat((LPSTR)szTitle, (LPSTR)szDash);
   lstrcat((LPSTR)szTitle, (LPSTR)szODBCDataSources);
   rs = GetConnectWindowResultsNode(ci);
   if(!CreateResultsSet(rs, ci->hwndClient, ci->hInst, 2, (LPSTR)szTitle))
      return FALSE;  

   //
   // Set the meta data
   //
   SetMetaDataColumn(rs, 0, (LPSTR)"Driver", 
                     GetTypeName(SQL_TYPE, SQL_CHAR), SQL_CHAR, 15, 0,
                     15, TA_LEFT);
   SetMetaDataColumn(rs, 1, (LPSTR)"Description", 
                     GetTypeName(SQL_TYPE, SQL_CHAR), SQL_CHAR, 35, 0,
                     35, TA_LEFT);

   //
   // Now create the MDI child window which will hold the results.
   //
   if(!CreateResultsWindow(ci, rs)) 
      goto exit00;

   
   //
   // Loop through each data source and add it to the results set.
   //
   if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HENV, &henv) )
	{
		 PrintErrors(ci, SQL_HANDLE_ENV);
		 goto exit00;
	}
	if (SQL_SUCCESS != SQLSetEnvAttr(henv,SQL_ATTR_ODBC_VERSION,
		(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER))
	{
		 PrintErrors(ci, SQL_HANDLE_ENV);
		 goto exit00;
	}
	
   retcode = SQLDataSources(henv, SQL_FETCH_FIRST, szDSN, sizeof(szDSN),
                            NULL, szDesc, sizeof(szDesc), NULL);
   while(retcode != SQL_NO_DATA) {
      if(retcode != SQL_SUCCESS )
		{
         PrintErrors(ci, SQL_HANDLE_ENV);
			if (retcode != SQL_SUCCESS_WITH_INFO)
				goto exit00;
		}
      rd = AllocateRowData(rs, rgbDft, RDATA_DEFAULT_BKGRND);
      SetColumnData(0, rd, szDSN);
      SetColumnData(1, rd, szDesc);
      AddRowData(rs, rd);
      retcode = SQLDataSources(henv, SQL_FETCH_NEXT, szDSN, sizeof(szDSN),
                               NULL, szDesc, sizeof(szDesc), NULL);
   }
   SQLFreeHandle(SQL_HANDLE_ENV, henv); 

   return TRUE;
   
  exit00:

   return FALSE;
}



//*---------------------------------------------------------------------------------
//| DisplayODBCDataTypes:
//|   This function will enumerate data type information.
//| Parms:
//|   in       ci                   CHILDINFO information
//| Returns:              
//|   TRUE if successful,
//|   FALSE on error
//*---------------------------------------------------------------------------------
BOOL DisplayODBCDataTypes(CHILDINFO FAR * ci)
{  
   RESULTSSET FAR *     rs;
   RETCODE              retcode;
   SWORD                cbCols;
   char                 szTitle[MAXBUFF];

   //
   // We'll use SQLGetTypeInfo for this query.  Since this function can return more
   //    than the standard types, we must first execute the query and then create
   //    the results set.
   //
   lstrcpy((LPSTR)szTitle, (LPSTR)ci->szClientTitle);
   lstrcat((LPSTR)szTitle, (LPSTR)szDash);
   lstrcat((LPSTR)szTitle, (LPSTR)szODBCDataTypes);
   retcode = SQLGetTypeInfo(ci->hstmt, SQL_ALL_TYPES);
   if(retcode != SQL_SUCCESS) {
      PrintErrors(ci, SQL_HANDLE_STMT);
      return FALSE;
   }

   if(!(cbCols = GetNumResultsCols(ci->hstmt)))
      return FALSE;

   rs = GetConnectWindowResultsNode(ci);
   if(!CreateResultsSet(rs, ci->hwndClient, ci->hInst, cbCols, (LPSTR)szTitle))
      return FALSE;  

   //
   // Set the meta data
   //
   SetMetaDataFromSql(ci->hwndOut, ci->hstmt, rs, cbCols);

   //
   // Now create the MDI child window which will hold the results.
   //
   if(!CreateResultsWindow(ci, rs)) 
      goto exit00;

   
   //
   // Loop through each data source and add it to the results set.
   //
   FetchAllRecordsToResults(ci->hwndOut, ci->hstmt, rs, cbCols, TRUE);
   SQLFreeStmt(ci->hstmt, SQL_CLOSE);

   return TRUE;
   
  exit00:
   return FALSE;
}



//*---------------------------------------------------------------------------------
//| EditPipe:
//|   This function allows the user to create a new pipe.
//| Parms:
//|   in       ci                   CHILDINFO information
//| Returns:              
//|   TRUE if successful,
//|   FALSE on error
//*---------------------------------------------------------------------------------
void EditPipe(CHILDINFO FAR * ci)
{
   HWND     fHwnd=GetFocus();

   if(-1 == DialogBoxParam(ci->hInst, 
                           MAKEINTRESOURCE(IDD_EDIT_PIPE),
                           ci->hwnd, 
                           (DLGPROC) EditPipeWndProc, (LPARAM)ci))
      MessageBox(NULL, "Could not open dialog box.",
                 "Pipe", MB_ICONEXCLAMATION);
   
   if(fHwnd)
      SetFocus(fHwnd);
}



//*------------------------------------------------------------------------
//| IsValidParms:
//|   Verify that the parameters specified are the correct comma
//|   separated format.
//| Parms:
//|   hwnd              Window handle for errors
//|   szParms           The null terminated list of parms
//| Returns:              
//|   TRUE if they are valid, FALSE on error
//*------------------------------------------------------------------------
BOOL WINAPI IsValidParms(HWND hwnd, LPSTR szParms)
{
   LPSTR       str=szParms, nstr;
   char        sztmp[MAXSQL];
   int         iNum, iCnt=0;

   lstrcpy(sztmp, szParms);
   nstr = str = strtok(sztmp, szCOMMA);
   while(str) {
      ++iCnt;
      if(!(strlen(str) == 1 && *str == '0')) {
         iNum = atoi(str);
         while(*str) {
            if(*str < '0' ||
               *str > '9')
               goto invalidint;
            ++str;
         }
         
         // It was not 0, so if atoi returned 0 it was invalid
         if(!iNum)
            goto invalidint;
      }
      
      nstr = str = strtok(NULL, szCOMMA);
   }
   
   if(iCnt <= MAXPARMS)
      return TRUE;
   else {
      szMessageBox(hwnd,
                   MB_ICONEXCLAMATION | MB_OK,
                   (LPSTR)szErrorMsgTitle,
                   iLoadString(idsTooManyParms, OutStr, MAXBUFF),
                   iCnt,
                   MAXPARMS);
      return FALSE;
   }

  invalidint:
   szMessageBox(hwnd, 
                MB_ICONEXCLAMATION | MB_OK,
                (LPSTR)szErrorMsgTitle,
                iLoadString(idsInvalidInt, OutStr, MAXBUFF),
                nstr);
   
   return FALSE;
}


//*------------------------------------------------------------------------
//| EditPipeWndProc:
//|   Message handler for creating a new pipe.
//| Parms:
//|   in       Standard window parms
//| Returns:              
//|   Depends on message
//*------------------------------------------------------------------------
BOOL EXTFUN EditPipeWndProc(HWND hDlg, unsigned msg, WPARAM wParam, LPARAM lParam)
{
   static CHILDINFO FAR *     ci;
   static                     cbNames;
   static char                szName[MAXNAME];

   switch(msg) {
     case WM_INITDIALOG:
      {
         ci = (CHILDINFO FAR *)lParam;
         CenterDialog(hDlg);

         SendMessage(GetDlgItem(hDlg, IDC_NAME), CB_LIMITTEXT, MAXPARMS, 0L);
         SendMessage(GetDlgItem(hDlg, IDE_SQL), EM_LIMITTEXT, MAXSQL, 0L);
         SendMessage(GetDlgItem(hDlg, IDE_PARMS), EM_LIMITTEXT, (MAXNAME*2), 0L);
         CheckRadioButton(hDlg, IDR_VALUE, IDR_ADDRESS, IDR_VALUE);
         SendMessage(hDlg, USER_RESETLIST, 0, 0L);
         SendMessage(hDlg, USER_SETSTATES, 0, 0L);
      }
      return TRUE;      


      // This user message is sent when the list needs to be refreshed
     case USER_RESETLIST:
      {
         LPSTR       str, addstr;

         addstr = str = (LPSTR)GetMemory(1000);
         if(!addstr)
            return TRUE;
         cbNames = 0;
         if(str) {
            SendMessage(GetDlgItem(hDlg, IDC_NAME), CB_RESETCONTENT, 0, 0L);
            if(GetPrivateProfileString((LPSTR)szPIPES, NULL, NULL,
                                       str, 1000, szLABINI)) 
               while(*addstr) {
                  ++cbNames;
                  SendMessage(GetDlgItem(hDlg, IDC_NAME),
                              CB_ADDSTRING, 0,
                              (LPARAM)(LPSTR)addstr);
                  addstr = addstr + lstrlen(addstr) + 1;
               }
         }
         ReleaseMemory(str);
         if(cbNames) 
            SendMessage(GetDlgItem(hDlg, IDC_NAME), CB_SETCURSEL, 0, 0L);
         SendMessage(hDlg, USER_SETDEFAULTS, 0, 0L);
         SendMessage(hDlg, USER_SETSTATES, 0, 0L);
      }
      return TRUE;
      
      // This user defined message will set the state of controls
     case USER_SETSTATES:
      EnableWindow(GetDlgItem(hDlg, IDB_DELETE), cbNames);
      EnableWindow(GetDlgItem(hDlg, IDE_SQL), cbNames);
      EnableWindow(GetDlgItem(hDlg, IDR_VALUE), cbNames);
      EnableWindow(GetDlgItem(hDlg, IDR_ADDRESS), cbNames);
      EnableWindow(GetDlgItem(hDlg, IDE_PARMS), cbNames);
      EnableWindow(GetDlgItem(hDlg, IDOK), cbNames);
      return TRUE;

      // This user defined message is for setting default values
     case USER_SETDEFAULTS: 
      {
         char  szParmType[10];
         char  szSql[MAXSQL];
         char  szParms[MAXBUFF];
         
         HWND  hName = GetDlgItem(hDlg, IDC_NAME);
         
         if(cbNames == 0) {               // No current driver
            SetDlgItemText(hDlg, IDE_SQL, "");
            SetDlgItemText(hDlg, IDE_PARMS, "");
            return TRUE;
         }
         SendMessage(hName, CB_GETLBTEXT,
                     (WPARAM)SendMessage(hName, CB_GETCURSEL, 0, 0L),
                     (LPARAM)(LPSTR)szName);
         if(GetPrivateProfileString(szName, szSQL, NULL, szSql, sizeof(szSql), szLABINI))
            SetDlgItemText(hDlg, IDE_SQL, szSql);
         else
            SetDlgItemText(hDlg, IDE_SQL, "");
         if(GetPrivateProfileString(szName, szPARMS, NULL, szParms, sizeof(szParms), szLABINI))
            SetDlgItemText(hDlg, IDE_PARMS, szParms);
         else
            SetDlgItemText(hDlg, IDE_PARMS, "");
         if(GetPrivateProfileString(szName, szPARMOPT, NULL, szParmType, sizeof(szParmType), szLABINI))
            if(lstrcmpi(szVALUE, szParmType) == 0)
               CheckRadioButton(hDlg, IDR_VALUE, IDR_ADDRESS, IDR_VALUE);
            else
               CheckRadioButton(hDlg, IDR_VALUE, IDR_ADDRESS, IDR_ADDRESS);
         CheckDlgButton(hDlg, IDX_DELETE, GetPrivateProfileInt(szName, szDELETEOPT, 0, szLABINI));
      }
      return TRUE;
      
     case WM_COMMAND:
      switch(GET_WM_COMMAND_ID(wParam, lParam)) {
        case IDB_NEW:
         {
            NEWPIPE  np;
            
            np.hwnd = hDlg;
            np.hInst = ci->hInst;
            NewPipe(&np);
            if(np.fSuccess) {
               lstrcpy(szName, np.szName);
               SendMessage(GetDlgItem(hDlg, IDC_NAME), CB_SETCURSEL,
                           (WPARAM)SendMessage(GetDlgItem(hDlg, IDC_NAME), CB_ADDSTRING, 
                                               0, (LPARAM)(LPSTR)szName), 0L);
               if(cbNames)
                  SendMessage(hDlg, USER_SETDEFAULTS, 0, 0L);
               else
                  SendMessage(hDlg, USER_RESETLIST, 0, 0L);
            }
         }              
         return TRUE;
         
        case IDB_DELETE:
         GetText(GetDlgItem(hDlg, IDC_NAME), szName);
         wsprintf(OutStr, szDeletePipe, (LPSTR)szName);
         if(IDOK == MessageBox(hDlg, OutStr, szEditPipe, MB_OKCANCEL)) {
            WritePrivateProfileString(szName, NULL, NULL, szLABINI);
            WritePrivateProfileString(szPIPES, szName, NULL, szLABINI);
            SendMessage(hDlg, USER_RESETLIST, 0, 0L);
         }
         return TRUE;
         
         //
         // Read in the info from the dialog, validate the parms, write to file
         //
        case IDOK:
         {
            char  szSql[MAXSQL];
            char  szParms[MAXBUFF];

            GetDlgItemText(hDlg, IDC_NAME, (LPSTR)szName, sizeof(szName));

            GetDlgItemText(hDlg, IDE_PARMS, szParms, sizeof(szParms));
            if(IsValidParms(hDlg, szParms)) {
               WritePrivateProfileString(szName, szPARMS, szParms, szLABINI);
               
               GetDlgItemText(hDlg, IDE_SQL, szSql, sizeof(szSql));
               WritePrivateProfileString(szName, szSQL, szSql, szLABINI);

               if(IsDlgButtonChecked(hDlg, IDR_VALUE))                   
                  WritePrivateProfileString(szName, szPARMOPT, szVALUE, szLABINI);
               else
                  WritePrivateProfileString(szName, szPARMOPT, szADDRESS, szLABINI);

               WritePrivateProfileString(szName, szDELETEOPT, 
                                         (IsDlgButtonChecked(hDlg, IDX_DELETE)) ? (LPSTR)"1" : (LPSTR)"0",
                                         szLABINI);
            }
         }
         return TRUE;
         
        case IDCANCEL:
         EndDialog(hDlg, IDCANCEL);;
         return TRUE;
      }
      // Now check for control notification messages
      switch(HIWORD(lParam)) {
        case CBN_SELENDOK:
        case CBN_KILLFOCUS:
         SendMessage(hDlg, USER_SETDEFAULTS, TRUE, 0L);
         return TRUE;
         
        default:
         break;
      }
      break;


     default:
      return FALSE;
   }
   return FALSE;
}


//*---------------------------------------------------------------------------------
//| NewPipe:
//|   This function allows the user to create a new pipe.
//| Parms:
//|   in       ci                   CHILDINFO information
//| Returns:              
//|   Nothing
//*---------------------------------------------------------------------------------
void NewPipe(NEWPIPE FAR * np)
{
   HWND     fHwnd=GetFocus();

   if(-1 == DialogBoxParam(np->hInst, 
                           MAKEINTRESOURCE(IDD_NEW_PIPE),
                           np->hwnd, 
                           (DLGPROC) NewPipeWndProc, (LPARAM)np))
      MessageBox(NULL, "Could not open dialog box.",
                 "Pipe", MB_ICONEXCLAMATION);
   
   if(fHwnd)
      SetFocus(fHwnd);
}


//*------------------------------------------------------------------------
//| NewPipeWndProc:
//|   Message handler for creating a new pipe.
//| Parms:
//|   in       Standard window parms
//| Returns:              
//|   Depends on message
//*------------------------------------------------------------------------
BOOL EXTFUN NewPipeWndProc(HWND hDlg, unsigned msg, WPARAM wParam, LPARAM lParam)
{
   char                       szName[MAXNAME];
   static NEWPIPE FAR *       np;

   switch(msg) {
     case WM_INITDIALOG:
      {
         np = (NEWPIPE FAR *)lParam;
         CenterDialog(hDlg);
         SendMessage(GetDlgItem(hDlg, IDE_NAME), EM_LIMITTEXT, MAXNAME, 0L);
      }
      return TRUE;      


     case WM_COMMAND:
      switch(GET_WM_COMMAND_ID(wParam, lParam)) {
        case IDOK:
         {
            char szTmp[MAXNAME];

            //
            // Don't allow names with [,], or = in them, nor any
            // reserved section names
            //
            GetText(GetDlgItem(hDlg, IDE_NAME), (LPSTR)szName);
            if(!ValidName((LPSTR)szName) ||
               !*szName ||
               !lstrcmpi((LPSTR)szName, szSCREEN) ||
               !lstrcmpi((LPSTR)szName, szFONT) ||
               !lstrcmpi((LPSTR)szName, szCONNECTOPTIONS) ||
               !lstrcmpi((LPSTR)szName, szPIPES)) {

               szMessageBox(hDlg,
                            MB_ICONEXCLAMATION | MB_OK,
                            (LPSTR)szErrorMsgTitle,
                            iLoadString(idsInvalidName, OutStr, MAXBUFF),
                            (LPSTR)szName);
               return TRUE;
            }
            if(GetPrivateProfileString(szPIPES, szName, NULL,
                                       szTmp, sizeof(szTmp), szLABINI)) 
               MessageBox(hDlg, szDuplicatePipe, szEditPipe, MB_OK);
            else {
               lstrcpy(np->szName, szName);
               np->fSuccess = TRUE;
               WritePrivateProfileString(szPIPES, szName, szInstalled, szLABINI);
               EndDialog(hDlg, IDOK);
            }
         }
         return TRUE;
         
        case IDCANCEL:
         np->fSuccess = FALSE;
         EndDialog(hDlg, IDCANCEL);
         return TRUE;
      }
      break;

     default:
      return FALSE;
   }
   return FALSE;
}



//*---------------------------------------------------------------------------------
//| HandlePipe:
//|   This function will use the active results set and run use pipes against it.
//| Parms:
//|   lpci              Connection window information
//|   lpri              Ative results set
//| Returns:              
//|   Nothing.
//*---------------------------------------------------------------------------------
void INTFUN HandlePipe(lpCHILDINFO lpci, lpRESULTSINFO lpri)
{
   HWND                 fHwnd=GetFocus();

   if(-1 == DialogBoxParam(lpci->hInst, 
                           MAKEINTRESOURCE(IDD_DO_PIPE),
                           lpci->hwnd, 
                           (DLGPROC) DoPipeWndProc, (LPARAM)(lpRESULTSINFO)lpri))
      MessageBox(NULL, "Could not open dialog box.",
                 "HandlePipe", MB_ICONEXCLAMATION);
   
   if(fHwnd)
      SetFocus(fHwnd);
}


//*------------------------------------------------------------------------
//| DoPipeWndProc:
//|   Handle dialog messages for IDD_DO_PIPE.
//| Parms:
//|   in       Standard window parms
//| Returns:              
//|   Depends on message
//*------------------------------------------------------------------------
BOOL EXTFUN DoPipeWndProc(HWND hDlg, unsigned msg, WPARAM wParam, LPARAM lParam)
{
   static CHILDINFO FAR *     ci;
   static RESULTSSET FAR *    rs;
   static SDWORD              cbPipes;

   switch(msg) {
     case WM_INITDIALOG:
      {
         lpRESULTSINFO rwi;
         rwi = (lpRESULTSINFO)lParam;
         ci = rwi->ci;
         rs = rwi->rs;
         CenterDialog(hDlg);
         cbPipes = RefreshPipeList(GetDlgItem(hDlg, IDL_PIPES));
         EnableWindow(GetDlgItem(hDlg, IDL_PIPES), (int)(cbPipes));
         EnableWindow(GetDlgItem(hDlg, IDOK), (int)(cbPipes));
      }
      return TRUE;      


     case WM_COMMAND:
      switch(GET_WM_COMMAND_ID(wParam, lParam)) {
         // User has clicked OK.  Retrieve an array of the selected indexes
         // and run the current pipe against each.  Finally see if this
         // pipe wants to delete items.
        case IDOK:
         {
            int         cbCnt;
            int FAR *   xSel;
            int         dex;
            char        szPipeName[MAXBUFF];

            Busy(TRUE);
            cbCnt = (int)SendMessage(rs->hwndList, LB_GETSELCOUNT, 0, 0L);
            xSel = (int FAR *)GetMemory(sizeof(int) * cbCnt);
            if(!xSel) {
               Busy(FALSE);
               return TRUE;
            }
            SendMessage(rs->hwndList, LB_GETSELITEMS, cbCnt, (LPARAM)(int FAR *)xSel);
            SendMessage(GetDlgItem(hDlg, IDL_PIPES), LB_GETTEXT,
                        (WPARAM)SendMessage(GetDlgItem(hDlg, IDL_PIPES), LB_GETCURSEL, 0, 0L),
                        (LPARAM)(LPSTR)szPipeName);
            DoPipe(rs, ci, (LPSTR)szPipeName, xSel, cbCnt);
            if(GetPrivateProfileInt(szPipeName, szDELETEOPT, 0, szLABINI))
               for(dex=cbCnt-1;  dex>=0;  dex--)
                  SendMessage(rs->hwndList, LB_DELETESTRING, xSel[dex], 0L);
            Busy(FALSE);
            ReleaseMemory(xSel);
         }
         return TRUE;
         
        case IDCANCEL:
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
//| RefreshPipeList:
//|   This function will reset the list of pipes based on the values returned
//|      from GetPipeName.  Having this extra level of abstraction allows us
//|      to change the location of the pipes without affecting this code.
//| Parms:
//|   in       hwnd                 Window handle to list box to fill
//| Returns:              
//|   Number of items selected
//*---------------------------------------------------------------------------------
SDWORD RefreshPipeList(HWND hDlg)
{
#define MAX_PIPE_SIZE 4000
   LPSTR    szPipes, str;
   SDWORD count=0;
   
   szPipes = (LPSTR)GetMemory(MAX_PIPE_SIZE);
   if(!szPipes) 
      return 0;
   
   SendMessage(hDlg, LB_RESETCONTENT, 0, 0L);
   GetPipeNames((LPSTR)szPipes, MAX_PIPE_SIZE);
   str = szPipes;
   while(*str) {
      SendMessage(hDlg, LB_ADDSTRING, 0, (LPARAM)(LPSTR)str);
      str += lstrlen(str) + 1;
      ++count;
   }
   if(count)
      SendMessage(hDlg, LB_SETCURSEL, 0, 0L);

   ReleaseMemory(szPipes);
   return count;
}


//*---------------------------------------------------------------------------------
//| DoPipe:
//|   This function will implement a pipe against the object which is passed in.
//| Parms:
//|   in       rs                   Pointer to results set describing data
//|   in       ci                   Connection window information
//|   in       szPipeName           Name of pipe to use
//|   in       xPipes               Array of items to pipe
//|   in       cbCnt                Number of items
//| Returns:              
//|   Nothing.
//*---------------------------------------------------------------------------------
void DoPipe(RESULTSSET FAR * rs, CHILDINFO FAR * ci, LPSTR szPipeName,
            int FAR xPipes[], int cbCnt)
{
   SDWORD            cbDataAtExec=SQL_DATA_AT_EXEC;
   int               dex;
   int               cParm;
   char              szpsql[200];
   char              szparms[35];
   char              parmopt[10];
   UWORD             cParmCnt=0;
   LPSTR             str=szparms;
   LPSTR             numstr=szparms;
   ROWDATA FAR *     rd;
   RETCODE           retcode;

   //
   // Make sure we can retrieve the pipe from the .ini file.  Also get the parameter
   //    values if they are available.
   //
   if(!GetPrivateProfileString(szPipeName, szSQL, NULL, szpsql, sizeof(szpsql), szLABINI)) {
      szWrite(ci->hwndOut, 
              GetidsString(idsPipeNotFound, OutStr, MAXBUFF), 
              (LPSTR)szPipeName);
      return;
   }
   GetPrivateProfileString(szPipeName, szPARMS, NULL, szparms, sizeof(szparms), szLABINI);
   GetPrivateProfileString(szPipeName, szPARMOPT, NULL, parmopt, sizeof(parmopt), szLABINI);

   //
   // If there are parameters to set, set each one based on user desription
   //
   if(str && *str)
      PrepareParmList(str);
   SQLFreeStmt(ci->hstmt, SQL_CLOSE);
   
   //
   // What type of parameter passing to do?  value means substitue text and execute,
   //    address means use parameter data.  The following will handle the former, the
   //    next more complicated routine will pass parameters.
   //
   if(lstrcmpi(parmopt, szVALUE) == 0) {
      DoPipeByValue(rs, ci, szpsql, str, xPipes, cbCnt, (LPSTR)szPipeName);
      return;
   }
   
   //
   // Now prepare the user's statement, return on error
   //
   retcode = SQLPrepare(ci->hstmt, szpsql, SQL_NTS);
   if(retcode != SQL_SUCCESS) {
      PrintErrors(ci, SQL_HANDLE_STMT);
      return;
   }
   
   //
   // For each parameter, make sure it's in our range, then see which mode we want,
   //    address (param data) or value (textual substitution).
   //
   while(*str) {
      ++cParmCnt;
      cParm = lpatoi(str);
      if(cParm > rs->cbColumns) 
         szWrite(ci->hwndOut, 
                 GetidsString(idsInvalidParamValue, OutStr, MAXBUFF), 
                 cParm, (LPSTR)szPipeName);
      else {
         retcode = SQLBindParameter(ci->hstmt, 
                                    cParmCnt, SQL_PARAM_INPUT,
                                    SQL_C_CHAR, SQL_CHAR, 
                                    rs->md[cParm-1].precision,
                                    rs->md[cParm-1].scale, 
                                    (PTR FAR *)(cParm - 1), 
                                    rs->md[cParm-1].precision,
                                    &cbDataAtExec);
         if(retcode != SQL_SUCCESS) 
            PrintErrors(ci, SQL_HANDLE_STMT);
      }
      str += lstrlen(str) + 1;
   }  


   //
   // For each row selected, retrieve the row data structure associated with it,
   //    then do an execute.  When prompted for SQL_NEED_DATA, substitute the
   //    correct parameter address.
   //
   for(dex=0;  dex<cbCnt;  dex++) { 
      int      cNeedParm;
      rd = (ROWDATA FAR *)SendMessage(rs->hwndList, LB_GETITEMDATA, (WPARAM)xPipes[dex], 0L);
      retcode = SQLExecute(ci->hstmt);
      switch(retcode) {
         //
         // User had parameter data which we are being prompted for.  Since we
         //    did the SQLSetParam using the index number, we simply use that
         //    value to index into our column data and give the driver what
         //    it requires.
         //
        case SQL_NEED_DATA:
         retcode = SQLParamData(ci->hstmt, (PTR FAR *)&cNeedParm);
         while(retcode == SQL_NEED_DATA) {
            retcode = SQLPutData(ci->hstmt, rd->cd[cNeedParm].szCols, SQL_NTS);
            retcode = SQLParamData(ci->hstmt, (PTR FAR *)&cNeedParm);
         }
         break;
         
        case SQL_SUCCESS:
         CheckForResults(ci);
         break;
         
        default:
         PrintErrors(ci, SQL_HANDLE_STMT);
         break;
      }
   }
   
   SQLFreeStmt(ci->hstmt, SQL_CLOSE);
   return;
}



//*---------------------------------------------------------------------------------
//| PrepareParmList:
//|   The user will enter a list of numbers separated by columns which will
//|   designate which parms go for what marker.  We will turn this list into
//|   a double-null terminated list which can be used later for retrieval.
//| Parms:
//|   in       str                  Pointer to string to work on
//| Returns:              
//|   Nothing.
//*---------------------------------------------------------------------------------
void PrepareParmList(LPSTR str)
{
   LPSTR tmpstr=str;
   LPSTR lststr=tmpstr;

   //
   // Convert parm list into a double-null terminated list
   //
   while(tmpstr) {
      if((tmpstr = _fstrchr(str, ','))) {
         lststr = tmpstr + 1;
         *tmpstr++ = '\0';
      }
      else {
         lststr += lstrlen(lststr) + 1;
         *lststr = '\0';
      }
   }
}        



//*---------------------------------------------------------------------------------
//| DoPipeByValue:
//|   This function will process all of the selcted values by creating a
//|   statement which has all parameters embedded in it.
//|
//|   Note:    There are some servers which use a semi-colon for the name of
//|            a stored procedure, but which cannot handle doing a drop of the
//|            object with this name.  If the pipe name is the reserved name
//|            of "Drop Procedure (with semi-colon)" then we will strip off the
//|            name since this can't really be done any other way.
//| Parms:
//|   in       rs                   Results set pointer
//|   in       ci                   Child information
//|   in       szUserSQL               Statement with parameter markers
//|   in       szParms              Parameter list, double null terminated
//|   in       xPipes               Array of indexes to use for param data
//|   in       cbCnt                Number of records to process
//|   in       szPipeName           Pipe names
//| Returns:              
//|   Nothing.
//*---------------------------------------------------------------------------------
void DoPipeByValue(RESULTSSET FAR * rs, CHILDINFO FAR * ci, LPSTR szUserSQL,
                   LPSTR szParms, int FAR xPipes[], int cbCnt, LPSTR szPipeName)
{
   char              szUserSQLCopy[300];
   char              sqlstmt[300];
   LPSTR             szParmStrOut;
   LPSTR             szParmStrIn;
   LPSTR             szParmStrLast;
   LPSTR             str=szParms;
   int               dex;
   int               cParm;
   ROWDATA FAR *     rd;
   BOOL              fSemiProc=FALSE;
   
   // Handle special case of a procedure name with a semi-colon
   if(lstrcmp(szPipeName, szDROPPROCSEMI) == 0)
      fSemiProc = TRUE;
   
   //
   // For each record selected, create a statement which can be executed by finding
   //    parameter markers and replacing them at run time.
   //
   for(dex=0;  dex<cbCnt;  dex++) {
      _fmemset(sqlstmt, 0, sizeof(sqlstmt));
      _fmemset(szUserSQLCopy, 0, sizeof(szUserSQLCopy));
      lstrcpy(szUserSQLCopy, szUserSQL);
      szParmStrOut = sqlstmt;
      szParmStrIn = szUserSQLCopy;
      szParmStrLast = szParmStrIn;
      str = szParms;
      rd = (ROWDATA FAR *)SendMessage(rs->hwndList, LB_GETITEMDATA, (WPARAM)xPipes[dex], 0L);
      while(*str) {
         cParm = lpatoi(str);
         if(cParm > rs->cbColumns) 
            szWrite(ci->hwndOut, 
                    GetidsString(idsInvalidParamValue, OutStr, MAXBUFF), 
                    cParm, (LPSTR)szPipeName);
         else if(szParmStrIn && *szParmStrIn) {
            if((szParmStrIn = _fstrchr(szParmStrIn, '?'))) {
               *szParmStrIn++ = '\0';
               lstrcpy(szParmStrOut, szParmStrLast);
               _fstrcat(szParmStrOut, rd->cd[cParm-1].szCols);
               // Remove semi-colon for special case of drop procedure
               if(fSemiProc) {
                  LPSTR    str = _fstrchr(szParmStrOut, ';');
                  if(str)
                     *str = '\0';
               }
               szParmStrLast = szParmStrIn; 
            }
            else
               lstrcpy(szParmStrOut, szParmStrLast);              // end of list
         }
         str += lstrlen(str) + 1;
      }
      if(*szParmStrLast)
         _fstrcat(szParmStrOut, szParmStrLast);
      ExecuteCmds(ci, sqlstmt);
   }
   
   return;
}
