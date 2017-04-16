VERSION 4.00
Begin VB.Form FormCtl 
   Caption         =   "Form1"
   ClientHeight    =   8445
   ClientLeft      =   7020
   ClientTop       =   1755
   ClientWidth     =   6690
   Height          =   8865
   Left            =   6960
   LinkTopic       =   "Form1"
   ScaleHeight     =   8445
   ScaleWidth      =   6690
   Top             =   1395
   Width           =   6810
   Begin VB.Timer Timer1 
      Left            =   480
      Top             =   5640
   End
   Begin VB.ListBox CtlList 
      Height          =   4935
      Left            =   120
      TabIndex        =   0
      Top             =   360
      Width           =   6495
   End
End
Attribute VB_Name = "FormCtl"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Sub EnumerateComponents()
End Sub

Private Sub Form_Click()
EnumerateComponents
End Sub

Private Sub Form_Load()
EnumerateComponents
End Sub
