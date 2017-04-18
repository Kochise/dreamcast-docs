VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CService"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Dim m_DisplayName As String
Dim m_ServiceName As String
Dim m_ServiceType As Long
Dim m_CurrentState As Long
Dim m_ControlsAccepted As Long
Dim m_Win32ExitCode As Long
Dim m_ServiceSpecificExitCode As Long
Dim m_Checkpoint As Long
Dim m_WaitHint As Long

'Constants for service API functions
Private Const ERROR_MORE_DATA = 234
Private Const SC_MANAGER_ENUMERATE_SERVICE = &H4

Private Const SERVICE_STOPPED = &H1
Private Const SERVICE_START_PENDING = &H2
Private Const SERVICE_STOP_PENDING = &H3
Private Const SERVICE_RUNNING = &H4
Private Const SERVICE_CONTINUE_PENDING = &H5
Private Const SERVICE_PAUSE_PENDING = &H6
Private Const SERVICE_PAUSED = &H7
Private Const SERVICE_ACCEPT_STOP = &H1
Private Const SERVICE_ACCEPT_PAUSE_CONTINUE = &H2
Private Const SERVICE_ACCEPT_SHUTDOWN = &H4
Public Enum ServiceTypes
    SERVICE_KERNEL_DRIVER = 1
    SERVICE_FILE_SYSTEM_DRIVER = 2
    SERVICE_ADAPTER = 4
    SERVICE_RECOGNIZER_DRIVER = 8
    SERVICE_DRIVER = 11     '(SERVICE_KERNEL_DRIVER Or
                            'SERVICE_FILE_SYSTEM_DRIVER Or
                            'SERVICE_RECOGNIZER_DRIVER)
    SERVICE_INTERACTIVE_PROCESS = 100
    SERVICE_WIN32_OWN_PROCESS = 10
    SERVICE_WIN32_SHARE_PROCESS = 20
    SERVICE_WIN32 = 30      '(SERVICE_WIN32_OWN_PROCESS Or
                            'SERVICE_WIN32_SHARE_PROCESS)
    SERVICE_TYPE_ALL = 145  '(SERVICE_WIN32 Or SERVICE_ADAPTER Or
                            'SERVICE_DRIVER Or SERVICE_INTERACTIVE_PROCESS)
End Enum
Public Enum ServiceStates
    SERVICE_ACTIVE = &H1
    SERVICE_INACTIVE = &H2
    SERVICE_STATE_ALL = 3   '(SERVICE_ACTIVE Or SERVICE_INACTIVE)
End Enum

Public Property Get DisplayName() As String
    DisplayName = m_DisplayName
End Property
Public Property Let DisplayName(ByVal sNewValue As String)
    m_DisplayName = sNewValue
End Property
Public Property Get ServiceName() As String
    ServiceName = m_ServiceName
End Property
Public Property Let ServiceName(ByVal sNewValue As String)
    m_ServiceName = sNewValue
End Property
Public Property Get ServiceType() As Long
    ServiceType = m_ServiceType
End Property
Public Property Let ServiceType(ByVal lNewValue As Long)
    m_ServiceType = lNewValue
End Property
Public Property Get OwnProcess() As Boolean
    If (m_ServiceType And SERVICE_WIN32_OWN_PROCESS) = SERVICE_WIN32_OWN_PROCESS Then
        OwnProcess = True
    Else
        OwnProcess = False
    End If
End Property
Public Property Get ShareProcess() As Boolean
    If (m_ServiceType And SERVICE_WIN32_SHARE_PROCESS) = SERVICE_WIN32_SHARE_PROCESS Then
        ShareProcess = True
    Else
        ShareProcess = False
    End If
End Property
Public Property Get DeviceDriver() As Boolean
    If (m_ServiceType And SERVICE_KERNEL_DRIVER) = SERVICE_KERNEL_DRIVER Then
        DeviceDriver = True
    Else
        DeviceDriver = False
    End If
End Property
Public Property Get FileSystemDriver() As Boolean
    If (m_ServiceType And SERVICE_FILE_SYSTEM_DRIVER) = SERVICE_FILE_SYSTEM_DRIVER Then
        FileSystemDriver = True
    Else
        FileSystemDriver = False
    End If
