VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CAdmin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Public Enum enumForumOffset
    icForumAlias = 0
    icForumDisplay = 1
End Enum

Public Enum enumSeatOffset
    icSeatAlias = 0
    icSeatForumAlias = 1
End Enum

Private Const scSeatAlias = "SeatAlias"
Private Const scForumAlias = "ForumAlias"

Private m_oAdminPvt As Object
Private m_oPool As Object
Private m_cForums   As Collection
Private m_cSeats    As Collection

'Used for temporary storage of error information
Private m_lErrNo        As Long
Private m_sErrDesc      As String

Public Sub Term()
Dim oForum As CForum
Dim oSeat  As CSeat

On Error Resume Next
For Each oForum In m_cForums
    oForum.Term
Next oForum
Set m_cForums = Nothing

For Each oSeat In m_cSeats
    oSeat.Term
Next oSeat
Set m_cSeats = Nothing
RemoveSeats
Set m_oAdminPvt = Nothing
End Sub

Friend Function GetForumByAlias(sAlias As String) As Object
On Error Resume Next
Set GetForumByAlias = m_oAdminPvt.GetForumByAlias(sAlias)
End Function

Friend Function GetNextId() As Long
On Error Resume Next
GetNextId = m_oAdminPvt.GetNextId
End Function

Friend Sub AddSeat(oSeat As CSeat, oForum As CForum)
Dim cTemp As Collection

On Error Resume Next
Set cTemp = New Collection
If m_cSeats Is Nothing Then Set m_cSeats = New Collection
cTemp.Add oSeat.Alias, scSeatAlias
cTemp.Add oForum.Alias, scForumAlias
m_cSeats.Add cTemp, oSeat.Alias
Set cTemp = Nothing
End Sub

Public Sub Refresh()
Dim oForum  As CForum
Dim iIndex  As Integer
Dim vTemp   As Variant

On Error Resume Next
On Error GoTo 0
Set m_cForums = New Collection
If m_oAdminPvt.GetForums(vTemp) Then
    For iIndex = LBound(vTemp, 1) To UBound(vTemp, 1)
        Set oForum = New CForum
        With oForum
            Set .Admin = Me
            .Alias = Trim$(vTemp(iIndex, icForumAlias))
            .DisplayName = Trim$(vTemp(iIndex, icForumDisplay))
        End With
        oForum.Refresh
        m_cForums.Add oForum, vTemp(iIndex, icForumAlias)
    Next iIndex
    Set oForum = Nothing
End If
End Sub

Friend Sub RemoveSeats(Optional sAlias As String, Optional sForumAlias As String)
Dim cTemp   As Collection
Dim iIndex  As Integer
Dim iBound  As Integer
Dim vTemp   As Variant

On Error Resume Next
If Len(sAlias) Then
    ReDim vTemp(icZero To icZero, icSeatAlias To icSeatForumAlias)
    vTemp(icZero, icSeatAlias) = Trim$(sAlias)
    vTemp(icZero, icSeatForumAlias) = Trim$(sForumAlias)
    m_oAdminPvt.RemoveSeats vTemp
    m_cSeats.Remove sAlias
Else
    If m_cSeats Is Nothing Then Exit Sub
    iBound = m_cSeats.Count
    If iBound > 0 Then iBound = iBound - 1
    ReDim vTemp(icZero To iBound, icSeatAlias To icSeatForumAlias)
    iIndex = 0
    For Each cTemp In m_cSeats
        vTemp(iIndex, icSeatAlias) = cTemp(scSeatAlias)
        vTemp(iIndex, icSeatForumAlias) = cTemp(scForumAlias)
        iIndex = iIndex + 1
    Next cTemp
    m_oAdminPvt.RemoveSeats vTemp

    Set m_cSeats = New Collection
End If
Set cTemp = Nothing
End Sub

Public Property Get Forums() As Collection
On Error Resume Next
If m_cForums Is Nothing Then Refresh
Set Forums = m_cForums
End Property

Private Sub Class_Initialize()
On Error GoTo ErrClass_Initialize
Set m_oPool = CreateObject("ForumPool.CPool")
Set m_oAdminPvt = m_oPool.GetForumService()
If m_oAdminPvt Is Nothing Then
    On Error GoTo 0
    Err.Raise vbObjectError, Trim$(App.Title) & ".CAdminPvt.Class_Initialize", "Error creating oAdminPvt"
End If
Set m_oPool = Nothing
Exit Sub
ErrClass_Initialize:
ErrRefresh:
    m_lErrNo = Err.Number
    m_sErrDesc = Err.Description
    On Error GoTo 0
    If m_lErrNo > vbObjectError Then
        Err.Raise m_lErrNo, Trim$(App.Title) & ".CAdmin.Class_Initialize", m_sErrDesc
    Else
        Err.Raise m_lErrNo + vbObjectError, Trim$(App.Title) & ".CAdminPvt.Class_Initialize", m_sErrDesc
    End If
    Exit Sub
End Sub

Private Sub Class_Terminate()
On Error Resume Next
Term
End Sub
