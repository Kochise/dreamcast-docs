VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Widget"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
' >> L'affichage complet du module donne de meilleurs résultats. <<
'
' Stockage pour le numéro ID de débogage.
Private mlngDebugID As Long
Implements IDebug

' Les numéros d'erreur définis dans
'   une instruction Enum de type Public
'   sont visibles dans la totalité
'   du projet.
Public Enum WidgetErrors
    wdgERRTaskCanceled = 1059
End Enum

' L'événement PercentDone est déclenché à
'   intervalles réguliers pendant la méthode
'   LongTask, pour informer l'appelant de
'   l'avancement. L'événement dispose d'un
'   argument de pourcentage complet et d'un
'   argument ByRef Cancel auxquels l'appelant
'   peut affecter la valeur True pour annuler
'   la méthode LongTask.
Event PercentDone(ByVal Percent As Double, _
    Cancel As Boolean)
    
' La méthode LongTask simule une tâche longue
' --------      qui déclenche l'événement
'   PercentDone et permet à l'appelant
'   d'annuler l'opération.
'
' Le premier argument demande à la méthode
'   LongTask de définir la durée de simulation
'   de la tâche, que vous avez choisie. Le
'   deuxième argument définit le temps minimum
'   devant s'écouler avant de déclencher des
'   événements qui informent l'appelant de
'   l'avancement.
'
' L'utilisation d'intervalles de temps
'   pour déterminer le moment où les
'   événements doivent être déclenchés
'   donne des résultats plus probants
'   sur différents ordinateurs. Pour une
'   approche différente, reportez-vous à
'   la méthode LongTask2.
'
Public Sub LongTask(ByVal Duration As Double, _
        ByVal MinimumInterval As Double)
    Dim dblThreshold As Double
    Dim dblStart As Double
    Dim blnCancel As Boolean
    
    dblStart = Timer
    dblThreshold = MinimumInterval
    
    Do While Timer < (dblStart + Duration)
        ' Dans une application réelle, une
        '   portion du travail serait faite ici.
        '   Le travail doit être divisé en portions
        '   (unités) qui ne sont ni trop grandes
        '   (trop longues entre les notifications),
        '   ni trop petites (plus les tests sont
        '   nombreux, moins la méthode LongTask
        '   est efficace).
        
        ' Après chaque unité de travail, faites un
        '   test pour vérifier s'il convient
        '   d'informer l'appelant de l'avancement
        '   de la méthode LongTask.
        If Timer > (dblStart + dblThreshold) Then
            ' Déclenche l'événement; l'exécution de
            '   la méthode LongTask sera interrompue
            '   jusqu'au renvoi de la procédure
            '   d'événement de l'appelant!
            RaiseEvent PercentDone( _
                dblThreshold / Duration, _
                blnCancel)
            '
            ' Fait un test pour vérifier si l'appelant
            '   veut annuler la méthode LongTask.
            If blnCancel Then
                Err.Raise vbObjectError + wdgERRTaskCanceled, , _
                    "Tâche annulée"
