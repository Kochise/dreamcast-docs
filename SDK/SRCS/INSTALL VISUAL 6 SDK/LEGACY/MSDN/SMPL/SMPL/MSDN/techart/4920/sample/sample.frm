VERSION 4.00
Begin VB.Form ServiceMain 
   Caption         =   "Sample NT Service"
   ClientHeight    =   4140
   ClientLeft      =   1395
   ClientTop       =   1620
   ClientWidth     =   6690
   Height          =   4545
   Icon            =   "sample.frx":0000
   Left            =   1335
   LinkTopic       =   "Form1"
   ScaleHeight     =   4140
   ScaleWidth      =   6690
   Top             =   1275
   Width           =   6810
   Begin VB.Timer Timer 
      Left            =   960
      Top             =   360
   End
   Begin NTService.NTService NTService1 
      Left            =   240
      Top             =   360
      _Version        =   65536
      _ExtentX        =   741
      _ExtentY        =   741
      _StockProps     =   0
      DisplayName     =   "Sample Service"
      ServiceName     =   "Sample"
      StartMode       =   3
   End
   Begin ComctlLib.StatusBar StatusBar 
      Align           =   2  'Align Bottom
      Height          =   300
      Left            =   0
      TabIndex        =   0
      Top             =   3840
      Width           =   6690
      _Version        =   65536
      _ExtentX        =   11800
      _ExtentY        =   529
      _StockProps     =   68
      AlignSet        =   -1  'True
      SimpleText      =   ""
      NumPanels       =   2
      i1              =   "sample.frx":000C
      i2              =   "sample.frx":00D9
   End
End
Attribute VB_Name = "ServiceMain"
Attribute VB_Creatable = False
Attribute VB_Exposed = False

Option Explicit

Private Sub Form_Load()

On Error GoTo Err_Load
    Dim strDisplayName As String
    Dim bStarted As Boolean
    
    strDisplayName = NTService1.DisplayName
    
    StatusBar.Panels(1).Text = "Loading"
    
    If Command = "-install" Then
        ' enable interaction with desktop
        NTService1.Interactive = True
        
        If NTService1.Install Then
            Call NTService1.SaveSetting("Parameters", "TimerInterval", "1000")
            MsgBox strDisplayName & " installed successfully"
        Else
            MsgBox strDisplayName & " failed to install"
        End If
        End
    ElseIf Command = "-uninstall" Then
        If NTService1.Uninstall Then
            MsgBox strDisplayName & " uninstalled successfully"
        Else
            MsgBox strDisplayName & " failed to uninstall"
        End If
        End
    ElseIf Command = "-debug" Then
        NTService1.Debug = True
    ElseIf Command <> "" Then
        MsgBox "Invalid command option"
        End
    End If
    
    Timer.Interval = CInt(NTService1.GetSetting("Parameters", "TimerInterval", "2000"))
    
    ' enable Pause/Continue. Must be set before StartService
    ' is called or in design mode
    NTService1.ControlsAccepted = svcCtrlPauseContinue
    
    ' connect service to Windows NT services controller
    NTService1.StartService
    
Err_Load:
    Call NTService1.LogEvent(svcMessageError, svcEventError, "[" & Err.Number & "] " & Err.Description)
End Sub


Private Sub NTService1_Continue(Success As Boolean)
On Error GoTo Err_Continue
    
    Timer.Enabled = True
    StatusBar.Panels(1).Text = "Running"
    Success = True
    Call NTService1.LogEvent(svcEventInformation, svcMessageInfo, "Service continued")
    
Err_Continue:
    Call NTService1.LogEvent(svcMessageError, svcEventError, "[" & Err.Number & "] " & Err.Description)
End Sub

Private Sub NTService1_Control(ByVal Event As Long)
On Error GoTo Err_Control
    
    StatusBar.SimpleText = NTService1.DisplayName & " Control signal " & Event

Err_Control:
    Call NTService1.LogEvent(svcMessageError, svcEventError, "[" & Err.Number & "] " & Err.Description)
End Sub


Private Sub NTService1_Pause(Success As Boolean)
On Error GoTo Err_Pause
    
    Timer.Enabled = False
    StatusBar.Panels(1).Text = "Paused"
    Call NTService1.LogEvent(svcEventError, svcMessageError, "Service paused")
    Success = True
    
Err_Pause:
    Call NTService1.LogEvent(svcMessageError, svcEventError, "[" & Err.Number & "] " & Err.Description)
End Sub


Private Sub NTService1_Start(Success As Boolean)
On Error GoTo Err_Start
    
    StatusBar.Panels(1).Text = "Running"
    Success = True
    
Err_Start:
    Call NTService1.LogEvent(svcMessageError, svcEventError, "[" & Err.Number & "] " & Err.Description)
End Sub


Private Sub NTService1_Stop()
On Error GoTo Err_Stop
    
    StatusBar.Panels(1).Text = "Stopped"
    Unload Me
    
Err_Stop:
    Call NTService1.LogEvent(svcMessageError, svcEventError, "[" & Err.Number & "] " & Err.Description)
End Sub


Private Sub Timer_Timer()
On Error GoTo Err_Timer
    StatusBar.Panels(2).Text = Format(Now(), "hh:mm:ss")

Err_Timer:
    Call NTService1.LogEvent(svcMessageError, svcEventError, "[" & Err.Number & "] " & Err.Description)
End Sub


