Attribute VB_Name = "Module2"
'Attribute VB_Name = "RegUtil"
Option Explicit

#If RA_WIN32 Then
  Global Const HKEY_CLASSES_ROOT = &H80000000
#Else
  Global Const HKEY_CLASSES_ROOT = 1
#End If
Global Const REG_SZ = 1

Global Const ERROR_NONE = 0
Global Const ERROR_BADDB = 1
Global Const ERROR_BADKEY = 2
Global Const ERROR_CANTOPEN = 3
Global Const ERROR_CANTREAD = 4
Global Const ERROR_CANTWRITE = 5
Global Const ERROR_OUTOFMEMORY = 6
Global Const ERROR_INVALID_PARAMETER = 7
Global Const ERROR_ACCESS_DENIED = 8
Global Const ERROR_NO_MORE_ITEMS = 259

#If RA_WIN32 Then
  Declare Function RegCloseKey Lib "advapi32.dll" (ByVal hkey As Long) As Long
  Declare Function RegCreateKey Lib "advapi32.dll" Alias "RegCreateKeyA" (ByVal hkey As Long, ByVal szSubKey As String, hkeyResult As Long) As Long
  Declare Function RegDeleteKey Lib "advapi32.dll" Alias "RegDeleteKeyA" (ByVal hkey As Long, ByVal szSubKey As String) As Long
  Declare Function RegEnumKey Lib "advapi32.dll" Alias "RegEnumKeyA" (ByVal hkey As Long, ByVal iSubKey As Long, ByVal szBuffer As String, ByVal cbBuf As Long) As Long
  Declare Function RegOpenKey Lib "advapi32.dll" Alias "RegOpenKeyA" (ByVal hkey As Long, ByVal szSubKey As String, hkeyResult As Long) As Long
  Declare Function RegQueryValue Lib "advapi32.dll" Alias "RegQueryValueA" (ByVal hkey As Long, ByVal szSubKey As String, ByVal szValue As String, chValue As Long) As Long
  Declare Function RegSetValue Lib "advapi32.dll" Alias "RegSetValueA" (ByVal hkey As Long, ByVal szSubKey As String, ByVal fdwType As Long, ByVal lpszValue As String, ByVal cb As Long) As Long
#Else
  Declare Function RegCloseKey Lib "shell.dll" (ByVal hkey As Long) As Long
  Declare Function RegCreateKey Lib "shell.dll" (ByVal hkey As Long, ByVal szSubKey As String, hkeyResult As Long) As Long
  Declare Function RegDeleteKey Lib "shell.dll" (ByVal hkey As Long, ByVal szSubKey As String) As Long
  Declare Function RegEnumKey Lib "shell.dll" (ByVal hkey As Long, ByVal iSubKey As Long, ByVal szBuffer As String, ByVal cbBuf As Long) As Long
  Declare Function RegOpenKey Lib "shell.dll" (ByVal hkey As Long, ByVal szSubKey As String, hkeyResult As Long) As Long
  Declare Function RegQueryValue Lib "shell.dll" (ByVal hkey As Long, ByVal szSubKey As String, ByVal szValue As String, chValue As Long) As Long
  Declare Function RegSetValue Lib "shell.dll" (ByVal hkey As Long, ByVal szSubKey As String, ByVal fdwType As Long, ByVal lpszValue As String, ByVal cb As Long) As Long
#End If

Function DeleteAllKeys() As Long
   Dim lRegErr As Long
   Dim sKey As String

   Do
     lRegErr = EnumKey(HKEY_CLASSES_ROOT, 0, sKey)
     If lRegErr = ERROR_BADKEY Or lRegErr = ERROR_ACCESS_DENIED Or lRegErr = ERROR_NO_MORE_ITEMS Then
       lRegErr = ERROR_NONE
       Exit Do
     ElseIf lRegErr <> ERROR_NONE Then
       Exit Do
     End If
     lRegErr = RegDeleteKey(HKEY_CLASSES_ROOT, sKey)
     If lRegErr <> ERROR_NONE Then
       Exit Do
     End If
   Loop

   DeleteAllKeys = lRegErr

End Function

Function EnumKey(ByVal hkey As Long, ByVal lSubKey As Long, rsSubKey As String) As Long
  Const nBufMax = 1024

  Static sResultBuf As String * nBufMax
  Dim nResultLen As Integer
  Dim lRegErr As Long
  
  lRegErr = RegEnumKey(hkey, lSubKey, sResultBuf, nBufMax)

  If lRegErr = 0 Then
    nResultLen = InStr(sResultBuf, Chr$(0))
    If nResultLen <> 0 Then
      rsSubKey = Left$(sResultBuf, nResultLen - 1)
    Else
      rsSubKey = sResultBuf
    End If
  Else
    rsSubKey = ""
  End If

  EnumKey = lRegErr
End Function

Function QueryValue(ByVal hkey As Long, ByVal sSubKey As String, rsValue As String) As Long
  Const nBufMax = 1024

  Static sResultBuf As String * nBufMax
  Dim nResultLen As Long
  Dim lRegErr As Long

  nResultLen = nBufMax
  lRegErr = RegQueryValue(hkey, sSubKey, sResultBuf, nResultLen)

  If lRegErr = 0 Then
    rsValue = Left$(sResultBuf, nResultLen - 1)
  Else
    rsValue = ""
  End If

  QueryValue = lRegErr
End Function

Function SetValue(ByVal hkey As Long, rsSubKey As String, rsValue As String) As Long

  SetValue = RegSetValue(hkey, rsSubKey, REG_SZ, rsValue, Len(rsValue))

End Function

' Écrit toutes les clés à niveau pour le descripteur de fichier 
' spécifié, ainsi que toutes les sous-clés.
'
' rsRoot est la représentation chaîne du niveau en cours à utiliser. 
Sub WriteKeys(rhkey As Long, fh As Integer, rsRoot As String, rbIHaveSubKeys As Integer)
  Dim i As Integer
  Dim sKey As String
  Dim sSubKey As String
  Dim lRegErr As Long
  Dim lhkSubKey As Long
  Dim sValue As String
  Dim bHasSubKeys As Integer

  i = 0
  rbIHaveSubKeys = False
  Do
    lRegErr = EnumKey(rhkey, i, sSubKey)
    If lRegErr = ERROR_BADKEY Or lRegErr = ERROR_ACCESS_DENIED Or lRegErr = ERROR_NO_MORE_ITEMS Then
      Exit Do
    ElseIf lRegErr <> ERROR_NONE Then
      Exit Sub
    End If

    rbIHaveSubKeys = True

    lRegErr = RegOpenKey(rhkey, sSubKey, lhkSubKey)
    If lRegErr <> ERROR_NONE Then
      Exit Sub
    End If

    sKey = rsRoot + "\" + sSubKey

    WriteKeys lhkSubKey, fh, sKey, bHasSubKeys

    lRegErr = QueryValue(lhkSubKey, "", sValue)
    If lRegErr = ERROR_NONE Then
      If Len(sValue) <> 0 Then
        Print #fh, sKey; " = "; sValue
      ElseIf Not bHasSubKeys Then
        Print #fh, sKey
      End If
    Else
      lRegErr = RegCloseKey(lhkSubKey)
      Exit Sub
    End If

    lRegErr = RegCloseKey(lhkSubKey)
    i = i + 1
  Loop
End Sub

