Type tagTimerInfo
    dwSize As Long
    dwStart As Long
    dwVM  As Long
End Type
Declare Function TimerCount Lib "ToolHelp" (tagTimerInfo As Any) As Integer
Declare Function timegettime Lib "MMSYSTEM.DLL" () As Long

Sub Main ()
Dim i As Integer, b    As Integer, j As Integer
Dim TimerInfo As tagTimerInfo
TimerInfo.dwSize = Len(TimerInfo)

'Find out how many milliseconds to execute 1000 times using the C-like method
t1& = Stopwatch_time()
For j = 1 To 1000
    rc% = TimerCount(TimerInfo)
    T& = TimerInfo.dwVM
Next j
t2& = Stopwatch_time()         'Difference between this and t1& is millseconds to
'Find out how many milliseconds to execute 1000 times using the VB-native method approach
For j = 1 To 1000
    T& = Stopwatch_time()
Next j
t3& = Stopwatch_time() 'Difference between this and t2& is millseconds to execute
For j = 1 To 1000
    
Next j
t4& = Stopwatch_time()
For j = 1 To 1000
    T& = timegettime()
Next j
t5& = Stopwatch_time()
MsgBox "C-Like Method:" & Str$(t2& - t1&) & "  VB-Native Method:" & Str$(t3& - t2&) & "  Loop time:" & Str$(t4& - t3&) & " timeGetTime:" & Str$(t5& - t4&) & ""
End

End Sub

