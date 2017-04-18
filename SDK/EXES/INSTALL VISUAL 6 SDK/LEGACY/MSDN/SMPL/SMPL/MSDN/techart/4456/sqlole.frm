VERSION 4.00
Begin VB.Form frmMSDNDemo 
   Caption         =   "SQLOLE OLE Server Demo"
   ClientHeight    =   1770
   ClientLeft      =   2460
   ClientTop       =   1845
   ClientWidth     =   4485
   Height          =   2460
   Left            =   2400
   LinkTopic       =   "Form1"
   ScaleHeight     =   1770
   ScaleWidth      =   4485
   Top             =   1215
   Width           =   4605
   Begin VB.CommandButton Command1 
      Caption         =   "&Refresh"
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   1320
      Width           =   1815
   End
   Begin VB.ListBox List1 
      Height          =   1230
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   4215
   End
   Begin VB.Menu mnuAbout 
      Caption         =   "&About"
   End
End
Attribute VB_Name = "frmMSDNDemo"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim ThisSQLOLE As New SQLOLE.Application
Dim ThisSQLServer As SQLOLE.SQLServer
Dim x As Database
Const ServerName$ = "ErlangB"

Private Sub Command1_Click()
Dim objSQLdb As SQLOLE.Database
List1.Clear
For Each objSQLdb In ThisSQLServer.Databases
    With objSQLdb
       If .Status <> SQLOLE.SQLOLE_DBSTATUS_TYPE.SQLOLEDBStat_Inaccessible Then
          List1.AddItem .Name & "[Size=" & Format$(.Size, "0.0") & " Mbytes, " _
          & " Used= " & Format$(.DataSpaceUsage, "0.0") _
          & ", Users=" & Format(.Users.Count, "0") & "]"
       End If
    End With
Next

End Sub

Private Sub Form_Load()
Set ThisSQLServer = CreateObject("SQLOLE.SQLSERVER")
ThisSQLServer.Connect ServerName:=ServerName$, Login:="sa", Password:=Null
Command1_Click
End Sub

Private Sub Form_Unload(Cancel As Integer)
  ThisSQLServer.DisConnect

End Sub

Private Sub mnuAbout_Click()
MsgBox "Demo from Microsoft Developers Network Library" & vbCr & "Author: Ken Lassesen", VBA.vbInformation, App.Title
End Sub

