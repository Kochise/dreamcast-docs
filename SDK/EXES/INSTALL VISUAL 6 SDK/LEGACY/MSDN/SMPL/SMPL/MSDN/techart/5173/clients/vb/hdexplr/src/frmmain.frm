VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "comdlg32.ocx"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "comctl32.ocx"
Begin VB.Form frmMain 
   Caption         =   "HelpDesk Explorer"
   ClientHeight    =   3405
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   7065
   LinkTopic       =   "Form1"
   ScaleHeight     =   3405
   ScaleWidth      =   7065
   StartUpPosition =   3  'Windows Default
   Begin ComctlLib.Toolbar tbToolBar 
      Align           =   1  'Align Top
      Height          =   420
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   7065
      _ExtentX        =   12462
      _ExtentY        =   741
      ButtonWidth     =   508
      ButtonHeight    =   466
      Appearance      =   1
      ImageList       =   "imlIcons"
      _Version        =   327682
      BeginProperty Buttons {0713E452-850A-101B-AFC0-4210102A8DA7} 
         NumButtons      =   14
         BeginProperty Button1 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Back"
            Object.ToolTipText     =   "Back"
            Object.Tag             =   ""
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Forward"
            Object.ToolTipText     =   "Forward"
            Object.Tag             =   ""
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   ""
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button4 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Cut"
            Object.ToolTipText     =   "Cut"
            Object.Tag             =   ""
            ImageIndex      =   3
         EndProperty
         BeginProperty Button5 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Copy"
            Object.ToolTipText     =   "Copy"
            Object.Tag             =   ""
            ImageIndex      =   4
         EndProperty
         BeginProperty Button6 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Paste"
            Object.ToolTipText     =   "Paste"
            Object.Tag             =   ""
            ImageIndex      =   5
         EndProperty
         BeginProperty Button7 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Delete"
            Object.ToolTipText     =   "Delete"
            Object.Tag             =   ""
            ImageIndex      =   6
         EndProperty
         BeginProperty Button8 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   ""
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button9 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Properties"
            Object.ToolTipText     =   "Properties"
            Object.Tag             =   ""
            ImageIndex      =   7
         EndProperty
         BeginProperty Button10 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   ""
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button11 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "ViewLarge"
            Object.ToolTipText     =   "Large Icon View"
            Object.Tag             =   ""
            ImageIndex      =   8
            Style           =   2
         EndProperty
         BeginProperty Button12 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "ViewSmall"
            Object.ToolTipText     =   "Small Icon View"
            Object.Tag             =   ""
            ImageIndex      =   9
            Style           =   2
         EndProperty
         BeginProperty Button13 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "ViewList"
            Object.ToolTipText     =   "List View"
            Object.Tag             =   ""
            ImageIndex      =   10
            Style           =   2
         EndProperty
         BeginProperty Button14 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "ViewDetails"
            Object.ToolTipText     =   "Details View"
            Object.Tag             =   ""
            ImageIndex      =   11
            Style           =   2
         EndProperty
      EndProperty
   End
   Begin ComctlLib.TreeView tv_ComponentTree 
      Height          =   2160
      Left            =   0
      TabIndex        =   6
      Top             =   708
      Width           =   2016
      _ExtentX        =   3545
      _ExtentY        =   3810
      _Version        =   327682
      Indentation     =   353
      LabelEdit       =   1
      LineStyle       =   1
      Style           =   7
      Appearance      =   1
   End
   Begin VB.PictureBox picSplitter 
      BackColor       =   &H00808080&
      BorderStyle     =   0  'None
      FillColor       =   &H00808080&
      Height          =   2160
      Left            =   5400
      ScaleHeight     =   938.182
      ScaleMode       =   0  'User
      ScaleWidth      =   468
      TabIndex        =   7
      Top             =   705
      Visible         =   0   'False
      Width           =   72
   End
   Begin ComctlLib.ListView lv_ContentsList 
      Height          =   2160
      Left            =   2052
      TabIndex        =   5
      Top             =   708
      Width           =   3216
      _ExtentX        =   5662
      _ExtentY        =   3810
      LabelEdit       =   1
      Sorted          =   -1  'True
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   327682
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin VB.PictureBox picTitles 
      Align           =   1  'Align Top
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   300
      Left            =   0
      ScaleHeight     =   300
      ScaleWidth      =   7065
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   420
      Width           =   7068
      Begin VB.Label lblTitle 
         BorderStyle     =   1  'Fixed Single
         Caption         =   " Contents"
         Height          =   270
         Index           =   1
         Left            =   2078
         TabIndex        =   4
         Tag             =   " ListView:"
         Top             =   12
         Width           =   3216
      End
      Begin VB.Label lblTitle 
         BorderStyle     =   1  'Fixed Single
         Caption         =   " Component"
         Height          =   270
         Index           =   0
         Left            =   0
         TabIndex        =   3
         Tag             =   " TreeView:"
         Top             =   12
         Width           =   2016
      End
   End
   Begin ComctlLib.StatusBar sbStatusBar 
      Align           =   2  'Align Bottom
      Height          =   270
      Left            =   0
      TabIndex        =   0
      Top             =   3135
      Width           =   7065
      _ExtentX        =   12462
      _ExtentY        =   476
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   3
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   1
            Object.Width           =   6826
            Text            =   "Status"
            TextSave        =   "Status"
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Style           =   6
            AutoSize        =   2
            TextSave        =   "1/30/98"
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel3 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Style           =   5
            AutoSize        =   2
            TextSave        =   "4:53 PM"
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComDlg.CommonDialog dlgCommonDialog 
      Left            =   1392
      Top             =   1056
      _ExtentX        =   688
      _ExtentY        =   688
      _Version        =   327681
   End
   Begin ComctlLib.ImageList imlBigIcons 
      Left            =   0
      Top             =   0
      _ExtentX        =   794
      _ExtentY        =   794
      BackColor       =   -2147483643
      ImageWidth      =   32
      ImageHeight     =   32
      MaskColor       =   12632256
      _Version        =   327682
   End
   Begin VB.Image imgSplitter 
      Height          =   2148
      Left            =   1968
      MousePointer    =   9  'Size W E
      Top             =   708
      Width           =   156
   End
   Begin ComctlLib.ImageList imlIcons 
      Left            =   1392
      Top             =   1056
      _ExtentX        =   794
      _ExtentY        =   794
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   11
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":0000
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":0526
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":0A4C
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":0F72
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":1498
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":19BE
            Key             =   ""
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":1EE4
            Key             =   ""
         EndProperty
         BeginProperty ListImage8 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":240A
            Key             =   ""
         EndProperty
         BeginProperty ListImage9 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":2930
            Key             =   ""
         EndProperty
         BeginProperty ListImage10 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":2E56
            Key             =   ""
         EndProperty
         BeginProperty ListImage11 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":337C
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFileOpen 
         Caption         =   "&Open"
      End
      Begin VB.Menu mnuFileFind 
         Caption         =   "&Find"
      End
      Begin VB.Menu mnuFileBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileSendTo 
         Caption         =   "Sen&d to"
      End
      Begin VB.Menu mnuFileBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileNew 
         Caption         =   "&New"
      End
      Begin VB.Menu mnuFileBar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileDelete 
         Caption         =   "&Delete"
      End
      Begin VB.Menu mnuFileRename 
         Caption         =   "Rena&me"
      End
      Begin VB.Menu mnuFileProperties 
         Caption         =   "Propert&ies"
      End
      Begin VB.Menu mnuFileBar4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileMRU 
         Caption         =   ""
         Index           =   0
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileMRU 
         Caption         =   ""
         Index           =   1
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileMRU 
         Caption         =   ""
         Index           =   2
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileMRU 
         Caption         =   ""
         Index           =   3
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileBar5 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileClose 
         Caption         =   "&Close"
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "&View"
      Begin VB.Menu mnuViewToolbar 
         Caption         =   "&Toolbar"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewStatusBar 
         Caption         =   "Status &Bar"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuListViewMode 
         Caption         =   "Lar&ge Icons"
         Index           =   0
      End
      Begin VB.Menu mnuListViewMode 
         Caption         =   "S&mall Icons"
         Index           =   1
      End
      Begin VB.Menu mnuListViewMode 
         Caption         =   "&List"
         Index           =   2
      End
      Begin VB.Menu mnuListViewMode 
         Caption         =   "&Details"
         Index           =   3
      End
      Begin VB.Menu mnuViewBar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuViewArrangeIcons 
         Caption         =   "Arrange &Icons"
         Begin VB.Menu mnuVAIByDate 
            Caption         =   "by &Date"
         End
         Begin VB.Menu mnuVAIByName 
            Caption         =   "by &Name"
         End
         Begin VB.Menu mnuVAIByType 
            Caption         =   "by &Type"
         End
         Begin VB.Menu mnuVAIBySize 
            Caption         =   "by &Size"
         End
      End
      Begin VB.Menu mnuViewLineUpIcons 
         Caption         =   "Li&ne Up Icons"
      End
      Begin VB.Menu mnuViewBar4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuViewRefresh 
         Caption         =   "&Refresh"
      End
      Begin VB.Menu mnuViewOptions 
         Caption         =   "&Options..."
      End
      Begin VB.Menu mnuViewBrowser 
         Caption         =   "&Web Browser"
      End
      Begin VB.Menu mnuViewBar5 
         Caption         =   "-"
      End
      Begin VB.Menu mnuViewAllRequests 
         Caption         =   "View &all requests"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuHelpContents 
         Caption         =   "&Contents"
      End
      Begin VB.Menu mnuHelpSearch 
         Caption         =   "&Search For Help On..."
      End
      Begin VB.Menu mnuHelpBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "&About HDExplr..."
      End
   End
