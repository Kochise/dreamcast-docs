VERSION 4.00
Begin VB.Form frmViewer 
   Caption         =   "Viewer"
   ClientHeight    =   3030
   ClientLeft      =   1305
   ClientTop       =   4815
   ClientWidth     =   4140
   Height          =   3435
   Left            =   1245
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   3030
   ScaleWidth      =   4140
   Top             =   4470
   Width           =   4260
   Begin VB.OLE oleExcel 
      Class           =   "Excel.Sheet.5"
      Height          =   2400
      Left            =   270
      OleObjectBlob   =   "frmViewer.frx":0000
      SourceDoc       =   "C:\MSPJ\Prototype\REPORT1.xls"
      TabIndex        =   0
      Top             =   165
      Width           =   3285
   End
End
Attribute VB_Name = "frmViewer"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit



Private Sub ResizeAll()

    'When we resize we need to resize the linked Excel viewer
    oleExcel.Top = 0
    oleExcel.Left = 0
    
    oleExcel.Height = Me.ScaleHeight
    oleExcel.Width = Me.ScaleWidth

End Sub

Public Sub SourceDoc(sSourceDoc As String)

    'This public sub is so the request form can set our document source
    oleExcel.CreateLink App.Path & "\" & sSourceDoc
    
End Sub


Private Sub Form_Load()

    'Initial resize
    ResizeAll

End Sub



Private Sub Form_Resize()

    'Resize on resize
    ResizeAll
    
End Sub


Private Sub oleExcel_Updated(Code As Integer)

End Sub
