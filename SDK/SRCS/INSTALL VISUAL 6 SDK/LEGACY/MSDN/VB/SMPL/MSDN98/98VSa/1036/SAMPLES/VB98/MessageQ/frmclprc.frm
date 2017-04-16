VERSION 5.00
Begin VB.Form frmClaimProcessing 
   Caption         =   "Traitement des déclarations"
   ClientHeight    =   3585
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   2520
   LinkTopic       =   "Form1"
   ScaleHeight     =   3585
   ScaleWidth      =   2520
   StartUpPosition =   3  'Windows Default
   Begin VB.ListBox lstPendingMessages 
      Height          =   3375
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2295
   End
End
Attribute VB_Name = "frmClaimProcessing"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'--------------------------------------------------------------
'Cette feuille est utilisée dans deux programmes différents,
'le 'processeur de déclarations' et le processeur 'comptabilité'.
'La logique est identique dans les deux cas, seul change le nom de la file
'--------------------------------------------------------------
#If CLAIM_PROCESSING Then
    'NOMS DES FILES
    Const RECIEVE_QUEUE = INSURANCE_CLAIMS_QUEUE_NAME
    Const SEND_QUEUE = INSURANCE_ACCOUNTING_QUEUE_NAME

    'IUG
    Const FORM_CAPTION = "Service de traitement des déclarations"

#ElseIf ACCOUNTING_PROCESSING Then
    'NOMS DES FILES
    Const RECIEVE_QUEUE = INSURANCE_ACCOUNTING_QUEUE_NAME
    Const SEND_QUEUE = "" 'Pas de file de destination, c'est la dernière étape du work-flow

    'IUG
    Const FORM_CAPTION = "Service comptable"
#End If

Private m_mqReceiveQueue As MSMQQueue 'File des déclarations entrantes
Private m_mqSendQueue As MSMQQueue 'File des déclarations sortantes
Private WithEvents MessageQueueEvents_ReceiveQueue As MSMQEvent
Attribute MessageQueueEvents_ReceiveQueue.VB_VarHelpID = -1


Private Sub Form_Load()
    Me.Caption = FORM_CAPTION
    InitializeQueueAccess
    DoEvents 'Permettre le déclenchement des événements d'arrivée de messages avant l'affichage de l'IUG
End Sub

'---------------------------------------------
'Définit nos accès aux files de messages qui reçoivent/envoient des messages et s'attache à la gestion des événements pour la file de réception
'
' [11/13/97, IvoSa] Created
'---------------------------------------------
Sub InitializeQueueAccess()
    'Ouvrir la file
    OpenMessageQueueForReceive
    OpenMessageQueueForSend

'    'Remplir la liste avec les en-têtes des messages
'    FillPendingMessagesList
    
    '-----------------------------------------
    'Définir l'événement de notification sur arrivée de messages (il sera déclenché immédiatement s'il y a des messages dans la file)
    '-----------------------------------------
    Set MessageQueueEvents_ReceiveQueue = New MSMQEvent
    m_mqReceiveQueue.EnableNotification MessageQueueEvents_ReceiveQueue
End Sub

'---------------------------------------------
'Remplir toute notre liste avec les étiquettes des messages en attente
' [in] colLabels : Collection d'étiquettes
'---------------------------------------------
Sub resyncPendingMessageList(ByVal colLabels As Collection)
Dim vntLabel As Variant
    lstPendingMessages.Clear
    
    For Each vntLabel In colLabels
        lstPendingMessages.AddItem CStr(vntLabel)
    Next
End Sub

Private Sub lstPendingMessages_DblClick()
    ShowIndividualClaim lstPendingMessages.List(lstPendingMessages.ListIndex)
End Sub

'---------------------------------------------
'Affiche la déclaration pour une personne
'---------------------------------------------
Sub ShowIndividualClaim(strLabel As String)
Dim objMsg As MSMQMessage
    Set objMsg = getMessageGivenLabelAndQueue(m_mqReceiveQueue, strLabel)
    
    If (objMsg Is Nothing) Then
        MsgBox "Le message " & strLabel & "n'existe pas"
        Exit Sub
    End If
    
    'Décoder le message
    Dim objStrBag As StringBag
    Set objStrBag = New StringBag
    objStrBag.DeSerialize objMsg.Body
    
    'Afficher une feuille avec ces données
    Dim frm As frmProcessClaim
    Set frm = New frmProcessClaim
    frm.Initialize objStrBag, m_mqSendQueue
    frm.Show
    DoEvents 'Affichage effectif
    
    'Remplir de nouveau la liste avec les en-têtes des messages...
    resyncPendingMessageList getLabelsOfMessagesInQueue(m_mqReceiveQueue)
End Sub


'---------------------------------------------------------
'Ouvre la file de messages 'Claims' (déclarations) pour soumission des messages
' [11/13/97, IvoSa] Création
' [12/6/97, IvoSa] Ajout de la gestion des erreurs
'---------------------------------------------------------
Sub OpenMessageQueueForReceive()
Dim lngError As Long
Dim strError As String
    
    If RECIEVE_QUEUE <> "" Then
        On Error Resume Next
            Set m_mqReceiveQueue = openMessageQueue(RECIEVE_QUEUE, MQ_RECEIVE_ACCESS, True)
            lngError = Err
            strError = Err.Description
        On Error GoTo 0
    
        If lngError Then
            MsgBox ERROR_TEXT_RUNADMINTOOL & "(texte de l'erreur spécifique: " & strError & ")"
            
            Stop 'Permettre le débogage de l'appli ici...
            End 'On ne poursuit pas après ce point
        End If
    
    End If
End Sub

'---------------------------------------------------------
'Ouvre la file de messages 'Claims' (déclarations) pour soumission des messages
' [11/13/97, IvoSa] Création
' [12/6/97, IvoSa] Ajout de la gestion des erreurs
'---------------------------------------------------------
Sub OpenMessageQueueForSend()
Dim lngError As Long
Dim strError As String
    
    If SEND_QUEUE <> "" Then
        On Error Resume Next
            Set m_mqSendQueue = openMessageQueue(SEND_QUEUE, MQ_SEND_ACCESS, True)
            lngError = Err
            strError = Err.Description
        On Error GoTo 0
        
        If lngError Then
            MsgBox ERROR_TEXT_RUNADMINTOOL & "(specific error text reads: " & strError & ")"
            
            Stop 'Permettre le débogage de l'appli ici...
            End 'On ne poursuit pas après ce point
        End If
    End If
End Sub


'---------------------------------------------------------
'Appelée sur arrivée de nouveaux messages
'---------------------------------------------------------
Private Sub MessageQueueEvents_ReceiveQueue_Arrived(ByVal Queue As Object, ByVal Cursor As Long)
Dim colLabels As Collection
    'Obtenir la liste des étiquettes de messages et définir l'événement à déclencher lorsque la déclaration suivante arrivera
    Set MessageQueueEvents_ReceiveQueue = getEventFireOnNextMessageArrival(m_mqReceiveQueue, colLabels)
    
    resyncPendingMessageList colLabels
End Sub

