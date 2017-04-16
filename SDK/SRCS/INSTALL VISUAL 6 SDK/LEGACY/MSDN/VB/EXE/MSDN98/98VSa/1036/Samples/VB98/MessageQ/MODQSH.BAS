Attribute VB_Name = "modQueueSupportHelper"
Option Explicit
' --------------------------------------------------
'  Contient les fonctions HELPER utiles pour l'accès
'  aux files de messages.  Ces fonctions ne sont PAS
'  conçues pour être appelées à partir d'applications
'  (elles ne font rien).  Elles sont conçues pour
'  supporter les fonctions principales
'
'  [10/11/97, IvoSa] Créée
' --------------------------------------------------

Const LEN_GUID_WITH_BRACKETS = 38
Const LEN_GUID_WITHOUT_BRACKETS = LEN_GUID_WITH_BRACKETS - 2

' ------------------------------------------------------------------
' Appelée lorsque le GUID de file correct est introuvable dans le
' Registre système (absent ou incorrect)
'  [in] strQueueName : Nom de la file à parcourir
'  [retval]          : GUID de la file QUEUE
'
'  [10/11/97, IvoSa] Créé
' ------------------------------------------------------------------
Function LookupGUIDAndPersistToRegisty(ByVal strQueueName As String) As String
Dim strQueueGUID As String
        
    ' Rechercher la file
    strQueueGUID = getGUIDOfMessageQueue(strQueueName)

    ' Contrôle de validité sur le GUID retourné
    If (Not (IsGUID(strQueueGUID))) Then
        Err.Raise qeBOGUS_GUID, "LookupGUIDAndPersistToRegisty", "GUID ID MSMQ non valide: " & qeBOGUS_GUID
    End If

    ' Inscrire le GUID avec le nom de la file
    SaveSetting regAPPLICATION_NAME, strQueueName, regKEY_NAME, strQueueGUID
    
    ' GUID de la file...
    LookupGUIDAndPersistToRegisty = strQueueGUID
End Function

' --------------------------------------------------
' Vérifie la validité d'une chaîne 'guid'
'  [in] strQueueGUID  : Nom de la file à ouvrir
'
'  [10/11/97, IvoSa] Créé
' --------------------------------------------------
Function IsGUID(ByVal strQueueGUID As String) As Boolean
    strQueueGUID = Trim(strQueueGUID)
    
    Dim lngStrLen As Long
    lngStrLen = Len(strQueueGUID)
    
    Select Case lngStrLen
    Case LEN_GUID_WITH_BRACKETS
    Case LEN_GUID_WITHOUT_BRACKETS
    Case Else
        IsGUID = False: Exit Function
    End Select

    ' On peut souhaiter des tests complémentaires
    IsGUID = True
End Function


' --------------------------------------------------
' Affiche un avertissement à l'utilisateur de l'application
'  [10/11/97, IvoSa] Créé
' --------------------------------------------------
Sub Queue_Warning(strWarning As String)
#If Not SUPPRESS_WARNINGS Then
    MsgBox strWarning, , "Avertissement sur accès à la file"
#End If
End Sub

' -----------------------------------------------------------
' Vérifie qu'un GUID ne contient pas de {}'
'  [in] strGuid : GUID avec ou sans {}'s
'
'  [11/12/97, IvoSa] Créé
' -----------------------------------------------------------
Function getGUIDWithoutBrackets(strGuid As String) As String
    Dim lngStrLen As Long
    lngStrLen = Len(strGuid)
    
    Select Case lngStrLen
    Case LEN_GUID_WITH_BRACKETS
        getGUIDWithoutBrackets = Mid(strGuid, 2, LEN_GUID_WITHOUT_BRACKETS)
    Case LEN_GUID_WITHOUT_BRACKETS
        getGUIDWithoutBrackets = strGuid
    Case Else
        Err.Raise qeBOGUS_GUID, "getGUIDWithoutBrackets", strGuid & " GUID incorrect, longueur 0."
    End Select
End Function

' -----------------------------------------------------------
' Vérifie qu'un GUID ne contient pas de {}'
'  [in] strGuid : GUID w/ or w/o {}'s
'
'  [11/12/97, IvoSa] Créée
' -----------------------------------------------------------
Function getGUIDWithBrackets(strGuid As String) As String
    Dim lngStrLen As Long
    lngStrLen = Len(strGuid)
    
    Select Case lngStrLen
    Case LEN_GUID_WITH_BRACKETS
        getGUIDWithBrackets = strGuid
    Case LEN_GUID_WITHOUT_BRACKETS
        getGUIDWithBrackets = "{" & strGuid & "}"
    Case Else
        Err.Raise qeBOGUS_GUID, "getGUIDWithBrackets", strGuid & " GUID incorrect, longueur 0."
    End Select
