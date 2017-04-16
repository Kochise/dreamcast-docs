VERSION 5.00
Begin VB.Form NewDatabase 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "New Database"
   ClientHeight    =   2100
   ClientLeft      =   1320
   ClientTop       =   2295
   ClientWidth     =   7065
   Icon            =   "Add Database.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2100
   ScaleWidth      =   7065
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Cancel"
      Height          =   375
      Left            =   5760
      TabIndex        =   11
      Top             =   720
      Width           =   1215
   End
   Begin VB.CommandButton cmdCreateNow 
      Caption         =   "C&reate Now"
      Default         =   -1  'True
      Height          =   375
      Left            =   5760
      TabIndex        =   10
      Top             =   240
      Width           =   1215
   End
   Begin VB.Frame Frame1 
      Height          =   1815
      Left            =   120
      TabIndex        =   12
      Top             =   120
      Width           =   5535
      Begin VB.TextBox txtLogSize 
         Height          =   285
         Left            =   4800
         TabIndex        =   9
         Text            =   "2"
         Top             =   1350
         Width           =   615
      End
      Begin VB.ComboBox cmbLogDevice 
         Height          =   315
         Left            =   1200
         Style           =   2  'Dropdown List
         TabIndex        =   7
         Top             =   1320
         Width           =   2655
      End
      Begin VB.TextBox txtDeviceSize 
         Height          =   285
         Left            =   4800
         TabIndex        =   5
         Text            =   "2"
         Top             =   840
         Width           =   615
      End
      Begin VB.ComboBox cmbDataDevice 
         Height          =   315
         Left            =   1200
         Style           =   2  'Dropdown List
         TabIndex        =   3
         Top             =   810
         Width           =   2655
      End
      Begin VB.TextBox txtName 
         Height          =   315
         Left            =   1200
         TabIndex        =   1
         Top             =   300
         Width           =   2655
      End
      Begin VB.Label Label5 
         Caption         =   "Siz&e  (MB):"
         Height          =   255
         Left            =   3960
         TabIndex        =   8
         Top             =   1380
         Width           =   855
      End
      Begin VB.Label Label4 
         Caption         =   "&Log Device:"
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   1380
         Width           =   1095
      End
      Begin VB.Label Label3 
         Caption         =   "Siz&e  (MB):"
         Height          =   255
         Left            =   3960
         TabIndex        =   4
         Top             =   870
         Width           =   855
      End
      Begin VB.Label Label2 
         Caption         =   "&Data Device:"
         Height          =   255
         Left            =   120
         TabIndex        =   2
         Top             =   870
         Width           =   1095
      End
      Begin VB.Label Label1 
         Caption         =   "&Name:"
         Height          =   255
         Left            =   120
         TabIndex        =   0
         Top             =   360
         Width           =   615
      End
   End
End
Attribute VB_Name = "NewDatabase"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public SQLServer As String, LoginID As String, Password As String

Public HostControl
Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdCreateNow_Click()
    DatabaseName = txtName.Text
    DeviceName = cmbDataDevice.Text
    DeviceSize = txtDeviceSize.Text
    LogDeviceName = cmbLogDevice.Text
    LogDeviceSize = txtLogSize.Text
    Unload Me
End Sub

Private Sub Form_Load()
    On Error GoTo errorhandler
    Dim objSQLServer As SQLOLE.SQLServer
    Dim device As SQLOLE.device
    
    Set objSQLServer = CreateObject("SQLOLE.SQLserver")
    
    'Connect to SQL Server
    objSQLServer.Connect ServerName:=SQLServer, login:=LoginID, Password:=Password
    
    For Each device In objSQLServer.Devices
        If device.Type = SQLOLEDevice_Database Then
            cmbDataDevice.AddItem device.Name
            cmbLogDevice.AddItem device.Name
        End If
    Next
    
    Me.Caption = "New Database - " & SQLServer
    
    If cmbDataDevice.ListCount > 0 Then
        cmbDataDevice.ListIndex = 0
        cmbLogDevice.ListIndex = 0
    End If
    
    objSQLServer.DisConnect
    
exitsub:
    Exit Sub
    
errorhandler:
    MsgBox Error
    Resume exitsub

End Sub

Private Sub txtDeviceSize_GotFocus()
    txtDeviceSize.SelStart = 0
    txtDeviceSize.SelLength = Len(txtDeviceSize.Text)
End Sub

Private Sub txtDeviceSize_KeyPress(KeyAscii As Integer)
    'Filter out all non numeric characters
    If KeyAscii > 57 Then KeyAscii = 0
    If KeyAscii < 48 Then KeyAscii = 0
End Sub


Private Sub txtLogSize_GotFocus()
    txtLogSize.SelStart = 0
    txtLogSize.SelLength = Len(txtLogSize.Text)
End Sub

Private Sub txtLogSize_KeyPress(KeyAscii As Integer)
    'Filter out all non numeric characters
    If KeyAscii > 57 Then KeyAscii = 0
    If KeyAscii < 48 Then KeyAscii = 0
End Sub

Private Sub txtName_GotFocus()
    txtName.SelStart = 0
    txtName.SelLength = Len(txtName.Text)

End Sub


