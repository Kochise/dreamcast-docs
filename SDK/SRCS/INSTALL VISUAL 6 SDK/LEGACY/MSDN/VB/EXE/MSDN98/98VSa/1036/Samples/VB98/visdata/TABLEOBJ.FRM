VERSION 5.00
Begin VB.Form frmTableObj 
   Caption         =   "Objet Table"
   ClientHeight    =   3495
   ClientLeft      =   1335
   ClientTop       =   2625
   ClientWidth     =   5580
   HelpContextID   =   2016145
   Icon            =   "TABLEOBJ.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MDIChild        =   -1  'True
   ScaleHeight     =   3480
   ScaleMode       =   0  'User
   ScaleWidth      =   5593.989
   ShowInTaskbar   =   0   'False
   Tag             =   "Recordset"
   Begin VB.PictureBox picViewButtons 
      Align           =   1  'Align Top
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   705
      Left            =   0
      ScaleHeight     =   705
      ScaleMode       =   0  'User
      ScaleWidth      =   5577.292
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   0
      Width           =   5580
      Begin VB.ComboBox cboIndexes 
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   315
         Left            =   720
         Style           =   2  'Dropdown List
         TabIndex        =   8
         Top             =   360
         Width           =   4335
      End
      Begin VB.CommandButton cmdSeek 
         Caption         =   "&Seek"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   330
         Left            =   2835
         TabIndex        =   5
         Top             =   0
         Width           =   900
      End
      Begin VB.CommandButton cmdFilter 
         Caption         =   "F&iltrer"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   330
         Left            =   3735
         TabIndex        =   6
         Top             =   0
         Width           =   900
      End
      Begin VB.CommandButton cmdClose 
         Cancel          =   -1  'True
         Caption         =   "&Fermer"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   330
         Left            =   4644
         TabIndex        =   7
         TabStop         =   0   'False
         Top             =   0
         Width           =   900
      End
      Begin VB.CommandButton cmdDelete 
         Caption         =   "&Effacer"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   330
         Left            =   1935
         TabIndex        =   4
         Top             =   0
         Width           =   900
      End
      Begin VB.CommandButton cmdEdit 
         Caption         =   "&Modifier"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   330
         Left            =   1020
         TabIndex        =   3
         Top             =   0
         Width           =   900
      End
      Begin VB.CommandButton cmdAdd 
         Caption         =   "&Ajouter"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   330
         Left            =   0
         TabIndex        =   2
         Top             =   0
         Width           =   1020
      End
      Begin VB.Label lblIndex 
         Caption         =   "Index:"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   24
         Top             =   400
         Width           =   615
      End
   End
   Begin VB.PictureBox picFieldHeader 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   240
      Left            =   0
      ScaleHeight     =   240
      ScaleMode       =   0  'User
      ScaleWidth      =   14948.92
      TabIndex        =   21
      Top             =   705
      Width           =   14946
      Begin VB.Label lblFieldValue 
         Caption         =   "Valeur (F4=Zoom) "
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   1680
         TabIndex        =   23
         Top             =   0
         Width           =   3165
      End
      Begin VB.Label lblFieldHdr 
         Caption         =   "Nom du champ:"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   252
         Left            =   120
         TabIndex        =   22
         Top             =   0
         Width           =   1212
      End
   End
   Begin VB.PictureBox picChangeButtons 
      BorderStyle     =   0  'None
      Height          =   690
      Left            =   0
      ScaleHeight     =   690
      ScaleMode       =   0  'User
      ScaleWidth      =   5658.375
      TabIndex        =   13
      TabStop         =   0   'False
      Top             =   0
      Visible         =   0   'False
      Width           =   5655
      Begin VB.CommandButton cmdUpdate 
         Caption         =   "&Mettre à jour"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   372
         Left            =   960
         TabIndex        =   15
         Top             =   48
         Width           =   1212
      End
      Begin VB.CommandButton cmdCancel 
         Caption         =   "A&nnuler"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   372
         Left            =   2640
         TabIndex        =   14
         Top             =   48
         Width           =   1212
      End
   End
   Begin VB.PictureBox picStatBox 
      Align           =   2  'Align Bottom
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   0
      ScaleHeight     =   298.153
      ScaleMode       =   0  'User
      ScaleWidth      =   5584.009
      TabIndex        =   19
      TabStop         =   0   'False
      Top             =   3204
      Width           =   5580
      Begin VB.CommandButton cmdNext 
         Caption         =   ">"
         Height          =   287
         Left            =   4200
         TabIndex        =   11
         Top             =   0
         Width           =   375
      End
      Begin VB.CommandButton cmdLast 
         Caption         =   ">|"
         Height          =   287
         Left            =   4575
         TabIndex        =   12
         Top             =   0
         Width           =   375
      End
      Begin VB.CommandButton cmdFirst 
         Caption         =   "|<"
         Height          =   287
         Left            =   0
         TabIndex        =   9
         Top             =   0
         Width           =   375
      End
      Begin VB.CommandButton cmdPrevious 
         Caption         =   "<"
         Height          =   287
         Left            =   375
         TabIndex        =   10
         Top             =   0
         Width           =   375
      End
      Begin VB.Label lblStatus 
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Left            =   735
         TabIndex        =   20
         Top             =   0
         Width           =   3360
      End
   End
   Begin VB.VScrollBar vsbScrollBar 
      Height          =   2616
      LargeChange     =   3000
      Left            =   5040
      SmallChange     =   300
      TabIndex        =   18
      Top             =   960
      Visible         =   0   'False
      Width           =   252
   End
   Begin VB.PictureBox picFields 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   120
      ScaleHeight     =   372
      ScaleMode       =   0  'User
      ScaleWidth      =   4812
      TabIndex        =   16
      TabStop         =   0   'False
      Top             =   960
      Width           =   4815
      Begin VB.TextBox txtFieldData 
         DataSource      =   "Data1"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00000000&
         Height          =   288
         Index           =   0
         Left            =   1560
         TabIndex        =   0
         Top             =   0
         Visible         =   0   'False
         Width           =   3252
      End
      Begin VB.Label lblFieldName 
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   252
         Index           =   0
         Left            =   0
         TabIndex        =   17
         Top             =   60
         Visible         =   0   'False
         Width           =   1572
      End
   End
