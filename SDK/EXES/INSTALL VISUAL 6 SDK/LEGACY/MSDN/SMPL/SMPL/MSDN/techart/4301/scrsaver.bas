Attribute VB_Name = "ScreenSaver"
Option Explicit
Public Sub frmScreenSaver_Init()
frmScreenSaver.Show 1 'Modal
End Sub
Public Sub frmScreenSaverConfig_Init()
frmudtScreenSaverConfig.Show 1 'Modal
End Sub
Public Sub frmScreenSaver_Destroy()
Static Once%  'If multiple calls occur we want to discard subsequent until first completes!
If Once% Then Exit Sub
Once% = True
frmScreenSaver.Timer.Enabled = False
frmScreenSaver.bmpFloat.Visible = False
If Len(frmScreenSaver.Tag) > 0 Then
    frmScreenSaverPassWord.Show 1 'Modal
    'NOTE: frmScreenSaver.Tag is set to "" if valid password given!
End If
If Len(frmScreenSaver.Tag) = 0 Then
    Unload frmScreenSaver
    End
End If
frmScreenSaver.Timer.Enabled = True
frmScreenSaver.bmpFloat.Visible = True
DoEvents 'Allow all pending messages to bounce first!
Once% = False
End Sub

