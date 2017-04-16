Attribute VB_Name = "AddIn"
Option Explicit

'---- run this application to setup the Expert Agent as a VB Add-In


'<Declare>------------------------------------------
Private Declare Function WritePrivateProfileString Lib "Kernel32" Alias "WritePrivateProfileStringA" (ByVal AppName As String, ByVal KeyName As String, ByVal KeyDefault As String, ByVal FileName As String) As Long
'</Declare>-----------------------------------------

Public Sub Main()
    Call WritePrivateProfileString("Add-Ins32", "ExpertAgent.Connect", "0", "vbaddin.ini")
End Sub
