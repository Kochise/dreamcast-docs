VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "UrlTools"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
Dim WithEvents UrlReader As READURLLib.UrlReader
Attribute UrlReader.VB_VarHelpID = -1

Private Sub Class_Initialize()
    
    Set UrlReader = New READURLLib.UrlReader

End Sub

Private Sub Class_Terminate()
    
    Set UrlReader = Nothing

End Sub

Private Sub UrlReader_ReadUrlError(ByVal lErrorCode As Long)
    
    MsgBox "Error reading URL:" & lErrorCode
    bFinished = True

End Sub

Private Sub UrlReader_ReadUrlFinished(ByVal lFlags As Long)
    
    MsgBox "Finished reading URL: " & MainForm.URLSpec
    bFinished = True

End Sub
Sub Read(ByVal Url As String, ByVal OutputSpec As String)
    
    UrlReader.ReadUrl Url, OutputSpec
    
End Sub
