VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CTrans"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
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

Private Const OBJNAME = "CTrans"

Private Const scConnect = "helpdesk"    'name of the DSN, ASSUMES TRUSTED CONNECTION!

Public Enum hdDOMAINS                   'Used in GetDomain method
    icAUDIT_TYPE = 0
    icLOCATION = 1
    icSKILL = 2
    icPRIORITY = 3
    icREQ_STATUS = 4
    icREQ_DET_TYPE = 5
    icSYS_PARM_TYPE = 6
    icRESOL_TYPE = 7
    icTECH_STATUS = 8
End Enum

Public Enum hdTECHS                     'Used in GetTechs method
    icALL_TECHS = 0
    icWORKING_TECHS = 1
End Enum

Public Enum hdSNAPSHOT
    icFIRST_DATE = 1
    icLAST_DATE = 2
End Enum

'=======================================================================
'Synopsis:              Function updates status in Request table in DB
'                       for the request ID passed.
'Function input:        Technician ID claiming the request
'                       Request ID being claimed
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function ClaimRequest(ByVal lReqId As Long, ByVal lTechId As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

ClaimRequest = False

'Build query string
sQry = scExecute & scClaimReq
sQry = sQry & " @ReqId = " & lReqId
sQry = sQry & scSpaceCommaSpace
sQry = sQry & " @TechId = " & lTechId

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'Call the method on the CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    ClaimRequest = True
End If
Set oExec = Nothing             'clear the object
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function updates status to RESOLVD and ResolType to CONFREC
'                       in Request table in DB for the request ID passed
'Function input:        Request ID
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function ConfirmResolution(ByVal lReqId As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

ConfirmResolution = False

'Build query string
sQry = scExecute & scConfirmRes
sQry = sQry & " @ReqId = " & lReqId

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    ConfirmResolution = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function deletes a member in a domain table in DB
'Function input:        icDomain selects domain table
'                       sCode is Code value for domein member
'Function output:       Returns TRUE if the function succeeds
'NOTE! This routine may fail due to referential integrity by the db
'=======================================================================
Public Function DeleteDomainMember(ByVal icDomain As hdDOMAINS, ByVal sCode As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

DeleteDomainMember = False

'Build query string
Select Case icDomain
    Case hdDOMAINS.icAUDIT_TYPE
        sQry = scExecute & scDel_Domain & " @Domain = " & scSQ & scDomainAuditType & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icLOCATION
        sQry = scExecute & scDel_Domain & " @Domain = " & scSQ & scDomainLocation & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icPRIORITY
        sQry = scExecute & scDel_Domain & " @Domain = " & scSQ & scDomainPriority & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icREQ_DET_TYPE
        sQry = scExecute & scDel_Domain & " @Domain = " & scSQ & scDomainReqDetType & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icREQ_STATUS
        sQry = scExecute & scDel_Domain & " @Domain = " & scSQ & scDomainReqStatus & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icRESOL_TYPE
        sQry = scExecute & scDel_Domain & " @Domain = " & scSQ & scDomainResolType & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icSKILL
        sQry = scExecute & scDel_Domain & " @Domain = " & scSQ & scDomainSkill & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icSYS_PARM_TYPE
        sQry = scExecute & scDel_Domain & " @Domain = " & scSQ & scDomainSysParmType & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icTECH_STATUS
        sQry = scExecute & scDel_Domain & " @Domain = " & scSQ & scDomainTechStat & scSQ & scSpaceCommaSpace
End Select
sQry = sQry & " @Code = " & scSQ & DoQuotes(sCode) & scSQ

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    DeleteDomainMember = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function deletes a record from the technician table in db
'Function input:        EMail Alias of technicicn
'Function output:       Returns TRUE if the function succeeds.
'NOTE! This routine may fail due to referential integrity by the db
'=======================================================================
Public Function DeleteTechnician(ByVal sEAlias As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sData()     As String
Dim sQry        As String

DeleteTechnician = False

'Build query string
sQry = scExecute & scDel_Tech
sQry = sQry & " @EmailAlias = " & scSQ & DoQuotes(sEAlias) & scSQ

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    DeleteTechnician = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function updates status in Request table in DB
'                       from PENDING to INPROG for the request ID passed
'Function input:        Request ID
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function DenyResolution(ByVal lReqId As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

DenyResolution = False

'Build query string
sQry = scExecute & scNotConfRes
sQry = sQry & " @ReqId = " & lReqId

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    DenyResolution = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function returns list of members of specified domain.
'
'Function input:        domain id from hdDOMAINS
'                       A string array which gets filled up with data
'Function output:       Returns TRUE if the function succeeds.
'                       The data is returned in string array
'=======================================================================
Public Function GetDomain(ByVal iDomain As hdDOMAINS, sData() As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

GetDomain = False

'Build query string
Select Case iDomain
Case hdDOMAINS.icLOCATION
    sQry = scExecute & scLvw_Locations
Case hdDOMAINS.icSKILL
    sQry = scExecute & scLvw_Skills
Case hdDOMAINS.icPRIORITY
    sQry = scExecute & scLvw_Priorities
Case hdDOMAINS.icREQ_STATUS
    sQry = scExecute & scLvw_ReqStatus
Case hdDOMAINS.icREQ_DET_TYPE
    sQry = scExecute & scLvw_ReqDetTypes
Case hdDOMAINS.icSYS_PARM_TYPE
    sQry = scExecute & scLvw_SysParmType
Case hdDOMAINS.icTECH_STATUS
    sQry = scExecute & scLvw_TechStat
Case Else
    'uh-oh
End Select

'create a new object context
#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If
'Call the method on the CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    GetDomain = True
End If
Set oExec = Nothing             'clear class
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function returns details of request from tbReqDet
'                       table in DB for ReqDetId passed
'Function input:        Req Det ID whose detail is required
'                       A string array which gets filled up with data
'Function output:       Returns TRUE if the function succeeds.
'                       The data is returned in string array
'=======================================================================
Public Function GetReqDetail(ByVal lReqDetId As Long, sData() As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

GetReqDetail = False

'Build query string
sQry = scExecute & scGet_ReqDet
sQry = sQry & " @ReqDetId = " & lReqDetId

#If bUseMTS Then
    'create object context
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'Call method on CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    GetReqDetail = True
End If

Set oExec = Nothing             'clear the class

#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function returns list of request details of a
'                       specific request from tbReqDet
'Function input:        Req ID whose list of detail records are required
'                       A string array which gets filled up with data
'Function output:       Returns TRUE if the function succeeds.
'                       The data is returned in string array
'=======================================================================
Public Function GetReqDetails(ByVal lReqId As Long, sData() As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

GetReqDetails = False

'Build query string
sQry = scExecute & scLvw_ReqDets
sQry = sQry & " @ReqId = " & lReqId

#If bUseMTS Then
    'Create a context object
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    GetReqDetails = True
End If

Set oExec = Nothing             'clear the class

#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function returns data of the request from DB
'                       for the supplied request ID or Tracking No.
'Function input:        A string array which gets filled up with data
'                       (Optional) Request ID of request to return
'                       (Optional) Tracking No of request to return
'Function output:       Returns TRUE if the function succeeds.
'                       The data is returned in string array
'=======================================================================
Public Function GetRequest(sData() As String, Optional ByVal lReqId As Long, Optional ByVal lTrackNo As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

GetRequest = False

'Build query string
If lReqId Then
    sQry = scExecute & scGet_Request
    sQry = sQry & " @ReqId = " & lReqId
End If
If lTrackNo Then
    sQry = scExecute & scGet_Request
    sQry = sQry & " @TrackingNo = " & lTrackNo
End If

#If bUseMTS Then
    'create object context
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'Call the method on the CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    GetRequest = True
End If

Set oExec = Nothing             'clear class
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function returns list of requests assigned to a
'                       technician
'Function input:        Technician ID whose requests are required
'                       A string array which gets filled up with data
'Function output:       Returns TRUE if the function succeeds.
'                       The data is returned in string array
'=======================================================================
Public Function GetRequests(ByVal lTechId As Long, sData() As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

GetRequests = False

'Build query string
sQry = scExecute & scLvw_Requests
If lTechId Then
    sQry = sQry & " @TechId = " & lTechId
End If

#If bUseMTS Then
    'create object context
    Set oCtxt = GetObjectContext()
    'new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'Call the method on the CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    GetRequests = True
End If

Set oExec = Nothing             'clear the class

#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function returns a date/time representing the
'                       extent of system snapshots stored in the db
'Function input:        iType - Member of enum hdSnapshot
'                           (icFirst) returns date/time of first snapshot in db
'                           (icLast)  returns date/time of last snapshot in db
'                       A string array which gets filled up with data
'Function output:       Returns TRUE if the function succeeds.
'                       The data is returned in string array
'=======================================================================
Public Function GetSnapshotDate(ByVal iType As hdSNAPSHOT, sData() As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

GetSnapshotDate = False

'Build query string
Select Case iType
Case hdSNAPSHOT.icFIRST_DATE
    sQry = scExecute & scGet_FirstSnapshotdate
Case hdSNAPSHOT.icLAST_DATE
    sQry = scExecute & scGet_LastSnapshotdate
Case Else
    'uh-oh
End Select

'create a new object context
#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If
'Call the method on the CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    GetSnapshotDate = True
End If
Set oExec = Nothing             'clear class
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If
End Function

'=======================================================================
'Synopsis:              Function returns a list of snapshot IDs for a contiguous
'                       range extending one snapshot beyond the supplied dates
'Function input:        First date in range
'                       Last date in range
'                       A string array which gets filled up with data
'Function output:       Returns TRUE if the function succeeds.
'                       The data is returned in string array
'=======================================================================
Public Function GetSnapshotIDs(ByVal dFirst As Date, ByVal dLast As Date, sData) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

GetSnapshotIDs = False

'Build query string
sQry = scExecute & scGet_SnapshotIDs
sQry = sQry & " @StartDate = " & scSQ & CStr(dFirst) & scSQ & scSpaceCommaSpace
sQry = sQry & " @EndDate = " & scSQ & CStr(dLast) & scSQ

'create a new object context
#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If
'Call the method on the CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    GetSnapshotIDs = True
End If
Set oExec = Nothing             'clear class
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If
End Function

'=======================================================================
'Synopsis:              Function returns a contiguous range of system snapshots
'Function input:        A string array which gets filled up with data
'                       (Optional) Id of first snapshot - defaults is first in db
'                       (Optional) Id of last snapshot - defaults is last in db
'Function output:       Returns TRUE if the function succeeds.
'                       The data is returned in string array
'=======================================================================
Public Function GetSnapshotRange(sData() As String, Optional lFirstId As Long, Optional lLastId As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

GetSnapshotRange = False

'Build query string
If lFirstId Then
    If Len(sQry) Then sQry = sQry & scSpaceCommaSpace
    sQry = sQry & " @FirstId = " & lFirstId
End If
If lLastId Then
    If Len(sQry) Then sQry = sQry & scSpaceCommaSpace
    sQry = sQry & " @LastId = " & lLastId
End If
sQry = scExecute & scLvw_SnapshotRange & sQry

'create a new object context
#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If
'Call the method on the CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    GetSnapshotRange = True
End If
Set oExec = Nothing             'clear class
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function returns a list of standard text responses
'Function input:        A string array which gets filled up with data
'Function output:       Returns TRUE if the function succeeds.
'                       The data is returned in string array
'=======================================================================
Public Function GetStdTextResponses(sData() As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec   As dbexec.CExec
Dim sQry    As String

GetStdTextResponses = False

sQry = scExecute & scLvw_StdTxtResp

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'Call the method on the CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    GetStdTextResponses = True
End If

Set oExec = Nothing             'clear the class
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function returns a list of standard voice responses
'Function input:        A string array which gets filled up with data
'Function output:       Returns TRUE if the function succeeds.
'                       The data is returned in string array
'=======================================================================
Public Function GetStdVoiceResponses(sData() As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec   As dbexec.CExec
Dim sQry    As String

GetStdVoiceResponses = False

sQry = scExecute & scLvw_StdVoiceResp

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'Call the method on the CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    GetStdVoiceResponses = True
End If

Set oExec = Nothing             'clear the class
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function returns a list of system paramters
'Function input:        A string array which gets filled up with data
'Function output:       Returns TRUE if the function succeeds.
'                       The data is returned in string array
'=======================================================================
Public Function GetSysParms(sData() As String, Optional ByVal sSysValue As String) As Boolean
#If bUseMTS Then
Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

GetSysParms = False

'Build query string
sQry = scExecute & scLvw_SysParms

#If bUseMTS Then
    'create a new context
    Set oCtxt = GetObjectContext()
    'new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'Call the method on the CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    GetSysParms = True
End If
Set oExec = Nothing             'clear class
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function returns details of a technician from
'                       tbTech
'Function input:        Technician ID whose details are required
'                       A string array which gets filled up with data
'Function output:       Returns TRUE if the function succeeds.
'                       The data is returned in string array
'=======================================================================
Public Function GetTech(ByVal lTechId As Long, sData() As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

GetTech = False

'Build query string
sQry = scExecute & scGet_Tech
sQry = sQry & " @TechId = " & lTechId

#If bUseMTS Then
    'create a new context object
    Set oCtxt = GetObjectContext()
    'new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    GetTech = True
End If
Set oExec = Nothing             'clear

#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function returns a list of technicians
'Function input:        First parameter lets you select either all the techs
'                       or just the technicians who are right now available.
'                       A string array which gets filled up with data
'                       Select technicians with a specific skill (Optional)
'                       Select technicians at a specific location(Optional)
'Function output:       Returns TRUE if the function succeeds.
'                       The data is returned in string array
'=======================================================================
Public Function GetTechs(ByVal iAvail As hdTECHS, sData() As String, Optional ByVal lSkillId As Long, Optional ByVal lLocId As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

GetTechs = False

'Build query string
sQry = ""
Select Case iAvail
Case hdTECHS.icALL_TECHS       'select all technicians
    'No parameter need to be passed
Case hdTECHS.icWORKING_TECHS   'select only technicians who are working right now
    sQry = " @Working = " & iAvail
Case Else
    'Nothing to do
End Select
If lSkillId Then    'If skill id is passed
    If sQry <> vbNullString Then sQry = sQry & scSpaceCommaSpace
    sQry = sQry & " @SkillId = " & lSkillId
End If
If lLocId Then      'if location id is passed
    If sQry <> vbNullString Then sQry = sQry & scSpaceCommaSpace
    sQry = sQry & " @LocId = " & lLocId
End If
sQry = scExecute & scLvw_Techs & sQry

#If bUseMTS Then
    'create a new context object
    Set oCtxt = GetObjectContext()
    'new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    GetTechs = True
End If

Set oExec = Nothing             'clear

#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function returns list of requests of a user logged
'Function input:        User EmailAlias who requests are to be retrieved
'                       A string array which gets filled up with data
'Function output:       Returns TRUE if the function succeeds.
'                       The data is returned in string array
'=======================================================================
Public Function GetUserRequests(ByVal sUserAlias As String, sData() As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

GetUserRequests = False

'Build query string
sQry = scExecute & scLvw_Requests
If Trim$(sUserAlias) <> vbNullString Then
    sQry = sQry & " @EmailAlias= " & scSQ & sUserAlias & scSQ
End If

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'Call the method on the CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    GetUserRequests = True
End If

Set oExec = Nothing             'clear the class
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function inserts a member in a domain table in DB
'Function input:        icDomain selects domain table
'                       sCode is Code value for domein member
'                       sDesc is Desc value for domain member
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function InsertDomainMember(ByVal icDomain As hdDOMAINS, ByVal sCode As String, ByVal sDesc As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

InsertDomainMember = False

'Build query string
Select Case icDomain
    Case hdDOMAINS.icAUDIT_TYPE
        sQry = scExecute & scIns_Domain & " @Domain = " & scSQ & scDomainAuditType & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icLOCATION
        sQry = scExecute & scIns_Domain & " @Domain = " & scSQ & scDomainLocation & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icPRIORITY
        sQry = scExecute & scIns_Domain & " @Domain = " & scSQ & scDomainPriority & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icREQ_DET_TYPE
        sQry = scExecute & scIns_Domain & " @Domain = " & scSQ & scDomainReqDetType & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icREQ_STATUS
        sQry = scExecute & scIns_Domain & " @Domain = " & scSQ & scDomainReqStatus & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icRESOL_TYPE
        sQry = scExecute & scIns_Domain & " @Domain = " & scSQ & scDomainResolType & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icSKILL
        sQry = scExecute & scIns_Domain & " @Domain = " & scSQ & scDomainSkill & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icSYS_PARM_TYPE
        sQry = scExecute & scIns_Domain & " @Domain = " & scSQ & scDomainSysParmType & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icTECH_STATUS
        sQry = scExecute & scIns_Domain & " @Domain = " & scSQ & scDomainTechStat & scSQ & scSpaceCommaSpace
End Select
sQry = sQry & " @Code = " & scSQ & DoQuotes(sCode) & scSQ & scSpaceCommaSpace
sQry = sQry & " @Descr = " & scSQ & DoQuotes(sDesc) & scSQ

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    InsertDomainMember = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function inserts a message in Message table in DB
'                       for the request ID passed.
'Function input:        (Optional) EmailAlias of user sending message
'                       (Optional) Tracking number of request to link message to an existing request
'                       (Optional) Date/Time of message
'                       (Optional) Message text
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function InsertMessage(Optional ByVal lTrackNo As Long, Optional ByVal sEmailAlias As String, Optional ByVal dMsgDate As Date, Optional ByVal sMsgText As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

InsertMessage = False

'Build query string
sQry = ""
If Len(sEmailAlias) Then
    sQry = " @EmailAlias = " & scSQ & DoQuotes(sEmailAlias) & scSQ & scSpaceCommaSpace
End If
If lTrackNo Then
    If sQry <> vbNullString Then sQry = sQry & scSpaceCommaSpace
    sQry = sQry & " @TrackingNo = " & lTrackNo
End If
If dMsgDate Then
    If sQry <> vbNullString Then sQry = sQry & scSpaceCommaSpace
    sQry = sQry & " @MsgDate = " & CStr(dMsgDate)
End If
If Len(sMsgText) Then
    If sQry <> vbNullString Then sQry = sQry & scSpaceCommaSpace
    sQry = sQry & " @MsgText = " & scSQ & DoQuotes(sMsgText) & scSQ & scSpaceCommaSpace
End If
sQry = scExecute & scInsertMessage & sQry

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    InsertMessage = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function inserts a request record into Request table
'Function input:        EMail Alias of who requested
'                       Description of the request
'Function output:       Returns TRUE if the function succeeds.
'                       Returns Tracking Number in lTrackNo
'=======================================================================
Public Function InsertRequest(ByVal lLocId As Long, ByVal lPriorityId As Long, ByVal lSkillId As Long, ByVal sEAlias As String, ByVal sDesc As String, lTrackNo As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim sData()     As String
Dim oExec       As dbexec.CExec
Dim sQry        As String
Dim iIndex      As Integer

InsertRequest = False

'Build query string
sQry = scExecute & scInsertReq
sQry = sQry & " @LocId = " & lLocId & scSpaceCommaSpace
sQry = sQry & " @PriorityId = " & lPriorityId & scSpaceCommaSpace
sQry = sQry & " @SkillId = " & lSkillId & scSpaceCommaSpace
sQry = sQry & " @EmailAlias = " & scSQ & DoQuotes(sEAlias) & scSQ & scSpaceCommaSpace
sQry = sQry & " @Description = " & scSQ & DoQuotes(sDesc) & scSQ

#If bUseMTS Then
    'create a new context object
    Set oCtxt = GetObjectContext()
    'new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    iIndex = UBound(sData, icTwoDim)
    lTrackNo = CLng(sData(icZeroDim, iIndex))
    If lTrackNo Then
        InsertRequest = True
    End If
End If

Set oExec = Nothing             'clear

#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function inserts a record into technician table in db
'Function input:        EMail Alias of technicicn
'                       Location ID of technician
'                       Skill ID of technician
'Function output:       Returns TRUE if the function succeeds.
'=======================================================================
Public Function InsertTechnician(ByVal sEAlias As String, ByVal lLocId As Long, ByVal lSkillId As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sData()     As String
Dim sQry        As String

InsertTechnician = False

'Build query string
sQry = scExecute & scIns_Tech
sQry = sQry & " @EmailAlias = " & scSQ & DoQuotes(sEAlias) & scSQ & scSpaceCommaSpace
sQry = sQry & " @LocId = " & lLocId & scSpaceCommaSpace
sQry = sQry & " @SkillId = " & lSkillId

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    InsertTechnician = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function updates status in Tech table in DB
'                       for the technician ID passed.
'Function input:        Technician ID
'
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function LogoffTech(ByVal lTechId As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

LogoffTech = False

'Build query string
sQry = scExecute & scLogoffTech
sQry = sQry & " @TechId = " & lTechId

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    LogoffTech = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If
End Function

'=======================================================================
'Synopsis:              Function updates status in Tech table in DB
'                       for the technician ID passed.
'Function input:        Technician ID
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function LogonTech(ByVal lTechId As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

LogonTech = False

'Build query string
sQry = scExecute & scLogonTech
sQry = sQry & " @TechId = " & lTechId

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    LogonTech = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If
End Function

'=======================================================================
'Synopsis:              Function reassigns a request from one technician to
'                           another technician
'Function input:        Technician ID of tech who has a request presently assigned
'                       Technician ID of tech to whom request is being reassigned
'                       Request ID of the request being reassigned
'Function output:       Returns TRUE if the function succeeds.
'=======================================================================
Public Function ReAssignReq(ByVal lReqId As Long, ByVal lFrTechId As Long, ByVal lToTechId As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

ReAssignReq = False

'Build query string
sQry = scExecute & scReAssignReq
sQry = sQry & " @FromTechId = " & lFrTechId & scSpaceCommaSpace
sQry = sQry & " @ToTechId = " & lToTechId & scSpaceCommaSpace
sQry = sQry & " @ReqId = " & lReqId

#If bUseMTS Then
    'a new context
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    ReAssignReq = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function inserts a request detail record into
'                       tbReqDet table. Called by technician clients.
'Function input:
'Function output:       Returns TRUE if the function succeeds.
'=======================================================================
Public Function SendStdTextResponse(ByVal lReqId As Long, ByVal lTechId As Long, ByVal lRespId As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

SendStdTextResponse = False

'Build query string
sQry = scExecute & scSendStdTextResp
sQry = sQry & " @ReqId = " & lReqId & scSpaceCommaSpace
sQry = sQry & " @TechId = " & lTechId & scSpaceCommaSpace
sQry = sQry & " @StdTextRespId = " & lRespId

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    SendStdTextResponse = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function inserts a request detail record into
'                       tbReqDet table. Called by technician clients.
'Function input:
'Function output:       Returns TRUE if the function succeeds.
'=======================================================================
Public Function SendStdVoiceResponse(ByVal lReqId As Long, ByVal lTechId As Long, ByVal lRespId As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

SendStdVoiceResponse = False

'Build query string
sQry = scExecute & scSendStdVoiceResp
sQry = sQry & " @ReqId = " & lReqId & scSpaceCommaSpace
sQry = sQry & " @TechId = " & lTechId & scSpaceCommaSpace
sQry = sQry & " @StdTextRespId = " & lRespId

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    SendStdVoiceResponse = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function inserts a request detail record into
'                       tbReqDet table. Called by User clients.
'Function input:
'Function output:       Returns TRUE if the function succeeds.
'=======================================================================
Public Function SendTextRequest(ByVal lReqId As Long, ByVal sMsgText As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

SendTextRequest = False

'Build query string
sQry = scExecute & scSendTextReq
sQry = sQry & " @ReqId = " & lReqId & scSpaceCommaSpace
sQry = sQry & " @MsgText = " & scSQ & DoQuotes(sMsgText) & scSQ

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    SendTextRequest = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function inserts a request detail record into
'                       tbReqDet table. Called by technician clients.
'Function input:
'Function output:       Returns TRUE if the function succeeds.
'=======================================================================
Public Function SendTextResponse(ByVal lReqId As Long, ByVal lTechId As Long, ByVal sMsgText As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

SendTextResponse = False

'Build query string
sQry = scExecute & scSendTxtResp
sQry = sQry & " @ReqId = " & lReqId & scSpaceCommaSpace
sQry = sQry & " @TechId = " & lTechId & scSpaceCommaSpace
sQry = sQry & " @MsgText = " & scSQ & DoQuotes(sMsgText) & scSQ

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    SendTextResponse = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function inserts a request detail record into
'                       tbReqDet table. Called by User clients.
'Function input:
'Function output:       Returns TRUE if the function succeeds.
'=======================================================================
Public Function SendVoiceRequest(ByVal lReqId As Long, ByVal sMsgText As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

SendVoiceRequest = False

'Build query string
sQry = scExecute & scSendVoiceReq
sQry = sQry & " @ReqId = " & lReqId & scSpaceCommaSpace
sQry = sQry & " @MsgText = " & scSQ & DoQuotes(sMsgText) & scSQ

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    SendVoiceRequest = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function inserts a request detail record into
'                       tbReqDet table. Called by technician clients.
'Function input:
'Function output:       Returns TRUE if the function succeeds.
'=======================================================================
Public Function SendVoiceResponse(ByVal lReqId As Long, ByVal lTechId As Long, ByVal sMsgText As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

SendVoiceResponse = False

'Build query string
sQry = scExecute & scSendVoiceResp
sQry = sQry & " @ReqId = " & lReqId & scSpaceCommaSpace
sQry = sQry & " @TechId = " & lTechId & scSpaceCommaSpace
sQry = sQry & " @MsgText = " & scSQ & DoQuotes(sMsgText) & scSQ

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    SendVoiceResponse = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function updates the request record in tbReq table
'                       with status PENDING. Also updates who resolved the
'                       request.
'Function input:        Request ID of request which was resolved
'                       Technician ID of tech who resolved the request
'Function output:       Returns TRUE if the function succeeds.
'=======================================================================
Public Function SubmitRequest(ByVal lReqId As Long, ByVal lTechId As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

SubmitRequest = False

'Build query string
sQry = scExecute & scSubmitReq
sQry = sQry & " @ReqId = " & lReqId & scSpaceCommaSpace
sQry = sQry & " @TechId = " & lTechId

#If bUseMTS Then
    'a new context
    Set oCtxt = GetObjectContext
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec
If oExec.ExecQuery(scConnect, sQry) Then
    SubmitRequest = True
End If

Set oExec = Nothing         'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function updates the request record in tbReq table
'                       status for the request. Changes status from CLAIMED
'                       to ASSIGNED NOT CLAIMED.
'Function input:        Technician ID of tech who unclaimed the request
'                       Request ID of request which was unclaimed
'Function output:       Returns TRUE if the function succeeds.
'=======================================================================
Public Function UnclaimRequest(ByVal lReqId As Long, ByVal lTechId As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

UnclaimRequest = False

'Build query string
sQry = scExecute & scUnclaimReq
sQry = sQry & " @ReqId = " & lReqId & scSpaceCommaSpace
sQry = sQry & " @TechId = " & lTechId

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec
If oExec.ExecQuery(scConnect, sQry) Then
    UnclaimRequest = True
End If

Set oExec = Nothing             'clear

#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function updates a member in a domain table in DB
'Function input:        icDomain selects domain table
'                       sCode is Code value for domein member
'                       sDesc is Desc value for domain member
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function UpdateDomainMember(ByVal icDomain As hdDOMAINS, ByVal sCode As String, ByVal sDesc As String) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

UpdateDomainMember = False

'Build query string
Select Case icDomain
    Case hdDOMAINS.icAUDIT_TYPE
        sQry = scExecute & scUpd_Domain & " @Domain = " & scSQ & scDomainAuditType & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icLOCATION
        sQry = scExecute & scUpd_Domain & " @Domain = " & scSQ & scDomainLocation & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icPRIORITY
        sQry = scExecute & scUpd_Domain & " @Domain = " & scSQ & scDomainPriority & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icREQ_DET_TYPE
        sQry = scExecute & scUpd_Domain & " @Domain = " & scSQ & scDomainReqDetType & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icREQ_STATUS
        sQry = scExecute & scUpd_Domain & " @Domain = " & scSQ & scDomainReqStatus & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icRESOL_TYPE
        sQry = scExecute & scUpd_Domain & " @Domain = " & scSQ & scDomainResolType & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icSKILL
        sQry = scExecute & scUpd_Domain & " @Domain = " & scSQ & scDomainSkill & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icSYS_PARM_TYPE
        sQry = scExecute & scUpd_Domain & " @Domain = " & scSQ & scDomainSysParmType & scSQ & scSpaceCommaSpace
    Case hdDOMAINS.icTECH_STATUS
        sQry = scExecute & scUpd_Domain & " @Domain = " & scSQ & scDomainTechStat & scSQ & scSpaceCommaSpace
End Select
sQry = sQry & " @Code = " & scSQ & DoQuotes(sCode) & scSQ & scSpaceCommaSpace
sQry = sQry & " @Descr = " & scSQ & DoQuotes(sDesc) & scSQ

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    UpdateDomainMember = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function

'=======================================================================
'Synopsis:              Function updates the technician record in tbTech table
'Function input:        Technician ID of tech to update
'                       email Alias, Location ID, and SkillId for technician
'Function output:       Returns TRUE if the function succeeds.
'=======================================================================
Public Function UpdateTechnician(ByVal lTechId As Long, ByVal sEAlias As String, ByVal lLocId As Long, ByVal lSkillId As Long)
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

UpdateTechnician = False

'Build query string
sQry = scExecute & scUpd_Tech
'sQry = sQry & " @TechId = " & lTechId & scSpaceCommaSpace
sQry = sQry & " @EmailAlias = " & scSQ & sEAlias & scSQ & scSpaceCommaSpace
sQry = sQry & " @LocId = " & lLocId & scSpaceCommaSpace
sQry = sQry & " @SkillId = " & lSkillId

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec
If oExec.ExecQuery(scConnect, sQry) Then
    UpdateTechnician = True
End If

Set oExec = Nothing             'clear

#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If
End Function

'=======================================================================
'Synopsis:              Function updates the request record in tbReq table
'                       status for the request. Changes status from CLAIMED
'                       to IN PROGRESS.
'Function input:        Technician ID of tech who started to work on the request
'                       Request ID of request which was started
'Function output:       Returns TRUE if the function succeeds.
'=======================================================================
Public Function WorkRequest(ByVal lReqId As Long, ByVal lTechId As Long) As Boolean
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As dbexec.CExec
Dim sQry        As String

WorkRequest = False

'Build query string
sQry = scExecute & scCommenceReq
sQry = sQry & " @ReqId = " & lReqId & scSpaceCommaSpace
sQry = sQry & " @TechId = " & lTechId

#If bUseMTS Then
    Set oCtxt = GetObjectContext()
    'a new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New dbexec.CExec
#End If

'call method on CExec class
If oExec.ExecQuery(scConnect, sQry) Then
    WorkRequest = True
End If

Set oExec = Nothing             'clear
#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function
