VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CbClientClass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
' Cette classe interne est créée par le client et passée au composant distant.
' Le composant distant se fixe à elle et l'alimente à intervalles réguliers.
' Note: les propriétés de la classe (appuyez sur F4) marquent cette classe comme Public.
' Cela lui permet d'être utilisé par l'horloge externe du système externe.

Private Sub class_terminate()
  Debug.Print "CbClientProj.CbClientClass Terminé."
End Sub

Private Sub class_initialize()
  Debug.Print "CbClientProj.CbClientClass Initialisé."
End Sub

Public Sub TellTime(sCurTime As String)
  ' Il s'agit de la méthode *public* que le composant appelle pour
  ' mettre à jour l'heure du client. Dans un scénario réel, le
  ' composant ferait des opérations un peu plus importantes, telles
  ' que la fourniture de cotations boursières, la proposition de
  ' nouveaux articles à des utilisateurs, ou des rapports
  ' d'activité. Notez cependant que si cette procédure n'est pas
  ' marquée comme Public, le composant ne pourra pas l'appeler.
  
    frmCBCli.lblTime.Caption = sCurTime
End Sub

