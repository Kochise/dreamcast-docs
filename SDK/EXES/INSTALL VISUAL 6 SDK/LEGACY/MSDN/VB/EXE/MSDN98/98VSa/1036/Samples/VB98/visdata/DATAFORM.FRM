VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmDataControl 
   Caption         =   "Contrôle Data"
   ClientHeight    =   2160
   ClientLeft      =   1230
   ClientTop       =   3075
   ClientWidth     =   5775
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   HelpContextID   =   2016122
   Icon            =   "DATAFORM.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form2"
   LockControls    =   -1  'True
   MDIChild        =   -1  'True
   ScaleHeight     =   2160
   ScaleWidth      =   5775
   ShowInTaskbar   =   0   'False
   Tag             =   "Recordset"
   Begin VB.PictureBox picButtons 
      Align           =   1  'Align Top
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   600
      Left            =   0
      ScaleHeight     =   600
      ScaleWidth      =   5775
      TabIndex        =   0
      Top             =   0
      Width           =   5772
      Begin VB.CommandButton cmdCancelAdd 
         Caption         =   "A&nnuler"
         Height          =   330
         Left            =   -15
         MaskColor       =   &H00000000&
         TabIndex        =   13
         Top             =   0
         Visible         =   0   'False
         Width           =   960
      End
      Begin VB.CommandButton cmdRefresh 
         Caption         =   "A&ctualiser"
         Height          =   330
         Left            =   3852
         MaskColor       =   &H00000000&
         TabIndex        =   12
         Top             =   0
         Width           =   960
      End
      Begin VB.CommandButton cmdFind 
         Caption         =   "&Rechercher"
         Height          =   330
         Left            =   2880
         MaskColor       =   &H00000000&
         TabIndex        =   5
         Top             =   0
         Width           =   960
      End
      Begin VB.CommandButton cmdClose 
         Cancel          =   -1  'True
         Caption         =   "&Fermer"
         Height          =   330
         Left            =   4800
         MaskColor       =   &H00000000&
         TabIndex        =   4
         Top             =   0
         Width           =   960
      End
      Begin VB.CommandButton cmdDelete 
         Caption         =   "&Supprimer"
         Height          =   330
         Left            =   1920
         MaskColor       =   &H00000000&
         TabIndex        =   3
         Top             =   0
         Width           =   960
      End
      Begin VB.CommandButton cmdAdd 
         Caption         =   "&Ajouter"
         Height          =   330
         Left            =   0
         MaskColor       =   &H00000000&
         TabIndex        =   2
         Top             =   0
         Width           =   960
      End
      Begin VB.CommandButton cmdUpdate 
         Caption         =   "&Valider"
         Height          =   330
         Left            =   960
         MaskColor       =   &H00000000&
         TabIndex        =   1
         Top             =   0
         Width           =   960
      End
      Begin VB.Label lblFieldHeader 
         Caption         =   "Nom:"
         Height          =   255
         Left            =   120
         TabIndex        =   15
         Top             =   360
         Width           =   1215
      End
      Begin VB.Label lblFieldValue 
         Caption         =   "Valeur:"
         Height          =   255
         Left            =   1680
         TabIndex        =   14
         Top             =   360
         Width           =   2655
      End
   End
   Begin VB.Data datDataCtl 
      Align           =   2  'Align Bottom
      Connect         =   "Access"
      DatabaseName    =   ""
      DefaultCursorType=   0  'DefaultCursor
      DefaultType     =   2  'UseODBC
      Exclusive       =   0   'False
      Height          =   345
      Left            =   0
      Options         =   0
      ReadOnly        =   0   'False
      RecordsetType   =   1  'Dynaset
      RecordSource    =   ""
      Tag             =   "OLE"
      Top             =   1815
      Width           =   5772
   End
   Begin VB.VScrollBar vsbScrollBar 
      Height          =   2440
      LargeChange     =   3000
      Left            =   7665
      SmallChange     =   300
      TabIndex        =   11
      Top             =   630
      Visible         =   0   'False
      Width           =   255
   End
   Begin VB.PictureBox picFields 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   1065
      Left            =   0
      ScaleHeight     =   1056.479
      ScaleMode       =   0  'User
      ScaleWidth      =   7600.264
      TabIndex        =   6
      TabStop         =   0   'False
      Top             =   600
      Width           =   7605
      Begin VB.TextBox txtFieldData 
         DataSource      =   "datDataCtl"
         ForeColor       =   &H00000000&
         Height          =   285
         Index           =   0
         Left            =   1665
         TabIndex        =   9
         Top             =   0
         Visible         =   0   'False
         Width           =   3255
      End
      Begin VB.CheckBox chkFieldData 
         DataSource      =   "datDataCtl"
         Height          =   282
         Index           =   0
         Left            =   1680
         MaskColor       =   &H00000000&
         TabIndex        =   8
         Top             =   735
         Visible         =   0   'False
         Width           =   3270
      End
      Begin VB.PictureBox picFieldData 
         BackColor       =   &H80000005&
         DataSource      =   "datDataCtl"
         Height          =   285
         Index           =   0
         Left            =   1680
         ScaleHeight     =   225
         ScaleWidth      =   3210
         TabIndex        =   7
         Top             =   360
         Visible         =   0   'False
         Width           =   3270
      End
      Begin VB.OLE oleFieldData 
         BackColor       =   &H00FFFFFF&
         DataSource      =   "datDataCtl"
         DisplayType     =   1  'Icon
         Height          =   300
         Index           =   0
         Left            =   1680
         TabIndex        =   16
         Top             =   360
         Visible         =   0   'False
         Width           =   3255
      End
      Begin VB.Label lblFieldName 
         ForeColor       =   &H00000000&
         Height          =   195
         Index           =   0
         Left            =   105
         TabIndex        =   10
         Top             =   0
         Visible         =   0   'False
         Width           =   300
      End
   End
   Begin MSComDlg.CommonDialog dlgCMD1 
      Left            =   2415
      Top             =   1755
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      FilterIndex     =   1019
   End
