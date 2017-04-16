Attribute VB_Name = "ODBC32"
#If Win32 Then
'
'|========================================================================|
'| ODBC Module Core Definitions                                           |
'|========================================================================|
'
'  ODBC Core API's Definitions -- 32 bit versions
'
Declare Function SQLAllocConnect Lib "odbc32.dll" (ByVal henv&, phdbc&) As Integer
Declare Function SQLAllocEnv Lib "odbc32.dll" (phenv&) As Integer
Declare Function SQLAllocStmt Lib "odbc32.dll" (ByVal hdbc&, phstmt&) As Integer
Declare Function SQLBindCol Lib "odbc32.dll" (ByVal hstmt&, ByVal icol%, ByVal fCType%, rgbValue As Any, ByVal cbValueMax&, pcbValue&) As Integer
Declare Function SQLCancel Lib "odbc32.dll" (ByVal hstmt&) As Integer

Declare Function SQLColAttributes Lib "odbc32.dll" (ByVal hstmt&, ByVal icol%, ByVal fDescType%, rgbDesc As Any, ByVal cbDescMax%, pcbDesc%, pfDesc&) As Integer
Declare Function SQLColAttributesString Lib "odbc32.dll" Alias "SQLColAttributes" (ByVal hstmt&, ByVal icol%, ByVal fDescType%, ByVal rgbDesc As String, ByVal cbDescMax%, pcbDesc%, pfDesc&) As Integer

Declare Function SQLConnect Lib "odbc32.dll" (ByVal hdbc&, ByVal szDSN$, ByVal cbDSN%, ByVal szUID$, ByVal cbUID%, ByVal szAuthStr$, ByVal cbAuthStr%) As Integer
Declare Function SQLDescribeCol Lib "odbc32.dll" (ByVal hstmt&, ByVal icol%, ByVal szColName$, ByVal cbColNameMax%, pcbColName%, pfSqlType%, pcbColDef&, pibScale%, pfNullable%) As Integer
Declare Function SQLDisconnect Lib "odbc32.dll" (ByVal hdbc&) As Integer
Declare Function SQLError Lib "odbc32.dll" (ByVal henv&, ByVal hdbc&, ByVal hstmt&, ByVal szSqlState$, pfNativeError&, ByVal szErrorMsg$, ByVal cbErrorMsgMax%, pcbErrorMsg%) As Integer
Declare Function SQLExecDirect Lib "odbc32.dll" (ByVal hstmt&, ByVal szSqlStr$, ByVal cbSqlStr&) As Integer
Declare Function SQLExecute Lib "odbc32.dll" (ByVal hstmt&) As Integer
Declare Function SQLFetch Lib "odbc32.dll" (ByVal hstmt&) As Integer
Declare Function SQLFreeConnect Lib "odbc32.dll" (ByVal hdbc&) As Integer
Declare Function SQLFreeEnv Lib "odbc32.dll" (ByVal henv&) As Integer
Declare Function SQLFreeStmt Lib "odbc32.dll" (ByVal hstmt&, ByVal fOption%) As Integer
Declare Function SQLGetCursorName Lib "odbc32.dll" (ByVal hstmt&, ByVal szCursor$, ByVal cbCursorMax%, pcbCursor%) As Integer
Declare Function SQLNumResultCols Lib "odbc32.dll" (ByVal hstmt&, pccol%) As Integer
Declare Function SQLPrepare Lib "odbc32.dll" (ByVal hstmt&, ByVal szSqlStr$, ByVal cbSqlStr&) As Integer
Declare Function SQLRowCount Lib "odbc32.dll" (ByVal hstmt&, pcrow&) As Integer
Declare Function SQLSetCursorName Lib "odbc32.dll" (ByVal hstmt&, ByVal szCursor$, ByVal cbCursor%) As Integer
Declare Function SQLSetParam Lib "odbc32.dll" (ByVal hstmt&, ByVal ipar%, ByVal fCType%, ByVal fSqlType%, ByVal cbColDef&, ByVal ibScale%, rgbValue As Any, pcbValue&) As Integer
Declare Function SQLTransact Lib "odbc32.dll" (ByVal henv&, ByVal hdbc&, ByVal fType%) As Integer
'
'|========================================================================|
'| ODBC Module Extended Definitions                                       |
'|========================================================================|
''  Level 1 Prototypes
'
Declare Function SQLBindParameter Lib "odbc32.dll" (ByVal hstmt&, ByVal ipar%, ByVal fParamType%, ByVal fCType%, ByVal fSqlType%, ByVal cbColDef&, ByVal ibScale%, rgbValue As Any, ByVal cbValueMax&, pcbValue As Long) As Integer
Declare Function SQLColumns Lib "odbc32.dll" (ByVal hstmt&, szTblQualifier As Any, ByVal cbTblQualifier%, szTblOwner As Any, ByVal cbTblOwner%, szTblName As Any, ByVal cbTblName%, szColName As Any, ByVal cbColName%) As Integer
Declare Function SQLDriverConnect Lib "odbc32.dll" (ByVal hdbc&, ByVal hWnd As Long, ByVal szCSIn$, ByVal cbCSIn%, ByVal szCSOut$, ByVal cbCSMax%, cbCSOut%, ByVal fDrvrComp%) As Integer

Declare Function SQLGetConnectOption Lib "odbc32.dll" (ByVal hdbc&, ByVal fOption%, ByRef pvParam As Any) As Integer
Declare Function SQLGetConnectOptionString Lib "odbc32.dll" Alias "SQLGetConnectOption" (ByVal hdbc&, ByVal fOption%, ByVal pvParam As String) As Integer

Declare Function SQLGetData Lib "odbc32.dll" (ByVal hstmt&, ByVal icol%, ByVal fCType%, ByVal rgbValue As String, ByVal cbValueMax&, pcbValue&) As Integer
Declare Function SQLGetNumericData Lib "odbc32.dll" Alias "SQLGetData" (ByVal hstmt&, ByVal icol%, ByVal fCType%, ByRef rgbValue As Any, ByVal cbValueMax&, pcbValue&) As Integer

Declare Function SQLGetFunctions Lib "odbc32.dll" (ByVal hdbc&, ByVal fFunction%, pfExists%) As Integer

Declare Function SQLGetInfo Lib "odbc32.dll" (ByVal hdbc&, ByVal fInfoType%, ByRef rgbInfoValue As Any, ByVal cbInfoMax%, cbInfoOut%) As Integer
Declare Function SQLGetInfoString Lib "odbc32.dll" Alias "SQLGetInfo" (ByVal hdbc&, ByVal fInfoType%, ByVal rgbInfoValue As String, ByVal cbInfoMax%, cbInfoOut%) As Integer

Declare Function SQLGetStmtOption Lib "odbc32.dll" (ByVal hstmt&, ByVal fOption%, ByRef pvParam As Any) As Integer
Declare Function SQLGetStmtOptionString Lib "odbc32.dll" Alias "SQLGetStmtOption" (ByVal hstmt&, ByVal fOption%, ByVal pvParam As String) As Integer

Declare Function SQLGetTypeInfo Lib "odbc32.dll" (ByVal hstmt&, ByVal fSqlType%) As Integer
Declare Function SQLParamData Lib "odbc32.dll" (ByVal hstmt&, prgbValue As Any) As Integer
Declare Function SQLPutData Lib "odbc32.dll" (ByVal hstmt&, rgbValue As Any, ByVal cbValue&) As Integer
Declare Function SQLSetConnectOption Lib "odbc32.dll" (ByVal hdbc&, ByVal fOption%, ByVal vParam As Any) As Integer
Declare Function SQLSetConnectStringOption Lib "odbc32.dll" Alias "SQLSetConnectOption" (ByVal hdbc&, ByVal fOption%, vParam$) As Integer

