VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.0#0"; "COMDLG32.OCX"
Begin VB.Form frmSDI 
   Caption         =   "Bloc-notes SDI - Sans titre"
   ClientHeight    =   5370
   ClientLeft      =   1080
   ClientTop       =   1035
   ClientWidth     =   6690
   LinkTopic       =   "Form1"
   ScaleHeight     =   5370
   ScaleWidth      =   6690
   Begin VB.TextBox txtNote 
      Height          =   3975
      HideSelection   =   0   'False
      Left            =   0
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Top             =   480
      Width           =   5655
   End
   Begin VB.PictureBox picToolbar 
      Align           =   1  'Align Top
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   405
      Left            =   0
      ScaleHeight     =   345
      ScaleWidth      =   6630
      TabIndex        =   1
      Top             =   0
      Width           =   6690
      Begin MSComDlg.CommonDialog CMDialog1 
         Left            =   1995
         Top             =   0
         _ExtentX        =   847
         _ExtentY        =   847
         CancelError     =   -1  'True
         DefaultExt      =   "TXT"
         Filter          =   "Fichiers Texte (*.txt)|*.txt|Tous les fichiers (*.*)|*.*"
         FilterIndex     =   473
         FontSize        =   7.98198e-38
      End
      Begin VB.Image imgFileNewButton 
         Height          =   330
         Left            =   0
         Picture         =   "frmsdi.frx":0000
         ToolTipText     =   "Nouveau"
         Top             =   0
         Width           =   360
      End
      Begin VB.Image imgFileOpenButton 
         Height          =   330
         Left            =   360
         Picture         =   "frmsdi.frx":018A
         ToolTipText     =   "Ouvrir"
         Top             =   0
         Width           =   360
      End
      Begin VB.Image imgCutButton 
         Height          =   330
         Left            =   840
         Picture         =   "frmsdi.frx":0314
         ToolTipText     =   "Couper"
         Top             =   0
         Width           =   375
      End
      Begin VB.Image imgCopyButton 
         Height          =   330
         Left            =   1200
         Picture         =   "frmsdi.frx":04F6
         ToolTipText     =   "Copier"
         Top             =   0
         Width           =   375
      End
      Begin VB.Image imgPasteButton 
         Height          =   330
         Left            =   1560
         Picture         =   "frmsdi.frx":06D8
         ToolTipText     =   "Coller"
         Top             =   0
         Width           =   375
      End
      Begin VB.Image imgFileNewButtonDn 
         Height          =   330
         Left            =   2040
         Picture         =   "frmsdi.frx":08BA
         Top             =   0
         Visible         =   0   'False
         Width           =   375
      End
      Begin VB.Image imgFileNewButtonUp 
         Height          =   330
         Left            =   2400
         Picture         =   "frmsdi.frx":0A9C
         Top             =   0
         Visible         =   0   'False
         Width           =   360
      End
      Begin VB.Image imgFileOpenButtonUp 
         Height          =   330
         Left            =   3120
         Picture         =   "frmsdi.frx":0C26
         Top             =   0
         Visible         =   0   'False
         Width           =   360
      End
      Begin VB.Image imgFileOpenButtonDn 
         Height          =   330
         Left            =   2760
         Picture         =   "frmsdi.frx":0DB0
         Top             =   0
         Visible         =   0   'False
         Width           =   360
      End
      Begin VB.Image imgCutButtonUp 
         Height          =   330
         Left            =   3480
         Picture         =   "frmsdi.frx":0F3A
         Top             =   0
         Visible         =   0   'False
         Width           =   375
      End
      Begin VB.Image imgCutButtonDn 
         Height          =   330
         Left            =   3840
         Picture         =   "frmsdi.frx":111C
         Top             =   0
         Visible         =   0   'False
         Width           =   375
      End
      Begin VB.Image imgCopyButtonUp 
         Height          =   330
         Left            =   4560
         Picture         =   "frmsdi.frx":12FE
         Top             =   0
         Visible         =   0   'False
         Width           =   375
      End
      Begin VB.Image imgCopyButtonDn 
         Height          =   330
         Left            =   4200
         Picture         =   "frmsdi.frx":14E0
         Top             =   0
         Visible         =   0   'False
         Width           =   375
      End
      Begin VB.Image imgPasteButtonDn 
         Height          =   330
         Left            =   4920
         Picture         =   "frmsdi.frx":16C2
         Top             =   0
         Visible         =   0   'False
         Width           =   375
      End
      Begin VB.Image imgPasteButtonUp 
         Height          =   330
         Left            =   5280
         Picture         =   "frmsdi.frx":18A4
         Top             =   0
         Visible         =   0   'False
         Width           =   375
      End
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&Fichier"
      Begin VB.Menu mnuFileNew 
         Caption         =   "&Nouveau"
      End
      Begin VB.Menu mnuFileOpen 
         Caption         =   "&Ouvrir"
      End
      Begin VB.Menu mnuFileSave 
         Caption         =   "&Enregistrer"
      End
      Begin VB.Menu mnuFileSaveAs 
         Caption         =   "Enregistrer &sous"
      End
      Begin VB.Menu mnuFSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "&Quitter"
      End
      Begin VB.Menu mnuRecentFile 
         Caption         =   "-"
         Index           =   0
         Visible         =   0   'False
      End
      Begin VB.Menu mnuRecentFile 
         Caption         =   "RecentFile1"
         Index           =   1
         Visible         =   0   'False
      End
      Begin VB.Menu mnuRecentFile 
         Caption         =   "RecentFile2"
         Index           =   2
         Visible         =   0   'False
      End
      Begin VB.Menu mnuRecentFile 
         Caption         =   "RecentFile3"
         Index           =   3
         Visible         =   0   'False
      End
      Begin VB.Menu mnuRecentFile 
         Caption         =   "RecentFile4"
         Index           =   4
         Visible         =   0   'False
      End
      Begin VB.Menu mnuRecentFile 
         Caption         =   "RecentFile5"
         Index           =   5
         Visible         =   0   'False
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "&Edition"
      Begin VB.Menu mnuEditCut 
         Caption         =   "&Couper"
         Shortcut        =   ^X
      End
      Begin VB.Menu mnuEditCopy 
         Caption         =   "Co&pier"
         Shortcut        =   ^C
      End
      Begin VB.Menu mnuEditPaste 
         Caption         =   "C&oller"
         Shortcut        =   ^V
      End
      Begin VB.Menu mnuEditDelete 
         Caption         =   "&Supprimer"
         Shortcut        =   {DEL}
      End
      Begin VB.Menu mnuEditSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditSelectAll 
         Caption         =   "Sélectionner &tout"
      End
      Begin VB.Menu mnuEditTime 
         Caption         =   "&Heure/Date"
      End
   End
   Begin VB.Menu mnuSearch 
      Caption         =   "&Rechercher"
      Begin VB.Menu mnuSearchFind 
         Caption         =   "&Chercher"
      End
      Begin VB.Menu mnuSearchFindNext 
         Caption         =   "&Suivant"
         Shortcut        =   {F3}
      End
   End
   Begin VB.Menu mnuOptions 
      Caption         =   "&Options"
      Begin VB.Menu mnuOptionsToolbar 
         Caption         =   "&Barre d'outils"
      End
      Begin VB.Menu mnuFonts 
         Caption         =   "&Police"
         Begin VB.Menu mnuFontName 
            Caption         =   "Nom de police"
            Index           =   0
         End
      End
      Begin VB.Menu mnuOptionsLaunch 
         Caption         =   "&Lancer une nouvelle instance"
      End
   End
