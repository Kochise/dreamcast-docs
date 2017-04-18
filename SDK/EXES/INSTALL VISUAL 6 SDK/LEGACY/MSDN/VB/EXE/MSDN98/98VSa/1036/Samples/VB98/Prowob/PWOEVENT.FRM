VERSION 5.00
Begin VB.Form frmEvents 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Déclenchement et gestion des événements"
   ClientHeight    =   4245
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4710
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4245
   ScaleWidth      =   4710
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdAddForm 
      Caption         =   "Ajouter un &destinataire"
      Height          =   375
      Left            =   2790
      TabIndex        =   3
      Top             =   3360
      Width           =   1785
   End
   Begin VB.TextBox txtMessage 
      Height          =   285
      Left            =   120
      TabIndex        =   2
      Top             =   3000
      Width           =   4455
   End
   Begin VB.CommandButton cmdPercentDone 
      Caption         =   "Démarrer une &tâche longue qui utilise un événement pour transmettre la progression"
      Height          =   615
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   4215
   End
   Begin VB.Label Label2 
      Caption         =   "Message après que tous les destinataires l'ont géré:"
      Height          =   375
      Left            =   120
      TabIndex        =   6
      Top             =   3360
      Width           =   2295
   End
   Begin VB.Label lblPercentDone 
      Height          =   255
      Left            =   360
      TabIndex        =   5
      Top             =   960
      Width           =   4095
   End
   Begin VB.Label lblEcho 
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   3840
      Width           =   4455
   End
   Begin VB.Label Label1 
      Caption         =   $"PWOEvent.frx":0000
      Height          =   1335
      Left            =   120
      TabIndex        =   1
      Top             =   1560
      Width           =   4455
   End
   Begin VB.Line Line1 
      X1              =   120
      X2              =   4560
      Y1              =   1440
      Y2              =   1440
   End
End
Attribute VB_Name = "frmEvents"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

' ========================================
'     Déclarations pour l'exemple Broadcast
'
' L'événement Broadcast a un argument,
'   le message à envoyer. L'argument
'   est ByRef; les destinataires peuvent donc le changer.
Event Broadcast(Message As String)

' Collection des destinataires.
Private mcolReceivers As New Collection

' ========================================
'       Déclarations et code pour le
'           pourcentage déjà réalisé de l'exemple.
'
Private WithEvents mWidget As Widget
Attribute mWidget.VB_VarHelpID = -1
Private mblnCancel As Boolean

Private Sub mWidget_PercentDone(ByVal Percent As Double, Cancel As Boolean)
    lblPercentDone.Caption = CInt(100 * Percent) & " % effectué"
    DoEvents
    If mblnCancel Then Cancel = True
End Sub

Private Sub cmdPercentDone_Click()
    Static blnProcessing As Boolean
    If blnProcessing Then
        mblnCancel = True
    Else
        blnProcessing = True
        cmdPercentDone.Caption = "&Annuler la tâche"
        mblnCancel = False
        lblPercentDone.Caption = "0 % effectué"
        lblPercentDone.Refresh
        
        ' Crée un objet Widget et lance
        '   une tâche longue.
        Set mWidget = New Widget
        On Error Resume Next
        Call mWidget.LongTask(14.4, 0.9)
        '
        ' Vérifie si l'appel s'est terminé car il
        '   a été annulé (ne peut pas tester uniquement
        '   mblnCancel pour cette raison; cela aurait dû
        '   être défini au moment où la méthode
        '   LongTask a été renvoyée).
        If Err.Number = 0 Then
            lblPercentDone.Caption = "Tâche effectuée"
        ElseIf Err.Number = vbObjectError + wdgERRTaskCanceled Then
            lblPercentDone.Caption = "Tâche annulée"
        Else
            ' (Gestion omise pour les autres erreurs.)
            lblPercentDone.Caption = "Quelque chose de mauvais s'est produit"
        End If
        Set mWidget = Nothing
        cmdPercentDone.Caption = "&Démarrer une tâche longue qui utilise un événement pour transmettre la progression"
        blnProcessing = False
    End If
End Sub

' ========================================
'        Code pour l'exemple Broadcast
'
Private Sub cmdAddForm_Click()
    Dim frm As New frmReceiver
    ' Conserve le suivi des destinataires.
    mcolReceivers.Add frm
    frm.Show vbModeless, Me
    Me.SetFocus
    txtMessage.SetFocus
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Dim frm As frmReceiver
    On Error Resume Next
    Do While mcolReceivers.Count > 0
        Unload mcolReceivers(1)
        mcolReceivers.Remove 1
    Loop
End Sub

Private Sub txtMessage_Change()
    Dim strMessage As String
    strMessage = txtMessage.Text
    '
    ' Déclenche l'événement Broadcast. Il n'y a
    '   aucun moyen de savoir si des destinataires
    '   gèrent l'événement.
    RaiseEvent Broadcast(strMessage)
    '
    ' Affiche le message après que tous les
    '   destinataires (le cas échéant) l'ont géré.
    '   Il n'y a aucun moyen de savoir
    '   quel destinataire a pu le modifier,
    '   ou quelles valeurs intermédiaires
    '   le message a pu avoir.
    lblEcho = strMessage
End Sub
