VERSION 5.00
Begin VB.Form frmFriends 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Type Friend passant des types définis par l'utilisateur"
   ClientHeight    =   3210
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5355
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3210
   ScaleWidth      =   5355
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtString 
      Height          =   285
      Left            =   1080
      TabIndex        =   5
      Top             =   2640
      Width           =   4095
   End
   Begin VB.TextBox txtLong 
      Height          =   285
      Left            =   1080
      MaxLength       =   9
      TabIndex        =   3
      Top             =   2160
      Width           =   1815
   End
   Begin VB.TextBox txtInteger 
      Height          =   285
      Left            =   1080
      MaxLength       =   4
      TabIndex        =   1
      Top             =   1680
      Width           =   1215
   End
   Begin VB.CommandButton cmdMethod 
      Caption         =   "&Méthode Friend"
      Height          =   375
      Left            =   3120
      TabIndex        =   7
      Top             =   2040
      Width           =   2055
   End
   Begin VB.CommandButton cmdProperty 
      Caption         =   "&Propriété Friend"
      Height          =   375
      Left            =   3120
      TabIndex        =   6
      Top             =   1560
      Width           =   2055
   End
   Begin VB.Label Label4 
      Alignment       =   1  'Right Justify
      Caption         =   "&Chaîne:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   2640
      Width           =   855
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      Caption         =   "Entier &long:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   2160
      Width           =   855
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "&Entier:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   1680
      Width           =   855
   End
   Begin VB.Label Label1 
      Caption         =   $"PWOFrien.frx":0000
      Height          =   1215
      Left            =   120
      TabIndex        =   8
      Top             =   120
      Width           =   5175
   End
End
Attribute VB_Name = "frmFriends"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
' Montre les propriétés et les méthodes Friend passant
'   des types définis par l'utilisateur entre les objets.

Private mtc1 As TestClass
Private mtc2 As TestClass
    
' Utilise des propriétés pour affecter/accéder à un type défini par l'utilisateur.
Private Sub cmdProperty_Click()
    ' La méthode d'assistance SetDemoParts
    '   affecte les contenus des zones de texte
    '   au type défini par l'utilisateur dans le
    '   premier objet TestClass; quelque chose
    '   pourra ainsi être passé au deuxième objet
    '   TestClass.
    Call mtc1.SetDemoParts(CInt("0" & txtInteger), _
        CLng("0" & txtLong), txtString)
    '
    ' Affiche les éléments de type défini par l'utilisateur du premier objet TestClass
    '   avant d'effectuer le passage.
    Call mtc1.ShowDemo("Passage d'un UDT en utilisant une propriété", "Passer à partir de:")
    '
    ' Affecte directement le type défini par l'utilisateur du premier
    '   objet TestClass à celui du deuxième
    '   objet TestClass, en utilisant la
    '   propriété Demo.
    mtc2.Demo = mtc1.Demo
    '
    ' Affiche les éléments de type défini par l'utilisateur du
    '   deuxième objet TestClass.
    Call mtc2.ShowDemo("Passage d'un UDT en utilisant une propriété", "Passé à:")
    '
    ' Lorsque la procédure se termine, mtc1 et mtc2
    '   passent hors de portée et les objets
    '   TestClass se terminent.
End Sub

' Utilise des méthodes pour affecter/accéder à un type défini par l'utilisateur.
Private Sub cmdMethod_Click()
    ' La méthode d'assistance SetDemoParts
    '   affecte les contenus des zones de texte
    '   au type défini par l'utilisateur dans le
    '   premier objet TestClass; quelque chose
    '   pourra ainsi être passé au deuxième objet
    '   TestClass.
    Call mtc1.SetDemoParts(CInt("0" & txtInteger), _
        CLng("0" & txtLong), txtString)
    '
    ' Affiche les éléments de type défini par l'utilisateur du
    '   premier objet TestClass avant d'effectuer le passage.
    Call mtc1.ShowDemo("Passage d'un UDT en utilisant une méthode", "Passer à partir de:")
    '
    ' La méthode GetDemo du premier objet
    '   TestClass renvoie le type défini par l'utilisateur, qui est
    '   passé à la méthode SetDemo du deuxième objet TestClass.
    Call mtc2.SetDemo(mtc1.GetDemo)
    '
    ' Affiche les éléments de type défini par l'utilisateur du
    ' deuxième objet TestClass.
    Call mtc2.ShowDemo("Passage d'un UDT en utilisant une méthode ", "Passé à:")
    '
    ' Lorsque la procédure se termine, mtc1 et mtc2
    '   passent hors de portée et les objets
    '   TestClass se terminent.
End Sub

Private Sub Form_Load()
    ' Crée les objets TestClass.
    Set mtc1 = New TestClass
    Set mtc2 = New TestClass
End Sub

Private Sub Form_Unload(Cancel As Integer)
    ' Libère les ressources de la feuille.
    Set frmFriends = Nothing
End Sub

Private Sub txtInteger_KeyPress(KeyAscii As Integer)
    Select Case KeyAscii
        Case 48 To 57     ' Autorise les chiffres.
        Case 8            ' Autorise les retours arrière.
        Case Else         ' Supprime tout le reste.
            Beep
            KeyAscii = 0
    End Select
End Sub

Private Sub txtLong_KeyPress(KeyAscii As Integer)
    Select Case KeyAscii
        Case 48 To 57     ' Autorise les chiffres.
        Case 8            ' Autorise les retours arrière.
        Case Else         ' Supprime tout le reste.
            Beep
            KeyAscii = 0
    End Select
End Sub

