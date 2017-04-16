VERSION 5.00
Begin VB.Form frmTechMaint 
   Caption         =   "Technician maintenance"
   ClientHeight    =   1680
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3795
   LinkTopic       =   "Form1"
   ScaleHeight     =   1680
   ScaleWidth      =   3795
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton btnCancel 
      Cancel          =   -1  'True
      Caption         =   "&Cancel"
      Height          =   372
      Left            =   2640
      TabIndex        =   5
      Top             =   1200
      Width           =   972
   End
   Begin VB.CommandButton btnAction 
      Caption         =   "Action"
      Default         =   -1  'True
      Height          =   372
      Left            =   120
      TabIndex        =   3
      Top             =   1200
      Width           =   972
   End
   Begin VB.TextBox txtAlias 
      Height          =   288
      Left            =   960
      TabIndex        =   0
      Top             =   0
      Width           =   2772
   End
   Begin VB.ComboBox cmbLocation 
      Height          =   288
      Left            =   960
      TabIndex        =   1
      Top             =   360
      Width           =   2772
   End
   Begin VB.ComboBox cmbSkill 
      Height          =   288
      Left            =   960
      TabIndex        =   2
      Top             =   720
      Width           =   2772
   End
   Begin VB.Label Label1 
      Caption         =   "Location"
      Height          =   252
      Index           =   1
      Left            =   0
      TabIndex        =   7
      Top             =   360
      Width           =   972
   End
   Begin VB.Label Label1 
      Caption         =   "Alias"
      Height          =   252
      Index           =   0
      Left            =   0
      TabIndex        =   6
      Top             =   0
      Width           =   972
   End
   Begin VB.Label Label1 
      Caption         =   "Skill"
      Height          =   252
      Index           =   2
      Left            =   0
      TabIndex        =   4
      Top             =   720
      Width           =   972
   End
End
Attribute VB_Name = "frmTechMaint"
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
Private Const OBJNAME = "frmTechMaint"
Dim m_sAlias As String
Dim m_iSkillID As Integer
Dim m_iLocationID As Integer
Dim m_iAction As TECH_MAINTENANCE

Private Sub DisplayError(ByVal ErrorID As RES_IDS, Optional ByVal ErrorMsg As String)
Dim sMsg As String

If ErrorID = icIDS_USEMSGASERROR Then
    sMsg = ErrorMsg
Else
    sMsg = LoadResString(ErrorID)
End If

MsgBox prompt:=sMsg, Title:=Trim$(App.Title) & ":" & OBJNAME

End Sub

Private Function InvokeError(ByVal ErrorID As RES_IDS, Optional ByVal ErrorMsg As String) As Boolean
Dim sMsg As String
Dim lErr As Long

sMsg = Trim$(App.Title) & ":" & OBJNAME
lErr = Err

If ErrorID = icIDS_USEMSGASERROR Then
    sMsg = sMsg & " " & ErrorMsg
Else
    sMsg = sMsg & " " & LoadResString(ErrorID)
End If

If lErr < vbObjectError Then
    lErr = lErr + vbObjectError
End If

On Error GoTo 0
Err.Raise lErr, sMsg, Err.Description
End Function

Private Sub btnAction_Click()
    Dim oTech As hdclient.CTech

    On Error Resume Next
    
    Select Case m_iAction
    Case TECH_ADD
        'fill in properties that require validation first
        If Len(txtAlias) = 0 Then
            DisplayError icIDS_ERR_ILLEGAL_VALUE
            txtAlias.SetFocus
            Exit Sub
        End If
        
        Set oTech = New hdclient.CTech
        oTech.Alias = txtAlias
        If Err Then
            DisplayError icIDS_ERR_ILLEGAL_VALUE
            txtAlias.SetFocus
            Set oTech = Nothing
            Exit Sub
        End If
        
        'fill in the rest of the properties
        oTech.LocationId = cmbLocation.ItemData(cmbLocation.ListIndex)
        If oTech.LocationId = 0 Then
            DisplayError icIDS_ERR_ILLEGAL_VALUE
            cmbLocation.SetFocus
            Set oTech = Nothing
            Exit Sub
        End If
        oTech.SkillId = cmbSkill.ItemData(cmbSkill.ListIndex)
        If oTech.SkillId = 0 Then
            DisplayError icIDS_ERR_ILLEGAL_VALUE
            cmbSkill.SetFocus
            Set oTech = Nothing
            Exit Sub
        End If
        
        'insert object into database via CAdmin object, with validation
        g_oSysAdmin.Insert oTech:=oTech
        If Err Then
            DisplayError icIDS_ERR_CANT_INSERT
            Set oTech = Nothing
            Exit Sub
        End If
        
    Case TECH_UPDATE
        If Len(txtAlias) = 0 Then
            DisplayError icIDS_ERR_ILLEGAL_VALUE
            txtAlias.SetFocus
            Exit Sub
        End If
        
        Set oTech = g_oTechAdmin.GetTechByAlias(txtAlias)
        If Err Then
            DisplayError icIDS_ERR_ILLEGAL_VALUE
            txtAlias.SetFocus
            Set oTech = Nothing
            Exit Sub
        End If
        
        'fill in the rest of the properties
        oTech.LocationId = cmbLocation.ItemData(cmbLocation.ListIndex)
        If oTech.LocationId = 0 Then
            DisplayError icIDS_ERR_ILLEGAL_VALUE
            cmbLocation.SetFocus
            Set oTech = Nothing
            Exit Sub
        End If
        oTech.SkillId = cmbSkill.ItemData(cmbSkill.ListIndex)
        If oTech.SkillId = 0 Then
            DisplayError icIDS_ERR_ILLEGAL_VALUE
            cmbSkill.SetFocus
            Set oTech = Nothing
            Exit Sub
        End If
        
        'insert object into database via CAdmin object, with validation
        g_oSysAdmin.Update oTech:=oTech
        If Err Then
            DisplayError icIDS_ERR_CANT_UPDATE
            Set oTech = Nothing
            Exit Sub
        End If
        
    Case TECH_DELETE
        'fill in properties that require validation first
        If Len(txtAlias) = 0 Then
            DisplayError icIDS_ERR_ILLEGAL_VALUE
            txtAlias.SetFocus
            Exit Sub
        End If
        
        Set oTech = New hdclient.CTech
        oTech.Alias = txtAlias
        If Err Then
            DisplayError icIDS_ERR_ILLEGAL_VALUE
            txtAlias.SetFocus
            Exit Sub
        End If
        
        'insert object into database via CAdmin object, with validation
        g_oSysAdmin.Delete oTech:=oTech
        If Err Then
            DisplayError icIDS_ERR_CANT_DELETE
            Set oTech = Nothing
            Exit Sub
        End If
        
    End Select
    
    Set oTech = Nothing
    Unload Me
    
