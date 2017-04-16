VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CAdmin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
'Copyright (C) 1998 Microsoft Corporation
'All rights reserved.
'
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
'EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
'MERCHANTIBILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
'
'Date    - 02/01/98
'Authors - Robert Coleridge, Steve Kirk, Fred Pace, Kevin Marzec, Dale Smith
'
Option Explicit

Private Const OBJNAME = "CAdmin"

'Enumeration used in FillListLocs and FillListSkills methods
Private Enum hdDOMAIN
    icDOMAIN_ID = 0
    icDOMAIN_DESC = 1
End Enum

'Enumeration used checking the type of logged in Alias - User or Tech
Public Enum hdLOGGED_IN_TYPE
    icUSER_LOGGED_IN = 1
    icTECH_LOGGED_IN = 2
End Enum

'This will be used to return either standard text or voice collection
Public Enum hdSTD_RESP
    icSTD_TEXT = 1
    icSTD_VOICE = 2
End Enum

Private m_cLocs         As Collection   'Collection of Locations
Private m_cSkills       As Collection   'Collection of Skills
Private m_cPriorities   As Collection   'collection of Priorities
Private m_cReqStatus    As Collection   'Collection of request status
Private m_cReqDetType   As Collection   'Collection of request detail types
Private m_cTechs        As Collection   'Collection of Technicians
Private m_cStdTxtResp   As Collection   'Collection of std text responses
Private m_cStdVoiceResp As Collection   'Collection of std voice responses

Private m_lTechId       As Long         'Module level Technician Id
Private m_sUserAlias    As String       'EmailAlias of user logged in

'Used for temporary storage of error information
Private m_lErrNo    As Long
Private m_sErrDesc  As String

'=======================================================================
'Synopsis:              Function initialises the different collections.
'                       Fills list of Technicians
'                       Fills list of Locations
'                       Fills list of Skills
'Function input:        Email Alias of technician/ user logged in
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function Init(ByVal sAlias As String, ByVal iLoggedInType As hdLOGGED_IN_TYPE) As Boolean

Dim oTech As hdclient.CTech

On Error GoTo errInit

Init = False
Term    'Clears all the collections and module level variables

'Check whether passed Alias string is proper
sAlias = UCase(Trim$(sAlias))
If sAlias = vbNullString Then
    GoTo ExitLoop
End If

FillListLocs        'Fill up all the locations
FillListSkills      'Fill up all skills
FillListPriorities  'Fill priority list
FillListReqStatus   'Fill request status list
FillListReqDetType  'Fill request detail types

'If a user has logged in - get requests of the user
'if a tech has logged in - get requests assigned to the Tech
Select Case iLoggedInType
Case hdLOGGED_IN_TYPE.icUSER_LOGGED_IN
    Init = True
Case hdLOGGED_IN_TYPE.icTECH_LOGGED_IN
    FillListTechs               'Fill up the technician collection
    For Each oTech In m_cTechs
        If UCase(oTech.Alias) = sAlias Then
            m_lTechId = oTech.PKId
            Init = True
            Exit For
        End If
    Next oTech
End Select

Set oTech = Nothing     'Clear local technician object

ExitLoop:
    Exit Function

errInit:
    Init = False
End Function

'=======================================================================
'Synopsis:              Procedure gets all Locations records and fills
'                       up the Locations collection
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillListLocs()

Dim oTrans  As hdserver.CTrans
Dim oLoc    As CLocation
Dim iIndex  As Integer
Dim sData() As String

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")    'Create a new Trans object
'Re-initialise the Collection object used for locations
Set m_cLocs = Nothing
Set m_cLocs = New Collection

'Call function on Trans object. Fill the data in collection
If oTrans.GetDomain(icLOCATION, sData) Then
    For iIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
        Set oLoc = New CLocation
        With oLoc
            .PKId = CLng(sData(icDomPKId, iIndex))
            .Code = Trim$(sData(icDomCode, iIndex))
            .Desc = Trim$(sData(icDomDesc, iIndex))
        End With
        m_cLocs.Add oLoc, ItemPKId(sData(icDomPKId, iIndex))
        Set oLoc = Nothing
    Next iIndex
End If

Set oTrans = Nothing    'clear the Trans object

End Sub

'=======================================================================
'Synopsis:              Procedure gets all Skill records and fills up the
'                       Locations collection
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillListSkills()

Dim oTrans  As hdserver.CTrans
Dim oSkill  As CSkill
Dim iIndex  As Integer
Dim sData() As String

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")    'Create a new Trans object

'Re-initialise the skills collection object
Set m_cSkills = Nothing
Set m_cSkills = New Collection

