Attribute VB_Name = "Startup"
Option Explicit

Sub Main()
    If App.StartMode <> 1 Then
        'OLE SERVER
    Else
        AppScreenSaver_Init
    End If
End Sub
Public Sub ShowFileInPictureBox(ByVal FileName$, bmpCtl As Control, mciCtl As Control)
If Len(FileName$) Then
    Select Case LCase(Right(FileName$, 3))
    Case "bmp", "ico", "wmf"
        bmpCtl.picture = LoadPicture(FileName)
    Case "avi"
        bmpCtl.AutoSize = True
        bmpCtl.picture = LoadPicture("")
        mciCtl.hWndDisplay = bmpCtl.hWnd
        mciCtl.Notify = False
        mciCtl.Wait = True
        mciCtl.Shareable = False
        mciCtl.DeviceType = "AVIVideo"
        mciCtl.FileName = FileName$
        bmpCtl.AutoSize = False
        mciCtl.Command = "Open"
        bmpCtl.AutoSize = True
        mciCtl.Command = "Play"
    Case Else 'Don't know -- don't use.

    End Select
Else
    'Keep preloaded image!
End If

End Sub
