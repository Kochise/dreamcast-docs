VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Begin VB.Form frmUserReq 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "User - Request List"
   ClientHeight    =   5490
   ClientLeft      =   1755
   ClientTop       =   1755
   ClientWidth     =   10590
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5490
   ScaleWidth      =   10590
   StartUpPosition =   2  'CenterScreen
   Begin ComctlLib.Toolbar tbrUserReq 
      Align           =   1  'Align Top
      Height          =   420
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   10590
      _ExtentX        =   18680
      _ExtentY        =   741
      ButtonWidth     =   635
      ButtonHeight    =   582
      Appearance      =   1
      ImageList       =   "imlToolBar"
      _Version        =   327682
      BeginProperty Buttons {0713E452-850A-101B-AFC0-4210102A8DA7} 
         NumButtons      =   4
         BeginProperty Button1 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "new"
            Object.ToolTipText     =   "Create new request"
            Object.Tag             =   ""
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "open"
            Object.ToolTipText     =   "Open request details"
            Object.Tag             =   ""
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Key             =   "confirm"
            Object.ToolTipText     =   "Send resolution confirmation"
            Object.Tag             =   ""
            ImageIndex      =   3
         EndProperty
         BeginProperty Button4 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Object.Visible         =   0   'False
            Key             =   "exit"
            Object.ToolTipText     =   "Exit application"
            Object.Tag             =   ""
         EndProperty
      EndProperty
      BorderStyle     =   1
   End
   Begin VB.PictureBox picLegend 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   0
      Left            =   40
      ScaleHeight     =   255
      ScaleWidth      =   240
      TabIndex        =   6
      Top             =   5200
      Width           =   240
      Begin VB.Image imgLegend 
         Height          =   240
         Index           =   0
         Left            =   0
         Stretch         =   -1  'True
         Top             =   0
         Width           =   240
      End
   End
   Begin VB.PictureBox picLegend 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   1
      Left            =   1820
      ScaleHeight     =   255
      ScaleWidth      =   240
      TabIndex        =   5
      Top             =   5200
      Width           =   240
      Begin VB.Image imgLegend 
         Height          =   240
         Index           =   1
         Left            =   0
         Stretch         =   -1  'True
         Top             =   0
         Width           =   240
      End
   End
   Begin VB.PictureBox picLegend 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   2
      Left            =   3590
      ScaleHeight     =   255
      ScaleWidth      =   240
      TabIndex        =   4
      Top             =   5200
      Width           =   240
      Begin VB.Image imgLegend 
         Height          =   240
         Index           =   2
         Left            =   0
         Stretch         =   -1  'True
         Top             =   0
         Width           =   240
      End
   End
   Begin VB.PictureBox picLegend 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   3
      Left            =   5350
      ScaleHeight     =   255
      ScaleWidth      =   240
      TabIndex        =   3
      Top             =   5200
      Width           =   240
      Begin VB.Image imgLegend 
         Height          =   240
         Index           =   3
         Left            =   0
         Stretch         =   -1  'True
         Top             =   0
         Width           =   240
      End
   End
   Begin ComctlLib.ProgressBar pgbReqLst 
      Height          =   255
      Left            =   0
      TabIndex        =   1
      Top             =   4920
      Width           =   10575
      _ExtentX        =   18653
      _ExtentY        =   450
      _Version        =   327682
      Appearance      =   1
   End
   Begin ComctlLib.ListView lvwDB 
      Height          =   4455
      Left            =   0
      TabIndex        =   0
      Top             =   480
      Width           =   10545
      _ExtentX        =   18600
      _ExtentY        =   7858
      View            =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   327682
      Icons           =   "imlIcons"
      SmallIcons      =   "imlSmallIcons"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      Appearance      =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      NumItems        =   6
      BeginProperty ColumnHeader(1) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Tracking #"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(2) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   1
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Description"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(3) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   2
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Status"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(4) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   3
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Request Date"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(5) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   4
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Category"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(6) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   5
         Key             =   ""
         Object.Tag             =   ""
         Text            =   ""
         Object.Width           =   2540
      EndProperty
   End
   Begin ComctlLib.StatusBar sbLegend 
      Align           =   2  'Align Bottom
      Height          =   360
      Left            =   0
      TabIndex        =   7
      Top             =   5130
      Width           =   10590
      _ExtentX        =   18680
      _ExtentY        =   635
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   8
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   529
            MinWidth        =   529
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Text            =   "Unclaimed"
            TextSave        =   "Unclaimed"
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel3 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   529
            MinWidth        =   529
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel4 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Text            =   "Claimed"
            TextSave        =   "Claimed"
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel5 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   529
            MinWidth        =   529
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel6 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Text            =   "In Progress"
            TextSave        =   "In Progress"
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel7 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   529
            MinWidth        =   529
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel8 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Text            =   "Pending"
            TextSave        =   "Pending"
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
   End
   Begin ComctlLib.ImageList imlToolBar 
      Left            =   3000
      Top             =   1320
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   3
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "userreq.frx":0000
            Key             =   "new"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "userreq.frx":0112
            Key             =   "open"
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "userreq.frx":0224
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin ComctlLib.ImageList imlIcons 
      Left            =   645
      Top             =   5160
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   32
      ImageHeight     =   32
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   2
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "userreq.frx":053E
            Key             =   "closed"
            Object.Tag             =   "closed"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "userreq.frx":0858
            Key             =   "open"
            Object.Tag             =   "open"
         EndProperty
      EndProperty
   End
   Begin ComctlLib.ImageList imlSmallIcons 
      Left            =   45
      Top             =   5175
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   6
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "userreq.frx":0B72
            Key             =   "UNASSGN"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "userreq.frx":0E8C
            Key             =   "UNCLAIM"
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "userreq.frx":11A6
            Key             =   "CLAIMED"
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "userreq.frx":14C0
            Key             =   "INPROG"
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "userreq.frx":17DA
            Key             =   "PENDING"
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "userreq.frx":1AF4
            Key             =   "RESOLVD"
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "File"
      Begin VB.Menu mnuNew 
         Caption         =   "&New Request"
      End
      Begin VB.Menu mnuOpen 
         Caption         =   "&Open Request"
      End
      Begin VB.Menu mnuSendRConf 
         Caption         =   "&Request Resolved "
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuExit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "Help"
      Begin VB.Menu mnuAbout 
         Caption         =   "About User Client"
      End
   End
