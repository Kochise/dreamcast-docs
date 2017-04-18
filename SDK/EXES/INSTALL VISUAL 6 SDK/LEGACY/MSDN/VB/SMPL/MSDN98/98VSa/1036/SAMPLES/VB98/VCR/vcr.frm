VERSION 5.00
Begin VB.Form frmVCR 
   BackColor       =   &H00000000&
   Caption         =   "VBTV"
   ClientHeight    =   6795
   ClientLeft      =   1170
   ClientTop       =   1470
   ClientWidth     =   7110
   FillStyle       =   0  'Solid
   Icon            =   "vcr.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   6795
   ScaleWidth      =   7110
   Begin VB.CommandButton cmdSet 
      Caption         =   "Définir"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   4560
      MaskColor       =   &H00000000&
      TabIndex        =   13
      ToolTipText     =   "Définit la minuterie pour l'enregistrement"
      Top             =   6000
      Width           =   855
   End
   Begin VB.Timer tmr2 
      Enabled         =   0   'False
      Left            =   6240
      Top             =   3240
   End
   Begin VB.Timer tmr1 
      Interval        =   65535
      Left            =   6240
      Top             =   2640
   End
   Begin VB.CommandButton cmdDown 
      Caption         =   "-"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   325
      Left            =   6120
      MaskColor       =   &H00000000&
      TabIndex        =   11
      ToolTipText     =   "Changement des chaînes"
      Top             =   1440
      Width           =   735
   End
   Begin VB.CommandButton cmdUp 
      Caption         =   "+"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   325
      Left            =   6120
      MaskColor       =   &H00000000&
      TabIndex        =   10
      ToolTipText     =   "Changement des chaînes"
      Top             =   1080
      Width           =   735
   End
   Begin VB.CommandButton cmdExit 
      Cancel          =   -1  'True
      Caption         =   "Éject."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   5760
      MaskColor       =   &H00000000&
      TabIndex        =   7
      ToolTipText     =   "Quitte l'application VBTV"
      Top             =   6000
      Width           =   1095
   End
   Begin VB.CommandButton cmdPause 
      Caption         =   "ll"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   1005
      MaskColor       =   &H00000000&
      TabIndex        =   6
      ToolTipText     =   "Pause"
      Top             =   6000
      Width           =   615
   End
   Begin VB.CommandButton cmdRec 
      Caption         =   "Enr."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   1650
      MaskColor       =   &H00000000&
      TabIndex        =   5
      ToolTipText     =   "Enregistrement"
      Top             =   6000
      Width           =   615
   End
   Begin VB.CommandButton cmdForward 
      Caption         =   ">>"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   2955
      MaskColor       =   &H00000000&
      TabIndex        =   4
      ToolTipText     =   "Avance rapide"
      Top             =   6000
      Width           =   615
   End
   Begin VB.CommandButton cmdRewind 
      Caption         =   "<<"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   2310
      MaskColor       =   &H00000000&
      TabIndex        =   3
      ToolTipText     =   "Retour rapide"
      Top             =   6000
      Width           =   615
   End
   Begin VB.CommandButton cmdStop 
      Caption         =   "Arrêt"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   3600
      MaskColor       =   &H00000000&
      TabIndex        =   2
      ToolTipText     =   "Arrêt"
      Top             =   6000
      Width           =   615
   End
   Begin VB.PictureBox picTV 
      AutoRedraw      =   -1  'True
      BackColor       =   &H00C0C0C0&
      BorderStyle     =   0  'None
      FillStyle       =   2  'Horizontal Line
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   4215
      Left            =   360
      ScaleHeight     =   4215
      ScaleWidth      =   5535
      TabIndex        =   1
      Top             =   240
      Width           =   5535
   End
   Begin VB.CommandButton cmdPlay 
      Caption         =   ">"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   360
      MaskColor       =   &H00000000&
      TabIndex        =   0
      ToolTipText     =   "Lecture"
      Top             =   6000
      Width           =   615
   End
   Begin VB.Line Line2 
      BorderColor     =   &H00808080&
      X1              =   0
      X2              =   7080
      Y1              =   4660
      Y2              =   4660
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00FFFFFF&
      X1              =   0
      X2              =   7080
      Y1              =   4700
      Y2              =   4700
   End
   Begin VB.Shape shpPlay 
      FillColor       =   &H0000FF00&
      FillStyle       =   0  'Solid
      Height          =   105
      Left            =   615
      Shape           =   3  'Circle
      Top             =   5835
      Visible         =   0   'False
      Width           =   105
   End
   Begin VB.Shape shpForward 
      FillColor       =   &H0000FF00&
      FillStyle       =   0  'Solid
      Height          =   105
      Left            =   3210
      Shape           =   3  'Circle
      Top             =   5835
      Visible         =   0   'False
      Width           =   105
   End
   Begin VB.Shape shpRewind 
      FillColor       =   &H0000FF00&
      FillStyle       =   0  'Solid
      Height          =   105
      Left            =   2565
      Shape           =   3  'Circle
      Top             =   5835
      Visible         =   0   'False
      Width           =   105
   End
   Begin VB.Shape shpRec 
      FillColor       =   &H000000FF&
      FillStyle       =   0  'Solid
      Height          =   105
      Left            =   1905
      Shape           =   3  'Circle
      Top             =   5835
      Visible         =   0   'False
      Width           =   105
   End
   Begin VB.Shape shpPause 
      FillColor       =   &H0000FF00&
      FillStyle       =   0  'Solid
      Height          =   105
      Left            =   1260
      Shape           =   3  'Circle
      Top             =   5835
      Visible         =   0   'False
      Width           =   105
   End
   Begin VB.Image img2 
      Height          =   1155
      Left            =   1680
      Picture         =   "vcr.frx":0442
      Top             =   6720
      Visible         =   0   'False
      Width           =   1155
   End
   Begin VB.Image img1 
      Height          =   1155
      Left            =   240
      Picture         =   "vcr.frx":10CC
      Top             =   6720
      Visible         =   0   'False
      Width           =   1155
   End
   Begin VB.Label lblTime 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   615
      Left            =   480
      TabIndex        =   12
      Top             =   4920
      Width           =   1935
   End
   Begin VB.Label lblBrand 
      BackStyle       =   0  'Transparent
      Caption         =   "Microsoft Visual Basic VCR - Version 1.0"
      ForeColor       =   &H00FFFFFF&
      Height          =   375
      Left            =   3360
      TabIndex        =   9
      Top             =   5160
      Width           =   2895
   End
   Begin VB.Image imgTapeSlot 
      BorderStyle     =   1  'Fixed Single
      Height          =   615
      Left            =   2640
      Top             =   4920
      Width           =   4215
   End
   Begin VB.Label lblChannel 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      BorderStyle     =   1  'Fixed Single
      Caption         =   "3"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   24
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   615
      Left            =   6120
      TabIndex        =   8
      ToolTipText     =   "Affichage de la chaîne"
      Top             =   240
      Width           =   735
   End
