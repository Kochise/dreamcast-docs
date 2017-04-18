VERSION 5.00
Begin VB.Form frmCheck 
   Caption         =   "Cases à cocher"
   ClientHeight    =   3075
   ClientLeft      =   2145
   ClientTop       =   1980
   ClientWidth     =   4530
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form4"
   ScaleHeight     =   3075
   ScaleWidth      =   4530
   Begin VB.CommandButton cmdClose 
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
      Left            =   3000
      TabIndex        =   3
      Top             =   2160
      Width           =   1095
   End
   Begin VB.CheckBox chkItalic 
      Caption         =   "&Italique"
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
      Top             =   1440
      Width           =   1215
   End
   Begin VB.CheckBox chkBold 
      Caption         =   "&Gras"
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
      TabIndex        =   1
      Top             =   960
      Width           =   1215
   End
   Begin VB.TextBox txtDisplay 
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
      Left            =   480
      TabIndex        =   0
      Text            =   "Exemple de texte"
      Top             =   360
      Width           =   3615
   End
   Begin VB.Label lblEnter 
      Caption         =   "Selectionnez les cases à cocher Gras et/ou Italique pour voir leurs effets sur le texte ci-dessus."
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
      Left            =   1800
      TabIndex        =   4
      Top             =   1080
      Width           =   2295
   End
End
Attribute VB_Name = "frmCheck"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub chkBold_Click()
' L'événement Click se produit lorsque l'état de la case à cocher change.
' La propriété Value indique le nouvel état de la case à cocher.
    If chkBold.Value = 1 Then     ' Si cochée.
        txtDisplay.FontBold = True
    Else                          ' Si non cochée.
        txtDisplay.FontBold = False
    End If
End Sub

Private Sub chkItalic_Click()
' L'événement Click se produit lorsque l'état de la case à cocher change.
' La propriété Value indique le nouvel état de la case à cocher.
    If chkItalic.Value = 1 Then     ' Si cochée.
        txtDisplay.FontItalic = True
    Else                          ' Si non cochée.
        txtDisplay.FontItalic = False
    End If
End Sub

Private Sub cmdClose_Click()
   Unload Me    ' Décharge cette feuille.
End Sub

