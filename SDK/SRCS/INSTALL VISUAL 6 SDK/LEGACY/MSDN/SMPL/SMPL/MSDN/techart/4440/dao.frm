VERSION 4.00
Begin VB.Form frmMSDNDemo 
   Caption         =   "DAO OLE Server Demo"
   ClientHeight    =   1515
   ClientLeft      =   2460
   ClientTop       =   1845
   ClientWidth     =   4485
   Height          =   2205
   Left            =   2400
   LinkTopic       =   "Form1"
   ScaleHeight     =   1515
   ScaleWidth      =   4485
   Top             =   1215
   Width           =   4605
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
Dim appDAO As DAO.DBEngine
Dim MyDB As DAO.Database
Private Sub Form_Load()
If Len(Dir("MSDN1.MDB")) > 0 Then Kill "MSDN1.MDB"
DoEvents

    Set MyDB = CreateDatabase(Name:="MSDN.MDB", Connect:=DAO.Constants.dbLangNorwDan, Option:=DAO.Constants.dbEncrypt)
With MyDB
    .Execute _
        Query:="Select 'Dr.Gui' As Name, 'MSDN@Microsoft' As Email, #1/1/52# as Birthdate into MyTables"
    For i% = 0 To .TableDefs.Count - 1
        List1.AddItem .TableDefs(i%).Name
        For j% = 0 To .TableDefs(i%).Fields.Count - 1
            List1.AddItem "  Field:" & .TableDefs(i%).Fields(j%).Name
        Next j%
    Next i%
End With
End Sub
Private Sub mnuAbout_Click()
MsgBox "Demo from Microsoft Developers Network Library" & vbCr & "Author: Ken Lassesen", VBA.vbInformation, App.Title
End Sub

