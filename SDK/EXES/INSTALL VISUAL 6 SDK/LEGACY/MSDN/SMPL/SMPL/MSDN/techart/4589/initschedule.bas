Attribute VB_Name = "InitSchedule"
Option Explicit
'The Exchange version of SP732EN.OLB must be installed.
'The version shipped with Windows 95 is broken
Global SPlusApplication As SPL.Application
Global scdSchedule As SPL.Schedule
Sub SchedulePlus_Init()
Dim x As Object
Set SPlusApplication = CreateObject("Schedule+.Application")
If SPlusApplication.LoggedOn = False Then
    SPlusApplication.Logon
End If
Set scdSchedule = SPlusApplication.ScheduleLogged
End Sub