End
Attribute VB_Name = "frmMain"
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
Private Const OBJNAME = "frmMain"
Const NAME_COLUMN = 0
Const TYPE_COLUMN = 1
Const SIZE_COLUMN = 2
Const DATE_COLUMN = 3
  
Dim mbMoving As Boolean
Dim m_ItemClicked As ComctlLib.ListItem

Const sglSplitLimit = 500
Private Declare Function OSWinHelp Lib "user32" Alias "WinHelpA" (ByVal hwnd&, ByVal HelpFile$, ByVal wCommand%, dwData As Any) As Integer

Private m_tvPathSep As String

Private m_Node_Technician As String
Private m_Node_SystemParms As String

Private m_Node_Location As String
Private m_Node_Skill As String
Private m_Node_Priority As String
Private m_Node_AuditTypes As String
Private m_Node_ReqDetType As String
Private m_Node_Status As String
Private m_Node_StdTextResp As String
Private m_Node_StdVocResp As String
Private m_Node_TechStatus As String

Private m_Node_Domains As String
Private m_Node_DomainLocations As String
Private m_Node_DomainPriorities As String
Private m_Node_DomainSkills As String
Private m_Node_DomainAuditTypes As String
Private m_Node_DomainReqDetType As String
Private m_Node_DomainStatus As String
Private m_Node_DomainStdTextResp As String
Private m_Node_DomainStdVocResp As String
Private m_Node_DomainTechStatus As String

Public Sub FillInitialList()
    Dim oItem As ListItem
    Dim sMisc As String
    Dim iCount As Integer
    Dim oDomainTechnician As CTech
    Dim oLocation As CLocation
    Dim oSkill As CSkill
    Dim oDomainTechnicians As Collection
    
    iCount = 0
    
    tv_ComponentTree.Nodes(m_Node_Technician).Selected = True
    lv_ContentsList.ListItems.Clear
    If lv_ContentsList.View = lvwReport Then
        SetColumnHeadings
    End If
    
    Refresh_technicians True
'    Set oDomainTechnicians = g_oTechAdmin.GetTechnicians
'    For Each oDomainTechnician In oDomainTechnicians
'        If lv_ContentsList.View = lvwReport Then
'            sMisc = oDomainTechnician.Alias
'            Set oItem = lv_ContentsList.ListItems.Add(Key:=sMisc, Text:=sMisc, Icon:=m_Node_Technician, SmallIcon:=m_Node_Technician)
'            Set oLocation = g_oTechAdmin.GetLocations.Item(g_oSysAdmin.FmtPKId(oDomainTechnician.LocationId))
'            oItem.SubItems(1) = oLocation.Desc
'            Set oSkill = g_oTechAdmin.GetSkills.Item(g_oSysAdmin.FmtPKId(oDomainTechnician.SkillId))
'            oItem.SubItems(2) = oSkill.Desc
'        Else
'            lv_ContentsList.ListItems.Add Key:=oDomainTechnician.Alias, Text:=oDomainTechnician.Alias, Icon:=m_Node_Technician, SmallIcon:=m_Node_Technician
'        End If
'        iCount = iCount + 1
'    Next oDomainTechnician
'    Set oDomainTechnicians = Nothing
        
    sbStatusBar.Panels.Item(1) = CStr(iCount) & " items"
