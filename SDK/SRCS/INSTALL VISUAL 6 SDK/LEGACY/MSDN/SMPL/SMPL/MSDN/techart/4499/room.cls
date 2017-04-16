VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Room"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit

Private szGuest As String
Private nOrder As Integer
Private szRoom As String
Private szStatus As String

Public Function Initialize(nOrd, szGst, szRm, szStat)
    nOrder = nOrd
    szGuest = szGst
    szRoom = szRm
    szStatus = szStat
    Initialize = True
    
End Function


Public Function RefreshClient(oClient As Object)
    Dim vValues(4) As Variant
    
    vValues(0) = nOrder
    vValues(1) = szRoom
    vValues(2) = szStatus
    vValues(3) = szGuest
    RefreshClient = oClient.Refresh(1, vValues)
    'RefreshClient = oClient.RoomUpdate(nOrder, szRoom, szStatus, szGuest)

End Function

Public Function ChangeStatus(oClient As Object, szStat As String)
    Dim vResult As Variant
    
    vResult = gPrimeRule.ExecRule(oClient, szStat)
    If vResult = 0 Then
        szStatus = szStat
    End If
    ChangeStatus = vResult
    
End Function
