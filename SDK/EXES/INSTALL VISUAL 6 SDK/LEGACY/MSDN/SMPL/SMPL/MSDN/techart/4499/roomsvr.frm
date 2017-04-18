VERSION 4.00
Begin VB.Form RoomSvr 
   Caption         =   "Room Server"
   ClientHeight    =   1065
   ClientLeft      =   1785
   ClientTop       =   5805
   ClientWidth     =   6165
   Height          =   1470
   Left            =   1725
   LinkTopic       =   "Form1"
   ScaleHeight     =   1065
   ScaleWidth      =   6165
   Top             =   5460
   Width           =   6285
   Begin VB.TextBox txtSeconds 
      Height          =   375
      Left            =   3960
      TabIndex        =   5
      Text            =   "5"
      Top             =   600
      Width           =   615
   End
   Begin VB.CommandButton cmdShutdown 
      Caption         =   "Shut Down All Clients"
      Height          =   375
      Left            =   840
      TabIndex        =   4
      Top             =   600
      Width           =   2895
   End
   Begin VB.CheckBox ckPrimeHours 
      Caption         =   "Prime Hours in Effect"
      Height          =   255
      Left            =   3600
      TabIndex        =   3
      Top             =   120
      Width           =   2295
   End
   Begin VB.CommandButton btnStop 
      Caption         =   "Stop"
      Height          =   375
      Left            =   2280
      TabIndex        =   2
      Top             =   120
      Width           =   1095
   End
   Begin VB.Label Label2 
      Caption         =   "Seconds"
      Height          =   375
      Left            =   4680
      TabIndex        =   6
      Top             =   600
      Width           =   975
   End
   Begin VB.Label lblActiveClients 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      Height          =   375
      Left            =   1560
      TabIndex        =   1
      Top             =   120
      Width           =   615
   End
   Begin VB.Label Label1 
      Caption         =   "Active Clients:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   1215
   End
End
Attribute VB_Name = "RoomSvr"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
' The RoomSvr is an implementation of the
' RoomMgr interface contract for providing
' real-time room information to any client
' that adheres to the specifications of the
' contract.  It also introduces an interesting
' design model facilitated by OLE whereby program logic
' can be dynamically changed during runtime.
' This can be seen in the usage of the two classes
' known as PrimeRule and NonPrimeRule.  Again,
' because the RoomMgr specifies a certain,
' consistent interface for status changes on a rule,
' different rules can be "hooked" on and executed
' during runtime.  This provides the facility
' for other programmers to independently define
' those rules and be assured that they will be
' compatible with the RoomMgr.  Again, the
' way in which they implement the rules is up to
' them.  The only requirement is that they adhere
' to the RoomMgr specifications.


Option Explicit

Private Sub btnStop_Click()
    If gnActiveClients > 0 Then
        MsgBox "Unable to terminate...clients are active"
        Exit Sub
    Else
        End
    End If
    
End Sub

Private Sub ckPrimeHours_Click()
' Apply the appropriate rule based on the status
' of the checkbox.  Naturally, the RoomMgr logic
' for hooking in different rules could vary.
' For example, it could be based on time, or the
' implementation of the logic could be specified
' within the registry to be set up by the RoomSvr
' at start-up time.  The latter, for example, might
' allow an external programming staff to design their
' own business logic that could be applied in lieu of
' the default logic provided by the RoomSvr.  This is
' the fundamental power of strongly typed and encapsulated
' interfaces.

    Set gPrimeRule = Nothing
    If ckPrimeHours.VALUE = 1 Then
        Set gPrimeRule = New PrimeRule
    Else
        Set gPrimeRule = New NonPrimeRule
    End If
    
End Sub

Private Sub cmdShutdown_Click()
    Dim nCnt As Integer
    
    For nCnt = 0 To gnActiveClients - 1
        gCliList(nCnt).ShutDown txtSeconds.TEXT
    Next nCnt
    
End Sub

Private Sub Form_Load()
    Dim nCnt As Integer
    Dim vResult As Variant

 'Dim and initialize the rooms collection
    gnNumRooms = MAX_CLIENTS
    ReDim gRoomList(gnNumRooms)
    For nCnt = 0 To gnNumRooms - 1
        Set gRoomList(nCnt) = New Room
        vResult = gRoomList(nCnt).Initialize(nCnt, "", 100 + nCnt, "Avail")
    Next nCnt

 'Initialize other variables
    gnActiveClients = 0
    Set gPrimeRule = New NonPrimeRule 'default rule
    

End Sub

Private Sub Form_Unload(Cancel As Integer)
    Dim nCnt As Integer

    Set gPrimeRule = Nothing
    
    For nCnt = 0 To gnNumRooms - 1
        Set gRoomList(nCnt) = Nothing
    Next nCnt
    
End Sub
