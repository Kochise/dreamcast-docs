' ------------------------------------------------------------------------
' Copyright (c) 1996-1998 by Microsoft Corporation, All Rights Reserved
'
' This software is provided as is without warranty of any kind.  The entire
' risk as to the results and performance of this software is assumed by the user.
' Microsoft disclaims all warranties, either express or implied, including but
' not limited, the implied warranties of merchantability, fitness for a
' particular purpose, title and noninfringement, with respect to this software.
' ------------------------------------------------------------------------
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
' #endif ODBC 2.00


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
Global Const SQL_CURSOR_FORWARD_ONLY = 0
Global Const SQL_CURSOR_KEYSET_DRIVEN = 1
Global Const SQL_CURSOR_DYNAMIC = 2
Global Const SQL_CURSOR_STATIC = 3

Global Const SQL_ROWSET_SIZE_DEFAULT = 1

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

