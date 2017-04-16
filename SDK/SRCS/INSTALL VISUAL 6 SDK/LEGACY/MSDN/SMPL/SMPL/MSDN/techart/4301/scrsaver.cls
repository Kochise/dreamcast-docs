VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "ScrSaver"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit
Public Sub Create()
frmScreenSaver.Caption = "LOCKED"
frmScreenSaver_Init
End Sub

Public Sub Destroy()
End
End Sub
Public Sub Status(ByVal Msg$)
frmScreenSaver.Caption = Msg$
frmScreenSaver.Refresh
End Sub
Public Sub SetPassWord(ByVal PW$)
frmScreenSaver.Tag = PW$
End Sub

