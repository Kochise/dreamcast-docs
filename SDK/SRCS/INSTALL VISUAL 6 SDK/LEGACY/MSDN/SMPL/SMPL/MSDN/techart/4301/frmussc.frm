VERSION 4.00
Begin VB.Form frmudtScreenSaverConfig 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Screen Saver Configuration"
   ClientHeight    =   3930
   ClientLeft      =   1005
   ClientTop       =   1830
   ClientWidth     =   6690
   Height          =   4335
   Left            =   945
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3930
   ScaleWidth      =   6690
   ShowInTaskbar   =   0   'False
   Top             =   1485
   Width           =   6810
   Begin VB.CommandButton pbOK 
      Caption         =   "&OK"
      Height          =   495
      Left            =   4680
      TabIndex        =   13
      Top             =   3360
      Width           =   1575
   End
   Begin VB.CommandButton pbCancel 
      Caption         =   "&Cancel"
      Height          =   495
      Left            =   3000
      TabIndex        =   12
      Top             =   3360
      Width           =   1455
   End
   Begin VB.Frame Frame1 
      Caption         =   "Behaviour"
      Height          =   855
      Left            =   120
      TabIndex        =   9
      Top             =   2280
      Width           =   2535
      Begin VB.OptionButton Option1 
         Caption         =   "Bounce off &Sides"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   11
         Top             =   480
         Width           =   2055
      End
      Begin VB.OptionButton Option1 
         Caption         =   "&Float Off Screen"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   10
         Top             =   240
         Width           =   2055
      End
   End
   Begin VB.HScrollBar HScroll1 
      Height          =   255
      LargeChange     =   4
      Left            =   4560
      Max             =   33
      Min             =   1
      TabIndex        =   7
      Top             =   2760
      Value           =   1
      Width           =   1695
   End
   Begin VB.TextBox txtPassWord 
      Height          =   285
      Left            =   4560
      TabIndex        =   6
      Top             =   2400
      Width           =   1695
   End
   Begin VB.CommandButton pbColor 
      Caption         =   "Background &Color"
      Height          =   615
      Left            =   120
      TabIndex        =   4
      Top             =   1560
      Width           =   2655
   End
   Begin VB.PictureBox Picture1 
      Height          =   2175
      Left            =   2880
      ScaleHeight     =   2145
      ScaleWidth      =   3345
      TabIndex        =   2
      Top             =   120
      Width           =   3375
      Begin VB.PictureBox Picture2 
         Height          =   615
         Left            =   120
         ScaleHeight     =   585
         ScaleWidth      =   705
         TabIndex        =   3
         Top             =   720
         Width           =   735
      End
   End
   Begin VB.CommandButton pbFloat 
      Caption         =   "&Floating Picture"
      Height          =   615
      Left            =   120
      TabIndex        =   1
      Top             =   840
      Width           =   2655
   End
   Begin VB.CommandButton pbBackGround 
      Caption         =   "&Back Ground Picture"
      Height          =   615
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2655
   End
   Begin MCI.MMControl MMC2 
      Height          =   330
      Left            =   240
      TabIndex        =   15
      Top             =   4320
      Visible         =   0   'False
      Width           =   3540
      _Version        =   65536
      _ExtentX        =   6244
      _ExtentY        =   582
      _StockProps     =   32
      BorderStyle     =   1
   End
   Begin MCI.MMControl MMC1 
      Height          =   330
      Left            =   120
      TabIndex        =   14
      Top             =   3960
      Visible         =   0   'False
      Width           =   3540
      _Version        =   65536
      _ExtentX        =   6244
      _ExtentY        =   582
      _StockProps     =   32
      BorderStyle     =   1
   End
   Begin VB.Label lblSpeed 
      AutoSize        =   -1  'True
      Caption         =   "Speed"
      Height          =   195
      Left            =   2880
      TabIndex        =   8
      Top             =   2760
      Width           =   465
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "PassWord:"
      Height          =   195
      Left            =   2880
      TabIndex        =   5
      Top             =   2400
      Width           =   780
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   2280
      Top             =   3360
      _Version        =   65536
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
End
Attribute VB_Name = "frmudtScreenSaverConfig"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Dim FrmUDT As udtScreenSaverConfig

Private Sub Form_Load()
udtScreenSaverConfig_Get FrmUDT
BackColor = FrmUDT.BackgroundImageColor
ShowFileInPictureBox FrmUDT.BackgroundImageFileName, Picture1, MMC1
ShowFileInPictureBox FrmUDT.MovingImageFileName, Picture2, MMC2
Select Case FrmUDT.ImageBehaviour
    Case 1
        Option1(FrmUDT.ImageBehaviour).Value = 1
    Case Else
        Option1(0).Value = 1
End Select
Select Case FrmUDT.ImageSpeed
    Case 1 - 33
    Case Else
        FrmUDT.ImageSpeed = 4
End Select
HScroll1.Value = FrmUDT.ImageSpeed
HScroll1_Change  'Force the event incase same value
txtPassWord.Text = FrmUDT.PassWord
End Sub

Private Sub HScroll1_Change()
FrmUDT.ImageSpeed = HScroll1.Value
lblSpeed = "Speed: " + Format(FrmUDT.ImageSpeed, "0") + " Fr/Sec"
End Sub

Private Sub Option1_Click(Index As Integer)
FrmUDT.ImageBehaviour = Index
End Sub

Private Sub pbBackGround_Click()
On Error GoTo BG_Abort
CommonDialog1.CancelError = True
CommonDialog1.FileName = "*.bmp;*.wmf"
CommonDialog1.Action = 1
Picture1.Picture = LoadPicture(CommonDialog1.FileName)
FrmUDT.BackgroundImageFileName = CommonDialog1.FileName
BG_Exit:
Exit Sub
BG_Abort:
Resume BG_Exit
End Sub

Private Sub pbCancel_Click()
Unload Me
End Sub

Private Sub pbColor_Click()
On Error GoTo c_Abort
CommonDialog1.CancelError = True
CommonDialog1.FileName = "*.bmp;*.wmf"
CommonDialog1.ShowColor
BackColor = CommonDialog1.Color
FrmUDT.BackgroundImageColor = CommonDialog1.Color
c_Exit:
Exit Sub
c_Abort:
Resume c_Exit
End Sub

Private Sub pbFloat_Click()
On Error GoTo F_Abort
CommonDialog1.CancelError = True
CommonDialog1.FileName = "*.bmp;*.wmf,*.ico,*.AVI"
CommonDialog1.ShowOpen
Picture2.Picture = LoadPicture(CommonDialog1.FileName)
FrmUDT.MovingImageFileName = CommonDialog1.FileName
F_Exit:
Exit Sub
F_Abort:
Resume F_Exit
End Sub

Private Sub pbOK_Click()
udtScreenSaverConfig_Put FrmUDT
Unload Me
End Sub

Private Sub txtPassWord_Change()
 FrmUDT.PassWord = txtPassWord.Text
End Sub
