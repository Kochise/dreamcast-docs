Option Explicit

'-----------------------------------------------------------------------------------------------------
' VBODBC
' Version 1.1 3/4/95
' Copyright 1995 Clarity Consulting, Inc.
' May not be sold or otherwise reproduced without express written consent
' of Clarity Consulting, Inc.
'
' Craig Goren
' Clarity Consulting, Inc.
' CIS:      72773,1062
' Internet: cgoren@claritycnslt.com
'
' VBODBC is a Visual Basic library that provides an easy method of accessing
' data from an ODBC data source.  It has the following characteristics:
'   - Maintains all database handles internally.
'   - Supports asynchronous query execution (if the driver supports it), so the user can perform tasks in other applications while the server is processing.
'   - A global error buffer, VBODBC_LastErr, containing detailed information regarding the last ODBC error.
'   - Supports only one open database and one open SQL statement at a time.
'   - Has been tested only with SQL Server, Access, and Oracle.
' It also provides includes all ODBC constant and function declarations.
'
' Comments, suggestions, and consulting opportunities welcome!
'
' Files:
'       1. VBODBC.BAS       VB module
'       2. VBODBC1.FRM      VB logon form
'       3. VBODBC2.FRM      VB query executing form
'
' APIs:
'       1. VBODBC_OpenDatabaseDialog() - Establishes an ODBC database connection, prompting the user for connection information.
'       2. VBODBC_OpenDatabase() - Establishes an ODBC database connection without prompting, for use with integrated security and custom dialogs.
'       3. VBODBC_OpenSqlProcDialog() - Executes a stored procedure statement.
'       4. VBODBC_OpenSqlStmtDialog() - Executes a SQL statement.
'       5. VBODBC_GetNextRow() - Retrieves another row of the SQL statement’s result set.  The row is retrieved into a variant array parameter, with each element corresponding the equivalent column number.  Element 0 contains all column values separated by tabs.
'       6. VBODBC_CloseSqlStmt() - Closes the SQL statement.
'       7. VBODBC_CloseDatabase() - Closes the database connection.
'
' Instructions:
'       1. Add VBODBC.BAS, VBODBC1.FRM, VBODBC2.FRM to your project.
'       2. Verify that you have a proper ODBC data source configured.
'       3. Follow the function flowchart within your code.  Note that only one SQL statement and one database connection can be active at a time, so that you don’t have to maintain any handles.
'       4. Inspect the global structure VBODBC_LastErr if you encounter an error.
'       5. Inspect the global structure VBODBC_ColDesc for a description of the last SQL statements columns.
'-----------------------------------------------------------------------------------------------------




'-----------------------------------------------------------------------
' Specific VBODBC Declarations and Constants
'-----------------------------------------------------------------------
'buffer for communication with logon form
Type VBODBC_LogonType
    'in
    AppName As String       'the application name
    'out
    ConnStrOut As String    'the returned full ODBC connection string
    Connected As Integer    'true if connected
    'in/out
    UID As String           'user id
    PWD As String           'password
    DSN As String           'data source name
End Type
Global VBODBC_Logon As VBODBC_LogonType  'the internal connection handle

'buffer for communication with sql execute form
Type VBODBC_SqlStmtType
    'in
    StmtType As Integer         'indicates if buffer holding procsdure or dynamic sql; VBODBC_STMTTYPE_SQL or VBODBC_STMTTYPE_PROC
    Parms(100) As String        'paramaters, if a proc.  Arbitrary 100 limit because can't pass variable length arrays in Types
    NumParms As Integer         'Number of parameters in Parms
    SqlStmt As String           'sql statement to run
    Caption As String           'the caption to display on the form
    'out
    ResCode As Integer          'result code of sql
    Cancelled As Integer        'true if user pressed cancel
End Type
Global Const VBODBC_STMTTYPE_SQL = 0
Global Const VBODBC_STMTTYPE_PROC = 1
Global VBODBC_SqlStmt As VBODBC_SqlStmtType


'state of connection, kept so programmers don't do things
'out of order, e.g. open a statement when one is already open
Global VBODBC_SqlState As Integer
'values of VBODBC_SQLSATE
Global Const VBODBC_SQLSTATE_CLOSED = 0    'nothing initialized, everything closed
Global Const VBODBC_SQLSTATE_OPENDB = 1    'database open, no SQL statement
Global Const VBODBC_SQLSTATE_OPENSTMT = 2  'database and SQL statement open

'description of result set columns
Type VBODBC_ColDescType
    ColName As String       'name of column
    SqlType As Integer      'ODBC type code of column data type
    ColLen As Long       'ODBC length of column
End Type
Global VBODBC_ColDesc() As VBODBC_ColDescType 'holds last results set's desc
Global VBODBC_NumCols As Integer 'stores number of cols in last result set


'error information structure
Type VBODBC_ErrType
    AllErrorInfo As String              'concationation of all error info, seperated by CRs, so it can be easily places in text file of msgbox
    'ODBC specific stuff
    ErrorMsg As String                  'the ODBC error message
    SqlErrResCodeStr As String          'the symbolic constant of the ODBC error code
    sqlstate As String                  'the ODBC Sql State
    NativeError As Long                 'the ODBC native error desc
    'VBODBC specific stuff
    VBODBCFunctionName As String        'VBODBC function error was detected
    ODBCFunctionName As String          'ODBC Function call name, if applicable
    ODBCFunctionResCodeStr As String    'ODBC FunctionName return code, if applicable
    OtherInfo As String                 'any other info supplied caller of VBODBC_DescribeError, e.g. the SqlStmt
End Type
'stores information of last ODBC error
Global VBODBC_LastErr As VBODBC_ErrType


' environment handle
Global VBODBC_henv As Long
'database handle
Global VBODBC_hdbc  As Long
'statement handle
Global VBODBC_hstmt As Long

'special error from internal VBODBC error
'used where normally SQL_ errors occur
Global Const SQL_VBODBC_ERR = -995
Global Const SQL_VBODBC_CANCELLED = -994


'Windows API, aliased so they don't conflict with other project definitions
Declare Function VBODBC_GetFocus Lib "User" Alias "GetFocus" () As Integer
Declare Function VBODBC_GetParent Lib "User" Alias "GetParent" (ByVal hwnd%) As Integer



'
'|========================================================================|
'| ODBC Module Core Definitions                                           |
'|========================================================================|
'
'  ODBC Core API's Definitions
'
Declare Function SQLAllocConnect Lib "odbc.dll" (ByVal henv&, phdbc&) As Integer
Declare Function SQLAllocEnv Lib "odbc.dll" (phenv&) As Integer
Declare Function SQLAllocStmt Lib "odbc.dll" (ByVal hdbc&, phstmt&) As Integer
Declare Function SQLBindCol Lib "odbc.dll" (ByVal hstmt&, ByVal icol%, ByVal fCType%, ByVal rgbValue As Any, ByVal cbValueMax&, pcbValue&) As Integer
Declare Function SQLCancel Lib "odbc.dll" (ByVal hstmt&) As Integer
Declare Function SQLColAttributes Lib "odbc.dll" (ByVal hstmt&, ByVal icol%, ByVal fDescType%, rgbDesc As Any, ByVal cbDescMax%, pcbDesc%, pfDesc&) As Integer
Declare Function SQLConnect Lib "odbc.dll" (ByVal hdbc&, ByVal szDSN$, ByVal cbDSN%, ByVal szUID$, ByVal cbUID%, ByVal szAuthStr$, ByVal cbAuthStr%) As Integer
Declare Function SQLDescribeCol Lib "odbc.dll" (ByVal hstmt&, ByVal icol%, ByVal szColName$, ByVal cbColNameMax%, pcbColName%, pfSqlType%, pcbColDef&, pibScale%, pfNullable%) As Integer
Declare Function SQLDisconnect Lib "odbc.dll" (ByVal hdbc&) As Integer
Declare Function SQLError Lib "odbc.dll" (ByVal henv&, ByVal hdbc&, ByVal hstmt&, ByVal szSqlState$, pfNativeError&, ByVal szErrorMsg$, ByVal cbErrorMsgMax%, pcbErrorMsg%) As Integer
Declare Function SQLExecDirect Lib "odbc.dll" (ByVal hstmt&, ByVal szSqlStr$, ByVal cbSqlStr&) As Integer
Declare Function SQLExecute Lib "odbc.dll" (ByVal hstmt&) As Integer
Declare Function SQLFetch Lib "odbc.dll" (ByVal hstmt&) As Integer
Declare Function SQLFreeConnect Lib "odbc.dll" (ByVal hdbc&) As Integer
Declare Function SQLFreeEnv Lib "odbc.dll" (ByVal henv&) As Integer
Declare Function SQLFreeStmt Lib "odbc.dll" (ByVal hstmt&, ByVal fOption%) As Integer
Declare Function SQLGetCursorName Lib "odbc.dll" (ByVal hstmt&, ByVal szCursor$, ByVal cbCursorMax%, pcbCursor%) As Integer
Declare Function SQLNumResultCols Lib "odbc.dll" (ByVal hstmt&, pccol%) As Integer
Declare Function SQLPrepare Lib "odbc.dll" (ByVal hstmt&, ByVal szSqlStr$, ByVal cbSqlStr&) As Integer
Declare Function SQLRowCount Lib "odbc.dll" (ByVal hstmt&, pcrow&) As Integer
Declare Function SQLSetCursorName Lib "odbc.dll" (ByVal hstmt&, ByVal szCursor$, ByVal cbCursor%) As Integer
Declare Function SQLSetParam Lib "odbc.dll" (ByVal hstmt&, ByVal ipar%, ByVal fCType%, ByVal fSqlType%, ByVal cbColDef&, ByVal ibScale%, rgbValue As Any, pcbValue&) As Integer
Declare Function SQLTransact Lib "odbc.dll" (ByVal henv&, ByVal hdbc&, ByVal fType%) As Integer


'
'|========================================================================|
'| ODBC Module Extended Definitions                                       |
'|========================================================================|
'
'  ODBC Extended API's Definitions
'
'  Level 1 Prototypes
'
'Declare Function SQLBindParameter Lib "odbc.dll" (ByVal hstmt&, ByVal ipar%, ByVal fParamType%, ByVal fCType%, ByVal fSqlType%, ByVal cbColDef&, ByVal ibScale%, rgbValue As Any, ByVal cbValueMax&, pcbValue As Long) As Integer
Declare Function SQLBindParameter Lib "odbc.dll" (ByVal hstmt&, ByVal ipar%, ByVal fParamType%, ByVal fCType%, ByVal fSqlType%, ByVal cbColDef&, ByVal ibScale%, ByVal rgbValue As String, ByVal cbValueMax&, pcbValue As Long) As Integer
Declare Function SQLColumns Lib "odbc.dll" (ByVal hstmt&, ByVal szTblQualifier&, ByVal cbTblQualifier%, ByVal szTblOwner&, ByVal cbTblOwner%, ByVal szTblName&, ByVal cbTblName%, ByVal szColName&, ByVal cbColName%) As Integer
Declare Function SQLDriverConnect Lib "odbc.dll" (ByVal hdbc&, ByVal hwnd%, ByVal szCSIn$, ByVal cbCSIn%, ByVal szCSOut$, ByVal cbCSMax%, cbCSOut%, ByVal fDrvrComp%) As Integer
Declare Function SQLGetConnectOption Lib "odbc.dll" (ByVal hdbc&, ByVal fOption%, pvParam As Any) As Integer
Declare Function SQLGetData Lib "odbc.dll" (ByVal hstmt&, ByVal icol%, ByVal fCType%, ByVal rgbValue As Any, ByVal cbValueMax&, pcbValue&) As Integer
Declare Function SQLGetFunctions Lib "odbc.dll" (ByVal hdbc&, ByVal fFunction%, pfExists%) As Integer
Declare Function SQLGetInfo Lib "odbc.dll" (ByVal hdbc&, ByVal fInfoType%, rgbInfoValue As Any, ByVal cbInfoMax%, cbInfoOut%) As Integer
Declare Function SQLGetStmtOption Lib "odbc.dll" (ByVal hstmt&, ByVal fOption%, pvParam As Any) As Integer
Declare Function SQLGetTypeInfo Lib "odbc.dll" (ByVal hstmt&, ByVal fSqlType%) As Integer
Declare Function SQLParamData Lib "odbc.dll" (ByVal hstmt&, prgbValue As Any) As Integer
Declare Function SQLPutData Lib "odbc.dll" (ByVal hstmt&, rgbValue As Any, ByVal cbValue&) As Integer
Declare Function SQLSetConnectOption Lib "odbc.dll" (ByVal hdbc&, ByVal fOption%, ByVal vParam&) As Integer
Declare Function SQLSetStmtOption Lib "odbc.dll" (ByVal hstmt&, ByVal fOption%, ByVal vParam&) As Integer
Declare Function SQLSpecialColumns Lib "odbc.dll" (ByVal hstmt&, ByVal fColType%, ByVal szTblQualifier&, ByVal cbTblQualifier%, ByVal szTblOwner$, ByVal cbTblOwner%, ByVal szTblName$, ByVal cbTblName%, ByVal fScope%, ByVal fNullable%) As Integer
Declare Function SQLStatistics Lib "odbc.dll" (ByVal hstmt&, ByVal szTblQualifier&, ByVal cbTblQualifier%, ByVal szTblOwner&, ByVal cbTblOwner%, ByVal szTblName&, ByVal cbTblName%, ByVal fUnique%, ByVal fAccuracy%) As Integer
Declare Function SQLTables Lib "odbc.dll" (ByVal hstmt&, ByVal szTblQualifier&, ByVal cbTblQualifier%, ByVal szTblOwner&, ByVal cbTblOwner%, ByVal szTblName&, ByVal cbTblName%, ByVal szTblType&, ByVal cbTblType%) As Integer