Declare Function SQLSetStmtOption Lib "odbc32.dll" (ByVal hstmt&, ByVal fOption%, ByVal vParam&) As Integer
Declare Function SQLSpecialColumns Lib "odbc32.dll" (ByVal hstmt&, ByVal fColType%, szTblQualifier As Any, ByVal cbTblQualifier%, szTblOwner As Any, ByVal cbTblOwner%, szTblName As Any, ByVal cbTblName%, ByVal fScope%, ByVal fNullable%) As Integer
Declare Function SQLStatistics Lib "odbc32.dll" (ByVal hstmt&, szTblQualifier As Any, ByVal cbTblQualifier%, szTblOwner As Any, ByVal cbTblOwner%, szTblName As Any, ByVal cbTblName%, ByVal fUnique%, ByVal fAccuracy%) As Integer
Declare Function SQLTables Lib "odbc32.dll" (ByVal hstmt&, szTblQualifier As Any, ByVal cbTblQualifier%, szTblOwner As Any, ByVal cbTblOwner%, szTblName As Any, ByVal cbTblName%, szTblType As Any, ByVal cbTblType%) As Integer

'  Level 2 Prototypes
'
Declare Function SQLBrowseConnect Lib "odbc32.dll" (ByVal hdbc&, ByVal szConnStrIn$, ByVal cbConnStrIn%, ByVal szConnStrOut$, ByVal cbConnStrOutMax%, pcbConnStrOut%) As Integer
Declare Function SQLColumnPrivileges Lib "odbc32.dll" (ByVal hstmt&, szTQf As Any, ByVal cbTQf%, szTOwn As Any, ByVal cbTOwn%, szTName As Any, ByVal cbTName%, szColName As Any, ByVal cbColName%) As Integer
Declare Function SQLDrivers Lib "odbc32.dll" (ByVal henv&, ByVal fDirection%, ByVal szDriverDesc$, ByVal cbDriverDescMax%, pcbDriverDesc%, ByVal szDriverAttr$, ByVal cbDrvrAttrMax%, pcbDrvrAttr%) As Integer
Declare Function SQLDataSources Lib "odbc32.dll" (ByVal henv&, ByVal fDirection%, ByVal szDSN$, ByVal cbDSNMax%, pcbDSN%, ByVal szDescription$, ByVal cbDescriptionMax%, pcbDescription%) As Integer
Declare Function SQLDescribeParam Lib "odbc32.dll" (ByVal hstmt&, ByVal ipar%, pfSqlType%, pcbColDef&, pibScale%, pfNullable%) As Integer
Declare Function SQLExtendedFetch Lib "odbc32.dll" (ByVal hstmt&, ByVal fFetchType%, ByVal irow&, pcrow&, rgfRowStatus%) As Integer
Declare Function SQLForeignKeys Lib "odbc32.dll" (ByVal hstmt&, ByVal PTQual&, ByVal PTQual%, ByVal PTOwnr&, ByVal PTOwnr%, ByVal PTName&, ByVal PTName%, ByVal FTQual&, ByVal FTQf%, ByVal FTOwnr&, ByVal FTOwnr%, ByVal FTName&, ByVal FTName%) As Integer
Declare Function SQLMoreResults Lib "odbc32.dll" (ByVal hstmt&) As Integer
Declare Function SQLNativeSql Lib "odbc32.dll" (ByVal hdbc&, ByVal szSqlStrIn$, ByVal cbSqlStrIn&, ByVal szSqlStr$, ByVal cbSqlStrMax&, pcbSqlStr&) As Integer
Declare Function SQLNumParams Lib "odbc32.dll" (ByVal hstmt&, pcpar%) As Integer
Declare Function SQLParamOptions Lib "odbc32.dll" (ByVal hstmt&, ByVal crow%, pirow&) As Integer
Declare Function SQLPrimaryKeys Lib "odbc32.dll" (ByVal hstmt&, szTblQualifier As Any, ByVal cbTblQualifier%, szTblOwner As Any, ByVal cbTblOwner%, szTblName As Any, ByVal cbTblName%) As Integer
Declare Function SQLProcedureColumns Lib "odbc32.dll" (ByVal hstmt&, szProcQualifier As Any, ByVal cbProcQualifier%, szProcOwner As Any, ByVal cbProcOwner%, szProcName As Any, ByVal cbProcName%, szColName As Any, ByVal cbColName%) As Integer
Declare Function SQLProcedures Lib "odbc32.dll" (ByVal hstmt&, szProcQualifier As Any, ByVal cbProcQualifier%, szProcOwner As Any, ByVal cbProcOwner%, szProcName As Any, ByVal cbProcName%) As Integer
Declare Function SQLSetPos Lib "odbc32.dll" (ByVal hstmt&, ByVal irow%, ByVal fOption%, ByVal fLock%) As Integer
Declare Function SQLSetScrollOptions Lib "odbc32.dll" (ByVal hstmt&, ByVal fConcurrency%, ByVal crowKeyset&, ByVal crowRowset%) As Integer
Declare Function SQLTablePrivileges Lib "odbc32.dll" (ByVal hstmt&, szTblQualifier As Any, ByVal cbTblQualifier%, szTblOwner As Any, ByVal cbTblOwner%, szTblName As Any, ByVal cbTblName%) As Integer
'
'  32 Bit declares
'  ODBC Constants/Types
'
'  generally useful constants
'
Global Const SQL_NTS As Long = -3                  '  NTS = Null Terminated String
Global Const SQL_SQLSTATE_SIZE As Long = 5         '  size of SQLSTATE
Global Const SQL_MAX_MESSAGE_LENGTH As Long = 512  '  message buffer size
Global Const SQL_MAX_DSN_LENGTH As Long = 32       '  maximum data source name size

'  RETCODEs
'
Global Const SQL_ERROR As Long = -1
Global Const SQL_INVALID_HANDLE As Long = -2
Global Const SQL_NO_DATA_FOUND As Long = 100
Global Const SQL_SUCCESS As Long = 0
Global Const SQL_SUCCESS_WITH_INFO As Long = 1

'  SQLFreeStmt defines
'
Global Const SQL_CLOSE As Long = 0
Global Const SQL_DROP As Long = 1
Global Const SQL_UNBIND As Long = 2
Global Const SQL_RESET_PARAMS As Long = 3

'  SQLSetParam defines
'
Global Const SQL_C_DEFAULT As Long = 99

'  SQLTransact defines
'
Global Const SQL_COMMIT As Long = 0
Global Const SQL_ROLLBACK As Long = 1

'  Standard SQL datatypes, using ANSI type numbering
'
Global Const SQL_CHAR As Long = 1
Global Const SQL_NUMERIC As Long = 2
Global Const SQL_DECIMAL As Long = 3
Global Const SQL_INTEGER As Long = 4
Global Const SQL_SMALLINT As Long = 5
Global Const SQL_FLOAT As Long = 6
Global Const SQL_REAL As Long = 7
Global Const SQL_DOUBLE As Long = 8
Global Const SQL_VARCHAR As Long = 12

