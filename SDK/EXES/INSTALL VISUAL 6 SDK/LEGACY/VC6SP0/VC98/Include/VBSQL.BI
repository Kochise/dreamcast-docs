Rem Global declarations for Visual Basic to DB-Library translation dll.
Rem Used by all apps linking with the VBSQL DLL (vbsql.vbx)

Rem Global return values for all RETCODE type functions
Global Const SUCCEED% = 1
Global Const FAIL% = 0

Rem return values permitted in error handlers
Global Const INTEXIT% = 0
Global Const INTCONTINUE% = 1
Global Const INTCANCEL% = 2

Global Const MOREROWS = -1
Global Const NOMOREROWS = -2
Global Const REGROW = -1
Global Const BUFFULL = -3

Rem Status code for dbresults(). Possible return values are
Rem SUCCEED, FAIL, and NO_MORE_RESULTS.

Global Const NOMORERESULTS = 2
Global Const NOMORERPCRESULTS = 3


Rem versions for SQLSetLVersion

Global Const SQLVER42% = 8
Global Const SQLVER60% = 9



Rem option values permitted in option setting/querying/clearing
Rem used by SqlSetOpt%(), SqlIsOpt%(), and SqlClrOpt%().

Global Const SQLBUFFER% = 0
Global Const SQLOFFSET% = 1
Global Const SQLROWCOUNT% = 2
Global Const SQLSTAT% = 3
Global Const SQLTEXTLIMIT% = 4
Global Const SQLTEXTSIZE% = 5
Global Const SQLARITHABORT% = 6
Global Const SQLARITHIGNORE% = 7
Global Const SQLNOAUTOFREE% = 8
Global Const SQLNOCOUNT% = 9
Global Const SQLNOEXEC% = 10
Global Const SQLPARSEONLY% = 11
Global Const SQLSHOWPLAN% = 12
Global Const SQLSTORPROCID% = 13
Global Const SQLANSItoOEM% = 14
Global Const SQLCLIENTCURSORS% = 16

Rem Data type token values.  Used for datatype determination for a column.

Global Const SQLTEXT% = &H23
Global Const SQLARRAY% = &H24
Global Const SQLVARBINARY% = &H25
Global Const SQLINTN% = &H26
Global Const SQLVARCHAR% = &H27
Global Const SQLBINARY% = &H2D
Global Const SQLIMAGE% = &H22
Global Const SQLCHAR% = &H2F
Global Const SQLINT1% = &H30
Global Const SQLBIT% = &H32
Global Const SQLINT2% = &H34
Global Const SQLINT4% = &H38
Global Const SQLMONEY% = &H3C
Global Const SQLDATETIME% = &H3D
Global Const SQLFLT8% = &H3E
Global Const SQLFLTN% = &H6D
Global Const SQLFLT4% = &H3B
Global Const SQLMONEYN% = &H6E
Global Const SQLDATETIMN% = &H6F
Global Const SQLAOPCNT% = &H4B
Global Const SQLAOPSUM% = &H4D
Global Const SQLAOPAVG% = &H4F
Global Const SQLAOPMIN% = &H51
Global Const SQLAOPMAX% = &H52
Global Const SQLAOPANY% = &H53
Global Const SQLAOPNOOP% = &H56
Global Const SQLMONEY4% = &H7A
Global Const SQLDATETIM4% = &H3A
Global Const SQLDECIMAL% = &H6A
Global Const SQLNUMERIC = &H6C



Rem error numbers VBSQL error codes that are passed to local error
Rem handler

