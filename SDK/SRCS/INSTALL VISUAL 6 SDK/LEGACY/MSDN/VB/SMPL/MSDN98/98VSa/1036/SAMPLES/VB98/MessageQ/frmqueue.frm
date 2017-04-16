VERSION 5.00
Begin VB.Form frmQueueMonitoring 
   Caption         =   "Feuille1"
   ClientHeight    =   3480
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8460
   LinkTopic       =   "Form1"
   ScaleHeight     =   3480
   ScaleWidth      =   8460
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdCheckForMessages 
      Caption         =   "&Vérifier les messages"
      Height          =   255
      Left            =   120
      TabIndex        =   17
      Top             =   3120
      Width           =   1695
   End
   Begin VB.ListBox lstAccountingQueue 
      Height          =   1035
      Left            =   6000
      TabIndex        =   16
      Top             =   1920
      Width           =   2415
   End
   Begin VB.ListBox lstClaimsQueue 
      Height          =   1035
      Left            =   6000
      TabIndex        =   15
      Top             =   600
      Width           =   2415
   End
   Begin VB.Frame Frame1 
      Height          =   1095
      Left            =   0
      TabIndex        =   7
      Top             =   480
      Width           =   5895
      Begin VB.TextBox txtClaimsQueueLocation 
         BackColor       =   &H8000000F&
         Height          =   285
         Left            =   3240
         TabIndex        =   9
         Top             =   600
         Width           =   2535
      End
      Begin VB.TextBox txtClaimsQueueName 
         BackColor       =   &H8000000F&
         Height          =   285
         Left            =   3240
         Locked          =   -1  'True
         TabIndex        =   8
         Top             =   240
         Width           =   2535
      End
      Begin VB.Label Label4 
         Caption         =   "(Vérification des réclamations)"
         Height          =   495
         Left            =   360
         TabIndex        =   13
         Top             =   360
         Width           =   1335
      End
      Begin VB.Label Label2 
         Caption         =   "File d'attente"
         Height          =   255
         Left            =   480
         TabIndex        =   12
         Top             =   120
         Width           =   975
      End
      Begin VB.Shape Shape1 
         Height          =   735
         Left            =   120
         Top             =   240
         Width           =   1815
      End
      Begin VB.Label lblQueueLocation 
         Caption         =   "Emplacement :"
         Height          =   255
         Left            =   2040
         TabIndex        =   11
         Top             =   600
         Width           =   1215
      End
      Begin VB.Label Label5 
         Caption         =   "Nom :"
         Height          =   255
         Left            =   2040
         TabIndex        =   10
         Top             =   240
         Width           =   735
      End
   End
   Begin VB.Frame Frame2 
      Height          =   1095
      Left            =   0
      TabIndex        =   0
      Top             =   1800
      Width           =   5895
      Begin VB.TextBox txtAccountingQueueName 
         BackColor       =   &H8000000F&
         Height          =   285
         Left            =   3240
         Locked          =   -1  'True
         TabIndex        =   2
         Top             =   240
         Width           =   2535
      End
      Begin VB.TextBox txtAccountingQueueLocation 
         BackColor       =   &H8000000F&
         Height          =   285
         Left            =   3240
         TabIndex        =   1
         Top             =   600
         Width           =   2535
      End
      Begin VB.Label Label8 
         Caption         =   "File d'attente"
         Height          =   255
         Left            =   480
         TabIndex        =   6
         Top             =   120
         Width           =   975
      End
      Begin VB.Label Label1 
         Caption         =   "Nom :"
         Height          =   255
         Left            =   2040
         TabIndex        =   5
         Top             =   240
         Width           =   735
      End
      Begin VB.Label Label6 
         Caption         =   "Emplacement :"
         Height          =   255
         Left            =   2040
         TabIndex        =   4
         Top             =   600
         Width           =   1095
      End
      Begin VB.Label Label7 
         Caption         =   "(Comptabilité)"
         Height          =   255
         Left            =   480
         TabIndex        =   3
         Top             =   480
         Width           =   1095
      End
      Begin VB.Shape Shape2 
         Height          =   735
         Left            =   120
         Top             =   240
         Width           =   1815
      End
   End
   Begin VB.Label Label3 
      Caption         =   "Entrée de réclamation"
      Height          =   255
      Left            =   2040
      TabIndex        =   14
      Top             =   0
      Width           =   1695
   End
   Begin VB.Line Line4 
      X1              =   2520
      X2              =   2760
      Y1              =   360
      Y2              =   480
   End
   Begin VB.Line Line5 
      X1              =   2760
      X2              =   3000
      Y1              =   480
      Y2              =   360
   End
   Begin VB.Line Line6 
      X1              =   2760
      X2              =   2760
      Y1              =   480
      Y2              =   240
   End
   Begin VB.Line Line10 
      X1              =   2760
      X2              =   2760
      Y1              =   1800
      Y2              =   1560
   End
   Begin VB.Line Line11 
      X1              =   2760
      X2              =   3000
      Y1              =   1800
      Y2              =   1680
   End
   Begin VB.Line Line12 
      X1              =   2520
      X2              =   2760
      Y1              =   1680
      Y2              =   1800
   End
