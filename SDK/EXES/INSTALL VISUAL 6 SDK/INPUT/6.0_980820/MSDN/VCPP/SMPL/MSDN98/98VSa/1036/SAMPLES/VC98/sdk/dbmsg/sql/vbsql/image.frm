VERSION 2.00
Begin Form PrimaryWindow 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Image"
   ControlBox      =   0   'False
   ForeColor       =   &H00000000&
   Height          =   7035
   Icon            =   IMAGE.FRX:0000
   Left            =   615
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   6345
   ScaleWidth      =   6990
   Top             =   75
   Width           =   7110
   Begin PictureBox Image_Control 
      Height          =   3495
      Left            =   120
      ScaleHeight     =   3465
      ScaleWidth      =   6705
      TabIndex        =   12
      Top             =   2760
      Width           =   6735
   End
   Begin VBSQL VBSQL1 
      Caption         =   "SQL Err/Msg"
      Height          =   272
      Left            =   4800
      Top             =   2505
      Visible         =   0   'False
      Width           =   2055
   End
   Begin ListBox Titles_List 
      Height          =   810
      Left            =   135
      TabIndex        =   8
      Top             =   1440
      Width           =   2055
   End
   Begin DirListBox Dir_Tree_Combo 
      Height          =   1275
      Left            =   2520
      TabIndex        =   4
      Top             =   1170
      Width           =   2055
   End
   Begin FileListBox Image_File_List 
      Height          =   1590
      Left            =   4800
      Pattern         =   "*.bmp"
      TabIndex        =   5
      Top             =   855
      Width           =   2055
   End
   Begin DriveListBox Drive_Combo 
      Height          =   357
      Left            =   2528
      TabIndex        =   3
      Top             =   833
      Width           =   2048
   End
   Begin ListBox Database_List 
      Height          =   420
      Left            =   135
      TabIndex        =   10
      Top             =   360
      Width           =   2055
   End
   Begin TextBox Title_Edit 
      Height          =   323
      Left            =   3855
      TabIndex        =   1
      Top             =   75
      Width           =   3000
   End
   Begin Label Label5 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Image in database:"
      Height          =   225
      Left            =   120
      TabIndex        =   11
      Top             =   2520
      Width           =   2055
   End
   Begin Label Label4 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Titles in database:"
      Height          =   225
      Left            =   120
      TabIndex        =   9
      Top             =   1200
      Width           =   2055
   End
   Begin Label Image_File_Label 
      BackColor       =   &H00C0C0C0&
      Caption         =   "(none)"
      Height          =   255
      Left            =   3000
      TabIndex        =   7
      Top             =   500
      Width           =   3840
   End
   Begin Label Label3 
      BackColor       =   &H00C0C0C0&
      Caption         =   "File:"
      Height          =   255
      Left            =   2520
      TabIndex        =   6
      Top             =   500
      Width           =   375
   End
   Begin Label Label2 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Image file title:"
      ForeColor       =   &H00000000&
      Height          =   225
      Left            =   2520
      TabIndex        =   2
      Top             =   120
      Width           =   1335
   End
   Begin Label Label1 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Databases:"
      Height          =   210
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2085
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
         Caption         =   "&View Image"
      End
      Begin Menu Insert_Selection 
         Caption         =   "&Insert Image"
      End
      Begin Menu Delete_Selection 
         Caption         =   "&Delete Image"
      End
   End
   Begin Menu About_Menu 
      Caption         =   "&About"
   End
End

Sub About_Menu_Click ()

    About_Form.Show 1

End Sub

Function CheckForImageTable () As Integer

Rem
Rem Check to see if sample table exits
Rem If it's not there, then see if they want to create it
Rem

    Results% = ExecuteSQLCommand("Select count(*) from sysobjects where name = 'image_table'")
    Do While (SqlResults%(SqlConn%) <> NOMORERESULTS)
	Do While (SqlNextRow(SqlConn%) <> NOMOREROWS)
	    Table_Found$ = Sqldata(SqlConn%, 1)
	Loop
    Loop
	
    If Val(Table_Found$) = 0 Then
	Results% = MsgBox("Text table not found in " + Database$ + " database." + Chr$(13) + Chr$(10) + "Do you wish to create the table?", 52)
	If Results% = 7 Then
	    CheckForImageTable = FAIL
	    Exit Function
	Else
	    Cmd$ = "create table image_table (title varchar(30) not null, image_col image null)"
	    Results% = SqlCmd(SqlConn%, Cmd$)
	    Results% = SqlExec(SqlConn%)
	    Do While (SqlResults%(SqlConn%) <> NOMORERESULTS)
		Do While (SqlNextRow(SqlConn%) <> NOMOREROWS)
		Loop
	    Loop
	    CheckForImageTable = SUCCEED
	End If
    Else
	CheckForImageTable = SUCCEED
    End If

End Function

Sub ClearImageTitles ()

    Rem Clear all text titles out of list box
    Do While Titles_List.ListCount
	Titles_List.RemoveItem 0
    Loop

End Sub

Sub Database_List_Click ()

