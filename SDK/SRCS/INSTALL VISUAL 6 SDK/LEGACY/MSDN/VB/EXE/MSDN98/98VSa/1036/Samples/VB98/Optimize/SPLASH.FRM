VERSION 5.00
Begin VB.Form Splash 
   AutoRedraw      =   -1  'True
   BorderStyle     =   0  'None
   ClientHeight    =   3450
   ClientLeft      =   1320
   ClientTop       =   1785
   ClientWidth     =   6855
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   Picture         =   "SPLASH.frx":0000
   ScaleHeight     =   3450
   ScaleWidth      =   6855
   WhatsThisHelp   =   -1  'True
   Begin VB.Label Label2 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "100%"
      ForeColor       =   &H80000008&
      Height          =   225
      Index           =   1
      Left            =   5955
      TabIndex        =   2
      Top             =   2925
      Width           =   465
   End
   Begin VB.Label Label2 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "0%"
      ForeColor       =   &H80000008&
      Height          =   225
      Index           =   0
      Left            =   1755
      TabIndex        =   1
      Top             =   2925
      Width           =   345
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "Chargement..."
      ForeColor       =   &H80000008&
      Height          =   240
      Left            =   3165
      TabIndex        =   0
      Top             =   2925
      Width           =   1815
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00FFFFFF&
      BorderWidth     =   2
      Index           =   1
      X1              =   6420
      X2              =   1755
      Y1              =   2835
      Y2              =   2835
   End
   Begin VB.Line Line2 
      BorderColor     =   &H00808080&
      BorderWidth     =   2
      Index           =   0
      X1              =   1755
      X2              =   1755
      Y1              =   2415
      Y2              =   2825
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00808080&
      BorderWidth     =   2
      Index           =   0
      X1              =   6420
      X2              =   1755
      Y1              =   2415
      Y2              =   2415
   End
   Begin VB.Shape rctStatusBar 
      BackColor       =   &H00800000&
      BackStyle       =   1  'Opaque
      BorderStyle     =   0  'Transparent
      Height          =   345
      Left            =   1800
      Top             =   2460
      Width           =   15
   End
   Begin VB.Line Line2 
      BorderColor     =   &H00FFFFFF&
      BorderWidth     =   2
      Index           =   1
      X1              =   6420
      X2              =   6420
      Y1              =   2430
      Y2              =   2820
   End
End
Attribute VB_Name = "Splash"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim iStatusBarWidth As Integer

Private Sub Form_Click()
    Unload Me

End Sub

Private Sub Form_Load()

  CenterMe Me

End Sub

