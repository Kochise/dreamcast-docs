VERSION 2.00
Begin Form PrimaryWindow 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Text"
   ControlBox      =   0   'False
   ForeColor       =   &H00000000&
   Height          =   6585
   Icon            =   TEXT.FRX:0000
   Left            =   630
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   5895
   ScaleWidth      =   7815
   Top             =   75
   Width           =   7935
   Begin TextBox Text_Edit 
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H00000000&
      Height          =   2775
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   0
      Top             =   2760
      Width           =   7575
   End
   Begin VBSQL VBSQL1 
      Caption         =   "SQL Err/Msg"
      Height          =   272
      Left            =   5580
      Top             =   2430
      Visible         =   0   'False
      Width           =   2055
   End
   Begin ListBox Titles_List 
      Height          =   810
      Left            =   135
      TabIndex        =   9
      Top             =   1410
      Width           =   2415
   End
   Begin DirListBox Dir_Tree_Combo 
      Height          =   1275
      Left            =   3360
      TabIndex        =   5
      Top             =   1155
      Width           =   2055
   End
   Begin FileListBox Text_File_List 
      Height          =   1590
      Left            =   5580
      Pattern         =   "*.txt"
      TabIndex        =   6
      Top             =   840
      Width           =   2055
   End
   Begin DriveListBox Drive_Combo 
      Height          =   357
      Left            =   3360
      TabIndex        =   4
      Top             =   833
      Width           =   2048
   End
   Begin ListBox Database_List 
      Height          =   420
      Left            =   135
      TabIndex        =   11
      Top             =   360
      Width           =   2415
   End
   Begin TextBox Title_Edit 
      Height          =   323
      Left            =   4605
      TabIndex        =   2
      Top             =   75
      Width           =   3075
   End
   Begin Label Label5 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Text in database:"
      Height          =   225
      Left            =   120
      TabIndex        =   12
      Top             =   2520
      Width           =   2055
   End
   Begin Label Label4 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Titles in database:"
      Height          =   225
      Left            =   120
      TabIndex        =   10
      Top             =   1185
      Width           =   2055
   End
   Begin Label Text_File_Label 
      BackColor       =   &H00C0C0C0&
      Caption         =   "(none)"
      Height          =   255
      Left            =   3855
      TabIndex        =   8
      Top             =   480
      Width           =   3870
   End
   Begin Label Label3 
      BackColor       =   &H00C0C0C0&
      Caption         =   "File:"
      Height          =   255
      Left            =   3360
      TabIndex        =   7
      Top             =   480
      Width           =   375
   End
   Begin Label Label2 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Text file title:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   3360
      TabIndex        =   3
      Top             =   120
      Width           =   1245
   End
   Begin Label Label1 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Databases:"
      Height          =   210
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   1005
   End
   Begin Menu Menu_File 
      Caption         =   "&File"
      Begin Menu Logon_Selection 
         Caption         =   "&Logon"
      End
      Begin Menu Log_Off_Selection 
         Caption         =   "Log &Off"
      End
      Begin Menu Exit_Selection 
         Caption         =   "&Exit"
      End
   End
   Begin Menu Options_Menu 
      Caption         =   "&Options"
      Begin Menu View_Selection 
         Caption         =   "&View Text"
      End
      Begin Menu Insert_Selection 
         Caption         =   "&Insert Text"
      End
      Begin Menu Delete_Selection 
         Caption         =   "&Delete Text"
      End
   End
   Begin Menu About_Menu 
      Caption         =   "&About"
   End
End

Sub About_Menu_Click ()

    About_Form.Show 1

End Sub

Function CheckForTextTable () As Integer

    Rem Check to see if sample table exits
    Cmd$ = "Select count(*) from sysobjects where name = 'text_table'"
    Results% = SqlCmd(SqlConn%, Cmd$)
    Results% = SqlExec(SqlConn%)
    Do While (SqlResults%(SqlConn%) <> NOMORERESULTS)
	Do While (SqlNextRow(SqlConn%) <> NOMOREROWS)
	    Table_Found$ = Sqldata(SqlConn%, 1)
	Loop
    Loop
	
    If Val(Table_Found$) = 0 Then
	Results% = MsgBox("Text table not found in " + Database$ + " database." + Chr$(13) + Chr$(10) + "Do you wish to create the table?", 52)
	If Results% = 7 Then
	    CheckForTextTable = FAIL
	    Exit Function
	Else
	    Rem If sample table does not exist, create it
	    Cmd$ = "create table text_table (title varchar(30) not null, text_col text null)"
	    Results% = SqlCmd(SqlConn%, Cmd$)
	    Results% = SqlExec(SqlConn%)
	    Do While (SqlResults%(SqlConn%) <> NOMORERESULTS)
		Do While (SqlNextRow(SqlConn%) <> NOMOREROWS)
		Loop
	    Loop
	    CheckForTextTable = SUCCEED
	End If
    Else
	CheckForTextTable = SUCCEED
    End If

