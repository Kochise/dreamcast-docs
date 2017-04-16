VERSION 4.00
Begin VB.Form frmMain 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Access Report Generator"
   ClientHeight    =   225
   ClientLeft      =   1575
   ClientTop       =   6495
   ClientWidth     =   4275
   Height          =   585
   Left            =   1515
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   225
   ScaleWidth      =   4275
   ShowInTaskbar   =   0   'False
   Top             =   6195
   Width           =   4395
   Begin VB.Timer tmMain 
      Enabled         =   0   'False
      Interval        =   500
      Left            =   2505
      Top             =   0
   End
   Begin ComctlLib.StatusBar sbMain 
      Align           =   2  'Align Bottom
      Height          =   225
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   4275
      _Version        =   65536
      _ExtentX        =   7541
      _ExtentY        =   397
      _StockProps     =   68
      AlignSet        =   -1  'True
      SimpleText      =   ""
      i1              =   "frmMain.frx":0000
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Public objWork As AccessReport

Private Sub Form_Unload(Cancel As Integer)
On Error Resume Next
Set objWork = Nothing
End Sub

Private Sub tmMain_Timer()
If objWork.fPhaseTwo Then
    tmMain.Enabled = False
    objWork.PrintReport False
End If
End Sub

Public Sub StatusSet(ByVal sTemp As String)
On Error Resume Next
sbMain.Panels(1).Text = " " & sTemp
End Sub
Public Sub StatusReset()
On Error Resume Next
sbMain.Panels(1).Text = " Ready"
End Sub
