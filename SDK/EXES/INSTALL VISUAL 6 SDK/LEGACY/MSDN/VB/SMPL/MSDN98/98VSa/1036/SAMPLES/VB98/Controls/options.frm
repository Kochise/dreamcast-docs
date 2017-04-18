VERSION 5.00
Begin VB.Form frmOptions 
   Caption         =   "Boutons d'options"
   ClientHeight    =   3825
   ClientLeft      =   3255
   ClientTop       =   2400
   ClientWidth     =   5040
   LinkTopic       =   "Form1"
   ScaleHeight     =   3825
   ScaleWidth      =   5040
   Begin VB.OptionButton opt686 
      Caption         =   "P&entium Pro"
      Height          =   255
      Left            =   360
      TabIndex        =   2
      Top             =   2040
      Width           =   1335
   End
   Begin VB.OptionButton opt586 
      Caption         =   "&Pentium"
      Height          =   255
      Left            =   360
      TabIndex        =   1
      Top             =   1560
      Width           =   1335
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Fermer"
      Height          =   495
      Left            =   3480
      TabIndex        =   5
      Top             =   2880
      Width           =   1095
   End
   Begin VB.OptionButton opt486 
      Caption         =   "&486"
      Height          =   255
      Left            =   360
      TabIndex        =   0
      Top             =   1080
      Value           =   -1  'True
      Width           =   1575
   End
   Begin VB.Frame fraSystem 
      Caption         =   "&Système d'exploitation"
      Height          =   1455
      Left            =   2400
      TabIndex        =   7
      Top             =   960
      Width           =   2175
      Begin VB.OptionButton optWin95 
         Caption         =   "&Windows 95"
         Height          =   255
         Left            =   360
         TabIndex        =   3
         Top             =   360
         Value           =   -1  'True
         Width           =   1335
      End
      Begin VB.OptionButton optWinNT 
         Caption         =   "Windows &NT"
         Height          =   255
         Left            =   360
         TabIndex        =   4
         Top             =   840
         Width           =   1335
      End
   End
   Begin VB.Label lblHelp 
      Caption         =   "Sélectionnez un processeur et un système d'exploitation."
      Height          =   615
      Left            =   360
      TabIndex        =   8
      Top             =   2880
      Width           =   2295
   End
   Begin VB.Label lblDisplay 
      BackColor       =   &H00C0C0C0&
      BorderStyle     =   1  'Fixed Single
      Height          =   495
      Left            =   120
      TabIndex        =   6
      Top             =   240
      Width           =   4695
   End
End
Attribute VB_Name = "frmOptions"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Déclare deux variables de type String pour stocker les légendes.
Dim strComputer As String
Dim strSystem As String

Sub DisplayCaption()
    ' Concatène la légende avec les deux variables de type String.
    lblDisplay.Caption = "Vous avez sélectionné un processeur " & _
     strComputer & " s'exécutant sur un système d'exploitation " & strSystem
End Sub


Private Sub cmdClose_Click()
    Unload Me   ' Décharge la feuille.
End Sub

Private Sub Form_Load()
    ' Provoque un événement Click pour chaque option par défaut,
    ' pour mettre à jour la légende du contrôle Label.
    opt486_Click
    optWin95_Click
End Sub

Private Sub opt486_Click()
    ' Affecte une valeur à la première variable de type String.
    strComputer = "486"
    ' Appel de la procédure DisplayCaption.
    Call DisplayCaption
End Sub


Private Sub opt586_Click()
    ' Affecte une valeur à la première variable de type String.
    strComputer = "Pentium"
    ' Appel de la procédure DisplayCaption.
    Call DisplayCaption
End Sub


Private Sub opt686_Click()
    ' Affecte une valeur à la première variable de type String.
    strComputer = "Pentium Pro"
    ' Appel de la procédure DisplayCaption.
    Call DisplayCaption
End Sub


Private Sub optWin95_Click()
    ' Affecte une valeur à la seconde variable de type String.
    strSystem = "Windows 95"
    ' Appel de la procédure DisplayCaption.
    Call DisplayCaption
End Sub


Private Sub optWinNT_Click()
    ' Affecte une valeur à la seconde variable de type String.
    strSystem = "Windows NT"
    ' Appel de la procédure DisplayCaption.
    Call DisplayCaption
End Sub


