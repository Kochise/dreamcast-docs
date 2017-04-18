VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "OCBSamp"
   ClientHeight    =   3645
   ClientLeft      =   1050
   ClientTop       =   1800
   ClientWidth     =   8265
   Height          =   4335
   Left            =   990
   LinkTopic       =   "Form1"
   ScaleHeight     =   3645
   ScaleWidth      =   8265
   Top             =   1170
   Width           =   8385
   Begin VB.CommandButton Properties 
      Caption         =   "Properties..."
      Height          =   375
      Left            =   4800
      TabIndex        =   7
      Top             =   840
      Width           =   1575
   End
   Begin VB.CommandButton SaveProperties 
      Caption         =   "Save Properties"
      Height          =   375
      Left            =   6600
      TabIndex        =   6
      Top             =   840
      Width           =   1455
   End
   Begin VB.CommandButton Display 
      Caption         =   "Display ->"
      Height          =   735
      Left            =   3480
      TabIndex        =   5
      Top             =   1200
      Width           =   1215
   End
   Begin VB.TextBox CommentsEdit 
      Height          =   1575
      Left            =   4800
      TabIndex        =   1
      Top             =   1680
      Width           =   3255
   End
   Begin VB.ListBox FileList 
      Height          =   3150
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   3135
   End
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   3480
      Top             =   240
      _Version        =   65536
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin VB.Label Label2 
      Caption         =   "Comments Property:"
      Height          =   255
      Left            =   4800
      TabIndex        =   4
      Top             =   1440
      Width           =   1575
   End
   Begin VB.Label PropFileName 
      Height          =   495
      Left            =   5640
      TabIndex        =   3
      Top             =   240
      Width           =   2415
   End
   Begin VB.Label Label1 
      Caption         =   "Filename:"
      Height          =   255
      Left            =   4800
      TabIndex        =   2
      Top             =   240
      Width           =   735
   End
   Begin VB.Menu File 
      Caption         =   "&File"
      Begin VB.Menu New 
         Caption         =   "&New"
      End
      Begin VB.Menu Open 
         Caption         =   "&Open..."
         Shortcut        =   ^O
      End
      Begin VB.Menu Close 
         Caption         =   "&Close"
      End
      Begin VB.Menu Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu Save 
         Caption         =   "&Save"
         Shortcut        =   ^S
      End
      Begin VB.Menu SaveAs 
         Caption         =   "Save &As..."
      End
      Begin VB.Menu Sep2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuProperties 
         Caption         =   "Propert&ies..."
      End
      Begin VB.Menu Sep3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuPostToExchange 
         Caption         =   "Post To &Exchange Folder"
      End
      Begin VB.Menu Sep4 
         Caption         =   "-"
      End
      Begin VB.Menu Exit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu View 
      Caption         =   "&View"
      Begin VB.Menu DocProperties 
         Caption         =   "Properties..."
      End
   End
   Begin VB.Menu Insert 
      Caption         =   "&Insert"
      Begin VB.Menu InsertFile 
         Caption         =   "&File..."
      End
   End
   Begin VB.Menu Tools 
      Caption         =   "&Tools"
      Begin VB.Menu mnuAutoCorrect 
         Caption         =   "&AutoCorrect..."
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim fCommentsChanged As Boolean

'Global Objects
Dim OC As Object
Dim Outlook As Object
Dim AutoCorrect As Object

' Per File Objects
Dim strOCFileName As String
Dim DocProps As Object
Dim BuiltInDocProps As Object
Dim JournalEntry As Object


Private Sub ClearAll()
    CloseJournal
    ClearDocProps
    FileList.Clear
    strOCFileName = ""
    Form1.Caption = "OfficeCompatible Sample App"
End Sub

Private Sub ClearDocProps()
    PropFileName.Caption = ""
    CommentsEdit.Text = ""
End Sub


Private Sub CloseJournal()
    If Not JournalEntry Is Nothing Then
        If DocProps Is Nothing Then
            JournalEntry.Close
        Else
            JournalEntry.Close DocProps
        End If
        
        Set JournalEntry = Nothing
    End If
End Sub

Private Sub SaveFile(strFileName)
    If (strFileName <> "") Then
        Open strOCFileName For Output Shared As #1
        Write #1, "Office Compatible Sample Data"
        For i = 0 To FileList.ListCount - 1
            Write #1, FileList.List(i)
        Next
        Write #1, ' Blank line at end of file names
        
        ' BUG: Save Routing Slip Info here
        
        ' Close before reopening in another mode.
        Close #1
    End If
End Sub

Private Sub Close_Click()
    CloseJournal ' this is actually done in ClearAll, but for completeness sake...
    ClearAll
End Sub

Private Sub CommentsEdit_Change()
    fCommentsChanged = True
    
    If AutoCorrect Is Nothing Then Exit Sub
    
    result = AutoCorrect.Correct(CommentsEdit.Text)
    If (result <> "") Then
        CommentsEdit.Text = result
        CommentsEdit.SelStart = Len(result)
    End If

End Sub

Private Sub CommentsEdit_GotFocus()
    fCommentsChanged = False
