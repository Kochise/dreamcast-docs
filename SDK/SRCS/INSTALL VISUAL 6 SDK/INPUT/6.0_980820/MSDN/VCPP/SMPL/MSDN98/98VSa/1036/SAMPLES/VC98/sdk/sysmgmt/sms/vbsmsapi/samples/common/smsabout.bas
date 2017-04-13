Attribute VB_Name = "basSMSABOUT"
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  STATBAR.BAS
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   6/13/95      Created.
'//
'//****************************************************************************

'For use by frmSMSAbout ONLY!
Global SMSAboutCaption$, SMSAboutInfo$

Sub SmsAbout(Caption$, Info$)
    SMSAboutCaption$ = Caption$
    SMSAboutInfo$ = Info$

    frmSMSAbout.Show MODAL
End Sub

