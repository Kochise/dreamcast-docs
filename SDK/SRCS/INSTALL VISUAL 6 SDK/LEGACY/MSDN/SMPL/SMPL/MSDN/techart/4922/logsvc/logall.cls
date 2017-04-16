VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Services"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit

Public Error As LayerLogError.Service
Public Event As LayerLogInformation.Service
Public Trans As LayerLogDatabase.Service

Private Sub Class_Initialize()
On Error Resume Next
Set Error = New LayerLogError.Service
Set Event = New LayerLogInformation.Service
Set Trans = New LayerLogDatabase.Service
End Sub

Private Sub Class_Terminate()
On Error Resume Next
Set Error = Nothing
Set Event = Nothing
Set Trans = Nothing
End Sub