'  Level 2 Prototypes
'
Declare Function SQLBrowseConnect Lib "odbc.dll" (ByVal hdbc&, ByVal szConnStrIn$, ByVal cbConnStrIn%, ByVal szConnStrOut$, ByVal cbConnStrOutMax%, pcbConnStrOut%) As Integer
Declare Function SQLColumnPrivileges Lib "odbc.dll" (ByVal hstmt&, ByVal szTQf$, ByVal cbTQf%, ByVal szTOwn$, ByVal cbTOwn%, ByVal szTName$, ByVal cbTName%, ByVal szColName$, ByVal cbColName%) As Integer
Declare Function SQLDrivers Lib "odbc.dll" (ByVal henv&, ByVal fDirection%, ByVal szDriverDesc$, ByVal cbDriverDescMax%, pcbDriverDesc%, ByVal szDriverAttr$, ByVal cbDrvrAttrMax%, pcbDrvrAttr%) As Integer
Declare Function SQLDataSources Lib "odbc.dll" (ByVal henv&, ByVal fDirection%, ByVal szDSN$, ByVal cbDSNMax%, pcbDSN%, ByVal szDescription$, ByVal cbDescriptionMax%, pcbDescription%) As Integer
Declare Function SQLDescribeParam Lib "odbc.dll" (ByVal hstmt&, ByVal ipar%, pfSqlType%, pcbColDef&, pibScale%, pfNullable%) As Integer
Declare Function SQLExtendedFetch Lib "odbc.dll" (ByVal hstmt&, ByVal fFetchType%, ByVal irow&, pcrow&, rgfRowStatus%) As Integer
Declare Function SQLForeignKeys Lib "odbc.dll" (ByVal hstmt&, ByVal PTQual&, ByVal PTQual%, ByVal PTOwnr&, ByVal PTOwnr%, ByVal PTName&, ByVal PTName%, ByVal FTQual&, ByVal FTQf%, ByVal FTOwnr&, ByVal FTOwnr%, ByVal FTName&, ByVal FTName%) As Integer
Declare Function SQLMoreResults Lib "odbc.dll" (ByVal hstmt&) As Integer
Declare Function SQLNativeSQl Lib "odbc.dll" (ByVal hdbc&, ByVal szSqlStrIn$, ByVal cbSqlStrIn&, ByVal szSqlStr$, ByVal cbSqlStrMax&, pcbSqlStr&) As Integer
Declare Function SQLNumParams Lib "odbc.dll" (ByVal hstmt&, pcpar%) As Integer
Declare Function SQLParamOptions Lib "odbc.dll" (ByVal hstmt&, ByVal crow%, pirow&) As Integer
Declare Function SQLPrimaryKeys Lib "odbc.dll" (ByVal hstmt&, ByVal szTblQualifier&, ByVal cbTblQualifier%, ByVal szTblOwner&, ByVal cbTblOwner%, ByVal szTblName&, ByVal cbTblName%) As Integer
Declare Function SQLProcedureColumns Lib "odbc.dll" (ByVal hstmt&, ByVal szProcQualifier&, ByVal cbProcQualifier%, ByVal szProcOwner&, ByVal cbProcOwner%, ByVal szProcName&, ByVal cbProcName%, ByVal szColName&, ByVal cbColName%) As Integer
Declare Function SQLProcedures Lib "odbc.dll" (ByVal hstmt&, ByVal szProcQualifier&, ByVal cbProcQualifier%, ByVal szProcOwner&, ByVal cbProcOwner%, ByVal szProcName&, ByVal cbProcName%) As Integer
Declare Function SQLSetPos Lib "odbc.dll" (ByVal hstmt&, ByVal irow%, ByVal fOption%, ByVal fLock%) As Integer
Declare Function SQLSetScrollOptions Lib "odbc.dll" (ByVal hstmt&, ByVal fConcurrency%, ByVal crowKeyset&, ByVal crowRowset%) As Integer
Declare Function SQLTablePrivileges Lib "odbc.dll" (ByVal hstmt&, ByVal szTblQualifier&, ByVal cbTblQualifier%, ByVal szTblOwner&, ByVal cbTblOwner%, ByVal szTblName&, ByVal cbTblName%) As Integer



'
'|========================================================================|
'| ODBC Global Core Definitions                                           |
'|========================================================================|
'
'  ODBC Constants/Types
'
'  generally useful constants
'
Global Const SQL_NTS = -3                  '  NTS = Null Terminated String
Global Const SQL_SQLSTATE_SIZE = 5         '  size of SQLSTATE
Global Const SQL_MAX_MESSAGE_LENGTH = 512  '  message buffer size
Global Const SQL_MAX_DSN_LENGTH = 32       '  maximum data source name size

'  RETCODEs
'
Global Const SQL_ERROR = -1
Global Const SQL_INVALID_HANDLE = -2
Global Const SQL_NO_DATA_FOUND = 100
Global Const SQL_SUCCESS = 0
Global Const SQL_SUCCESS_WITH_INFO = 1

'  SQLFreeStmt defines
'
Global Const SQL_CLOSE = 0
Global Const SQL_DROP = 1
Global Const SQL_UNBIND = 2
Global Const SQL_RESET_PARAMS = 3

'  SQLSetParam defines
'
Global Const SQL_C_DEFAULT = 99

'  SQLTransact defines
'
Global Const SQL_COMMIT = 0
Global Const SQL_ROLLBACK = 1

'  Standard SQL datatypes, using ANSI type numbering
'
Global Const SQL_CHAR = 1
Global Const SQL_NUMERIC = 2
Global Const SQL_DECIMAL = 3
Global Const SQL_INTEGER = 4
Global Const SQL_SMALLINT = 5
Global Const SQL_FLOAT = 6
Global Const SQL_REAL = 7
Global Const SQL_DOUBLE = 8
Global Const SQL_VARCHAR = 12

Global Const SQL_TYPE_MIN = 1
Global Const SQL_TYPE_NULL = 0
Global Const SQL_TYPE_MAX = 12

'  C datatype to SQL datatype mapping    SQL types
'
Global Const SQL_C_CHAR = SQL_CHAR         '  CHAR, VARCHAR, DECIMAL, NUMERIC
Global Const SQL_C_LONG = SQL_INTEGER      '  INTEGER
Global Const SQL_C_SHORT = SQL_SMALLINT    '  SMALLINT
Global Const SQL_C_FLOAT = SQL_REAL        '  REAL
Global Const SQL_C_DOUBLE = SQL_DOUBLE     '  FLOAT, DOUBLE

'  NULL status constants.  These are used in SQLColumns, SQLColAttributes,
'  SQLDescribeCol, and SQLSpecialColumns to describe the nullablity of a
'  column in a table.  SQL_NULLABLE_UNKNOWN can be returned only by
'  SQLDescribeCol or SQLColAttributes.  It is used when the DBMS's meta-data
'  does not contain this info.
'
Global Const SQL_NO_NULLS = 0
Global Const SQL_NULLABLE = 1
Global Const SQL_NULLABLE_UNKNOWN = 2

'  Special length values
'
Global Const SQL_NULL_DATA = -1
Global Const SQL_DATA_AT_EXEC = -2

'  SQLColAttributes defines
'
Global Const SQL_COLUMN_COUNT = 0
Global Const SQL_COLUMN_NAME = 1
Global Const SQL_COLUMN_TYPE = 2
Global Const SQL_COLUMN_LENGTH = 3
Global Const SQL_COLUMN_PRECISION = 4
Global Const SQL_COLUMN_SCALE = 5
Global Const SQL_COLUMN_DISPLAY_SIZE = 6
Global Const SQL_COLUMN_NULLABLE = 7
Global Const SQL_COLUMN_UNSIGNED = 8
Global Const SQL_COLUMN_MONEY = 9
Global Const SQL_COLUMN_UPDATABLE = 10
Global Const SQL_COLUMN_AUTO_INCREMENT = 11
Global Const SQL_COLUMN_CASE_SENSITIVE = 12
Global Const SQL_COLUMN_SEARCHABLE = 13
Global Const SQL_COLUMN_TYPE_NAME = 14
' #if ODBC 2.00
Global Const SQL_COLUMN_TABLE_NAME = 15
Global Const SQL_COLUMN_OWNER_NAME = 16
Global Const SQL_COLUMN_QUALIFIER_NAME = 17
Global Const SQL_COLUMN_LABEL = 18
' #endif ODBC 2.00
'#define SQL_COLATT_OPT_MAX          SQL_COLUMN_LABEL

'  SQLColAttributes subdefines for SQL_COLUMN_UPDATABLE
'
Global Const SQL_ATTR_READONLY = 0
Global Const SQL_ATTR_WRITE = 1
Global Const SQL_ATTR_READWRITE_UNKNOWN = 2

'  SQLColAttributes subdefines for SQL_COLUMN_SEARCHABLE
'  These are also used by SQLGetInfo
'
Global Const SQL_UNSEARCHABLE = 0
Global Const SQL_LIKE_ONLY = 1
Global Const SQL_ALL_EXCEPT_LIKE = 2
Global Const SQL_SEARCHABLE = 3

'  SQLError defines
'
Global Const SQL_NULL_HENV = 0
Global Const SQL_NULL_HDBC = 0
Global Const SQL_NULL_HSTMT = 0

'
'|========================================================================|
'| ODBC Global Extended Definitions                                       |
'|========================================================================|

' Level 1 Definitions/Functions
' Generally useful constants
'
Global Const SQL_MAX_OPTION_STRING_LENGTH = 256

' Additional return codes
'
Global Const SQL_STILL_EXECUTING = 2
Global Const SQL_NEED_DATA = 99

' SQL extended datatypes
'
Global Const SQL_DATE = 9
Global Const SQL_TIME = 10
Global Const SQL_TIMESTAMP = 11
Global Const SQL_LONGVARCHAR = -1
Global Const SQL_BINARY = -2
Global Const SQL_VARBINARY = -3
Global Const SQL_LONGVARBINARY = -4
Global Const SQL_BIGINT = -5
Global Const SQL_TINYINT = -6
Global Const SQL_BIT = -7
Global Const SQL_TYPE_DRIVER_START = -80

