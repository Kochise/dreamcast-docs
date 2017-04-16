VERSION 5.00
Object = "{831FDD16-0C5C-11d2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmCBCli 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Client Rappel de l'horloge"
   ClientHeight    =   2205
   ClientLeft      =   2880
   ClientTop       =   2610
   ClientWidth     =   5370
   ClipControls    =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2205
   ScaleWidth      =   5370
   Begin MSComCtlLib.StatusBar stbStatusBar 
      Align           =   2  'Align Bottom
      Height          =   375
      Left            =   0
      TabIndex        =   8
      Top             =   1830
      Width           =   5370
      _ExtentX        =   9472
      _ExtentY        =   661
      Style           =   1
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.PictureBox Picture1 
      Height          =   615
      Left            =   240
      ScaleHeight     =   555
      ScaleWidth      =   3435
      TabIndex        =   5
      Top             =   960
      Width           =   3495
      Begin VB.Label lblTime 
         AutoSize        =   -1  'True
         BackColor       =   &H00FFFFFF&
         BackStyle       =   0  'Transparent
         Caption         =   "00:00:00"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00800000&
         Height          =   300
         Left            =   2280
         TabIndex        =   7
         Top             =   120
         Width           =   1065
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         Caption         =   "Heure courante:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         Index           =   0
         Left            =   120
         TabIndex        =   6
         Top             =   120
         Width           =   1995
      End
   End
   Begin VB.TextBox txtInterval 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   3240
      TabIndex        =   4
      Text            =   "1"
      Top             =   360
      Width           =   495
   End
   Begin VB.CommandButton cmdButton 
      Caption         =   "&Quitter"
      Height          =   495
      Index           =   2
      Left            =   3975
      TabIndex        =   2
      Top             =   1200
      Width           =   1215
   End
   Begin VB.CommandButton cmdButton 
      Caption         =   "&Déconnexion"
      Enabled         =   0   'False
      Height          =   495
      Index           =   1
      Left            =   3975
      TabIndex        =   1
      Top             =   660
      Width           =   1215
   End
   Begin VB.CommandButton cmdButton 
      Caption         =   "&Connexion"
      Default         =   -1  'True
      Height          =   495
      Index           =   0
      Left            =   3975
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label2 
      BackStyle       =   0  'Transparent
      Caption         =   "Intervalle de mise à jour:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   960
      TabIndex        =   3
      Top             =   435
      Width           =   2220
   End
   Begin VB.Image Image1 
      Height          =   480
      Index           =   1
      Left            =   240
      Top             =   240
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image Image1 
      Height          =   480
      Index           =   0
      Left            =   240
      Top             =   240
      Width           =   480
   End
End
Attribute VB_Name = "frmCBCli"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
' Pour plus d'informations sur le fonctionnement de cette
' application, veuillez vous reporter aux notes du projet du
' composant.

Dim objCbSvr As Object
Dim mnCallInterval  As Integer
Dim mbIsConnected As Boolean

Private Sub cmdButton_Click(Index As Integer)
  Static objMyClassInstance As Object
  Dim bSuccess As Integer
  Dim bRetVal As Boolean
  Dim iCounter As Integer
  
  ' Utilisé par le gestionnaire de collision des composants ActiveX.
  Dim nCurErrorCount As Integer
  Const MAX_ERROR_COUNT = 10
  
  On Error GoTo cmdButtonError
  
  Screen.MousePointer = vbHourglass
  
  Select Case Index
  
    Case 0  ' Connexion.
      Set objMyClassInstance = New CbClientProj.CbClientClass
      Set objCbSvr = CreateObject("CbServerProj.CbServerClass")
      mnCallInterval = Val(txtInterval.Text)
      bSuccess = objCbSvr.SetInterval(mnCallInterval)
      If objCbSvr.AddObjectReference(objMyClassInstance) Then
        mbIsConnected = True
        cmdButton(0).Enabled = False
        cmdButton(1).Enabled = True
        cmdButton(2).Enabled = False
        Image1(0).Visible = False
        Image1(1).Visible = True
        stbStatusBar.SimpleText = "Connexion réussie..."
        
      Else
        stbStatusBar.SimpleText = "Échec de la connexion..."
      
      End If
      
    Case 1  ' Déconnexion.
        ' Augmente l'intervalle du rappel pour réduire le risque de collision.
        bSuccess = objCbSvr.SetInterval(30)
        ' Demande au composant de se déconnecter.
100   If objCbSvr.DropObjectReference(objMyClassInstance) Then
110   mbIsConnected = False
        ' Supprime la référence de l'objet local
        Set objMyClassInstance = Nothing
        ' Supprime la référence de l'objet du composant.
        Set objCbSvr = Nothing
        cmdButton(0).Enabled = True
        cmdButton(1).Enabled = False
        cmdButton(2).Enabled = True
        Image1(0).Visible = True
        Image1(1).Visible = False
        stbStatusBar.SimpleText = "Deconnexion réussie..."
        
      Else
        stbStatusBar.SimpleText = "Échec de la connexion..."
        
      End If
    
    Case 2  'Exit
      Unload Me
    
  End Select
  
  Screen.MousePointer = vbDefault
  Exit Sub

cmdButtonError:
  ' Lors de l'utilisation de rappels asynchrones entre deux objets ActiveX, ce code de contrôle d'erreur est
  ' nécessaire pour gérer les risques de collision. Celle-ci peut se produire quand un client et
  ' un composant tentent de s'appeler en même temps. Ce gestionnaire d'erreurs force le client à attendre
  ' pendant une période aléatoire avant de refaire une tentative. Le composant pourra profiter de cette période
  ' pour mettre fin à son appel; l'appel du client vers le composant peut donc avoir lieu.
  ' Le même code du gestionnaire d'erreurs doit également être implémenté dans l'objet du composant.
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
  
  Screen.MousePointer = vbDefault
  MsgBox Error$, vbCritical, "Erreur cmdButton"
EndOfError:
End Sub
Private Sub Form_Load()
  Me.Left = (Screen.Width - Me.Width) / 2
  Me.Top = (Screen.Height - Me.Height) / 2
  
End Sub

Private Sub txtInterval_LostFocus()
        Dim bSuccess As Integer
        Dim iCounter As Integer
        
        ' Utilisé par le gestionnaire de collision des composants ActiveX.
        Dim nCurErrorCount As Integer
        Const MAX_ERROR_COUNT = 10

        On Error GoTo SetIntervalError
        If Val(txtInterval.Text) <> mnCallInterval And mbIsConnected Then
          mnCallInterval = Val(txtInterval.Text)
100     bSuccess = objCbSvr.SetInterval(mnCallInterval)
110  End If

SetIntervalError:
  ' Lors de l'utilisation de rappels asynchrones entre deux objets ActiveX, ce code de contrôle d'erreur est
  ' nécessaire pour gérer les risques de collision. Celle-ci peut se produire quand un client et
  ' un composant tentent de s'appeler en même temps. Ce gestionnaire d'erreurs force le client à attendre
  ' pendant une période aléatoire avant de refaire une tentative. Le composant pourra profiter de cette période
  ' pour mettre fin à son appel; l'appel du client vers le composant peut donc avoir lieu.
  ' Le même code du gestionnaire d'erreurs doit également être implémenté dans l'objet du composant.
  If Erl = 100 And Err = &H80010001 Then
    If nCurErrorCount >= MAX_ERROR_COUNT Then
      MsgBox "Impossible de mettre à jour l'intervalle de la minuterie. Réessayez plus tard.", vbExclamation, "Erreur de la mise à jour de l'intervalle"
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


