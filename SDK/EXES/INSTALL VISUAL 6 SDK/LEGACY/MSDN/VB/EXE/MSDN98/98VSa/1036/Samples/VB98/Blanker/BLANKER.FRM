VERSION 5.00
Begin VB.Form DemoForm 
   BackColor       =   &H00000000&
   Caption         =   "Démonstration Mise en veille"
   ClientHeight    =   3855
   ClientLeft      =   960
   ClientTop       =   2535
   ClientWidth     =   7470
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H00000000&
   Icon            =   "BLANKER.frx":0000
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3855
   ScaleWidth      =   7470
   WhatsThisHelp   =   -1  'True
   Begin VB.Timer Timer1 
      Interval        =   1
      Left            =   6960
      Top             =   120
   End
   Begin VB.CommandButton cmdStartStop 
      BackColor       =   &H00000000&
      Caption         =   "Lancer la démo"
      Default         =   -1  'True
      Height          =   390
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   1830
   End
   Begin VB.PictureBox picBall 
      AutoSize        =   -1  'True
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   480
      Left            =   1800
      Picture         =   "BLANKER.frx":030A
      ScaleHeight     =   480
      ScaleWidth      =   480
      TabIndex        =   1
      Top             =   720
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image imgMoon 
      Height          =   480
      Index           =   8
      Left            =   6330
      Picture         =   "BLANKER.frx":0614
      Top             =   3765
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Line linLineCtl 
      BorderColor     =   &H00FF0000&
      BorderWidth     =   5
      Visible         =   0   'False
      X1              =   240
      X2              =   4080
      Y1              =   2760
      Y2              =   2760
   End
   Begin VB.Image imgMoon 
      Height          =   480
      Index           =   7
      Left            =   5760
      Picture         =   "BLANKER.frx":091E
      Top             =   3720
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image imgMoon 
      Height          =   480
      Index           =   6
      Left            =   5160
      Picture         =   "BLANKER.frx":0C28
      Top             =   3720
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image imgMoon 
      Height          =   480
      Index           =   5
      Left            =   4560
      Picture         =   "BLANKER.frx":0F32
      Top             =   3720
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image imgMoon 
      Height          =   480
      Index           =   4
      Left            =   3960
      Picture         =   "BLANKER.frx":123C
      Top             =   3720
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image imgMoon 
      Height          =   480
      Index           =   3
      Left            =   3360
      Picture         =   "BLANKER.frx":1546
      Top             =   3720
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image imgMoon 
      Height          =   480
      Index           =   2
      Left            =   2760
      Picture         =   "BLANKER.frx":1850
      Top             =   3720
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image imgMoon 
      Height          =   480
      Index           =   1
      Left            =   2160
      Picture         =   "BLANKER.frx":1B5A
      Top             =   3720
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image imgMoon 
      Height          =   480
      Index           =   0
      Left            =   1560
      Picture         =   "BLANKER.frx":1E64
      Top             =   3720
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Shape shpClone 
      BackColor       =   &H00000000&
      BackStyle       =   1  'Opaque
      BorderColor     =   &H00FF0000&
      FillColor       =   &H000000FF&
      Height          =   1215
      Index           =   0
      Left            =   240
      Top             =   720
      Visible         =   0   'False
      Width           =   1410
   End
   Begin VB.Shape Shape1 
      Height          =   15
      Left            =   960
      Top             =   1080
      Width           =   15
   End
   Begin VB.Menu mnuOption 
      Caption         =   "&Options"
      Begin VB.Menu mnuLineCtlDemo 
         Caption         =   "&Ligne sautante"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuCtlMoveDemo 
         Caption         =   "Re&bond"
      End
      Begin VB.Menu mnuImageDemo 
         Caption         =   "&Rotation de la lune"
      End
      Begin VB.Menu mnuShapeDemo 
         Caption         =   "&Objets de couleur"
      End
      Begin VB.Menu mnuPSetDemo 
         Caption         =   "&Confetti"
      End
      Begin VB.Menu mnuLineDemo 
         Caption         =   "B&alles traçantes"
      End
      Begin VB.Menu mnuCircleDemo 
         Caption         =   "&Tapis arc-en-ciel"
      End
      Begin VB.Menu mnuScaleDemo 
         Caption         =   "Barr&es colorées"
      End
      Begin VB.Menu sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuExit 
         Caption         =   "&Quitter"
      End
   End
