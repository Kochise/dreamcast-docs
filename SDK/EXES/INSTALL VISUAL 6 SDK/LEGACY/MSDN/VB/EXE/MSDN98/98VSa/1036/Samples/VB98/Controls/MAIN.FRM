VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "Exemples de contrôles"
   ClientHeight    =   2910
   ClientLeft      =   210
   ClientTop       =   1935
   ClientWidth     =   4830
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form2"
   ScaleHeight     =   2910
   ScaleWidth      =   4830
   Begin VB.CommandButton cmdImages 
      Caption         =   "&Images"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2640
      TabIndex        =   5
      Top             =   1440
      Width           =   1815
   End
   Begin VB.CommandButton cmdOption 
      Caption         =   "Boutons d'o&ptions"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2640
      TabIndex        =   4
      Top             =   840
      Width           =   1815
   End
   Begin VB.CommandButton cmdCheck 
      Caption         =   "&Cases à cocher"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2640
      TabIndex        =   3
      Top             =   240
      Width           =   1815
   End
   Begin VB.CommandButton cmdText 
      Caption         =   "&Zone de texte"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   240
      TabIndex        =   2
      Top             =   1440
      Width           =   1815
   End
   Begin VB.CommandButton cmdWordWrap 
      Caption         =   "&AutoSize et WordWrap"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Top             =   840
      Width           =   1815
   End
   Begin VB.CommandButton cmdButtons 
      Caption         =   "&Boutons de test"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   1815
   End
   Begin VB.CommandButton cmdExit 
      Cancel          =   -1  'True
      Caption         =   "&Quitter"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2640
      TabIndex        =   6
      Top             =   2160
      Width           =   1815
   End
   Begin VB.Menu mnuFileMain 
      Caption         =   "&Fichier"
      Begin VB.Menu mnuFileExit 
         Caption         =   "&Quitter"
      End
   End
   Begin VB.Menu mnuOptionsMain 
      Caption         =   "&Options"
      Begin VB.Menu mnuButtons 
         Caption         =   "&Boutons de test"
      End
      Begin VB.Menu mnuWordWrap 
         Caption         =   "&AutoSize et WordWrap"
      End
      Begin VB.Menu mnuText 
         Caption         =   "&Zone de texte"
      End
      Begin VB.Menu mnuCheck 
         Caption         =   "&Cases à cocher"
      End
      Begin VB.Menu mnuOption 
         Caption         =   "Boutons d'o&ptions"
      End
      Begin VB.Menu mnuImages 
         Caption         =   "&Images"
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub cmdButtons_Click()
    ' Provoque un événement Click à partir du menu.
    mnuButtons_Click
End Sub

Private Sub cmdCheck_Click()
    ' Provoque un événement Click à partir du menu.
    mnuCheck_Click
End Sub

Private Sub cmdExit_Click()
    Unload Me       ' Décharge la feuille
    End             ' Termine l'application
End Sub

Private Sub cmdImages_Click()
    ' Provoque un événement Click à partir du menu.
    mnuImages_Click
End Sub

Private Sub cmdOption_Click()
    ' Provoque un événement Click à partir du menu.
    mnuOption_Click
End Sub

Private Sub cmdText_Click()
    ' Provoque un événement Click à partir du menu.
    mnuText_Click
End Sub

Private Sub cmdWordWrap_Click()
    ' Provoque un événement Click à partir du menu.
    mnuWordWrap_Click
End Sub

Private Sub Form_Load()
    frmMain.Height = 3600
    frmMain.Width = 4965
End Sub

Private Sub mnuButtons_Click()
    ' Affiche la feuille.
    frmButton.Show
End Sub

Private Sub mnuCheck_Click()
    ' Affiche la feuille.
    frmCheck.Show
End Sub

Private Sub mnuFileExit_Click()
' Provoque un événement Click à partir du menu.
    cmdExit_Click
End Sub

Private Sub mnuImages_Click()
    ' Affiche la feuille.
    frmImages.Show
End Sub

Private Sub mnuOption_Click()
    ' Affiche la feuille.

    frmOptions.Show
End Sub



Private Sub mnuText_Click()
    ' Affiche la feuille.
    frmText.Show
End Sub

Private Sub mnuWordWrap_Click()
    ' Affiche la feuille.
    frmWordWrap.Show
End Sub