End
Attribute VB_Name = "frmVCR"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'***************************************************
' Sujet:   Feuille principale de l'exemple
'          d'application VCR. Émule un magnétoscope
'          en utilisant des objets Visual Basic.
'***************************************************
Option Explicit

' Crée une instance de la classe Tape.
Dim Tape As New clsTape

Dim vntChannel As Variant   ' Numéro de chaîne.

' Constantes pour la fonction QBColor.
Const vcrBlack = 0
Const vcrGreen = 2
Const vcrCyan = 3
Const vcrRed = 4
Const vcrMagenta = 5
Const vcrYellow = 6
Const vcrWhite = 7
Const vcrGray = 8
Const vcrLightBlue = 9
Const vcrLightGreen = 10
Const vcrLightCyan = 11
Const vcrLightRed = 12
Const vcrLightMagenta = 13




Private Sub cmdDown_Click()
    ' Si le chiffre est correct, définit le numéro de la chaîne.
    If vntChannel > 2 Then
        vntChannel = vntChannel - 1
    Else
        vntChannel = 13
    End If
    
    ' Affecte la variable de la chaîne à l'affichage.
    lblChannel.Caption = vntChannel
End Sub

Private Sub cmdExit_Click()
    ' Décharge la feuille, libère la référence.
    Unload Me
    Set frmVCR = Nothing
