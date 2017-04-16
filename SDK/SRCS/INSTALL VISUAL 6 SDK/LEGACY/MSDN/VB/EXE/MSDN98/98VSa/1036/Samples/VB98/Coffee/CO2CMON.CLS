VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CoffeeMonitor"
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

' La classe CoffeeMonitor surveille le fonctionnement
'   d'une cafetière "high tech" connectée à une interface
'   série imaginaire, en utilisant une minuterie de
'   rappel (objet XTimer) qui détermine la fréquence
'   avec laquelle il faut vérifier le café. Lorsque
'   le café est prêt, l'objet CoffeeMonitor déclenche
'   un événement pour en informer les clients. Bien
'   entendu, ce type de cafetière "high tech" n'ayant
'   pas encore été inventé, cet exemple
'   d'application déclenche donc simplement un évennement
'   CoffeeReady tous les dix secondes.
'
' (Reportez-vous également à la classe CoffeeMonitor2
'   qui illustre une notification en utilisant une
'   méthode de rappel au lieu d'un événement.)
'
' Note: la valeur PublicNotCreatable a été affectée à la
'   propriété Instancing de la classe CoffeeMonitor.
'   Cela signifie que les clients ne peuvent pas créer
'   des objets CoffeeMonitor; ils ne peuvent qu'obtenir
'   une référence à l'objet partagée CoffeeMonitor
'   en créant un objet Connector et en accédant à sa
'   propriété CoffeeMonitor.
'
' En utilisant une minuterie en code seul, cette version
'   de CoffeeMonitor corrige le bogue décrit dans la section
'   "Utilisation du CoffeeMonitor partagé" du chapitre
'   "Création d'un composant EXE ActiveX", des Manuels
'   en ligne, au moyen duquel des objets CoffeeMonitor
'   multiples peuvent parfois être créés.
'
' Ce bogue était provoqué par le code 'compte d'utilisation'
'   que l'objet Connector utilisait pour libérer la
'   référence globale à l'objet partagé CoffeeMonitor.
'   Le compte d'utilisation était requis parce que les
'   procédures pas à pas des Manuels en ligne utilisaient
'   une feuille cachée pour maintenir un contrôle Timer;
'   les feuilles cachées empêchent le déchargement des
'   composants (comme le décrit la section "Démarrage et
'   arrêt d'un composant" des Manuels en ligne), ainsi que
'   la libération de la mémoire globale, et l'affectation
'   de la valeur Nothing à la variable gCoffeeMonitor.
'
' Contrairement à ce que fait la feuille cachée avec le contrôle
'   Timer, l'objet XTimer n'empêche pas le déchargement du composant
'   Coffee2 lorsque le dernier client libère sa dernière
'   référence. Vous remarquerez, cependant, que la variable
'   globale gCoffeeMonitor maintiendra l'objet CoffeeMonitor
'   en vie jusqu'à ce que tous les objets fournis par Coffee2
'   soient libérés par leurs clients respectifs.

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

' mwTimer maintient une référence à la minuterie en code
' -------   seul qui indique à l'objet CoffeeMonitor
'   à quel moment il faut surveiller le café. La
'   variable étant déclarée en tant que WithEvents,
'   l'objet CoffeeMonitor reçoit les événements Tick
'   de l'objet XTimer (reportez-vous à Sub mwXTimer_Tick,
'   plus bas). Le code pour l'objet XTimer se trouve
'   dans le fichier XTimers.vbp.
Private WithEvents mwXTimer As XTimer
Attribute mwXTimer.VB_VarHelpID = -1

' CoffeeReady est l'événement que CoffeeMonitor déclenche
' -----------   pour ses clients lorsque le café est prêt.
'   Le mot clé Public est omis de la déclaration de
'   l'événement car les événements sont toujours publics.
Event CoffeeReady()
    
Private Sub Class_Initialize()
    ' La première chose que fait un objet CoffeeMonitor est de créer
    '   l'objet XTimer. Lorsque l'affectation est faite,
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
' Il est important de désactiver l'objet XTimer
    '   avant de le libérer. Comme cela est décrit
    '   dans le fichier XTimers.vbp, l'abandon de
    '   l'exécution d'un objet XTimer provoque
    '   essentiellement une perte de la minuterie du
    '   système, jusqu'à ce que XTimers.DLL ne soit
    '   déchargé.
    mwXTimer.Enabled = False
    Set mwXTimer = Nothing
    '
    Debug.Print "CoffeeMonitor (événements) s'est terminé à " & Now
End Sub

' mwXTimer_Tick est la procédure d'événement que CoffeeMonitor2
' -------------   utilise pour recevoir les événements Tick
'   de l'objet XTimer. Le nom d'une procédure d'événement
'   associée avec une variable WithEvents prend toujours le
'   nom de la variable comme préfixe.
'
Private Sub mwXTimer_Tick()
    ' (Code de test du port série omis.)
'
    ' Informe le client.
    RaiseEvent CoffeeReady
End Sub
