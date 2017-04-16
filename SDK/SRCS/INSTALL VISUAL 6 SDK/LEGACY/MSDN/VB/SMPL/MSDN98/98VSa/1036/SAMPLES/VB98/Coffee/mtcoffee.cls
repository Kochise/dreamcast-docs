VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Coffee"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
Private Declare Function timeGetTime Lib "winmm.dll" () As Long

' L'objet Coffee présente, par rapport à ce
'   qu'effectue l'objet CoffeeMonitors, un
'   style différent de notifications asynchrones.
'   Au lieu des notifications périodiques,
'   l'objet Coffee fournit des rapports de
'   progression sur une tâche longue, ainsi
'   qu'un événement d'achèvement.
'
' Le mécanisme utilisé pour ces notifications est
'   de déclencher des événements.
'   Il est également possible d'utiliser les
'   méthodes de rappel (CallBack), et ce avec un certain
'   nombre d'avantages. Ces méthodes permettent
'   en effet à un composant de gérer de manière
'   intelligente les erreurs du client, alors que
'   les événements ne renvoient pas ces erreurs.
'   Cet aspect est abordé à la section
'   "Notifications asynchrones à l'aide de
'   méthodes de rappel" des Manuels en ligne.

' Nombre d'itérations à exécuter dans une tâche
'   de test.
Private mlngIterations As Long

' L'objet XTimer est utilisé pour démarrer la
'   tâche longue en mode asynchrone.
Private WithEvents mwXTimer As XTimer
Attribute mwXTimer.VB_VarHelpID = -1

Event Progress(ByVal PercentDone As Single, _
        ByRef Cancel As Boolean)
Event Complete(ByVal Canceled As Boolean)
        
' La propriété ThreadID renvoie l'ID de la thread
'   du système pour la thread sur
'   laquelle l'objet a été créé.
'
Public Property Get ThreadID() As Long
    ThreadID = App.ThreadID
End Property

' La propriété NumberOnThread renvoie le nombre
' --------------    d'objets Coffee s'exécutant
'   sur cette thread. Il s'agit uniquement de
'   la valeur de la variable globale glngGlobalData
'   que les objets Coffee incrémentent dans
'   leurs événements Initialize et décrémentent
'   dans leurs événements Terminate.
'
' Si le projet MTCoffee a été compilé avec l'option
'   Thread par objet, les objets multiples ne
'   peuvent partager une thread (et l'instance
'   de données globales associée) que si un autre
'   objet Coffee a été créé sur cette thread en
'   appelant GetCoffeeOnSameThread.
'
' Si le projet MTCoffee a été compilé avec l'option
'   Nb max de thread et que le nombre des
'   objets actifs est supérieur au nombre des
'   threads du regroupement, les objets Coffee
'   partageront les threads.
'
Public Property Get NumberOnThread() As Long
    NumberOnThread = glngGlobalData
End Property

' La méthode StartLongTask prépare le terrain pour la tâche
' -------------     de test longue. Celle-ci est
'   en fait démarrée par un objet XTimer en code
'   seul qui est lancé par la méthode StartLongTask.
'
Public Sub StartLongTask(ByVal Iterations As Long)
    ' Ceci est un raccourci pour tester la dépréciation
    '   des appels. Reportez-vous à la méthode CallAnotherCoffee.
    If Iterations = 0 Then Exit Sub
    '
    ' Stocke la taille de la tâche de test.
    mlngIterations = Iterations
    '
    ' Affecte à la minuterie un intervalle
    '   court, puis le lance avant de le
    '   renvoyer.
    mwXTimer.Interval = 55
    mwXTimer.Enabled = True
End Sub

' La méthode GetCoffeeOnSameThread crée un nouvel objet
' ---------------------     Coffee sur la même
'   thread, en simulant les effets du regroupement
'   de threads. Ceci ne peut être fait qu'en
'   interne, comme l'explique la section
'   "Création d'objets dans les composants
'   Visual Basic" des Manuels en ligne.
'
Public Function GetCoffeeOnSameThread() As Coffee
    ' Tous les objets créés en utilisant le mot clé
    '   New seront sur la thread du concepteur, y
    '   compris un nouvel objet Coffee.
    Set GetCoffeeOnSameThread = New Coffee
End Function

