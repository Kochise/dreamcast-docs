VERSION 5.00
Begin VB.Form frmRequestDetails 
   Caption         =   "Request details"
   ClientHeight    =   2400
   ClientLeft      =   45
   ClientTop       =   510
   ClientWidth     =   6225
   LinkTopic       =   "Form1"
   ScaleHeight     =   2400
   ScaleWidth      =   6225
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton btnClose 
      Caption         =   "&Close"
      Default         =   -1  'True
      Height          =   372
      Left            =   5160
      TabIndex        =   1
      Top             =   1920
      Width           =   972
   End
   Begin VB.TextBox txtDetails 
      Height          =   1812
      Left            =   120
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   0
      Top             =   0
      Width           =   6012
   End
   Begin VB.Menu mnuClose 
      Caption         =   "&Close"
   End
End
Attribute VB_Name = "frmRequestDetails"
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
'Date    - 02/01/98
'Authors - Robert Coleridge, Steve Kirk, Fred Pace, Kevin Marzec, Dale Smith
'
Option Explicit

Private m_oRequest As hdclient.CRequest

Private m_bt As Integer
Private m_bl As Integer
Private m_dh As Integer
Private m_dw As Integer
    
Private Sub btnClose_Click()
    mnuClose_Click
End Sub


Private Sub Form_Load()
Dim oReqDetail As hdclient.CReqDetail
Dim cReqDetails As Collection
Dim cTags As Collection

    m_bt = (Me.Height - btnClose.Top) + 100
    m_bl = Me.Width - btnClose.Left
    m_dh = Me.Height - txtDetails.Height
    m_dw = Me.Width - txtDetails.Width
    
    Set cReqDetails = m_oRequest.Details

    Set cTags = New Collection
    cTags.Add m_oRequest.ReqDate, "DATE"
    txtDetails = g_oHDExt.ReplaceTags(LoadResString(icIDS_INITIALIREQUESTDATE), cTags) & Chr$(13) & Chr$(10)
    Set cTags = Nothing
    txtDetails = txtDetails & m_oRequest.Desc & Chr$(13) & Chr$(10)
    txtDetails = txtDetails & Chr$(13) & Chr$(10)
    
    For Each oReqDetail In cReqDetails
        txtDetails = txtDetails & "----- " & oReqDetail.DetDate & " -----" & Chr$(13) & Chr$(10)
        txtDetails = txtDetails & oReqDetail.DetailText & Chr$(13) & Chr$(10)
        txtDetails = txtDetails & Chr$(13) & Chr$(10)
    Next oReqDetail
    
    Set cReqDetails = Nothing

End Sub

Private Sub Form_Resize()

    On Error Resume Next
    
    btnClose.Top = Me.Height - m_bt
    btnClose.Left = Me.Width - m_bl
    txtDetails.Height = Me.Height - m_dh
    txtDetails.Width = Me.Width - m_dw
    
End Sub


Public Property Get Request() As CRequest
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Request
    Set Request = m_oRequest
End Property


Public Property Set Request(oRequest As CRequest)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Request = y
    Set m_oRequest = oRequest
End Property




Private Sub mnuClose_Click()
    Unload Me
End Sub


