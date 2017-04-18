VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CServiceAdmin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

'Service API functions
Private Declare Function CloseServiceHandle Lib "advapi32.dll" (ByVal hSCObject As Long) As Long

Private Declare Function EnumServicesStatus Lib "advapi32.dll" Alias "EnumServicesStatusA" _
    (ByVal hSCManager As Long, ByVal dwServiceType As Long, ByVal dwServiceState As Long, _
    lpBufAddress As ENUM_SERVICE_STATUS, ByVal cbBufSize As Long, pcbBytesNeeded As Long, _
    lpServicesReturned As Long, lpResumeHandle As Long) As Long

Private Declare Function OpenSCManager Lib "advapi32.dll" Alias "OpenSCManagerA" _
    (ByVal lpMachineName As String, ByVal lpDatabaseName As String, _
    ByVal dwDesiredAccess As Long) As Long

'String API procedure
Private Declare Function lstrcpy Lib "kernel32" Alias "lstrcpyA" (ByVal lpString1 As String, ByVal lpString2 As Long) As Long
Private Declare Function lstrlen Lib "kernel32" Alias "lstrlenA" (ByVal lpString As String) As Long

'Constants for service API functions
Private Const ERROR_MORE_DATA = 234

Private Const SC_MANAGER_ENUMERATE_SERVICE = &H4


'Types for service API functions
Private Type SERVICE_STATUS
        dwServiceType As Long
        dwCurrentState As Long
        dwControlsAccepted As Long
        dwWin32ExitCode As Long
        dwServiceSpecificExitCode As Long
        dwCheckPoint As Long
        dwWaitHint As Long
End Type
Private Type ENUM_SERVICE_STATUS
        lpServiceName As Long
        lpDisplayName As Long
        ServiceStatus As SERVICE_STATUS
End Type

Dim m_services As Collection
Dim m_ServiceType As Long
Dim m_ServiceState As Long

Public Property Get Services() As Variant
    If m_services Is Nothing Then Set m_services = New Collection
    Set Services = m_services
End Property

Private Sub Class_Initialize()
    FillServices
End Sub
Public Sub FillServices()
    Dim oService As CService
    Dim vEnumServiceStatus() As ENUM_SERVICE_STATUS
    Dim bResult As Boolean
    Dim GLE As Long
    Dim hSCM As Long
    Dim lBytesNeeeded As Long
    Dim lNdx
    Dim lRetVal As Long
    Dim lResult As Long
    Dim lResumeHandle As Long
    Dim lServicesReturned As Long
    Dim sDatabaseName As String
    Dim sMachineName As String
    Dim sDisplayName As String * 256
    Dim sServiceName As String * 256
    
    On Error GoTo ErrFillServices
    
    'Initialize the collection
    Set m_services = Nothing
    Set m_services = New Collection
    'Open the service manager
    hSCM = OpenSCManager(sMachineName, sDatabaseName, SC_MANAGER_ENUMERATE_SERVICE)
    If hSCM = 0 Then
        GLE = Err.LastDllError
        On Error GoTo 0
        Err.Raise vbObjectError + GLE, App.Title
        Exit Sub
    End If

    'Enumerate the services
    lBytesNeeeded = 0
    lServicesReturned = 0
    lResumeHandle = 0
    bResult = True
    ReDim vEnumServiceStatus(256) As ENUM_SERVICE_STATUS
    While bResult
        lRetVal = EnumServicesStatus(hSCM, _
            m_ServiceType, _
            m_ServiceState, _
            vEnumServiceStatus(0), _
            256, _
            lBytesNeeeded, _
            lServicesReturned, _
            lResumeHandle)
        
        'Retrieve LastError set by EnumServicesStatus
        GLE = Err.LastDllError
        If lRetVal = 0 Then
            If GLE = ERROR_MORE_DATA Then
                bResult = True
            Else
                bResult = False
            End If
        Else
            bResult = True
        End If
        
        If bResult Then
            'Retrieve services from buffer
            For lNdx = 0 To lServicesReturned - 1
                Set oService = New CService
                'Resolve ServiceName and DisplayName from pointers
                lResult = lstrcpy(sServiceName, vEnumServiceStatus(lNdx).lpServiceName)
                lResult = lstrcpy(sDisplayName, vEnumServiceStatus(lNdx).lpDisplayName)
                oService.ServiceName = Mid$(sServiceName, 1, lstrlen(sServiceName))
                oService.DisplayName = Mid$(sDisplayName, 1, lstrlen(sDisplayName))
                'Resolve Service Status
                oService.ServiceType = vEnumServiceStatus(lNdx).ServiceStatus.dwServiceType
                oService.CurrentState = vEnumServiceStatus(lNdx).ServiceStatus.dwCurrentState
                oService.ControlsAccepted = vEnumServiceStatus(lNdx).ServiceStatus.dwControlsAccepted
                oService.Win32ExitCode = vEnumServiceStatus(lNdx).ServiceStatus.dwWin32ExitCode
                oService.ServiceSpecificExitCode = vEnumServiceStatus(lNdx).ServiceStatus.dwServiceSpecificExitCode
                oService.CheckPoint = vEnumServiceStatus(lNdx).ServiceStatus.dwCheckPoint
                oService.WaitHint = vEnumServiceStatus(lNdx).ServiceStatus.dwWaitHint
                'Add the service to the services collection
                m_services.Add oService, oService.DisplayName
                Set oService = Nothing
            Next
        End If
                    
        If lResumeHandle = 0 Then
            bResult = False
        End If
Wend
            
    'Close the service manager
    CloseServiceHandle (hSCM)

Exit Sub
ErrFillServices:
    MsgBox ("ErrFillServices " & Error$)
    Resume
End Sub


Public Property Get ServiceType() As Long
    ServiceType = m_ServiceType
End Property

Public Property Let ServiceType(ByVal lNewValue As Long)
    m_ServiceType = lNewValue
End Property

Public Property Get ServiceState() As Long
    ServiceState = m_ServiceState
End Property

Public Property Let ServiceState(ByVal lNewValue As Long)
    m_ServiceState = lNewValue
End Property
