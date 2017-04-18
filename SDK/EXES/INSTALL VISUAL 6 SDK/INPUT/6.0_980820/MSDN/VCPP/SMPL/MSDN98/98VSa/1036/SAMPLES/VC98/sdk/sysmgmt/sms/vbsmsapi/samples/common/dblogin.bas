Attribute VB_Name = "basDBLOGIN"
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  DBLOGIN.BAS
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

'Global database variables (For DBLOGIN.FRM use ONLY!)
Global OpenDBInfo As SQL_CONNECT_PARAMS
Global OpenDBUserCanceled%
Global OpenDBConnect&

Function DBLogin%(DbInfo As SQL_CONNECT_PARAMS, hConnect&)
    
    'Copy values to OpenDB form
    OpenDBInfo.ds = DbInfo.ds
    OpenDBInfo.pszServer = DbInfo.pszServer
    OpenDBInfo.pszUserName = DbInfo.pszUserName
    OpenDBInfo.pszPasswd = DbInfo.pszPasswd
    OpenDBInfo.pszDbName = DbInfo.pszDbName
    OpenDBInfo.pszKey = DbInfo.pszKey
    OpenDBInfo.pFunc = DbInfo.pFunc

    OpenDBConnect& = hConnect&
    
    frmDBLogin.Show MODAL

    If Not OpenDBUserCanceled% Then
        'Set return values
        DbInfo.ds = OpenDBInfo.ds
        DbInfo.pszServer = OpenDBInfo.pszServer
        DbInfo.pszUserName = OpenDBInfo.pszUserName
        DbInfo.pszPasswd = OpenDBInfo.pszPasswd
        DbInfo.pszDbName = OpenDBInfo.pszDbName
        DbInfo.pszKey = OpenDBInfo.pszKey
        DbInfo.pFunc = OpenDBInfo.pFunc

        hConnect& = OpenDBConnect&
    End If

    DBLogin% = Not OpenDBUserCanceled%
End Function

Sub DBLogout(hConnect&)
    Dim lRet&
    
    If hConnect& Then
        'No sense checking this for an error
        lRet& = SmsDataSourceDisconnect&(hConnect&)
    End If
End Sub

