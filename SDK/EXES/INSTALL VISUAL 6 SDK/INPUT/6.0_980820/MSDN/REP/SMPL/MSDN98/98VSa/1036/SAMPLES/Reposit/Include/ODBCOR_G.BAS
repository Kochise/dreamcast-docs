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
Global Const SQL_COLATT_OPT_MAX = SQL_COLUMN_LABEL

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

