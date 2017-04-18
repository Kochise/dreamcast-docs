Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  PICKPROP.BAS
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

'Global variables (For PICKPROP.FRM use ONLY!)
Global PickPropertiesUserCanceled%
Global PickPropertieshConnect&
Global PickPropertiesMachineGroupID$
Global PickPropertiesIsFiltered%

'Global variables (For use by PICKPROP.FRM and MACHGRP.FRM ONLY!)
Global PickPropertiesList$()
Global PickPropertiesCount%

Function PickProperties% (hConnect&, MachineGroupID$, IsFiltered%, Properties$(), PropertyCount%)
    'Pass parameters to form module
    PickPropertieshConnect& = hConnect&
    PickPropertiesMachineGroupID$ = MachineGroupID$
    ReDim PickPropertiesList$(0 To 0)
    PickPropertiesCount% = 0

    'Show dialog
    frmPickProperties.Show Modal

    'Copy user selections
    If Not PickPropertiesUserCanceled% Then
        ReDim Properties$(0 To PickPropertiesCount%)
        For PropertyCount% = 0 To PickPropertiesCount% - 1
            Properties$(PropertyCount%) = PickPropertiesList$(PropertyCount%)
        Next PropertyCount%

        IsFiltered% = PickPropertiesIsFiltered%
    End If

    'Return user response to dialog
    PickProperties% = Not PickPropertiesUserCanceled%
End Function

