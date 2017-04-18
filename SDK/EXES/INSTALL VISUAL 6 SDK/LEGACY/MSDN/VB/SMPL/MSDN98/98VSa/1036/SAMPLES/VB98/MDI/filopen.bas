Attribute VB_Name = "Module2"
'*** Module standard contenant des procédures pour travailler avec des ***
'*** fichiers. Partie de l'exemple d'application Bloc-notes MDI.    ***
'********************************************************************
Option Explicit

Sub FileOpenProc()
    Dim intRetVal
    On Error Resume Next
    Dim strOpenFileName As String
    frmMDI.CMDialog1.Filename = ""
    frmMDI.CMDialog1.ShowOpen
    If Err <> 32755 Then    ' L'utilisateur a cliqué sur Annuler.
        strOpenFileName = frmMDI.CMDialog1.Filename
        ' Si le fichier dépasse 65 Ko, il ne peut pas être ouvert.
        ' Annule l'opération.
        If FileLen(strOpenFileName) > 65000 Then
            MsgBox " Le fichier est trop grand pour être ouvert."
            Exit Sub
        End If
        
        OpenFile (strOpenFileName)
        UpdateFileMenu (strOpenFileName)
        ' Affiche la barre d'outils si les boutons ne sont pas déjà visibles.
        If gToolsHidden Then
            frmMDI.imgCutButton.Visible = True
            frmMDI.imgCopyButton.Visible = True
            frmMDI.imgPasteButton.Visible = True
            gToolsHidden = False
        End If
    End If
End Sub

Function GetFileName(Filename As Variant)
    ' Affiche la boîte de dialogue Enregistrer sous et renvoie un nom de fichier.
    ' Si l'utilisateur clique sur Annuler, une chaîne vide est renvoyée.
    On Error Resume Next
    frmMDI.CMDialog1.Filename = Filename
    frmMDI.CMDialog1.ShowSave
    If Err <> 32755 Then    ' L'utilisateur a cliqué sur Annuler.
        GetFileName = frmMDI.CMDialog1.Filename
    Else
        GetFileName = ""
    End If
End Function

Function OnRecentFilesList(Filename) As Integer
  Dim i         ' Variable Compteur.

  For i = 1 To 4
    If frmMDI.mnuRecentFile(i).Caption = Filename Then
      OnRecentFilesList = True
      Exit Function
    End If
  Next i
    OnRecentFilesList = False
End Function

Sub OpenFile(Filename)
    Dim fIndex As Integer
    
    On Error Resume Next
    ' Ouvre le fichier sélectionné.
    Open Filename For Input As #1
    If Err Then
        MsgBox "Impossible d'ouvrir le fichier: " + Filename
        Exit Sub
    End If
    ' Transforme le pointeur de la souris en sablier.
    Screen.MousePointer = 11
    
    ' Modifie le titre de la feuille et affiche le nouveau texte.
    fIndex = FindFreeIndex()
    Document(fIndex).Tag = fIndex
    Document(fIndex).Caption = UCase(Filename)
    Document(fIndex).Text1.Text = StrConv(InputB(LOF(1), 1), vbUnicode)
    FState(fIndex).Dirty = False
    Document(fIndex).Show
    Close #1
    ' Réinitialise le pointeur de la souris.
    Screen.MousePointer = 0
    
End Sub

Sub SaveFileAs(Filename)
    On Error Resume Next
    Dim strContents As String

    ' Ouvre le fichier.
    Open Filename For Output As #1
    ' Place le contenu du Bloc-notes dans une variable.
    strContents = frmMDI.ActiveForm.Text1.Text
    ' Affiche le sablier.
    Screen.MousePointer = 11
    ' Écrit le contenu de la variable dans le fichier enregistré.
    Print #1, strContents
    Close #1
    ' Réinitialise le pointeur de la souris.
    Screen.MousePointer = 0
    ' Définit le titre de la feuille.
    If Err Then
        MsgBox Error, 48, App.Title
    Else
        frmMDI.ActiveForm.Caption = UCase(Filename)
        ' Réinitialise la propriété Dirty.
        FState(frmMDI.ActiveForm.Tag).Dirty = False
    End If
End Sub

Sub UpdateFileMenu(Filename)
        Dim intRetVal As Integer
        ' Vérifie que le nom du fichier ouvert est déjà dans la liste des fichiers.
        intRetVal = OnRecentFilesList(Filename)
        If Not intRetVal Then
            ' Écrit le nom du fichier ouvert dans la base de registres.
            WriteRecentFiles (Filename)
        End If
        ' Mise à jour de la liste des fichiers ouverts dans le menu Fichier.
        GetRecentFiles
End Sub


