VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Service"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit

Public Function CloseKey(hKey As Long) As Boolean
If RegCloseKey(hKey) Then
    CloseKey = False
Else
    CloseKey = True
End If
End Function

Public Function CreateKey(hKey As Long, sSubKey As String, sClass As String) As Long
Dim hKeyBuffer      As Long
Dim lErr            As Long
Dim lAccessDesired  As Long
Dim lOptions        As Long
Dim lDisposition    As Long

lAccessDesired = KEY_ALL_ACCESS
lOptions = 0
lDisposition = 0

If RegCreateKeyExA(hKey, sSubKey, 0, sClass, lOptions, lAccessDesired, vbNull, hKeyBuffer, lDisposition) Then
    CreateKey = False
Else
    CreateKey = hKeyBuffer
End If
End Function

Public Function DeleteKey(hKey As Long, sSubKey As String) As Boolean
'Win95 will delete a Registry Key and all of it's descendants.
'WinNT will delete a Registry Key ONLY if NO descendants are present.
If RegDeleteKey(hKey, sSubKey) Then
    DeleteKey = False
Else
    DeleteKey = True
End If
End Function

Public Function DeleteValue(hKey As Long, sName As String) As Boolean
If RegDeleteValue(hKey, sName) Then
    DeleteValue = False
Else
    DeleteValue = True
End If
End Function

Public Function GetKey(hKey As Long, sSubKey As String) As Long
Dim lAccessDesired  As Long
Dim hKeyBuffer      As Long
lAccessDesired = KEY_ALL_ACCESS
If RegOpenKeyExA(hKey, sSubKey, 0, lAccessDesired, hKeyBuffer) Then
    GetKey = False
Else
    GetKey = hKeyBuffer
End If
End Function

Public Function GetValue(hKey As Long, sName As String) As String
Dim sData As String
sData = Space(254)
If RegQueryValueExA(hKey, sName, 0, REG_SZ, ByVal sData, Len(sData)) Then
    GetValue = ""
Else
    GetValue = Left$(sData, InStr(sData, Chr$(0)) - 1)
End If
End Function

Public Function SetValue(hKey As Long, sName As String, sData As String) As Boolean
If RegSetValueExA(hKey, sName, 0, REG_SZ, ByVal sData, Len(sData)) Then
    SetValue = False
Else
    SetValue = True
End If
End Function
