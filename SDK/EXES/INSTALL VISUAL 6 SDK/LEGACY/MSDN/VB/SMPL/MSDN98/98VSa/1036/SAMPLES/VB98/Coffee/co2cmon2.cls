VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CoffeeMonitor2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
' > Pour plus d'informations sur cet exemple d'application,
'   recherchez "Coffee" dans l'aide en ligne.
' > Le fichier AboutCof.Txt, présent dans le dossier
'   Documents associés de CoffWat2.vbp, contient également
'   des informations sur cet exemple.

' Classe CoffeeMonitor2
' --------------------
' Tout comme l'objet CoffeeMonitor, l'objet
'   CoffeeMonitor2 surveille le fonctionnement d'une
'   cafetière "high tech" connectée à une interface
'   série imaginaire, en utilisant une minuterie qui
'   détermine la fréquence avec laquelle il faut
'   vérifier le café.
'
' Au lieu de déclencher un événement lorsque le café
'   est prêt, l'objet CoffeeMonitor2 invoque une
'   méthode de rappel qui doit être implémentée par
'   une des classes du client. La méthode de rappel
'   est déclarée dans la classe ICallBack.
'
' (Bien entendu, ce type de cafetière "high tech"
'   n'ayant pas encore été inventé, cet exemple
'   d'application invoque donc simplement une méthode
'   de rappel toutes les dix secondes.)
'
' IMPORTANT: Afin de simplifier un exemple somme toute
'   assez complexe, la classe ICallBack a été ajoutée
'   à ce projet. Ceci ne marchera PAS sur les vrais
'   systèmes, qui utilisent de nombreuses versions. Si
'   une deuxième version de Coffee2 est réalisée, le
'   numéro de version ID de l'interface sera incrémenté,
'   et les anciens clients ne pourront PAS fonctionner
'   avec la nouvelle version de Coffee2. Les interfaces
'   standard telles que ICallBack devraient être créées
'   par elles-mêmes dans des petites DLL qui pourront
'   être référencées à la fois par le client et par le
'   composant. Une interface utilisée par des applications
'   qui sont terminées ne devrait jamais changer. Pour
'   plus d'informations, recherchez "polymorphisme"
'   dans les Manuels en ligne.
'
' Note: la valeur PublicNotCreatable a été affectée à la
'   propriété Instancing de la classe CoffeeMonitor2.
'   Cela signifie que les clients ne peuvent pas créer
'   un objet CoffeeMonitor2; ils ne peuvent qu'obtenir
'   une référence à la classe partagée CoffeeMonitor2
'   en créant un objet Connector2 et en accédant à sa
'   propriété CoffeeMonitor2.
'
' Tout comme la classe CoffeeMonitor, la classe
'   CoffeeMonitor2 corrige le bogue décrit dans la section
'   "Utilisation du CoffeeMonitor partagé" du chapitre
'   "Création d'un composant EXE ActiveX", des Manuels
'   en ligne, au moyen duquel des objets CoffeeMonitor
'   multiples peuvent parfois être créés.

' =======================================================
'  AVERTISSEMENT!  Les minuteries en code seul sont
'   implicitement dangereuses dans l'environnement de
'   développement Visual Basic car le système effectue
'   sans relâche des appels dans votre code jusqu'à ce
'   que la minuterie soit arrêtée par un appel d'API.
'   Il est plus sûr d'utiliser des contrôles Timer pendant
'   une grande partie de la procédure de développement,
'   et de repasser à des minuteries de rappel tout à la fin.
' =======================================================

Const ICN_ARRAYINCREMENT = 10

' maicnClients stocke des références à tous les clients
' ------------   qui ont requis des rappels. Vous remarquerez
'   que cela diffère de l'utilisation des événements dans
'   l'objet CoffeeMonitor: un événement peut être reçu par
'   plusieurs clients, alors que les rappels doivent être
'   faits un par un. Un tableau est utilisé, à la place
'   d'une Collection, car les objets Collection conservent
'   des objets dans des Variants, ce qui entraîne des liaisons
'   tardives.
Private maicnClients() As ICoffeeNotify
Private mlngMaxClients As Long