End Sub

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





Private Function Refresh_technicians(ByVal bClearListView As Boolean) As Integer
    Dim oItem As ListItem
    Dim sMisc As String
    Dim iCount As Integer
    Dim oDomainTechnician As CTech
    Dim oLocation As CLocation
    Dim oSkill As CSkill
    Dim oDomainTechnicians As Collection
    
    On Error Resume Next
    
    lv_ContentsList.ListItems.Clear
    
    g_oTechAdmin.Refresh
    
    iCount = 0

    Set oDomainTechnicians = g_oTechAdmin.GetTechnicians
    For Each oDomainTechnician In oDomainTechnicians
        If lv_ContentsList.View = lvwReport Then
            sMisc = oDomainTechnician.Alias
            Set oItem = lv_ContentsList.ListItems.Add(Key:=sMisc, Text:=sMisc, Icon:=m_Node_Technician, SmallIcon:=m_Node_Technician)
            Set oLocation = g_oTechAdmin.GetLocations.Item(g_oSysAdmin.FmtPKId(oDomainTechnician.LocationId))
            oItem.SubItems(1) = oLocation.Desc
            Set oSkill = g_oTechAdmin.GetSkills.Item(g_oSysAdmin.FmtPKId(oDomainTechnician.SkillId))
            oItem.SubItems(2) = oSkill.Desc
        Else
            lv_ContentsList.ListItems.Add Key:=oDomainTechnician.Alias, Text:=oDomainTechnician.Alias, Icon:=m_Node_Technician, SmallIcon:=m_Node_Technician
        End If
        iCount = iCount + 1
    Next oDomainTechnician
    
    Set oDomainTechnicians = Nothing
    
    Refresh_technicians = iCount

End Function

Private Sub Form_Load()
    Dim sNodeKey As String
    
    'get form persistance seetings
    Me.Left = GetSetting(App.Title, "Settings", "MainLeft", 1000)
    Me.Top = GetSetting(App.Title, "Settings", "MainTop", 1000)
    Me.Width = GetSetting(App.Title, "Settings", "MainWidth", 6500)
    Me.Height = GetSetting(App.Title, "Settings", "MainHeight", 6500)
    
    'initialize vars and values from resource file
    m_tvPathSep = tv_ComponentTree.PathSeparator
    m_Node_Domains = LoadResString(icIDS_KWTV_DOMAINS)
    m_Node_Technician = LoadResString(icIDS_KWTV_TECHNICIAN)
    m_Node_Location = LoadResString(icIDS_KWTV_LOCATIONS)
    m_Node_Priority = LoadResString(icIDS_KWTV_PRIORITIES)
    m_Node_Skill = LoadResString(icIDS_KWTV_SKILLS)
    m_Node_SystemParms = LoadResString(icIDS_KWTV_SYSTEMPARMS)
'@@  m_Node_AuditTypes = LoadResString(icIDS_KWTV_AUDITTYPES)
'    m_Node_ReqDetType = LoadResString(icIDS_KWTV_REQDETTYPES)
'    m_Node_Status = LoadResString(icIDS_KWTV_STATUS)
'    m_Node_StdTextResp = LoadResString(icIDS_KWTV_STDTEXTRESP)
'    m_Node_StdVocResp = LoadResString(icIDS_KWTV_STDVOCRESP)
'    m_Node_TechStatus = LoadResString(icIDS_KWTV_TECHSTATUS)
    
    m_Node_DomainLocations = m_Node_Domains & m_tvPathSep & m_Node_Location
    m_Node_DomainPriorities = m_Node_Domains & m_tvPathSep & m_Node_Priority
    m_Node_DomainSkills = m_Node_Domains & m_tvPathSep & m_Node_Skill
