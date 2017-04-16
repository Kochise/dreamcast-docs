Attribute VB_Name = "VBSQL"
Rem Global declarations for Visual Basic to DB-Library translation dll.
Rem Used by all apps linking with the VBSQL DLL (VBSQL.OCX)

Rem Global return values for all RETCODE type functions
Global Const SUCCEED& = 1
Global Const FAIL& = 0

Rem return values permitted in error handlers
Global Const INTEXIT& = 0
Global Const INTCONTINUE& = 1
Global Const INTCANCEL& = 2

Global Const MOREROWS& = -1
Global Const NOMOREROWS& = -2
Global Const REGROW& = -1
Global Const BUFFULL& = -3

Rem Status code for dbresults(). Possible return values are
Rem SUCCEED, FAIL, and NO_MORE_RESULTS.

Global Const NOMORERESULTS& = 2
Global Const NOMORERPCRESULTS& = 3


Rem versions for SQLSetLVersion

Global Const SQLVER42& = 8
Global Const SQLVER60& = 9



Rem option values permitted in option setting/querying/clearing
Rem used by SqlSetOpt&(), SqlIsOpt&(), and SqlClrOpt&().

Global Const SQLBUFFER& = 0
Global Const SQLOFFSET& = 1
Global Const SQLROWCOUNT& = 2
Global Const SQLSTAT& = 3
Global Const SQLTEXTLIMIT& = 4
Global Const SQLTEXTSIZE& = 5
Global Const SQLARITHABORT& = 6
Global Const SQLARITHIGNORE& = 7
Global Const SQLNOAUTOFREE& = 8
Global Const SQLNOCOUNT& = 9
Global Const SQLNOEXEC& = 10
Global Const SQLPARSEONLY& = 11
Global Const SQLSHOWPLAN& = 12
Global Const SQLSTORPROCID& = 13
Global Const SQLANSItoOEM& = 14
Global Const SQLCLIENTCURSORS& = 16
Global Const SQLQUOTEDIDENT& = 18

Rem Data type token values.  Used for datatype determination for a column.

Global Const SQLTEXT& = &H23
Global Const SQLARRAY& = &H24
Global Const SQLVARBINARY& = &H25
Global Const SQLINTN& = &H26
Global Const SQLVARCHAR& = &H27
Global Const SQLBINARY& = &H2D
Global Const SQLIMAGE& = &H22
Global Const SQLCHAR& = &H2F
Global Const SQLINT1& = &H30
Global Const SQLBIT& = &H32
Global Const SQLINT2& = &H34
Global Const SQLINT4& = &H38
Global Const SQLMONEY& = &H3C
Global Const SQLDATETIME& = &H3D
Global Const SQLFLT8& = &H3E
Global Const SQLFLTN& = &H6D
Global Const SQLFLT4& = &H3B
Global Const SQLMONEYN& = &H6E
Global Const SQLDATETIMN& = &H6F
Global Const SQLAOPCNT& = &H4B
Global Const SQLAOPSUM& = &H4D
Global Const SQLAOPAVG& = &H4F
Global Const SQLAOPMIN& = &H51
Global Const SQLAOPMAX& = &H52
Global Const SQLAOPANY& = &H53
Global Const SQLAOPNOOP& = &H56
Global Const SQLMONEY4& = &H7A
Global Const SQLDATETIM4& = &H3A
Global Const SQLDECIMAL& = &H6A
Global Const SQLNUMERIC = &H6C



Rem error numbers VBSQL error codes that are passed to local error
Rem handler