End
Attribute VB_Name = "DemoForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

' Déclare une variable pour le suivi du cadre d'animation.
Dim FrameNum
' Déclare les variables des coordonnées X et Y pour le suivi de la position.
Dim XPos
Dim YPos
' Déclare un indicateur de variable pour arrêter les routines graphiques.
Dim DoFlag
' Déclare une variable pour suivre les contrôles en déplacement.
Dim Motion
' Déclare les variables de feuille pour la couleur.
Dim R
Dim G
Dim B

Private Sub CircleDemo()
    ' Déclare les variables locales.
    Dim Radius
    ' Crée des couleurs RGB au hasard.
    R = 255 * Rnd
    G = 255 * Rnd
    B = 255 * Rnd
    ' Positionne le centre des cercles au centre de la feuille.
    XPos = ScaleWidth / 2
    YPos = ScaleHeight / 2
    ' Génère un rayon compris entre 0 et près de la moitié de la hauteur de la feuille.
    Radius = ((YPos * 0.9) + 1) * Rnd
    ' Dessine un cercle sur la feuille.
    Circle (XPos, YPos), Radius, RGB(R, G, B)
End Sub

Private Sub cmdStartStop_Click()
' Déclare des variables locales.
Dim UnClone
Dim MakeClone
Dim X1
Dim Y1
    Select Case DoFlag
        Case True
            cmdStartStop.Caption = "Lancer la démo"
            DoFlag = False
            mnuOption.Enabled = True
            If mnuCtlMoveDemo.Checked = True Then
                ' Cache à nouveau le graphisme bondissant.
                picBall.Visible = False
            ElseIf mnuLineDemo.Checked = True Then
                ' Supprime des lignes de la feuille..
                Cls
            ElseIf mnuShapeDemo.Checked = True Then
                ' Supprime tous les contrôles Shape chargés dynamiquement.
                For UnClone = 1 To 20
                    Unload shpClone(UnClone)
                Next UnClone
                ' Réinitialise la couleur d'arrière-plan à noir.
                DemoForm.BackColor = QBColor(0)
                ' Rafraîchit la feuille pour que le changement de couleur prenne effet.
                Refresh
            ElseIf mnuPSetDemo.Checked = True Then
                ' Supprime des morceaux de confettis de la feuille.
                Cls
            ElseIf mnuLineCtlDemo.Checked = True Then
                ' Cache le contrôle Line à nouveau.
                linLineCtl.Visible = False
                ' Supprime tous les pixels restants.
                Cls
            ElseIf mnuImageDemo.Checked = True Then
                ' Cache à nouveau le graphisme bondissant.
                imgMoon(0).Visible = False
            ElseIf mnuScaleDemo.Checked = True Then
                ' Efface la feuille.
                Cls
                ' Renvoie l'échelle par défaut de la feuille.
                Scale
            ElseIf mnuCircleDemo.Checked = True Then
                ' Supprime les cercles de la feuille.
                Cls
            End If
        Case False
            cmdStartStop.Caption = "Stopper la démo"
            DoFlag = True
            mnuOption.Enabled = False
            If mnuCtlMoveDemo.Checked = True Then
                ' Rend visible le graphisme bondissant (contrôle PictureBox).
                picBall.Visible = True
                ' Détermine le mouvement initial du graphisme bondissant au hasard.
                ' Paramètres compris entre 1 et 4.
                ' La valeur de la variable Motion détermine
                ' quelle partie de la routine Do Loop s'exécute.
                Motion = Int(4 * Rnd + 1)
            ElseIf mnuLineDemo.Checked = True Then
                ' Initialise le générateur de nombres aléatoires.
                Randomize
                ' Définit la largeur du trait.
                DrawWidth = 2
                ' Définit les coordonnées X et Y initiales en un
                ' point de la feuille pris au hasard.
                X1 = Int(DemoForm.Width * Rnd + 1)
                Y1 = Int(DemoForm.Height * Rnd + 1)
            ElseIf mnuShapeDemo.Checked = True Then
                ' Charge dynamiquement un groupe de contrôles de 20
                ' contrôles Shape sur la feuille.
                For MakeClone = 1 To 20
                    Load shpClone(MakeClone)
                Next MakeClone
            ElseIf mnuPSetDemo.Checked = True Then
                ' Définit l'épaisseur des confettis.
                DrawWidth = 5
            ElseIf mnuLineCtlDemo.Checked = True Then
                ' Rend visible le contrôle Line.
                linLineCtl.Visible = True
                ' Définit l'épaisseur du trait tel qu'il apparaîtra.
                DrawWidth = 7
            ElseIf mnuImageDemo.Checked = True Then
                ' Rend visible le graphisme bondissant (contrôle Image).
                imgMoon(0).Visible = True
                ' Définit le cadre d'animation initial.
                FrameNum = 0
                ' Définit de manière aléatoire le déplacement initial du graphisme rebondissant.
                ' Paramètres compris entre 1 et 4.
                ' La valeur de la variable Motion détermine quelle partie de la routine Do Loop s'exécute.
                Motion = Int(4 * Rnd + 1)
            ElseIf mnuScaleDemo.Checked = True Then
                ' Initialise le générateur de nombres aléatoires.
                Randomize
                ' Définit la largeur des contours de zones pour que celles-ci ne se recouvrent pas.
                DrawWidth = 1
                ' Définit la valeur de l'abscisse X du bord gauche de la feuille.
                ' Définit l'abscisse X à 1 pour la première zone, 2 pour la seconde zone et ainsi de suite.
                ScaleLeft = 1
                ' Définit l'ordonnée Y du bord supérieur de la feuille à 10.
                ScaleTop = 10
                ' Définit le nombre d'unités comprises dans la largeur de la feuille
                ' avec un nombre aléatoire compris entre 3 et 12. Cela modifie le nombre
                ' de zones dessinées chaque fois que la routine démarre.
                ScaleWidth = Int(13 * Rnd + 3)
                ' Définit le nombre d'unités comprises dans la hauteur de la feuille à -10.
                ' Ainsi, la hauteur des zones varie de 0 à 10 et l'ordonnée Y démarre au bas
                ' de la feuille.
                ScaleHeight = -10
            ElseIf mnuCircleDemo.Checked = True Then
                ' Définit la largeur du contour du cercle.
                DrawWidth = 1
                ' Dessine les cercles en traits discontinus.
                DrawStyle = vbDash
                ' Dessine les traits à l'aide du crayon XOR, en combinant les couleurs
                ' du crayon ou de l'affichage, mais pas les deux.
                DrawMode = vbXorPen
            End If
    End Select
