VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Resource"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
'VB Component - Error Resources - 06/95
'by Ken Bergmann
'Purpose: Contains the error object resources.
'Modification Log:
'   When    Who     What
'   ----------------------------------------------------------------------------
'   9/94    kenbe   Original Creation
'
'Usage Notes:
'
'Procedures:
'Sub Localize(ByVal lErrNum As Long, sOutText As String)
Option Explicit

'Localize - Error Object - 06/95
'by Ken Bergmann
'Purpose - Allows the application to introduce code
'          to localize errors from external source.
Public Sub Localize(ByVal lErrNum As Long, sOutText As String)
Dim sText As String
On Error Resume Next
Err = 0
sText = LoadResString(lErrNum)
If Not CBool(Err) Then sOutText = Trim$(sText)
End Sub
