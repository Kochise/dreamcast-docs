VERSION 5.00
Begin VB.Form frmFind 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Rechercher"
   ClientHeight    =   1485
   ClientLeft      =   1500
   ClientTop       =   1875
   ClientWidth     =   4950
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
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1485
   ScaleWidth      =   4950
   Begin VB.Frame Frame1 
      Caption         =   "Direction"
      Height          =   735
      Left            =   1320
      TabIndex        =   3
      Top             =   720
      Width           =   2295
      Begin VB.OptionButton optDirection 
         Caption         =   "Vers le &bas"
         Height          =   375
         Index           =   1
         Left            =   1200
         TabIndex        =   5
         ToolTipText     =   "Rechercher vers la fin du document"
         Top             =   240
         Value           =   -1  'True
         Width           =   975
      End
      Begin VB.OptionButton optDirection 
         Caption         =   "&Vers le haut"
         Height          =   375
         Index           =   0
         Left            =   120
         TabIndex        =   4
         ToolTipText     =   "Rechercher vers le début du document"
         Top             =   240
         Width           =   975
      End
   End
   Begin VB.CheckBox chkCase 
      Caption         =   "Respecter la &casse"
      Height          =   495
      Left            =   120
      TabIndex        =   2
      ToolTipText     =   "Prendre en compte les différences majuscules/minuscules"
      Top             =   720
      Width           =   1335
   End
   Begin VB.TextBox txtFind 
      Height          =   500
      Left            =   1200
      TabIndex        =   1
      ToolTipText     =   "Texte à rechercher"
      Top             =   120
      Width           =   2415
   End
   Begin VB.CommandButton cmdcancel 
      Cancel          =   -1  'True
      Caption         =   "&Annuler"
      Height          =   372
      Left            =   3720
      TabIndex        =   7
      ToolTipText     =   "Retourner au bloc-note"
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton cmdFind 
      Caption         =   "&Rechercher"
      Default         =   -1  'True
      Height          =   372
      Left            =   3720
      TabIndex        =   6
      ToolTipText     =   "Commencer la recherche"
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Rec&hercher:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   1095
   End
End
Attribute VB_Name = "frmFind"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'*** Boîte de dialogue Rechercher (du texte).      ***
'*** Créé pour l'exemple d'application SDI Notepad ***
'*** Variables: gFindCase (permutte le respect de  ***
'*** la casse); gFindString (texte à rechercher);  ***
'*** gFindDirection (permutte la direction de la   ***
'*** recherche); gFirstTime (permutte le départ au ***
'*** début du texte)                               ***
'**************************************************

Option Explicit

Private Sub chkCase_Click()
    ' Affecte une valeur à la variable publique.
    gFindCase = chkCase.Value
End Sub

Private Sub cmdCancel_Click()
    ' Enregistre les valeurs dans les variables publiques.
    gFindString = txtFind.Text
    gFindCase = chkCase.Value
    ' Décharger le dialogue de recherche.
    Unload frmFind
End Sub

Private Sub cmdFind_Click()
    ' Affecte la chaîne à une variable publique.
    gFindString = txtFind.Text
    FindIt
End Sub

Private Sub Form_Load()
    ' Désactiver la bouton Rechercher - pas de texte à rechercher pour l'instant.
    cmdFind.Enabled = False
    ' Lire la variable publique et définir le bouton d'option.
    optDirection(gFindDirection).Value = 1
End Sub

Private Sub optDirection_Click(Index As Integer)
    ' Affecte une valeur à la variable publique.
    gFindDirection = Index
End Sub

Private Sub txtFind_Change()
    ' Définir la variable publique.
    gFirstTime = True
    ' Si la zone de texte est vide, désactiver le bouton Rechercher.
    If txtFind.Text = "" Then
        cmdFind.Enabled = False
    Else
        cmdFind.Enabled = True
    End If
End Sub