Rem
Rem This procedure gets the chosen database.
Rem Checks to see if the image table is there
Rem If it's not, then clear the images field, and disable other fields
Rem If it is, then get the list of images, display the list and enable other fields.
Rem

    DatabaseSelection$ = Database_List.Text
    Results% = SqlUse(SqlConn%, DatabaseSelection$)
    Results% = CheckForImageTable()
    If Results% = SUCCEED Then
	PrimaryWindow.MousePointer = 11
	RetrieveImageTitles
	View_Selection.Enabled = True
	Insert_Selection.Enabled = True
	Delete_Selection.Enabled = True
	PrimaryWindow.MousePointer = 0
    Else
	ClearImageTitles
	View_Selection.Enabled = False
	Insert_Selection.Enabled = False
	Delete_Selection.Enabled = False
    End If

Rem
Rem Change the primary window title to show the database name
Rem Clear the image control
Rem

    DatabaseName$ = SQLName(SqlConn%)
    ChangePrimaryWindowCaption
    Image_Control.Picture = LoadPicture()

End Sub

Sub Delete_Selection_Click ()

    Image_Title$ = Titles_List.Text

    If Image_Title$ = "" Then
	Beep
	MsgBox "You must first select a title."
    Else
	Response% = MsgBox("Delete " + Image_Title$ + "?", 49)
	If Response% = 1 Then
	    PrimaryWindow.MousePointer = 11
	    Results% = ExecuteSQLCommand("Delete from image_table where title = '" + Image_Title$ + "'")
	    Results% = SqlResults%(SqlConn%)
	    Do While (SqlNextRow(SqlConn%) <> NOMOREROWS)
	    Loop
	    Image_Control.Picture = LoadPicture()
	    RetrieveImageTitles
	    PrimaryWindow.MousePointer = 0
	Else
	    MsgBox "Delete aborted."
	End If
    End If

End Sub

Sub Dir_Tree_Combo_Change ()

    Image_File_Label.Caption = "(none)"
    Image_File_List.Path = Dir_Tree_Combo.Path

End Sub

Sub Drive_Combo_Change ()

    Image_File_Label.Caption = "(none)"
    Dir_Tree_Combo.Path = Drive_Combo.Drive

End Sub

Sub Exit_Selection_Click ()

    ExitApplication
    End

End Sub

Sub Form_Load ()

   Temp_Image_File = "c:\image.tmp"

    PrimaryWindowTitle = "Image Example"
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

Sub Image_File_List_Click ()

    If Right$(Dir_Tree_Combo.Path, 1) = "\" Then
	Image_File_Label.Caption = Dir_Tree_Combo.Path + Image_File_List.FileName
    Else
	Image_File_Label.Caption = Dir_Tree_Combo.Path + "\" + Image_File_List.FileName
    End If

End Sub

Sub Insert_Selection_Click ()

Rem
Rem This routine will insert the image from the file into the database
Rem

    Image_File$ = Image_File_Label.Caption
    Title$ = Title_Edit.Text
    Title$ = PrepareString(Title$)

    If Image_File$ = "(none)" Then
	Beep
	MsgBox "Please select a bitmap to insert."
    ElseIf Title$ = "" Then
	Beep
	MsgBox "Please enter a title for the bitmap you wish to insert."
    Else
	PrimaryWindow.MousePointer = 11
	InsertImage Title$, Image_File$
	Title_Edit.Text = ""
	Image_File_List.ListIndex = -1
	Image_File_Label.Caption = ""
	RetrieveImageTitles
	PrimaryWindow.MousePointer = 0
    End If

End Sub

Sub InsertImage (Title As String, Bitmap_File As String)
    
Rem
Rem This routine inserts an image into the SQL Server
Rem Insert new row with title and image token data
Rem

    Results% = ExecuteSQLCommand("Insert into image_table values ('" + Title + "',0x80)")
    Do While SqlResults(SqlConn%) <> NOMORERESULTS%
	Do While SqlNextRow(SqlConn%) <> NOMOREROWS%
	Loop
    Loop

Rem Get identifier for image column in current row

    Results% = ExecuteSQLCommand("select image_col from image_table where title = '" + Title + "'")
    Do While SqlResults(SqlConn%) <> NOMORERESULTS%
	Do While SqlNextRow(SqlConn%) <> NOMOREROWS%
	    SqlPointer$ = SqlTxPtr(SqlConn%, 1)
	    SqlTimestamp$ = SqlTxTimeStamp(SqlConn%, 1)
	Loop
    Loop

Rem Open bitmap file to load into SQL Server table

    Open Bitmap_File For Binary As #1
    FileLength& = LOF(1)
    