End
Attribute VB_Name = "frmSDI"
Attribute VB_Base = "0{8EC00D4C-E9E4-11CF-84BA-00AA00C007F0}"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_TemplateDerived = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'*** Feuille principale de l'exemple d'application Bloc-notes SDI.***
'********************************************************************
Option Explicit

Private Sub Form_Load()
    Dim i As Integer        ' Variable Compteur.
    
    ' L'application commence ici (événement Load de la feuille de démarrage).
    Show
    ' Définit le dossier de travail comme étant le dossier de l'application.
    ChDir App.Path
    FState.Dirty = False
    ' Lit la base de registres du système et définit de manière adéquate
    ' la liste des derniers fichiers ouverts, dans le menu Fichier.
    GetRecentFiles
    ' Définit la variable publique gFindDirection qui détermine dans quelle direction
    ' la fonction FindIt va effectuer la recherche.
    gFindDirection = 1
        
    ' Affecte le nom de la première police dans l'entrée du menu Police,
    ' puis fait une boucle sur la collection Fonts, en les ajoutant au menu.
    mnuFontName(0).Caption = Screen.Fonts(0)
    For i = 1 To Screen.FontCount - 1
        Load mnuFontName(i)
        mnuFontName(0).Caption = Screen.Fonts(i)
    Next
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    Dim strMsg As String
    Dim strFilename As String
    Dim intResponse As Integer

    ' Vérifie si le texte à été modifié.
    If FState.Dirty Then
        strFilename = Me.Caption
        strMsg = "Le texte de [" & strFilename & "] a été modifié."
        strMsg = strMsg & vbCrLf
        strMsg = strMsg & " Enregistrer les modifications?"
        intResponse = MsgBox(strMsg, 51, frmSDI.Caption)
        Select Case intResponse
            Case 6      ' L'utilisateur a cliqué sur Oui.
                If Left(Me.Caption, 10) = "Sans titre" Then
                    ' Le fichier n'a pas encore été enregistré.
                    strFilename = "Sans titre.txt"
                    ' Obtient le nom de fichier, appelle ensuite la procédure d'enregistrement SaveFileAs.
                    strFilename = GetFileName(strFilename)
                Else
                    ' Le titre de la feuille contient le nom du fichier ouvert.
                    strFilename = Me.Caption
                End If
                ' Appelle la procédure d'enregistrement. Si la variable strFilename est vide,
                ' l'utilisateur a cliqué sur Annuler dans la boîte de dialogue Enregistrer sous...;
                ' sinon, enregistre le fichier.
                If strFilename <> "" Then
                    SaveFileAs strFilename
                End If
            Case 7      ' L'utilisateur a cliqué sur Non. Décharge le fichier.
                Cancel = False
            Case 2      ' L'utilisateur a cliqué sur Annuler. Annule le déchargement.
                Cancel = True
        End Select
    End If
