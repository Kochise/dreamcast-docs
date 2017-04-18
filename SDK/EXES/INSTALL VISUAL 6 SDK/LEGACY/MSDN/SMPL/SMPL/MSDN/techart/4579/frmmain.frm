VERSION 4.00
Begin VB.Form frmMain 
   Caption         =   "Access Report Tester"
   ClientHeight    =   4335
   ClientLeft      =   1395
   ClientTop       =   2040
   ClientWidth     =   2910
   Height          =   4695
   Left            =   1335
   LinkTopic       =   "Form1"
   ScaleHeight     =   4335
   ScaleWidth      =   2910
   Top             =   1740
   Width           =   3030
   Begin VB.TextBox txtFName 
      Height          =   285
      Left            =   90
      TabIndex        =   3
      Top             =   300
      Width           =   2745
   End
   Begin VB.ListBox lstReps 
      Height          =   2985
      Left            =   90
      Sorted          =   -1  'True
      TabIndex        =   1
      Top             =   1245
      Width           =   2745
   End
   Begin VB.CommandButton btDoMe 
      Caption         =   "Refresh Reports"
      Height          =   465
      Left            =   90
      TabIndex        =   0
      Top             =   690
      Width           =   2745
   End
   Begin VB.Label lblMain 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Database File Name"
      Height          =   195
      Left            =   90
      TabIndex        =   2
      Top             =   60
      Width           =   1440
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Public RepGen As ReportGen.AccessReport
Public repMe As Object

Private Sub btDoMe_Click()
Dim vList As Variant
Dim iIndx As Integer

If Len(Trim$(txtFName)) = 0 Then Exit Sub
Set RepGen = CreateObject("ReportGen.AccessReport")

If Not (RepGen.InitializeAccess(txtFName)) Then
    MsgBox "There was a problem initializing the database."
    Exit Sub
End If

vList = RepGen.ReportList()

lstReps.Visible = False
For iIndx = LBound(vList) To UBound(vList)
    lstReps.AddItem Trim$(vList(iIndx))
Next iIndx
lstReps.Visible = True
End Sub

Private Sub Form_Unload(Cancel As Integer)
On Error Resume Next
RepGen.TerminateAccess
Set RepGen = Nothing
End Sub

Private Sub lstReps_DblClick()
Set repMe = RepGen.GetReport(lstReps.List(lstReps.ListIndex))
'repMe is valid report, so you could do what you want with it
'For now, we request the server to print it out.
RepGen.PrintReport True
End Sub
