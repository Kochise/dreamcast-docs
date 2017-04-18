Attribute VB_Name = "basCHDClient"
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

'All the below constants are used in calling different methods on CAdmin
Public Const scConfirmRes = "ConfirmResolution"      'Used in ConfirmResolution
Public Const scDenyRes = "DenyResolution"            'Used in DenyResolution
Public Const scReAssignReq = "ReAssignReq"           'Used in ReAssignReq method
Public Const scClaimReq = "ClaimRequest"             'Used in ClaimRequest method
Public Const scResolveReq = "ResolveRequest"         'Used in ResolveReq method
Public Const scUnclaimReq = "UnclaimRequest"         'used in UnclaimRequest method
Public Const scWorkReq = "WorkRequest"               'Used in WorkRequest method
Public Const scInsertReq = "InsertRequest"           'Used in InsertRequest method
Public Const scSendTextReq = "SendTextRequest"       'Used in SendTextRequest method
Public Const scSendVoiceReq = "SendVoiceRequest"     'used in SendVoiceRequest method
Public Const scSendStdTxtResp = "SendStdTxtResponse"   'used in SendStdTxtResponse method
Public Const scSendTxtResp = "SendTxtResponse"       'used in SendTextResponse method
Public Const scSendStdVoiceResp = "SendStdVoiceResponse " 'used in SendSVoiceResponse method"
Public Const scSendVoiceResp = "SendVoiceResponse"   'used in SendVoiceResponse method
Public Const scAdmSkills = "GetSkills"               'used in GetSkills method
Public Const scAdmLocs = "GetLocations"              'used in GetLocations method
Public Const scAdmTechs = "GetTechnicians"           'used in GetTechnicians method
Public Const scAdmPriorities = "GetPriorities"       'used in GetPriorities method
Public Const scAdmReqStatus = "GetReqStatus"         'used in GetReqStatus method
Public Const scAdmReqDetTypes = "GetReqDetTypes"     'used in GetReqDetTypes method
Public Const scAdmStdRespCol = "GetStdRespCols"

'This enumeration represents the structure of the data as it comes from the
'DB when a Request record is retrieved

Public Enum hdRequest
    icReqPkID = 0
    icReqDate = 1
    icReqResDate = 2
    icReqLocId = 3
    icReqPriorId = 4
    icReqResolBy = 5
    icReqResolType = 6
    icReqSkillId = 7
    icReqStatusId = 8
    icReqTechId = 9
    icReqTrackNo = 10
    icReqEAlias = 11
    icReqResOther = 12
    icReqDesc = 13
End Enum

'This enumeration represents the structure of the data as it comes from the
'DB when a Technician record is retrieved

Public Enum hdTech
    icTechPkId = 0
    icTechLocId = 1
    icTechSkillId = 2
    icAlias = 3
End Enum

'This enumeration represents the structure of the data as it comes from the
'DB when a Request Detail record is retrieved
Public Enum hdReqDetail
    icRDPKId = 0
    icRDDate = 1
    icRDTypeId = 2
    icRDTechId = 3
    icRDDetMsg = 4
End Enum

'This enumeration represents the structure of the data as it comes from the
'DB when a Location record is retrieved
Public Enum hdListDomains
    icDomPKId = 0
    icDomDesc = 1
    icDomCode = 2
End Enum

'This enumeration represents the structure of the data as it comes from the
'DB when a standard text or voice response record is retrieved
Public Enum hdListStdResp
    icStdRespPKId = 0
    icStdRespDesc = 1
    icStdRespCode = 2
    icStdRespMsg = 3
End Enum

