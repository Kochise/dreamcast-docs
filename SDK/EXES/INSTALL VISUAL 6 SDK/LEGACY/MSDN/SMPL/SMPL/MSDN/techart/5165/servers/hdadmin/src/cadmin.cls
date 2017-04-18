VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CAdmin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
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

Private Const OBJNAME = "CAdmin"

'Enumeration used in FillListSysParms methods
Private Enum icSysParm
    icPKID = 0
    icCHANGEDBYID = 1
    icPARMTYPEID = 2
    icCHANGEDATE = 3
    icDESCR = 4
    icSYSVALUE = 5
End Enum

'Enumeration used checking the type of logged in Alias - User or Tech
Private Enum icLoggedInType
    icUSERLOGGEDIN = 1
    icTECHLOGGEDIN = 2
    icADMINLOGGEDIN = 2
End Enum

Private Const PKIdPrefix = "ID="

Private m_cSysParmTypes As Collection   'Collection of Sys Parm Types
Private m_cSysParms As Collection       'Collection of Sys Parms
Private m_cRequests As Collection       'collection of requests for specific technicia

'Used for temporary storage of error information
Private m_lErrNo    As Long
Private m_sErrDesc  As String

'=======================================================================
'Synopsis:              Procedure fills the request collection
'                       with request records determined by technician.
'Function input:        Technician identifier.
'Function output:       None
'=======================================================================
Private Sub FillListRequestsByTechId(ByVal lTechId As Long)
Dim oTrans  As HDServer.CTrans
Dim oRequest As HDClient.CRequest
Dim iIndex  As Integer
Dim sData() As String
Dim oTech As HDClient.CTech

Set oTrans = New HDServer.CTrans    'Create a new Trans object

'Re-initialise the collection object
Set m_cRequests = Nothing
Set m_cRequests = New Collection

'Call method on the Trans object. Fill the skills collection
If oTrans.GetRequests(lTechId, sData) Then
    For iIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
        Set oTech = New HDClient.CTech
        With oTech
            oTech.PKid = CLng(sData(icReqTechId, iIndex))
        End With
        Set oRequest = New HDClient.CRequest
        With oRequest
            .PKid = CLng(sData(icReqPKId, iIndex))
            .Alias = sData(icReqEmailAlias, iIndex)
            .Desc = sData(icReqDescr, iIndex)
            .LocId = CLng(sData(icReqLocId, iIndex))
            .Other = sData(icReqResolOther, iIndex)
            .PriorityId = CLng(sData(icReqPriorityId, iIndex))
            .ReqDate = CDate(sData(icReqReqDate, iIndex))
            .SkillId = CLng(sData(icReqSkillId, iIndex))
            .StatusId = CLng(sData(icReqStatusId, iIndex))
            .TrackingNo = CLng(sData(icReqTrackingNo, iIndex))
            'these may fial if request is not yet resolved
            On Error Resume Next
            .ResolvedBy = CLng(sData(icReqResolById, iIndex))
            .ResTypeId = CLng(sData(icReqResolTypeId, iIndex))
            .ResDate = CDate(sData(icReqResolDate, iIndex))
            On Error GoTo 0
            'fill in technician
            Set .Tech = oTech
        End With
        m_cRequests.Add oRequest, FmtPKId(sData(icReqPKId, iIndex))
        Set oRequest = Nothing
        Set oTech = Nothing
    Next iIndex
End If

Set oTrans = Nothing    'clear local Trans object

End Sub

'=======================================================================
'Synopsis:              This method returns a request object determined
'                       by tracking identifier.
'Function input:        Tracking identifier.
'Function output:       Request object.
'=======================================================================
Public Function GetRequest(ByVal lTrackNo As Long) As CRequest
    Dim oTrans As HDServer.CTrans
    Dim oRequest As HDClient.CRequest
    
    Set oTrans = New HDServer.CTrans
    Set oRequest = New HDClient.CRequest
    
    oRequest.TrackingNo = lTrackNo
    Debug.Print oRequest.Alias
    Set GetRequest = oRequest
    
    Set oTrans = Nothing

End Function

'=======================================================================
'Synopsis:              Returns requests determined
'                       by technician identifier.
'Function input:        Technician identifier.
'Function output:       Returns a collection of requests.
'=======================================================================
Public Function GetRequestsByTechId(ByVal lTechId As Long) As Collection
Dim sErrDesc    As String
Dim lErrNo      As Long

On Error GoTo GetSkErr
FillListRequestsByTechId lTechId

Set GetRequestsByTechId = m_cRequests
Exit Function

