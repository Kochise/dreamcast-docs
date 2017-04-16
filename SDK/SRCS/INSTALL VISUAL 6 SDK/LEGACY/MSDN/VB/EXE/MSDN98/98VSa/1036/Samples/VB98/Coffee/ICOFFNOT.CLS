VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "ICoffeeNotify"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

' Le module ICoffeeNotify définie une interface
'   contenant la méthode de rappel CoffeeReady,
'   et une propriété utilisée pour stocker l'ID
'   du client (affecté par CoffeeMonitor2).
'

' L'implémentation de la méthode CoffeeReady contient
' ----------- tout le code que le client veut
'   exécuter lorsqu'un rappel se produit.
'
Public Sub CoffeeReady()
End Sub

' L'implémentation de la propriété NotifyID doit fournir 
' --------    des données de type Long pour stocker
'   le numéro ID. CoffeeMonitor2 l'utilise pour
'   rechercher l'objet de rappel lorsque une
'   demande de déconnexion est faite.
'
Public Property Get NotifyID() As Long
End Property
Public Property Let NotifyID(ByVal NewValue As Long)
End Property
