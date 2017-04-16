VERSION 5.00
Begin VB.Form frmTblStruct 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Modifier la structure"
   ClientHeight    =   6195
   ClientLeft      =   1560
   ClientTop       =   945
   ClientWidth     =   8835
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   HelpContextID   =   2016147
   Icon            =   "TBLSTRU.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6195
   ScaleWidth      =   8835
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.PictureBox picFieldProps 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      Enabled         =   0   'False
      ForeColor       =   &H80000008&
      Height          =   615
      Left            =   3120
      ScaleHeight     =   615
      ScaleWidth      =   4455
      TabIndex        =   40
      TabStop         =   0   'False
      Top             =   4335
      Width           =   4455
      Begin VB.CheckBox chkUnique 
         Caption         =   "Unique"
         Enabled         =   0   'False
         Height          =   255
         Left            =   1560
         MaskColor       =   &H00000000&
         TabIndex        =   45
         TabStop         =   0   'False
         Top             =   0
         Width           =   1230
      End
      Begin VB.CheckBox chkRequiredInd 
         Caption         =   "Required"
         Enabled         =   0   'False
         Height          =   255
         Left            =   120
         MaskColor       =   &H00000000&
         TabIndex        =   44
         TabStop         =   0   'False
         Top             =   360
         Width           =   1230
      End
      Begin VB.CheckBox chkIgnoreNull 
         Caption         =   "IgnoreNull"
         Enabled         =   0   'False
         Height          =   255
         Left            =   1560
         MaskColor       =   &H00000000&
         TabIndex        =   43
         TabStop         =   0   'False
         Top             =   360
         Width           =   1230
      End
      Begin VB.CheckBox chkPrimary 
         Caption         =   "Primary"
         Enabled         =   0   'False
         Height          =   255
         Left            =   120
         MaskColor       =   &H00000000&
         TabIndex        =   42
         TabStop         =   0   'False
         Top             =   0
         Width           =   1230
      End
      Begin VB.CheckBox chkForeign 
         Caption         =   "Foreign"
         Enabled         =   0   'False
         Height          =   255
         Left            =   3120
         MaskColor       =   &H00000000&
         TabIndex        =   41
         TabStop         =   0   'False
         Top             =   0
         Width           =   1230
      End
   End
   Begin VB.PictureBox picFieldProps2 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1695
      Left            =   5640
      ScaleHeight     =   1695
      ScaleWidth      =   3015
      TabIndex        =   38
      TabStop         =   0   'False
      Top             =   2040
      Width           =   3015
      Begin VB.CheckBox chkRequired 
         Caption         =   "Required"
         Height          =   255
         Left            =   1440
         MaskColor       =   &H00000000&
         TabIndex        =   7
         Top             =   360
         Width           =   1215
      End
      Begin VB.CheckBox chkAllowZeroLen 
         Caption         =   "AllowZeroLength"
         Height          =   255
         Left            =   1440
         MaskColor       =   &H00000000&
         TabIndex        =   5
         Top             =   0
         Width           =   1695
      End
      Begin VB.TextBox txtOrdinalPos 
         Height          =   285
         Left            =   0
         TabIndex        =   6
         Top             =   360
         Width           =   1095
      End
      Begin VB.TextBox txtValidationText 
         Height          =   285
         Left            =   0
         TabIndex        =   8
         Top             =   720
         Width           =   2895
      End
      Begin VB.TextBox txtValidationRule 
         Height          =   285
         Left            =   0
         TabIndex        =   9
         Top             =   1080
         Width           =   2895
      End
      Begin VB.TextBox txtDefaultValue 
         Height          =   285
         Left            =   0
         TabIndex        =   10
         Top             =   1440
         Width           =   2895
      End
   End
   Begin VB.PictureBox picFieldProps1 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      Enabled         =   0   'False
      ForeColor       =   &H80000008&
      Height          =   1095
      Left            =   5640
      ScaleHeight     =   1095
      ScaleWidth      =   3015
      TabIndex        =   32
      TabStop         =   0   'False
      Top             =   960
      Width           =   3015
      Begin VB.TextBox txtCollatingOrder 
         Enabled         =   0   'False
         Height          =   285
         Left            =   0
         TabIndex        =   39
         TabStop         =   0   'False
         Top             =   720
         Width           =   1095
      End
      Begin VB.CheckBox chkAutoInc 
         Caption         =   "AutoIncrement"
         Enabled         =   0   'False
         Height          =   255
         Left            =   1440
         MaskColor       =   &H00000000&
         TabIndex        =   37
         TabStop         =   0   'False
         Top             =   720
         Width           =   1400
      End
      Begin VB.CheckBox chkVariable 
         Caption         =   "VariableLength"
         Enabled         =   0   'False
         Height          =   255
         Left            =   1440
         MaskColor       =   &H00000000&
         TabIndex        =   36
         TabStop         =   0   'False
         Top             =   360
         Width           =   1400
      End
      Begin VB.CheckBox chkFixedField 
         Caption         =   "FixedLength"
         Enabled         =   0   'False
         Height          =   255
         Left            =   1440
         MaskColor       =   &H00000000&
         TabIndex        =   35
         TabStop         =   0   'False
         Top             =   0
         Width           =   1400
      End
      Begin VB.TextBox txtFieldSize 
         Enabled         =   0   'False
         Height          =   285
         Left            =   0
         TabIndex        =   34
         TabStop         =   0   'False
         Top             =   360
         Width           =   1095
      End
      Begin VB.ComboBox cboFieldType 
         Enabled         =   0   'False
         Height          =   315
         ItemData        =   "TBLSTRU.frx":000C
         Left            =   0
         List            =   "TBLSTRU.frx":000E
         Style           =   1  'Simple Combo
         TabIndex        =   33
         TabStop         =   0   'False
         Top             =   0
         Width           =   1095
      End
   End
   Begin VB.TextBox txtIndexName 
      Height          =   285
      Left            =   4680
      TabIndex        =   14
      Top             =   3975
      Width           =   2895
   End
   Begin VB.TextBox txtFieldName 
      Height          =   285
      Left            =   5640
      Locked          =   -1  'True
      TabIndex        =   4
      Top             =   480
      Width           =   2895
   End
   Begin VB.TextBox txtFields 
      Height          =   285
      Left            =   4695
      TabIndex        =   15
      TabStop         =   0   'False
      Top             =   5055
      Width           =   3615
   End
   Begin VB.ListBox lstIndexes 
      Height          =   840
      Left            =   120
      TabIndex        =   11
      Top             =   4215
      Width           =   2895
   End
   Begin VB.CommandButton cmdAddTable 
      Caption         =   "&Construire la table"
      Enabled         =   0   'False
      Height          =   375
      HelpContextID   =   2016147
      Left            =   240
      MaskColor       =   &H00000000&
      TabIndex        =   16
      Top             =   5640
      Visible         =   0   'False
      Width           =   2295
   End
   Begin VB.CommandButton cmdClose 
      Cancel          =   -1  'True
      Caption         =   "&Fermer"
      Height          =   375
      Left            =   2760
      MaskColor       =   &H00000000&
      TabIndex        =   17
      Top             =   5640
      Width           =   2175
   End
   Begin VB.CommandButton cmdPrint 
      Caption         =   "&Imprimer la structure"
      Height          =   375
      Left            =   5160
      MaskColor       =   &H00000000&
      TabIndex        =   18
      Top             =   5640
      Visible         =   0   'False
      Width           =   2295
   End
   Begin VB.CommandButton cmdRemoveIndex 
      Caption         =   "Su&pprimer l'index"
      Height          =   375
      Left            =   1560
      MaskColor       =   &H00000000&
      TabIndex        =   13
      Top             =   5115
      Width           =   1440
   End
   Begin VB.CommandButton cmdAddIndex 
      Caption         =   "&Ajouter un index"
      Height          =   375
      Left            =   120
      MaskColor       =   &H00000000&
      TabIndex        =   12
      Top             =   5115
      Width           =   1440
   End
   Begin VB.ListBox lstFields 
      Height          =   2595
      Left            =   105
      TabIndex        =   1
      Top             =   720
      Width           =   3945
   End
   Begin VB.CommandButton cmdAddField 
      Caption         =   "Ajouter un &champ"
      Height          =   375
      Left            =   105
      MaskColor       =   &H00000000&
      TabIndex        =   2
      Top             =   3360
      Width           =   1650
   End
   Begin VB.CommandButton cmdRemoveField 
      Caption         =   "&Supprimer le champ"
      Height          =   375
      Left            =   1890
      MaskColor       =   &H00000000&
      TabIndex        =   3
      Top             =   3360
      Width           =   1965
   End
   Begin VB.TextBox txtTableName 
      Height          =   285
      Left            =   1920
      TabIndex        =   0
      Top             =   120
      Width           =   3135
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Nom: "
      Height          =   195
      Index           =   24
      Left            =   3240
      TabIndex        =   31
      Top             =   3975
      Width           =   510
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Nom: "
      Height          =   195
      Index           =   20
      Left            =   4395
      TabIndex        =   30
      Top             =   480
      Width           =   510
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Champs: "
      Height          =   300
      Index           =   23
      Left            =   3780
      TabIndex        =   29
      Top             =   5055
      Width           =   510
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "DefaultValue: "
      Height          =   195
      Index           =   10
      Left            =   4395
      TabIndex        =   28
      Top             =   3480
      Width           =   1020
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "ValidationRule: "
      Height          =   195
      Index           =   9
      Left            =   4395
      TabIndex        =   27
      Top             =   3120
      Width           =   1110
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "ValidationText: "
      Height          =   195
      Index           =   8
      Left            =   4395
      TabIndex        =   26
      Top             =   2760
      Width           =   1125
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "OrdinalPosition: "
      Height          =   195
      Index           =   7
      Left            =   4395
      TabIndex        =   25
      Top             =   2400
      Width           =   1170
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Size: "
      Height          =   195
      Index           =   5
      Left            =   4395
      TabIndex        =   24
      Top             =   1320
      Width           =   390
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Type: "
      Height          =   195
      Index           =   4
      Left            =   4395
      TabIndex        =   23
      Top             =   960
      Width           =   465
   End
   Begin VB.Line Line1 
      BorderWidth     =   3
      X1              =   120
      X2              =   8715
      Y1              =   3840
      Y2              =   3840
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "CollatingOrder: "
      Height          =   195
      Index           =   22
      Left            =   4395
      TabIndex        =   22
      Top             =   1680
      Width           =   1140
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   " Liste des index: "
      Height          =   195
      Index           =   2
      Left            =   120
      TabIndex        =   21
      Top             =   3975
      Width           =   855
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Liste des champs: "
      Height          =   195
      Index           =   1
      Left            =   120
      TabIndex        =   20
      Top             =   480
      Width           =   720
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Nom de la table: "
      Height          =   195
      Index           =   0
      Left            =   120
      TabIndex        =   19
      Top             =   120
      Width           =   945
   End
