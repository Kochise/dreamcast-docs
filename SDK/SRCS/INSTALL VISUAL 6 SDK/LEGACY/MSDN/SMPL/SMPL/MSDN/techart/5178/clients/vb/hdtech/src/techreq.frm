VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Begin VB.Form frmTechReq 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Technician Request List"
   ClientHeight    =   5265
   ClientLeft      =   150
   ClientTop       =   435
   ClientWidth     =   10545
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5265
   ScaleWidth      =   10545
   StartUpPosition =   2  'CenterScreen
   Begin ComctlLib.Toolbar tbrTReq 
      Align           =   1  'Align Top
      Height          =   420
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   10545
      _ExtentX        =   18600
      _ExtentY        =   741
      ButtonWidth     =   635
      ButtonHeight    =   582
      Appearance      =   1
      ImageList       =   "imlToolbar"
      _Version        =   327682
      BeginProperty Buttons {0713E452-850A-101B-AFC0-4210102A8DA7} 
         NumButtons      =   5
         BeginProperty Button1 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Key             =   "open"
            Object.ToolTipText     =   "Show details of request"
            Object.Tag             =   ""
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Key             =   "claim"
            Object.ToolTipText     =   "Claim request"
            Object.Tag             =   ""
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Key             =   "unclaim"
            Object.ToolTipText     =   "Release/ Unclaim request"
            Object.Tag             =   ""
            ImageIndex      =   3
         EndProperty
         BeginProperty Button4 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Key             =   "resolve"
            Object.ToolTipText     =   "Resolve request"
            Object.Tag             =   ""
            ImageIndex      =   5
         EndProperty
         BeginProperty Button5 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Key             =   "refresh"
            Object.ToolTipText     =   "Refresh request list"
            Object.Tag             =   ""
            ImageIndex      =   6
         EndProperty
      EndProperty
      BorderStyle     =   1
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
      TabIndex        =   7
      Top             =   4980
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
   Begin VB.PictureBox picLegend 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   2
      Left            =   3590
      ScaleHeight     =   255
      ScaleWidth      =   240
      TabIndex        =   6
      Top             =   4980
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
      Index           =   1
      Left            =   1820
      ScaleHeight     =   255
      ScaleWidth      =   240
      TabIndex        =   5
      Top             =   4980
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
      Index           =   0
      Left            =   40
      ScaleHeight     =   255
      ScaleWidth      =   240
      TabIndex        =   4
      Top             =   4980
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
   Begin ComctlLib.StatusBar sbLegend 
      Align           =   2  'Align Bottom
      Height          =   360
      Left            =   0
      TabIndex        =   3
      Top             =   4905
      Width           =   10545
      _ExtentX        =   18600
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
   Begin ComctlLib.ProgressBar pgbReqLst 
      Height          =   255
      Left            =   0
      TabIndex        =   1
      Top             =   4680
      Width           =   10575
      _ExtentX        =   18653
      _ExtentY        =   450
      _Version        =   327682
      Appearance      =   1
   End
   Begin ComctlLib.ListView lvwDB 
      Height          =   4215
      Left            =   0
      TabIndex        =   0
      Top             =   480
      Width           =   10545
      _ExtentX        =   18600
      _ExtentY        =   7435
      View            =   1
      LabelEdit       =   1
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
         Text            =   "Priority"
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
         Text            =   "Location"
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
   Begin ComctlLib.ImageList imlToolbar 
      Left            =   5040
      Top             =   2160
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
            Picture         =   "techreq.frx":0000
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "techreq.frx":0112
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "techreq.frx":042C
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "techreq.frx":0746
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "techreq.frx":0A60
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "techreq.frx":0D7A
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
      ImageWidth      =   13
      ImageHeight     =   13
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   1
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "techreq.frx":1094
            Key             =   "Data"
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
            Picture         =   "techreq.frx":13AE
            Key             =   "UNASSGN"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "techreq.frx":16C8
            Key             =   "UNCLAIM"
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "techreq.frx":19E2
            Key             =   "CLAIMED"
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "techreq.frx":1CFC
            Key             =   "INPROG"
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "techreq.frx":2016
            Key             =   "PENDING"
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "techreq.frx":2330
            Key             =   "RESOLVD"
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "File"
      Begin VB.Menu mnuReqDet 
         Caption         =   "&Open Request Details"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuClaim 
         Caption         =   "&Claim"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuUnclaim 
         Caption         =   "&Unclaim"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuResolve 
         Caption         =   "&Submit for Confirmation"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuRefresh 
         Caption         =   "Re&fresh"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuExit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuAbout 
         Caption         =   "About Technician Client"
      End
   End
End
Attribute VB_Name = "frmTechReq"
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

