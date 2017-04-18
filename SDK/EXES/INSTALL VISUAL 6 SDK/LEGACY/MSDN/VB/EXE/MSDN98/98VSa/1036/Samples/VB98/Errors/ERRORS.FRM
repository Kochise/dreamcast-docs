VERSION 5.00
Begin VB.Form frmErrors 
   Caption         =   "Exemple de gestion d'erreurs"
   ClientHeight    =   2670
   ClientLeft      =   1140
   ClientTop       =   1530
   ClientWidth     =   5295
   LinkTopic       =   "Form1"
   ScaleHeight     =   2670
   ScaleWidth      =   5295
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdMakeError 
      Caption         =   "Générer une erreur"
      Height          =   375
      Left            =   2760
      TabIndex        =   4
      Top             =   1920
      Width           =   2175
   End
   Begin VB.CommandButton cmdCentral 
      Caption         =   "Gestion d'erreurs centralisée"
      Height          =   375
      Left            =   360
      TabIndex        =   3
      Top             =   1920
      Width           =   2175
   End
   Begin VB.TextBox txtFileSpec 
      Height          =   375
      Left            =   480
      TabIndex        =   2
      Text            =   "*:\error.xyz"
      Top             =   600
      Width           =   3495
   End
   Begin VB.CommandButton cmdInline 
      Caption         =   "Gestion d'erreurs en ligne"
      Height          =   375
      Left            =   2760
      TabIndex        =   1
      Top             =   1320
      Width           =   2175
   End
   Begin VB.CommandButton cmdNone 
      Caption         =   "Pas de gestion d'erreurs"
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Top             =   1320
      Width           =   2175
   End
   Begin VB.Label Label1 
      Caption         =   "Entrez ici les spécifications d'un fichier non valide: "
      Height          =   255
      Left            =   480
      TabIndex        =   5
      Top             =   360
      Width           =   3735
   End
End
Attribute VB_Name = "frmErrors"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdCentral_Click()
    Dim strErrnum As String
    Dim intErr As Integer
    Dim intReturn As Integer
    
    On Error GoTo CallFileErrors
    strErrnum = InputBox("Entrez un numéro d'erreur", "Erreurs", "68")
    intErr = Val(strErrnum)
    Err.Raise Number:=intErr
    Exit Sub
CallFileErrors:
    intReturn = FileErrors()
    If intReturn = 0 Then
        Resume
    ElseIf intReturn = 1 Then
        Resume Next
    ElseIf intReturn = 2 Then
        MsgBox "Erreur irrécupérable"
        End
    Else
        MsgBox "Erreur inconnue"
        Resume
    End If
        
End Sub

Private Sub cmdInline_Click()
    Dim blnResult As Boolean
    
    blnResult = FileExists2(txtFileSpec.Text)
End Sub


Private Sub cmdMakeError_Click()
    Err.Raise Number:=71        ' Simule l'erreur "Disque non prêt".
End Sub

Private Sub cmdNone_Click()
    Dim blnResult As Boolean
    
    blnResult = FileExists1(txtFileSpec.Text)
End Sub

Function FileExists1(filename) As Boolean
    ' Pas de gestion d'erreurs.
    FileExists1 = (Dir(filename) <> "")
End Function
Function FileExists2(filename) As Boolean
    Dim Msg As String
    ' Active la récupération d'erreurs. Si une erreur est détectée le gestionnaire d'erreurs la traite.
    On Error GoTo CheckError
        FileExists2 = (Dir(filename) <> "")
        ' Évite l'exécution de la gestion d'erreurs si aucune erreur ne se produit.
        Exit Function

CheckError:                 ' Se positionne ici, si une erreur se produit.
    ' Définit des constantes représentant des codes d'erreur intrinsèques Visual Basic.
    Const mnErrDiskNotReady = 71, mnErrDeviceUnavailable = 68
    ' vbExclamation, vbOK, vbCancel, vbCritical, et vbOKCancel sont des constantes
    ' définies dans la bibliothèque de types VBA.
    If (Err.Number = mnErrDiskNotReady) Then
        Msg = "Insérer une disquette dans le lecteur."
        ' Affiche la boîte de message avec une icône exclamation et les boutons OK et Annuler.
    If MsgBox(Msg, vbExclamation & vbOKCancel) = vbOK Then
            Resume
        Else
            Resume Next
        End If
    ElseIf Err.Number = mnErrDeviceUnavailable Then
        Msg = "Ce lecteur ou ce chemin n'existe pas: " & filename
        MsgBox Msg, vbExclamation
        Resume Next
    Else
        Msg = "Une erreur inattendue s'est produite:  #" & Str(Err.Number) & ", " & Err.Description
        ' Affiche le message d'erreur avec une icône Stop et un bouton OK.
        MsgBox Msg, vbCritical
        Stop
    End If
    Resume
End Function

