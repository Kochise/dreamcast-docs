VERSION 5.00
Begin VB.Form frmDomMaint 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Domain maintenance"
   ClientHeight    =   1470
   ClientLeft      =   30
   ClientTop       =   315
   ClientWidth     =   4005
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1470
   ScaleWidth      =   4005
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton btnCancel 
      Cancel          =   -1  'True
      Caption         =   "&Cancel"
      Height          =   372
      Left            =   2880
      TabIndex        =   4
      Top             =   960
      Width           =   972
   End
   Begin VB.CommandButton btnAction 
      Caption         =   "Action"
      Default         =   -1  'True
      Height          =   372
      Left            =   120
      TabIndex        =   3
      Top             =   960
      Width           =   972
   End
   Begin VB.TextBox txtDescription 
      Height          =   288
      Left            =   1080
      TabIndex        =   2
      Top             =   480
      Width           =   2772
   End
   Begin VB.TextBox txtCode 
      Height          =   288
      Left            =   1080
      TabIndex        =   1
      Top             =   120
      Width           =   2772
   End
   Begin VB.Label Label1 
      Caption         =   "Description"
      Height          =   252
      Index           =   1
      Left            =   120
      TabIndex        =   5
      Top             =   480
      Width           =   972
   End
   Begin VB.Label Label1 
      Caption         =   "Code"
      Height          =   252
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   972
   End
End
Attribute VB_Name = "frmDomMaint"
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
Private Const OBJNAME = "frmDomMaint"
Dim m_iDomain As RES_IDS
Dim m_sCode As String
Dim m_sDescription As String
Dim m_iAction As DOMAIN_MAINTENANCE

Private Function InvokeError(ByVal ErrorID As RES_IDS, Optional ByVal ErrorMsg As String) As Boolean
Dim sMsg As String
Dim lErr As Long

    sMsg = Trim$(App.Title) & ":" & OBJNAME
    lErr = Err
    
    If ErrorID = 0 Then
        sMsg = sMsg & " " & ErrorMsg
    Else
        sMsg = sMsg & " " & LoadResString(ErrorID)
    End If
    
    If Err < vbObjectError Then
        lErr = lErr + vbObjectError
    End If
    
    Err.Raise lErr, sMsg, Err.Description
End Function



