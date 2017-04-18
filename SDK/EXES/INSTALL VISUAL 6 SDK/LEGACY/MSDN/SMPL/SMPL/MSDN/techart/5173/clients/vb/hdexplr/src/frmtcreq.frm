VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "comctl32.ocx"
Begin VB.Form frmTechReqs 
   Caption         =   "Technician Reqests"
   ClientHeight    =   3255
   ClientLeft      =   45
   ClientTop       =   270
   ClientWidth     =   6750
   LinkTopic       =   "Form1"
   ScaleHeight     =   3255
   ScaleWidth      =   6750
   StartUpPosition =   2  'CenterScreen
   Begin ComctlLib.ListView lv_TechnicianRequests 
      Height          =   2532
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   6492
      _ExtentX        =   11456
      _ExtentY        =   4471
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   327682
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   8
      BeginProperty ColumnHeader(1) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         Key             =   "TrackingNo"
         Object.Tag             =   ""
         Text            =   "Tracking No."
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(2) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   1
         Key             =   "Status"
         Object.Tag             =   ""
         Text            =   "Status"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(3) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   2
         Key             =   "Technician"
         Object.Tag             =   ""
         Text            =   "Technician"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(4) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   3
         Key             =   "Location"
         Object.Tag             =   ""
         Text            =   "Location"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(5) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   4
         Key             =   "Skill"
         Object.Tag             =   ""
         Text            =   "Skill"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(6) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   5
         Key             =   "Priorirty"
         Object.Tag             =   ""
         Text            =   "Priorirty"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(7) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   6
         Key             =   "Request"
         Object.Tag             =   ""
         Text            =   "Request"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(8) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   7
         Key             =   ""
         Object.Tag             =   ""
         Text            =   ""
         Object.Width           =   2540
      EndProperty
   End
   Begin VB.CommandButton btnClose 
      Caption         =   "&Close"
      Default         =   -1  'True
      Height          =   372
      Left            =   5640
      TabIndex        =   0
      Top             =   2760
      Width           =   972
   End
End
Attribute VB_Name = "frmTechReqs"
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

Private m_oTech As hdclient.CTech

Private m_bt As Integer
Private m_bl As Integer
Private m_dh As Integer
Private m_dw As Integer

Public Property Get Tech() As CTech
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Tech
    Set Tech = m_oTech
End Property

Public Property Set Tech(oTech As CTech)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Tech = y
    Set m_oTech = oTech
End Property



Private Sub btnClose_Click()
    Unload Me
End Sub


Private Sub Form_Load()
Dim oRequest As hdclient.CRequest
Dim cRequests As Collection
Dim oReqStatus As hdclient.CReqStatus
Dim cReqStatuses As Collection
Dim oLocation As hdclient.CLocation
Dim cLocations As Collection
Dim oSkill As hdclient.CSkill
Dim cSkills As Collection
Dim oPriority As hdclient.CPriority
Dim cPriorities As Collection
Dim oItem As ListItem

    m_bt = (Me.Height - btnClose.Top) + 100
    m_bl = Me.Width - btnClose.Left
    m_dh = Me.Height - lv_TechnicianRequests.Height
    m_dw = Me.Width - lv_TechnicianRequests.Width
    
    Set cReqStatuses = g_oTechAdmin.GetReqStatus
    Set cLocations = g_oTechAdmin.GetLocations
    Set cSkills = g_oTechAdmin.GetSkills
    Set cPriorities = g_oTechAdmin.GetPriorities

    If m_oTech Is Nothing Then
        'get all requests
        Set cRequests = g_oSysAdmin.GetRequestsByTechId(0)
    Else
        'get specfic technicians requests
        Set cRequests = g_oSysAdmin.GetRequestsByTechId(m_oTech.PKid)
    End If

    For Each oRequest In cRequests
        Set oItem = lv_TechnicianRequests.ListItems.Add(Key:=g_oTechAdmin.Format_ItemPKId(oRequest.PKid), Text:=CStr(oRequest.TrackingNo))
        oItem.SubItems(2) = oRequest.Alias
        oItem.SubItems(6) = oRequest.Desc
        
        Set oReqStatus = cReqStatuses(g_oTechAdmin.Format_ItemPKId(oRequest.StatusId))
        oItem.SubItems(1) = oReqStatus.Desc
        Set oReqStatus = Nothing
        Set oLocation = cLocations(g_oTechAdmin.Format_ItemPKId(oRequest.LocId))
        oItem.SubItems(3) = oLocation.Desc
        Set oLocation = Nothing
        Set oSkill = cSkills(g_oTechAdmin.Format_ItemPKId(oRequest.SkillId))
        oItem.SubItems(4) = oSkill.Desc
        Set oSkill = Nothing
        Set oPriority = cPriorities(g_oTechAdmin.Format_ItemPKId(oRequest.PriorityId))
        oItem.SubItems(5) = oPriority.Desc
        Set oPriority = Nothing
    Next oRequest
    
    Set cRequests = Nothing
End Sub


Private Sub Form_Resize()
    On Error Resume Next
    
    btnClose.Top = Me.Height - m_bt
    btnClose.Left = Me.Width - m_bl
    lv_TechnicianRequests.Height = Me.Height - m_dh
    lv_TechnicianRequests.Width = Me.Width - m_dw

End Sub


Private Sub lv_TechnicianRequests_ColumnClick(ByVal ColumnHeader As ComctlLib.ColumnHeader)

    lv_TechnicianRequests.Sorted = True
    lv_TechnicianRequests.SortKey = ColumnHeader.Index - 1

End Sub

Private Sub lv_TechnicianRequests_DblClick()
Dim oItem As ListItem
Dim n As Integer
Dim oRequest As hdclient.CRequest

    Set oItem = lv_TechnicianRequests.SelectedItem
    n = CLng(oItem)
    Set oRequest = g_oSysAdmin.GetRequest(n)
    Set frmRequestDetails.Request = oRequest
    frmRequestDetails.Show vbModal
End Sub


