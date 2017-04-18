VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Connector2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = True
Option Explicit
' > Pour plus d'informations sur cet exemple d'application,
'   recherchez "Coffee" dans l'aide en ligne.
' > Le fichier AboutCof.Txt, présent dans le dossier
'   Documents associés de CoffWat2.vbp, contient également
'   des informations sur cet exemple.

' La classe Connector2 permet à plusieurs clients de partager
' ----------------  une instance unique de CoffeeMonitor2. La
'   propriété Instancing de la classe Connector2 a pour
'   valeur MultiUse; ainsi, chaque client peut créer son
'   propre objet Connector2. Tous les objets Connector2
'   renvoient une référence à l'unique objet CoffeeMonitor2
'   partagé; ainsi, tous les clients partagent le même objet
'   CoffeeMonitor2 (Reportez-vous à la propriété CoffeeMonitor2
'   ci-dessous).

' La propriété CoffeeMonitor2 renvoie toujours la
' --------------   référence globale unique à
'   l'instance partagée de CoffeeMonitor2.
'
Public Property Get CoffeeMonitor2() As CoffeeMonitor2
    ' Si l'objet partagé CoffeeMonitor2 n'est pas créé,
    '   le crée et y stocke une référence globale.
    If gCoffeeMonitor2 Is Nothing Then
        Set gCoffeeMonitor2 = New CoffeeMonitor2
    End If
    
    Set CoffeeMonitor2 = gCoffeeMonitor2
End Property
    