'Call method on the Trans object. Fill the skills collection
If oTrans.GetDomain(icSKILL, sData) Then
    For iIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
        Set oSkill = New CSkill
        With oSkill
            .PKId = CLng(sData(icDomPKId, iIndex))
            .Code = Trim$(sData(icDomCode, iIndex))
            .Desc = Trim$(sData(icDomDesc, iIndex))
        End With
        m_cSkills.Add oSkill, ItemPKId(sData(icDomPKId, iIndex))
        Set oSkill = Nothing
    Next iIndex
End If

Set oTrans = Nothing    'clear local Trans object

End Sub

'=======================================================================
'Synopsis:              Procedure gets all technicians available and fills
'                       up the Technician collection
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillListTechs()

Dim oTrans  As hdserver.CTrans
Dim oTech   As CTech
Dim iIndex  As Integer
Dim sData() As String

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")    'new Trans object

're-initialise the technician collection
Set m_cTechs = Nothing
Set m_cTechs = New Collection

'call method on Trans object. Fill the collection of technicians
If oTrans.GetTechs(hdTECHS.icWORKING_TECHS, sData) Then
    For iIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
        Set oTech = New CTech
        With oTech
            .PKId = CLng(sData(icTechPkId, iIndex))
            .SkillId = CLng(sData(icTechSkillId, iIndex))
            .LocationId = CLng(sData(icTechLocId, iIndex))
            .Alias = CStr(sData(icAlias, iIndex))
        End With
        m_cTechs.Add oTech, ItemPKId(oTech.PKId)
        Set oTech = Nothing
    Next iIndex
End If
Set oTrans = Nothing    'clear the Trans object

End Sub

'=======================================================================
'Synopsis:              This method returns a Technician object if the
'                       Email Alias of technician is passed in the parameter
'Function input:        Email Alias of the intented technician
'Function output:       Technican object
'=======================================================================
Public Function GetTechByAlias(ByVal sAlias As String) As CTech

Dim oTech As CTech

'Set method to a default value
Set GetTechByAlias = Nothing

If m_cTechs Is Nothing Then
    FillListTechs               'Fill up the technician collection
End If

'Iterate through the collection of Technicians.If the alias is found then return it
sAlias = Trim$(sAlias)
If Len(sAlias) Then
    For Each oTech In m_cTechs
        
        If StrComp(oTech.Alias, sAlias, vbTextCompare) = 0 Then
            Set GetTechByAlias = oTech
            Exit For
        End If
    Next oTech
End If
 Set oTech = Nothing     'clear Technician object

End Function

'=======================================================================
'Synopsis:              This method reassigns a request from one technician
'                       to another. Calls HDServer.
'Function input:        Request object which is to be re-assigned
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function ReAssignReq(oReq As CRequest, oTech As CTech) As Boolean
Dim oTrans      As hdserver.CTrans
Dim lFrTechId   As Long
Dim lReqId      As Long
Dim lToTechId   As Long

On Error GoTo errReAssignReq

ReAssignReq = False

'Get parameters from Request object
With oReq
    'Request ID
    lReqId = .PKIdEx
    'From Technician ID
    lFrTechId = .Tech.PKIdEx
End With
'Get To technician ID from technician object
lToTechId = oTech.PKIdEx            'Get the TechId to ReAssign the request

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")    'Create a new Transaction object
If oTrans.ReAssignReq(lReqId, lFrTechId, lToTechId) Then
    oReq.Term                       'Terminate the request object
    oTech.Term                      'Terminate the technician objecy
    ReAssignReq = True              'Return success in function
End If
Set oTrans = Nothing                'Clear the Transaction object

Exit Function

errReAssignReq:
    ReAssignReq = False
    Set oTrans = Nothing
    m_lErrNo = Err
    m_sErrDesc = Err.Description
    
    If Err < vbObjectError Then
        m_lErrNo = m_lErrNo + vbObjectError
    End If
    
    Err.Raise m_lErrNo, Trim$(App.Title) & scReAssignReq, m_sErrDesc
    Exit Function
End Function

'=======================================================================
'Synopsis:              This method changes status of a request from IN PROGRESS
'                       to PENDING. It calls HDServer.
'Function input:        Request object whose status is to be updated
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function SubmitRequest(oReq As CRequest) As Boolean
Dim oTrans  As hdserver.CTrans
Dim lReqId  As Long
Dim lTechId As Long

On Error GoTo errResReq

SubmitRequest = False

'Get parameters from Request object
With oReq
    'Request ID
    lReqId = .PKIdEx
    'Technician ID
    lTechId = .Tech.PKIdEx
End With

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")    'Create a new transaction object
'Call the method to resolve the request
If oTrans.SubmitRequest(lReqId, lTechId) Then
    oReq.Term                       'Terminate the Request Object
    SubmitRequest = True           'Set the function to return True
End If
Set oTrans = Nothing                'Set the object to Nothing

Exit Function

errResReq:
    SubmitRequest = False
    Set oTrans = Nothing
    m_lErrNo = Err
    m_sErrDesc = Err.Description
    
    If Err < vbObjectError Then
        m_lErrNo = m_lErrNo + vbObjectError
    End If
    Err.Raise m_lErrNo, Trim$(App.Title) & scResolveReq, m_sErrDesc
    Exit Function
