VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Begin VB.Form frmPatternFinder 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Pattern Finder - Repeated Object References"
   ClientHeight    =   7470
   ClientLeft      =   3165
   ClientTop       =   1230
   ClientWidth     =   8550
   Icon            =   "frmPatternFinder.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7470
   ScaleWidth      =   8550
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdClear 
      Caption         =   "&Clear"
      Height          =   495
      Left            =   7665
      TabIndex        =   3
      Top             =   1395
      Width           =   870
   End
   Begin VB.CommandButton cmdRun 
      Caption         =   "&Run"
      Height          =   495
      Left            =   7665
      TabIndex        =   2
      Top             =   855
      Width           =   870
   End
   Begin VB.CommandButton cmdRecommend 
      Caption         =   "Get &Recommendations"
      Enabled         =   0   'False
      Height          =   375
      Left            =   6630
      TabIndex        =   12
      Top             =   3915
      Width           =   1845
   End
   Begin VB.TextBox txtRecommend 
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2865
      Left            =   90
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   9
      Top             =   4515
      Width           =   8385
   End
   Begin VB.TextBox txtComment 
      Height          =   315
      Left            =   1875
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      TabIndex        =   6
      Top             =   1545
      Width           =   5730
   End
   Begin VB.ListBox lstProc 
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1110
      Left            =   90
      TabIndex        =   1
      Top             =   315
      Width           =   7515
   End
   Begin VB.CommandButton cmdStep 
      Caption         =   "&Step"
      Default         =   -1  'True
      Height          =   495
      Left            =   7665
      TabIndex        =   4
      Top             =   330
      Width           =   870
   End
   Begin ComctlLib.ListView lvwAnalysis 
      Height          =   1620
      Left            =   75
      TabIndex        =   11
      Top             =   2265
      Width           =   8400
      _ExtentX        =   14817
      _ExtentY        =   2858
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   327680
      SmallIcons      =   "ImageList"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      MouseIcon       =   "frmPatternFinder.frx":0442
      NumItems        =   4
      BeginProperty ColumnHeader(1) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Type"
         Object.Width           =   2118
      EndProperty
      BeginProperty ColumnHeader(2) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   1
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Line"
         Object.Width           =   531
      EndProperty
      BeginProperty ColumnHeader(3) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   2
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Reference"
         Object.Width           =   3175
      EndProperty
      BeginProperty ColumnHeader(4) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   3
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Comment"
         Object.Width           =   5834
      EndProperty
   End
   Begin VB.Label lblTip 
      Alignment       =   1  'Right Justify
      Caption         =   "Note: step through the ListBox; do not manually select a ListItem."
      ForeColor       =   &H8000000D&
      Height          =   195
      Left            =   1485
      TabIndex        =   10
      Top             =   90
      Width           =   6090
   End
   Begin VB.Label lblGeneric 
      Caption         =   "Recommendations:"
      Height          =   210
      Index           =   4
      Left            =   120
      TabIndex        =   8
      Top             =   4290
      Width           =   1680
   End
   Begin VB.Label lblGeneric 
      Alignment       =   1  'Right Justify
      Caption         =   "Comment:"
      Height          =   210
      Index           =   2
      Left            =   135
      TabIndex        =   5
      Top             =   1590
      Width           =   1680
   End
   Begin ComctlLib.ImageList ImageList 
      Left            =   7845
      Top             =   1965
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327680
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   3
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmPatternFinder.frx":045E
            Key             =   "Dim"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmPatternFinder.frx":0778
            Key             =   "Repeated"
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmPatternFinder.frx":0A92
            Key             =   "Object"
         EndProperty
      EndProperty
   End
   Begin VB.Label lblGeneric 
      Caption         =   "Analysis:"
      Height          =   210
      Index           =   1
      Left            =   120
      TabIndex        =   7
      Top             =   2055
      Width           =   1215
   End
   Begin VB.Label lblGeneric 
      Caption         =   "Current Line:"
      Height          =   210
      Index           =   0
      Left            =   90
      TabIndex        =   0
      Top             =   90
      Width           =   1215
   End
End
Attribute VB_Name = "frmPatternFinder"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'------------------------------------------------------
' ExpertAgent
'-------------------
' Author:
'   Valor Whisler
'   highest quality UI and applications development
'   valorw@ix.netcom.com
'------------------------------------------------------

Option Explicit

'<Constant>----------------------------------------
Const xagObjectRef      As String = "Object Ref"
'</Constant>-----------------------------------------

'<Public>------------------------------------------
Public CodeToAnalyze    As String
'</Public>-----------------------------------------

