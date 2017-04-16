VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "IShape"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

' Le module de classe IShape est une "classe
'   abstraite" définissant l'interface IShape.
'   En réalité, ce n'est pas tout à fait le
'   cas puisqu'une véritable classe abstraite
'   ne peut servir à créer des objets. Cette
'   classe, comme toute classe définie dans
'   Visual Basic, peut servir à la création
'   d'objets mais ces objets ne seront pas
'   très utiles car il existe des membres
'   sans implémentation, comme une véritable
'   classe abstraite.

' La méthode TimeTest ne prend pas d'arguments
' --------      et son implémentation est
'   toujours vide (elle n'exécute pas de code).
'   Elle a pour seul but de montrer les liaisons
'   tardives et précoces.
Public Sub TimeTest()
End Sub

Public Sub DrawToPictureBox(ByVal pb As PictureBox)
End Sub

