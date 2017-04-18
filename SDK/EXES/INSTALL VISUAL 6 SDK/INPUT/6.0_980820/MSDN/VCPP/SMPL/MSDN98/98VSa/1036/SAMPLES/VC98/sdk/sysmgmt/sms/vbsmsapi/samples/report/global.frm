VERSION 4.00
Begin VB.Form frmGlobal 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Global Utilities"
   ClientHeight    =   1050
   ClientLeft      =   3015
   ClientTop       =   4380
   ClientWidth     =   3480
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   1
      weight          =   700
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   Height          =   1455
   Left            =   2955
   LinkTopic       =   "Form1"
   ScaleHeight     =   1050
   ScaleWidth      =   3480
   Top             =   4035
   Visible         =   0   'False
   Width           =   3600
   Begin Crystal.CrystalReport CrystalReport 
      Left            =   1800
      Top             =   300
      _ExtentX        =   741
      _ExtentY        =   741
      _StockProps     =   0
      ReportFileName  =   ""
      Destination     =   0
      WindowLeft      =   100
      WindowTop       =   100
      WindowWidth     =   480
      WindowHeight    =   300
      WindowTitle     =   ""
      WindowBorderStyle=   2
      WindowControlBox=   -1  'True
      WindowMaxButton =   -1  'True
      WindowMinButton =   -1  'True
      CopiesToPrinter =   1
      PrintFileName   =   ""
      PrintFileType   =   2
      SelectionFormula=   ""
      GroupSelectionFormula=   ""
      Connect         =   ""
      UserName        =   ""
      ReportSource    =   -4083
      BoundReportHeading=   ""
      BoundReportFooter=   -1  'True
   End
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   1020
      Top             =   300
      _Version        =   65536
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
End
Attribute VB_Name = "frmGlobal"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

