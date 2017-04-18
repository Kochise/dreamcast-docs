Attribute VB_Name = "ResourceProperties"
'Copyright (C) 1998 Microsoft Corporation
'All rights reserved.
'
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
'EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
'MERCHANTIBILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
'
'Date         - 01/05/98
'Author       - Venu Yerra

Option Explicit

Private Const OBJNAME = "Res_h.bas"

Public Enum RES_IDS
    icIDS_USEMSGASERROR = -1
    icIDS_ERR_USERINIT = 1
    icIDS_ERR_NOREQTEXT = 2
    icIDS_ERR_SENDREQTEXT = 3
    icIDS_ERR_NOREQDESC = 4
    icIDS_ERR_NOLOCATION = 5
    icIDS_ERR_NOPRIORITY = 6
    icIDS_ERR_NOSKILL = 7
    icIDS_ERR_NOLISTITEMS = 8
    icIDS_ERR_NOSELECTION = 9
    icIDS_ERR_CONFNOTSENT = 10
    icIDS_ERR_INSERTFAILED = 11
    icIDS_TT_NEWREQUEST = 12
    icIDS_TT_OPENREQUEST = 13
    icIDS_TT_SENDCONF = 14
    icIDS_TT_EXITAPP = 15
End Enum

'
' This is merely a sample of how a possible error handling routine might look like
'
Private Function InvokeError(ByVal ErrorID As RES_IDS, _
                             Optional ByVal ErrorMsg As String) _
                             As Boolean
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
