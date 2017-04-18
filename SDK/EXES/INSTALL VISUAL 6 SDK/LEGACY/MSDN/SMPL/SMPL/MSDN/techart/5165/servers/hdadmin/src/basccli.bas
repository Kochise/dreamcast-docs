Attribute VB_Name = "basHDAdmin"
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

Public Const scAdmSysParmTypes = "GetSysParmTypes"   'used in GetSysParmTypes method
Public Const scAdmSysParm = "GetSysParm"         'used in GetSysParm method

Public Enum icSysParm
    icSysParmPkId = 0
    icSysParmChangedById = 1
    icSysParmParmTypeId = 2
    icSysParmChangeDate = 3
    icSysParmDescr = 4
    icSysParmSysValue = 5
End Enum

Public Enum icListDomains
    icDomPKId = 0
    icDomDesc = 1
    icDomCode = 2
End Enum

Public Enum icListRequests
    icReqPKId = 0
    icReqReqDate = 1
    icReqResolDate = 2
    icReqLocId = 3
    icReqPriorityId = 4
    icReqResolById = 5
    icReqResolTypeId = 6
    icReqSkillId = 7
    icReqStatusId = 8
    icReqTechId = 9
    icReqTrackingNo = 10
    icReqEmailAlias = 11
    icReqResolOther = 12
    icReqDescr = 13
End Enum