End
Attribute VB_Name = "frmTblStruct"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "Modifier la structure"
Const BUTTON1 = "&Ajouter un champ"
Const BUTTON2 = "&Supprimer le champ"
Const BUTTON3 = "Ajouter un &index"
Const BUTTON4 = "Su&pprimer l'index"
Const BUTTON5 = "&Créer la table"
Const BUTTON6 = "&Fermer"
Const BUTTON7 = "&Imprimer la structure"
Const Label1 = "&Nom de la table:"
Const Label2 = "&Liste des champs:"
Const LABEL3 = "Liste des inde&x:"
Const MSG1 = "Entrez les nouveaux paramètres de champ, puis cliquez sur 'OK'"
Const MSG2 = " Entrez les nouveaux paramètres d'index, puis cliquez sur 'OK'"
Const MSG3 = "Ajout de la nouvelle table à la base de données"
Const MSG4 = "Supprimer l'index?"
Const MSG5 = "Ouverture de la feuille de conception"
Const MSG6 = "Impression de la structure de la table"
Const MSG7 = "Supprimer le champ?"
Const MSG8 = "Fermer sans enregistrer?"
'>>>>>>>>>>>>>>>>>>>>>>>>

Dim msCurrField As String
Dim mfldCurrFld As Field
Dim msCurrIndex As String
Dim mindCurrInd As Index
Dim mnFldCount As Integer
Dim mnIndCount As Integer
Dim mbTableNameChanged As Boolean