' C datatype to SQL datatype mapping
'
' #if ODBC 2.00
Global Const SQL_SIGNED_OFFSET = -20
Global Const SQL_UNSIGNED_OFFSET = -22
' #endif ODBC 2.00
'
Global Const SQL_C_DATE = SQL_DATE
Global Const SQL_C_TIME = SQL_TIME
Global Const SQL_C_TIMESTAMP = SQL_TIMESTAMP
Global Const SQL_C_BINARY = SQL_BINARY
Global Const SQL_C_BIT = SQL_BIT
Global Const SQL_C_TINYINT = SQL_TINYINT
' #if ODBC 2.00
Global Const SQL_C_SLONG = SQL_C_LONG + SQL_SIGNED_OFFSET
Global Const SQL_C_SSHORT = SQL_C_SHORT + SQL_SIGNED_OFFSET
Global Const SQL_C_STINYINT = SQL_TINYINT + SQL_SIGNED_OFFSET
Global Const SQL_C_ULONG = SQL_C_LONG + SQL_UNSIGNED_OFFSET
Global Const SQL_C_USHORT = SQL_C_SHORT + SQL_UNSIGNED_OFFSET
Global Const SQL_C_UTINYINT = SQL_TINYINT + SQL_UNSIGNED_OFFSET
Global Const SQL_C_BOOKMARK = SQL_C_ULONG
' #endif ODBC 2.00

Global Const SQL_ALL_TYPES = 0
'
'  Date/Time/Timestamp Structs
'
Type DATE_STRUCT
  year      As Integer
  month     As Integer
  day       As Integer
End Type

Type TIME_STRUCT
  hour      As Integer
  minute    As Integer
  second    As Integer
End Type

Type TIMESTAMP_STRUCT
  year      As Integer
  month     As Integer
  day       As Integer
  hour      As Integer
  minute    As Integer
  second    As Integer
  fraction  As Long
End Type

' Options for SQLDriverConnect
'
Global Const SQL_DRIVER_NOPROMPT = 0
Global Const SQL_DRIVER_COMPLETE = 1
Global Const SQL_DRIVER_PROMPT = 2
Global Const SQL_DRIVER_COMPLETE_REQUIRED = 3

' Special return values for SQLGetData
'
Global Const SQL_NO_TOTAL = -4

' SQLSetParam extensions
' #if ODBC 2.00
Global Const SQL_DEFAULT_PARAM = -5
Global Const SQL_IGNORE = -6
Global Const SQL_LEN_DATA_AT_EXEC_OFFSET = -100
' #endif ODBC 2.00

' Defines for SQLGetFunctions
' Core Functions
'
Global Const SQL_API_SQLALLOCCONNECT = 1
Global Const SQL_API_SQLALLOCENV = 2
Global Const SQL_API_SQLALLOCSTMT = 3
Global Const SQL_API_SQLBINDCOL = 4
Global Const SQL_API_SQLCANCEL = 5
Global Const SQL_API_SQLCOLATTRIBUTES = 6
Global Const SQL_API_SQLCONNECT = 7
Global Const SQL_API_SQLDESCRIBECOL = 8
Global Const SQL_API_SQLDISCONNECT = 9
Global Const SQL_API_SQLERROR = 10
Global Const SQL_API_SQLEXECDIRECT = 11
Global Const SQL_API_SQLEXECUTE = 12
Global Const SQL_API_SQLFETCH = 13
Global Const SQL_API_SQLFREECONNECT = 14
Global Const SQL_API_SQLFREEENV = 15
Global Const SQL_API_SQLFREESTMT = 16
Global Const SQL_API_SQLGETCURSORNAME = 17
Global Const SQL_API_SQLNUMRESULTCOLS = 18
Global Const SQL_API_SQLPREPARE = 19
Global Const SQL_API_SQLROWCOUNT = 20
Global Const SQL_API_SQLSETCURSORNAME = 21
Global Const SQL_API_SQLSETPARAM = 22
Global Const SQL_API_SQLTRANSACT = 23
Global Const SQL_NUM_FUNCTIONS = 23
Global Const SQL_EXT_API_START = 40

' Level 1 Functions
'
Global Const SQL_API_SQLCOLUMNS = 40
Global Const SQL_API_SQLDRIVERCONNECT = 41
Global Const SQL_API_SQLGETCONNECTOPTION = 42
Global Const SQL_API_SQLGETDATA = 43
Global Const SQL_API_SQLGETFUNCTIONS = 44
Global Const SQL_API_SQLGETINFO = 45
Global Const SQL_API_SQLGETSTMTOPTION = 46
Global Const SQL_API_SQLGETTYPEINFO = 47
Global Const SQL_API_SQLPARAMDATA = 48
Global Const SQL_API_SQLPUTDATA = 49
Global Const SQL_API_SQLSETCONNECTOPTION = 50
Global Const SQL_API_SQLSETSTMTOPTION = 51
Global Const SQL_API_SQLSPECIALCOLUMNS = 52
Global Const SQL_API_SQLSTATISTICS = 53
Global Const SQL_API_SQLTABLES = 54

' Level 2 Functions
'
Global Const SQL_API_SQLBROWSECONNECT = 55
Global Const SQL_API_SQLCOLUMNPRIVILEGES = 56
Global Const SQL_API_SQLDATASOURCES = 57
Global Const SQL_API_SQLDESCRIBEPARAM = 58
Global Const SQL_API_SQLEXTENDEDFETCH = 59
Global Const SQL_API_SQLFOREIGNKEYS = 60
Global Const SQL_API_SQLMORERESULTS = 61
Global Const SQL_API_SQLNATIVESQL = 62
Global Const SQL_API_SQLNUMPARAMS = 63
Global Const SQL_API_SQLPARAMOPTIONS = 64
Global Const SQL_API_SQLPRIMARYKEYS = 65
Global Const SQL_API_SQLPROCEDURECOLUMNS = 66
Global Const SQL_API_SQLPROCEDURES = 67
Global Const SQL_API_SQLSETPOS = 68
Global Const SQL_API_SQLSETSCROLLOPTIONS = 69
Global Const SQL_API_SQLTABLEPRIVILEGES = 70
' #if ODBC 2.00
Global Const SQL_API_SQLDRIVERS = 71
Global Const SQL_API_SQLBINDPARAMETER = 72
' #endif ODBC 2.00
Global Const SQL_EXT_API_LAST = 72
Global Const SQL_API_ALL_FUNCTIONS = 0

Global Const SQL_NUM_EXTENSIONS = (SQL_EXT_API_LAST - SQL_EXT_API_START + 1)

' Defines for SQLGetInfo
'
Global Const SQL_INFO_FIRST = 0
Global Const SQL_ACTIVE_CONNECTIONS = 0
Global Const SQL_ACTIVE_STATEMENTS = 1
Global Const SQL_DATA_SOURCE_NAME = 2
Global Const SQL_DRIVER_HDBC = 3
Global Const SQL_DRIVER_HENV = 4
Global Const SQL_DRIVER_HSTMT = 5
Global Const SQL_DRIVER_NAME = 6
Global Const SQL_DRIVER_VER = 7
Global Const SQL_FETCH_DIRECTION = 8
Global Const SQL_ODBC_API_CONFORMANCE = 9
Global Const SQL_ODBC_VER = 10
Global Const SQL_ROW_UPDATES = 11
Global Const SQL_ODBC_SAG_CLI_CONFORMANCE = 12
Global Const SQL_SERVER_NAME = 13
Global Const SQL_SEARCH_PATTERN_ESCAPE = 14
Global Const SQL_ODBC_SQL_CONFORMANCE = 15

Global Const SQL_DBMS_NAME = 17
Global Const SQL_DBMS_VER = 18

Global Const SQL_ACCESSIBLE_TABLES = 19
Global Const SQL_ACCESSIBLE_PROCEDURES = 20
Global Const SQL_PROCEDURES = 21
Global Const SQL_CONCAT_NULL_BEHAVIOR = 22
Global Const SQL_CURSOR_COMMIT_BEHAVIOR = 23
Global Const SQL_CURSOR_ROLLBACK_BEHAVIOR = 24
Global Const SQL_DATA_SOURCE_READ_ONLY = 25
Global Const SQL_DEFAULT_TXN_ISOLATION = 26
Global Const SQL_EXPRESSIONS_IN_ORDERBY = 27
Global Const SQL_IDENTIFIER_CASE = 28
Global Const SQL_IDENTIFIER_QUOTE_CHAR = 29
Global Const SQL_MAX_COLUMN_NAME_LEN = 30
Global Const SQL_MAX_CURSOR_NAME_LEN = 31
Global Const SQL_MAX_OWNER_NAME_LEN = 32
Global Const SQL_MAX_PROCEDURE_NAME_LEN = 33
Global Const SQL_MAX_QUALIFIER_NAME_LEN = 34
Global Const SQL_MAX_TABLE_NAME_LEN = 35
Global Const SQL_MULT_RESULT_SETS = 36
Global Const SQL_MULTIPLE_ACTIVE_TXN = 37
Global Const SQL_OUTER_JOINS = 38
Global Const SQL_OWNER_TERM = 39
Global Const SQL_PROCEDURE_TERM = 40
Global Const SQL_QUALIFIER_NAME_SEPARATOR = 41
Global Const SQL_QUALIFIER_TERM = 42
Global Const SQL_SCROLL_CONCURRENCY = 43
Global Const SQL_SCROLL_OPTIONS = 44
Global Const SQL_TABLE_TERM = 45
Global Const SQL_TXN_CAPABLE = 46
Global Const SQL_USER_NAME = 47

Global Const SQL_CONVERT_FUNCTIONS = 48
Global Const SQL_NUMERIC_FUNCTIONS = 49
Global Const SQL_STRING_FUNCTIONS = 50
Global Const SQL_SYSTEM_FUNCTIONS = 51
Global Const SQL_TIMEDATE_FUNCTIONS = 52

Global Const SQL_CONVERT_BIGINT = 53
Global Const SQL_CONVERT_BINARY = 54
Global Const SQL_CONVERT_BIT = 55
Global Const SQL_CONVERT_CHAR = 56
Global Const SQL_CONVERT_DATE = 57
Global Const SQL_CONVERT_DECIMAL = 58
Global Const SQL_CONVERT_DOUBLE = 59
Global Const SQL_CONVERT_FLOAT = 60
Global Const SQL_CONVERT_INTEGER = 61
Global Const SQL_CONVERT_LONGVARCHAR = 62
Global Const SQL_CONVERT_NUMERIC = 63
Global Const SQL_CONVERT_REAL = 64
Global Const SQL_CONVERT_SMALLINT = 65
Global Const SQL_CONVERT_TIME = 66
Global Const SQL_CONVERT_TIMESTAMP = 67
Global Const SQL_CONVERT_TINYINT = 68
Global Const SQL_CONVERT_VARBINARY = 69
Global Const SQL_CONVERT_VARCHAR = 70
Global Const SQL_CONVERT_LONGVARBINARY = 71

