VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "comctl32.ocx"
Begin VB.Form frmReqDet 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Request Details"
   ClientHeight    =   4740
   ClientLeft      =   150
   ClientTop       =   435
   ClientWidth     =   10560
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4740
   ScaleWidth      =   10560
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin ComctlLib.Toolbar tbrReqDet 
      Align           =   1  'Align Top
      Height          =   420
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   10560
      _ExtentX        =   18627
      _ExtentY        =   741
      ButtonWidth     =   635
      ButtonHeight    =   582
      Appearance      =   1
      ImageList       =   "imlToolBar"
      _Version        =   327682
      BeginProperty Buttons {0713E452-850A-101B-AFC0-4210102A8DA7} 
         NumButtons      =   3
         BeginProperty Button1 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "stdtext"
            Object.ToolTipText     =   "Standard Text Response"
            Object.Tag             =   ""
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "stdvoice"
            Object.ToolTipText     =   "Standard Voice Response"
            Object.Tag             =   ""
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "textresp"
            Object.ToolTipText     =   "Text Response"
            Object.Tag             =   ""
            ImageIndex      =   3
         EndProperty
      EndProperty
      BorderStyle     =   1
   End
   Begin ComctlLib.ListView lvwDb 
      Height          =   3975
      Left            =   0
      TabIndex        =   2
      Top             =   480
      Width           =   10575
      _ExtentX        =   18653
      _ExtentY        =   7011
      View            =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   327682
      Icons           =   "imlIcons"
      SmallIcons      =   "imlSmallIcons"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
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
         Text            =   "Description"
         Object.Width           =   22719
      EndProperty
   End
   Begin ComctlLib.ProgressBar pgbReqLst 
      Height          =   255
      Left            =   30
      TabIndex        =   0
      Top             =   4480
      Width           =   10515
      _ExtentX        =   18547
      _ExtentY        =   450
      _Version        =   327682
      Appearance      =   1
   End
   Begin ComctlLib.ImageList imlToolBar 
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
         NumListImages   =   3
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "reqdet.frx":0000
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "reqdet.frx":031A
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "reqdet.frx":0634
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
            Picture         =   "reqdet.frx":094E
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
            Picture         =   "reqdet.frx":0C68
            Key             =   "recv"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "reqdet.frx":0F82
            Key             =   "sent"
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuSText 
         Caption         =   "Send St&andard Text"
      End
      Begin VB.Menu mnuSVoice 
         Caption         =   "Send Stan&dard Voice"
      End
      Begin VB.Menu mnuText 
         Caption         =   "Send &Text"
      End
      Begin VB.Menu mnuClose 
         Caption         =   "&Close"
      End
   End
End
Attribute VB_Name = "frmReqDet"
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
'   Synopsis :  This is the request dialog.
'=======================================================================

'Constants used in SetReqDetails
Const ID = "Id "
Const DTE = "DTE "
Const MSG = "MSG "
Const ROOT = "Root"

'constants used in toolbar button click
Const STDTEXT = "stdtext"
Const STDVOCE = "stdvoice"
Const txtResp = "textresp"
Const CLSFRM = "close"

'constants used to load the icon into treeview
Const TXTREQ = "TXTREQ"
Const VOCREQ = "VOCREQ"
Const TXTRSP = "TXTRSP"
Const VOCRSP = "VOCRSP"
Const STDTXT = "STDTXT"
Const STDVOC = "STDVOC"

Const RECV = "recv"
Const SENT = "sent"

Dim m_oReq          As hdclient.CRequest    'module level request object
Dim m_lTrackID      As Long                 'The requestid which is passed from the main form
Dim m_blnRightClick As Boolean

Private Sub Form_Load()
    On Error GoTo LoadErr
    
    'configure ListView control
    lvwDb.View = lvwReport
    
    'fill up the list
    RefreshList
    
    Dim sCode As String
    Dim iCount As Integer
    
    'configure the menu
    For iCount = 1 To tbrReqDet.Buttons.Count
        tbrReqDet.Buttons(iCount).Enabled = False
    Next iCount
    mnuText.Enabled = False
    mnuSText.Enabled = False
    mnuSVoice.Enabled = False
    sCode = GetRequestStatus
    Select Case sCode
        Case scSTATUS_INPROG, scSTATUS_CLAIMED
            For iCount = 1 To tbrReqDet.Buttons.Count
                tbrReqDet.Buttons(iCount).Enabled = True
            Next iCount
            mnuText.Enabled = True
            mnuSText.Enabled = True
            mnuSVoice.Enabled = True
    End Select
    
    Exit Sub
    
LoadErr:
    MsgBox Err.Number & " : " & Err.Description
    Err.Clear
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Set m_oReq = Nothing
    Set frmReqDet = Nothing
End Sub

Private Sub lvwDb_DblClick()
    'show expanded detail
    ExpandDetail
End Sub

Private Sub lvwDb_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Button = vbRightButton Then
        m_blnRightClick = True
    End If
End Sub

Private Sub tbrReqDet_ButtonClick(ByVal Button As ComctlLib.Button)
    Select Case Button.Key
        Case STDTEXT
            StdResp icText
        Case STDVOCE
            StdResp icVoice
        Case txtResp
            TextResp
        Case CLSFRM
            Unload Me
    End Select
End Sub

