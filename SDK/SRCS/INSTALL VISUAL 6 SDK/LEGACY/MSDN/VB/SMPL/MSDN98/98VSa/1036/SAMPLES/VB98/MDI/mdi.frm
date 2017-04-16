VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.MDIForm frmMDI 
   BackColor       =   &H8000000C&
   Caption         =   "Bloc-notes MDI"
   ClientHeight    =   3495
   ClientLeft      =   915
   ClientTop       =   2205
   ClientWidth     =   5835
   LinkTopic       =   "MDIForm1"
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
      ScaleWidth      =   5775
      TabIndex        =   0
      Top             =   0
      Width           =   5835
      Begin MSComDlg.CommonDialog CMDialog1 
         Left            =   1995
         Top             =   0
         _ExtentX        =   847
         _ExtentY        =   847
         _Version        =   393216
         CancelError     =   -1  'True
         DefaultExt      =   "TXT"
         Filter          =   "Fichiers Texte (*.txt)|*.txt|Tous les fichiers (*.*)|*.*"
         FilterIndex     =   557
         FontSize        =   1,27584e-37
      End
      Begin VB.Image imgPasteButtonUp 
         Height          =   330
         Left            =   5280
         Picture         =   "mdi.frx":0000
         Top             =   0
         Visible         =   0   'False
         Width           =   375
      End
      Begin VB.Image imgPasteButtonDn 
         Height          =   330
         Left            =   4920
         Picture         =   "mdi.frx":01E2
         Top             =   0
         Visible         =   0   'False
         Width           =   375
      End
      Begin VB.Image imgCopyButtonDn 
         Height          =   330
         Left            =   4200
         Picture         =   "mdi.frx":03C4
         Top             =   0
         Visible         =   0   'False
         Width           =   375
      End
      Begin VB.Image imgCopyButtonUp 
         Height          =   330
         Left            =   4560
         Picture         =   "mdi.frx":05A6
         Top             =   0
         Visible         =   0   'False
         Width           =   375
      End
      Begin VB.Image imgCutButtonDn 
         Height          =   330
         Left            =   3840
         Picture         =   "mdi.frx":0788
         Top             =   0
         Visible         =   0   'False
         Width           =   375
      End
      Begin VB.Image imgCutButtonUp 
         Height          =   330
         Left            =   3480
         Picture         =   "mdi.frx":096A
         Top             =   0
         Visible         =   0   'False
         Width           =   375
      End
      Begin VB.Image imgFileOpenButtonDn 
         Height          =   330
         Left            =   2760
         Picture         =   "mdi.frx":0B4C
         Top             =   0
         Visible         =   0   'False
         Width           =   360
      End
      Begin VB.Image imgFileOpenButtonUp 
         Height          =   330
         Left            =   3120
         Picture         =   "mdi.frx":0CD6
         Top             =   0
         Visible         =   0   'False
         Width           =   360
      End
      Begin VB.Image imgFileNewButtonUp 
         Height          =   330
         Left            =   2400
         Picture         =   "mdi.frx":0E60
         Top             =   0
         Visible         =   0   'False
         Width           =   360
      End
      Begin VB.Image imgFileNewButtonDn 
         Height          =   330
         Left            =   2040
         Picture         =   "mdi.frx":0FEA
         Top             =   0
         Visible         =   0   'False
         Width           =   375
      End
      Begin VB.Image imgPasteButton 
         Height          =   330
         Left            =   1560
         Picture         =   "mdi.frx":11CC
         ToolTipText     =   "Coller"
         Top             =   0
         Width           =   375
      End
      Begin VB.Image imgCopyButton 
         Height          =   330
         Left            =   1200
         Picture         =   "mdi.frx":13AE
         ToolTipText     =   "Copier"
         Top             =   0
         Width           =   375
      End
      Begin VB.Image imgCutButton 
         Height          =   330
         Left            =   840
         Picture         =   "mdi.frx":1590
         ToolTipText     =   "Couper"
         Top             =   0
         Width           =   375
      End
      Begin VB.Image imgFileOpenButton 
         Height          =   330
         Left            =   360
         Picture         =   "mdi.frx":1772
         ToolTipText     =   "Ouvrir"
         Top             =   0
         Width           =   360
      End
      Begin VB.Image imgFileNewButton 
         Height          =   330
         Left            =   0
         Picture         =   "mdi.frx":18FC
         ToolTipText     =   "Nouveau"
         Top             =   0
         Width           =   360
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
      Begin VB.Menu mnuFileExit 
         Caption         =   "&Quitter"
      End
      Begin VB.Menu mnuSeparator 
         Caption         =   "-"
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
   Begin VB.Menu mnuOptions 
      Caption         =   "&Options"
      Begin VB.Menu mnuOptionsToolbar 
         Caption         =   "&Barre d'outils"
      End
   End