End Function

'=======================================================================
'Synopsis:              This method changes status of a request from CLAIMED
'                       to ASSIGNED NOT CLAIMED. Calls HDServer.
'Function input:        Request object whose status is to be updated
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function UnclaimRequest(oReq As CRequest) As Boolean
Dim oTrans  As hdserver.CTrans
Dim lReqId  As Long
Dim lTechId As Long

On Error GoTo errUnClmReq

UnclaimRequest = False

'Get parameters from Request object
With oReq
    'Request ID
    lReqId = oReq.PKIdEx
    'Tech ID
    lTechId = oReq.Tech.PKIdEx
End With

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")    'Create a new transaction object
'Call the method to unclaim the request
If oTrans.UnclaimRequest(lReqId, lTechId) Then
    oReq.Term                       'Terminate the Request Object
    UnclaimRequest = True           'Set the function to return True
End If
Set oTrans = Nothing                'Set the object to Nothing

Exit Function

errUnClmReq:
    UnclaimRequest = False
    Set oTrans = Nothing
    m_lErrNo = Err
    m_sErrDesc = Err.Description
    If Err < vbObjectError Then
        m_lErrNo = m_lErrNo + vbObjectError
    End If
    Err.Raise m_lErrNo, Trim$(App.Title) & scUnclaimReq, m_sErrDesc
    Exit Function
End Function

'=======================================================================
'Synopsis:              This method changes status of a request from CLAIMED
'                       to IN PROGRESS. Calls HDServer.
'Function input:        Request object whose status is to be updated
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function WorkRequest(oReq As CRequest) As Boolean
Dim oTrans  As hdserver.CTrans
Dim lReqId  As Long
Dim lTechId As Long

On Error GoTo errWorkReq

WorkRequest = False

'Get parameters from Request object
With oReq
    'Request ID
    lReqId = oReq.PKIdEx
    'Tech ID
    lTechId = oReq.Tech.PKIdEx
End With

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")        'Create a new Transaction object
'Call the method to unclaim the request
If oTrans.WorkRequest(lReqId, lTechId) Then
    oReq.Term                           'Terminate the Request Object
    WorkRequest = True                  'Set the function to return True
End If
Set oTrans = Nothing                    'Set the object to Nothing

Exit Function

errWorkReq:
    WorkRequest = False
    Set oTrans = Nothing
    m_lErrNo = Err
    m_sErrDesc = Err.Description
    If Err < vbObjectError Then
        m_lErrNo = m_lErrNo + vbObjectError
    End If
    Err.Raise m_lErrNo, Trim$(App.Title) & scWorkReq, m_sErrDesc
    Exit Function
End Function

'=======================================================================
'Synopsis:              This clears all collections in CAdmin
'Function input:        None
'Function output:       None
'=======================================================================
Public Sub Term()
Dim oReq As hdclient.CRequest
Dim oTech As hdclient.CTech

Set m_cLocs = Nothing
Set m_cSkills = Nothing
Set m_cPriorities = Nothing
Set m_cReqStatus = Nothing
Set m_cReqDetType = Nothing
Set m_cStdTxtResp = Nothing
Set m_cStdVoiceResp = Nothing

Set m_cTechs = Nothing

End Sub

'=======================================================================
'Synopsis:              This method changes status of a request from
'                       ASSIGNED NOT CLAIMED to CLAIMED. Calls HDServer.
'Function input:        Request object whose status is to be updated
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function ClaimRequest(oReq As CRequest) As Boolean
Dim oTrans      As hdserver.CTrans
Dim lReqId      As Long
Dim lTechId     As Long

On Error GoTo errClaimReq

ClaimRequest = False

'Get parameters from Request object
With oReq
    'Request ID
    lReqId = oReq.PKIdEx
    'Tech ID
    lTechId = oReq.Tech.PKIdEx
End With

Set oTrans = New hdserver.CTrans        'Create a new Transaction object
'Call the method to claim the request
If oTrans.ClaimRequest(lReqId, lTechId) Then
    oReq.Term                           'Terminate the Request Object
    ClaimRequest = True                 'Set the function to return True
End If
Set oTrans = Nothing                    'Set the object to Nothing

Exit Function

errClaimReq:
    ClaimRequest = False
    Set oTrans = Nothing
    m_lErrNo = Err
    m_sErrDesc = Err.Description
    If Err < vbObjectError Then
        m_lErrNo = m_lErrNo + vbObjectError
    End If
    Err.Raise m_lErrNo, Trim$(App.Title) & scClaimReq, m_sErrDesc
    Exit Function
End Function

'=======================================================================
'Synopsis:              This method Refreshes the requests collection
'                       and technician collection
'Function input:        None
'Function output:       None
'=======================================================================
Public Sub Refresh()
Dim oReq    As hdclient.CRequest
Dim oTech   As hdclient.CTech

