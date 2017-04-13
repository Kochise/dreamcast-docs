VERSION 4.00
Begin VB.Form frmDBLogin 
   Appearance      =   0  'Flat
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Microsoft SMS Login"
   ClientHeight    =   3195
   ClientLeft      =   2535
   ClientTop       =   5070
   ClientWidth     =   5430
   ControlBox      =   0   'False
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   0
      weight          =   700
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   Height          =   3600
   Left            =   2475
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3195
   ScaleWidth      =   5430
   Top             =   4725
   Width           =   5550
   Begin Threed.SSPanel pnlDialogBackdrop 
      Height          =   3195
      Left            =   0
      TabIndex        =   18
      Top             =   0
      Width           =   5415
      _Version        =   65536
      _ExtentX        =   9551
      _ExtentY        =   5636
      _StockProps     =   15
      Begin Threed.SSPanel pnlIconBackdrop 
         Height          =   1035
         Left            =   4140
         TabIndex        =   20
         Top             =   1980
         Width           =   1095
         _Version        =   65536
         _ExtentX        =   1931
         _ExtentY        =   1826
         _StockProps     =   15
         Begin VB.Image imgIcon 
            Appearance      =   0  'Flat
            Height          =   480
            Left            =   300
            Picture         =   "DBLOGIN.frx":0000
            Top             =   300
            Width           =   480
         End
      End
      Begin VB.CommandButton cmdCancel 
         Appearance      =   0  'Flat
         Cancel          =   -1  'True
         Caption         =   "Cancel"
         Height          =   375
         Left            =   4140
         TabIndex        =   17
         Top             =   600
         Width           =   1095
      End
      Begin VB.CommandButton cmdOk 
         Appearance      =   0  'Flat
         Caption         =   "OK"
         Default         =   -1  'True
         Height          =   375
         Left            =   4140
         TabIndex        =   16
         Top             =   180
         Width           =   1095
      End
      Begin Threed.SSPanel pnlTextBoxBackdrop 
         Height          =   2835
         Left            =   240
         TabIndex        =   19
         Top             =   180
         Width           =   3735
         _Version        =   65536
         _ExtentX        =   6588
         _ExtentY        =   5001
         _StockProps     =   15
         Begin Threed.SSPanel pnlPassword 
            Height          =   315
            Left            =   120
            TabIndex        =   13
            Top             =   2400
            Width           =   3495
            _Version        =   65536
            _ExtentX        =   6165
            _ExtentY        =   556
            _StockProps     =   15
            BevelOuter      =   1
            Begin VB.PictureBox picPassword 
               Appearance      =   0  'Flat
               BackColor       =   &H80000005&
               BorderStyle     =   0  'None
               ForeColor       =   &H80000008&
               Height          =   255
               Left            =   30
               ScaleHeight     =   255
               ScaleWidth      =   3435
               TabIndex        =   14
               TabStop         =   0   'False
               Top             =   30
               Width           =   3435
               Begin VB.TextBox txtPassword 
                  Appearance      =   0  'Flat
                  BorderStyle     =   0  'None
                  Height          =   195
                  Left            =   30
                  PasswordChar    =   "*"
                  TabIndex        =   15
                  Tag             =   "OL"
                  Top             =   30
                  Width           =   3375
               End
            End
         End
         Begin Threed.SSPanel pnlUserName 
            Height          =   315
            Left            =   120
            TabIndex        =   9
            Top             =   1740
            Width           =   3495
            _Version        =   65536
            _ExtentX        =   6165
            _ExtentY        =   556
            _StockProps     =   15
            BevelOuter      =   1
            Begin VB.PictureBox picUserName 
               Appearance      =   0  'Flat
               BackColor       =   &H80000005&
               BorderStyle     =   0  'None
               ForeColor       =   &H80000008&
               Height          =   255
               Left            =   30
               ScaleHeight     =   255
               ScaleWidth      =   3435
               TabIndex        =   10
               TabStop         =   0   'False
               Top             =   30
               Width           =   3435
               Begin VB.TextBox txtUserName 
                  Appearance      =   0  'Flat
                  BorderStyle     =   0  'None
                  Height          =   195
                  Left            =   30
                  TabIndex        =   11
                  Tag             =   "OL"
                  Top             =   30
                  Width           =   3375
               End
            End
         End
         Begin Threed.SSPanel pnlDBName 
            Height          =   315
            Left            =   120
            TabIndex        =   1
            Top             =   420
            Width           =   3495
            _Version        =   65536
            _ExtentX        =   6165
            _ExtentY        =   556
            _StockProps     =   15
            BevelOuter      =   1
            Begin VB.PictureBox picDBName 
               Appearance      =   0  'Flat
               BackColor       =   &H80000005&
               BorderStyle     =   0  'None
               ForeColor       =   &H80000008&
               Height          =   255
               Left            =   30
               ScaleHeight     =   255
               ScaleWidth      =   3435
               TabIndex        =   2
               TabStop         =   0   'False
               Top             =   30
               Width           =   3435
               Begin VB.TextBox txtDBName 
                  Appearance      =   0  'Flat
                  BorderStyle     =   0  'None
                  Height          =   195
                  Left            =   30
                  TabIndex        =   3
                  Top             =   30
                  Width           =   3375
               End
            End
         End
         Begin Threed.SSPanel pnlDataBase 
            Height          =   315
            Left            =   120
            TabIndex        =   5
            Top             =   1080
            Width           =   3495
            _Version        =   65536
            _ExtentX        =   6165
            _ExtentY        =   556
            _StockProps     =   15
            BevelOuter      =   1
            Begin VB.PictureBox picDataBase 
               Appearance      =   0  'Flat
               BackColor       =   &H80000005&
               BorderStyle     =   0  'None
               ForeColor       =   &H80000008&
               Height          =   255
               Left            =   30
               ScaleHeight     =   255
               ScaleWidth      =   3435
               TabIndex        =   6
               TabStop         =   0   'False
               Top             =   30
               Width           =   3435
               Begin VB.TextBox txtDataBase 
                  Appearance      =   0  'Flat
                  BorderStyle     =   0  'None
                  Height          =   195
                  Left            =   30
                  TabIndex        =   7
                  Tag             =   "OL"
                  Top             =   30
                  Width           =   3375
               End
            End
         End
         Begin VB.Label lblPassword 
            Appearance      =   0  'Flat
            Caption         =   "&Password:"
            ForeColor       =   &H80000008&
            Height          =   255
            Left            =   120
            TabIndex        =   12
            Top             =   2160
            Width           =   1335
         End
         Begin VB.Label lblUserName 
            Appearance      =   0  'Flat
            Caption         =   "&Login ID:"
            ForeColor       =   &H80000008&
            Height          =   255
            Left            =   120
            TabIndex        =   8
            Top             =   1500
            Width           =   1335
         End
         Begin VB.Label lblDBName 
            Appearance      =   0  'Flat
            Caption         =   "&SQL Server Name:"
            ForeColor       =   &H80000008&
            Height          =   255
            Left            =   120
            TabIndex        =   0
            Top             =   180
            Width           =   1590
         End
         Begin VB.Label lblDataBase 
            Appearance      =   0  'Flat
            Caption         =   "&Database:"
            ForeColor       =   &H80000008&
            Height          =   255
            Left            =   120
            TabIndex        =   4
            Top             =   840
            Width           =   1335
         End
      End
   End
