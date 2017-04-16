VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "ReportBuildMessage"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit

'External handles
Public Header As Object
Public Fields As Object
Private Sub Class_Initialize()

    Set Header = New Header
    Set Fields = New Fields

End Sub


