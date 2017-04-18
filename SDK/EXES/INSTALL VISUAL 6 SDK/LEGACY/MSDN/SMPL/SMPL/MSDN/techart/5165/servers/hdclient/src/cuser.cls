VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CUser"
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

Private Const OBJNAME = "CUser"

Dim m_cReqs     As Collection   'Requests for User
Dim m_sAlias    As String       'Alias of the user
Dim m_bExpand   As Boolean      'signifies whether already refreshed

'=======================================================================
'Attribute:     Returns EmailAlias of the user.
'=======================================================================
Public Property Get Alias() As String
If Not m_bExpand Then
    Refresh
End If

Alias = m_sAlias
End Property

'=======================================================================
'Attribute:     Sets EmailAlias of the user.
'=======================================================================
Public Property Let Alias(ByVal sNewValue As String)
m_sAlias = sNewValue
End Property

'=======================================================================
'Synopsis:              Fills up the user object attributes. If
'                       Refresh is partial then Requests collection is
'                       not filled.
'Function input:        Boolean value indicating partial or complete refresh
'Function output:       None
'=======================================================================
Private Sub Refresh()

If m_bExpand Then
    Exit Sub
End If

If Trim$(m_sAlias) = vbNullString Then
    Exit Sub
End If

'Reinitalise the object
Clear

'Initialize Details list and clear array
Set m_cReqs = New Collection

Set m_cReqs = GetUserReqs(m_sAlias)

End Sub

Private Sub Term()
Clear
End Sub

'=======================================================================
'Synopsis:              Clears all module level variables
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub Clear()
Dim oReq As hdclient.CRequest

'Clear the objects in the collection
If Not (m_cReqs Is Nothing) Then
    For Each oReq In m_cReqs
        Set oReq = Nothing
    Next
End If
Set m_cReqs = Nothing   'Clear the collection object

End Sub

'=======================================================================
'Attribute:     Returns collection of requests that belong to this
'               user.
'=======================================================================
Public Property Get Requests() As Collection

If Not m_bExpand Then
    Refresh
End If

Set Requests = m_cReqs

End Property

'=======================================================================
'Synopsis:              Returns requests determined
'                       by user.
'Function input:        User identifier.
'Function output:       Returns a collection of requests.
'=======================================================================
Private Function GetUserReqs(ByVal sUserAlias) As Collection
Dim oTrans  As HDServer.CTrans
Dim oReq    As CRequest
Dim cReqs As Collection
Dim sData() As String
Dim lIndex  As Long

Set cReqs = New Collection

Set oTrans = New HDServer.CTrans 'CreateObject("HDServer.CTrans")
If oTrans.GetUserRequests(sUserAlias, sData) Then
    For lIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
        Set oReq = New CRequest
        With oReq
            .TrackingNo = CLng(sData(icReqTrackNo, lIndex))
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
Set GetUserReqs = cReqs

End Function

