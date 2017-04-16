VERSION 5.00
Begin VB.Form frmTextReq 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Send Text Request"
   ClientHeight    =   3285
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7845
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3285
   ScaleWidth      =   7845
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
      Left            =   6720
      TabIndex        =   2
      Top             =   2880
      Width           =   1095
   End
   Begin VB.TextBox txtReq 
      Height          =   2415
      Left            =   20
      MultiLine       =   -1  'True
      TabIndex        =   1
      Top             =   360
      Width           =   7815
   End
   Begin VB.Label lblResp 
      Caption         =   "Enter Request text Below"
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
      Top             =   120
      Width           =   2175
   End
End
Attribute VB_Name = "frmTextReq"
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
'   Synopsis :  This is the text request entry dialog.
'=======================================================================
Dim m_lTrackID As Long

Private Sub cmdSend_Click()
    Dim oReqDet As HDClient.CReqDetail
    Dim oReq    As HDClient.CRequest
    
    If Trim$(txtReq) = vbNullString Then
        MsgBox LoadResString(icIDS_ERR_NOREQTEXT)
        Exit Sub
    End If
    
    'get a new request detail object
    Set oReqDet = New HDClient.CReqDetail
    Set oReq = New HDClient.CRequest
    
    'set attributes for request object
    oReq.Alias = g_sEAlias
    oReq.TrackingNo = m_lTrackID
    
    'set attributes to request detail object
    oReqDet.DetailText = Trim$(txtReq)     'Text of request
    
    'set the request for the request detail object
    Set oReqDet.Request = oReq
    
    'send the text request
    If Not (g_oAdmin.SendTextRequest(oReqDet)) Then
        MsgBox LoadResString(icIDS_ERR_SENDREQTEXT)
    End If
    
    'clean up
    Set oReq = Nothing
    Set oReqDet = Nothing
    Unload Me
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'clean up
    Set frmTextReq = Nothing
End Sub

Public Property Let TrackID(ByVal lNewValue As Long)
    m_lTrackID = lNewValue
End Property
