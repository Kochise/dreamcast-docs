VERSION 5.00
Begin VB.Form frmDynaSnap 
   Caption         =   "Dynaset/Snapshot"
   ClientHeight    =   3750
   ClientLeft      =   2730
   ClientTop       =   2610
   ClientWidth     =   5490
   HelpContextID   =   2016125
   Icon            =   "DYNASNAP.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MDIChild        =   -1  'True
   ScaleHeight     =   3733.906
   ScaleMode       =   0  'User
   ScaleWidth      =   5503.698
   ShowInTaskbar   =   0   'False
   Tag             =   "Recordset"
   Begin VB.PictureBox picViewButtons 
      Align           =   1  'Align Top
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   852
      Left            =   0
      ScaleHeight     =   855
      ScaleMode       =   0  'User
      ScaleWidth      =   5487.272
      TabIndex        =   13
      TabStop         =   0   'False
      Top             =   0
      Width           =   5484
      Begin VB.CommandButton cmdMove 
         Caption         =   "&Déplacer"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   345
         Left            =   2730
         MaskColor       =   &H00000000&
         TabIndex        =   7
         Top             =   375
         Width           =   1365
      End
      Begin VB.CommandButton cmdSort 
         Caption         =   "&Trier"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   345
         Left            =   0
         MaskColor       =   &H00000000&
         TabIndex        =   5
         Top             =   372
         Width           =   1365
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
         Height          =   345
         Left            =   1365
         MaskColor       =   &H00000000&
         TabIndex        =   6
         Top             =   375
         Width           =   1365
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
         Height          =   345
         Left            =   4095
         MaskColor       =   &H00000000&
         TabIndex        =   4
         TabStop         =   0   'False
         Top             =   15
         Width           =   1365
      End
      Begin VB.CommandButton cmdDelete 
         Caption         =   "&Supprimer"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   345
         Left            =   2730
         MaskColor       =   &H00000000&
         TabIndex        =   3
         Top             =   15
         Width           =   1365
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
         Height          =   345
         Left            =   1365
         MaskColor       =   &H00000000&
         TabIndex        =   2
         Top             =   15
         Width           =   1365
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
         Height          =   345
         Left            =   0
         MaskColor       =   &H00000000&
         TabIndex        =   1
         Top             =   20
         Width           =   1365
      End
      Begin VB.CommandButton cmdFind 
         Caption         =   "&Rechercher"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   345
         Left            =   4095
         MaskColor       =   &H00000000&
         TabIndex        =   8
         Top             =   375
         Width           =   1365
      End
   End
   Begin VB.PictureBox picChangeButtons 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   855
      Left            =   0
      ScaleHeight     =   919.528
      ScaleMode       =   0  'User
      ScaleWidth      =   5719.056
      TabIndex        =   14
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
         MaskColor       =   &H00000000&
         TabIndex        =   11
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
         MaskColor       =   &H00000000&
         TabIndex        =   12
         Top             =   48
         Width           =   1212
      End
   End
   Begin VB.PictureBox picFldHdr 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   240
      Left            =   0
      ScaleHeight     =   240
      ScaleMode       =   0  'User
      ScaleWidth      =   14948.92
      TabIndex        =   18
      TabStop         =   0   'False
      Top             =   840
      Width           =   14946
      Begin VB.Label lblFieldValue 
         Caption         =   " Valeur (F4=Zoom)"
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
         TabIndex        =   20
         Top             =   0
         Width           =   2295
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
         TabIndex        =   19
         Top             =   0
         Width           =   1212
      End
   End
   Begin VB.PictureBox picMoveButtons 
      Align           =   2  'Align Bottom
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   288
      Left            =   0
      ScaleHeight     =   298.153
      ScaleMode       =   0  'User
      ScaleWidth      =   5493.878
      TabIndex        =   17
      TabStop         =   0   'False
      Top             =   3465
      Width           =   5484
      Begin VB.HScrollBar hsclCurrRow 
         Height          =   255
         Left            =   0
         Max             =   100
         TabIndex        =   9
         Top             =   29
         Width           =   2895
      End
      Begin VB.Label lblStatus 
         Height          =   255
         Left            =   3000
         TabIndex        =   21
         Top             =   38
         Width           =   1695
      End
   End
   Begin VB.VScrollBar vsbScrollBar 
      Height          =   2250
      LargeChange     =   3000
      Left            =   5040
      SmallChange     =   300
      TabIndex        =   10
      Top             =   1080
      Visible         =   0   'False
      Width           =   255
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
      TabIndex        =   15
      TabStop         =   0   'False
      Top             =   1080
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
         ForeColor       =   &H00000000&
         Height          =   252
         Index           =   0
         Left            =   0
         TabIndex        =   16
         Top             =   60
         Visible         =   0   'False
         Width           =   1572
      End
   End
