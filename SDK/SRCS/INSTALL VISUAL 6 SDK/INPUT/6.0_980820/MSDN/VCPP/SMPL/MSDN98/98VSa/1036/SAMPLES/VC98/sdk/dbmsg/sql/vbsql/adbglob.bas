' ===========================================================================
' Global variables specifically for this application:
Global Server$, LoginID$, Password$, DataBase$, Worksta$, AppName$, SQLUser$
Global ShowSql As Integer
Global NEWLINE$

' Global constants for the variable MODE which is used uniquelly in every form
    Global Const SQLREST = 0
    Global Const SQLNEW = 1
    Global Const SQLSHOW = 2

' Memory management functions for determining system information
' displayed in the About Dialog

' Returns the current system configurations flags
Declare Function GetWinFlags Lib "kernel" () As Long

' Returns the number of free bytes in the global heap
Declare Function GetFreeSpace Lib "kernel" (ByVal flag%) As Long

' System configuration flags
Global Const WF_CPU286 = &H2&
Global Const WF_CPU386 = &H4&
Global Const WF_CPU486 = &H8&
Global Const WF_STANDARD = &H10&
Global Const WF_ENHANCED = &H20&
Global Const WF_80x87 = &H400&

' ===========================================================================

Declare Function WinHelp Lib "User" (ByVal hWnd As Integer, ByVal lpHelpFile As String, ByVal wCommand As Integer, dwData As Any) As Integer