End
Attribute VB_Name = "frmUserReq"
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
'   Synopsis :  This is the Visual Basic Client for a Technician to log
'               in. Uses the HelpDesk object model.
'
'=======================================================================
Const ZERO = 0     'This constant is used in GetLoggedInUser() function

'used in Admin Init method to notify that a User has logged in
Const USER_LOGGEDIN = 1

'used in toolbar button click event
Const NEWREQ = "new"
Const OPNREQ = "open"
Const SNDCNF = "confirm"
Const EXTAPP = "exit"

'Constants used in getting Icons for status to be displayed in listview
Const UNASSGN = "UNASSGN"
Const ASGNCLM = "UNCLAIM"
Const CLAIMED = "CLAIMED"
Const INPROGS = "INPROG"
Const RESCSNT = "PENDING"
Const RESCRCV = "RESOLVD"

Dim m_oUser                 As HDClient.CUser   'Module level Technician EmailAlias
Private mNode               As Node             'Module-level variable for Nodes
Private m_blnRightClick     As Boolean

'This function declaration is used in GetLoggedInUser()
Private Declare Function GetUserName Lib "advapi32.dll" Alias "GetUserNameA" _
(ByVal lpBuffer As String, nSize As Long) As Long

Private Sub Form_Load()
    On Error GoTo FLdErr
    Dim bTemp As Boolean
    
    'get login details of the logged in User
    If Not GetLoggedInUser(g_sEAlias) Then
        Unload Me
        Exit Sub
    End If
    
    frmSplash.Show
    DoEvents
    
    'create an Admin object
    Set g_oAdmin = New HDClient.CAdmin
    Set m_oUser = New HDClient.CUser
    
    'assign to UserAlias module level variable
    m_oUser.Alias = g_sEAlias
    
    'Initialize the Admin object so that it fills the requests and
    'request details for the logged in technician
    If Not g_oAdmin.Init(g_sEAlias, USER_LOGGEDIN) Then
        MsgBox LoadResString(icIDS_ERR_USERINIT)
        Unload frmSplash
        Unload Me
        Exit Sub
    End If
    
    Unload frmSplash
    
    'insert localized tool tips
    tbrUserReq.Buttons(NEWREQ).ToolTipText = LoadResString(icIDS_TT_NEWREQUEST)
    tbrUserReq.Buttons(OPNREQ).ToolTipText = LoadResString(icIDS_TT_OPENREQUEST)
    tbrUserReq.Buttons(SNDCNF).ToolTipText = LoadResString(icIDS_TT_SENDCONF)
    tbrUserReq.Buttons(EXTAPP).ToolTipText = LoadResString(icIDS_TT_EXITAPP)

    'configure the ListView control
    lvwDb.View = lvwReport
    
    'call function to fill up requests in ListView
    FillListView
    
    'enable the Open menu if there are items in the list
    If (lvwDb.ListItems.Count = ZERO) Then
        mnuOpen.Enabled = False
        tbrUserReq.Buttons(2).Enabled = False
    Else
        mnuOpen.Enabled = True
        tbrUserReq.Buttons(2).Enabled = True
    End If
    
    imgLegend(0).Picture = imlSmallIcons.ListImages(2).Picture
    imgLegend(1).Picture = imlSmallIcons.ListImages(3).Picture
    imgLegend(2).Picture = imlSmallIcons.ListImages(4).Picture
    imgLegend(3).Picture = imlSmallIcons.ListImages(5).Picture
    
    Exit Sub

