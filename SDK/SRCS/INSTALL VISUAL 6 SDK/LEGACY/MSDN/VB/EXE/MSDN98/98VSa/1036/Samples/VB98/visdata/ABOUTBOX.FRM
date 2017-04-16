VERSION 5.00
Begin VB.Form frmAboutBox 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "À propos du Gestionnaire de données"
   ClientHeight    =   2280
   ClientLeft      =   4395
   ClientTop       =   2925
   ClientWidth     =   5055
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "ABOUTBOX.frx":0000
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2280
   ScaleWidth      =   5055
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdOK 
      Cancel          =   -1  'True
      Caption         =   "&OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   2040
      MaskColor       =   &H00000000&
      TabIndex        =   1
      Top             =   1800
      Width           =   975
   End
   Begin VB.PictureBox picIcon 
      BackColor       =   &H00C0C0C0&
      BorderStyle     =   0  'None
      BeginProperty DataFormat 
         Type            =   2
         Format          =   ""
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
      EndProperty
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   525
      Left            =   255
      Picture         =   "ABOUTBOX.frx":000C
      ScaleHeight     =   525
      ScaleWidth      =   480
      TabIndex        =   0
      Top             =   300
      Width           =   480
   End
   Begin VB.Label lblLabels 
      Alignment       =   2  'Center
      Caption         =   "Copyright (c) Microsoft Corp. 1996-98"
      BeginProperty DataFormat 
         Type            =   0
         Format          =   ""
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
      EndProperty
      Height          =   375
      Index           =   3
      Left            =   1320
      TabIndex        =   5
      Top             =   1320
      Width           =   2535
   End
   Begin VB.Label lblLabels 
      Alignment       =   2  'Center
      Caption         =   "Version 6.0"
      BeginProperty DataFormat 
         Type            =   0
         Format          =   ""
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
      EndProperty
      Height          =   210
      Index           =   2
      Left            =   1320
      TabIndex        =   4
      Top             =   840
      Width           =   2535
   End
   Begin VB.Label lblLabels 
      Alignment       =   2  'Center
      Caption         =   "Gestionnaire de données"
      BeginProperty DataFormat 
         Type            =   0
         Format          =   ""
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
      EndProperty
      Height          =   210
      Index           =   1
      Left            =   1200
      TabIndex        =   3
      Top             =   600
      Width           =   2895
   End
   Begin VB.Label lblLabels 
      Alignment       =   2  'Center
      Caption         =   "Microsoft Visual Basic"
      BeginProperty DataFormat 
         Type            =   0
         Format          =   ""
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
      EndProperty
      Height          =   270
      Index           =   0
      Left            =   1320
      TabIndex        =   2
      Top             =   120
      Width           =   2535
   End
End
Attribute VB_Name = "frmAboutBox"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "À propos du Gestionnaire de données"
Const LABEL0 = "Microsoft Visual Basic"
Const Label1 = "Gestionnaire de données"
Const Label2 = "Version 6.0"
Const LABEL3 = "Copyright (c) Microsoft Corp. 1996-98"
Const BUTTON1 = "&OK"
'>>>>>>>>>>>>>>>>>>>>>>>>


Private Sub Form_KeyPress(KeyAscii As Integer)
  Unload Me
End Sub

Private Sub Form_Load()
  Me.Caption = FORMCAPTION
  lblLabels(0).Caption = LABEL0
  lblLabels(1).Caption = Label1
  lblLabels(2).Caption = Label2
  lblLabels(3).Caption = LABEL3
  cmdOK.Caption = BUTTON1
End Sub

Private Sub cmdOK_Click()
  Unload Me
End Sub

Private Sub cmdOK_KeyPress(KeyAscii As Integer)
  Unload Me
End Sub