Const CHAR_ZERO = 0     'This constant is used in GetLoggedInUser() function
Const ID = "Id "
Const KeyVal = 3

'Constants used in toolbar button click event
Const OPNDET = "open"
Const CLAIM = "claim"
Const UNCLM = "unclaim"
Const RESOL = "resolve"
Const REFSH = "refresh"
Const EXITAPP = "exit"

Private m_blnRightClick As Boolean

Private Declare Function GetUserName Lib "advapi32.dll" Alias "GetUserNameA" _
(ByVal lpbuffer As String, nSize As Long) As Long

Private Sub Form_Load()
    On Error GoTo FLdErr
    Dim bTemp As Boolean
    
        
    'configure ListView control
    lvwDb.View = lvwReport
    
    'fill the listview with requests
    FillListView
    
    'enable the Open menu if there are items
    If (lvwDb.ListItems.Count = 0) Then
        mnuRefresh.Enabled = False
        tbrTReq.Buttons(REFSH).Enabled = False
    Else
        mnuRefresh.Enabled = True
        tbrTReq.Buttons(REFSH).Enabled = True
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
    Set frmTechReq = Nothing
    End
End Sub

Private Sub lvwDB_ColumnClick(ByVal ColumnHeader As ColumnHeader)
    lvwDb.SortKey = ColumnHeader.Index - 1
    
    'Set Sorted to True to sort the list.
    lvwDb.Sorted = True
End Sub


Private Sub lvwDb_DblClick()
    'show the request detail list screen
    ReqDetails
End Sub

Private Sub lvwDB_ItemClick(ByVal Item As ComctlLib.ListItem)
    Dim sCode As String
    
    Call disableMenu
    tbrTReq.Buttons(1).Enabled = True
    mnuReqDet.Enabled = True
    sCode = GetRequestStatus
    Select Case sCode
        Case scSTATUS_UNCLAIM
            tbrTReq.Buttons(CLAIM).Enabled = True
            mnuClaim.Enabled = True
        Case scSTATUS_CLAIMED
            tbrTReq.Buttons(UNCLM).Enabled = True
            mnuUnclaim.Enabled = True
        Case scSTATUS_INPROG
            tbrTReq.Buttons(RESOL).Enabled = True
            mnuResolve.Enabled = True
        Case scSTATUS_PENDING
    End Select
    If m_blnRightClick Then
        m_blnRightClick = False
        mnuExit.Visible = False
        Me.PopupMenu mnuFile, , , , mnuReqDet
        mnuExit.Visible = True
    End If
End Sub

Private Sub lvwDb_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Button = vbRightButton Then
        m_blnRightClick = True
    End If
End Sub

Private Sub mnuAbout_Click()
    'show the About form
    frmAbout.Show vbModal, Me
End Sub

Private Sub mnuClaim_Click()
    'claim a request
    ClaimReq
End Sub

Private Sub mnuExit_Click()
    Unload Me
End Sub

Private Sub mnuRefresh_Click()
    'Refresh the request list
    RefreshReq
End Sub

Private Sub mnuReqDet_Click()
    'show the request detail list screen
    ReqDetails
End Sub

Private Sub mnuResolve_Click()
    'resolve a request
    ResolveReq
End Sub

Private Sub mnuUnclaim_Click()
    'unclaim a request
    UnclaimReq
End Sub

Private Sub tbrTReq_ButtonClick(ByVal Button As ComctlLib.Button)
    Select Case Button.Key
        Case OPNDET
            ReqDetails
        Case CLAIM
            ClaimReq
        Case UNCLM
            UnclaimReq
        Case RESOL
            ResolveReq
        Case REFSH
            RefreshReq
        Case EXITAPP
            Unload Me
    End Select
End Sub

