VERSION 5.00
Object = "{A8AF3246-AED7-11D0-A771-00A0C90391D3}#1.0#0"; "ATLMovie.dll"
Begin VB.Form Form1 
   BackColor       =   &H00808080&
   Caption         =   "ATL Movie"
   ClientHeight    =   5580
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6900
   LinkTopic       =   "Form1"
   ScaleHeight     =   5580
   ScaleWidth      =   6900
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command4 
      Caption         =   "Reset"
      Height          =   495
      Left            =   5040
      TabIndex        =   4
      Top             =   4680
      Width           =   1335
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Stop"
      Height          =   495
      Left            =   3480
      TabIndex        =   3
      Top             =   4680
      Width           =   1335
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Pause"
      Height          =   495
      Left            =   1920
      TabIndex        =   2
      Top             =   4680
      Width           =   1335
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Play"
      Height          =   495
      Left            =   360
      TabIndex        =   1
      Top             =   4680
      Width           =   1335
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   720
      TabIndex        =   0
      Text            =   "\\deanro1\atlmovie\cybervision.mpg"
      Top             =   4080
      Width           =   3975
   End
   Begin VB.CommandButton Command5 
      Enabled         =   0   'False
      Height          =   1575
      Left            =   120
      TabIndex        =   5
      Top             =   3840
      Width           =   6615
   End
   Begin VB.CommandButton Command6 
      Enabled         =   0   'False
      Height          =   3615
      Left            =   120
      TabIndex        =   6
      Top             =   120
      Width           =   6615
   End
   Begin ATLMOVIELibCtl.MovieCtl Movie 
      Height          =   3135
      Left            =   360
      OleObjectBlob   =   "VBTest.frx":0000
      TabIndex        =   7
      Top             =   360
      Width           =   6135
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    On Error GoTo errClick
    Movie.Play
    Exit Sub
errClick:
    MsgBox "Cannot play movie"
End Sub

Private Sub Command2_Click()
    Movie.Pause
End Sub

Private Sub Command3_Click()
    Movie.Stop
End Sub

Private Sub Command4_Click()
    Movie.Reset
End Sub

Private Sub Text1_LostFocus()
    Movie.filename = Text1
End Sub