Private Sub btnAction_Click()
    Dim oLocation As CLocation
    Dim oSkill As CSkill
    Dim oPriority As CPriority
    
    Select Case m_iAction
    Case DM_ADD
        
        'fill in properties and insert new record
        Select Case m_iDomain
        Case icIDS_SQLTB_LOCATION
            Set oLocation = New hdclient.CLocation
            oLocation.Code = txtCode
            oLocation.Desc = txtDescription
            g_oSysAdmin.Insert oLocation:=oLocation
            If Err Then
                On Error GoTo 0
                InvokeError icIDS_ERR_CANT_INSERT
                Exit Sub
            End If
            Set oLocation = Nothing
        
        Case icIDS_SQLTB_SKILL
            Set oSkill = New hdclient.CSkill
            oSkill.Code = txtCode
            oSkill.Desc = txtDescription
            g_oSysAdmin.Insert oSkill:=oSkill
            If Err Then
                On Error GoTo 0
                InvokeError icIDS_ERR_CANT_INSERT
                Exit Sub
            End If
            Set oSkill = Nothing
        
        Case icIDS_SQLTB_PRIORITY
            Set oPriority = New hdclient.CPriority
            oPriority.Code = txtCode
            oPriority.Desc = txtDescription
            g_oSysAdmin.Insert oPriority:=oPriority
            If Err Then
                On Error GoTo 0
                InvokeError icIDS_ERR_CANT_INSERT
                Exit Sub
            End If
            Set oPriority = Nothing
        
        End Select
        
    Case DM_DELETE
        
        'fill in properties and delete new record
        Select Case m_iDomain
        Case icIDS_SQLTB_LOCATION
            Set oLocation = New hdclient.CLocation
            oLocation.Code = txtCode
            g_oSysAdmin.Delete oLocation:=oLocation
            If Err Then
                On Error GoTo 0
                InvokeError icIDS_ERR_CANT_DELETE
                Exit Sub
            End If
            Set oLocation = Nothing
        
        Case icIDS_SQLTB_SKILL
            Set oSkill = New hdclient.CSkill
            oSkill.Code = txtCode
            g_oSysAdmin.Delete oSkill:=oSkill
            If Err Then
                On Error GoTo 0
                InvokeError icIDS_ERR_CANT_DELETE
                Exit Sub
            End If
            Set oSkill = Nothing
        
        Case icIDS_SQLTB_PRIORITY
            Set oPriority = New hdclient.CPriority
            oPriority.Code = txtCode
            g_oSysAdmin.Delete oPriority:=oPriority
            If Err Then
                On Error GoTo 0
                InvokeError icIDS_ERR_CANT_DELETE
                Exit Sub
            End If
            Set oPriority = Nothing
        
        End Select
       
    Case DM_UPDATE
        
        'fill in properties and update new record
        Select Case m_iDomain
        Case icIDS_SQLTB_LOCATION
            Set oLocation = New hdclient.CLocation
            oLocation.PKid = g_oSysAdmin.ExtrPKId(m_sCode)
            oLocation.Code = txtCode
            oLocation.Desc = txtDescription
            g_oSysAdmin.Update oLocation:=oLocation
            If Err Then
                On Error GoTo 0
                InvokeError icIDS_ERR_CANT_UPDATE
                Exit Sub
            End If
            Set oLocation = Nothing
        
        Case icIDS_SQLTB_SKILL
            Set oSkill = New hdclient.CSkill
            oSkill.PKid = g_oSysAdmin.ExtrPKId(m_sCode)
            oSkill.Code = txtCode
            oSkill.Desc = txtDescription
            g_oSysAdmin.Update oSkill:=oSkill
            If Err Then
                On Error GoTo 0
                InvokeError icIDS_ERR_CANT_UPDATE
                Exit Sub
            End If
            Set oSkill = Nothing
        
        Case icIDS_SQLTB_PRIORITY
            Set oPriority = New hdclient.CPriority
            oPriority.PKid = g_oSysAdmin.ExtrPKId(m_sCode)
            oPriority.Code = txtCode
            oPriority.Desc = txtDescription
            g_oSysAdmin.Update oPriority:=oPriority
            If Err Then
                On Error GoTo 0
                InvokeError icIDS_ERR_CANT_UPDATE
                Exit Sub
            End If
            Set oPriority = Nothing
        
        End Select
        
    End Select
    
    Unload Me
    
End Sub

Private Sub DisplayError(ByVal ErrorID As RES_IDS, Optional ByVal ErrorMsg As String)
Dim sMsg As String

If ErrorID = icIDS_USEMSGASERROR Then
    sMsg = ErrorMsg
Else
    sMsg = LoadResString(ErrorID)
End If

MsgBox prompt:=sMsg, Title:=Trim$(App.Title) & ":" & OBJNAME

End Sub


Private Sub btnCancel_Click()
    
    Unload Me

End Sub

Public Sub SetParameters(ByVal iAction As DOMAIN_MAINTENANCE, ByVal iDomain As RES_IDS, ByVal sCode As String, ByVal sDescription As String)
    
    m_iDomain = iDomain
    m_sCode = sCode
    m_sDescription = sDescription
    m_iAction = iAction
    
    txtCode = sCode
    txtDescription = sDescription

    Select Case iAction
    Case DM_ADD
        btnAction.Caption = LoadResString(icIDS_BTN_ADDNEW)
    Case DM_UPDATE
        btnAction.Caption = LoadResString(icIDS_BTN_UPDATE)
    End Select

End Sub