'=======================================================================
'Synopsis:              Fill the listbox with request information.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillListView()
    Dim oReq            As hdclient.CRequest
    Dim oLocs           As Collection
    Dim oPriorities     As Collection
    Dim oItem           As ListItem
    Dim sTemp           As String
    Dim sSIcon          As String
    Dim sLIcon          As String
    Dim sReqKey         As String
    Dim lCount          As Long
    Dim lReqCnt         As Long
    
    
    'clear the old request items
    lvwDb.ListItems.Clear
    
    'get the count of requests collection
    lReqCnt = g_oTech.Requests.Count
    
    'set the min and max properties of the progress bar
    If lReqCnt <> 0 Then
        pgbReqLst.Visible = True
        pgbReqLst.Min = 0
        pgbReqLst.Max = lReqCnt
    End If
    
    'get locations collection
    Set oLocs = g_oAdmin.GetLocations()
    
    'get priorities collection
    Set oPriorities = g_oAdmin.GetPriorities()
    
    'fill the list view with the requests and its details
    For Each oReq In g_oTech.Requests
        sReqKey = ID & oReq.PKId
        GetIconForStatus oReq, sSIcon, sLIcon
        Set oItem = lvwDb.ListItems.Add(, sReqKey, CStr(oReq.TrackingNo), , sSIcon)
        oItem.SubItems(1) = oReq.Desc
        GetPriorityDesc oPriorities, oReq.PriorityId, sTemp
        oItem.SubItems(2) = sTemp
        oItem.SubItems(3) = oReq.ReqDate
        GetLocationDesc oLocs, oReq.LocId, sTemp
        oItem.SubItems(4) = sTemp
        lCount = lCount + 1
        pgbReqLst.Value = lCount
    Next
    
    'reset the progress bar
    pgbReqLst.Value = pgbReqLst.Min
    pgbReqLst.Visible = False
    
    'clean up
    Set oReq = Nothing
    Set oItem = Nothing
    Set oLocs = Nothing
    Set oPriorities = Nothing
    
    Call disableMenu
    
End Sub

Public Property Let TechAlias(ByVal sNewValue As String)
    g_oTech.Alias = Trim$(sNewValue)
End Property

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
    
    'Dimension variables
    Dim sBuff   As String * 25
    Dim lRet    As Long
    
    'Get the user name minus any trailing spaces found in the name.
    lRet = GetUserName(sBuff, 25)
    
    'Remove the NULL characters that get appended
    sUserName = Left(sBuff, InStr(sBuff, Chr(CHAR_ZERO)) - 1)
    
    'Fail the function if the UserName returned is a null string
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
'Synopsis:              This function gets a priority description
'                       from the HDClient.
'Function input:        Priorities collection from the HDClient Admin
'                       member and priority from the HDClient request
'                       member.
'Function output:       Returns the description for the given priority.
'=======================================================================
Private Sub GetPriorityDesc(ByVal oPriorities As Collection, ByVal iPriority As Integer, sDesc As String)
    Dim oPriority As hdclient.CPriority
    
    For Each oPriority In oPriorities
        If (oPriority.PKId = iPriority) Then
            sDesc = oPriority.Desc
            Exit For
        End If
    Next
    
    Set oPriority = Nothing
End Sub

'=======================================================================
'Synopsis:              This function gets a location description
'                       from the HDClient.
'Function input:        Priorities collection from the HDClient Admin
'                       member and priority from the HDClient request
'                       member.
'Function output:       Returns the description for the given priority.
'=======================================================================
Private Sub GetLocationDesc(ByVal oLocs As Collection, ByVal iLoc As Integer, sDesc As String)
    Dim oLoc As hdclient.CLocation
    
    For Each oLoc In oLocs
        If (oLoc.PKId = iLoc) Then
            sDesc = oLoc.Desc
            Exit For
        End If
    Next
    
    Set oLoc = Nothing
End Sub

'=======================================================================
'Synopsis:              This subroutine claims the selected request.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub ClaimReq()
    On Error GoTo ClaimErr
    
    Dim oReq    As hdclient.CRequest
    Dim lReqId  As Long
        
    
    'create a new request object
    Set oReq = New CRequest
    
    'get the selected request from the Listview
    If (lvwDb.ListItems.Count <> 0) Then
        lReqId = CLng(Mid$(lvwDb.SelectedItem.Key, KeyVal))
    Else
        Exit Sub
    End If
    
    Set oReq.Tech = g_oTech
    'set the Id for the request Object
    oReq.PKId = lReqId
    
    'call the method on the object to claim the request
    If Not g_oAdmin.ClaimRequest(oReq) Then
        MsgBox ERR_CLAIMFAILED
    End If
    
    'clean up
    Set oReq = Nothing
    
    'refresh the data and fill the list
    RefreshReq
    
    Exit Sub

ClaimErr:
    MsgBox Err.Number & " : " & Err.Description
    Err.Clear

End Sub

'=======================================================================
'Synopsis:              This subroutine opens the request detail list
'                       dialog.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub ReqDetails()
    'set the property for the Request Details form
    If (lvwDb.ListItems.Count <> 0) Then
        frmReqDet.TrackID = CLng(lvwDb.SelectedItem.Text)
    Else
        Exit Sub
    End If
    
    'show the request details form
    frmReqDet.Show vbModal, Me
    
    'refresh the request list
    RefreshReq
End Sub

'=======================================================================
'Synopsis:              Clear and fill the list.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub RefreshReq()
    'force a refresh of the technician object
    g_oTech.Term
    
    'fill the list view
    FillListView
End Sub

