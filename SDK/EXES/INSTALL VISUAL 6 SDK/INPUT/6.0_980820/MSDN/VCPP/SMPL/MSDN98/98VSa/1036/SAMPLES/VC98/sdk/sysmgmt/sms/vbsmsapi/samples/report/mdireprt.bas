Attribute VB_Name = "basMDIReprt"
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  MDIREPRT.BAS
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

'Types of reports that can be created
Global Const UNKNOWN_REPORT = 0
Global Const SITE_HIERARCHY_REPORT = 1
Global Const MACHINE_GROUP_REPORT = 2
Global Const MACHINE_REPORT = 3
Global Const GENERIC_REPORT = 4

'Size of one pixel in Twips (Set in MDIReport Form Load)
Global X_PIX_SIZE%
Global Y_PIX_SIZE%

'Got this value from outline control error message 32002
Global Const MAX_OUTLINE_ENTRIES = 6536

'Some constants for crystal reports
Global Const CRW_PRINT_TO_WINDOW = 0
Global Const CRW_PRINT_TO_PRINTER = 1
Global Const CRW_PRINT_TO_FILE = 2

'For MDIReport.bas and Report Forms ONLY!
Global Const MAX_REPORT_WINDOWS = 16
Global ReportWindow(1 To MAX_REPORT_WINDOWS) As Form
Global InitReporthConnect&
Global InitReportFileSpec$
Global InitReportTempSpec$
Global InitReportNewNumber%

'For all report forms
Global gbNeedPrintDialog%
Sub FreeReportWindow(frm As Form)
    Dim i%

    For i% = 1 To MAX_REPORT_WINDOWS
        If ReportWindow(i%) Is frm Then
            Set ReportWindow(i%) = Nothing
            Exit For
        End If
    Next i%
End Sub

Sub Main()
    'Initialize the application
    If Init_SMSAPI() Then
        'Put up the main MDI form
        frmMDIReport.Show
    Else
        MsgBox "Error initializing application.  SMS Report can not run.", MB_OK + MB_ICONINFORMATION
    End If
End Sub

Function RegisterReportWindow%(frm As Form, ErrStr$)
    Dim i%

    'Find a free entry in ReportWindow array
    For i% = 1 To MAX_REPORT_WINDOWS
        If ReportWindow(i%) Is Nothing Then
            Set ReportWindow(i%) = frm
            RegisterReportWindow% = i%
            Exit Function
        End If
    Next i%

    'Return value 0 (Failed)
    RegisterReportWindow% = 0
    ErrStr$ = "Too many windows already open."
End Function

