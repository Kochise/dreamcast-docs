VERSION 2.00
Begin Form PrimaryWindow 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Cursor Scroll Bar Example"
   ForeColor       =   &H00000000&
   Height          =   7215
   Icon            =   CURSORS.FRX:0000
   Left            =   990
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   6285
   ScaleWidth      =   7725
   Top             =   -30
   Width           =   7845
   Begin ListBox Cursor_Buffer 
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "Courier"
      FontSize        =   9.75
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   2955
      Left            =   120
      TabIndex        =   18
      Top             =   3240
      Width           =   7215
   End
   Begin VScrollBar VScroll1 
      Height          =   3255
      LargeChange     =   15
      Left            =   7320
      Max             =   500
      SmallChange     =   15
      TabIndex        =   20
      Top             =   3000
      Width           =   255
   End
   Begin VBSQL VBSQL1 
      Caption         =   "SQL Error/Message"
      Height          =   255
      Left            =   5160
      Top             =   2760
      Visible         =   0   'False
      Width           =   2175
   End
   Begin Frame Frame2 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Cursor Information"
      Height          =   1575
      Left            =   120
      TabIndex        =   5
      Top             =   1080
      Width           =   7455
      Begin CommandButton Update_Button 
         Caption         =   "&Update"
         Height          =   375
         Left            =   6360
         TabIndex        =   16
         Top             =   1080
         Width           =   975
      End
      Begin ComboBox CC_List 
         Height          =   300
         Left            =   2160
         Style           =   2  'Dropdown List
         TabIndex        =   13
         Top             =   1080
         Width           =   3255
      End
      Begin CommandButton Close_Button 
         Caption         =   "C&lose"
         Height          =   375
         Left            =   6360
         TabIndex        =   15
         Top             =   720
         Width           =   975
      End
      Begin TextBox IntN_value 
         Height          =   285
         Left            =   4800
         TabIndex        =   11
         Text            =   "Text1"
         Top             =   720
         Width           =   495
      End
      Begin ComboBox Sensitivity_List 
         Height          =   300
         Left            =   2160
         Style           =   2  'Dropdown List
         TabIndex        =   9
         Top             =   720
         Width           =   2175
      End
      Begin CommandButton Open_Button 
         Caption         =   "&Open "
         Height          =   375
         Left            =   6360
         TabIndex        =   14
         Top             =   360
         Width           =   975
      End
      Begin TextBox Fetch_size 
         Height          =   285
         Left            =   2160
         TabIndex        =   7
         Text            =   "1"
         Top             =   360
         Width           =   375
      End
      Begin Label Label3 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Concurrenc&y Control:"
         Height          =   210
         Left            =   120
         TabIndex        =   12
         Top             =   1080
         Width           =   1845
      End
      Begin Label Label8 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&N:"
         Height          =   255
         Left            =   4440
         TabIndex        =   10
         Top             =   720
         Width           =   255
      End
      Begin Label Label2 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Cursor &Sensitivity:"
         Height          =   225
         Left            =   120
         TabIndex        =   8
         Top             =   720
         Width           =   1605
      End
      Begin Label Label6 
         BackColor       =   &H00C0C0C0&
         Caption         =   "(Max = 15)"
         Height          =   255
         Left            =   2640
         TabIndex        =   19
         Top             =   360
         Width           =   975
      End
      Begin Label Label5 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Rows per &Fetch:"
         Height          =   240
         Left            =   120
         TabIndex        =   6
         Top             =   360
         Width           =   1815
      End
   End
   Begin Frame Frame1 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Object"
      Height          =   855
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   7455
      Begin ComboBox Table_List 
         Height          =   300
         Left            =   4800
         TabIndex        =   4
         Text            =   "Table_List"
         Top             =   360
         Width           =   2295
      End
      Begin ComboBox Database_List 
         Height          =   300
         Left            =   1320
         TabIndex        =   2
         Text            =   "Database_List"
         Top             =   360
         Width           =   2295
      End
      Begin Label Label4 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Table:"
         Height          =   225
         Left            =   3840
         TabIndex        =   3
         Top             =   360
         Width           =   735
      End
      Begin Label Label1 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Database:"
         Height          =   210
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Width           =   1005
      End
   End
   Begin Label COLUMN_LABEL 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Label8"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "Courier"
      FontSize        =   9.75
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   255
      Left            =   120
      TabIndex        =   21
      Top             =   3000
      Width           =   7215
   End
   Begin Label Label7 
      BackColor       =   &H00C0C0C0&
      Caption         =   "&Results:"
      Height          =   255
      Left            =   120
      TabIndex        =   17
      Top             =   2760
      Width           =   855
   End
   Begin Menu Menu_File 
      Caption         =   "&Connect"
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
   Begin Menu Menu_Help 
      Caption         =   "&Help"
      Begin Menu About_Selection 
         Caption         =   "&About..."
      End
   End
