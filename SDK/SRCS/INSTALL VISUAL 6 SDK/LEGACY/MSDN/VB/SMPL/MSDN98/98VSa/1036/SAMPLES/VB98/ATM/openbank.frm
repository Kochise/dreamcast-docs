VERSION 5.00
Begin VB.Form frmOpen 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Distributeur automatique de billets (D.A.B.)"
   ClientHeight    =   3765
   ClientLeft      =   2265
   ClientTop       =   1980
   ClientWidth     =   5085
   Icon            =   "openbank.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3765
   ScaleWidth      =   5085
   Begin VB.Frame Frame 
      Caption         =   "Choisissez une langue :"
      Height          =   2175
      Left            =   240
      TabIndex        =   10
      Top             =   1320
      Width           =   4575
      Begin VB.CommandButton Command1 
         Caption         =   "English"
         Height          =   375
         Left            =   840
         TabIndex        =   0
         Top             =   480
         Width           =   1095
      End
      Begin VB.CommandButton Command2 
         Caption         =   "Francais"
         Height          =   375
         Left            =   840
         TabIndex        =   1
         Top             =   960
         Width           =   1095
      End
      Begin VB.CommandButton Command3 
         Caption         =   "Deutsch"
         Height          =   375
         Left            =   840
         TabIndex        =   2
         Top             =   1440
         Width           =   1095
      End
      Begin VB.CommandButton Command4 
         Caption         =   "Italiano"
         Height          =   375
         Left            =   3000
         TabIndex        =   3
         Top             =   480
         Width           =   1095
      End
      Begin VB.CommandButton Command5 
         Caption         =   "Espanol"
         Height          =   375
         Left            =   3000
         TabIndex        =   4
         Top             =   960
         Width           =   1095
      End
      Begin VB.CommandButton Command6 
         Caption         =   "Japan"
         Height          =   375
         Left            =   3000
         TabIndex        =   5
         Top             =   1440
         Visible         =   0   'False
         Width           =   1095
      End
      Begin VB.Image Image 
         Height          =   375
         Index           =   0
         Left            =   360
         Picture         =   "openbank.frx":000C
         Stretch         =   -1  'True
         Top             =   480
         Width           =   375
      End
      Begin VB.Image Image 
         Height          =   375
         Index           =   1
         Left            =   360
         Picture         =   "openbank.frx":0316
         Stretch         =   -1  'True
         Top             =   960
         Width           =   375
      End
      Begin VB.Image Image 
         Height          =   375
         Index           =   2
         Left            =   360
         Picture         =   "openbank.frx":0620
         Stretch         =   -1  'True
         Top             =   1440
         Width           =   375
      End
      Begin VB.Image Image 
         Height          =   375
         Index           =   3
         Left            =   2520
         Picture         =   "openbank.frx":092A
         Stretch         =   -1  'True
         Top             =   480
         Width           =   375
      End
      Begin VB.Image Image 
         Height          =   375
         Index           =   4
         Left            =   2520
         Picture         =   "openbank.frx":0C34
         Stretch         =   -1  'True
         Top             =   960
         Width           =   375
      End
      Begin VB.Image Image 
         Height          =   375
         Index           =   5
         Left            =   2520
         Picture         =   "openbank.frx":0F3E
         Stretch         =   -1  'True
         Top             =   1440
         Visible         =   0   'False
         Width           =   375
      End
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      Caption         =   """Service personnalisé partout dans le monde"""
      Height          =   240
      Index           =   3
      Left            =   15
      TabIndex        =   9
      Top             =   840
      Width           =   5040
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      Caption         =   "Distributeur automatique de billets"
      Height          =   240
      Index           =   2
      Left            =   135
      TabIndex        =   8
      Top             =   600
      Width           =   4700
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      Caption         =   "Bienvenue à la"
      Height          =   240
      Index           =   0
      Left            =   135
      TabIndex        =   7
      Top             =   120
      Width           =   4700
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      Caption         =   "BANQUE MONDIALE DES VOYAGEURS"
      Height          =   240
      Index           =   1
      Left            =   135
      TabIndex        =   6
      Top             =   360
      Width           =   4700
   End
End
Attribute VB_Name = "frmOpen"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Chaque bouton de commande représente une langue. Si l'utilisateur choisit l'anglais,
' l'application charge les arguments dont l'identificateur se trouve entre 16 et 47.
Option Explicit

Sub command1_click()
    i = 16              ' L'utilisateur a choisi l'anglais.
    frmInput.Show vbModal
End Sub

Sub Command2_Click()
    i = 48              ' L'utilisateur a choisi le français.
    frmInput.Show vbModal
End Sub

Sub Command3_Click()
    i = 80              ' L'utilisateur a choisi l'allemand.
    frmInput.Show vbModal
End Sub

Sub Command4_Click()
    i = 112             ' L'utilisateur a choisi l'italien.
    frmInput.Show vbModal
End Sub

Sub Command5_Click()
    i = 144              ' L'utilisateur a choisi l'espagnol.
    frmInput.Show vbModal
End Sub

Sub Command6_Click()     ' Le japonais est disponible uniquement avec un système DCBS.
    i = 176              ' L'utilisateur a choisi le japonais.
    frmInput.Show vbModal
End Sub

Private Sub Form_Load()
    Dim iIndex As Byte
    
    ' Initialise la table de conversion des monnaies.
    ConversionTable_Initialize
    
    ' Initialise l'icône du curseur de la souris pour les boutons.
    Cursor_Initialize
    SetCursor Command1
    SetCursor Command2
    SetCursor Command3
    SetCursor Command4
    SetCursor Command5
    SetCursor Command6
    
    ' Pour DBCS, le nom de police doit être spécifié par VB au moment
    ' du chargement du projet. Pour que cet exemple fonctionne dans tous
    ' les cas, il est nécessaire de spécifier les propriétés des polices par programme.

    For iIndex = 0 To 3
        Label(iIndex).FontSize = 10
        Label(iIndex).FontBold = True
    Next iIndex
    
    ' Pour DBCS, les plateformes des langues d'Extrême Orient ne sont pas en
    ' mesure de lire les caractères HighAnsi. Puisque certains de ces caractères sont
    ' utilisés sur les boutons des langues, il est nécessaire de les modifier dans ce cas.

    If IMEStatus = vbIMENoOp Then
        Command2.Caption = "Français"
        Command5.Caption = "Español"
    End If
End Sub
