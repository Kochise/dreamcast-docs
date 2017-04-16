Attribute VB_Name = "Module1"
'*** Module global pour l'exemple d'application Bloc-notes SDI. ***
'******************************************************************
Option Explicit

' Type défini par l'utilisateur pour stocker des informations au sujet des feuilles fille.
Type FormState
    Deleted As Integer
    Dirty As Integer
    Color As Long
End Type

Public FState As FormState              ' Tableau de types définis par l'utilisateur.
Public gFindString As String            ' Stocke le texte recherché.
Public gFindCase As Integer             ' Clé pour la recherche avec respect de la casse.
Public gFindDirection As Integer        ' Clé pour la direction de la recherche.
Public gCurPos As Integer               ' Stocke la position du curseur.
Public gFirstTime As Integer            ' Clé pour la position de démarrage.
Public Const ThisApp = "MDINote"        ' Constante Registry App.
Public Const ThisKey = "Recent Files"   ' Constante Registry Key.


Sub EditCopyProc()
    ' Copie le texte sélectionné dans le Presse-papiers.
    Clipboard.SetText frmSDI.txtNote.SelText
End Sub

Sub EditCutProc()
    ' Copie le texte sélectionné dans le Presse-papiers.
    Clipboard.SetText frmSDI.txtNote.SelText
    ' Supprime le texte sélectionné.
    frmSDI.txtNote.SelText = ""
End Sub

Sub EditPasteProc()
    ' Place le texte depuis le Presse-papiers dans un contrôle actif.
    frmSDI.txtNote.SelText = Clipboard.GetText()
End Sub

Sub FileNew()
    Dim intResponse As Integer
    
    ' Si le fichier a changé, l'enregistre.
    If FState.Dirty = True Then
        intResponse = FileSave
        If intResponse = False Then Exit Sub
    End If
    ' Efface le contenu du contrôle TextBox et met à jour le titre de la feuille.
    frmSDI.txtNote.Text = ""
    frmSDI.Caption = "Bloc-notes SDI - Sans titre"
End Sub
Function FileSave() As Integer
    Dim strFilename As String

    If frmSDI.Caption = "Bloc-notes SDI - Sans titre" Then
        ' Le fichier n'a pas encore été enregistré.
        ' Obtient le nom de fichier, puis appelle la procédure d'enregistrement SaveFileAs.
        strFilename = GetFileName(strFilename)
    Else
        ' Le titre de la feuille contient le nom du fichier ouvert.
        strFilename = Right(frmSDI.Caption, Len(frmSDI.Caption) - 17)
    End If
    ' Appelle la procédure d'enregistrement. Si la variable strFilename est vide,
    ' l'utilisateur a cliqué sur Annuler dans la boîte de dialogue Enregistrer sous...;
    ' sinon, enregistre le fichier.
    If strFilename <> "" Then
        SaveFileAs strFilename
        FileSave = True
    Else
        FileSave = False
    End If
End Function


Sub FindIt()
    Dim intStart As Integer
    Dim intPos As Integer
    Dim strFindString As String
    Dim strSourceString As String
    Dim strMsg As String
    Dim intResponse As Integer
    Dim intOffset As Integer
    
    ' Définit la variable offset basée sur la position du curseur.
    If (gCurPos = frmSDI.txtNote.SelStart) Then
        intOffset = 1
    Else
        intOffset = 0
    End If

    ' Lit la variable publique pour la position de démarrage.
    If gFirstTime Then intOffset = 0
    ' Affecte une valeur pour la valeur de démarrage.
    intStart = frmSDI.txtNote.SelStart + intOffset
        
    ' Sans respect de la casse, convertit la chaîne en majuscules.
    If gFindCase Then
        strFindString = gFindString
        strSourceString = frmSDI.txtNote.Text
    Else
        strFindString = UCase(gFindString)
        strSourceString = UCase(frmSDI.txtNote.Text)
    End If
            
    ' Recherche pour la chaîne.
    If gFindDirection = 1 Then
        intPos = InStr(intStart + 1, strSourceString, strFindString)
    Else
        For intPos = intStart - 1 To 0 Step -1
            If intPos = 0 Then Exit For
            If Mid(strSourceString, intPos, Len(strFindString)) = strFindString Then Exit For
        Next
    End If

    ' Si la chaîne est trouvée...
    If intPos Then
        frmSDI.txtNote.SelStart = intPos - 1
        frmSDI.txtNote.SelLength = Len(strFindString)
    Else
        strMsg = "Impossible de trouver " & Chr(34) & gFindString & Chr(34)
        intResponse = MsgBox(strMsg, 0, App.Title)
    End If
    
    ' Réinitialise les variables publiques.
    gCurPos = frmSDI.txtNote.SelStart
    gFirstTime = False
