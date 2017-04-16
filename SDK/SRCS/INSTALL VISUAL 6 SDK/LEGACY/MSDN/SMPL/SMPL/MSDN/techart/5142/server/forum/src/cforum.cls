VERSION 1.0 CLASS
BEGIN
  MultiUse = 0   'False
END
Attribute VB_Name = "CForumPvt"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Public Enum enumMessageOffset
    icSourceId = 0
    icDestId = 1
    icMsgType = 2
    icMsgText = 3
End Enum

Public Enum enumSeatsOffset
    icSeatId = 0
    icSeatAlias = 1
    icSeatDisplay = 2
End Enum

Public Enum enumStatus
    [Initializing]
    [Working]
    [Delivering]
    [Processing]
    [Sleeping]
    [Shutting Down]
End Enum

Private m_cSeats        As Collection
Private m_etStatus      As enumStatus
Private m_sAlias        As String
Private m_sDisplayName  As String

' for catching error info
Private m_lErrNo        As Long
Private m_sErrDesc      As String

Public Sub Term()
On Error Resume Next
Dim oSeat As CSeatPvt

If g_lHandle Then g_lHandle = KillTimer(0, g_lHandle)

For Each oSeat In m_cSeats
    oSeat.Term
Next oSeat
Set oSeat = Nothing
Set m_cSeats = Nothing
End Sub

Public Function GetSeats(vData As Variant) As Boolean
Dim oSeat   As CSeatPvt
Dim iBound  As Integer
Dim iIndex  As Integer

On Error GoTo ErrGetSeats:
If g_lHandle Then g_lHandle = KillTimer(0, g_lHandle)

iBound = m_cSeats.Count
If iBound > 0 Then iBound = iBound - 1

ReDim vData(icZero To iBound, icSeatId To icSeatDisplay)
iIndex = 0
For Each oSeat In m_cSeats
    vData(iIndex, icSeatId) = oSeat.SeatId
    vData(iIndex, icSeatAlias) = oSeat.Alias
    vData(iIndex, icSeatDisplay) = oSeat.DisplayName
    iIndex = iIndex + 1
Next
Set oSeat = Nothing
GetSeats = True
g_lHandle = SetTimer(0, 0, g_lInterval, AddressOf TimerProc)
Exit Function

ErrGetSeats:
    g_lHandle = SetTimer(0, 0, g_lInterval, AddressOf TimerProc)
    m_lErrNo = Err.Number
    m_sErrDesc = Err.Description
    On Error GoTo 0
    If m_lErrNo > vbObjectError Then
        Err.Raise m_lErrNo, Trim$(App.Title) & ".CForumPvt.GetSeats", m_sErrDesc
    Else
        Err.Raise m_lErrNo + vbObjectError, Trim$(App.Title) & ".CForumPvt.GetSeats", m_sErrDesc
    End If
    Exit Function
End Function

Private Sub Deliver()
Dim oSeat       As CSeatPvt
Dim oMsg        As CMessagePvt
Dim oWork       As Object
Dim iInCount    As Integer
Dim iIndex      As Integer
Dim vTemp       As Variant

