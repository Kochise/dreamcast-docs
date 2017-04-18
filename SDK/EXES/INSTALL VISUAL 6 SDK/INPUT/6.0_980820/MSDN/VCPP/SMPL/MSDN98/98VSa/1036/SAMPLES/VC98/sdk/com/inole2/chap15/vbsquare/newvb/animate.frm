VERSION 4.00
Begin VB.Form AnimateForm 
   Caption         =   "Animate"
   ClientHeight    =   1620
   ClientLeft      =   7965
   ClientTop       =   5175
   ClientWidth     =   3735
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   1
      weight          =   700
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   Height          =   2025
   Left            =   7905
   LinkTopic       =   "Form1"
   ScaleHeight     =   1620
   ScaleWidth      =   3735
   Top             =   4830
   Width           =   3855
   Begin VB.TextBox Theta 
      Alignment       =   1  'Right Justify
      Height          =   375
      Left            =   2520
      TabIndex        =   0
      Text            =   "0"
      Top             =   720
      Width           =   735
   End
   Begin VB.Timer Animate 
      Interval        =   1
      Left            =   1380
      Top             =   1140
   End
   Begin VB.CommandButton Stop 
      Caption         =   "S&top"
      Default         =   -1  'True
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   840
      Width           =   1095
   End
   Begin VB.CommandButton Start 
      Caption         =   "&Start"
      Height          =   495
      Left            =   120
      TabIndex        =   3
      Top             =   240
      Width           =   1095
   End
   Begin VB.TextBox Declination 
      Alignment       =   1  'Right Justify
      Height          =   375
      Left            =   2520
      TabIndex        =   1
      Text            =   "0"
      Top             =   240
      Width           =   735
   End
   Begin Spin.SpinButton ThetaSpin 
      Height          =   375
      Left            =   3240
      TabIndex        =   7
      Top             =   720
      Width           =   255
      _version        =   65536
      _extentx        =   450
      _extenty        =   661
      _stockprops     =   73
      delay           =   100
   End
   Begin Spin.SpinButton DeclineSpin 
      Height          =   375
      Left            =   3240
      TabIndex        =   6
      Top             =   240
      Width           =   255
      _version        =   65536
      _extentx        =   450
      _extenty        =   661
      _stockprops     =   73
      delay           =   100
   End
   Begin VB.Label DText 
      Alignment       =   1  'Right Justify
      Caption         =   "&Declination"
      Height          =   255
      Left            =   1440
      TabIndex        =   5
      Top             =   300
      Width           =   975
   End
   Begin VB.Label TText 
      Alignment       =   1  'Right Justify
      Caption         =   "&Theta"
      Height          =   255
      Left            =   1440
      TabIndex        =   4
      Top             =   780
      Width           =   975
   End
End
Attribute VB_Name = "AnimateForm"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim fStart As Integer

Private Sub Animate_Timer()
    If fStart Then
        Square.Declination = Square.Declination + (Val(Declination.Text) / 57.29577951)
        Square.Theta = Square.Theta + (Val(Theta.Text) / 57.29577951)
    
        Square.Draw
    End If
End Sub

Private Sub DeclineSpin_SpinDown()
    d = Val(Declination.Text) - 1

    If (d < 0) Then
        d = 45
    End If

    Declination.Text = Str$(d)
End Sub

Private Sub DeclineSpin_SpinUp()
    d = Val(Declination.Text) + 1

    If (d > 45) Then
        d = 0
    End If

    Declination.Text = Str$(d)
End Sub


Private Sub DeclineSpin_Click()

End Sub

Private Sub Form_Load()
    fStart = False

    Declination.Text = "0"
    Theta.Text = "0"
End Sub

Private Sub Start_Click()
    fStart = True
End Sub

Private Sub Stop_Click()
    fStart = False
End Sub

Private Sub ThetaSpin_SpinDown()
    th = Val(Theta.Text) - 1

    If (th < 0) Then
        th = 45
    End If

    Theta.Text = Str$(th)
End Sub

Private Sub ThetaSpin_SpinUp()
    th = Val(Theta.Text) + 1

    If (th > 45) Then
        th = 0
    End If

    Theta.Text = Str$(th)
End Sub