End Sub

Sub GetRecentFiles()
    ' Cette procédure montre l'utilisation de la fonction GetAllSettings,
    ' qui retourne un tableau de valeurs de la base de registres de Windows.
    ' Dans ce cas, la base de registres contient les derniers fichiers ouverts.
    ' Utilisez l'instruction SaveSetting pour écrire le nom des fichiers les plus récents.
    ' Cette instruction est utilisée dans la procédure WriteRecentFiles.
    Dim i As Integer
    Dim varFiles As Variant ' Variable pour stocker le tableau renvoyé.
 
    ' Obtient les fichiers les plus récents de la base de registres à l'aide de l'instruction GetAllSettings.
    ' ThisApp et ThisKey sont des constantes définies dans ce module.
    If GetSetting(ThisApp, ThisKey, "RecentFile1") = Empty Then Exit Sub
    
    varFiles = GetAllSettings(ThisApp, ThisKey)
    
    For i = 0 To UBound(varFiles, 1)
        frmSDI.mnuRecentFile(0).Visible = True
        frmSDI.mnuRecentFile(i + 1).Caption = varFiles(i, 1)
        frmSDI.mnuRecentFile(i + 1).Visible = True
    Next i
End Sub
Sub ResizeNote()
    ' Agrandit la zone de texte pour remplir la zone interne de la feuille.
    If frmSDI.picToolbar.Visible Then
        frmSDI.txtNote.Height = frmSDI.ScaleHeight - frmSDI.picToolbar.Height
        frmSDI.txtNote.Width = frmSDI.ScaleWidth
        frmSDI.txtNote.Top = frmSDI.picToolbar.Height
    Else
        frmSDI.txtNote.Height = frmSDI.ScaleHeight
        frmSDI.txtNote.Width = frmSDI.ScaleWidth
        frmSDI.txtNote.Top = 0
    End If
End Sub


Sub WriteRecentFiles(OpenFileName)
    ' Cette procédure utilise l'instruction SaveSettings pour écrire le nom des derniers fichiers
    ' ouverts dans la base de registres. L'instruction SaveSettings requiert
    ' trois paramètres. Deux d'entre eux sont stockés en tant que constantes et sont
    ' définis dans ce module. La fonction GetAllSettings est utilisée dans la procédure
    ' GetRecentFiles pour récupérer les noms de fichiers stockés dans cette procédure.
    
    Dim i As Integer
    Dim strFile As String
    Dim strKey As String

    ' Copie RecentFile1 dans RecentFile2, et ainsi de suite.
    For i = 3 To 1 Step -1
        strKey = "RecentFile" & i
        strFile = GetSetting(ThisApp, ThisKey, strKey)
        If strFile <> "" Then
            strKey = "RecentFile" & (i + 1)
            SaveSetting ThisApp, ThisKey, strKey, strFile
        End If
    Next i
  
    ' Écrit le fichier ouvert dans le fichier le plus récent.
    SaveSetting ThisApp, ThisKey, "RecentFile1", OpenFileName
End Sub

