VERSION 2.00
Begin Form Progress 
   BorderStyle     =   3  'Fixed Double
   ClientHeight    =   1380
   ClientLeft      =   1110
   ClientTop       =   1470
   ClientWidth     =   5550
   DrawMode        =   10  'Not Xor Pen
   FillColor       =   &H80000008&
   Height          =   1785
   Left            =   1050
   LinkTopic       =   "Form2"
   ScaleHeight     =   1380
   ScaleWidth      =   5550
   Top             =   1125
   Width           =   5670
   Begin CommandButton Cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   315
      Left            =   2100
      TabIndex        =   1
      Top             =   960
      Width           =   1335
   End
   Begin PictureBox PIC_Bar 
      BackColor       =   &H00FFFFFF&
      DrawMode        =   4  'Not Copy Pen
      FillColor       =   &H00FF0000&
      FillStyle       =   0  'Solid
      ForeColor       =   &H00FF0000&
      Height          =   375
      Left            =   360
      ScaleHeight     =   345
      ScaleWidth      =   4845
      TabIndex        =   0
      Top             =   390
      Width           =   4875
      Begin PictureBox PIC_Percent 
         AutoRedraw      =   -1  'True
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   0  'None
         DrawMode        =   10  'Not Xor Pen
         FillColor       =   &H00FF0000&
         ForeColor       =   &H00FF0000&
         Height          =   255
         Left            =   2160
         ScaleHeight     =   255
         ScaleWidth      =   615
         TabIndex        =   6
         Top             =   60
         Width           =   615
      End
   End
   Begin Label Text 
      Alignment       =   2  'Center
      Height          =   195
      Left            =   0
      TabIndex        =   5
      Top             =   120
      Width           =   5535
   End
   Begin Label Value 
      Caption         =   " 0"
      Height          =   195
      Left            =   1380
      TabIndex        =   4
      Top             =   750
      Visible         =   0   'False
      Width           =   2055
   End
   Begin Label Max 
      Caption         =   " 100"
      Height          =   195
      Left            =   3480
      TabIndex        =   3
      Top             =   750
      Visible         =   0   'False
      Width           =   2055
   End
   Begin Label Min 
      Caption         =   " 0"
      Height          =   195
      Left            =   0
      TabIndex        =   2
      Top             =   750
      Visible         =   0   'False
      Width           =   2055
   End
End
Option Explicit

Dim OldPer, CallingForm As Form

'SetWindowPos() declaration
Declare Sub SetWindowPos Lib "User" (ByVal hWnd%, ByVal hWndInsertAfter%, ByVal x%, ByVal y%, ByVal cx%, ByVal cy%, ByVal fuFlags%)

'SetWindowPos() and WINDOWPOS flags
Const SWP_NOSIZE = &H1
Const SWP_NOMOVE = &H2
Const SWP_NOZORDER = &H4
Const SWP_NOREDRAW = &H8
Const SWP_NOACTIVATE = &H10

'SetWindowPos() hwndInsertAfter field values
Const HWND_TOP = 0
Const HWND_BOTTOM = 1
Const HWND_TOPMOST = -1
Const HWND_NOTOPMOST = -2

Sub Cancel_Click ()
   Cancel.Enabled = False
   Progress.Hide
End Sub

Sub Form_Load ()
   'Identify the calling form
   Set CallingForm = Screen.ActiveForm
   
   'Center form on currently active form
   Me.Left = CallingForm.Left + CallingForm.Width / 2 - Me.Width / 2
   If Me.Left < 0 Then Me.Left = 0
   If Me.Left + Me.Width > Screen.Width Then Me.Left = Screen.Width - Me.Width
   Me.Top = CallingForm.Top + CallingForm.Height / 4 - Me.Height / 2
   If Me.Top < 0 Then Me.Top = 0
   If Me.Top + Me.Height > Screen.Height Then Me.Top = Screen.Height - Me.Height

   'Make form topmost
   SetWindowPos Me.hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE Or SWP_NOMOVE Or SWP_NOSIZE Or SWP_NOREDRAW

   'Size and Center the PIC_Percent in the PIC_Bar
   PIC_Percent.Width = PIC_Percent.TextWidth("100%")
   PIC_Percent.Height = PIC_Percent.TextHeight("100%")
   PIC_Percent.Left = (PIC_Bar.Width - PIC_Percent.Width) / 2
   PIC_Percent.Top = (PIC_Bar.Height - PIC_Percent.Height) / 2

   PIC_Percent.CurrentX = (PIC_Percent.Width - PIC_Percent.TextWidth("0%")) / 2
   PIC_Percent.CurrentY = (PIC_Percent.Height - PIC_Percent.TextHeight("0%")) / 2
   PIC_Percent.Print "0%"

   'Enable the Cancel button
   Cancel.Enabled = True
End Sub

Sub Form_Unload (Cancel As Integer)
    CallingForm.SetFocus
End Sub

Sub Max_Change ()
   Value_Change
End Sub

Sub Min_Change ()
   Value_Change
End Sub

Sub PIC_Bar_Paint ()
   OldPer = 0
   Value_Change
End Sub

Sub Value_Change ()
   Dim Value, Min, Max, Per, Percent$, TempClr&, x1%, x2%
   
   'Convert label captions into real values
   Value = Val(Me.Value)
   Min = Val(Me.Min)
   Max = Val(Me.Max)
   
   'Determine Percent complete and convert to a string
   If Value < Min Then Value = Min
   If Value > Max Then Value = Max
   If Min < Max Then
      Per = (Value - Min) / (Max - Min)
      Percent$ = LTrim$(Str$(CInt(Per * 100))) + "%"
   Else
      Per = 1
      Percent$ = "100%"
   End If
   
   'Quit early if no change
   If CInt(Per * 100) = CInt(OldPer * 100) Then
      DoEvents
      Exit Sub
   End If
   
   x1% = PIC_Bar.Width * OldPer
   x2% = PIC_Bar.Width * Per
   
   'Update percent text
   PIC_Percent.Cls
   PIC_Percent.CurrentX = (PIC_Percent.Width - PIC_Percent.TextWidth(Percent$)) / 2
   PIC_Percent.CurrentY = (PIC_Percent.Height - PIC_Percent.TextHeight(Percent$)) / 2
   PIC_Percent.Print Percent$
   
   'Invert up to the end of the progress bar
   PIC_Percent.Line (-15, 0)-(x2% - PIC_Percent.Left, PIC_Percent.Height), PIC_Percent.FillColor, BF

   'Now update the progress bar
   If x1% > x2% Then
      'Going backwards, so erase the bar
      PIC_Bar.DrawMode = WHITENESS
      PIC_Bar.Line (x1%, 0)-(x2%, PIC_Bar.Height), , BF
      'Fix-up 1 pixel wide line (line drawn below)
      x1% = x2%
   End If
   
   'Set the bar if going forward, or fix-up if going backward
   PIC_Bar.DrawMode = COPY_PEN
   PIC_Bar.Line (x1%, 0)-(x2%, PIC_Bar.Height), , BF
   
   'Save current percent value and Do Events
   OldPer = Per
   DoEvents
End Sub