End Property
Public Property Get InteractsWithDesktop() As Boolean
    If (m_ServiceType And SERVICE_INTERACTIVE_PROCESS) = SERVICE_INTERACTIVE_PROCESS Then
        InteractsWithDesktop = True
    Else
        InteractsWithDesktop = False
    End If
End Property
Public Property Get CurrentState() As Long
    CurrentState = m_CurrentState
End Property
Public Property Let CurrentState(ByVal lNewValue As Long)
    m_CurrentState = lNewValue
End Property
Public Property Get Stopped() As Boolean
    If (m_CurrentState And SERVICE_STOPPED) = SERVICE_STOPPED Then
        Stopped = True
    Else
        Stopped = False
    End If
End Property
Public Property Get StartPending() As Boolean
    If (m_CurrentState And SERVICE_START_PENDING) = SERVICE_START_PENDING Then
        StartPending = True
    Else
        StartPending = False
    End If
End Property
Public Property Get StopPending() As Boolean
    If (m_CurrentState And SERVICE_STOP_PENDING) = SERVICE_STOP_PENDING Then
        StopPending = True
    Else
        StopPending = False
    End If
End Property
Public Property Get Running() As Boolean
    If (m_CurrentState And SERVICE_RUNNING) = SERVICE_RUNNING Then
        Running = True
    Else
        Running = False
    End If
End Property
Public Property Get ContinuePending() As Boolean
    If (m_CurrentState And SERVICE_CONTINUE_PENDING) = SERVICE_CONTINUE_PENDING Then
        ContinuePending = True
    Else
        ContinuePending = False
    End If
End Property
Public Property Get PausePending() As Boolean
    If (m_CurrentState And SERVICE_PAUSE_PENDING) = SERVICE_PAUSE_PENDING Then
        PausePending = True
    Else
        PausePending = False
    End If
End Property
Public Property Get Paused() As Boolean
    If (m_CurrentState And SERVICE_PAUSED) = SERVICE_PAUSED Then
        Paused = True
    Else
        Paused = False
    End If
End Property
Public Property Get ControlsAccepted() As Long
    ControlsAccepted = m_ControlsAccepted
End Property
Public Property Let ControlsAccepted(ByVal lNewValue As Long)
    m_ControlsAccepted = lNewValue
End Property
Public Property Get AcceptStop() As Boolean
    If (m_ControlsAccepted And SERVICE_ACCEPT_STOP) = SERVICE_ACCEPT_STOP Then
        AcceptStop = True
    Else
        AcceptStop = False
    End If
End Property
Public Property Get AcceptPauseContinue() As Boolean
    If (m_ControlsAccepted And SERVICE_ACCEPT_PAUSE_CONTINUE) = SERVICE_ACCEPT_PAUSE_CONTINUE Then
        AcceptPauseContinue = True
    Else
        AcceptPauseContinue = False
    End If
End Property
Public Property Get AcceptShutdown() As Boolean
    If (m_ControlsAccepted And SERVICE_ACCEPT_SHUTDOWN) = SERVICE_ACCEPT_SHUTDOWN Then
        AcceptShutdown = True
    Else
        AcceptShutdown = False
    End If
End Property
Public Property Get Win32ExitCode() As Long
    Win32ExitCode = m_Win32ExitCode
End Property
Public Property Let Win32ExitCode(ByVal lNewValue As Long)
    m_Win32ExitCode = lNewValue
End Property
Public Property Get ServiceSpecificExitCode() As Long
    ServiceSpecificExitCode = m_ServiceSpecificExitCode
End Property
Public Property Let ServiceSpecificExitCode(ByVal lNewValue As Long)
    m_ServiceSpecificExitCode = lNewValue
End Property
Public Property Get CheckPoint() As Long
    CheckPoint = m_Checkpoint
End Property
Public Property Let CheckPoint(ByVal lNewValue As Long)
    m_Checkpoint = lNewValue
End Property
Public Property Get WaitHint() As Long
    WaitHint = m_WaitHint
End Property
Public Property Let WaitHint(ByVal lNewValue As Long)
    m_WaitHint = lNewValue
End Property

