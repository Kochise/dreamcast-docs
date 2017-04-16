VERSION 4.00
Begin VB.Form frmSimple 
   Caption         =   "MSJ Simple Sockets"
   ClientHeight    =   6705
   ClientLeft      =   1215
   ClientTop       =   1545
   ClientWidth     =   8445
   Height          =   7125
   Left            =   1155
   LinkTopic       =   "Form1"
   ScaleHeight     =   6705
   ScaleWidth      =   8445
   Top             =   1185
   Width           =   8565
   Begin VB.CommandButton btnSend 
      Caption         =   "&Send"
      Height          =   375
      Left            =   7440
      TabIndex        =   8
      Top             =   1080
      Width           =   855
   End
   Begin VB.TextBox edtOutput 
      Height          =   285
      Left            =   120
      TabIndex        =   7
      Top             =   1200
      Width           =   7215
   End
   Begin VB.TextBox edtPort 
      Height          =   285
      Left            =   840
      TabIndex        =   4
      Text            =   "119"
      Top             =   480
      Width           =   2895
   End
   Begin VB.TextBox edtSite 
      Height          =   285
      Left            =   840
      TabIndex        =   1
      Text            =   "nntp.ix.netcom.com"
      Top             =   120
      Width           =   2895
   End
   Begin VB.CommandButton btnConnect 
      Caption         =   "Connect"
      Height          =   375
      Left            =   3840
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label5 
      BackStyle       =   0  'Transparent
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Outbound"
      ForeColor       =   &H00008000&
      Height          =   255
      Left            =   5520
      TabIndex        =   12
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label4 
      BackStyle       =   0  'Transparent
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Inbound"
      ForeColor       =   &H000000FF&
      Height          =   255
      Left            =   6840
      TabIndex        =   11
      Top             =   480
      Width           =   1455
   End
   Begin VB.Label Label3 
      BackStyle       =   0  'Transparent
      BorderStyle     =   1  'Fixed Single
      Caption         =   "WinSock Errors"
      Height          =   255
      Left            =   5520
      TabIndex        =   10
      Top             =   480
      Width           =   1215
   End
   Begin VB.Label Label2 
      BackStyle       =   0  'Transparent
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Info"
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   6840
      TabIndex        =   9
      Top             =   120
      Width           =   1455
   End
   Begin RichtextLib.RichTextBox redInOut 
      Height          =   5055
      Left            =   120
      TabIndex        =   6
      Top             =   1560
      Width           =   8175
      _Version        =   65536
      _ExtentX        =   14420
      _ExtentY        =   8916
      _StockProps     =   69
      BackColor       =   -2147483643
      ScrollBars      =   2
      TextRTF         =   $"Simple Sockets.frx":0000
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "Port:"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   480
      Width           =   615
   End
   Begin VB.Label lblSite 
      Alignment       =   1  'Right Justify
      Caption         =   "Server:"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   120
      Width           =   615
   End
   Begin MSJSOCKLib.MSJSock MSJSockCtrl 
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   375
      _Version        =   65536
      _ExtentX        =   661
      _ExtentY        =   661
      _StockProps     =   0
   End
End
Attribute VB_Name = "frmSimple"
Attribute VB_Creatable = False
Attribute VB_Exposed = False


' SIMPLE SOCKETS.FRM -
'   This is the main (and only) form for the MSJ Simple Sockets program.
'   It connects to a user-supplied server and port, and allows the user to 
'   interactively type commands to the server. Results are shown in a jaunty,
'   multicolored rich text edit box.


'--------------------------------------------------------------------------

Private Sub btnConnect_Click()
    ' Using the MSJSock control, create a socket
    sock = MSJSockCtrl.CreateSocket

    ' Get the port the user typed in, as an integer
    port = CInt(edtPort.Text)

    ' Look up the user-supplied host name. This will come back as a
    ' GotHost event later on, at which point the connection will continue.
    host = MSJSockCtrl.gethostbyname(edtSite.Text)

    ' Add informational text to the output RTE (rich text edit), colored blue
    Call DebugToList("Connecting to host " & edtSite.Text & " port " _
                     & port & Chr$(13) & Chr$(10), RGB(0, 0, 255))
End Sub

'--------------------------------------------------------------------------