'@@    m_Node_DomainAuditTypes = m_Node_Domains & m_tvPathSep & m_Node_AuditTypes
'    m_Node_DomainReqDetType = m_Node_Domains & m_tvPathSep & m_Node_ReqDetType
'    m_Node_DomainStatus = m_Node_Domains & m_tvPathSep & m_Node_Status
'    m_Node_DomainStdTextResp = m_Node_Domains & m_tvPathSep & m_Node_StdTextResp
'    m_Node_DomainStdVocResp = m_Node_Domains & m_tvPathSep & m_Node_StdVocResp
'    m_Node_DomainTechStatus = m_Node_Domains & m_tvPathSep & m_Node_TechStatus

    'load context menus
    Load frmContext
    
    ' Set Treeview control properties.
    tv_ComponentTree.LineStyle = tvwRootLines

    'build image list of icons for general tables
    imlIcons.ListImages.Add Key:=m_Node_Technician, Picture:=LoadResPicture(icIDI_TECHNICIAN, vbResIcon)
    imlBigIcons.ListImages.Add Key:=m_Node_Technician, Picture:=LoadResPicture(icIDI_TECHNICIAN, vbResIcon)
    imlIcons.ListImages.Add Key:=m_Node_SystemParms, Picture:=LoadResPicture(icIDI_SYSPARM, vbResIcon)
    imlBigIcons.ListImages.Add Key:=m_Node_SystemParms, Picture:=LoadResPicture(icIDI_SYSPARM, vbResIcon)

    'build image list of icons for "folders"
    imlIcons.ListImages.Add Key:=m_Node_Domains, Picture:=LoadResPicture(icIDI_DOMAINS, vbResIcon)
    imlBigIcons.ListImages.Add Key:=m_Node_Domains, Picture:=LoadResPicture(icIDI_DOMAINS, vbResIcon)
    imlIcons.ListImages.Add Key:=m_Node_DomainLocations, Picture:=LoadResPicture(icIDI_DOMAIN, vbResIcon)
    imlBigIcons.ListImages.Add Key:=m_Node_DomainLocations, Picture:=LoadResPicture(icIDI_DOMAIN, vbResIcon)
    imlIcons.ListImages.Add Key:=m_Node_DomainPriorities, Picture:=LoadResPicture(icIDI_DOMAIN, vbResIcon)
    imlBigIcons.ListImages.Add Key:=m_Node_DomainPriorities, Picture:=LoadResPicture(icIDI_DOMAIN, vbResIcon)
    imlIcons.ListImages.Add Key:=m_Node_DomainSkills, Picture:=LoadResPicture(icIDI_DOMAIN, vbResIcon)
    imlBigIcons.ListImages.Add Key:=m_Node_DomainSkills, Picture:=LoadResPicture(icIDI_DOMAIN, vbResIcon)
    
    'build image list of icons for domains
    imlIcons.ListImages.Add Key:=m_Node_Location, Picture:=LoadResPicture(icIDI_LOCATION, vbResIcon)
    imlBigIcons.ListImages.Add Key:=m_Node_Location, Picture:=LoadResPicture(icIDI_LOCATION, vbResIcon)
    imlIcons.ListImages.Add Key:=m_Node_Priority, Picture:=LoadResPicture(icIDI_PRIORITY, vbResIcon)
    imlBigIcons.ListImages.Add Key:=m_Node_Priority, Picture:=LoadResPicture(icIDI_PRIORITY, vbResIcon)
    imlIcons.ListImages.Add Key:=m_Node_Skill, Picture:=LoadResPicture(icIDI_SKILL, vbResIcon)
    imlBigIcons.ListImages.Add Key:=m_Node_Skill, Picture:=LoadResPicture(icIDI_SKILL, vbResIcon)

    'attach icons to visual components
    tv_ComponentTree.ImageList = imlIcons
    lv_ContentsList.SmallIcons = imlIcons
    lv_ContentsList.Icons = imlBigIcons
    
    ' First node with 'Root' as text.
    sNodeKey = m_Node_Technician
    tv_ComponentTree.Nodes.Add _
        Key:=sNodeKey, _
        Text:=m_Node_Technician, _
        Image:=m_Node_Technician
    
    sNodeKey = m_Node_Domains
    tv_ComponentTree.Nodes.Add _
        Key:=sNodeKey, _
        Text:=m_Node_Domains
    tv_ComponentTree.Nodes.Add _
        relative:=sNodeKey, _
        relationship:=tvwChild, _
        Key:=sNodeKey & m_Node_Location, _
        Text:=m_Node_Location, _
        Image:=m_Node_Location
    tv_ComponentTree.Nodes.Add _
        relative:=sNodeKey, _
        relationship:=tvwChild, _
        Key:=sNodeKey & m_Node_Priority, _
        Text:=m_Node_Priority, _
        Image:=m_Node_Priority
    tv_ComponentTree.Nodes.Add _
        relative:=sNodeKey, _
        relationship:=tvwChild, _
        Key:=sNodeKey & m_Node_Skill, _
        Text:=m_Node_Skill, _
        Image:=m_Node_Skill
    
    sNodeKey = m_Node_SystemParms
    tv_ComponentTree.Nodes.Add _
        Key:=sNodeKey, _
        Text:=m_Node_SystemParms, _
        Image:=m_Node_SystemParms
        
End Sub


Private Sub Form_Paint()
    
    lv_ContentsList.View = Val(GetSetting(App.Title, "Settings", "ViewMode", "0"))
    tbToolBar.Buttons(lv_ContentsList.View + LISTVIEW_BUTTON).Value = tbrPressed
    mnuListViewMode(lv_ContentsList.View).Checked = True
    
End Sub


Private Sub Form_Unload(Cancel As Integer)
    Dim i As Integer


    'close all sub forms
    For i = Forms.Count - 1 To 1 Step -1
        Unload Forms(i)
    Next
    If Me.WindowState <> vbMinimized Then
        SaveSetting App.Title, "Settings", "MainLeft", Me.Left
        SaveSetting App.Title, "Settings", "MainTop", Me.Top
        SaveSetting App.Title, "Settings", "MainWidth", Me.Width
        SaveSetting App.Title, "Settings", "MainHeight", Me.Height
    End If
    SaveSetting App.Title, "Settings", "ViewMode", lv_ContentsList.View
    
    basMain.Terminate
    
End Sub

Private Sub lv_ContentsList_ItemClick(ByVal Item As ComctlLib.ListItem)
    Set m_ItemClicked = Item
End Sub

