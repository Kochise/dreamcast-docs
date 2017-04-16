VERSION 5.00
Begin VB.Form NewDevice 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "New Device"
   ClientHeight    =   2100
   ClientLeft      =   1320
   ClientTop       =   2295
   ClientWidth     =   7065
   Icon            =   "Add Device.frx":0000
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
      TabIndex        =   7
      Top             =   720
      Width           =   1215
   End
   Begin VB.CommandButton cmdCreateNow 
      Caption         =   "C&reate Now"
      Default         =   -1  'True
      Height          =   375
      Left            =   5760
      TabIndex        =   6
      Top             =   240
      Width           =   1215
   End
   Begin VB.Frame Frame1 
      Height          =   1815
      Left            =   120
      TabIndex        =   8
      Top             =   120
      Width           =   5535
      Begin VB.TextBox txtLocation 
         Height          =   315
         Left            =   1200
         TabIndex        =   3
         Text            =   "C:\"
         Top             =   810
         Width           =   2175
      End
      Begin VB.TextBox txtDeviceSize 
         Height          =   285
         Left            =   4800
         TabIndex        =   5
         Text            =   "2"
         Top             =   840
         Width           =   615
      End
      Begin VB.TextBox txtName 
         Height          =   315
         Left            =   1200
         TabIndex        =   1
         Top             =   300
         Width           =   2655
      End
      Begin VB.Label Label4 
         Caption         =   ".DAT"
         Height          =   255
         Left            =   3390
         TabIndex        =   9
         Top             =   870
         Width           =   495
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
         Caption         =   "&Location:"
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
Attribute VB_Name = "NewDevice"
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
    DeviceName = txtName.Text
    DeviceSize = txtDeviceSize.Text
    DeviceLocation = txtLocation.Text & ".DAT"
    Unload Me
End Sub

Private Sub Form_Load()
    Me.Caption = "New Device - " & SQLServer
End Sub

Private Sub Frame1_DragDrop(Source As Control, X As Single, Y As Single)

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



Private Sub txtLogSize_KeyPress(KeyAscii As Integer)
    'Filter out all non numeric characters
    If KeyAscii > 57 Then KeyAscii = 0
    If KeyAscii < 48 Then KeyAscii = 0
End Sub

Private Sub txtLocation_Change()
    txtLocation.SelStart = 0
    txtLocation.SelLength = Len(txtLocation.Text)

End Sub

Private Sub txtName_Change()
    txtLocation.Text = "C:\" & txtName.Text
End Sub

Private Sub txtName_GotFocus()
    txtName.SelStart = 0
    txtName.SelLength = Len(txtName.Text)

End Sub