End Sub


Private Sub CommentsEdit_LostFocus()
    If fCommentsChanged = False Then Exit Sub ' nothing changed
    
    If BuiltInDocProps Is Nothing Then Exit Sub ' no document properties
    
    BuiltInDocProps(5).Value = CommentsEdit.Text
End Sub


Private Sub Display_Click()
    PropFileName.Caption = FileList.List(FileList.ListIndex)
    
    If OC Is Nothing Or PropFileName.Caption = "" Then Exit Sub
    
    On Error Resume Next
    Set DocProps = OC.CreateDocProps(PropFileName.Caption)
    If (Err.Number <> 0) Then Set DocProps = Nothing
    On Error GoTo 0
    
    If DocProps Is Nothing Then Exit Sub
    
    ' got a doc property
    Set BuiltInDocProps = DocProps.BuiltInDocumentProperties
    CommentsEdit.Text = BuiltInDocProps(5).Value
    
End Sub

Private Sub DocProperties_Click()
    Properties_Click
End Sub

Private Sub Exit_Click()
    End
End Sub

Private Sub FileList_KeyDown(KeyCode As Integer, Shift As Integer)
    If KeyCode = vbKeyBack Or KeyCode = vbKeyDelete Then
        FileList.RemoveItem FileList.ListIndex
    End If
End Sub


Private Sub Form_Load()
    Set OC = CreateObject("OfficeCompatible.Application")
    
    If OC Is Nothing Then Exit Sub
    
    On Error Resume Next
    OC.init "OCBSamp", "Office Compatible Basic Sample App"
    If (Err.Number <> 0) Then
        Set OC = Nothing
        On Error GoTo 0
        Exit Sub
    End If
        
    On Error GoTo 0
    
    Set Outlook = OC.Outlook
    If Not Outlook Is Nothing Then
        Outlook.Logging = True
    End If
    
    Set AutoCorrect = OC.AutoCorrect
    If Not AutoCorrect Is Nothing Then
        AutoCorrect.ReplaceText = True ' Turn on
    End If
    
End Sub

Private Sub InsertFile_Click()
    CommonDialog.Filter = "All Files (*.*)|*.*"
    CommonDialog.ShowOpen
    
    If CommonDialog.filename <> "" Then
        FileList.AddItem CommonDialog.filename
    End If
End Sub


Private Sub Label3_Click()

End Sub

Private Sub mnuAutoCorrect_Click()
    If AutoCorrect Is Nothing Then Exit Sub
    
    AutoCorrect.ShowDialog
End Sub

Private Sub mnuPostToExchange_Click()
    If OC Is Nothing Then Exit Sub
    
    If strOCFileName = "" Then
        MsgBox "You must Save the document first."
        Exit Sub
    End If
    
    If OC.CanPostDocument = False Then
        MsgBox "Unable to post document to Exchange."
        Exit Sub
    End If
    
    On Error Resume Next
    OC.PostDocument strOCFileName
    On Error GoTo 0
End Sub

Private Sub mnuProperties_Click()
    Properties_Click
End Sub


Private Sub New_Click()
    ClearAll
    
    If Not Outlook Is Nothing Then
        Set JournalEntry = Outlook.CreateJournalEntry
    End If
End Sub


Private Sub Open_Click()
    CommonDialog.Filter = "OCSample Files (*.ocs)|*.ocs"
    CommonDialog.ShowOpen
    
    ClearAll
    
    strOCFileName = CommonDialog.filename
    Form1.Caption = strOCFileName
    
    If strOCFileName <> "" Then
        Open strOCFileName For Input Shared As #1
        
        Input #1, TitleString ' Office Compatible Sample Data
        
        Do
            Input #1, strFileName
            If strFileName <> "" Then
                FileList.AddItem strFileName
            End If
        Loop Until strFileName = ""
        
        ' BUG: Load Routing Slip Info here
        
        ' Close before reopening in another mode.
        Close #1
        
    End If
    
    If Not Outlook Is Nothing Then
        Set JournalEntry = Outlook.CreateJournalEntry(strOCFileName)
    End If
    
End Sub


Private Sub Properties_Click()
    If Not (IsNull(DocProps) Or DocProps Is Nothing) Then
        DocProps.ShowDlg
        CommentsEdit.Text = BuiltInDocProps(5).Value
    End If
End Sub

Private Sub Save_Click()
    If (strOCFileName = "") Then
        CommonDialog.filename = strOCFileName
        CommonDialog.ShowSave
        strOCFileName = CommonDialog.filename
    End If
    
    If Not JournalEntry Is Nothing Then
        JournalEntry.Save
    End If
    
    SaveFile (strOCFileName)
End Sub

Private Sub SaveAs_Click()
    CommonDialog.filename = strOCFileName
    CommonDialog.ShowSave
    strOCFileName = CommonDialog.filename
    
    JournalEntry.SaveAs strFileName
    
    SaveFile strFileName
End Sub

Private Sub SaveProperties_Click()
    If DocProps Is Nothing Then Exit Sub
    
    DocProps.Save
End Sub


