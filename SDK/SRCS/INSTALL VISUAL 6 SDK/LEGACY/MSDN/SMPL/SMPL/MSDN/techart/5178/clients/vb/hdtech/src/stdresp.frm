VERSION 5.00
Begin VB.Form frmStdResp 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "List of Standard"
   ClientHeight    =   3060
   ClientLeft      =   7470
   ClientTop       =   7320
   ClientWidth     =   6495
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3060
   ScaleWidth      =   6495
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdSend 
      Caption         =   "&Send"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   5480
      TabIndex        =   2
      Top             =   2640
      Width           =   975
   End
   Begin VB.TextBox txtStd 
      Height          =   2595
      Left            =   2250
      MultiLine       =   -1  'True
      TabIndex        =   1
      Top             =   0
      Width           =   4215
   End
   Begin VB.ListBox lstStdResp 
      Height          =   2400
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   2175
   End
End
Attribute VB_Name = "frmStdResp"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'Copyright (C) 1998 Microsoft Corporation
'All rights reserved.
'
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
'EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
'MERCHANTIBILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
'
'Date         - 01/05/98
'Author       - Venu Yerra
'
Option Explicit
'=======================================================================
'   HelpDesk project - Visual Basic Client
'   Microsoft Corporation
'   Date : 14 October 1997
'   Synopsis :  This is the standard response entry dialog.
'=======================================================================

'used in setting caption of this form
Const STD_TEXT = " Text Responses"
Const STD_VOICE = " Text Responses"

'used for response
Dim m_oStdResp      As hdclient.CStdResp
Dim m_lRespType     As Long
Dim m_lTrackID      As Long
Dim m_cStdResps     As Collection

Private Sub Form_Load()
    On Error GoTo FLoadErr
    
    Select Case m_lRespType
        Case icText
            Me.Caption = Me.Caption & " Text Responses"
        Case icVoice
            Me.Caption = Me.Caption & " Voice Responses"
    End Select
    
    'fill the list box with either standard text or Voice
    FillList
    
    Exit Sub

FLoadErr:
    MsgBox Err.Number & " : " & Err.Description
    Err.Clear
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Set frmStdResp = Nothing
End Sub

Private Sub cmdSend_Click()
    Dim oReq As hdclient.CRequest
    Dim oReqDet As hdclient.CReqDetail
    
    'check whether any item is selected
    If m_oStdResp Is Nothing Then
        Exit Sub
    End If
    
    'set the request to in progress
    CommenceReq
    
    'get a new request and request detail object
    Set oReq = New CRequest
    Set oReqDet = New CReqDetail
    
    'set the attributes of request object
    oReq.TrackingNo = m_lTrackID
    
    'set the attributes of request detail object
    Set oReqDet = New CReqDetail
    oReqDet.DetId = m_oStdResp.PKId
    Set oReqDet.Request = oReq
    Set oReqDet.Tech = g_oTech
    
    'send the response
    Select Case m_lRespType
    Case icText
        If Not g_oAdmin.SendStdTextResponse(oReqDet) Then
            MsgBox ERR_SENDRESPTEXT
        End If
        
    Case icVoice
        If Not g_oAdmin.SendStdVoiceResponse(oReqDet) Then
            MsgBox ERR_SENDRESPTEXT
        End If
    End Select
    
    Set oReqDet = Nothing
    Set oReq = Nothing
    
    Unload Me

End Sub

Private Sub lstStdResp_Click()
    Dim oStdResp As hdclient.CStdResp
    Set m_oStdResp = Nothing
    
    'exit if there are no items in the list
    If lstStdResp.ListCount = 0 Then
        Exit Sub
    End If
    
    For Each oStdResp In m_cStdResps
        If (oStdResp.PKId) = lstStdResp.ItemData(lstStdResp.ListIndex) Then
            Set m_oStdResp = oStdResp
            txtStd = oStdResp.MsgText
        End If
    Next
    Set oStdResp = Nothing
End Sub


'=======================================================================
'Synopsis:              Fill the listbox with response detail
'                       information.
'Function input:        None
'Function output:       None
'=======================================================================
Sub FillList()
    Dim oStdResp    As hdclient.CStdResp
    Dim lCnt        As Long
    
    Select Case m_lRespType
    Case icText
        'get the stdandard text collection object
        Set m_cStdResps = g_oAdmin.GetStdResponses(m_lRespType)
    Case icVoice
        'get the stdandard voice collection object
        Set m_cStdResps = g_oAdmin.GetStdResponses(m_lRespType)
    End Select
    
    lCnt = m_cStdResps.Count
    If lCnt = 0 Then
        Exit Sub
    End If
    
    'fill the list
    For Each oStdResp In m_cStdResps
        lstStdResp.AddItem oStdResp.Desc
        lstStdResp.ItemData(lstStdResp.NewIndex) = oStdResp.PKId
    Next
    
    Set oStdResp = Nothing

End Sub

Public Property Let TrackID(ByVal lNewValue As Long)
    m_lTrackID = lNewValue
End Property

Public Property Let ResponseType(ByVal lNewValue As Long)
    m_lRespType = lNewValue
End Property

'=======================================================================
'Synopsis:              This subroutine commences processing the claimed
'                       request.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub CommenceReq()
    On Error GoTo CommenceErr
    
    Dim oReq    As hdclient.CRequest
    Dim lReqId  As Long
        
    'create a new request object
    Set oReq = New CRequest
    
    'set the request id to the Request object
    oReq.TrackingNo = m_lTrackID
    
    'start working on the request
    If Not g_oAdmin.WorkRequest(oReq) Then
        MsgBox ERR_COMMENCEFAILED
    End If
    
    'delete the request object
    Set oReq = Nothing
    
    Exit Sub

CommenceErr:
    MsgBox Err.Number & " : " & Err.Description
    Err.Clear
End Sub