Global Const SQL_TYPE_MIN As Long = 1
Global Const SQL_TYPE_NULL As Long = 0
Global Const SQL_TYPE_MAX As Long = 12

'  C datatype to SQL datatype mapping    SQL types
'
Global Const SQL_C_CHAR As Long = SQL_CHAR         '  CHAR, VARCHAR, DECIMAL, NUMERIC
Global Const SQL_C_LONG As Long = SQL_INTEGER      '  INTEGER
Global Const SQL_C_SHORT As Long = SQL_SMALLINT    '  SMALLINT
Global Const SQL_C_FLOAT As Long = SQL_REAL        '  REAL
Global Const SQL_C_DOUBLE As Long = SQL_DOUBLE     '  FLOAT, DOUBLE

'  NULL status constants.  These are used in SQLColumns, SQLColAttributes,
'  SQLDescribeCol, and SQLSpecialColumns to describe the nullablity of a
'  column in a table.  SQL_NULLABLE_UNKNOWN can be returned only by
'  SQLDescribeCol or SQLColAttributes.  It is used when the DBMS's meta-data
'  does not contain this info.
'
Global Const SQL_NO_NULLS As Long = 0
Global Const SQL_NULLABLE As Long = 1
Global Const SQL_NULLABLE_UNKNOWN As Long = 2

'  Special length values
'
Global Const SQL_NULL_DATA As Long = -1
Global Const SQL_DATA_AT_EXEC As Long = -2

'  SQLColAttributes defines
'
Global Const SQL_COLUMN_COUNT As Long = 0
Global Const SQL_COLUMN_NAME As Long = 1
Global Const SQL_COLUMN_TYPE As Long = 2
Global Const SQL_COLUMN_LENGTH As Long = 3
Global Const SQL_COLUMN_PRECISION As Long = 4
Global Const SQL_COLUMN_SCALE As Long = 5
Global Const SQL_COLUMN_DISPLAY_SIZE As Long = 6
Global Const SQL_COLUMN_NULLABLE As Long = 7
Global Const SQL_COLUMN_UNSIGNED As Long = 8
Global Const SQL_COLUMN_MONEY As Long = 9
Global Const SQL_COLUMN_UPDATABLE As Long = 10
Global Const SQL_COLUMN_AUTO_INCREMENT As Long = 11
Global Const SQL_COLUMN_CASE_SENSITIVE As Long = 12
Global Const SQL_COLUMN_SEARCHABLE As Long = 13
Global Const SQL_COLUMN_TYPE_NAME As Long = 14
Global Const SQL_COLUMN_TABLE_NAME As Long = 15
Global Const SQL_COLUMN_OWNER_NAME As Long = 16
Global Const SQL_COLUMN_QUALIFIER_NAME As Long = 17
Global Const SQL_COLUMN_LABEL As Long = 18
Global Const SQL_COLATT_OPT_MAX As Long = SQL_COLUMN_LABEL

'  SQLColAttributes subdefines for SQL_COLUMN_UPDATABLE
'
Global Const SQL_ATTR_READONLY As Long = 0
Global Const SQL_ATTR_WRITE As Long = 1
Global Const SQL_ATTR_READWRITE_UNKNOWN As Long = 2

'  SQLColAttributes subdefines for SQL_COLUMN_SEARCHABLE
'  These are also used by SQLGetInfo
'
Global Const SQL_UNSEARCHABLE As Long = 0
Global Const SQL_LIKE_ONLY As Long = 1
Global Const SQL_ALL_EXCEPT_LIKE As Long = 2
Global Const SQL_SEARCHABLE As Long = 3

'  SQLError defines
'
Global Const SQL_NULL_HENV As Long = 0
Global Const SQL_NULL_HDBC As Long = 0
Global Const SQL_NULL_HSTMT As Long = 0


'|========================================================================|
'| ODBC Global Extended Definitions                                       |
'|========================================================================|

' Level 1 Definitions/Functions
' Generally useful constants
'
Global Const SQL_MAX_OPTION_STRING_LENGTH = 256

' Additional return codes
'
Global Const SQL_STILL_EXECUTING As Long = 2
Global Const SQL_NEED_DATA As Long = 99

' SQL extended datatypes
'
Global Const SQL_DATE As Long = 9
Global Const SQL_TIME As Long = 10
Global Const SQL_TIMESTAMP As Long = 11
Global Const SQL_LONGVARCHAR As Long = -1
Global Const SQL_BINARY As Long = -2
Global Const SQL_VARBINARY As Long = -3
Global Const SQL_LONGVARBINARY As Long = -4
Global Const SQL_BIGINT As Long = -5
Global Const SQL_TINYINT As Long = -6
Global Const SQL_BIT As Long = -7
Global Const SQL_TYPE_DRIVER_START As Long = -80

' C datatype to SQL datatype mapping
'
'
Global Const SQL_SIGNED_OFFSET As Long = -20
Global Const SQL_UNSIGNED_OFFSET As Long = -22

Global Const SQL_C_DATE As Long = SQL_DATE
Global Const SQL_C_TIME As Long = SQL_TIME
Global Const SQL_C_TIMESTAMP As Long = SQL_TIMESTAMP
Global Const SQL_C_BINARY As Long = SQL_BINARY
Global Const SQL_C_BIT As Long = SQL_BIT
Global Const SQL_C_TINYINT As Long = SQL_TINYINT
Global Const SQL_C_SLONG As Long = SQL_C_LONG + SQL_SIGNED_OFFSET
Global Const SQL_C_SSHORT As Long = SQL_C_SHORT + SQL_SIGNED_OFFSET
Global Const SQL_C_STINYINT As Long = SQL_TINYINT + SQL_SIGNED_OFFSET
Global Const SQL_C_ULONG As Long = SQL_C_LONG + SQL_UNSIGNED_OFFSET
Global Const SQL_C_USHORT As Long = SQL_C_SHORT + SQL_UNSIGNED_OFFSET
Global Const SQL_C_UTINYINT As Long = SQL_TINYINT + SQL_UNSIGNED_OFFSET
Global Const SQL_C_BOOKMARK As Long = SQL_C_ULONG


Global Const SQL_ALL_TYPES As Long = 0
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
Global Const SQL_DRIVER_NOPROMPT As Long = 0
Global Const SQL_DRIVER_COMPLETE As Long = 1
Global Const SQL_DRIVER_PROMPT As Long = 2
Global Const SQL_DRIVER_COMPLETE_REQUIRED As Long = 3

' Special return values for SQLGetData
'
Global Const SQL_NO_TOTAL As Long = -4

' SQLSetParam extensions
'
Global Const SQL_DEFAULT_PARAM As Long = -5
Global Const SQL_IGNORE As Long = -6
Global Const SQL_LEN_DATA_AT_EXEC_OFFSET As Long = -100


