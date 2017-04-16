VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CTDetDSO"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private oListener As DataSourceListener
Private oOSP As CTDetOSP

Public Function msDataSourceObject(ByVal qualifier As String) As OLEDBSimpleProvider
Attribute msDataSourceObject.VB_UserMemId = -3900
    Set msDataSourceObject = oOSP
End Function
Public Function addDataSourceListener(ByVal idslListener As DataSourceListener)
Attribute addDataSourceListener.VB_UserMemId = -3901
    Set oListener = idslListener
End Function
Public Sub removeDataSourceListener(ByVal idslListener As DataSourceListener)
Attribute removeDataSourceListener.VB_UserMemId = -3902
    Set oListener = Nothing
End Sub
Private Sub Class_Initialize()
    Set oOSP = New CTDetOSP
End Sub
Private Sub Class_Terminate()
    Set oOSP = Nothing
End Sub

Public Property Let ReqId(ByVal vNewValue As Variant)
    'Init OSP for a request
    oOSP.InitForReqId vNewValue
End Property