End
Attribute VB_Name = "frmDataControl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const BUTTON1 = "A&nnuler"
Const BUTTON2 = "&Valider"
Const BUTTON3 = "&Supprimer"
Const BUTTON4 = "&Rechercher"
Const BUTTON5 = "A&ctualiser"
Const BUTTON6 = "&Fermer"
Const BUTTON7 = "&Ajouter"
Const Label1 = "Nom:"
Const Label2 = "Valeur:"
Const MSG1 = "Nouvel enregistrement"
Const MSG2 = "Sélectionnez un fichier d'image à charger"
Const MSG3 = "L'événement d'erreur de donnée renvoie l'erreur:"
Const MSG4 = "Enregistrer?"
Const MSG5 = "Accepter les modifications?"
Const MSG6 = "Accepter les modifications avant de fermer?"
Const MSG7 = "Supprimer l'enregistrement en cours?"
Const MSG8 = "Entrer la valeur de recherche:"
Const MSG9 = "Entrer l'expression de recherche:"
Const MSG10 = " Lignes"
Const MSG11 = " Lignes (Jeu d'enregistrements en avant seulement)"
Const MSG12 = "  [Mise à jour impossible]"
Const MSG13 = "Cette fonction n'est pas disponible pour requêtes paramètrisées"
'>>>>>>>>>>>>>>>>>>>>>>>>

'============================================================================
' Ceci est une feuille assez courante utilisable dans de nombreux
' cas avec des tables ou des objets Querydef.
'============================================================================

