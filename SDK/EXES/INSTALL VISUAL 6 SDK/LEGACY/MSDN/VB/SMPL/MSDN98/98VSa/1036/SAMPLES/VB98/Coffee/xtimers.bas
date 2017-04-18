Attribute VB_Name = "XTimerSupport"
Option Explicit
'================================================
' AVERTISSEMENT! Vous ne DEVEZ PAS cliquer sur
'   le bouton Fin pendant le débogage de ce
'   projet! En mode Arrêt, n'effectuez pas de
'   modifications: cela réinitialise le projet!
'
' Ce module est dangereux car il utilise l'API
'   SetTimer et l'opérateur AddressOf pour
'   initialiser une minuterie en code seul. Lorsque
'   ce type de minuterie est défini, le système
'   continue d'appeler la fonction TimerProc
'   MÊME LORSQUE VOUS REPASSEZ EN MODE CRÉATION.
'
' La fonction TimerProc n'étant pas disponible
'   en mode Création, le système provoquera
'   une ERREUR DE PROGRAMME dans Visual Basic.
'
' Lors du débogage de ce module, vérifiez que
'   toutes les minuteries du système ont été
'   arrêtées (en utilisant la fonction KillTimer)
'   avant de repasser en mode Création. La vérification
'   peut être faite en appelant la procédure SCRUB
'   depuis la fenêtre Exécution.
'
' Les minuteries utilisant des fonctions Callback sont
'   implicitement dangereuses. Il est plus sûr d'utiliser 
'   des contrôles Timer pendant une grande partie de la
'   procédure de développement, et de repasser à des fonctions
'   callback tout à la fin.
'==================================================

' Équivaut à augmenter la taille du tableau maxti
'   lorsque plus de minuteries sont nécessaires.
Const MAXTIMERINCREMEMT = 5

Private Type XTIMERINFO
    xt As XTimer
    id As Long
    blnReentered As Boolean
End Type

Declare Function SetTimer Lib "user32" (ByVal hWnd As Long, ByVal nIDEvent As Long, ByVal uElapse As Long, ByVal lpTimerProc As Long) As Long
Declare Function KillTimer Lib "user32" (ByVal hWnd As Long, ByVal nIDEvent As Long) As Long

' maxti est un tableau d'objets XTimer actifs. Il est
'   préférable d'utiliser un tableau de types définis par
'   l'utilisateur au lieu d'un objet Collection. Cela
'   permet d'obtenir une liaison précoce lors du déclenchement
'   de l'événement Tick de l'objet XTimer.
Private maxti() As XTIMERINFO
'
' La variable mintMaxTimers donne la dimension du tableau maxti
'   à un moment donné.
Private mintMaxTimers As Integer

' La fonction BeginTimer est appelée par un objet XTimer
' -------------------   lorsque la propriété Interval de
'   l'objet XTimer a une valeur différente de zéro.
'
' La fonction utilise les appels API requis pour initialiser
'   une minuterie.
'   Si la création de la minuterie réussit, la fonction place
'   une référence à l'objet XTimer dans le tableau maxti. Cette
'   référence sera utilisée pour appeler la méthode qui
'   déclenche l'événement Tick de l'objet XTimer.
'
Public Function BeginTimer(ByVal xt As XTimer, ByVal Interval As Long)
    Dim lngTimerID As Long
    Dim intTimerNumber As Integer
    
    lngTimerID = SetTimer(0, 0, Interval, AddressOf TimerProc)
    ' Si la fonction SetTimer réussit, une valeur différente de zéro
    '   est renvoyée. Si une minuterie ne peut
    '   être obtenue, déclenche une erreur.
    If lngTimerID = 0 Then Err.Raise vbObjectError + 31013, , "Aucune minuterie de disponible"
    
    ' La boucle suivante localise le premier emplacement vide
    '   dans le tableau maxti. Si la limite supérieure
    '   est atteinte, une erreur se produit et le tableau est
    '   agrandi. Si vous compilez cette DLL en code natif,
    '   ne désactivez PAS la vérification des limites!
    For intTimerNumber = 1 To mintMaxTimers
        If maxti(intTimerNumber).id = 0 Then Exit For
    Next
    '
    ' Si aucun espace libre n'est trouvé, augmente
    '   la taille du tableau.
    If intTimerNumber > mintMaxTimers Then
        mintMaxTimers = mintMaxTimers + MAXTIMERINCREMEMT
        ReDim Preserve maxti(1 To mintMaxTimers)
    End If
    '
    ' Enregistre une référence à utiliser lors du déclenchement
    '   de l'événement Tick de l'objet XTimer.
    Set maxti(intTimerNumber).xt = xt
    '
    ' Enregistre l'ID de la minuterie renvoyée par l'API
    '   SetTimer et renvoie la valeur à l'objet XTimer.
    maxti(intTimerNumber).id = lngTimerID
    maxti(intTimerNumber).blnReentered = False
    BeginTimer = lngTimerID
End Function