End Function

Sub ClearTextTitles ()

	Rem Clear all text titles out of list box
	Do While Titles_List.ListCount
	    Titles_List.RemoveItem 0
	Loop

End Sub

Sub Database_List_Click ()

Rem
Rem Get the database user wants to open
Rem If it doesn't have the text table in it, see if user wants to create one
Rem If it does exist, get all the text titles
Rem
   
    DatabaseSelection$ = Database_list.Text
    Results% = SqlUse(SqlConn%, DatabaseSelection$)
    Results% = CheckForTextTable()
    If Results% = SUCCEED Then
	PrimaryWindow.MousePointer = 11
	RetrieveTextTitles
	View_Selection.Enabled = True
	Insert_Selection.Enabled = True
	Delete_Selection.Enabled = True
	PrimaryWindow.MousePointer = 0
    Else
	ClearTextTitles
	View_Selection.Enabled = False
	Insert_Selection.Enabled = False
	Delete_Selection.Enabled = False
    End If

Rem
Rem Display the current database in the title window
Rem clear the text field
Rem

    DatabaseName$ = SqlName(SqlConn%)
    ChangePrimaryWindowCaption
    Text_Edit.Text = ""

End Sub

Sub Delete_Selection_Click ()

    Text_Title$ = Titles_List.Text

    If Text_Title$ = "" Then
	Beep
	MsgBox "You must first select a title."
    Else
	Response% = MsgBox("Delete " + Text_Title$ + "?", 49)
	If Response% = 1 Then
	    PrimaryWindow.MousePointer = 11
	    Results% = ExecuteSQLCommand("Delete from text_table where title = '" + Text_Title$ + "'")
	    Results% = SqlResults%(SqlConn%)
	    Do While (SqlNextRow(SqlConn%) <> NOMOREROWS)
	    Loop
	    PrimaryWindow.Text_Edit.Text = ""
	    RetrieveTextTitles
	    PrimaryWindow.MousePointer = 0
	Else
	    MsgBox "Delete aborted."
	End If
    End If

End Sub

Sub Dir_Tree_Combo_Change ()

    Text_File_Label.Caption = "(none)"
    Text_File_List.Path = Dir_Tree_Combo.Path

End Sub

Sub Drive_Combo_Change ()

    Text_File_Label.Caption = "(none)"
    Dir_Tree_Combo.Path = Drive_Combo.Drive

End Sub

Sub Exit_Selection_Click ()

    ExitApplication
    End

End Sub

Sub Form_Load ()

    PrimaryWindowTitle = "Text Example"
    ChangePrimaryWindowCaption

    InitializeApplication
    MsgBox DBLIB_VERSION$

    Logon_Selection.Enabled = True
    Log_Off_Selection.Enabled = False
    Exit_Selection.Enabled = True
    View_Selection.Enabled = False
    Insert_Selection.Enabled = False
    Delete_Selection.Enabled = False

End Sub

Sub Insert_Selection_Click ()

    Text_File$ = Text_File_Label.Caption
    Title$ = Title_Edit.Text
    Title$ = PrepareString(Title$)

    If Text_File$ = "(none)" Then
	Beep
	MsgBox "Please select a text file to insert."
    ElseIf Title$ = "" Then
	Beep
	MsgBox "Please enter a title for the text file you wish to insert."
    Else
	PrimaryWindow.MousePointer = 11
	InsertText Title$, Text_File$
	Title_Edit.Text = ""
	Text_File_List.ListIndex = -1
	Text_File_Label.Caption = ""
	RetrieveTextTitles
	PrimaryWindow.MousePointer = 0
    End If

End Sub

Sub InsertText (Title As String, Text_File As String)
    
