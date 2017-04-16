VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   1395
   ClientLeft      =   2400
   ClientTop       =   2535
   ClientWidth     =   2760
   Height          =   1800
   Left            =   2340
   LinkTopic       =   "Form1"
   ScaleHeight     =   1395
   ScaleWidth      =   2760
   Top             =   2190
   Width           =   2880
   Begin VB.CommandButton Command5 
      Caption         =   "&*"
      Height          =   255
      Left            =   2520
      TabIndex        =   5
      Top             =   120
      Width           =   135
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   120
      TabIndex        =   4
      Text            =   "Text1"
      Top             =   120
      Width           =   2415
   End
   Begin VB.CommandButton Command4 
      Caption         =   "&Stop"
      Height          =   375
      Left            =   120
      TabIndex        =   3
      Top             =   960
      Width           =   1095
   End
   Begin VB.CommandButton Command3 
      Caption         =   "&Resume"
      Height          =   375
      Left            =   1440
      TabIndex        =   2
      Top             =   960
      Width           =   1095
   End
   Begin VB.CommandButton Command2 
      Caption         =   "&Pause"
      Height          =   375
      Left            =   1440
      TabIndex        =   1
      Top             =   480
      Width           =   1095
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Read"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   480
      Width           =   1095
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   120
      Top             =   0
      _Version        =   65536
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim Vtxt As New VTxtAuto.VTxtAuto
Dim Word As Word.WordBasic

Private Sub Command1_Click()
Word.FileOpen Name:=Text1.Text
While Not Word.AtEndOfDocument()
With Word
    .PageDown Count:=1, Select:=1
    Word.EditCopy
    A$ = Clipboard.GetText
    If Len(A$) > 0 Then
    Vtxt.Speak pszBuffer:=A$, dwFlags:=VTxtAuto.vtxtst_READING
    End If
    .CharRight Count:=1, Select:=0
    While Vtxt.IsSpeaking()
        If fStop Then Vtxt.StopSpeaking: GoTo Stop_Now
        DoEvents
    Wend
End With
Wend
Stop_Now:
Word.FileClose
End Sub

Private Sub Command2_Click()
Vtxt.AudioPause
End Sub

Private Sub Command3_Click()
Vtxt.AudioResume
End Sub

Private Sub Command4_Click()
fStop = True
End Sub

Private Sub Command5_Click()
CommonDialog1.Flags = cdlOFNFileMustExist
If Len(CommonDialog1.filename) = 0 Then CommonDialog1.filename = "*.doc"
CommonDialog1.Filter = "Documents (*.doc)"
CommonDialog1.Action = 1
Text1 = CommonDialog1.filename
End Sub

Private Sub Form_Load()
Set Word = CreateObject("Word.Basic")
 Vtxt.Register pszSite:="", pszApp:=App.Title
 '
End Sub

Private Sub Form_Unload(Cancel As Integer)
End
End Sub
