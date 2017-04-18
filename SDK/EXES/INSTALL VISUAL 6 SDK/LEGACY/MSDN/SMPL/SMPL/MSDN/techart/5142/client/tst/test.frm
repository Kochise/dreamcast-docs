VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "Form1"
   ClientHeight    =   4365
   ClientLeft      =   60
   ClientTop       =   300
   ClientWidth     =   10035
   LinkTopic       =   "Form1"
   ScaleHeight     =   4365
   ScaleWidth      =   10035
   StartUpPosition =   3  'Windows Default
   Begin VB.ListBox lstForums 
      Height          =   4200
      IntegralHeight  =   0   'False
      Left            =   45
      Sorted          =   -1  'True
      TabIndex        =   11
      Top             =   90
      Width           =   1800
   End
   Begin VB.CommandButton btAutomatic 
      Caption         =   "Automatic"
      Height          =   420
      Left            =   5805
      TabIndex        =   10
      Top             =   1950
      Width           =   1980
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   9480
      Top             =   1935
   End
   Begin VB.ListBox lstSeat2 
      Height          =   1425
      Left            =   3720
      TabIndex        =   9
      Top             =   2460
      Width           =   4785
   End
   Begin VB.ListBox lstSeat1 
      Height          =   1425
      Left            =   3720
      TabIndex        =   8
      Top             =   75
      Width           =   4785
   End
   Begin VB.CommandButton btRefresh 
      Caption         =   "Refresh"
      Default         =   -1  'True
      Height          =   420
      Left            =   3780
      TabIndex        =   7
      Top             =   1950
      Width           =   1980
   End
   Begin VB.TextBox txtSend2 
      Height          =   300
      Left            =   3720
      TabIndex        =   6
      Text            =   "Barrr"
      Top             =   3990
      Width           =   4785
   End
   Begin VB.TextBox txtSend1 
      Height          =   300
      Left            =   3720
      TabIndex        =   5
      Text            =   "Fooo"
      Top             =   1560
      Width           =   4785
   End
   Begin VB.CommandButton btBrd2 
      Caption         =   "Broadcast"
      Height          =   390
      Left            =   8625
      TabIndex        =   4
      Top             =   2895
      Width           =   1350
   End
   Begin VB.CommandButton btMsg2 
      Caption         =   "Message"
      Height          =   390
      Left            =   8625
      TabIndex        =   3
      Top             =   2460
      Width           =   1350
   End
   Begin VB.CommandButton btBrd1 
      Caption         =   "Broadcast"
      Height          =   390
      Left            =   8610
      TabIndex        =   2
      Top             =   525
      Width           =   1350
   End
   Begin VB.CommandButton btMsg1 
      Caption         =   "Message"
      Height          =   390
      Left            =   8610
      TabIndex        =   1
      Top             =   90
      Width           =   1350
   End
   Begin VB.ListBox lstSeats 
      Height          =   4200
      IntegralHeight  =   0   'False
      Left            =   1875
      Sorted          =   -1  'True
      TabIndex        =   0
      Top             =   90
      Width           =   1800
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private m_oAdmin As CAdmin
Private m_oForum As CForum
Private m_oSeat1 As CSeat
Private m_oSeat2 As CSeat

Private Sub btAutomatic_Click()
Timer1.Enabled = Not Timer1.Enabled
End Sub

Private Sub btBrd1_Click()
Dim oMsg As CMessage

Set oMsg = New CMessage
oMsg.Message = txtSend1
m_oSeat1.Status = [Adding Outgoing]
m_oSeat1.Outgoing.Add oMsg
m_oSeat1.Status = Listening
Set oMsg = Nothing
End Sub

Private Sub btBrd2_Click()
Dim oMsg As CMessage

Set oMsg = New CMessage
oMsg.Message = txtSend2
m_oSeat2.Status = [Adding Outgoing]
m_oSeat2.Outgoing.Add oMsg
m_oSeat2.Status = Listening
Set oMsg = Nothing
End Sub