Global Const SQL_TXN_ISOLATION_OPTION = 72
Global Const SQL_ODBC_SQL_OPT_IEF = 73
Global Const SQL_CORRELATION_NAME = 74
Global Const SQL_NON_NULLABLE_COLUMNS = 75
' #if ODBC 2.00
Global Const SQL_DRIVER_HLIB = 76
Global Const SQL_DRIVER_ODBC_VER = 77
Global Const SQL_LOCK_TYPES = 78
Global Const SQL_POS_OPERATIONS = 79
Global Const SQL_POSITIONED_STATEMENTS = 80
Global Const SQL_GETDATA_EXTENSIONS = 81
Global Const SQL_BOOKMARK_PERSISTENCE = 82
Global Const SQL_STATIC_SENSITIVITY = 83
Global Const SQL_FILE_USAGE = 84
Global Const SQL_NULL_COLLATION = 85
Global Const SQL_ALTER_TABLE = 86
Global Const SQL_COLUMN_ALIAS = 87
Global Const SQL_GROUP_BY = 88
Global Const SQL_KEYWORDS = 89
Global Const SQL_ORDER_BY_COLUMNS_IN_SELECT = 90
Global Const SQL_OWNER_USAGE = 91
Global Const SQL_QUALIFIER_USAGE = 92
Global Const SQL_QUOTED_IDENTIFIER_CASE = 93
Global Const SQL_SPECIAL_CHARACTERS = 94
Global Const SQL_SUBQUERIES = 95
Global Const SQL_UNION = 96
Global Const SQL_MAX_COLUMNS_IN_GROUP_BY = 97
Global Const SQL_MAX_COLUMNS_IN_INDEX = 98
Global Const SQL_MAX_COLUMNS_IN_ORDER_BY = 99
Global Const SQL_MAX_COLUMNS_IN_SELECT = 100
Global Const SQL_MAX_COLUMNS_IN_TABLE = 101
Global Const SQL_MAX_INDEX_SIZE = 102
Global Const SQL_MAX_ROW_SIZE_INCLUDES_LONG = 103
Global Const SQL_MAX_ROW_SIZE = 104
Global Const SQL_MAX_STATEMENT_LEN = 105
Global Const SQL_MAX_TABLES_IN_SELECT = 106
Global Const SQL_MAX_USER_NAME_LEN = 107
Global Const SQL_MAX_CHAR_LITERAL_LEN = 108
Global Const SQL_TIMEDATE_ADD_INTERVALS = 109
Global Const SQL_TIMEDATE_DIFF_INTERVALS = 110
Global Const SQL_NEED_LONG_DATA_LEN = 111
Global Const SQL_MAX_BINARY_LITERAL_LEN = 112
Global Const SQL_LIKE_ESCAPE_CLAUSE = 113
Global Const SQL_QUALIFIER_LOCATION = 114
' #endif ODBC 2.00

Global Const SQL_INFO_LAST = SQL_QUALIFIER_LOCATION
Global Const SQL_INFO_DRIVER_START = 1000

' "SQL_CONVERT_" return value bitmasks
'
Global Const SQL_CVT_CHAR = &H1&
Global Const SQL_CVT_NUMERIC = &H2&
Global Const SQL_CVT_DECIMAL = &H4&
Global Const SQL_CVT_INTEGER = &H8&
Global Const SQL_CVT_SMALLINT = &H10&
Global Const SQL_CVT_FLOAT = &H20&
Global Const SQL_CVT_REAL = &H40&
Global Const SQL_CVT_DOUBLE = &H80&
Global Const SQL_CVT_VARCHAR = &H100&
Global Const SQL_CVT_LONGVARCHAR = &H200&
Global Const SQL_CVT_BINARY = &H400&
Global Const SQL_CVT_VARBINARY = &H800&
Global Const SQL_CVT_BIT = &H1000&
Global Const SQL_CVT_TINYINT = &H2000&
Global Const SQL_CVT_BIGINT = &H4000&
Global Const SQL_CVT_DATE = &H8000&
Global Const SQL_CVT_TIME = &H10000
Global Const SQL_CVT_TIMESTAMP = &H20000
Global Const SQL_CVT_LONGVARBINARY = &H40000


' Conversion functions
'
Global Const SQL_FN_CVT_CONVERT = &H1&

' String functions
'
Global Const SQL_FN_STR_CONCAT = &H1&
Global Const SQL_FN_STR_INSERT = &H2&
Global Const SQL_FN_STR_LEFT = &H4&
Global Const SQL_FN_STR_LTRIM = &H8&
Global Const SQL_FN_STR_LENGTH = &H10&
Global Const SQL_FN_STR_LOCATE = &H20&
Global Const SQL_FN_STR_LCASE = &H40&
Global Const SQL_FN_STR_REPEAT = &H80&
Global Const SQL_FN_STR_REPLACE = &H100&
Global Const SQL_FN_STR_RIGHT = &H200&
Global Const SQL_FN_STR_RTRIM = &H400&
Global Const SQL_FN_STR_SUBSTRING = &H800&
Global Const SQL_FN_STR_UCASE = &H1000&
Global Const SQL_FN_STR_ASCII = &H2000&
Global Const SQL_FN_STR_CHAR = &H4000&
' #if ODBC 2.00
Global Const SQL_FN_STR_DIFFERENCE = &H8000&
Global Const SQL_FN_STR_LOCATE_2 = &H10000
Global Const SQL_FN_STR_SOUNDEX = &H20000
Global Const SQL_FN_STR_SPACE = &H40000
' #endif ODBC 2.00

' Numeric functions
'
Global Const SQL_FN_NUM_ABS = &H1&
Global Const SQL_FN_NUM_ACOS = &H2&
Global Const SQL_FN_NUM_ASIN = &H4&
Global Const SQL_FN_NUM_ATAN = &H8&
Global Const SQL_FN_NUM_ATAN2 = &H10&
Global Const SQL_FN_NUM_CEILING = &H20&
Global Const SQL_FN_NUM_COS = &H40&
Global Const SQL_FN_NUM_COT = &H80&
Global Const SQL_FN_NUM_EXP = &H100&
Global Const SQL_FN_NUM_FLOOR = &H200&
Global Const SQL_FN_NUM_LOG = &H400&
Global Const SQL_FN_NUM_MOD = &H800&
Global Const SQL_FN_NUM_SIGN = &H1000&
Global Const SQL_FN_NUM_SIN = &H2000&
Global Const SQL_FN_NUM_SQRT = &H4000&
Global Const SQL_FN_NUM_TAN = &H8000&
Global Const SQL_FN_NUM_PI = &H10000
Global Const SQL_FN_NUM_RAND = &H20000
' #if ODBC 2.00
Global Const SQL_FN_NUM_DEGREES = &H40000
Global Const SQL_FN_NUM_LOG10 = &H80000
Global Const SQL_FN_NUM_POWER = &H100000
Global Const SQL_FN_NUM_RADIANS = &H200000
Global Const SQL_FN_NUM_ROUND = &H400000
Global Const SQL_FN_NUM_TRUNCATE = &H800000
' #endif ODBC 2.00

' Time/date functions
'
Global Const SQL_FN_TD_NOW = &H1&
Global Const SQL_FN_TD_CURDATE = &H2&
Global Const SQL_FN_TD_DAYOFMONTH = &H4&
Global Const SQL_FN_TD_DAYOFWEEK = &H8&
Global Const SQL_FN_TD_DAYOFYEAR = &H10&
Global Const SQL_FN_TD_MONTH = &H20&
Global Const SQL_FN_TD_QUARTER = &H40&
Global Const SQL_FN_TD_WEEK = &H80&
Global Const SQL_FN_TD_YEAR = &H100&
Global Const SQL_FN_TD_CURTIME = &H200&
Global Const SQL_FN_TD_HOUR = &H400&
Global Const SQL_FN_TD_MINUTE = &H800&
Global Const SQL_FN_TD_SECOND = &H1000&
' #if ODBC 2.00
Global Const SQL_FN_TD_TIMESTAMPADD = &H2000&
Global Const SQL_FN_TD_TIMESTAMPDIFF = &H4000&
Global Const SQL_FN_TD_DAYNAME = &H8000&
Global Const SQL_FN_TD_MONTHNAME = &H10000
' #endif ODBC 2.00

' System functions
'
Global Const SQL_FN_SYS_USERNAME = &H1&
Global Const SQL_FN_SYS_DBNAME = &H2&
Global Const SQL_FN_SYS_IFNULL = &H4&

' Timedate intervals
'
' #if ODBC 2.00
Global Const SQL_FN_TSI_FRAC_SECOND = &H1&
Global Const SQL_FN_TSI_SECOND = &H2&
Global Const SQL_FN_TSI_MINUTE = &H4&
Global Const SQL_FN_TSI_HOUR = &H8&
Global Const SQL_FN_TSI_DAY = &H10&
Global Const SQL_FN_TSI_WEEK = &H20&
Global Const SQL_FN_TSI_MONTH = &H40&
Global Const SQL_FN_TSI_QUARTER = &H80&
Global Const SQL_FN_TSI_YEAR = &H100&
' #endif ODBC 2.00

' ODBC API conformance
'
Global Const SQL_OAC_NONE = 0
Global Const SQL_OAC_LEVEL1 = 1
Global Const SQL_OAC_LEVEL2 = 2

' SAG CLI conformance
'
Global Const SQL_OSCC_NOT_COMPLIANT = 0
Global Const SQL_OSCC_COMPLIANT = 1

' ODBC SQL conformance
'
Global Const SQL_OSC_MINIMUM = 0
Global Const SQL_OSC_CORE = 1
Global Const SQL_OSC_EXTENDED = 2

' Concatenation behavior
'
Global Const SQL_CB_NULL = 0
Global Const SQL_CB_NON_NULL = 1

' Cursor commit behavior
'
Global Const SQL_CB_DELETE = 0
Global Const SQL_CB_CLOSE = 1
Global Const SQL_CB_PRESERVE = 2

' Identifier case
'
Global Const SQL_IC_UPPER = 1
Global Const SQL_IC_LOWER = 2
Global Const SQL_IC_SENSITIVE = 3
Global Const SQL_IC_MIXED = 4

' Transaction capable
'
Global Const SQL_TC_NONE = 0
Global Const SQL_TC_DML = 1
Global Const SQL_TC_ALL = 2
' #if ODBC 2.00
Global Const SQL_TC_DDL_COMMIT = 3
Global Const SQL_TC_DDL_IGNORE = 4
' #endif ODBC 2.00

' Scroll option masks
'
Global Const SQL_SO_FORWARD_ONLY = &H1&
Global Const SQL_SO_KEYSET_DRIVEN = &H2&
Global Const SQL_SO_DYNAMIC = &H4&
Global Const SQL_SO_MIXED = &H8&
' #if ODBC 2.00
Global Const SQL_SO_STATIC = &H10&
' #endif ODBC 2.00

' Scroll concurrency option masks
'
Global Const SQL_SCCO_READ_ONLY = &H1&
Global Const SQL_SCCO_LOCK = &H2&
Global Const SQL_SCCO_OPT_ROWVER = &H4&
Global Const SQL_SCCO_OPT_VALUES = &H8&

' Fetch direction option masks
'
Global Const SQL_FD_FETCH_NEXT = &H1&
Global Const SQL_FD_FETCH_FIRST = &H2&
Global Const SQL_FD_FETCH_LAST = &H4&
Global Const SQL_FD_FETCH_PRIOR = &H8&
Global Const SQL_FD_FETCH_ABSOLUTE = &H10&
Global Const SQL_FD_FETCH_RELATIVE = &H20&
Global Const SQL_FD_FETCH_RESUME = &H40&
' #if ODBC 2.00
Global Const SQL_FD_FETCH_BOOKMARK = &H80&
' #endif ODBC 2.00

' Transaction isolation option masks
'
Global Const SQL_TXN_READ_UNCOMMITTED = &H1&
Global Const SQL_TXN_READ_COMMITTED = &H2&
Global Const SQL_TXN_REPEATABLE_READ = &H4&
Global Const SQL_TXN_SERIALIZABLE = &H8&
Global Const SQL_TXN_VERSIONING = &H10&

' Correlation name
'
Global Const SQL_CN_NONE = 0
Global Const SQL_CN_DIFFERENT = 1
Global Const SQL_CN_ANY = 2

' Non-nullable columns
'
Global Const SQL_NNC_NULL = 0
Global Const SQL_NNC_NON_NULL = 1

' #if ODBC 2.00
' Null collation
'
Global Const SQL_NC_HIGH = 0
Global Const SQL_NC_LOW = 1
Global Const SQL_NC_START = 2
Global Const SQL_NC_END = 4

