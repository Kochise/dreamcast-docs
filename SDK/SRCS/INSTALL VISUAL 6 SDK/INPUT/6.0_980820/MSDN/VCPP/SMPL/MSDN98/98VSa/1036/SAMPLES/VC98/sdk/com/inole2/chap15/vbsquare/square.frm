VERSION 2.00
Begin Form RotateControl 
   Caption         =   "Rotation Controller"
   ClientHeight    =   1695
   ClientLeft      =   7920
   ClientTop       =   3030
   ClientWidth     =   3795
   Height          =   2070
   Left            =   7875
   LinkTopic       =   "Form1"
   ScaleHeight     =   1695
   ScaleWidth      =   3795
   Top             =   2700
   Width           =   3885
   Begin CommandButton Animate 
      Caption         =   "&Animate..."
      Height          =   495
      Left            =   240
      TabIndex        =   4
      Top             =   960
      Width           =   1095
   End
   Begin TextBox Radius 
      Alignment       =   1  'Right Justify
      Height          =   375
      Left            =   2640
      TabIndex        =   2
      Text            =   "100"
      Top             =   1140
      Width           =   735
   End
   Begin SpinButton RadiusSpin 
      Delay           =   0
      Height          =   375
      Left            =   3360
      Top             =   1140
      Width           =   255
   End
   Begin TextBox Theta 
      Alignment       =   1  'Right Justify
      Height          =   375
      Left            =   2640
      TabIndex        =   3
      Text            =   "0"
      Top             =   600
      Width           =   735
   End
   Begin SpinButton ThetaSpin 
      Delay           =   0
      Height          =   375
      Left            =   3360
      Top             =   600
      Width           =   255
   End
   Begin TextBox Declination 
      Alignment       =   1  'Right Justify
      Height          =   375
      Left            =   2640
      TabIndex        =   1
      Text            =   "0"
      Top             =   120
      Width           =   735
   End
   Begin SpinButton DeclineSpin 
      Delay           =   0
      Height          =   375
      Left            =   3360
      Top             =   120
      Width           =   255
   End
   Begin CommandButton Draw 
      Caption         =   "&Draw"
      Default         =   -1  'True
      Height          =   495
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   1095
   End
   Begin Label RadiusText 
      Alignment       =   1  'Right Justify
      Caption         =   "&Radius"
      Height          =   255
      Left            =   1440
      TabIndex        =   7
      Top             =   1200
      Width           =   1095
   End
   Begin Label TText 
      Alignment       =   1  'Right Justify
      Caption         =   "&Theta"
      Height          =   255
      Left            =   1440
      TabIndex        =   6
      Top             =   660
      Width           =   1095
   End
   Begin Label DText 
      Alignment       =   2  'Center
      Caption         =   "&Declination"
      Height          =   255
      Left            =   1440
      TabIndex        =   5
      Top             =   180
      Width           =   1155
   End
End

Sub Animate_Click ()
    AnimateForm.Show
End Sub

Sub Declination_Change ()
    d = Val(Declination.Text)
    Square.Declination = d / 57.29577951
    Square.Draw
End Sub

Sub DeclineSpin_SpinDown ()
    d = Val(Declination.Text) - 1

    If (d < 0) Then
        d = 0
    End If

    Declination.Text = Str$(d)
End Sub

Sub DeclineSpin_SpinUp ()
    d = Val(Declination.Text) + 1

    If (d > 180) Then
        d = 180
    End If

    Declination.Text = Str$(d)
End Sub

Sub Draw_Click ()
    Square.Declination = Val(Declination.Text) / 57.29577951
    Square.Theta = Val(Theta.Text) / 57.29577951
    Square.Radius = Val(Radius.Text)
    Square.Draw
End Sub

Sub Form_Load ()
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

Sub Form_Unload (Cancel As Integer)
    Set Square = Nothing
End Sub

Sub Radius_Change ()
    r = Val(Radius.Text)
    Square.Radius = r
    Square.Draw
End Sub

Sub RadiusSpin_SpinDown ()
    r = Val(Radius.Text) - 1

    If (r < 0) Then
        r = 0
    End If

    Radius.Text = Str$(r)
    'Square.Radius = r
    'Square.Draw
End Sub

Sub RadiusSpin_SpinUp ()
    r = Val(Radius.Text) + 1

    If (r > 500) Then
        r = 500
    End If

    Radius.Text = Str$(r)
    'Square.Radius = r
    'Square.Draw
End Sub

Sub Theta_Change ()
    th = Val(Theta.Text)
    Square.Theta = th / 57.29577951
    Square.Draw
End Sub

Sub ThetaSpin_SpinDown ()
    th = Val(Theta.Text) - 1

    If (th < 0) Then
        th = 359
    End If

    Theta.Text = Str$(th)
End Sub

Sub ThetaSpin_SpinUp ()
    th = Val(Theta.Text) + 1

    If (th > 359) Then
        th = 0
    End If

    Theta.Text = Str$(th)
End Sub

