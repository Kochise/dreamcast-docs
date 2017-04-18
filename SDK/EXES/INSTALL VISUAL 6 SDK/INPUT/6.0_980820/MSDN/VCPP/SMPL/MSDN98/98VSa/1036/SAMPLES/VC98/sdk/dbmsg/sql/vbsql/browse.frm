VERSION 2.00
Begin Form PrimaryWindow 
   BackColor       =   &H00FFFF00&
   Caption         =   "Browse Mode Example"
   Height          =   5190
   Icon            =   BROWSE.FRX:0000
   Left            =   1515
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   4665
   ScaleWidth      =   6105
   Top             =   930
   Width           =   6225
   Begin VBSQL VBSQL1 
      Caption         =   "SQL Msg/Err"
      Height          =   255
      Left            =   3840
      Top             =   4440
      Visible         =   0   'False
      Width           =   1935
   End
   Begin TextBox Contract_Edit 
      Height          =   285
      Left            =   3840
      TabIndex        =   19
      Top             =   4200
      Width           =   1935
   End
   Begin CommandButton Command3 
      Caption         =   "Exit"
      Height          =   495
      Left            =   1200
      TabIndex        =   1
      Top             =   3960
      Width           =   855
   End
   Begin CommandButton Command1 
      Caption         =   "About"
      Height          =   495
      Left            =   240
      TabIndex        =   13
      Top             =   3960
      Width           =   855
   End
   Begin TextBox Zip_Code_Edit 
      Height          =   285
      Left            =   3840
      TabIndex        =   18
      Top             =   3720
      Width           =   1935
   End
   Begin TextBox State_Edit 
      Height          =   285
      Left            =   3840
      TabIndex        =   17
      Top             =   3240
      Width           =   1935
   End
   Begin CommandButton Cancel_Query_Button 
      Caption         =   "Cancel Query"
      Height          =   615
      Left            =   240
      TabIndex        =   8
      Top             =   3000
      Width           =   1815
   End
   Begin TextBox City_Edit 
      Height          =   285
      Left            =   3840
      TabIndex        =   20
      Top             =   2760
      Width           =   1935
   End
   Begin TextBox Address_Edit 
      Height          =   285
      Left            =   3840
      TabIndex        =   16
      Top             =   2280
      Width           =   1935
   End
   Begin CommandButton Update_Button 
      Caption         =   "Update Row"
      Height          =   615
      Left            =   240
      TabIndex        =   11
      Top             =   2040
      Width           =   1815
   End
   Begin TextBox Phone_Edit 
      Height          =   285
      Left            =   3840
      TabIndex        =   15
      Top             =   1800
      Width           =   1935
   End
   Begin TextBox First_Name_Edit 
      Height          =   285
      Left            =   3840
      TabIndex        =   14
      Top             =   1320
      Width           =   1935
   End
   Begin CommandButton Next_Button 
      Caption         =   "Next Row"
      Height          =   615
      Left            =   240
      TabIndex        =   12
      Top             =   1200
      Width           =   1815
   End
   Begin TextBox Last_Name_Edit 
      Height          =   285
      Left            =   3840
      TabIndex        =   22
      Top             =   840
      Width           =   1935
   End
   Begin CommandButton Select_Button 
      Caption         =   "Select for Browse"
      Height          =   615
      Left            =   240
      TabIndex        =   0
      Top             =   360
      Width           =   1815
   End
   Begin Label Label9 
      BackColor       =   &H00FFFF00&
      Caption         =   "Contract:"
      Height          =   255
      Left            =   2640
      TabIndex        =   10
      Top             =   4200
      Width           =   825
   End
   Begin Label Label6 
      BackColor       =   &H00FFFF00&
      Caption         =   "Zip Code:"
      Height          =   255
      Left            =   2640
      TabIndex        =   6
      Top             =   3720
      Width           =   975
   End
   Begin Label Label5 
      BackColor       =   &H00FFFF00&
      Caption         =   "State:"
      Height          =   255
      Left            =   2640
      TabIndex        =   5
      Top             =   3240
      Width           =   555
   End
   Begin Label Label4 
      BackColor       =   &H00FFFF00&
      Caption         =   "City:"
      Height          =   285
      Left            =   2640
      TabIndex        =   4
      Top             =   2760
      Width           =   420
   End
   Begin Label Label8 
      BackColor       =   &H00FFFF00&
      Caption         =   "Address:"
      Height          =   255
      Left            =   2640
      TabIndex        =   9
      Top             =   2280
      Width           =   780
   End
   Begin Label Label3 
      BackColor       =   &H00FFFF00&
      Caption         =   "Phone:"
      Height          =   255
      Left            =   2640
      TabIndex        =   3
      Top             =   1800
      Width           =   630
   End
   Begin Label Label7 
      BackColor       =   &H00FFFF00&
      Caption         =   "First Name:"
      Height          =   255
      Left            =   2655
      TabIndex        =   23
      Top             =   1365
      Width           =   1095
   End
   Begin Label Label2 
      BackColor       =   &H00FFFF00&
      Caption         =   "Last Name:"
      Height          =   255
      Left            =   2670
      TabIndex        =   7
      Top             =   870
      Width           =   1095
   End
   Begin Label Author_ID_Label 
      BackColor       =   &H00FFFF00&
      Height          =   255
      Left            =   3840
      TabIndex        =   21
      Top             =   405
      Width           =   1935
   End
   Begin Label Label1 
      BackColor       =   &H00FFFF00&
      Caption         =   "Author ID:"
      Height          =   195
      Left            =   2640
      TabIndex        =   2
      Top             =   360
      Width           =   915
   End
