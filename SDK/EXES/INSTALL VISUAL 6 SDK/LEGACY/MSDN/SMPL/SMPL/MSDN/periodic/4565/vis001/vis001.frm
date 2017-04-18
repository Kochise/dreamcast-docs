VERSION 2.00
Begin Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "VB3 Version"
   ClientHeight    =   1650
   ClientLeft      =   1365
   ClientTop       =   2535
   ClientWidth     =   4245
   Height          =   2085
   Left            =   1305
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   1650
   ScaleWidth      =   4245
   Top             =   2160
   Width           =   4365
   Begin CommandButton btnGetString 
      Caption         =   "GetString"
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   1575
   End
   Begin CommandButton btnPowers 
      Caption         =   "Powers"
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   1080
      Width           =   1575
   End
   Begin CommandButton btnGetStringA 
      Caption         =   "GetStringA"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   600
      Width           =   1575
   End
   Begin Label lblPowers 
      Caption         =   "(Powers)"
      Height          =   255
      Left            =   1800
      TabIndex        =   5
      Top             =   1080
      Width           =   2175
   End
   Begin Label lblGetStringA 
      Caption         =   "(GetStringA)"
      Height          =   255
      Left            =   1800
      TabIndex        =   4
      Top             =   600
      Width           =   2175
   End
   Begin Label lblGetString 
      Caption         =   "(GetString)"
      Height          =   255
      Left            =   1800
      TabIndex        =   3
      Top             =   120
      Width           =   2175
   End
End

Sub btnGetString_Click ()
    Dim stg As Long
    Dim y As String * 32
    stg = GetString(5)

    n = lstrcpy(y, stg)
    lblGetString.Caption = y
End Sub

Sub btnGetStringA_Click ()
    Dim y As String * 32

    i = GetStringA(y, 14)
    lblGetStringA.Caption = y
End Sub

Sub btnPowers_Click ()
    Dim z As Double
    z = Powers(2, 13)
    lblPowers.Caption = z
End Sub