Rem
Rem This routine will insert the text data into the table
Rem Insert new row with title and token text value
Rem

    Results% = ExecuteSQLCommand("Insert into text_table values ('" + Title + "','none')")
    Do While SqlResults(SqlConn%) <> NOMORERESULTS%
	Do While SqlNextRow(SqlConn%) <> NOMOREROWS%
	Loop
    Loop

Rem Get identifier for text column in current row

    Results% = ExecuteSQLCommand("select text_col from text_table where title = '" + Title + "'")
    Do While SqlResults(SqlConn%) <> NOMORERESULTS%
	Do While SqlNextRow(SqlConn%) <> NOMOREROWS%
	    SqlPointer$ = SqlTxPtr(SqlConn%, 1)
	    SqlTimestamp$ = SqlTxTimeStamp(SqlConn%, 1)
	Loop
    Loop

Rem Open text file to load into SQL Server table

    DataPartLimit& = 8192
    Done% = False
    
    Open Text_File For Input As #1

    FileLength& = LOF(1)
    If FileLength& > 65536 Then
	MsgBox "This application cannot display text files greater than 64K."
    Else
	FileData$ = ""
	Do While Not EOF(1)
	    Input #1, DataPart$
	    If Right$(DataPart$, 2) <> Chr$(13) + Chr$(10) Then
		If Right$(DataPart$, 1) = Chr$(13) Then
		    FileData$ = FileData$ + Left$(DataPart$, Len(DataPart$) - 1) + Chr$(13) + Chr$(10)
		ElseIf Right$(DataPart$, 1) = Chr$(10) Then
		    FileData$ = FileData$ + Left$(DataPart$, Len(DataPart$) - 1) + Chr$(13) + Chr$(10)
		Else
		    FileData$ = FileData$ + DataPart$ + Chr$(13) + Chr$(10)
		End If
	    Else
		FileData$ = FileData$ + DataPart$
	    End If
	Loop

Rem Begin inserting text into text column in DatePartLimit& size chunks

	Table$ = "text_table.text_col"
	DataPos& = 1
	DataLen& = Len(FileData$)

	If SqlWriteText(SqlConn%, Table$, SqlPointer$, SQLTXPLEN%, SqlTimestamp$, 1, DataLen&, "") <> FAIL% Then
	    If SqlOk(SqlConn%) <> FAIL% Then
		Results% = SqlResults(SqlConn%)
		Do While Not Done%
		    If DataPos& + DataPartLimit& - 1 < DataLen& Then
			DataPart$ = Mid$(FileData$, DataPos&, DataPartLimit&)
			DataPos& = DataPos& + Len(DataPart$)
		    Else
			DataPart$ = Mid$(FileData$, DataPos&, DataLen& - DataPos& + 1)
			Done% = True
		    End If
		Results% = SqlMoreText%(SqlConn%, Len(DataPart$), DataPart$)
		Loop
		If SqlOk(SqlConn%) <> FAIL% Then
		    If SqlResults(SqlConn%) <> FAIL% Then
		    MsgBox "Text inserted."
		    End If
		End If
	    End If
	End If
    End If
Close 1

End Sub

Sub LoadText (Title As String)
    
Rem
Rem This routine will read the text field from the table
Rem Clear Text_Edit box on primary window
Rem

    Text_Edit.Text = ""

Rem Get length of text in text column

    Results% = ExecuteSQLCommand("select datalength(text_col) from text_table where title = '" + Title + "'")
    Do While SqlResults(SqlConn%) <> NOMORERESULTS
	Do While SqlNextRow(SqlConn%) <> NOMOREROWS
	    TextLen& = Val(Sqldata(SqlConn%, 1))
	Loop
    Loop

    Offset& = 0
	
Rem Set size limit on chunks of text data

    LoadSizeLimit& = 8192
    If LoadSizeLimit& > TextLen& Then
	LoadSizeLimit& = TextLen&
    End If
    
    LoadSize& = LoadSizeLimit&

Rem Set size of text returned to LoadSizeLimit&

    Results% = ExecuteSQLCommand("set textsize " + Str$(LoadSizeLimit&))
    Do While SqlResults(SqlConn%) <> NOMORERESULTS
	Do While SqlNextRow(SqlConn%) <> NOMOREROWS
	Loop
    Loop