'=======================================================================
'Synopsis:              This subroutine resolves processing the request.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub ResolveReq()
    On Error GoTo ResolveErr
    
    Dim oReq    As hdclient.CRequest
    Dim lReqId  As Long
    
    Set oReq = New CRequest
    
    'get the selected request from the Listview
    If (lvwDb.ListItems.Count <> 0) Then
        lReqId = CLng(Mid$(lvwDb.SelectedItem.Key, KeyVal))
    Else
        Exit Sub
    End If
    
    'set ReqId to the Request object
    oReq.PKId = lReqId
    
    'submit the request for resolution confirmation
    If Not g_oAdmin.SubmitRequest(oReq) Then
        MsgBox ERR_RESOLVEFAILED
    End If
    
    'clean up
    Set oReq = Nothing
    
    'refresh the data
    RefreshReq
    
    Exit Sub

ResolveErr:
    MsgBox Err.Number & " : " & Err.Description
    Err.Clear
End Sub

'=======================================================================
'Synopsis:              This subroutine unclaims the selected request.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub UnclaimReq()
    On Error GoTo UnClaimErr
    
    Dim oReq    As hdclient.CRequest
    Dim lReqId  As Long
    
    Set oReq = New CRequest
        
    'get the selected request from the Listview
    If (lvwDb.ListItems.Count <> 0) Then
        lReqId = CLng(Mid$(lvwDb.SelectedItem.Key, KeyVal))
    Else
        Exit Sub
    End If
    
    'set ReqId to the Request object
    oReq.PKId = lReqId
    
    'unclaim the request
    If Not g_oAdmin.UnclaimRequest(oReq) Then
        MsgBox ERR_UNCLAIMFAILED
    End If
    
    'clean up
    Set oReq = Nothing
    
    'refresh the data and fill the list
    RefreshReq
    
    Exit Sub
UnClaimErr:
    MsgBox Err.Number & " : " & Err.Description
    Err.Clear
End Sub

'=======================================================================
'Synopsis:              This function gets the status of the request.
'Function input:        Request.
'Function output:       Returns the status of this request.
'=======================================================================
Private Sub GetIconForStatus(ByVal oReq As hdclient.CRequest, sSIcon As String, sLIcon As String)
    Dim cReqStat    As Collection
    Dim oStat       As hdclient.CReqStatus
    Dim sStCode     As String
    Dim lStatus     As Long
    
    'get the status of the request object passed
    lStatus = oReq.StatusId
    
    'get the request status collection
    Set cReqStat = g_oAdmin.GetReqStatus()
    
    For Each oStat In cReqStat
        If (oStat.PKId = lStatus) Then
            sStCode = oStat.Code
            Exit For
        End If
    Next
    
    sSIcon = sStCode
    sLIcon = sStCode
    
    'clean up
    Set oStat = Nothing
    Set cReqStat = Nothing
End Sub

'=======================================================================
'Synopsis:              This subroutine returns the status from the
'                       selected request.
'Function input:        None
'Function output:       None
'=======================================================================
Private Function GetRequestStatus() As String
    On Error GoTo StatusErr
    
    Dim cReqStat    As Collection
    Dim oReq        As hdclient.CRequest
    Dim oStat       As hdclient.CReqStatus
    Dim lReqId      As Long
    Dim sStCode     As String
    Dim lStatus     As Long
        
    
    'create a new request object
    Set oReq = New CRequest
    
    'get the selected request from the Listview
    If (lvwDb.ListItems.Count <> 0) Then
        lReqId = CLng(Mid$(lvwDb.SelectedItem.Key, KeyVal))
    Else
        Exit Function
    End If
    
    Set oReq.Tech = g_oTech
    'set the Id for the request Object
    oReq.PKId = lReqId
    
    lStatus = oReq.StatusId
    
    'get the request status collection
    Set cReqStat = g_oAdmin.GetReqStatus()
    
    For Each oStat In cReqStat
        If (oStat.PKId = lStatus) Then
            sStCode = oStat.Code
            Exit For
        End If
    Next
    'get the status of the request object passed
    GetRequestStatus = sStCode
    
    'clean up
    Set oReq = Nothing
    
    Exit Function

StatusErr:
    MsgBox Err.Number & " : " & Err.Description
    Err.Clear


End Function

'=======================================================================
'Synopsis:              Reset the menu.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub disableMenu()
    Dim iCount As Integer
    
    For iCount = 2 To tbrTReq.Buttons.Count - 1
        tbrTReq.Buttons(iCount).Enabled = False
    Next iCount
    mnuClaim.Enabled = False
    mnuUnclaim.Enabled = False
    mnuResolve.Enabled = False
End Sub