End Sub

Private Sub CtlMoveDemo()
    Select Case Motion
    Case 1
        ' Déplace le graphisme vers la gauche et vers le haut de 20 twips en utilisant la méthode Move.
        picBall.Move picBall.Left - 20, picBall.Top - 20
        ' Si le graphisme atteint le bord gauche de la feuille, le déplace vers la droite et vers le haut.
        If picBall.Left <= 0 Then
            Motion = 2
        ' Si le graphisme atteint le bord supérieur de la feuille, le déplace vers la gauche et vers le bas.
        ElseIf picBall.Top <= 0 Then
            Motion = 4
        End If
    Case 2
        ' Déplace le graphisme vers la droite et vers le haut de 20 twips.
        picBall.Move picBall.Left + 20, picBall.Top - 20

        ' Si le graphisme atteint le bord droit de la feuille, le
        ' déplace vers la gauche et vers le haut. La routine détermine le
        ' bord droit de la feuille en soustrayant la largeur du
        ' graphisme de la largeur de la feuille.
        If picBall.Left >= (DemoForm.Width - picBall.Width) Then
            Motion = 1
        ' Si le graphisme atteint le bord supérieur de la feuille, le déplace vers la droite et vers le bas.
        ElseIf picBall.Top <= 0 Then
            Motion = 3
        End If
    Case 3
        ' Déplace le graphisme vers la droite et vers le bas de 20 twips.
        picBall.Move picBall.Left + 20, picBall.Top + 20
        ' Si le graphisme atteint le bord droit de la feuille, le déplace vers la gauche et vers le bas.
        If picBall.Left >= (DemoForm.Width - picBall.Width) Then
            Motion = 4
        ' Si le graphisme atteint le bord inférieur de la feuille, le déplace vers la droite et vers le haut.
        ' La routine détermine le bord inférieur de la feuille en soustrayant la hauteur du graphisme
        ' de la hauteur de la feuille moins 680 twips pour tenir compte de la hauteur
        ' de la barre de titre et de la barre de menu.

        ElseIf picBall.Top >= (DemoForm.Height - picBall.Height) - 680 Then
            Motion = 2
        End If
    Case 4
        ' Déplace le graphisme vers la gauche et vers le bas de 20 twips.
        picBall.Move picBall.Left - 20, picBall.Top + 20
        ' Si le graphisme atteint le bord gauche de la feuille, le déplace vers la droite et vers le bas.
        If picBall.Left <= 0 Then
            Motion = 3
        ' Si le graphisme atteint le bord inférieur de la feuille, le déplace vers la gauche et vers le haut.
        ElseIf picBall.Top >= (DemoForm.Height - picBall.Height) - 680 Then
            Motion = 1
        End If
    End Select
