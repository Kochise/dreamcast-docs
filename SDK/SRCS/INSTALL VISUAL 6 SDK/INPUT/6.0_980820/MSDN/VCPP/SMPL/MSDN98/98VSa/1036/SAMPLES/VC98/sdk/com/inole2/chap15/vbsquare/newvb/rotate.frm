VERSION 4.00
Begin VB.Form RotateControl 
   Caption         =   "Rotation Controller"
   ClientHeight    =   1695
   ClientLeft      =   7920
   ClientTop       =   3030
   ClientWidth     =   3795
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   1
      weight          =   700
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   Height          =   2100
   Left            =   7860
   LinkTopic       =   "Form1"
   ScaleHeight     =   1695
   ScaleWidth      =   3795
   Top             =   2685
   Width           =   3915
   Begin VB.CommandButton Animate 
      Caption         =   "&Animate..."
      Height          =   495
      Left            =   240
      TabIndex        =   4
      Top             =   960
      Width           =   1095
   End
   Begin VB.TextBox Radius 
      Alignment       =   1  'Right Justify
      Height          =   375
      Left            =   2640
      TabIndex        =   2
      Text            =   "100"
      Top             =   1140
      Width           =   735
   End
   Begin VB.TextBox Theta 
      Alignment       =   1  'Right Justify
      Height          =   375
      Left            =   2640
      TabIndex        =   3
      Text            =   "0"
      Top             =   600
      Width           =   735
   End
   Begin VB.TextBox Declination 
      Alignment       =   1  'Right Justify
      Height          =   375
      Left            =   2640
      TabIndex        =   1
      Text            =   "0"
      Top             =   120
      Width           =   735
   End
   Begin VB.CommandButton Draw 
      Caption         =   "&Draw"
      Default         =   -1  'True
      Height          =   495
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   1095
   End
   Begin Spin.SpinButton RadiusSpin 
      Height          =   375
      Left            =   3360
      TabIndex        =   8
      Top             =   1140
      Width           =   255
      _version        =   65536
      _extentx        =   450
      _extenty        =   661
      _stockprops     =   73
      forecolor       =   -2147483640
      backcolor       =   -2147483643
      delay           =   0
   End
   Begin Spin.SpinButton ThetaSpin 
      Height          =   375
      Left            =   3360
      TabIndex        =   9
      Top             =   600
      Width           =   255
      _version        =   65536
      _extentx        =   450
      _extenty        =   661
      _stockprops     =   73
      forecolor       =   -2147483640
      backcolor       =   -2147483643
      delay           =   0
   End
   Begin Spin.SpinButton DeclineSpin 
      Height          =   375
      Left            =   3360
      TabIndex        =   10
      Top             =   120
      Width           =   255
      _version        =   65536
      _extentx        =   450
      _extenty        =   661
      _stockprops     =   73
      forecolor       =   -2147483640
      backcolor       =   -2147483643
      delay           =   0
   End
   Begin VB.Label RadiusText 
      Alignment       =   1  'Right Justify
      Caption         =   "&Radius"
      Height          =   255
      Left            =   1440
      TabIndex        =   7
      Top             =   1200
      Width           =   1095
   End
   Begin VB.Label TText 
      Alignment       =   1  'Right Justify
      Caption         =   "&Theta"
      Height          =   255
      Left            =   1440
      TabIndex        =   6
      Top             =   660
      Width           =   1095
   End
   Begin VB.Label DText 
      Alignment       =   2  'Center
      Caption         =   "&Declination"
      Height          =   255
      Left            =   1440
      TabIndex        =   5
      Top             =   180
      Width           =   1155
   End
End
Attribute VB_Name = "RotateControl"
Attribute VB_Creatable = False
Attribute VB_Exposed = False

Private Sub Animate_Click()
    AnimateForm.Show
End Sub

Private Sub Declination_Change()
    d = Val(Declination.Text)
    Square.Declination = d / 57.29577951
    Square.Draw
End Sub

Private Sub DeclineSpin_SpinDown()
    d = Val(Declination.Text) - 1

    If (d < 0) Then
        d = 0
    End If

    Declination.Text = Str$(d)
End Sub

Private Sub DeclineSpin_SpinUp()
    d = Val(Declination.Text) + 1

    If (d > 180) Then
        d = 180
    End If

    Declination.Text = Str$(d)
End Sub

Private Sub Draw_Click()
    Square.Declination = Val(Declination.Text) / 57.29577951
    Square.Theta = Val(Theta.Text) / 57.29577951
    Square.Radius = Val(Radius.Text)
    Square.Draw
End Sub

Private Sub Form_Load()
    Set Square = CreateObject("SphereSquare.Object")
    Declination.Text = Str$(Square.Declination)
    Theta.Text = Str$(Square.Theta)
    Radius.Text = Str$(Square.Radius)

    Square.BackColor = RGB(0, 0, 0)
    Square.LineColorPositive = RGB(255, 255, 0)
    Square.LineColorNegative = RGB(0, 255, 0)

    Square.SetWindowPosition 100, 100
    Square.SetWindowSize 300, 300
    Square.ShowWindow (SW_SHOW)
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Set Square = Nothing
End Sub

Private Sub Radius_Change()
    r = Val(Radius.Text)
    Square.Radius = r
    Square.Draw
End Sub

Private Sub RadiusSpin_SpinDown()
    r = Val(Radius.Text) - 1

    If (r < 0) Then
        r = 0
    End If

    Radius.Text = Str$(r)
    'Square.Radius = r
    'Square.Draw
End Sub

Private Sub RadiusSpin_SpinUp()
    r = Val(Radius.Text) + 1

    If (r > 500) Then
        r = 500
    End If

    Radius.Text = Str$(r)
    'Square.Radius = r
    'Square.Draw
End Sub

Private Sub Theta_Change()
    th = Val(Theta.Text)
    Square.Theta = th / 57.29577951
    Square.Draw
End Sub

Private Sub ThetaSpin_SpinDown()
    th = Val(Theta.Text) - 1

    If (th < 0) Then
        th = 359
    End If

    Theta.Text = Str$(th)
End Sub

Private Sub ThetaSpin_SpinUp()
    th = Val(Theta.Text) + 1

    If (th > 359) Then
        th = 0
    End If

    Theta.Text = Str$(th)
End Sub