Dim maFldArr() As Object
Public mrsFormRecordset As Recordset
Public mbIsParameterized As Boolean
Dim mvBookMark As Variant        ' Signet de la feuille.
Dim mnNumFields As Integer       ' Nombre de champs.
Dim mlNumRows As Long            ' Propriété Recordcount pour le jeu d'enregistrements.
Dim mbJustUsedFind As Boolean    ' Indicateur de fonction de recherche.
Dim mbResizing As Boolean        ' Indicateur empêchant la répétition du redimensionnement.
Dim mbCancel As Boolean          ' Indicateur annulant la méthode Addnew.
Dim mnFieldTop As Integer        ' Position du champ supérieur.

Const mnMSGBOX_TYPE = vbYesNo + vbQuestion
Const mnCTLARRAYHEIGHT = 340

Private Sub cmdAdd_Click()
  On Error GoTo AddErr

  datDataCtl.Recordset.AddNew
  datDataCtl.Caption = MSG1
  cmdCancelAdd.Visible = True
  cmdAdd.Visible = False
  If datDataCtl.Recordset.RecordCount <> 0 Then
    mvBookMark = datDataCtl.Recordset.Bookmark
    maFldArr(0).SetFocus
  End If

  Exit Sub
  
AddErr:
  ShowErrMsg

End Sub

Private Sub cmdCancelAdd_Click()
  On Error Resume Next

  mbCancel = True
  ' Retourne à l'enregistrement en cours précédent.
  If Len(mvBookMark) > 0 Then
    datDataCtl.Recordset.Bookmark = mvBookMark
  End If

End Sub

'----------------------------------------------------------
' Cette procédure charge la feuille de propriété du contrôle Data
' le met en commentaire pour une utilisation autonome.
'----------------------------------------------------------
Sub datDataCtl_MouseUp(BUTTON As Integer, Shift As Integer, x As Single, y As Single)
  On Error GoTo DCPErr

  Dim i As Integer
  Dim recClone As Recordset
  Dim sTmpRS As String
  Dim sTmpDB As String
  Dim sTmpTag As String
  
  If BUTTON = 2 Then
    If mbIsParameterized Then
      MsgBox MSG13, vbInformation
      Exit Sub
    End If
  
    Screen.MousePointer = vbHourglass
    sTmpRS = datDataCtl.RecordSource
    sTmpDB = datDataCtl.DatabaseName
    sTmpTag = datDataCtl.Tag
    Set gDataCtlObj = datDataCtl
    frmDataCtlProp.Show vbModal
    If Not gDataCtlObj Is Nothing Then
      ' Vérifie si un jeu d'enregistrements, une base de
      ' données ou un type binaire lié a changé
      ' et efface les champs liés si un a changé de données ou un type binaire lié a changé
      If (sTmpRS <> gDataCtlObj.RecordSource Or sTmpDB <> gDataCtlObj.DatabaseName) _
         Or gDataCtlObj.Tag <> sTmpTag Then
        ' Efface les noms de champ et dissocie les contrôles.
        For i = 0 To mnNumFields - 1
          lblFieldName(i).Caption = vbNullString
          maFldArr(i).DataField = vbNullString
          maFldArr(i).Visible = False
        Next
      End If
      datDataCtl.Refresh
      If (sTmpRS <> gDataCtlObj.RecordSource Or sTmpDB <> gDataCtlObj.DatabaseName) _
         Or gDataCtlObj.Tag <> sTmpTag Then
        Set recClone = datDataCtl.Recordset.Clone()
        If recClone.BOF = False And (datDataCtl.Options And dbForwardOnly) = 0 Then
          recClone.MoveLast
          mlNumRows = recClone.RecordCount
        Else
          mlNumRows = 0
        End If
        recClone.Close
        LoadFields
        SetRecNum
      Else
        ' Il faut actualiser la copie du jeu
        ' d'enregistrements local pour d'autres opérations
        ' l'utilisant pour accéder aux propriétés.
        Set mrsFormRecordset = datDataCtl.Recordset
        ' S'il s'agit d'un jeu d'enregistrements de type
        ' en avant seulement, la méthode SetRecNum doit être
        ' appelée pour afficher la légende du contrôle de
        ' données correct.
        If (datDataCtl.Options And dbForwardOnly) = dbForwardOnly Then
          SetRecNum
        End If
      End If
      gbSettingDataCtl = False
      If gDataCtlObj.Tag <> sTmpTag Then
        Form_Resize    ' Il faut définir la propriété Left du dernier contrôle chargé.
      End If
    End If
    
  End If
  Exit Sub
  
