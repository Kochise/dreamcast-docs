Attribute VB_Name = "modQueueSupport"
Option Explicit
' --------------------------------------------------
'  Contient des fonctions utiles pour les files de
'  messages.  Ces fonctions sont prévues pour être
'  appelées à partir des applications pour créer,
'  détruire, gérer et accéder les files.
'
'  [11/10/97, IvoSa] Création
' --------------------------------------------------

' Informations du Registre pour gérer les ID de file, etc.
Global Const regAPPLICATION_NAME = "MessageQueueAdministration"
Global Const regKEY_NAME = "QueueGUID"
Global Const regNOT_FOUND = "<Not Found>"

' Heure
Global Const ONE_SECOND = 1000 '1000ms
Global Const FIVE_SECONDS = ONE_SECOND * 5


' Heures générées éventuellement par ce module
Public Enum QueueErrors
    qeNO_QUEUE = 30000
    qeBOGUS_GUID = 30001
End Enum

' --------------------------------------------------
' Ouvre une file de messages
'  [in] strQueueName : Nom de la file à ouvrir
'  [in] qaAccessMode : Mode d'accès (lecture/écriture)
'  [in] boolPromotUser : Demande à l'utilisateur si besoin d'autres informations ?
'  [out] objQueueInfo : Informations de file (utiles pour l'appelant)
'  [retval] : Objet file
'
' Cette fonction générale permet d'ouvrir une file
' de messages pour l'utilisateur, que l'utilisateur (ou la file)
' soit ou ne soit pas actuellement connecté au réseau.
' Cette fonction doit être appelée au moins une fois
' avec une connexion réseau sinon elle échouera.
' (Lors du premier appel de cette fonction sur une
' machine/utilisateur notera le GUID des files
' de messages pour future référence)
'
' [11/10/97, IvoSa] Création
' --------------------------------------------------
Public Function openMessageQueue(ByVal strQueueName As String, ByVal qaAccessMode As MQACCESS, Optional ByVal boolPromotUser As Boolean = True, Optional objQueueInfo As MSMQQueueInfo) As MSMQQueue
    Dim strQueueGUID As String
    
    ' -------------------------------------------------------------------
    ' Détermine le GUID de la file de message
    ' -------------------------------------------------------------------
    
    ' Lit le GUID qui identifie de façon unique la file
    strQueueGUID = GetSetting(regAPPLICATION_NAME, strQueueName, regKEY_NAME, regNOT_FOUND)
    
    ' S'il n'y a pas de valeur spécifiée pour la file
    If (strQueueGUID = regNOT_FOUND) Then
        
        ' Essaye de demander à l'utilisateur
        If (boolPromotUser = True) Then
            Dim lngYesNo As VbMsgBoxResult
            lngYesNo = MsgBox("Il n'y a pas de file inscrite localement pour '" & strQueueName & ". Voulez-vous rechercher cette file sur le réseau ('Non' pour abandonner)?", vbYesNo)
            
            ' S'il répond non, abandonner
            If (lngYesNo = vbNo) Then
                Err.Raise qeNO_QUEUE, "OpenMessageQueue", "Il n'y a pas de file inscrite pour cet utilisateur/machine pour " & strQueueName
            End If
        End If
        
        strQueueGUID = LookupGUIDAndPersistToRegisty(strQueueName)
    End If
    
    ' -------------------------------------------------------------------
    ' Essaye d'ouvrir la file de messages...
    ' -------------------------------------------------------------------
    Dim lngError As Long
    Dim strError As Long
    On Error Resume Next
        Set objQueueInfo = getQueueInfoForLogon(strQueueGUID)
        Set openMessageQueue = objQueueInfo.Open(qaAccessMode, MQ_DENY_NONE)
        lngError = Err.Number
        strError = Err.Description
    On Error GoTo 0

    ' -------------------------------------------------
    ' Gère les erreurs éventuelles...
    ' -------------------------------------------------
    Select Case lngError
    Case 0  ' Pas d'erreur
        Exit Function ' C'est fini
    
    Case MQ_ERROR_QUEUE_NOT_FOUND ' La file est mal inscrite (ou plus probablement détruite et recréée)
        
        ' Essaye de demander à l'utilisateur
        If (boolPromotUser = True) Then
            lngYesNo = MsgBox("Les informations locales pour '" & strQueueName & " sont incorrects. Voulez-vous rechercher cette file sur le réseau ('Non' pour abandonner)?", vbYesNo)
            
            ' S'il répond non, abandonner
            If (lngYesNo = vbNo) Then
                Err.Raise qeNO_QUEUE, "OpenMessageQueue", "Il n'y a pas de file inscrite pour cet utilisateur/machine pour " & strQueueName
            End If
        End If
        
        ' --------------------------------------------------
        ' Essaye d'ouvrir la file
        ' --------------------------------------------------
        ' Si une erreur se produit de nouveau, remonter-la simplement
        strQueueGUID = LookupGUIDAndPersistToRegisty(strQueueName)
        Set objQueueInfo = getQueueInfoForLogon(strQueueGUID)
        Set openMessageQueue = objQueueInfo.Open(qaAccessMode, MQ_DENY_NONE)
    
    Case Else ' Pas une erreur gérée, la remonter.
        Err.Raise lngError, , strError
    End Select
    
