Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  PICKMACH.BAS
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

'Global variables (For PICKMACH.FRM use ONLY!)
Global PickMachineGroupsUserCanceled%
Global PickMachineGroupshConnect&
Global PickMachineGroupsDB As Database

'Global variables (For use by PICKMACH.FRM ONLY!)
Global MachineGroupPicked$

Function PickMachineGroups% (hConnect&, db As Database, MachineGroupID$)
    'Pass parameters to form module
    PickMachineGroupshConnect& = hConnect&
    Set PickMachineGroupsDB = db
    MachineGroupPicked$ = ""

    'Show dialog
    frmPickMachineGroups.Show Modal

    'Don't leave behind any references to data base object
    Set PickMachineGroupsDB = Nothing

    'Return user response to dialog
    If Not PickMachineGroupsUserCanceled% Then MachineGroupID$ = MachineGroupPicked$
    PickMachineGroups% = Not PickMachineGroupsUserCanceled%
End Function

