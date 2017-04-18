VERSION 4.00
Begin VB.Form frmAddInMgr 
   Caption         =   "Add-In Manager"
   ClientHeight    =   5850
   ClientLeft      =   4740
   ClientTop       =   5145
   ClientWidth     =   8505
   ClipControls    =   0   'False
   ControlBox      =   0   'False
   Height          =   6270
   Left            =   4680
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5850
   ScaleWidth      =   8505
   Top             =   4785
   Width           =   8625
   Begin VB.Frame Frame2 
      Caption         =   "Project Contents"
      Height          =   3375
      Left            =   120
      TabIndex        =   5
      Top             =   1920
      Width           =   2415
      Begin VB.ListBox FileList 
         Height          =   2985
         Left            =   120
         MultiSelect     =   2  'Extended
         TabIndex        =   6
         Top             =   240
         Width           =   2175
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Active Add-Ins"
      Height          =   1695
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2415
      Begin VB.CheckBox Check4 
         Caption         =   "Shared Code Library"
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Top             =   1320
         Width           =   1815
      End
      Begin VB.CheckBox Check3 
         Caption         =   "Sub-Classing "
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   960
         Width           =   1335
      End
      Begin VB.CheckBox Check2 
         Caption         =   "Record to UDT Generator"
         Height          =   255
         Left            =   120
         TabIndex        =   2
         Top             =   600
         Width           =   2175
      End
      Begin VB.CheckBox Check1 
         Caption         =   "Menu Generator"
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Width           =   1695
      End
   End
   Begin TabDlg.SSTab SSTab1 
      Height          =   5055
      Left            =   2640
      TabIndex        =   7
      Top             =   240
      Width           =   3855
      _Version        =   65536
      _ExtentX        =   6800
      _ExtentY        =   8916
      _StockProps     =   15
      Caption         =   "Tab 1"
      TabsPerRow      =   3
      Tab             =   1
      TabOrientation  =   0
      Tabs            =   3
      Style           =   0
      TabMaxWidth     =   0
      TabHeight       =   529
      Tab(0).ControlCount=   2
      Tab(0).ControlEnabled=   0   'False
      Tab(0).Control(0)=   "pbAddMenu"
      Tab(0).Control(1)=   "TreeView1"
      Tab(1).ControlCount=   2
      Tab(1).ControlEnabled=   -1  'True
      Tab(1).Control(0)=   "Command1"
      Tab(1).Control(1)=   "List1"
      Tab(2).ControlCount=   0
      Tab(2).ControlEnabled=   0   'False
      Begin VB.ListBox List1 
         Height          =   3570
         Left            =   240
         TabIndex        =   9
         Top             =   1200
         Width           =   3375
      End
      Begin VB.CommandButton Command1 
         Caption         =   "&Apply to Forms"
         Height          =   495
         Left            =   240
         TabIndex        =   8
         Top             =   600
         Width           =   2895
      End
   End
End
Attribute VB_Name = "frmAddInMgr"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
