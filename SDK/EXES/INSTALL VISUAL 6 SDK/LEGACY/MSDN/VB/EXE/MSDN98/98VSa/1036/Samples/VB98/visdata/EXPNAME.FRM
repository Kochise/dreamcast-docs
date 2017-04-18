VERSION 5.00
Begin VB.Form frmExpName 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Exporter"
   ClientHeight    =   1335
   ClientLeft      =   2775
   ClientTop       =   2670
   ClientWidth     =   4950
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   HelpContextID   =   2016127
   Icon            =   "EXPNAME.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1335
   ScaleWidth      =   4950
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Annuler"
      Height          =   375
      Left            =   3480
      MaskColor       =   &H00000000&
      TabIndex        =   4
      Top             =   600
      Width           =   1335
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   3480
      MaskColor       =   &H00000000&
      TabIndex        =   3
      Top             =   120
      Width           =   1335
   End
   Begin VB.TextBox txtTable 
      Height          =   285
      Left            =   160
      TabIndex        =   1
      Top             =   480
      Width           =   2895
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Height          =   195
      Left            =   165
      TabIndex        =   2
      Top             =   840
      Width           =   45
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Height          =   195
      Left            =   165
      TabIndex        =   0
      Top             =   120
      Width           =   45
   End
End
Attribute VB_Name = "frmExpName"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "Exporter"
Const BUTTON1 = "&OK"
Const BUTTON2 = "&Annuler"
'>>>>>>>>>>>>>>>>>>>>>>>>


Private Sub cmdCancel_Click()
  gExpTable = vbNullString
  Unload Me
End Sub

Private Sub cmdOK_Click()
  gExpTable = txtTable.Text
  Unload Me
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016127
  End If
End Sub

Sub Form_Load()
  Me.Caption = FORMCAPTION
  cmdOK.Caption = BUTTON1
  cmdCancel.Caption = BUTTON2
End Sub
