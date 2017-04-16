VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "ServerInterface"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Public Function objGetClassInstance(rstrClassName As String) As Object
' Retourne une référence d'objet Automation pour la classe demandée. 
' Retourne Nothing en cas d'erreur. 
On Error GoTo gciError

Set objGetClassInstance = CreateObject("InterfaceProj." & rstrClassName)
GoTo gciExit

gciError:
  objGetClassInstance = Nothing
  Resume gciExit
  
gciExit:
End Function