End Function


' --------------------------------------------------
' Informations de file nécessaires pour créer une file
'
'  [in] strPath  : chemin de la file
'  [in] strLabel  : étiquette de la file
'  [retval] QueueInfo nécessaire pour créer l'objet
'
'  NOTES: L'objet de cette fonction consiste à
'         combiner la création/initialisation de cet
'         objet en une unité atomique.

'
'  [11/12/97, IvoSa] Créée
' --------------------------------------------------
Function getQueueInfoForCreation(strPath As String, strLabel As String) As MSMQQueueInfo
 Dim objQInfo As MSMQQueueInfo

    ' A FAIRE : ajouter du code pour vérifier si une file de ce nom existe déjà.
    
    Set objQInfo = New MSMQQueueInfo
    objQInfo.PathName = strPath
    objQInfo.Label = strLabel
    
    Set getQueueInfoForCreation = objQInfo
End Function


' --------------------------------------------------
' Informations de file nécessaires pour ouvrir une file par nom de GUID
'
'  [in] strGUIDForQueue : GUID de la file
'  [retval] QueueInfo nécessaire pour créer l'objet
'
'  NOTES: L'objet de cette fonction consiste à
'         combiner la création/initialisation
'         de cet objet en une unité atomique.
'
'  [11/12/97, IvoSa] Créée
' --------------------------------------------------
Function getQueueInfoForLogon(strGUIDForQueue As String) As MSMQQueueInfo
    Dim objQI As MSMQQueueInfo
    Set objQI = New MSMQQueueInfo
    objQI.FormatName = "PUBLIC=" & getGUIDWithoutBrackets(strGUIDForQueue)
    Set getQueueInfoForLogon = objQI
End Function

' --------------------------------------------------
' Informations de file nécessaires pour supprimer un file par étiquette
'
'  [in] strLabelForQueue  : étiquette de la file
'  [retval] QueueInfo nécessaire pour supprimer l'objet
'
'  NOTES: L'objet de cette fonction consiste à
'         combiner la création/initialisation
'         de cet objet en une unité atomique.
'
'  [11/12/97, IvoSa] Créée
' --------------------------------------------------
Function getQueueInfoForDeletion(strLabelForQueue As String) As MSMQQueueInfo
    Dim objQuery As MSMQQuery
    Set objQuery = New MSMQQuery
    
    Dim objQI As MSMQQueueInfo
    Dim objQIs As MSMQQueueInfos
    Set objQIs = objQuery.LookupQueue(Label:=strLabelForQueue)
    
    objQIs.Reset
    
    ' A FAIRE : on peut vérifier s'il y en a plusieurs
    Set getQueueInfoForDeletion = objQIs.Next
End Function


' --------------------------------------------------
' Retourne le GUID qui identifie une file de messages
'  [in] strQueueName : Nom de la file à ouvrir
'
'  SUPPOSITION: Nous sommes branchés sur le réseau
'  lorsque ceci est appelé (sinon on risque le blocage)
'
'  [10/11/97, IvoSa] Créée
' --------------------------------------------------
Function getGUIDOfMessageQueue(ByVal strQueueName As String) As String
Dim objQuery As MSMQQuery
Dim objQInfos As MSMQQueueInfos
Dim objQInfo As MSMQQueueInfo
Dim objQinfoTemp As MSMQQueueInfo
    
    ' Nouvelle requête pour rechercher les files de messages
    Set objQuery = New MSMQQuery
    
    ' Exécute la requête, retourne un ensemble de requêtes
    Set objQInfos = objQuery.LookupQueue(Label:=strQueueName)
    
    ' Retourne au début (est-ce nécessaire ?)
    objQInfos.Reset

    ' Parcourt les files de messages et recherche les notres
    Dim lngCount As Long
    Set objQinfoTemp = objQInfos.Next
    While Not (objQinfoTemp Is Nothing)
        Set objQInfo = objQinfoTemp
        lngCount = lngCount + 1
        
        ' Avance jusqu'à l'élément suivant
        Set objQinfoTemp = objQInfos.Next
    Wend
    
    ' Une seule file permise avec l'ID spécifié
    If (lngCount > 1) Then
        Queue_Warning "La file compte plus d'un (" & CStr(lngCount) & ").  Plusieurs files ont la même étiquette, donc: 1) la requête de file doit être plus spécifique ou 2) toutes les files portant cette étiquette sauf une doivent être supprimées.  Utilisation par défaut de la première file trouvée."
    End If
    
    getGUIDOfMessageQueue = objQInfo.QueueGuid
End Function


