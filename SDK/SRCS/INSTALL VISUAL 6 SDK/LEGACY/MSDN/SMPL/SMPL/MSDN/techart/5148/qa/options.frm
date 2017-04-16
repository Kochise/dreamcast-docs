VERSION 5.00
Begin VB.Form frmOptions 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Options"
   ClientHeight    =   3090
   ClientLeft      =   2055
   ClientTop       =   2130
   ClientWidth     =   5595
   Icon            =   "Options.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3090
   ScaleWidth      =   5595
   ShowInTaskbar   =   0   'False
   Begin VB.CheckBox chkOption 
      Caption         =   "Give extra help"
      Height          =   225
      Index           =   3
      Left            =   375
      TabIndex        =   5
      Top             =   1560
      Width           =   2955
   End
   Begin VB.CheckBox chkOption 
      Caption         =   "Text on buttons"
      Height          =   225
      Index           =   2
      Left            =   375
      TabIndex        =   4
      Top             =   1140
      Width           =   2955
   End
   Begin VB.CheckBox chkOption 
      Caption         =   "Log error messages"
      Height          =   225
      Index           =   1
      Left            =   375
      TabIndex        =   3
      Top             =   750
      Width           =   2955
   End
   Begin VB.CheckBox chkOption 
      Caption         =   "Show tool tips"
      Height          =   225
      Index           =   0
      Left            =   375
      TabIndex        =   2
      Top             =   345
      Width           =   2955
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   4290
      TabIndex        =   1
      Top             =   795
      Width           =   1125
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   4290
      TabIndex        =   0
      Top             =   360
      Width           =   1125
   End
End
Attribute VB_Name = "frmOptions"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'<Public>----------------------------------------------
Public optShowTips      As Integer
Public optLogErrors     As Integer
Public optButtonText    As Integer
Public optExtraHelp     As Integer
Public PressedOK        As Boolean
'</Public>---------------------------------------------

Private Sub cmdCancel_Click()

    PressedOK = False
    Unload Me

End Sub

Private Sub cmdOK_Click()

    optShowTips = chkOption(0).Value
    optLogErrors = chkOption(1).Value
    optButtonText = chkOption(2).Value
    optExtraHelp = chkOption(3).Value

    PressedOK = True
    Unload Me

End Sub