End
Attribute VB_Name = "frmDBLogin"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  DBLOGIN.FRM
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

Dim OldMousePointer%
Dim CallingForm As Form

Private Sub CheckOkStatus()
    cmdOK.Enabled = (txtDBName > "" And txtDatabase > "" And txtUserName > "")
End Sub

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOk_Click()
    Dim lRet&, LoadDLLFailed%

    OpenDBInfo.ds = DB_SQL
    OpenDBInfo.pszServer = txtDBName
    OpenDBInfo.pszUserName = txtUserName
    OpenDBInfo.pszPasswd = txtPassword
    OpenDBInfo.pszDbName = txtDatabase
    OpenDBInfo.pszKey = ""
    OpenDBInfo.pFunc = 0

    'Put up wait cursor
    MousePointer = HOURGLASS

    'Login to SMS
    ' (This loads the DLLs since it is the first call)
    LoadDLLFailed% = False
    On Error Resume Next
    lRet& = SmsDataSourceConnect&(OpenDBInfo, OpenDBConnect&)
    If (Err > 0) Then LoadDLLFailed% = True
    On Error GoTo 0

    'Restore normal cursor
    MousePointer = DEFAULT

    If LoadDLLFailed% Then
        MsgBox "Unable to load VB4SMS32.OLB:" + Chr$(10) + "Please check that all SMSAPI dlls are installed and search paths are correct.", MB_OK + MB_ICONINFORMATION
        Exit Sub
    End If

    If (lRet& <> SMS_OK) Then
        MsgBox "Login Failed!", MB_ICONEXCLAMATION, Caption
        txtPassword.SetFocus
        Exit Sub
    End If

    'Set to login success
    OpenDBUserCanceled% = False
    MousePointer = NORMAL
    Unload Me
End Sub

Private Sub Form_Activate()
    If txtDBName = "" Then
        txtDBName.SetFocus
    ElseIf txtDatabase = "" Then
        txtDatabase.SetFocus
    ElseIf txtUserName = "" Then
        txtUserName.SetFocus
    Else
        txtPassword.SetFocus
    End If
End Sub

Private Sub Form_Load()
    Dim NewLeft%, NewTop%
    
    'Save the old mouse pointer
    Set CallingForm = Screen.ActiveForm
    OldMousePointer% = CallingForm.MousePointer
    
    'Turn on normal pointer
    MousePointer = NORMAL
    
    'Center form on calling form
    NewLeft% = CallingForm.left + (CallingForm.Width - Width) / 2
    If NewLeft% + Width > Screen.Width Then NewLeft% = Screen.Width - Width
    If NewLeft% < 0 Then NewLeft% = 0
    NewTop% = CallingForm.top + (CallingForm.Height - Height) / 2
    If NewTop% + Height > Screen.Height Then NewTop% = Screen.Height - Height
    If NewTop% < 0 Then NewTop% = 0
    left = NewLeft%
    top = NewTop%
    
    'Set default to be user canceled
    OpenDBUserCanceled% = True
    
    CheckOkStatus
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'Replace mouse pointer
    CallingForm.MousePointer = OldMousePointer%
End Sub

Private Sub txtDataBase_Change()
    CheckOkStatus
End Sub

Private Sub txtDataBase_GotFocus()
    txtDatabase.SelStart = 0
    txtDatabase.SelLength = Len(txtDatabase)
End Sub

Private Sub txtDBName_Change()
    CheckOkStatus
End Sub

Private Sub txtDBName_GotFocus()
    txtDBName.SelStart = 0
    txtDBName.SelLength = Len(txtDBName)
End Sub

Private Sub txtPassword_GotFocus()
    txtPassword.SelStart = 0
    txtPassword.SelLength = Len(txtPassword)
End Sub

Private Sub txtUserName_Change()
    CheckOkStatus
End Sub

Private Sub txtUserName_GotFocus()
    txtUserName.SelStart = 0
    txtUserName.SelLength = Len(txtUserName)
End Sub

