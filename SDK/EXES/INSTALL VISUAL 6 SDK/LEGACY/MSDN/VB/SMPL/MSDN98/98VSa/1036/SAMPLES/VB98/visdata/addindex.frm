VERSION 5.00
Begin VB.Form frmAddIndex 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Ajoute un index"
   ClientHeight    =   3495
   ClientLeft      =   2100
   ClientTop       =   4215
   ClientWidth     =   5400
   ForeColor       =   &H00000000&
   HelpContextID   =   2016118
   Icon            =   "Addindex.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3067.929
   ScaleMode       =   0  'User
   ScaleWidth      =   5311.688
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CheckBox chkIgnoreNulls 
      Caption         =   "IgnoreNulls"
      Height          =   255
      Left            =   3120
      MaskColor       =   &H00000000&
      TabIndex        =   5
      Top             =   1320
      Width           =   2188
   End
   Begin VB.CheckBox chkPrimary 
      Caption         =   "Primary"
      Height          =   255
      Left            =   3120
      MaskColor       =   &H00000000&
      TabIndex        =   3
      Top             =   360
      Value           =   1  'Checked
      Width           =   2188
   End
   Begin VB.TextBox txtIndexName 
      Height          =   285
      Left            =   120
      TabIndex        =   0
      Top             =   360
      Width           =   2775
   End
   Begin VB.TextBox txtFields 
      Height          =   525
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   1
      Top             =   960
      Width           =   2775
   End
   Begin VB.ListBox lstFields 
      Height          =   1425
      Left            =   120
      Sorted          =   -1  'True
      TabIndex        =   2
      Top             =   1800
      Width           =   2775
   End
   Begin VB.CheckBox chkUnique 
      Caption         =   "Unique"
      Height          =   252
      Left            =   3120
      MaskColor       =   &H00000000&
      TabIndex        =   4
      Top             =   840
      Value           =   1  'Checked
      Width           =   2188
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Default         =   -1  'True
      Enabled         =   0   'False
      Height          =   375
      Left            =   3240
      MaskColor       =   &H00000000&
      TabIndex        =   6
      Top             =   2400
      Width           =   1815
   End
   Begin VB.CommandButton cmdClose 
      Cancel          =   -1  'True
      Caption         =   "&Fermer"
      Height          =   375
      Left            =   3240
      MaskColor       =   &H00000000&
      TabIndex        =   7
      Top             =   2880
      Width           =   1815
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Champs disponibles: "
      Height          =   195
      Index           =   2
      Left            =   120
      TabIndex        =   10
      Top             =   1560
      Width           =   1200
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Champs indexés:"
      Height          =   195
      Index           =   1
      Left            =   120
      TabIndex        =   9
      Top             =   720
      Width           =   1155
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Nom: "
      Height          =   195
      Index           =   0
      Left            =   120
      TabIndex        =   8
      Top             =   120
      Width           =   510
   End
End
Attribute VB_Name = "frmAddIndex"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "Ajouter un index"
Const BUTTON1 = "&OK"
Const BUTTON2 = "&Fermer"
Const LABEL0 = "Nom:"
Const Label1 = "Champs indexés:"
Const Label2 = "Champs disponibles:"
'>>>>>>>>>>>>>>>>>>>>>>>>


Private Sub lstFields_Click()
  Dim sTmp As String

  sTmp = txtFields.Text
  If Len(sTmp) = 0 Then
    txtFields.Text = sTmp & lstFields
  Else
    txtFields.Text = sTmp & ";" & lstFields
  End If
  txtFields.Refresh
End Sub

Private Sub txtFields_Change()
  cmdOK.Enabled = Len(txtIndexName.Text) > 0 And Len(txtFields.Text) > 0
End Sub

Private Sub txtFields_LostFocus()
  cmdOK.Enabled = Len(txtIndexName.Text) > 0 And Len(txtFields.Text) > 0
End Sub

Private Sub txtIndexName_LostFocus()
  cmdOK.Enabled = Len(txtIndexName.Text) > 0 And Len(txtFields.Text) > 0
End Sub

Private Sub cmdClose_Click()
  Unload Me
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016118
  End If
End Sub

Private Sub Form_Load()
  Dim tblTableDef As TableDef
  Dim fld As Field
  Dim i As Integer

  Me.Caption = FORMCAPTION
  cmdOK.Caption = BUTTON1
  cmdClose.Caption = BUTTON2
  lblLabels(0).Caption = LABEL0
  lblLabels(1).Caption = Label1
  lblLabels(2).Caption = Label2
  
  If gbAddTableFlag Then
    Me.Caption = Me.Caption & " à " & frmTblStruct.txtTableName
    For i = 0 To frmTblStruct.lstFields.ListCount - 1
      lstFields.AddItem frmTblStruct.lstFields.List(i)
    Next
  Else
    Me.Caption = Me.Caption & " à " & StripConnect(gnodDBNode2.Text)
    Set tblTableDef = gdbCurrentDB.TableDefs(StripConnect(gnodDBNode2.Text))
    ListItemNames tblTableDef.Fields, lstFields, False
  End If
  If gsDataType <> gsMSACCESS Then
    chkPrimary.Enabled = False
    chkIgnoreNulls.Enabled = False
    chkPrimary.Value = vbGrayed
    chkIgnoreNulls.Value = vbGrayed
  End If
  SetDefaults
  
End Sub

Private Sub txtIndexName_Change()
  cmdOK.Enabled = Len(txtIndexName.Text) > 0 And Len(txtFields.Text) > 0
End Sub

Private Sub cmdOK_Click()
  Dim indIndexObj As Index
  Dim tblTableDefObj As TableDef
  Dim sTmp As String

  On Error GoTo AddIndexErr

  Screen.MousePointer = vbHourglass

  Set indIndexObj = gtdfTableDef.CreateIndex(txtIndexName.Text)
  With indIndexObj
    .Fields = txtFields.Text
    .Unique = chkUnique.Value
    If gsDataType = gsMSACCESS Then
      .Primary = IIf(chkPrimary.Value, True, False)
      .IgnoreNulls = IIf(chkIgnoreNulls.Value = vbChecked, True, False)
    End If
  End With

  ' Ajoute l'index à l'objet TableDef global
  ' À partir de la feuille tblstruct.
  gtdfTableDef.Indexes.Append indIndexObj
  ' Ajoute l'index à la liste.
  frmTblStruct.lstIndexes.AddItem txtIndexName.Text
  ' Active le nouvel élément.
  frmTblStruct.lstIndexes.ListIndex = frmTblStruct.lstIndexes.NewIndex
  
  ' Efface le nom et autorise la saisie d'un autre.
  SetDefaults
  txtIndexName.SetFocus
  
  Screen.MousePointer = vbDefault
  Exit Sub

AddIndexErr:
  ShowError
End Sub

Private Sub SetDefaults()
  txtIndexName.Text = vbNullString
  If gsDataType = gsMSACCESS Then
    txtFields.Text = vbNullString
    chkUnique.Value = vbChecked
  End If
End Sub
