VERSION 5.00
Begin VB.Form frmTextResp 
   Caption         =   "Send Text Response"
   ClientHeight    =   3165
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7830
   LinkTopic       =   "Form1"
   ScaleHeight     =   3165
   ScaleWidth      =   7830
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
      Left            =   6720
      TabIndex        =   2
      Top             =   2760
      Width           =   1095
   End
   Begin VB.TextBox txtResp 
      Height          =   2415
      Left            =   0
      MultiLine       =   -1  'True
      TabIndex        =   1
      Top             =   240
      Width           =   7815
   End
   Begin VB.Label lblResp 
      Caption         =   "Enter Response text"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   2175
   End
End
Attribute VB_Name = "frmTextResp"
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
'   Synopsis :  This is the text response entry dialog.
'=======================================================================

Dim m_lTrackID As Long

Private Sub Form_Unload(Cancel As Integer)
    Set frmTextResp = Nothing
End Sub

Private Sub cmdSend_Click()
    Dim oReq As hdclient.CRequest
    Dim oReqDet As hdclient.CReqDetail
    Dim sMsgtext As String
    sMsgtext = Trim$(txtResp)
    If sMsgtext = vbNullString Then
        MsgBox ERR_NORESPTEXT
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
    oReqDet.DetailText = sMsgtext
    Set oReqDet.Request = oReq
    Set oReqDet.Tech = g_oTech
    
    'send the text response
    If Not g_oAdmin.SendTextResponse(oReqDet) Then
        MsgBox ERR_SENDRESPTEXT
    End If
    
    'clean up
    Set oReqDet = Nothing
    Set oReq = Nothing
    
    Unload Me

End Sub

Public Property Let TrackID(ByVal lNewValue As Long)
    m_lTrackID = lNewValue
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
    
    'call the method on the object to start working on the request
    If Not g_oAdmin.WorkRequest(oReq) Then
        MsgBox ERR_COMMENCEFAILED
    End If
    
    'clean up
    Set oReq = Nothing
    
    
    Exit Sub

CommenceErr:
    MsgBox Err.Number & " : " & Err.Description
    Err.Clear
End Sub

