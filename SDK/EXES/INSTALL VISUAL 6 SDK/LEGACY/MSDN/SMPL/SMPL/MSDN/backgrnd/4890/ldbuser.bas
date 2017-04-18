Attribute VB_Name = "mLDB"
Declare Function LDBUser_GetUsers Lib "MSLDBUSR.DLL" (lpszUserBuffer() As String, ByVal lpszFilename As String, ByVal nOptions As Long) As Integer
Declare Function LDBUser_GetError Lib "MSLDBUSR.DLL" (ByVal nErrorNo As Long) As String

Public Const OptAllLDBUsers = &H1
Public Const OptLDBLoggedUsers = &H2
Public Const OptLDBCorruptUsers = &H4
Public Const OptLDBUserCount = &H8
Public Const OptLDBUserAuthor = &HB0B

