VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "HelloClass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True

Public Function SayHello() As String
    SayHello = "Utilisateur de Microsoft Visual Basic, Bonjour!"
End Function

Private Sub Class_Terminate()
  Unload frmHello
End Sub
