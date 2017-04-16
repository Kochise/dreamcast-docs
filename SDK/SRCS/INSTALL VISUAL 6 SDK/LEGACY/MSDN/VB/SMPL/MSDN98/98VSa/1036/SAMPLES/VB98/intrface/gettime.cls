VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "InterfaceTimeClass"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Public Function GetTime() As String
    GetTime = Time
End Function

