VERSION 5.00
Begin VB.Form frmFindForm 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Rechercher un enregistrement"
   ClientHeight    =   2430
   ClientLeft      =   1995
   ClientTop       =   2595
   ClientWidth     =   5445
   HelpContextID   =   2016128
   Icon            =   "FIND.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2024.58
   ScaleMode       =   0  'User
   ScaleWidth      =   5358.743
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.OptionButton optFindType 
      Caption         =   "FindLast"
      Height          =   255
      Index           =   3
      Left            =   3120
      MaskColor       =   &H00000000&
      TabIndex        =   9
      Top             =   1440
      Width           =   2055
   End
   Begin VB.OptionButton optFindType 
      Caption         =   "FindPrevious"
      Height          =   255
      Index           =   2
      Left            =   3120
      MaskColor       =   &H00000000&
      TabIndex        =   8
      Top             =   1200
      Width           =   2055
   End
   Begin VB.OptionButton optFindType 
      Caption         =   "FindNext"
      Height          =   255
      Index           =   1
      Left            =   3120
      MaskColor       =   &H00000000&
      TabIndex        =   7
      Top             =   960
      Width           =   2055
   End
   Begin VB.OptionButton optFindType 
      Caption         =   "FindFirst"
      Height          =   255
      Index           =   0
      Left            =   3120
      MaskColor       =   &H00000000&
      TabIndex        =   6
      Top             =   720
      Value           =   -1  'True
      Width           =   2055
   End
   Begin VB.ListBox lstFields 
      Height          =   1425
      ItemData        =   "FIND.frx":030A
      Left            =   240
      List            =   "FIND.frx":030C
      TabIndex        =   1
      Top             =   360
      Width           =   1695
   End
   Begin VB.ListBox lstOperators 
      Height          =   1425
      ItemData        =   "FIND.frx":030E
      Left            =   2040
      List            =   "FIND.frx":0310
      TabIndex        =   3
      Top             =   360
      Width           =   960
   End
   Begin VB.TextBox txtExpression 
      Height          =   285
      Left            =   3120
      TabIndex        =   5
      Top             =   360
      Width           =   2055
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Default         =   -1  'True
      Enabled         =   0   'False
      Height          =   372
      Left            =   600
      MaskColor       =   &H00000000&
      TabIndex        =   10
      Top             =   1919
      Width           =   1691
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Annuler"
      Height          =   372
      Left            =   2879
      MaskColor       =   &H00000000&
      TabIndex        =   11
      Top             =   1919
      Width           =   1691
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "O&pérateurs: "
      Height          =   195
      Index           =   1
      Left            =   2040
      TabIndex        =   2
      Top             =   120
      Width           =   840
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "&Champs: "
      Height          =   195
      Index           =   0
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   510
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "&Valeur ou expression: "
      Height          =   195
      Index           =   2
      Left            =   3120
      TabIndex        =   4
      Top             =   120
      Width           =   1515
   End
End
Attribute VB_Name = "frmFindForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "Rechercher un enregistrement"
Const BUTTON1 = "&OK"
Const BUTTON2 = "&Annuler"
Const Label1 = "&Champs:"
Const Label2 = "O&pérateurs:"
Const LABEL3 = "&Valeur ou expression:"
'>>>>>>>>>>>>>>>>>>>>>>>>

Dim mbNotFound As Integer


Private Sub cmdCancel_Click()
  Hide
  ' Définit l'indicateur pour la feuille de l'objet Recordset/Recagrid.
  gbFindFailed = True
End Sub

Private Sub optFindType_Click(Index As Integer)
  gnFindType = Index
End Sub

Private Sub txtExpression_Change()
  cmdOK.Enabled = Len(lstFields.Text) > 0 And Len(lstOperators.Text) > 0 And Len(txtExpression.Text) > 0
End Sub

Private Sub lstFields_Click()
  cmdOK.Enabled = Len(lstFields.Text) > 0 And Len(lstOperators.Text) > 0 And Len(txtExpression.Text) > 0
End Sub

Private Sub lstOperators_Click()
  cmdOK.Enabled = Len(lstFields.Text) > 0 And Len(lstOperators.Text) > 0 And Len(txtExpression.Text) > 0
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016128
  End If
End Sub

Private Sub Form_Load()
  Me.Caption = FORMCAPTION
  cmdOK.Caption = BUTTON1
  cmdCancel.Caption = BUTTON2
  lblLabels(0).Caption = Label1
  lblLabels(1).Caption = Label2
  lblLabels(2).Caption = LABEL3
  
  lstOperators.AddItem "="
  lstOperators.AddItem "<>"
  lstOperators.AddItem ">="
  lstOperators.AddItem "<="
  lstOperators.AddItem ">"
  lstOperators.AddItem "<"
  lstOperators.AddItem "Like"
  lstOperators.ListIndex = 0
    
  mbNotFound = False
End Sub

Private Sub cmdOK_Click()
   On Error GoTo FindErr

   Dim i As Integer

   i = lstFields.ListIndex
   mbNotFound = False
   Screen.MousePointer = vbHourglass

   gsFindField = lstFields.Text
   gsFindExpr = txtExpression.Text
   gsFindOp = lstOperators.Text

   Hide
   Screen.MousePointer = vbDefault
   Exit Sub

FindErr:
   If Err <> gnEOF_ERR Then
     ShowError
   Else
     mbNotFound = True
     Resume Next
   End If
End Sub
