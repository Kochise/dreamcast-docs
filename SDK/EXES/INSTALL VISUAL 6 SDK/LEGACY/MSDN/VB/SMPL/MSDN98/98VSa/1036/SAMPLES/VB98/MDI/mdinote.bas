Attribute VB_Name = "Module1"
'***   Module global de l'application Bloc-notes MDI    ***
'**********************************************************
Option Explicit

' Type défini par l'utilisateur pour stocker les informations sur les feuilles filles
Type FormState
    Deleted As Integer
    Dirty As Integer
    Color As Long
End Type

Public FState()  As FormState           ' Tableau des types définis par l'utilisateur
Public Document() As New frmNotePad     ' Tableau des objets des feuilles filles
Public gFindString As String            ' Contient le texte à chercher.
Public gFindCase As Integer             ' Clé pour une recherche avec casse.
Public gFindDirection As Integer        ' Clé pour la direction de recherche.
Public gCurPos As Integer               ' Contient la location du curseur.
Public gFirstTime As Integer            ' Clé pour position initiale.
Public gToolsHidden As Boolean          ' Contient l'état de la barre d'outils.
Public Const ThisApp = "MDINote"        ' Constante de l'application des registres.
Public Const ThisKey = "Recent Files"   ' Constante de la clé des registres.


Function AnyPadsLeft() As Integer
    Dim i As Integer        ' Variable counteur

    ' Cycle à travers le tableau des documents.
    ' Retourne la valeur True s'il y a au moins un document ouvert.
    For i = 1 To UBound(Document)
        If Not FState(i).Deleted Then
            AnyPadsLeft = True
            Exit Function
        End If
    Next
End Function


Sub EditCopyProc()
    ' Copie le texte sélectionné dans la Presse-papiers.
    Clipboard.SetText frmMDI.ActiveForm.ActiveControl.SelText
End Sub

Sub EditCutProc()
    ' Copie le texte sélectionné dans la Presse-papiers.
    Clipboard.SetText frmMDI.ActiveForm.ActiveControl.SelText
    ' Supprime le texte sélectionné.
    frmMDI.ActiveForm.ActiveControl.SelText = ""
End Sub

Sub EditPasteProc()
    ' Place le texte du Presse-papiers dans le contrôle actif.
    frmMDI.ActiveForm.ActiveControl.SelText = Clipboard.GetText()
End Sub

Sub FileNew()
    Dim fIndex As Integer

    ' Trouve le prochain index et affiche la feuille fille.
    fIndex = FindFreeIndex()
    Document(fIndex).Tag = fIndex
    Document(fIndex).Caption = "Sans titre:" & fIndex
    Document(fIndex).Show

    ' Assurez-vous que les boutons d'édition de la barre d'outils soient visibles.
    frmMDI.imgCutButton.Visible = True
    frmMDI.imgCopyButton.Visible = True
    frmMDI.imgPasteButton.Visible = True
End Sub

Function FindFreeIndex() As Integer
    Dim i As Integer
    Dim ArrayCount As Integer

    ArrayCount = UBound(Document)

    ' Cycle à travers le tableau des documents.
    ' Si l'un des documents vient d'être supprimé, alors retourne cet index.
    For i = 1 To ArrayCount
        If FState(i).Deleted Then
            FindFreeIndex = i
            FState(i).Deleted = False
            Exit Function
        End If
    Next
    ' Si aucun élément dans le tableau des documents a été supprimé
    ' alors incrémente de 1 les tableaux des documents et des états
    ' et puis retourne l'index au nouvel élément.
    ReDim Preserve Document(ArrayCount + 1)
    ReDim Preserve FState(ArrayCount + 1)
    FindFreeIndex = UBound(Document)
End Function