End Sub

Private Sub Delay()
    Dim Start
    Dim Check
    Start = Timer
    Do Until Check >= Start + 0.15
        Check = Timer
    Loop
End Sub

Private Sub Form_Load()
    DoFlag = False
End Sub

Private Sub Form_Resize()
    If mnuScaleDemo.Checked = True And DemoForm.WindowState = 0 Then
        ' Initialise le générateur de nombres aléatoires.
        Randomize
        ' Définit une largeur étroite de contours de zone pour que les zones ne se superposent pas.
        DrawWidth = 1
        ' Définit la valeur de l'abscisse X du bord gauche de la feuille à 1.
        ' Cela permet de définir aisément la position de chaque zone.
        ' La première possède une abscisse égale à 1, la seconde une abscisse égale à 2, etc.
        ScaleLeft = 1
        ' Définit la valeur de l'ordonnée Y du bord supérieur de la feuille à 10.
        ScaleTop = 10
        ' Définit le nombre d'unités dans la largeur de la feuille avec un nombre aléatoire
        ' compris entre 3 et 12. De ce fait, le nombre de zones dessinées varie chaque fois
        ' que l'utilisateur redémarre la routine.
        ScaleWidth = Int(13 * Rnd + 3)
        ' Définit le nombre d'unités dans la hauteur de la feuille à -10. L'effet est double.
        ' Premièrement, toutes les zones ont une hauteur qui varie entre 0 et 10.
        ' Deuxièmement, à cause de la valeur négative, les ordonnées Y commencent à partir
        ' du bord inférieur de la feuille au lieu du bord supérieur.

        ScaleHeight = -10
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    End
End Sub

