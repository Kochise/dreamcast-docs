Attribute VB_Name = "AppScreenSaver"
Option Explicit

Public Sub AppScreenSaver_Init()
MyApp_Init 1    'Single Instance Only
If InStr(LCase$(Command$), "s") Then 'Contains {'s','S'}?
    Call frmScreenSaver_Init
Else
    Dim MyUDT As udtScreenSaverConfig  'Create the object
    udtScreenSaverConfig_Get MyUDT
    udtScreenSaverConfig_Edit MyUDT, frmudtScreenSaverConfig
    End
End If
End Sub