End
Attribute VB_Name = "frmDynaSnap"
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
Const BUTTON5 = "&Trier"
Const BUTTON6 = "F&iltrer"
Const BUTTON7 = "&Déplacer"
Const BUTTON8 = "&Rechercher"
Const BUTTON9 = "A&nnuler"
Const BUTTON10 = "&Valider"
Const Label1 = "Nom du champ:"
Const Label2 = "Valeur (F4=Zoom)"
Const MSG1 = "Ajouter un enregistrement"
Const MSG2 = "Entrez le nombre de lignes à déplacer:"
Const MSG3 = "(Utilisez une valeur négative pour un déplacement en arrière)"
Const MSG4 = "Longueur de champ insuffisante, données tronquées!"
Const MSG5 = "Effacer l'enregistrement en cours?"
Const MSG6 = "Modifier l'enregistrement"
Const MSG7 = "Entrer une expression de filtre:"
Const MSG8 = "Définition d'un nouveau filtre"
Const MSG9 = "Entrer des paramètres de recherche"
Const MSG10 = "Recherche d'un nouvel enregistrement"
Const MSG11 = "Enregistrement introuvable"
Const MSG12 = "Redimensionnement de la feuille"
Const MSG13 = "Entrer la colonne à trier:"
Const MSG14 = "Définition d'un nouvel ordre de tri"
'>>>>>>>>>>>>>>>>>>>>>>>>


' Variables de la feuille.
Public mrsFormRecordset As Recordset
Dim msTableName As String      ' Nom de la table du jeu d'enregistrements de la feuille.
Dim mvBookMark As Variant      ' Signet de la feuille.
Dim mbNotFound As Integer      ' Utilisé par la fonction de recherche.
Dim mbEditFlag As Integer      ' Mode édition.
Dim mbAddNewFlag As Integer    ' Mode ajout
Dim mbDataChanged As Integer   ' Indicateur de modification des données du champ.
Dim mfrmFind As New frmFindForm      ' Rechercher les instances de la feuille.
Dim mlNumRows As Long          ' Nombre total de lignes dans le jeu d'enregistrements.

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
  hsclCurrRow.Enabled = False
  
  ClearDataFields Me, mrsFormRecordset.Fields.Count
  txtFieldData(0).SetFocus
  mbDataChanged = False
  Exit Sub

AddErr:
  ShowError
End Sub

Private Sub cmdCancel_Click()
   On Error Resume Next

   picChangeButtons.Visible = False
   picViewButtons.Visible = True
   hsclCurrRow.Enabled = True

   mbEditFlag = False
   mbAddNewFlag = False
   mrsFormRecordset.CancelUpdate
   DBEngine.Idle dbFreeLocks
   DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
   mbDataChanged = False

End Sub

Private Sub cmdMove_Click()
  On Error GoTo MVErr
  
  Dim sBookMark As String
  Dim sRows As String
  Dim lRows As Long
  
  sRows = InputBox(MSG2 & vbCrLf & MSG3)
  If Len(sRows) = 0 Then Exit Sub
  
  lRows = CLng(sRows)
  mrsFormRecordset.Move lRows
  
  ' vérifie si on a dépassé les limites du jeu d'enregistrements
  If mrsFormRecordset.EOF Then
    mrsFormRecordset.MoveLast
  ElseIf mrsFormRecordset.BOF Then
    mrsFormRecordset.MoveFirst
  End If
  sBookMark = mrsFormRecordset.Bookmark  ' Enregistre la nouvelle position.
  ' La barre de déplacement doit être repositionnée pour tenir compte du déplacement.
  If mlNumRows > 32767 Then
    hsclCurrRow.Value = (mrsFormRecordset.PercentPosition * 32767) / 100 + 1
  ElseIf mlNumRows > 99 Then
    hsclCurrRow.Value = (mrsFormRecordset.PercentPosition * mlNumRows) / 100 + 1
  Else
    hsclCurrRow.Value = mrsFormRecordset.PercentPosition
  End If
  mrsFormRecordset.Bookmark = sBookMark
  
  Exit Sub
  
