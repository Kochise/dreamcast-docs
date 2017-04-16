VERSION 4.00
Begin VB.Form frmMSDNDemo 
   Caption         =   "Access 95 OLE Server Demo"
   ClientHeight    =   540
   ClientLeft      =   2460
   ClientTop       =   1845
   ClientWidth     =   4485
   Height          =   1230
   Left            =   2400
   LinkTopic       =   "Form1"
   ScaleHeight     =   540
   ScaleWidth      =   4485
   Top             =   1215
   Width           =   4605
   Begin VB.CommandButton pbForm 
      Caption         =   "&Form"
      Height          =   375
      Left            =   2160
      TabIndex        =   1
      Top             =   120
      Width           =   1935
   End
   Begin VB.CommandButton pbReport 
      Caption         =   "&Report"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1935
   End
   Begin VB.Menu mnuAbout 
      Caption         =   "&About"
   End
End
Attribute VB_Name = "frmMSDNDemo"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim ThisAccess As New Access.Application
Dim MyReport As Access.Report
Dim MyForm As Access.Form
Private Sub Form_Load()
Test
Set ThisAccess = CreateObject("Access.Application")
With ThisAccess
        .OpenCurrentDatabase "E:\Office95\Access\samples\NorthWind.mdb"
End With

End Sub

Private Sub Form_Unload(Cancel As Integer)
ThisAccess.Quit Option:=Access.acExit
End Sub

Private Sub mnuAbout_Click()
MsgBox "Demo from Microsoft Developers Network Library" & vbCr & "Author: Ken Lassesen", VBA.vbInformation, App.Title
End Sub

Private Sub pbForm_Click()
With ThisAccess.DoCmd
    .OpenForm FormName:="Orders", _
         View:=Access.acNormal, _
         DataMode:=Access.acEdit, _
         WindowMode:=Access.acNormal
         'WARNING: "WindowMode:=Access.acDialog" will not return until user closes form!
End With
End Sub

Private Sub pbReport_Click()
With ThisAccess.DoCmd
    .OpenReport ReportName:="Invoice", _
        View:=Access.acPreview
End With
End Sub
Sub Test()
Dim ThisAccess As New Access.Application
'Set ThisAccess = CreateObject("Access.Application")
With ThisAccess
        .OpenCurrentDatabase "E:\Office95\Access\samples\NorthWind.mdb"
   With .DoCmd
        .OpenForm FormName:="Orders", _
         View:=Access.acNormal, _
         DataMode:=Access.acEdit, _
         WindowMode:=Access.acNormal
         'WARNING: "WindowMode:=Access.acDialog" will not return until user closes form!
       .OpenReport ReportName:="Invoice", _
        View:=Access.acPreview
   End With
End With

End Sub