' File usage
'
Global Const SQL_FILE_NOT_SUPPORTED = 0
Global Const SQL_FILE_TABLE = 1
Global Const SQL_FILE_QUALIFIER = 2

' SQLGetData extensions masks
'
Global Const SQL_GD_ANY_COLUMN = &H1&
Global Const SQL_GD_ANY_ORDER = &H2&
Global Const SQL_GD_BLOCK = &H4&
Global Const SQL_GD_BOUND = &H8&

' Alter table
'
Global Const SQL_AT_ADD_COLUMN = 1
Global Const SQL_AT_DROP_COLUMN = 2

' Positioned statements masks
'
Global Const SQL_PS_POSITIONED_DELETE = &H1&
Global Const SQL_PS_POSITIONED_UPDATE = &H2&
Global Const SQL_PS_SELECT_FOR_UPDATE = &H4&

' Group By
'
Global Const SQL_GB_NOT_SUPPORTED = 0
Global Const SQL_GB_GROUP_BY_EQUALS_SELECT = 1
Global Const SQL_GB_GROUP_BY_CONTAINS_SELECT = 2
Global Const SQL_GB_NO_RELATION = 3

' Owner usage masks
'
Global Const SQL_OU_DML_STATEMENTS = &H1&
Global Const SQL_OU_PROCEDURE_INVOCATION = &H2&
Global Const SQL_OU_TABLE_DEFINITION = &H4&
Global Const SQL_OU_INDEX_DEFINITION = &H8&
Global Const SQL_OU_PRIVILEGE_DEFINITION = &H10&

' Qualifier usage masks
'
Global Const SQL_QU_DML_STATEMENTS = &H1&
Global Const SQL_QU_PROCEDURE_INVOCATION = &H2&
Global Const SQL_QU_TABLE_DEFINITION = &H4&
Global Const SQL_QU_INDEX_DEFINITION = &H8&
Global Const SQL_QU_PRIVILEGE_DEFINITION = &H10&

' Subqueries masks
'
Global Const SQL_SQ_COMPARISON = &H1&
Global Const SQL_SQ_EXISTS = &H2&
Global Const SQL_SQ_IN = &H4&
Global Const SQL_SQ_QUANTIFIED = &H8&
Global Const SQL_SQ_CORRELATED_SUBQUERIES = &H10&

' Union masks
'
Global Const SQL_U_UNION = &H1&
Global Const SQL_U_UNION_ALL = &H2&

' Bookmark persistence
'
Global Const SQL_BP_CLOSE = &H1&
Global Const SQL_BP_DELETE = &H2&
Global Const SQL_BP_DROP = &H4&
Global Const SQL_BP_TRANSACTION = &H8&
Global Const SQL_BP_UPDATE = &H10&
Global Const SQL_BP_OTHER_HSTMT = &H20&
Global Const SQL_BP_SCROLL = &H40&

' Static sensitivity
'
Global Const SQL_SS_ADDITIONS = &H1&
Global Const SQL_SS_DELETIONS = &H2&
Global Const SQL_SS_UPDATES = &H4&

' Lock types masks
'
Global Const SQL_LCK_NO_CHANGE = &H1&
Global Const SQL_LCK_EXCLUSIVE = &H2&
Global Const SQL_LCK_UNLOCK = &H4&

' Positioned operations masks
'
Global Const SQL_POS_POSITION = &H1&
Global Const SQL_POS_REFRESH = &H2&
Global Const SQL_POS_UPDATE = &H4&
Global Const SQL_POS_DELETE = &H8&
Global Const SQL_POS_ADD = &H10&

' Qualifier location
'
Global Const SQL_QL_START = 1
Global Const SQL_QL_END = 2
' Global Const  ODBC 2.00


' Options for SQLGetStmtOption/SQLSetStmtOption
'
Global Const SQL_QUERY_TIMEOUT = 0
Global Const SQL_MAX_ROWS = 1
Global Const SQL_NOSCAN = 2
Global Const SQL_MAX_LENGTH = 3
Global Const SQL_ASYNC_ENABLE = 4
Global Const SQL_BIND_TYPE = 5
' #if ODBC 2.00
Global Const SQL_CURSOR_TYPE = 6
Global Const SQL_CONCURRENCY = 7
Global Const SQL_KEYSET_SIZE = 8
Global Const SQL_ROWSET_SIZE = 9
Global Const SQL_SIMULATE_CURSOR = 10
Global Const SQL_RETRIEVE_DATA = 11
Global Const SQL_USE_BOOKMARKS = 12
Global Const SQL_GET_BOOKMARK = 13
Global Const SQL_ROW_NUMBER = 14
' #endif ODBC 2.00
Global Const SQL_STMT_OPT_MAX = SQL_ROW_NUMBER

' Statement option values & defaults
'
Global Const SQL_QUERY_TIMEOUT_DEFAULT = 0
Global Const SQL_MAX_ROWS_DEFAULT = 0

Global Const SQL_NOSCAN_OFF = 0
Global Const SQL_NOSCAN_ON = 1
Global Const SQL_NOSCAN_DEFAULT = SQL_NOSCAN_OFF

Global Const SQL_MAX_LENGTH_DEFAULT = 0

Global Const SQL_ASYNC_ENABLE_OFF = 0
Global Const SQL_ASYNC_ENABLE_ON = 1
Global Const SQL_ASYNC_ENABLE_DEFAULT = SQL_ASYNC_ENABLE_OFF

Global Const SQL_BIND_BY_COLUMN = 0

Global Const SQL_CONCUR_READ_ONLY = 1
Global Const SQL_CONCUR_LOCK = 2
Global Const SQL_CONCUR_ROWVER = 3
Global Const SQL_CONCUR_VALUES = 4

' #if ODBC 2.00
'#define SQL_CURSOR_FORWARD_ONLY = 0
'#define SQL_CURSOR_KEYSET_DRIVEN = 1
'#define SQL_CURSOR_DYNAMIC = 2
'#define SQL_CURSOR_STATIC = 3

'#define SQL_ROWSET_SIZE_DEFAULT = 1

Global Const SQL_KEYSET_SIZE_DEFAULT = 0

Global Const SQL_SC_NON_UNIQUE = 0
Global Const SQL_SC_TRY_UNIQUE = 1
Global Const SQL_SC_UNIQUE = 2

Global Const SQL_RD_OFF = 0
Global Const SQL_RD_ON = 1
Global Const SQL_RD_DEFAULT = SQL_RD_ON

Global Const SQL_UB_OFF = 0
Global Const SQL_UB_ON = 1
Global Const SQL_UB_DEFAULT = SQL_UB_ON
' #endif ODBC 2.00

' Options for SQLSetConnectOption/SQLGetConnectOption
'
Global Const SQL_ACCESS_MODE = 101
Global Const SQL_AUTOCOMMIT = 102
Global Const SQL_LOGIN_TIMEOUT = 103
Global Const SQL_OPT_TRACE = 104
Global Const SQL_OPT_TRACEFILE = 105
Global Const SQL_TRANSLATE_DLL = 106
Global Const SQL_TRANSLATE_OPTION = 107
Global Const SQL_TXN_ISOLATION = 108
Global Const SQL_CURRENT_QUALIFIER = 109
Global Const SQL_CONNECT_OPT_DRVR_START = 1000
' #if ODBC 2.00
Global Const SQL_ODBC_CURSORS = 110
Global Const SQL_QUIET_MODE = 111
Global Const SQL_PACKET_SIZE = 112
' #endif ODBC 2.00
Global Const SQL_CONN_OPT_MAX = SQL_PACKET_SIZE

Global Const SQL_CONN_OPT_MIN = SQL_ACCESS_MODE

' Access mode options
'
Global Const SQL_MODE_READ_WRITE = 0
Global Const SQL_MODE_READ_ONLY = 1
Global Const SQL_MODE_DEFAULT = SQL_MODE_READ_WRITE

' Autocommit options
'
Global Const SQL_AUTOCOMMIT_OFF = 0
Global Const SQL_AUTOCOMMIT_ON = 1
Global Const SQL_AUTOCOMMIT_DEFAULT = SQL_AUTOCOMMIT_ON

' Login timeout options
'
Global Const SQL_LOGIN_TIMEOUT_DEFAULT = 15

' Trace options
'
Global Const SQL_OPT_TRACE_OFF = 0
Global Const SQL_OPT_TRACE_ON = 1
Global Const SQL_OPT_TRACE_DEFAULT = SQL_OPT_TRACE_OFF
Global Const SQL_OPT_TRACE_FILE_DEFAULT = "\\SQL.LOG"

' #if ODBC 2.00
' Cursor options
'
Global Const SQL_CUR_USE_IF_NEEDED = 0
Global Const SQL_CUR_USE_ODBC = 1
Global Const SQL_CUR_USE_DRIVER = 2
Global Const SQL_CUR_DEFAULT = SQL_CUR_USE_DRIVER
' #endif ODBC 2.00

' Column types and scopes in SQLSpecialColumns.
'
Global Const SQL_BEST_ROWID = 1
Global Const SQL_ROWVER = 2

Global Const SQL_SCOPE_CURROW = 0
Global Const SQL_SCOPE_TRANSACTION = 1
Global Const SQL_SCOPE_SESSION = 2

' Level 2 Functions
'
' SQLExtendedFetch "fFetchType" values
'
Global Const SQL_FETCH_NEXT = 1
Global Const SQL_FETCH_FIRST = 2
Global Const SQL_FETCH_LAST = 3
Global Const SQL_FETCH_PRIOR = 4
Global Const SQL_FETCH_ABSOLUTE = 5
Global Const SQL_FETCH_RELATIVE = 6
' #if ODBC 2.00
Global Const SQL_FETCH_BOOKMARK = 8
' #endif ODBC 2.00

' SQLExtendedFetch "rgfRowStatus" element values
'
Global Const SQL_ROW_SUCCESS = 0
Global Const SQL_ROW_DELETED = 1
Global Const SQL_ROW_UPDATED = 2
Global Const SQL_ROW_NOROW = 3
' #if ODBC 2.00
Global Const SQL_ROW_ADDED = 4
Global Const SQL_ROW_ERROR = 5
' #endif ODBC 2.00

' Defines for SQLForeignKeys (returned in result set)
'
Global Const SQL_CASCADE = 0
Global Const SQL_RESTRICT = 1
Global Const SQL_SET_NULL = 2

' Defines for SQLProcedureColumns (returned in the result set)
'
Global Const SQL_PARAM_TYPE_UNKNOWN = 0
Global Const SQL_PARAM_INPUT = 1
Global Const SQL_PARAM_INPUT_OUTPUT = 2
Global Const SQL_RESULT_COL = 3
' #if ODBC 2.00
Global Const SQL_PARAM_OUTPUT = 4
' #endif ODBC 2.00

' Defines for SQLStatistics
'
Global Const SQL_INDEX_UNIQUE = 0
Global Const SQL_INDEX_ALL = 1
Global Const SQL_ENSURE = 1
Global Const SQL_QUICK = 0

' Defines for SQLStatistics (returned in the result set)
'
Global Const SQL_TABLE_STAT = 0
Global Const SQL_INDEX_CLUSTERED = 1
Global Const SQL_INDEX_HASHED = 2
Global Const SQL_INDEX_OTHER = 3

' #if ODBC 2.00
' Procedures
'
Global Const SQL_PT_UNKNOWN = 0
Global Const SQL_PT_PROCEDURE = 1
Global Const SQL_PT_FUNCTION = 2

' Procedure columns
'
Global Const SQL_PC_UNKNOWN = 0
Global Const SQL_PC_NON_PSEUDO = 1
Global Const SQL_PC_PSEUDO = 2
' #endif ODBC 2.00

' Defines for SQLSetPos
'
Global Const SQL_ENTIRE_ROWSET = 0

Global Const SQL_POSITION = 0
Global Const SQL_REFRESH = 1
' #if ODBC 2.00
Global Const SQL_UPDATE = 2
Global Const SQL_DELETE = 3
Global Const SQL_ADD = 4
' #endif ODBC 2.00