Private Sub ImageDemo()
    Select Case Motion
    Case 1
        ' Déplace le graphisme vers la gauche et vers le haut de 100 twips à l'aide de la méthode Move.
        imgMoon(0).Move imgMoon(0).Left - 100, imgMoon(0).Top - 100
        ' Incrémente l'animation au cadre suivant.
        IncrFrame
        ' Si le graphisme atteint le bord gauche de la feuille, le déplace vers la droite et vers le haut.
        If imgMoon(0).Left <= 0 Then
            Motion = 2
        ' Si le graphisme atteint le bord supérieur de la feuille, le déplace vers la gauche et vers le bas.
        ElseIf imgMoon(0).Top <= 0 Then
            Motion = 4
        End If
    Case 2
        ' Déplace le graphisme vers la droite et vers le haut de 100 twips.
        imgMoon(0).Move imgMoon(0).Left + 100, imgMoon(0).Top - 100
        ' Incrémente l'animation au cadre suivant.
        IncrFrame
        ' Si le graphisme atteint le bord droit de la feuille, le déplace vers la gauche et vers le haut.
        ' La routine détermine le bord droit de la feuille en soustrayant la largeur
        ' du graphisme de celle du contrôle.

        If imgMoon(0).Left >= (DemoForm.Width - imgMoon(0).Width) Then
            Motion = 1
        ' Si le graphisme atteint le bord supérieur de la feuille, le déplace vers la droite et vers le bas.
        ElseIf imgMoon(0).Top <= 0 Then
            Motion = 3
        End If
    Case 3
        ' Déplace le graphisme vers la droite et vers le bas de 100 twips.
        imgMoon(0).Move imgMoon(0).Left + 100, imgMoon(0).Top + 100
        ' Incrémente l'animation au cadre suivant.
        IncrFrame
        ' Si le graphisme atteint le bord droit de la feuille, le déplace vers la gauche et vers le bas.
        If imgMoon(0).Left >= (DemoForm.Width - imgMoon(0).Width) Then
            Motion = 4
        ' Si le graphisme atteint le bord inférieur de la feuille, le déplace vers la droite et vers le haut.
        ' La routine détermine le bord inférieur de la feuille en soustrayant la hauteur du
        ' graphisme de la hauteur de la feuille moins 680 twips pour tenir compte de la hauteur
        ' de la barre de titre et de la barre de menu.
        ElseIf imgMoon(0).Top >= (DemoForm.Height - imgMoon(0).Height) - 680 Then
            Motion = 2
        End If
    Case 4
        ' Déplace le graphisme vers la gauche et vers le bas de 100 twips.
        imgMoon(0).Move imgMoon(0).Left - 100, imgMoon(0).Top + 100
        ' Incrémente l'animation au cadre suivant.
        IncrFrame
        ' Si le graphisme atteint le bord gauche de la feuille, le déplace vers la droite et vers le bas.
        If imgMoon(0).Left <= 0 Then
            Motion = 3
        ' Si le graphisme atteint le bord inférieur de la feuille, le déplace vers la gauche et vers le haut.
        ElseIf imgMoon(0).Top >= (DemoForm.Height - imgMoon(0).Height) - 680 Then
            Motion = 1
        End If
    End Select
End Sub

Private Sub IncrFrame()
    ' Incrémente le numéro de cadre.
    FrameNum = FrameNum + 1
    ' Le groupe de contrôles avec cadres d'animation comporte les éléments 0 à 7.
    ' Au 8e cadre, réinitialise le numéro de cadrer à 1 pour créer une boucle d'animation sans fin.
    If FrameNum > 8 Then
        FrameNum = 1
    End If
    ' Définit pour la propriété du contrôle Image la propriété Image du cadre en cours.
    imgMoon(0).Picture = imgMoon(FrameNum).Picture
    ' Marque une pause dans l'affichage pour ralentir l'animation.
    Me.Refresh
    Delay
End Sub

Private Sub LineCtlDemo()
    ' Définit les coordonnées X et Y du début de ligne (position gauche/droite)
    ' en un point de la feuille pris au hasard.
    linLineCtl.X1 = Int(DemoForm.Width * Rnd)
    linLineCtl.Y1 = Int(DemoForm.Height * Rnd)
    ' Définit les coordonnées X et Y de la fin de ligne (position gauche/droite)
    ' en un point de la feuille pris au hasard.
    linLineCtl.X2 = Int(DemoForm.Width * Rnd)
    linLineCtl.Y2 = Int(DemoForm.Height * Rnd)
    ' Efface la feuille pour supprimer les pixels restants.
    Cls
    ' Marque une pause dans l'affichage avant de redéplacer le trait.
    Delay
End Sub