For Each oTech In m_cTechs
    Set oTech = Nothing
Next
Set m_cTechs = Nothing      'clear technician collection

If m_cSkills Is Nothing Then
    FillListSkills  'Fill skills
End If

If m_cLocs Is Nothing Then
    FillListLocs    'Fill locations
End If

FillListTechs   'Fill technician collection

End Sub

'=======================================================================
'Synopsis:              Executed when all the references to class are
'                       released.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub Class_Terminate()

Term    'clear all module level objects

End Sub

'=======================================================================
'Synopsis:              This method inserts a request. Calls HDServer.
'Function input:        Request object to be inserted
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function InsertRequest(oReq As hdclient.CRequest, lTrackNo As Long) As Boolean
Dim oTrans        As hdserver.CTrans
Dim lLocId        As Long
Dim lPriorityId   As Long
Dim lSkillId      As Long
Dim sDesc         As String
Dim sEAlias       As String

On Error GoTo errInsReq

InsertRequest = False

'Get parameters from Request object
With oReq
    'Get the location
    lLocId = .LocId
    'Get the priority
    lPriorityId = .PriorityId
    'Get the skill
    lSkillId = .SkillId
    'Get the alias of who requested
    sEAlias = .Alias
    'Get description of Request object passed
    sDesc = .Desc
End With

Set oTrans = New hdserver.CTrans        'Create a new Transaction object
'Call the method to claim the request
If oTrans.InsertRequest(lLocId, lPriorityId, lSkillId, sEAlias, sDesc, lTrackNo) Then
    oReq.Term                           'Terminate the Request Object
    InsertRequest = True                'Set the function to return True
End If
Set oTrans = Nothing                    'Set the object to Nothing

Exit Function

errInsReq:
    InsertRequest = False
    Set oTrans = Nothing
    m_lErrNo = Err
    m_sErrDesc = Err.Description
    If Err < vbObjectError Then
        m_lErrNo = m_lErrNo + vbObjectError
    End If
    Err.Raise m_lErrNo, Trim$(App.Title) & scInsertReq, m_sErrDesc
    Exit Function
    
End Function

'=======================================================================
'Synopsis:              This method inserts a request detail. Calls HDServer.
'Function input:        Request detail object to be inserted
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function SendTextRequest(oReqDet As hdclient.CReqDetail) As Boolean
Dim oTrans      As hdserver.CTrans
Dim lReqId      As Long
Dim sMsgText    As String

On Error GoTo errInsReq

SendTextRequest = False

'Get parameters from Request Detail object
With oReqDet
    lReqId = oReqDet.Request.PKIdEx
    sMsgText = oReqDet.DetailText
End With

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")        'Create a new Transaction object

'Call the method to claim the request
If oTrans.SendTextRequest(lReqId, sMsgText) Then
    oReqDet.Term                           'Terminate the Request Object
    SendTextRequest = True                 'Set the function to return True
End If
Set oTrans = Nothing                       'Set the object to Nothing

Exit Function

errInsReq:
    SendTextRequest = False
    Set oTrans = Nothing
    m_lErrNo = Err
    m_sErrDesc = Err.Description
    If Err < vbObjectError Then
        m_lErrNo = m_lErrNo + vbObjectError
    End If
    Err.Raise m_lErrNo, Trim$(App.Title) & scSendTextReq, m_sErrDesc
    Exit Function
    
End Function

'=======================================================================
'Synopsis:              This method inserts a request detail. Calls HDServer.
'Function input:        Request detail object to be inserted
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function SendVoiceRequest(oReqDet As hdclient.CReqDetail) As Boolean
Dim oTrans      As hdserver.CTrans
Dim lReqId      As Long
Dim sMsgText    As String

On Error GoTo errInsReq

SendVoiceRequest = False

'Get parameters from Request Detail object
With oReqDet
    lReqId = .Request.PKIdEx
    sMsgText = .DetailText
End With

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")        'Create a new Transaction object
'Call the method to claim the request
If oTrans.SendVoiceRequest(lReqId, sMsgText) Then
    oReqDet.Term                           'Terminate the Request Object
    SendVoiceRequest = True                 'Set the function to return True
End If
Set oTrans = Nothing                       'Set the object to Nothing

Exit Function

errInsReq:
    SendVoiceRequest = False
    Set oTrans = Nothing
    m_lErrNo = Err
    m_sErrDesc = Err.Description
    If Err < vbObjectError Then
        m_lErrNo = m_lErrNo + vbObjectError
    End If
    Err.Raise m_lErrNo, Trim$(App.Title) & scSendVoiceReq, m_sErrDesc
    Exit Function
    
End Function

