VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   1575
   ClientLeft      =   6270
   ClientTop       =   4950
   ClientWidth     =   2130
   LinkTopic       =   "Form1"
   ScaleHeight     =   1575
   ScaleWidth      =   2130
   Begin VB.CommandButton Command1 
      Caption         =   "GO!"
      Height          =   495
      Left            =   480
      TabIndex        =   0
      Top             =   600
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
On Error GoTo error_olemsg
    
    ' create a session then log on, supplying username and password
    Set objSession = CreateObject("MAPI.Session")
    ' change the parameters to valid values for your configuration
    objSession.Logon profileName:="TO DO: Place profile name here"
 
    ' create a message and fill in its properties
    Set objMessage = objSession.Outbox.Messages.Add
    objMessage.subject = "Gift of droids"
    objMessage.Text = "Help us, Obi-wan. You are our only hope."
 
    ' create the recipient
    Set objOneRecip = objMessage.Recipients.Add
    objOneRecip.Name = "TO DO: Place email alias here"
    objOneRecip.Type = mapiTo
    objOneRecip.Resolve
 
    ' send the message and log off
    objMessage.Send showDialog:=False
    MsgBox "The message has been sent"
    objSession.Logoff
    GoTo end_olemsg
    
error_olemsg:
    MsgBox "Error " & Str(Err) & ": " & Error$(Err)
end_olemsg:
End Sub

