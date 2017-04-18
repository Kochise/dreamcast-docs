VERSION 4.00
Begin VB.Form frmScreenSaver 
   BorderStyle     =   0  'None
   ClientHeight    =   6975
   ClientLeft      =   4020
   ClientTop       =   4035
   ClientWidth     =   9660
   ControlBox      =   0   'False
   Height          =   7380
   KeyPreview      =   -1  'True
   Left            =   3960
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6975
   ScaleWidth      =   9660
   ShowInTaskbar   =   0   'False
   Tag             =   "PASSWORD"
   Top             =   3690
   Width           =   9780
   WindowState     =   2  'Maximized
   Begin VB.PictureBox bmpFloat 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ClipControls    =   0   'False
      ForeColor       =   &H80000008&
      Height          =   480
      Left            =   0
      Negotiate       =   -1  'True
      Picture         =   "FRMSS.frx":0000
      ScaleHeight     =   480
      ScaleWidth      =   480
      TabIndex        =   1
      Top             =   0
      Width           =   480
   End
   Begin VB.PictureBox bmpBackground 
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      BorderStyle     =   0  'None
      DrawStyle       =   6  'Inside Solid
      Height          =   4425
      Left            =   960
      Picture         =   "FRMSS.frx":030A
      ScaleHeight     =   295
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   600
      TabIndex        =   0
      Top             =   120
      Width           =   9000
   End
   Begin VB.Timer Timer 
      Left            =   480
      Top             =   240
   End
   Begin MCI.MMControl MMControl1 
      Height          =   3375
      Left            =   1080
      TabIndex        =   2
      Top             =   240
      Visible         =   0   'False
      Width           =   390
      _Version        =   65536
      BackEnabled     =   -1  'True
      DeviceType      =   "AVIVideo"
      FileName        =   "C:\Windows\Help\Explorer.avi"
      Orientation     =   1
      _ExtentX        =   688
      _ExtentY        =   5953
      _StockProps     =   32
   End
End
Attribute VB_Name = "frmScreenSaver"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
#If Win16 Then
Private Declare Function ShowCursor Lib "User" (ByVal fShow As Integer) As Integer
Private Declare Sub SetWindowPos Lib "User" (ByVal hWnd As Integer, ByVal hWndInsertAfter As Integer, ByVal X As Integer, ByVal Y As Integer, ByVal cx As Integer, ByVal cy As Integer, ByVal wFlags As Integer)
#Else
Private Declare Sub SetWindowPos Lib "User32" (ByVal hWnd As Long, ByVal hWndInsertAfter As Long, ByVal X As Long, ByVal Y As Long, ByVal cx As Long, ByVal cy As Long, ByVal wFlags As Long)
Private Declare Function ShowCursor Lib "User32" (ByVal fShow As Integer) As Integer
#End If
Dim FrmUDT As udtScreenSaverConfig
Dim XD%, YD%
Private Sub bmpBackground_Click()
Form_Click
End Sub

Private Sub bmpFloat_Click()
Form_Click
End Sub

Private Sub bmpFloat_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
Form_MouseMove Button, Shift, X, Y
End Sub
Private Sub Form_Click()
frmScreenSaver_Destroy
End Sub

Private Sub Form_DblClick()
MsgBox "oops"
frmScreenSaver_Destroy
End Sub

Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
frmScreenSaver_Destroy
End Sub

Private Sub Form_KeyPress(KeyAscii As Integer)
frmScreenSaver_Destroy
End Sub

Private Sub Form_Load()
 Const HWND_TOPMOST = -1
 Const SWP_NOSIZE = &H1
 Dim RC%
udtScreenSaverConfig_Get FrmUDT
bmpBackground.AutoSize = True
ShowFileInPictureBox FrmUDT.BackgroundImageFileName, bmpBackground, MMControl1
bmpBackground.Move (Screen.Width - bmpBackground.Width) / 2, (Screen.Height - bmpBackground.Height) / 2 'Fill the screen

BackColor = FrmUDT.BackgroundImageColor

If Len(FrmUDT.MovingImageFileName) Then
        bmpFloat.AutoSize = True
        bmpFloat.Picture = LoadPicture(FrmUDT.MovingImageFileName)
Else
    'Keep Preloaded image!
End If
Select Case FrmUDT.ImageSpeed
    Case Is < 1
        frmScreenSaver.Timer.Interval = 100 '10 frames per second is default!
    Case Is < 34
        frmScreenSaver.Timer.Interval = 1000 / FrmUDT.ImageSpeed 'frames per second is assumed
     Case Else
                frmScreenSaver.Timer.Interval = FrmUDT.ImageSpeed
End Select
'--------------------------------------------------
SetWindowPos Me.hWnd, HWND_TOPMOST, 0&, 0&, 0, 0, SWP_NOSIZE
RC% = ShowCursor(0)
ScaleMode = 3 'Place into Pixels.
XD% = ScaleWidth
YD% = ScaleHeight
End Sub

Private Sub Form_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
frmScreenSaver_Destroy
End Sub

Private Sub Form_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
Static X0 As Integer, Y0 As Integer
If X0 = 0 And Y0 = 0 Then
    X0 = X
    Y0 = Y
    Exit Sub
End If
'Permit slow mouse movements or 'wobbles'
If Abs(X0 - X) < 5 And Abs(Y0 - Y) < 5 Then
    X0 = X
    Y0 = Y
    Exit Sub
End If
frmScreenSaver_Destroy
End Sub

Private Sub Form_Unload(Cancel As Integer)
Dim RC%
RC% = ShowCursor(-1)
Screen.MousePointer = 0
MMControl1.Command = "Close"
End Sub

Private Sub MMControl1_Done(NotifyCode As Integer)
MMControl1.Command = "Prev"
MMControl1.Command = "Play"

End Sub

Private Sub Timer_Timer()
Static BounceX%, BounceY%
If BounceX% = 0 Then BounceX% = 1: BounceY% = 1 'First Time

Select Case FrmUDT.ImageBehaviour
    Case 1
        If bmpFloat.Left > XD% Then BounceX% = -1
        If bmpFloat.Left < 0 Then BounceX% = 1
        If bmpFloat.Top > YD% Then BounceY% = -1
        If bmpFloat.Top < 0 Then BounceY% = 1
    Case Else
End Select
bmpFloat.Move bmpFloat.Left + BounceX% Mod (Width + bmpFloat.Width), bmpFloat.Top + BounceY% Mod (Height + bmpFloat.Height)

DoEvents  'Process any key strokes incase short time cycle.
End Sub
