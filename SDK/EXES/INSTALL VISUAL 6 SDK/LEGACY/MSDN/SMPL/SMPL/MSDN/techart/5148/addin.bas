Attribute VB_Name = "AddIn"
Option Explicit

'<Declare>------------------------------------------
Private Declare Function WritePrivateProfileString Lib "Kernel32" Alias "WritePrivateProfileStringA" (ByVal AppName As String, ByVal KeyName As String, ByVal KeyDefault As String, ByVal FileName As String) As Long
'</Declare>-----------------------------------------

'---------------------------------------------------------
' this sub should be executed from the Immediate window
' in order to get this app added to the VBADDIN.INI file
' <Note> this code can also be run using the AgentIni
' project
'---------------------------------------------------------
Public Sub SetupAddIn()

    Call WritePrivateProfileString("Add-Ins32", "ExpertAgent.Connect", "0", "vbaddin.ini")

End Sub
