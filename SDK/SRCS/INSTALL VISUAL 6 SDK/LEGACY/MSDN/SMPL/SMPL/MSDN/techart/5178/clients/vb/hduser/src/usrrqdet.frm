VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Begin VB.Form frmUserReqDet 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Request Details"
   ClientHeight    =   5190
   ClientLeft      =   1755
   ClientTop       =   1755
   ClientWidth     =   10590
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5190
   ScaleWidth      =   10590
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin ComctlLib.Toolbar tbrUReqDet 
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
         NumButtons      =   1
         BeginProperty Button1 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "text"
            Object.ToolTipText     =   "Send text request"
            Object.Tag             =   ""
            ImageIndex      =   1
         EndProperty
      EndProperty
      BorderStyle     =   1
   End
   Begin ComctlLib.ListView lvwDb 
      Height          =   4455
      Left            =   0
      TabIndex        =   3
      Top             =   480
      Width           =   10575
      _ExtentX        =   18653
      _ExtentY        =   7858
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   327682
      Icons           =   "imlIcons"
      SmallIcons      =   "imlSmallIcons"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   3
      BeginProperty ColumnHeader(1) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Type"
         Object.Width           =   1764
      EndProperty
      BeginProperty ColumnHeader(2) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   1
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Date"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(3) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   2
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "description"
         Object.Width           =   22719
      EndProperty
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
   Begin ComctlLib.TabStrip TabStrip1 
      Height          =   30
      Left            =   1305
      TabIndex        =   0
      Top             =   5145
      Width           =   30
      _ExtentX        =   53
      _ExtentY        =   53
      _Version        =   327682
      BeginProperty Tabs {0713E432-850A-101B-AFC0-4210102A8DA7} 
         NumTabs         =   1
         BeginProperty Tab1 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Key             =   ""
            Object.Tag             =   ""
            ImageVarType    =   2
         EndProperty
      EndProperty
   End
   Begin ComctlLib.ImageList imlToolBar 
      Left            =   5040
      Top             =   2280
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   1
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "usrrqdet.frx":0000
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin ComctlLib.ImageList imlIcons 
      Left            =   645
      Top             =   4800
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
            Picture         =   "usrrqdet.frx":031A
            Key             =   "Data"
         EndProperty
      EndProperty
   End
   Begin ComctlLib.ImageList imlSmallIcons 
      Left            =   45
      Top             =   4935
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   2
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "usrrqdet.frx":0634
            Key             =   "RECV"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "usrrqdet.frx":094E
            Key             =   "SENT"
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuText 
         Caption         =   "Send &Text"
      End
      Begin VB.Menu mnuClose 
         Caption         =   "&Close"
      End
   End
End
Attribute VB_Name = "frmUserReqDet"
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
'   Synopsis :  This form displays the conversation that has happened with
'               a particular request.
'=======================================================================
Const ZERO = 0
Const DASH = " - " '@@
Const ROOT = "Root"
Const ID = "Id "
Const DTE = "DTE "
Const MSG = "MSG "
Const TRACKSTR = "Tracking # "

'constants used in getting Icons for treeview
Const RECV = "RECV"
Const SENT = "SENT"

'constants used to load the icon into treeview
Const txtReq = "TXTREQ"
Const VOCREQ = "VOCREQ"
Const TXTRSP = "TXTRSP"
Const VOCRSP = "VOCRSP"
Const STDTXT = "STDTXT"
Const STDVOC = "STDVOC"

'constants used in toolbar button click event
Const CLSFRM = "close"
Const SNDTXT = "text"

Dim m_oReq          As HDClient.CRequest    'module level request object
Dim m_lTrackID      As Long                 'The tracking number of request
Dim m_blnRightClick As Boolean

Public Property Let TrackingID(ByVal lTrackId As Long)
    m_lTrackID = lTrackId
End Property

Private Sub Form_Load()
    On Error GoTo LoadErr
    
    'configure ListView control
    lvwDb.View = lvwReport

    'fill up the list
    ListRefresh
Exit Sub

LoadErr:
    MsgBox Err.Number & " : " & Err.Description
    Err.Clear
End Sub