End Sub

Private Sub Form_Resize()
    ' Appelle la procédure de redimensionnement.
    ResizeNote
End Sub

Private Sub Form_Unload(Cancel As Integer)
    ' Appelle la procédure pour obtenir la liste des fichiers ouverts.
    GetRecentFiles
End Sub

Private Sub imgCopyButton_Click()
    ' Rafraîchit l'image.
    imgCopyButton.Refresh
    ' Appelle la procédure pour copier.
    EditCopyProc
End Sub

Private Sub imgCopyButton_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Affiche l'image pour l'état Down.
    imgCopyButton.Picture = imgCopyButtonDn.Picture
End Sub

Private Sub imgCopyButton_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Si le bouton est enfoncé, affiche le bitmap Up lorsque la
    ' souris est déplacée à l'extérieur de la zone de boutons.
    ' Sinon, affiche le bitmap Down.
    Select Case Button
    Case 1
        If X <= 0 Or X > imgCopyButton.Width Or Y < 0 Or Y > imgCopyButton.Height Then
            imgCopyButton.Picture = imgCopyButtonUp.Picture
        Else
            imgCopyButton.Picture = imgCopyButtonDn.Picture
        End If
    End Select
End Sub

Private Sub imgCopyButton_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Affiche l'image pour l'état Up.
    imgCopyButton.Picture = imgCopyButtonUp.Picture
End Sub

Private Sub imgCutButton_Click()
    ' Rafraîchit l'image.
    imgCutButton.Refresh
    ' Appelle la procédure pour couper.
    EditCutProc
End Sub

Private Sub imgCutButton_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Affiche l'image pour l'état Down.
    imgCutButton.Picture = imgCutButtonDn.Picture
End Sub

Private Sub imgCutButton_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Si le bouton est enfoncé, affiche le bitmap Up lorsque la
    ' souris est déplacée à l'extérieur de la zone de boutons.
    ' Sinon, affiche le bitmap Down.
    Select Case Button
    Case 1
        If X <= 0 Or X > imgCutButton.Width Or Y < 0 Or Y > imgCutButton.Height Then
            imgCutButton.Picture = imgCutButtonUp.Picture
        Else
            imgCutButton.Picture = imgCutButtonDn.Picture
        End If
    End Select
End Sub

Private Sub imgCutButton_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Affiche l'image pour l'état Up.
    imgCutButton.Picture = imgCutButtonUp.Picture
End Sub

Private Sub imgFileNewButton_Click()
    ' Rafraîchit l'image.
    imgFileNewButton.Refresh
    ' Appelle la procédure pour créer une nouvelle feuille.
    FileNew