' Lock options
'
Global Const SQL_LOCK_NO_CHANGE = 0
Global Const SQL_LOCK_EXCLUSIVE = 1
' #if ODBC 2.00
Global Const SQL_LOCK_UNLOCK = 2
' #endif ODBC 2.00

' Deprecated global constants
'
Global Const SQL_DATABASE_NAME = 16
Global Const SQL_FD_FETCH_PREV = SQL_FD_FETCH_PRIOR
Global Const SQL_FETCH_PREV = SQL_FETCH_PRIOR
Global Const SQL_CONCUR_TIMESTAMP = SQL_CONCUR_ROWVER
Global Const SQL_SCCO_OPT_TIMESTAMP = SQL_SCCO_OPT_ROWVER
Global Const SQL_CC_DELETE = SQL_CB_DELETE
Global Const SQL_CR_DELETE = SQL_CB_DELETE
Global Const SQL_CC_CLOSE = SQL_CB_CLOSE
Global Const SQL_CR_CLOSE = SQL_CB_CLOSE
Global Const SQL_CC_PRESERVE = SQL_CB_PRESERVE
Global Const SQL_CR_PRESERVE = SQL_CB_PRESERVE
Global Const SQL_FETCH_RESUME = 7
Global Const SQL_SCROLL_FORWARD_ONLY = 0
Global Const SQL_SCROLL_KEYSET_DRIVEN = -1
Global Const SQL_SCROLL_DYNAMIC = -2
Global Const SQL_SCROLL_STATIC = -3

Function VBODBC_CloseDatabase () As Integer
  
'closes the current database connection, assuming one is open and
'no sqlstmt remains open

'Returns SQL_SUCCESS is successful

Dim ResCode As Integer

'make sure we're in right SqlState
If VBODBC_SqlState <> VBODBC_SQLSTATE_OPENDB Then
    If VBODBC_SqlState = VBODBC_SQLSTATE_CLOSED Then
	Call VBODBC_DescribeError("VBODBC_CloseDatabase", "", SQL_VBODBC_ERR, "[VBODBC] Database not open.")
    ElseIf VBODBC_SqlState = VBODBC_SQLSTATE_OPENSTMT Then
	Call VBODBC_DescribeError("VBODBC_CloseDatabase", "", SQL_VBODBC_ERR, "[VBODBC] Must close SQL Statement before closing database.")
    End If
    GoTo VBODBC_CloseDatabase_Err
End If


'close database connection
ResCode = SQLDisconnect(VBODBC_hdbc)
If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
    Call VBODBC_DescribeError("VBODBC_CloseDatabase", "SQLDisconnect", ResCode, "")
    GoTo VBODBC_CloseDatabase_Err
End If

'free resources used by just-closed db connection
ResCode = SQLFreeConnect(VBODBC_hdbc)
If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
    Call VBODBC_DescribeError("VBODBC_CloseDatabase", "SQLFreeConnect", ResCode, "")
    GoTo VBODBC_CloseDatabase_Err
End If

'free the environment resources
ResCode = SQLFreeEnv(VBODBC_henv)
If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
    Call VBODBC_DescribeError("VBODBC_CloseDatabase", "SQLFreeEnv", ResCode, "")
    GoTo VBODBC_CloseDatabase_Err
End If

'update to new SqlState
VBODBC_SqlState = VBODBC_SQLSTATE_CLOSED


Exit Function

VBODBC_CloseDatabase_Err:
VBODBC_CloseDatabase = SQL_ERROR


End Function

Function VBODBC_CloseSqlStmt () As Integer

'closes the current sql stmt, assuming one is open

'Returns SQL_SUCCESS is successful

Dim ResCode As Integer

'make sure we're in right SqlState
If VBODBC_SqlState <> VBODBC_SQLSTATE_OPENSTMT Then
    Call VBODBC_DescribeError("VBODBC_CloseSqlStmt", "", SQL_VBODBC_ERR, "[VBODBC] SQL Statement not open.")
    GoTo VBODBC_CloseSqlStmt_Err
End If

'free the resources used by this stmt
ResCode = SQLFreeStmt(VBODBC_hstmt, SQL_DROP)
If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
    Call VBODBC_DescribeError("VBODBC_CloseSqlStmt", "SQLFreeStmt", ResCode, "")
    GoTo VBODBC_CloseSqlStmt_Err
End If

'update to new SqlState
VBODBC_SqlState = VBODBC_SQLSTATE_OPENDB

Exit Function

VBODBC_CloseSqlStmt_Err:
VBODBC_CloseSqlStmt = SQL_ERROR

End Function

Sub VBODBC_DescribeError (VBODBCFunctionName As String, ODBCFunctionName As String, ODBCFunctionResCode As Integer, OtherInfo As String)

'Populates a global error structure VBODBC_LastErr so the caller can examine the error

'even though ODBC may return multiple error messages for a particular ODBC
'call, the VBODB buffer will only hold the FIRST error

'VBODBCFunctionName is the VB function name that the error occured
'ODBCFunctionName is the ODBC call that generated the error
'OtherInfo is any additional info the caller wants to log

'odbc function call parms
Dim sqlstate As String * 16
Dim ErrorMsg As String * 256
Dim ErrorMsgOutLen As Integer
Dim NativeError As Long
Dim ResCode As Integer

'temporary work buffer
Dim TempOdbcErr As VBODBC_ErrType
Dim AllErrorInfoTemp As String

Dim CR As String * 2

sqlstate = String$(16, 32)
ErrorMsg = String$(255, 32)

'all error msg delimiter
CR = Chr$(13) & Chr$(10)

'assign VBODBC stuff to structure
TempOdbcErr.VBODBCFunctionName = VBODBCFunctionName
TempOdbcErr.ODBCFunctionName = ODBCFunctionName
TempOdbcErr.ODBCFunctionResCodeStr = VBODBC_ODBCResCodeToString(ODBCFunctionResCode)
TempOdbcErr.OtherInfo = OtherInfo

    'we may get many errors,only look at first one
    'look up ODBC error info
    ResCode = SQLError(VBODBC_henv, VBODBC_hdbc, VBODBC_hstmt, sqlstate, NativeError, ErrorMsg, Len(ErrorMsg), ErrorMsgOutLen)
    TempOdbcErr.SqlErrResCodeStr = VBODBC_ODBCResCodeToString(ResCode)
    'remove null
    If InStr(1, sqlstate, Chr$(0)) Then Mid$(sqlstate, InStr(1, sqlstate, Chr$(0)), 1) = " "
    TempOdbcErr.sqlstate = sqlstate
    TempOdbcErr.NativeError = NativeError
    If ResCode = SQL_SUCCESS Or ResCode = SQL_SUCCESS_WITH_INFO Then
	If ErrorMsgOutLen = 0 Then
	    TempOdbcErr.ErrorMsg = "[VBODBC] No message available!"
	Else
	    TempOdbcErr.ErrorMsg = Left$(ErrorMsg, ErrorMsgOutLen)
	End If
    End If

    'build all error msg text
    AllErrorInfoTemp = "ErrorMsg:               " & TempOdbcErr.ErrorMsg
    AllErrorInfoTemp = AllErrorInfoTemp & CR & "SqlState:               " & Trim$(TempOdbcErr.sqlstate)
    AllErrorInfoTemp = AllErrorInfoTemp & CR & "NativeError:            " & TempOdbcErr.NativeError
    AllErrorInfoTemp = AllErrorInfoTemp & CR & "SqlErrResCodeStr:       " & TempOdbcErr.SqlErrResCodeStr
    AllErrorInfoTemp = AllErrorInfoTemp & CR & "VBODBCFunctionName:     " & TempOdbcErr.VBODBCFunctionName
    AllErrorInfoTemp = AllErrorInfoTemp & CR & "ODBCFunctionName:       " & TempOdbcErr.ODBCFunctionName
    AllErrorInfoTemp = AllErrorInfoTemp & CR & "ODBCFunctionResCodeStr: " & TempOdbcErr.ODBCFunctionResCodeStr
    AllErrorInfoTemp = AllErrorInfoTemp & CR & "OtherInfo:              " & TempOdbcErr.OtherInfo
    
    TempOdbcErr.AllErrorInfo = AllErrorInfoTemp


'copy structure to global structure
VBODBC_LastErr = TempOdbcErr

End Sub

Function VBODBC_GetDataSources (ListCtrl As Control) As Integer
'
'this routine fills a list box (ListCtrl) with all available
'ODBC data sources found in ODBC.INI
'

'Returns SQL_SUCESS is successful

'error handler for this routine
On Error GoTo VBODBC_GetDataSources_Err

'win api parms
Dim DataSource As String, description As String
Dim DataSourceLen As Integer, DescriptionLen As Integer
Dim ResCode As Integer
Dim henv As Long

'allocate environment
If SQLAllocEnv(henv) <> SQL_ERROR Then
    'initialize buffers
    DataSource = String$(32, 32)
    description = String$(255, 32)
    'get the first one
    ResCode = SQLDataSources(henv, SQL_FETCH_FIRST, DataSource, Len(DataSource), DataSourceLen, description, Len(description), DescriptionLen)
    While ResCode = SQL_SUCCESS Or ResCode = SQL_SUCCESS_WITH_INFO
	'add data source to list control
	ListCtrl.AddItem Mid(DataSource, 1, DataSourceLen)
	'reinitialize buffers
	DataSource = String$(32, 32)
	description = String$(255, 32)
	'get all the others
	ResCode = SQLDataSources(henv, SQL_FETCH_NEXT, DataSource, Len(DataSource), DataSourceLen, description, Len(description), DescriptionLen)
    Wend
    
    'free the environment resources
    ResCode = SQLFreeEnv(henv)
    If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
	'uh oh, error
	Call VBODBC_DescribeError("VBODBC_CloseDatabase", "SQLFreeEnv", ResCode, "")
	GoTo VBODBC_GetDataSources_Err
    End If

End If


Exit Function

'error handler
VBODBC_GetDataSources_Err:
VBODBC_GetDataSources = SQL_ERROR


End Function

Function VBODBC_GetNextRow (RowBuf() As Variant) As Integer

'retrieves the next row from the active sqlstmt

'Returns SQL_SUCCESS if worked
'Returns SQL_NO_DATA_FOUND if no more rows
'Returns SQL_ERROR if error occured

'RowBuf is populated with next row's results.  Element 1=column 1, etc.
'Since its a variant, each element may be a different data type
'Since its a variant, Nulls will be returned as Null
'Element 0 is a string concatination of all columns, delimited by Delim, for easy placment in controls that take delimited rows (like grid)

'buffers for specific data types
Dim IntegerBuf As Integer
Dim LongBuf As Long
Dim SingleBuf As Single
Dim StringBuf As String * 255
Dim DoubleBuf As Double

Dim ColNum As Integer   'column number
Dim ResCode As Integer
Dim OutLen As Long      'length of output

Dim Delim As String     'RowBuf(0)'s delimiter
Delim = Chr$(9)

ReDim RowBuf(VBODBC_NumCols)

'make sure we're in right SqlState and update to new sql state
If VBODBC_SqlState <> VBODBC_SQLSTATE_OPENSTMT Then
    Call VBODBC_DescribeError("VBODBC_GetNextRow", "", SQL_VBODBC_ERR, "[VBODBC] SQL Statement not open.")
    GoTo VBODBC_GetNextRow_Err
End If

If VBODBC_NumCols = 0 Then
	'no columns returned, must be non-select query
	'exit
	VBODBC_GetNextRow = SQL_NO_DATA_FOUND
	Exit Function
End If

'fetch next record into DLL buffer
ResCode = SQLFetch(VBODBC_hstmt)
'switch as result code of fetch
Select Case ResCode

    Case SQL_NO_DATA_FOUND: 'last row
	VBODBC_GetNextRow = SQL_NO_DATA_FOUND
	Exit Function
    
    Case SQL_SUCCESS: 'do nothing

    Case Else 'some error occured
	Call VBODBC_DescribeError("VBODBC_GetNextRow", "SQLFetch", ResCode, "")
	GoTo VBODBC_GetNextRow_Err