'=======================================================================
'Synopsis:              Fill the listbox with request detail information.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillReqDetails()
    Dim oReqDet     As HDClient.CReqDetail
    Dim lCount      As Long
    Dim lRDCnt      As Long
    
    'clear all nodes in listview
    lvwDb.ListItems.Clear
    
    'fill the tree view with the requests and its details
    For Each oReqDet In m_oReq.Details
        SetReqDetails oReqDet
        lCount = lCount + 1         'Increase the counter
        pgbReqLst.Value = lCount    'increment the progress bar
    Next
    
    'clean up
    Set oReqDet = Nothing
    
    'reSet the progress bar
    pgbReqLst.Value = pgbReqLst.Min
    pgbReqLst.Visible = False
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    
    'clean up
    Set m_oReq = Nothing
    Set frmUserReqDet = Nothing
End Sub

Private Sub SetReqDetails(oReqDet As HDClient.CReqDetail)
    Dim oRDType     As HDClient.CReqDetType
    Dim oItem       As ListItem
    Dim sDetCode    As String
    Dim sIcon       As String
            
    'get the data of request detail
     For Each oRDType In g_oAdmin.GetReqDetTypes
        If (oRDType.PKId = oReqDet.DetTypeId) Then
            sDetCode = oRDType.Code
            Exit For
        End If
    Next
       
    'get the type of request detail - used to decide which picture to display
    Select Case sDetCode
        Case txtReq, VOCREQ
            sIcon = RECV
        Case Else
            sIcon = SENT
    End Select
    
    Dim sId As String
    sId = "ID" & oReqDet.PKId
    Set oItem = lvwDb.ListItems.Add(, sId, sDetCode, , sIcon)
    oItem.SubItems(1) = Format$(oReqDet.DetDate, "mm/dd hh:mm am/pm")
    oItem.SubItems(2) = oReqDet.DetailText
    
    'clean up
    Set oRDType = Nothing
    Set oItem = Nothing
    
End Sub

Private Sub lvwDb_DblClick()
    'show expanded detail
    ExpandDetail
End Sub

Private Sub mnuClose_Click()
    Unload Me
End Sub

Private Sub mnuText_Click()
    'send text request
    SendText
End Sub

Private Sub ListRefresh()
    Set m_oReq = Nothing
    
    'instantiate the request object
    Set m_oReq = New HDClient.CRequest
    
    'Set the request id to the Request object
    m_oReq.TrackingNo = m_lTrackID
    
    'fill the treeview with request details
    FillReqDetails
End Sub

Private Sub tbrUReqDet_ButtonClick(ByVal Button As ComctlLib.Button)
    Select Case Button.Key
        Case SNDTXT
            SendText
        Case CLSFRM
            Unload Me
    End Select
End Sub

Private Sub SendText()
    'set the Tracking ID as a property for the form
    frmTextReq.TrackID = m_lTrackID
    
    'set the form for text response entry
    frmTextReq.Caption = "Send Text Response"
    frmTextReq.cmdSend.Visible = True
    frmTextReq.lblResp.Visible = True
    frmTextReq.txtReq.Enabled = True
    
    'show the text request screen
    frmTextReq.Show vbModal, Me
    
    ListRefresh
End Sub

Private Sub tvwDB_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    If Button = vbRightButton Then
        m_blnRightClick = True
    End If
End Sub

Private Sub tvwDB_NodeClick(ByVal Node As ComctlLib.Node)
    If m_blnRightClick Then
        m_blnRightClick = False
        Me.PopupMenu mnuFile, , , , mnuText
    End If
End Sub

'=======================================================================
'Synopsis:              Opens expanded detail form.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub ExpandDetail()
    Dim oReqDet     As HDClient.CReqDetail
    
    For Each oReqDet In m_oReq.Details
        If "ID" & oReqDet.PKId = lvwDb.ListItems(lvwDb.SelectedItem.Index).Key Then
            'set the text response form to display detail information
            frmTextReq.Caption = ""
            frmTextReq.cmdSend.Visible = False
            frmTextReq.lblResp.Visible = False
            frmTextReq.txtReq.Text = oReqDet.DetailText
            frmTextReq.txtReq.Enabled = False
            
            'show text response screen Modally
            frmTextReq.Show vbModal, Me
            Exit For
        End If
    Next
    
    'clean up
    Set oReqDet = Nothing

End Sub

