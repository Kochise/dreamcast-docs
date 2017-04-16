VERSION 4.00
Begin VB.Form frmMSDNDemo 
   Caption         =   "RDO OLE Server Demo"
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
Private Sub Form_Load()
On Error GoTo rDO_Error
Dim DB As rdo.rdoConnection
Dim RS As rdo.rdoResultset

Set DB = rdoEngine.rdoEnvironments(0).OpenConnection( _
    dsName:="Pubs", _
    Connect:="ODBC;Userid=sa;Password=;")
Set RS = DB.OpenResultset( _
    Name:="Select * from Authors;")
While Not RS.EOF
    List1.AddItem (RS(0))
    RS.MoveNext
Wend
RS.Close

rDO_Exit:
On Error GoTo 0
Exit Sub

rDO_Error: 'Display message and exit procedure
MsgBox Error$, vbExclamation, "Error:" & Err
Resume rDO_Exit

End Sub
Private Sub mnuAbout_Click()
MsgBox "Demo from Microsoft Developers Network Library" & vbCr & "Author: Ken Lassesen", VBA.vbInformation, App.Title
End Sub