End Sub

Private Sub btnCancel_Click()

    Unload Me
    
End Sub
Public Sub SetParameters(ByVal iAction As TECH_MAINTENANCE, Optional oTech As CTech)
    Dim n As Integer

    m_iAction = iAction
    If oTech Is Nothing Then
        m_sAlias = ""
        m_iSkillID = -1
        m_iLocationID = -1
    Else
        m_sAlias = oTech.Alias
        m_iSkillID = oTech.SkillId
        m_iLocationID = oTech.LocationId
    End If
    txtAlias = m_sAlias
    
    If m_iLocationID < 1 Then
        cmbLocation.Text = LoadResString(icIDS_PH_SELECTFROMLIST)
    Else
        For n = 0 To cmbLocation.ListCount - 1
            If cmbLocation.ItemData(n) = m_iLocationID Then
                cmbLocation.Text = cmbLocation.List(n)
                Exit For
            End If
        Next n
    End If

    If m_iSkillID < 1 Then
        cmbSkill.Text = LoadResString(icIDS_PH_SELECTFROMLIST)
    Else
        For n = 0 To cmbSkill.ListCount - 1
            If cmbSkill.ItemData(n) = m_iSkillID Then
                cmbSkill.Text = cmbSkill.List(n)
                Exit For
            End If
        Next n
    End If

    Select Case iAction
    Case TECH_ADD
        btnAction.Caption = LoadResString(icIDS_BTN_ADDNEW)
    Case TECH_UPDATE
        btnAction.Caption = LoadResString(icIDS_BTN_UPDATE)
    Case TECH_DELETE
        btnAction.Caption = LoadResString(icIDS_BTN_DELETE)
    End Select

End Sub

Private Sub Form_Load()

    Dim oLocation As CLocation
    Dim oSkill As CSkill
    Dim cColl As Collection
    Dim lindex As Long
    
    Set cColl = g_oTechAdmin.GetLocations
    For Each oLocation In cColl
        cmbLocation.AddItem oLocation.Desc
        cmbLocation.ItemData(cmbLocation.NewIndex) = oLocation.PKid
    Next oLocation
    
    Set cColl = Nothing
    ' Select item in list
    For lindex = 0 To cmbLocation.ListCount - 1
        If cmbLocation.ItemData(lindex) = m_iLocationID Then
            cmbLocation.ListIndex = lindex
            Exit For
        End If
    Next
    
'Dim m_iSkillID As Integer
'Dim m_iLocationID As Integer

    Set cColl = g_oTechAdmin.GetSkills
    For Each oSkill In cColl
        cmbSkill.AddItem oSkill.Desc
        cmbSkill.ItemData(cmbSkill.NewIndex) = oSkill.PKid
    Next oSkill
    Set cColl = Nothing
    ' Select item in list
    For lindex = 0 To cmbSkill.ListCount - 1
        If cmbSkill.ItemData(lindex) = m_iSkillID Then
            cmbSkill.ListIndex = lindex
            Exit For
        End If
    Next

End Sub

Private Sub txtAlias_Change()
    Dim sValidFirstChars As String

    'emailalias' must start with a certain range of characters
    If Len(txtAlias) Then
        sValidFirstChars = LoadResString(icIDS_VALIDTECHALIASSTARTS)
        If InStr(1, sValidFirstChars, Left(txtAlias, 1)) = 0 Then
            Dim cTags As Collection
            Set cTags = New Collection
            cTags.Add sValidFirstChars, "RANGE"
            MsgBox g_oHDExt.ReplaceTags(LoadResString(icIDS_ERR_INVALIDTECHALIAS), cTags)
            Set cTags = Nothing
        End If
    End If
End Sub