DCPErr:
  ShowError
  Unload Me
End Sub

Private Sub Form_Unload(Cancel As Integer)
  DBEngine.Idle dbFreeLocks
End Sub

Private Sub oleFieldData_MouseUp(Index As Integer, BUTTON As Integer, Shift As Integer, x As Single, y As Single)
  If BUTTON <> 2 Then Exit Sub
  ' Ceci affiche la boîte de dialogue autorisant
  ' les entrées dans le champ OLE
  oleFieldData(Index).InsertObjDlg
End Sub

Private Sub txtFieldData_KeyPress(Index As Integer, KeyAscii As Integer)
  ' Va au champ suivant lors d'une entrée au clavier
  If KeyAscii = 13 Then
    KeyAscii = 0
    SendKeys "{Tab}"
  End If
End Sub

Private Sub picFieldData_Click(Index As Integer)
  'ceci active la dimension d'un contrôle Picture
  'pour l'afficher ou la réduire.
  If picFieldData(Index).Height <= 280 Then
    picFieldData(Index).AutoSize = True
  Else
    picFieldData(Index).AutoSize = False
    picFieldData(Index).Height = 280
  End If
End Sub

Private Sub picFieldData_DblClick(Index As Integer)
  On Error GoTo PicErr

  With dlgCMD1
    .Filter = "Fichiers bitmap (*.bmp)|*.bmp|Icônes (*.ico)|*.ico|Métafichiers(*.wmf)|*.wmf|Tous les fichiers (*.*)|*.*"
    .DialogTitle = MSG2
    .FilterIndex = 1
    .ShowOpen
  
    If Len(.FileName) > 0 Then
      picFieldData(Index).Picture = LoadPicture(.FileName)
    End If
  End With

  Exit Sub
  
PicErr:
  ShowErrMsg
  Exit Sub

End Sub

Private Sub cmdClose_Click()
  On Error Resume Next

  Unload Me
End Sub

Private Sub vsbScrollBar_Change()
  Dim nCurrVal As Integer

  nCurrVal = vsbScrollBar
  If (nCurrVal - mnFieldTop) Mod mnCTLARRAYHEIGHT = 0 Then
    picFields.Top = nCurrVal
  Else
    picFields.Top = ((nCurrVal - mnFieldTop) \ mnCTLARRAYHEIGHT) * mnCTLARRAYHEIGHT + mnFieldTop
  End If

End Sub

Private Sub datDataCtl_Error(DataErr As Integer, Response As Integer)
  If DataErr = 481 Then  ' Rejette l'erreur de la mauvaise image
    Response = vbDataErrContinue
  Else
    MsgBox MSG3 & Error(DataErr)
  End If
End Sub

Private Sub datDataCtl_RePosition()
  On Error GoTo RepErr

  Dim sBookMark As String
  Dim recClone As Recordset
  
  ' Ignore cette procédure pendant la redéfinition du contrôle Data
  If gbSettingDataCtl Then Exit Sub
  
  ' Si le jeu d'enregistrements est vide alors que le mode AddNew
  ' n'est pas actif, la procédure cmdAdd_Click doit être appelée
  ' pour exécuter la méthode AddNew.
  If (datDataCtl.Recordset.RecordCount = 0) And _
     (datDataCtl.EditMode <> dbEditAdd) And _
      datDataCtl.Recordset.Updatable Then
    Call cmdAdd_Click
    Exit Sub
  End If

  SetRecNum

  
  Exit Sub
  
RepErr:
  ShowErrMsg
  Exit Sub

End Sub