End


Sub About_Selection_Click ()
    About_Form.Show 1
End Sub

Sub BeginTran ()
    Results% = ExecuteSQLCommand("begin tran")
    Do While SqlResults(SqlConn%) <> NOMORERESULTS
    Do While SqlNextRow(SqlConn%) <> NOMOREROWS
    Loop
    Loop
    OpenTran% = True
End Sub

Sub CC_List_Click ()
    If Sensitivity_List.ListIndex = -1 Or Table_List.ListIndex = -1 Then
	Open_Button.Enabled = False
    Else
	Open_Button.Enabled = True
    End If

End Sub

Sub ClearCursorBuffer ()

Do While Cursor_Buffer.ListCount
    Cursor_Buffer.RemoveItem 0
Loop

End Sub

Sub ClearDatabaseList ()
    
Rem Clear all databases out of list box

    Do While Database_List.ListCount
	Database_List.RemoveItem 0
    Loop
    Database_List.Text = ""
End Sub

 Sub ClearOutputBuffer ()

 For i% = 0 To 19
    OutputData(i%) = ""
 Next i%

End Sub

Sub ClearTableList ()

    Rem Clear all tables out of list box
    Do While Table_List.ListCount
	Table_List.RemoveItem 0
    Loop
    Table_List.Text = ""

End Sub

Sub Close_Button_Click ()
    If OpenTran% Then
	CommitTran
    End If

    SqlCursorClose CursorHandle%

    Open_Button.Enabled = True
    Close_Button.Enabled = False
    Update_Button.Enabled = False
    Fetch_Size.Enabled = True
    Sensitivity_List.Enabled = True
    CC_List.Enabled = True
    IntN_value.Enabled = True
    
    COLUMN_LABEL.Caption = ""
    ClearCursorBuffer

End Sub

Sub CommitTran ()
    Results% = ExecuteSQLCommand("commit tran")
    Do While SqlResults(SqlConn%) <> NOMORERESULTS
    Do While SqlNextRow(SqlConn%) <> NOMOREROWS
    Loop
    Loop
OpenTran% = False
End Sub

Sub Database_List_Click ()

Rem
Rem This routine will use the selected database, get all the user
Rem tables in the database, and change the primary window title
Rem to reflect the database change.
Rem

    DatabaseSelection$ = Database_List.Text
    Results% = SqlUse(SqlConn%, DatabaseSelection$)
    If Results% = SUCCEED Then
	PrimaryWindow.MousePointer = 11
	RetrieveTableNames
	PrimaryWindow.MousePointer = 0
	DatabaseName = SqlName$(SqlConn%)
	ChangePrimaryWindowCaption
	If Table_List.ListIndex = -1 Or Sensitivity_List.ListIndex = -1 Or CC_List.ListIndex = -1 Then
	    Open_Button.Enabled = False
	Else
	    Open_Button.Enabled = True
	End If
    End If



End Sub

Sub Exit_Selection_Click ()

    ExitApplication
    End

End Sub

Sub Fetch_First ()

    ClearCursorBuffer
    If Not OpenTran% Then
	BeginTran
    Else
	CommitTran
	BeginTran
    End If

    Results% = SqlCursorFetch%(CursorHandle%, FETCHFIRST, 0)
    If Results% = SUCCEED And Int(RowStatus&(0)) <> FTCENDOFRESULTS% Then
	ProcessCursorRows
	Update_Button.Enabled = True
	FillCursorBuffer -1        'display the data
    Else
	MsgBox "Problem fetching cursor.", 0, "Cursor Example"
    End If
End Sub

Sub Fetch_Last ()
    If Not OpenTran% Then
	BeginTran
    Else
	CommitTran
	BeginTran
    End If
    
    Results% = SqlCursorFetch%(CursorHandle%, FETCHLAST, 0)
    If Results% = SUCCEED And Int(RowStatus&(0)) <> FTCENDOFRESULTS% Then
	ProcessCursorRows
	Update_Button.Enabled = True
	FillCursorBuffer -1        'display the data
    Else
	MsgBox "Problem fetching cursor.", 0, "Cursor Example"
    End If