Sub cboFieldType_Change()
  If mfldCurrFld.Type < 9 Then
    cboFieldType.ListIndex = mfldCurrFld.Type - 1
  Else
    cboFieldType.ListIndex = mfldCurrFld.Type - 2
  End If
End Sub

Sub cboFieldType_Click()
  If cboFieldType.ListIndex = -1 Then Exit Sub
  If mfldCurrFld.Type < 9 Then
    cboFieldType.ListIndex = mfldCurrFld.Type - 1
  Else
    cboFieldType.ListIndex = mfldCurrFld.Type - 2
  End If
End Sub

Private Sub chkAllowZeroLen_Click()
  On Error GoTo AZErr
  
  If mfldCurrFld Is Nothing Then Exit Sub
  
  mfldCurrFld.AllowZeroLength = IIf(chkAllowZeroLen.Value = vbChecked, True, False)
  Exit Sub
  
AZErr:
  ShowError
End Sub


Private Sub chkRequired_Click()
  On Error GoTo RQErr
  If mfldCurrFld Is Nothing Then Exit Sub
  
  mfldCurrFld.Required = IIf(chkRequired.Value = vbChecked, True, False)
  Exit Sub
  
RQErr:
  ShowError
End Sub

Private Sub cmdAddField_Click()
  MsgBar MSG1, False
  frmAddField.Show vbModal
  MsgBar vbNullString, False
