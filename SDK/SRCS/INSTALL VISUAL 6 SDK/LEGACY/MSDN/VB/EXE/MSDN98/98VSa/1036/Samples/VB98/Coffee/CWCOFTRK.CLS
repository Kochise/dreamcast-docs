VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CoffeeTracker"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

' CoffeeTracker est un petit objet privé
' =============     pour garder la trace
'   d'une tâche exécutée par un objet
'   Coffee. L'utilisation d'objets est
'   dictée par le fait que les variables
'   WithEvents ne peuvent être mises dans des
'   tableaux. Pour en avoir un nombre
'   variable, il convient d'avoir une
'   classe d'objets pour conserver les
'   variables WithEvents.
'
' Définit les propriétés ThreadID et Size avant le
'   début de l'exécution de la tâche longue; définit
'   la propriété Coffee JUSTE avant que vous
'   n'appeliez StartLongTask. L'ID est affecté
'   par la procédure NewTracker dans la
'   feuille frmThread; il s'agit de l'index
'   de l'objet dans l'objet Collection
'   CoffeeTrackers.

Public ThreadID As Long
Public Size As Long
Public ID As String

' Stockage pour l'objet Coffee dont il faut garder une trace.
Private WithEvents mwCoffee As Coffee
Attribute mwCoffee.VB_VarHelpID = -1
'
' Heure de début (depuis l'API timeGetTimer).
Private mlngStart As Long

Public Property Get Coffee() As Coffee
    Set Coffee = mwCoffee
End Property
Public Property Set Coffee(ByVal NewValue As Coffee)
    ' Enregistre l'heure de début.
    mlngStart = timeGetTime
    Set mwCoffee = NewValue
End Property

' L'objet Coffee déclenche un événement
'   Complete lorsque la tâche dont il faut
'   garder une trace est terminée. L'objet
'   CoffeeTracker met les informations
'   sur la tâche (ID de la thread, taille
'   et nombre de secondes par itération)
'   dans une zone de liste de la feuille
'   frmThread.
'
Private Sub mwCoffee_Complete(ByVal Canceled As Boolean)
    Dim lngEnd As Long
    Dim dblElapsed As Double
    
    lngEnd = timeGetTime
    '
    ' Libère l'objet Coffee.
    Set mwCoffee = Nothing
    '
    ' Ajoute une ligne d'état à la zone de liste.
    If Canceled Then
        frmThread.lstResults.AddItem ThreadID _
            & " (" & Size & ") annulé", 0
    Else
        frmThread.lstResults.AddItem ThreadID _
            & " (" & Size & ") " _
            & (CDbl(lngEnd) - mlngStart) / Size / 1000# _
            & " sec/itération", 0
    End If
    '
    ' L'objet CoffeeTracker supprime sa référence
    '   de la collection, ce qui le laisse
    '   sans références. Il peut donc se
    '   terminer.
    frmThread.CoffeeTrackers.Remove ID
End Sub

' Pour les tâches longues, les événements
'   Coffee déclenchent un événement Progress
'   à chaque 10% effectué par la tâche. L'objet
'   CoffeeTracker ajoute une entrée à la
'   zone de liste de la feuille frmThread.
'
Private Sub mwCoffee_Progress(ByVal PercentDone As Single, Cancel As Boolean)
    frmThread.lstResults.AddItem ThreadID _
        & " (" & Size & ") " _
        & Format$(PercentDone * 100, "#0.0") & "%", 0
    '
    ' Dès qu'un objet CoffeeTracker détecte
    '   l'indicateur global Cancel, il arrête
    '   la tâche longue qu'il attendait.
    '   L'objet Coffee déclenchera ensuite
    '   un événement Complete (voir ci-dessus).
    If frmThread.CancelAll Then Cancel = True
End Sub