End Function



' --------------------------------------------------
' Create message queue
'  [in] strQueueName     : Nom de la file à ouvrir
'  [in] strQueueLocation : Emplacement de la file ('MACHINE\CHEMIN')
'  [in] boolPromptUser   : Demande à l'utilisateur en cas de problème de création de la file
'  [in] boolWorldReadable: Rend la file visible par tous ou uniquement par son créateur...
'
'  [retval] T/F : était une 'nouvelle' file créée
'
'  Cette fonction générale permet de créer une nouvelle file de messages
'
'  [11/10/97, IvoSa] Création
'  [12/6/97, IvoSa]  File rendue 'Lisible par tous'
' --------------------------------------------------
Public Function createMessageQueue(ByVal strQueueName As String, ByVal strQueueLocation As String, Optional ByVal boolPromptUser As Boolean = True, Optional ByVal boolWorldReadable As Boolean = True) As Boolean
Dim objQInfo As MSMQQueueInfo
Dim boolNewQueueCreated As Boolean
    boolNewQueueCreated = True ' commence à vrai
    
    ' A FAIRE : ajouter du code pour vérifier si une file de ce nom existe déjà.
    
    ' Tentative de création de la file
    Dim lngError As Long
    Dim strError As Long
    On Error Resume Next
        getQueueInfoForCreation(strQueueLocation, strQueueName).Create
        lngError = Err.Number
        strError = Err.Description
    On Error GoTo 0

    Dim lngYesNo As Long
    ' -------------------------------------------------
    ' Gère les erreurs éventuelles...
    ' -------------------------------------------------
    Select Case lngError
    Case 0  ' Pas d'erreur
        GoTo exit_function ' [11/19,97, IvoSa] C'est fini
    
    Case MQ_ERROR_QUEUE_EXISTS 'La file est mal inscrite (ou plus probablement détruite et recréée)
                
        ' Essaye de demander à l'utilisateur
        If (boolPromptUser = True) Then
            lngYesNo = MsgBox("La file '" & strQueueName & "' existe.  Voulez-vous la créer et en créer une nouvelle? ", vbYesNo)
            
            ' S'il répond non, abandonner
            If (lngYesNo = vbNo) Then
                ' La file existe et ils sont satisfaits, quitter.
                boolNewQueueCreated = False
                GoTo exit_function
            End If
        Else
            ' Par sécurité, génère une erreur
            Err.Raise MQ_ERROR_QUEUE_EXISTS, "CreateMessageQueue", "La file existe '" & strQueueName & "'"
        End If
        
        ' --------------------------------------------------
        ' Tentative de suppression de la file
        ' --------------------------------------------------
        getQueueInfoForDeletion(strQueueName).Delete
        
        ' --------------------------------------------------
        ' Tentative de création d'une nouvelle file
        ' --------------------------------------------------
        getQueueInfoForCreation(strQueueLocation, strQueueName).Create IsWorldReadable:=boolWorldReadable ' [12/6/97, IvoSa] Accès public aux files...
        
        ' Si une erreur se produit de nouveau, remonter-la simplement
    
    Case Else ' Pas une erreur gérée, la remonter.
        Err.Raise lngError, , strError
    End Select

exit_function:
    createMessageQueue = boolNewQueueCreated
End Function

' --------------------------------------------------
' Supprime une file de messages
'  [in] strQueueName : Nom de la file à ouvrir
'  [in] boolPromotUser : Demande à l'utilisateur si besoin d'autres informations ?
'
'  Cette fonction générale permet de supprimer une file de messages pour l'utilisateur.'
'  [11/12/97, IvoSa] Création
' --------------------------------------------------
Public Sub deleteMessageQueue(ByVal strQueueName As String, Optional ByVal boolPromotUser As Boolean = True)
    Dim strQueueGUID As String
    
    ' -------------------------------------------------------------------
    ' Détermine le GUID de la file de message
    ' -------------------------------------------------------------------
    
    ' Lit le GUID qui identifie de façon unique la file
    strQueueGUID = GetSetting(regAPPLICATION_NAME, strQueueName, regKEY_NAME, regNOT_FOUND)
    
    ' S'il n'y a pas de valeur spécifiée pour la file ?
    If (strQueueGUID = regNOT_FOUND) Then
        
        ' Essaye de demander à l'utilisateur
        If (boolPromotUser = True) Then
            Dim lngYesNo As VbMsgBoxResult
            lngYesNo = MsgBox("Il n'y a pas de file inscrite localement pour '" & strQueueName & ". Voulez-vous rechercher cette file sur le réseau ('Non' pour abandonner)?", vbYesNo)
            
            ' S'il répond non, abandonner
            If (lngYesNo = vbNo) Then
                Err.Raise qeNO_QUEUE, "deleteMessageQueue", "Il n'y a pas de file inscrite pour cet utilisateur/machine pour " & strQueueName
            End If
        End If
        
        strQueueGUID = LookupGUIDAndPersistToRegisty(strQueueName)
    End If
    
    ' -------------------------------------------------------------------
    ' Tentative de suppression de la file de messages...
    ' -------------------------------------------------------------------
    getQueueInfoForLogon(strQueueGUID).Delete
