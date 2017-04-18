VERSION 4.00
Begin VB.Form frmMSDNDemo 
   Caption         =   "Word OLE Server Demo"
   ClientHeight    =   1515
   ClientLeft      =   2460
   ClientTop       =   1845
   ClientWidth     =   4485
   Height          =   2205
   Left            =   2400
   LinkTopic       =   "Form1"
   ScaleHeight     =   1515
   ScaleWidth      =   4485
   Top             =   1215
   Width           =   4605
   Begin VB.TextBox Text1 
      Height          =   975
      Left            =   120
      TabIndex        =   1
      Text            =   "Text1"
      Top             =   0
      Width           =   4335
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Add Comments"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   1080
      Width           =   4335
   End
   Begin VB.Menu mnuAbout 
      Caption         =   "&About"
   End
End
Attribute VB_Name = "frmMSDNDemo"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim ThisWord As Word.WordBasic

Private Sub Command1_Click()
With ThisWord
    .Underline True
    .Insert Format(Now, "HH:NN:SS")
    .Underline False
    .InsertPara
    .Insert Text1.Text
    .InsertPara
End With
End Sub

Private Sub Form_Load()
Set ThisWord = CreateObject("Word.Basic")
With ThisWord
    .AppMaximize
    .FileNewDefault
    .FormatFont _
        Points:=22, _
        Bold:=True, _
        Italic:=True
    .Insert "Welcome to Word OLE Automation"
    .InsertPara
    .FormatFont _
        Points:=10, _
        Bold:=False, _
        Italic:=False
    .Insert "Report Created:"
    .InsertDateTime _
        DateTimePic:="YYYY MM DD HH:MM:SS", _
        InsertAsField:=False
    .InsertPara
End With
End Sub

Private Sub mnuAbout_Click()
MsgBox "Demo from Microsoft Developers Network Library" & vbCr & "Author: Ken Lassesen", VBA.vbInformation, App.Title
End Sub

