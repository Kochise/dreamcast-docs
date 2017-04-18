VERSION 4.00
Begin VB.Form frmNewReport 
   Appearance      =   0  'Flat
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "New Report"
   ClientHeight    =   3210
   ClientLeft      =   3045
   ClientTop       =   1710
   ClientWidth     =   5250
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   1
      weight          =   700
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   Height          =   3615
   Left            =   2985
   LinkTopic       =   "Form1"
   ScaleHeight     =   3210
   ScaleWidth      =   5250
   Top             =   1365
   Width           =   5370
   Begin VB.CommandButton cmdCancel 
      Appearance      =   0  'Flat
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   4020
      TabIndex        =   6
      Top             =   540
      Width           =   1095
   End
   Begin VB.CommandButton cmdOk 
      Appearance      =   0  'Flat
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   4020
      TabIndex        =   5
      Top             =   120
      Width           =   1095
   End
   Begin Threed.SSPanel pnlTextBoxBackdrop 
      Height          =   2955
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3735
      _Version        =   65536
      _ExtentX        =   6588
      _ExtentY        =   5212
      _StockProps     =   15
      Begin VB.Label lblReportType 
         Appearance      =   0  'Flat
         Caption         =   "Type of Report:"
         ForeColor       =   &H80000008&
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Top             =   180
         Width           =   1590
      End
      Begin Threed.SSOption optReportType 
         Height          =   270
         Index           =   0
         Left            =   480
         TabIndex        =   3
         Top             =   480
         Width           =   3135
         _Version        =   65536
         _ExtentX        =   5530
         _ExtentY        =   476
         _StockProps     =   78
         Caption         =   "&Site Hierarchy"
      End
      Begin Threed.SSOption optReportType 
         Height          =   270
         Index           =   1
         Left            =   480
         TabIndex        =   2
         TabStop         =   0   'False
         Top             =   840
         Width           =   3135
         _Version        =   65536
         _ExtentX        =   5530
         _ExtentY        =   476
         _StockProps     =   78
         Caption         =   "&Machine Properties"
      End
      Begin Threed.SSOption optReportType 
         Height          =   270
         Index           =   2
         Left            =   480
         TabIndex        =   1
         TabStop         =   0   'False
         Top             =   1200
         Visible         =   0   'False
         Width           =   3135
         _Version        =   65536
         _ExtentX        =   5530
         _ExtentY        =   476
         _StockProps     =   78
         Caption         =   "&Generic"
      End
   End
End
Attribute VB_Name = "frmNewReport"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  NEWREPRT.FRM
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

Dim OldMousePointer%
Dim CallingForm As Form

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOk_Click()
    'Set to login success
    NewReportUserCanceled% = False
    Unload Me
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
    NewReportUserCanceled% = True

    'Set the first radio button true
    optReportType(0) = True
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'Replace mouse pointer
    CallingForm.MousePointer = OldMousePointer%
End Sub

Private Sub optReportType_Click(Index As Integer, Value As Integer)
    Select Case Index
        Case 0
            NewReportSelection% = SITE_HIERARCHY_REPORT
        Case 1
            NewReportSelection% = MACHINE_GROUP_REPORT
        Case 2
            NewReportSelection% = GENERIC_REPORT
        Case Else
            NewReportSelection% = UNKNOWN_REPORT
    End Select
End Sub

