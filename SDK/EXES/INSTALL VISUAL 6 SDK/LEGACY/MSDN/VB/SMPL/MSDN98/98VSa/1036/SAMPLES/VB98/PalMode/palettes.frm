VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Exemple PaletteMode"
   ClientHeight    =   5190
   ClientLeft      =   1860
   ClientTop       =   1530
   ClientWidth     =   7965
   LinkTopic       =   "Form1"
   ScaleHeight     =   5190
   ScaleWidth      =   7965
   Begin VB.OptionButton Option1 
      Caption         =   "Personnalisé (Pastel DIB)"
      Height          =   255
      Index           =   3
      Left            =   5760
      TabIndex        =   6
      Top             =   240
      Width           =   2175
   End
   Begin VB.CommandButton cmdQuit 
      Cancel          =   -1  'True
      Caption         =   "Quitter"
      Height          =   495
      Left            =   6270
      TabIndex        =   4
      Top             =   4080
      Width           =   1215
   End
   Begin VB.PictureBox Picture1 
      AutoSize        =   -1  'True
      Height          =   3855
      Left            =   240
      ScaleHeight     =   3795
      ScaleWidth      =   4305
      TabIndex        =   3
      Top             =   720
      Width           =   4365
   End
   Begin VB.OptionButton Option1 
      Caption         =   "Personnalisé (Niveaux de gris)"
      Height          =   255
      Index           =   2
      Left            =   2970
      TabIndex        =   2
      Top             =   240
      Width           =   2505
   End
   Begin VB.OptionButton Option1 
      Caption         =   "ZOrder"
      Height          =   255
      Index           =   1
      Left            =   1830
      TabIndex        =   1
      Top             =   240
      Width           =   855
   End
   Begin VB.OptionButton Option1 
      Caption         =   "Demi-teintes"
      Height          =   255
      Index           =   0
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Value           =   -1  'True
      Width           =   1335
   End
   Begin VB.Timer Timer1 
      Interval        =   800
      Left            =   6180
      Top             =   2850
   End
   Begin VB.Label Label1 
      Caption         =   "Note: Pour un effet optimal, cet exemple doit s'exécuter en mode 256 couleurs."
      Height          =   255
      Left            =   240
      TabIndex        =   5
      Top             =   4800
      Width           =   6135
   End
   Begin VB.Image Image1 
      BorderStyle     =   1  'Fixed Single
      Height          =   1290
      Left            =   6030
      Picture         =   "Palettes.frx":0000
      Stretch         =   -1  'True
      Top             =   720
      Width           =   1620
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Cet exemple d'application illustre l'utilisation des propriétés
' PaletteMode et Palette pour les feuilles et les contrôles.
' Version 1.0 16/09/1996
'
' Note: cet exemple doit être exécuté en mode 256 couleurs.
' Les propriétés Palette et PaletteMode n'ont aucun effet
' avec les autres modes de couleur.

Option Explicit
Dim objPic As Picture    ' Objet de type Picture pour l'option 4.

Private Sub cmdQuit_Click()
    Unload Me
End Sub

Private Sub Form_Load()
' Charge la palette 256 couleurs DIB dans l'objet Picture.
    Set objPic = LoadPicture(App.Path & "\PASTEL.DIB")
End Sub

Private Sub Option1_Click(Index As Integer)
    Timer1.Enabled = False
    Select Case Index
        Case 0
            ' Utilise le mode "Demi-teintes" (Valeur par défaut).
            Form1.PaletteMode = vbPaletteModeHalftone
        Case 1
            ' Utilise la palette de couleurs de l'image chargée -
            ' Le résultat est une couleur clignotante (mode ZOrder).
            Form1.PaletteMode = vbPaletteModeUseZOrder
        Case 2
            ' Définit Form1.Palette = Nothing
            ' Affecte la palette de couleurs du contrôle Image1
            ' à la propriété Palette de la feuille.
            Form1.Palette = Image1.Picture
            ' Utilise le mode Personnalisé.
            Form1.PaletteMode = vbPaletteModeCustom
        Case 3
            ' Définit Form1.Palette = Nothing
            ' Affecte la palette de l'objet objPic à la propriété
            ' Palette de la feuille.
            Form1.Palette = objPic
            ' Utilise le mode Personnalisé.
            Form1.PaletteMode = vbPaletteModeCustom
    End Select
    Picture1.Refresh
    Timer1.Enabled = True
End Sub

Private Sub Timer1_Timer()
    Static intC As Integer
    
    ' Choisit entre trois types de format d'images.
    If intC < 1 Then
        Picture1 = LoadPicture(App.Path & "\BANNER.GIF")
        intC = 1
    ElseIf intC = 1 Then
        Picture1 = LoadPicture(App.Path & "\CLOUDS.BMP")
        intC = 2
    Else
        Picture1 = LoadPicture(App.Path & "\FOREST.JPG")
        intC = 0
    End If
End Sub