' Defines for SQLGetFunctions
' Core Functions
'
Global Const SQL_API_SQLALLOCCONNECT As Long = 1
Global Const SQL_API_SQLALLOCENV As Long = 2
Global Const SQL_API_SQLALLOCSTMT As Long = 3
Global Const SQL_API_SQLBINDCOL As Long = 4
Global Const SQL_API_SQLCANCEL As Long = 5
Global Const SQL_API_SQLCOLATTRIBUTES As Long = 6
Global Const SQL_API_SQLCONNECT As Long = 7
Global Const SQL_API_SQLDESCRIBECOL As Long = 8
Global Const SQL_API_SQLDISCONNECT As Long = 9
Global Const SQL_API_SQLERROR As Long = 10
Global Const SQL_API_SQLEXECDIRECT As Long = 11
Global Const SQL_API_SQLEXECUTE As Long = 12
Global Const SQL_API_SQLFETCH As Long = 13
Global Const SQL_API_SQLFREECONNECT As Long = 14
Global Const SQL_API_SQLFREEENV As Long = 15
Global Const SQL_API_SQLFREESTMT As Long = 16
Global Const SQL_API_SQLGETCURSORNAME As Long = 17
Global Const SQL_API_SQLNUMRESULTCOLS As Long = 18
Global Const SQL_API_SQLPREPARE As Long = 19
Global Const SQL_API_SQLROWCOUNT As Long = 20
Global Const SQL_API_SQLSETCURSORNAME As Long = 21
Global Const SQL_API_SQLSETPARAM As Long = 22
Global Const SQL_API_SQLTRANSACT As Long = 23
Global Const SQL_NUM_FUNCTIONS As Long = 23
Global Const SQL_EXT_API_START As Long = 40

' Level 1 Functions
'
Global Const SQL_API_SQLCOLUMNS As Long = 40
Global Const SQL_API_SQLDRIVERCONNECT As Long = 41
Global Const SQL_API_SQLGETCONNECTOPTION As Long = 42
Global Const SQL_API_SQLGETDATA As Long = 43
Global Const SQL_API_SQLGETFUNCTIONS As Long = 44
Global Const SQL_API_SQLGETINFO As Long = 45
Global Const SQL_API_SQLGETSTMTOPTION As Long = 46
Global Const SQL_API_SQLGETTYPEINFO As Long = 47
Global Const SQL_API_SQLPARAMDATA As Long = 48
Global Const SQL_API_SQLPUTDATA As Long = 49
Global Const SQL_API_SQLSETCONNECTOPTION As Long = 50
Global Const SQL_API_SQLSETSTMTOPTION As Long = 51
Global Const SQL_API_SQLSPECIALCOLUMNS As Long = 52
Global Const SQL_API_SQLSTATISTICS As Long = 53
Global Const SQL_API_SQLTABLES As Long = 54

' Level 2 Functions
'
Global Const SQL_API_SQLBROWSECONNECT As Long = 55
Global Const SQL_API_SQLCOLUMNPRIVILEGES As Long = 56
Global Const SQL_API_SQLDATASOURCES As Long = 57
Global Const SQL_API_SQLDESCRIBEPARAM As Long = 58
Global Const SQL_API_SQLEXTENDEDFETCH As Long = 59
Global Const SQL_API_SQLFOREIGNKEYS As Long = 60
Global Const SQL_API_SQLMORERESULTS As Long = 61
Global Const SQL_API_SQLNATIVESQL As Long = 62
Global Const SQL_API_SQLNUMPARAMS As Long = 63
Global Const SQL_API_SQLPARAMOPTIONS As Long = 64
Global Const SQL_API_SQLPRIMARYKEYS As Long = 65
Global Const SQL_API_SQLPROCEDURECOLUMNS As Long = 66
Global Const SQL_API_SQLPROCEDURES As Long = 67
Global Const SQL_API_SQLSETPOS As Long = 68
Global Const SQL_API_SQLSETSCROLLOPTIONS As Long = 69
Global Const SQL_API_SQLTABLEPRIVILEGES As Long = 70
Global Const SQL_API_SQLDRIVERS As Long = 71
Global Const SQL_API_SQLBINDPARAMETER As Long = 72

Global Const SQL_EXT_API_LAST As Long = 72
Global Const SQL_API_ALL_FUNCTIONS As Long = 0

Global Const SQL_NUM_EXTENSIONS As Long = (SQL_EXT_API_LAST - SQL_EXT_API_START + 1)

' Defines for SQLGetInfo
'
Global Const SQL_INFO_FIRST As Long = 0
Global Const SQL_ACTIVE_CONNECTIONS As Long = 0
Global Const SQL_ACTIVE_STATEMENTS As Long = 1
Global Const SQL_DATA_SOURCE_NAME As Long = 2
Global Const SQL_DRIVER_HDBC As Long = 3
Global Const SQL_DRIVER_HENV As Long = 4
Global Const SQL_DRIVER_HSTMT As Long = 5
Global Const SQL_DRIVER_NAME As Long = 6
Global Const SQL_DRIVER_VER As Long = 7
Global Const SQL_FETCH_DIRECTION As Long = 8
Global Const SQL_ODBC_API_CONFORMANCE As Long = 9
Global Const SQL_ODBC_VER As Long = 10
Global Const SQL_ROW_UPDATES As Long = 11
Global Const SQL_ODBC_SAG_CLI_CONFORMANCE As Long = 12
Global Const SQL_SERVER_NAME As Long = 13
Global Const SQL_SEARCH_PATTERN_ESCAPE As Long = 14
Global Const SQL_ODBC_SQL_CONFORMANCE As Long = 15

Global Const SQL_DBMS_NAME As Long = 17
Global Const SQL_DBMS_VER As Long = 18

Global Const SQL_ACCESSIBLE_TABLES As Long = 19
Global Const SQL_ACCESSIBLE_PROCEDURES As Long = 20
Global Const SQL_PROCEDURES As Long = 21
Global Const SQL_CONCAT_NULL_BEHAVIOR As Long = 22
Global Const SQL_CURSOR_COMMIT_BEHAVIOR As Long = 23
Global Const SQL_CURSOR_ROLLBACK_BEHAVIOR As Long = 24
Global Const SQL_DATA_SOURCE_READ_ONLY As Long = 25
Global Const SQL_DEFAULT_TXN_ISOLATION As Long = 26
Global Const SQL_EXPRESSIONS_IN_ORDERBY As Long = 27
Global Const SQL_IDENTIFIER_CASE As Long = 28
Global Const SQL_IDENTIFIER_QUOTE_CHAR As Long = 29
Global Const SQL_MAX_COLUMN_NAME_LEN As Long = 30
Global Const SQL_MAX_CURSOR_NAME_LEN As Long = 31
Global Const SQL_MAX_OWNER_NAME_LEN As Long = 32
Global Const SQL_MAX_PROCEDURE_NAME_LEN As Long = 33
Global Const SQL_MAX_QUALIFIER_NAME_LEN As Long = 34
Global Const SQL_MAX_TABLE_NAME_LEN As Long = 35
Global Const SQL_MULT_RESULT_SETS As Long = 36
Global Const SQL_MULTIPLE_ACTIVE_TXN As Long = 37
Global Const SQL_OUTER_JOINS As Long = 38
Global Const SQL_OWNER_TERM As Long = 39
Global Const SQL_PROCEDURE_TERM As Long = 40
Global Const SQL_QUALIFIER_NAME_SEPARATOR As Long = 41
Global Const SQL_QUALIFIER_TERM As Long = 42
Global Const SQL_SCROLL_CONCURRENCY As Long = 43
Global Const SQL_SCROLL_OPTIONS As Long = 44
Global Const SQL_TABLE_TERM As Long = 45
Global Const SQL_TXN_CAPABLE As Long = 46
Global Const SQL_USER_NAME As Long = 47

Global Const SQL_CONVERT_FUNCTIONS As Long = 48
Global Const SQL_NUMERIC_FUNCTIONS As Long = 49
Global Const SQL_STRING_FUNCTIONS As Long = 50
Global Const SQL_SYSTEM_FUNCTIONS As Long = 51
Global Const SQL_TIMEDATE_FUNCTIONS As Long = 52

