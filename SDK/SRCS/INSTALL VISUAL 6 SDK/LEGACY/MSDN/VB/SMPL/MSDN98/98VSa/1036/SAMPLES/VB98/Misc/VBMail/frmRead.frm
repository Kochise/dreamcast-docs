VERSION 5.00
Object = "{831FDD16-0C5C-11d2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmRead 
   Caption         =   "Lire"
   ClientHeight    =   4995
   ClientLeft      =   3735
   ClientTop       =   2370
   ClientWidth     =   6720
   LinkTopic       =   "Form1"
   ScaleHeight     =   4995
   ScaleWidth      =   6720
   Begin MSComCtlLib.Toolbar tbrRead 
      Align           =   1  'Align Top
      Height          =   630
      Left            =   0
      TabIndex        =   7
      Top             =   0
      Width           =   6720
      _ExtentX        =   11853
      _ExtentY        =   1111
      ButtonWidth     =   2275
      ButtonHeight    =   953
      Appearance      =   1
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   5
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Répondre"
            Key             =   "reply"
            Description     =   "Reply"
            Object.ToolTipText     =   "Reply"
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Enabled         =   0   'False
            Style           =   4
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Répondre à tous"
            Key             =   "ReplyAll"
            Description     =   "Replly all"
            Object.ToolTipText     =   "Reply to all receipients"
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Enabled         =   0   'False
            Style           =   4
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Transférer"
            Key             =   "forward"
            Description     =   "Forward the message"
            Object.ToolTipText     =   "Forward the message"
         EndProperty
      EndProperty
   End
   Begin VB.TextBox txtRead 
      Height          =   2805
      Left            =   240
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   3
      Top             =   2010
      Width           =   6375
   End
   Begin VB.Label Label2 
      Caption         =   "À"
      Height          =   210
      Left            =   0
      TabIndex        =   9
      Top             =   1005
      Width           =   855
   End
   Begin VB.Label lblTo 
      Height          =   210
      Left            =   960
      TabIndex        =   8
      Top             =   1005
      Width           =   5535
   End
   Begin VB.Label lblCC 
      Height          =   210
      Left            =   960
      TabIndex        =   6
      Top             =   1350
      Width           =   5535
   End
   Begin VB.Label lblFrom 
      Height          =   210
      Left            =   960
      TabIndex        =   5
      Top             =   720
      Width           =   5535
   End
   Begin VB.Label lblSubject 
      Height          =   210
      Left            =   960
      TabIndex        =   4
      Top             =   1650
      Width           =   5535
   End
   Begin VB.Label Label3 
      Caption         =   "Sujet"
      Height          =   210
      Left            =   0
      TabIndex        =   2
      Top             =   1650
      Width           =   855
   End
   Begin VB.Label lbl 
      Caption         =   "CC"
      Height          =   210
      Left            =   0
      TabIndex        =   1
      Top             =   1350
      Width           =   855
   End
   Begin VB.Label Label1 
      Caption         =   "De:"
      Height          =   210
      Left            =   0
      TabIndex        =   0
      Top             =   720
      Width           =   855
   End
End
Attribute VB_Name = "frmRead"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private intMsgIndex As Integer


Private Sub Form_Load()
    ' Stocke le message en cas d'erreur.
    intMsgIndex = frmMain.mapMess.MsgIndex
End Sub

Private Sub tbrRead_ButtonClick(ByVal Button As MSComCtlLib.Button)
    On Error GoTo SendErr
    
    Select Case Button.Key
    Case "reply"
        With frmMain.mapMess
            .Copy
            .Reply
            .AddressResolveUI = True
            .Send True
        End With

    Case "ReplyAll"
        With frmMain.mapMess
            .ReplyAll
            .Send True
        End With
    Case "forward"
        With frmMain.mapMess
            .Forward
            .AddressResolveUI = True
            .Send True
        End With
    Case Else
        Debug.Print Button.Key
    End Select
    Exit Sub
SendErr:
    If Err.Number = mapInvalidComposeBufferAction Then
        frmMain.mapMess.MsgIndex = intMsgIndex ' Reset to read buffer.
        Resume
    Else ' autre cas
        MsgBox Err.Number & ": " & Err.Description
    End If
End Sub
