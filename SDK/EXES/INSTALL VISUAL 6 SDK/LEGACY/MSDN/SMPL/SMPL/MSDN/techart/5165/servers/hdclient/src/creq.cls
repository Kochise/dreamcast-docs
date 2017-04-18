VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CRequest"
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

Private Const OBJNAME = "CRequest"

Private m_oTech         As CTech
Private m_oRTech        As CTech
Private m_cDetails      As Collection
Private m_dtReqDate     As Date
Private m_dtResDate     As Date
Private m_sAlias        As String
Private m_sDescr        As String
Private m_sOther        As String
Private m_lPKId         As Long
Private m_lLocId        As Long
Private m_lPriorityId   As Long
Private m_lResTypeId    As Long
Private m_lSkillId      As Long
Private m_lStatusId     As Long
Private m_lTrackNo      As Long
Private m_bExpPart      As Boolean
Private m_bExpFull      As Boolean

Private Enum icRequest
    icPKId = 0
    icReqDate = 1
    icResDate = 2
    icLocId = 3
    icPriorityId = 4
    icRTechId = 5
    icResTypeId = 6
    icSkillId = 7
    icStatusId = 8
    icTechId = 9
    icReqDetPKId = 10
    icAlias = 11
    icOther = 12
    icDescr = 13
End Enum

'=======================================================================
'Synopsis:              Clears all module level variables
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub Clear()
Dim oReqDet As hdclient.CReqDetail

Set m_oTech = Nothing
Set m_oRTech = Nothing

m_dtReqDate = 0
m_dtResDate = 0
m_lLocId = 0
m_lPriorityId = 0
m_lResTypeId = 0
m_lSkillId = 0
m_lStatusId = 0

m_sAlias = vbNullString
m_sDescr = vbNullString
m_sOther = vbNullString

If Not (m_cDetails Is Nothing) Then
    For Each oReqDet In m_cDetails
        Set oReqDet = Nothing
    Next
End If
Set m_cDetails = Nothing        'Set the collection of request details to nothing

m_bExpPart = False              'Set partial expand to false
m_bExpFull = False              'set full expand to false

End Sub

'=======================================================================
'Synopsis:              Fills up the request object attributes. If Refresh
'                       is partial then ReqDetail collection is not filled.
'Function input:        Boolean value indicating partial or complete refresh
'Function output:       None
'=======================================================================
Private Sub Refresh(lExpandFull As Boolean)

Dim oTrans  As HDServer.CTrans
Dim oReqDet As CReqDetail
Dim oTech   As CTech
Dim iIndex  As Integer
Dim lTechId As Long
Dim sData() As String

On Error Resume Next

'Check whether request PKId is passed
If CBool(m_lPKId) Or CBool(m_lTrackNo) Then
    Clear
    Set oTrans = New HDServer.CTrans 'CreateObject("HDServer.CTrans")
    
    'Call method on CTrans object
    If oTrans.GetRequest(sData, m_lPKId, m_lTrackNo) Then
        m_lPKId = CLng(sData(icReqPkID, icZeroDim))
        m_dtReqDate = CDate(sData(icReqDate, icZeroDim)) 'Assign member variables
        m_dtResDate = CDate(sData(icResDate, icZeroDim))
        m_lLocId = CLng(sData(icLocId, icZeroDim))
        m_lPriorityId = CLng(sData(icPriorityId, icZeroDim))
        m_lResTypeId = CLng(sData(icResTypeId, icZeroDim))
        m_lSkillId = CLng(sData(icSkillId, icZeroDim))
        m_lStatusId = CLng(sData(icStatusId, icZeroDim))
        m_sAlias = Trim$(sData(icAlias, icZeroDim))
        m_sDescr = Trim$(sData(icDescr, icZeroDim))
        m_sOther = Trim$(sData(icOther, icZeroDim))
        m_lTrackNo = CLng(sData(icReqTrackNo, icZeroDim))
        
        'Set Technician object
        Set oTech = New CTech
        oTech.PKId = CLng(sData(icTechId, icZeroDim))
        Set m_oTech = oTech
        Set oTech = Nothing
        
        'Set Resolved By Technician object
        lTechId = CLng(sData(icRTechId, icZeroDim))
        If lTechId Then
            Set oTech = New CTech
            oTech.PKId = lTechId
            Set m_oRTech = oTech
            Set oTech = Nothing
        End If
        
        'If parameter is passed to expand the object completely
        'then fill Request Details collection
        If lExpandFull Then
            'Initialize Details list and clear array
            Set m_cDetails = New Collection
            Set m_cDetails = GetReqDetails(m_lPKId)
            m_bExpFull = True
        End If                  'Ending check on lExpandFull
    
    End If 'ending check on success of GetRequest method