'<Private>-----------------------------------------
Private StepIndex       As Integer
Private LastDimLine     As Integer
Private PrevLines(2)    As String '---- last two previous lines
'</Private>----------------------------------------

Private Sub cmdClear_Click()

    '---- reset controls
    lstProc.ListIndex = -1
    txtComment = ""
    lvwAnalysis.ListItems.Clear
    txtRecommend = ""
    cmdRecommend.Enabled = False
    
    '---- reset modular variables
    StepIndex = -1
    LastDimLine = 0
    PrevLines(0) = ""
    PrevLines(1) = ""
    
    
    cmdStep.SetFocus
    
End Sub

'-------------------------------------------------------
'<Purpose> analyzes the items obtained while stepping
' through the code and makes recommendations for
' modifying it
'-------------------------------------------------------
Private Sub cmdRecommend_Click()
    Dim FoundFirst      As Boolean '---- found the first object reference
    Dim i               As Integer
    Dim CharPos         As Integer
    Dim NumberTimes     As Integer
    Dim FirstLine       As String  '---- the line of the first object ref
    Dim InstanceItem    As ListItem
    Dim ThisSubItem     As String
    Dim FirstObjectRef  As String
    Dim TempStr         As String
    Dim NewCode()       As String
    Const EditPad       As String = "    "

    '---- iterate throught each item
    For Each InstanceItem In lvwAnalysis.ListItems
    
        If (InstanceItem.Text = xagObjectRef) Then
            '---- cache the line of the first ref
            If (Not FoundFirst) Then
                '---- get the object reference to the first dot
                ThisSubItem = InstanceItem.SubItems(2)
                CharPos = InStr(ThisSubItem, ".")
                FirstObjectRef = Left(ThisSubItem, CharPos - 1)
                
                FirstLine = InstanceItem.SubItems(1)
                NumberTimes = 1
                FoundFirst = True
            Else
                NumberTimes = NumberTimes + 1
            End If
            
            '---- add the line to the new code array
            ReDim Preserve NewCode(1 To NumberTimes)
            TempStr = lstProc.List(InstanceItem.SubItems(1) - 1)
            CharPos = InStr(TempStr, FirstObjectRef)
            TempStr = Left(TempStr, CharPos - 1) & Mid(TempStr, CharPos + Len(FirstObjectRef))
            NewCode(NumberTimes) = TempStr
            
        Else  '---- must be the last line; make a recommendation
            If FoundFirst Then Exit For
        End If
        
    Next

    If FoundFirst Then
        TempStr = "A repeating object reference was found to the object: '" & FirstObjectRef & "'" & vbCrLf
        TempStr = TempStr & "This reference was repeated " & NumberTimes & " times" & vbCrLf & vbCrLf
        TempStr = TempStr & "Recommended code changes follow: " & vbCrLf & vbCrLf
        
        '---- create the recommended code
        TempStr = TempStr & EditPad & "With " & FirstObjectRef & vbCrLf
        
        For i = 1 To NumberTimes
            TempStr = TempStr & EditPad & EditPad & NewCode(i) & vbCrLf
        Next
        
        TempStr = TempStr & EditPad & "End With"
        
        txtRecommend = TempStr
    End If

Cleanup:
    Set InstanceItem = Nothing

End Sub

Private Sub cmdRun_Click()
    Dim i As Integer
    
    For i = 0 To lstProc.ListCount - 1
        cmdStep_Click
    Next
    
    If cmdRecommend.Enabled Then cmdRecommend_Click

End Sub