End Select

'grab each col from DLL and place in VB array buffer
For ColNum = 1 To VBODBC_NumCols

    'do things differently, depending on what data type we're working with
    Select Case VBODBC_ColDesc(ColNum).SqlType

	'This could be more complete, by switching on more data types.
	'In this version only integers and longs are converted properly,
	'everything else is just a variant string.
	Case SQL_SMALLINT: 'integer
	    
	    ResCode = SQLGetData(VBODBC_hstmt, ColNum, SQL_CHAR, StringBuf, Len(StringBuf), OutLen)
	    If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
		Call VBODBC_DescribeError("VBODBC_GetNextRow", "SQLGetData", ResCode, "[ColNum]" & ColNum & " [SqlType]" & VBODBC_ColDesc(ColNum).SqlType)
		GoTo VBODBC_GetNextRow_Err
	    End If
	    'see if its null, assign return buffer data
	    If OutLen = SQL_NULL_DATA Then
		RowBuf(ColNum) = Null
	    Else
		RowBuf(ColNum) = CInt(Left$(StringBuf, OutLen))
	    End If

	Case SQL_INTEGER: 'long
	    
	    ResCode = SQLGetData(VBODBC_hstmt, ColNum, SQL_CHAR, StringBuf, Len(StringBuf), OutLen)
	    If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
		Call VBODBC_DescribeError("VBODBC_GetNextRow", "SQLGetData", ResCode, "[ColNum]" & ColNum & " [SqlType]" & VBODBC_ColDesc(ColNum).SqlType)
		GoTo VBODBC_GetNextRow_Err
	    End If
	    'see if its null, assign return buffer data
	    If OutLen = SQL_NULL_DATA Then
		RowBuf(ColNum) = Null
	    Else
		RowBuf(ColNum) = CLng(Left$(StringBuf, OutLen))
	    End If
	
	Case Else:  'consider everything else character data
	    
	    ResCode = SQLGetData(VBODBC_hstmt, ColNum, SQL_CHAR, StringBuf, Len(StringBuf), OutLen)
	    If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
		Call VBODBC_DescribeError("VBODBC_GetNextRow", "SQLGetData", ResCode, "[ColNum]" & ColNum & " [SqlType]" & VBODBC_ColDesc(ColNum).SqlType)
		GoTo VBODBC_GetNextRow_Err
	    End If
	    'see if its null, assign return buffer data
	    If OutLen = SQL_NULL_DATA Then
		RowBuf(ColNum) = Null
	    Else
		RowBuf(ColNum) = Trim$(Left$(StringBuf, OutLen))
	    End If

    End Select

    'assign element 0 as concatination of all columns,
    'delimited by Delim
    If ColNum = 1 Then
	'no delim for first column
	RowBuf(0) = RowBuf(ColNum)
    Else
	RowBuf(0) = RowBuf(0) & Delim & RowBuf(ColNum)
    End If

Next ColNum

Exit Function

VBODBC_GetNextRow_Err:
VBODBC_GetNextRow = SQL_ERROR

End Function

Private Function VBODBC_ODBCResCodeToString (ResCode As Integer) As String

'Given as ODBC return code, return a string that corresponds to the
'internal constant symbol.
'Used by VBODBC_DescribeError error function.

Dim s As String

Select Case ResCode
    Case SQL_ERROR:
	s = "SQL_ERROR"
    Case SQL_INVALID_HANDLE
	s = "SQL_INVALID_HANDLE"
    Case SQL_SUCCESS
	s = "SQL_SUCCESS"
    Case SQL_SUCCESS_WITH_INFO
	s = "SQL_SUCCESS_WITH_INFO"
    Case SQL_NEED_DATA
	s = "SQL_NEED_DATA"
    Case SQL_NO_DATA_FOUND
	s = "SQL_NO_DATA_FOUND"
    Case SQL_VBODBC_ERR
	s = "SQL_VBODBC_ERR"
    Case Else
	s = "UNKNOWN!"
End Select

VBODBC_ODBCResCodeToString = s


End Function

Function VBODBC_OpenDatabase (ConnStrPassed As String) As Integer

'Established an ODBC connection to the database, using
'ConnStrPassed as the default ODBC connection string.

'ConnStrPassed can be left blank, in which case the DLL will pop up a dialog
'box to get connection info, or it can contain connection info to bypass
'the DLL dialogs.

'This is used by VBODBC_OpenDatabaseDialog, but can also
'This should be used for custom connection dialog boxes.

'After a connection, ConnStrPassed is modified to contain the actual, full
'connection string generated by the DLL.

'Example ConnStrPassed:
'DSN=DSS Prod;UID=CGoren;PWD=NeverGuess


Dim ResCode As Integer
Dim ConnStr As String * 255
Dim ConnStrOut As String * 255
Dim ConnStrOutLen As Integer 'length of data in ConnStrOut

ConnStr = ConnStrPassed      'connection string sent to ODBC
ConnStrOut = String(255, 0)  'actual connection string returned from ODBC


'make sure we're in right SqlState
If VBODBC_SqlState <> VBODBC_SQLSTATE_CLOSED Then
    Call VBODBC_DescribeError("VBODBC_OpenDataBase", "", SQL_VBODBC_ERR, "[VBODBC] Database already open.")
    GoTo VBODBC_OpenDatabase_Err
End If

' allocates memory for an environment handle
' initialize the ODBC call-level interface
ResCode = SQLAllocEnv(VBODBC_henv)
If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
    Call VBODBC_DescribeError("VBODBC_OpenDataBase", "SQLAllocEnv", ResCode, "")
    GoTo VBODBC_OpenDatabase_Err
End If

' Allocate a connection handle
ResCode = SQLAllocConnect(VBODBC_henv, VBODBC_hdbc)
If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
    Call VBODBC_DescribeError("VBODBC_OpenDataBase", "SQLAllocConnect", ResCode, "")
    GoTo VBODBC_OpenDatabase_Err
End If
  
' Make the connection
' use the form with current focus as parent (this is really only needed when driver prompts for more info)
' use NOPROMPT option so archaic ODBC dialog doesn't pop up
ResCode = SQLDriverConnect(VBODBC_hdbc, VBODBC_GetParent(VBODBC_GetFocus()), ConnStr, Len(ConnStr), ConnStrOut, Len(ConnStrOut), ConnStrOutLen, SQL_DRIVER_NOPROMPT)
If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
    Call VBODBC_DescribeError("VBODBC_OpenDataBase", "SQLDriverConnect", ResCode, "")
    GoTo VBODBC_OpenDatabase_Err
End If
  
'update passed connect string to full connect string
ConnStrPassed = ConnStrOut

'update new SqlState to indicate DB opened
VBODBC_SqlState = VBODBC_SQLSTATE_OPENDB

Exit Function

VBODBC_OpenDatabase_Err:
VBODBC_OpenDatabase = SQL_ERROR

End Function

Function VBODBC_OpenDatabaseDialog (UID As String, PWD As String, DSN As String, AppName As String, ConStrOut As String) As Integer

'Returns SQL_SUCCESS for success, SQL_ERROR for failure and the user cancelled.

'UID, PWD, and DSN are default values that will appear in the dialog
'box.  They should be stored by your program in an INI file so the user
'doesn't have to always type them. They are modified by the routine
'to the values the user used.

'AppName is the AppName passed to ODBC for monitoring, if the driver supports
'it.  E.g. "My Killer Program"

'ConnStrOut is the full, final ODBC connection string built by the driver.

'make sure we're in right SqlState
If VBODBC_SqlState <> VBODBC_SQLSTATE_CLOSED Then
    Call VBODBC_DescribeError("VBODBC_OpenDataBase", "", SQL_VBODBC_ERR, "[VBODBC] Database already open.")
    'populate return buffer with error info
    UID = ""
    PWD = ""
    DSN = ""
    VBODBC_Logon.ConnStrOut = ""
    VBODBC_OpenDatabaseDialog = SQL_ERROR
    Exit Function
End If

'fill form buffer with defaults and initial values
VBODBC_Logon.UID = UID
VBODBC_Logon.PWD = PWD
VBODBC_Logon.DSN = DSN
VBODBC_Logon.ConnStrOut = ""
VBODBC_Logon.AppName = AppName
VBODBC_Logon.Connected = 0

'show the logon form modally
frmVBODBC1.Show 1

'see what happened in the model form
If VBODBC_Logon.Connected Then      'connected!
    'repopulate buffer connection info
    UID = VBODBC_Logon.UID
    PWD = VBODBC_Logon.PWD
    DSN = VBODBC_Logon.DSN
    ConStrOut = VBODBC_Logon.ConnStrOut
    VBODBC_OpenDatabaseDialog = SQL_SUCCESS
Else 'user cancelled!
    'populate return buffer with error info
    UID = ""
    PWD = ""
    DSN = ""
    VBODBC_Logon.ConnStrOut = ""
    VBODBC_OpenDatabaseDialog = SQL_ERROR
    Call VBODBC_DescribeError("VBODBC_OpenDatabaseDialog", "", SQL_VBODBC_ERR, "[VBODBC] Cancelled open database dialog.")
End If


End Function

Function VBODBC_OpenSqlProc (ByVal SqlStmt As String, Parms() As String) As Integer

'Used interanally by VBODBC_OpenSqlProcDialog to execute a SQL
'statement.

'Exectutes the given SqlStmt on the open database ansynchronously,
'if available.

'Returns SQL_SUCCESS if successful.


Dim ResCode As Integer
Dim ColNum As Integer
Dim ColName As String * 255
Dim ColLen As Integer
Dim SqlType As Integer

Dim ParmNum As Integer

Dim ColDef As Long
Dim ColScale As Integer
Dim Nullable As Integer

Dim AlreadyCancelled As Integer 'true if the query has already been cancelled

Dim Delim As String
Delim = Chr$(9)

'make sure we're in right SqlState
If VBODBC_SqlState <> VBODBC_SQLSTATE_OPENDB Then
    If VBODBC_SqlState = VBODBC_SQLSTATE_CLOSED Then
	Call VBODBC_DescribeError("VBODBC_CloseDatabase", "", SQL_VBODBC_ERR, "[VBODBC] Database not open.")
    ElseIf VBODBC_SqlState = VBODBC_SQLSTATE_OPENSTMT Then
	Call VBODBC_DescribeError("VBODBC_CloseDatabase", "", SQL_VBODBC_ERR, "[VBODBC] Must close SQL Statement before opening a new SQL Statement.")
    End If
    GoTo VBODBC_OpenSqlProc_Err
End If

'Allocate a statement handle
ResCode = SQLAllocStmt(VBODBC_hdbc, VBODBC_hstmt)
If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
    Call VBODBC_DescribeError("VBODBC_OpenSqlProc", "SQLAllocStmt", ResCode, "[SqlStmt]" & SqlStmt)
    GoTo VBODBC_OpenSqlProc_Err
End If
  
'enable asyncronous processing, assume error means not available
'(e.g. ignore any info)
ResCode = SQLSetStmtOption(VBODBC_hstmt, SQL_ASYNC_ENABLE, SQL_ASYNC_ENABLE_ON)

'reset holder of column information
ReDim VBODBC_ColDesc(0)


'create ODBC place holder string of form {call MyProc (?,?,?)}
SqlStmt = "{call " & SqlStmt & " "
For ParmNum = 1 To UBound(Parms)
    If ParmNum = 1 Then
	SqlStmt = SqlStmt & "(?"  'no comma for first
    Else
	SqlStmt = SqlStmt & ", ?"
    End If
Next
If UBound(Parms) > 0 Then
    SqlStmt = SqlStmt & ")"
End If
SqlStmt = SqlStmt & "}"