Private Sub datDataCtl_Validate(Action As Integer, Save As Integer)
  On Error GoTo ValErr

  If mbCancel Then
    Save = False
    mbCancel = False
    Exit Sub
  End If

  ' Vérifie d'abord un déplacement depuis un enregistrement obtenu avec la méthode Addnew ou Edit.
  If Action < 5 Then
    If Save Then       ' Les données ont changé.
      If datDataCtl.EditMode = dbEditAdd Then
        If MsgBox(MSG4, mnMSGBOX_TYPE) = vbYes Then
          mlNumRows = mlNumRows + 1
        Else
          Save = False
        End If
      Else
        If MsgBox(MSG5, mnMSGBOX_TYPE) <> vbYes Then
          Save = False        ' Perte des modifications.
        End If
      End If
    End If
  End If

  Select Case Action
    Case vbDataActionMoveFirst
      ' Ne rien faire
    Case vbDataActionMovePrevious
      ' Ne rien faire
    Case vbDataActionMoveNext
      ' Ne rien faire
    Case vbDataActionMoveLast
      ' Ne rien faire
    Case vbDataActionAddNew
      ' Ne rien faire
    Case vbDataActionUpdate
       ' Se déplacer vers le code de l'événement cmdUpdate_click.
    Case vbDataActionDelete
      ' Ne rien faire
    Case vbDataActionFind
      ' Définit l'indicateur pour l'utiliser dans l'événement Reposition.
      mbJustUsedFind = True
    Case vbDataActionBookmark
      ' Ne rien faire
    Case vbDataActionClose, vbDataActionUnload
      If Save Then
        If MsgBox(MSG6, mnMSGBOX_TYPE) <> vbYes Then
          Save = False
        End If
      End If

  End Select

  Exit Sub

ValErr:
  ShowErrMsg
  Exit Sub
  
End Sub

Private Sub cmdDelete_Click()
  On Error GoTo DELErr

  If MsgBox(MSG7, mnMSGBOX_TYPE) = vbYes Then
    datDataCtl.Recordset.Delete
    mlNumRows = mlNumRows - 1
    datDataCtl.Recordset.MoveNext
    ' Retire la condition EOF si nécessaire.
    If datDataCtl.Recordset.RecordCount > 0 Then datDataCtl.Recordset.MoveLast
    maFldArr(0).SetFocus
  End If

  Exit Sub

DELErr:
  ShowErrMsg
  Exit Sub

End Sub

Private Sub cmdFind_Click()
  On Error GoTo FindErr

  Dim sBookMark As String
  Dim sFindStr As String

  If datDataCtl.Recordset.Type = dbOpenTable Then
    sFindStr = InputBox(MSG8)
  Else
    sFindStr = InputBox(MSG9)
  End If
  If Len(sFindStr) = 0 Then Exit Sub

  If datDataCtl.Recordset.RecordCount > 0 Then
    sBookMark = datDataCtl.Recordset.Bookmark
  End If

  If datDataCtl.Recordset.Type = dbOpenTable Then
    datDataCtl.Recordset.Seek "=", sFindStr
  Else
    datDataCtl.Recordset.FindFirst sFindStr
  End If

  ' Retourne à l'ancien enregistrement si aucune correspondance n'est trouvée.
  If datDataCtl.Recordset.NoMatch And Len(sBookMark) > 0 Then
    datDataCtl.Recordset.Bookmark = sBookMark
  End If

  maFldArr(0).SetFocus
  Exit Sub

FindErr:
  ShowErrMsg
  maFldArr(0).SetFocus
  Exit Sub

End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016122
  End If
End Sub

