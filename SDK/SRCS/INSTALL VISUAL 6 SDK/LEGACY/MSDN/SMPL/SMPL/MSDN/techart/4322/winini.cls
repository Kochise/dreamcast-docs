VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "WININI"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Compare Text
Option Explicit
Private Declare Function GetProfileString Lib "Kernel" (ByVal lpAppName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Integer) As Integer
Private Declare Function WriteProfileString Lib "Kernel" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpString As Any) As Integer
Const BufferLen = 255   'Max Size of All INI Strings

Public Property Get Value(AppName As String, KeyName As String) As String
Dim Buffer As String * BufferLen, RC%, Default As String
MsgBox AppName + KeyName + Buffer, BufferLen
RC% = GetProfileString(AppName, KeyName, Default, Buffer, BufferLen)
Value = Left$(Buffer, RC%)
End Property

Public Property Let Value(AppName As String, KeyName As String, vNewValue$)
Dim RC%
RC% = WriteProfileString(AppName, KeyName, vNewValue$)
End Property

