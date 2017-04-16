VERSION 5.00
Begin VB.Form frmInput 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   3645
   ClientLeft      =   3615
   ClientTop       =   2625
   ClientWidth     =   5220
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3645
   ScaleWidth      =   5220
   Begin VB.Frame fraAccount 
      Caption         =   "fraAccount"
      Height          =   1215
      Left            =   1080
      TabIndex        =   8
      Top             =   960
      Width           =   3975
      Begin VB.OptionButton optChecking 
         Caption         =   "optChecking"
         Height          =   255
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Value           =   -1  'True
         Width           =   3495
      End
      Begin VB.OptionButton optSavings 
         Caption         =   "optSavings"
         Height          =   255
         Left            =   240
         TabIndex        =   2
         Top             =   720
         Width           =   3495
      End
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "cmdOK"
      Default         =   -1  'True
      Height          =   375
      Left            =   3960
      TabIndex        =   4
      Top             =   3120
      Width           =   1095
   End
   Begin VB.TextBox txtUSDollarsAmt 
      Height          =   285
      Left            =   1080
      TabIndex        =   3
      Top             =   2640
      Width           =   2295
   End
   Begin VB.TextBox Text1 
      Height          =   285
      HideSelection   =   0   'False
      IMEMode         =   3  'DISABLE
      Left            =   1080
      PasswordChar    =   "*"
      TabIndex        =   0
      Top             =   480
      Width           =   3975
   End
   Begin VB.Label lblUSDollars 
      Caption         =   "Dollars US"
      Height          =   195
      Left            =   3480
      TabIndex        =   7
      Top             =   2685
      Width           =   1575
   End
   Begin VB.Image imgFlag 
      BorderStyle     =   1  'Fixed Single
      Height          =   735
      Left            =   120
      Stretch         =   -1  'True
      Top             =   120
      Width           =   735
   End
   Begin VB.Label lblAmount 
      Caption         =   "lblAmount"
      Height          =   195
      Left            =   1080
      TabIndex        =   6
      Top             =   2400
      Width           =   3975
   End
   Begin VB.Label lblPINCode 
      Caption         =   "lblPINCode"
      Height          =   195
      Left            =   1080
      TabIndex        =   5
      Top             =   240
      Width           =   3975
   End
End
Attribute VB_Name = "frmInput"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

' Cet exemple d'application démontre comment utiliser des fichiers de ressources
' pour localiser une application Visual Basic. Il ne traite pas les erreurs et la validation des données.

' Cette application utilise la fonction LoadResPicture pour charger une image,
' LoadResString pour charger une chaîne de caractères, et LoadResData pour lire
' un fichier de son (.WAV) du fichier de ressources, en fonction du bouton de
' commande choisi par l'utilisateur (dans frmOpen).
Option Explicit

Sub Form_Load()
    imgFlag = LoadResPicture(i, vbResBitmap)
    Caption = LoadResString(i)
    lblPINCode = LoadResString(1 + i)
    fraAccount = LoadResString(2 + i)
    optChecking.Caption = LoadResString(3 + i)
    optSavings.Caption = LoadResString(4 + i)
    lblAmount = LoadResString(5 + i)
    cmdOK.Caption = LoadResString(6 + i)
    SetCursor cmdOK
End Sub

Sub cmdOK_click()
    MsgBox LoadResString(7 + i)   ' Affiche un message de processus.
    frmAmountWithdrawn.Show vbModal
    Unload Me
End Sub

Private Sub Form_Unload(Cancel As Integer)
    EndPlaySound
End Sub