Global Const SQLEMEM& = 10000
Global Const SQLENULL& = 10001
Global Const SQLENLOG& = 10002
Global Const SQLEPWD& = 10003
Global Const SQLECONN& = 10004
Global Const SQLEDDNE& = 10005
Global Const SQLNULLO& = 10006
Global Const SQLESMSG& = 10007
Global Const SQLEBTOK& = 10008
Global Const SQLENSPE& = 10009
Global Const SQLEREAD& = 10010
Global Const SQLECNOR& = 10011
Global Const SQLETSIT& = 10012
Global Const SQLEPARM& = 10013
Global Const SQLEAUTN& = 10014
Global Const SQLECOFL& = 10015
Global Const SQLERDCN& = 10016
Global Const SQLEICN& = 10017
Global Const SQLECLOS& = 10018
Global Const SQLENTXT& = 10019
Global Const SQLEDNTI& = 10020
Global Const SQLETMTD& = 10021
Global Const SQLEASEC& = 10022
Global Const SQLENTLL& = 10023
Global Const SQLETIME& = 10024
Global Const SQLEWRIT& = 10025
Global Const SQLEMODE& = 10026
Global Const SQLEOOB& = 10027
Global Const SQLEITIM& = 10028
Global Const SQLEDBPS& = 10029
Global Const SQLEIOPT& = 10030
Global Const SQLEASNL& = 10031
Global Const SQLEASUL& = 10032
Global Const SQLENPRM& = 10033
Global Const SQLEDBOP& = 10034
Global Const SQLENSIP& = 10035
Global Const SQLECNULL& = 10036
Global Const SQLESEOF& = 10037
Global Const SQLERPND& = 10038
Global Const SQLECSYN& = 10039
Global Const SQLENONET& = 10040
Global Const SQLEBTYP& = 10041
Global Const SQLEABNC& = 10042
Global Const SQLEABMT& = 10043
Global Const SQLEABNP& = 10044
Global Const SQLEBNCR& = 10045
Global Const SQLEAAMT& = 10046
Global Const SQLENXID& = 10047
Global Const SQLEIFNB& = 10048
Global Const SQLEKBCO& = 10049
Global Const SQLEBBCI& = 10050
Global Const SQLEKBCI& = 10051
Global Const SQLEBCWE& = 10052
Global Const SQLEBCNN& = 10053
Global Const SQLEBCOR& = 10054
Global Const SQLEBCPI& = 10055
Global Const SQLEBCPN& = 10056
Global Const SQLEBCPB& = 10057
Global Const SQLEVDPT& = 10058
Global Const SQLEBIVI& = 10059
Global Const SQLEBCBC& = 10060
Global Const SQLEBCFO& = 10061
Global Const SQLEBCVH& = 10062
Global Const SQLEBCUO& = 10063
Global Const SQLEBUOE& = 10064
Global Const SQLEBWEF& = 10065
Global Const SQLEBTMT& = 10066
Global Const SQLEBEOF& = 10067
Global Const SQLEBCSI& = 10068
Global Const SQLEPNUL& = 10069
Global Const SQLEBSKERR& = 10070
Global Const SQLEBDIO& = 10071
Global Const SQLEBCNT& = 10072
Global Const SQLEMDBP& = 10073
Global Const SQLEINIT& = 10074
Global Const SQLCRSINV& = 10075
Global Const SQLCRSCMD& = 10076
Global Const SQLCRSNOIND& = 10077
Global Const SQLCRSDIS& = 10078
Global Const SQLCRSAGR& = 10079
Global Const SQLCRSORD& = 10080
Global Const SQLCRSMEM& = 10081
Global Const SQLCRSBSKEY& = 10082
Global Const SQLCRSNORES& = 10083
Global Const SQLCRSVIEW& = 10084
Global Const SQLCRSBUFR& = 10085
Global Const SQLCRSFROWN& = 10086
Global Const SQLCRSBROL& = 10087
Global Const SQLCRSFRAND& = 10088
Global Const SQLCRSFLAST& = 10089
Global Const SQLCRSRO& = 10090
Global Const SQLCRSTAB& = 10091
Global Const SQLCRSUPDTAB& = 10092
Global Const SQLCRSUPDNB& = 10093
Global Const SQLCRSVIIND& = 10094
Global Const SQLCRSNOUPD& = 10095
Global Const SQLCRSOS2& = 10096
Global Const SQLEBCSA& = 10097
Global Const SQLEBCRO& = 10098
Global Const SQLEBCNE& = 10099
Global Const SQLEBCSK& = 10100
Global Const SQLEUVBF& = 10101
Global Const SQLEBIHC& = 10102
Global Const SQLEBWFF& = 10103