Global Const SQL_CONVERT_BIGINT As Long = 53
Global Const SQL_CONVERT_BINARY As Long = 54
Global Const SQL_CONVERT_BIT As Long = 55
Global Const SQL_CONVERT_CHAR As Long = 56
Global Const SQL_CONVERT_DATE As Long = 57
Global Const SQL_CONVERT_DECIMAL As Long = 58
Global Const SQL_CONVERT_DOUBLE As Long = 59
Global Const SQL_CONVERT_FLOAT As Long = 60
Global Const SQL_CONVERT_INTEGER As Long = 61
Global Const SQL_CONVERT_LONGVARCHAR As Long = 62
Global Const SQL_CONVERT_NUMERIC As Long = 63
Global Const SQL_CONVERT_REAL As Long = 64
Global Const SQL_CONVERT_SMALLINT As Long = 65
Global Const SQL_CONVERT_TIME As Long = 66
Global Const SQL_CONVERT_TIMESTAMP As Long = 67
Global Const SQL_CONVERT_TINYINT As Long = 68
Global Const SQL_CONVERT_VARBINARY As Long = 69
Global Const SQL_CONVERT_VARCHAR As Long = 70
Global Const SQL_CONVERT_LONGVARBINARY As Long = 71

Global Const SQL_TXN_ISOLATION_OPTION As Long = 72
Global Const SQL_ODBC_SQL_OPT_IEF As Long = 73
Global Const SQL_CORRELATION_NAME As Long = 74
Global Const SQL_NON_NULLABLE_COLUMNS As Long = 75
Global Const SQL_DRIVER_HLIB As Long = 76
Global Const SQL_DRIVER_ODBC_VER As Long = 77
Global Const SQL_LOCK_TYPES As Long = 78
Global Const SQL_POS_OPERATIONS As Long = 79
Global Const SQL_POSITIONED_STATEMENTS As Long = 80
Global Const SQL_GETDATA_EXTENSIONS As Long = 81
Global Const SQL_BOOKMARK_PERSISTENCE As Long = 82
Global Const SQL_STATIC_SENSITIVITY As Long = 83
Global Const SQL_FILE_USAGE As Long = 84
Global Const SQL_NULL_COLLATION As Long = 85
Global Const SQL_ALTER_TABLE As Long = 86
Global Const SQL_COLUMN_ALIAS As Long = 87
Global Const SQL_GROUP_BY As Long = 88
Global Const SQL_KEYWORDS As Long = 89
Global Const SQL_ORDER_BY_COLUMNS_IN_SELECT As Long = 90
Global Const SQL_OWNER_USAGE As Long = 91
Global Const SQL_QUALIFIER_USAGE As Long = 92
Global Const SQL_QUOTED_IDENTIFIER_CASE As Long = 93
Global Const SQL_SPECIAL_CHARACTERS As Long = 94
Global Const SQL_SUBQUERIES As Long = 95
Global Const SQL_UNION As Long = 96
Global Const SQL_MAX_COLUMNS_IN_GROUP_BY As Long = 97
Global Const SQL_MAX_COLUMNS_IN_INDEX As Long = 98
Global Const SQL_MAX_COLUMNS_IN_ORDER_BY As Long = 99
Global Const SQL_MAX_COLUMNS_IN_SELECT As Long = 100
Global Const SQL_MAX_COLUMNS_IN_TABLE As Long = 101
Global Const SQL_MAX_INDEX_SIZE As Long = 102
Global Const SQL_MAX_ROW_SIZE_INCLUDES_LONG As Long = 103
Global Const SQL_MAX_ROW_SIZE As Long = 104
Global Const SQL_MAX_STATEMENT_LEN As Long = 105
Global Const SQL_MAX_TABLES_IN_SELECT As Long = 106
Global Const SQL_MAX_USER_NAME_LEN As Long = 107
Global Const SQL_MAX_CHAR_LITERAL_LEN As Long = 108
Global Const SQL_TIMEDATE_ADD_INTERVALS As Long = 109
Global Const SQL_TIMEDATE_DIFF_INTERVALS As Long = 110
Global Const SQL_NEED_LONG_DATA_LEN As Long = 111
Global Const SQL_MAX_BINARY_LITERAL_LEN As Long = 112
Global Const SQL_LIKE_ESCAPE_CLAUSE As Long = 113
Global Const SQL_QUALIFIER_LOCATION As Long = 114


Global Const SQL_INFO_LAST As Long = SQL_QUALIFIER_LOCATION
Global Const SQL_INFO_DRIVER_START As Long = 1000

' "SQL_CONVERT_" return value bitmasks
'
Global Const SQL_CVT_CHAR As Long = &H1&
Global Const SQL_CVT_NUMERIC As Long = &H2&
Global Const SQL_CVT_DECIMAL As Long = &H4&
Global Const SQL_CVT_INTEGER As Long = &H8&
Global Const SQL_CVT_SMALLINT As Long = &H10&
Global Const SQL_CVT_FLOAT As Long = &H20&
Global Const SQL_CVT_REAL As Long = &H40&
Global Const SQL_CVT_DOUBLE As Long = &H80&
Global Const SQL_CVT_VARCHAR As Long = &H100&
Global Const SQL_CVT_LONGVARCHAR As Long = &H200&
Global Const SQL_CVT_BINARY As Long = &H400&
Global Const SQL_CVT_VARBINARY As Long = &H800&
Global Const SQL_CVT_BIT As Long = &H1000&
Global Const SQL_CVT_TINYINT As Long = &H2000&
Global Const SQL_CVT_BIGINT As Long = &H4000&
Global Const SQL_CVT_DATE As Long = &H8000&
Global Const SQL_CVT_TIME As Long = &H10000
Global Const SQL_CVT_TIMESTAMP As Long = &H20000
Global Const SQL_CVT_LONGVARBINARY As Long = &H40000


' Conversion functions
'
Global Const SQL_FN_CVT_CONVERT As Long = &H1&

' String functions
'
Global Const SQL_FN_STR_CONCAT As Long = &H1&
Global Const SQL_FN_STR_INSERT As Long = &H2&
Global Const SQL_FN_STR_LEFT As Long = &H4&
Global Const SQL_FN_STR_LTRIM As Long = &H8&
Global Const SQL_FN_STR_LENGTH As Long = &H10&
Global Const SQL_FN_STR_LOCATE As Long = &H20&
Global Const SQL_FN_STR_LCASE As Long = &H40&
Global Const SQL_FN_STR_REPEAT As Long = &H80&
Global Const SQL_FN_STR_REPLACE As Long = &H100&
Global Const SQL_FN_STR_RIGHT As Long = &H200&
Global Const SQL_FN_STR_RTRIM As Long = &H400&
Global Const SQL_FN_STR_SUBSTRING As Long = &H800&
Global Const SQL_FN_STR_UCASE As Long = &H1000&
Global Const SQL_FN_STR_ASCII As Long = &H2000&
Global Const SQL_FN_STR_CHAR As Long = &H4000&
Global Const SQL_FN_STR_DIFFERENCE As Long = &H8000&
Global Const SQL_FN_STR_LOCATE_2 As Long = &H10000
Global Const SQL_FN_STR_SOUNDEX As Long = &H20000
Global Const SQL_FN_STR_SPACE As Long = &H40000


