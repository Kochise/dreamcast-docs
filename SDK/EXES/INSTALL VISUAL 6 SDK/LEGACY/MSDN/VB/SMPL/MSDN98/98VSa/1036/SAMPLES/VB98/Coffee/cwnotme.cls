VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "NotifyMe"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

' La classe NotifyMe implémente ICoffeeNotify de
'   sorte que sa méthode de rappel
'   (CoffeeReady) peut être appelée
'   au moyen d'une liaison précoce.
Implements ICoffeeNotify

' Stockage pour l'implémentation de NotifyID.
Private mlngNotifyID As Long

' La méthode ICoffeeNotify.CoffeeReady est appelé par
' ============= -----------     l'objet
'   CoffeeMonitor2 dans Coffee2. Cette
'   implémentation ajoute l'heure de l'appel
'   à la zone de liste et efface le cas
'   échéant les anciennes entrées.
'
Private Sub ICoffeeNotify_CoffeeReady()
    With Form1.lstCallBacks
        .AddItem Format$(Now, "ddd hh:mm:ss"), 0
        If .ListCount > 10 Then .RemoveItem 10
    End With
End Sub

' La propriété ICoffeeNotify.NotifyID
' ============= --------       maintient
'   la clé de l'objet de la notification
'   dans le tableau CoffeeMonitor2 des
'   objets du client. L'implémentation
'   du client ne fait que stocker et
'   renvoyer la valeur.
'
Private Property Let ICoffeeNotify_NotifyID(ByVal RHS As Long)
    mlngNotifyID = RHS
End Property
'
Private Property Get ICoffeeNotify_NotifyID() As Long
    ICoffeeNotify_NotifyID = mlngNotifyID
End Property
