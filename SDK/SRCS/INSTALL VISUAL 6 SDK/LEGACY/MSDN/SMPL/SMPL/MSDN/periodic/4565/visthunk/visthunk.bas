Attribute VB_Name = "basVisThunk"
Declare Function OGetString Lib "yeller.dll" Alias "GetString" (ByVal x As Integer) As Long ' For LPSTR
Declare Function OGetStringA Lib "yeller.dll" Alias "GetStringA" (ByVal stg As String, ByVal x As Integer) As Integer
Declare Function OPowers Lib "yeller.dll" Alias "Powers" (ByVal x As Integer, ByVal n As Integer) As Double
Declare Function lstrcpy Lib "kernel" (ByVal lpString1 As String, ByVal lpString2 As Any) As Long

Sub Main()
End Sub