End Sub

Private Sub cmdAddIndex_Click()
  MsgBar MSG2, False
  frmAddIndex.Show vbModal
  MsgBar vbNullString, False
End Sub

Private Sub cmdAddTable_Click()
  On Error GoTo ATErr

  Dim i As Integer

  If DupeTableName(gtdfTableDef.Name) Then
    Screen.MousePointer = vbDefault
    Exit Sub
  End If
  
  Screen.MousePointer = vbHourglass
  MsgBar MSG3, True

  ' Ajoute l'objet Tabledef.
  gdbCurrentDB.TableDefs.Append gtdfTableDef

  RefreshTables Nothing

  Screen.MousePointer = vbDefault
  MsgBar vbNullString, False
  Unload Me
  Exit Sub

ATErr:
  ShowError
End Sub

Private Sub cmdClose_Click()
  If mbTableNameChanged Then
    RefreshTables Nothing
  End If
  If cmdAddTable.Visible And cmdAddTable.Enabled Then
    If MsgBox(MSG8, vbYesNo + vbQuestion, Me.Caption) = vbYes Then
      Unload Me
      MsgBar vbNullString, False
    End If
  Else
    Unload Me
    MsgBar vbNullString, False
  End If
End Sub

Sub lstFields_Click()
  On Error GoTo FErr

  If lstFields.ListIndex = -1 Then Exit Sub
  
  msCurrField = lstFields.Text
  Set mfldCurrFld = gtdfTableDef.Fields(msCurrField)
    
  ' Active ces champs uniquement s'il existe un champ en
  ' cours dans une base de données Access.
  txtFieldName.Enabled = (gsDataType = gsMSACCESS)
  txtValidationText.Enabled = (gsDataType = gsMSACCESS)
  txtValidationRule.Enabled = (gsDataType = gsMSACCESS)
  txtDefaultValue.Enabled = (gsDataType = gsMSACCESS)
  chkRequired.Enabled = (gsDataType = gsMSACCESS)
  chkAllowZeroLen.Enabled = (gsDataType = gsMSACCESS)
  txtOrdinalPos.Enabled = (gsDataType = gsMSACCESS)
  
  ' Déverrouille le champ du nom.
  txtFieldName.Locked = False
  txtFieldName.Text = mfldCurrFld.Name
  txtOrdinalPos.Text = mfldCurrFld.OrdinalPosition
  If mfldCurrFld.Type < 9 Then
    cboFieldType.ListIndex = mfldCurrFld.Type - 1
  Else
    cboFieldType.ListIndex = mfldCurrFld.Type - 2
  End If
  txtFieldSize.Text = mfldCurrFld.Size
  txtCollatingOrder.Text = mfldCurrFld.CollatingOrder
  chkFixedField.Value = IIf((mfldCurrFld.Attributes And dbFixedField) = dbFixedField, 1, 0)
  chkVariable.Value = IIf((mfldCurrFld.Attributes And dbVariableField) = dbVariableField, 1, 0)
  chkAutoInc.Value = IIf((mfldCurrFld.Attributes And dbAutoIncrField) = dbAutoIncrField, 1, 0)
  
  If gsDataType = gsMSACCESS Then
    txtValidationText.Text = mfldCurrFld.ValidationText
    txtValidationRule.Text = mfldCurrFld.ValidationRule
    txtDefaultValue.Text = mfldCurrFld.DefaultValue
    chkRequired.Value = IIf(mfldCurrFld.Required, 1, 0)
    chkAllowZeroLen.Value = IIf(mfldCurrFld.AllowZeroLength, 1, 0)
  End If
  
  Exit Sub
  
