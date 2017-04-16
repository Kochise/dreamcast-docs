VERSION 4.00
Begin VB.Form frmSProc 
   Caption         =   "Stored Procedures"
   ClientHeight    =   3705
   ClientLeft      =   3630
   ClientTop       =   6645
   ClientWidth     =   8340
   Height          =   4065
   Left            =   3570
   LinkTopic       =   "Form1"
   ScaleHeight     =   3705
   ScaleWidth      =   8340
   Top             =   6345
   Visible         =   0   'False
   Width           =   8460
   Begin VB.TextBox txtOut 
      Height          =   675
      Left            =   300
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   4
      Top             =   2730
      Width           =   6630
   End
   Begin Threed.SSPanel pnlTop 
      Align           =   1  'Align Top
      Height          =   420
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   8340
      _Version        =   65536
      _ExtentX        =   14711
      _ExtentY        =   741
      _StockProps     =   15
      BackColor       =   12632256
      Begin VB.ComboBox cmbView 
         Height          =   315
         Left            =   555
         Style           =   2  'Dropdown List
         TabIndex        =   1
         Top             =   45
         Width           =   4065
      End
      Begin VB.Label lblSProc 
         Caption         =   "View:"
         Height          =   225
         Left            =   105
         TabIndex        =   2
         Top             =   105
         Width           =   450
      End
   End
   Begin ComctlLib.ImageList imgList 
      Left            =   6405
      Top             =   1560
      _Version        =   65536
      _ExtentX        =   1005
      _ExtentY        =   1005
      _StockProps     =   1
      BackColor       =   -2147483643
      ImageWidth      =   32
      ImageHeight     =   32
      NumImages       =   1
      i1              =   "Dmosproc.frx":0000
   End
   Begin ComctlLib.ListView lvSProc 
      Height          =   2130
      Left            =   120
      TabIndex        =   3
      Top             =   525
      Width           =   4125
      _Version        =   65536
      _ExtentX        =   7276
      _ExtentY        =   3757
      _StockProps     =   205
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      Appearance      =   1
      Arrange         =   1
      Icons           =   "imgList"
      SmallIcons      =   "imgList"
   End
End
Attribute VB_Name = "frmSProc"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Private Sub cmbView_Click()
lvSProc.View = cmbView.ListIndex
End Sub

Private Sub Form_Load()
With cmbView
    .AddItem "Icon"         ' 0
    .AddItem "SmallIcon"    ' 1
    .AddItem "List"         ' 2
    .AddItem "Report"       ' 3
    .ListIndex = 0
End With
End Sub

Private Sub Form_Resize()
On Error Resume Next
lvSProc.Left = 0
txtOut.Left = 0
lvSProc.Top = pnlTop.Height
lvSProc.Width = pnlTop.Width
txtOut.Width = pnlTop.Width
lvSProc.Height = (Me.ScaleHeight - pnlTop.Height) / 2
txtOut.Top = lvSProc.Top + lvSProc.Height
txtOut.Height = Me.ScaleHeight - pnlTop.Height - lvSProc.Height
End Sub
Private Sub lvSProcs_ColumnClick(ByVal ColumnHeader As ColumnHeader)
lvSProcs.SortKey = ColumnHeader.Index - 1
' Set Sorted to True to sort the list.
lvSProcs.Sorted = True
End Sub

Private Sub lvSProc_ItemClick(ByVal Item As ListItem)
Dim oSProc    As StoredProcedure
Set oSProc = oSQLServer.Databases(Item.Tag).StoredProcedures(CStr(Item))
txtOut = oSProc.Text
End Sub
