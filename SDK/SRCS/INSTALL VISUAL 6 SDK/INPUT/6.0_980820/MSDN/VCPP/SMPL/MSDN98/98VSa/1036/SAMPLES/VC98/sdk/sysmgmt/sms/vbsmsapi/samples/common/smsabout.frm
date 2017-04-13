VERSION 4.00
Begin VB.Form frmSMSAbout 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "About SMS Report"
   ClientHeight    =   2895
   ClientLeft      =   1080
   ClientTop       =   1485
   ClientWidth     =   7755
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
   Height          =   3300
   Left            =   1020
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2895
   ScaleWidth      =   7755
   Top             =   1140
   Width           =   7875
   Begin Threed.SSPanel pnlDialogBackdrop 
      Height          =   2895
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   7755
      _Version        =   65536
      _ExtentX        =   13679
      _ExtentY        =   5106
      _StockProps     =   15
      BackColor       =   -2147483633
      Begin VB.Timer tmrAnimation 
         Interval        =   100
         Left            =   180
         Top             =   2340
      End
      Begin VB.CommandButton cmdOk 
         Appearance      =   0  'Flat
         Caption         =   "OK"
         Default         =   -1  'True
         Height          =   375
         Left            =   6480
         TabIndex        =   3
         Top             =   2400
         Width           =   1095
      End
      Begin Threed.SSPanel pnlOutlineBackdrop 
         Height          =   1995
         Left            =   180
         TabIndex        =   1
         Top             =   240
         Width           =   7395
         _Version        =   65536
         _ExtentX        =   13044
         _ExtentY        =   3519
         _StockProps     =   15
         BackColor       =   -2147483633
         Begin Threed.SSPanel pnlVersion 
            Height          =   315
            Left            =   240
            TabIndex        =   2
            Top             =   1500
            Width           =   6915
            _Version        =   65536
            _ExtentX        =   12197
            _ExtentY        =   556
            _StockProps     =   15
            BackColor       =   -2147483633
            BevelOuter      =   1
            Autosize        =   3
         End
         Begin VB.PictureBox picLogo 
            Appearance      =   0  'Flat
            BackColor       =   &H80000005&
            BorderStyle     =   0  'None
            ForeColor       =   &H80000008&
            Height          =   960
            Left            =   240
            ScaleHeight     =   960
            ScaleWidth      =   960
            TabIndex        =   4
            Top             =   180
            Width           =   960
         End
         Begin PicClip.PictureClip pcpAnimation 
            Left            =   -3885
            Top             =   -1965
            _Version        =   65536
            _ExtentX        =   8625
            _ExtentY        =   5186
            _StockProps     =   0
            Rows            =   3
            Cols            =   5
            Picture         =   "SMSABOUT.frx":0000
         End
         Begin VB.Label Label1 
            Appearance      =   0  'Flat
            Caption         =   "Version Information:"
            ForeColor       =   &H80000008&
            Height          =   255
            Left            =   240
            TabIndex        =   6
            Top             =   1260
            Width           =   1875
         End
         Begin VB.Label lblInfo 
            Alignment       =   2  'Center
            Appearance      =   0  'Flat
            ForeColor       =   &H80000008&
            Height          =   975
            Left            =   1380
            TabIndex        =   5
            Top             =   180
            Width           =   5775
         End
      End
   End
End
Attribute VB_Name = "frmSMSAbout"
Attribute VB_Creatable = False
Attribute VB_Exposed = False

Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  SMSABOUT.FRM
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   6/13/95      Created.
'//
'//****************************************************************************

Dim OldMousePointer%
Dim CallingForm As Form

Private Sub cmdOk_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    Dim NewLeft%, NewTop%
    Dim lRet&, Ver$
    
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

    'Set caption and info fields
    Caption = SMSAboutCaption$
    lblInfo = SMSAboutInfo$

    'Get SMS version string
    lRet& = SmsAPIVer&(Ver$)
    If lRet& = SMS_OK Then
        pnlVersion.Caption = Ver$
    Else: pnlVersion.Caption = "<Error obtaining version string>"
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'Replace mouse pointer
    CallingForm.MousePointer = OldMousePointer%
End Sub

Private Sub tmrAnimation_Timer()
    Static index%

    picLogo.Picture = pcpAnimation.GraphicCell(index%)
    index% = (index% + 1) Mod 14
End Sub