End
Attribute VB_Name = "frmTableObj"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const BUTTON1 = "&Ajouter"
Const BUTTON2 = "&Modifier"
Const BUTTON3 = "&Supprimer"
Const BUTTON4 = "&Fermer"
Const BUTTON5 = "&Seek"
Const BUTTON6 = "F&iltrer"
Const BUTTON7 = "A&nnuler"
Const BUTTON8 = "&Valider"
Const Label1 = "Nom du champ:"
Const Label2 = "Valeur (F4=Zoom)"
Const MSG1 = "Ajouter un enregistrement"
Const MSG2 = "Longueur de champ insuffisante, données tronquées!"
Const MSG3 = "Effacer l'enregistrement en cours?"
Const MSG4 = "Modifier l'enregistrement"
Const MSG5 = "Entrer une expression de filtre:"
Const MSG6 = "Ouverture de la table"
Const MSG7 = "Redimensionnement de la feuille"
Const MSG8 = "Entrez les paramètres pour la méthode Seek"
Const MSG9 = "Enregistrement introuvable"
'>>>>>>>>>>>>>>>>>>>>>>>>

' Variables de la feuille.
Public mrsFormRecordset As Recordset
Dim msTableName As String        ' Nom de la table du jeu d'enregistrements de la feuille.
Dim mvBookMark As Variant        ' Signet de la feuille.
Dim mbEditFlag As Integer        ' Mode édition
Dim mbAddNewFlag As Integer      ' Mode ajout
Dim mbDataChanged As Integer
Dim mfrmSeek As New frmSeek      ' Recherche les instances de la feuille.
Dim mlNumRows As Long            ' Nombre total de lignes dans la table.