FErr:
  ShowError
End Sub

Sub lstIndexes_Click()
  On Error GoTo IErr

  If lstIndexes.ListIndex = -1 Then Exit Sub
  
  msCurrIndex = lstIndexes.Text
  Set mindCurrInd = gtdfTableDef.Indexes(msCurrIndex)
    
  txtIndexName.Text = mindCurrInd.Name
  txtFields.Text = mindCurrInd.Fields
  chkRequiredInd.Value = IIf(mindCurrInd.Required, 1, 0)
  chkUnique.Value = IIf(mindCurrInd.Unique, 1, 0)
  chkIgnoreNull.Value = IIf(mindCurrInd.IgnoreNulls, 1, 0)
  
  If gsDataType = gsMSACCESS Then
    chkPrimary.Value = IIf(mindCurrInd.Primary, 1, 0)
    chkForeign.Value = IIf(mindCurrInd.Foreign, 1, 0)
  End If
  
  Exit Sub
  
IErr:
  ShowError
End Sub

Private Sub txtCollatingOrder_LostFocus()
  If mfldCurrFld Is Nothing Then Exit Sub
  
  ' Le redéfinit car il est en lecture seule.
  txtCollatingOrder.Text = mfldCurrFld.CollatingOrder
End Sub

Private Sub txtDefaultValue_LostFocus()
  On Error GoTo DVErr
  
  If mfldCurrFld Is Nothing Then Exit Sub
  
  If mfldCurrFld.DefaultValue <> txtDefaultValue.Text Then
    If Len(txtDefaultValue.Text) > 0 Then
      mfldCurrFld.DefaultValue = txtDefaultValue.Text
    End If
  End If
  Exit Sub
  
DVErr:
  ShowError
End Sub

Private Sub txtFieldName_LostFocus()
  On Error GoTo FNErr
  
  Dim i As Integer
  
  If mfldCurrFld Is Nothing Then Exit Sub
  
  ' Modifie le nom si l'utilisateur l'a modifié.
  If mfldCurrFld.Name <> txtFieldName.Text Then
    If Len(txtFieldName.Text) > 0 Then
      For i = 0 To lstFields.ListCount - 1
        If lstFields.List(i) = mfldCurrFld.Name Then
          lstFields.RemoveItem i
          lstFields.AddItem txtFieldName.Text, i
          Exit For
        End If
      Next
      mfldCurrFld.Name = txtFieldName.Text
    End If
  End If
  Exit Sub
  
FNErr:
  ShowError
End Sub

Sub txtFields_LostFocus()
  If mindCurrInd Is Nothing Then Exit Sub
  
  ' Le redéfinit car il est en lecture seule.
  txtFields.Text = mindCurrInd.Fields
End Sub

Private Sub txtFieldSize_LostFocus()
  If mfldCurrFld Is Nothing Then Exit Sub
  
  ' Le redéfinit car il est en lecture seule.
  txtFieldSize.Text = mfldCurrFld.Size
End Sub

Private Sub txtIndexName_LostFocus()
  On Error GoTo IDNErr
  
  Dim i As Integer
  
  If mindCurrInd Is Nothing Then Exit Sub
  
  ' Modifie le nom si l'utilisateur l'a modifié.
  If mindCurrInd.Name <> txtIndexName.Text Then
    If Len(txtIndexName.Text) > 0 And gsDataType = gsMSACCESS Then
      For i = 0 To lstIndexes.ListCount - 1
        If lstIndexes.List(i) = mindCurrInd.Name Then
          lstIndexes.RemoveItem i
          lstIndexes.AddItem txtIndexName.Text, i
          Exit For
        End If
      Next
      mindCurrInd.Name = txtIndexName.Text
    End If
  End If
  Exit Sub
  
IDNErr:
  ShowError
End Sub

Private Sub txtOrdinalPos_LostFocus()
  On Error GoTo OPErr
  
  If mfldCurrFld Is Nothing Then Exit Sub
  
  If mfldCurrFld.OrdinalPosition <> txtOrdinalPos.Text Then
    If Len(txtFieldName.Text) > 0 And gsDataType = gsMSACCESS Then
      mfldCurrFld.OrdinalPosition = txtOrdinalPos.Text
    End If
  End If
  Exit Sub
  