' Numeric functions
'
Global Const SQL_FN_NUM_ABS As Long = &H1&
Global Const SQL_FN_NUM_ACOS As Long = &H2&
Global Const SQL_FN_NUM_ASIN As Long = &H4&
Global Const SQL_FN_NUM_ATAN As Long = &H8&
Global Const SQL_FN_NUM_ATAN2 As Long = &H10&
Global Const SQL_FN_NUM_CEILING As Long = &H20&
Global Const SQL_FN_NUM_COS As Long = &H40&
Global Const SQL_FN_NUM_COT As Long = &H80&
Global Const SQL_FN_NUM_EXP As Long = &H100&
Global Const SQL_FN_NUM_FLOOR As Long = &H200&
Global Const SQL_FN_NUM_LOG As Long = &H400&
Global Const SQL_FN_NUM_MOD As Long = &H800&
Global Const SQL_FN_NUM_SIGN As Long = &H1000&
Global Const SQL_FN_NUM_SIN As Long = &H2000&
Global Const SQL_FN_NUM_SQRT As Long = &H4000&
Global Const SQL_FN_NUM_TAN As Long = &H8000&
Global Const SQL_FN_NUM_PI As Long = &H10000
Global Const SQL_FN_NUM_RAND As Long = &H20000
Global Const SQL_FN_NUM_DEGREES As Long = &H40000
Global Const SQL_FN_NUM_LOG10 As Long = &H80000
Global Const SQL_FN_NUM_POWER As Long = &H100000
Global Const SQL_FN_NUM_RADIANS As Long = &H200000
Global Const SQL_FN_NUM_ROUND As Long = &H400000
Global Const SQL_FN_NUM_TRUNCATE As Long = &H800000


' Time/date functions
'
Global Const SQL_FN_TD_NOW As Long = &H1&
Global Const SQL_FN_TD_CURDATE As Long = &H2&
Global Const SQL_FN_TD_DAYOFMONTH As Long = &H4&
Global Const SQL_FN_TD_DAYOFWEEK As Long = &H8&
Global Const SQL_FN_TD_DAYOFYEAR As Long = &H10&
Global Const SQL_FN_TD_MONTH As Long = &H20&
Global Const SQL_FN_TD_QUARTER As Long = &H40&
Global Const SQL_FN_TD_WEEK As Long = &H80&
Global Const SQL_FN_TD_YEAR As Long = &H100&
Global Const SQL_FN_TD_CURTIME As Long = &H200&
Global Const SQL_FN_TD_HOUR As Long = &H400&
Global Const SQL_FN_TD_MINUTE As Long = &H800&
Global Const SQL_FN_TD_SECOND As Long = &H1000&
'
Global Const SQL_FN_TD_TIMESTAMPADD As Long = &H2000&
Global Const SQL_FN_TD_TIMESTAMPDIFF As Long = &H4000&
Global Const SQL_FN_TD_DAYNAME As Long = &H8000&
Global Const SQL_FN_TD_MONTHNAME As Long = &H10000


' System functions
'
Global Const SQL_FN_SYS_USERNAME As Long = &H1&
Global Const SQL_FN_SYS_DBNAME As Long = &H2&
Global Const SQL_FN_SYS_IFNULL As Long = &H4&

' Timedate intervals
'
'
Global Const SQL_FN_TSI_FRAC_SECOND As Long = &H1&
Global Const SQL_FN_TSI_SECOND As Long = &H2&
Global Const SQL_FN_TSI_MINUTE As Long = &H4&
Global Const SQL_FN_TSI_HOUR As Long = &H8&
Global Const SQL_FN_TSI_DAY As Long = &H10&
Global Const SQL_FN_TSI_WEEK As Long = &H20&
Global Const SQL_FN_TSI_MONTH As Long = &H40&
Global Const SQL_FN_TSI_QUARTER As Long = &H80&
Global Const SQL_FN_TSI_YEAR As Long = &H100&


' ODBC API conformance
'
Global Const SQL_OAC_NONE As Long = 0
Global Const SQL_OAC_LEVEL1 As Long = 1
Global Const SQL_OAC_LEVEL2 As Long = 2

' SAG CLI conformance
'
Global Const SQL_OSCC_NOT_COMPLIANT As Long = 0
Global Const SQL_OSCC_COMPLIANT As Long = 1

' ODBC SQL conformance
'
Global Const SQL_OSC_MINIMUM As Long = 0
Global Const SQL_OSC_CORE As Long = 1
Global Const SQL_OSC_EXTENDED As Long = 2

' Concatenation behavior
'
Global Const SQL_CB_NULL As Long = 0
Global Const SQL_CB_NON_NULL As Long = 1

' Cursor commit behavior
'
Global Const SQL_CB_DELETE As Long = 0
Global Const SQL_CB_CLOSE As Long = 1
Global Const SQL_CB_PRESERVE As Long = 2

' Identifier case
'
Global Const SQL_IC_UPPER As Long = 1
Global Const SQL_IC_LOWER As Long = 2
Global Const SQL_IC_SENSITIVE As Long = 3
Global Const SQL_IC_MIXED As Long = 4

' Transaction capable
'
Global Const SQL_TC_NONE As Long = 0
Global Const SQL_TC_DML As Long = 1
Global Const SQL_TC_ALL As Long = 2
'
Global Const SQL_TC_DDL_COMMIT As Long = 3
Global Const SQL_TC_DDL_IGNORE As Long = 4


' Scroll option masks
'
Global Const SQL_SO_FORWARD_ONLY As Long = &H1&
Global Const SQL_SO_KEYSET_DRIVEN As Long = &H2&
Global Const SQL_SO_DYNAMIC As Long = &H4&
Global Const SQL_SO_MIXED As Long = &H8&
'
Global Const SQL_SO_STATIC As Long = &H10&


' Scroll concurrency option masks
'
Global Const SQL_SCCO_READ_ONLY As Long = &H1&
Global Const SQL_SCCO_LOCK As Long = &H2&
Global Const SQL_SCCO_OPT_ROWVER As Long = &H4&
Global Const SQL_SCCO_OPT_VALUES As Long = &H8&

' Fetch direction option masks
'
Global Const SQL_FD_FETCH_NEXT As Long = &H1&
Global Const SQL_FD_FETCH_FIRST As Long = &H2&
Global Const SQL_FD_FETCH_LAST As Long = &H4&
Global Const SQL_FD_FETCH_PRIOR As Long = &H8&
Global Const SQL_FD_FETCH_ABSOLUTE As Long = &H10&
Global Const SQL_FD_FETCH_RELATIVE As Long = &H20&
Global Const SQL_FD_FETCH_RESUME As Long = &H40&
'
Global Const SQL_FD_FETCH_BOOKMARK As Long = &H80&


' Transaction isolation option masks
'
Global Const SQL_TXN_READ_UNCOMMITTED As Long = &H1&
Global Const SQL_TXN_READ_COMMITTED As Long = &H2&
Global Const SQL_TXN_REPEATABLE_READ As Long = &H4&
Global Const SQL_TXN_SERIALIZABLE As Long = &H8&
Global Const SQL_TXN_VERSIONING As Long = &H10&

' Correlation name
'
Global Const SQL_CN_NONE As Long = 0
Global Const SQL_CN_DIFFERENT As Long = 1
Global Const SQL_CN_ANY As Long = 2

