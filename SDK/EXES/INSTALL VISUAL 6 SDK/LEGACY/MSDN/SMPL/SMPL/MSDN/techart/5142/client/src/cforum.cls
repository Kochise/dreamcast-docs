VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CForum"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Public Enum enumForumSeatOffset
    icForumSeatId = 0
    icForumSeatAlias = 1
    icForumSeatDisplay = 2
End Enum

Private m_oAdmin        As CAdmin
Private m_cForumSeats   As Collection
Private m_sAlias        As String
Private m_sDisplayName  As String

Public Sub Term()
On Error Resume Next
Set m_cForumSeats = Nothing
Set m_oAdmin = Nothing
End Sub

Public Function GetSeat(sAlias As String, sDisplay As String) As CSeat
Dim oSeat As CSeat
Dim oForum As Object

On Error Resume Next
sAlias = Trim$(sAlias)
sDisplay = Trim$(sDisplay)

Set oSeat = New CSeat
With oSeat
    Set .Admin = m_oAdmin
    .SeatId = m_oAdmin.GetNextId
    .Alias = sAlias
    .DisplayName = sDisplay
    .ForumAlias = m_sAlias
End With

Set oForum = m_oAdmin.GetForumByAlias(m_sAlias)
oForum.SeatAdd oSeat
m_cForumSeats.Add oSeat

Set GetSeat = oSeat
Set oSeat = Nothing
Set oForum = Nothing
End Function

Public Sub Refresh()
Dim oForum      As Object
Dim oForumSeat  As CForumSeat
Dim iIndex      As Integer
Dim vTemp       As Variant

On Error Resume Next
Set m_cForumSeats = Nothing
Set m_cForumSeats = New Collection
Set oForum = m_oAdmin.GetForumByAlias(m_sAlias)
If oForum.GetSeats(vTemp) Then
    For iIndex = LBound(vTemp, 1) To UBound(vTemp, 1)
        Set oForumSeat = New CForumSeat
        With oForumSeat
            .SeatId = CLng(vTemp(iIndex, icForumSeatId))
            .Alias = vTemp(iIndex, icForumSeatAlias)
            .DisplayName = vTemp(iIndex, icForumSeatDisplay)
        End With
        m_cForumSeats.Add oForumSeat, vTemp(iIndex, icForumSeatAlias)
    Next iIndex
End If
Set oForum = Nothing
Set oForumSeat = Nothing
End Sub

Public Property Set Admin(oNewAdmin As CAdmin)
On Error Resume Next
Set m_oAdmin = oNewAdmin
End Property

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

Public Property Get Seats() As Collection
On Error Resume Next
If m_cForumSeats Is Nothing Then Refresh
Set Seats = m_cForumSeats
End Property

Private Sub Class_Terminate()
On Error Resume Next
Term
End Sub