End Sub

Sub Fetch_Next ()

Rem
Rem This routine will get this next batch of rows
Rem

    If Not OpenTran% Then
	BeginTran
    Else
	CommitTran
	BeginTran
    End If

    Results% = SqlCursorFetch%(CursorHandle%, FETCHNEXT, 0)
    If Results% = SUCCEED And Int(RowStatus&(0)) <> FTCENDOFRESULTS% Then
	ProcessCursorRows
	Update_Button.Enabled = True
	FillCursorBuffer -1        'display the data
    Else
	MsgBox "Problem fetching cursor. You are more than likely at the end of the result set", 0, "Cursor Example"
    End If
End Sub

Sub Fetch_Previous ()

Rem
Rem This routine will get the previous batch of rows
Rem

    If Not OpenTran% Then
	BeginTran
    Else
	CommitTran
	BeginTran
    End If

    Results% = SqlCursorFetch%(CursorHandle%, FETCHPREV, 0)
    If Results% = SUCCEED And Int(RowStatus&(0)) <> FTCENDOFRESULTS% Then
	ProcessCursorRows
	Update_Button.Enabled = True
	FillCursorBuffer -1        'display the data
    Else
	MsgBox "Problem fetching cursor.", 0, "Cursor Example"
    End If
End Sub

Sub Fetch_Random (Rownum As Integer)

Rem
Rem This routine will get a row number to start fetching from
Rem

    If Not OpenTran% Then
	BeginTran
    Else
	CommitTran
	BeginTran
    End If

    Results% = SqlCursorFetch%(CursorHandle%, FETCHRANDOM, Rownum%)
    If Results% = SUCCEED And Int(RowStatus&(0)) <> FTCENDOFRESULTS% Then
	ProcessCursorRows
	Update_Button.Enabled = True
	FillCursorBuffer -1        'display the data
    Else
	MsgBox "Problem fetching cursor.", 0, "Cursor Example"
    End If
End Sub

Sub Fetch_Relative (ScrollValue As Integer)

Rem
Rem This routine will get a batch relative to the selected row
Rem First Calculate where to start the fetch
Rem

    MaxRows% = Vscroll1.Max
    n = (ScrollValue * MaxRows%) / 100
    Rownum% = n - CursorSliderValue%

Rem
Rem Fetch the rows
Rem

    If Not OpenTran% Then
	BeginTran
    Else
	CommitTran
	BeginTran
    End If

    Results% = SqlCursorFetch%(CursorHandle%, FETCHRELATIVE, Rownum%)
    If Results% = SUCCEED And Int(RowStatus&(0)) <> FTCENDOFRESULTS% Then
	ProcessCursorRows
	Update_Button.Enabled = True
	FillCursorBuffer -1        'display the data
    Else
	MsgBox "Problem fetching cursor.", 0, "Cursor Example"
    End If
End Sub

Sub Fetch_size_LostFocus ()

Rem
Rem Make sure the fetch size fits in the results list box to avoid scrolling
Rem

    Num% = Val(Fetch_Size.Text) * Val(IntN_value.Text)

    If Val(Fetch_Size.Text) < 1 Or Val(Fetch_Size.Text) > 15 Then
	MsgBox "Value must be between 1 and 15", 0, "Cursor Example"
	Fetch_Size.SetFocus
    End If


End Sub

Sub FillCursorBuffer (x As Integer)

Rem
Rem If x% >= 0, then we are doing a horizontal scroll
Rem Clear the list box
Rem Fill the list box with the shifted data
Rem

    If x% >= 0 Then

    ClearCursorBuffer
    startshift% = x%
    
    rowlen& = Len(OutputData(0))
    i% = 0
    While OutputData(i%) <> ""
	If i% <= 2 Then
	If x% = 0 Then startshift% = 1
	Cursor_Buffer.AddItem Mid$(OutputData(i%), startshift%, rowlen&)
	Else
	If x% = 0 Then startshift% = 2
	Cursor_Buffer.AddItem Mid$(OutputData(i%), startshift% - 1, rowlen&)
	End If
	i% = i% + 1
    Wend

Rem
Rem First fill the buffer with the headings
Rem Then fill in the data
Rem

    Else
	i% = 0
	While OutputData(i%) <> ""
	    Cursor_Buffer.AddItem OutputData(i%)
	    i% = i% + 1
	Wend

    End If
End Sub

Sub Form_Load ()