' Non-nullable columns
'
Global Const SQL_NNC_NULL As Long = 0
Global Const SQL_NNC_NON_NULL As Long = 1

'
' Null collation
'
Global Const SQL_NC_HIGH As Long = 0
Global Const SQL_NC_LOW As Long = 1
Global Const SQL_NC_START As Long = 2
Global Const SQL_NC_END As Long = 4

' File usage
'
Global Const SQL_FILE_NOT_SUPPORTED As Long = 0
Global Const SQL_FILE_TABLE As Long = 1
Global Const SQL_FILE_QUALIFIER As Long = 2

' SQLGetData extensions masks
'
Global Const SQL_GD_ANY_COLUMN As Long = &H1&
Global Const SQL_GD_ANY_ORDER As Long = &H2&
Global Const SQL_GD_BLOCK As Long = &H4&
Global Const SQL_GD_BOUND As Long = &H8&

' Alter table
'
Global Const SQL_AT_ADD_COLUMN As Long = 1
Global Const SQL_AT_DROP_COLUMN As Long = 2

' Positioned statements masks
'
Global Const SQL_PS_POSITIONED_DELETE As Long = &H1&
Global Const SQL_PS_POSITIONED_UPDATE As Long = &H2&
Global Const SQL_PS_SELECT_FOR_UPDATE As Long = &H4&

' Group By
'
Global Const SQL_GB_NOT_SUPPORTED As Long = 0
Global Const SQL_GB_GROUP_BY_EQUALS_SELECT As Long = 1
Global Const SQL_GB_GROUP_BY_CONTAINS_SELECT As Long = 2
Global Const SQL_GB_NO_RELATION As Long = 3

' Owner usage masks
'
Global Const SQL_OU_DML_STATEMENTS As Long = &H1&
Global Const SQL_OU_PROCEDURE_INVOCATION As Long = &H2&
Global Const SQL_OU_TABLE_DEFINITION As Long = &H4&
Global Const SQL_OU_INDEX_DEFINITION As Long = &H8&
Global Const SQL_OU_PRIVILEGE_DEFINITION As Long = &H10&

' Qualifier usage masks
'
Global Const SQL_QU_DML_STATEMENTS As Long = &H1&
Global Const SQL_QU_PROCEDURE_INVOCATION As Long = &H2&
Global Const SQL_QU_TABLE_DEFINITION As Long = &H4&
Global Const SQL_QU_INDEX_DEFINITION As Long = &H8&
Global Const SQL_QU_PRIVILEGE_DEFINITION As Long = &H10&

' Subqueries masks
'
Global Const SQL_SQ_COMPARISON As Long = &H1&
Global Const SQL_SQ_EXISTS As Long = &H2&
Global Const SQL_SQ_IN As Long = &H4&
Global Const SQL_SQ_QUANTIFIED As Long = &H8&
Global Const SQL_SQ_CORRELATED_SUBQUERIES As Long = &H10&

' Union masks
'
Global Const SQL_U_UNION As Long = &H1&
Global Const SQL_U_UNION_ALL As Long = &H2&

' Bookmark persistence
'
Global Const SQL_BP_CLOSE As Long = &H1&
Global Const SQL_BP_DELETE As Long = &H2&
Global Const SQL_BP_DROP As Long = &H4&
Global Const SQL_BP_TRANSACTION As Long = &H8&
Global Const SQL_BP_UPDATE As Long = &H10&
Global Const SQL_BP_OTHER_HSTMT As Long = &H20&
Global Const SQL_BP_SCROLL As Long = &H40&

' Static sensitivity
'
Global Const SQL_SS_ADDITIONS As Long = &H1&
Global Const SQL_SS_DELETIONS As Long = &H2&
Global Const SQL_SS_UPDATES As Long = &H4&

' Lock types masks
'
Global Const SQL_LCK_NO_CHANGE As Long = &H1&
Global Const SQL_LCK_EXCLUSIVE As Long = &H2&
Global Const SQL_LCK_UNLOCK As Long = &H4&

' Positioned operations masks
'
Global Const SQL_POS_POSITION As Long = &H1&
Global Const SQL_POS_REFRESH As Long = &H2&
Global Const SQL_POS_UPDATE As Long = &H4&
Global Const SQL_POS_DELETE As Long = &H8&
Global Const SQL_POS_ADD As Long = &H10&

' Qualifier location
'
Global Const SQL_QL_START As Long = 1
Global Const SQL_QL_END As Long = 2



' Options for SQLGetStmtOption/SQLSetStmtOption
'
Global Const SQL_QUERY_TIMEOUT As Long = 0
Global Const SQL_MAX_ROWS As Long = 1
Global Const SQL_NOSCAN As Long = 2
Global Const SQL_MAX_LENGTH As Long = 3
Global Const SQL_ASYNC_ENABLE As Long = 4
Global Const SQL_BIND_TYPE As Long = 5
Global Const SQL_CURSOR_TYPE As Long = 6
Global Const SQL_CONCURRENCY As Long = 7
Global Const SQL_KEYSET_SIZE As Long = 8
Global Const SQL_ROWSET_SIZE As Long = 9
Global Const SQL_SIMULATE_CURSOR As Long = 10
Global Const SQL_RETRIEVE_DATA As Long = 11
Global Const SQL_USE_BOOKMARKS As Long = 12
Global Const SQL_GET_BOOKMARK As Long = 13
Global Const SQL_ROW_NUMBER As Long = 14

Global Const SQL_STMT_OPT_MAX As Long = SQL_ROW_NUMBER

' Statement option values & defaults
'
Global Const SQL_QUERY_TIMEOUT_DEFAULT As Long = 0
Global Const SQL_MAX_ROWS_DEFAULT As Long = 0

Global Const SQL_NOSCAN_OFF As Long = 0
Global Const SQL_NOSCAN_ON As Long = 1
Global Const SQL_NOSCAN_DEFAULT As Long = SQL_NOSCAN_OFF

Global Const SQL_MAX_LENGTH_DEFAULT As Long = 0

Global Const SQL_ASYNC_ENABLE_OFF As Long = 0
Global Const SQL_ASYNC_ENABLE_ON As Long = 1
Global Const SQL_ASYNC_ENABLE_DEFAULT As Long = SQL_ASYNC_ENABLE_OFF

Global Const SQL_BIND_BY_COLUMN As Long = 0

Global Const SQL_CONCUR_READ_ONLY As Long = 1
Global Const SQL_CONCUR_LOCK As Long = 2
Global Const SQL_CONCUR_ROWVER As Long = 3
Global Const SQL_CONCUR_VALUES As Long = 4
Global Const SQL_CURSOR_FORWARD_ONLY As Long = 0
Global Const SQL_CURSOR_KEYSET_DRIVEN As Long = 1
Global Const SQL_CURSOR_DYNAMIC As Long = 2
Global Const SQL_CURSOR_STATIC As Long = 3

Global Const SQL_ROWSET_SIZE_DEFAULT As Long = 1

Global Const SQL_KEYSET_SIZE_DEFAULT As Long = 0

Global Const SQL_SC_NON_UNIQUE As Long = 0
Global Const SQL_SC_TRY_UNIQUE As Long = 1
Global Const SQL_SC_UNIQUE As Long = 2

Global Const SQL_RD_OFF As Long = 0
Global Const SQL_RD_ON As Long = 1
Global Const SQL_RD_DEFAULT As Long = SQL_RD_ON

