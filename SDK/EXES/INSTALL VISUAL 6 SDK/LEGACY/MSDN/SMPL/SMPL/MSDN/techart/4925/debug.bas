Attribute VB_Name = "MDebug"
Option Explicit
#If Win32 Then
DefLng A-Z
#Else
DefInt A-Z
#End If

'$ Uses UTILITY.BAS

Private iLogFile As Integer
Private msTemp As Long

' Output flags determine output destination of BugAsserts and messages
''@B BugConst
#Const afLogfile = 1
#Const afMsgBox = 2
#Const afDebugWin = 4
''@E BugConst

' Display appropriate error message, and then stop
' program.  These errors should NOT be possible in
' shipping product.
''@B BugAssert
Sub BugAssert(ByVal fExpression As Variant, _
              Optional sExpression As Variant)
#If afDebug Then
    If fExpression Then Exit Sub
    If IsMissing(sExpression) Then sExpression = sEmpty
    BugMessage "BugAssert failed: " & sExpression
    Stop
#End If
End Sub
''@E BugAssert
    
    
''@B BugMessage
Sub BugMessage(sMsg As String)
#If afDebug And afLogfile Then
    If iLogFile = 0 Then
        iLogFile = FreeFile
        ' Warning: multiple instances can overwrite log file
        Open App.EXEName & ".DBG" For Output Shared As iLogFile
        ' Challenge: Rewrite to give each instance its own log file
    End If
    Print #iLogFile, sMsg
#End If
#If afDebug And afMsgBox Then
    MsgBox sMsg
#End If
#If afDebug And afDebugWin Then
    Debug.Print sMsg
#End If
End Sub
''@E BugMessage

Sub BugTerm()
#If afDebug And afLogfile Then
    ' Close log file
    Close iLogFile
#End If
End Sub

''@B ProfileStart
Sub ProfileStart(msStart As Long)
#If afDebug Then
    msStart = timeGetTime()
#End If
End Sub
''@E ProfileStart

''@B ProfileStop
Sub ProfileStop(msStart As Long, msTiming As Long)
#If afDebug Then
    msTiming = timeGetTime() - msStart
#End If
End Sub
''@E ProfileStop

Sub ProfileStopMessage(sOutput As String, sPrefix As String, _
        msStart As Long, sPost As String)
#If afDebug Then
    msTemp = timeGetTime() - msStart
    ' Return through parameter so that routine can be Sub
    sOutput = sPrefix & Format$(msTemp, "#,###") + " ms " & sPost
#End If
End Sub

''@B BugProfileStop
Sub BugProfileStop(sPrefix As String, msStart As Long)
#If afDebug Then
    msTemp = timeGetTime() - msStart
    BugMessage sPrefix & Format$(msTemp, "#,###") + " ms"
#End If
End Sub
''@E ProfileStop

''@B BugDumpHandle
Sub BugDumpHandle(h)
#If afDebug Then
    Dim c As Long, p As Long, ab() As Byte
    If h Then
        p = GlobalLock(h)
        If p Then
            c = GlobalSize(h)
            If c Then
                ReDim ab(c)
                'CopyMemoryLpToBytes ab(0), p, c
                BugMessage HexDump(ab)
            End If
        End If
        Call GlobalUnlock(h)
    End If
#End If
End Sub
''@E BugDumpHandle

