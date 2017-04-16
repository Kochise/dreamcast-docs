VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Thunk"
Attribute VB_Creatable = True
Attribute VB_Exposed = True

Function GetString(i As Integer) As String
    Dim l As Long
    Dim y As String * 32
    
    l = OGetString(i)
    n = lstrcpy(y, l)

    GetString = y
End Function


Function GetStringA(str As String, x As Integer) As Integer
    Dim irc As Integer
    irc = OGetStringA(str, x)
    GetStringA = irc
End Function

Function Powers(x As Integer, n As Integer) As Double
    Dim dbl As Double
    dbl = OPowers(x, n)
    Powers = dbl
End Function
