VERSION 5.00
Begin VB.Form frmDBPWD 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Mot de passe demandé"
   ClientHeight    =   1350
   ClientLeft      =   2550
   ClientTop       =   3330
   ClientWidth     =   3735
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   HelpContextID   =   2016133
   Icon            =   "DBPwd.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   ScaleHeight     =   1350
   ScaleWidth      =   3735
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Annuler"
      Height          =   375
      Left            =   1890
      MaskColor       =   &H00000000&
      TabIndex        =   3
      Top             =   795
      Width           =   1215
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   525
      MaskColor       =   &H00000000&
      TabIndex        =   2
      Top             =   795
      Width           =   1215
   End
   Begin VB.TextBox txtPassword 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   105
      PasswordChar    =   "*"
      TabIndex        =   1
      Top             =   315
      Width           =   3495
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Entrez le mot de passe pour la base de données:"
      Height          =   195
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   50
      Width           =   3585
   End
End
Attribute VB_Name = "frmDBPWD"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "Mot de passe demandé"
Const BUTTON1 = "&OK"
Const BUTTON2 = "&Annuler"
Const Label1 = "&Entrez le mot de passe pour la base de données:"
'>>>>>>>>>>>>>>>>>>>>>>>>

Public PWD As String

Private Sub cmdCancel_Click()
  PWD = vbNullString
  Hide
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016133
  End If
End Sub

Private Sub Form_Load()
  Me.Caption = FORMCAPTION
  cmdOK.Caption = BUTTON1
  cmdCancel.Caption = BUTTON2
  lblLabels(0).Caption = Label1
End Sub

Private Sub cmdOK_Click()
  PWD = txtPassword.Text
  Hide
End Sub

Private Sub txtPassword_GotFocus()
  txtPassword.SelStart = 0
  txtPassword.SelLength = Len(txtPassword.Text)
End Sub
