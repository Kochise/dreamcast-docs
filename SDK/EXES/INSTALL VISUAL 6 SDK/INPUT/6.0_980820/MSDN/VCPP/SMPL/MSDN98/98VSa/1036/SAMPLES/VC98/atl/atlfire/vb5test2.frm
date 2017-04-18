VERSION 5.00
Object = "{479B29E1-9A2C-11D0-B696-00A0C903487A}#1.0#0"; "ATLFire.dll"
Begin VB.Form Form1 
   BackColor       =   &H80000008&
   Caption         =   "Form1"
   ClientHeight    =   6300
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9555
   BeginProperty Font 
      Name            =   "Script"
      Size            =   12
      Charset         =   255
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   ScaleHeight     =   6300
   ScaleWidth      =   9555
   StartUpPosition =   2  'CenterScreen
   Begin ATLFIRELibCtl.FireTabCtrl FireTabCtrl3 
      Height          =   2895
      Left            =   2640
      TabIndex        =   2
      Top             =   3240
      Width           =   4455
   End
   Begin ATLFIRELibCtl.FireTabCtrl FireTabCtrl2 
      Height          =   2895
      Left            =   5040
      TabIndex        =   1
      Top             =   120
      Width           =   4335
   End
   Begin ATLFIRELibCtl.FireTabCtrl FireTabCtrl1 
      Height          =   2895
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   4455
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