Rem Begin reading text column in LoadSizeLimit& size chunks

    Cmd$ = "Declare @val varbinary(30)"
    Results% = SqlCmd(SqlConn%, Cmd$)
    Cmd$ = "Select @val = textptr(text_col) from text_table where title = '" + Title + "'"
    Results% = SqlCmd(SqlConn%, Cmd$)
    Done% = False
	Do While Not Done%
	    Cmd$ = "READTEXT text_table.text_col @val " + Str$(Offset&) + " " + Str$(LoadSize&)
	    Results% = SqlCmd(SqlConn%, Cmd$)
	    If Offset& + LoadSize& = TextLen& Then
		Done% = True
	    Else
		Offset& = Offset& + LoadSizeLimit&
		If Offset& + LoadSizeLimit& > TextLen& Then
		    LoadSize& = TextLen& - Offset&
		End If
	    End If
	Loop

Rem Retrieve text data in result rows and place in text_edit box
    
    FileData$ = ""
    If SqlExec(SqlConn%) <> FAIL% Then
	Do While SqlResults(SqlConn%) <> NOMORERESULTS
	    Do While SqlNextRow(SqlConn%) <> NOMOREROWS
		FileData$ = FileData$ + Sqldata(SqlConn%, 1)
	    Loop
	Loop
    End If

Rem Load text data into edit box on primary window
    Text_Edit.Text = FileData$

End Sub

Sub Log_Off_Selection_Click ()

    Logoff

    Logon_Selection.Enabled = True
    Log_Off_Selection.Enabled = False
    Exit_Selection.Enabled = True
    View_Selection.Enabled = False
    Insert_Selection.Enabled = False
    Delete_Selection.Enabled = False

End Sub

Sub Logon_Selection_Click ()

    Login.Show 1
    PrimaryWindow.MousePointer = 11
    If CheckServerConnection() = 1 Then
	Results% = GetDatabases(Database_list)
	ChangePrimaryWindowCaption
	Logon_Selection.Enabled = False
	Log_Off_Selection.Enabled = True
    End If
    PrimaryWindow.MousePointer = 0

End Sub

Function PrepareString (String_In As String) As String

Rem
Rem This routine will double up the single quotation mark to
Rem avoid syntax errors
Rem

    String_Out$ = ""

    For I% = 1 To Len(String_In)
	If Mid$(String_In, I%, 1) = Chr$(39) Then
	    String_Out$ = String_Out$ + Chr$(39) + Chr$(39)
	Else
	    String_Out$ = String_Out$ + Mid$(String_In, I%, 1)
	End If
    Next

    PrepareString = String_Out$

End Function

Sub RetrieveTextTitles ()

Rem
Rem This routine will get all the text titles from the table
Rem Put them in the list box as they are retrieved.
Rem

    ClearTextTitles
    Results% = ExecuteSQLCommand("Select title from text_table")
    Do While (SqlResults%(SqlConn%) <> NOMORERESULTS)
	Do While (SqlNextRow(SqlConn%) <> NOMOREROWS)
	    Titles_List.AddItem Sqldata(SqlConn%, 1)
	Loop
    Loop

End Sub

Sub Text_Edit_KeyPress (KeyAscii As Integer)

    If KeyAscii <> 0 Then
	KeyAscii = 0
    End If

End Sub

Sub Text_File_List_Click ()

    If Right$(Dir_Tree_Combo.Path, 1) = "\" Then
	Text_File_Label.Caption = Dir_Tree_Combo.Path + Text_File_List.FileName
    Else
	Text_File_Label.Caption = Dir_Tree_Combo.Path + "\" + Text_File_List.FileName
    End If

End Sub

Sub Title_Edit_KeyPress (KeyAscii As Integer)

    If Len(Title_Edit.Text) = 30 Then
	If KeyAscii <> 8 Then
	    KeyAscii = 0
	End If
    End If
    
End Sub

Sub Titles_List_Click ()

    Text_Edit.Text = ""

End Sub

Sub Titles_List_DblClick ()

    Text_Title$ = Titles_List.Text
    PrimaryWindow.MousePointer = 11
    LoadText Text_Title$
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

Sub View_Selection_Click ()

    Text_Title$ = Titles_List.Text
    If Text_Title$ = "" Then
	Beep
	MsgBox "You must first select a title."
    Else
	PrimaryWindow.MousePointer = 11
	LoadText Text_Title$
	PrimaryWindow.MousePointer = 0
    End If

End Sub

