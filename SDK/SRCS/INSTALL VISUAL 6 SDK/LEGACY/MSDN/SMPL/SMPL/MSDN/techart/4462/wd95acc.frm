VERSION 4.00
Begin VB.Form frmMSDNDemo 
   Caption         =   "Word95 Access OLE Server Demo"
   ClientHeight    =   525
   ClientLeft      =   2460
   ClientTop       =   1845
   ClientWidth     =   4020
   Height          =   1215
   Left            =   2400
   LinkTopic       =   "Form1"
   ScaleHeight     =   525
   ScaleWidth      =   4020
   Top             =   1215
   Width           =   4140
   Begin VB.CommandButton Command1 
      Caption         =   "&Merge data"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   1455
   End
   Begin VB.Menu mnuAbout 
      Caption         =   "&About"
   End
End
Attribute VB_Name = "frmMSDNDemo"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim ThisWord As wORD95aCC.Word95Access

Private Sub Command1_Click()
With ThisWord
    .MailMergeOpenDataSource Name:="E:\Office95\ACCESS\Samples\Northwind.mdb", _
        LinkToSource:=1, _
        Connection:="TABLE Customers", _
        SQLStatement:="SELECT * FROM [Customers]"

    .MailMerge CheckErrors:=1, _
        Destination:=0, _
        MergeRecords:=1, _
        From:="1", _
        To:="10", _
        MailMerge:=1
End With
End Sub

Private Sub Form_Load()
Set ThisWord = CreateObject("Word.Basic")
ThisWord.FileOpen Name:=App.Path & "\MyMerge.Doc"
ThisWord.AppShow
End Sub
Private Sub mnuAbout_Click()
MsgBox "Demo from Microsoft Developers Network Library" & vbCr & "Author: Ken Lassesen", VBA.vbInformation, App.Title
End Sub
