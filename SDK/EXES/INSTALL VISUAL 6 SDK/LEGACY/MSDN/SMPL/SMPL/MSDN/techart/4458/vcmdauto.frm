VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "VCmdAuto OLE Server Demo"
   ClientHeight    =   480
   ClientLeft      =   1935
   ClientTop       =   2850
   ClientWidth     =   3315
   Height          =   1170
   Left            =   1875
   LinkTopic       =   "Form1"
   ScaleHeight     =   480
   ScaleWidth      =   3315
   Top             =   2220
   Width           =   3435
   Begin VB.Timer Timer1 
      Interval        =   200
      Left            =   2880
      Top             =   0
   End
   Begin VB.ComboBox WordSpoken 
      Height          =   315
      Left            =   120
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   0
      Width           =   3135
   End
   Begin VB.Menu MnuHello 
      Caption         =   "&Hello"
   End
   Begin VB.Menu MnuMicrosoft 
      Caption         =   "&Microsoft"
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim VCmd As Object
Dim VMenu As Object

Private Sub Form_Load()
WordSpoken.AddItem "Go"
WordSpoken.AddItem "Stop"
WordSpoken.AddItem "Yield"
Set VCmd = CreateObject("Speech.VoiceCommand")
Call VCmd.Register("")
Set VMenu = VCmd.MenuCreate("VB Test Program", "TestMenu", 1033&, "", vcmdmc_CREATE_ALWAYS)
For i = 0 To WordSpoken.ListCount - 1
    Call VMenu.Add(i, WordSpoken.List(i))
Next i
VMenu.Active = True
End Sub

Private Sub Form_Unload(Cancel As Integer)
End
End Sub

Private Sub Timer1_Timer()
WordSpoken.ListIndex = VCmd.CommandSpoken
End Sub
Sub Checkforword(ByVal Seconds As Single)
endat = Seconds / (24# * 3600#) + Now
Debug.Print Now, endat
While Now < endat
    DoEvents
    WordSpoken.ListIndex = VCmd.CommandSpoken
    Debug.Print VCmd.CommandSpoken, Now
Wend
End Sub