End
Attribute VB_Name = "frmQueueMonitoring"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private WithEvents MessageQueueEvents_Claims As MSMQEvent
Attribute MessageQueueEvents_Claims.VB_VarHelpID = -1
Private WithEvents MessageQueueEvents_Accounting As MSMQEvent
Attribute MessageQueueEvents_Accounting.VB_VarHelpID = -1

Private m_mqClaims As MSMQQueue ' File d'attente pour le service des réclamations
Attribute m_mqClaims.VB_VarHelpID = -1
Private m_mqAccounting As MSMQQueue ' File d'attente pour le service comptabilité


'---------------------------------------------
' Nous permet de lire les messages dans les files d'attente
' [11/13/97, IvoSa]
' [12/6/97, IvoSa] Ajout d'un message d'erreur si la file d'attente n'est pas trouvée...
'---------------------------------------------
Sub InitializeQueueAccess()
Dim lngError As Long
Dim strError As String
Dim objQI As MSMQQueueInfo
    
    ' File d'attente des réclamations
    txtClaimsQueueName = INSURANCE_CLAIMS_QUEUE_NAME
    On Error Resume Next
        Set m_mqClaims = openMessageQueue(INSURANCE_CLAIMS_QUEUE_NAME, MQ_PEEK_ACCESS, True, objQI)
        lngError = Err
        strError = Err.Description
    On Error GoTo 0
    
    ' Vérifie si une erreur s'est produite...
    If lngError Then
        MsgBox ERROR_TEXT_RUNADMINTOOL & "(texte d'erreur specifique : " & strError & ")"
        
        Stop ' Permet de déboguer l'application...
        End ' Arrêt de l'application
    End If

    txtClaimsQueueLocation = objQI.PathName

    ' File d'attente pour la comptabilité
    txtAccountingQueueName = INSURANCE_ACCOUNTING_QUEUE_NAME
    On Error Resume Next
        Set m_mqAccounting = openMessageQueue(INSURANCE_ACCOUNTING_QUEUE_NAME, MQ_PEEK_ACCESS, True, objQI)
        lngError = Err
        strError = Err.Description
    On Error GoTo 0
    
    ' Vérifie si une erreur s'est produite...
    If lngError Then
        MsgBox ERROR_TEXT_RUNADMINTOOL & "(texte d'erreur specifique : " & strError & ")"
        
        Stop ' Permet de déboguer l'application...
        End ' Arrêt de l'application
    End If
    
    txtAccountingQueueLocation = objQI.PathName

    ' Remplit les zones de liste avec les libellés des messages dans les files d'attente
'    resyncClaimsQueueList
'    resyncAccountingQueueList
    
    '-----------------------------------------
    ' Définit les événements pour notifier l'arrivée des messages
    ' (les événements se déclenchent immédiatement si des messages se trouvent dans la file d'attente)
    '-----------------------------------------
    Set MessageQueueEvents_Claims = New MSMQEvent
    m_mqClaims.EnableNotification MessageQueueEvents_Claims
    
    Set MessageQueueEvents_Accounting = New MSMQEvent
    m_mqAccounting.EnableNotification MessageQueueEvents_Accounting
    
