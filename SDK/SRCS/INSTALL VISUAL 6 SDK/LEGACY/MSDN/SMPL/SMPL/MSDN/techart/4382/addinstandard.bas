Attribute VB_Name = "AddInStandard"
'AddInStandard : Routines to use in all AddIns
Option Explicit
Dim uSERNAME$
#If Win16 Then
Private Declare Function WritePrivateProfileString% Lib "KERNEL" (ByVal AppName$, ByVal KeyName$, ByVal keydefault$, ByVal FileName$)
Private Declare Function GetPrivateProfileString% Lib "KERNEL" (ByVal AppName$, ByVal KeyName$, ByVal keydefault$, ByVal ReturnString$, ByVal NumBytes As Integer, ByVal FileName$)
#Else
Private Declare Function WritePrivateProfileString% Lib "Kernel32" Alias "WritePrivateProfileStringA" (ByVal AppName$, ByVal KeyName$, ByVal keydefault$, ByVal FileName$)
Private Declare Function GetPrivateProfileString% Lib "Kernel32" Alias "GetPrivateProfileStringA" (ByVal AppName$, ByVal KeyName$, ByVal keydefault$, ByVal ReturnString$, ByVal NumBytes As Integer, ByVal FileName$)
#End If
'Add automatically if not register -- maintain bitness [not needed]
Sub AddIn_RegisterSame(ByVal AddInName$)
Dim ReturnString As String, Errcode As Integer
Dim i%, Section$
#If Win16 Then
        Section$ = "Add-Ins16"
    #Else
        Section$ = "Add-Ins32"
    #End If
    ReturnString = String$(255, Chr$(0))
    Errcode = GetPrivateProfileString(Section$, AddInName$, "NotFound", ReturnString, Len(ReturnString) + 1, "VB.INI")
    If Left(ReturnString, InStr(ReturnString, Chr(0)) - 1) = "NotFound" Then
        Errcode = WritePrivateProfileString%(Section$, AddInName$, "0", "VB.INI")
    End If
End Sub
'Register this for use with both 16 and 32 -- Out of Proc Server
Sub AddIn_RegisterAll(ByVal AddInName$)
Dim i%, Section$
Dim ReturnString As String, Errcode As Integer
    For i% = 0 To 1
        Select Case i%
            Case 0
            Section$ = "Add-Ins16"
            Case 1
            Section$ = "Add-Ins32"
        End Select
        ReturnString = String$(255, Chr$(0))
        Errcode = GetPrivateProfileString(Section$, AddInName$, "NotFound", ReturnString, Len(ReturnString) + 1, "VB.INI")
        If Left(ReturnString, InStr(ReturnString, Chr(0)) - 1) = "NotFound" Then
            Errcode = WritePrivateProfileString%(Section$, AddInName$, "0", "VB.INI")
        End If
    Next i%
End Sub

'Checks that License user -- we check that user is MSDN user
Sub AddIn_License()
Dim i%, Section$
Dim ReturnString As String, Errcode As Integer
ReturnString = String$(255, Chr$(0))
Errcode = GetPrivateProfileString("MSDN.Settings", "licensed.name", "", ReturnString, Len(ReturnString) + 1, "INFOVIEW.INI") 'July 95 onwards
If Errcode > 0 Then uSERNAME$ = Left$(ReturnString, Errcode)
If Len(uSERNAME$) = 0 Then
    MsgBox "You are not a licensed user of this Add-In.  Please call 1.206.936.8661 to become a MSDN Library subscriber.", 16, "Unlicensed Use"
    End
End If
End Sub