Private Sub Form_Load()
  On Error GoTo LoadErr

  cmdCancelAdd.Caption = BUTTON1
  cmdUpdate.Caption = BUTTON2
  cmdDelete.Caption = BUTTON3
  cmdFind.Caption = BUTTON4
  cmdRefresh.Caption = BUTTON5
  cmdClose.Caption = BUTTON6
  cmdAdd.Caption = BUTTON7
  lblFieldHeader.Caption = Label1
  lblFieldValue.Caption = Label2
  
  ' mrsFormRecordset est une variable de type Public
  ' de niveau module qui doit être définie avant
  ' l'affichage de cette feuille.
  
  
  With mrsFormRecordset
    If .Type = dbOpenTable Then
      ' Il faut définir l'index.
      If gdbCurrentDB.TableDefs(.Name).Indexes.Count > 0 Then
        .Index = gdbCurrentDB.TableDefs(.Name).Indexes(0).Name
      End If
    End If
    If .RecordCount > 0 Then
      ' Enregistrement suivant, puis précédent, pour lire le nombre d'enregistrements
      .MoveLast
      .MoveFirst
    End If
  End With
  Set datDataCtl.Recordset = mrsFormRecordset
  
  Me.Width = 5868
  LoadFields
  Me.Show
  maFldArr(0).SetFocus
  Exit Sub

LoadErr:
  ShowErrMsg
  Unload Me
End Sub

Private Sub Form_Resize()
  On Error Resume Next

  If gbSettingDataCtl Then Exit Sub
  If mbResizing Then Exit Sub

  Dim nHeight As Integer
  Dim i As Integer
  Dim nTotalWidth As Integer

  mbResizing = True
  If Me.WindowState <> 1 And lblFieldName(0).Visible Then ' Non réduit.
    ' Vérifie que le bord supérieur de la feuille est aligné sur un champ.
    nHeight = Me.Height
    If (nHeight - 1320) Mod mnCTLARRAYHEIGHT <> 0 Then
      Me.Height = ((nHeight - 1280) \ mnCTLARRAYHEIGHT) * mnCTLARRAYHEIGHT + 1280
    End If
    ' Redimensionne la barre d'état.
    datDataCtl.Top = Me.Height - 650
    ' Redimensionne la barre de défilement.
    vsbScrollBar.Height = Me.Height - 1300
    vsbScrollBar.Left = Me.Width - 360
    If mrsFormRecordset.Fields.Count > 10 Then
      picFields.Width = Me.Width - 260
      nTotalWidth = vsbScrollBar.Left - 20
    Else
      picFields.Width = Me.Width - 20
      nTotalWidth = Me.Width - 50
    End If
    picButtons.Width = Me.Width - 20
    ' Agrandit les champs si possible.
    For i = 0 To mrsFormRecordset.Fields.Count - 1
      lblFieldName(i).Width = 0.3 * nTotalWidth - 100
      maFldArr(i).Left = lblFieldName(i).Width + 200
      If datDataCtl.Recordset.Fields(i).Type > 9 Then
        maFldArr(i).Width = 0.7 * nTotalWidth - 270
      End If
    Next
    lblFieldValue.Left = maFldArr(0).Left

  End If

  mbResizing = False

End Sub

Private Function GetFieldWidth(rnType As Integer)
  ' Détermine la largeur du contrôle de la feuille
  ' en fonction du type de champ.
  Select Case rnType
    Case dbBoolean
      GetFieldWidth = 850
    Case dbByte
      GetFieldWidth = 650
    Case dbInteger
      GetFieldWidth = 900
    Case dbLong
      GetFieldWidth = 1100
    Case dbCurrency
      GetFieldWidth = 1800
    Case dbSingle
      GetFieldWidth = 1800
    Case dbDouble
      GetFieldWidth = 2200
    Case dbDate
      GetFieldWidth = 2000
    Case dbText
      GetFieldWidth = 3250
    Case dbMemo
      GetFieldWidth = 3250
    Case Else
      GetFieldWidth = 3250
  End Select

End Function