Private Sub mnuClose_Click()
    Unload Me
End Sub

Private Sub mnuSText_Click()
    'call procedure to show standard response form
    StdResp icText
End Sub

Private Sub mnuSVoice_Click()
    'show standard response form
    StdResp icText
End Sub

Private Sub mnuText_Click()
    'show text response form
    TextResp
End Sub

Public Property Let TrackID(ByVal lTrackId As Long)
    m_lTrackID = lTrackId
End Property

'=======================================================================
'Synopsis:              Opens expanded detail form.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub ExpandDetail()
    Dim oReqDet     As hdclient.CReqDetail
    
    For Each oReqDet In m_oReq.Details
        If "ID" & oReqDet.PKId = lvwDb.ListItems(lvwDb.SelectedItem.Index).Key Then
            'Set the text response form to display detail
            frmTextResp.Caption = ""
            frmTextResp.cmdSend.Visible = False
            frmTextResp.lblResp.Visible = False
            frmTextResp.txtResp.Text = oReqDet.DetailText
            frmTextResp.txtResp.Enabled = False
            
            'Show text response screen Modally
            frmTextResp.Show vbModal, Me
            Exit For
        End If
    Next
    Set oReqDet = Nothing

    'refresh the ReqDetails list
    RefreshList

End Sub

'=======================================================================
'Synopsis:              Fill the TreeView with request detail
'                       information.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub FillReqDetails()
    Dim oReqDet     As hdclient.CReqDetail
    Dim lCount      As Long
    Dim lRDCnt      As Long
    
    'clear all nodes in listview
    lvwDb.ListItems.Clear

    'set the min and max properties of the progress bar
    pgbReqLst.Visible = True
    pgbReqLst.Min = 0
    
    lRDCnt = m_oReq.Details.Count
    If lRDCnt <> 0 Then
        pgbReqLst.Max = lRDCnt
    End If
               
    'fill the list with the requests and details
    For Each oReqDet In m_oReq.Details
        SetReqDetails oReqDet
        lCount = lCount + 1         'Increase the counter
        pgbReqLst.Value = lCount    'increment the progress bar
    Next
    Set oReqDet = Nothing
    
    'reset the progress bar
    pgbReqLst.Value = pgbReqLst.Min
    pgbReqLst.Visible = False
    
End Sub

'=======================================================================
'Synopsis:              Checks the type of request detail object and
'                       adds the node to TreeView.
'Function input:        request detail object
'Function output:       None
'=======================================================================
Private Sub SetReqDetails(oReqDet As hdclient.CReqDetail)
    Dim oRDType     As hdclient.CReqDetType
    Dim oItem       As ListItem
    Dim sDetCode    As String
    Dim sIcon       As String
        
    
    'Get the data of request detail
     For Each oRDType In g_oAdmin.GetReqDetTypes
        If (oRDType.PKId = oReqDet.DetTypeId) Then
            sDetCode = oRDType.Code
            Exit For
        End If
    Next
       
    'Get the type of request detail - used to decide which picture to display
    Select Case sDetCode
        Case TXTREQ, VOCREQ
            sIcon = RECV
        Case Else
            sIcon = SENT
    End Select
    
    Dim sId As String
    sId = "ID" & oReqDet.PKId
    Set oItem = lvwDb.ListItems.Add(, sId, sDetCode, , sIcon)
    oItem.SubItems(1) = Format$(oReqDet.DetDate, "mm/dd hh:mm am/pm")
    oItem.SubItems(2) = oReqDet.DetailText
    
    Set oRDType = Nothing
    Set oItem = Nothing
    
End Sub

'=======================================================================
'Synopsis:              Establishes connection to the request object and
'                       fills the TreeView with request details.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub RefreshList()
    'instantiate the request object
    Set m_oReq = New CRequest
    
    'set the request id to the Request object
    m_oReq.TrackingNo = m_lTrackID
    
    'fill the list with request details
    FillReqDetails
End Sub

'=======================================================================
'Synopsis:              Opens standard entry dialog
'Function input:        Type of response - text or voice
'Function output:       None
'=======================================================================
Private Sub StdResp(ByVal iType As Integer)
    'set request property of form
    frmStdResp.TrackID = m_lTrackID
    
    'set the property to show Standard Text responses
    frmStdResp.ResponseType = iType
    
    'show the standard responses screen
    frmStdResp.Show vbModal, Me
    
    'refresh the list
    RefreshList
End Sub

'=======================================================================
'Synopsis:              Opens text entry dialog.
'Function input:        None
'Function output:       None
'=======================================================================
Private Sub TextResp()
    'set request property for form
    frmTextResp.TrackID = m_lTrackID
    
    'set the form for text response entry
    frmTextResp.Caption = "Send Text Response"
    frmTextResp.cmdSend.Visible = True
    frmTextResp.lblResp.Visible = True
    frmTextResp.txtResp.Enabled = True
    
    'show the text response screen
    frmTextResp.Show vbModal, Me
    
    'refresh the list
    RefreshList
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
        
    
    'create a new request
    Set oReq = New CRequest
    
    'set the request id to the Request object
    oReq.TrackingNo = m_lTrackID
    
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
    
    'delete the request object
    Set oReq = Nothing
    
    Exit Function

StatusErr:
    MsgBox Err.Number & " : " & Err.Description
    Err.Clear


End Function

