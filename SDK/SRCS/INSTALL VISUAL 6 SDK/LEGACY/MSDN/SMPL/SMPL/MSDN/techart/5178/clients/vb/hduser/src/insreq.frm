VERSION 5.00
Begin VB.Form frmInsReq 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Create a New Request"
   ClientHeight    =   3660
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7590
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3660
   ScaleWidth      =   7590
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton Command1 
      Caption         =   "&Cancel"
      Height          =   375
      Left            =   6240
      TabIndex        =   9
      Top             =   3240
      Width           =   1215
   End
   Begin VB.ComboBox cmbSkill 
      Height          =   315
      Left            =   4680
      Style           =   2  'Dropdown List
      TabIndex        =   5
      Top             =   240
      Width           =   2895
   End
   Begin VB.ComboBox cmbPriority 
      Height          =   315
      Left            =   2280
      Style           =   2  'Dropdown List
      TabIndex        =   3
      Top             =   240
      Width           =   2295
   End
   Begin VB.ComboBox cmbLoc 
      Height          =   315
      Left            =   0
      Style           =   2  'Dropdown List
      TabIndex        =   1
      Top             =   240
      Width           =   2175
   End
   Begin VB.CommandButton cmdSend 
      Caption         =   "&Send"
      Height          =   375
      Left            =   4920
      TabIndex        =   8
      Top             =   3240
      Width           =   1215
   End
   Begin VB.TextBox txtReq 
      Height          =   2295
      Left            =   0
      MultiLine       =   -1  'True
      TabIndex        =   7
      Top             =   840
      Width           =   7575
   End
   Begin VB.Label lblSkills 
      Caption         =   "Category"
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
      Left            =   5400
      TabIndex        =   4
      Top             =   0
      Width           =   1215
   End
   Begin VB.Label lblPriority 
      Caption         =   "Priority"
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
      Left            =   2880
      TabIndex        =   2
      Top             =   0
      Width           =   735
   End
   Begin VB.Label lblLoc 
      Caption         =   "Location"
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
      Left            =   600
      TabIndex        =   0
      Top             =   0
      Width           =   855
   End
   Begin VB.Label lblReqTxt 
      Caption         =   "Description"
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
      Left            =   3000
      TabIndex        =   6
      Top             =   600
      Width           =   1215
   End
End
Attribute VB_Name = "frmInsReq"
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
'   Synopsis :  This dialog allows you to format a request by location,
'               priority, and skill
'=======================================================================


Private Sub cmdSend_Click()
    Dim oReq        As HDClient.CRequest
    Dim oReqDet     As HDClient.CReqDetail
    Dim lTrackNo    As Long
    
    'validate location
    If (cmbLoc.ListIndex < icNumberZero) Then
        MsgBox LoadResString(icIDS_ERR_NOLOCATION)
        cmbLoc.SetFocus
        Exit Sub
    End If
    
    'validate priority
    If (cmbPriority.ListIndex < icNumberZero) Then
        MsgBox LoadResString(icIDS_ERR_NOPRIORITY)
        cmbPriority.SetFocus
        Exit Sub
    End If
    
    'validate skill
    If (cmbSkill.ListIndex < icNumberZero) Then
        MsgBox LoadResString(icIDS_ERR_NOSKILL)
        cmbSkill.SetFocus
        Exit Sub
    End If
    
    'validate request text
    If Trim$(txtReq) = vbNullString Then
        MsgBox LoadResString(icIDS_ERR_NOREQDESC)
        txtReq.SetFocus
        Exit Sub
    End If
    
    'call method on Admin to get new request object
    Set oReq = New HDClient.CRequest
    
    'set the attributes on the object
    oReq.LocId = cmbLoc.ItemData(cmbLoc.ListIndex)
    g_lLocationId = oReq.LocId
    oReq.PriorityId = cmbPriority.ItemData(cmbPriority.ListIndex)
    g_lPriorityId = oReq.PriorityId
    oReq.SkillId = cmbSkill.ItemData(cmbSkill.ListIndex)
    oReq.Alias = g_sEAlias
    If Len(Trim$(txtReq)) < 51 Then
        oReq.Desc = Trim$(txtReq)           'Sets the Description attribute
    Else
        oReq.Desc = Left(Trim$(txtReq), 50) 'Sets the Description attribute
    End If
    
    'call the insert method on the Admin object
    If Not g_oAdmin.InsertRequest(oReq, lTrackNo) Then
        MsgBox LoadResString(icIDS_ERR_INSERTFAILED)
    End If
    
    'get a new request detail object
    Set oReqDet = New HDClient.CReqDetail
    
    'set attributes for request object
    oReq.Alias = g_sEAlias
    oReq.TrackingNo = lTrackNo
    
    'add request detail
    oReqDet.DetailText = Trim$(txtReq)           'Sets the Description attribute
    
    'set the request for the request detail object
    Set oReqDet.Request = oReq
    
    'call method on the Admin object to send text request
    If Not (g_oAdmin.SendTextRequest(oReqDet)) Then
        MsgBox LoadResString(icIDS_ERR_SENDREQTEXT)
    End If
    
    'clean up
    Set oReq = Nothing
    Set oReqDet = Nothing
    
    Unload Me

