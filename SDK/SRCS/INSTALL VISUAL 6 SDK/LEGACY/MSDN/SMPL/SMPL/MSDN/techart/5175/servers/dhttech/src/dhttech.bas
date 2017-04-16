Attribute VB_Name = "dhtech"
Private Declare Function GetUserName Lib "advapi32.dll" Alias "GetUserNameA" (ByVal lpbuffer As String, nSize As Long) As Long

Public Const scUNCLAIMED = "UNCLAIM"
Public Const scCLAIMED = "CLAIMED"
Public Const scINPROG = "INPROG"
Public Const scPENDING = "PENDING"

Public Function sGetUserName() As String
Dim sBuffer As String
Dim sUser As String
Dim lSize As Long

'Get user name
sBuffer = Space$(255)
lSize = Len(sBuffer)
Call GetUserName(sBuffer, lSize)
If lSize > 0 Then
    sUser = Left$(sBuffer, lSize - 1)
End If
'Return user name
sGetUserName = sUser
End Function