'=======================================================================
'Synopsis:              This method inserts a request detail. Calls HDServer.
'Function input:        Request detail object to be inserted
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function SendStdTextResponse(oReqDet As hdclient.CReqDetail) As Boolean
Dim oTrans      As hdserver.CTrans
Dim lReqId      As Long
Dim lTechId     As Long
Dim lRespId     As Long

On Error GoTo errInsReq

SendStdTextResponse = False

'Get parameters from Request Detail object
With oReqDet
    'Request ID
    lReqId = .Request.PKIdEx
    'Technician ID
    lTechId = .Tech.PKIdEx
    'Standard Voice Response ID
    lRespId = .DetId
End With

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")        'Create a new Transaction object

'Call the method to claim the request
If oTrans.SendStdTextResponse(lReqId, lTechId, lRespId) Then
    oReqDet.Term                           'Terminate the Request Object
    SendStdTextResponse = True                'Set the function to return True
End If
Set oTrans = Nothing                       'Set the object to Nothing

Exit Function

errInsReq:
    SendStdTextResponse = False
    Set oTrans = Nothing
    m_lErrNo = Err
    m_sErrDesc = Err.Description
    If Err < vbObjectError Then
        m_lErrNo = m_lErrNo + vbObjectError
    End If
    Err.Raise m_lErrNo, Trim$(App.Title) & scSendStdTxtResp, m_sErrDesc
    Exit Function
    
End Function

'=======================================================================
'Synopsis:              This method inserts a request detail. Calls HDServer.
'Function input:        Request detail object to be inserted
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function SendTextResponse(oReqDet As hdclient.CReqDetail) As Boolean
Dim oTrans      As hdserver.CTrans

Dim lReqId      As Long
Dim lTechId     As Long
Dim sMsgText    As String

On Error GoTo errInsReq

SendTextResponse = False

'Get parameters from Request Detail object
With oReqDet
    'Request ID
    lReqId = .Request.PKIdEx
    'Technician ID
    lTechId = .Tech.PKIdEx
    'Message Text
    sMsgText = .DetailText
End With

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")        'Create a new Transaction object

'Call the method to claim the request
If oTrans.SendTextResponse(lReqId, lTechId, sMsgText) Then
    oReqDet.Term                           'Terminate the Request Object
    SendTextResponse = True               'Set the function to return True
End If
Set oTrans = Nothing                       'Set the object to Nothing

Exit Function

errInsReq:
    SendTextResponse = False
    Set oTrans = Nothing
    m_lErrNo = Err
    m_sErrDesc = Err.Description
    If Err < vbObjectError Then
        m_lErrNo = m_lErrNo + vbObjectError
    End If
    Err.Raise m_lErrNo, Trim$(App.Title) & scSendTxtResp, m_sErrDesc
    Exit Function
    
End Function

'=======================================================================
'Synopsis:              This method inserts a request detail. Calls HDServer.
'Function input:        Request detail object to be inserted
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function SendStdVoiceResponse(oReqDet As hdclient.CReqDetail) As Boolean
Dim oTrans      As hdserver.CTrans
Dim lReqId As Long
Dim lTechId As Long
Dim lRespId As Long

On Error GoTo errInsReq

SendStdVoiceResponse = False

'Get parameters from Request Detail object
With oReqDet
    'Request ID
    lReqId = .Request.PKIdEx
    'Technician ID
    lTechId = .Tech.PKIdEx
    'Standard Voice Response ID
    lRespId = .DetId
End With

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")        'Create a new Transaction object
'Call the method to claim the request
If oTrans.SendStdVoiceResponse(lReqId, lTechId, lRespId) Then
    oReqDet.Term                           'Terminate the Request Object
    SendStdVoiceResponse = True              'Set the function to return True
End If
Set oTrans = Nothing                       'Set the object to Nothing

Exit Function

errInsReq:
    SendStdVoiceResponse = False
    Set oTrans = Nothing
    m_lErrNo = Err
    m_sErrDesc = Err.Description
    If Err < vbObjectError Then
        m_lErrNo = m_lErrNo + vbObjectError
    End If
    Err.Raise m_lErrNo, Trim$(App.Title) & scSendStdVoiceResp, m_sErrDesc
    Exit Function
    
End Function

'=======================================================================
'Synopsis:              This method inserts a request detail. Calls HDServer.
'Function input:        Request detail object to be inserted
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function SendVoiceResponse(oReqDet As hdclient.CReqDetail) As Boolean
Dim oTrans      As hdserver.CTrans
Dim sMsgText    As String
Dim lReqId      As Long
Dim lTechId     As Long

On Error GoTo errInsReq

SendVoiceResponse = False

'Get parameters from Request Detail object
With oReqDet
    'Request ID
    lReqId = .Request.PKIdEx
    'Technician ID
    lTechId = .Tech.PKIdEx
    'Message Text
    sMsgText = .DetailText
