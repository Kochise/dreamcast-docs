VERSION 5.00
Object = "*\A..\src\concon.vbp"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   5910
   ClientLeft      =   60
   ClientTop       =   300
   ClientWidth     =   10425
   LinkTopic       =   "Form1"
   ScaleHeight     =   5910
   ScaleWidth      =   10425
   StartUpPosition =   3  'Windows Default
   Begin ConCon.Patron Patron3 
      Height          =   1905
      Left            =   6510
      TabIndex        =   4
      Top             =   3945
      Width           =   3855
      _ExtentX        =   6800
      _ExtentY        =   3360
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      AccountNumber   =   "BNK1ACCT10"
   End
   Begin ConCon.Lender Lender1 
      Height          =   3135
      Left            =   900
      TabIndex        =   3
      Top             =   2640
      Width           =   3900
      _ExtentX        =   6879
      _ExtentY        =   5530
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      AccountNumber   =   "BNK1ACCT4"
   End
   Begin ConCon.Patron Patron2 
      Height          =   1905
      Left            =   6510
      TabIndex        =   2
      Top             =   2025
      Width           =   3855
      _ExtentX        =   6800
      _ExtentY        =   3360
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      AccountNumber   =   "BNK1ACCT9"
   End
   Begin ConCon.Patron Patron1 
      Height          =   1905
      Left            =   6510
      TabIndex        =   1
      Top             =   90
      Width           =   3855
      _ExtentX        =   6800
      _ExtentY        =   3360
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      AccountNumber   =   "BNK1ACCT6"
   End
   Begin ConCon.Bank Bank1 
      Height          =   2490
      Left            =   45
      TabIndex        =   0
      Top             =   30
      Width           =   6645
      _ExtentX        =   11165
      _ExtentY        =   4392
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      DataSource      =   "\\rainmaker\d$\banking.mdb"
      BankCode        =   "23-98-12"
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
If Not Bank1.Init() Then MsgBox "Didn't Work"
Set Lender1.Bank = Bank1
Lender1.Refresh
Set Patron1.Bank = Bank1
Set Patron1.Lender = Lender1
Patron1.Refresh
Set Patron2.Bank = Bank1
Set Patron2.Lender = Lender1
Patron2.Refresh
Set Patron3.Bank = Bank1
Set Patron3.Lender = Lender1
Patron3.Refresh
End Sub