Private Sub cmdAdd_Click()
  On Error GoTo AddErr

  ' Définit le mode.
  mrsFormRecordset.AddNew
  lblStatus.Caption = MSG1
  mbAddNewFlag = True
  If mrsFormRecordset.RecordCount > 0 Then
    mvBookMark = mrsFormRecordset.Bookmark
  Else
    mvBookMark = vbNullString
  End If

  picChangeButtons.Visible = True
  picViewButtons.Visible = False
  cmdNext.Enabled = False
  cmdFirst.Enabled = False
  cmdLast.Enabled = False
  cmdPrevious.Enabled = False

  ClearDataFields Me, mrsFormRecordset.Fields.Count
  txtFieldData(0).SetFocus
  Exit Sub

AddErr:
  ShowError
End Sub

Private Sub cmdCancel_Click()
   On Error Resume Next

   picChangeButtons.Visible = False
   picViewButtons.Visible = True
   cmdNext.Enabled = True
   cmdFirst.Enabled = True
   cmdLast.Enabled = True
   cmdPrevious.Enabled = True

   mbEditFlag = False
   mbAddNewFlag = False
   If Len(mvBookMark) > 0 Then mrsFormRecordset.Bookmark = mvBookMark
   DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
   mbDataChanged = False
   DBEngine.Idle dbFreeLocks

End Sub

Private Sub txtFieldData_Change(Index As Integer)
  ' Définit l'indicateur uniquement si les données ont changé.
  ' La valeur False est réaffectée lors de l'affichage d'un nouvel enregistrement.
  mbDataChanged = True
End Sub

Private Sub txtFieldData_KeyDown(Index As Integer, KeyCode As Integer, Shift As Integer)
  If KeyCode = &H73 Then   'F4
    lblFieldName_DblClick Index

  ElseIf KeyCode = 34 And vsbScrollBar.Visible Then
    ' Une page vers le bas si champs > 10.
    vsbScrollBar.Value = vsbScrollBar.Value - 3000

  ElseIf KeyCode = 33 And vsbScrollBar.Visible Then
    ' Une page vers le haut si champs < 10.
    vsbScrollBar.Value = vsbScrollBar.Value + 3000

  End If
End Sub

Private Sub txtFieldData_KeyPress(Index As Integer, KeyAscii As Integer)
  ' Autorise retour uniquement en mode modification ou ajout.
  If mbEditFlag Or mbAddNewFlag Then
    If KeyAscii = 13 Then
      KeyAscii = 0
      SendKeys "{Tab}"
    End If

  ' Se débarrasse des séquences de touches s'il ne s'agit pas du mode édition ou ajout.
  ElseIf mbEditFlag = False And mbAddNewFlag = False Then
    KeyAscii = 0
  End If

End Sub

Private Sub txtFieldData_LostFocus(Index As Integer)
  On Error GoTo FldDataErr

  If mbDataChanged Then
    ' Enregistrer les données dans le champ.
    mrsFormRecordset(Index) = txtFieldData(Index)
  End If

  ' Réinitialisation pour une condition valide ou d'erreur.
  mbDataChanged = False
  Exit Sub

FldDataErr:
  ShowError
  mbDataChanged = False
End Sub

