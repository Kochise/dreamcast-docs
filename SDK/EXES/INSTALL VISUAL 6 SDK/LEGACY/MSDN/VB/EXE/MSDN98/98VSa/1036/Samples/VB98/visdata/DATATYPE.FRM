VERSION 5.00
Begin VB.Form frmDataType 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Type de données"
   ClientHeight    =   1515
   ClientLeft      =   2280
   ClientTop       =   3165
   ClientWidth     =   4605
   HelpContextID   =   2016123
   Icon            =   "DATATYPE.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form2"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1515
   ScaleWidth      =   4605
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Annuler"
      Height          =   375
      Left            =   3120
      MaskColor       =   &H00000000&
      TabIndex        =   2
      Top             =   960
      Width           =   1335
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   3120
      MaskColor       =   &H00000000&
      TabIndex        =   1
      Top             =   360
      Width           =   1335
   End
   Begin VB.ListBox lstTypes 
      Height          =   1035
      ItemData        =   "DATATYPE.frx":030A
      Left            =   120
      List            =   "DATATYPE.frx":030C
      TabIndex        =   0
      Top             =   360
      Width           =   2895
   End
   Begin VB.Label lblLabel1 
      AutoSize        =   -1  'True
      Caption         =   " Source de données: "
      Height          =   195
      Left            =   120
      TabIndex        =   3
      Top             =   60
      Width           =   1035
   End
End
Attribute VB_Name = "frmDataType"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const BUTTON1 = "&OK"
Const BUTTON2 = "&Annuler"
Const Label1 = "Source de données:"
'>>>>>>>>>>>>>>>>>>>>>>>>


Private Sub cmdCancel_Click()
  gnDataType = gnDT_NONE
  Me.Hide
End Sub

Private Sub cmdOK_Click()
  gnDataType = lstTypes.ListIndex
  Me.Hide
End Sub

Private Sub lstTypes_DblClick()
  Call cmdOK_Click
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016123
  End If
End Sub

Private Sub Form_Load()
  cmdOK.Caption = BUTTON1
  cmdCancel.Caption = BUTTON2
  lblLabel1.Caption = Label1
  
  If Tag <> "CHARGÉ" Then
    Tag = "CHARGÉ"
  End If
  lstTypes.AddItem "Access MDB"
  lstTypes.AddItem "Dbase IV"
  lstTypes.AddItem "Dbase III"
  lstTypes.AddItem "FoxPro 2.6"
  lstTypes.AddItem "FoxPro 2.5"
  lstTypes.AddItem "FoxPro 2.0"
  lstTypes.AddItem "Paradox 4.X"
  lstTypes.AddItem "Paradox 3.X"
  lstTypes.AddItem "Btrieve"
  lstTypes.AddItem "Excel 5.0"
  lstTypes.AddItem "Excel 4.0"
  lstTypes.AddItem "Excel 3.0"
  lstTypes.AddItem "Text"
  lstTypes.AddItem "ODBC"

  lstTypes.ListIndex = 0

End Sub
