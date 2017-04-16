VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CForumSeat"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private m_lSeatId       As Long
Private m_sAlias        As String
Private m_sDisplayName  As String

Public Property Get Alias() As String
On Error Resume Next
Alias = m_sAlias
End Property

Public Property Let Alias(ByVal sNewAlias As String)
On Error Resume Next
m_sAlias = Trim$(sNewAlias)
End Property

Public Property Get DisplayName() As String
On Error Resume Next
DisplayName = m_sDisplayName
End Property

Public Property Let DisplayName(ByVal sNewDisplayName As String)
On Error Resume Next
m_sDisplayName = Trim$(sNewDisplayName)
End Property

Public Property Get SeatId() As Long
On Error Resume Next
SeatId = m_lSeatId
End Property

Public Property Let SeatId(ByVal lNewSeatId As Long)
On Error Resume Next
m_lSeatId = lNewSeatId
End Property