Private Sub lblFieldName_DblClick(Index As Integer)
  On Error GoTo ZoomErr

  If mrsFormRecordset(Index).Type = dbText Or mrsFormRecordset(Index).Type = dbMemo Then
     If mrsFormRecordset(Index).Type = dbText Then
       gsZoomData = txtFieldData(Index).Text
     ElseIf mrsFormRecordset(Index).FieldSize() < gnGETCHUNK_CUTOFF Then
       gsZoomData = txtFieldData(Index).Text
     Else
       ' Ajoute le reste des données du champ avec Getchunk
       MsgBar "Lecture des données du champ Memo", True
       Screen.MousePointer = vbHourglass
       gsZoomData = txtFieldData(Index).Text & StripNonAscii(mrsFormRecordset(Index).GetChunk(gnGETCHUNK_CUTOFF, gnMAX_MEMO_SIZE))
       Screen.MousePointer = vbDefault
       MsgBar vbNullString, False
     End If
     frmZoom.Caption = Mid(lblFieldName(Index).Caption, 1, Len(lblFieldName(Index).Caption) - 1)
     frmZoom.Top = Top + 1200
     frmZoom.Left = Left + 250
     If mbAddNewFlag Or mbEditFlag Then
       frmZoom.cmdSave.Visible = True
       frmZoom.cmdCloseNoSave.Visible = True
     Else
       frmZoom.cmdClose.Visible = True
     End If
     If mrsFormRecordset(Index).Type = dbText Then
       frmZoom.txtZoomData.Text = gsZoomData
       frmZoom.Height = 1125
     Else
       frmZoom.txtMemo.Text = gsZoomData
       frmZoom.txtMemo.Visible = True
       frmZoom.txtZoomData.Visible = False
       frmZoom.Height = 2205
     End If
     frmZoom.Show vbModal
     If (mbAddNewFlag Or mbEditFlag) And gsZoomData <> "__CANCELLED__" Then
       If mrsFormRecordset(Index).Type = dbText And Len(gsZoomData) > mrsFormRecordset(Index).Size Then
         Beep
         MsgBox MSG2, 48
         txtFieldData(Index).Text = Mid(gsZoomData, 1, mrsFormRecordset(Index).Size)
       Else
         txtFieldData(Index).Text = gsZoomData
       End If
       mrsFormRecordset(Index) = txtFieldData(Index).Text
       mbDataChanged = False
     End If
  End If
  Exit Sub

ZoomErr:
  ShowError
End Sub

Private Sub cboIndexes_Click()
  On Error GoTo IndErr

  If mrsFormRecordset Is Nothing Then Exit Sub
  If mrsFormRecordset.Index = Mid(cboIndexes.Text, 1, InStr(1, cboIndexes.Text, ":") - 1) Then Exit Sub

  mrsFormRecordset.Index = Mid(cboIndexes.Text, 1, InStr(1, cboIndexes.Text, ":") - 1)
  DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
  mbDataChanged = False

  Exit Sub

IndErr:
  ShowError
End Sub

Private Sub cmdClose_Click()
  Unload Me
End Sub

Private Sub vsbScrollBar_Change()
  Dim nTop As Integer

  nTop = vsbScrollBar
  If (nTop - 960) Mod gnCTLARRAYHEIGHT = 0 Then
    picFields.Top = nTop
  Else
    picFields.Top = ((nTop - 960) \ gnCTLARRAYHEIGHT) * gnCTLARRAYHEIGHT + 960
  End If

End Sub

Private Sub cmdDelete_Click()
  On Error GoTo DelRecErr

  If MsgBox(MSG3, vbYesNo + vbQuestion) = vbYes Then
    mrsFormRecordset.Delete
    If gbTransPending Then gbDBChanged = True
    If mrsFormRecordset.EOF = False Then
      mrsFormRecordset.MoveNext
    End If
    mlNumRows = mlNumRows - 1
    DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
    mbDataChanged = False
  End If

  Exit Sub

DelRecErr:
  ShowError
End Sub

Private Sub cmdEdit_Click()
   On Error GoTo EditErr

  Dim nDelay As Long
  Dim nRetryCnt As Integer
  
  Screen.MousePointer = vbHourglass
RetryEdit:
   mrsFormRecordset.Edit
   lblStatus.Caption = MSG4
   mbEditFlag = True
   txtFieldData(0).SetFocus
   mvBookMark = mrsFormRecordset.Bookmark

   picChangeButtons.Visible = True
   picViewButtons.Visible = False
   cmdNext.Enabled = False
   cmdFirst.Enabled = False
   cmdLast.Enabled = False
   cmdPrevious.Enabled = False
   
   Screen.MousePointer = vbDefault
   Exit Sub

