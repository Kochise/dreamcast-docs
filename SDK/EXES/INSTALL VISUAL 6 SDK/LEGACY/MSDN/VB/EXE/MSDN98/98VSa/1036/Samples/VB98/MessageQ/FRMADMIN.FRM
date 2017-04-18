VERSION 5.00
Begin VB.Form frmCreateQueues 
   Caption         =   "Schéma de workflow simple (création de file)"
   ClientHeight    =   4605
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6690
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   ScaleHeight     =   4605
   ScaleWidth      =   6690
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdViewExistingQueues 
      Caption         =   "&Afficher les files existantes"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   0
      TabIndex        =   1
      Top             =   3360
      Width           =   2295
   End
   Begin VB.Frame Frame2 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1215
      Left            =   0
      TabIndex        =   12
      Top             =   1920
      Width           =   5895
      Begin VB.TextBox txtAccountingQueueLocation 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Left            =   3240
         TabIndex        =   5
         Top             =   600
         Width           =   2535
      End
      Begin VB.TextBox txtAccountingQueueName 
         BackColor       =   &H8000000F&
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Left            =   3240
         Locked          =   -1  'True
         TabIndex        =   4
         Top             =   240
         Width           =   2535
      End
      Begin VB.Shape Shape2 
         Height          =   495
         Left            =   120
         Top             =   240
         Width           =   1815
      End
      Begin VB.Label Label7 
         Caption         =   "(Comptabilité)"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   360
         TabIndex        =   15
         Top             =   480
         Width           =   1455
      End
      Begin VB.Label Label6 
         Caption         =   "Emplacement de la file:"
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
         Left            =   2040
         TabIndex        =   14
         Top             =   600
         Width           =   1215
      End
      Begin VB.Label Label1 
         Caption         =   "Nom de la file:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   2040
         TabIndex        =   13
         Top             =   240
         Width           =   1095
      End
      Begin VB.Label Label8 
         Caption         =   "File"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   360
         TabIndex        =   16
         Top             =   240
         Width           =   1215
      End
   End
   Begin VB.CommandButton cmdCreateQueue 
      Caption         =   "&Créer de nouvelles files"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   3960
      TabIndex        =   0
      Top             =   3360
      Width           =   1935
   End
   Begin VB.Frame Frame1 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1095
      Left            =   0
      TabIndex        =   6
      Top             =   480
      Width           =   5895
      Begin VB.TextBox txtClaimsQueueName 
         BackColor       =   &H8000000F&
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Left            =   3240
         Locked          =   -1  'True
         TabIndex        =   2
         Top             =   240
         Width           =   2535
      End
      Begin VB.TextBox txtClaimsQueueLocation 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Left            =   3240
         TabIndex        =   3
         Top             =   600
         Width           =   2535
      End
      Begin VB.Label Label5 
         Caption         =   "Nom de la file:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   2040
         TabIndex        =   11
         Top             =   240
         Width           =   1095
      End
      Begin VB.Label lblQueueLocation 
         Caption         =   "Emplacement de la file:"
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
         Left            =   2040
         TabIndex        =   9
         Top             =   600
         Width           =   1215
      End
      Begin VB.Shape Shape1 
         Height          =   735
         Left            =   120
         Top             =   240
         Width           =   1815
      End
      Begin VB.Label Label2 
         Caption         =   "File"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   360
         TabIndex        =   7
         Top             =   240
         Width           =   1215
      End
      Begin VB.Label Label4 
         Caption         =   "(Vérification des déclarations)"
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
         Left            =   360
         TabIndex        =   8
         Top             =   480
         Width           =   1455
      End
   End
   Begin VB.Line Line12 
      X1              =   2520
      X2              =   2760
      Y1              =   1680
      Y2              =   1800
   End
   Begin VB.Line Line11 
      X1              =   2760
      X2              =   3000
      Y1              =   1800
      Y2              =   1680
   End
   Begin VB.Line Line10 
      X1              =   2760
      X2              =   2760
      Y1              =   1800
      Y2              =   1560
   End
   Begin VB.Line Line6 
      X1              =   2760
      X2              =   2760
      Y1              =   480
      Y2              =   240
   End
   Begin VB.Line Line5 
      X1              =   2760
      X2              =   3000
      Y1              =   480
      Y2              =   360
   End
   Begin VB.Line Line4 
      X1              =   2520
      X2              =   2760
      Y1              =   360
      Y2              =   480
   End
   Begin VB.Label Label3 
      Caption         =   "Déclarations vide"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   2400
      TabIndex        =   10
      Top             =   0
      Width           =   975
   End
End
Attribute VB_Name = "frmCreateQueues"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'-----------------------------------------
'Crée une nouvelle file
'-----------------------------------------
Private Sub cmdCreateQueue_Click()
    If createMessageQueue(txtClaimsQueueName.Text, txtClaimsQueueLocation.Text) Then
        'Stocker localement le GUID de la file
        LookupGUIDAndPersistToRegisty txtClaimsQueueName.Text
        
        MsgBox txtClaimsQueueName.Text & " : file créée avec succès."
    End If
    
    If createMessageQueue(txtAccountingQueueName.Text, txtAccountingQueueLocation.Text) Then
        'Stocker localement le GUID de la file
        LookupGUIDAndPersistToRegisty txtAccountingQueueName.Text
        MsgBox txtAccountingQueueName.Text & " : file créée avec succès."
    End If

End Sub

'Afficher la feuille de suivi de la file
Private Sub cmdViewExistingQueues_Click()
    frmQueueMonitoring.Show
End Sub

Private Sub Form_Load()
    InitializeQueueData
End Sub

'----------------------------------------------
'Définit les zones de texte contenant les données de nos files
' [11/13/97, IvoSa] Created
'----------------------------------------------
Sub InitializeQueueData()
    txtClaimsQueueName.Text = INSURANCE_CLAIMS_QUEUE_NAME
    txtClaimsQueueLocation.Text = INSURANCE_CLAIMS_QUEUE_LOCATION
    
    txtAccountingQueueName.Text = INSURANCE_ACCOUNTING_QUEUE_NAME
    txtAccountingQueueLocation.Text = INSURANCE_ACCOUNTING_QUEUE_LOCATION
End Sub

