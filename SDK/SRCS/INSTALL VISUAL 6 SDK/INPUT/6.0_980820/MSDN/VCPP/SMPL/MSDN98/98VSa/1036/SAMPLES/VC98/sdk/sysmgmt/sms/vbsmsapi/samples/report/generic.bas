Attribute VB_Name = "GENERIC"
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  GENERIC.BAS
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

Function NewGenericReportWindow%(hConnect&, ByVal FileSpec$, ErrStr$)
    Dim i%, Ret&, TempPath$, TempSpec$, frm As Form

    'Default return value zero (Failed)
    NewGenericReportWindow% = 0

    'Allocate space for returned string
    TempSpec$ = String$(256, 0)

    'Get a temp file name
    TempPath$ = Environ$("TEMP")
    Ret& = GetTempFileName(TempPath$, "MDB", 0, TempSpec$)
    ErrStr$ = "Could not get a temporary file name for the new report."
    If (Ret& = 0) Then Exit Function

    'Clean up return string of null terminator
    i% = InStr(TempSpec$, Chr$(0))
    If i% = 0 Then i% = Len(TempSpec$) + 1
    TempSpec$ = left$(TempSpec$, i% - 1)

    'Create a temporary document file
    On Error GoTo NewGenericReportWindowErr
    If FileSpec$ > "" Then
        'File Open: so copy the file the user selected
        ErrStr$ = "Could not create a temporary copy of " + FileSpec$ + ".+"
        FileCopy FileSpec$, TempSpec$
    Else
        'File New: so create a new empty document HERE
        ErrStr$ = "Could not create a temporary file for the new report."
    End If
    On Error GoTo 0

    'Pass the new document the file name to use
    InitReporthConnect& = hConnect&
    InitReportFileSpec$ = FileSpec$
    InitReportTempSpec$ = TempSpec$
    If InitReportFileSpec$ <= "" Then InitReportNewNumber% = InitReportNewNumber% + 1

    'Create a new document window
    On Error GoTo NewGenericReportWindowErr
    ErrStr$ = "Could not create site report document window."
    Set frm = New frmGenericReport
    Load frm
    On Error GoTo 0

    'Register document window with MDI
    
    i% = RegisterReportWindow%(frm, ErrStr$)
    If i% <= 0 Then GoTo NewGenericReportWindowErr

    'Show the document window
    frm.Show
    NewGenericReportWindow% = i%
    Exit Function

NewGenericReportWindowErr:
    On Error Resume Next
    If Not frm Is Nothing Then Unload frm
    Kill TempSpec$
    Exit Function
End Function

