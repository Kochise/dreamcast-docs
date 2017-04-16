VERSION 5.00
Begin VB.Form frmButton 
   Caption         =   "Boutons de test"
   ClientHeight    =   2790
   ClientLeft      =   1815
   ClientTop       =   2205
   ClientWidth     =   4770
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form3"
   ScaleHeight     =   2790
   ScaleWidth      =   4770
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Fermer"
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
      Left            =   3000
      TabIndex        =   1
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CommandButton cmdChange 
      Caption         =   "Change &Signal"
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
      Left            =   600
      TabIndex        =   0
      Top             =   1320
      Width           =   1695
   End
   Begin VB.Label lblHelp 
      Caption         =   "Pour changer le signal, cliquez sur le bouton Change Signal ou directement sur l'icône de signalisation."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   600
      TabIndex        =   2
      Top             =   2040
      Width           =   3615
   End
   Begin VB.Image imgRed 
      Appearance      =   0  'Flat
      Height          =   480
      Left            =   2160
      Picture         =   "button.frx":0000
      Top             =   480
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image imgYellow 
      Height          =   480
      Left            =   2160
      Picture         =   "button.frx":030A
      Top             =   480
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image imgGreen 
      Height          =   480
      Left            =   2160
      Picture         =   "button.frx":0614
      Top             =   480
      Width           =   480
   End
End
Attribute VB_Name = "frmButton"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub ChangeSignal()
    ' Vérifie la couleur du signal et la remplace par
    ' la couleur suivante.
    ' l'ordre est vert, orange et enfin rouge.

    If imgGreen.Visible = True Then
        imgGreen.Visible = False
        imgYellow.Visible = True
    ElseIf imgYellow.Visible = True Then
        imgYellow.Visible = False
        imgRed.Visible = True
    Else
        imgRed.Visible = False
        imgGreen.Visible = True
    End If
End Sub

Private Sub cmdChange_Click()
    Call ChangeSignal        ' Appelle la procédure ChangeSignal.
End Sub

Private Sub cmdClose_Click()
   Unload Me            ' Décharge cette feuille.
End Sub

Private Sub imgGreen_Click()
    Call ChangeSignal        ' Appelle la procédure ChangeSignal.
End Sub

Private Sub imgRed_Click()
    Call ChangeSignal        ' Appelle la procédure ChangeSignal.
End Sub

Private Sub imgYellow_Click()
    Call ChangeSignal        ' Appelle la procédure ChangeSignal.
End Sub