Global Const SQL_UB_OFF As Long = 0
Global Const SQL_UB_ON As Long = 1
Global Const SQL_UB_DEFAULT As Long = SQL_UB_ON


' Options for SQLSetConnectOption/SQLGetConnectOption
'
Global Const SQL_ACCESS_MODE As Long = 101
Global Const SQL_AUTOCOMMIT As Long = 102
Global Const SQL_LOGIN_TIMEOUT As Long = 103
Global Const SQL_OPT_TRACE As Long = 104
Global Const SQL_OPT_TRACEFILE As Long = 105
Global Const SQL_TRANSLATE_DLL As Long = 106
Global Const SQL_TRANSLATE_OPTION As Long = 107
Global Const SQL_TXN_ISOLATION As Long = 108
Global Const SQL_CURRENT_QUALIFIER As Long = 109
Global Const SQL_CONNECT_OPT_DRVR_START As Long = 1000
'
Global Const SQL_ODBC_CURSORS As Long = 110
Global Const SQL_QUIET_MODE As Long = 111
Global Const SQL_PACKET_SIZE As Long = 112

Global Const SQL_CONN_OPT_MAX As Long = SQL_PACKET_SIZE

Global Const SQL_CONN_OPT_MIN As Long = SQL_ACCESS_MODE

' Access mode options
'
Global Const SQL_MODE_READ_WRITE As Long = 0
Global Const SQL_MODE_READ_ONLY As Long = 1
Global Const SQL_MODE_DEFAULT As Long = SQL_MODE_READ_WRITE

' Autocommit options
'
Global Const SQL_AUTOCOMMIT_OFF As Long = 0
Global Const SQL_AUTOCOMMIT_ON As Long = 1
Global Const SQL_AUTOCOMMIT_DEFAULT As Long = SQL_AUTOCOMMIT_ON

' Login timeout options
'
Global Const SQL_LOGIN_TIMEOUT_DEFAULT As Long = 15

' Trace options
'
Global Const SQL_OPT_TRACE_OFF As Long = 0
Global Const SQL_OPT_TRACE_ON As Long = 1
Global Const SQL_OPT_TRACE_DEFAULT As Long = SQL_OPT_TRACE_OFF
Global Const SQL_OPT_TRACE_FILE_DEFAULT = "\\SQL.LOG"

'
' Cursor options
'
Global Const SQL_CUR_USE_IF_NEEDED As Long = 0
Global Const SQL_CUR_USE_ODBC As Long = 1
Global Const SQL_CUR_USE_DRIVER As Long = 2
Global Const SQL_CUR_DEFAULT As Long = SQL_CUR_USE_DRIVER


' Column types and scopes in SQLSpecialColumns.
'
Global Const SQL_BEST_ROWID As Long = 1
Global Const SQL_ROWVER As Long = 2

Global Const SQL_SCOPE_CURROW As Long = 0
Global Const SQL_SCOPE_TRANSACTION As Long = 1
Global Const SQL_SCOPE_SESSION As Long = 2

' Level 2 Functions
'
' SQLExtendedFetch "fFetchType" values
'
Global Const SQL_FETCH_NEXT As Long = 1
Global Const SQL_FETCH_FIRST As Long = 2
Global Const SQL_FETCH_LAST As Long = 3
Global Const SQL_FETCH_PRIOR As Long = 4
Global Const SQL_FETCH_ABSOLUTE As Long = 5
Global Const SQL_FETCH_RELATIVE As Long = 6
Global Const SQL_FETCH_BOOKMARK As Long = 8


' SQLExtendedFetch "rgfRowStatus" element values
'
Global Const SQL_ROW_SUCCESS As Long = 0
Global Const SQL_ROW_DELETED As Long = 1
Global Const SQL_ROW_UPDATED As Long = 2
Global Const SQL_ROW_NOROW As Long = 3
'
Global Const SQL_ROW_ADDED As Long = 4
Global Const SQL_ROW_ERROR As Long = 5


' Defines for SQLForeignKeys (returned in result set)
'
Global Const SQL_CASCADE As Long = 0
Global Const SQL_RESTRICT As Long = 1
Global Const SQL_SET_NULL As Long = 2

' Defines for SQLProcedureColumns (returned in the result set)
'
Global Const SQL_PARAM_TYPE_UNKNOWN As Long = 0
Global Const SQL_PARAM_INPUT As Long = 1
Global Const SQL_PARAM_INPUT_OUTPUT As Long = 2
Global Const SQL_RESULT_COL As Long = 3
'
Global Const SQL_PARAM_OUTPUT As Long = 4


' Defines for SQLStatistics
'
Global Const SQL_INDEX_UNIQUE As Long = 0
Global Const SQL_INDEX_ALL As Long = 1
Global Const SQL_ENSURE As Long = 1
Global Const SQL_QUICK As Long = 0

' Defines for SQLStatistics (returned in the result set)
'
Global Const SQL_TABLE_STAT As Long = 0
Global Const SQL_INDEX_CLUSTERED As Long = 1
Global Const SQL_INDEX_HASHED As Long = 2
Global Const SQL_INDEX_OTHER As Long = 3

'
' Procedures
'
Global Const SQL_PT_UNKNOWN As Long = 0
Global Const SQL_PT_PROCEDURE As Long = 1
Global Const SQL_PT_FUNCTION As Long = 2

' Procedure columns
'
Global Const SQL_PC_UNKNOWN As Long = 0
Global Const SQL_PC_NON_PSEUDO As Long = 1
Global Const SQL_PC_PSEUDO As Long = 2


' Defines for SQLSetPos
'
Global Const SQL_ENTIRE_ROWSET As Long = 0

Global Const SQL_POSITION As Long = 0
Global Const SQL_REFRESH As Long = 1
Global Const SQL_UPDATE As Long = 2
Global Const SQL_DELETE As Long = 3
Global Const SQL_ADD As Long = 4


' Lock options
'
Global Const SQL_LOCK_NO_CHANGE As Long = 0
Global Const SQL_LOCK_EXCLUSIVE As Long = 1
Global Const SQL_LOCK_UNLOCK As Long = 2


' Deprecated global constants
'
Global Const SQL_DATABASE_NAME As Long = 16
Global Const SQL_FD_FETCH_PREV As Long = SQL_FD_FETCH_PRIOR
Global Const SQL_FETCH_PREV As Long = SQL_FETCH_PRIOR
Global Const SQL_CONCUR_TIMESTAMP As Long = SQL_CONCUR_ROWVER
Global Const SQL_SCCO_OPT_TIMESTAMP As Long = SQL_SCCO_OPT_ROWVER
Global Const SQL_CC_DELETE As Long = SQL_CB_DELETE
Global Const SQL_CR_DELETE As Long = SQL_CB_DELETE
Global Const SQL_CC_CLOSE As Long = SQL_CB_CLOSE
Global Const SQL_CR_CLOSE As Long = SQL_CB_CLOSE
Global Const SQL_CC_PRESERVE As Long = SQL_CB_PRESERVE
Global Const SQL_CR_PRESERVE As Long = SQL_CB_PRESERVE
Global Const SQL_FETCH_RESUME As Long = 7
Global Const SQL_SCROLL_FORWARD_ONLY As Long = 0
Global Const SQL_SCROLL_KEYSET_DRIVEN As Long = -1
Global Const SQL_SCROLL_DYNAMIC As Long = -2
Global Const SQL_SCROLL_STATIC As Long = -3

#End If 'Win32



