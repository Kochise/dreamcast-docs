VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CReqDetail"
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

Private Const OBJNAME = "CReqDetail"
Private m_oRequest          As CRequest
Private m_oTech             As CTech
Private m_dtDetDate         As Date
Private m_sDetailText       As String
Private m_lPKId             As Long
Private m_lDetId            As Long
Private m_lDetTypeId        As Long

Private m_bExpanded         As Boolean

'=======================================================================
'Synopsis:              Clears all module level variables
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub Clear()

m_dtDetDate = 0
m_lDetTypeId = 0
m_lDetId = 0
Set m_oTech = Nothing
m_sDetailText = vbNullString

m_bExpanded = False

End Sub

'=======================================================================
'Synopsis:              Fills up the request detail object attributes
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub Refresh()

Dim oTrans  As HDServer.CTrans
Dim oReq    As CRequest
Dim sData() As String

On Error Resume Next

'Continue with getting details if only ReqDetPKId is supplied
If CBool(m_lPKId) Then
    Clear
    Set oTrans = New HDServer.CTrans 'CreateObject("HDServer.CTrans")
    
    'Call method to get the request detail record in the array
    If oTrans.GetReqDetail(m_lPKId, sData) Then
        m_dtDetDate = CDate(sData(icRDDate, icZeroDim)) 'Assign member variables
        m_lDetTypeId = CLng(sData(icRDTypeId, icZeroDim))
        Set m_oTech = New CTech
        m_oTech.PKId = CLng(sData(icRDTechId, icZeroDim))
        m_sDetailText = Trim$(sData(icRDDetMsg, icZeroDim))
    End If
    Set oTrans = Nothing
    m_bExpanded = True          'Set the expanded property to TRUE
End If

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
'Attribute:     Returns ID of Request to which the present Request Detail
'               object belongs
'=======================================================================
Public Property Get Request() As CRequest

If Not m_bExpanded Then     'If the object does not contain details yet
    Refresh                 'Call Refresh to fill up details
End If

Set Request = m_oRequest
End Property

'=======================================================================
'Attribute:     Sets ID of Request to which the present Request Detail
'               object belongs.
'=======================================================================
Public Property Set Request(oRequest As CRequest)
Set m_oRequest = oRequest
End Property

'=======================================================================
'Attribute:     Returns ID of Request detail
'=======================================================================
Public Property Get PKId() As Long
PKId = m_lPKId
End Property

'=======================================================================
'Attribute:     Sets ID of Request detail
'=======================================================================
Public Property Let PKId(ByVal lNewPKId As Long)
m_lPKId = lNewPKId
End Property

'=======================================================================
'Attribute:     Returns ID of Request detail - uses self expansion
'=======================================================================
Public Property Get PKIdEx() As Long

If Not m_bExpanded Then     'If the object does not contain details yet
    Refresh                 'Call Refresh to fill up details
End If

PKIdEx = m_lPKId
End Property

'=======================================================================
'Attribute:     Sets date on which Request Detail was created.
'=======================================================================
Public Property Let DetDate(ByVal dtNewDetDate As Date)
m_dtDetDate = dtNewDetDate
End Property

'=======================================================================
'Attribute:     Returns date on which Request Detail was created.
'=======================================================================
Public Property Get DetDate() As Date

If Not m_bExpanded Then     'If the object does not contain details yet
    Refresh                 'Call Refresh to fill up details
End If

DetDate = m_dtDetDate

End Property

'=======================================================================
'Attribute:     Returns type of request detail object.
'=======================================================================
Public Property Get DetTypeId() As Long

If Not m_bExpanded Then     'If the object does not contain details yet
    Refresh                 'Call Refresh to fill up details
End If

DetTypeId = m_lDetTypeId

End Property

'=======================================================================
'Attribute:     Sets type of Request detail object.
'=======================================================================
Public Property Let DetTypeId(lNewDetTypeId As Long)
m_lDetTypeId = lNewDetTypeId
End Property

'=======================================================================
'Attribute:     Returns ID of technician.
'=======================================================================
Public Property Get Tech() As CTech

If Not m_bExpanded Then     'If the object does not contain details yet
    Refresh                 'Call Refresh to fill up details
End If

Set Tech = m_oTech
End Property

'=======================================================================
'Attribute:     Sets ID of technician.
'=======================================================================
Public Property Set Tech(oNewTech As CTech)
Set m_oTech = oNewTech
End Property
Private Sub Class_Terminate()
Term    'Call terminate function before unloading
End Sub

'=======================================================================
'Attribute:     Returns Id of Detail Text
'=======================================================================
Public Property Get DetId() As Long

If Not m_bExpanded Then     'If the object does not contain details yet
    Refresh                 'Call Refresh to fill up details
End If

DetId = m_lDetId
End Property

'=======================================================================
'Attribute:     Sets ID of detail text.
'=======================================================================
Public Property Let DetId(ByVal lNewValue As Long)
m_lDetId = lNewValue
End Property

'=======================================================================
'Attribute:     Returns Detail Text
'=======================================================================
Public Property Get DetailText() As String
If Not m_bExpanded Then     'If the object does not contain details yet
    Refresh                 'Call Refresh to fill up details
End If

DetailText = m_sDetailText
End Property

'=======================================================================
'Attribute:     Sets Detail Text.
'=======================================================================
Public Property Let DetailText(ByVal sNewValue As String)
m_sDetailText = sNewValue
End Property
