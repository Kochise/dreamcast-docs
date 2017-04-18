VERSION 4.00
Begin VB.Form frmMSDNDemo 
   Caption         =   "MicrosoftOffice OLE Server Demo"
   ClientHeight    =   3210
   ClientLeft      =   1065
   ClientTop       =   690
   ClientWidth     =   3315
   Height          =   3900
   Left            =   1005
   LinkTopic       =   "Form1"
   ScaleHeight     =   3210
   ScaleWidth      =   3315
   Top             =   60
   Width           =   3435
   Begin VB.ComboBox Combo1 
      Height          =   315
      Left            =   0
      Style           =   2  'Dropdown List
      TabIndex        =   2
      Top             =   0
      Width           =   3255
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Show Document Properties"
      Height          =   255
      Left            =   0
      TabIndex        =   1
      Top             =   360
      Width           =   3255
   End
   Begin VB.ListBox List1 
      Height          =   2400
      Left            =   0
      TabIndex        =   0
      Top             =   720
      Width           =   3255
   End
   Begin VB.Menu mnuAbout 
      Caption         =   "&About"
   End
End
Attribute VB_Name = "frmMSDNDemo"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim ThisObject As Object
Const OB$ = "Office.Binder"
Const EA$ = "Excel.Application"
Const MA$ = "MSProject.Application"


Private Sub Combo1_Click()
Select Case Combo1
Case OB$
    Set ThisObject = CreateObject(OB$)
    ThisObject.Visible = True
Case EA$
    Set AppObject = CreateObject(EA$)
    AppObject.Workbooks.Add
    Set ThisObject = AppObject.Workbooks(1)
    AppObject.Visible = True
Case MA$
    Set AppObject = CreateObject(MA$)
    AppObject.Visible = True
    AppObject.FileNew
    Set ThisObject = AppObject.Projects(1)
End Select
End Sub

Private Sub Command1_Click()
List1.Clear
List1.AddItem "Build in Properties"
On Error GoTo BadValue_err

For Each Prop In ThisObject.BuiltinDocumentProperties
    With Prop
        AName$ = .Name
        List1.AddItem .Name & ":= " & .Value
    End With
Next
List1.AddItem "Custom in Properties"
For Each Prop In ThisObject.CustomDocumentProperties
    With Prop
        AName$ = .Name
        List1.AddItem .Name & ":= " & .Value
    End With
Next
On Error GoTo 0
Exit Sub
BadValue_err:
List1.AddItem AName$ & ":= #NULL#"
Resume Next
End Sub

Private Sub Form_Load()
Combo1.AddItem OB
Combo1.AddItem EA
Combo1.AddItem MA
End Sub
Private Sub mnuAbout_Click()
MsgBox "Demo from Microsoft Developers Network Library" & vbCr & "Author: Ken Lassesen", VBA.vbInformation, App.Title
End Sub

Sub AddInfoTo(AnObject As MicrosoftOffice.DocumentProperties)
End Sub