End With

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")        'Create a new Transaction object
'Call the method to claim the request
If oTrans.SendVoiceResponse(lReqId, lTechId, sMsgText) Then
    oReqDet.Term                           'Terminate the Request Object
    SendVoiceResponse = True              'Set the function to return True
End If
Set oTrans = Nothing                       'Set the object to Nothing

Exit Function

errInsReq:
    SendVoiceResponse = False
    Set oTrans = Nothing
    m_lErrNo = Err
    m_sErrDesc = Err.Description
    If Err < vbObjectError Then
        m_lErrNo = m_lErrNo + vbObjectError
    End If
    Err.Raise m_lErrNo, Trim$(App.Title) & scSendVoiceResp, m_sErrDesc
    Exit Function
    
End Function

'=======================================================================
'Synopsis:
'Function input:
'Function output:       Returns a collection of locations.
'=======================================================================
Public Function GetLocations() As Collection
On Error GoTo GetLocErr
Dim sErrDesc    As String
Dim lErrNo      As Long


If m_cTechs Is Nothing Then
    FillListLocs               'Fill up the location collection
End If

Set GetLocations = m_cLocs
Exit Function

GetLocErr:
    On Error Resume Next
    Set GetLocations = Nothing
    sErrDesc = Err.Description
    
    If Err < vbObjectError Then
        lErrNo = lErrNo + vbObjectError
    End If
    
    On Error GoTo 0
    Err.Raise lErrNo, Trim$(App.Title) & scAdmLocs, sErrDesc
    Exit Function

End Function

'=======================================================================
'Synopsis:
'Function input:
'Function output:       Returns a collection of technicians.
'=======================================================================
Public Function GetTechnicians() As Collection
On Error GoTo GetTechErr
Dim sErrDesc    As String
Dim lErrNo      As Long

If m_cTechs Is Nothing Then
    FillListTechs               'Fill up the technician collection
End If

Set GetTechnicians = m_cTechs
Exit Function

GetTechErr:
    On Error Resume Next
    Set GetTechnicians = Nothing
    sErrDesc = Err.Description
    
    If Err < vbObjectError Then
        lErrNo = lErrNo + vbObjectError
    End If
    
    On Error GoTo 0
    Err.Raise lErrNo, Trim$(App.Title) & scAdmTechs, sErrDesc
    Exit Function

End Function

'=======================================================================
'Synopsis:
'Function input:
'Function output:       Returns a collection of skill levels.
'=======================================================================
Public Function GetSkills() As Collection
On Error GoTo GetSkErr
Dim sErrDesc    As String
Dim lErrNo      As Long

If m_cSkills Is Nothing Then
    FillListSkills               'Fill up the skills collection
End If

Set GetSkills = m_cSkills
Exit Function

GetSkErr:
    On Error Resume Next
    Set GetSkills = Nothing
    sErrDesc = Err.Description
    
    If Err < vbObjectError Then
        lErrNo = lErrNo + vbObjectError
    End If
    
    On Error GoTo 0
    Err.Raise lErrNo, Trim$(App.Title) & scAdmSkills, sErrDesc
    Exit Function

End Function

'=======================================================================
'Synopsis:              Procedure fills the priority collection
'                       with priority records.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillListPriorities()

Dim oTrans      As hdserver.CTrans
Dim oPriority   As CPriority
Dim iIndex      As Integer
Dim sData()     As String

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")    'Create a new Trans object

'Re-initialise the Collection object used for locations
Set m_cPriorities = Nothing
Set m_cPriorities = New Collection

'Call function on Trans object. Fill the data in collection
If oTrans.GetDomain(icPRIORITY, sData) Then
    For iIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
        Set oPriority = New CPriority
        With oPriority
            .PKId = CLng(sData(icDomPKId, iIndex))
            .Code = Trim$(sData(icDomCode, iIndex))
            .Desc = Trim$(sData(icDomDesc, iIndex))
        End With
        m_cPriorities.Add oPriority, ItemPKId(sData(icDomPKId, iIndex))
        Set oPriority = Nothing
    Next iIndex
End If
Set oTrans = Nothing    'clear the Trans object

End Sub

'=======================================================================
'Synopsis:
'Function input:
'Function output:       Returns a collection of priorities.
'=======================================================================
Public Function GetPriorities() As Collection
On Error GoTo GetPrErr
Dim sErrDesc    As String
Dim lErrNo      As Long

If m_cPriorities Is Nothing Then
    FillListPriorities  'Fill priority list
End If

Set GetPriorities = m_cPriorities
Exit Function

GetPrErr:
    On Error Resume Next
    Set GetPriorities = Nothing
    sErrDesc = Err.Description
    
    If Err < vbObjectError Then
        lErrNo = lErrNo + vbObjectError
    End If
    
    On Error GoTo 0
    Err.Raise lErrNo, Trim$(App.Title) & scAdmPriorities, sErrDesc
    Exit Function

End Function

'=======================================================================
'Synopsis:              Procedure fills the request status collection
'                       with request status records.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillListReqStatus()