Global Const SQLEMEM% = 10000
Global Const SQLENULL% = 10001
Global Const SQLENLOG% = 10002
Global Const SQLEPWD% = 10003
Global Const SQLECONN% = 10004
Global Const SQLEDDNE% = 10005
Global Const SQLNULLO% = 10006
Global Const SQLESMSG% = 10007
Global Const SQLEBTOK% = 10008
Global Const SQLENSPE% = 10009
Global Const SQLEREAD% = 10010
Global Const SQLECNOR% = 10011
Global Const SQLETSIT% = 10012
Global Const SQLEPARM% = 10013
Global Const SQLEAUTN% = 10014
Global Const SQLECOFL% = 10015
Global Const SQLERDCN% = 10016
Global Const SQLEICN% = 10017
Global Const SQLECLOS% = 10018
Global Const SQLENTXT% = 10019
Global Const SQLEDNTI% = 10020
Global Const SQLETMTD% = 10021
Global Const SQLEASEC% = 10022
Global Const SQLENTLL% = 10023
Global Const SQLETIME% = 10024
Global Const SQLEWRIT% = 10025
Global Const SQLEMODE% = 10026
Global Const SQLEOOB% = 10027
Global Const SQLEITIM% = 10028
Global Const SQLEDBPS% = 10029
Global Const SQLEIOPT% = 10030
Global Const SQLEASNL% = 10031
Global Const SQLEASUL% = 10032
Global Const SQLENPRM% = 10033
Global Const SQLEDBOP% = 10034
Global Const SQLENSIP% = 10035
Global Const SQLECNULL% = 10036
Global Const SQLESEOF% = 10037
Global Const SQLERPND% = 10038
Global Const SQLECSYN% = 10039
Global Const SQLENONET% = 10040
Global Const SQLEBTYP% = 10041
Global Const SQLEABNC% = 10042
Global Const SQLEABMT% = 10043
Global Const SQLEABNP% = 10044
Global Const SQLEBNCR% = 10045
Global Const SQLEAAMT% = 10046
Global Const SQLENXID% = 10047
Global Const SQLEIFNB% = 10048
Global Const SQLEKBCO% = 10049
Global Const SQLEBBCI% = 10050
Global Const SQLEKBCI% = 10051
Global Const SQLEBCWE% = 10052
Global Const SQLEBCNN% = 10053
Global Const SQLEBCOR% = 10054
Global Const SQLEBCPI% = 10055
Global Const SQLEBCPN% = 10056
Global Const SQLEBCPB% = 10057
Global Const SQLEVDPT% = 10058
Global Const SQLEBIVI% = 10059
Global Const SQLEBCBC% = 10060
Global Const SQLEBCFO% = 10061
Global Const SQLEBCVH% = 10062
Global Const SQLEBCUO% = 10063
Global Const SQLEBUOE% = 10064
Global Const SQLEBWEF% = 10065
Global Const SQLEBTMT% = 10066
Global Const SQLEBEOF% = 10067
Global Const SQLEBCSI% = 10068
Global Const SQLEPNUL% = 10069
Global Const SQLEBSKERR% = 10070
Global Const SQLEBDIO% = 10071
Global Const SQLEBCNT% = 10072
Global Const SQLEMDBP% = 10073
Global Const SQLEINIT% = 10074
Global Const SQLCRSINV% = 10075
Global Const SQLCRSCMD% = 10076
Global Const SQLCRSNOIND% = 10077
Global Const SQLCRSDIS% = 10078
Global Const SQLCRSAGR% = 10079
Global Const SQLCRSORD% = 10080
Global Const SQLCRSMEM% = 10081
Global Const SQLCRSBSKEY% = 10082
Global Const SQLCRSNORES% = 10083
Global Const SQLCRSVIEW% = 10084
Global Const SQLCRSBUFR% = 10085
Global Const SQLCRSFROWN% = 10086
Global Const SQLCRSBROL% = 10087
Global Const SQLCRSFRAND% = 10088
Global Const SQLCRSFLAST% = 10089
Global Const SQLCRSRO% = 10090
Global Const SQLCRSTAB% = 10091
Global Const SQLCRSUPDTAB% = 10092
Global Const SQLCRSUPDNB% = 10093
Global Const SQLCRSVIIND% = 10094
Global Const SQLCRSNOUPD% = 10095
Global Const SQLCRSOS2% = 10096
Global Const SQLEBCSA% = 10097
Global Const SQLEBCRO% = 10098
Global Const SQLEBCNE% = 10099
Global Const SQLEBCSK% = 10100
Global Const SQLEUVBF% = 10101
Global Const SQLEBIHC% = 10102
Global Const SQLEBWFF% = 10103

Rem The severity levels are defined here for error handlers

