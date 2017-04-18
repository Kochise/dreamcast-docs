VERSION 5.00
Begin VB.Form frmCYOCC 
   Caption         =   "Création de vos propres classes Collection"
   ClientHeight    =   1920
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4845
   LinkTopic       =   "Form2"
   ScaleHeight     =   1920
   ScaleWidth      =   4845
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdBricks 
      Caption         =   "Maison en briques"
      Height          =   375
      Left            =   750
      TabIndex        =   2
      Top             =   1200
      Width           =   3255
   End
   Begin VB.CommandButton cmdSticks 
      Caption         =   "Maison en bois"
      Height          =   375
      Left            =   750
      TabIndex        =   1
      Top             =   720
      Width           =   3255
   End
   Begin VB.CommandButton cmdStraw 
      Caption         =   "Maison en paille"
      Height          =   375
      Left            =   750
      TabIndex        =   0
      Top             =   240
      Width           =   3255
   End
End
Attribute VB_Name = "frmCYOCC"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
' La feuille frmCYOCC affiche ses feuilles adjacentes en utilisant
'   les variables globales cachées créées par Visual
'   Basic pour chaque classe de feuille
'   (frmStraw, frmSticks et frmBricks,
'   dans ce cas). La variable globale cachée
'   est décrite à la section "Cycle de vie des feuilles
'   Visual Basic" des Manuels en ligne.
'
' Les feuilles sont affichées de manière non modale, et
'   frmCYOCC se définit lui-même (Me) comme le
'   propriétaire de chaque feuille. Ainsi,
'   ses feuilles apparaissent toujours au dessus
'   de la feuille frmCYOCC.

' Maison en paille -- l'objet Collection public.
Private Sub cmdStraw_Click()
    frmStraw.Show vbModeless, Me
End Sub

' Maison en bois -- l'objet Collection privé.
Private Sub cmdSticks_Click()
    frmSticks.Show vbModeless, Me
End Sub

' Maison en briques -- la classe Collection.
Private Sub cmdBricks_Click()
    frmBricks.Show vbModeless, Me
End Sub

Private Sub Form_Unload(Cancel As Integer)
    ' Si des feuilles non modales sont
    '   toujours chargées, fermez-les.
    If Not frmBricks Is Nothing Then
        Unload frmBricks
        Set frmBricks = Nothing
    End If
    If Not frmSticks Is Nothing Then
        Unload frmBricks
        Set frmBricks = Nothing
    End If
    If Not frmStraw Is Nothing Then
        Unload frmBricks
        Set frmBricks = Nothing
    End If
    
    ' Affecte la valeur Nothing à la variable globale
    ' cachée frmCYOCC, ce qui libère ses ressources.
    Set frmCYOCC = Nothing
End Sub
