VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "comctl32.ocx"
Begin VB.Form frmBrowser 
   ClientHeight    =   5160
   ClientLeft      =   3045
   ClientTop       =   3330
   ClientWidth     =   6570
   LinkTopic       =   "Form1"
   ScaleHeight     =   5160
   ScaleWidth      =   6570
   ShowInTaskbar   =   0   'False
   Begin ComctlLib.Toolbar tbToolBar 
      Align           =   1  'Align Top
      Height          =   420
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   6570
      _ExtentX        =   11589
      _ExtentY        =   741
      Appearance      =   1
      ImageList       =   "imlIcons"
      _Version        =   327682
      BeginProperty Buttons {0713E452-850A-101B-AFC0-4210102A8DA7} 
         NumButtons      =   6
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
            Key             =   "Stop"
            Object.ToolTipText     =   "Stop"
            Object.Tag             =   ""
            ImageIndex      =   3
         EndProperty
         BeginProperty Button4 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Refresh"
            Object.ToolTipText     =   "Refresh"
            Object.Tag             =   ""
            ImageIndex      =   4
         EndProperty
         BeginProperty Button5 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Home"
            Object.ToolTipText     =   "Home"
            Object.Tag             =   ""
            ImageIndex      =   5
         EndProperty
         BeginProperty Button6 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Search"
            Object.ToolTipText     =   "Search"
            Object.Tag             =   ""
            ImageIndex      =   6
         EndProperty
      EndProperty
   End
   Begin VB.PictureBox brwWebBrowser 
      Height          =   3720
      Left            =   120
      ScaleHeight     =   3660
      ScaleWidth      =   6090
      TabIndex        =   4
      Top             =   1200
      Width           =   6144
   End
   Begin VB.Timer timTimer 
      Enabled         =   0   'False
      Interval        =   5
      Left            =   6180
      Top             =   1500
   End
   Begin VB.PictureBox picAddress 
      Align           =   1  'Align Top
      BorderStyle     =   0  'None
      Height          =   675
      Left            =   0
      ScaleHeight     =   675
      ScaleWidth      =   6570
      TabIndex        =   3
      TabStop         =   0   'False
      Top             =   420
      Width           =   6564
      Begin VB.ComboBox cboAddress 
         Height          =   288
         Left            =   45
         TabIndex        =   1
         Text            =   "Combo1"
         Top             =   300
         Width           =   3795
      End
      Begin VB.Label lblAddress 
         Caption         =   "&Address:"
         Height          =   255
         Left            =   45
         TabIndex        =   0
         Tag             =   "&Address:"
         Top             =   60
         Width           =   3075
      End
   End
   Begin ComctlLib.ImageList imlIcons 
      Left            =   2796
      Top             =   2388
      _ExtentX        =   794
      _ExtentY        =   794
      BackColor       =   -2147483643
      ImageWidth      =   24
      ImageHeight     =   24
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   6
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmBrows.frx":0000
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmBrows.frx":005E
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmBrows.frx":00BC
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmBrows.frx":011A
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmBrows.frx":0178
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmBrows.frx":01D6
            Key             =   ""
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "frmBrowser"
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
Private Const OBJNAME = "frmBrowser"

Public StartingAddress As String
Dim mbDontNavigateNow As Boolean
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



Private Sub Form_Load()
    On Error Resume Next
    Me.Show
    tbToolBar.Refresh
    Form_Resize


    cboAddress.Move 50, lblAddress.Top + lblAddress.Height + 15


    If Len(StartingAddress) > 0 Then
        cboAddress.Text = StartingAddress
        cboAddress.AddItem cboAddress.Text
        'try to navigate to the starting address
        timTimer.Enabled = True
        'brwWebBrowser.StartingAddress
    End If


End Sub





Private Sub brwWebBrowser_DownloadComplete()
    On Error Resume Next
    'Me.Caption = brwWebBrowser.LocationName
End Sub


Private Sub brwWebBrowser_NavigateComplete(ByVal URL As String)
    Dim i As Integer
    Dim bFound As Boolean
    'Me.Caption = brwWebBrowser.LocationName
    'For i = 0 To cboAddress.ListCount - 1
    '    If cboAddress.List(i) = brwWebBrowser.LocationURL Then
    '        bFound = True
    '        Exit For
    '    End If
    'Next i
    'mbDontNavigateNow = True
    'If bFound Then
    '    cboAddress.RemoveItem i
    'End If
    'cboAddress.AddItem brwWebBrowser.LocationURL, 0
    'cboAddress.ListIndex = 0
    'mbDontNavigateNow = False
End Sub


Private Sub cboAddress_Click()
    'If mbDontNavigateNow Then Exit Sub
    'timTimer.Enabled = True
    'brwWebBrowser.Navigate cboAddress.Text
End Sub


Private Sub cboAddress_KeyPress(KeyAscii As Integer)
    On Error Resume Next
    If KeyAscii = vbKeyReturn Then
        cboAddress_Click
    End If
End Sub


Private Sub Form_Resize()
    cboAddress.Width = Me.ScaleWidth - 100
    brwWebBrowser.Width = Me.ScaleWidth - 100
    brwWebBrowser.Height = Me.ScaleHeight - (picAddress.Top + picAddress.Height) - 100
End Sub


Private Sub timTimer_Timer()
    'If brwWebBrowser.Busy = False Then
    '    timTimer.Enabled = False
    '    Me.Caption = brwWebBrowser.LocationName
    'Else
    '    Me.Caption = "Working..."
    'End If
End Sub


Private Sub tbToolBar_ButtonClick(ByVal Button As Button)
    On Error Resume Next
      

    timTimer.Enabled = True
      

    Select Case Button.Key
        Case "Back"
            'brwWebBrowser.GoBack
        Case "Forward"
            'brwWebBrowser.GoForward
        Case "Refresh"
            'brwWebBrowser.Refresh
        Case "Home"
            'brwWebBrowser.GoHome
        Case "Search"
            'brwWebBrowser.GoSearch
        Case "Stop"
            'timTimer.Enabled = False
            'brwWebBrowser.Stop
            'Me.Caption = brwWebBrowser.LocationName
    End Select


End Sub

