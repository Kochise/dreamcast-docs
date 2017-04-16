Attribute VB_Name = "Errors"
Option Explicit
Const mnErrDeviceUnavailable = 68
Const mnErrDiskNotReady = 71
Const mnErrDeviceIO = 57
Const mnErrDiskFull = 61
Const mnErrBadFileName = 64
Const mnErrBadFileNameOrNumber = 52
Const mnErrPathDoesNotExist = 76
Const mnErrBadFileMode = 54
Const mnErrFileAlreadyOpen = 55
Const mnErrInputPastEndOfFile = 62
Function FileErrors() As Integer
    Dim intMsgType As Integer
    Dim strMsg As String
    Dim intResponse As Integer
    ' Valeur retournée     Signification
    ' 0                    Resume
    ' 1                    Resume Next
    ' 2                    Erreur irrécupérable
    ' 3                    Erreur non reconnue
    intMsgType = vbExclamation
    Select Case Err.Number
        Case mnErrDeviceUnavailable             ' Erreur 68
            strMsg = "Périphérique non disponible."
            intMsgType = vbExclamation + vbOKCancel
        Case mnErrDiskNotReady                  ' Erreur 71
            strMsg = "Insérer une disquette dans le lecteur."
            intMsgType = vbExclamation + vbOKCancel
        Case mnErrDeviceIO                      ' Erreur 57
            strMsg = "Erreur interne."
            intMsgType = vbExclamation + vbOKOnly
        Case mnErrDiskFull                      ' Erreur 61
            strMsg = "Disque plein. Continuer?"
            intMsgType = vbExclamation + vbAbortRetryIgnore
        Case mnErrBadFileName, mnErrBadFileNameOrNumber ' Erreurs 64 et 52
            strMsg = "Nom de fichier incorrect."
            intMsgType = vbExclamation + vbOKCancel
        Case mnErrPathDoesNotExist                ' Erreur 76
            strMsg = "Chemin d'accès introuvable."
            intMsgType = vbExclamation + vbOKCancel
        Case mnErrBadFileMode                     ' Erreur 54
            strMsg = "Mode d'accès au fichier incorrect."
        Case mnErrFileAlreadyOpen             ' Erreur 55
            strMsg = "Fichier déjà ouvert."
            intMsgType = vbExclamation + vbOKOnly
        Case mnErrInputPastEndOfFile              ' Erreur 62
            strMsg = "Ce fichier a un marqueur de fin non standard,"
            strMsg = strMsg & " ou une tentative de lecture au-delà du marqueur"
            strMsg = strMsg & " de fin de fichier s'est produite."
            intMsgType = vbExclamation + vbAbortRetryIgnore
        Case Else
            FileErrors = 3
            Exit Function
    End Select
    intResponse = MsgBox(strMsg, intMsgType, "Erreur disque")
    Select Case intResponse
        Case 1, 4       ' Boutons OK, Réessayer.
            FileErrors = 0
        Case 2, 5       ' Boutons Annuler, Ignorer.
            FileErrors = 1
        Case 3          ' Bouton Abandonner.
            FileErrors = 2
        Case Else
            FileErrors = 3
    End Select
End Function