' mwXTimer maintient une référence à la minuterie en code
' -------   seul qui indique à l'objet CoffeeMonitor2
'   à quel moment il faut surveiller le café. La
'   variable étant déclarée en tant que WithEvents,
'   l'objet CoffeeMonitor2 reçoit les événements Tick
'   de l'objet XTimer (reportez-vous à Sub mwXTimer_Tick,
'   plus bas). Le code pour l'objet XTimer se trouve
'   dans le fichier XTimers.vbp.
Private WithEvents mwXTimer As XTimer
Attribute mwXTimer.VB_VarHelpID = -1

Private Sub Class_Initialize()
    ' Alloue de l'espace dans le tableau des objets du client.
    mlngMaxClients = ICN_ARRAYINCREMENT
    ReDim maicnClients(1 To mlngMaxClients)
    '
    ' Crée l'objet XTimer. Lorsque l'affectation est faite,
    '   Visual Basic connecte l'événement Tick de l'objet
    '   XTimer à la procédure d'événement mwXTimer_Tick
    '   (Voir ci-dessous).
    Set mwXTimer = New XTimer
    '
    ' La minuterie est définie pour émettre un événement
    '   Tick toutes les dix secondes (10.000 millisecondes).
    mwXTimer.Interval = 10000
    mwXTimer.Enabled = True
End Sub

Private Sub Class_Terminate()
    Dim intCt As Integer
    
    ' Il est important de désactiver l'objet XTimer
    '   avant de le libérer. Comme cela est décrit
    '   dans le fichier XTimers.vbp, l'abandon de
    '   l'exécution d'un objet XTimer provoque
    '   essentiellement une perte de la minuterie du
    '   système, jusqu'à ce que le fichier XTimers.DLL
    '   ne soit déchargé.
    mwXTimer.Enabled = False
    Set mwXTimer = Nothing
    '
    ' Libère tous les clients restants du rappel,
    '   au cas où ils auraient libéré CoffeeMonitor2
    '   sans effectuer d'abord de demande de fin des
    '   notifications.
    For intCt = 1 To mlngMaxClients
        Set maicnClients(intCt) = Nothing
    Next
    '
    Debug.Print "CoffeeMonitor2 (rappels) s'est terminé à " & Now
End Sub

' La méthode TellMeReady est appelé par un client voulant recevoir
' -----------   un rappel lorsque le café est prêt. Le
'   client doit implémenter l'interface ICoffeeNotify,
'   définie dans la classe ICoffeeNotify.
'
Public Sub TellMeReady(ByVal icn As ICoffeeNotify)
    Dim lngCt As Long
    
    ' Cherche un emplacement dans le tableau des interfaces.
    For lngCt = 1 To mlngMaxClients
        If maicnClients(lngCt) Is Nothing Then Exit For
    Next
    '
    ' S'il n'y a pas d'emplacements libres, redimensionne
    '   le tableau.
    If lngCt > mlngMaxClients Then
        mlngMaxClients = mlngMaxClients + ICN_ARRAYINCREMENT
        ReDim Preserve maicnClients(1 To mlngMaxClients)
    End If
    '
    Set maicnClients(lngCt) = icn
    '
    ' Donne à l'objet l'index de son entrée, qui constituent
    '   une clé pour un verrouillage rapide lorsque la
    '   déconnexion est demandée.
    icn.NotifyID = lngCt
End Sub

' La méthode CeaseCallBacks supprime le client de la liste des objets
' --------------   recevant des notifications de rappel, en
'   utilisant la clé affectée à l'objet lors de la demande
'   des notifications.
'
Public Sub CeaseCallBacks(ByVal icn As ICoffeeNotify)
    Set maicnClients(icn.NotifyID) = Nothing
End Sub

' mwXTimer_Tick est la procédure d'événement que CoffeeMonitor2
' -------------   utilise pour recevoir les événements Tick
'   de l'objet XTimer. Le nom d'une procédure d'événement
'   associée avec une variable WithEvents prend toujours le
'   nom de la variable comme préfixe.
'
Private Sub mwXTimer_Tick()
    Dim lngCt As Long
    
    ' (Code de test du port série omis.)
    '
    On Error Resume Next
    '
    ' La méthode de rappel doit être appelée pour chaque
    '   objet ayant demandé une notification.
    For lngCt = 1 To mlngMaxClients
        If Not maicnClients(lngCt) Is Nothing Then
            maicnClients(lngCt).CoffeeReady
            If Err.Number <> 0 Then
                ' L'erreur &H80010005 est ignorée; elle peut
                '   avoir été causée par l'objet du client qui
                '   n'a pas répondu temporairement.
                If Err.Number <> &H80010005 Then
                    ' Si une application client s'est terminée
                    '   sans avoir mis fin aux notifications,
                    '   supprimez-la de la liste.
                    Set maicnClients(lngCt) = Nothing
                End If
                '
                ' Si l'instruction On Error Resume Next est
                '   utilisée, le numéro d'erreur doit être
                '   effacé après chaque erreur.
                Err.Number = 0
            End If
        End If
    Next
End Sub