MVErr:
  ShowError
End Sub

Private Sub hsclCurrRow_Change()
  On Error GoTo SCRErr
  
  Static nPrevVal As Integer
  Dim rsTmp As Recordset

  ' En fonction nombre de lignes, un autre facteur est requis
  ' pour définir la position courante dans le jeu
  ' d'enregistrements.
  If mlNumRows > 0 Then
    If mlNumRows > 99 Then   '32767 Then
      ' si supérieur à 32767, il faut utiliser les méthodes Move
      ' car la barre de déplacement est limitée à 32767.
      ' Si ce facteur n'est pas appliqué, il est impossible d'arriver
      ' à chaque enregistrement sur une petite modification de
      ' la barre de déplacement.
      If hsclCurrRow.Value - nPrevVal = 1 Then
        mrsFormRecordset.MoveNext
        If mrsFormRecordset.EOF Then
          mrsFormRecordset.MoveLast
        End If
      ElseIf hsclCurrRow.Value - nPrevVal = -1 Then
        mrsFormRecordset.MovePrevious
        If mrsFormRecordset.BOF Then
          mrsFormRecordset.MoveFirst
        End If
      Else
        If mlNumRows > 32767 Then
          mrsFormRecordset.PercentPosition = (hsclCurrRow.Value / 32767) * 100 + 0.005
        Else
          mrsFormRecordset.PercentPosition = (hsclCurrRow.Value / mlNumRows) * 100 + 0.005
        End If
      End If
      nPrevVal = hsclCurrRow.Value
    Else
      mrsFormRecordset.PercentPosition = hsclCurrRow.Value
    End If
  End If
  DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
  mbDataChanged = False

  Screen.MousePointer = vbDefault
  MsgBar vbNullString, False
  Exit Sub

SCRErr:
  ShowError
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
    ' Déplacement d'une page vers le bas si les champs sont supérieurs à 10.
    vsbScrollBar.Value = vsbScrollBar.Value - 3000

  ElseIf KeyCode = 33 And vsbScrollBar.Visible Then
    ' Déplacement d'une page vers le haut si les champs sont supérieurs à 10.
    vsbScrollBar.Value = vsbScrollBar.Value + 3000

  End If
End Sub

Private Sub txtFieldData_KeyPress(Index As Integer, KeyAscii As Integer)
  ' Autorise un renvoi uniquement s'il s'agit du mode édition ou ajout.
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
    ' Enregistre les données dans le champ.
    mrsFormRecordset(Index) = txtFieldData(Index)
  End If

  ' Réinitialisation pour une condition valide ou d'erreur.
  mbDataChanged = False
  Exit Sub

FldDataErr:
  ' Réinitialisation pour une condition valide ou d'erreur.
  mbDataChanged = False
  ShowError
End Sub

Private Sub lblFieldName_DblClick(Index As Integer)
  On Error GoTo ZoomErr

  If mrsFormRecordset(Index).Type = dbText Or mrsFormRecordset(Index).Type = dbMemo Then
     If mrsFormRecordset(Index).Type = dbText Then
       gsZoomData = txtFieldData(Index).Text
     ElseIf mrsFormRecordset(Index).FieldSize() < gnGETCHUNK_CUTOFF Then
       gsZoomData = txtFieldData(Index).Text
     Else
       ' Ajoute le restant des données du champ avec Getchunk
       MsgBar "Lecture des données du champ Memo", True
       Screen.MousePointer = vbHourglass
       gsZoomData = txtFieldData(Index).Text & _
         StripNonAscii(mrsFormRecordset(Index).GetChunk(gnGETCHUNK_CUTOFF, gnMAX_MEMO_SIZE))
       Screen.MousePointer = vbDefault
       MsgBar vbNullString, False
     End If
     frmZoom.Caption = Mid(lblFieldName(Index).Caption, 1, Len(lblFieldName(Index).Caption) - 1)
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
         MsgBox MSG4, 48
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

