VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "ComDlg32.OCX"
Begin VB.Form frmBookSales 
   Caption         =   "Serveur Ventes de livres"
   ClientHeight    =   2265
   ClientLeft      =   -195
   ClientTop       =   345
   ClientWidth     =   5340
   ClipControls    =   0   'False
   Icon            =   "Book_svr.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2265
   ScaleWidth      =   5340
   WhatsThisHelp   =   -1  'True
   Begin MSComDlg.CommonDialog dlgFindDB 
      Left            =   4200
      Top             =   75
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      FontSize        =   2.54052e-29
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Nombre d'instances:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   135
      TabIndex        =   5
      Top             =   165
      Width           =   1785
   End
   Begin VB.Label lblInstanceCount 
      BorderStyle     =   1  'Fixed Single
      Height          =   285
      Left            =   1995
      TabIndex        =   4
      Top             =   120
      Width           =   750
   End
   Begin VB.Label lblStatus 
      BorderStyle     =   1  'Fixed Single
      Height          =   765
      Index           =   1
      Left            =   1995
      TabIndex        =   3
      Top             =   1380
      Width           =   3255
      WordWrap        =   -1  'True
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Réponse locale:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Index           =   1
      Left            =   135
      TabIndex        =   2
      Top             =   1425
      Width           =   1470
   End
   Begin VB.Label lblStatus 
      BorderStyle     =   1  'Fixed Single
      Height          =   765
      Index           =   0
      Left            =   1995
      TabIndex        =   1
      Top             =   510
      Width           =   3255
      WordWrap        =   -1  'True
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Demande à distance:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   525
      Width           =   1815
   End
End
Attribute VB_Name = "frmBookSales"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