Sub FindIt()
    Dim intStart As Integer
    Dim intPos As Integer
    Dim strFindString As String
    Dim strSourceString As String
    Dim strMsg As String
    Dim intResponse As Integer
    Dim intOffset As Integer
    
    ' Définit la variable de décalage basée sur la position du curseur.
    If (gCurPos = frmMDI.ActiveForm.ActiveControl.SelStart) Then
        intOffset = 1
    Else
        intOffset = 0
    End If

    ' Lit la position initiale de la variable publique.
    If gFirstTime Then intOffset = 0
    ' Affecte une valeur à la valeur initiale.
    intStart = frmMDI.ActiveForm.ActiveControl.SelStart + intOffset
        
    ' S'il n'est pas avec casse, convertit la chaîne en majuscule
    If gFindCase Then
        strFindString = gFindString
        strSourceString = frmMDI.ActiveForm.ActiveControl.Text
    Else
        strFindString = UCase(gFindString)
        strSourceString = UCase(frmMDI.ActiveForm.ActiveControl.Text)
    End If
            
    ' Recherche la chaîne.
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
        frmMDI.ActiveForm.ActiveControl.SelStart = intPos - 1
        frmMDI.ActiveForm.ActiveControl.SelLength = Len(strFindString)
    Else
        strMsg = "Impossible de trouver " & Chr(34) & gFindString & Chr(34)
        intResponse = MsgBox(strMsg, 0, App.Title)
    End If
    
    ' Réinitialise les variables publiques
    gCurPos = frmMDI.ActiveForm.ActiveControl.SelStart
    gFirstTime = False
End Sub

Sub GetRecentFiles()
    ' Cette procédure démontre l'utilisation de la fonction GetAllSettings,
    ' laquelle retourne un tableau de valeurs à partir de la base de registres Windows.
    ' Dans ce cas le registre contient les fichiers ouverts le plus récemment.
    ' Utilise la procédure SaveSetting pour écrire les noms des fichiers les
    ' plus récents. Cette procédure est utilisée dans WriteRecentFiles.

    Dim i, j As Integer
    Dim varFiles As Variant ' Variable pour stocker le tableau renvoyé.
    ' Obtient les fichiers récents de la base de registres avec la procédure GetAllSettings.
    ' ThisApp et ThisKey sont des constantes définies dans ce module.
    If GetSetting(ThisApp, ThisKey, "RecentFile1") = Empty Then Exit Sub
    
    varFiles = GetAllSettings(ThisApp, ThisKey)
    
    For i = 0 To UBound(varFiles, 1)
        
        frmMDI.mnuRecentFile(0).Visible = True
        frmMDI.mnuRecentFile(i).Caption = varFiles(i, 1)
        frmMDI.mnuRecentFile(i).Visible = True
            ' Cycle à travers tous les documents et met à jour chaque menu.
            For j = 1 To UBound(Document)
                If Not FState(j).Deleted Then
                    Document(j).mnuRecentFile(0).Visible = True
                    Document(j).mnuRecentFile(i + 1).Caption = varFiles(i, 1)
                    Document(j).mnuRecentFile(i + 1).Visible = True
                End If
            Next j
    Next i

End Sub

Sub OptionsToolbarProc(CurrentForm As Form)
    ' Bascule la valeur de la case à cocher
    CurrentForm.mnuOptionsToolbar.Checked = Not CurrentForm.mnuOptionsToolbar.Checked
    ' S'il n'est pas une feuille MDI, définit la case à cocher de la feuille MDI.
    If Not TypeOf CurrentForm Is MDIForm Then
        frmMDI.mnuOptionsToolbar.Checked = CurrentForm.mnuOptionsToolbar.Checked
    End If
    ' Bascule la barre d'outils
    If CurrentForm.mnuOptionsToolbar.Checked Then
        frmMDI.picToolbar.Visible = True
    Else
        frmMDI.picToolbar.Visible = False
    End If
End Sub

Sub WriteRecentFiles(OpenFileName)
    ' Cette procédure utilise SaveSettings pour écrire les noms des fichiers les
    ' plus récents dans la base de registres système. La procédure SaveSetting nécessite
    ' trois paramètres. Deux de ces paramètres sont stockés comme constantes et sont définis
    ' dans ce module. La fonction GetAllSettings est utilisée dans la procédure GetRecentFiles
    ' pour récupérer le noms des fichiers stockés dans cette procédure.
    
    Dim i, j As Integer
    Dim strFile, key As String

    ' Copie RecentFile1 dans RecentFile2
    For i = 3 To 1 Step -1
        key = "RecentFile" & i
        strFile = GetSetting(ThisApp, ThisKey, key)
        If strFile <> "" Then
            key = "RecentFile" & (i + 1)
            SaveSetting ThisApp, ThisKey, key, strFile
        End If
    Next i
  
    ' Écrit le nom du fichier ouvert comme étant le fichier le plus récent.
    SaveSetting ThisApp, ThisKey, "RecentFile1", OpenFileName
End Sub