Private Sub cmdClose_Click()
  DBEngine.Idle dbFreeLocks
  Unload Me
End Sub

Private Sub vsbScrollBar_Change()
  Dim nTop As Integer

  nTop = vsbScrollBar.Value
  If (nTop - 1080) Mod gnCTLARRAYHEIGHT = 0 Then
    picFields.Top = nTop
  Else
    picFields.Top = ((nTop - 1080) \ gnCTLARRAYHEIGHT) * gnCTLARRAYHEIGHT + 1080
  End If

End Sub

Private Sub cmdDelete_Click()
  On Error GoTo DelRecErr

  If MsgBox(MSG5, vbYesNo + vbQuestion) = vbYes Then
    mrsFormRecordset.Delete
    If gbTransPending Then gbDBChanged = True
    If mrsFormRecordset.EOF = False Then
      ' voit si on peut passer à l'enregistrement suivant
      mrsFormRecordset.MoveNext
      If mrsFormRecordset.EOF And (mrsFormRecordset.RecordCount > 0) Then
        ' c'est le dernier enregistrement donc on ne peut pas aller plus loin
        mrsFormRecordset.MoveLast
      End If
    End If
    mlNumRows = mlNumRows - 1
    SetScrollBar
    mlNumRows = mrsFormRecordset.RecordCount
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
   lblStatus.Caption = MSG6
   mbEditFlag = True
   txtFieldData(0).SetFocus
   mvBookMark = mrsFormRecordset.Bookmark

   picChangeButtons.Visible = True
   picViewButtons.Visible = False
   hsclCurrRow.Enabled = False

   Screen.MousePointer = vbDefault
   Exit Sub

EditErr:
  If Err = 3260 And nRetryCnt < gnMURetryCnt Then
    nRetryCnt = nRetryCnt + 1
    DBEngine.Idle dbFreeLocks
    ' Attend le nombre de secondes défini par gnMUDelay.
    nDelay = Timer
    While Timer - nDelay < gnMUDelay
      ' Ne rien faire.
    Wend
    Resume RetryEdit
  Else
    ShowError
  End If
End Sub

Private Sub cmdFilter_Click()
  On Error GoTo FilterErr

  Dim sBookMark As String
  Dim recRecordset1 As Recordset, recRecordset2 As Recordset
  Dim sFilterStr As String

  If mrsFormRecordset.RecordCount = 0 Then Exit Sub

  sBookMark = mrsFormRecordset.Bookmark        ' Enregistrer le signet.
  Set recRecordset1 = mrsFormRecordset            ' Enregistrer le jeu d'enregistrements.
  
  sFilterStr = InputBox(MSG7)
  If Len(sFilterStr) = 0 Then Exit Sub

  Screen.MousePointer = vbHourglass
  MsgBar MSG8, True
  mrsFormRecordset.Filter = sFilterStr
  Set recRecordset2 = mrsFormRecordset.OpenRecordset(mrsFormRecordset.Type) ' Établir le filtre.
  ' Force le stockage à obtenir un objet Recordcount approprié.
  recRecordset2.MoveLast
  recRecordset2.MoveFirst
  Set mrsFormRecordset = recRecordset2            ' L'affecter en retour à l'objet Recordset de départ.

  ' Tout doit être correct; réaffiche la feuille sur le premier enregistrement.
  mlNumRows = mrsFormRecordset.RecordCount
  SetScrollBar
  hsclCurrRow.Value = 0
  DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
  mbDataChanged = False
  Screen.MousePointer = vbDefault
  MsgBar vbNullString, False
  Exit Sub

FilterRecover:
  On Error Resume Next
  Set mrsFormRecordset = recRecordset1            'réaffecter à l'original
  mrsFormRecordset.Bookmark = sBookMark           'retourner à l'enregistrement original
  Exit Sub