Rem
Rem Initialize the application
Rem

    PrimaryWindowTitle = "Cursor Example"
    ChangePrimaryWindowCaption

    InitializeApplication
    MsgBox DBLIB_VERSION$, 0, "Cursor Example"

Rem
Rem Set the initial state of each of the controls in the form
Rem

    Sensitivity_List.AddItem "Static"
    Sensitivity_List.AddItem "Keyset driven"
    Sensitivity_List.AddItem "Dynamic"
    Sensitivity_List.AddItem "Int N"

    CC_List.AddItem "Read only"
    CC_List.AddItem "Locking control"
    CC_List.AddItem "Optimistic concurrency"
    CC_List.AddItem "Optimistic concurrency by values"

    Logon_Selection.Enabled = True
    Log_Off_Selection.Enabled = False
    Exit_Selection.Enabled = True

    Open_Button.Enabled = False
    Close_Button.Enabled = False
    Update_Button.Enabled = False

    OpenTran% = False
    COLUMN_LABEL.Caption = ""
    ClearCursorBuffer
    ClearDatabaseList
    ClearTableList
    IntN_value.Text = "0"
End Sub

Sub Log_Off_Selection_Click ()

Rem
Rem Set the state of the controls
Rem Logoff
Rem

    ClearDatabaseList
    ClearTableList
    Open_Button.Enabled = False
    Close_Button.Enabled = False
    Update_Button.Enabled = False
    
    Logoff

    Logon_Selection.Enabled = True
    Log_Off_Selection.Enabled = False
    Exit_Selection.Enabled = True

End Sub

Sub Logon_Selection_Click ()

Rem
Rem Logon to the server
Rem Get the databases in the server and display them in the list box
Rem Change the primary window caption to reflect current status
Rem

    Login.Show 1
    PrimaryWindow.MousePointer = 11
    If CheckServerConnection() = 1 Then
	Results% = GetDatabases(Database_List)
	ChangePrimaryWindowCaption
	Logon_Selection.Enabled = False
	Log_Off_Selection.Enabled = True
    End If
    PrimaryWindow.MousePointer = 0

End Sub

Sub Open_Button_Click ()

Rem
Rem Get the fetch size and keyset size
Rem Redimension the rowstatus array
Rem

    NumRowsInCursor% = Val(Fetch_Size.Text)
    IntN% = Val(IntN_value.Text)
    ReDim RowStatus&(NumRowsInCursor%)

Rem
Rem Set the scroll option and concurrency control values
Rem

    Select Case Sensitivity_List.Text
    Case "Static"
	ScrollOpt% = CURFORWARD%
    Case "Keyset driven"
	    ScrollOpt% = CURKEYSET%
    Case "Dynamic"
	ScrollOpt% = CURDYNAMIC%
    Case "Int N"
	If IntN% <= 0 Then
	    MsgBox "You must Supply N", 0, "Cursor Example"
	    Exit Sub
	Else
	    ScrollOpt% = IntN%
	End If
    End Select

    Select Case CC_List.Text
    Case "Read only"
	Concuropt% = CURREADONLY%
    Case "Locking control"
	Concuropt% = CURLOCKCC%
    Case "Optimistic concurrency"
	Concuropt% = CUROPTCC%
    Case "Optimistic concurrency by values"
	Concuropt% = CUROPTCCVAL%
    End Select

Rem
Rem Setup the select statement and open the cursor
Rem

    Statement$ = "select * from " + Table_List.Text

    CursorHandle% = SqlCursorOpen(SqlConn%, Statement$, ScrollOpt%, Concuropt%, NumRowsInCursor%, RowStatus&(0))

    If CursorHandle% <> FAIL Then
	Open_Button.Enabled = False
	Close_Button.Enabled = True
    
Rem
Rem Get Column names and lengths
Rem Output the column header
Rem
   
	Results% = SqlCursorInfo%(CursorHandle%, NumCols%, NumRowsInKeyset&)
	For ColCount% = 1 To NumCols%
	    Results% = SqlCursorColInfo%(CursorHandle%, ColCount%, colname$, Coltype%, ColLen&, UserType%)
	    CursorColName$(ColCount%) = colname$
	    CursorColLen&(ColCount%) = ColLen&
	Next ColCount%
	ClearOutputBuffer
	ProcessCursorHeader
	IntN_value.Enabled = False
	Sensitivity_List.Enabled = False
	CC_List.Enabled = False
 
