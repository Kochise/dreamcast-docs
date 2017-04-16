VERSION 4.00
Begin VB.Form frmMain 
   Caption         =   "Silk Screen"
   ClientHeight    =   5910
   ClientLeft      =   1140
   ClientTop       =   1380
   ClientWidth     =   8475
   Height          =   6285
   Left            =   1080
   LinkTopic       =   "Form1"
   ScaleHeight     =   5910
   ScaleWidth      =   8475
   Top             =   1065
   Width           =   8595
   Begin Threed.SSPanel pnlTop 
      Align           =   1  'Align Top
      Height          =   345
      Left            =   0
      TabIndex        =   4
      Top             =   0
      Width           =   8475
      _Version        =   65536
      _ExtentX        =   14949
      _ExtentY        =   609
      _StockProps     =   15
      BackColor       =   8421504
      BevelOuter      =   0
      Begin VB.CommandButton btGo 
         Caption         =   "Go!"
         Default         =   -1  'True
         Height          =   285
         Left            =   4200
         TabIndex        =   2
         Top             =   30
         Width           =   450
      End
      Begin VB.TextBox txtAddress 
         Height          =   285
         Left            =   30
         TabIndex        =   1
         Top             =   15
         Width           =   4140
      End
      Begin VB.Label lblStatus 
         BackStyle       =   0  'Transparent
         Caption         =   "Ready"
         Height          =   210
         Left            =   4680
         TabIndex        =   0
         Top             =   60
         Width           =   5010
      End
   End
   Begin Threed.SSPanel pnlLeft 
      Align           =   3  'Align Left
      Height          =   5565
      Left            =   0
      TabIndex        =   5
      Top             =   345
      Width           =   1245
      _Version        =   65536
      _ExtentX        =   2196
      _ExtentY        =   9816
      _StockProps     =   15
      BackColor       =   8421504
      BevelOuter      =   0
      Begin VB.Label lblMaxBytes 
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Height          =   195
         Left            =   90
         TabIndex        =   7
         Top             =   2775
         Width           =   45
      End
      Begin VB.Label lblBytes 
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Height          =   195
         Left            =   90
         TabIndex        =   6
         Top             =   2550
         Width           =   45
      End
      Begin VB.Image imgRefresh 
         Height          =   525
         Left            =   600
         Picture         =   "frmBrowse.frx":0000
         Top             =   660
         Width           =   585
      End
      Begin VB.Image imgStop 
         Height          =   525
         Left            =   0
         Picture         =   "frmBrowse.frx":033E
         Top             =   660
         Width           =   585
      End
      Begin VB.Image imgForward 
         Height          =   525
         Left            =   600
         Picture         =   "frmBrowse.frx":067C
         Top             =   15
         Width           =   585
      End
      Begin VB.Image imgBack 
         Height          =   525
         Left            =   0
         Picture         =   "frmBrowse.frx":09BA
         Top             =   15
         Width           =   585
      End
      Begin VB.Image imgPrint 
         Height          =   525
         Left            =   0
         Picture         =   "frmBrowse.frx":0CF8
         Top             =   1920
         Width           =   585
      End
      Begin VB.Image imgSearch 
         Height          =   525
         Left            =   600
         Picture         =   "frmBrowse.frx":1036
         Top             =   1305
         Width           =   585
      End
      Begin VB.Image imgHome 
         Height          =   525
         Left            =   0
         Picture         =   "frmBrowse.frx":1374
         Top             =   1305
         Width           =   585
      End
   End
   Begin SHDocVwCtl.WebBrowser webMain 
      Height          =   3825
      Left            =   1830
      TabIndex        =   3
      TabStop         =   0   'False
      Top             =   900
      Width           =   4995
      Object.Height          =   255
      Object.Width           =   333
      AutoSize        =   0
      ViewMode        =   1
      AutoSizePercentage=   0
      AutoArrange     =   -1  'True
      NoClientEdge    =   -1  'True
      AlignLeft       =   0   'False
      Location        =   ""
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Private Sub btGo_Click()
On Error Resume Next
'The txtAddress control is an edit box
'that contains a URL
webMain.Navigate txtAddress
End Sub

Private Sub Form_Load()
On Error Resume Next
'When we first start the application,
'lets show the users home page
webMain.GoHome
End Sub

Private Sub Form_Resize()
On Error Resume Next
webMain.Left = pnlLeft.Width + 20
webMain.Top = pnlTop.Height + 20
webMain.Width = frmMain.ScaleWidth - pnlLeft.Width - 40
webMain.Height = frmMain.ScaleHeight - pnlTop.Height - 40
txtAddress.Width = (frmMain.ScaleWidth - 60) / 2
btGo.Left = txtAddress.Left + txtAddress.Width + 30
lblStatus.Left = btGo.Left + btGo.Width + 40
End Sub

Private Sub imgBack_Click()
On Error Resume Next
'Navigate backwards through the user's history list
webMain.GoBack
End Sub

Private Sub imgForward_Click()
On Error Resume Next
'Navigate forwards through the user's history list
webMain.GoForward
End Sub

Private Sub imgHome_Click()
On Error Resume Next
'Navigate to the user's home page
webMain.GoHome
End Sub

Private Sub imgPrint_Click()
On Error Resume Next
'Use the default settings of the default printer
webMain.PrintOut
End Sub

Private Sub imgRefresh_Click()
On Error Resume Next
'Reload the currently displayed URL
webMain.Refresh
End Sub

Private Sub imgSearch_Click()
On Error Resume Next
'Navigate to the user's pre-defined search page
webMain.GoSearch
End Sub

Private Sub imgStop_Click()
On Error Resume Next
'Discontinue any current download attempts
webMain.Stop
End Sub

Private Sub webMain_OnBeginNavigate(ByVal URL As String, ByVal Flags As Long, ByVal TargetFrameName As String, PostData As Variant, ByVal Headers As String, ByVal Referrer As String, Cancel As Boolean)
On Error Resume Next
Debug.Print "OnBeginNavigate: " & URL
lblStatus = "Opening..." & URL
End Sub

Private Sub webMain_OnNavigate(ByVal URL As String, ByVal Flags As Long, ByVal TargetFrameName As String, PostData As Variant, ByVal Headers As String, ByVal Referrer As String)
On Error Resume Next
Debug.Print "OnNavigate: " & URL
lblStatus = "Ready"
txtAddress = URL
End Sub

Private Sub webMain_OnProgress(ByVal Progress As Long, ByVal ProgressMax As Long)
On Error Resume Next
Debug.Print "OnProgress: Progress=" & CStr(Progress) & " ProgressMax=" & CStr(ProgressMax)
If CBool(Progress) And CBool(ProgressMax) Then
    lblBytes = CStr(Progress) & " of"
    DoEvents
    lblMaxBytes = CStr(ProgressMax) & " bytes"
    DoEvents
Else
    lblBytes = ""
    lblBytes = ""
End If
End Sub

Private Sub webMain_OnStatusTextChange(ByVal bstrText As String)
Debug.Print "OnStatusTextChange: " & bstrText
lblStatus = bstrText
End Sub