End
Attribute VB_Name = "frmMDI"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'*** Feuille MDI principale pour l'application Bloc-notes MDI ***
'****************************************************************
Option Explicit
Private Sub imgCopyButton_Click()
    ' Rafraîchit l'image.
    imgCopyButton.Refresh
    ' Appelle la procédure pour copier.
    EditCopyProc
End Sub

Private Sub imgCopyButton_MouseDown(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Affiche l'image pour l'état Down.
    imgCopyButton.Picture = imgCopyButtonDn.Picture
End Sub

Private Sub imgCopyButton_MouseMove(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Si le bouton est enfoncé, affiche le bitmap Up lorsque la
    ' souris est déplacée à l'extérieur de la zone de boutons.
    ' Sinon, affiche le bitmap Down.
    Select Case Button
    Case 1
        If x <= 0 Or x > imgCopyButton.Width Or Y < 0 Or Y > imgCopyButton.Height Then
            imgCopyButton.Picture = imgCopyButtonUp.Picture
        Else
            imgCopyButton.Picture = imgCopyButtonDn.Picture
        End If
    End Select
End Sub

Private Sub imgCopyButton_MouseUp(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Affiche l'image pour l'état Up.
    imgCopyButton.Picture = imgCopyButtonUp.Picture
End Sub

Private Sub imgCutButton_Click()
    ' Rafraîchit l'image.
    imgCutButton.Refresh
    ' Appelle la procédure pour couper.
    EditCutProc
End Sub

Private Sub imgCutButton_MouseDown(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Affiche l'image pour l'état Down.
    imgCutButton.Picture = imgCutButtonDn.Picture
End Sub

Private Sub imgCutButton_MouseMove(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Si le bouton est enfoncé, affiche le bitmap Up lorsque la
    ' souris est déplacée à l'extérieur de la zone de boutons.
    ' Sinon, affiche le bitmap Down.
    Select Case Button
    Case 1
        If x <= 0 Or x > imgCutButton.Width Or Y < 0 Or Y > imgCutButton.Height Then
            imgCutButton.Picture = imgCutButtonUp.Picture
        Else
            imgCutButton.Picture = imgCutButtonDn.Picture
        End If
    End Select
End Sub

Private Sub imgCutButton_MouseUp(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Affiche l'image pour l'état Up.
    imgCutButton.Picture = imgCutButtonUp.Picture
End Sub

Private Sub imgFileNewButton_Click()
    ' Rafraîchit l'image.
    imgFileNewButton.Refresh
    ' Appelle la procédure pour créer une nouvelle feuille.
    FileNew
End Sub

Private Sub imgFileNewButton_MouseDown(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Affiche l'image pour l'état Down.
    imgFileNewButton.Picture = imgFileNewButtonDn.Picture
End Sub

Private Sub imgFileNewButton_MouseMove(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Si le bouton est enfoncé, affiche le bitmap Up lorsque la
    ' souris est déplacée à l'extérieur de la zone de boutons.
    ' Sinon, affiche le bitmap Down.
    Select Case Button
    Case 1
        If x <= 0 Or x > imgFileNewButton.Width Or Y < 0 Or Y > imgFileNewButton.Height Then
            imgFileNewButton.Picture = imgFileNewButtonUp.Picture
        Else
            imgFileNewButton.Picture = imgFileNewButtonDn.Picture
        End If
    End Select
End Sub

Private Sub imgFileNewButton_MouseUp(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Affiche l'image pour l'état Up.
    imgFileNewButton.Picture = imgFileNewButtonUp.Picture
End Sub

Private Sub imgFileOpenButton_Click()
    ' Rafraîchit l'image.
    imgFileOpenButton.Refresh
    ' Appelle la procédure pour ouvrir un fichier.
    FileOpenProc
End Sub

Private Sub imgFileOpenButton_MouseDown(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Affiche l'image pour l'état Down.
    imgFileOpenButton.Picture = imgFileOpenButtonDn.Picture
End Sub

Private Sub imgFileOpenButton_MouseMove(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Si le bouton est enfoncé, affiche le bitmap Up lorsque la
    ' souris est déplacée à l'extérieur de la zone de boutons.
    ' Sinon, affiche le bitmap Down.
    Select Case Button
    Case 1
        If x <= 0 Or x > imgFileOpenButton.Width Or Y < 0 Or Y > imgFileOpenButton.Height Then
            imgFileOpenButton.Picture = imgFileOpenButtonUp.Picture
        Else
            imgFileOpenButton.Picture = imgFileOpenButtonDn.Picture
        End If
    End Select
End Sub

Private Sub imgFileOpenButton_MouseUp(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Affiche l'image pour l'état Up.
    imgFileOpenButton.Picture = imgFileOpenButtonUp.Picture
End Sub

Private Sub imgPasteButton_Click()
    ' Rafraîchit l'image.
    imgPasteButton.Refresh
    ' Appelle la procédure pour coller.
    EditPasteProc
End Sub

Private Sub imgPasteButton_MouseDown(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Affiche l'image pour l'état Down.
    imgPasteButton.Picture = imgPasteButtonDn.Picture
End Sub

Private Sub imgPasteButton_MouseMove(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Si le bouton est enfoncé, affiche le bitmap Up lorsque la
    ' souris est déplacée à l'extérieur de la zone de boutons.
    ' Sinon, affiche le bitmap Down.
    Select Case Button
    Case 1
        If x <= 0 Or x > imgPasteButton.Width Or Y < 0 Or Y > imgPasteButton.Height Then
            imgPasteButton.Picture = imgPasteButtonUp.Picture
        Else
            imgPasteButton.Picture = imgPasteButtonDn.Picture
        End If
    End Select
End Sub

Private Sub imgPasteButton_MouseUp(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Afficher l'image pour l'état Up.
    imgPasteButton.Picture = imgPasteButtonUp.Picture
End Sub

Private Sub MDIForm_Load()
    ' L'application commence ici (évènement Load de la feuille Startup).
    Show
    ' Définir toujours le répertoire de travail comme le répertoire qui contient l'application.
    ChDir App.Path
    ' Initialiser le tableau de la feuille des documents, et montre le premier document.
    ReDim Document(1)
    ReDim FState(1)
    Document(1).Tag = 1
    FState(1).Dirty = False
    ' Lire la base des registres du système et mettre à jour le tableau de contrôle des fichiers utilisés récemment.
    GetRecentFiles
    ' Définir la variable publique gFindDirection qui détermine la direction
    ' de recherche de la fonction FindIt.
    gFindDirection = 1
End Sub

Private Sub MDIForm_Unload(Cancel As Integer)
    ' Si l'évènement Unload n'a pas été annulé (dans les évènements QueryUnload pour les feuilles Notepad),
    ' il n'y a plus de fenêtre de document ouverte, donc on peut procéder à la fermeture de l'application.
    If Not AnyPadsLeft() Then
        End
    End If
End Sub

Private Sub mnuFileExit_Click()
    ' Quitter application.
    End
End Sub

Private Sub mnuFileNew_Click()
    ' Appeler la procédure de nouveau fichier
    FileNew
End Sub

Private Sub mnuFileOpen_Click()
    ' Appeler la procédure d'ouverture de fichier.
    FileOpenProc
End Sub

Private Sub mnuOptions_Click()
    ' Permuter l'affichage de la barre d'outils.
    mnuOptionsToolbar.Checked = frmMDI.picToolbar.Visible
End Sub


Private Sub mnuOptionsToolbar_Click()
    ' Appeler la procédure de barre d'outil et passer
    ' une référence à cette feuille.
    OptionsToolbarProc Me
End Sub


Private Sub mnuRecentFile_Click(index As Integer)
    ' Appeler la procédure d'ouverture de fichier et passer
    ' une référence au nom de fichier sélectionné
    OpenFile (mnuRecentFile(index).Caption)
    ' Mettre à jour la liste des fichiers récemment ouverts.
    GetRecentFiles
End Sub

