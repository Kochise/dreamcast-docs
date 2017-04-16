VERSION 5.00
Begin VB.Form frmLogin 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "HDExplorer Login"
   ClientHeight    =   1620
   ClientLeft      =   36
   ClientTop       =   312
   ClientWidth     =   3780
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1620
   ScaleWidth      =   3780
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Tag             =   "Login"
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   360
      Left            =   2100
      TabIndex        =   5
      Tag             =   "Cancel"
      Top             =   1020
      Width           =   1140
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   360
      Left            =   495
      TabIndex        =   4
      Tag             =   "OK"
      Top             =   1020
      Width           =   1140
   End
   Begin VB.TextBox txtPassword 
      Height          =   288
      IMEMode         =   3  'DISABLE
      Left            =   1305
      PasswordChar    =   "*"
      TabIndex        =   1
      Top             =   525
      Width           =   2325
   End
   Begin VB.TextBox txtUserName 
      Height          =   288
      Left            =   1305
      TabIndex        =   3
      Top             =   135
      Width           =   2325
   End
   Begin VB.Label lblLabels 
      Caption         =   "&Password:"
      Height          =   248
      Index           =   1
      Left            =   105
      TabIndex        =   0
      Tag             =   "&Password:"
      Top             =   540
      Width           =   1080
   End
   Begin VB.Label lblLabels 
      Caption         =   "&Admin Name:"
      Height          =   248
      Index           =   0
      Left            =   105
      TabIndex        =   2
      Tag             =   "&User Name:"
      Top             =   150
      Width           =   1080
   End
End
Attribute VB_Name = "frmLogin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Const OBJNAME = "frmLogin"

Private Declare Function GetUserName Lib "advapi32.dll" Alias "GetUserNameA" (ByVal lpbuffer As String, nSize As Long) As Long


Public OK As Boolean
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
    
    If Err <= vbObjectError Then
        lErr = lErr = vbObjectError
    End If
    
    Err.Raise lErr, sMsg, Err.Description
End Function




Private Sub Form_Load()
    Dim sBuffer As String
    Dim lSize As Long


    sBuffer = Space$(255)
    lSize = Len(sBuffer)
    Call GetUserName(sBuffer, lSize)
    If lSize > 0 Then
        txtUserName.Text = Left$(sBuffer, lSize)
    Else
        txtUserName.Text = vbNullString
    End If
End Sub





Private Sub cmdCancel_Click()
    OK = False
    Me.Hide
End Sub


Private Sub cmdOK_Click()
    'To Do - create test for correct password
    'check for correct password
    If txtPassword.Text = "" Then
        OK = True
        Me.Hide
    Else
        MsgBox LoadResString(icIDS_ERR_INVALID_PASSWORD), "Login"
        txtPassword.SetFocus
        txtPassword.SelStart = 0
        txtPassword.SelLength = Len(txtPassword.Text)
    End If
End Sub