End Sub

Private Sub imgFileNewButton_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Affiche l'image pour l'état Down.
    imgFileNewButton.Picture = imgFileNewButtonDn.Picture
End Sub

Private Sub imgFileNewButton_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Si le bouton est enfoncé, affiche le bitmap Up lorsque la
    ' souris est déplacée à l'extérieur de la zone de boutons.
    ' Sinon, affiche le bitmap Down.
    Select Case Button
    Case 1
        If X <= 0 Or X > imgFileNewButton.Width Or Y < 0 Or Y > imgFileNewButton.Height Then
            imgFileNewButton.Picture = imgFileNewButtonUp.Picture
        Else
            imgFileNewButton.Picture = imgFileNewButtonDn.Picture
        End If
    End Select
End Sub

Private Sub imgFileNewButton_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Affiche l'image pour l'état Up.
    imgFileNewButton.Picture = imgFileNewButtonUp.Picture
End Sub

Private Sub imgFileOpenButton_Click()
    ' Rafraîchit l'image.
    imgFileOpenButton.Refresh
    ' Appelle la procédure pour ouvrir un fichier.
    FileOpenProc
End Sub

Private Sub imgFileOpenButton_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Affiche l'image pour l'état Down.
    imgFileOpenButton.Picture = imgFileOpenButtonDn.Picture
End Sub

Private Sub imgFileOpenButton_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Si le bouton est enfoncé, affiche le bitmap Up lorsque la
    ' souris est déplacée à l'extérieur de la zone de boutons.
    ' Sinon, affiche le bitmap Down.
    Select Case Button
    Case 1
        If X <= 0 Or X > imgFileOpenButton.Width Or Y < 0 Or Y > imgFileOpenButton.Height Then
            imgFileOpenButton.Picture = imgFileOpenButtonUp.Picture
        Else
            imgFileOpenButton.Picture = imgFileOpenButtonDn.Picture
        End If
    End Select
End Sub

Private Sub imgFileOpenButton_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Affiche l'image pour l'état Up.
    imgFileOpenButton.Picture = imgFileOpenButtonUp.Picture

End Sub

Private Sub imgPasteButton_Click()
    ' Rafraîchit l'image.
    imgPasteButton.Refresh
    ' Appelle la procédure pour coller.
    EditPasteProc
End Sub

Private Sub imgPasteButton_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Affiche l'image pour l'état Down.
    imgPasteButton.Picture = imgPasteButtonDn.Picture
End Sub

Private Sub imgPasteButton_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Si le bouton est enfoncé, affiche le bitmap Up lorsque la
    ' souris est déplacée à l'extérieur de la zone de boutons.
    ' Sinon, affiche le bitmap Down.
    Select Case Button
    Case 1
        If X <= 0 Or X > imgPasteButton.Width Or Y < 0 Or Y > imgPasteButton.Height Then
            imgPasteButton.Picture = imgPasteButtonUp.Picture
        Else
            imgPasteButton.Picture = imgPasteButtonDn.Picture
        End If
    End Select
End Sub

Private Sub imgPasteButton_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Affiche l'image pour l'état Up.
    imgPasteButton.Picture = imgPasteButtonUp.Picture
End Sub

Private Sub mnuEditCopy_Click()
    ' Appelle la procédure pour copier.
    EditCopyProc
End Sub

Private Sub mnuEditCut_Click()
    ' Appelle la procédure pour couper.
    EditCutProc
End Sub

Private Sub mnuEditDelete_Click()
' Si le curseur n'est pas à la fin du Bloc-notes...
    If txtNote.SelStart <> Len(Screen.ActiveControl.Text) Then
        ' Si rien n'est sélectionné, étend la sélection de un.
        If txtNote.SelLength = 0 Then
            txtNote.SelLength = 1
            ' Si le curseur est sur une ligne blanche, étend la sélection de deux.
            If Asc(txtNote.SelText) = 13 Then
                txtNote.SelLength = 2
            End If
        End If
        ' Suppression du texte sélectionné.
        txtNote.SelText = ""
    End If
End Sub

Private Sub mnuEditPaste_Click()
    ' Appelle la procédure pour coller.
    EditPasteProc
End Sub

Private Sub mnuEditSelectAll_Click()
    ' Utilise les propriétés SelStart et SelLength pour sélectionner le texte.
    txtNote.SelStart = 0
    txtNote.SelLength = Len(txtNote.Text)
