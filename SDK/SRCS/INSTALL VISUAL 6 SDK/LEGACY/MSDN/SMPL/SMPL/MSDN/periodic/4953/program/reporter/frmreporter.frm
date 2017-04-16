VERSION 4.00
Begin VB.MDIForm frmReporter 
   AutoShowChildren=   0   'False
   BackColor       =   &H00808000&
   Caption         =   "Reporter"
   ClientHeight    =   6165
   ClientLeft      =   6840
   ClientTop       =   2745
   ClientWidth     =   7980
   Height          =   6570
   Left            =   6780
   LinkTopic       =   "MDIForm1"
   Top             =   2400
   Width           =   8100
   Begin ComctlLib.ImageList imlMainToolBar 
      Left            =   120
      Top             =   5460
      _Version        =   65536
      _ExtentX        =   1005
      _ExtentY        =   1005
      _StockProps     =   1
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      NumImages       =   1
      i1              =   "frmReporter.frx":0000
   End
   Begin ComctlLib.Toolbar Toolbar1 
      Align           =   1  'Align Top
      Height          =   390
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   7980
      _Version        =   65536
      _ExtentX        =   14076
      _ExtentY        =   688
      _StockProps     =   96
      ImageList       =   "imlMainToolBar"
      NumButtons      =   1
      i1              =   "frmReporter.frx":01B7
      AlignSet        =   -1  'True
   End
End
Attribute VB_Name = "frmReporter"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Private Sub Toolbar1_ButtonClick(ByVal Button As Button)

    Select Case Button.Index
        Case 1
            Load frmRequestWizard
            CenterChild Me, frmRequestWizard
            frmRequestWizard.Show
    End Select
    
End Sub