Dim oTrans  As hdserver.CTrans
Dim oReqSt  As CReqStatus
Dim iIndex  As Integer
Dim sData() As String

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")    'Create a new Trans object

'Re-initialise the Collection object used for locations
Set m_cReqStatus = Nothing
Set m_cReqStatus = New Collection

'Call function on Trans object. Fill the data in collection
If oTrans.GetDomain(icREQ_STATUS, sData) Then
    For iIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
        Set oReqSt = New CReqStatus
        With oReqSt
            .PKId = CLng(sData(icDomPKId, iIndex))
            .Code = Trim$(sData(icDomCode, iIndex))
            .Desc = Trim$(sData(icDomDesc, iIndex))
        End With
        m_cReqStatus.Add oReqSt, ItemPKId(sData(icDomPKId, iIndex))
        Set oReqSt = Nothing
    Next iIndex
End If

Set oTrans = Nothing    'clear the Trans object

End Sub

'=======================================================================
'Synopsis:
'Function input:
'Function output:       Returns a collection of request status items.
'=======================================================================
Public Function GetReqStatus() As Collection
On Error GoTo GetRSErr
Dim sErrDesc    As String
Dim lErrNo      As Long

If m_cReqStatus Is Nothing Then
    FillListReqStatus               'Fill up the request status collection
End If

Set GetReqStatus = m_cReqStatus
Exit Function

GetRSErr:
    On Error Resume Next
    Set GetReqStatus = Nothing
    sErrDesc = Err.Description
    
    If Err < vbObjectError Then
        lErrNo = lErrNo + vbObjectError
    End If
    
    On Error GoTo 0
    Err.Raise lErrNo, Trim$(App.Title) & scAdmReqStatus, sErrDesc
    Exit Function

End Function

'=======================================================================
'Synopsis:              Procedure fills the request detail type collection
'                       with request detail type records.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillListReqDetType()

Dim oTrans      As hdserver.CTrans
Dim oReqDType   As CReqDetType
Dim iIndex      As Integer
Dim sData()     As String

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")    'Create a new Trans object

'Re-initialise the Collection object used for locations
Set m_cReqDetType = Nothing
Set m_cReqDetType = New Collection

'Call function on Trans object. Fill the data in collection
If oTrans.GetDomain(icREQ_DET_TYPE, sData) Then
    For iIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
        Set oReqDType = New CReqDetType
        With oReqDType
            .PKId = CLng(sData(icDomPKId, iIndex))
            .Code = Trim$(sData(icDomCode, iIndex))
            .Desc = Trim$(sData(icDomDesc, iIndex))
        End With
        m_cReqDetType.Add oReqDType, ItemPKId(sData(icDomPKId, iIndex))
        Set oReqDType = Nothing
    Next iIndex
End If

Set oTrans = Nothing    'clear the Trans object

End Sub

'=======================================================================
'Synopsis:
'Function input:
'Function output:       Returns a collection of request detail types.
'=======================================================================
Public Function GetReqDetTypes() As Collection
On Error GoTo GetReqDetErr
Dim sErrDesc    As String
Dim lErrNo      As Long

If m_cReqDetType Is Nothing Then
    FillListReqDetType               'Fill up the request detail type collection
End If

Set GetReqDetTypes = m_cReqDetType
Exit Function

GetReqDetErr:
    On Error Resume Next
    Set GetReqDetTypes = Nothing
    sErrDesc = Err.Description
    
    If Err < vbObjectError Then
        lErrNo = lErrNo + vbObjectError
    End If
    On Error GoTo 0
    Err.Raise lErrNo, Trim$(App.Title) & scAdmReqDetTypes, sErrDesc
    Exit Function
End Function

'=======================================================================
'Synopsis:              Procedure fills the standard text responses
'                       collection with standard text response records.
'Function input:        None
'Function output:       None
'=======================================================================
Public Sub FillStdTextResponses()

Dim oTrans  As hdserver.CTrans
Dim oSResp  As CStdResp
Dim sData() As String
Dim iIndex  As Integer

Set oTrans = New hdserver.CTrans

Set m_cStdTxtResp = Nothing
Set m_cStdTxtResp = New Collection

If oTrans.GetStdTextResponses(sData) Then
    For iIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
        Set oSResp = New CStdResp
        With oSResp
                .PKId = CLng(sData(icStdRespPKId, iIndex))
                .Code = Trim$(sData(icStdRespCode, iIndex))
                .Desc = Trim$(sData(icStdRespDesc, iIndex))
                .MsgText = Trim$(sData(icStdRespMsg, iIndex))
        End With
        m_cStdTxtResp.Add oSResp, ItemPKId(sData(icStdRespPKId, iIndex))
        Set oSResp = Nothing
    Next iIndex
End If

Set oTrans = Nothing

End Sub