End
Dim Qual$

Dim UpdateValueArray(8) As String
Dim TableNameArray(8) As String




Sub Address_Edit_Change ()

    If Address_Edit.Text <> "not changed" Then
        Update_Button.Enabled = True
        UpdateValueArray(3) = Address_Edit.Text
    End If

End Sub

Sub Cancel_Query_Button_Click ()
    
    Rem Cancel Query
    PrimaryWindow.MousePointer = 11
    Results% = SQLCanQuery(SqlConn%)
    ClearAuthorInformation
    Select_Button.Enabled = True
    Cancel_Query_Button.Enabled = False
    Update_Button.Enabled = False
    Next_Button.Enabled = False
    PrimaryWindow.MousePointer = 0

End Sub

Sub CheckForTimestampColumn ()

    
    Rem Change context to pubs sample database
    Results% = SqlUse(SqlConn%, "pubs")
    Results% = SqlUse(SqlUpdConn%, "pubs")
    If Results% = FAIL Then
        Beep
        Msg$ = "The SQL Server you have logged" + Chr$(13) + Chr$(10)
        Msg$ = Msg$ + "into (" + Servername$ + ") does not contain the" + Chr$(13) + Chr$(10)
        Msg$ = Msg$ + "Pubs sample database."
        MsgBox Msg$
        ExitApplication
    Else
        Rem Check to see if sample authors table has a timestamp column
        Cmd$ = "If 'timestamp' in (select c.name from syscolumns c, "
        Cmd$ = Cmd$ + "sysobjects o where c.id = o.id and o.name = 'authors') "
        Cmd$ = Cmd$ + "select -1 else select 0 "
        Results% = ExecuteSQLCommand(Cmd$)
        Do While (SqlResults%(SqlConn%) <> NOMORERESULTS)
            Do While (SqlNextRow(SqlConn%) <> NOMOREROWS)
                Timestamp_Found% = Val(Sqldata(SqlConn%, 1))
            Loop
        Loop
        If Not Timestamp_Found% Then
            Rem Add timestamp column
            Cmd$ = "alter table authors add timestamp timestamp null "
            Results% = ExecuteSQLCommand(Cmd$)
            Do While (SqlResults%(SqlConn%) <> NOMORERESULTS)
                Do While (SqlNextRow(SqlConn%) <> NOMOREROWS)
                Loop
            Loop
            Rem Now initialize the timestamp values
            Cmd$ = "update authors set au_id = au_id"
            Results% = ExecuteSQLCommand(Cmd$)
            Do While (SqlResults%(SqlConn%) <> NOMORERESULTS)
                Do While (SqlNextRow(SqlConn%) <> NOMOREROWS)
                Loop
            Loop
        End If
    End If
End Sub

Sub City_Edit_Change ()
    
    If City_Edit.Text <> "not changed" Then
        Update_Button.Enabled = True
        UpdateValueArray(4) = City_Edit.Text
    End If

End Sub

Sub ClearAuthorInformation ()

    Author_ID_Label.Caption = ""
    First_Name_Edit.Text = ""
    Last_Name_Edit.Text = ""
    Phone_Edit.Text = ""
    Address_Edit.Text = ""
    City_Edit.Text = ""
    State_Edit.Text = ""
    Zip_Code_Edit.Text = ""
    Contract_Edit.Text = ""

End Sub

Sub Command1_Click ()

    About_Form.Show 1

End Sub

Sub Command3_Click ()

    ExitApplication

End Sub

Sub Contract_Edit_Change ()

    If Contract_Edit.Text <> "not changed" Then
        Update_Button.Enabled = True
        UpdateValueArray(7) = Contract_Edit.Text
    End If

End Sub

Sub First_Name_Edit_Change ()
    
    If First_Name_Edit.Text <> "not changed" Then
        Update_Button.Enabled = True
        UpdateValueArray(1) = First_Name_Edit.Text
    End If

End Sub