Private Sub btnSend_Click()
    ' When the user clicks the send button, send their current typed-in
    ' command, with a CR-LF appended
    rc = WSSend(sock, edtOutput.Text & Chr$(13) & Chr$(10))
End Sub

'--------------------------------------------------------------------------

Private Sub edtOutput_KeyPress(KeyAscii As Integer)
    ' If the user hits <enter>, treat it just as if they'd clicked the
    ' Send button.
    If KeyAscii = 13 Or KeyAscii = 10 Then
        btnSend_Click
    End If
End Sub

'--------------------------------------------------------------------------

Private Sub MSJSockCtrl_connect(ByVal hTask As Long)
    Dim rcl As Long
    
    ' When the host connects, print an informational message to the RTE
    Call DebugToList("Connected to host." & Chr$(13) & Chr$(10), RGB(0, 0, 255))
    
    ' Now that you're connected, have the MSJSock control capture read and
    ' write messages
    rcl = MSJSockCtrl.AsyncSelect(sock, FD_READ + FD_WRITE + FD_CLOSE)
End Sub

'--------------------------------------------------------------------------

Private Sub MSJSockCtrl_GotHost(ByVal hostent As Long)
    Dim rcl As Long

    ' Once you've found the host, tell the MSJSock control to form a
    ' connection to it using the current socket and user-indicated port.
    rcl = MSJSockCtrl.Connect(sock, port, hostent)
End Sub

'--------------------------------------------------------------------------

Private Sub MSJSockCtrl_RecvData(ByVal hTask As Long, ByVal Data As String)
    Dim msg As String
    
    ' When the MSJSock control receives incoming data, call the WinSock
    ' recv API function to retrieve it 10k at a time.
    msg = Space(10240)
    rc = recv(sock, msg, 10240, 0)

    msg = Trim(msg)

    ' Put the received information into the RTE box using red text, so you
    ' can tell it from other messages.
    DebugToList msg, RGB(127, 0, 0)
End Sub

'--------------------------------------------------------------------------

Private Sub MSJSockCtrl_SockError(ByVal hTask As Long, ByVal ENum As Integer)
    ' Print WinSock errors to the RTE using black.
    DebugToList "WinSock error " & ENum & ": " & WSErrStr(ENum) & Chr$(13) & Chr$(10), RGB(0, 0, 0)
End Sub

'--------------------------------------------------------------------------

Sub DebugToList(dbgtxt As String, clr As Long)
    Dim prvlen As Long
    
    ' DebugToList appends colored text to a rich text edit (RTE) box. Since
    ' you can't just do Ctrl.Text = Ctrl.Text + newtext (you'd overwrite all
    ' the old formatting, you have to move the insertion point to the end
    ' and insert new text.

    ' Find the location the new text will start (at the end of the old text)
    prvlen = Len(redInOut.Text)

    ' Move the insertion point to the end of the RTE box
    redInOut.SelStart = Len(redInOut.Text) + 1

    ' Replace the selection (which is nothing right now) with the new
    ' text, appending it without changing the previous formatting.
    redInOut.SelText = dbgtxt

    ' Now select the entire inserted text
    redInOut.SelStart = prvlen
    redInOut.SelLength = Len(dbgtxt)

    ' Change the selected (newly inserted) text to the requested color
    redInOut.SelColor = clr


    ' Move the insertion point back to the end of the RTE
    redInOut.SelStart = Len(redInOut.Text) + 1
End Sub

'--------------------------------------------------------------------------

Sub HandleWSError(rc As Integer)
    ' Check for an unhandled WinSock error. If there is one, handle it
    ' just like an error coming in from the MSJSock control.
    If (rc = SOCKET_ERROR) Then
        WSErrorN = WSAGetLastError()
        Call MSJSockCtrl_SockError(-1, WSErrorN)
    End If
End Sub

'--------------------------------------------------------------------------

Function WSSend(wsock As Long, strg As String) As Integer
    Dim rc As Integer

    ' As the user sends data, send it to the RTE in green.
    DebugToList strg, RGB(0, 127, 0)

    ' Call the WinSock API send function to send the data.
    rc = send(wsock, strg, Len(strg), 0)
    
    DoEvents

    ' Check to see if send returned an error. If so, it will be handled
    ' by HandleWSError
    HandleWSError rc
    WSSend = rc
End Function
