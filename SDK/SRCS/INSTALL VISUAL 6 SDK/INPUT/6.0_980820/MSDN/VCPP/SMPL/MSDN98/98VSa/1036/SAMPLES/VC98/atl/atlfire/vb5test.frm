VERSION 5.00
Object = "{479B29E1-9A2C-11D0-B696-00A0C903487A}#1.0#0"; "ATLFire.dll"
Begin VB.Form Form1 
   BackColor       =   &H8000000B&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Form1"
   ClientHeight    =   3816
   ClientLeft      =   48
   ClientTop       =   336
   ClientWidth     =   4572
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
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3816
   ScaleWidth      =   4572
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin ATLFIRELibCtl.FireTabCtrl FireTabCtrl2 
      Height          =   3012
      Left            =   360
      TabIndex        =   0
      Top             =   480
      Width           =   3852
      FireDecay       =   2
      FireFlammability=   385
      FireMaxHeat     =   223
      FireSpreadRate  =   20
      FireSize        =   260
      RenderSmoothness=   1
      RenderDistribution=   1
      RenderChaos     =   50
      StartTab        =   0
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
