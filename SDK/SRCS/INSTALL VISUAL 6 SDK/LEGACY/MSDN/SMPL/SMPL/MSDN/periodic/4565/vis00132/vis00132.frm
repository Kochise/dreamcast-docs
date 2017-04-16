VERSION 4.00
Begin VB.Form Form1 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "VB4/32 Version"
   ClientHeight    =   1650
   ClientLeft      =   2220
   ClientTop       =   4170
   ClientWidth     =   4245
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   0
      weight          =   700
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   Height          =   2055
   Left            =   2160
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   1650
   ScaleWidth      =   4245
   Top             =   3825
   Width           =   4365
   Begin VB.CommandButton btnGetString 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "GetString"
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   1575
   End
   Begin VB.CommandButton btnPowers 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Powers"
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   1080
      Width           =   1575
   End
   Begin VB.CommandButton btnGetStringA 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "GetStringA"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   600
      Width           =   1575
   End
   Begin VB.Label lblPowers 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "(Powers)"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   1800
      TabIndex        =   5
      Top             =   1080
      Width           =   2175
   End
   Begin VB.Label lblGetStringA 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "(GetStringA)"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   1800
      TabIndex        =   4
      Top             =   600
      Width           =   2175
   End
   Begin VB.Label lblGetString 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "(GetString)"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   1800
      TabIndex        =   3
      Top             =   120
      Width           =   2175
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim Obj As New VisThunk.Thunk


Private Sub btnGetString_Click()
    Dim y As String * 32
    y = Obj.GetString(5)
    lblGetString.Caption = y
End Sub

Private Sub btnGetStringA_Click()
    Dim y As String * 32
    i = Obj.GetStringA(y, 14)
    lblGetStringA.Caption = y
End Sub

Private Sub btnPowers_Click()
    Dim z As Double
    z = Obj.Powers(2, 13)
    lblPowers.Caption = z
End Sub