End Sub

Private Sub Command1_Click()

    Unload Me

End Sub

Private Sub Form_Load()
    On Error GoTo FLoadErr
    
    'fill the location listbox
    FillLocations
    
    'fill the priority listbox
    FillPriorities
    
    'fill the Skill listbox
    FillSkills
    
    Exit Sub
    
FLoadErr:
    MsgBox Err.Number & " : " & Err.Description '@@
    Err.Clear
End Sub

'=======================================================================
'Synopsis:              This Sub fills the locations list.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillLocations()
    Dim oLocs       As Collection
    Dim oLoc        As HDClient.CLocation
    
    Dim iTemp       As Integer
    Dim iIndex      As Integer
    
    
    'get the list of locations
    Set oLocs = g_oAdmin.GetLocations()
    
    iIndex = -1
    For Each oLoc In oLocs
        cmbLoc.AddItem oLoc.Desc
        cmbLoc.ItemData(cmbLoc.NewIndex) = oLoc.PKId
        If oLoc.PKId = g_lLocationId Then
            iIndex = cmbLoc.NewIndex
        End If
    Next
    If iIndex <> -1 Then
        cmbLoc.Text = cmbLoc.List(iIndex)
    End If
    
    'Clean up
    Set oLoc = Nothing
    Set oLocs = Nothing

End Sub

'=======================================================================
'Synopsis:              This Sub fills the priorities list.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillPriorities()
    Dim oPriorities As Collection
    Dim oPriority   As HDClient.CPriority
    
    Dim iTemp       As Integer
    Dim iIndex      As Integer

    
    'get the list of priorities
    Set oPriorities = g_oAdmin.GetPriorities()
    
    iIndex = -1
    For Each oPriority In oPriorities
        cmbPriority.AddItem oPriority.Desc
        cmbPriority.ItemData(cmbPriority.NewIndex) = oPriority.PKId
        If oPriority.PKId = g_lLocationId Then
            iIndex = cmbPriority.NewIndex
        End If
    Next
    If iIndex <> -1 Then
        cmbPriority.Text = cmbPriority.List(iIndex)
    End If
    
    'clean up
    Set oPriority = Nothing
    Set oPriorities = Nothing
End Sub

'=======================================================================
'Synopsis:              This Sub fills the skills list.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillSkills()
    Dim oSkills     As Collection
    Dim oSkill      As HDClient.CSkill
    
    Dim iTemp       As Integer
        
    'get the list of skills
    Set oSkills = g_oAdmin.GetSkills()
    
    For Each oSkill In oSkills
        cmbSkill.AddItem oSkill.Desc
        cmbSkill.ItemData(cmbSkill.NewIndex) = oSkill.PKId
    Next
    
    'clean up
    Set oSkill = Nothing
    Set oSkills = Nothing
End Sub