Private Sub btMsg1_Click()
Dim oMsg As CMessage

If lstSeats.ListIndex < 0 Then Exit Sub
Set oMsg = New CMessage
oMsg.Message = txtSend1
oMsg.MessageType = [Private Message]
oMsg.SourceId = m_oSeat1.SeatId
oMsg.DestinationId = lstSeats.ItemData(lstSeats.ListIndex)
m_oSeat1.Status = [Adding Outgoing]
m_oSeat1.Outgoing.Add oMsg
m_oSeat1.Status = Listening
Set oMsg = Nothing
End Sub

Private Sub btMsg2_Click()
Dim oMsg As CMessage

If lstSeats.ListIndex < 0 Then Exit Sub
Set oMsg = New CMessage
oMsg.Message = txtSend2
oMsg.MessageType = [Private Message]
oMsg.SourceId = m_oSeat2.SeatId
oMsg.DestinationId = lstSeats.ItemData(lstSeats.ListIndex)
m_oSeat2.Status = [Adding Outgoing]
m_oSeat2.Outgoing.Add oMsg
m_oSeat2.Status = Listening
Set oMsg = Nothing
End Sub

Private Sub btRefresh_Click()
Dim sTemp As CMessage
m_oSeat1.Status = [Checking Incoming]
For Each sTemp In m_oSeat1.Incoming
    'lstSeat1.AddItem m_oForum.Seats(sTemp.SourceId).Alias & ": " & sTemp.Message
    lstSeat1.AddItem sTemp.Message
Next sTemp
m_oSeat1.IncomingClear
m_oSeat1.Status = Listening

m_oSeat2.Status = [Checking Incoming]
For Each sTemp In m_oSeat2.Incoming
    'lstSeat2.AddItem m_oForum.Seats(sTemp.SourceId).Alias & ": " & sTemp.Message
    lstSeat2.AddItem sTemp.Message
Next sTemp
m_oSeat2.IncomingClear
m_oSeat2.Status = Listening
End Sub

Private Sub Form_Load()
Dim oForum  As CForum

Set m_oAdmin = New CAdmin

For Each oForum In m_oAdmin.Forums
    lstForums.AddItem oForum.Alias & "-" & oForum.DisplayName
Next oForum
On Error Resume Next
lstForums.ListIndex = 0
End Sub

Private Sub Form_Unload(Cancel As Integer)
On Error Resume Next
Set m_oSeat1 = Nothing
Set m_oSeat2 = Nothing
Set m_oForum = Nothing
m_oAdmin.Term
Set m_oAdmin = Nothing
End Sub

Private Sub lstForums_Click()
Dim cSeats  As Collection
Dim oSeat   As CForumSeat
Dim oForum  As CForum

If lstForums.ListIndex < 0 Then Exit Sub
Set m_oForum = m_oAdmin.Forums(Left$(lstForums.Text, InStr(lstForums.Text, "-") - 1))

If m_oForum Is Nothing Then Exit Sub

'On Error Resume Next
'm_oSeat1.Term
'Set m_oSeat1 = Nothing
'm_oSeat2.Term
'Set m_oSeat2 = Nothing
'On Error GoTo 0
'Set m_oSeat1 = m_oForum.GetSeat("kenbe", "Ken Bergmann")
'Set m_oSeat2 = m_oForum.GetSeat("robcol", "Robert Coleridge")

m_oForum.Refresh

lstSeats.Clear
For Each oSeat In m_oForum.Seats
    lstSeats.AddItem oSeat.DisplayName & " [" & oSeat.Alias & "]"
    lstSeats.ItemData(lstSeats.NewIndex) = oSeat.SeatId
Next oSeat
On Error Resume Next
lstSeats.ListIndex = 0
End Sub

Private Sub Timer1_Timer()
btRefresh_Click
End Sub
