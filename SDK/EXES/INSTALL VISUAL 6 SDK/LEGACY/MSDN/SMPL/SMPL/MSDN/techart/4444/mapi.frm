VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "MAPI OLE Server Demo"
   ClientHeight    =   2985
   ClientLeft      =   1140
   ClientTop       =   1515
   ClientWidth     =   6450
   Height          =   3390
   Left            =   1080
   LinkTopic       =   "Form1"
   ScaleHeight     =   2985
   ScaleWidth      =   6450
   Top             =   1170
   Width           =   6570
   Begin VB.CommandButton Command1 
      Caption         =   "&Send Email"
      Height          =   375
      Left            =   3840
      TabIndex        =   1
      Top             =   2520
      Width           =   2535
   End
   Begin VB.TextBox Text1 
      Height          =   2415
      Left            =   0
      TabIndex        =   0
      Text            =   "Ken's article is excellent. He's worth $2.00 per email!"
      Top             =   0
      Width           =   6375
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim ThisSession As Object 'MAPI.Session
Dim thisMessage As Object 'MAPI.Message
Dim thisRecipient As Object 'MAPI.Recipient
Dim MSSession As Object

Private Sub Command1_Click()
Set thisMessage = ThisSession.Outbox.Messages.Add( _
        subject:="Thank you for your article", _
        Text:=Text1.Text, _
        type:="IPM.NOTE", _
        importance:=MAPI.mapiImportance.mapiHigh)
With thisMessage
    Set thisRecipient = thisMessage.Recipients.Add( _
        Name:="Kenl@Microsoft.Com", _
        type:=MAPI.mapiRecipientType.mapiTo)
    rc% = .Send( _
        saveCopy:=True, _
        showDialog:=True, _
        parentWindow:=hWnd)
    If rc% <> 0 Then MsgBox "Problem sending message"
End With
End Sub

Private Sub Form_Load()
Set ThisSession = CreateObject("MAPI.Session")
ThisSession.Logon
End Sub

Private Sub Form_Unload(Cancel As Integer)
ThisSession.Logoff
End Sub