Rem Begin inserting bitmap into image column in DatePartLimit& size chunks

    Table$ = "image_table.image_col"
    DataPartLimit& = 4096
    DataPartSize& = 0
    If SqlWriteText(SqlConn%, Table$, SqlPointer$, SQLTXPLEN%, SqlTimestamp$, 1, FileLength&, "") <> FAIL% Then
	If SqlOk(SqlConn%) <> FAIL% Then
	    Results% = SqlResults(SqlConn%)
	    Done% = False
	    Do While Not Done%
		DataPart$ = Input$(DataPartLimit&, 1)
		DataPartSize& = DataPartSize& + Len(DataPart$)
		Results% = SqlMoreText%(SqlConn%, Len(DataPart$), DataPart$)
		If DataPartSize& = FileLength& Then
		    Done% = True
		End If
	    Loop
	    If SqlOk(SqlConn%) <> FAIL% Then
		If SqlResults(SqlConn%) <> FAIL% Then
		    MsgBox "Image inserted."
		End If
	    End If
	End If
    End If

Close 1

End Sub

Sub LoadImage (Title As String)
    
Rem
Rem This routine reads an image from the SQL Server
Rem Get length of bitmap image in image column
Rem

    Results% = ExecuteSQLCommand("select datalength(image_col) from image_table where title = '" + Title + "'")
    Do While SqlResults(SqlConn%) <> NOMORERESULTS
	Do While SqlNextRow(SqlConn%) <> NOMOREROWS
	    ImageLen& = Val(Sqldata(SqlConn%, 1))
	Loop
    Loop

    Offset& = 0
	
Rem Set LoadSizeLimit to 8K

    LoadSizeLimit& = 4096
    If LoadSizeLimit& > ImageLen& Then
	LoadSizeLimit& = ImageLen&
    End If
    
    LoadSize& = LoadSizeLimit&

Rem Set size of image returned to LoadSizeLimit&

    Results% = ExecuteSQLCommand("set textsize " + Str$(LoadSizeLimit&))
    Do While SqlResults(SqlConn%) <> NOMORERESULTS
	Do While SqlNextRow(SqlConn%) <> NOMOREROWS
	Loop
    Loop

Rem Begin reading image column in LoadSizeLimit& size chunks

    Cmd$ = "Declare @val varbinary(30)"
    Results% = SqlCmd(SqlConn%, Cmd$)
    Cmd$ = "Select @val = textptr(image_col) from image_table where title = '" + Title + "'"
    Results% = SqlCmd(SqlConn%, Cmd$)
    Table$ = "image_table.image_col"
    Done% = False
    Do While Not Done%
	Cmd$ = "READTEXT " + Table$ + " @val " + Str$(Offset&) + " " + Str$(LoadSize&)
	Results% = SqlCmd(SqlConn%, Cmd$)
	If Offset& + LoadSize& = ImageLen& Then
	    Done% = True
	Else
	    Offset& = Offset& + LoadSizeLimit&
	    If Offset& + LoadSizeLimit& > ImageLen& Then
		LoadSize& = ImageLen& - Offset&
	    End If
	End If
    Loop

Rem Retrieve image data in result rows and write to temporary bitmap file
    
    If SqlExec(SqlConn%) <> FAIL% Then
	Open Temp_Image_File For Binary As #1
	filepos& = 1
	Do While SqlResults(SqlConn%) <> NOMORERESULTS
	    Do While SqlNextRow(SqlConn%) <> NOMOREROWS
		in$ = Sqldata(SqlConn%, 1)
		Put 1, filepos&, in$
		filepos& = filepos& + Len(in$)
	    Loop
	Loop
	Close 1
    End If

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
	Results% = GetDatabases(Database_List)
	ChangePrimaryWindowCaption
	Logon_Selection.Enabled = False
	Log_Off_Selection.Enabled = True
    End If
    PrimaryWindow.MousePointer = 0

End Sub

Function PrepareString (String_In As String) As String

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

Sub RetrieveImageTitles ()

    ClearImageTitles
    Rem Retrieve text titles from SQL Server into list box
    Results% = ExecuteSQLCommand("Select title from image_table")
    Do While (SqlResults%(SqlConn%) <> NOMORERESULTS)
	Do While (SqlNextRow(SqlConn%) <> NOMOREROWS)
	    Titles_List.AddItem Sqldata(SqlConn%, 1)
	Loop
    Loop

End Sub

Sub Title_Edit_KeyPress (KeyAscii As Integer)

    If Len(Title_Edit.Text) = 30 Then
	If KeyAscii <> 8 Then
	    KeyAscii = 0
	End If
    End If
    
End Sub

Sub Titles_List_Click ()

Rem
Rem Clear the picture
Rem

    Image_Control.Picture = LoadPicture()

End Sub

Sub Titles_List_DblClick ()

Rem
Rem Get the image image selected from the server
Rem Display the image
Rem


    Image_Title$ = Titles_List.Text
    PrimaryWindow.MousePointer = 11
    LoadImage Image_Title$
    Image_Control.Picture = LoadPicture(Temp_Image_File)
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

    Image_Title$ = Titles_List.Text
    If Image_Title$ = "" Then
	Beep
	MsgBox "You must first select a title."
    Else
	PrimaryWindow.MousePointer = 11
	LoadImage Image_Title$
	Image_Control.Picture = LoadPicture(Temp_Image_File)
	PrimaryWindow.MousePointer = 0
    End If

End Sub

