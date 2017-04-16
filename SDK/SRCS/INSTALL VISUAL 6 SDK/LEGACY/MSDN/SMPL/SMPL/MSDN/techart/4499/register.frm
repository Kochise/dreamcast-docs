VERSION 4.00
Begin VB.Form Register 
   Caption         =   "Guest Registration"
   ClientHeight    =   2895
   ClientLeft      =   1890
   ClientTop       =   1605
   ClientWidth     =   4260
   Height          =   3300
   Left            =   1830
   LinkTopic       =   "Form1"
   ScaleHeight     =   2895
   ScaleWidth      =   4260
   Top             =   1260
   Width           =   4380
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Left            =   2880
      Top             =   1560
   End
   Begin VB.CommandButton cmdAvail 
      Caption         =   "Available"
      Height          =   375
      Left            =   2520
      TabIndex        =   1
      Top             =   720
      Width           =   1455
   End
   Begin VB.CommandButton cmdMntDown 
      Caption         =   "Down for Maint"
      Height          =   375
      Left            =   2520
      TabIndex        =   0
      Top             =   120
      Width           =   1455
   End
   Begin VB.Frame Frame1 
      Caption         =   "Rooms"
      Height          =   2055
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   2295
      Begin MSGrid.Grid grdRooms 
         Height          =   1455
         Left            =   120
         TabIndex        =   3
         Top             =   360
         Width           =   1935
         _Version        =   65536
         _ExtentX        =   3413
         _ExtentY        =   2566
         _StockProps     =   77
         BackColor       =   16777215
         Cols            =   3
         FixedRows       =   0
         FixedCols       =   0
      End
   End
   Begin VB.Label lblError 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   120
      TabIndex        =   4
      Top             =   2280
      Width           =   3975
      WordWrap        =   -1  'True
   End
End
Attribute VB_Name = "Register"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
' This example demonstrates a key OLE concept
' regarding the interface "contract".
' The contract with the RoomMgr interface specifies that
' it will provide real-time, refreshed room information
' as well as enforcement of any and all business rules
' to any client that wishes to participate in the
' contract.  However, clients that wish to participate
' in the RoomMgr contract must support a Notification
' interface as part of the terms and conditions
' of their aggreement with the
' RoomMgr.  The actual way in which they implement
' that interface is up to them, as long as they adhere
' to the specifications of the interface as determined
' in the RoomMgr contract.

' To use this demonstration you should start up
' two or more Register clients and note how the
' RoomMgr keeps track of all collected client apps.
' Then, by clicking on a specific room within
' the grid control and pushing either the
' Available button or the Maintenance button,
' note how all clients are updated real-time
' with the new information from the RoomMgr server.

' Although this particular demonstration does
' not incorporate any data services, it's somewhat
' academic to see how it would.  What is interesting,
' however is to extrapolate from this example how
' the business components and data services might
' be handled in a full enterprise where you might
' want a centralized reservation server that
' maintains the reservation objects world-wide and
' is used by the individual RoomMgr servers to
' support both real-time reservations made
' at the hotel and
' through call-ins to a centralized 1-800 number.




Option Explicit
Dim RoomMgr As New RoomMgr.Server
Dim Notify As New Notify
Dim vResult As Variant


Private Sub cmdAvail_Click()
    Dim oRoom As Object
    Dim vResult As Variant
    
    Set oRoom = RoomMgr.Rooms(grdRooms.Row)
    vResult = oRoom.ChangeStatus(Notify, "Avail")
    vResult = RoomMgr.RefreshClientItem(oRoom)


End Sub

Private Sub cmdMntDown_Click()
    Dim oRoom As Object
    Dim vResult As Variant

    Set oRoom = RoomMgr.Rooms(grdRooms.Row)
    vResult = oRoom.ChangeStatus(Notify, "Mnt")
    If vResult = 0 Then
        vResult = RoomMgr.RefreshClientItem(oRoom)
    Else
        Beep
        lblError = gszLastError
    End If

End Sub

Private Sub Form_Load()
    'Set Notify = CreateObject("Regist.Notify")
    'Set RoomMgr = CreateObject("RoomMgr.Server")
    grdRooms.Rows = RoomMgr.GetTotalRooms

    vResult = RoomMgr.Connect(Notify)
    ' The above call provides the OLE server
    ' with the callback object to be used in
    ' updating the grid control.  The Connect
    ' function on the server is responsible for
    ' using this callback to initially provide the client
    ' with the current information on all of
    ' the rooms.  Note that even different client
    ' applications could potentially participate
    ' in these sorts of updates simply by
    ' implementing a Notify-like class that supports
    ' the same functions as this Notify class.
    ' This is the fundamental idea behind the interface
    ' contract whereby an interface is defined
    ' as a set of related functions that are
    ' expected to behave within certain general
    ' guidelines, but their actual implementations
    ' may differ.  In other words, in order for
    ' any client to participate in the "RoomMgr"
    ' contract, it must provide, as part of that
    ' contract, a notification interface defined
    ' in a specific manner.  Otherwise, it cannot
    ' participate in the contract.
    
    
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    vResult = RoomMgr.Disconnect(Notify)
    Set Notify = Nothing
    Set RoomMgr = Nothing
    
End Sub

Private Sub Timer1_Timer()
    vResult = RoomMgr.Disconnect(Notify)
    Set Notify = Nothing
    Set RoomMgr = Nothing
    End
End Sub