GetSkErr:
    On Error Resume Next
    Set GetRequestsByTechId = Nothing
    sErrDesc = Err.Description
    
    If Err < vbObjectError Then
        lErrNo = lErrNo + vbObjectError
    End If
    
    On Error GoTo 0
    Err.Raise lErrNo, Trim$(App.Title) & scAdmSysParm, sErrDesc
    Exit Function

End Function

'=======================================================================
'Synopsis:              This method returns a system parameter object
'                       determined by a parameter key.
'Function input:        Parameter key.
'Function output:       System parameter object
'=======================================================================
Public Function GetSysParmByKey(ByVal sParmKey As String) As CSysParm

Dim oSysParm As CSysParm

Set GetSysParmByKey = Nothing

sParmKey = Trim$(sParmKey)

If m_cSysParms Is Nothing Then
    FillListSysParms
End If

If Len(sParmKey) Then
    For Each oSysParm In m_cSysParms
        If oSysParm.Desc = sParmKey Then
            Set GetSysParmByKey = oSysParm
            Exit For
        End If
    Next oSysParm
End If

Set oSysParm = Nothing     'clear object

End Function

'=======================================================================
'Synopsis:              Function deletes an item from one of the
'                       collections.
'Function input:        One of location, priority, skill, or technician.
'Function output:       Returns TRUE if the function succeeds.
'=======================================================================
Public Function Delete( _
                    Optional oLocation As CLocation, _
                    Optional oPriority As CPriority, _
                    Optional oSkill As CSkill, _
                    Optional oTech As CTech _
                    ) As Boolean
    Dim oTrans As HDServer.CTrans
    Dim iCount As Integer

    'there can only be one object passed in
    iCount = 0
    If Not oLocation Is Nothing Then
        iCount = iCount + 1
    End If
    If Not oPriority Is Nothing Then
        iCount = iCount + 1
    End If
    If Not oSkill Is Nothing Then
        iCount = iCount + 1
    End If
    If Not oTech Is Nothing Then
        iCount = iCount + 1
    End If
    
    'if more than one object passed in then raise error
    If iCount <> 1 Then
        Err.Raise 5
        Exit Function
    End If

    'Deleting a Location
    If Not oLocation Is Nothing Then
        Set oTrans = New HDServer.CTrans
        If oTrans.DeleteDomainMember(icLOCATION, oLocation.Code) Then
            Delete = True
        End If
        Set oTrans = Nothing
        Exit Function
    End If
    
    'Deleting  a Priority
    If Not oPriority Is Nothing Then
        Set oTrans = New HDServer.CTrans
        If oTrans.DeleteDomainMember(icPRIORITY, oLocation.Code) Then
            Delete = True
        End If
        Set oTrans = Nothing
        Exit Function
    End If
    
    'Deleting  a Skill
    If Not oSkill Is Nothing Then
        Set oTrans = New HDServer.CTrans
        If oTrans.DeleteDomainMember(icSKILL, oSkill.Code) Then
            Delete = True
        End If
        Set oTrans = Nothing
        Exit Function
    End If
   
    'Deleting  a Technician
    If Not oTech Is Nothing Then
        Set oTrans = New HDServer.CTrans
        If oTrans.DeleteTechnician(oTech.Alias) Then
            Delete = True
        End If
        Set oTrans = Nothing
        Exit Function
    End If

    Delete = True
End Function

'=======================================================================
'Synopsis:              Converts PKid from string to integer.
'Function input:        String.
'Function output:       Integer.
'=======================================================================
Public Function ExtrPKId(ByVal sFmtPKid As String) As Integer
    Dim iIndex As Integer
    
    iIndex = InStr(1, sFmtPKid, PKIdPrefix)
    If iIndex < 1 Then
        ExtrPKId = -1
        Exit Function
    End If
    
    iIndex = iIndex + Len(PKIdPrefix)
    
    ExtrPKId = CInt(Right$(sFmtPKid, iIndex))
End Function

'=======================================================================
'Synopsis:              Converts PKid to string.
'Function input:        Integer.
'Function output:       String.
'=======================================================================
Public Function FmtPKId(ByVal iPKid As Integer) As String
    FmtPKId = PKIdPrefix & CStr(iPKid)
End Function

'=======================================================================
'Synopsis:
'Function input:
'Function output:       Returns a collection of system parameters.
'=======================================================================
Public Function GetSysParms() As Collection
On Error GoTo GetSkErr
Dim sErrDesc    As String
Dim lErrNo      As Long

If m_cSysParms Is Nothing Then
    FillListSysParms               'Fill up the sys parms collection
End If

Set GetSysParms = m_cSysParms
Exit Function

GetSkErr:
    On Error Resume Next
    Set GetSysParms = Nothing
    sErrDesc = Err.Description
    
    If Err < vbObjectError Then
        lErrNo = lErrNo + vbObjectError
    End If
    
    On Error GoTo 0
    Err.Raise lErrNo, Trim$(App.Title) & scAdmSysParm, sErrDesc
    Exit Function