EditErr:
  If Err = 3260 And nRetryCnt < gnMURetryCnt Then
    nRetryCnt = nRetryCnt + 1
    DBEngine.Idle dbFreeLocks
    ' Attend le nombre de secondes défini par gnMUDelay.
    nDelay = Timer
    While Timer - nDelay < gnMUDelay
      ' Ne rien faire
    Wend
    Resume RetryEdit
  Else
    ShowError
  End If
End Sub

Private Sub cmdFilter_Click()
  On Error GoTo FilterErr

  Dim sFilter As String
  Dim frmDyn As New frmDynaSnap

  sFilter = InputBox(MSG5)
  If Len(sFilter) = 0 Then Exit Sub

  gsTableDynaFilter = "select * from " & AddBrackets(msTableName) & " where " & sFilter
  frmDyn.Show                           ' Ouvre la feuille du jeu d'enregistrements avec une table filtrée.
  gsTableDynaFilter = vbNullString
  
  Exit Sub

FilterErr:
  ShowError
End Sub

Private Sub cmdFirst_Click()
   On Error GoTo GoFirstError

   mrsFormRecordset.MoveFirst
   DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
   mbDataChanged = False

   Screen.MousePointer = vbDefault
   MsgBar vbNullString, False
   Exit Sub

GoFirstError:
   ShowError
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016145
  End If
End Sub

Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
  If mbEditFlag Or mbAddNewFlag Then Exit Sub
  
  Select Case KeyCode
    Case 35                ' Fin.
      Call cmdLast_Click
    Case 36                ' Origine.
      Call cmdFirst_Click
    Case 38                ' Flèche haut.
      If Shift = 2 Then
        Call cmdFirst_Click
      Else
        Call cmdPrevious_Click
      End If
    Case 40                ' Flèche bas.
      If Shift = 2 Then
        Call cmdLast_Click
      Else
        Call cmdNext_Click
      End If

  End Select

End Sub