FLdErr:
    MsgBox Err.Number & " : " & Err.Description
    Err.Clear
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'clean up
    Set g_oAdmin = Nothing
    g_sEAlias = vbNullString
    
    Set frmUserReq = Nothing
End Sub

Private Sub lvwDB_Click()
    If (lvwDb.SelectedItem.Text = vbNullString) Then
        mnuSendRConf.Enabled = False
        tbrUserReq.Buttons(3).Enabled = False
    Else
        mnuSendRConf.Enabled = True
        tbrUserReq.Buttons(3).Enabled = True
    End If
End Sub

Private Sub lvwDB_ColumnClick(ByVal ColumnHeader As ColumnHeader)
    lvwDb.SortKey = ColumnHeader.Index - 1
    
    'sort the list
    lvwDb.Sorted = True
End Sub

Private Sub lvwDb_DblClick()
    'show request details form
    OpenReq
End Sub

Private Sub lvwDB_ItemClick(ByVal Item As ComctlLib.ListItem)
    If m_blnRightClick Then
        m_blnRightClick = False
        mnuExit.Visible = False
        Me.PopupMenu mnuFile, , , , mnuOpen
        mnuExit.Visible = True
    End If
End Sub

Private Sub lvwDB_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    If Button = vbRightButton Then
        m_blnRightClick = True
    End If
End Sub

Private Sub tbrUserReq_ButtonClick(ByVal Button As ComctlLib.Button)
    Select Case Button.Key
        Case NEWREQ
            CreateNewReq
        Case OPNREQ
            OpenReq
        Case SNDCNF
            SendConf
        Case EXTAPP
            Unload Me
    End Select
End Sub

Private Sub mnuSendRConf_Click()
    'send confirmation
    SendConf
End Sub

Private Sub mnuAbout_Click()
    'show the about form
    frmAbout.Show vbModal, Me
End Sub

Private Sub mnuExit_Click()
    'exit the application
    Unload Me
End Sub

Private Sub mnuNew_Click()
    'show the create request form
    CreateNewReq
End Sub

Private Sub mnuOpen_Click()
    'show the request details form
    OpenReq
End Sub

'=======================================================================
'Synopsis:              Fill the listbox with request information.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillListView()
    Dim oReq        As HDClient.CRequest
    Dim cSkills     As Collection
    Dim cStatus     As Collection
    Dim oItem       As ListItem
    Dim sTemp       As String
    Dim sLIcon      As String
    Dim sSIcon      As String
    Dim lCount      As Long
    Dim lCount1     As Long
    
    'clear the old request items
    lvwDb.ListItems.Clear
    
    'get the number of requests
    lCount1 = m_oUser.Requests.Count
    
    'Set the min and max properties of the progress bar
    If lCount1 > ZERO Then
        pgbReqLst.Visible = True
        pgbReqLst.Min = ZERO
        pgbReqLst.Max = lCount1
    Else
        Exit Sub
    End If
    
    Set cSkills = g_oAdmin.GetSkills()
    Set cStatus = g_oAdmin.GetReqStatus()
    
    'fill the list view with the requests and its details
    For Each oReq In m_oUser.Requests
        GetIconForStatus cStatus, oReq.StatusId, sTemp, sLIcon, sSIcon
        Set oItem = lvwDb.ListItems.Add(, , oReq.TrackingNo, , sSIcon)
        oItem.SubItems(1) = oReq.Desc
        oItem.SubItems(2) = sTemp
        oItem.SubItems(3) = oReq.ReqDate
        GetSkillDesc cSkills, oReq.SkillId, sTemp
        oItem.SubItems(4) = sTemp
        lCount = lCount + 1
        pgbReqLst.Value = lCount
    Next
    
    'ReSet the progress bar
    pgbReqLst.Value = pgbReqLst.Min
    pgbReqLst.Visible = False
    
    ' disable menu item Send Request Confirmation when no item selected
    mnuSendRConf.Enabled = False
    tbrUserReq.Buttons(3).Enabled = False
    
    'clean up
    Set oItem = Nothing
    Set oReq = Nothing
    Set cSkills = Nothing
    Set cStatus = Nothing
