VERSION 4.00
Begin VB.Form frmMSDNDemo 
   Caption         =   "Binder OLE Server Demo"
   ClientHeight    =   1395
   ClientLeft      =   1335
   ClientTop       =   1710
   ClientWidth     =   3945
   Height          =   2085
   Left            =   1275
   LinkTopic       =   "Form1"
   ScaleHeight     =   1395
   ScaleWidth      =   3945
   Top             =   1080
   Width           =   4065
   Begin VB.CommandButton pbAdd 
      Caption         =   "Word.Document"
      Height          =   375
      Index           =   4
      Left            =   120
      TabIndex        =   4
      Top             =   960
      Width           =   1815
   End
   Begin VB.CommandButton pbAdd 
      Caption         =   "PowerPoint.Slide"
      Height          =   375
      Index           =   3
      Left            =   2040
      TabIndex        =   3
      Top             =   480
      Width           =   1815
   End
   Begin VB.CommandButton pbAdd 
      Caption         =   "PowerPoint.Show"
      Height          =   375
      Index           =   2
      Left            =   120
      TabIndex        =   2
      Top             =   480
      Width           =   1815
   End
   Begin VB.CommandButton pbAdd 
      Caption         =   "Excel.Sheet"
      Height          =   375
      Index           =   1
      Left            =   2040
      TabIndex        =   1
      Top             =   0
      Width           =   1815
   End
   Begin VB.CommandButton pbAdd 
      Caption         =   "Excel.Chart"
      Height          =   375
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   1815
   End
   Begin VB.Menu mnuAbout 
      Caption         =   "&About"
   End
End
Attribute VB_Name = "frmMSDNDemo"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim ThisBinder As OfficeBinder.Binder

Private Sub Form_Load()
    Set ThisBinder = CreateObject("Office.Binder")
    ThisBinder.Visible = True
End Sub

Private Sub Form_Unload(Cancel As Integer)
ThisBinder.SaveAs filename:="MSDN.obd", SaveOption:=OfficeBinder.Constants.bindOverwriteExisting
Set ThisBinder = Nothing
End Sub

Private Sub mnuAbout_Click()
MsgBox "Demo from Microsoft Developers Network Library" & vbCr & "Author: Ken Lassesen", VBA.vbInformation, App.Title
End Sub

Private Sub pbAdd_Click(Index As Integer)
Enabled = False 'It can take a few seconds to load.
With ThisBinder
    .Sections.Add Type:=pbAdd(Index).Caption
End With
Enabled = True
End Sub
