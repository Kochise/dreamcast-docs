Attribute VB_Name = "basMain"
'Copyright (C) 1998 Microsoft Corporation
'All rights reserved.
'
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
'EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
'MERCHANTIBILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
'
'Date         - 01/05/98
'Author       - Venu Yerra
'
Option Explicit
'=======================================================================
'   HelpDesk project - Visual Basic Client
'   Microsoft Corporation
'   Date : 14 October 1997
'   Synopsis :  This is Public BAS for constants to be used in Technician
'               client
'
'=======================================================================

Private Const OBJNAME = "basMain"
Global Const scSTATUS_UNCLAIM = "UNCLAIM"
Global Const scSTATUS_CLAIMED = "CLAIMED"
Global Const scSTATUS_INPROG = "INPROG"
Global Const scSTATUS_PENDING = "PENDING"

Private Declare Function GetUserName Lib "advapi32.dll" Alias "GetUserNameA" (ByVal lpbuffer As String, nSize As Long) As Long

'Public objects
Public g_oAdmin      As hdclient.CAdmin
Public g_oHDExt      As hdextlib.CHDExt
Public g_oTech       As hdclient.CTech
Public g_frmMainForm As frmTechReq

'Declare error constants
Public Const ERR_LISTEMPTY = "No requests available"
Public Const ERR_CLAIMFAILED = "Request Claim failed"
Public Const ERR_COMMENCEFAILED = "Request  commencement failed"
Public Const ERR_UNCLAIMFAILED = "Request Unclaim failed"
Public Const ERR_RESOLVEFAILED = "Request Resolve failed"
Public Const ERR_REQUESTOBJNOTSET = "Request was not selected to show Request Details"
Public Const ERR_TECHNOTFOUND = "Technician not found"
Public Const ERR_NORESPTEXT = "Response text not entered"
Public Const ERR_SENDRESPTEXT = "Error sending Response text"


'Used in Standard Responses screen
Enum RespType
    icText = 1
    icVoice = 2
End Enum

Public Function Initialize(ByVal sUser As String) As Boolean

    Initialize = False
    Set g_oAdmin = New hdclient.CAdmin
    Set g_oTech = g_oAdmin.GetTechByAlias(sUser)
    If g_oTech Is Nothing Then
        Set g_oAdmin = Nothing
    Else
        If g_oAdmin.Init(sUser, icTECH_LOGGED_IN) Then
            Set g_frmMainForm = New frmTechReq
            Load g_frmMainForm
            Initialize = True
        Else
            Set g_oTech = Nothing
            Set g_oAdmin = Nothing
        End If
    End If

End Function


Public Sub Terminate()
    g_oTech.Term
    Set g_oTech = Nothing
    
    g_oAdmin.Term
    Set g_oAdmin = Nothing
    
    Set g_oHDExt = Nothing
End Sub

Sub Main()
    Dim sBuffer As String
    Dim lSize As Long
    Dim sUser As String
    Dim cTags As Collection

    'instantiate Extension library
    Set g_oHDExt = New hdextlib.CHDExt
    
    'get user name
    sBuffer = Space$(255)
    lSize = Len(sBuffer)
    Call GetUserName(sBuffer, lSize)
    If lSize > 0 Then
        sUser = Left$(sBuffer, lSize - 1)
    Else
        MsgBox ERR_TECHNOTFOUND
        End
    End If
    
    'Adjust splash screen and show it
    frmSplash.Show
    Set cTags = New Collection
    cTags.Add sUser, "USER"
    Set cTags = Nothing
    frmSplash.Refresh
    DoEvents

    'initialize for logged-in user. If valid then do main screen, else fail
    If basMain.Initialize(sUser) Then
        Unload frmSplash
        g_frmMainForm.Show
    Else
        MsgBox ERR_TECHNOTFOUND
        Unload frmSplash
        End
    End If
    
End Sub