Private Sub LoadFields()
   Dim recTmp As Recordset
   Dim nFldType As Integer
   Dim i As Integer

   On Error GoTo LoadFieldsErr

   Set mrsFormRecordset = datDataCtl.Recordset
   Set recTmp = mrsFormRecordset

   ' Charge les contrôles sur la feuille du jeu d'enregistrements.
   mnNumFields = recTmp.Fields.Count
   ReDim maFldArr(mnNumFields) As Object
   lblFieldName(0).Visible = True
   nFldType = recTmp.Fields(0).Type
   If nFldType = dbBoolean Then
     Set maFldArr(0) = chkFieldData(0)
   ElseIf nFldType = dbLongBinary Then
     If datDataCtl.Tag = "OLE" Then
       Set maFldArr(0) = oleFieldData(0)
     Else
       Set maFldArr(0) = picFieldData(0)
     End If
   Else
     Set maFldArr(0) = txtFieldData(0)
   End If
   maFldArr(0).Visible = True
   maFldArr(0).Top = 0
   maFldArr(0).Width = GetFieldWidth(nFldType)
   If nFldType = dbText Then maFldArr(0).MaxLength = recTmp.Fields(0).Size

   maFldArr(0).TabIndex = 0
   On Error Resume Next
   For i = 1 To recTmp.Fields.Count - 1
     picFields.Height = picFields.Height + mnCTLARRAYHEIGHT
     Load lblFieldName(i)
     lblFieldName(i).Top = lblFieldName(i - 1).Top + mnCTLARRAYHEIGHT
     lblFieldName(i).Visible = True
     nFldType = recTmp.Fields(i).Type
     If nFldType = dbBoolean Then
       Load chkFieldData(i)
       Set maFldArr(i) = chkFieldData(i)
     ElseIf nFldType = dbLongBinary Then
       If datDataCtl.Tag = "OLE" Then
         Load oleFieldData(i)
         Set maFldArr(i) = oleFieldData(i)
       Else
         Load picFieldData(i)
         Set maFldArr(i) = picFieldData(i)
       End If
     Else
       Load txtFieldData(i)
       Set maFldArr(i) = txtFieldData(i)
     End If
     maFldArr(i).Top = maFldArr(i - 1).Top + mnCTLARRAYHEIGHT
     maFldArr(i).Visible = True
     maFldArr(i).Width = GetFieldWidth(nFldType)
     maFldArr(i).TabIndex = i
     If nFldType = dbText Then maFldArr(i).MaxLength = recTmp.Fields(i).Size
   Next

   On Error GoTo LoadFieldsErr

   ' Redimensionne la fenêtre principale.
   picFields.Top = picButtons.Top + picButtons.Height
   mnFieldTop = picFields.Top
   vsbScrollBar.Value = mnFieldTop
   If i <= 10 Then
     Height = i * mnCTLARRAYHEIGHT + 1500
     vsbScrollBar.Visible = False
   Else
     Height = 4500
     Width = Width + 260
     vsbScrollBar.Visible = True
     vsbScrollBar.Min = mnFieldTop
     vsbScrollBar.Max = mnFieldTop - (i * mnCTLARRAYHEIGHT) + 3000
   End If

   ' Affiche les noms de champ.
   For i = 0 To recTmp.Fields.Count - 1
     lblFieldName(i).Caption = recTmp.Fields(i).Name & ":"
   Next
   
   ' Lie les contrôles.
   On Error Resume Next   ' Lie même si la table est vide.
   For i = 0 To recTmp.Fields.Count - 1
     maFldArr(i).DataField = recTmp.Fields(i).Name
   Next

   Exit Sub

LoadFieldsErr:
   ShowErrMsg
   Exit Sub

End Sub

Private Sub cmdRefresh_Click()
  On Error GoTo RefErr

  If mbIsParameterized Then
    MsgBox MSG13, vbInformation
    Exit Sub
  End If
  
  datDataCtl.Refresh
  Exit Sub

RefErr:
  ShowErrMsg
End Sub

