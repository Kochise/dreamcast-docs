VERSION 5.00
Begin VB.Form frmNewPassword 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Définir le mot de passe"
   ClientHeight    =   1995
   ClientLeft      =   3645
   ClientTop       =   3540
   ClientWidth     =   3750
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   HelpContextID   =   2016136
   Icon            =   "NEWPW.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1995
   ScaleWidth      =   3750
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.TextBox txtVerify 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   120
      MaxLength       =   20
      PasswordChar    =   "*"
      TabIndex        =   5
      Top             =   1560
      Width           =   1695
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Annuler"
      Default         =   -1  'True
      Height          =   375
      Left            =   2040
      MaskColor       =   &H00000000&
      TabIndex        =   7
      Top             =   960
      Width           =   1575
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Height          =   375
      Left            =   2040
      MaskColor       =   &H00000000&
      TabIndex        =   6
      Top             =   360
      Width           =   1575
   End
   Begin VB.TextBox txtNewPW 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   120
      MaxLength       =   20
      PasswordChar    =   "*"
      TabIndex        =   3
      Top             =   960
      Width           =   1695
   End
   Begin VB.TextBox txtOldPW 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   120
      PasswordChar    =   "*"
      TabIndex        =   1
      Top             =   360
      Width           =   1695
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Confirmer:"
      Height          =   195
      Index           =   2
      Left            =   120
      TabIndex        =   4
      Top             =   1320
      Width           =   480
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Nouveau mot de passe:"
      Height          =   195
      Index           =   1
      Left            =   120
      TabIndex        =   2
      Top             =   720
      Width           =   1110
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Ancien &mot de passe:"
      Height          =   195
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1035
   End
End
Attribute VB_Name = "frmNewPassword"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "Définir le mot de passe"
Const BUTTON1 = "&OK"
Const BUTTON2 = "&Annuler"
Const Label1 = "Ancien &mot de passe:"
Const Label2 = "&Nouveau mot de passe:"
Const LABEL3 = "&Confirmer:"
Const MSG1 = "Mot de passe incorrect, essayez de nouveau."
'>>>>>>>>>>>>>>>>>>>>>>>>


Private Sub cmdCancel_Click()
  Unload Me
End Sub

Private Sub cmdOK_Click()
  On Error GoTo OKErr
  
  Dim sTmp As String
  Dim usr As User
  
  If txtNewPW.Text <> txtVerify.Text Then
    Beep
    MsgBox MSG1, 48
    txtVerify.SetFocus
    Exit Sub
  End If
  
  gwsMainWS.Users(gwsMainWS.UserName).NewPassword txtOldPW.Text, txtNewPW.Text
  
  Unload Me
  Exit Sub
  
OKErr:
  ShowError
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016136
  End If
End Sub

Private Sub Form_Load()
  Me.Caption = FORMCAPTION
  cmdOK.Caption = BUTTON1
  cmdCancel.Caption = BUTTON2
  lblLabels(0).Caption = Label1
  lblLabels(1).Caption = Label2
  lblLabels(2).Caption = LABEL3
End Sub