OPErr:
  ShowError
End Sub

Private Sub txtTableName_Change()
  If gbAddTableFlag Then
    If Len(txtTableName.Text) > 0 And lstFields.ListCount > 0 Then
      cmdAddTable.Enabled = True
    Else
      cmdAddTable.Enabled = False
    End If
    gtdfTableDef.Name = txtTableName.Text
  End If
End Sub

Private Sub txtTableName_LostFocus()
  On Error GoTo TBNErr
  
  Dim i As Integer
  
  ' Modifie le nom si l'utilisateur l'a modifié.
  If gtdfTableDef.Name <> txtTableName.Text Then
    If Len(txtTableName.Text) > 0 And gsDataType = gsMSACCESS Then
      ' Cherche et renomme l'entrée dans la liste de la feuille des tables.
      gtdfTableDef.Name = txtTableName.Text
      mbTableNameChanged = True
    End If
  End If
  Exit Sub
  
TBNErr:
  ShowError
End Sub

Private Sub txtTableName_KeyPress(KeyAscii As Integer)
  If txtTableName.TabStop = False Then
    KeyAscii = 0   ' Se débarrasse de la touche.
  End If
End Sub

Private Sub cmdRemoveIndex_Click()
  On Error GoTo DELErr

  If lstIndexes.ListIndex < 0 Then Exit Sub
  
  If MsgBox(MSG4, vbYesNo + vbQuestion) = vbYes Then
    If gbAddTableFlag = False Then
      gtdfTableDef.Indexes.Delete lstIndexes.Text
    End If
    ' Rachraîchit la liste des index.
    lstIndexes.RemoveItem lstIndexes.ListIndex
  End If
  
  ' Efface les propriétés.
  txtIndexName.Text = vbNullString
  txtFields.Text = vbNullString
  chkRequiredInd.Value = vbUnchecked
  chkUnique.Value = vbUnchecked
  chkIgnoreNull.Value = vbUnchecked
  chkPrimary.Value = vbUnchecked
  chkForeign.Value = vbUnchecked
  
  Exit Sub

DELErr:
  ShowError
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016147
  End If
End Sub

Private Sub Form_Load()
  On Error GoTo LoadErr
  
  Dim fld As Field
  Dim idx As Index
  
  Me.Caption = FORMCAPTION
  cmdAddField.Caption = BUTTON1
  cmdRemoveField.Caption = BUTTON2
  cmdAddIndex.Caption = BUTTON3
  cmdRemoveIndex.Caption = BUTTON4
  cmdAddTable.Caption = BUTTON5
  cmdClose.Caption = BUTTON6
  cmdPrint.Caption = BUTTON7
  lblLabels(0).Caption = Label1
  lblLabels(1).Caption = Label2
  lblLabels(2).Caption = LABEL3
  
  Screen.MousePointer = vbHourglass
  MsgBar MSG5, True
  
  cboFieldType.AddItem "Boolean"
  cboFieldType.AddItem "Byte"
  cboFieldType.AddItem "Integer"
  cboFieldType.AddItem "Long"
  cboFieldType.AddItem "Currency"
  cboFieldType.AddItem "Single"
  cboFieldType.AddItem "Double"
  cboFieldType.AddItem "Date/Time"
  cboFieldType.AddItem "Text"
  cboFieldType.AddItem "Binary"
  cboFieldType.AddItem "Memo"
  
  If gbAddTableFlag Then
    Set gtdfTableDef = gdbCurrentDB.CreateTableDef()
    mnFldCount = 0
    mnIndCount = 0
    cmdAddTable.Visible = True
  Else
    cmdPrint.Visible = True
    Set gtdfTableDef = gdbCurrentDB.TableDefs(StripConnect(gnodDBNode2.Text))
    txtTableName.Text = gtdfTableDef.Name
    ListItemNames gtdfTableDef.Fields, lstFields, False
    mnFldCount = lstFields.ListCount
    lstFields.ListIndex = 0
    ListItemNames gtdfTableDef.Indexes, lstIndexes, False
    mnIndCount = lstIndexes.ListCount
    If mnIndCount > 0 Then lstIndexes.ListIndex = 0
  End If
  
  If gsDataType <> gsMSACCESS Then
    ' Impossible de modifier les noms des tables non mdb.
    If gbAddTableFlag = False Then txtTableName.Locked = True
    ' Impossible de supprimer les tables non mdb.
    If gbAddTableFlag = False Then cmdRemoveField.Enabled = False
    ' Désactive les propriétés non modifiables sur des tables non mdb.
    txtFieldName.Locked = True
    chkRequired.Enabled = False
    chkAllowZeroLen.Enabled = False
    
    txtIndexName.Locked = True
    txtFields.Locked = True
  End If
  
  Screen.MousePointer = vbDefault
  MsgBar vbNullString, False
  Exit Sub

