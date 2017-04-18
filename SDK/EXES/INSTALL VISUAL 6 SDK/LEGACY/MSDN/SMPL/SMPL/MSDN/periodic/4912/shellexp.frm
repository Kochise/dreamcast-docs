VERSION 4.00
Begin VB.Form shellexp 
   Caption         =   "MSJ Browser Demo"
   ClientHeight    =   7635
   ClientLeft      =   525
   ClientTop       =   765
   ClientWidth     =   10725
   Height          =   8340
   Left            =   465
   LinkTopic       =   "Form1"
   ScaleHeight     =   7635
   ScaleWidth      =   10725
   Top             =   120
   Width           =   10845
   Begin VB.CommandButton Command3 
      Caption         =   ">>"
      Height          =   375
      Left            =   1680
      TabIndex        =   4
      Top             =   120
      Width           =   375
   End
   Begin VB.CommandButton Command2 
      Caption         =   "<<"
      Height          =   375
      Left            =   1200
      TabIndex        =   3
      Top             =   120
      Width           =   375
   End
   Begin VB.CommandButton Command1 
      Caption         =   "GoTo"
      Height          =   375
      Left            =   0
      TabIndex        =   2
      Top             =   120
      Width           =   1095
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   2160
      TabIndex        =   1
      Text            =   "Text1"
      Top             =   120
      Width           =   6135
   End
   Begin SHDocVwCtl.ShellExplorer ShellExplorer1 
      Height          =   6975
      Left            =   0
      OleObjectBlob   =   "shellexp.frx":0000
      TabIndex        =   0
      Top             =   600
      Width           =   10695
   End
   Begin VB.Menu mnuFile 
      Caption         =   "File"
      Begin VB.Menu mnuFileExit 
         Caption         =   "Exit"
      End
   End
End
Attribute VB_Name = "shellexp"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Private Sub Command1_Click()
    ShellExplorer1.Location = Text1.Text
End Sub

Private Sub Command2_Click()
    ShellExplorer1.Application.GoBack
End Sub

Private Sub Command3_Click()
    ShellExplorer1.Application.GoForward
End Sub

Private Sub Toolbar1_ButtonClick(ByVal Button As Button)

End Sub