Rem
Rem Set the vertical scroll bar to <page up> and <page down> the size of the fetch
Rem Determine the max value of VScroll1
Rem     If we are dealing with a mixed scroll, then set to number (ScrollOpt% * IntN%) * an arbitrary number
Rem         NOTE: You choose an arbitrary number because you want to be able to go outside of keyset.
Rem     If Dealing with keyset or static scroll and we have enough room to store the whole keyset,
Rem         then set max to full keyset size.
Rem     Otherwise, we're dealing with Dynamic scroll or we can't fit the who keyset.
Rem         Make a guess as to how big the keyset is by multiplying the "asked for"
Rem         fetch size by some arbitrary number (we chose 10).
Rem Fetch the first batch of rows
Rem

	Vscroll1.SmallChange = NumRowsInCursor%
	Vscroll1.LargeChange = Vscroll1.SmallChange
	Vscroll1.Value = 0
	Vscroll1.Refresh        'Refresh the vertical scrollbar
	CursorSliderValue = 0

	If IntN% <> 0 Then
	    Vscroll1.Max = (ScrollOpt% * IntN%) * 10
	Else
	    If NumRowsInKeyset& > 0 Then
		Vscroll1.Max = NumRowsInKeyset&
	    Else
		Vscroll1.Max = NumRowsInCursor% * 10       'Note: the number 10 is an arbitrary number
	    End If
	End If
	Fetch_First
    Else
	MsgBox "Cursor failed to open.", 0, "Cursor Example"
    End If

End Sub

Function PrepareString (String_In As String) As String

    String_Out$ = ""

    For i% = 1 To Len(String_In)
    If Mid$(String_In, i%, 1) = Chr$(39) Then
	String_Out$ = String_Out$ + Chr$(39) + Chr$(39)
    Else
	String_Out$ = String_Out$ + Mid$(String_In, i%, 1)
    End If
    Next

    PrepareString = String_Out$

End Function

Sub ProcessCursorHeader ()
    
Rem
Rem This routine gets and formats the cursor header
Rem

    TABKEY$ = "    "
    NEWLINE$ = Chr$(13) + Chr$(10)
    colline$ = ""

    For ColCount% = 1 To NumCols%
    tmplen% = CursorColLen&(ColCount%)
    If tmplen% > 256 Then tmplen% = 256
    colname$ = CursorColName$(ColCount%)
    actuallen& = Len(colname$)
    If actuallen& < tmplen% Then
	If ColCount% <> NumCols% Then
	    colline$ = colline$ + colname$ + Space$((tmplen% - actuallen&) + 1) + TABKEY$
	Else
	    colline$ = colline$ + colname$ + Space$((tmplen% - actuallen&) + 1)
	End If
    Else
	If ColCount% <> NumCols% Then
	    colline$ = colline$ + colname$ + TABKEY$
	Else
	    colline$ = colline$ + colname$
	End If

    End If
    Next ColCount%

Rem
Rem Set the COLUMN_LABEL label
Rem

    COLUMN_LABEL.Caption = colline$
End Sub

Sub ProcessCursorRows ()

Rem
Rem This routine gets each of the cursor rows and displays them
Rem

    TABKEY$ = Chr$(9)
    colline$ = ""
    ClearCursorBuffer
    ClearOutputBuffer

Rem    HScroll1.Refresh     'Refresh the horizontal scroll bar

Rem
Rem Set the end of results and keyset values
Rem

    ENDRESULTS% = FTCENDOFRESULTS% + 1
    ENDKEYSET% = FTCENDOFRESULTS% + FTCENDOFKEYSET% + 1

Rem
Rem Get the cursor data based on the row and column
Rem

    For RowCount% = 1 To NumRowsInCursor%
	For ColCount% = 1 To NumCols%
	    ColValue$ = SqlCursorData(CursorHandle%, RowCount%, ColCount%)
	    actuallen& = Len(ColValue$)
	    tmplen% = CursorColLen(ColCount%)
	    If tmplen% > 256 Then tmplen% = 256
	    If actuallen& < tmplen% Then
		If ColCount% <> NumCols% Then
		    DataStr$ = DataStr$ + ColValue$ + Space$((tmplen% - actuallen&) + 1) + TABKEY$
		Else
		    DataStr$ = DataStr$ + ColValue$ + Space$((tmplen% - actuallen&) + 1)
		End If
	    Else
		If ColCount% <> NumCols% Then
		    DataStr$ = DataStr$ + ColValue$ + TABKEY$
		Else
		    DataStr$ = DataStr$ + ColValue$
		End If
	    End If
	    ColValue$ = ""
	Next ColCount%
	OutputData(RowCount% - 1) = DataStr$
	DataStr$ = ""
	testval% = Int(RowStatus&(RowCount% - 1))
	If testval% = ENDRESULTS% Or testval% = ENDKEYSET% Or testval% = FTCENDOFRESULTS% Then
	    Exit For
	End If
    Next RowCount%