End Sub

'=======================================================================
'Synopsis:              This function gets the present logged in user
'                       into NT.
'Function input:        None
'Function output:       Returns current user.
'                       Returns True if successful.
'=======================================================================
Private Function GetLoggedInUser(sUserName As String) As Boolean
    On Error GoTo UserErr
    
    GetLoggedInUser = False
    
    'dimension variables
    Dim sBuff   As String * 25
    Dim lRet    As Long
    
    'get the user name minus any trailing spaces found in the name.
    lRet = GetUserName(sBuff, 25)
    
    'remove the NULL characters that get appended
    sUserName = Left(sBuff, InStr(sBuff, Chr(ZERO)) - 1)
    
    'fail if the UserName is a null string
    If Trim$(sUserName) = vbNullString Then
        Exit Function
    End If
    
    GetLoggedInUser = True
    Exit Function

UserErr:
    MsgBox Err.Number & " : " & Err.Description
    Err.Clear
End Function

'=======================================================================
'Synopsis:              This function gets a skills description
'                       from the HDClient.
'Function input:        Skills collection from the HDClient Admin
'                       member and skill from the HDClient request
'                       member.
'Function output:       Returns the description for the given skill.
'=======================================================================
Private Sub GetSkillDesc(ByVal oSkills As Collection, ByVal iSkillId As Integer, sDesc As String)
    Dim oSkill As HDClient.CSkill
    
    
    'get the description
    For Each oSkill In oSkills
        If (oSkill.PKId = iSkillId) Then
            sDesc = oSkill.Desc
            Exit For
        End If
    Next
    
    'clean up
    Set oSkill = Nothing
End Sub

'=======================================================================
'Synopsis:              Clear and fill the list.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub ListRefresh()
    'initialize the user
    Set m_oUser = Nothing
    
    'get a new user object
    Set m_oUser = New HDClient.CUser
    m_oUser.Alias = g_sEAlias
    
    'fill the listview
    FillListView
End Sub

'=======================================================================
'Synopsis:              This function gets the status of the request.
'Function input:        Request.
'Function output:       Returns the status of this request.
'=======================================================================
Private Sub GetIconForStatus(ByVal cStatus As Collection, ByVal StatusId As Integer, sStatusDesc As String, sLIcon As String, sSIcon As String)
    Dim oStatus As HDClient.CReqStatus
    Dim sCode   As String
    
    For Each oStatus In cStatus
        If (oStatus.PKId = StatusId) Then
            sStatusDesc = oStatus.Desc
            sCode = oStatus.Code
            Exit For
        End If
    Next
    sSIcon = sCode
    
    'clean up
    Set oStatus = Nothing
End Sub

'=======================================================================
'Synopsis:              This subroutine opens the request insert dialog
'                       and subsequently refills the request list.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub CreateNewReq()
    'called from menu and toolbar button
    'show the Request insert screen
    frmInsReq.Show vbModal, Me
    
    'fill the list again to show the added request
    ListRefresh
End Sub

'=======================================================================
'Synopsis:              This subroutine opens the request detail list
'                       dialog.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub OpenReq()
    
    'set the request tracking no
    frmUserReqDet.TrackingID = CLng(lvwDb.SelectedItem.Text)
    
    'show User request details screen
    frmUserReqDet.Show vbModal, Me
    
    'refresh the requests
    ListRefresh
End Sub

'=======================================================================
'Synopsis:              This subroutine sends resolution confirmation.
'Function input:
'Function output:
'=======================================================================
Private Sub SendConf()
    Dim oReq As HDClient.CRequest
    
    'if there is no selected item in the listview then exit
    If lvwDb.SelectedItem.Text = vbNullString Then
        Exit Sub
    End If
    
    'get a request object
    Set oReq = New HDClient.CRequest
    
    'set the attributes for request object
    oReq.TrackingNo = CLng(lvwDb.SelectedItem.Text)
    
    'send the confirmation
    If Not g_oAdmin.ConfirmResolution(oReq) Then
        MsgBox LoadResString(icIDS_ERR_CONFNOTSENT)
    End If
    
    'clean up
    Set oReq = Nothing
    mnuSendRConf.Enabled = False
    tbrUserReq.Buttons(3).Enabled = False
End Sub
