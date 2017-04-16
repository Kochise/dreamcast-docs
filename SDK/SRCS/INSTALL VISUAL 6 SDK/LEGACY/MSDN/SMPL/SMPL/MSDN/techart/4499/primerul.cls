VERSION 1.0 CLASS
BEGIN
  MultiUse = 0   'False
END
Attribute VB_Name = "PrimeRule"
Attribute VB_Creatable = True
Attribute VB_Exposed = True

Public Function ExecRule(oClient As Object, szStat As String)
    Dim vResult As Variant
    
    If szStat = "Mnt" Then
        vResult = oClient.Refresh(0, "Maintenance cannot be applied during prime hours")
        ExecRule = 1
    Else
        ExecRule = 0
    End If
    
End Function
