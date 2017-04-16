VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CTech"
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

Private Const OBJNAME = "CTech"

Private m_cReqs     As Collection
Private m_sAlias    As String
Private m_lLocId    As Long
Private m_lPKId     As Long
Private m_lSkillId  As Long
Private m_bExpPart  As Boolean
Private m_bExpFull  As Boolean

'=======================================================================
'Synopsis:              Clears all module level variables
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub Clear()
Dim oReq As hdclient.CRequest

m_sAlias = vbNullString

If Not (m_cReqs Is Nothing) Then
    For Each oReq In m_cReqs
        Set oReq = Nothing
    Next
End If
Set m_cReqs = Nothing


m_bExpPart = False
m_bExpFull = False

End Sub

'=======================================================================
'Synopsis:              Fills up the technician object attributes. If
'                       Refresh is partial then Requests collection is
'                       not filled.
'Function input:        Boolean value indicating partial or complete refresh
'Function output:       None
'=======================================================================
Private Sub Refresh(bExpandFull As Boolean)

Dim oTrans  As HDServer.CTrans
Dim oReq    As CRequest
Dim iIndex  As Integer
Dim sData() As String

On Error Resume Next

'Nothing to do without m_lPKId
If CBool(m_lPKId) Then
    Clear
    Set oTrans = New HDServer.CTrans 'CreateObject("HDServer.CTrans")
    'If data fills array populate member variables
    If oTrans.GetTech(m_lPKId, sData) Then
        'Assign member variables
        m_lLocId = CLng(sData(icTechLocId, icZeroDim))
        m_lSkillId = CLng(sData(icTechSkillId, icZeroDim))
        m_sAlias = Trim$(sData(icAlias, icZeroDim))
        
        If bExpandFull Then
            'Initialize Details list and clear array
            Set m_cReqs = New Collection
            'begin new code
            Set m_cReqs = GetTechReqs(m_lPKId)
            m_bExpFull = True
            'end new code
            'ReDim sData(0)
            'If oTrans.GetRequests(m_lPKId, sData) Then
            '    For iIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
            '        Set oReq = New CRequest
            '        With oReq
            '            .PKId = CLng(sData(icReqPkID, iIndex))
            '            .PriorityId = CLng(sData(icReqPriorId, iIndex))
            '            .StatusId = CLng(sData(icReqStatusId, iIndex))
            '            .Desc = Trim$(sData(icReqDesc, iIndex))
            '            .ReqDate = CDate(sData(icReqDate, iIndex))
            '        End With
            '        m_cReqs.Add oReq, ItemPKId(oReq.PKId)
            '        Set oReq = Nothing
            '        m_bExpFull = True
            '    Next iIndex
            'End If
        End If  'End of lExpandFull check
    End If  'End of GetTech method check
    Set oTrans = Nothing
    m_bExpPart = True
End If  'End of PKId check

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
'Attribute:     Returns collection of requests that belong to this
'               technician
'=======================================================================
Public Property Get Requests() As Collection

If Not m_bExpFull Then
    Refresh True    'This refreshes the object completely
End If

If m_cReqs Is Nothing Then
    Set m_cReqs = New Collection
End If

Set Requests = m_cReqs

End Property

'=======================================================================
'Attribute:     Returns ID of technician
'=======================================================================
Public Property Get PKId() As Long
PKId = m_lPKId
End Property

'=======================================================================
'Attribute:     Sets ID of technician
'=======================================================================
Public Property Let PKId(ByVal lNewPKId As Long)
m_lPKId = lNewPKId
End Property

'=======================================================================
'Attribute:     Returns ID of technician - uses self expansion.
'=======================================================================
Public Property Get PKIdEx() As Long

If Not m_bExpPart Then
    Refresh False   'This refreshed the object partially
End If

PKIdEx = m_lPKId
End Property

'=======================================================================
'Attribute:     Returns ID of location
'=======================================================================
Public Property Get LocationId() As Long

If Not m_bExpPart Then
    Refresh False   'This refreshed the object partially
End If

LocationId = m_lLocId
End Property

'=======================================================================
'Attribute:     Sets ID of location.
'=======================================================================
Public Property Let LocationId(lNewLocId As Long)
m_lLocId = lNewLocId
End Property

'=======================================================================
'Attribute:     Returns ID of skills of technician
'=======================================================================
Public Property Get SkillId() As Long
If Not m_bExpPart Then
    Refresh False   'This refreshes the object partially
End If

SkillId = m_lSkillId
End Property

'=======================================================================
'Attribute:     Sets ID of skill.
'=======================================================================
Public Property Let SkillId(lNewSkillId As Long)
m_lSkillId = lNewSkillId
End Property

'=======================================================================
'Attribute:     Returns EmailAlias of technician.
'=======================================================================
Public Property Get Alias() As String
If Not m_bExpPart Then
    Refresh False   'Refreshes object partially
End If

Alias = m_sAlias
End Property

'=======================================================================
'Attribute:     Sets EmailAlias of techinician.
'=======================================================================
Public Property Let Alias(ByVal sNewAlias As String)
m_sAlias = sNewAlias
End Property

Private Sub Class_Terminate()
Term    'Clear everything before terminating
End Sub

'=======================================================================
'Synopsis:              Returns requests determined
'                       by tech.
'Function input:        Technician identifier.
'Function output:       Returns a collection of requests.
'=======================================================================
Private Function GetTechReqs(ByVal lTechId) As Collection
Dim oTrans  As HDServer.CTrans
Dim oReq    As CRequest
Dim cReqs As Collection
Dim sData() As String
Dim lIndex  As Long

Set cReqs = New Collection

Set oTrans = New HDServer.CTrans 'CreateObject("HDServer.CTrans")
If oTrans.GetRequests(lTechId, sData) Then
    For lIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
        Set oReq = New CRequest
        With oReq
            .PKId = CLng(sData(icReqPkID, lIndex))
            .PriorityId = CLng(sData(icReqPriorId, lIndex))
            .StatusId = CLng(sData(icReqStatusId, lIndex))
            .Desc = Trim$(sData(icReqDesc, lIndex))
            .ReqDate = CDate(sData(icReqDate, lIndex))
        End With
        cReqs.Add oReq, ItemPKId(oReq.PKId)
        Set oReq = Nothing
    Next lIndex
End If
Set oTrans = Nothing
Set GetTechReqs = cReqs

End Function