Global Const EXINFO% = 1
Global Const EXUSER% = 2
Global Const EXNONFATAL% = 3
Global Const EXCONVERSION% = 4
Global Const EXSERVER% = 5
Global Const EXTIME% = 6
Global Const EXPROGRAM% = 7
Global Const EXRESOURCE% = 8
Global Const EXCOMM% = 9
Global Const EXFATAL% = 10
Global Const EXCONSISTENCY% = 11

Rem Length of text timestamp and text pointer
Global Const SQLTXTSLEN% = 8          ' length of text timestamp
Global Const SQLTXPLEN% = 16          ' length of text pointer

Global Const OFF_SELECT% = &H16D
Global Const OFF_FROM% = &H14F
Global Const OFF_ORDER% = &H165
Global Const OFF_COMPUTE% = &H139
Global Const OFF_TABLE% = &H173
Global Const OFF_PROCEDURE% = &H16A
Global Const OFF_STATEMENT% = &H1CB
Global Const OFF_PARAM% = &H1C4
Global Const OFF_EXEC% = &H12C

Rem Bulk Copy Definitions (bcp)

Global Const DBIN% = 1              ' transfer from client to server
Global Const DBOUT% = 2            ' transfer from server to client

Global Const BCPMAXERRS% = 1        ' SqlBcpControl parameter
Global Const BCPFIRST% = 2          ' SqlBcpControl parameter
Global Const BCPLAST% = 3           ' SqlBcpControl parameter
Global Const BCPBATCH% = 4          ' SqlBcpControl parameter
Global Const BCPKEEPNULLS% = 5      ' SqlBcpControl parameter

Rem Cursor related constants

Rem Following flags are used in the concuropt parameter in the
Rem SqlCursorOpen function

Global Const CURREADONLY% = 1   ' Read only cursor, no data modifications
Global Const CURLOCKCC% = 2     ' Intent to update, all fetched data locked
				' when dbcursorfetch is called inside a
				' transaction block
Global Const CUROPTCC% = 3      ' Optimistic concurrency control, data
				' modifications succeed only if the row
				' hasn't been updated since the last fetch
Global Const CUROPTCCVAL% = 4   ' Optimistic concurrency control based on
				' selected column values

Rem Following flags are used in the scrollopt parameter in the
Rem SqlCursorOpen function

Global Const CURFORWARD% = 0   ' Forward only scrolling
Global Const CURKEYSET% = -1   ' Keyset driven scrolling
Global Const CURDYNAMIC% = 1   ' Fully dynamic
Global Const CURINSENSITIVE% = -2  ' Server-side cursors only

Rem Any other number indicates mixed scrolling. (Keyset driven within the given
Rem number, dynamic outside)

Rem Following flags define the fetchtype in the SqlCursorFetch function

Global Const FETCHFIRST% = 1    ' Fetch first n rows
Global Const FETCHNEXT% = 2     ' Fetch next n rows
Global Const FETCHPREV% = 3     ' Fetch previous n rows
Global Const FETCHRANDOM% = 4   ' Fetch n rows beginning with given row#
Global Const FETCHRELATIVE% = 5 ' Fetch relative to previous fetch row #
Global Const FETCHLAST% = 6     ' Fetch the last n rows

Rem Following flags define the per row status as filled by SqlCursorFetch

Global Const FTCEMPTY% = &H0    ' No row available
Global Const FTCSUCCEED% = &H1  ' Fetch succeeded, (failed if not set)
Global Const FTCMISSING% = &H2  ' The row is missing
Global Const FTCENDOFKEYSET% = &H4' End of the keyset reached
Global Const FTCENDOFRESULTS% = &H8 ' End of results set reached

Rem Following flags define the operator types for the SqlCursor function

Global Const CRSUPDATE% = 1     ' Update operation
Global Const CRSDELETE% = 2     ' Delete operation
Global Const CRSINSERT% = 3     ' Insert operation
Global Const CRSREFRESH% = 4    ' Refetch given row
Global Const CRSLOCKCC% = 5     ' Lock given row (if only inside a transaction)