Rem The severity levels are defined here for error handlers

Global Const EXINFO& = 1
Global Const EXUSER& = 2
Global Const EXNONFATAL& = 3
Global Const EXCONVERSION& = 4
Global Const EXSERVER& = 5
Global Const EXTIME& = 6
Global Const EXPROGRAM& = 7
Global Const EXRESOURCE& = 8
Global Const EXCOMM& = 9
Global Const EXFATAL& = 10
Global Const EXCONSISTENCY& = 11

Rem Length of text timestamp and text pointer
Global Const SQLTXTSLEN& = 8          ' length of text timestamp
Global Const SQLTXPLEN& = 16          ' length of text pointer

Global Const OFF_SELECT& = &H16D
Global Const OFF_FROM& = &H14F
Global Const OFF_ORDER& = &H165
Global Const OFF_COMPUTE& = &H139
Global Const OFF_TABLE& = &H173
Global Const OFF_PROCEDURE& = &H16A
Global Const OFF_STATEMENT& = &H1CB
Global Const OFF_PARAM& = &H1C4
Global Const OFF_EXEC& = &H12C

Rem Bulk Copy Definitions (bcp)

Global Const DBIN& = 1              ' transfer from client to server
Global Const DBOUT& = 2            ' transfer from server to client

Global Const BCPMAXERRS& = 1        ' SqlBcpControl parameter
Global Const BCPFIRST& = 2          ' SqlBcpControl parameter
Global Const BCPLAST& = 3           ' SqlBcpControl parameter
Global Const BCPBATCH& = 4          ' SqlBcpControl parameter
Global Const BCPKEEPNULLS& = 5      ' SqlBcpControl parameter

Rem Cursor related constants

Rem Following flags are used in the concuropt parameter in the
Rem SqlCursorOpen function

Global Const CURREADONLY& = 1   ' Read only cursor, no data modifications
Global Const CURLOCKCC& = 2     ' Intent to update, all fetched data locked
                                ' when dbcursorfetch is called inside a
                                ' transaction block
Global Const CUROPTCC& = 3      ' Optimistic concurrency control, data
                                ' modifications succeed only if the row
                                ' hasn't been updated since the last fetch
Global Const CUROPTCCVAL& = 4   ' Optimistic concurrency control based on
                                ' selected column values

Rem Following flags are used in the scrollopt parameter in the
Rem SqlCursorOpen function

Global Const CURFORWARD& = 0   ' Forward only scrolling
Global Const CURKEYSET& = -1   ' Keyset driven scrolling
Global Const CURDYNAMIC& = 1   ' Fully dynamic
Global Const CURINSENSITIVE& = -2  ' Server-side cursors only

Rem Any other number indicates mixed scrolling. (Keyset driven within the given
Rem number, dynamic outside)

Rem Following flags define the fetchtype in the SqlCursorFetch function

Global Const FETCHFIRST& = 1    ' Fetch first n rows
Global Const FETCHNEXT& = 2     ' Fetch next n rows
Global Const FETCHPREV& = 3     ' Fetch previous n rows
Global Const FETCHRANDOM& = 4   ' Fetch n rows beginning with given row#
Global Const FETCHRELATIVE& = 5 ' Fetch relative to previous fetch row #
Global Const FETCHLAST& = 6     ' Fetch the last n rows

Rem Following flags define the per row status as filled by SqlCursorFetch

Global Const FTCEMPTY& = &H0    ' No row available
Global Const FTCSUCCEED& = &H1  ' Fetch succeeded, (failed if not set)
Global Const FTCMISSING& = &H2  ' The row is missing
Global Const FTCENDOFKEYSET& = &H4 ' End of the keyset reached
Global Const FTCENDOFRESULTS& = &H8 ' End of results set reached

Rem Following flags define the operator types for the SqlCursor function

Global Const CRSUPDATE& = 1     ' Update operation
Global Const CRSDELETE& = 2     ' Delete operation
Global Const CRSINSERT& = 3     ' Insert operation
Global Const CRSREFRESH& = 4    ' Refetch given row
Global Const CRSLOCKCC& = 5     ' Lock given row (if only inside a transaction)

