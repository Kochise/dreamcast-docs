VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsReport"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'Internal variable for the file name
Private sFileName As String

Public Property Get FileName()
    
    'Property for retrieving the file name
    FileName = sFileName

End Property


Public Sub SetFileName(sFileNameIN As String)

    'Property for setting the file name
    sFileName = sFileNameIN
    
End Sub


