VERSION 5.00
Begin VB.Form frmClient 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Client gestionnaire de regroupement"
   ClientHeight    =   2550
   ClientLeft      =   3225
   ClientTop       =   2715
   ClientWidth     =   4380
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2550
   ScaleWidth      =   4380
   Begin VB.Frame Frame2 
      Caption         =   "Bonjour par l'intermédiaire du composant PassThrough"
      Height          =   750
      Left            =   135
      TabIndex        =   7
      Top             =   105
      Width           =   4140
      Begin VB.CommandButton cmdUpdate 
         Caption         =   "Dire Bonjour"
         Height          =   300
         Index           =   0
         Left            =   2280
         TabIndex        =   8
         Top             =   270
         Width           =   1050
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Composant Interface"
      Height          =   990
      Left            =   120
      TabIndex        =   1
      Top             =   960
      Width           =   4140
      Begin VB.CommandButton cmdUpdate 
         Caption         =   "Mettre à jour"
         Height          =   300
         Index           =   1
         Left            =   2280
         TabIndex        =   6
         Top             =   270
         Width           =   1050
      End
      Begin VB.Label lab1 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Date:"
         Height          =   270
         Index           =   0
         Left            =   195
         TabIndex        =   5
         Top             =   315
         Width           =   465
      End
      Begin VB.Label lab1 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Heure:"
         Height          =   270
         Index           =   1
         Left            =   120
         TabIndex        =   4
         Top             =   600
         Width           =   570
      End
      Begin VB.Label labDate 
         BackColor       =   &H00C0C0C0&
         Caption         =   "labDate"
         Height          =   210
         Left            =   690
         TabIndex        =   3
         Top             =   315
         Width           =   840
      End
      Begin VB.Label labTime 
         BackColor       =   &H00C0C0C0&
         Caption         =   "labTime"
         Height          =   210
         Left            =   720
         TabIndex        =   2
         Top             =   600
         Width           =   720
      End
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "Fermer"
      Default         =   -1  'True
      Height          =   300
      Left            =   150
      TabIndex        =   0
      Top             =   2085
      Width           =   1050
   End
End
Attribute VB_Name = "frmClient"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim mobjPoolMngr As Object
Const miPASS_THRU_HELLO = 0
Const miINTERFACE_SVR = 1


Private Sub cmdClose_Click()
  Unload frmClient
End Sub

Private Sub cmdUpdate_Click(Index As Integer)
' Les deux options utilisent le gestionnaire de regroupement afin
' d'acquérir des pointeurs de références aux composants ActiveX déjà créés.
' Ceci réduit grandement le temps de démarrage et permet au
' gestionnaire de regroupement de contrôler qui peut avoir quels
' objets et d'où ils doivent venir. Cet exemple peut facilement être
' étendu pour regrouper des objets situés sur plusieurs
' serveurs, sur un réseau.

  Dim bSuccess  As Integer
  Dim nProjID  As Integer
  Dim objInterface  As Object
  Dim bInterfaceOpen As Integer
  Dim objServer As Object

  If Index = miPASS_THRU_HELLO Then
    ' Cette option utilise le composant PassThrough pour demander
    ' une référence vers le composant externe Bonjour. Sur une
    ' seule machine, cela n'est pas très intéressant. En revanche,
    ' si le composant PassThrough est inscrit pour une exécution
    ' à distance avec l'Automation à distance, cette méthode
    ' fournit alors une solution simple aux clients pour accéder
    ' aux composants in-process se trouvant sur des machines
    ' distantes. Les composants in-process peuvent être plus
    ' rapides que les composants out-of-process. Ils partagent
    ' également le même espace de traitement que le composant
    ' PassThrough, ce qui peux réduire notablement les temps de
    ' réponse de la machine distante quand plusieurs composants
    ' ActiveX coopèrent pour répondre à une demande spécifique du
    ' client.
    
    Set objInterface = mobjPoolMngr.objGetProjInstance("PassThruProj.PassThruClass", nProjID)
    bInterfaceOpen = True
    
    Set objServer = objInterface.RunServer("HelloProj.HelloClass", bSuccess)
    If bSuccess Then MsgBox objServer.SayHello
    Set objServer = Nothing
    bSuccess = mobjPoolMngr.ReturnProjInstance("PassThruProj.PassThruClass", nProjID)
  Else
    ' Cette option utilise le composant Interface pour demander
    ' une référence aux objets Date et Time internes.
    ' Pour plus de détails sur le fonctionnement du composant
    ' Interface, consulter le fichier Intrface.txt dans le dossier
    ' Intrface.
    
    Set objInterface = mobjPoolMngr.objGetProjInstance("InterfaceProj.ServerInterface", nProjID)
    If nProjID < 0 Then GoTo cuError2
    bInterfaceOpen = True
    
    Set objServer = objInterface.objGetClassInstance("InterfaceDateClass")
    labDate.Caption = objServer.GetDate
    Set objServer = Nothing
    Set objServer = objInterface.objGetClassInstance("InterfaceTimeClass")
    labTime.Caption = objServer.GetTime
    Set objServer = Nothing
    bSuccess = mobjPoolMngr.ReturnProjInstance("InterfaceProj.ServerInterface", nProjID)
  End If
  GoTo cuExit

cuError:
  MsgBox Error$
  Resume cuExit

cuError2:
  MsgBox "Impossible de se connecter au composant"

cuExit:
  If bInterfaceOpen Then Set objInterface = Nothing
End Sub

Private Sub Form_Load()
' Dans un cas réel, le gestionnaire de regroupement doit toujours
' être en cours d'exécution, en raison du fait qu'il nécessite un
' temps de démarrage relativement long lorsqu'il doit initialiser
' un grand nombre de composants.

  Set mobjPoolMngr = CreateObject("PoolMngrProj.PoolMngrClass")
  cmdUpdate_Click miINTERFACE_SVR
End Sub

Private Sub Form_Unload(Cancel As Integer)
  Set mobjPoolMngr = Nothing
End Sub

