Attribute VB_Name = "ResourceProperties"
'Copyright (C) 1998 Microsoft Corporation
'All rights reserved.
'
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
'EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
'MERCHANTIBILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
'
'Date    - 02/01/98
'Authors - Robert Coleridge, Steve Kirk, Fred Pace, Kevin Marzec, Dale Smith
'
Option Explicit

Private Const OBJNAME = "Res_h.bas"

Public Enum RES_IDS
    icIDS_USEMSGASERROR = -1
    icIDS_CONF_MSG = 1
    icIDS_CONF_SUBJECT = 2
    'ic_APS_NEXT_RESOURCE_VALUE = 138
    'ic_APS_NEXT_COMMAND_VALUE = 40001
    'ic_APS_NEXT_CONTROL_VALUE = 1000
    'ic_APS_NEXT_SYMED_VALUE = 101
End Enum

Private Function InvokeError(ByVal ErrorID As RES_IDS, Optional ByVal ErrorMsg As String) As Boolean
    Dim sMsg As String
    Dim lErr As Long

    sMsg = Trim$(App.Title) & ":" & OBJNAME
    lErr = Err

    If ErrorID = icIDS_USEMSGASERROR Then
        sMsg = sMsg & " " & ErrorMsg
    Else
        sMsg = sMsg & " " & LoadResString(ErrorID)
    End If

    If Err < vbObjectError Then
        lErr = lErr + vbObjectError
    End If

    Err.Raise lErr, sMsg, Err.Description
End Function
