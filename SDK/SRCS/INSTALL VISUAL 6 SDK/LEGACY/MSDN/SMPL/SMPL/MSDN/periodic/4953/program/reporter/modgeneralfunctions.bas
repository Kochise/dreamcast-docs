Attribute VB_Name = "modGeneralFunctions"
Option Explicit

Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

Public Sub CenterChild(oMain As Form, oChild As Form)
'Center Child in parent

    oChild.Top = (oMain.ScaleHeight - oChild.Height) / 2
    oChild.Left = (oMain.ScaleWidth - oChild.Width) / 2

End Sub