FilterErr:
  ShowError
  Resume FilterRecover
End Sub

Private Sub cmdFind_Click()
  On Error GoTo FindErr
  
  Dim i As Integer
  Dim sBookMark As String
  Dim sTmp As String

  ' Charge les noms de la colonne dans la feuille de recherche.
  If mfrmFind.lstFields.ListCount = 0 Then
    For i = 0 To mrsFormRecordset.Fields.Count - 1
      mfrmFind.lstFields.AddItem Mid(lblFieldName(i).Caption, 1, Len(lblFieldName(i).Caption) - 1)
    Next
  End If

FindStart:

  ' Réinitialise les indicateurs.
  gbFindFailed = False
  gbFromTableView = False
  mbNotFound = False

  MsgBar MSG9, False
  mfrmFind.Show vbModal
  MsgBar MSG10, True
  If gbFindFailed Then    ' Recherche annulée.
    GoTo AfterWhile
  End If

  Screen.MousePointer = vbHourglass

  i = mfrmFind.lstFields.ListIndex
  sBookMark = mrsFormRecordset.Bookmark
  ' Recherche l'enregistrement.
  If mrsFormRecordset(i).Type = dbText Or mrsFormRecordset(i).Type = dbMemo Then
    sTmp = AddBrackets((mrsFormRecordset(i).Name)) & " " & gsFindOp & " '" & gsFindExpr & "'"
  ElseIf mrsFormRecordset(i).Type = dbDate Then
    sTmp = AddBrackets((mrsFormRecordset(i).Name)) & " " & gsFindOp & " #" & gsFindExpr & "#"
  Else
    sTmp = AddBrackets((mrsFormRecordset(i).Name)) & gsFindOp & Val(gsFindExpr)
  End If
  Select Case gnFindType
    Case 0
      mrsFormRecordset.FindFirst sTmp
    Case 1
      mrsFormRecordset.FindNext sTmp
    Case 2
      mrsFormRecordset.FindPrevious sTmp
    Case 3
      mrsFormRecordset.FindLast sTmp
  End Select
  mbNotFound = mrsFormRecordset.NoMatch

AfterWhile:

  Screen.MousePointer = vbDefault

  If gbFindFailed Then    ' Retourne à l'enregistrement de départ.
    mrsFormRecordset.Bookmark = sBookMark
  ElseIf mbNotFound Then
    Beep
    MsgBox MSG11, 48
    mrsFormRecordset.Bookmark = sBookMark
    GoTo FindStart
  Else
    sBookMark = mrsFormRecordset.Bookmark  ' Enregistre la nouvelle position.
    ' La barre de déplacement doit être repositionnée pour tenir compte du déplacement.
    If mlNumRows > 99 Then
      hsclCurrRow.Value = (mrsFormRecordset.PercentPosition * mlNumRows) / 100 + 1
    Else
      hsclCurrRow.Value = mrsFormRecordset.PercentPosition
    End If
    mrsFormRecordset.Bookmark = sBookMark
  End If

  DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
  mbDataChanged = False

  MsgBar vbNullString, False
  Exit Sub

FindErr:
  Screen.MousePointer = vbDefault
  If Err <> gnEOF_ERR Then
    ShowError
  Else
    mbNotFound = True
    Resume Next
  End If
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016125
  End If
End Sub