Private Sub SetRecNum()
  On Error GoTo SRErr
  
  Dim sCurrStat As String
  Dim lCurrRec As Long
  Dim bNoInd As Integer
  
  ' Nombre d'enregistrements actuel
  mlNumRows = datDataCtl.Recordset.RecordCount
  
  If datDataCtl.EditMode <> dbEditAdd Then
    If datDataCtl.Recordset.BOF Then
      sCurrStat = "(BOF)/" & mlNumRows
    ElseIf datDataCtl.Recordset.EOF Then
      sCurrStat = "(EOF)/" & mlNumRows
    Else
      ' Vérifie si une table sans index est utilisée.
      If datDataCtl.Recordset.Type = dbOpenTable Then
        If datDataCtl.Database(datDataCtl.RecordSource).Indexes.Count = 0 Then
          bNoInd = True
        End If
      End If
      ' Si les index manquent dans la table ou si le jeu
      ' d'enregistrements est de type en avant seulement,
      ' la propriété PercentPosition n'est pas disponible.
      If bNoInd Then
        sCurrStat = mlNumRows & MSG10
      ElseIf (datDataCtl.Options And dbForwardOnly) = dbForwardOnly Then
        sCurrStat = mlNumRows & MSG11
      Else
        lCurrRec = (mlNumRows * (datDataCtl.Recordset.PercentPosition * 0.01)) + 1
        sCurrStat = lCurrRec & "/" & mlNumRows
      End If
    End If
    If datDataCtl.Recordset.Updatable = False Then
      sCurrStat = sCurrStat & MSG12
      cmdAdd.Enabled = False
      cmdCancelAdd.Enabled = False
      cmdUpdate.Enabled = False
      cmdDelete.Enabled = False
    Else
      cmdAdd.Enabled = True
      cmdCancelAdd.Enabled = True
      cmdUpdate.Enabled = True
      cmdDelete.Enabled = True
    End If
    datDataCtl.Caption = sCurrStat
  End If

  ' Redéfinit les boutons si nécessaire.
  If datDataCtl.EditMode <> dbEditAdd Then
    cmdCancelAdd.Visible = False
    cmdAdd.Visible = True
  End If

  Exit Sub
SRErr:
  If Err <> 3021 Then
    ShowErrMsg
  End If
  Exit Sub

End Sub

Private Sub cmdUpdate_Click()
  On Error GoTo UpdErr

  Dim bAddFlag As Integer

  Dim nDelay As Long
  Dim nRetryCnt As Integer

  bAddFlag = datDataCtl.EditMode
  
  If datDataCtl.EditMode = dbEditAdd Then
    If MsgBox(MSG4, mnMSGBOX_TYPE) = vbYes Then
      Screen.MousePointer = vbHourglass
RetryUpd1:
      datDataCtl.UpdateRecord
      mlNumRows = mlNumRows + 1
    End If
  Else
    If MsgBox(MSG5, mnMSGBOX_TYPE) = vbYes Then
      Screen.MousePointer = vbHourglass
RetryUpd2:
      datDataCtl.UpdateRecord
    End If
  End If

  If bAddFlag = dbEditAdd Then
    mrsFormRecordset.MoveLast
  End If

  DBEngine.Idle dbFreeLocks
  Screen.MousePointer = vbDefault
  Exit Sub

UpdErr:
  If Err = 3260 And nRetryCnt < gnMURetryCnt Then
    nRetryCnt = nRetryCnt + 1
    datDataCtl.Recordset.Bookmark = datDataCtl.Recordset.Bookmark   'Annuler la mise à jour
    DBEngine.Idle dbFreeLocks
    nDelay = Timer
    ' Attend gnMUDelay secondes.
    While Timer - nDelay < gnMUDelay
      ' Ne rien faire
    Wend
    If datDataCtl.EditMode = dbEditAdd Then
      Resume RetryUpd1
    Else
      Resume RetryUpd2
    End If
  Else
    Screen.MousePointer = vbDefault
    ShowErrMsg
    Exit Sub
  End If

End Sub

Private Sub ShowErrMsg()
  MsgBox "Erreur:" & Err & " " & Error
End Sub
