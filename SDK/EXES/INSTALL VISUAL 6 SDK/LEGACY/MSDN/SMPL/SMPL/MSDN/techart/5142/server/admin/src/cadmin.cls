VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CAdminPvt"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Public Enum enumForumOffset
    icFAlias = 0
    icFDisplay = 1
End Enum

Public Enum enumForumSeatOffset
    icSeatAlias = 0
    icForumAlias = 1
End Enum

Private m_cForums       As Collection
Private m_bRefreshed    As Boolean
Private m_cLastForumId  As Long

'Used for temporary storage of error information
Private m_lErrNo        As Long
Private m_sErrDesc      As String

Public Sub Term()
On Error Resume Next
Dim oForum As Object

For Each oForum In m_cForums
    oForum.Term
Next oForum
Set m_cForums = Nothing
End Sub

Public Function GetForums(vData As Variant) As Boolean
Dim oForum As Object
Dim iBound As Integer
Dim iIndex As Integer

On Error GoTo ErrGetForums:
iBound = m_cForums.Count
If iBound > 0 Then iBound = iBound - 1
ReDim vData(icZero To iBound, icFAlias To icFDisplay)
iIndex = 0
For Each oForum In m_cForums
    vData(iIndex, icFAlias) = oForum.Alias
    vData(iIndex, icFDisplay) = oForum.DisplayName
    iIndex = iIndex + 1
Next oForum
Set oForum = Nothing
GetForums = True
Exit Function

ErrGetForums:
    m_lErrNo = Err.Number
    m_sErrDesc = Err.Description
    On Error GoTo 0
    If m_lErrNo > vbObjectError Then
        Err.Raise m_lErrNo, Trim$(App.Title) & ".CAdminPvt.GetForums", m_sErrDesc
    Else
        Err.Raise m_lErrNo + vbObjectError, Trim$(App.Title) & ".CAdminPvt.GetForums", m_sErrDesc
    End If
    Exit Function
End Function

Public Function GetForumByAlias(ByVal sForumAlias As String) As Object
Dim oForum As Object

On Error Resume Next
sForumAlias = Trim$(sForumAlias)
Set oForum = m_cForums(sForumAlias)
Set GetForumByAlias = oForum
Set oForum = Nothing
End Function

Public Function GetNextId() As Long
On Error Resume Next
m_cLastForumId = m_cLastForumId + 1
GetNextId = m_cLastForumId
End Function

Public Sub CreateSampleForums()
'temp method to create sample forums in registry
SaveSetting appname:=App.Title, section:="Registered Forums", _
            Key:="lheart", setting:="Lonely Hearts Club"

SaveSetting appname:=App.Title, section:="Registered Forums", _
            Key:="madhell", setting:="We Are Mad As Hell"

SaveSetting appname:=App.Title, section:="Registered Forums", _
            Key:="noway", setting:="No Way Are You Going To Do It"

SaveSetting appname:=App.Title, section:="Registered Forums", _
            Key:="remember", setting:="Remember The Way It Was"

End Sub

Public Sub Refresh()
Dim oForum  As Object
Dim iIndex  As Integer
Dim lVal    As Long
Dim vTemp   As Variant

On Error GoTo ErrRefresh
Term
Set m_cForums = New Collection
vTemp = GetAllSettings(appname:=App.Title, section:="Registered Forums")
For iIndex = LBound(vTemp, 1) To UBound(vTemp, 1)
    Set oForum = CreateObject("ForumPvt.CForumPvt")
    oForum.Init vTemp(iIndex, icFDisplay), vTemp(iIndex, icFAlias)
    m_cForums.Add oForum, oForum.Alias
    Set oForum = Nothing
Next iIndex
Exit Sub
ErrRefresh:
    m_lErrNo = Err.Number
    m_sErrDesc = Err.Description
    On Error GoTo 0
    If m_lErrNo > vbObjectError Then
        Err.Raise m_lErrNo, Trim$(App.Title) & ".CAdminPvt.Refresh", m_sErrDesc
    Else
        Err.Raise m_lErrNo + vbObjectError, Trim$(App.Title) & ".CAdminPvt.Refresh", m_sErrDesc
    End If
    Exit Sub
End Sub

Public Sub RemoveSeats(ByVal vForumSeats As Variant)
Dim oForum As Object
Dim iIndex As Integer

On Error GoTo errExit
If m_cForums Is Nothing Then Exit Sub
If IsEmpty(vForumSeats) Then Exit Sub
If UBound(vForumSeats, 1) = 0 Then Exit Sub
For iIndex = LBound(vForumSeats, 1) To UBound(vForumSeats, 1)
    Set oForum = m_cForums(vForumSeats(iIndex, icForumAlias))
    oForum.SeatRemove Trim$(vForumSeats(iIndex, icSeatAlias))
    Set oForum = Nothing
Next
Exit Sub

errExit:
    Err = False
    Exit Sub

End Sub

Private Sub Class_Initialize()
On Error Resume Next
Refresh
End Sub

Private Sub Class_Terminate()
On Error Resume Next
Term
End Sub