'=======================================================================
'Synopsis:              Procedure fills the standard voice responses
'                       collection with standard voice response records.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillStdVoiceResponses()

Dim oTrans  As hdserver.CTrans
Dim oSResp  As CStdResp
Dim sData() As String
Dim iIndex  As Integer

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")

Set m_cStdVoiceResp = Nothing
Set m_cStdVoiceResp = New Collection

If oTrans.GetStdVoiceResponses(sData) Then
    For iIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
        Set oSResp = New CStdResp
        With oSResp
            .PKId = CLng(sData(icStdRespPKId, iIndex))
            .Code = Trim$(sData(icStdRespCode, iIndex))
            .Desc = Trim$(sData(icStdRespDesc, iIndex))
            .MsgText = Trim$(sData(icStdRespMsg, iIndex))
        End With
        m_cStdVoiceResp.Add oSResp, ItemPKId(sData(icStdRespPKId, iIndex))
    Next iIndex
End If

Set oTrans = Nothing

End Sub

'=======================================================================
'Synopsis:              Converts PKid to string.
'Function input:        Integer.
'Function output:       String.
'=======================================================================
Public Function Format_ItemPKId(ByVal iPKid As Integer) As String
    Format_ItemPKId = ItemPKId(iPKid)
End Function

'=======================================================================
'Synopsis:              Returns standard responses determined
'                       by type.
'Function input:        Response type - text or voice.
'Function output:       Returns a collection of standard responses.
'=======================================================================
Public Function GetStdResponses(ByVal iStdRespType As hdSTD_RESP) As Collection
On Error GoTo StdRespErr

Dim sErrDesc    As String
Dim lErrNo      As Long

Select Case iStdRespType
    Case hdSTD_RESP.icSTD_TEXT
        If m_cStdTxtResp Is Nothing Then
            FillStdTextResponses
        End If
        Set GetStdResponses = m_cStdTxtResp
    Case hdSTD_RESP.icSTD_VOICE
        If m_cStdVoiceResp Is Nothing Then
            FillStdVoiceResponses
        End If
        Set GetStdResponses = m_cStdVoiceResp
End Select

Exit Function

StdRespErr:
    On Error Resume Next
    Set GetStdResponses = Nothing
    sErrDesc = Err.Description
    
    If Err < vbObjectError Then
        lErrNo = lErrNo + vbObjectError
    End If
    
    On Error GoTo 0
    Err.Raise lErrNo, Trim$(App.Title) & scAdmStdRespCol, sErrDesc
    Exit Function

End Function

'=======================================================================
'Synopsis:              This method changes status of a request from PENDING
'                       to RESOLVED . Calls HDServer.
'Function input:        Request object whose status is to be updated
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function ConfirmResolution(oReq As CRequest) As Boolean
Dim oTrans  As hdserver.CTrans
Dim lReqId  As Long

On Error GoTo errCnfRes

ConfirmResolution = False

'Get parameters from Request object
With oReq
    'Request ID
    lReqId = .PKIdEx
End With

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")    'Create a new transaction object
'Call the method to resolve the request
If oTrans.ConfirmResolution(lReqId) Then
    oReq.Term                       'Terminate the Request Object
    ConfirmResolution = True           'Set the function to return True
End If
Set oTrans = Nothing                'Set the object to Nothing

Exit Function

errCnfRes:
    ConfirmResolution = False
    Set oTrans = Nothing
    m_lErrNo = Err
    m_sErrDesc = Err.Description
    
    If Err < vbObjectError Then
        m_lErrNo = m_lErrNo + vbObjectError
    End If
    Err.Raise m_lErrNo, Trim$(App.Title) & scConfirmRes, m_sErrDesc
    Exit Function
End Function

'=======================================================================
'Synopsis:              This method changes status of a request from PENDING
'                       to IN PROCESS . Calls HDServer.
'Function input:        Request object whose status is to be updated
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function DenyResolution(oReq As CRequest) As Boolean
Dim oTrans  As hdserver.CTrans
Dim lReqId  As Long

On Error GoTo errDnyRes

DenyResolution = False

'Get parameters from Request object
With oReq
    'Request ID
    lReqId = .PKIdEx
End With

Set oTrans = New hdserver.CTrans 'CreateObject("HDServer.CTrans")    'Create a new transaction object
'Call the method to resolve the request
If oTrans.DenyResolution(lReqId) Then
    oReq.Term                       'Terminate the Request Object
    DenyResolution = True           'Set the function to return True
End If
Set oTrans = Nothing                'Set the object to Nothing

Exit Function

errDnyRes:
    DenyResolution = False
    Set oTrans = Nothing
    m_lErrNo = Err
    m_sErrDesc = Err.Description
    
    If Err < vbObjectError Then
        m_lErrNo = m_lErrNo + vbObjectError
    End If
    Err.Raise m_lErrNo, Trim$(App.Title) & scDenyRes, m_sErrDesc
    Exit Function
End Function
