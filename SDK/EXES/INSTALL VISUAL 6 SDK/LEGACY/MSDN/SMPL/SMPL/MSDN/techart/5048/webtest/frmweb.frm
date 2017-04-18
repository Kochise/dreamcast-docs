VERSION 5.00
Object = "{48E59290-9880-11CF-9754-00AA00C00908}#1.0#0"; "MSINET.OCX"
Begin VB.Form frmWeb 
   Caption         =   "Web Test Client "
   ClientHeight    =   6615
   ClientLeft      =   3150
   ClientTop       =   1785
   ClientWidth     =   7020
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   ScaleHeight     =   6615
   ScaleWidth      =   7020
   Begin VB.TextBox txtMachine 
      Height          =   285
      Left            =   1080
      TabIndex        =   11
      Top             =   480
      Width           =   5775
   End
   Begin InetCtlsObjects.Inet Inet1 
      Left            =   120
      Top             =   6360
      _ExtentX        =   1005
      _ExtentY        =   1005
      RequestTimeout  =   600
   End
   Begin VB.TextBox txtHTML 
      Height          =   2295
      Left            =   120
      MultiLine       =   -1  'True
      TabIndex        =   9
      Top             =   4200
      Width           =   6735
   End
   Begin VB.TextBox txtURL 
      Height          =   285
      Left            =   1080
      TabIndex        =   1
      Text            =   "http://brianlab2/aspsamp/IOSim.asp"
      Top             =   120
      Width           =   5775
   End
   Begin VB.Frame frmMode 
      Caption         =   "Mode"
      Height          =   2535
      Left            =   120
      TabIndex        =   2
      Top             =   840
      Width           =   6735
      Begin VB.CommandButton cmdStopLog 
         Caption         =   "Stop Logging"
         Height          =   495
         Left            =   2160
         TabIndex        =   8
         Top             =   1800
         Width           =   1575
      End
      Begin VB.CommandButton cmdStartLog 
         Caption         =   "Start Logging"
         Height          =   495
         Left            =   240
         TabIndex        =   7
         Top             =   1800
         Width           =   1575
      End
      Begin VB.CommandButton cmdStopRequests 
         Caption         =   "Stop Requests"
         Height          =   495
         Left            =   2160
         TabIndex        =   6
         Top             =   1200
         Width           =   1575
      End
      Begin VB.CommandButton cmdStartRequests 
         Caption         =   "Start Requests"
         Height          =   495
         Left            =   240
         TabIndex        =   5
         Top             =   1200
         Width           =   1575
      End
      Begin VB.OptionButton optRequest 
         Caption         =   "Request Mode"
         Height          =   375
         Left            =   240
         TabIndex        =   4
         Top             =   720
         Value           =   -1  'True
         Width           =   1815
      End
      Begin VB.OptionButton optLog 
         Caption         =   "Adminstrate Log Mode "
         Height          =   375
         Left            =   240
         TabIndex        =   3
         Top             =   240
         Width           =   2175
      End
      Begin VB.Label lblLogStatus 
         Height          =   375
         Left            =   4200
         TabIndex        =   20
         Top             =   720
         Width           =   1215
      End
      Begin VB.Label Label4 
         Caption         =   "Logging Time"
         Height          =   255
         Left            =   2640
         TabIndex        =   19
         Top             =   720
         Width           =   1455
      End
      Begin VB.Label lblRequestStatus 
         Height          =   255
         Left            =   4200
         TabIndex        =   18
         Top             =   360
         Width           =   1215
      End
      Begin VB.Label Label3 
         Caption         =   "Requesting Objects"
         Height          =   375
         Left            =   2640
         TabIndex        =   17
         Top             =   360
         Width           =   1575
      End
   End
   Begin VB.Label lblTimeRequest 
      Height          =   255
      Left            =   4200
      TabIndex        =   16
      Top             =   3840
      Width           =   1815
   End
   Begin VB.Label Label2 
      Caption         =   "Time for Last Request"
      Height          =   255
      Left            =   2160
      TabIndex        =   15
      Top             =   3840
      Width           =   1695
   End
   Begin VB.Label lblTotalRequests 
      Height          =   255
      Left            =   4200
      TabIndex        =   14
      Top             =   3480
      Width           =   1695
   End
   Begin VB.Label Label1 
      Caption         =   "Total Number Requests"
      Height          =   255
      Left            =   2160
      TabIndex        =   13
      Top             =   3480
      Width           =   1935
   End
   Begin VB.Label lblMachine 
      Caption         =   "Machine"
      Height          =   255
      Left            =   240
      TabIndex        =   12
      Top             =   480
      Width           =   615
   End
   Begin VB.Label lblHTMLResults 
      Caption         =   "HTML Results"
      Height          =   255
      Left            =   120
      TabIndex        =   10
      Top             =   3600
      Width           =   1815
   End
   Begin VB.Label lblURL 
      Caption         =   "URL:"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   615
   End
