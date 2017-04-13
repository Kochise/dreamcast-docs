VERSION 2.00
Begin Form PrimaryWindow 
   Caption         =   "Remote Stored Procedure"
   Height          =   6765
   Icon            =   0
   Left            =   150
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   6075
   ScaleWidth      =   9060
   Top             =   390
   Width           =   9180
   Begin VBSQL VBSQL1 
      Caption         =   "VBSQL1"
      Height          =   255
      Left            =   5280
      Top             =   120
      Visible         =   0   'False
      Width           =   855
   End
   Begin TextBox RESULT_FIELD 
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "Courier"
      FontSize        =   9.75
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   2430
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   3
      Text            =   "Text1"
      Top             =   3600
      Width           =   8460
   End
   Begin Frame Frame2 
      Caption         =   "Procedure Sampler"
      Height          =   1575
      Left            =   120
      TabIndex        =   11
      Top             =   1680
      Width           =   8895
      Begin TextBox PARAMVALUE_FIELD 
         Height          =   285
         Left            =   1800
         TabIndex        =   15
         Text            =   "Text1"
         Top             =   1080
         Width           =   6975
      End
      Begin TextBox PARAMNAME_FIELD 
         Height          =   285
         Left            =   1800
         TabIndex        =   16
         Text            =   "Text2"
         Top             =   720
         Width           =   6975
      End
      Begin ComboBox PROCNAME_COMBO 
         Height          =   300
         Left            =   1800
         TabIndex        =   17
         Top             =   360
         Width           =   2895
      End
      Begin Label Label7 
         Caption         =   "Parameter &Values:"
         Height          =   255
         Left            =   120
         TabIndex        =   14
         Top             =   1080
         Width           =   1815
      End
      Begin Label Label6 
         Caption         =   "Para&meter Names:"
         Height          =   255
         Left            =   120
         TabIndex        =   13
         Top             =   720
         Width           =   1815
      End
      Begin Label Label3 
         Caption         =   "&Procedure Name:"
         Height          =   255
         Left            =   120
         TabIndex        =   12
         Top             =   360
         Width           =   1575
      End
   End
   Begin CommandButton SEND_QUERY_BUTTON 
      Caption         =   "E&xecute Proc"
      Enabled         =   0   'False
      Height          =   375
      Left            =   6360
      TabIndex        =   1
      Top             =   720
      Width           =   1575
   End
   Begin CommandButton MAKE_PROC_BUTTON 
      Caption         =   "&Make Test Proc"
      Enabled         =   0   'False
      Height          =   375
      Left            =   6360
      TabIndex        =   0
      Top             =   240
      Width           =   1575
   End
   Begin Frame Frame1 
      Caption         =   "Procedure qualifiers (optional)"
      Height          =   1455
      Left            =   120
      TabIndex        =   4
      Top             =   120
      Width           =   5055
      Begin TextBox OWNER_FIELD 
         Height          =   285
         Left            =   2040
         TabIndex        =   10
         Text            =   "Text3"
         Top             =   1080
         Width           =   2535
      End
      Begin TextBox DBNAME_FIELD 
         Height          =   285
         Left            =   2040
         TabIndex        =   8
         Text            =   "Text2"
         Top             =   720
         Width           =   2535
      End
      Begin ComboBox SERVER_COMBO 
         Height          =   300
         Left            =   2040
         TabIndex        =   6
         Top             =   360
         Width           =   2535
      End
      Begin Label Label5 
         Caption         =   "&Owner:"
         Height          =   255
         Left            =   120
         TabIndex        =   9
         Top             =   1080
         Width           =   735
      End
      Begin Label Label4 
         Caption         =   "&Database Name:"
         Height          =   255
         Left            =   120
         TabIndex        =   7
         Top             =   720
         Width           =   1455
      End
      Begin Label Label1 
         Caption         =   "Remote &Server:"
         Height          =   255
         Left            =   120
         TabIndex        =   5
         Top             =   360
         Width           =   1455
      End
   End
   Begin Label Label2 
      Caption         =   "&Results:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   3360
      Width           =   735
   End
   Begin Menu CONNECT_MENU 
      Caption         =   "&Connection"
      Begin Menu LOGIN_MENU 
         Caption         =   "&Login"
      End
      Begin Menu DATABASE_MENU 
         Caption         =   "Change &Database"
      End
      Begin Menu EXIT_MENU 
         Caption         =   "E&xit"
      End
   End
