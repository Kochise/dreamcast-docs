VERSION 1.0 CLASS 
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsTape"
Attribute VB_Base = "0{FCFB3D2A-A0FA-1068-A738-08002B3371B5}"
Attribute VB_Creatable = False
Attribute VB_TemplateDerived = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Customizable = False
'**********************************************
' Module de classe pour l'exemple d'application VCR.
' Agit comme mécanisme d'entraînement de la bande pour le
' magnétoscope et les contrôles "playback" des images.
'**********************************************

Option Explicit

Public Left As Integer      ' Dernier emplacement.
Public Forward As Boolean   ' Sens de défilement de la bande.
Public Speed As Integer     ' Vitesse de la bande.
'**********************************************
' Sujet:    Calcule les nouvelles coordonnées pour
'           chaque étape de l'animation.
' Entrées:  Width: la largeur de la zone d'image
'           où est affichée l'animation. 
'**********************************************
Public Sub Animate(Width As Integer)
    If Forward = True Then
        ' déplacement avant - incrémente la partie de gauche en cours
        ' sauf si on approche du bord droit.
        If Left < Width - 50 Then
            Left = Left + 50
        Else
            Left = 0
        End If
    Else
        ' déplacement avant - décrémente la partie de gauche en cours
        ' sauf si on approche du bord gauche.
        If Left > 0 Then
            Left = Left - 50
        Else
            Left = Width - 50
        End If
    End If
End Sub

Private Sub Class_Initialize()
    ' Initialise les propriétés de classe.
    Forward = True
    Left = 0
    Speed = 300
End Sub
