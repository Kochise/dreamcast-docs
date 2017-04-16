VERSION 5.00
Begin VB.Form frmAbout 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "À propos de"
   ClientHeight    =   3855
   ClientLeft      =   1305
   ClientTop       =   1485
   ClientWidth     =   6000
   Icon            =   "frmabout.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3855
   ScaleWidth      =   6000
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdOk 
      Cancel          =   -1  'True
      Caption         =   "O&k"
      Default         =   -1  'True
      Height          =   375
      Left            =   4800
      TabIndex        =   3
      Top             =   3300
      Width           =   945
   End
   Begin VB.Label Label3 
      Caption         =   $"frmabout.frx":000C
      Height          =   1575
      Left            =   240
      TabIndex        =   2
      Top             =   1620
      Width           =   5475
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00FF0000&
      X1              =   240
      X2              =   5760
      Y1              =   720
      Y2              =   720
   End
   Begin VB.Label Label2 
      Caption         =   $"frmabout.frx":01FC
      Height          =   855
      Left            =   240
      TabIndex        =   1
      Top             =   780
      Width           =   5475
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   " Ceci est une démonstration des capacités d'accès aux données des contrôles standard ListBox et ComboBox."
      Height          =   495
      Left            =   600
      TabIndex        =   0
      Top             =   120
      Width           =   4635
   End
End
Attribute VB_Name = "frmAbout"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdOk_Click()
    Unload Me
End Sub



Private Sub Form_Load()
    '
    ' Centre la feuille.
    '
    Me.Move (Screen.Width - Me.Width) / 2, (Screen.Height - Me.Height) / 2

End Sub
