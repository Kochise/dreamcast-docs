VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CSeatPvt"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private m_oSeat         As Object
Private m_cIncoming     As Collection
Private m_cOutgoing     As Collection
Private m_lSeatId       As Long
Private m_sAlias        As String
Private m_sDisplayName  As String

Public Sub Term()
On Error Resume Next
Set m_cOutgoing = Nothing
Set m_cIncoming = Nothing
Set m_oSeat = Nothing
End Sub

Public Sub ClearIncoming()
On Error Resume Next
Set m_cIncoming = New Collection
End Sub

Public Sub ClearOutgoing()
On Error Resume Next
Set m_cOutgoing = New Collection
End Sub

Public Property Get Alias() As String
On Error Resume Next
Alias = m_sAlias
End Property

Public Property Let Alias(ByVal sNewValue As String)
On Error Resume Next
m_sAlias = Trim$(sNewValue)
End Property

Public Property Get DisplayName() As String
On Error Resume Next
DisplayName = m_sDisplayName
End Property

Public Property Let DisplayName(ByVal sNewValue As String)
On Error Resume Next
m_sDisplayName = Trim$(sNewValue)
End Property

Public Property Get SeatId() As Long
On Error Resume Next
SeatId = m_lSeatId
End Property

Public Property Let SeatId(ByVal lNewValue As Long)
On Error Resume Next
m_lSeatId = lNewValue
End Property

Public Property Get Incoming() As Collection
On Error Resume Next
If m_cIncoming Is Nothing Then Set m_cIncoming = New Collection
Set Incoming = m_cIncoming
End Property

Public Property Get Outgoing() As Collection
On Error Resume Next
If m_cOutgoing Is Nothing Then Set m_cOutgoing = New Collection
Set Outgoing = m_cOutgoing
End Property

Public Property Get Seat()
On Error Resume Next
Set Seat = m_oSeat
End Property

Public Property Set Seat(oNewSeat As Object)
On Error Resume Next
Set m_oSeat = oNewSeat
End Property

Private Sub Class_Terminate()
On Error Resume Next
Term
End Sub

