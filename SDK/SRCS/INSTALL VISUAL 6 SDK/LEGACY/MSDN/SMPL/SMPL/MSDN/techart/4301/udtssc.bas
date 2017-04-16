Attribute VB_Name = "udtScreenSaverConfigModule"
Option Explicit
Type udtScreenSaverConfig
    BackgroundImageFileName As String  'May be Null
    BackgroundImageColor As Long 'May be 0
    MovingImageFileName As String 'May be Null
    ImageSpeed As Integer 'Min 1
    ImageBehaviour As Integer
    PassWord As String
End Type
Dim localUDT As udtScreenSaverConfig

Sub udtScreenSaverConfig_fCacheUDT(MyUDT As udtScreenSaverConfig)
localUDT = MyUDT 'localUDT is DIM as udtScreenSaverConfig in Declatations
End Sub

Sub udtScreenSaverConfig_fRecoverUDT(MyUDT As udtScreenSaverConfig)
MyUDT = localUDT 'localUDT is DIM as udtScreenSaverConfig in Declatations
End Sub
Public Sub udtScreenSaverConfig_Put(MyUDT As udtScreenSaverConfig)
Validate MyUDT  'This is a PRIVATE procedure
On Error Resume Next 'Incase of any bad parameters
    MyApp_PutParm "BackgroundImageFileName", MyUDT.BackgroundImageFileName
    MyApp_PutParm "BackgroundImageColor", Format(MyUDT.BackgroundImageColor, "0")
    MyApp_PutParm "MovingImageFileName", MyUDT.MovingImageFileName
    MyApp_PutParm "ImageSpeed", Format(MyUDT.ImageSpeed, "0")
    MyApp_PutParm "ImageBehaviour", Format(MyUDT.ImageBehaviour, "0")
    MyApp_PutParm "PassWord", MyUDT.PassWord
On Error GoTo 0    'Next subroutine must do its own error handling
End Sub
Public Sub udtScreenSaverConfig_Get(MyUDT As udtScreenSaverConfig)
On Error Resume Next 'Incase of any bad parameters
    MyUDT.BackgroundImageFileName = MyApp_GetParm("BackgroundImageFileName")
    MyUDT.BackgroundImageColor = Val(MyApp_GetParm("BackgroundImageColor"))
    MyUDT.MovingImageFileName = MyApp_GetParm("MovingImageFileName")
    MyUDT.ImageSpeed = Val(MyApp_GetParm("ImageSpeed"))
    MyUDT.ImageBehaviour = Val(MyApp_GetParm("ImageBehaviour"))
    MyUDT.PassWord = MyApp_GetParm("PassWord")
On Error GoTo 0    'Next subroutine must do its own error handling
    Validate MyUDT  'This is a PRIVATE procedure
End Sub
Sub Validate(MyUDT As udtScreenSaverConfig)
On Error Resume Next    'Incase of network problems

'Verify MyUDT.BackgroundImageFileName exists
If Len(MyUDT.BackgroundImageFileName) > 0 Then
    If Len(Dir(MyUDT.BackgroundImageFileName)) = 0 Then
        MyUDT.BackgroundImageFileName = ""  'File missing or not accessible
    End If
End If

'Verify MyUDT.BackgroundImageFileName exists
If Len(MyUDT.MovingImageFileName) > 0 Then
    If Len(Dir(MyUDT.MovingImageFileName)) = 0 Then
        MyUDT.MovingImageFileName = ""  'File missing or not accessible
    End If
End If

On Error GoTo 0
End Sub
Sub udtScreenSaverConfig_Edit(MyUDT As udtScreenSaverConfig, Aform As Form)
   udtScreenSaverConfig_fCacheUDT MyUDT
   Aform.Show 1 'Modal: Any form may be used.
   udtScreenSaverConfig_fRecoverUDT MyUDT
   Validate MyUDT   'This is a PRIVATE procedure
End Sub