Private Sub lv_ContentsList_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Dim oTech As CTech
    Dim oSysParm As CSysParm
    Dim iDomain As Integer
    Dim iAction As Integer
    Dim bDoSomething As Boolean
    Dim bDoAdd As Integer

    'initialize vars
    bDoSomething = False
    bDoAdd = False

    'we only respond to right mouse clicks, or "folder" node clicks
    If Button <> 2 And (tv_ComponentTree.SelectedItem.FullPath <> m_Node_Domains) Then
        Exit Sub
    End If

    'check for adding
    If lv_ContentsList.SelectedItem Is Nothing Then
        bDoAdd = True
    ElseIf lv_ContentsList.SelectedItem.Selected = False Then
        bDoAdd = True
    End If

    'if nothing selected then do an add menu
    If bDoAdd Then
        frmContext.Selected_Context = CM_NOTHING_SELECTED
        Select Case tv_ComponentTree.SelectedItem.FullPath
            Case m_Node_SystemParms
                iDomain = icIDS_SQLTB_SYSTEMPARMS
                PopupMenu frmContext.mnu_lv_AddMenu

            Case m_Node_Technician
                iDomain = icIDS_SQLTB_TECHNICIAN
                PopupMenu frmContext.mnu_lv_AddMenu

            Case m_Node_DomainLocations
                iDomain = icIDS_SQLTB_LOCATION
                PopupMenu frmContext.mnu_lv_AddMenu

            Case m_Node_DomainSkills
                iDomain = icIDS_SQLTB_SKILL
                PopupMenu frmContext.mnu_lv_AddMenu

            Case m_Node_DomainPriorities
                iDomain = icIDS_SQLTB_PRIORITY
                PopupMenu frmContext.mnu_lv_AddMenu
        End Select

        'exit out if nothing selected
        If frmContext.Selected_Context = CM_NOTHING_SELECTED Then
            Exit Sub
        End If

        'if add selected then adjust selection value
        Select Case tv_ComponentTree.SelectedItem.FullPath
            Case m_Node_SystemParms
                frmContext.Selected_Context = CM_NOTHING_SELECTED

            Case m_Node_Technician
                frmContext.Selected_Context = CM_TECHNICIAN_ADD

            Case m_Node_DomainLocations
                frmContext.Selected_Context = CM_DOMAIN_ADD

            Case m_Node_DomainSkills
                frmContext.Selected_Context = CM_DOMAIN_ADD

            Case m_Node_DomainPriorities
                frmContext.Selected_Context = CM_DOMAIN_ADD
        End Select

        bDoSomething = True
    End If

    'do something with the data
    If lv_ContentsList.SelectedItem.Selected Then
        frmContext.Selected_Context = CM_NOTHING_SELECTED
        Select Case tv_ComponentTree.SelectedItem.FullPath
            Case m_Node_SystemParms
                iDomain = icIDS_SQLTB_SYSTEMPARMS
                PopupMenu frmContext.mnu_lv_SysParm

            Case m_Node_Technician
                iDomain = icIDS_SQLTB_TECHNICIAN
                PopupMenu frmContext.mnu_lv_Technician

            Case m_Node_DomainLocations
                iDomain = icIDS_SQLTB_LOCATION
                PopupMenu frmContext.mnu_lv_Location

            Case m_Node_DomainSkills
                iDomain = icIDS_SQLTB_SKILL
                PopupMenu frmContext.mnu_lv_Skill

            Case m_Node_DomainPriorities
                iDomain = icIDS_SQLTB_PRIORITY
                PopupMenu frmContext.mnu_lv_Priority

            'VERY SPECIAL CASE - Click is on a "folder" icon
            Case m_Node_Domains
                'select requested domain in tree view
                Select Case lv_ContentsList.SelectedItem.Key
                Case m_Node_Location
                    Set tv_ComponentTree.SelectedItem = tv_ComponentTree.Nodes.Item(m_Node_Domains & m_Node_Location)

                Case m_Node_Priority
                    Set tv_ComponentTree.SelectedItem = tv_ComponentTree.Nodes.Item(m_Node_Domains & m_Node_Priority)

                Case m_Node_Skill
                    Set tv_ComponentTree.SelectedItem = tv_ComponentTree.Nodes.Item(m_Node_Domains & m_Node_Skill)

                Case m_Node_AuditTypes
                    Set tv_ComponentTree.SelectedItem = tv_ComponentTree.Nodes.Item(m_Node_Domains & m_Node_AuditTypes)

                Case m_Node_ReqDetType
                    Set tv_ComponentTree.SelectedItem = tv_ComponentTree.Nodes.Item(m_Node_Domains & m_Node_ReqDetType)

                Case m_Node_Status
                    Set tv_ComponentTree.SelectedItem = tv_ComponentTree.Nodes.Item(m_Node_Domains & m_Node_Status)

                Case m_Node_StdTextResp
                    Set tv_ComponentTree.SelectedItem = tv_ComponentTree.Nodes.Item(m_Node_Domains & m_Node_StdTextResp)

                Case m_Node_StdVocResp
                    Set tv_ComponentTree.SelectedItem = tv_ComponentTree.Nodes.Item(m_Node_Domains & m_Node_StdVocResp)

                Case m_Node_TechStatus
                    Set tv_ComponentTree.SelectedItem = tv_ComponentTree.Nodes.Item(m_Node_Domains & m_Node_TechStatus)

                End Select

                'simulate a mouse click on the tree view
                tv_ComponentTree_Click
                Exit Sub

        End Select

        If frmContext.Selected_Context = CM_NOTHING_SELECTED Then
            Exit Sub
        End If

        bDoSomething = True
    End If

    'check for selected item or adding new
    If bDoSomething Then
        Select Case frmContext.Selected_Context
            Case CM_SYSTEM_SYSPARM_PROPERTIES
                Set oSysParm = g_oSysAdmin.GetSysParmByKey(m_ItemClicked.Key)
                frmSysProp.SetParameters SP_PROPERTY, oSysParm
                frmSysProp.Show vbModal, Me
                Set oSysParm = Nothing

            Case CM_TECHNICIAN_REQUESTS
                Set frmTechReqs.Tech = g_oTechAdmin.GetTechByAlias(m_ItemClicked.Key)
                frmTechReqs.Show vbModal, Me

            Case CM_TECHNICIAN_ADD
                frmTechMaint.SetParameters TECH_ADD
                frmTechMaint.Show vbModal, Me
                Refresh_technicians True

            Case CM_TECHNICIAN_DELETE
                Set oTech = g_oTechAdmin.GetTechByAlias(m_ItemClicked.Key)
                frmTechMaint.SetParameters TECH_DELETE, oTech
                Set oTech = Nothing
                frmTechMaint.Show vbModal, Me
                Refresh_technicians True

            Case CM_TECHNICIAN_UPDATE
                Set oTech = g_oTechAdmin.GetTechByAlias(m_ItemClicked.Key)
                frmTechMaint.SetParameters TECH_UPDATE, oTech
                Set oTech = Nothing
                frmTechMaint.Show vbModal, Me

            Case CM_DOMAIN_ADD
                frmDomMaint.SetParameters DM_ADD, iDomain, "", ""
                frmDomMaint.Show vbModal, Me

            Case CM_DOMAIN_UPDATE
                frmDomMaint.SetParameters DM_UPDATE, iDomain, m_ItemClicked.Key, m_ItemClicked.Text
                frmDomMaint.Show vbModal, Me

        End Select
    End If

End Sub

Private Sub mnuViewAllRequests_Click()
    Set frmTechReqs.Tech = Nothing
    frmTechReqs.Show vbModal, Me
End Sub


Private Sub mnuViewBrowser_Click()
    
    Dim frmB As New frmBrowser
    frmB.StartingAddress = "http://www.microsoft.com"
    frmB.Show

End Sub



Private Sub mnuHelpAbout_Click()
    
    frmAbout.Show vbModal, Me

End Sub



Private Sub mnuViewOptions_Click()
    
    frmOptions.Show vbModal, Me

End Sub



Private Sub mnuViewStatusBar_Click()
    
    If mnuViewStatusBar.Checked Then
        sbStatusBar.Visible = False
        mnuViewStatusBar.Checked = False
    Else
        sbStatusBar.Visible = True
        mnuViewStatusBar.Checked = True
    End If
    SizeControls imgSplitter.Left

End Sub