On Error Resume Next
m_etStatus = [Delivering]
For Each oSeat In m_cSeats
    Set oWork = oSeat.Seat
    If Not (oWork Is Nothing) Then
        With oWork
            Err = False
            If .PickUp(vTemp) Then
                If Err = False Then
                    For iIndex = LBound(vTemp, 1) To UBound(vTemp, 1)
                        Set oMsg = New CMessagePvt
                        oMsg.SourceId = CLng(vTemp(iIndex, icSourceId))
                        oMsg.DestinationId = CLng(vTemp(iIndex, icDestId))
                        oMsg.MessageType = CInt(vTemp(iIndex, icMsgType))
                        oMsg.Message = vTemp(iIndex, icMsgText)
                        oSeat.Outgoing.Add oMsg
                        Set oMsg = Nothing
                    Next iIndex
                End If
            End If
            iInCount = 0
            iInCount = oSeat.Incoming.Count
            If iInCount Then
                iIndex = 1
                ReDim vTemp(iIndex To iInCount, icSourceId To icMsgText) As Variant
                For Each oMsg In oSeat.Incoming
                    vTemp(iIndex, icSourceId) = oMsg.SourceId
                    vTemp(iIndex, icDestId) = oMsg.DestinationId
                    vTemp(iIndex, icMsgType) = oMsg.MessageType
                    vTemp(iIndex, icMsgText) = oMsg.Message
                    iIndex = iIndex + 1
                Next oMsg
                Err = False
                If .DropOff(vTemp) Then
                    If Err = False Then oSeat.ClearIncoming
                End If
            End If
        End With
    End If
    Set oWork = Nothing
Next oSeat
m_etStatus = [Sleeping]
End Sub

Public Sub Init(ByVal sNameIn As String, ByVal sAliasIn As String)
On Error Resume Next
m_sDisplayName = Trim$(sNameIn)
m_sAlias = Trim$(sAliasIn)
End Sub

Private Sub Process()
Dim oMsg    As CMessagePvt
Dim oSeat   As CSeatPvt
Dim oWork   As CSeatPvt

On Error GoTo errExit
m_etStatus = [Processing]
For Each oSeat In m_cSeats
    For Each oMsg In oSeat.Outgoing
        Select Case oMsg.MessageType
            Case [Broadcast Message]
                For Each oWork In m_cSeats
                    If oWork.SeatId <> oSeat.SeatId Then
                        oWork.Incoming.Add oMsg
                    End If
                Next oWork
                Set oWork = Nothing
            Case [Private Message]
                For Each oWork In m_cSeats
                    If oWork.SeatId = oMsg.DestinationId Then
                        oWork.Incoming.Add oMsg
                    End If
                Next oWork
                Set oWork = Nothing
        End Select
    Next oMsg
    oSeat.ClearOutgoing
Next oSeat
Set oSeat = Nothing
m_etStatus = [Sleeping]
Exit Sub

errExit:
    Err = False
    Exit Sub
    
End Sub

Public Sub SeatAdd(oSeat As Object)
Dim oSeatPvt As CSeatPvt

On Error Resume Next
If g_lHandle Then g_lHandle = KillTimer(0, g_lHandle)
Set oSeatPvt = New CSeatPvt
Set oSeatPvt.Seat = oSeat
oSeatPvt.SeatId = oSeat.SeatId
oSeatPvt.Alias = oSeat.Alias
oSeatPvt.DisplayName = oSeat.DisplayName
m_cSeats.Add oSeatPvt, oSeatPvt.Alias
Set oSeatPvt = Nothing
g_lHandle = SetTimer(0, 0, g_lInterval, AddressOf TimerProc)
End Sub

Public Sub SeatRemove(ByVal sAlias As String)
On Error Resume Next
If g_lHandle Then g_lHandle = KillTimer(0, g_lHandle)
m_cSeats.Remove sAlias
g_lHandle = SetTimer(0, 0, g_lInterval, AddressOf TimerProc)
End Sub

Public Sub Timer()
On Error Resume Next
Deliver
Process
End Sub

Public Property Get Alias() As String
On Error Resume Next
Alias = m_sAlias
End Property

Public Property Get DisplayName() As String
On Error Resume Next
DisplayName = m_sDisplayName
End Property

Private Sub Class_Initialize()
On Error Resume Next
m_etStatus = [Initializing]
Set m_cSeats = New Collection
Set g_oForum = Me
g_lHandle = SetTimer(0, 0, g_lInterval, AddressOf TimerProc)
m_etStatus = [Sleeping]
End Sub

Private Sub Class_Terminate()
On Error Resume Next
If g_lHandle Then g_lHandle = KillTimer(0, g_lHandle)
Term
End Sub
