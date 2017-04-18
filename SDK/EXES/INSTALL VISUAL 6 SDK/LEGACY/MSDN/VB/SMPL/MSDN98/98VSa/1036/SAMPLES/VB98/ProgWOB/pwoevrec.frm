VERSION 5.00
Begin VB.Form frmReceiver 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Message reçu par l'événement de gestion Broadcast"
   ClientHeight    =   690
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5550
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   690
   ScaleWidth      =   5550
   StartUpPosition =   3  'Windows Default
   Begin VB.CheckBox chkReceive 
      Caption         =   "&Recevoir les messages"
      Height          =   255
      Left            =   3030
      TabIndex        =   2
      Top             =   360
      Width           =   2445
   End
   Begin VB.CheckBox chkGarble 
      Caption         =   "&Tronquer les messages"
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   360
      Width           =   2895
   End
   Begin VB.Label lblMessage 
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5355
   End
End
Attribute VB_Name = "frmReceiver"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
' La variable Source est déclarée au
'   moyen du mot clé WithEvents; les
'   événements de l'objet frmEvents qui lui
'   ont été affectés peuvent donc être gérés
'   (reportez-vous à la procédure de l'événement
'   Source_Broadcast). Lorsque la référence est
'   affectée, Visual Basic relie l'objet à la
'   procédure de l'événement.
Private WithEvents Source As frmEvents
Attribute Source.VB_VarHelpID = -1

Private Sub chkReceive_Click()
    If chkReceive = vbChecked Then
        Set Source = frmEvents
    Else
        ' L'affectation de la valeur Nothing à
        '   la variable WithEvents déconnecte
        '   la procédure de l'événement de l'objet
        '   frmEvents.
        Set Source = Nothing
    End If
End Sub

Private Sub Form_Load()
    chkReceive = vbChecked
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Set Source = Nothing
End Sub

' Procédure d'événement pour l'événement Broadcast.
'   L'argument Message étant ByRef,
'   il peut être endommagé -- et ces modifications
'   seront vues par tous les gestionnaires suivants
'   de l'événement.
Private Sub Source_Broadcast(Message As String)
    Dim intCt As Integer
    lblMessage = Message
    '
    ' Si l'option Tronqué est cochée, tronque
    '   le message.
    If chkGarble = vbChecked Then
        ' Utilise une étape aléatoire qui touche
        '   entre un caractère sur trois (minimum) et un
        '   caractère sur neuf (maximum).
        For intCt = 1 To Len(Message) Step (Int(7 * Rnd) + 3)
            ' Pour tous les caractères tronqués,
            '   remplace la valeur ASCII par un nombre
            '   aléatoire compris entre -3 et +3.
            Mid$(Message, intCt, 1) = Chr$(Asc(Mid$(Message, intCt, 1)) + Int(7 * Rnd) - 3)
        Next
    End If
End Sub
