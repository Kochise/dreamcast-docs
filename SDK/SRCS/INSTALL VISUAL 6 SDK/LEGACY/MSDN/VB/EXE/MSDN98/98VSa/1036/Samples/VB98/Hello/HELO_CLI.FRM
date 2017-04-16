VERSION 5.00
Begin VB.Form frmClient 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Client Bonjour"
   ClientHeight    =   1485
   ClientLeft      =   2820
   ClientTop       =   3855
   ClientWidth     =   3345
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   1485
   ScaleWidth      =   3345
   Begin VB.CommandButton cmdSayHi 
      Caption         =   "Dire Bonjour"
      Height          =   405
      Left            =   1020
      TabIndex        =   0
      Top             =   540
      Width           =   1230
   End
End
Attribute VB_Name = "frmClient"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim objNew As Object

Private Sub cmdSayHi_Click()
  MsgBox objNew.SayHello
End Sub

Private Sub Form_Load()
  Set objNew = CreateObject("HelloProj.HelloClass")
End Sub

Private Sub Form_Unload(Cancel As Integer)
  Set objNew = Nothing
End Sub
