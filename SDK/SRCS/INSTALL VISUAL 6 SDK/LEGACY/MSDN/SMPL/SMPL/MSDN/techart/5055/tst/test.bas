Attribute VB_Name = "Module1"

Sub OldMain()
    Dim oService As New CService
    Dim oServiceAdmin As New CServiceAdmin
    Debug.Print CStr(oServiceAdmin.Services.Count) & " Services found"
    Debug.Print "______________________________________________________________"
    For Each oService In oServiceAdmin.Services
        Debug.Print "ServiceName" & Chr$(9) & oService.ServiceName
        Debug.Print Chr$(9) & "DisplayName" & Chr$(9) & oService.DisplayName
        Debug.Print Chr$(9) & "OwnProcess" & Chr$(9) & CStr(oService.OwnProcess)
        Debug.Print Chr$(9) & "ShareProcess" & Chr$(9) & CStr(oService.ShareProcess)
        Debug.Print Chr$(9) & "DeviceDriver" & Chr$(9) & CStr(oService.DeviceDriver)
        Debug.Print Chr$(9) & "FileSystemDriver" & Chr$(9) & CStr(oService.FileSystemDriver)
        Debug.Print Chr$(9) & "InteractsWithDesktop" & Chr$(9) & CStr(oService.InteractsWithDesktop)
        Debug.Print Chr$(9) & "Stopped" & Chr$(9) & CStr(oService.Stopped)
        Debug.Print Chr$(9) & "StartPending" & Chr$(9) & CStr(oService.StartPending)
        Debug.Print Chr$(9) & "StopPending" & Chr$(9) & CStr(oService.StopPending)
        Debug.Print Chr$(9) & "Running" & Chr$(9) & CStr(oService.Running)
        Debug.Print Chr$(9) & "ContinuePending" & Chr$(9) & CStr(oService.ContinuePending)
        Debug.Print Chr$(9) & "PausePending" & Chr$(9) & CStr(oService.PausePending)
        Debug.Print Chr$(9) & "Paused" & Chr$(9) & CStr(oService.Paused)
        Debug.Print Chr$(9) & "AcceptStop" & Chr$(9) & CStr(oService.AcceptStop)
        Debug.Print Chr$(9) & "AcceptPauseContinue" & Chr$(9) & CStr(oService.AcceptPauseContinue)
        Debug.Print Chr$(9) & "AcceptShutdown" & Chr$(9) & CStr(oService.AcceptShutdown)
        Debug.Print Chr$(9) & "Win32ExitCode" & Chr$(9) & CStr(oService.Win32ExitCode)
        Debug.Print Chr$(9) & "ServiceSpecificExitCode" & Chr$(9) & CStr(oService.ServiceSpecificExitCode)
        Debug.Print Chr$(9) & "CheckPoint" & Chr$(9) & CStr(oService.CheckPoint)
        Debug.Print Chr$(9) & "WaitHint" & Chr$(9) & CStr(oService.WaitHint)
        Debug.Print "Press F5 to continue"
        Stop
    Next
    Debug.Print "______________________________________________________________"
    Debug.Print "Finished"
    Stop
End Sub
