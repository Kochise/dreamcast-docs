VERSION 4.00
Begin VB.Form frmDragDrop 
   Caption         =   "MSJ Drag 'N' Drop Demo"
   ClientHeight    =   5895
   ClientLeft      =   1575
   ClientTop       =   2025
   ClientWidth     =   6690
   Height          =   6315
   Left            =   1515
   LinkTopic       =   "Form1"
   ScaleHeight     =   5895
   ScaleWidth      =   6690
   Top             =   1665
   Width           =   6810
   Begin VB.PictureBox Picture1 
      AutoSize        =   -1  'True
      Height          =   4335
      Left            =   120
      ScaleHeight     =   4275
      ScaleWidth      =   6435
      TabIndex        =   0
      Top             =   1440
      Width           =   6495
      Begin MSJDRAGLib.MSJDrag MSJDrag1 
         Height          =   855
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Width           =   1215
         _Version        =   65536
         _ExtentX        =   2143
         _ExtentY        =   1508
         _StockProps     =   0
      End
   End
   Begin VB.Label This 
      Caption         =   $"DragDrop.frx":0000
      Height          =   1215
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   6375
   End
End
Attribute VB_Name = "frmDragDrop"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Private Sub MSJDrag1_FileDrop(ByVal hWnd As Long, ByVal FName As String)
    Picture1.Picture = LoadPicture(FName)
End Sub