Set oTrans = Nothing
m_bExpPart = True
End If 'ending check on PKId passed

End Sub

'=======================================================================
'Synopsis:              Terminates the object and releases all references
'Function input:        None
'Function output:       None
'=======================================================================
Public Sub Term()
Clear
End Sub

'=======================================================================
'Attribute:     Returns technician object to whom request has been assigned
'=======================================================================
Public Property Get Tech() As CTech

If Not m_bExpPart Then
    Refresh False   'This expands request object partially
End If

Set Tech = m_oTech

End Property

'=======================================================================
'Attribute:     Sets technician to whom request has been assigned.
'=======================================================================
Public Property Set Tech(oTech As CTech)
Set m_oTech = oTech
End Property

'=======================================================================
'Attribute:     Returns technician who resolved the request
'=======================================================================
Public Property Get ResolvedBy() As CTech

If Not m_bExpPart Then
    Refresh False   'This expands request object partially
End If

Set ResolvedBy = m_oRTech
End Property

'=======================================================================
'Attribute:     Sets technician who resolved request
'=======================================================================
Public Property Set ResolvedBy(oTech As CTech)
Set m_oRTech = oTech
End Property

'=======================================================================
'Attribute:     Returns a collection of request detail records which
'               belong to this request.
'=======================================================================
Public Property Get Details() As Collection

If Not m_bExpFull Then
    Refresh True    'This expands the request object completely
End If

If m_cDetails Is Nothing Then
    Set m_cDetails = New Collection
End If
Set Details = m_cDetails

End Property

'=======================================================================
'Attribute:     Returns ID of request.
'=======================================================================
Public Property Get PKId() As Long
PKId = m_lPKId
End Property

'=======================================================================
'Attribute:     Sets ID of request.
'=======================================================================
Public Property Let PKId(ByVal lNewPKId As Long)
m_lPKId = lNewPKId
End Property

'=======================================================================
'Attribute:     Returns ID of request - uses self expansion.
'=======================================================================
Public Property Get PKIdEx() As Long

If Not m_bExpPart Then
    Refresh False   'This expands request object partially
End If

PKIdEx = m_lPKId
End Property

'=======================================================================
'Attribute:     Sets Date on which this request was made.
'=======================================================================
Public Property Let ReqDate(ByVal dtNewReqDate As Date)
m_dtReqDate = dtNewReqDate
End Property

'=======================================================================
'Attribute:     Returns Date on which this request was made.
'=======================================================================
Public Property Get ReqDate() As Date

If Not m_bExpPart Then
    Refresh False   'This expands request object partially
End If

ReqDate = m_dtReqDate
End Property

'=======================================================================
'Attribute:     Sets Date on which this request was resolved.
'=======================================================================
Public Property Let ResDate(ByVal dtNewResDate As Date)
m_dtResDate = dtNewResDate
End Property

'=======================================================================
'Attribute:     Returns Date on which this request was resolved.
'=======================================================================
Public Property Get ResDate() As Date

If Not m_bExpPart Then
    Refresh False   'This expands request object partially
End If

ResDate = m_dtResDate
End Property

'=======================================================================
'Attribute:     Returns location ID of request
'=======================================================================
Public Property Get LocId() As Long
If Not m_bExpPart Then
    Refresh False   'This expands request object partially
End If
LocId = m_lLocId
End Property

'=======================================================================
'Attribute:     Sets location ID of request.
'=======================================================================
Public Property Let LocId(lNewLocId As Long)
m_lLocId = lNewLocId
End Property

'=======================================================================
'Attribute:     Returns priority ID of request.
'=======================================================================
Public Property Get PriorityId() As Long

If Not m_bExpPart Then
    Refresh False   'This expands request object partially
End If

PriorityId = m_lPriorityId
End Property

'=======================================================================
'Attribute:     Sets priority ID of request.
'=======================================================================
Public Property Let PriorityId(lNewPriorityId As Long)
m_lPriorityId = lNewPriorityId
End Property