Rem Following define row information type requested from SqlColInfo
Global Const SQLCI_REGULAR% = 1         ' regular row
Global Const SQLCI_ALTERNATE% = 2       ' compute row
Global Const SQLCI_CURSOR% = 3          ' cursor row

Rem Following are values returned to ColInfo Usertype Type field for Cursors
Global Const CU_CLIENT& = &H1
Global Const CU_SERVER& = &H2
Global Const CU_KEYSET& = &H4
Global Const CU_MIXED& = &H8
Global Const CU_DYNAMIC& = &H10
Global Const CU_FORWARD& = &H20
Global Const CU_INSENSITIVE& = &H40
Global Const CU_READONLY& = &H80
Global Const CU_LOCKCC& = &H100
Global Const CU_OPTCC& = &H200
Global Const CU_OPTCCVAL& = &H400

Rem  Following are values returned to ColInfo Usertype Status field forCursors
Global Const CU_FILLING = &H1
Global Const CU_FILLED = &H2


Rem Remote Procedure Call function options
Global Const SQLRPCRECOMPILE% = &H1 ' recompile the stored procedure
Global Const SQLRPCRESET% = &H4     ' reset rpc processing
Global Const SQLRPCRETURN% = 1      ' return parameter

Rem The following values are passed to SqlServerEnum for searching criteria.
Global Const NETSEARCH% = 1
Global Const LOCSEARCH% = 2


Rem These constants are the possible return values from SqlServerEnum.
Global Const ENUMSUCCESS% = 0
Global Const MOREDATA% = 1
Global Const NETNOTAVAIL% = 2
Global Const OUTOFMEMORY% = 4
Global Const NOTSUPPORTED% = 8

Rem These constants are passed to SqlUpdateText for setting update type
Global Const UTTEXTPTR% = &H1
Global Const UTTEXT% = &H2
Global Const UTMORETEXT% = &H4
Global Const UTDELETEONLY% = &H8
Global Const UTLOG% = &H10


Rem These constants are used by SqlProcInfo
Global Const SERVTYPEUNKNOWN% = 0
Global Const SERVTYPEMICROSOFT% = 1


Rem State unknown in SqlColInfo
Global Const SQLUNKNOWN% = 2

Rem User defined data type for SqlGetColumnInfo
Type ColumnData
   Coltype As Integer
   Collen As Long
   Colname As String * 31
   ColSqlType As String * 31
End Type

Rem User defined data type for SqlGetAltColInfo
Type AltColumnData
   ColID As Integer
   DataType As Integer
   MaxLen As Long
   AggType As Integer
   AggOpName As String * 31
End Type

Rem User defined data type for SqlBcpColumnFormat
Type BcpColData
    FType As Integer
    FPLen As Integer
    fColLen As Long
    FTerm As String * 31
    FTLen As Integer
    TCol As Integer
End Type

Rem User defined data type for SqlDateCrack
Type DateInfo
    Year As Integer
    Quarter As Integer
    Month As Integer
    DayOfYear As Integer
    Day As Integer
    Week As Integer
    WeekDay As Integer
    Hour As Integer
    Minute As Integer
    Second As Integer
    Millisecond As Integer
End Type

Rem User defined data type for SqlColInfo
Type ColInfo
    Name As String * 31
    ActualName As String * 31
    TableName As String * 31
    CType As Integer
    UserType As Long
    MaxLength As Long
    Precision As Integer
    Scale As Integer
    VarLength As Integer
    Null As Integer
    CaseSensitive As Integer
    Updatable As Integer
    Identity As Integer
End Type

Type ProcInfo
    ServerType As Integer
    ServerMajor As Integer
    ServerMinor As Integer
    ServerRevision As Integer
    ServerName As String * 31
    NetLibName As String * 31
    NetLibConnStr As String * 256
End Type

Type SqlCursorInfo
    TotCols As Long
    TotRows As Long
    CurRow As Long
    TotRowsFetched As Long
    CursorType As Long
    Status As Long
End Type


