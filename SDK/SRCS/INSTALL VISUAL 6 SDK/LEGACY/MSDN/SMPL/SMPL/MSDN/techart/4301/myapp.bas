Attribute VB_Name = "MyApp"
Option Explicit
#Const Win16 = False
#If Win16 Then
Private Declare Function GetPrivateProfileString Lib "Kernel" (ByVal lpAppName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Integer, ByVal FileName$) As Integer
Private Declare Function WritePrivateProfileString Lib "Kernel" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpString As Any, ByVal FileName$) As Integer
#Else
Private Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpAppName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal FileName$) As Long
Private Declare Function WritePrivateProfileString Lib "kernel32.dll" Alias "WritePrivateProfileStringA" (ByVal lpAppName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal FileName$) As Long
#End If
Const BufferLen = 255   'Max Size of All Init

'VB Specific File
Public Function MyApp_INIFile$()
MyApp_INIFile$ = App.Path + "\" + App.EXEName + ".INI"
End Function
Public Sub MyApp_Init(ByVal SingleInstance%)
If App.PrevInstance And SingleInstance% = 1 Then
    End
End If

End Sub
Public Sub MyApp_About()
Dim A$, CR$
CR$ = Chr$(13) + Chr$(10)
A$ = App.Title + CR$
A$ = A$ + App.FileDescription + CR$
A$ = A$ + App.CompanyName + CR$
A$ = A$ + "Version " + Format(App.Revision, "0") + "." + Format(App.Major, "00") + ":" + Format(App.Minor, "00") + CR$
A$ = A$ + App.LegalCopyright + CR$
A$ = A$ + App.LegalTrademarks + CR$
A$ = A$ + App.Comments
MsgBox A$, 64, "About..." + App.Title
End Sub
Function MyApp_GetParm$(ByVal Parm$)
Dim Buffer As String * BufferLen, RC%
RC% = GetPrivateProfileString("INIT", Parm$, "", Buffer, BufferLen, MyApp_INIFile$())
If RC% = 0 Then
    MyApp_GetParm$ = ""
Else
    MyApp_GetParm$ = Left$(Buffer, RC%)
End If
End Function
Sub MyApp_PutParm(ByVal Parm$, ByVal NewValue$)
Dim RC%
Debug.Print Parm$, NewValue$,
RC% = WritePrivateProfileString("INIT", Parm$, NewValue$, MyApp_INIFile$())
Debug.Print RC%
End Sub
