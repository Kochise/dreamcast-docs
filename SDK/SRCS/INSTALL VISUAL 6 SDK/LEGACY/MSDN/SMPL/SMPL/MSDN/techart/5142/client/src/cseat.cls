VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CSeat"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Public Enum enumMessageOffset
    icSourceId = 0
    icDestId = 1
    icMsgType = 2
    icMsgText = 3
End Enum

Public Enum enumSeatStatus
    [Listening] = 0
    [Adding Outgoing] = 1
    [Checking Incoming] = 2
End Enum

Private m_oAdmin        As CAdmin
Private m_cIncoming     As Collection
Private m_cOutgoing     As Collection
Private m_etStatus      As enumSeatStatus
Private m_lSeatId       As Long
Private m_sAlias        As String
Private m_sDisplayName  As String
Private m_sForumAlias   As String

Public Sub Term()
On Error Resume Next
m_oAdmin.RemoveSeats m_sAlias, m_sForumAlias
Set m_cIncoming = Nothing
Set m_cOutgoing = Nothing
Set m_oAdmin = Nothing
End Sub
Public Function DropOff(vData As Variant) As Boolean
Dim oMsg    As CMessage
Dim iIndex  As Integer

On Error Resume Next
DropOff = False
If m_etStatus Then Exit Function

Status = [Checking Incoming]
If m_cIncoming Is Nothing Then Set m_cIncoming = New Collection

For iIndex = LBound(vData, 1) To UBound(vData, 1)
    Set oMsg = New CMessage
    oMsg.SourceId = CLng(vData(iIndex, icSourceId))
    oMsg.DestinationId = CLng(vData(iIndex, icDestId))
    oMsg.MessageType = CInt(vData(iIndex, icMsgType))
    oMsg.Message = vData(iIndex, icMsgText)
    m_cIncoming.Add oMsg
    Set oMsg = Nothing
Next iIndex

Status = Listening
DropOff = True
End Function

Public Function PickUp(vData As Variant) As Boolean
Dim oMsg    As CMessage
Dim iBound  As Integer
Dim iIndex  As Integer
Dim vTemp   As Variant

On Error Resume Next
PickUp = False
If m_etStatus Then Exit Function
If m_cOutgoing Is Nothing Then Exit Function

Status = [Adding Outgoing]
iBound = m_cOutgoing.Count
If iBound > 0 Then iBound = iBound - 1
ReDim vTemp(icZero To iBound, icSourceId To icMsgText)
iIndex = 0
For Each oMsg In m_cOutgoing
    Set oMsg = m_cOutgoing(iIndex)
    vTemp(iIndex, icSourceId) = oMsg.SourceId
    vTemp(iIndex, icDestId) = oMsg.DestinationId
    vTemp(iIndex, icMsgType) = oMsg.MessageType
    vTemp(iIndex, icMsgText) = oMsg.Message
    iIndex = iIndex + 1
Next oMsg
Set oMsg = Nothing
vData = vTemp

Set m_cOutgoing = New Collection

Status = Listening
PickUp = True
End Function

Public Sub IncomingClear()
On Error Resume Next
Set m_cIncoming = Nothing
End Sub

Public Property Set Admin(oNewAdmin As CAdmin)
On Error Resume Next
Set m_oAdmin = oNewAdmin
End Property

Public Property Get Alias() As String
On Error Resume Next
Alias = m_sAlias
End Property

Friend Property Let Alias(ByVal sNewAlias As String)
On Error Resume Next
m_sAlias = Trim$(sNewAlias)
End Property

Public Property Get DisplayName() As String
On Error Resume Next
DisplayName = m_sDisplayName
End Property

Friend Property Let DisplayName(ByVal sNewDisplayName As String)
On Error Resume Next
m_sDisplayName = Trim$(sNewDisplayName)
End Property

Public Property Get ForumAlias() As String
On Error Resume Next
ForumAlias = m_sForumAlias
End Property

Friend Property Let ForumAlias(ByVal sNewFAlias As String)
On Error Resume Next
m_sForumAlias = Trim$(sNewFAlias)
End Property

Public Property Get SeatId() As Long
On Error Resume Next
SeatId = m_lSeatId
End Property

Friend Property Let SeatId(ByVal lNewSeatId As Long)
On Error Resume Next
m_lSeatId = lNewSeatId
End Property

Public Property Get Incoming() As Collection
On Error Resume Next
If m_cIncoming Is Nothing Then Set m_cIncoming = New Collection
Set Incoming = m_cIncoming
End Property

Public Property Set Incoming(cIncomingIn As Collection)
On Error Resume Next
Set m_cIncoming = cIncomingIn
End Property

Public Property Get Outgoing() As Collection
On Error Resume Next
If m_cOutgoing Is Nothing Then Set m_cOutgoing = New Collection
Set Outgoing = m_cOutgoing
End Property

Public Property Let Status(ByVal etSeatStatus As enumSeatStatus)
On Error Resume Next
m_etStatus = etSeatStatus
End Property

Private Sub Class_Initialize()
On Error Resume Next
Status = Listening
End Sub

Private Sub Class_Terminate()
On Error Resume Next
Term
End Sub

