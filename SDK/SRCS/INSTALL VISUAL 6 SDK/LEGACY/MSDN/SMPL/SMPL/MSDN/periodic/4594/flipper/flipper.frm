VERSION 4.00
Begin VB.Form frmFlipper 
   Caption         =   "Flipper: The MSJ Finger Demo"
   ClientHeight    =   3600
   ClientLeft      =   5385
   ClientTop       =   3900
   ClientWidth     =   6090
   Height          =   4020
   Left            =   5325
   LinkTopic       =   "Form1"
   ScaleHeight     =   3600
   ScaleWidth      =   6090
   Top             =   3540
   Width           =   6210
   Begin VB.TextBox edtUser 
      Height          =   285
      Left            =   720
      TabIndex        =   0
      Top             =   120
      Width           =   2895
   End
   Begin VB.TextBox edtSite 
      Height          =   285
      Left            =   720
      TabIndex        =   1
      Top             =   480
      Width           =   2895
   End
   Begin VB.CommandButton btnFinger 
      Caption         =   "&Finger"
      Height          =   375
      Left            =   3720
      TabIndex        =   3
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label lblOutput 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   2415
      Left            =   120
      TabIndex        =   6
      Top             =   1080
      Width           =   5895
   End
   Begin VB.Label lblSite 
      Alignment       =   1  'Right Justify
      Caption         =   "Site:"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   600
      Width           =   495
   End
   Begin VB.Label lblUser 
      Alignment       =   1  'Right Justify
      Caption         =   "User:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   240
      Width           =   495
   End
   Begin MSJSOCKLib.MSJSock MSJSockCtrl 
      Height          =   375
      Left            =   5400
      TabIndex        =   2
      Top             =   240
      Width           =   375
      _Version        =   65536
      _ExtentX        =   661
      _ExtentY        =   661
      _StockProps     =   0
   End
End
Attribute VB_Name = "frmFlipper"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
'-----------------------------------------------------
' FLIPPER.FRM
'   This is the form definition for Flipper: The MSJ
'   Finger program.


'-----------------------------------------------------
' When the "Finger" button is clicked, Flipper should
' perform three tasks: create a socket, get the finger
' service port, and get the remote host's IP address
' given its name.

Private Sub btnFinger_Click()
    Dim rc
    sock = MSJSockCtrl.CreateSocket
    fingport = MSJSockCtrl.getservbyname("finger")
    rc = MSJSockCtrl.gethostbyname(edtSite.Text)
End Sub

'-----------------------------------------------------
' When a user types in the site or userid edit boxes,
' the "Finger" button is enabled or disabled depending
' on whether both boxes have data.

Private Sub edtSite_Change()
    If Len(edtUser) = 0 Or Len(edtSite) = 0 Then
        btnFinger.Enabled = False
    Else
        btnFinger.Enabled = True
    End If
End Sub

Private Sub edtUser_Change()
    If Len(edtUser) = 0 Or Len(edtSite) = 0 Then
        btnFinger.Enabled = False
    Else
        btnFinger.Enabled = True
    End If
End Sub

'-----------------------------------------------------
' When the form is loaded, disable the Finger
' button until both userid and site are filled in.

Private Sub Form_Load()
    btnFinger.Enabled = False
End Sub


'-----------------------------------------------------
' MSJSockCtrl_connect is an event called by the MSJSock
' OLE control when a successful connection has been made.
' If you want, you can track a particular task by its handle
' (given here as hTask)

Private Sub MSJSockCtrl_connect(ByVal hTask As Long)
    Dim rcl As Long, rc As Integer
    
    ' Tell the MSJSock control to watch for "ready to read," "ready for more writing,"
    ' and "connection closed" events.
    rcl = MSJSockCtrl.AsyncSelect(sock, FD_READ + FD_WRITE + FD_CLOSE)
    
    ' send() is a direct WINSOCK API call. It sends the indicated
    ' text to the socket specified. In this case, we're just sending
    ' a username to the finger port...
    rc = send(sock, edtUser.Text, Len(edtUser.Text), 0)
    
    ' ...and appending a CR-LF pair.
    rc = send(sock, Chr$(13) & Chr$(10), 2, 0)
End Sub

'-----------------------------------------------------
' When we called gethostbyname when the Finger button is
' clicked, it had to go off and find the host's IP address. When
' the OLE control gets that data back, it returns it by calling
' the GotHost event.

Private Sub MSJSockCtrl_GotHost(ByVal hostent As Long)
    ' Now that we have a pointer to the host's address (in hostent),
    ' we can take the socket we created earlier and connect it to
    ' the appropriate host and its finger port.
    Call MSJSockCtrl.Connect(sock, fingport, hostent)
End Sub

'-----------------------------------------------------
' Whenever our TCP/IP stack receives data from the network,
' it notifies the MSJSock control. In turn, if the control is
' expecting some data, it informs the VB container program
' that data needs to be read by calling the RecvData event.

Private Sub MSJSockCtrl_RecvData(ByVal hTask As Long, ByVal Data As String)
    Dim msg As String
    Dim rc As String
    
    ' Initialize the variable-length string with 1024 blanks - enough room to
    ' read in data.
    msg = Space(1024)
    
    ' recv() is part of WINSOCK.DLL. Since we've just been notified that
    ' there's data to receive, Flipper calls it to receive the data.
    rc = recv(sock, msg, 1024, 0)
    
    ' Trim the network input and display it in the output text box.
    lblOutput = Trim(msg)
End Sub

'-----------------------------------------------------
' If the MSJSock control returns a WinSock error, filter it through our WSERROR.BAS
' and display it for the user.

Private Sub MSJSockCtrl_SockError(ByVal hTask As Long, ByVal ENum As Integer)
    MsgBox "WinSock error " & ENum & "(" & WSErrStr(ENum) & ")", vbOKOnly, "WinSock Error"
End Sub
