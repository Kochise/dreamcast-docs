VERSION 5.00
Begin VB.Form frmPropsNew 
   Caption         =   "Object Properties"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   Begin VB.ListBox lstProps 
      Height          =   3210
      IntegralHeight  =   0   'False
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   4695
   End
End
Attribute VB_Name = "frmPropsNew"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim iHMargin As Integer   ' width along sides of the tree view
Dim iVMargin As Integer   ' width along bottom of the tree view
Dim iTop As Integer       ' position of top of tree view

Private Sub Close_Click()
    MainForm.bPropsShow = False
    Unload Me
End Sub

Private Sub Form_Load()
    MainForm.bPropsShow = True
    iTop = lstProps.Top
    iHMargin = (Width - lstProps.Width) / 2
    iVMargin = Height - lstProps.Height - lstProps.Top
End Sub

Private Sub Form_Resize()
    Dim lstWidth As Integer
    Dim lstHeight As Integer
    
    lstWidth = Width - iHMargin * 2
    lstHeight = Height - iTop - iVMargin
    
    If (lstWidth > 0) Then lstProps.Width = lstWidth
    If (lstHeight > 0) Then lstProps.Height = lstHeight

End Sub