'Prepare the query
ResCode = SQLPrepare(VBODBC_hstmt, SqlStmt, Len(SqlStmt))
If ResCode <> SQL_SUCCESS Then
    Call VBODBC_DescribeError("VBODBC_OpenSqlProc", "SQLAllocStmt", ResCode, "[SqlStmt]" & SqlStmt)
    GoTo VBODBC_OpenSqlProc_Err
End If

'Bind the parameters
For ParmNum = 1 To UBound(Parms)
    ResCode = SQLBindParameter(VBODBC_hstmt, ParmNum, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, Len(Parms(ParmNum)), 0, Parms(ParmNum), 0, SQL_NTS)
    If ResCode <> SQL_SUCCESS Then
	Call VBODBC_DescribeError("VBODBC_OpenSqlProc", "SQLAllocStmt", ResCode, "[SqlStmt]" & SqlStmt)
	GoTo VBODBC_OpenSqlProc_Err
    End If
Next


'Execute the procedure
ResCode = SQLExecute(VBODBC_hstmt)
'Wait until query is done, or user pressed cancel.
'VBODBC_SqlStmt.Cancelled is set True when the user preses
'frmVBODBC2.pbCancel button.
Do Until ResCode <> SQL_STILL_EXECUTING
    'see if cancelled and haven't already called SQLCancel.
    If VBODBC_SqlStmt.Cancelled And Not AlreadyCancelled Then
	ResCode = SQLCancel(VBODBC_hstmt)
	AlreadyCancelled = True
    End If
    'let other apps have some processing time.
    DoEvents
    ResCode = SQLExecute(VBODBC_hstmt)
Loop
'check for query error
If ResCode <> SQL_SUCCESS And ResCode <> SQL_STILL_EXECUTING Then
    Call VBODBC_DescribeError("VBODBC_OpenSqlProc", "SQLExecDirect", ResCode, "[SqlStmt]" & SqlStmt)
    GoTo VBODBC_OpenSqlProc_Err
End If

'find out number of columns
ResCode = SQLNumResultCols(VBODBC_hstmt, VBODBC_NumCols)
If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
    Call VBODBC_DescribeError("VBODBC_OpenSqlProc", "SQLNumREsultCols", ResCode, "[SqlStmt]" & SqlStmt)
    GoTo VBODBC_OpenSqlProc_Err
End If

'redim holder of column information
ReDim VBODBC_ColDesc(VBODBC_NumCols)
  
'retrieve column info
For ColNum = 1 To VBODBC_NumCols
    ColName = ""
    ResCode = SQLDescribeCol(VBODBC_hstmt, ColNum, ColName, Len(ColName), ColLen, SqlType, ColDef, ColScale, Nullable)
    If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
	Call VBODBC_DescribeError("VBODBC_OpenSqlProc", "SQLDescribeCol", ResCode, "[SqlStmt]" & SqlStmt)
	GoTo VBODBC_OpenSqlProc_Err
    End If
    'column name
    VBODBC_ColDesc(ColNum).ColName = Left$(ColName, ColLen)
    'ODBC SQL type code
    VBODBC_ColDesc(ColNum).SqlType = SqlType
    'length of column
    VBODBC_ColDesc(ColNum).ColLen = ColDef
    
    'pupulate first element with tab delim const names
    If ColNum = 1 Then
	VBODBC_ColDesc(0).ColName = VBODBC_ColDesc(ColNum).ColName
    Else
	VBODBC_ColDesc(0).ColName = VBODBC_ColDesc(0).ColName & Delim & VBODBC_ColDesc(ColNum).ColName
    End If

Next ColNum

'update to new sqlstate
VBODBC_SqlState = VBODBC_SQLSTATE_OPENSTMT

Exit Function

VBODBC_OpenSqlProc_Err:
VBODBC_OpenSqlProc = SQL_ERROR

End Function

Function VBODBC_OpenSqlProcDialog (ByVal SqlStmt As String, Parms() As String, Cancelled As Integer, Caption As String) As Integer

'Exectutes the given SqlProc on the open database ansynchronously,
'if available. Sets Cancelled=true of the user cancelled the query.
'Shows a modal form with a caption of Caption to prevent the user from
'initiating any other events in the current application until the server
' is done.

'Returns SQL_SUCCESS if successful.

'Populates global VBODBC_ColDesc array which defines the
'result-set column information.

Dim ParmNum As Integer

'fill buffer with defaults and initial values
'for frmVBODC2 (the cancel form)
VBODBC_SqlStmt.StmtType = VBODBC_STMTTYPE_PROC 'indicate procedure
VBODBC_SqlStmt.SqlStmt = SqlStmt
VBODBC_SqlStmt.NumParms = UBound(Parms)
For ParmNum = 1 To UBound(Parms)
    VBODBC_SqlStmt.Parms(ParmNum) = Parms(ParmNum)
Next
VBODBC_SqlStmt.ResCode = 0
VBODBC_SqlStmt.Cancelled = 0
VBODBC_SqlStmt.Caption = Trim$(Caption)

'show the canel form, which actually executes the query
frmVBODBC2.Show 1

'see what happened, and return info to caller.
VBODBC_OpenSqlProcDialog = VBODBC_SqlStmt.ResCode
Cancelled = VBODBC_SqlStmt.Cancelled
VBODBC_SqlStmt.Caption = ""
    

Exit Function

VBODBC_OpenSqlProcDialog_Err:
VBODBC_OpenSqlProcDialog = SQL_ERROR

End Function

Function VBODBC_OpenSqlStmt (ByVal SqlStmt As String) As Integer

'Used interanally by VBODBC_OpenSqlStmtDialog to execute a SQL
'statement.

'Exectutes the given SqlStmt on the open database ansynchronously,
'if available.

'Returns SQL_SUCCESS if successful.


Dim ResCode As Integer
Dim ColNum As Integer
Dim ColName As String * 255
Dim ColLen As Integer
Dim SqlType As Integer

Dim ColDef As Long
Dim ColScale As Integer
Dim Nullable As Integer

Dim AlreadyCancelled As Integer 'true if the query has already been cancelled

Dim Delim As String
Delim = Chr$(9)

'make sure we're in right SqlState
If VBODBC_SqlState <> VBODBC_SQLSTATE_OPENDB Then
    If VBODBC_SqlState = VBODBC_SQLSTATE_CLOSED Then
	Call VBODBC_DescribeError("VBODBC_CloseDatabase", "", SQL_VBODBC_ERR, "[VBODBC] Database not open.")
    ElseIf VBODBC_SqlState = VBODBC_SQLSTATE_OPENSTMT Then
	Call VBODBC_DescribeError("VBODBC_CloseDatabase", "", SQL_VBODBC_ERR, "[VBODBC] Must close SQL Statement before opening a new SQL Statement.")
    End If
    GoTo VBODBC_OpenSqlStmt_Err
End If

'Allocate a statement handle
ResCode = SQLAllocStmt(VBODBC_hdbc, VBODBC_hstmt)
If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
    Call VBODBC_DescribeError("VBODBC_OpenSqlStmt", "SQLAllocStmt", ResCode, "[SqlStmt]" & SqlStmt)
    GoTo VBODBC_OpenSqlStmt_Err
End If
  
'enable asyncronous processing, assume error means not available
'(e.g. ignore any info)
ResCode = SQLSetStmtOption(VBODBC_hstmt, SQL_ASYNC_ENABLE, SQL_ASYNC_ENABLE_ON)

'reset holder of column information
ReDim VBODBC_ColDesc(0)

'Execute the query
ResCode = SQLExecDirect(VBODBC_hstmt, SqlStmt, Len(SqlStmt))
'Wait until query is done, or user pressed cancel.
'VBODBC_SqlStmt.Cancelled is set True when the user preses
'frmVBODBC2.pbCancel button.
Do Until ResCode <> SQL_STILL_EXECUTING
    'see if cancelled and haven't already called SQLCancel.
    If VBODBC_SqlStmt.Cancelled And Not AlreadyCancelled Then
	ResCode = SQLCancel(VBODBC_hstmt)
	AlreadyCancelled = True
    End If
    'let other apps have some processing time.
    DoEvents
    ResCode = SQLExecDirect(VBODBC_hstmt, SqlStmt, Len(SqlStmt))
Loop
'check for query error
If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO And ResCode <> SQL_STILL_EXECUTING Then
    Call VBODBC_DescribeError("VBODBC_OpenSqlStmt", "SQLExecDirect", ResCode, "[SqlStmt]" & SqlStmt)
    GoTo VBODBC_OpenSqlStmt_Err
End If

'find out number of columns
ResCode = SQLNumResultCols(VBODBC_hstmt, VBODBC_NumCols)
If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
    Call VBODBC_DescribeError("VBODBC_OpenSqlStmt", "SQLNumREsultCols", ResCode, "[SqlStmt]" & SqlStmt)
    GoTo VBODBC_OpenSqlStmt_Err
End If

'redim holder of column information
ReDim VBODBC_ColDesc(VBODBC_NumCols)
  
'retrieve column info
For ColNum = 1 To VBODBC_NumCols
    ColName = ""
    ResCode = SQLDescribeCol(VBODBC_hstmt, ColNum, ColName, Len(ColName), ColLen, SqlType, ColDef, ColScale, Nullable)
    If ResCode <> SQL_SUCCESS And ResCode <> SQL_SUCCESS_WITH_INFO Then
	Call VBODBC_DescribeError("VBODBC_OpenSqlStmt", "SQLDescribeCol", ResCode, "[SqlStmt]" & SqlStmt)
	GoTo VBODBC_OpenSqlStmt_Err
    End If
    'column name
    VBODBC_ColDesc(ColNum).ColName = Left$(ColName, ColLen)
    'ODBC SQL type code
    VBODBC_ColDesc(ColNum).SqlType = SqlType
    'length of column
    VBODBC_ColDesc(ColNum).ColLen = ColDef
    
    'pupulate first element with tab delim const names
    If ColNum = 1 Then
	VBODBC_ColDesc(0).ColName = VBODBC_ColDesc(ColNum).ColName
    Else
	VBODBC_ColDesc(0).ColName = VBODBC_ColDesc(0).ColName & Delim & VBODBC_ColDesc(ColNum).ColName
    End If

Next ColNum

'update to new sqlstate
VBODBC_SqlState = VBODBC_SQLSTATE_OPENSTMT

Exit Function

VBODBC_OpenSqlStmt_Err:
VBODBC_OpenSqlStmt = SQL_ERROR

End Function

Function VBODBC_OpenSqlStmtDialog (ByVal SqlStmt As String, Cancelled As Integer, Caption As String) As Integer

'Exectutes the given SqlStmt on the open database ansynchronously,
'if available. Sets Cancelled=true of the user cancelled the query.
'Shows a modal form with a caption of Caption to prevent the user from
'initiating any other events in the current application until the server
' is done.

'Returns SQL_SUCCESS if successful.

'Populates global VBODBC_ColDesc array which defines the
'result-set column information.


'fill buffer with defaults and initial values
'for frmVBODC2 (the cancel form)
VBODBC_SqlStmt.StmtType = VBODBC_STMTTYPE_SQL 'indicate SQL
VBODBC_SqlStmt.SqlStmt = SqlStmt
VBODBC_SqlStmt.NumParms = 0
'VBODBC_SqlStmt.Parm(ParmNum) =
VBODBC_SqlStmt.ResCode = 0
VBODBC_SqlStmt.Cancelled = 0
VBODBC_SqlStmt.Caption = Trim$(Caption)

'show the canel form, which actually executes the query
frmVBODBC2.Show 1

'see what happened, and return info to caller.
VBODBC_OpenSqlStmtDialog = VBODBC_SqlStmt.ResCode
Cancelled = VBODBC_SqlStmt.Cancelled
VBODBC_SqlStmt.Caption = ""
    

Exit Function

VBODBC_OpenSqlStmtDialog_Err:
VBODBC_OpenSqlStmtDialog = SQL_ERROR

End Function

