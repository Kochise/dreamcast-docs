VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "IDebug"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

' L'interface IDebug est implémentée par tous
' ======    les objets du projet. Elle
'   contient des méthodes et des propriétés
'   de débogage (ProgWOb dispose seulement
'   de l'une d'entre elles: la propriété DebugID).
'
' Pourquoi une interface séparée? Dans ce
'   projet, la classe Polygon est utilisée
'   de deux façons: les objets Polygon sont
'   créés, et l'interface Polygon est
'   implémentée par deux autres classes.
'   En plaçant une propriété DebugID sur
'   l'interface Polygon par défaut, nous
'   pourrions tout à fait  placer des
'   propriétés DebugID simulées sur ces
'   implémentations, comme nous l'avons
'   fait avec la méthode TimeTest.
'
' Une interface séparée ne demande qu'une
'   ligne de code supplémentaire (l'instruction
'   Implements IDebug) par rapport à l'ajout
'   de la propriété DebugID sur l'interface
'   par défaut de chaque classe
'
'
' La propriété DebugID est implémentée en
' -------       fournissant une variable
'   de type Long pour stocker l'identificateur
'   de débogage, et en appelant la propriété
'   DebugInit pour définir l'identificateur
'   (dans l'événement Initialize).
'
Public Property Get DebugID() As Long
End Property