Private Sub Form_Load()
  Dim sTmp As String             ' Chaîne temporaire du nom du jeu d'enregistrements
  Dim nFieldType As Integer      ' Type du champ en cours.
  Dim i As Integer, j As Integer ' Index.

  On Error GoTo DynasetErr
   
   
  cmdAdd.Caption = BUTTON1
  cmdEdit.Caption = BUTTON2
  cmdDelete.Caption = BUTTON3
  cmdClose.Caption = BUTTON4
  cmdSort.Caption = BUTTON5
  cmdFilter.Caption = BUTTON6
  cmdMove.Caption = BUTTON7
  cmdFind.Caption = BUTTON8
  cmdCancel.Caption = BUTTON9
  cmdUpdate.Caption = BUTTON10
  lblFieldHdr.Caption = Label1
  lblFieldValue.Caption = Label2
  
  ' mrsFormRecordset est une variable de type Public de niveau
  ' module qui doit être définie avant l'affichage de cette
  ' feuille.

   
   
  ' Définit le type de verrouillage (Le met en commentaire pour une utilisation autonome).
  If gsDataType = gsMSACCESS And mrsFormRecordset.Type <> dbOpenSnapshot Then
    mrsFormRecordset.LockEdits = gnMULocking
  End If

  ' Lit le nombre de lignes.
  With mrsFormRecordset
    If .RecordCount > 0 Then
      ' Va au dernier puis au premier pour obtenir
      ' le nombre d'enregistrements.
      .MoveLast
      .MoveFirst
    End If
    mlNumRows = .RecordCount
  End With
  SetScrollBar

  ' Charge les contrôles sur la feuille du jeu d'enregistrements.
  lblFieldName(0).Visible = True
  txtFieldData(0).Visible = True
  nFieldType = mrsFormRecordset(0).Type
  txtFieldData(0).Width = GetFieldWidth(nFieldType)
  If nFieldType = dbText Then txtFieldData(0).MaxLength = mrsFormRecordset(0).Size
  txtFieldData(0).TabIndex = 0
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
    If nFieldType = dbText Then txtFieldData(i).MaxLength = mrsFormRecordset(i).Size
    txtFieldData(i).TabIndex = i
  Next

  ' Redimensionne la fenêtre principale.
  Me.Width = 5580
  If i <= 10 Then
    Me.Height = ((i + 1) * gnCTLARRAYHEIGHT) + 1600
  Else
    Me.Height = 4368
    Me.Width = Me.Width + 260
    vsbScrollBar.Visible = True
    vsbScrollBar.Min = 1080
    vsbScrollBar.Max = 1080 - (i * gnCTLARRAYHEIGHT) + 2240
  End If

  ' Affiche les noms du champ.
  For i = 0 To mrsFormRecordset.Fields.Count - 1
    lblFieldName(i).Caption = mrsFormRecordset(i).Name & ":"
  Next

  DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
  mbDataChanged = False

  Me.Left = 1000
  Me.Top = 1000
  
  MsgBar vbNullString, False
  Exit Sub

DynasetErr:
  ShowError
  Unload Me
End Sub

Private Sub Form_Resize()
  On Error Resume Next

  Dim nHeight As Integer
  Dim i As Integer
  Dim nTotWidth As Integer
  Const nHeightFactor = 1420

  If WindowState <> 1 Then   ' Non réduit.
    MsgBar MSG12, True
    ' Vérifie que la feuille est alignée sur le bord supérieur d'un champ.
    nHeight = Height
    If (nHeight - nHeightFactor) Mod gnCTLARRAYHEIGHT <> 0 Then
      Me.Height = ((nHeight - nHeightFactor) \ gnCTLARRAYHEIGHT) * gnCTLARRAYHEIGHT + nHeightFactor
    End If
    ' Redimensionne la barre d'état.
    picMoveButtons.Top = Me.Height - 650
    ' Redimensionne la barre de défilement.
    vsbScrollBar.Height = picMoveButtons.Top - (picViewButtons.Top - picFldHdr.Height) - 1320
    vsbScrollBar.Left = Me.Width - 360
    If mrsFormRecordset.Fields.Count > 10 Then
      picFields.Width = Me.Width - 260
      nTotWidth = vsbScrollBar.Left - 20
    Else
      picFields.Width = Me.Width - 20
      nTotWidth = Me.Width - 50
    End If
    picFldHdr.Width = Me.Width - 20
    ' Élargit les champs si possible.
    For i = 0 To mrsFormRecordset.Fields.Count - 1
      lblFieldName(i).Width = 0.3 * nTotWidth
      txtFieldData(i).Left = lblFieldName(i).Width + 20
      If mrsFormRecordset(i).Type = dbText Or mrsFormRecordset(i).Type = dbMemo Then
        txtFieldData(i).Width = 0.7 * nTotWidth - 250
      End If
    Next
    lblFieldValue.Left = txtFieldData(0).Left
    hsclCurrRow.Width = picMoveButtons.Width \ 2
    lblStatus.Width = picMoveButtons.Width \ 2
    lblStatus.Left = hsclCurrRow.Width + 10
  End If
  MsgBar vbNullString, False
