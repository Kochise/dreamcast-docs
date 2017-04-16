Attribute VB_Name = "basForum"
Option Explicit

Public Enum enumArrayOffsets
    icZero = 0
    icOne = 1
    icTwo = 2
    icThree = 3
    icFour = 4
    icFive = 5
    icSix = 6
End Enum

Public g_oForum     As Object
Public g_lInterval  As Long
Public g_lHandle    As Long

Declare Function SetTimer Lib "user32" (ByVal hWnd As Long, ByVal nIDEvent As Long, ByVal uElapse As Long, ByVal lpTimerFunc As Long) As Long
Declare Function KillTimer Lib "user32" (ByVal hWnd As Long, ByVal nIDEvent As Long) As Long

Public Sub TimerProc(ByVal hWnd As Long, ByVal uMsg As Long, ByVal idEvent As Long, ByVal dwTime As Long)
If g_lHandle Then g_lHandle = KillTimer(0, g_lHandle)
g_oForum.Timer
g_lHandle = SetTimer(0, 0, g_lInterval, AddressOf TimerProc)
End Sub

Sub Main()
g_lInterval = 1000
End Sub