End

Sub ClearFields ()
    RESULT_FIELD.Text = ""
    DBNAME_FIELD.Text = ""
    OWNER_FIELD.Text = ""
    PARAMNAME_FIELD.Text = ""
    PARAMVALUE_FIELD.Text = ""
End Sub

Sub DATABASE_MENU_Click ()
    If SqlConn% = 0 Then
        MsgBox "Must login first"
        Exit Sub
    End If
    CHNGDB.Show 1

End Sub

Sub EXIT_MENU_Click ()

    ExitApplication

End Sub

Sub Form_Load ()

Rem
Rem Initialize the connection to SQL Server
Rem
    InitializeApplication
    MsgBox DBLIB_VERSION$
    PrimaryWindowTitle = "VBSQL RPC demonstration"

Rem
Rem Call routine to clear the fields
Rem Fill in the procedure names combobox
Rem

    ClearFields
    PROCNAME_COMBO.AddItem "sp_help"
    PROCNAME_COMBO.AddItem "sp_who"
    PROCNAME_COMBO.AddItem "echo_test"
End Sub

Function GetServers (Server_Control As Control) As Integer

Rem
Rem This routine gets the name of all the remote servers
Rem Fill each element in the combobox or list box which is passed into this procedure
Rem execute the command.  Get each server name and fill the combobox.
Rem

    If ExecuteSQLCommand("Select srvname from master..sysservers where srvid != 0") = FAIL% Then
        GetServers = FAIL
        Exit Function
    Else
        If SqlResults(SqlConn%) = FAIL% Then Exit Function
        While SqlNextRow(SqlConn%) <> NOMOREROWS%
            Server_Control.AddItem SqlData(SqlConn%, 1)
        Wend
    End If


    GetServers = SUCCEED
End Function

Sub LOGIN_MENU_Click ()
    
    Login.Show 1

    If SqlConn% <> 0 Then
        SEND_QUERY_BUTTON.Enabled = True
        MAKE_PROC_BUTTON.Enabled = True
        Results% = GetServers(SERVER_COMBO)
    End If
End Sub

Sub MAKE_PROC_BUTTON_Click ()
Static OutputData(0) As String


cmd$ = "CREATE PROCEDURE echo_test(@inparm1 varchar(20), @inparm2 int, "
cmd$ = cmd$ + "@outparm varchar(20) = NULL OUTPUT) AS "
cmd$ = cmd$ + "select @outparm = @inparm1 "
cmd$ = cmd$ + "return @inparm2"

Ret% = ExecuteSQLCommand(cmd$)
If Ret% = SUCCEED% Then
    MsgBox "Procedure echo_test created successfully"
    ' get rid of an result rows
    numrows& = Process_SQL_query("", OutputData())
End If

End Sub

Sub Parse_params (ParamIn As String, Delimiter As String, ParamOut() As String) '

Rem
Rem This routine takes the comma delimited Parameter names/values
Rem

Start% = 1
For i% = 0 To UBound(ParamOut)
    If done% = False Then
        'look for delimiter
        endpos% = InStr(Start%, ParamIn$, Delimiter$)
        If endpos% = 0 Then
            'we're at the last parameter
            ParamOut(i%) = Mid$(ParamIn$, Start%, 255)
            done% = True
        Else
            ParamOut(i%) = Mid$(ParamIn$, Start%, (endpos% - Start%))
            Start% = endpos% + 1
        End If
    Else
        'clear out rest of array
        ParamOut(i%) = ""
    End If
Next i%


End Sub

Sub PROCNAME_COMBO_Click ()

Select Case PROCNAME_COMBO.Text
    Case Is = "sp_help"
        PARAMNAME_FIELD.Text = "@objname VARCHAR(30)"
        PARAMVALUE_FIELD.Text = "sysobjects"
    Case Is = "echo_test"
        PARAMNAME_FIELD.Text = "@inparm1 VARCHAR(20),@inparm2 INTEGER,@outparm VARCHAR(20) OUT"
        PARAMVALUE_FIELD.Text = "hello,7,notused"
    Case Else
        PARAMNAME_FIELD.Text = ""
        PARAMVALUE_FIELD.Text = ""