Private Sub mnuViewToolbar_Click()
    
    If mnuViewToolbar.Checked Then
        tbToolBar.Visible = False
        mnuViewToolbar.Checked = False
    Else
        tbToolBar.Visible = True
        mnuViewToolbar.Checked = True
    End If
    SizeControls imgSplitter.Left

End Sub





Private Sub Form_Resize()
    
    On Error Resume Next
    If Me.Width < 3000 Then Me.Width = 3000
    SizeControls imgSplitter.Left

End Sub


Private Sub imgSplitter_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    
    With imgSplitter
        picSplitter.Move .Left, .Top, .Width \ 2, .Height - 20
    End With
    picSplitter.Visible = True
    mbMoving = True

End Sub


Private Sub imgSplitter_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Dim sglPos As Single
    

    If mbMoving Then
        sglPos = X + imgSplitter.Left
        If sglPos < sglSplitLimit Then
            picSplitter.Left = sglSplitLimit
        ElseIf sglPos > Me.Width - sglSplitLimit Then
            picSplitter.Left = Me.Width - sglSplitLimit
        Else
            picSplitter.Left = sglPos
        End If
    End If

End Sub


Private Sub imgSplitter_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    
    SizeControls picSplitter.Left
    picSplitter.Visible = False
    mbMoving = False

End Sub


Sub SizeControls(X As Single)
    On Error Resume Next
    

    'set the width
    If X < 1500 Then X = 1500
    If X > (Me.Width - 1500) Then X = Me.Width - 1500
    tv_ComponentTree.Width = X
    imgSplitter.Left = X
    lv_ContentsList.Left = X + 40
    lv_ContentsList.Width = Me.Width - (tv_ComponentTree.Width + 140)
    lblTitle(0).Width = tv_ComponentTree.Width
    lblTitle(1).Left = lv_ContentsList.Left + 20
    lblTitle(1).Width = lv_ContentsList.Width - 40


    'set the top
    If tbToolBar.Visible Then
        tv_ComponentTree.Top = tbToolBar.Height + picTitles.Height
    Else
        tv_ComponentTree.Top = picTitles.Height
    End If
    lv_ContentsList.Top = tv_ComponentTree.Top
    

    'set the height
    If sbStatusBar.Visible Then
        tv_ComponentTree.Height = Me.ScaleHeight - (picTitles.Top + picTitles.Height + sbStatusBar.Height)
    Else
        tv_ComponentTree.Height = Me.ScaleHeight - (picTitles.Top + picTitles.Height)
    End If
    

    lv_ContentsList.Height = tv_ComponentTree.Height
    imgSplitter.Top = tv_ComponentTree.Top
    imgSplitter.Height = tv_ComponentTree.Height

End Sub


Private Sub TreeView1_DragDrop(Source As Control, X As Single, Y As Single)
    
    If Source = imgSplitter Then
        SizeControls X
    End If

End Sub


Private Sub tbToolBar_ButtonClick(ByVal Button As ComctlLib.Button)
    Dim iListViewType As Integer
    
    iListViewType = lv_ContentsList.View
    
    Select Case Button.Key
        Case "Back"
            'To Do
            MsgBox "Back Code goes here!"
        
        Case "Forward"
            'To Do
            MsgBox "Forward Code goes here!"
        
        Case "Cut"
            'To Do
            MsgBox "Cut Code goes here!"
        
        Case "Copy"
            'To Do
            MsgBox "Copy Code goes here!"
        
        Case "Paste"
            'To Do
            MsgBox "Paste Code goes here!"
        
        Case "Delete"
            mnuFileDelete_Click
        
        Case "Properties"
            mnuFileProperties_Click
        
        Case "ViewLarge"
            mnuListViewMode_Click lvwIcon
        
        Case "ViewSmall"
            mnuListViewMode_Click lvwSmallIcon
        
        Case "ViewList"
            mnuListViewMode_Click lvwList
        
        Case "ViewDetails"
                mnuListViewMode_Click lvwReport
            If iListViewType = lvwReport Then
                SetColumnHeadings
                tv_ComponentTree_Click
            End If
        
        End Select

End Sub

Private Sub mnuHelpContents_Click()
    

    Dim nRet As Integer


    'if there is no helpfile for this project display a message to the user
    'you can set the HelpFile for your application in the
    'Project Properties dialog
    If Len(App.HelpFile) = 0 Then
        MsgBox "Unable to display Help Contents. There is no Help associated with this project.", vbInformation, Me.Caption
    Else
        On Error Resume Next
        nRet = OSWinHelp(Me.hwnd, App.HelpFile, 3, 0)
        If Err Then
            MsgBox Err.Description
        End If
    End If

End Sub


Private Sub mnuHelpSearch_Click()
    

    Dim nRet As Integer


    'if there is no helpfile for this project display a message to the user
    'you can set the HelpFile for your application in the
    'Project Properties dialog
    If Len(App.HelpFile) = 0 Then
        MsgBox "Unable to display Help Contents. There is no Help associated with this project.", vbInformation, Me.Caption
    Else
        On Error Resume Next
        nRet = OSWinHelp(Me.hwnd, App.HelpFile, 261, 0)
        If Err Then
            MsgBox Err.Description
        End If
    End If

End Sub



Private Sub mnuVAIByDate_Click()
    'To Do
'  lv_ContentsList.SortKey = DATE_COLUMN
End Sub


Private Sub mnuVAIByName_Click()
    'To Do
'  lv_ContentsList.SortKey = NAME_COLUMN
End Sub


Private Sub mnuVAIBySize_Click()
    'To Do
'  lv_ContentsList.SortKey = SIZE_COLUMN
End Sub


Private Sub mnuVAIByType_Click()
    'To Do
'  lv_ContentsList.SortKey = TYPE_COLUMN
End Sub


Private Sub mnuListViewMode_Click(Index As Integer)
    'uncheck the current type
    mnuListViewMode(lv_ContentsList.View).Checked = False
    'set the listview mode
    lv_ContentsList.View = Index
    'check the new type
    mnuListViewMode(Index).Checked = True
    'set the toolabr to the same new type
    tbToolBar.Buttons(Index + LISTVIEW_BUTTON).Value = tbrPressed
End Sub


Private Sub mnuViewLineUpIcons_Click()
    'To Do
    'lv_ContentsList.Arrange = lvwAutoLeft
End Sub