End
Attribute VB_Name = "frmWeb"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Declare Function GetTickCount Lib "kernel32" () As Long

Private blnStopRequests As Boolean

'**************************************************
'Purpose: Sends a message to the server to start
'logging the results to the MachineTimes database
'***************************************************
Private Sub cmdStartLog_Click()

Dim ulCounter As Long


On Error GoTo ErrHandler
    
    Inet1.OpenURL (txtURL.Text & "?LogResults=Start")
    lblLogStatus.Caption = "Logging Results"
    DoEvents
    
Exit Sub

ErrHandler:
    
    'Try again
    For ulCounter = 1 To 5
    DoEvents
    Next ulCounter
    Resume
    
End Sub



'************************************************************************
'Sends continual requsest to the server to access the URL listed in
'txtMachine.Text.
'************************************************************************
Private Sub cmdStartRequests_Click()
    
    
Dim dwStartTime As Long
Dim dwFinishTime As Long
Dim strAccessTime As String
Dim strResult As String
Dim ulCounter As Long
Static ulTotalNumberRequests As Long

If (txtMachine.Text = "") Then
    txtMachine.Text = "Machine1"
End If

On Error GoTo ErrHandler

blnStopRequests = False
strAccessTime = "0"
ulTotalNumberRequests = 0

    Do Until (blnStopRequests = True)

StartCycle:

        'Here is where the time for the request is gained-the result is stored and sent in the
        'next call to the Web Page
        dwStartTime = GetTickCount()
        strResult = Inet1.OpenURL(txtURL.Text & "?MachineName=" & txtMachine.Text & "&Time=" & strAccessTime)
        dwFinishTime = GetTickCount()
    
        strAccessTime = CStr(dwFinishTime - dwStartTime)
    
        ulTotalNumberRequests = ulTotalNumberRequests + 1
        txtHTML = strResult
        lblTotalRequests.Caption = ulTotalNumberRequests
        lblTimeRequest.Caption = strAccessTime
        lblRequestStatus.Caption = "True"
        
        DoEvents
    
    Loop
   
Exit Sub

ErrHandler:
   
GoTo StartCycle
   
End Sub

'******************************************************
'Sends a message to stop logging the results
'******************************************************
Private Sub cmdStopLog_Click()
Dim ulCounter As Long


On Error GoTo ErrHandler
    
    Inet1.OpenURL (txtURL.Text & "?LogResults=Stop")
    lblLogStatus.Caption = "Not Logging"
    DoEvents
    
Exit Sub

ErrHandler:
    
    'Try again
    For ulCounter = 1 To 5
    DoEvents
    Next ulCounter
    Resume
End Sub

'******************************************************************
'Sets a global Flag to indicate that requests should no longer
'be sent - we then break out of the Do loop in cmdStartRequests_Click
'*********************************************************************
Private Sub cmdStopRequests_Click()
    blnStopRequests = True
    lblRequestStatus.Caption = "False"
    DoEvents
End Sub

Private Sub Form_Load()

    If (App.PrevInstance) Then
        MsgBox "Previous instance running also!!"
    End If
    
    optRequest_Click
    lblRequestStatus.Caption = "False"
    lblLogStatus.Caption = "False"
End Sub

Private Sub optLog_Click()
    If (optLog) Then
        cmdStartRequests.Enabled = False
        cmdStopRequests.Enabled = False
        cmdStartLog.Enabled = True
        cmdStopLog.Enabled = True
    End If
End Sub

Private Sub optRequest_Click()
    If (optRequest) Then
        cmdStartLog.Enabled = False
        cmdStopLog.Enabled = False
        cmdStartRequests.Enabled = True
        cmdStopRequests.Enabled = True
    End If
End Sub
