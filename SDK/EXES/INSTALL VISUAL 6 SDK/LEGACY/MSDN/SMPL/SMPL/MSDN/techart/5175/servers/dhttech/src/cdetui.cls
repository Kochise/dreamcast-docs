VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CDetUI"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private m_oAdmin As HDClient.CAdmin
Private m_oReq As HDClient.CRequest
Private m_oReqLstDSO As CTReqDSO
Private m_oTech As HDClient.CTech

Private m_bClaim As Boolean
Private m_bUnclaim As Boolean
Private m_bSubmit As Boolean
Private m_bSend As Boolean

Public Property Get UIClaimReq() As Boolean
    UIClaimReq = m_bClaim
End Property
Public Property Get UIUnclaimReq() As Boolean
    UIUnclaimReq = m_bUnclaim
End Property
Public Property Get UISubmitReq() As Boolean
    UISubmitReq = m_bSubmit
End Property
Public Property Get UISendResp() As Boolean
    UISendResp = m_bSend
End Property
Public Property Get Admin() As HDClient.CAdmin
    Set Admin = m_oAdmin
End Property
Public Property Set Admin(oAdmin As HDClient.CAdmin)
    Set m_oAdmin = oAdmin
End Property
Public Property Get Request() As HDClient.CRequest
    Set Request = m_oReq
End Property
Public Property Set Request(oReq As HDClient.CRequest)
    Dim sStat As String

    Set m_oReq = oReq
    
    'Init UI flags
    m_bClaim = False
    m_bUnclaim = False
    m_bSubmit = False
    m_bSend = False
    
    'Set UI flags for request status
    sStat = m_oAdmin.GetReqStatus(m_oAdmin.Format_ItemPKId(m_oReq.StatusId)).Code
    Select Case sStat
        Case scUNCLAIMED
            m_bClaim = True
        Case scCLAIMED
            m_bUnclaim = True
            m_bSend = True
        Case scINPROG
            m_bSend = True
            m_bSubmit = True
    End Select
End Property
Public Property Get ReqLstDSO() As CTReqDSO
    Set ReqLstDSO = m_oReqLstDSO
End Property
Public Property Set ReqLstDSO(oDSO As CTReqDSO)
    Dim sStat As String
    Set m_oReqLstDSO = oDSO
    
    Set m_oAdmin = oDSO.Admin
    Set m_oReq = oDSO.Request
    Set m_oTech = oDSO.Tech
    
    'Init UI flags
    m_bClaim = False
    m_bUnclaim = False
    m_bSubmit = False
    m_bSend = False
    
    'Set UI flags for request status
    sStat = m_oAdmin.GetReqStatus(m_oAdmin.Format_ItemPKId(m_oReq.StatusId)).Code
    Select Case sStat
        Case scUNCLAIMED
            m_bClaim = True
        Case scCLAIMED
            m_bUnclaim = True
            m_bSend = True
        Case scINPROG
            m_bSend = True
            m_bSubmit = True
    End Select

End Property
Public Property Get Tech() As HDClient.CTech
    Set Tech = m_oTech
End Property
Public Property Set Tech(oTech As HDClient.CTech)
    Set m_oTech = oTech
End Property
Public Sub ClaimRequest()
    Dim lReqId As Long
    lReqId = m_oReq.PKIdEx
    Call m_oAdmin.ClaimRequest(m_oReq)
    m_oReqLstDSO.RefreshRequest lReqId
End Sub
Public Sub UnClaimRequest()
    Dim lReqId As Long
    lReqId = m_oReq.PKIdEx
    Call m_oAdmin.UnClaimRequest(m_oReq)
    m_oReqLstDSO.RefreshRequest lReqId
End Sub
Public Sub SubmitRequest()
    Dim lReqId As Long
    lReqId = m_oReq.PKIdEx
    Call m_oAdmin.SubmitRequest(m_oReq)
    m_oReqLstDSO.RefreshRequest lReqId
End Sub
Public Sub SendTextResponse(ByVal sMsg As String)
    Dim oReqDet As New CReqDetail
    Dim lReqId As Long
    
    lReqId = m_oReq.PKIdEx
    Set oReqDet.Request = m_oReq
    Set oReqDet.Tech = m_oTech
    oReqDet.DetailText = sMsg
    Call m_oAdmin.SendTextResponse(oReqDet)
    m_oReqLstDSO.RefreshRequest lReqId

End Sub
Public Sub SendStdTextResponse(ByVal lRspId As Long)
    Dim oReqDet As New CReqDetail
    Dim lReqId As Long
    
    lReqId = m_oReq.PKIdEx
    Set oReqDet.Request = m_oReq
    Set oReqDet.Tech = m_oTech
    oReqDet.DetId = lRspId
    Call m_oAdmin.SendStdTextResponse(oReqDet)
    m_oReqLstDSO.RefreshRequest lReqId
    oReqDet.DetId = lRspId
    Call m_oAdmin.SendStdTextResponse(oReqDet)
End Sub
Public Sub SendVoiceResponse(ByVal sMsg As String)
    Dim oReqDet As New CReqDetail
    Dim lReqId As Long
    
    lReqId = m_oReq.PKIdEx
    Set oReqDet.Request = m_oReq
    Set oReqDet.Tech = m_oTech
    oReqDet.DetailText = sMsg
    Call m_oAdmin.SendVoiceResponse(oReqDet)
    m_oReqLstDSO.RefreshRequest lReqId
End Sub
Public Sub SendStdVoiceRsp(ByVal lRspId As Long)
    Dim oReqDet As New CReqDetail
    Dim lReqId As Long
    
    lReqId = m_oReq.PKIdEx
    Set oReqDet.Request = m_oReq
    Set oReqDet.Tech = m_oTech
    oReqDet.DetId = lRspId
    Call m_oAdmin.SendStdTextResponse(oReqDet)
    m_oReqLstDSO.RefreshRequest lReqId
    oReqDet.DetId = lRspId
    Call m_oAdmin.SendStdVoiceResponse(oReqDet)
End Sub