End Sub

Private Sub mnuEditTime_Click()
    ' Insère la date et l'heure courantes.
    txtNote.SelText = Now
End Sub

Private Sub mnuFileExit_Click()
    ' Termine l'application.
    Unload Me
End Sub

Public Sub mnuFileNew_Click()
    ' Appelle la procédure pour créer un nouveau fichier.
    FileNew
End Sub

Private Sub mnuFileOpen_Click()
    ' Appelle la procédure pour ouvrir un fichier.
    FileOpenProc
End Sub

Private Sub mnuFileSave_Click()
    ' Appelle la procédure d'enregistrement.
    FileSave
End Sub

Private Sub mnuFileSaveAs_Click()
    Dim strSaveFileName As String
    Dim strDefaultName As String
    
    ' Affecte le titre de la feuille à la variable.
    strDefaultName = Right$(Me.Caption, Len(Me.Caption) - 17)
    If Me.Caption = "Bloc-notes SDI - Sans titre" Then
        ' Le fichier n'a pas encore été enregistré.
        ' Obtient le nom du fichier, puis appelle la procédure d'enregistrement SaveFileAs.
        strSaveFileName = GetFileName("Sans titre.txt")
        If strSaveFileName <> "" Then SaveFileAs (strSaveFileName)
        ' Mise à jour de la liste des fichiers ouverts dans le menu Fichier.
        UpdateFileMenu (strSaveFileName)
    Else
        ' Le titre de la feuille contient le nom du fichier ouvert.
        strSaveFileName = GetFileName(strDefaultName)
        If strSaveFileName <> "" Then SaveFileAs (strSaveFileName)
        ' Mise à jour de la liste des fichiers ouverts dans le menu Fichier.
        UpdateFileMenu (strSaveFileName)
    End If
End Sub

Private Sub mnuFontName_Click(Index As Integer)
    ' Affecte la propriété FontName du contrôle TextBox avec la police sélectionnée.
    txtNote.FontName = mnuFontName(Index).Caption
End Sub

Private Sub mnuOptions_Click()
    ' Bascule la propriété Checked pour correspondre à la propriété Visible.
    mnuOptionsToolbar.Checked = picToolbar.Visible
End Sub

Private Sub mnuOptionsLaunch_Click()
    Dim strApp As String
    
    ' Démarre une nouvelle instance du Bloc-notes.
    strApp = App.Path & "\" & App.EXEName
    Shell strApp, 1
End Sub

Private Sub mnuOptionsToolbar_Click()
    ' Bascule la propriété Visible du contrôle ToolBar.
    picToolbar.Visible = Not picToolbar.Visible
    ' Active/désactive la coche selon l'état en cours.
    mnuOptionsToolbar.Checked = picToolbar.Visible
    ' Appelle la procédure de redimensionnement.
    ResizeNote
End Sub

Private Sub mnuRecentFile_Click(Index As Integer)
    ' Appelle la procédure pour ouvrir un fichier en passant comme
    ' référence le nom du fichier sélectionné.
    OpenFile (mnuRecentFile(Index).Caption)
    ' Mise à jour de la liste des fichiers ouverts dans le menu Fichier.
    GetRecentFiles
End Sub

Private Sub mnuSearchFind_Click()
    ' S'il existe du texte dans la zone de texte, l'affecte
    ' à la zone de texte de la feuille Chercher, sinon affecte la dernière valeur recherchée.
    If txtNote.SelText <> "" Then
        frmFind.txtFind.Text = txtNote.SelText
    Else
        frmFind.txtFind.Text = gFindString
    End If
    ' Définit la variable publique pour démarrer au début.
    gFirstTime = True
    ' Définit la case à cocher pour correspondre à la variable publique.
    If (gFindCase) Then
        frmFind.chkCase = 1
    End If
    ' Affiche la feuille Chercher.
    frmFind.Show vbModal
End Sub

Private Sub mnuSearchFindNext_Click()
    ' Si la variable publique n'est pas vide, appelle la procédure
    ' pour rechercher; sinon appelle le menu Chercher.
    If Len(gFindString) > 0 Then
        FindIt
    Else
        mnuSearchFind_Click
    End If
End Sub

Private Sub txtNote_Change()
    ' Définit la variable publique pour montrer que le texte a changé.
    FState.Dirty = True
End Sub
