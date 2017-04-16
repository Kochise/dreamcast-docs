VERSION 5.00
Begin VB.Form frmText 
   Caption         =   "Zone de texte"
   ClientHeight    =   4455
   ClientLeft      =   930
   ClientTop       =   1290
   ClientWidth     =   6915
   LinkTopic       =   "Form1"
   ScaleHeight     =   4455
   ScaleWidth      =   6915
   Begin VB.CommandButton cmdReset 
      Caption         =   "&Réinitialiser"
      Height          =   495
      Left            =   1560
      TabIndex        =   2
      Top             =   3720
      Width           =   1215
   End
   Begin VB.CommandButton cmdClose 
      Cancel          =   -1  'True
      Caption         =   "&Fermer"
      Height          =   495
      Left            =   4800
      TabIndex        =   3
      Top             =   3720
      Width           =   1215
   End
   Begin VB.Frame fraInsert 
      Caption         =   "Définit le point d'insertion"
      Height          =   2295
      Left            =   120
      TabIndex        =   5
      Top             =   1200
      Width           =   3735
      Begin VB.OptionButton optText 
         Caption         =   "Insertion de &texte"
         Height          =   255
         Left            =   360
         TabIndex        =   9
         Top             =   1800
         Width           =   2055
      End
      Begin VB.OptionButton optSelect 
         Caption         =   "&Sélection de tout le texte"
         Height          =   255
         Left            =   360
         TabIndex        =   8
         Top             =   1440
         Width           =   2055
      End
      Begin VB.OptionButton optInsert 
         Caption         =   "Point d'&insertion après le 5e caractère"
         Height          =   255
         Left            =   360
         TabIndex        =   7
         Top             =   1080
         Width           =   3255
      End
      Begin VB.OptionButton optEnd 
         Caption         =   "&Point d'insertion à la fin"
         Height          =   255
         Left            =   360
         TabIndex        =   6
         Top             =   720
         Width           =   1935
      End
      Begin VB.OptionButton optDefault 
         Caption         =   "&Valeurs par défaut"
         Height          =   255
         Left            =   360
         TabIndex        =   1
         Top             =   360
         Value           =   -1  'True
         Width           =   1815
      End
   End
   Begin VB.TextBox txtDisplay 
      Height          =   285
      HideSelection   =   0   'False
      Left            =   120
      TabIndex        =   0
      Text            =   "La valeur True est affectée à la propriété Multiline dans cet exemple."
      Top             =   480
      Width           =   3735
   End
   Begin VB.TextBox txtMulti 
      Height          =   735
      Left            =   4080
      MultiLine       =   -1  'True
      TabIndex        =   4
      TabStop         =   0   'False
      Text            =   "text.frx":0000
      Top             =   360
      Width           =   2655
   End
   Begin VB.Label lblHelp 
      Caption         =   "Sélectionnez une option pour voir ses effets sur la première zone de texte."
      Height          =   735
      Left            =   4320
      TabIndex        =   10
      Top             =   2160
      Width           =   2295
   End
End
Attribute VB_Name = "frmText"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False




Private Sub cmdClose_Click()
    Unload Me   ' Décharge la feuille.
End Sub

Private Sub cmdReset_Click()
    ' Restaure le texte original.
    txtDisplay.Text = " La valeur True est affectée à la propriété Multiline dans cet exemple "
    ' Réinitialise le groupe d'options avec le bouton par défaut.
    optDefault.Value = True
End Sub

Private Sub optDefault_Click()
    ' Place le point d'insertion au début.
    txtDisplay.SelStart = 0
    
    ' Attribue le focus à la zone de texte. Ainsi, vous pouvez
    ' voir le résultat de vos valeurs.
    txtDisplay.SetFocus
End Sub

Private Sub optEnd_Click()
    ' Trouve la longueur de la chaîne et place le point d'insertion à la fin.
    txtDisplay.SelStart = Len(txtDisplay.Text)
    
    ' Attribue le focus à la zone de texte. Ainsi, vous pouvez
    ' voir le résultat de vos valeurs.
    txtDisplay.SetFocus
End Sub


Private Sub optInsert_Click()
    ' place le point d'insertion après le cinquième caractère.
    txtDisplay.SelStart = 5
        
    ' Attribue le focus à la zone de texte. Ainsi, vous pouvez
    ' voir le résultat de vos valeurs.
    txtDisplay.SetFocus
End Sub


Private Sub optSelect_Click()
    ' place le point d'insertion au début.
    txtDisplay.SelStart = 0
    ' Trouve la longueur de la chaîne et sélectionne ce nombre de caractères.
    txtDisplay.SelLength = Len(txtDisplay.Text)

    ' Attribue le focus à la zone de texte. Ainsi, vous pouvez
    ' voir le résultat de vos valeurs.
    txtDisplay.SetFocus
End Sub


Private Sub optText_Click()
    ' Insère "NOUVELLE CHAÎNE" au point d'insertion, si le texte est sélectionné, il sera remplacé.
txtDisplay.SelText = " NOUVELLE CHAÎNE"
    
    ' Attribue le focus à la zone de texte. Ainsi, vous pouvez
    ' voir le résultat de vos valeurs.
    txtDisplay.SetFocus
End Sub

