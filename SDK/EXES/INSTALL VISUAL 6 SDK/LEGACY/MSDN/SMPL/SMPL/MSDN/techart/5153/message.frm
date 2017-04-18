VERSION 5.00
Begin VB.Form frmMessage 
   Caption         =   "Send Message"
   ClientHeight    =   4830
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7485
   LinkTopic       =   "Form1"
   ScaleHeight     =   4830
   ScaleWidth      =   7485
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdSend 
      Caption         =   "Send"
      Height          =   375
      Left            =   6240
      TabIndex        =   8
      Top             =   4320
      Width           =   975
   End
   Begin VB.TextBox txtText 
      Height          =   2655
      Left            =   1080
      TabIndex        =   6
      ToolTipText     =   "Enter the Text here"
      Top             =   1440
      Width           =   6375
   End
   Begin VB.TextBox txtSub 
      Height          =   375
      Left            =   1080
      TabIndex        =   4
      ToolTipText     =   "Enter the Subject here"
      Top             =   960
      Width           =   6375
   End
   Begin VB.TextBox txtCC 
      Height          =   375
      Left            =   1080
      TabIndex        =   2
      ToolTipText     =   "Enter Address to send a copy"
      Top             =   540
      Width           =   6375
   End
   Begin VB.TextBox txtTo 
      Height          =   375
      Left            =   1080
      TabIndex        =   0
      ToolTipText     =   "Enter Address to send"
      Top             =   120
      Width           =   6375
   End
   Begin VB.Label lblTxt 
      Alignment       =   1  'Right Justify
      Caption         =   "Text :"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   1500
      Width           =   855
   End
   Begin VB.Label lblSub 
      Alignment       =   1  'Right Justify
      Caption         =   "Subject :"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   1020
      Width           =   855
   End
   Begin VB.Label lblCC 
      Alignment       =   1  'Right Justify
      Caption         =   "CC :"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   600
      Width           =   855
   End
   Begin VB.Label lblTo 
      Alignment       =   1  'Right Justify
      Caption         =   "To :"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   180
      Width           =   855
   End
End
Attribute VB_Name = "frmMessage"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Const SETTINGS = "MS Exchange Settings"
Const SEMICOLON = ";"
Private Sub cmdSend_Click()

On Error GoTo ErrSend

Dim oSess       As Mapi.Session
Dim oMsg        As Mapi.Message
Dim oRecipTo    As Mapi.Recipient
Dim oRecipCC    As Mapi.Recipient

'Create an object of Session
Set oSess = CreateObject("Mapi.Session")

'Logon to the Session
oSess.Logon SETTINGS

'create a message and fill in its properties
Set oMsg = oSess.Outbox.Messages.Add
oMsg.Subject = txtSub
oMsg.Text = txtText

SetRecipients oMsg, oRecipTo, ActMsgTo
SetRecipients oMsg, oRecipTo, ActMsgCc

' send the message and log off
oMsg.Update
oMsg.Send

'logoff the session
oSess.Logoff

'Clear all the objects before exiting the procedure
Set oRecipTo = Nothing
Set oRecipCC = Nothing
Set oMsg = Nothing
Set oSess = Nothing

Exit Sub
    
ErrSend:
    MsgBox Err.Number & " : " & Err.Description
    'Clear all the objects before exiting the procedure
    Set oRecipTo = Nothing
    Set oRecipCC = Nothing
    Set oMsg = Nothing
    Set oSess = Nothing

End Sub
'This procedure sets all the recipients and
'adds them to the Recipients collection of
'Message object
Public Sub SetRecipients(oMsg As Mapi.Message, oRec As Mapi.Recipient, iRecipType As Integer)

    Dim sRecipients As String
    Dim sTemp       As String
    Dim iPos        As Integer
    Dim iStart      As Integer
    
    Select Case UCase$(iRecipType)
        Case ActMsgTo
            sRecipients = txtTo
        Case ActMsgCc
            sRecipients = txtCC
    End Select
        
    If (Right(sRecipients, 1) <> SEMICOLON) And Trim(sRecipients) <> "" Then
        sRecipients = sRecipients & SEMICOLON
    End If
    
    '=========================================================
    'Initialise the Position and Start counters
    iPos = 1
    iStart = 1
    '=========================================================
    
    '=========================================================
    Do While iPos <> 0
        iPos = InStr(iStart, sRecipients, ";")
        If iPos > 0 Then
            sTemp = Mid$(sRecipients, iStart, iPos - iStart)
            Set oRec = oMsg.Recipients.Add
            oRec.Name = sTemp
            oRec.Type = iRecipType
            oRec.Resolve
        End If
        iStart = iPos + 1
    Loop
    '=========================================================

End Sub