' TimerProc est la procédure de minuterie que le système
' ---------   appelle si une de vos minuteries s'arrête.
'
' IMPORTANT -- Étant donné que cette procédure doit se
'   trouver dans un module standard, tous vos objets Timer
'   doivent la partager. Cela signifie que la procédure doit
'   identifier quelle minuterie s'est arrêtée. Cela est
'   réalisable en recherchant dans le tableau maxti
'   l'ID de la minuterie (idEvent).
'
' Si cette déclaration de procédure est fausse, une
'   ERREUR DE PROGRAMME se produira! Ceci constitue l'un des
'   dangers qui existent lorsque des API qui nécessitent
'   des fonctions Callback sont utilisées.
'
Public Sub TimerProc(ByVal hWnd As Long, ByVal uMsg As Long, ByVal idEvent As Long, ByVal lngSysTime As Long)
    Dim intCt As Integer

    For intCt = 1 To mintMaxTimers
        If maxti(intCt).id = idEvent Then
            ' Ne déclenche pas d'événement si une ancienne
            '   instance de cet événement est en cours de
            '   traitement.
            If maxti(intCt).blnReentered Then Exit Sub
            ' L'indicateur blnReentered bloque les
            '   instances suivantes de cet événement
            '   jusqu'à ce que l'instance en cours se
            '   termine.
            maxti(intCt).blnReentered = True
            On Error Resume Next
            ' Déclenche l'événement Tick pour l'objet
            '   XTimer approprié.
            maxti(intCt).xt.RaiseTick
            If Err.Number <> 0 Then
                ' Si une erreur se produit, l'objet XTimer
                '   se termine sans que sa minuterie ne s'arrete.
                '   La minuterie orpheline est supprimée, pour éviter
                '   une erreur de protection générale ultérieure.
                KillTimer 0, idEvent
                maxti(intCt).id = 0
                '
                ' Libère la référence à l'objet
                '   XTimer.
                Set maxti(intCt).xt = Nothing
            End If
            '
            ' Autorise cet événement à entrer de nouveau
            '   une procédure TimerProc.
            maxti(intCt).blnReentered = False
            Exit Sub
        End If
    Next
    ' La ligne qui suit est protégée contre les échecs,
    '   au cas où un objet Xtimer serait libéré sans que
    '   la minuterie du système ne soit supprimée.
'
    ' L'exécution peut s'arrêter sur cette ligne en
    '   raison d'un bogue connu avec NT 3.51, avec
    '   lequel vous pouvez recevoir un événement
    '   Timer supplémentaire APRÈS avoir exécuté
    '   l'API KillTimer.
    KillTimer 0, idEvent
End Sub

' La procédure EndTimer est appelée par l'objet XTimer
' ------------------   lorsque la valeur False est affectée
'   à la propriété Enabled et qu'un nouvel intervalle de
'   minuterie est requis. Il n'existe aucun moyen de
'   réinitialiser une minuterie de système. La seule
'   solution pour modifier l'intervalle est donc de
'   supprimer la minuterie existante et d'appeler la
'   méthode BeginTimer pour en démarrer une nouvelle.
'
Public Sub EndTimer(ByVal xt As XTimer)
    Dim lngTimerID As Long
    Dim intCt As Integer
    
    ' Demande à l'objet XTimer son numéro TimerID, nécessaire
    '   pour rechercher dans le tableau le XTIMERINFO correct. Il
    '   est possible de rechercher la référence même de
    '   l'objet XTimer en utilisant l'opérateur Is qui compare
    '   xt et maxti(intCt).xt. Cette possiblité n'offre pas
    '   cependant la même rapidité.
    lngTimerID = xt.TimerID
    '
    ' Si l'ID de la minuterie est égale à zéro, la fonction EndTimer
    '   a été appelé avec une erreur.
    If lngTimerID = 0 Then Exit Sub
    '
    For intCt = 1 To mintMaxTimers
        If maxti(intCt).id = lngTimerID Then
            ' Supprime la minuterie du système.
            KillTimer 0, lngTimerID
            '
            ' Libère la référence à l'objet XTimer.
            Set maxti(intCt).xt = Nothing
            '
            ' Réinitialise l'ID en libérant un emplacement
            '   pour une nouvelle minuterie active.
            maxti(intCt).id = 0
            Exit Sub
        End If
    Next
End Sub

' La procédure Scrub peut être considérée comme un dispositif
' ---------------   de sécurité dans le cas du débogage: pour
'   mettre fin à ce projet alors qu'il reste des objets XTimer
'   actifs, appelez cette procédure à partir de la fenêtre
'   Exécution. Cela appellera l'API KillTimer pour toutes les
'   minuteries du système. Ainsi, l'environnement de développement
'   peut repasser sans risque en mode Création.
'
Public Sub Scrub()
    Dim intCt As Integer
    ' Supprime les minuteries actives restantes.
    For intCt = 1 To mintMaxTimers
        If maxti(intCt).id <> 0 Then KillTimer 0, maxti(intCt).id
    Next
End Sub
