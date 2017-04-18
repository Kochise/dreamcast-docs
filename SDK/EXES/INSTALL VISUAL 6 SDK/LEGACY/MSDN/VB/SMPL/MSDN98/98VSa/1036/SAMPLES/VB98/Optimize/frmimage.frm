VERSION 5.00
Begin VB.Form frmImages 
   AutoRedraw      =   -1  'True
   Caption         =   "Contrôles de l'image"
   ClientHeight    =   3810
   ClientLeft      =   7035
   ClientTop       =   1755
   ClientWidth     =   4320
   ClipControls    =   0   'False
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
   LinkTopic       =   "Form5"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3810
   ScaleWidth      =   4320
   Tag             =   "Apparent"
   WhatsThisHelp   =   -1  'True
   Begin VB.CommandButton cmdExit 
      Caption         =   "&Quitter"
      Default         =   -1  'True
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1545
      TabIndex        =   0
      Top             =   3240
      Width           =   1215
   End
   Begin VB.Image Image1 
      Appearance      =   0  'Flat
      Height          =   480
      Index           =   9
      Left            =   840
      Picture         =   "frmimage.frx":0000
      Top             =   360
      Width           =   480
   End
   Begin VB.Image Image1 
      Appearance      =   0  'Flat
      Height          =   480
      Index           =   8
      Left            =   1680
      Picture         =   "frmimage.frx":030A
      Top             =   600
      Width           =   480
   End
   Begin VB.Image Image1 
      Appearance      =   0  'Flat
      Height          =   480
      Index           =   7
      Left            =   330
      Picture         =   "frmimage.frx":0614
      Top             =   2040
      Width           =   480
   End
   Begin VB.Image Image1 
      Appearance      =   0  'Flat
      Height          =   480
      Index           =   6
      Left            =   600
      Picture         =   "frmimage.frx":091E
      Top             =   1320
      Width           =   480
   End
   Begin VB.Image Image1 
      Appearance      =   0  'Flat
      Height          =   480
      Index           =   5
      Left            =   1470
      Picture         =   "frmimage.frx":0C28
      Top             =   1740
      Width           =   480
   End
   Begin VB.Image Image1 
      Appearance      =   0  'Flat
      Height          =   480
      Index           =   4
      Left            =   2235
      Picture         =   "frmimage.frx":0F32
      Top             =   1245
      Width           =   480
   End
   Begin VB.Image Image1 
      Appearance      =   0  'Flat
      Height          =   480
      Index           =   3
      Left            =   3075
      Picture         =   "frmimage.frx":123C
      Top             =   450
      Width           =   480
   End
   Begin VB.Image Image1 
      Appearance      =   0  'Flat
      Height          =   480
      Index           =   2
      Left            =   1200
      Picture         =   "frmimage.frx":1546
      Top             =   2520
      Width           =   480
   End
   Begin VB.Image Image1 
      Appearance      =   0  'Flat
      Height          =   480
      Index           =   1
      Left            =   2400
      Picture         =   "frmimage.frx":1850
      Top             =   2520
      Width           =   480
   End
   Begin VB.Image Image1 
      Appearance      =   0  'Flat
      Height          =   480
      Index           =   0
      Left            =   3120
      Picture         =   "frmimage.frx":1B5A
      Top             =   1680
      Width           =   480
   End
End
Attribute VB_Name = "frmImages"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_TemplateDerived = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub cmdExit_Click()
  Unload Me

End Sub

Private Sub Form_Load()
  PosForm Me
  Me.Show
  ScrambleDisks

End Sub

Private Sub ScrambleDisks()
  iMaxWidth = Me.ScaleWidth - Image1(0).Width + 1
  iMaxHeight = Me.ScaleWidth - Image1(0).Height + 1

  For iCounter = 1 To 5
    For iDiskImage = 0 To 9
      Image1(iDiskImage).Move Int(iMaxWidth * Rnd), Int(iMaxHeight * Rnd)
    Next iDiskImage
  Next iCounter

End Sub