Private Sub mnuViewRefresh_Click()
    'To Do
    MsgBox "Refresh Code goes here!"
End Sub


Private Sub mnuFileOpen_Click()
    'To Do
    MsgBox "Open Code goes here!"
End Sub


Private Sub mnuFileFind_Click()
    'To Do
    MsgBox "Find Code goes here!"
End Sub


Private Sub mnuFileSendTo_Click()
    'To Do
    MsgBox "Send To Code goes here!"
End Sub


Private Sub mnuFileNew_Click()
    'To Do
    MsgBox "New File Code goes here!"
End Sub


Private Sub mnuFileDelete_Click()
    'To Do
    MsgBox "Delete Code goes here!"
End Sub


Private Sub mnuFileRename_Click()
    'To Do
    MsgBox "Rename Code goes here!"
End Sub


Private Sub mnuFileProperties_Click()
    'To Do
    MsgBox "Properties Code goes here!"
End Sub


Private Sub mnuFileMRU_Click(Index As Integer)
    'To Do
    MsgBox "MRU Code goes here!"
End Sub


Private Sub mnuFileClose_Click()
    'unload the form
    Unload Me
End Sub

Private Sub tv_ComponentTree_Click()
    Dim oItem As ListItem
    Dim sMisc As String
    Dim iCount As Integer
    
    On Error Resume Next

    lv_ContentsList.ListItems.Clear
    If lv_ContentsList.View = lvwReport Then
        SetColumnHeadings
    End If
    
    iCount = 0
    
    Select Case tv_ComponentTree.SelectedItem.FullPath
        Case m_Node_Domains
            If lv_ContentsList.View = lvwReport Then
                Set oItem = lv_ContentsList.ListItems.Add(Key:=m_Node_Location, Text:=m_Node_Location, Icon:=m_Node_DomainLocations, SmallIcon:=m_Node_DomainLocations)
                oItem.SubItems(1) = m_Node_Location
                Set oItem = lv_ContentsList.ListItems.Add(Key:=m_Node_Priority, Text:=m_Node_Priority, Icon:=m_Node_DomainPriorities, SmallIcon:=m_Node_DomainPriorities)
                oItem.SubItems(1) = m_Node_Priority
                Set oItem = lv_ContentsList.ListItems.Add(Key:=m_Node_Skill, Text:=m_Node_Skill, Icon:=m_Node_DomainSkills, SmallIcon:=m_Node_DomainSkills)
                oItem.SubItems(1) = m_Node_Skill
                Set oItem = lv_ContentsList.ListItems.Add(Key:=m_Node_AuditTypes, Text:=m_Node_AuditTypes, Icon:=m_Node_DomainAuditTypes, SmallIcon:=m_Node_DomainAuditTypes)
                oItem.SubItems(1) = m_Node_AuditTypes
                Set oItem = lv_ContentsList.ListItems.Add(Key:=m_Node_ReqDetType, Text:=m_Node_ReqDetType, Icon:=m_Node_DomainReqDetType, SmallIcon:=m_Node_DomainReqDetType)
                oItem.SubItems(1) = m_Node_ReqDetType
                Set oItem = lv_ContentsList.ListItems.Add(Key:=m_Node_Status, Text:=m_Node_Status, Icon:=m_Node_DomainStatus, SmallIcon:=m_Node_DomainStatus)
                oItem.SubItems(1) = m_Node_Status
                Set oItem = lv_ContentsList.ListItems.Add(Key:=m_Node_StdTextResp, Text:=m_Node_StdTextResp, Icon:=m_Node_DomainStdTextResp, SmallIcon:=m_Node_DomainStdTextResp)
                oItem.SubItems(1) = m_Node_StdTextResp
                Set oItem = lv_ContentsList.ListItems.Add(Key:=m_Node_StdVocResp, Text:=m_Node_StdVocResp, Icon:=m_Node_DomainStdVocResp, SmallIcon:=m_Node_DomainStdVocResp)
                oItem.SubItems(1) = m_Node_StdTextResp
                Set oItem = lv_ContentsList.ListItems.Add(Key:=m_Node_TechStatus, Text:=m_Node_TechStatus, Icon:=m_Node_DomainTechStatus, SmallIcon:=m_Node_DomainTechStatus)
                oItem.SubItems(1) = m_Node_TechStatus
            Else
                lv_ContentsList.ListItems.Add Key:=m_Node_Location, Text:=m_Node_Location, Icon:=m_Node_DomainLocations, SmallIcon:=m_Node_DomainLocations
                lv_ContentsList.ListItems.Add Key:=m_Node_Priority, Text:=m_Node_Priority, Icon:=m_Node_DomainPriorities, SmallIcon:=m_Node_DomainPriorities
                lv_ContentsList.ListItems.Add Key:=m_Node_Skill, Text:=m_Node_Skill, Icon:=m_Node_DomainSkills, SmallIcon:=m_Node_DomainSkills
                lv_ContentsList.ListItems.Add Key:=m_Node_AuditTypes, Text:=m_Node_AuditTypes, Icon:=m_Node_DomainAuditTypes, SmallIcon:=m_Node_DomainAuditTypes
                lv_ContentsList.ListItems.Add Key:=m_Node_ReqDetType, Text:=m_Node_ReqDetType, Icon:=m_Node_DomainReqDetType, SmallIcon:=m_Node_DomainReqDetType
                lv_ContentsList.ListItems.Add Key:=m_Node_Status, Text:=m_Node_Status, Icon:=m_Node_DomainStatus, SmallIcon:=m_Node_DomainStatus
                lv_ContentsList.ListItems.Add Key:=m_Node_StdTextResp, Text:=m_Node_StdTextResp, Icon:=m_Node_DomainStdTextResp, SmallIcon:=m_Node_DomainStdTextResp
                lv_ContentsList.ListItems.Add Key:=m_Node_StdVocResp, Text:=m_Node_StdVocResp, Icon:=m_Node_DomainStdVocResp, SmallIcon:=m_Node_DomainStdVocResp
                lv_ContentsList.ListItems.Add Key:=m_Node_TechStatus, Text:=m_Node_TechStatus, Icon:=m_Node_DomainTechStatus, SmallIcon:=m_Node_DomainTechStatus
            End If
            iCount = iCount + 1
        
        Case m_Node_SystemParms
            Dim oSysParm As hdadmin.CSysParm
            Dim cSysParms As Collection
            Set cSysParms = g_oSysAdmin.GetSysParms
            For Each oSysParm In cSysParms
                If lv_ContentsList.View = lvwReport Then
                    Set oItem = lv_ContentsList.ListItems.Add(Key:=oSysParm.Desc, Text:=oSysParm.Desc, Icon:=m_Node_SystemParms, SmallIcon:=m_Node_SystemParms)
                    oItem.SubItems(1) = oSysParm.Desc
                Else
                    lv_ContentsList.ListItems.Add Key:=oSysParm.Desc, Text:=oSysParm.Desc, Icon:=m_Node_SystemParms, SmallIcon:=m_Node_SystemParms
                End If
                iCount = iCount + 1
            Next oSysParm
            Set cSysParms = Nothing
        
        Case m_Node_Technician
            Dim oDomainTechnician As CTech
            Dim oLocation As CLocation
            Dim oSkill As CSkill
            Dim oDomainTechnicians As Collection
            Set oDomainTechnicians = g_oTechAdmin.GetTechnicians
            For Each oDomainTechnician In oDomainTechnicians
                If lv_ContentsList.View = lvwReport Then
                    sMisc = oDomainTechnician.Alias
                    Set oItem = lv_ContentsList.ListItems.Add( _
                                    Key:=sMisc, _
                                    Text:=sMisc, _
                                    Icon:=m_Node_Technician, _
                                    SmallIcon:=m_Node_Technician)
                    Set oLocation = g_oTechAdmin.GetLocations.Item( _
                                    g_oSysAdmin.FmtPKId(oDomainTechnician.LocationId))
                    oItem.SubItems(1) = oLocation.Desc
                    Set oSkill = g_oTechAdmin.GetSkills.Item( _
                                    g_oSysAdmin.FmtPKId(oDomainTechnician.SkillId))
                    oItem.SubItems(2) = oSkill.Desc
                Else
                    lv_ContentsList.ListItems.Add _
                            Key:=oDomainTechnician.Alias, _
                            Text:=oDomainTechnician.Alias, _
                            Icon:=m_Node_Technician, _
                            SmallIcon:=m_Node_Technician
                End If
                iCount = iCount + 1
            Next oDomainTechnician
            Set oDomainTechnicians = Nothing
        
        Case m_Node_DomainLocations
            Dim oDomainLocation As CLocation
            Dim oDomainLocations As Collection
            Set oDomainLocations = g_oTechAdmin.GetLocations
            For Each oDomainLocation In oDomainLocations
                If lv_ContentsList.View = lvwReport Then
                    Set oItem = lv_ContentsList.ListItems.Add(Key:=oDomainLocation.Code, Text:=oDomainLocation.Desc, Icon:=m_Node_Location, SmallIcon:=m_Node_Location)
                    oItem.SubItems(1) = oDomainLocation.Code
                Else
                    lv_ContentsList.ListItems.Add Key:=oDomainLocation.Code, Text:=oDomainLocation.Desc, Icon:=m_Node_Location, SmallIcon:=m_Node_Location
                End If
                iCount = iCount + 1
            Next oDomainLocation
            Set oDomainLocations = Nothing
        
        Case m_Node_DomainSkills
            Dim oDomainSkill As CSkill
            Dim oDomainSkills As Collection
            Set oDomainSkills = g_oTechAdmin.GetSkills
            For Each oDomainSkill In oDomainSkills
                If lv_ContentsList.View = lvwReport Then
                    Set oItem = lv_ContentsList.ListItems.Add(Key:=oDomainSkill.Code, Text:=oDomainSkill.Desc, Icon:=m_Node_Skill, SmallIcon:=m_Node_Skill)
                    oItem.SubItems(1) = oDomainSkill.Code
                Else
                    lv_ContentsList.ListItems.Add Key:=oDomainSkill.Code, Text:=oDomainSkill.Desc, Icon:=m_Node_Skill, SmallIcon:=m_Node_Skill
                End If
                iCount = iCount + 1
            Next oDomainSkill
            Set oDomainSkills = Nothing
        
        Case m_Node_DomainPriorities
            Dim oDomainPriority As CPriority
            Dim oDomainPriorities As Collection
            Set oDomainPriorities = g_oTechAdmin.GetPriorities
            For Each oDomainPriority In oDomainPriorities
                If lv_ContentsList.View = lvwReport Then
                    Set oItem = lv_ContentsList.ListItems.Add(Key:=oDomainPriority.Code, Text:=oDomainPriority.Desc, Icon:=m_Node_Priority, SmallIcon:=m_Node_Priority)
                    oItem.SubItems(1) = oDomainPriority.Code
                Else
                    lv_ContentsList.ListItems.Add Key:=oDomainPriority.Code, Text:=oDomainPriority.Desc, Icon:=m_Node_Priority, SmallIcon:=m_Node_Priority
                End If
                iCount = iCount + 1
            Next oDomainPriority
            Set oDomainPriorities = Nothing
    
    End Select
    
    sbStatusBar.Panels.Item(1) = CStr(iCount) & " items"
    
End Sub

Private Sub SetColumnHeadings()
    
    lv_ContentsList.ColumnHeaders.Clear
    Select Case tv_ComponentTree.SelectedItem.FullPath
    
        Case m_Node_SystemParms

        Case m_Node_Technician
            lv_ContentsList.ColumnHeaders.Add Key:=LoadResString(icIDS_KW_ALIAS), Text:=LoadResString(icIDS_KW_ALIAS)
            lv_ContentsList.ColumnHeaders.Add Key:=LoadResString(icIDS_KW_LOCATION), Text:=LoadResString(icIDS_KW_LOCATION)
            lv_ContentsList.ColumnHeaders.Add Key:=LoadResString(icIDS_KW_SKILL), Text:=LoadResString(icIDS_KW_SKILL)
            
        Case m_Node_DomainLocations, _
                m_Node_DomainSkills, _
                m_Node_DomainPriorities
            lv_ContentsList.ColumnHeaders.Add Key:=LoadResString(icIDS_KW_DESCRIPTION), Text:=LoadResString(icIDS_KW_DESCRIPTION)
            lv_ContentsList.ColumnHeaders.Add Key:=LoadResString(icIDS_KW_CODE), Text:=LoadResString(icIDS_KW_CODE)
    End Select
    
End Sub
