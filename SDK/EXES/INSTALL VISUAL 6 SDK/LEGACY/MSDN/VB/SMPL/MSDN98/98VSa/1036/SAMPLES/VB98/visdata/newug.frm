VERSION 5.00
Begin VB.Form frmNewUserGroup 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Nouveau groupe d'utilisateur"
   ClientHeight    =   1935
   ClientLeft      =   3990
   ClientTop       =   3525
   ClientWidth     =   3480
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   HelpContextID   =   2016137
   Icon            =   "NEWUG.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1935
   ScaleWidth      =   3480
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Annuler"
      Default         =   -1  'True
      Height          =   375
      Left            =   1800
      MaskColor       =   &H00000000&
      TabIndex        =   5
      Top             =   1440
      Width           =   1455
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Enabled         =   0   'False
      Height          =   375
      Left            =   240
      MaskColor       =   &H00000000&
      TabIndex        =   4
      Top             =   1440
      Width           =   1455
   End
   Begin VB.TextBox txtPID 
      Height          =   285
      Left            =   120
      MaxLength       =   20
      TabIndex        =   3
      Top             =   960
      Width           =   3255
   End
   Begin VB.TextBox txtName 
      Height          =   285
      Left            =   120
      TabIndex        =   1
      Top             =   360
      Width           =   3255
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "N° &personnel:"
      Height          =   195
      Index           =   1
      Left            =   120
      TabIndex        =   2
      Top             =   720
      Width           =   315
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "&Nom:"
      Height          =   195
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   465
   End
End
Attribute VB_Name = "frmNewUserGroup"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const BUTTON1 = "&OK"
Const BUTTON2 = "&Annuler"
Const Label1 = "&Nom:"
Const Label2 = "&N° &personnel:"
Const MSG1 = "Le N° personnel doit comporter au minimum 4 caractères et au maximum 20 caractères!"
'>>>>>>>>>>>>>>>>>>>>>>>>

Public UserOrGroup As Integer

Private Sub cmdCancel_Click()
  Unload Me
End Sub

Private Sub cmdOK_Click()
  On Error GoTo OKErr
  
  Dim sTmp As String
  Dim usr As User
  Dim grp As Group
  
  If Len(txtPID) < 4 Then
    Beep
    MsgBox MSG1, 48
    Exit Sub
  End If
  
  If UserOrGroup = 0 Then
    Set usr = gwsMainWS.CreateUser(txtName.Text, txtPID.Text)
    gwsMainWS.Users.Append usr
    gwsMainWS.Groups.Refresh
    frmGroupsUsers.lstUsers.AddItem txtName.Text
    frmGroupsUsers.lstGroupsUsers.AddItem txtName.Text
    ' Ajoute le nouvel utilisateur au groupe des utilisateurs par défaut.
    On Error Resume Next  ' Au cas où le groupe des utilisateurs n'existe plus.
    gwsMainWS.Groups("Users").Users.Append usr
    gwsMainWS.Users(txtName.Text).Groups.Refresh
  Else
    Set grp = gwsMainWS.CreateGroup(txtName.Text, txtPID.Text)
    gwsMainWS.Groups.Append grp
    gwsMainWS.Users.Refresh
    frmGroupsUsers.lstGroups.AddItem txtName.Text
    frmGroupsUsers.lstUsersGroups.AddItem txtName.Text
  End If
  
  Unload Me
  Exit Sub
  
OKErr:
  ShowError
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016137
  End If
End Sub

Private Sub Form_Load()
  cmdOK.Caption = BUTTON1
  cmdCancel.Caption = BUTTON2
  lblLabels(0).Caption = Label1
  lblLabels(1).Caption = Label2
End Sub

Private Sub txtName_Change()
  cmdOK.Enabled = Len(txtName.Text) > 0
End Sub