End Sub


' --------------------------------------------------
'  Retourne les étiquettes des messages de la file
'  [in] objQueue     : File de messages
'
'  [11/10/97, IvoSa] Création
' --------------------------------------------------
Public Function getLabelsOfMessagesInQueue(ByVal objQueue As MSMQQueue) As Collection
Dim objMessage As MSMQMessage
Dim colLables As Collection
    
    ' Collection de stockage des étiquettes
    Set colLables = New Collection
    
    ' Atteind le premier élément de la file
    objQueue.Reset
    
    ' Parcourt tous les éléments et ajoute les étiquettes à la collection
    Set objMessage = objQueue.PeekCurrent(, , ONE_SECOND) ' ONE_SECOND nécessaire (le délai par défaut est infini)
    While Not (objMessage Is Nothing)
        colLables.Add objMessage.Label
        Set objMessage = objQueue.PeekNext(, , ONE_SECOND) ' ONE_SECOND nécessaire (le délai par défaut est infini)
    Wend
    
    ' Retourne la collection d'étiquettes de messages
    Set getLabelsOfMessagesInQueue = colLables
End Function


' -----------------------------------------------------
' À partir de l'étiquette de message, on extraie le message
' [in] objQueue     : File de messages
' [in] strLabel     : Étiquette souhaitée
'
' [11/10/97, IvoSa] Création
' -----------------------------------------------------
Public Function getMessageGivenLabelAndQueue(ByVal objQueue As MSMQQueue, ByVal strLabel As String) As MSMQMessage
Dim objMessage As MSMQMessage
    
    objQueue.Reset ' Atteind le premier élément
        
    ' Parcourt tous les éléments et ajoute les étiquettes à la collection
    Set objMessage = objQueue.PeekCurrent(, , ONE_SECOND) ' ONE_SECOND nécessaire (le délai par défaut est infini)
    While Not (objMessage Is Nothing)
        If objMessage.Label = strLabel Then GoTo found_label
        Set objMessage = objQueue.PeekNext(, , ONE_SECOND) ' ONE_SECOND nécessaire (le délai par défaut est infini)
    Wend
        
    Set getMessageGivenLabelAndQueue = Nothing
    Exit Function

found_label:

    Set getMessageGivenLabelAndQueue = objQueue.ReceiveCurrent(receivetimeout:=FIVE_SECONDS)
End Function


' -----------------------------------------------------------
' Envoie un message dans une file
' [in] objQueue
' [in] strMessageLabel
' [in] strMessage
' [in] mdMode:
'       MQMSG_DELIVERY_RECOVERABLE = Enregistre sur le disque (survit au redémarrage)
'       MQMSG_DELIVERY_EXPRESS     = Garde en mémoire (ne survit pas au redémarrage)
' [11/12/97, IvoSa] Création
' -----------------------------------------------------------
Sub sendMessageToQueue(ByVal objQueue As MSMQQueue, strMessageLabel As String, strMessage As String, Optional ByVal mdMode As MQMSGDELIVERY = MQMSG_DELIVERY_RECOVERABLE)
    Dim objMsg As MSMQMessage
    
    Set objMsg = New MSMQMessage
    objMsg.Label = strMessageLabel
    objMsg.Body = strMessage
    objMsg.Delivery = mdMode
    
    objMsg.Send objQueue
End Sub

' -----------------------------------------------------------
' Lit les étiquettes des messages de la file et définit un
'  événement d'attente pour les nouveaux messages
' [in] objQueue : File de messages
' [out] colMsgLabels : Étiquettes des messages de la file
' [11/13/97, IvoSa] Création
' -----------------------------------------------------------
Public Function getEventFireOnNextMessageArrival(ByVal objQueue As MSMQQueue, Optional colMsgLabels As Collection) As MSMQEvent

    ' -------------------------------------------------
    ' Lit les étiquettes des messages existants et
    '  avance le curseur jusqu'à la fin de la file
    ' -------------------------------------------------
    Set colMsgLabels = getLabelsOfMessagesInQueue(objQueue)
    
    Dim objQEvent As MSMQEvent
    Set objQEvent = New MSMQEvent
    
    objQueue.EnableNotification objQEvent, MQMSG_CURRENT
    Set getEventFireOnNextMessageArrival = objQEvent
End Function

