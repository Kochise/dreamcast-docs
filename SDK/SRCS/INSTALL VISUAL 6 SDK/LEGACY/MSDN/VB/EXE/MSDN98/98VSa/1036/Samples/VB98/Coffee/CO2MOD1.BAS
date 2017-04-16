Attribute VB_Name = "Module1"
Option Explicit
' > Pour plus d'informations sur cet exemple d'application,
'   recherchez "Coffee" dans l'aide en ligne.
' > Le fichier AboutCof.txt, présent dans le dossier
'   Documents associés de CoffWat2.vbp, contient également
'   des informations sur cet exemple.

' La variable gCoffeeMonitor maintient une référence à l'objet
' --------------   CoffeeMonitor partagé. Quand un client
'   accède à la propriété CoffeeMonitor d'un objet
'   Connector, la propriété Get renvoie cette référence
'   (Reportez-vous au module de la classe Connector).
Public gCoffeeMonitor As CoffeeMonitor

' La variable gCoffeeMonitor2 maintient une référence à l'objet
' --------------   CoffeeMonitor2 partagé. Quand un client
'   accède à la propriété CoffeeMonitor2 d'un objet
'   Connector2, la propriété Get renvoie cette référence
'   (Reportez-vous au module de la classe Connector2).
Public gCoffeeMonitor2 As CoffeeMonitor2