Private Sub LineDemo()
    ' Déclare des variables locales.
    Dim X2
    Dim Y2
    ' Crée des couleurs RGB au hasard.
    R = 255 * Rnd
    G = 255 * Rnd
    B = 255 * Rnd
    ' Définit l'extrémité finale du trait en un point pris au hasard dans la feuille.
    X2 = Int(DemoForm.Width * Rnd + 1)
    Y2 = Int(DemoForm.Height * Rnd + 1)
    ' A l'aide de la Méthode Line, dessine depuis les coordonnées en cours jusqu'à l'extrémité
    ' en cours, en donnant une couleur aléatoire au trait. Chaque trait commence au point
    ' où le précédent se termine.
    Line -(X2, Y2), RGB(R, G, B)
End Sub

Private Sub mnuCircleDemo_Click()
    Cls
    mnuCtlMoveDemo.Checked = False
    mnuLineDemo.Checked = False
    mnuShapeDemo.Checked = False
    mnuPSetDemo.Checked = False
    mnuLineCtlDemo.Checked = False
    mnuImageDemo.Checked = False
    mnuScaleDemo.Checked = False
    mnuCircleDemo.Checked = True
End Sub

Private Sub mnuCtlMoveDemo_Click()
    Cls
    mnuCtlMoveDemo.Checked = True
    mnuLineDemo.Checked = False
    mnuShapeDemo.Checked = False
    mnuPSetDemo.Checked = False
    mnuLineCtlDemo.Checked = False
    mnuImageDemo.Checked = False
    mnuScaleDemo.Checked = False
    mnuCircleDemo.Checked = False
End Sub

Private Sub mnuExit_Click()
    End
End Sub

Private Sub mnuImageDemo_Click()
    Cls
    mnuCtlMoveDemo.Checked = False
    mnuLineDemo.Checked = False
    mnuShapeDemo.Checked = False
    mnuPSetDemo.Checked = False
    mnuLineCtlDemo.Checked = False
    mnuImageDemo.Checked = True
    mnuScaleDemo.Checked = False
    mnuCircleDemo.Checked = False
End Sub

Private Sub mnuLineCtlDemo_Click()
    Cls
    mnuCtlMoveDemo.Checked = False
    mnuLineDemo.Checked = False
    mnuShapeDemo.Checked = False
    mnuPSetDemo.Checked = False
    mnuLineCtlDemo.Checked = True
    mnuImageDemo.Checked = False
    mnuScaleDemo.Checked = False
    mnuCircleDemo.Checked = False
End Sub

Private Sub mnuLineDemo_Click()
    Cls
    mnuCtlMoveDemo.Checked = False
    mnuLineDemo.Checked = True
    mnuShapeDemo.Checked = False
    mnuPSetDemo.Checked = False
    mnuLineCtlDemo.Checked = False
    mnuImageDemo.Checked = False
    mnuScaleDemo.Checked = False
    mnuCircleDemo.Checked = False
End Sub

Private Sub mnuPSetDemo_Click()
    Cls
    mnuCtlMoveDemo.Checked = False
    mnuLineDemo.Checked = False
    mnuShapeDemo.Checked = False
    mnuPSetDemo.Checked = True
    mnuLineCtlDemo.Checked = False
    mnuImageDemo.Checked = False
    mnuScaleDemo.Checked = False
    mnuCircleDemo.Checked = False
End Sub

Private Sub mnuScaleDemo_Click()
    Cls
    mnuCtlMoveDemo.Checked = False
    mnuLineDemo.Checked = False
    mnuShapeDemo.Checked = False
    mnuPSetDemo.Checked = False
    mnuLineCtlDemo.Checked = False
    mnuImageDemo.Checked = False
    mnuScaleDemo.Checked = True
    mnuCircleDemo.Checked = False
End Sub

Private Sub mnuShapeDemo_Click()
    Cls
    mnuCtlMoveDemo.Checked = False
    mnuLineDemo.Checked = False
    mnuShapeDemo.Checked = True
    mnuPSetDemo.Checked = False
    mnuLineCtlDemo.Checked = False
    mnuImageDemo.Checked = False
    mnuScaleDemo.Checked = False
    mnuCircleDemo.Checked = False
End Sub

