Attribute VB_Name = "Module2"
' Force toutes les erreurs d'exécution à être gérées ici.
Sub DisplayErrorMessageBox()
    Dim Msg As String
    Select Case Err
        Case conMCIErrCannotLoadDriver
            Msg = "Erreur de chargement du gestionnaire de périphérique multimédia."
        Case conMCIErrDeviceOpen
            Msg = "Le périphérique n'est pas ouvert ou il est inconnu."
        Case conMCIErrInvalidDeviceID
            Msg = "Identificateur de périphérique incorrect."
        Case conMCIErrInvalidFile
            Msg = "Nom de fichier incorrect."
        Case conMCIErrUnsupportedFunction
            Msg = "Le périphérique ne gère pas cette action."
        Case Else
            Msg = "Erreur inconnue (" + Str$(Err) + ")."
    End Select

    MsgBox Msg, 48, conMCIAppTIitle
End Sub

' Cette procédure autorise les événements de Windows a être traités.
' Ceci peut être nécessaire pour résoudre les problèmes de
' synchronisation avec les événements de Windows.
' Cette procédure peut être utilisée pour forcer une attente
' dans un traitement.
Sub WaitForEventsToFinish(NbrTimes As Integer)
    Dim i As Integer

    For i = 1 To NbrTimes
        dummy% = DoEvents()
    Next i
End Sub