'=======================================================================
'Attribute:     Returns type of resolution.
'=======================================================================
Public Property Get ResTypeId() As Long
If Not m_bExpPart Then
    Refresh False   'This expands request object partially
End If

ResTypeId = m_lResTypeId
End Property

'=======================================================================
'Attribute:     Sets type of resolution.
'=======================================================================
Public Property Let ResTypeId(lNewResTypeId As Long)
m_lResTypeId = lNewResTypeId
End Property

'=======================================================================
'Attribute:     Returns skill ID required for request.
'=======================================================================
Public Property Get SkillId() As Long
If Not m_bExpPart Then
    Refresh False   'This expands request object partially
End If

SkillId = m_lSkillId
End Property

'=======================================================================
'Attribute:     Sets skill ID required for request.
'=======================================================================
Public Property Let SkillId(lNewSkillId As Long)
m_lSkillId = lNewSkillId
End Property

'=======================================================================
'Attribute:     Returns status of request.
'=======================================================================
Public Property Get StatusId() As Long
If Not m_bExpPart Then
    Refresh False   'This expands request object partially
End If
StatusId = m_lStatusId
End Property

'=======================================================================
'Attribute:     Sets status of request.
'=======================================================================
Public Property Let StatusId(lNewStatusId As Long)
m_lStatusId = lNewStatusId
End Property

'=======================================================================
'Attribute:     Returns who requested this.
'=======================================================================
Public Property Get Alias() As String
If Not m_bExpPart Then
    Refresh False   'This expands request object partially
End If
Alias = m_sAlias
End Property

'=======================================================================
'Attribute:     Sets who requested this.
'=======================================================================
Public Property Let Alias(ByVal sNewAlias As String)
m_sAlias = sNewAlias
End Property

'=======================================================================
'Attribute:     Returns description of request.
'=======================================================================
Public Property Get Desc() As String
If Not m_bExpPart Then
    Refresh False   'This expands request object partially
End If
Desc = m_sDescr
End Property

'=======================================================================
'Attribute:     Sets description of request.
'=======================================================================
Public Property Let Desc(ByVal sNewDescr As String)
m_sDescr = sNewDescr
End Property

'=======================================================================
'Attribute:     Returns other details of request.
'=======================================================================
Public Property Get Other() As String
If Not m_bExpPart Then
    Refresh False   'This expands request object partially
End If
Other = m_sOther
End Property

'=======================================================================
'Attribute:     Sets other details of request.
'=======================================================================
Public Property Let Other(ByVal sNewOther As String)
m_sOther = sNewOther
End Property

Private Sub Class_Terminate()
Term    'Clear all attributes before terminating
End Sub
Public Property Get TrackingNo() As Long

If Not m_bExpPart Then
    Refresh False   'This expands request object partially
End If

TrackingNo = m_lTrackNo

End Property

Public Property Let TrackingNo(ByVal lNewValue As Long)
m_lTrackNo = lNewValue
End Property

'=======================================================================
'Synopsis:              Returns request details determined
'                       by a request.
'Function input:        Request identifier.
'Function output:       Returns a collection of request details.
'=======================================================================
Private Function GetReqDetails(ByVal lReqId As Long) As Collection
Dim oTrans  As HDServer.CTrans
Dim oReqDet As CReqDetail
Dim oTech As CTech
Dim cDets As Collection
Dim sData() As String
Dim lIndex  As Long
Dim lTechId As Long

On Error Resume Next
Set cDets = New Collection

Set oTrans = New HDServer.CTrans 'CreateObject("HDServer.CTrans")
If oTrans.GetReqDetails(lReqId, sData) Then
    For lIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
        Set oReqDet = New CReqDetail
        With oReqDet
            .PKId = CLng(sData(icRDPKId, lIndex))
            .DetDate = CDate(sData(icRDDate, lIndex))
            .DetTypeId = CLng(sData(icRDTypeId, lIndex))
            .DetailText = Trim$(sData(icRDDetMsg, lIndex))
        End With
        lTechId = CLng(sData(icRDTechId, lIndex))
        If lTechId Then
            Set oTech = New CTech
            oTech.PKId = lTechId
            Set oReqDet.Tech = oTech
            Set oTech = Nothing
        End If
        cDets.Add oReqDet, ItemPKId(oReqDet.PKId)
        Set oReqDet = Nothing
    Next lIndex
End If
Set oTrans = Nothing
Set GetReqDetails = cDets
End Function