' NOTE: Si votre programme s'arrête ici, faites
'   un clic droit pour faire apparaître le menu
'   contextuel de la fenêtre Code. Cliquez sur
'   Activer, puis sur Arrêt sur les erreurs non
'   gérées. Appuyez sur F5 pour continuer
'   l'exécution du programme (vous devez appuyer
'   sur Alt+Tab pour rappeler la feuille frmEvents).
'   Explications: l'option par défaut, Arrêt dans
'   les modules de classe, est très utile si vous
'   obtenez une erreur lors d'un appel à une
'   méthode d'une classe, car elle permet à Visual
'   Basic de provoquer un arrêt à l'INTÉRIEUR du
'   module de classe, à l'endroit de l'erreur. Rien
'   n'est plus pratique que de voir la classe
'   déclencher des erreurs automatiquement, comme
'   ici!
' Vous pouvez définir l'option par défaut Arrêt
'   sur les erreurs non gérées dans l'onglet
'   Général de la boîte de dialogue Options,
'   accessible à partir du menu Outils. En
'   faisant cela, n'oubliez pas que lorsque vous
'   effectuez un arrêt sur un appel de méthode,
'   et que vous voulez aller à l'endroit où
'   l'erreur s'est produite, vous pouvez utiliser
'   le menu contextuel de la fenêtre Code pour
'   activer l'option Arrêt dans les modules de
'   classe.
' Note: Vous pouvez également utiliser la combinaison
'   Alt+F5 pour ignorer une erreur en utilisant
'   l'option Arrêt dans les modules de classe
'   (ou Alt+F8 pour ignorer l'erreur et continuer
'   le débogage). Si ces touches ne provoquent
'   de déplacement dans le code, aucun gestionnaire
'   d'erreur n'est disponible. Pour plus
'   d'informations, reportez-vous à la section
'   "Débogage des modules de classe" des
'   Manuels en ligne.
' [Fin de la digression]
            End If
            '
            ' Définit le seuil pour la
            '   notification suivante.
            dblThreshold = dblThreshold + MinimumInterval
       End If
    Loop
End Sub
 
' La méthode LongTask2 simule également
' ---------     une tâche longue qui
'   déclenche l'événement PercentDone
'   et permet à l'appelant d'annuler
'   l'opération.
'
' La tâche simulée consiste en des calculs
'   répétés en virgule flottante. Le
'   premier argument demande à la méthode
'   LongTask2 de définir le nombre d'itérations
'   de la tâche, que vous avez choisi. Le
'   deuxième argument donne les modifications
'   du pourcentage, qui déclenche l'événement
'   de notification. Vous remarquerez que cette
'   méthode est le résultat d'une longueur
'   variable de temps entre les notifications,
'   une variation qui peut comprendre les
'   différences des performances des machines.
'
' En revanche, la méthode LongTask
'   utilise un intervalle de temps pour
'   déterminer la fréquence de déclenchement
'   de l'événement; cela donne des résultats
'   plus probants sur différents ordinateurs.
'
Public Sub LongTask2(ByVal Iterations As Long, _
        ByVal PercentChange As Byte)
    Dim lngThreshold As Long
    Dim dblIterationsPerEvent As Double
    Dim lngCt As Long
    Dim dblDummy As Double
    Dim blnCancel As Boolean
    
    dblIterationsPerEvent = Iterations _
        * (CDbl(PercentChange) / 100)
    lngThreshold = dblIterationsPerEvent
    
    For lngCt = 1 To Iterations
        ' Dans une application réelle, une
        '   portion du travail serait faite ici.
        '   Le travail doit être divisé en portions
        '   (unités) qui ne sont ni trop grandes
        '   (trop longues entre les notifications),
        '   ni trop petites (plus les tests sont
        '   nombreux, moins la méthode LongTask
        '   est efficace).
        dblDummy = 3.14159 * 2640 * 2640
        
        ' Après chaque unité de travail, faites un
        '   test pour vérifier s'il convient
        '   d'informer l'appelant de l'avancement
        '   de la méthode LongTask.
        If lngCt > lngThreshold Then
            ' Déclenche l'événement; l'exécution de
            '   la méthode LongTask2 sera interrompue
            '   jusqu'au renvoi de la procédure
            '   d'événement de l'appelant!
            RaiseEvent PercentDone( _
                lngCt * 100 / Iterations, _
                blnCancel)
            '
            ' Fait un test pour vérifier si l'appelant
            '   veut annuler la méthode LongTask2.
            If blnCancel Then
                Err.Raise vbObjectError + wdgERRTaskCanceled, , _
                    " Tâche annulée "
            End If
            '
            ' Définit le seuil pour la
            '   notification suivante.
            lngThreshold = lngThreshold + dblIterationsPerEvent
        End If
    Next
End Sub

Private Sub Class_Initialize()
    mlngDebugID = DebugInit(Me)
End Sub

Private Sub Class_Terminate()
    DebugTerm Me
End Sub

' -------- Implémentation de IDebug --------
'
' IDebug.DebugID permet de distinguer
' ====== -------    les différents objets. Il
'   est requis par les procédures de débogage
'   DebugInit, DebugTerm et DebugShow
'   déclarées dans le module modFriend.
'
Private Property Get IDebug_DebugID() As Long
    IDebug_DebugID = mlngDebugID
End Property