End Sub

Sub RetrieveTableNames ()

Rem
Rem Retrieve table names from SQL Server into list box
Rem

    ClearTableList
    Results% = ExecuteSQLCommand("Select name from sysobjects where type = 'U'")
    Do While (SqlResults%(SqlConn%) <> NOMORERESULTS)
	Do While (SqlNextRow(SqlConn%) <> NOMOREROWS)
	    Table_List.AddItem SqlData(SqlConn%, 1)
	Loop
    Loop
    Table_List.Text = Table_List.List(0)
End Sub

Sub Sensitivity_List_Click ()

Rem
Rem Make sure the required data is supplied before enabling the open button
Rem

    If Table_List.ListIndex = -1 Or CC_List.ListIndex = -1 Then
	Open_Button.Enabled = False
    Else
	Open_Button.Enabled = True
    End If

End Sub

Sub Table_List_Click ()

Rem
Rem Make sure the required data is supplied before enabling the open button
Rem
    
    If Sensitivity_List.ListIndex = -1 Or CC_List.ListIndex = -1 Then
	Open_Button.Enabled = False
    Else
	Open_Button.Enabled = True
    End If

End Sub

Sub Update_Button_Click ()

Rem
Rem Get the selected row number
Rem

    Rownum% = Cursor_Buffer.ListIndex + 1
    
    If Rownum% = 0 Then
	Beep
    MsgBox "Select a row to update.", 0, "Cursor Example"
	Exit Sub
    End If
    
Rem
Rem Get column # to update and new value
Rem

    ColNum$ = InputBox$("Number of column to update:", "Update")
    If ColNum$ = "" Then Exit Sub

    Value$ = InputBox$("Update column " + ColNum$ + " with value: ", "Update")
    If Value$ = "" Then Exit Sub

    Table$ = Table_List.Text

Rem
Rem Determine name of column to update
Rem Create the update string
Rem

    Results% = SqlCursorColInfo(CursorHandle%, Val(ColNum$), colname$, Coltype%, ColLen&, UserType%)

    UpdateValue$ = "set " + colname$ + "="
    If Coltype% = SQLCHAR Or Coltype% = SQLVARCHAR Then
       UpdateValue$ = UpdateValue$ + "'" + Value$ + "'"
    Else
	UpdateValue$ = UpdateValue$ + Value$
    End If

Rem
Rem Perform update
Rem

    Results% = SqlCursor(CursorHandle%, CRSUPDATE, Rownum%, Table$, UpdateValue$)

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

Sub VScroll1_Change ()

If Vscroll1.Value = 0 And CursorSliderValue% = 0 Then Exit Sub

Rem
Rem Define <Page Up> and <Page Down> values
Rem Get the current scroll value
Rem

PAGEUP = CursorSliderValue% - Vscroll1.SmallChange
PAGEDOWN = CursorSliderValue% + Vscroll1.SmallChange

x = Vscroll1.Value

Rem
Rem Based on the scroll value, call the appropriate routine
Rem If "Mixed" scroll and scrolling within the keyset, then just do a random
Rem

If x > CursorSliderValue% And x < PAGEDOWN Then
    If x > Vscroll1.SmallChange Then
	Fetch_Random (x)
    Else
	Fetch_Relative (x)
    End If
Else
    If x < CursorSliderValue% And x > PAGEUP Then
	If x > Vscroll1.SmallChange Then
	    Fetch_Random (x)
	Else
	    Fetch_Relative (x)
	End If
    Else

Rem
Rem User is either doing a <Page Down>, <Page Up>, or Dynamic scrolling
Rem

	Select Case x
	    Case Is = PAGEDOWN
		Fetch_Next
	    Case Is = PAGEUP
		Fetch_Previous
	    Case Is > PAGEDOWN
		If ScrollOpt% = CURKEYSET% Then
		    Fetch_Random Int(x)
		Else
		    Fetch_Relative Int(x)
		End If
	    Case Is < PAGEUP
		If ScrollOpt% = CURKEYSET% Then
		    Fetch_Random Int(x)
		Else
		    Fetch_Relative Int(x)
		End If
	End Select
    End If
End If

Rem
Rem Save the current scroll value for next time.
Rem

CursorSliderValue = x


End Sub

