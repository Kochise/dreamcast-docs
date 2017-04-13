Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  STATBAR.BAS
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

Dim CurrentStatusBar As Label

Function GetStatBarMsg$ ()
    If CurrentStatusBar Is Nothing Then Exit Function
    GetStatBarMsg$ = CurrentStatusBar
End Function

Sub SetCurrentStatusBar (Bar As Label)
    Set CurrentStatusBar = Bar
End Sub

Sub SetStatBarMsg (msg As String)
    ' displays message on status bar
    If CurrentStatusBar Is Nothing Then Exit Sub
    If msg = "" Then
        CurrentStatusBar = "Ready"
    Else
        CurrentStatusBar = msg
    End If
    CurrentStatusBar.Refresh
End Sub