End Sub

Private Sub cmdForward_Click()
    ' Appelle la fonction pour sauvegarder l'ancienne chaîne.
    SaveChannel vntChannel
    ' Se mettre sur la chaîne 3 pour regarder une cassette.
    vntChannel = 3
    lblChannel.Caption = vntChannel
    ' Définit les propriétés de la classe Tape.
    Tape.Forward = True
    Tape.Speed = 50
    ' Lance la minuterie.
    tmr2.Enabled = True
    tmr2.Interval = Tape.Speed
    ' Appelle la fonction pour mettre à jour les contrôles.
    ButtonManager frmVCR.cmdForward
End Sub

Private Sub cmdPause_Click()
    ' Arrête la minuterie.
    tmr2.Enabled = False
    ' Appelle la fonction pour mettre à jour les contrôles.
    ButtonManager frmVCR.cmdPause
End Sub

Private Sub cmdPlay_Click()
    ' Appelle la fonction pour sauvegarder l'ancienne chaîne.
    SaveChannel vntChannel
    ' Se mettre sur la chaîne 3 pour regarder une cassette.
    vntChannel = 3
    lblChannel.Caption = vntChannel
    ' Définit les propriétés de la classe Tape.
    Tape.Forward = True
    Tape.Speed = 300
    ' Lance la minuterie.
    tmr2.Enabled = True
    tmr2.Interval = Tape.Speed
    ' Appelle la fonction pour mettre à jour les contrôles.
    ButtonManager frmVCR.cmdPlay
End Sub

Private Sub cmdRec_Click()
    Dim strStatus As String     ' Texte de l'affichage.
    
    ' Appelle la fonction pour sauvegarder l'ancienne chaîne.
    SaveChannel vntChannel
    ' Efface l'écran
    picTV.Cls
    ' Affiche le statut
    strStatus = "Enregistrement: Chaîne " & vntChannel
    picTV.Print strStatus
    strStatus = lblTime.Caption
    picTV.Print strStatus
    ' Appelle la fonction pour mettre à jour les contrôles.
    ButtonManager frmVCR.cmdRec
End Sub

Private Sub cmdRewind_Click()
    ' Appelle la fonction pour sauvegarder l'ancienne chaîne.
    SaveChannel vntChannel
    ' Se mettre sur la chaîne 3 pour regarder une cassette.
    vntChannel = 3
    lblChannel.Caption = vntChannel
    ' Définit les propriétés de la classe Tape.
    Tape.Forward = False
    Tape.Speed = 50
    ' Lance la minuterie.
    tmr2.Enabled = True
    tmr2.Interval = Tape.Speed
    ' Appelle la fonction pour mettre à jour les contrôles.
    ButtonManager frmVCR.cmdRewind
End Sub

Private Sub cmdSet_Click()
    ' Affiche la feuille de saisie de l'utilisateur de manière modale.
    frmSetTime.Show vbModal
End Sub

Private Sub cmdStop_Click()
    Dim intChannel As Integer   ' Numéro de chaîne.
    
    ' Arrête la minuterie.
    tmr2.Enabled = False
    ' Appelle la fonction pour mettre à jour les contrôles.
    ButtonManager frmVCR.cmdStop
    ' Efface l'écran.
    picTV.Cls
    ' Restaure l'ancienne chaîne.
    intChannel = SaveChannel(0)
    vntChannel = intChannel
    lblChannel.Caption = vntChannel
End Sub

