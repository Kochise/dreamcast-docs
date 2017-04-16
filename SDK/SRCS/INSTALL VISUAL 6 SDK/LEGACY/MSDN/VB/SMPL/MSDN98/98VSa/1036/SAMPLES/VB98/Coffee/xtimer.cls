VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "XTimer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
'===============================================
' AVERTISSEMENT! Vous ne DEVEZ PAS cliquer sur
'   le bouton Fin pendant le débogage de ce
'   projet! Reportez-vous aux explications
'   figurant au début du module XTimerSupport
'   (XTimerS.bas).
'===============================================

' Stockage privé pour les propriétés de l'objet XTimer:
Private mlngTimerID As Long
Private mlngInterval As Long
Private mblnEnabled As Boolean

' Le seul événement de l'objet XTimer est Tick.
' Celui-ci n'a pas d'arguments (ce qui améliore sensiblement
' la vitesse d'exécution de l'événement) mais rien ne vous 
' empêche d'en fournir si vous le désirez.
Event Tick()

' La propriété TimerID est requise par la procédure EndTimer,
' ----------------   afin de localiser rapidement la minuterie
'   dans le tableau du module XTimerSupport des minuteries actives.
'
' Il n'y a pas de raison que le client utilise cette propriété;
'   elle est donc déclarée en tant que Friend au lieu de Public.
'
Friend Property Get TimerID() As Long
    TimerID = mlngTimerID
End Property

' La propriété Enabled allume et éteint la minuterie.
' ----------------      Cela est réalisé en arrêtant la
'   minuterie du système car il n'existe pas de solution
'   pour la suspendre, son rôle étant de fonctionner.
'
Public Property Get Enabled() As Boolean
    Enabled = mblnEnabled
End Property
'
Public Property Let Enabled(ByVal NewValue As Boolean)
    ' Si aucune modification n'intervient dans l'état
    '   de la propriété, alors quitte. Cela
    '   empêche de démarrer une autre minuterie
    '   lorsqu'il y en a une qui fonctionne déjà.
    If NewValue = mblnEnabled Then Exit Property
    '
    ' Enregistre la nouvelle valeur de la propriété.
    mblnEnabled = NewValue
    '
    ' Si l'intervalle est égale à zéro, la minuterie
    '   est déjà arrêtée. Ne pas la démarrer.
    If mlngInterval = 0 Then Exit Property
    '
    ' Allume ou éteint la minuterie.
    If mblnEnabled Then
        Debug.Assert mlngTimerID = 0
        mlngTimerID = BeginTimer(Me, mlngInterval)
    Else
        ' Ce qui suit est nécessaire car l'objet
        '   XTimer peut éteindre sa minuterie
        '   du système de deux façons: Enabled = False,
        '   ou Interval = 0.
        If mlngTimerID <> 0 Then
            Call EndTimer(Me)
            mlngTimerID = 0
        End If
    End If
End Property

' La propriété Interval peut faire plus que de définir
' -----------------   uniquement l'intervalle de la minuterie.
'   Si l'objet XTimer est activée, et que la propriété
'   Interval passe de zéro à une valeur différente de zéro,
'   une minuterie du système pourra démarrer. De même, si la
'   propriété Interval prend la valeur 0, la minuterie doit être
'   arrêtée.
'
' La procédure de la propriété Let met fin également à une
'   minuterie du système et en démarre une autre lorsque
'   l'intervalle change. cela s'explique par l'impossibilité
'   de modifier l'intervalle d'une minuterie.
'
Public Property Get Interval() As Long
    Interval = mlngInterval