Rem Function/Sub declarations for Visual Basic App Global module
Declare Function SqlInit Lib "VBSQL.VBX" () As String
Declare Sub SqlWinExit Lib "VBSQL.VBX" ()
Declare Function SqlLogin Lib "VBSQL.VBX" () As Integer
Declare Function SQLSETLUSER Lib "VBSQL.VBX" (ByVal Login As Integer, User As String) As Integer
Declare Function SqlSetLPwd Lib "VBSQL.VBX" (ByVal Login As Integer, Pwd As String) As Integer
Declare Function SqlSetLApp Lib "VBSQL.VBX" (ByVal Login As Integer, App As String) As Integer
Declare Function SqlSetLHost Lib "VBSQL.VBX" (ByVal Login As Integer, Host As String) As Integer
Declare Function SqlSetLNatLang Lib "VBSQL.VBX" (ByVal Login As Integer, Lang As String) As Integer
Declare Function SqlSetLSecure Lib "VBSQL.VBX" (ByVal Login As Integer) As Integer
Declare Function SQLSETLVERSION Lib "VBSQL.VBX" (ByVal Login As Integer, ByVal Version As Integer) As Integer
Declare Function SqlOpen Lib "VBSQL.VBX" (ByVal Login As Integer, Server As String) As Integer
Declare Sub SqlClose Lib "VBSQL.VBX" (ByVal SqlConn As Integer)
Declare Sub SqlFreeLogin Lib "VBSQL.VBX" (ByVal Login As Integer)
Declare Function SqlCmd Lib "VBSQL.VBX" (ByVal SqlConn As Integer, Cmd As String) As Integer
Declare Function SqlExec Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlResults Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlNextRow Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlNumCols Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlColName Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Column As Integer) As String
Declare Function SqlColType Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Column As Integer) As Integer
Declare Function SqlColUType Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Column As Integer) As Long
Declare Function SqlColLen Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Column As Integer) As Integer
Declare Function SqlDatLen Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Column As Integer) As Long
Declare Function SqlData Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Column As Integer) As String
Declare Function SqlColInfo Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal InfoType As Integer, ByVal Column As Integer, ByVal ComputeId As Integer, ColInf As ColInfo) As Integer
Declare Function SqlDataReady Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Sub SqlExit Lib "VBSQL.VBX" ()
Declare Function SqlSetLoginTime Lib "VBSQL.VBX" (ByVal Seconds As Integer) As Integer
Declare Function SqlSetTime Lib "VBSQL.VBX" (ByVal Seconds As Integer) As Integer
Declare Function SqlSend Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlOk Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlGetChar Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal CharNum As Integer) As String
Declare Function SqlStrCpy Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Start As Integer, ByVal NumBytes As Integer, Buffer As String) As Integer
Declare Function SqlStrLen Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlSetOpt Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Opt As Integer, Param As String) As Integer
Declare Function SqlClrOpt Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Opt As Integer, Param As String) As Integer
Declare Function SqlIsOpt Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Opt As Integer, Param As String) As Integer
Declare Sub SqlFreeBuf Lib "VBSQL.VBX" (ByVal SqlConn As Integer)
Declare Function SqlCancel Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlCanQuery Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlGetRow Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal RowNum As Long) As Integer
Declare Sub SqlClrBuf Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal RowNum As Long)
Declare Function SqlColBrowse Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Column As Integer) As Integer
Declare Function SqlColSource Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal TabNum As Integer) As String
Declare Function SqlQual Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal TabNum As Integer, TableName As String) As String
Declare Function SqlTabBrowse Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal TabNum As Integer) As Integer
Declare Function SqlTabCount Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlTabName Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal TabNum As Integer) As String
Declare Function SqlTabSource Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal ColNum As Integer, TabNum As Integer) As String
Declare Function SqlTsNewLen Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlTsNewVal Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As String
Declare Function SqlTsPut Lib "VBSQL.VBX" (ByVal SqlConn As Integer, NewTs As String, ByVal NewTsLen As Integer, ByVal TabNum As Integer, TabName As String) As Integer
Declare Function SqlMoreText Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Size As Long, Text As String) As Integer
Declare Function SqlTxPtr Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Column As Integer) As String
Declare Function SqlTxTimeStamp Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Column As Integer) As String
Declare Function SqlTxTsNewVal Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As String
Declare Function SqlTxTsPut Lib "VBSQL.VBX" (ByVal SqlConn As Integer, NewTxTs As String, ByVal Column As Integer) As Integer
Declare Function SqlWriteText Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ObjName As String, TextPtr As String, ByVal TextPtrLen As Integer, TimeStamp As String, ByVal Logging As Integer, ByVal Size As Long, Text As String) As Integer
Declare Function SqlUpdateText Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ObjName As String, TextPtr As String, TimeStamp As String, ByVal UType As Integer, ByVal Offset As Long, ByVal DelLen As Long, SrcName As String, ByVal Size As Long, Text As String) As Integer
Declare Function SqlCmdRow Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlIsCount Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlCount Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Long
Declare Function SqlCurCmd Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlCurRow Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Long
Declare Function SqlDead Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlFirstRow Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Long
Declare Function SqlGetTime Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlIsAvail Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlLastRow Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Long
Declare Function SqlMoreCmds Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlNumOrders Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlRows Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlRowType Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlNumAlts Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal ComputeId As Integer) As Integer
Declare Function SqlAltType Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal ComputeId As Integer, ByVal Column As Integer) As Integer
Declare Function SqlAltUType Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal ComputeId As Integer, ByVal Column As Integer) As Long
Declare Function SqlAltLen Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal ComputeId As Integer, ByVal Column As Integer) As Integer
Declare Function SqlADLen Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal ComputeId As Integer, ByVal Column As Integer) As Long
Declare Function SqlAData Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal ComputeId As Integer, ByVal Column As Integer) As String
Declare Function SqlAltColId Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal ComputeId As Integer, ByVal Column As Integer) As Integer
Declare Function SqlAltOp Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal ComputeId As Integer, ByVal Column As Integer) As Integer
Declare Function SqlByList Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal ComputeId As Integer) As String
Declare Function SqlNumCompute Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlUse Lib "VBSQL.VBX" (ByVal SqlConn As Integer, DataBase As String) As Integer
Declare Function SqlGetOff Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal OffType As Integer, ByVal StartFrom As Integer) As Integer
Declare Function SqlOrderCol Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Order As Integer) As Integer
Declare Function SqlChange Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As String
Declare Function SqlGetMaxProcs Lib "VBSQL.VBX" () As Integer
Declare Function SqlName Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As String
Declare Function SQLPRTYPE Lib "VBSQL.VBX" (ByVal Token As Integer) As String
Declare Sub SqlSetAvail Lib "VBSQL.VBX" (ByVal SqlConn As Integer)
Declare Function SqlSetMaxProcs Lib "VBSQL.VBX" (ByVal MaxProcs As Integer) As Integer
Declare Function SqlBCPColfmt Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal FColumn As Integer, ByVal FType As Integer, ByVal FPLen As Integer, ByVal FCLen As Long, FTerm As String, ByVal FTLen As Integer, ByVal TCol As Integer) As Integer
Declare Function SqlBCPColumns Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal ColCount As Integer) As Integer
Declare Function SqlBCPControl Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal Param As Integer, ByVal Value As Long) As Integer
Declare Function SqlBCPExec Lib "VBSQL.VBX" (ByVal SqlConn As Integer, RowsCopied As Long) As Integer
Declare Function SqlBCPInit Lib "VBSQL.VBX" (ByVal SqlConn As Integer, TblName As String, HFile As String, ErrFile As String, ByVal Direction As Integer) As Integer
Declare Function SqlBCPSetL Lib "VBSQL.VBX" (ByVal Loginrec As Integer, ByVal Enable As Integer) As Integer
Declare Function SqlBCPDone Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlSendCmd Lib "VBSQL.VBX" (ByVal SqlConn As Integer, Cmd As String) As Integer
Declare Function SqlGetColumnInfo Lib "VBSQL.VBX" (ByVal SqlConn As Integer, Col As ColumnData, ByVal Column As Integer) As Integer
Declare Function SqlGetAltColInfo Lib "VBSQL.VBX" (ByVal SqlConn As Integer, AltCol As AltColumnData, ByVal ComputeId As Integer, ByVal AltColumn As Integer) As Integer
Declare Function SqlOpenConnection Lib "VBSQL.VBX" (Server As String, LoginID As String, Pwd As String, WorkStation As String, Application As String) As Integer
Declare Function SqlTextUpdate1Row Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ObjName As String, ByVal Column As Integer, Text As String) As Integer
Declare Function SqlTextUpdateManyRows Lib "VBSQL.VBX" (ByVal QSqlConn As Integer, ByVal USqlConn As Integer, ObjName As String, ByVal Column As Integer, Text As String) As Long
Declare Function SqlBCPColumnFormat Lib "VBSQL.VBX" (ByVal SqlConn As Integer, Col As BcpColData, ByVal NumCols As Integer) As Integer
Declare Function SqlTsUpdate Lib "VBSQL.VBX" (ByVal QSqlConn As Integer, ByVal USqlConn As Integer, ByVal TabNum As Integer, TabName As String) As Integer
Declare Function SqlCursorOpen Lib "VBSQL.VBX" (ByVal SqlConn As Integer, Statement As String, ByVal ScrollOpt As Integer, ByVal ConCurOpt As Integer, ByVal nRows As Integer, PStat As Long) As Integer
Declare Function SqlCursorFetch Lib "VBSQL.VBX" (SqlCursor As Integer, ByVal FetchType As Integer, ByVal RowNum As Integer) As Integer
Declare Function SqlCursorFetchEx Lib "VBSQL.VBX" (SqlCursor As Integer, ByVal FetchType As Integer, ByVal RowNum As Long, ByVal nRows As Long, ByVal Reserved As Long) As Integer
Declare Function SqlCursorData Lib "VBSQL.VBX" (SqlCursor As Integer, ByVal BufNo As Integer, ByVal Column As Integer) As String
Declare Function SqlCursor Lib "VBSQL.VBX" (SqlCursor As Integer, ByVal OpType As Integer, ByVal BufNo As Integer, Table As String, Statement As String) As Integer
Declare Sub SqlCursorClose Lib "VBSQL.VBX" (SqlCursor As Integer)
Declare Function SqlCursorColInfo Lib "VBSQL.VBX" (SqlCursor As Integer, ByVal Column As Integer, Colname As String, Coltype As Integer, Collen As Long, UserType As Integer) As Integer
Declare Function SqlCursorInfo Lib "VBSQL.VBX" (SqlCursor As Integer, Columns As Integer, Rows As Long) As Integer
Declare Function SqlCursorInfoEx Lib "VBSQL.VBX" (SqlCursor As Integer, SqlCursInf As SqlCursorInfo) As Integer
Declare Function SqlDateCrack Lib "VBSQL.VBX" (ByVal SqlConn As Integer, SqlDateInfo As DateInfo, DateTime As String) As Integer
Declare Function SQLHasRetStat Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SQLNumRets Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SQLRetData Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal RetNum As Integer) As String
Declare Function SQLRetLen Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal RetNum As Integer) As Long
Declare Function SQLRetName Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal RetNum As Integer) As String
Declare Function SQLRetStatus Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Long
Declare Function SQLRetType Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ByVal RetNum As Integer) As Integer
Declare Function SqlRpcInit Lib "VBSQL.VBX" (ByVal SqlConn As Integer, RpcName As String, ByVal Options As Integer) As Integer
Declare Function SqlRpcParam Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ParamName As String, ByVal Status As Integer, ByVal ParamType As Integer, ByVal MaxLen As Long, ByVal DataLen As Long, Value As String) As Integer
Declare Function SqlRpcSend Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlRpcExec Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Sub SqlRPwClr Lib "VBSQL.VBX" (ByVal Login As Integer)
Declare Function SqlRPwSet Lib "VBSQL.VBX" (ByVal Login As Integer, SrvName As String, Password As String) As Integer
Declare Function SqlServerEnum Lib "VBSQL.VBX" (ByVal SearchMode As Integer, ServerBuf As String, NumEntries As Integer) As Integer
Declare Function SqlSetLPacket Lib "VBSQL.VBX" (ByVal Login As Integer, ByVal PacketSize As Integer) As Integer
Declare Function SqlGetPacket Lib "VBSQL.VBX" (ByVal SqlConn As Integer) As Integer
Declare Function SqlProcInfo Lib "VBSQL.VBX" (ByVal SqlConn As Integer, ProcInf As ProcInfo) As Integer



