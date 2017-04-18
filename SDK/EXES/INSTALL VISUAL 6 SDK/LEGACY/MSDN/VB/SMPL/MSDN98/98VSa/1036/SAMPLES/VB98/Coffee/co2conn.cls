VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Connector"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = True
Option Explicit
' > Pour plus d'informations sur cet exemple d'application,
'   recherchez "Coffee" dans l'aide en ligne.
' > Le fichier AboutCof.txt, présent dans le dossier
'   Documents associés de CoffWat2.vbp, contient également
'   des informations sur cet exemple.

' Classe Connector
' ---------------
' La classe Connector permet à plusieurs clients de partager
' ----------------  une instance unique de CoffeeMonitor. La
'   propriété Instancing de la classe Connector a pour
'   valeur MultiUse; ainsi, chaque client peut créer son
'   propre objet Connector. Tous les objets Connector
'   renvoient une référence à l'unique objet CoffeeMonitor
'   partagé; ainsi, tous les clients partagent le même objet
'   CoffeeMonitor (Reportez-vous à la propriété CoffeeMonitor
'   ci-dessous).
'
' La lecture du chapitre "Création d'un composant EXE ActiveX"
'   des Manuels en ligne fait apparaître une différence:
'   cette version de Connector ne dispose pas de "compte
'   d'utilisation" qui détermine lorsqu'il faut affecter
'   la valeur Nothing à la variable gCoffeeMonitor. Le code de
'   l'événement Initialize n'est pas indispensable pour
'   incrémenter ce compte d'utilisation, et celui de
'   l'événement Terminate ne l'est pas pour décrémenter
'   et tester ce compte.
'
' Cela résout un bogue décrit dans la section
'   "Utilisation du CoffeeMonitor partagé" du chapitre
'   mentionné ci-dessus. Pour en savoir plus sur le
'   compte d'utilisation et sur sa manière de régler
'   le bogue, reportez-vous au module de classe
'   CoffeeMonitor.


' La propriété CoffeeMonitor renvoie toujours la
' --------------   référence globale unique à
'   l'instance partagée de CoffeeMonitor (créée
'   lors de la première demande d'un client à
'   CoffeeMonitor).
'
Public Property Get CoffeeMonitor() As CoffeeMonitor
    '' Si l'objet partagé CoffeeMonitor n'est pas créé,
    '   le crée et y stocke une référence globale.
    If gCoffeeMonitor Is Nothing Then
        Set gCoffeeMonitor = New CoffeeMonitor
    End If
    
    Set CoffeeMonitor = gCoffeeMonitor
End Property
    
