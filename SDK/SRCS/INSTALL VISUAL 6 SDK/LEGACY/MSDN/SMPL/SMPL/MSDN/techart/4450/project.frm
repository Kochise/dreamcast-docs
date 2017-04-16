VERSION 4.00
Begin VB.Form frmMSDNDemo 
   Caption         =   "MSProject OLE Server Demo"
   ClientHeight    =   1710
   ClientLeft      =   2400
   ClientTop       =   2820
   ClientWidth     =   4770
   Height          =   2400
   Left            =   2340
   LinkTopic       =   "Form1"
   ScaleHeight     =   1710
   ScaleWidth      =   4770
   Top             =   2190
   Width           =   4890
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   720
      TabIndex        =   1
      Text            =   "Text1"
      Top             =   0
      Width           =   3615
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Add Resource Above"
      Height          =   735
      Left            =   240
      TabIndex        =   0
      Top             =   600
      Width           =   4335
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   1560
      Top             =   960
   End
   Begin VB.Menu mnuAbout 
      Caption         =   "&About"
   End
End
Attribute VB_Name = "frmMSDNDemo"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim ThisMSProject As MSProject.Application
Dim ThisProject As MSProject.Project

Private Sub Command1_Click()
If Len(Text1.Text) > 0 Then
    With ThisMSProject
        .ActiveProject.Resources.Add Name:=Text1.Text
        .ViewApply Name:="Resource &Sheet"
    End With
End If
End Sub

Private Sub Form_Load()
Dim i As Integer
Dim MyTask As MSProject.Task
Set ThisMSProject = CreateObject("MSProject.Application")
With ThisMSProject
    .Visible = True
    .FileNew SummaryInfo:=False
    With .ActiveProject
        For i = 1 To 10
             Set MyTask = .Tasks.Add(Name:="Task" & i)
             With MyTask
                .Duration = i * 8 * 60 'Duration in Minutes
             End With
        Next i
    End With
End With
End Sub

Private Sub Form_Unload(Cancel As Integer)
    ThisMSProject.Quit
End Sub

Private Sub mnuAbout_Click()
MsgBox "Demo from Microsoft Developers Network Library" & vbCr & "Author: Ken Lassesen", VBA.vbInformation, App.Title
End Sub