End Property
'
Public Property Let Interval(ByVal NewInterval As Long)
    ' Si la nouvelle valeur de la propriété Interval est égale
    '   à l'ancienne, il n'existe aucune raison de faire
    '   quelque chose.
    If NewInterval = mlngInterval Then Exit Property
    '
    ' Enregistre la nouvelle valeur.
    mlngInterval = NewInterval
    '
    ' Si l'objet XTimer est active, mlngTimerID
    '   est différent de zéro. Dans ce cas, l'ancienne
    '   minuterie du système doit être arrêtée avant
    '   le démarrage de la nouvelle.
    If mlngTimerID <> 0 Then
        Call EndTimer(Me)
        mlngTimerID = 0
    End If
    '
    ' Si le nouvel intervalle est égale à zéro, l'objet
    '   XTimer est désactivée, quelle que soit la
    '   valeur de la propriété Enabled. Si le nouvel
    '   intervalle est différent de zéro ET que la
    '   valeur de la propriété Enabled est True, une
    '   nouvelle minuterie démarre et son ID est stocké
    '   dans mlngTimerID.
    If (NewInterval <> 0) And mblnEnabled Then
        mlngTimerID = BeginTimer(Me, NewInterval)
    End If
End Property

' La méthode RaiseTick est appelée par le module XTimerSupport
' ----------------   lorsque l'événement de la minuterie se
'   produit pour la minuterie du système de cet objet XTimer.
'
' Explication de l'implémentation:   il est préférable de déclarer
'   cette méthode en tant que Friend au lieu de Public, dans la
'   mesure où le client n'a pas besoin d'appeler cette méthode
'   RaiseTick. Il peut être dangereux de déclarer la méthode en
'   tant que Public car l'objet peut être libéré alors que
'   l'événement Tick est toujours maintenu. Un objet ne se
'   terminera PAS tant que l'une de ses méthodes de type Public
'   est sur la pile. En revanche, il PEUT se terminer si une
'   méthode de type Friend est sur la pile. Si l'objet se
'   termine avant le renvoi de la méthode Friend (ce qui peut
'   se produire si le client exécute beaucoup de code dans
'   l'événement Tick de l'objet XTimer), une erreur de 
'   protection générale se produira.
'   Note: ce scénario est très improbable et dépend d'événements
'   extérieurs; il ne se produit pas lors de l'utilisation
'   courante des fonctions Friend.
'
Public Sub RaiseTick()
    RaiseEvent Tick
End Sub

Private Sub Class_Terminate()
    ' Lorsque le client libère sa dernière référence à
    '   un objet XTimer, il s'arrête -- mais uniquement
    '   si la propriété Enabled de l'objet XTimer a
    '   pour valeur False, ou que sa propriété
    '   Interval a pour valeur True!
    '
    ' Pendant le fonctionnement de la minuterie de
    '   l'objet XTimer, le module XTimerSupport doit,
    '   en effet, avoir une référence à l'objet XTimer
    '   pour pouvoir déclencher son événement Tick.
    '   L'échec du client pour désactiver les objets
    '   XTimer avant de les libérer entraîne la perte
    '   des minuteries du système!
    '
    ' Cette perte des minuteries du système ne sera
    '   pas récupérable tant que le composant XTimers
    '   ne s'arrête pas, en d'autres termes, tant que le
    '   client qui utilise la DLL ne s'arrête pas.
    '   La DLL ne sera PAS déchargée lorsque tous les
    '   objets XTimer sont libérés, car les références
    '   aux objets de type Public (dans ce cas, les
    '   références maintenues par le module XTimerSupport)
    '   empêchent le déchargement des DLL.
    '
    ' Pourquoi donc se soucier de nettoyer la minuterie
    '   du système dans l'événement Terminate? Parce que
    '   toutes les références à l'objet XTimer seront
    '   nettoyées lors du déchargement de la DLL, et que
    '   l'objet XTimer obtiendra son événement Terminate.
    '   La minuterie du système serait détruite à
    '   ce moment-là.
    On Error Resume Next
    If mlngTimerID <> 0 Then KillTimer 0, mlngTimerID
    '
    ' Ce qui suit montre ce que ferait l'objet XTimer
    '   dans l'hypothèse où il serait libéré avant
    '   le déchargement de la DLL.
    'If mlngTimerID <> 0 Then Call EndTimer(Me)
End Sub

