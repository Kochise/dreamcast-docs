Attribute VB_Name = "ModOLECont"
Option Explicit

Public MDINew As Integer

Sub NewObject()
    MDINew = True
    NewOleForm
    If ParentForm.ActiveForm.OLE1.OLEType = vbOLENone Then
        Unload ParentForm.ActiveForm
    End If
End Sub

Sub DisplayInstructions()
    ' Déclare les variables locales.
    Dim MsgText
    Dim PB
    ' Initialise la variable d'arrêt du paragraphe.
    PB = Chr(10) & Chr(13) & Chr(10) & Chr(13)
    ' Affiche les instructions.
    MsgText = "Pour insérer un nouvel objet, cliquez sur Nouveau dans le menu Fichier, sélectionnez ensuite un objet de la boîte de dialogue Insertion de l'objet."
    MsgText = MsgText & PB & "Après avoir enregistré un objet inséré en cliquant sur Enregistrer sous, vous pouvez cliquer sur Ouvrir dans le menu Fichier pour afficher l'objet lors de sessions ultérieures."
    MsgText = MsgText & PB & "Pour modifier un objet, double-cliquez sur l'objet pour afficher l'environnement d'édition pour l'application de laquelle provient l'objet."
    MsgText = MsgText & PB & "Cliquez sur l'objet à l'aide du bouton droit de la souris pour afficher les attributs de l'objet."
    MsgText = MsgText & PB & "Utilisez les commandes Copier, Couper, et Collage spécial pour copier, couper et coller des objets."
    MsgText = MsgText & PB & "Cliquez sur Mettre à jour pour mettre à jour le sommaire de l'objet à insérer."
    MsgBox MsgText, 64, "Instructions de la démonstration du contrôle conteneur OLE"
End Sub

Sub NewOleForm()
    Dim Newform As New ChildForm
    Newform.Show
    ' Affiche uniquement la boîte de dialogue Insertion de l'objet si l'utilisateur clique sur
    ' Nouveau dans le menu Fichier.
    If MDINew Then
        ParentForm.ActiveForm.OLE1.InsertObjDlg
    End If
    
    UpdateCaption
End Sub

Sub OpenObject()
    MDINew = False
    NewOleForm
    OpenSave ("Open")
    If ParentForm.ActiveForm.OLE1.OLEType = vbOLENone Then
        Unload ParentForm.ActiveForm
    End If
End Sub

' L'ouverture d'un nouveau fichier ne marche qu'avec un fichier contenant un objet OLE Automation valide.
' Pour faire marcher cette application, suivez cette procédure :
' 1) Cliquez sur Nouveau dans le menu Fichier, spécifiez ensuite un objet.
' 2) Modifiez l'objet, puis cliquez sur Enregistrer sous du menu Fichier.
' 3) Cliquez sur la zone du contrôle menu de l'objet pour le fermer.
' 4) Cliquez sur Ouvrir dans le menu Fichier, sélectionnez le fichier que vous venez d'enregistrer.
Sub OpenSave(Action As String)
    Dim Filenum
    Filenum = FreeFile
    ' Définit les options et les filtres du contrôle CommonDialog.
    ParentForm.ActiveForm.CommonDialog1.Filter = _
      "Objets à insérer (*.OLE)|*.OLE|Tous les fichiers (*.*)|*.*"
    ParentForm.ActiveForm.CommonDialog1.FilterIndex = 1
  
    ParentForm.ActiveForm.OLE1.FileNumber = Filenum

On Error Resume Next

    Select Case Action
        Case "Save"
            ' Affiche la boîte de dialogue Enregistrer sous.
            ParentForm.ActiveForm.CommonDialog1.ShowSave
            If Err Then
                ' Bouton Annuler a été sélectionné.
                If Err = 32755 Then
                    Exit Sub
                Else
                    MsgBox "Une erreur non gérée s'est produite avec la boîte de dialogue Enregistrer sous."
                End If
            End If
            ' Ouvre et enregistre le fichier.
            Open ParentForm.ActiveForm.CommonDialog1.filename For Binary As Filenum
            If Err Then
                MsgBox (Error)
                    Exit Sub
            End If
                ParentForm.ActiveForm.OLE1.SaveToFile Filenum
            If Err Then MsgBox (Error)

        Case "Open"
            ' Affiche la boîte de dialogue Ouvrir.
            ParentForm.ActiveForm.CommonDialog1.ShowOpen
            If Err Then
                ' Bouton Annuler a été sélectionné.
                If Err = 32755 Then
                    Exit Sub
                Else
                    MsgBox "Une erreur non gérée s'est produite avec la boîte de dialogue Ouvrir."
                End If
            End If
            ' Ouvre le fichier.
            Open ParentForm.ActiveForm.CommonDialog1.filename For Binary As Filenum
            If Err Then
                Exit Sub
            End If
            ' Affiche le pointeur de souris sous forme de sablier.
            Screen.MousePointer = 11
            ParentForm.ActiveForm.OLE1.ReadFromFile Filenum
            If (Err) Then
                If Err = 30015 Then
                    MsgBox "Objet OLE invalide."
                Else
                    MsgBox Error$
                End If
                Unload ParentForm.ActiveForm
            End If
            ' Si aucune erreur ne se produit lors de l'ouverture, active l'objet.
            ParentForm.ActiveForm.OLE1.DoVerb -1

        ' Définit les propriétés de la feuille maintenant que le contrôle conteneur OLE contient un objet.
        UpdateCaption
        ' Rétablit le pointeur de souris.
        Screen.MousePointer = 0
    End Select
  
    Close Filenum
End Sub

Sub UpdateCaption()
    ' Définit les propriétés de la feuille maintenant que le contrôle conteneur OLE contient un objet.
    ParentForm.ActiveForm.Caption = "Objet" + ParentForm.ActiveForm.OLE1.Class 
    On Error Resume Next
End Sub

