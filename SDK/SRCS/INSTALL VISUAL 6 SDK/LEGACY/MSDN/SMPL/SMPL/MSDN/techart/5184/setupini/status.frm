VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.1#0"; "COMCTL32.OCX"
Begin VB.Form Status 
   AutoRedraw      =   -1  'True
   Caption         =   "Install Status"
   ClientHeight    =   2196
   ClientLeft      =   2256
   ClientTop       =   4200
   ClientWidth     =   7176
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2196
   ScaleWidth      =   7176
   Begin ComctlLib.ProgressBar ProgressBar1 
      Height          =   495
      Left            =   360
      TabIndex        =   0
      Top             =   360
      Width           =   6375
      _ExtentX        =   11240
      _ExtentY        =   868
      _Version        =   327680
      BorderStyle     =   1
      Appearance      =   1
      MouseIcon       =   "Status.frx":0000
   End
   Begin VB.Label StatusText 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   480
      TabIndex        =   1
      Top             =   1200
      Width           =   5415
   End
End
Attribute VB_Name = "Status"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