Rem Following define row information type requested from SqlColInfo
Global Const SQLCI_REGULAR& = 1         ' regular row
Global Const SQLCI_ALTERNATE& = 2       ' compute row
Global Const SQLCI_CURSOR& = 3          ' cursor row

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
Global Const SQLRPCRECOMPILE& = &H1 ' recompile the stored procedure
Global Const SQLRPCRESET& = &H4     ' reset rpc processing
Global Const SQLRPCRETURN& = 1      ' return parameter

Rem The following values are passed to SqlServerEnum for searching criteria.
Global Const NETSEARCH& = 1
Global Const LOCSEARCH& = 2


Rem These constants are the possible return values from SqlServerEnum.
Global Const ENUMSUCCESS& = 0
Global Const MOREDATA& = 1
Global Const NETNOTAVAIL& = 2
Global Const OUTOFMEMORY& = 4
Global Const NOTSUPPORTED& = 8
Global Const ENUMINVALIDPARAM& = 16

Rem These constants are passed to SqlUpdateText for setting update type
Global Const UTTEXTPTR& = &H1
Global Const UTTEXT& = &H2
Global Const UTMORETEXT& = &H4
Global Const UTDELETEONLY& = &H8
Global Const UTLOG& = &H10


Rem These constants are used by SqlProcInfo
Global Const SERVTYPEUNKNOWN& = 0
Global Const SERVTYPEMICROSOFT& = 1


Rem State unknown in SqlColInfo
Global Const SQLUNKNOWN& = 2

Rem User defined data type for SqlGetColumnInfo
Type ColumnData
   Coltype As Long
   Collen As Long
   Colname As String
   ColSqlType As String
End Type

Rem User defined data type for SqlGetAltColInfo
Type AltColumnData
   ColID As Long
   DataType As Long
   MaxLen As Long
   AggType As Long
   AggOpName As String * 31
End Type

Rem User defined data type for SqlBcpColumnFormat
Type BcpColData
    FType As Long
    FPLen As Long
    fColLen As Long
    FTerm As String * 31
    FTLen As Long
    TCol As Long
End Type

Rem User defined data type for SqlDateCrack
Type DateInfo
    Year As Long
    Quarter As Long
    Month As Long
    DayOfYear As Long
    Day As Long
    Week As Long
    WeekDay As Long
    Hour As Long
    Minute As Long
    Second As Long
    Millisecond As Long
End Type

Rem User defined data type for SqlColInfo
Type ColInfo
    Name As String * 31
    ActualName As String * 31
    TableName As String * 31
    CType As Long
    UserType As Long
    MaxLength As Long
    Precision As Long
    Scale As Long
    VarLength As Long
    Null As Long
    CaseSensitive As Long
    Updatable As Long
    Identity As Long
End Type