End Function

'=======================================================================
'Synopsis:              Function initialises the different collections.
'                       Fills list of Technicians
'                       Fills list of Locations
'                       Fills list of Skills
'Function input:        Email Alias of technician/ user logged in
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function Init(ByVal sAlias As String, ByVal iLoggedInType As Integer) As Boolean

On Error GoTo errInit

Init = False
Term    'Clears all the collections and module level variables

'Check whether passed Alias string is proper
sAlias = UCase(Trim$(sAlias))
If sAlias = vbNullString Then
    GoTo ExitLoop
End If

FillListSysParmTypes 'Fill up all the sys parm types

ExitLoop:
    Exit Function

errInit:
    Init = False
End Function

'=======================================================================
'Synopsis:              Procedure fills the system parameter collection
'                       with system parameter records.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillListSysParms()
Dim oTrans   As HDServer.CTrans
Dim oSysParm As CSysParm
Dim iIndex   As Integer
Dim sData()  As String

Set oTrans = New HDServer.CTrans    'Create a new Trans object

'Re-initialise the Collection object used for locations
Set m_cSysParms = Nothing
Set m_cSysParms = New Collection

'Call function on Trans object. Fill the data in collection
If oTrans.GetSysParms(sData()) Then
    For iIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
        Set oSysParm = New CSysParm
        With oSysParm
            .PKid = CLng(sData(icPKID, iIndex))
            .ChangedById = CLng(sData(icCHANGEDBYID, iIndex))
            .ParmTypeId = CLng(sData(icPARMTYPEID, iIndex))
            .ChangeDate = CDate(sData(icCHANGEDATE, iIndex))
            .Desc = Trim$(sData(icDESCR, iIndex))
            .SysValue = Trim$(sData(icSYSVALUE, iIndex))
        End With
        m_cSysParms.Add oSysParm, FmtPKId(sData(icDomPKId, iIndex))
    Next iIndex
End If

Set oSysParm = Nothing

Set oTrans = Nothing    'clear the Trans object

End Sub

'=======================================================================
'Synopsis:              Procedure fills the system parameter type
'                       collection with system parameter type records.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillListSysParmTypes()
Dim oTrans  As HDServer.CTrans
Dim oSysParmType As CSysParmType
Dim iIndex  As Integer
Dim sData() As String

Set oTrans = New HDServer.CTrans    'Create a new Trans object

'Re-initialise the skills collection object
Set m_cSysParmTypes = Nothing
Set m_cSysParmTypes = New Collection

'Call method on the Trans object. Fill the skills collection
If oTrans.GetDomain(icSYS_PARM_TYPE, sData) Then
    For iIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
        Set oSysParmType = New CSysParmType
        With oSysParmType
            .PKid = CLng(sData(icDomPKId, iIndex))
            .Desc = Trim$(sData(icDomDesc, iIndex))
            .Code = Trim$(sData(icDomCode, iIndex))
        End With
        m_cSysParmTypes.Add oSysParmType, FmtPKId(sData(icDomPKId, iIndex))
    Next iIndex
End If

Set oSysParmType = Nothing
Set oTrans = Nothing    'clear local Trans object

End Sub

'=======================================================================
'Synopsis:
'Function input:
'Function output:       Returns a collection of system parameter types.
'=======================================================================
Public Function GetSysParmTypes() As Collection
On Error GoTo GetSkErr
Dim sErrDesc    As String
Dim lErrNo      As Long

If m_cSysParmTypes Is Nothing Then
    FillListSysParmTypes               'Fill up the sys parm types collection
End If

Set GetSysParmTypes = m_cSysParmTypes
Exit Function

GetSkErr:
    On Error Resume Next
    Set GetSysParmTypes = Nothing
    sErrDesc = Err.Description
    
    If Err < vbObjectError Then
        lErrNo = lErrNo + vbObjectError
    End If
    
    On Error GoTo 0
    Err.Raise lErrNo, Trim$(App.Title) & scAdmSysParmTypes, sErrDesc
    Exit Function

End Function

