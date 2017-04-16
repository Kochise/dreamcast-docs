VERSION 5.00
Begin VB.Form frmReplace 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Remplacement global"
   ClientHeight    =   3855
   ClientLeft      =   1860
   ClientTop       =   2070
   ClientWidth     =   5175
   HelpContextID   =   2016091
   Icon            =   "REPLACE.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3421.786
   ScaleMode       =   0  'User
   ScaleWidth      =   5081.244
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.ListBox lstTables 
      Height          =   1620
      Left            =   240
      Sorted          =   -1  'True
      TabIndex        =   1
      Top             =   360
      Width           =   2295
   End
   Begin VB.ListBox lstFields 
      Height          =   1620
      Left            =   2640
      Sorted          =   -1  'True
      TabIndex        =   3
      Top             =   360
      Width           =   2295
   End
   Begin VB.TextBox txtReplaceWith 
      Height          =   285
      Left            =   240
      TabIndex        =   5
      Top             =   2280
      Width           =   4695
   End
   Begin VB.TextBox txtCondition 
      Height          =   285
      Left            =   240
      TabIndex        =   7
      Top             =   2880
      Width           =   4695
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Default         =   -1  'True
      Enabled         =   0   'False
      Height          =   375
      Left            =   480
      MaskColor       =   &H00000000&
      TabIndex        =   8
      Top             =   3360
      Width           =   2055
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Annuler"
      Height          =   375
      Left            =   2640
      MaskColor       =   &H00000000&
      TabIndex        =   9
      Top             =   3360
      Width           =   2055
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Tables:"
      Height          =   195
      Index           =   0
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   450
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Critères:"
      Height          =   195
      Index           =   3
      Left            =   240
      TabIndex        =   6
      Top             =   2640
      Width           =   585
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Remplacer par:"
      Height          =   195
      Index           =   2
      Left            =   240
      TabIndex        =   4
      Top             =   2040
      Width           =   1110
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Champs:"
      Height          =   195
      Index           =   1
      Left            =   2640
      TabIndex        =   2
      Top             =   120
      Width           =   390
   End
End
Attribute VB_Name = "frmReplace"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "Remplacement global"
Const BUTTON1 = "&OK"
Const BUTTON2 = "&Annuler"
Const Label1 = "&Tables:"
Const Label2 = "&Champs:"
Const LABEL3 = "&Remplacer par:"
Const LABEL4 = "Cr&itères:"
Const MSG1 = "Enregistrements remplacés"
'>>>>>>>>>>>>>>>>>>>>>>>>


Private Sub cmdCancel_Click()
  Unload Me
End Sub

Private Sub lstFields_Click()
  cmdOK.Enabled = Len(lstFields.Text) > 0 And Len(txtReplaceWith.Text) > 0
End Sub

Private Sub txtReplaceWith_Change()
  cmdOK.Enabled = Len(lstFields.Text) > 0 And Len(txtReplaceWith.Text) > 0
End Sub

Private Sub lstTables_Click()
  Dim i As Integer
  Dim fld As Field

  ListItemNames gdbCurrentDB.TableDefs(StripConnect(lstTables.Text)).Fields, lstFields, True
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016091
  End If
End Sub

Private Sub Form_Load()
  Me.Caption = FORMCAPTION
  cmdOK.Caption = BUTTON1
  cmdCancel.Caption = BUTTON2
  lblLabels(0).Caption = Label1
  lblLabels(1).Caption = Label2
  lblLabels(2).Caption = LABEL3
  lblLabels(3).Caption = LABEL4
  
  RefreshTables frmReplace.lstTables
End Sub

Private Sub cmdOK_Click()
  Dim sReplaceTxt As String       ' Chaîne de remplacement
  Dim sWhereCondition As String   ' Condition Where

  On Error GoTo ReplaceErr

  MsgBar MSG1, True
  If gdbCurrentDB.TableDefs(StripConnect(lstTables.Text)).Fields(lstFields).Type = dbText Then
    sReplaceTxt = "'" & txtReplaceWith & "'"
  Else
    sReplaceTxt = txtReplaceWith
  End If
  If Len(txtCondition.Text) = 0 Then
    sWhereCondition = vbNullString
  Else
    sWhereCondition = " where " & txtCondition
  End If
  If gsDataType = gsSQLDB Then
    gdbCurrentDB.Execute "update " & StripConnect(lstTables.Text) & " set " & lstFields.Text & "=" & sReplaceTxt & sWhereCondition, dbSQLPassThrough
  Else
    gdbCurrentDB.Execute "update " & StripConnect(lstTables.Text) & " set [" & lstFields.Text & "]=" & sReplaceTxt & sWhereCondition
  End If
  If gdbCurrentDB.RecordsAffected > 0 Then
    If gbTransPending Then gbDBChanged = True
  End If

  Unload Me

  MsgBar vbNullString, False
  Exit Sub

ReplaceErr:
  ShowError
End Sub