Sub Form_Load ()
        
    LoadTableNameArray
    PrimaryWindowTitle$ = "Browse Mode Example"
    InitializeApplication
    Login.Show 1
    CheckForTimestampColumn
    DatabaseName = SqlName(SqlConn%)
    ChangePrimaryWindowCaption
    Cancel_Query_Button.Enabled = False
    Next_Button.Enabled = False
    Update_Button.Enabled = False

End Sub

Sub Form_Unload (Cancel As Integer)

    ExitApplication

End Sub

Sub InitializeUpdateArray ()
    Dim count As Integer

    For count = 0 To 7
        UpdateValueArray(count) = "not changed"
    Next

End Sub

Sub Last_Name_Edit_Change ()
    
    If Last_Name_Edit.Text <> "not changed" Then
        Update_Button.Enabled = True
        UpdateValueArray(0) = Last_Name_Edit.Text
    End If

End Sub

Sub LoadTableNameArray ()

    TableNameArray(0) = "au_lname"
    TableNameArray(1) = "au_fname"
    TableNameArray(2) = "phone"
    TableNameArray(3) = "address"
    TableNameArray(4) = "city"
    TableNameArray(5) = "state"
    TableNameArray(6) = "zip"
    TableNameArray(7) = "contract"

End Sub

Sub Next_Button_Click ()
    
    PrimaryWindow.MousePointer = 11
    If SqlNextRow%(SqlConn%) <> NOMOREROWS Then
        ProcessResultRow
    Else
        Next_Button.Enabled = False
        Cancel_Query_Button.Enabled = False
        Select_Button.Enabled = True
        ClearAuthorInformation
        Beep
        MsgBox "No more rows in table."
    End If
    InitializeUpdateArray
    Update_Button.Enabled = False
    PrimaryWindow.MousePointer = 0

End Sub

Sub Phone_Edit_Change ()

    If Phone_Edit.Text <> "not changed" Then
        Update_Button.Enabled = True
        UpdateValueArray(2) = Phone_Edit.Text
    End If

End Sub

Sub ProcessResultRow ()
    
    Author_ID_Label.Caption = Sqldata(SqlConn%, 1)
    Last_Name_Edit.Text = Sqldata(SqlConn%, 2)
    First_Name_Edit.Text = Sqldata(SqlConn%, 3)
    Phone_Edit.Text = Sqldata(SqlConn%, 4)
    Address_Edit.Text = Sqldata(SqlConn%, 5)
    City_Edit.Text = Sqldata(SqlConn%, 6)
    State_Edit.Text = Sqldata(SqlConn%, 7)
    Zip_Code_Edit.Text = Sqldata(SqlConn%, 8)
    Contract_Edit.Text = Sqldata(SqlConn%, 9)
    Rem Get Qual String
    Qual$ = SqlQual$(SqlConn%, -1, "authors")

End Sub

Sub Select_Button_Click ()

    Rem Send Query to SQL Server
    PrimaryWindow.MousePointer = 11
    Results% = ExecuteSQLCommand("Select * from authors for browse")
    Results% = SqlResults%(SqlConn%)
    If SqlNextRow%(SqlConn%) <> NOMOREROWS Then
        ProcessResultRow
    End If
    Cancel_Query_Button.Enabled = True
    Next_Button.Enabled = True
    Update_Button.Enabled = False
    Select_Button.Enabled = False
    InitializeUpdateArray
    PrimaryWindow.MousePointer = 0
        
End Sub

Sub State_Edit_Change ()

    If State_Edit.Text <> "not changed" Then
        Update_Button.Enabled = True
        UpdateValueArray(5) = State_Edit.Text
    End If

End Sub

Sub Update_Button_Click ()
    Dim count As Integer

    PrimaryWindow.MousePointer = 11

    Cmd$ = "update authors set "
    For count = 0 To 7
        If UpdateValueArray(count) <> "not changed" Then
            Cmd$ = Cmd$ + TableNameArray(count) + " = '"
            Cmd$ = Cmd$ + UpdateValueArray(count) + "',"
        End If
    Next
    Rem Replace final comma with space before adding qual string
    Cmd$ = Left$(Cmd$, Len(Cmd$) - 1) + " "
    Rem Now add qual string
    Cmd$ = Cmd$ + Qual$
    Results% = SqlCmd(SqlUpdConn%, Cmd$)
    Results% = SqlExec(SqlUpdConn%)
    Do While (SqlResults%(SqlUpdConn%) <> NOMORERESULTS)
        Do While (SqlNextRow(SqlUpdConn%) <> NOMOREROWS)
        Loop
    Loop
    Update_Button.Enabled = False
    PrimaryWindow.MousePointer = 0

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

Sub Zip_Code_Edit_Change ()

    If Zip_Code_Edit.Text <> "not changed" Then
        Update_Button.Enabled = True
        UpdateValueArray(6) = Zip_Code_Edit.Text
    End If

End Sub