Private Sub Form_Load()
   Dim nFieldType As Integer
   Dim i As Integer
   Dim tdf As TableDef
   Dim idx As Index
   Dim sIndex As String

   On Error GoTo TableErr

   cmdAdd.Caption = BUTTON1
   cmdEdit.Caption = BUTTON2
   cmdDelete.Caption = BUTTON3
   cmdClose.Caption = BUTTON4
   cmdSeek.Caption = BUTTON5
   cmdFilter.Caption = BUTTON6
   cmdCancel.Caption = BUTTON7
   cmdUpdate.Caption = BUTTON8
   lblFieldHdr.Caption = Label1
   lblFieldValue.Caption = Label2
   
   Screen.MousePointer = vbHourglass
   MsgBar MSG6, True

   msTableName = mrsFormRecordset.Name
   Set tdf = gdbCurrentDB.TableDefs(msTableName)
   For Each idx In tdf.Indexes
     sIndex = idx.Name
     sIndex = sIndex & ":" & idx.Fields
     If idx.Unique Then
       sIndex = sIndex & ":Unique"
     Else
       sIndex = sIndex & ":Non unique"
     End If
     If idx.Primary Then
       sIndex = sIndex & ":Primaire"
     End If
     cboIndexes.AddItem sIndex
   Next
   
   ' Définit le type de verrouillage.
   If gsDataType = gsMSACCESS Then
     mrsFormRecordset.LockEdits = gnMULocking
   End If

   ' Affiche le premier enregistrement.
   mlNumRows = mrsFormRecordset.RecordCount

   ' Charge les contrôles sur la feuille de la table.
   lblFieldName(0).Visible = True
   txtFieldData(0).Visible = True
   nFieldType = mrsFormRecordset.Fields(0).Type
   txtFieldData(0).Width = GetFieldWidth(nFieldType)
   txtFieldData(0).TabIndex = 0
   If nFieldType = dbText Then txtFieldData(0).MaxLength = mrsFormRecordset.Fields(0).Size
   For i = 1 To mrsFormRecordset.Fields.Count - 1
     picFields.Height = picFields.Height + gnCTLARRAYHEIGHT
     Load lblFieldName(i)
     lblFieldName(i).Top = lblFieldName(i - 1).Top + gnCTLARRAYHEIGHT
     lblFieldName(i).Visible = True
     Load txtFieldData(i)
     txtFieldData(i).Top = txtFieldData(i - 1).Top + gnCTLARRAYHEIGHT
     txtFieldData(i).Visible = True
     nFieldType = mrsFormRecordset.Fields(i).Type
     txtFieldData(i).Width = GetFieldWidth(nFieldType)
     txtFieldData(i).TabIndex = i
     If nFieldType = dbText Then txtFieldData(i).MaxLength = mrsFormRecordset(i).Size
   Next

   ' Redimensionne la fenêtre principale.
   If i <= 10 Then
     Me.Height = ((i + 1) * gnCTLARRAYHEIGHT) + 1600
   Else
     Me.Height = 4668
     Me.Width = Me.Width + 260
     vsbScrollBar.Visible = True
     vsbScrollBar.Min = 900
     vsbScrollBar.Max = 900 - (i * gnCTLARRAYHEIGHT&) + 2500
   End If

   ' Affiche les noms du champ.
   For i = 0 To mrsFormRecordset.Fields.Count - 1
     lblFieldName(i).Caption = mrsFormRecordset(i).Name & ":"
   Next

   If cboIndexes.ListCount > 0 Then
     cboIndexes.ListIndex = 0
   Else
     DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
     mbDataChanged = False
   End If

   Me.Width = 5508
   Me.Left = 1000
   Me.Top = 1000
   
   Screen.MousePointer = vbDefault
   MsgBar vbNullString, False
   Exit Sub

TableErr:
   ShowError
   Unload Me
End Sub

Private Sub Form_Resize()
  On Error Resume Next

  Dim nHeight As Integer
  Dim i As Integer
  Dim nTotWidth As Integer

  If WindowState <> 1 Then   ' Non réduit.
    MsgBar MSG7, True
    ' Vérifie que la feuille est alignée sur le bord supérieur d'un champ.
    nHeight = Me.Height
    If (nHeight - 1660) Mod gnCTLARRAYHEIGHT <> 0 Then
      Me.Height = ((nHeight - 1660) \ gnCTLARRAYHEIGHT) * gnCTLARRAYHEIGHT + 1660
    End If
    ' Redimensionne la barre d'état.
    picStatBox.Top = Me.Height - 650
    ' Redimensionne la barre de défilement.
    vsbScrollBar.Height = picStatBox.Top - (picViewButtons.Top - picFieldHeader.Height) - 1200
    vsbScrollBar.Left = Me.Width - 360
    If mrsFormRecordset.Fields.Count > 10 Then
      picFields.Width = Me.Width - 260
      nTotWidth = vsbScrollBar.Left - 20
    Else
      picFields.Width = Me.Width - 20
      nTotWidth = Me.Width - 50
    End If
    picFieldHeader.Width = Me.Width - 20
    ' Élargit les champs si possible.
    For i = 0 To mrsFormRecordset.Fields.Count - 1
      lblFieldName(i).Width = 0.3 * nTotWidth
      txtFieldData(i).Left = lblFieldName(i).Width + 20
      If mrsFormRecordset(i).Type = dbText Or mrsFormRecordset(i).Type = dbMemo Then
        txtFieldData(i).Width = 0.7 * nTotWidth - 250
      End If
    Next
    lblFieldValue.Left = txtFieldData(0).Left
    lblStatus.Width = Me.Width - 1600
    cmdNext.Left = lblStatus.Width + 745
    cmdLast.Left = cmdNext.Left + 370
  End If
  MsgBar vbNullString, False
