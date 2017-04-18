VERSION 2.00
Begin Form PrimaryWindow 
   BackColor       =   &H00808000&
   Caption         =   "VBSQL Sample Query Tool - [No Server]"
   ForeColor       =   &H00000000&
   Height          =   6120
   Left            =   240
   ScaleHeight     =   5430
   ScaleWidth      =   8760
   Top             =   660
   Width           =   8880
   Begin VBSQL VBSQL1 
      Caption         =   "Errors"
      Height          =   375
      Left            =   2640
      Top             =   0
      Visible         =   0   'False
      Width           =   1815
   End
   Begin CommandButton SEND_QUERY_BUTTON 
      BackColor       =   &H00C0C0C0&
      Caption         =   "&Send Query"
      Enabled         =   0   'False
      Height          =   480
      Left            =   7080
      TabIndex        =   5
      Top             =   960
      Width           =   1440
   End
   Begin CommandButton NEW_QUERY_BUTTON 
      BackColor       =   &H00C0C0C0&
      Caption         =   "&New Query"
      Enabled         =   0   'False
      Height          =   480
      Left            =   7080
      TabIndex        =   4
      Top             =   240
      Width           =   1440
   End
   Begin TextBox RESULT_FIELD 
      BackColor       =   &H00FFFFFF&
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "Courier"
      FontSize        =   9.75
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      ForeColor       =   &H00000000&
      Height          =   3120
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   3
      Top             =   1920
      Width           =   8520
   End
   Begin TextBox QUERY_FIELD 
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H00000000&
      Height          =   960
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   1
      Top             =   480
      Width           =   6480
   End
   Begin Label Label2 
      BackColor       =   &H00808000&
      Caption         =   "&Results:"
      ForeColor       =   &H00000000&
      Height          =   240
      Left            =   120
      TabIndex        =   2
      Top             =   1680
      Width           =   720
   End
   Begin Label Label1 
      BackColor       =   &H00808000&
      Caption         =   "&Query:"
      ForeColor       =   &H00000000&
      Height          =   240
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   720
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
   Begin Menu HELP_MENU 
      Caption         =   "&Help"
      Begin Menu ABOUT_MENU 
         Caption         =   "&About..."
      End
   End
End
'$INCLUDE: 'VBQUERY.BI'
'$INCLUDE: 'VBDSQL.BI'

Sub ABOUT_MENU_Click ()
    About_Form.Show 1
End Sub

Sub ClearFields ()
	QUERY_FIELD.Text = ""
	RESULT_FIELD.Text = ""
End Sub

Sub DATABASE_MENU_Click ()
	If SqlConn = 0 Then
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
	PrimaryWindowTitle = "VBSQL Sample Query Tool"
End Sub

Sub LOGIN_MENU_Click ()
	
	Login.Show 1
	NEW_QUERY_BUTTON.Enabled = -1
	SEND_QUERY_BUTTON.Enabled = -1

End Sub

Sub NEW_QUERY_BUTTON_Click ()
	ClearFields
	QUERY_FIELD.SetFocus
End Sub

Sub SEND_QUERY_BUTTON_Click ()
	
On Error GoTo OutofRoom

Static OutputData() As String
ReDim Preserve OutputData(500) As String

Rem
Rem Get the query.  Make sure there is one
Rem

CRLF$ = Chr$(13) + Chr$(10)

cmd$ = QUERY_FIELD.Text

If cmd$ = "" Then
	MsgBox "There is no query in the Query field"
	Exit Sub
End If

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


'fill temporary string first, to avoid flashing with every row

For i% = 0 To numrows& - 1
	DataLine$ = DataLine$ + OutputData(i%) + CRLF$

Next i%

RESULT_FIELD.Text = DataLine$
QUERY_FIELD.SetFocus

Exit Sub

OutofRoom:
'can run out of space filling strings.  If so, try just 20 rows
DataLine$ = ""
If numrows& > 20 Then
	numrows& = 20

	For i% = 0 To numrows& - 1
		DataLine$ = DataLine$ + OutputData(i%) + CRLF$
	Next i%

	RESULT_FIELD.Text = DataLine$
End If
MsgBox "Out of room, output truncated"
QUERY_FIELD.SetFocus
Exit Sub

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