End Sub

Private Sub Form_Unload(Cancel As Integer)
  On Error Resume Next

  Unload mfrmFind   ' Se débarrasse de la feuille de recherche jointe.
  mrsFormRecordset.Close          ' Ferme le jeu d'enregistrements de la feuille.
  DBEngine.Idle dbFreeLocks
  MsgBar vbNullString, False
End Sub

Private Sub cmdSort_Click()
  On Error GoTo SortErr

  Dim sBookMark As String
  Dim recRecordset1 As Recordset, recRecordset2 As Recordset
  Dim SortStr As String

  If mrsFormRecordset.RecordCount = 0 Then Exit Sub

  sBookMark = mrsFormRecordset.Bookmark        ' Enregistre le signet.
  Set recRecordset1 = mrsFormRecordset         ' Enregistre le jeu d'enregistrements.
  
  SortStr = InputBox(MSG13)
  If Len(SortStr) = 0 Then Exit Sub

  Screen.MousePointer = vbHourglass
  MsgBar MSG14, True
  mrsFormRecordset.Sort = SortStr
  ' Établit le tri.
  Set recRecordset2 = mrsFormRecordset.OpenRecordset(mrsFormRecordset.Type)
  Set mrsFormRecordset = recRecordset2            ' Réaffecter à l'objet Recordset de départ.

  ' Tout doit être correct; réaffiche la feuille sur le premier enregistrement.
  mlNumRows = mrsFormRecordset.RecordCount
  hsclCurrRow.Value = 0
  DisplayCurrentRecord Me, mrsFormRecordset, mlNumRows, mbAddNewFlag
  mbDataChanged = False
  Screen.MousePointer = vbDefault
  MsgBar vbNullString, False
  Exit Sub

SortRecover:
  On Error Resume Next
  Set mrsFormRecordset = recRecordset1            'réaffecter à l'original
  mrsFormRecordset.Bookmark = sBookMark           'retourner à l'enregistrement original
  Exit Sub

SortErr:
  ShowError
  Resume SortRecover
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
    SetScrollBar
    ' Se déplace vers le nouvel enregistrement.
    mrsFormRecordset.MoveLast
  End If

  picChangeButtons.Visible = False
  picViewButtons.Visible = True
  hsclCurrRow.Enabled = True
  mbEditFlag = False
  mbAddNewFlag = False
  hsclCurrRow_Change
  DBEngine.Idle dbFreeLocks

  Screen.MousePointer = vbDefault
  Exit Sub

UpdateErr:
  ' Contrôle l'erreur verrouillée.
  If Err = 3260 And nRetryCnt < gnMURetryCnt Then
    nRetryCnt = nRetryCnt + 1
    mrsFormRecordset.Bookmark = mrsFormRecordset.Bookmark   'Cancel the update
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

Private Sub SetScrollBar()
  On Error Resume Next
  
  If mlNumRows < 2 Then
    hsclCurrRow.Max = 100
    hsclCurrRow.SmallChange = 1 '00
    hsclCurrRow.LargeChange = 100
  ElseIf mlNumRows > 32767 Then
    hsclCurrRow.Max = 32767
    hsclCurrRow.SmallChange = 1
    hsclCurrRow.LargeChange = 1000
  ElseIf mlNumRows > 99 Then
    hsclCurrRow.Max = mlNumRows
    hsclCurrRow.SmallChange = 1
    hsclCurrRow.LargeChange = mlNumRows \ 20
  Else
    ' Doit être compris entre 2 et 100.
    hsclCurrRow.Max = 100
    hsclCurrRow.SmallChange = 100 \ (mlNumRows - 1)
    hsclCurrRow.LargeChange = (100 \ (mlNumRows - 1)) * 10
  End If
  ' Lance la procédure, puis revenir à la barre clignotante fixe.
  txtFieldData(0).SetFocus
  hsclCurrRow.SetFocus
End Sub

