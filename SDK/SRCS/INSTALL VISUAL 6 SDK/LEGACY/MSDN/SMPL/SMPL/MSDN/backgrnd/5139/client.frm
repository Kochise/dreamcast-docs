VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Hellojtx Client"
   ClientHeight    =   2055
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   3285
   LinkTopic       =   "Form1"
   ScaleHeight     =   2055
   ScaleWidth      =   3285
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdSayHello 
      Caption         =   "Say &Hello"
      Height          =   495
      Left            =   360
      TabIndex        =   0
      Top             =   480
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdSayHello_Click()
       
    Dim myHello As CHellojtx
    Dim str As String
    Dim nRet As Long
    
    On Error GoTo onError

    Set myHello = CreateObject("Hellojtx.Hello")
    nRet = myHello.SayHello(str)
    MsgBox str
    
    Exit Sub

onError:
    MsgBox "error"

End Sub
