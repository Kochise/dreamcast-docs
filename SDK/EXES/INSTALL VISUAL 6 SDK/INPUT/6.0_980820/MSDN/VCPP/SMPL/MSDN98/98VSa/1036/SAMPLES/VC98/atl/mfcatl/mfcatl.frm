VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "VB driver for MfcAtl Sample"
   ClientHeight    =   3060
   ClientLeft      =   1140
   ClientTop       =   1515
   ClientWidth     =   3720
   Height          =   3465
   Left            =   1080
   LinkTopic       =   "Form1"
   ScaleHeight     =   3060
   ScaleWidth      =   3720
   Top             =   1170
   Width           =   3840
   Begin VB.CommandButton Command3 
      Caption         =   "Call Both Objects"
      Height          =   735
      Left            =   360
      TabIndex        =   2
      Top             =   2160
      Width           =   2895
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Call Object Two"
      Height          =   735
      Left            =   360
      TabIndex        =   1
      Top             =   1200
      Width           =   2895
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Call Object One"
      Height          =   735
      Left            =   360
      TabIndex        =   0
      Top             =   240
      Width           =   2895
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False

Private Sub Command1_Click()
    Dim obj1 As Object
    Set obj1 = CreateObject("MfcAtl.ObjectOne")
    MsgBox obj1.SayHello()
    Set obj1 = Nothing
End Sub


Private Sub Command2_Click()
    Dim obj2 As New ObjectTwo
    MsgBox obj2.SayHello()
    Set obj2 = Nothing
End Sub


Private Sub Command3_Click()
    Dim obj1 As Object
    Set obj1 = CreateObject("MfcAtl.ObjectOne")
    Dim obj2 As New ObjectTwo
    MsgBox obj1.SayHello()
    MsgBox obj2.SayHello()
    Set obj2 = Nothing
    Set obj1 = Nothing
End Sub