Private Sub PSetDemo()
    ' Crée des couleurs RGB aléatoires.
    R = 255 * Rnd
    G = 255 * Rnd
    B = 255 * Rnd
    ' XPos définit la position horizontale d'un confetti en un point pris au hasard dans la feuille.
    XPos = Rnd * ScaleWidth
    ' YPos définit la position verticale d'un confetti en un point pris au hasard dans la feuille.
    YPos = Rnd * ScaleHeight
    ' Dessine un confetti au point XPos, Ypos. Affecte au confetti une couleur aléatoire.
    PSet (XPos, YPos), RGB(R, G, B)
End Sub

Private Sub ScaleDemo()
    ' Déclare des variables locales.
    Dim Box
    ' Crée autant de zones que d'unités dans la largeur de la feuille.
    For Box = 1 To ScaleWidth
        ' Crée des couleurs RGB aléatoires.
        R = 255 * Rnd
        G = 255 * Rnd
        B = 255 * Rnd
        ' Dessine des zones à l'aide de la méthode Line et des options B (zone), F (remplie).
        ' Les zones commencent à chaque abscisse X déterminée par la propriété ScaleWidth
        ' et à une ordonnée Y égale à 0 (bas de la feuille). Chaque zone mesure 1 unité de large
        ' et possède une hauteur aléatoire comprise entre 0 et 10. Remplit la zone d'une couleur aléatoire.
        Line (Box, 0)-Step(1, (Int(11 * Rnd))), RGB(R, G, B), BF
    Next Box
    ' Pause pour l'affichage de toutes les zones avant de redessiner.
    Delay
End Sub

Private Sub ShapeDemo()
    ' Déclare des variables locales.
    Dim CloneID
    ' Crée des couleurs RGB aléatoires.
    R = 255 * Rnd
    G = 255 * Rnd
    B = 255 * Rnd
    ' Définit une couleur aléatoire pour l'arrière-plan de la feuille.
    DemoForm.BackColor = RGB(R, G, B)
    ' Sélectionne un contrôle Shape au hasard dans le groupe de contrôles.
    CloneID = Int(20 * Rnd + 1)
    ' XPos et Ypos définissent la position du contrôle Shape sélectionné en un point
    ' pris au hasard dans la feuille.
    XPos = Int(DemoForm.Width * Rnd + 1)
    YPos = Int(DemoForm.Height * Rnd + 1)
    ' Définit une figure au hasard pour le contrôle Shape sélectionné.
    shpClone(CloneID).Shape = Int(6 * Rnd)
    ' Définit la hauteur et la largeur du contrôle Shape sélectionné à une dimension au hasard
    ' comprise entre 500 et 2500 twips.
    shpClone(CloneID).Height = Int(2501 * Rnd + 500)
    shpClone(CloneID).Width = Int(2501 * Rnd + 500)
    ' Définit la couleur d'arrière-plan et DrawMode du contrôle Shape à une couleur aléatoire.
    shpClone(CloneID).BackColor = QBColor(Int(15 * Rnd))
    shpClone(CloneID).DrawMode = Int(16 * Rnd + 1)
    ' Déplace le contrôle Figure sélectionné à l'aide de la méthode Move
    shpClone(CloneID).Move XPos, YPos
    ' Rend visible le contrôle Shape sélectionné.
    shpClone(CloneID).Visible = True
    ' Attend brièvement avant sélection et modification du contrôle Shape suivant.
    Delay
End Sub

Private Sub Timer1_Timer()
    If mnuCtlMoveDemo.Checked And DoFlag = True Then
        CtlMoveDemo
    ElseIf mnuLineDemo.Checked And DoFlag = True Then
        LineDemo
    ElseIf mnuShapeDemo.Checked And DoFlag = True Then
        ShapeDemo
    ElseIf mnuPSetDemo.Checked And DoFlag = True Then
        PSetDemo
    ElseIf mnuLineCtlDemo.Checked And DoFlag = True Then
        LineCtlDemo
    ElseIf mnuImageDemo.Checked And DoFlag = True Then
        ImageDemo
    ElseIf mnuScaleDemo.Checked And DoFlag = True Then
        ScaleDemo
    ElseIf mnuCircleDemo.Checked And DoFlag = True Then
        CircleDemo
    End If
End Sub

