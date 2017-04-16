VERSION 5.00
Begin VB.Form frmImages 
   Caption         =   "Images"
   ClientHeight    =   3465
   ClientLeft      =   1635
   ClientTop       =   1740
   ClientWidth     =   4725
   LinkTopic       =   "Form1"
   ScaleHeight     =   3465
   ScaleWidth      =   4725
   Begin VB.CommandButton cmdClose 
      Cancel          =   -1  'True
      Caption         =   "&Fermer"
      Height          =   495
      Left            =   3000
      MaskColor       =   &H00000000&
      TabIndex        =   1
      Top             =   2280
      Width           =   1095
   End
   Begin VB.PictureBox picStatus 
      Align           =   2  'Align Bottom
      AutoSize        =   -1  'True
      FillColor       =   &H000080FF&
      Height          =   315
      Left            =   0
      ScaleHeight     =   255
      ScaleWidth      =   4665
      TabIndex        =   0
      TabStop         =   0   'False
      Top             =   3150
      Width           =   4725
   End
   Begin VB.Label lblEnter 
      Caption         =   "Cliquez sur une image et regardez ce qui se passe."
      Height          =   615
      Left            =   720
      TabIndex        =   2
      Top             =   2280
      Width           =   1575
   End
   Begin VB.Shape shpCard 
      BorderColor     =   &H00000000&
      BorderWidth     =   2
      Height          =   735
      Left            =   120
      Shape           =   4  'Rounded Rectangle
      Top             =   600
      Width           =   495
   End
   Begin VB.Image imgSpade 
      Height          =   480
      Left            =   3480
      Picture         =   "images.frx":0000
      Top             =   720
      Width           =   480
   End
   Begin VB.Image imgHeart 
      Height          =   480
      Left            =   2520
      Picture         =   "images.frx":0442
      Top             =   720
      Width           =   480
   End
   Begin VB.Image imgDiamond 
      Height          =   480
      Left            =   1560
      Picture         =   "images.frx":0884
      Top             =   720
      Width           =   480
   End
   Begin VB.Image imgClub 
      Height          =   480
      Left            =   720
      Picture         =   "images.frx":0CC6
      Top             =   720
      Width           =   480
   End
End
Attribute VB_Name = "frmImages"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdClose_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    shpCard.Left = -500
End Sub

Private Sub imgClub_Click()
    shpCard.Left = imgClub.Left
    picStatus.Cls
    picStatus.Print " Couleur sélectionnée: Trèfle"
End Sub


Private Sub imgDiamond_Click()
    shpCard.Left = imgDiamond.Left
    picStatus.Cls
    picStatus.Print " Couleur sélectionnée: Carreau"
End Sub


Private Sub imgHeart_Click()
    shpCard.Left = imgHeart.Left
    picStatus.Cls
    picStatus.Print " Couleur sélectionnée: Coeur"
End Sub


Private Sub imgSpade_Click()
    shpCard.Left = imgSpade.Left
    picStatus.Cls
    picStatus.Print " Couleur sélectionnée: Pique"
End Sub