LoadErr:
  ShowError
  Unload Me
End Sub

Private Sub cmdPrint_Click()
  On Error GoTo PRTErr
  
  ' Cette procédure imprime uniquement la définition
  ' de la table courante sélectionnée.

  Dim i As Integer
  Dim sTmp As String

  MsgBar MSG6, True
  Printer.Print
  Printer.Print
  Printer.Print
  Printer.Print "Base de données: " & gsDBName
  Printer.Print
  Printer.Print
  Printer.Print "Définition de la table pour " & txtTableName
  Printer.Print
  Printer.Print
  Printer.Print "Champs: (Nom - Type - Taille)"
  Printer.Print String(60, "-")
  For i = 0 To lstFields.ListCount - 1
    lstFields.ListIndex = i
    sTmp = txtFieldName.Text & " - "
    sTmp = sTmp & cboFieldType.Text & " - "
    sTmp = sTmp & txtFieldSize.Text
    Printer.Print sTmp
  Next
  Printer.Print
  Printer.Print
  Printer.Print "Index: (Nom - Champs - Unique)"
  Printer.Print String(60, "-")
  For i = 0 To lstIndexes.ListCount - 1
    sTmp = txtIndexName.Text & " - "
    sTmp = sTmp & txtFields.Text & " - "
    sTmp = sTmp & IIf(chkUnique = 1, "True", "False")
    Printer.Print sTmp
  Next
  Printer.NewPage
  Printer.EndDoc
  MsgBar vbNullString, False
  Exit Sub
  
PRTErr:
  ShowError
End Sub

Private Sub cmdRemoveField_Click()
  On Error GoTo RFErr

  If lstFields.ListIndex < 0 Then Exit Sub

  If MsgBox(MSG7, vbYesNo + vbQuestion) = vbYes Then
    ' Efface les valeurs de la propriété Text des champs.
    txtFieldName.Text = vbNullString
    txtOrdinalPos.Text = vbNullString
    cboFieldType.ListIndex = -1
    cboFieldType.Text = vbNullString
    txtFieldSize.Text = vbNullString
    txtCollatingOrder.Text = vbNullString
    chkFixedField.Value = vbUnchecked
    chkVariable.Value = vbUnchecked
    chkAutoInc.Value = vbUnchecked
    txtValidationText.Text = vbNullString
    txtValidationRule.Text = vbNullString
    txtDefaultValue.Text = vbNullString
    chkRequired.Value = vbUnchecked
    chkAllowZeroLen.Value = vbUnchecked
    ' Supprime de la structure Tabledef.
    gtdfTableDef.Fields.Delete lstFields.Text
    ' Supprime de la liste.
    lstFields.RemoveItem lstFields.ListIndex
  End If
  If lstFields.ListCount = 0 Then
    ' Aucun champ; désactive le bouton Créer la table.
    cmdAddTable.Enabled = False
  End If
  
  Exit Sub

RFErr:
  ShowError
End Sub


Private Sub txtValidationRule_LostFocus()
  On Error GoTo VRErr
  
  If mfldCurrFld Is Nothing Then Exit Sub
  
  If mfldCurrFld.ValidationRule <> txtValidationRule.Text Then
    If Len(txtValidationRule.Text) > 0 And gsDataType = gsMSACCESS Then
      mfldCurrFld.ValidationRule = txtValidationRule.Text
    End If
  End If
  Exit Sub
  
VRErr:
  ShowError
End Sub

Private Sub txtValidationText_LostFocus()
  On Error GoTo VTErr
  
  If mfldCurrFld Is Nothing Then Exit Sub
  
  If mfldCurrFld.ValidationText <> txtValidationText.Text Then
    If Len(txtValidationText.Text) > 0 And gsDataType = gsMSACCESS Then
      mfldCurrFld.ValidationText = txtValidationText.Text
    End If
  End If
  Exit Sub
  
VTErr:
  ShowError
End Sub
