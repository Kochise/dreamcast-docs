VERSION 5.00
Begin VB.Form frmSeek 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Paramètres de recherche"
   ClientHeight    =   1950
   ClientLeft      =   1440
   ClientTop       =   2595
   ClientWidth     =   3390
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   HelpContextID   =   2016143
   Icon            =   "SEEK.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form2"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1950
   ScaleWidth      =   3390
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Annuler"
      Height          =   375
      Left            =   1800
      MaskColor       =   &H00000000&
      TabIndex        =   8
      Top             =   1440
      Width           =   1455
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   120
      MaskColor       =   &H00000000&
      TabIndex        =   7
      Top             =   1440
      Width           =   1455
   End
   Begin VB.OptionButton optSeekOperator 
      Caption         =   "="
      Height          =   255
      Index           =   0
      Left            =   120
      MaskColor       =   &H00000000&
      TabIndex        =   0
      Top             =   360
      Value           =   -1  'True
      Width           =   495
   End
   Begin VB.OptionButton optSeekOperator 
      Caption         =   ">="
      Height          =   255
      Index           =   1
      Left            =   720
      MaskColor       =   &H00000000&
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   360
      Width           =   615
   End
   Begin VB.OptionButton optSeekOperator 
      Caption         =   "<="
      Height          =   255
      Index           =   2
      Left            =   1440
      MaskColor       =   &H00000000&
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   360
      Width           =   615
   End
   Begin VB.OptionButton optSeekOperator 
      Caption         =   ">"
      Height          =   255
      Index           =   3
      Left            =   2160
      MaskColor       =   &H00000000&
      TabIndex        =   3
      TabStop         =   0   'False
      Top             =   360
      Width           =   495
   End
   Begin VB.OptionButton optSeekOperator 
      Caption         =   "<"
      Height          =   255
      Index           =   4
      Left            =   2760
      MaskColor       =   &H00000000&
      TabIndex        =   4
      TabStop         =   0   'False
      Top             =   360
      Width           =   495
   End
   Begin VB.TextBox txtSeekValue 
      Height          =   285
      Left            =   120
      TabIndex        =   6
      Top             =   960
      Width           =   3135
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Valeur: "
      Height          =   195
      Index           =   1
      Left            =   120
      TabIndex        =   5
      Top             =   720
      Width           =   495
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Opérateur: "
      Height          =   195
      Index           =   0
      Left            =   120
      TabIndex        =   9
      Top             =   120
      Width           =   765
   End
End
Attribute VB_Name = "frmSeek"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "Paramètres de recherche"
Const BUTTON1 = "&OK"
Const BUTTON2 = "&Annuler"
Const Label1 = "Opérateurs:"
Const Label2 = "&Valeur:"
'>>>>>>>>>>>>>>>>>>>>>>>>


Private Sub cmdCancel_Click()
  gsSeekValue = vbNullString
  txtSeekValue.SetFocus
  Me.Hide
End Sub

Private Sub optSeekOperator_Click(Index As Integer)
  txtSeekValue.SetFocus
End Sub

Private Sub txtSeekValue_Change()
  If Len(txtSeekValue.Text) = 0 Then
    cmdOK.Enabled = False
  Else
    cmdOK.Enabled = True
  End If
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016143
  End If
End Sub

Private Sub Form_Load()
  Me.Caption = FORMCAPTION
  cmdOK.Caption = BUTTON1
  cmdCancel.Caption = BUTTON2
  lblLabels(0).Caption = Label1
  lblLabels(1).Caption = Label2
End Sub

Private Sub cmdOK_Click()
  If optSeekOperator(0).Value Then
    gsSeekOperator = "="
  ElseIf optSeekOperator(1).Value Then
    gsSeekOperator = ">="
  ElseIf optSeekOperator(2).Value Then
    gsSeekOperator = "<="
  ElseIf optSeekOperator(3).Value Then
    gsSeekOperator = ">"
  ElseIf optSeekOperator(4).Value Then
    gsSeekOperator = "<"
  End If
  gsSeekValue = txtSeekValue
  txtSeekValue.SetFocus
  Me.Hide
End Sub