Type ProcInfo
    ServerType As Long
    ServerMajor As Long
    ServerMinor As Long
    ServerRevision As Long
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
Declare Function SqlInit Lib "VBSQL.OCX" () As String
Declare Sub SqlWinExit Lib "VBSQL.OCX" ()
Declare Function SqlLogin Lib "VBSQL.OCX" () As Long
Declare Function SqlSetLUser Lib "VBSQL.OCX" (ByVal Login As Long, User As String) As Long
Declare Function SqlSetLPwd Lib "VBSQL.OCX" (ByVal Login As Long, Pwd As String) As Long
Declare Function SqlSetLApp Lib "VBSQL.OCX" (ByVal Login As Long, App As String) As Long
Declare Function SqlSetLHost Lib "VBSQL.OCX" (ByVal Login As Long, Host As String) As Long
Declare Function SqlSetLNatLang Lib "VBSQL.OCX" (ByVal Login As Long, Lang As String) As Long
Declare Function SqlSetLSecure Lib "VBSQL.OCX" (ByVal Login As Long) As Long
Declare Function SqlSetLVersion Lib "VBSQL.OCX" (ByVal Login As Long, ByVal Version As Long) As Long
Declare Function SqlSetLFallback Lib "VBSQL.OCX" (ByVal Login As Long, State As String) As Long
Declare Function SqlOpen Lib "VBSQL.OCX" (ByVal Login As Long, Server As String) As Long
Declare Sub SqlClose Lib "VBSQL.OCX" (ByVal SqlConn As Long)
Declare Sub SqlFreeLogin Lib "VBSQL.OCX" (ByVal Login As Long)
Declare Function SqlCmd Lib "VBSQL.OCX" (ByVal SqlConn As Long, Cmd As String) As Long
Declare Function SqlExec Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlResults Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlNextRow Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlNumCols Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlColName Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Column As Long) As String
Declare Function SqlColType Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Column As Long) As Long
Declare Function SqlColUType Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Column As Long) As Long
Declare Function SqlColLen Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Column As Long) As Long
Declare Function SqlDatLen Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Column As Long) As Long
Declare Function SqlData Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Column As Long) As String
Declare Function SqlColInfo Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal InfoType As Long, ByVal Column As Long, ByVal ComputeId As Long, ColInf As ColInfo) As Long
Declare Function SqlDataReady Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Sub SqlExit Lib "VBSQL.OCX" ()
Declare Function SqlSetLoginTime Lib "VBSQL.OCX" (ByVal Seconds As Long) As Long
Declare Function SqlSetTime Lib "VBSQL.OCX" (ByVal Seconds As Long) As Long
Declare Function SqlSend Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlOk Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlGetChar Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal CharNum As Long) As String
Declare Function SqlStrCpy Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Start As Long, ByVal NumBytes As Long, Buffer As String) As Long
Declare Function SqlStrLen Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlSetOpt Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Opt As Long, Param As String) As Long
Declare Function SqlClrOpt Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Opt As Long, Param As String) As Long
Declare Function SqlIsOpt Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Opt As Long, Param As String) As Long
Declare Sub SqlFreeBuf Lib "VBSQL.OCX" (ByVal SqlConn As Long)
Declare Function SqlCancel Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlCanQuery Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlGetRow Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal RowNum As Long) As Long
Declare Sub SqlClrBuf Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal RowNum As Long)
Declare Function SqlColBrowse Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Column As Long) As Long
Declare Function SqlColSource Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal TabNum As Long) As String
Declare Function SqlQual Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal TabNum As Long, TableName As String) As String
Declare Function SqlTabBrowse Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal TabNum As Long) As Long
Declare Function SqlTabCount Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlTabName Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal TabNum As Long) As String
Declare Function SqlTabSource Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal ColNum As Long, TabNum As Long) As String
Declare Function SqlTsNewLen Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlTsNewVal Lib "VBSQL.OCX" (ByVal SqlConn As Long) As String
Declare Function SqlTsPut Lib "VBSQL.OCX" (ByVal SqlConn As Long, NewTs As String, ByVal NewTsLen As Long, ByVal TabNum As Long, TabName As String) As Long
Declare Function SqlMoreText Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Size As Long, Text As String) As Long
Declare Function SqlTxPtr Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Column As Long) As String
Declare Function SqlTxTimeStamp Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Column As Long) As String
Declare Function SqlTxTsNewVal Lib "VBSQL.OCX" (ByVal SqlConn As Long) As String
Declare Function SqlTxTsPut Lib "VBSQL.OCX" (ByVal SqlConn As Long, NewTxTs As String, ByVal Column As Long) As Long
Declare Function SqlWriteText Lib "VBSQL.OCX" (ByVal SqlConn As Long, ObjName As String, TextPtr As String, ByVal TextPtrLen As Long, TimeStamp As String, ByVal Logging As Long, ByVal Size As Long, Text As String) As Long
Declare Function SqlUpdateText Lib "VBSQL.OCX" (ByVal SqlConn As Long, ObjName As String, TextPtr As String, TimeStamp As String, ByVal UType As Long, ByVal Offset As Long, ByVal DelLen As Long, SrcName As String, ByVal Size As Long, Text As String) As Long
Declare Function SqlCmdRow Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlIsCount Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlCount Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlCurCmd Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlCurRow Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlDead Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlFirstRow Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlGetTime Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlIsAvail Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlLastRow Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlMoreCmds Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlNumOrders Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlRows Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlRowType Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlNumAlts Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal ComputeId As Long) As Long
Declare Function SqlAltType Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal ComputeId As Long, ByVal Column As Long) As Long
Declare Function SqlAltUType Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal ComputeId As Long, ByVal Column As Long) As Long
Declare Function SqlAltLen Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal ComputeId As Long, ByVal Column As Long) As Long
Declare Function SqlADLen Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal ComputeId As Long, ByVal Column As Long) As Long
Declare Function SqlAData Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal ComputeId As Long, ByVal Column As Long) As String
Declare Function SqlAltColId Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal ComputeId As Long, ByVal Column As Long) As Long
Declare Function SqlAltOp Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal ComputeId As Long, ByVal Column As Long) As Long
Declare Function SqlByList Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal ComputeId As Long) As String
Declare Function SqlNumCompute Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlUse Lib "VBSQL.OCX" (ByVal SqlConn As Long, DataBase As String) As Long
Declare Function SqlGetOff Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal OffType As Long, ByVal StartFrom As Long) As Long
Declare Function SqlOrderCol Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Order As Long) As Long
Declare Function SqlChange Lib "VBSQL.OCX" (ByVal SqlConn As Long) As String
Declare Function SqlGetMaxProcs Lib "VBSQL.OCX" () As Long
Declare Function SqlName Lib "VBSQL.OCX" (ByVal SqlConn As Long) As String
Declare Function SqlPrType Lib "VBSQL.OCX" (ByVal Token As Long) As String
Declare Sub SqlSetAvail Lib "VBSQL.OCX" (ByVal SqlConn As Long)
Declare Function SqlSetMaxProcs Lib "VBSQL.OCX" (ByVal MaxProcs As Long) As Long
Declare Function SqlBCPColfmt Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal FColumn As Long, ByVal FType As Long, ByVal FPLen As Long, ByVal FCLen As Long, FTerm As String, ByVal FTLen As Long, ByVal TCol As Long) As Long
Declare Function SqlBCPColumns Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal ColCount As Long) As Long
Declare Function SqlBCPControl Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal Param As Long, ByVal Value As Long) As Long
Declare Function SqlBCPExec Lib "VBSQL.OCX" (ByVal SqlConn As Long, RowsCopied As Long) As Long
Declare Function SqlBCPInit Lib "VBSQL.OCX" (ByVal SqlConn As Long, TblName As String, HFile As String, ErrFile As String, ByVal Direction As Long) As Long
Declare Function SqlBCPSetL Lib "VBSQL.OCX" (ByVal loginrec As Long, ByVal Enable As Long) As Long
Declare Function SqlBCPDone Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlSendCmd Lib "VBSQL.OCX" (ByVal SqlConn As Long, Cmd As String) As Long
Declare Function SqlGetColumnInfo Lib "VBSQL.OCX" (ByVal SqlConn As Long, Col As ColumnData, ByVal Column As Long) As Long
Declare Function SqlGetAltColInfo Lib "VBSQL.OCX" (ByVal SqlConn As Long, AltCol As AltColumnData, ByVal ComputeId As Long, ByVal AltColumn As Long) As Long
'Declare Function SqlOpenConnection Lib "VBSQL.OCX" Alias "_SqlOpenConnection@20" (Server As String, LoginID As String, Pwd As String, WorkStation As String, Application As String) As Long
Declare Function SqlOpenConnection Lib "VBSQL.OCX" (Server As String, LoginID As String, Pwd As String, WorkStation As String, Application As String) As Long
Declare Function SqlTextUpdate1Row Lib "VBSQL.OCX" (ByVal SqlConn As Long, ObjName As String, ByVal Column As Long, Text As String) As Long
Declare Function SqlTextUpdateManyRows Lib "VBSQL.OCX" (ByVal QSqlConn As Long, ByVal USqlConn As Long, ObjName As String, ByVal Column As Long, Text As String) As Long
Declare Function SqlBCPColumnFormat Lib "VBSQL.OCX" (ByVal SqlConn As Long, Col As BcpColData, ByVal NumCols As Long) As Long
Declare Function SqlTsUpdate Lib "VBSQL.OCX" (ByVal QSqlConn As Long, ByVal USqlConn As Long, ByVal TabNum As Long, TabName As String) As Long
'Declare Function SqlCursorOpen Lib "VBSQL.OCX" (ByVal SqlConn As Long, Statement As String, ByVal ScrollOpt As Long, ByVal ConCurOpt As Long, ByVal nRows As Long, PStat As Long) As Long
Declare Function SqlCursorOpen Lib "VBSQL.OCX" (ByVal SqlConn As Long, Statement As String, ByVal ScrollOpt As Long, ByVal ConCurOpt As Long, ByVal nRows As Long) As Long
Declare Function SqlCursorFetch Lib "VBSQL.OCX" (SqlCursor As Long, ByVal FetchType As Long, ByVal RowNum As Long) As Long
Declare Function SqlCursorFetchEx Lib "VBSQL.OCX" (SqlCursor As Long, ByVal FetchType As Long, ByVal RowNum As Long, ByVal nRows As Long, ByVal Reserved As Long) As Long
Declare Function SqlCursorRowStatus Lib "VBSQL.OCX" (SqlCursor As Long, ByVal Row As Long, ByRef Status As Long) As Long
Declare Function SqlCursorData Lib "VBSQL.OCX" (SqlCursor As Long, ByVal BufNo As Long, ByVal Column As Long) As String
Declare Function SqlCursor Lib "VBSQL.OCX" (SqlCursor As Long, ByVal OpType As Long, ByVal BufNo As Long, Table As String, Statement As String) As Long
Declare Sub SqlCursorClose Lib "VBSQL.OCX" (SqlCursor As Long)
Declare Function SqlCursorColInfo Lib "VBSQL.OCX" (SqlCursor As Long, ByVal Column As Long, Colname As String, Coltype As Long, Collen As Long, UserType As Long) As Long
Declare Function SqlCursorInfo Lib "VBSQL.OCX" (SqlCursor As Long, Columns As Long, Rows As Long) As Long
Declare Function SqlCursorInfoEx Lib "VBSQL.OCX" (SqlCursor As Long, SqlCursInf As SqlCursorInfo) As Long
Declare Function SqlDateCrack Lib "VBSQL.OCX" (ByVal SqlConn As Long, SqlDateInfo As DateInfo, DateTime As String) As Long
Declare Function SqlHasRetStat Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlNumRets Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlRetData Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal RetNum As Long) As String
Declare Function SqlRetLen Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal RetNum As Long) As Long
Declare Function SqlRetName Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal RetNum As Long) As String
Declare Function SqlRetStatus Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlRetType Lib "VBSQL.OCX" (ByVal SqlConn As Long, ByVal RetNum As Long) As Long
Declare Function SqlRpcInit Lib "VBSQL.OCX" (ByVal SqlConn As Long, RpcName As String, ByVal Options As Long) As Long
Declare Function SqlRpcParam Lib "VBSQL.OCX" (ByVal SqlConn As Long, ParamName As String, ByVal Status As Long, ByVal ParamType As Long, ByVal MaxLen As Long, ByVal DataLen As Long, Value As String) As Long
Declare Function SqlRpcSend Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlRpcExec Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Sub SqlRPwClr Lib "VBSQL.OCX" (ByVal Login As Long)
Declare Function SqlRPwSet Lib "VBSQL.OCX" (ByVal Login As Long, SrvName As String, Password As String) As Long
Declare Function SqlServerEnum Lib "VBSQL.OCX" (ByVal SearchMode As Long, ServerBuf As String, NumEntries As Long) As Long
Declare Function SqlSetLPacket Lib "VBSQL.OCX" (ByVal Login As Long, ByVal PacketSize As Long) As Long
Declare Function SqlGetPacket Lib "VBSQL.OCX" (ByVal SqlConn As Long) As Long
Declare Function SqlProcInfo Lib "VBSQL.OCX" (ByVal SqlConn As Long, ProcInf As ProcInfo) As Long