' La méthode GetCoffeeOnNewThread crée un nouvel objet
' --------------------     Coffee sur une nouvelle 
'   thread en appelant la fonction CreateObject.
'   La différence existant entre ce type de
'   création et la création interne réalisée
'   par la méthode GetCoffeeOnSameThread est abordée à
'   la section "Création d'objets dans les
'   composants Visual Basic" des Manuels en ligne.
'
' Note: cette technique peut être utilisée pour
'   créer des objets sur différentes threads qui
'   peuvent communiquer entre elles, sans que
'   le client doive passer à un objet une
'   référence à l'autre objet (comme le fait
'   CoffeeWatch). Si vous apppliquez cette technique,
'   la dépréciation des appels de marshaling 
'   entre les threads est presque aussi
'   importante que la dépréciation des appels
'   de marshaling entre les processus.
'
Public Function GetCoffeeOnNewThread() As Coffee
    ' Le crée comme un client externe.
    Set GetCoffeeOnNewThread = CreateObject("MTCoffee.Coffee")
End Function

' La méthode CallAnotherCoffee donne un aperçu de la
' -----------------     dépréciation des appels
'   entre les threads. Il lui passe un objet
'   Coffee sur une autre thread, ou sur la même
'   thread, puis compare les résultats. La
'   méthode fait des appels de test à la méthode
'   StartLongTask; ainsi, il mesure
'   essentiellement la dépréciation de l'appel.
'
Public Function CallAnotherCoffee(ByVal cfe As Coffee) As Double
    Const TRIES = 10000
    Dim timeStart As Long
    Dim timeEnd As Long
    Dim lngTries As Long
    
    timeStart = timeGetTime
    For lngTries = 1 To TRIES
        cfe.StartLongTask 0
    Next
    timeEnd = timeGetTime
    '
    ' Renvoie un nombre de secondes (ss.mmm) par
    '   appel. Le résultat obtenu sera incorrect
    '   si vous exécutez la méthode CallAnotherCoffee 
    '   au moment où la minuterie du système
    '   repasse à zéro.
    CallAnotherCoffee = ((CDbl(timeEnd) - timeStart) / 1000#) / TRIES
End Function

Private Sub Class_Initialize()
    ' Incrémente le nombre global des
    '   objets Coffee, pour cette thread.
    glngGlobalData = glngGlobalData + 1
    '
    ' Crée un objet XTimer.
    Set mwXTimer = New XTimer
End Sub

Private Sub Class_Terminate()
    ' Décrémente le nombre global des
    '   objets Coffee, pour cette thread.
    glngGlobalData = glngGlobalData - 1
    '
    ' Libère l'objet XTimer.
    Set mwXTimer = Nothing
End Sub

Private Sub mwXTimer_Tick()
    ' Arrête la minuterie, pour commencer.
    mwXTimer.Enabled = False
    Call LongTask
End Sub

' La tâche de test.
'
Private Sub LongTask()
    Dim dblDummy As Double
    Dim lngCt As Long
    Dim sngNextMark As Single
    Dim blnCancel As Boolean
    
    ' Pour des petites transactions, n'effectue pas
    '   les rappels pendant l'exécution.
    If mlngIterations < 100000 Then
        sngNextMark = 1!
    Else
        sngNextMark = 0.1!
    End If
        
    ' Il s'agit juste d'une façon de perdre du temps.
    For lngCt = 1 To mlngIterations
        ' Dans le cas d'une vraie application, une
        '   partie du travail serait effectuée ici.
        '   Il peut être intéressant de remplacer
        '   cette activité importante en termes de
        '   traitements par une activité qui fait
        '   peu appel au système, tels que des appels
        '   à une base de données d'une autre machine
        '   ou la lecture d'un gros fichier. Le
        '   débit sur une station de travail à un
        '   seul processeur est beaucoup plus
        '   important lorsque de nombreuses threads
        '   sont bloquées, en attendant l'entrée
        '   d'un fichier ou le résultat d'un appel
        '   à une base de données.
        '
        dblDummy = 3033.14159 * 2081.14159 * 1138.14159
        '
        If CDbl(lngCt) / mlngIterations > sngNextMark Then
            RaiseEvent Progress(sngNextMark, blnCancel)
            If blnCancel Then
                ' Si le client ne veut plus attendre
                '   et annuler la tâche, il déclenche
                '   l'événement Complete avec la valeur
                '   True (annulé).
                RaiseEvent Complete(True)
                Exit Sub
            End If
            sngNextMark = sngNextMark + 0.1!
        End If
    Next
    ' Lorsque la tâche réussit, il déclenche
    '   l'événement Complete avec la valeur False
    '   (non annulé).
    RaiseEvent Complete(False)
End Sub
