VERSION 4.00
Begin VB.Form frmScreenSaverPassWord 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   660
   ClientLeft      =   4605
   ClientTop       =   4140
   ClientWidth     =   4065
   ControlBox      =   0   'False
   Height          =   1065
   Left            =   4545
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   660
   ScaleWidth      =   4065
   ShowInTaskbar   =   0   'False
   Top             =   3795
   Width           =   4185
   Begin VB.Timer Timer1 
      Interval        =   30000
      Left            =   3720
      Top             =   120
   End
   Begin VB.TextBox Text1 
      BeginProperty Font 
         name            =   "Arial Special G1"
         charset         =   2
         weight          =   700
         size            =   12
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1440
      PasswordChar    =   "*"
      TabIndex        =   1
      Top             =   120
      Width           =   2295
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "PassWord"
      BeginProperty Font 
         name            =   "Arial Special G1"
         charset         =   2
         weight          =   700
         size            =   12
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1185
   End
End
Attribute VB_Name = "frmScreenSaverPassWord"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
#If Win16 Then
Private Declare Sub SetWindowPos Lib "User" (ByVal hWnd As Integer, ByVal hWndInsertAfter As Integer, ByVal X As Integer, ByVal Y As Integer, ByVal cx As Integer, ByVal cy As Integer, ByVal wFlags As Integer)
#Else
Private Declare Sub SetWindowPos Lib "User32" (ByVal hWnd As Long, ByVal hWndInsertAfter As Long, ByVal X As Long, ByVal Y As Long, ByVal cx As Long, ByVal cy As Long, ByVal wFlags As Long)
#End If
Private Sub Form_Load()
Const HWND_TOPMOST = -1
 Const SWP_NOSIZE = &H1
 SetWindowPos Me.hWnd, HWND_TOPMOST, 0&, 0&, 0, 0, SWP_NOSIZE
 End
 End
 Move (Screen.Width - Width) / 2, (Screen.Height - Height) / 2 'Fill the screen
 Text1.MaxLength = Len(frmScreenSaver.Tag)
End Sub


Private Sub Form_Resize()
Text1.SetFocus
End Sub

Private Sub Text1_Change()
Debug.Print Text1, frmScreenSaver.Tag, StrComp(frmScreenSaver.Tag, Text1.Text, 1)

Timer1.Enabled = False
Timer1.Interval = 0
Timer1.Interval = 30000
Timer1.Enabled = True 'Restart Timer!

'Check if Valid Password
If StrComp(frmScreenSaver.Tag, Text1.Text, 1) = 0 Or Len(frmScreenSaver.Tag) = 0 Then
    frmScreenSaver.Tag = ""
    Unload Me
End If
End Sub

Private Sub Text1_KeyPress(KeyAscii As Integer)
If KeyAscii < 30 Then Unload Me
End Sub

Private Sub Text1_LostFocus()
 Text1.SetFocus
End Sub

Private Sub Timer1_Timer()
Unload Me
End Sub
