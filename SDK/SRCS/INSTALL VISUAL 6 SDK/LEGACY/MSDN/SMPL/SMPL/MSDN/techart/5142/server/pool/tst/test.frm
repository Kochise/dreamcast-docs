VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "Pool"
   ClientHeight    =   735
   ClientLeft      =   60
   ClientTop       =   300
   ClientWidth     =   1590
   LinkTopic       =   "Form1"
   ScaleHeight     =   735
   ScaleWidth      =   1590
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton btPool 
      Caption         =   "Start Pool"
      Height          =   615
      Left            =   90
      TabIndex        =   0
      Top             =   60
      Width           =   1440
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private m_oPool As Object

Private Sub btPool_Click()
Dim oTemp As Object

If btPool.Caption = "Start Pool" Then
    btPool.Caption = "Stop Pool"
    Set m_oPool = CreateObject("ForumPool.CPool")
    Set oTemp = m_oPool.GetForumService()
    oTemp.CreateSampleForums
    Set oTemp = Nothing
Else
    Set oTemp = m_oPool.GetForumService()
    oTemp.Term
    Set oTemp = Nothing
    Set m_oPool = Nothing
    btPool.Caption = "Start Pool"
End If
End Sub