'-------------------------------------------------------
'<Purpose> analyzes the next line
'<Note> This procedures shows a simplistic case of
' parsing each line looking for patterns.
' Actual code parsing will be fairly complex in order
' to accommodate the many possible patterns.
'-------------------------------------------------------
Private Sub cmdStep_Click()
    Dim LineNumber      As Integer
    Dim CurLine         As String
    Dim ThisReference   As String
    Dim WorkingItem     As ListItem
    
    StepIndex = lstProc.ListIndex + 1
    LineNumber = StepIndex + 1
    
    '---- are we done with this proc
    If (StepIndex >= (lstProc.ListCount - 1)) Then
        cmdRecommend.Enabled = True
        GoTo Cleanup
    End If
    
    '---- clear old comment
    txtComment = ""
    
    '---- show the next line
    lstProc.ListIndex = StepIndex
    CurLine = Trim(lstProc.Text)
    
    
    '---- skip various patterns
    If (CurLine = "") Then
        txtComment = "Blank line"
        
        '---- assumption that last "Dim" is followed by a blank line
        If (LastDimLine > 0) Then
            '---- add the last dim reference to the list
            Set WorkingItem = lvwAnalysis.ListItems.Add(, , "Last Dim", , 1)
            WorkingItem.SubItems(1) = LineNumber
            WorkingItem.SubItems(2) = PrevLines(1)
            WorkingItem.SubItems(3) = "useful if adding variable declarations"
            
            '---- reset counter
            LastDimLine = 0
        End If
        
        GoTo CacheLines
    End If
    If (InStr(CurLine, "Public Sub") > 0) Then
        txtComment = "Start of Sub"
        GoTo CacheLines
    End If
    If (InStr(CurLine, "End Sub") > 0) Then
        txtComment = "End of Sub"
        GoTo CacheLines
    End If
    If (InStr(CurLine, "Dim ") > 0) Then
        CurLine = Mid(CurLine, Len("Dim ") + 1)
        CurLine = Left(CurLine, InStr(CurLine, " ") - 1)
        txtComment = "Variable Declaration: " & "[" & CurLine & "]"
        LastDimLine = LineNumber
        GoTo CacheLines
    End If
    If (Left(CurLine, 1) = "'") Then
        txtComment = "Comment Line"
        GoTo CacheLines
    End If
    
    ThisReference = CheckForReference(CurLine)
    If (ThisReference <> "") Then
        '---- add the last dim reference to the list
        Set WorkingItem = lvwAnalysis.ListItems.Add(, , xagObjectRef, , 3)
        WorkingItem.SubItems(1) = LineNumber
        WorkingItem.SubItems(2) = ThisReference
        WorkingItem.SubItems(3) = "reference to an object"
        '---- show the reference
        txtComment = "Object Reference: " & "[" & ThisReference & "]"
    End If
    
CacheLines:
    '---- cache previous lines
    PrevLines(0) = PrevLines(1)
    PrevLines(1) = CurLine

Cleanup:
    Set WorkingItem = Nothing
    
End Sub

Private Sub Form_Load()
    Dim ThisLine    As String
    Dim ThisProc    As String
    Dim CharPos     As String
    
    ThisProc = CodeToAnalyze
    
    Do
        CharPos = InStr(ThisProc, vbCrLf)
        If (CharPos = 0) Then Exit Do
        ThisLine = Left(ThisProc, CharPos - 1)
        ThisProc = Mid(ThisProc, CharPos + 2)
        lstProc.AddItem ThisLine
    Loop
    
    lstProc.AddItem ThisProc
    
End Sub

'----------------------------------------------------------
'<Purpose> checks the current line for an object reference
'<Note> This procedures looks for an object reference at
' the beggining of a line. There are other ways and places
' to reference objects that this logic would not catch.
'----------------------------------------------------------
Private Function CheckForReference(CurLine As String) As String
    Dim i           As Integer
    Dim DotPos      As Integer
    Dim CharCount   As Integer
    Dim LeftDot     As String
    Dim RightDot    As String
    Dim ThisChar    As String

    '---- looking for properties or methods of an object
    DotPos = InStr(CurLine, ".")
    If (DotPos = 0) Then Exit Function
    
    '---- get everything to the left of the dot
    For i = (DotPos - 1) To 1 Step -1
        ThisChar = Mid(CurLine, i, 1)
        Select Case Asc(ThisChar)
            Case 65 To 90  '---- uppercase A-Z
                CharCount = CharCount + 1
            Case 97 To 122 '---- lowercase a-z
                CharCount = CharCount + 1
            Case Else      '---- any other character
                LeftDot = Mid(CurLine, i + 1, CharCount)
                Exit For
        End Select
    Next
    
    '---- reference began at beggining of line
    If (CharCount = Len(Left(CurLine, DotPos - 1))) Then
        LeftDot = Left(CurLine, DotPos - 1)
    End If
    
    CharCount = 0
    '---- get everything to the right of the dot
    For i = (DotPos + 1) To Len(CurLine)
        ThisChar = Mid(CurLine, i, 1)
        Select Case Asc(ThisChar)
            Case 65 To 90  '---- uppercase A-Z
                CharCount = CharCount + 1
            Case 97 To 122 '---- lowercase a-z
                CharCount = CharCount + 1
            Case 46        '---- another dot operator
                CharCount = CharCount + 1
            Case Else      '---- any other character
                RightDot = Mid(CurLine, DotPos + 1, CharCount)
                Exit For
        End Select
    Next

    CheckForReference = LeftDot & "." & RightDot

End Function
