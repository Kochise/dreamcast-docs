VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3795
   ClientLeft      =   1140
   ClientTop       =   1515
   ClientWidth     =   6315
   Height          =   4200
   Left            =   1080
   LinkTopic       =   "Form1"
   ScaleHeight     =   3795
   ScaleWidth      =   6315
   Top             =   1170
   Width           =   6435
   Begin VB.CommandButton Command1 
      Caption         =   "Beep"
      Height          =   1095
      Left            =   1680
      TabIndex        =   0
      Top             =   480
      Width           =   2295
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim x As New Beeper

Private Sub Command1_Click()
x.Beep
Dim str As Variant
For Each str In x
    MsgBox str
Next
End Sub