End Sub

Private Sub Form_Unload(Cancel As Integer)
  On Error Resume Next

  Unload mfrmSeek   ' Se débarrasse de la feuille de recherche jointe.
  mrsFormRecordset.Close          ' Ferme la table de la feuille.
  DBEngine.Idle dbFreeLocks
  MsgBar vbNullString, False
End Sub

Private Sub cmdLast_Click()
   On Error GoTo GoLastError

   mrsFormRecordset.MoveLast
   ' Affiche l'enregistrement actif.
   DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
   mbDataChanged = False

   Exit Sub

GoLastError:
   ShowError
End Sub

Private Sub cmdNext_Click()
   On Error GoTo GoNextError

   mrsFormRecordset.MoveNext
   ' Affiche l'enregistrement actif.
   DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
   mbDataChanged = False

   Exit Sub

GoNextError:
   ShowError
End Sub

Private Sub cmdPrevious_Click()
   On Error GoTo GoPrevError

   mrsFormRecordset.MovePrevious
   ' Affiche l'enregistrement actif.
   DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
   mbDataChanged = False

   Exit Sub

GoPrevError:
   ShowError
End Sub

Private Sub cmdSeek_Click()
  On Error GoTo SeekErr
  
  Dim sBookMark As String

  If mrsFormRecordset.RecordCount = 0 Then Exit Sub

SeekStart:
  MsgBar MSG8, False
  frmSeek.Show vbModal
  If Len(gsSeekValue) = 0 Then
    MsgBar vbNullString, False
    Exit Sub
  End If

  sBookMark = mrsFormRecordset.Bookmark

  Screen.MousePointer = vbHourglass
  mrsFormRecordset.Seek gsSeekOperator, gsSeekValue
  Screen.MousePointer = vbDefault

  ' Retourne à l'ancien enregistrement si aucune correspondance n'a été trouvée.
  If mrsFormRecordset.NoMatch And Len(sBookMark) > 0 Then
    Beep
    MsgBox MSG9, 48
    mrsFormRecordset.Bookmark = sBookMark
    GoTo SeekStart
  End If

  DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
  mbDataChanged = False
  MsgBar vbNullString, False
  Exit Sub

SeekErr:
  Screen.MousePointer = vbDefault
  MsgBox Error
  Exit Sub
  
End Sub

Private Sub cmdUpdate_Click()
  On Error GoTo UpdateErr

  Dim nDelay As Long
  Dim nRetryCnt As Integer

  Screen.MousePointer = vbHourglass
RetryUpd:
  mrsFormRecordset.Update
  If gbTransPending Then gbDBChanged = True

  If mbAddNewFlag Then
    mlNumRows = mlNumRows + 1
    mrsFormRecordset.MoveLast               ' Se déplace vers le nouvel enregistrement.
  End If

  mbEditFlag = False
  mbAddNewFlag = False
  picChangeButtons.Visible = False
  picViewButtons.Visible = True
  cmdNext.Enabled = True
  cmdFirst.Enabled = True
  cmdLast.Enabled = True
  cmdPrevious.Enabled = True
  DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
  mbDataChanged = False

  DBEngine.Idle dbFreeLocks
  Screen.MousePointer = vbDefault
  Exit Sub

UpdateErr:
  If Err = 3260 And nRetryCnt < gnMURetryCnt Then
    nRetryCnt = nRetryCnt + 1
    mrsFormRecordset.Bookmark = mrsFormRecordset.Bookmark   ' Annuler la mise à jour.
    DBEngine.Idle dbFreeLocks
    nDelay = Timer
    ' Attend gnMUDelay secondes
    While Timer - nDelay < gnMUDelay
      ' Ne rien faire
    Wend
    Resume RetryUpd
  Else
    ShowError
  End If
End Sub
