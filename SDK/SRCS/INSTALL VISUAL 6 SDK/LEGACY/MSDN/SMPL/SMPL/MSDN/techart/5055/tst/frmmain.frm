VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "Windows NT Services"
   ClientHeight    =   5475
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8025
   LinkTopic       =   "Form1"
   ScaleHeight     =   5475
   ScaleWidth      =   8025
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txt1 
      Height          =   3375
      HideSelection   =   0   'False
      Left            =   3480
      MaxLength       =   1025
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   7
      Text            =   "frmMain.frx":0000
      Top             =   1680
      Width           =   4335
   End
   Begin VB.CheckBox chkInactive 
      Caption         =   "Inactive"
      Height          =   255
      Index           =   3
      Left            =   3000
      TabIndex        =   6
      Top             =   720
      Value           =   1  'Checked
      Width           =   1695
   End
   Begin VB.CheckBox chkActive 
      Caption         =   "Active"
      Height          =   255
      Index           =   2
      Left            =   3000
      TabIndex        =   3
      Top             =   480
      Value           =   1  'Checked
      Width           =   1695
   End
   Begin VB.Frame Frame2 
      Caption         =   "Service Status"
      Height          =   855
      Left            =   2880
      TabIndex        =   2
      Top             =   240
      Width           =   2415
   End
   Begin VB.Frame Frame1 
      Caption         =   "Service Type"
      Height          =   855
      Left            =   240
      TabIndex        =   1
      Top             =   240
      Width           =   2415
      Begin VB.CheckBox chkDevice 
         Caption         =   "Driver"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   5
         Top             =   480
         Value           =   1  'Checked
         Width           =   1695
      End
      Begin VB.CheckBox chkWin32 
         Caption         =   "Win32"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   4
         Top             =   240
         Value           =   1  'Checked
         Width           =   1695
      End
   End
   Begin VB.ListBox lst1 
      Height          =   3375
      Left            =   240
      TabIndex        =   0
      Top             =   1680
      Width           =   2895
   End
   Begin VB.Label Label1 
      Caption         =   "Properties"
      Height          =   255
      Index           =   1
      Left            =   3480
      TabIndex        =   9
      Top             =   1320
      Width           =   1575
   End
   Begin VB.Label lbl1 
      Caption         =   "Services"
      Height          =   255
      Index           =   0
      Left            =   240
      TabIndex        =   8
      Top             =   1320
      Width           =   1575
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private oServiceAdmin As New CServiceAdmin
Private oService As New CService
Sub DisplayData()
    lst1.Clear
    txt1.Text = ""
    lbl1(0).Caption = "Services (" & CStr(oServiceAdmin.Services.Count) & ") found"
    For Each oService In oServiceAdmin.Services
        lst1.AddItem oService.DisplayName
    Next
    If lst1.ListCount > 0 Then
        lst1.ListIndex = 0
    End If
End Sub
Sub GetFilteredServices()
    oServiceAdmin.ServiceType = 0
    If chkWin32(0).Value = 1 Then
        oServiceAdmin.ServiceType = oServiceAdmin.ServiceType Or SERVICE_WIN32
    End If
    If chkDevice(1).Value = 1 Then
        oServiceAdmin.ServiceType = oServiceAdmin.ServiceType Or SERVICE_DRIVER
    End If
    oServiceAdmin.ServiceState = 0
    If chkActive(2).Value = 1 Then
        oServiceAdmin.ServiceState = oServiceAdmin.ServiceState Or SERVICE_ACTIVE
    End If
    If chkInactive(3).Value = 1 Then
        oServiceAdmin.ServiceState = oServiceAdmin.ServiceState Or SERVICE_INACTIVE
    End If
    
    oServiceAdmin.FillServices
End Sub

Private Sub chkActive_Click(Index As Integer)
    GetFilteredServices
    DisplayData
    lst1.SetFocus
End Sub

Private Sub chkDevice_Click(Index As Integer)
    GetFilteredServices
    DisplayData
    lst1.SetFocus
End Sub

Private Sub chkInactive_Click(Index As Integer)
    GetFilteredServices
    DisplayData
    lst1.SetFocus
End Sub

Private Sub chkWin32_Click(Index As Integer)
    GetFilteredServices
    DisplayData
    lst1.SetFocus
End Sub

Private Sub Form_Load()
    GetFilteredServices
    DisplayData
End Sub

Private Sub lst1_Click()
Dim sProperties As String
Dim sCRLF As String
sCRLF = Chr$(13) & Chr$(10)
Set oService = oServiceAdmin.Services(lst1.Text)
sProperties = "ServiceName" & Chr$(9) & RTrim(oService.ServiceName)
sProperties = sProperties & sCRLF & "DisplayName" & Chr$(9) & RTrim(oService.DisplayName)
sProperties = sProperties & sCRLF & "OwnProcess" & Chr$(9) & CStr(oService.OwnProcess)
sProperties = sProperties & sCRLF & "ShareProcess" & Chr$(9) & CStr(oService.ShareProcess)
sProperties = sProperties & sCRLF & "DeviceDriver" & Chr$(9) & CStr(oService.DeviceDriver)
sProperties = sProperties & sCRLF & "FileSystemDriver" & Chr$(9) & CStr(oService.FileSystemDriver)
sProperties = sProperties & sCRLF & "InteractsWithDesktop" & Chr$(9) & CStr(oService.InteractsWithDesktop)
sProperties = sProperties & sCRLF & "Stopped" & Chr$(9) & CStr(oService.Stopped)
sProperties = sProperties & sCRLF & "StartPending" & Chr$(9) & CStr(oService.StartPending)
sProperties = sProperties & sCRLF & "Running" & Chr$(9) & CStr(oService.Running)
sProperties = sProperties & sCRLF & "ContinuePending" & Chr$(9) & CStr(oService.ContinuePending)
sProperties = sProperties & sCRLF & "PausePending" & Chr$(9) & CStr(oService.PausePending)
sProperties = sProperties & sCRLF & "Paused" & Chr$(9) & CStr(oService.Paused)
sProperties = sProperties & sCRLF & "AcceptStop" & Chr$(9) & CStr(oService.AcceptStop)
sProperties = sProperties & sCRLF & "AcceptPauseContinue" & Chr$(9) & CStr(oService.AcceptPauseContinue)
sProperties = sProperties & sCRLF & "AcceptShutdown" & Chr$(9) & CStr(oService.AcceptShutdown)
sProperties = sProperties & sCRLF & "Win32ExitCode" & Chr$(9) & CStr(oService.Win32ExitCode)
sProperties = sProperties & sCRLF & "ServiceSpecificExitCode" & Chr$(9) & CStr(oService.ServiceSpecificExitCode)
sProperties = sProperties & sCRLF & "CheckPoint" & Chr$(9) & CStr(oService.CheckPoint)
sProperties = sProperties & sCRLF & "WaitHint" & Chr$(9) & CStr(oService.WaitHint)
txt1.Text = sProperties
End Sub
