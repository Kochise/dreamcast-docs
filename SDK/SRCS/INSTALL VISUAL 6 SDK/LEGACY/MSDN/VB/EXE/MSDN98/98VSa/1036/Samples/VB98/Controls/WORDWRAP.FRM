VERSION 5.00
Begin VB.Form frmWordWrap 
   Caption         =   "AutoSize et WordWrap"
   ClientHeight    =   4320
   ClientLeft      =   1110
   ClientTop       =   1665
   ClientWidth     =   5760
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   ScaleHeight     =   4320
   ScaleWidth      =   5760
   Begin VB.CommandButton cmdCycle 
      Caption         =   "C&ycle"
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
      Left            =   480
      TabIndex        =   2
      Top             =   2520
      Width           =   1215
   End
   Begin VB.CheckBox chkAutoSize 
      Caption         =   "&AutoSize"
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
      Left            =   3840
      TabIndex        =   0
      Top             =   1080
      Width           =   1215
   End
   Begin VB.CheckBox chkWordWrap 
      Caption         =   "&WordWrap"
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
      Left            =   3840
      TabIndex        =   1
      Top             =   1680
      Width           =   1575
   End
   Begin VB.CommandButton cmdClose 
      Cancel          =   -1  'True
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
      Left            =   3840
      TabIndex        =   3
      Top             =   2520
      Width           =   1215
   End
   Begin VB.Label lblHelp 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Acivez les cases à cocher AutoSize et/ou WordWrap pour voir leurs effets sur le contrôle Label."
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
      Left            =   480
      TabIndex        =   5
      Top             =   3360
      Width           =   2775
   End
   Begin VB.Label lblDisplay 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Démonstration des propriétés AutoSize et WordWrap."
      Height          =   255
      Left            =   480
      TabIndex        =   4
      Top             =   480
      Width           =   1815
   End
End
Attribute VB_Name = "frmWordWrap"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Sub Display()
    ' Cette procédure change les caractéristiques de l'affichage du contrôle Label.

    ' Réinitialise l'exemple.
    lblDisplay.AutoSize = False
    lblDisplay.WordWrap = False
    lblDisplay.Width = 1695
    lblDisplay.Height = 225
    ' Vérifie pour WordWrap et Autosize.
    If chkWordWrap.Value = 1 Then
        lblDisplay.WordWrap = True
    End If
    If chkAutoSize.Value = 1 Then
        lblDisplay.AutoSize = True
    End If
End Sub

Private Sub chkAutoSize_Click()
    ' Appelle la procédure Display.
    Call Display
End Sub


Private Sub chkWordWrap_Click()
    ' Appelle la procédure Display.
    Call Display
End Sub


Private Sub cmdClose_Click()
   Unload Me    ' Décharge la feuille.
End Sub

Private Sub cmdCycle_Click()
    ' Permet de faire défiler une à une les quatre combinaisons possibles.
    
    ' Aucune case à cocher n'est activée.
    If chkAutoSize.Value = 0 And _
     chkWordWrap.Value = 0 Then
        ' Active la case à cocher AutoSize.
        chkAutoSize.Value = 1
    ' Les deux cases à cocher sont activées.
    ElseIf chkAutoSize.Value = 1 And _
     chkWordWrap.Value = 1 Then
        ' Désactive la case à cocher AutoSize et active la case à cocher WordWrap.
        chkAutoSize.Value = 0
        chkWordWrap.Value = 1
    ' Seule la case à cocher WordWrap est activée.
    ElseIf chkAutoSize.Value = 0 And _
     chkWordWrap.Value = 1 Then
        ' Désactive les deux cases à cocher.
        chkAutoSize.Value = 0
        chkWordWrap.Value = 0
    ' Seule la case à cocher AutoSize est activée.
    Else
        ' Active la case à cocher WordWrap, la case à cocher
        ' AutoSize étant déjà activée.
        chkWordWrap.Value = 1
    End If
End Sub


