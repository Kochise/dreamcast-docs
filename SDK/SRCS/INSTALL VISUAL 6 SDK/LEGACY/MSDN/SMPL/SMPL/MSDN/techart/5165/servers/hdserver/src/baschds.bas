Attribute VB_Name = "basCHDServer"
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

Public Const scExecute = "Execute "

Public Const scDel_Domain = "pcDel_Domain"
Public Const scDel_Tech = "pcDel_technician"

Public Const scDomainAuditType = "tbAuditType"
Public Const scDomainLocation = "tbLocation"
Public Const scDomainPriority = "tbPriority"
Public Const scDomainReqDetType = "tbReqDetType"
Public Const scDomainReqStatus = "tbStatus"
Public Const scDomainResolType = "tbResolType"
Public Const scDomainSkill = "tbSkill"
Public Const scDomainSysParmType = "tbSysParmType"
Public Const scDomainTechStat = "tbTechStat"

Public Const scGet_ReqDet = "pcGet_ReqDet"
Public Const scGet_Request = "pcGet_Req"
Public Const scGet_Tech = "pcGet_Tech"
Public Const scGet_FirstSnapshotdate = "pcGet_FirstSnapshotDate"
Public Const scGet_LastSnapshotdate = "pcGet_LastSnapshotDate"
Public Const scGet_SnapshotIDs = "pcGet_SnapshotIDs"

Public Const scIns_Domain = "pcIns_Domain"
Public Const scIns_Tech = "pcIns_technician"

Public Const scLvw_Locations = "pcLvw_Locations"
Public Const scLvw_Priorities = "pcLvw_Priority"
Public Const scLvw_ReqDets = "pcLvw_ReqDets"
Public Const scLvw_ReqDetTypes = "pcLvw_ReqDetTypes"
Public Const scLvw_ReqStatus = "pcLvw_Status"
Public Const scLvw_Requests = "pcLvw_Requests"
Public Const scLvw_Snapshot = "pcLvw_Snapshot"
Public Const scLvw_SnapshotRange = "pcLvw_SnapshotRange"
Public Const scLvw_Skills = "pcLvw_Skills"
Public Const scLvw_StdTxtResp = "pcLvw_StdTxtResp"
Public Const scLvw_StdVoiceResp = "pcLvw_StdVoiceResp"
Public Const scLvw_SysParms = "pcLvw_SysParms"
Public Const scLvw_SysParmType = "pcLvw_SysParmType"
Public Const scLvw_Techs = "pcLvw_Techs"
Public Const scLvw_TechStat = "pcLvw_TechStat"

Public Const scClaimReq = "pcClaim_Req"
Public Const scCommenceReq = "pcCommence_Req"
Public Const scInsertMessage = "pcIns_Msg"
Public Const scInsertReq = "pcIns_Req"
Public Const scLogoffTech = "pcLogoff_Tech"
Public Const scLogonTech = "pcLogon_Tech"
Public Const scNotConfRes = "pcNotConfRes"
Public Const scConfirmRes = "pcResConfirm"

Public Const scUpd_Domain = "pcUpd_domain"
Public Const scUpd_Tech = "pcUpd_technician"

Public Const scReAssignReq = "pcReAssign_Req"
Public Const scSaveConversationText = "pcSaveConversationText"
Public Const scSendStdTextResp = "pcSendStdTextResp"
Public Const scSendStdVoiceResp = "pcSendStdVoiceResp"
Public Const scSendTextReq = "pcSendTextReq"
Public Const scSendTxtResp = "pcSendTextResp"
Public Const scSendVoiceReq = "pcSendVoiceReq"
Public Const scSendVoiceResp = "pcSendVoiceResp"
Public Const scSubmitReq = "pcSubmit_Req"
Public Const scUnclaimReq = "pcUnclaim_Req"

'=======================================================================
'Synopsis:              This function adds a required second qoute to
'                       a string used in a stored procedure.
'Function input:        String to be converted.
'Function output:       Returns converted string.
'=======================================================================
Public Function DoQuotes(ByVal sData As String) As String
If Len(sData) = 0 Then Exit Function
Dim iLast As Integer
Dim sPart As String

'Find first single quote
iLast = InStr(sData, Chr$(39))
While iLast
    'Build the string from the left, include two single quotes
    sPart = sPart & Left$(sData, iLast - 1) & Chr$(39) & Chr$(39)
    'Truncate the working string from the right
    sData = Right$(sData, Len(sData) - iLast)
    'Find next single quote in the remainder
    iLast = InStr(sData, Chr$(39))
Wend
'Put any remaining string data on the end
sData = sPart & sData
'Return valid string
DoQuotes = Trim$(sData)
End Function

