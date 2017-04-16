VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "Composant Rappel de l'horloge"
   ClientHeight    =   1140
   ClientLeft      =   4350
   ClientTop       =   3870
   ClientWidth     =   4050
   ClipControls    =   0   'False
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   1140
   ScaleWidth      =   4050
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   5000
      Left            =   3450
      Top             =   60
   End
   Begin VB.Label lblInterval 
      AutoSize        =   -1  'True
      Caption         =   "00"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Left            =   2895
      TabIndex        =   4
      Top             =   645
      Width           =   255
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "(Sec.)"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   2
      Left            =   3225
      TabIndex        =   3
      Top             =   630
      Width           =   690
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "Intervalle de mise à jour:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   1
      Left            =   150
      TabIndex        =   2
      Top             =   630
      Width           =   2565
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "Heure courante:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   0
      Left            =   150
      TabIndex        =   1
      Top             =   270
      Width           =   1395
   End
   Begin VB.Label lblTime 
      AutoSize        =   -1  'True
      Caption         =   "00:00:00"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Left            =   1845
      TabIndex        =   0
      Top             =   285
      Width           =   855
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim sCurTime As String

Private Sub lblInterval_Click()
  lblInterval.Caption = Format$(Timer1.Interval / 1000)
End Sub

Private Sub Timer1_Timer()
  Dim iCounter As Integer
  ' Utilisé par le gestionnaire de collision des composants ActiveX.
  Dim nCurErrorCount As Integer
  Const MAX_ERROR_COUNT = 10

  On Error GoTo CallbackError
  
      If gbConnected Then
        sCurTime = Time
        lblTime.Caption = sCurTime
100   gObjRef.TellTime (sCurTime)
110 End If
Exit Sub

CallbackError:
' Lors de l'utilisation de rappels asynchrones entre deux objets ActiveX, ce code de contrôle d'erreur est
  ' nécessaire pour gérer les risques de collision. Celle-ci peut se produire quand un client et
  ' un composant tentent de s'appeler en même temps. Ce gestionnaire d'erreurs force le composant à attendre
  ' pendant une période aléatoire avant de refaire une tentative. Le client pourra profiter de cette période
  ' pour mettre fin à son appel; l'appel du composant vers le client peut donc avoir lieu.
  ' Le même code du gestionnaire d'erreurs doit également être implémenté dans l'objet du client.
  If Erl = 100 And Err = &H80010001 Then
    If nCurErrorCount >= MAX_ERROR_COUNT Then
      MsgBox "Impossible de libérer la référence du composant. Réessayez plus tard.", vbExclamation, "Erreur de déconnexion du composant distant."
Resume EndOfError
    Else
      For iCounter = 1 To 2000 * Rnd()
        DoEvents
      Next iCounter
      Resume
    End If
  End If
EndOfError:
End Sub