'=======================================================================
'Synopsis:              Function inserts an item into one of the
'                       collections.
'Function input:        One of location, priority, skill, or technician.
'Function output:       Returns TRUE if the function succeeds.
'=======================================================================
Public Function Insert( _
                    Optional oLocation As CLocation, _
                    Optional oPriority As CPriority, _
                    Optional oSkill As CSkill, _
                    Optional oTech As CTech _
                    ) As Boolean
    Dim oTrans As HDServer.CTrans
    Dim iCount As Integer
    
    'there can only be one object passed in
    iCount = 0
    If Not oLocation Is Nothing Then
        iCount = iCount + 1
    End If
    If Not oPriority Is Nothing Then
        iCount = iCount + 1
    End If
    If Not oSkill Is Nothing Then
        iCount = iCount + 1
    End If
    If Not oTech Is Nothing Then
        iCount = iCount + 1
    End If
    
    'if more than one object passed in then raise error
    If iCount <> 1 Then
        Err.Raise 5
        Exit Function
    End If
    
    'Inserting a Location
    If Not oLocation Is Nothing Then
        Set oTrans = New HDServer.CTrans
        If oTrans.InsertDomainMember(icLOCATION, oLocation.Code, oLocation.Desc) Then
            Insert = True
        End If
        Set oTrans = Nothing
        Exit Function
    End If
    
    'Inserting a Priority
    If Not oPriority Is Nothing Then
        Set oTrans = New HDServer.CTrans
        If oTrans.InsertDomainMember(icPRIORITY, oLocation.Code, oLocation.Desc) Then
            Insert = True
        End If
        Set oTrans = Nothing
        Exit Function
    End If
    
    'Inserting a Skill
    If Not oSkill Is Nothing Then
        Set oTrans = New HDServer.CTrans
        If oTrans.InsertDomainMember(icSKILL, oSkill.Code, oSkill.Desc) Then
            Insert = True
        End If
        Set oTrans = Nothing
        Exit Function
    End If
   
    'Inserting a Technician
    If Not oTech Is Nothing Then
        Set oTrans = New HDServer.CTrans
        If oTrans.InsertTechnician(oTech.Alias, oTech.LocationId, oTech.SkillId) Then
            Insert = True
        End If
        Set oTrans = Nothing
        Exit Function
    End If

End Function

'=======================================================================
'Synopsis:              Terminates the object and releases all references
'Function input:        None
'Function output:       None
'=======================================================================
Public Sub Term()

Set m_cSysParmTypes = Nothing

End Sub

'=======================================================================
'Synopsis:              This method Refreshes the system parameter types
'                       collection.
'Function input:        None
'Function output:       None
'=======================================================================
Public Sub Refresh()

If m_cSysParmTypes Is Nothing Then
    FillListSysParmTypes 'Fill SysParm Types
End If

End Sub

'=======================================================================
'Synopsis:              Function updates one of the collections.
'Function input:        One of location, priority, skill, or technician.
'Function output:       Returns TRUE if the function succeeds.
'=======================================================================
Public Function Update( _
                    Optional oLocation As CLocation, _
                    Optional oPriority As CPriority, _
                    Optional oSkill As CSkill, _
                    Optional oTech As CTech _
                    ) As Boolean
    Dim oTrans As HDServer.CTrans
    Dim iCount As Integer

    'there can only be one object passed in
    iCount = 0
    If Not oLocation Is Nothing Then
        iCount = iCount + 1
    End If
    If Not oPriority Is Nothing Then
        iCount = iCount + 1
    End If
    If Not oSkill Is Nothing Then
        iCount = iCount + 1
    End If
    If Not oTech Is Nothing Then
        iCount = iCount + 1
    End If
    
    'if more than one object passed in then raise error
    If iCount <> 1 Then
        Err.Raise 5
        Exit Function
    End If
    
    'Updating a Location
    If Not oLocation Is Nothing Then
        Set oTrans = New HDServer.CTrans
        If oTrans.UpdateDomainMember(icLOCATION, oLocation.Code, oLocation.Desc) Then
            Update = True
        End If
        Set oTrans = Nothing
        Exit Function
    End If
    
    'Updating a Priority
    If Not oPriority Is Nothing Then
        Set oTrans = New HDServer.CTrans
        If oTrans.UpdateDomainMember(icPRIORITY, oLocation.Code, oLocation.Desc) Then
            Update = True
        End If
        Set oTrans = Nothing
        Exit Function
    End If
    
    'Updating a Skill
    If Not oSkill Is Nothing Then
        Set oTrans = New HDServer.CTrans
        If oTrans.UpdateDomainMember(icSKILL, oSkill.Code, oSkill.Desc) Then
            Update = True
        End If
        Set oTrans = Nothing
        Exit Function
    End If
   
    'Updating a Technician
    If Not oTech Is Nothing Then
        Set oTrans = New HDServer.CTrans
        If oTrans.UpdateTechnician(oTech.PKIdEx, oTech.Alias, oTech.LocationId, oTech.SkillId) Then
            Update = True
        End If
        Set oTrans = Nothing
        Exit Function
    End If

    Update = True
End Function

Private Sub Class_Terminate()

Term    'clear all module level objects

End Sub
