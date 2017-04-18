Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  NEWREPRT.BAS
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

'Global database variables (For NEWREPRT.FRM use ONLY!)
Global NewReportUserCanceled%
Global NewReportSelection%

Function NewReport% (Selection%)
    frmNewReport.Show MODAL

    If Not NewReportUserCanceled% Then
        Selection% = NewReportSelection%
    End If

    NewReport% = Not NewReportUserCanceled%
End Function

