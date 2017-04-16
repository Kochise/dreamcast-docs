VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CMReqDSO"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private oListener As DataSourceListener
Private oOSP As CMReqOSP
Private m_oReq As HDClient.CRequest

Public Function msDataSourceObject(ByVal qualifier As String) As OLEDBSimpleProvider
Attribute msDataSourceObject.VB_UserMemId = -3900
    Set msDataSourceObject = oOSP
End Function
Public Function addDataSourceListener(ByVal idslListener As DataSourceListener)
Attribute addDataSourceListener.VB_UserMemId = -3901
    Set oListener = idslListener
End Function
Public Sub removeDataSourceListener(ByVal idslListener As DataSourceListener)
Attribute removeDataSourceListener.VB_UserMemId = -3902
    Set oListener = Nothing
End Sub
Private Sub Class_Initialize()
    Set oOSP = New CMReqOSP
End Sub
Private Sub Class_Terminate()
    Set m_oReq = Nothing
    Set oOSP = Nothing
End Sub
Public Property Get Admin() As HDClient.CAdmin
    Set Admin = oOSP.Admin
End Property
Public Property Get Request() As HDClient.CRequest
    Set Request = m_oReq
End Property
Public Property Get Tech() As HDClient.CTech
    Set Tech = oOSP.Tech
End Property
Public Sub ExpandRequest(ByVal lPKId As Long, ByVal sUIFile As String)
        
    'Prepare request object
    Set m_oReq = New HDClient.CRequest
    m_oReq.PKId = lPKId
        
    'Expand specified request on OSP
    oOSP.ExpandDetail lPKId, sUIFile
End Sub
Public Sub RefreshRequest(ByVal lPKId As Long)
    'Prepare request object
    Set m_oReq = New HDClient.CRequest
    m_oReq.PKId = lPKId
        
    'Refresh specified request on OSP
    oOSP.RefreshRequest lPKId
End Sub
Public Sub ToggleRequest(ByVal lPKId As Long, ByVal sUIFile As String)
    'Prepare request object
    Set m_oReq = New HDClient.CRequest
    m_oReq.PKId = lPKId
        
    'Expand specified request on OSP
    oOSP.ToggleDetail lPKId, sUIFile
End Sub