End Sub

'-------------------------------------------------
' Resynchronise les listes de messages
' [11/13/97, Ivosa] Créé
' [3/19/98, Ivosa]  Bogue du gestionnaire d'événements de file d'attente résolu
'-------------------------------------------------
Private Sub cmdCheckForMessages_Click()
    
Dim colMsgLabels As Collection
    ' Lit les libellés des réclamations concernant les assurances dans la file d'attente 'Réclamations'
    Set colMsgLabels = getLabelsOfMessagesInQueue(m_mqClaims)
    ' Resynchronise la liste
    resyncClaimsQueueList colMsgLabels
    
    ' Lit les libellés des réclamations concernant les assurances dans la file d'attente 'Comptabilité'
    Set colMsgLabels = getLabelsOfMessagesInQueue(m_mqAccounting)
    ' Resynchronise la liste
    resyncAccountingQueueList colMsgLabels
End Sub

Private Sub Form_Load()
    InitializeQueueAccess
    DoEvents ' Remplit les listes avec les événements de messages (ceci permet de déclencher les événements)
End Sub

'---------------------------------
' Cet événement est déclenché lorsque la file d'attente n'est plus vide
'---------------------------------
Private Sub MessageQueueEvents_Accounting_Arrived(ByVal Queue As Object, ByVal Cursor As Long)
Dim colLabels As Collection
    ' Obtient la liste des libellés des messages et définit l'événement à déclencher lorsqu'une réclamation arrive
    Set MessageQueueEvents_Accounting = getEventFireOnNextMessageArrival(m_mqAccounting, colLabels)
    
    resyncAccountingQueueList colLabels
End Sub

Private Sub MessageQueueEvents_Accounting_ArrivedError(ByVal Queue As Object, ByVal ErrorCode As Long, ByVal Cursor As Long)
Stop ' NON GÉRÉ
End Sub

'---------------------------------
' Cet événement est déclenché lorsque la file d'attente n'est plus vide
'---------------------------------
Private Sub MessageQueueEvents_Claims_Arrived(ByVal Queue As Object, ByVal Cursor As Long)
Dim colLabels As Collection
    
    ' Obtient la liste des libellés des messages et définit l'événement à déclencher lorsqu'une réclamation arrive
    Set MessageQueueEvents_Claims = getEventFireOnNextMessageArrival(m_mqClaims, colLabels)
    
    resyncClaimsQueueList colLabels
End Sub

'---------------------------------------------------
' Obtient la liste des messages et remplit la liste avec leurs libellés
' [entré] colLables : Collection des libellés
' [11/13/97, IvoSa] Créé
'---------------------------------------------------
Sub resyncAccountingQueueList(ByVal colLabels As Collection)
Dim vntLabel As Variant
    
    Dim lst As ListBox
    Set lst = lstAccountingQueue
    ' Efface l'ancienne liste
    lst.Clear
    For Each vntLabel In colLabels
        lst.AddItem CStr(vntLabel)
    Next
End Sub

'---------------------------------------------------
' Obtient la liste des messages et remplit la liste avec leurs libellés
' [entré] colLables : Collection des libellés
' [11/13/97, IvoSa] Créé
'---------------------------------------------------
Sub resyncClaimsQueueList(ByVal colLabels As Collection)
Dim vntLabel As Variant
    Dim lst As ListBox
    Set lst = lstClaimsQueue
    ' Efface l'ancienne liste
    lst.Clear
    For Each vntLabel In colLabels
        lst.AddItem CStr(vntLabel)
    Next
End Sub

Private Sub MessageQueueEvents_Claims_ArrivedError(ByVal Queue As Object, ByVal ErrorCode As Long, ByVal Cursor As Long)
Stop ' NON GÉRÉ
End Sub