Private Sub cmdUp_Click()
' Si le chiffre est correct, définit le numéro de la chaîne.
    If vntChannel < 13 Then
        vntChannel = vntChannel + 1
    Else
        vntChannel = 2
    End If
    
    ' Affecte la variable de la chaîne à l'écran.
     lblChannel.Caption = vntChannel
End Sub

Private Sub Form_Load()
    ' Affiche l'heure courante.
    lblTime.Caption = Format((Now), "hh:mm")
    ' Définit la hauteur de la feuille.
    frmVCR.Height = 6990
    img1.Visible = True
    ' Affiche la feuille.
    Me.Show
    ' Définit la chaîne de départ.
    vntChannel = 3
    lblChannel.Caption = vntChannel
End Sub

Private Sub Form_Unload(Cancel As Integer)
    ' Libère les références.
    Set Tape = Nothing
    Set Recorder = Nothing
    Set frmVCR = Nothing
End Sub

Private Sub lblChannel_Change()
    ' Change la couleur de l'écran basée sur la chaîne.
    Select Case vntChannel
        Case 2
            picTV.BackColor = QBColor(vcrGreen)
        Case 3
            picTV.BackColor = QBColor(vcrWhite)
        Case 4
            picTV.BackColor = QBColor(vcrRed)
        Case 5
            picTV.BackColor = QBColor(vcrMagenta)
        Case 6
            picTV.BackColor = QBColor(vcrYellow)
        Case 7
            picTV.BackColor = QBColor(vcrCyan)
        Case 8
            picTV.BackColor = QBColor(vcrGray)
        Case 9
            picTV.BackColor = QBColor(vcrLightBlue)
        Case 10
            picTV.BackColor = QBColor(vcrLightGreen)
        Case 11
            picTV.BackColor = QBColor(vcrLightCyan)
        Case 12
            picTV.BackColor = QBColor(vcrLightRed)
        Case 13
            picTV.BackColor = QBColor(vcrLightMagenta)
    End Select
    
    ' Efface l'écran.
    picTV.Cls
    ' Affiche la chaîne et l'heure.
    picTV.Print "Chaîne: " & vntChannel
    picTV.Print lblTime.Caption
End Sub

Private Sub tmr1_Timer()
    ' Met à jour l'affichage de l'heure.
    lblTime.Caption = Format((Now), "hh:mm")
    ' Si l'objet Recorder est activée.
    If Recorder.Enabled = True Then
        ' S'il est l'heure de lancer l'enregistrement.
        If Recorder.StartRecording = lblTime.Caption Then
            ' Démarre l'enregistrement.
            vntChannel = Recorder.Channel
            lblChannel.Caption = vntChannel
            ' Active le bouton d'enregistrement.
            cmdRec.Value = True
            ' Efface la propriété de la classe Recorder.
            Recorder.StartRecording = Empty
        End If
    Else
        ' S'il est l'heure d'arrêter l'enregistrement.
        If Recorder.StopRecording = lblTime.Caption Then
            ' Active le bouton Arrêt.
            cmdStop.Value = True
            ' Efface la propriété de la classe Recorder.
            Recorder.StopRecording = Empty
        End If
    End If
End Sub


Private Sub tmr2_Timer()
    Dim intWidth As Integer     ' Valeur de la largeur.
    Dim intLeft As Integer      ' Valeur de la position Gauche.
    Dim objImage As Control     ' Contrôle Image.
    
    ' Obtient la largeur de l'écran.
    intWidth = picTV.Width
    ' Appelle la méthode de la classe Tape
    ' pour regarder la "cassette".
    Tape.Animate intWidth
    
    ' Extrait la propriété Left de la classe.
    intLeft = Tape.Left
    ' Affiche la première ou la seconde image.
    If img1.Visible = True Then
        img1.Visible = False
        Set objImage = img2
    Else
        img1.Visible = True
        Set objImage = img1
    End If
    
    ' Efface l'écran.
    picTV.Cls
    ' Affiche la nouvelle image dans le nouvel emplacement.
    picTV.PaintPicture objImage.Picture, intLeft, 1200
End Sub