End Select

End Sub

Sub SEND_QUERY_BUTTON_Click ()
    
Static OutputData(500) As String
CRLF$ = Chr$(13) + Chr$(10)

Rem
Rem Assemble the procedure name
Rem Get the parameter names
Rem Get the parameter values
Rem Initialize the stored proc.
Rem Fill the parameters
Rem

    
Static Param_Values(10) As String
Static Param_Declares(10) As String
Static Param_Types(2) As String
Static Param_Datatype(1) As String


'  Note:  If this is a remote server-to-server procedure call (SERVER_NAME is
'       not blank), and your remote password is different from your local
'       password, you will need to set the remote password field with SqlRPwSet%
'       prior to logging on.

procname$ = SERVER_COMBO.Text + "." + DBNAME_FIELD.Text + "." + OWNER_FIELD.Text + "." + PROCNAME_COMBO.Text
Results% = SqlRpcInit(SqlConn%, procname$, 0)


If PARAMVALUE_FIELD.Text <> "" Then
    In$ = PARAMVALUE_FIELD.Text
    Parse_params In$, ",", Param_Values()
    In$ = PARAMNAME_FIELD.Text
    Parse_params In$, ",", Param_Declares()
    For i% = 0 To 10
        'check to see if we are at the end of the parameters provided
        If Param_Values(i%) = "" Then Exit For

        'for each parameter, find out its type
        'first split type declaration into name, type(len), output
        In$ = Param_Declares(i%)
        Parse_params In$, " ", Param_Types()

        'param name is first part
        paramname$ = Param_Types(0)

        'If this is an output var, set the flag
        If Left$(Param_Types(2), 3) = "OUT" Then
            status% = SQLRPCRETURN%
        Else
            status% = 0
        End If
        
        'now take type(len) and split into type, len)
        In$ = Param_Types(1)
        Parse_params In$, "(", Param_Datatype()
        
        Select Case Param_Datatype(0)
            Case "VARCHAR"
                typecode% = SQLVARCHAR%
                If status% = SQLRPCRETURN% Then
                    maxlen& = Val(Left$(Param_Datatype(1), Len(Param_Datatype(1)) - 1))
                Else
                    maxlen& = -1
                End If
                datalen& = Len(Param_Values(i%))

            Case "INTEGER"
                typecode% = SQLINT4%
                maxlen& = -1
                datalen& = -1

            Case Else
                MsgBox "Sample does not handle " + Param_Datatype(0) + " paramters"
                Exit Sub
        End Select

        Results% = SqlRpcParam(SqlConn%, paramname$, status%, typecode%, maxlen&, datalen&, Param_Values(i%))
    Next i%
End If

Results% = SqlRpcSend(SqlConn%)

Rem
Rem Clear the result array, and result controls first
Rem

i% = 0
For i% = 0 To 499
    OutputData(i%) = ""
Next

Rem
Rem Fill the result array with the data
Rem Fill the results field
Rem

RESULT_FIELD.Text = ""
numrows& = Process_SQL_query(cmd$, OutputData())


For i% = 0 To numrows& - 1
    DataLine$ = DataLine$ + OutputData(i%) + CRLF$
Next i%

RESULT_FIELD.Text = DataLine$

End Sub

Sub VBSQL1_Error (SqlConn As Integer, Severity As Integer, ErrorNum As Integer, ErrorStr As String, RetCode As Integer)
' Call the required VBSQL error-handling function
' OSErr and OSErrStr not used in VBSQL for Windows, but DOS interprets
' anything other than -1 as an OS error
    OsErr% = -1

    RetCode% = UserSqlErrorHandler%(SqlConn, Severity%, ErrorNum%, OsErr%, ErrorStr$, OsErrStr$)


End Sub

Sub VBSQL1_Message (SqlConn As Integer, Message As Long, State As Integer, Severity As Integer, MsgStr As String)
    UserSqlMsgHandler SqlConn, Message&, State%, Severity%, MsgStr$

End Sub

