VERSION 5.00
Begin VB.Form frmThread 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Exemple de traitement multithread"
   ClientHeight    =   4950
   ClientLeft      =   4140
   ClientTop       =   1470
   ClientWidth     =   7095
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4950
   ScaleWidth      =   7095
   Begin VB.Timer tmrShort 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   2280
      Top             =   3840
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "&Annuler les tâches longues"
      Height          =   375
      Left            =   240
      TabIndex        =   8
      Top             =   4440
      Width           =   2895
   End
   Begin VB.TextBox txtN 
      Height          =   375
      Left            =   2760
      MaxLength       =   1
      TabIndex        =   6
      Text            =   "4"
      Top             =   2160
      Width           =   375
   End
   Begin VB.CommandButton cmdNLong 
      Caption         =   "...avec &n tâches longues"
      Height          =   375
      Left            =   240
      TabIndex        =   5
      Top             =   2160
      Width           =   2415
   End
   Begin VB.CommandButton cmdShortLong 
      Caption         =   "...avec tâches &longues"
      Height          =   375
      Left            =   240
      TabIndex        =   4
      Top             =   1680
      Width           =   2895
   End
   Begin VB.CommandButton cmdShortOnly 
      Caption         =   "&Tâches courtes, en série..."
      Height          =   375
      Left            =   240
      TabIndex        =   3
      Top             =   1200
      Width           =   2895
   End
   Begin VB.CommandButton cmdIDs 
      Caption         =   "Liste des &ID de thread"
      Height          =   375
      Left            =   240
      TabIndex        =   2
      Top             =   720
      Width           =   2895
   End
   Begin VB.ListBox lstResults 
      Height          =   4545
      Left            =   3360
      TabIndex        =   1
      Top             =   120
      Width           =   3615
   End
   Begin VB.CommandButton cmdXThread 
      Caption         =   "&Dépréciation entre les threads"
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   2895
   End
   Begin VB.Label Label1 
      Caption         =   "Vos tests ici..."
      Height          =   255
      Left            =   240
      TabIndex        =   7
      Top             =   2760
      Width           =   2895
   End
End
Attribute VB_Name = "frmThread"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
' L'exemple de traitement multithread:
'   - Affiche les ID des threads et le nombre
'       des objets d'une thread (ceci est
'       plus intéressant si le nombre maximale
'       de threads est de 3 ou de 4 lors de la
'       compilation de MTCoffee.exe).
'   - Compare la dépréciation entre les appels
'       effectués sur une même thread et ceux
'       effectués entre plusieurs threads.
'   - Fournit le temps par itération pour les
'       tâches courtes en série (Voir l'objet
'       Coffee défini dans MTCoffee.cls).
'   - Fournit le temps par itération pour une
'       tâche longue, et des tâches courtes en
'       série s'exécutant en même temps.
'   - Fournit le temps par itération pour un
'       nombre de tâches longues, et des tâches
'       courtes en série s'exécutant en même temps.
'
' Ceci constitue une base à laquelle vous pouvez
'   adjoindre vos propres tests. Il peut donc être
'   intéressant de comparer le comportement des
'   tâches qui bloquent (telles que les requêtes
'   aux bases de données sur des ordinateurs
'   distants, ou les transferts de fichiers
'   importants). Sur un ordinateur à un seul
'   processeur, ce type de tâches se comporte
'   mieux que les tâches qui sont proposées
'   dans les exemples ci-dessus, qui exigent
'   d'importantes ressources de traitement.
'   Les threads qui exécutent ce genre de
'   tâches entrent en conflit pour utiliser
'   l'unique processeur de la machine et
'   leur performance décroît à mesure que le
'   nombre de threads actives augmente.
'
' Pour plus d'informations, reportez-vous à
'   la section "Évolutivité et traitement
'   Multithread", du chapitre "Construction
'   de composants de code" des Manuels en ligne.
 
' Ces constantes contrôlent la taille relative
'   d'une tâche longue et d'une tâche courte.
'   Vous devrez peut-être les ajuster à la
'   vitesse de votre processeur.
Const SHORTTASKSIZE = 50000
Const LONGTASKSIZE = 2000000

' Tableau d'objets Coffee.
Private macfe(1 To 20) As Coffee

' Collection d'objets CoffeeTracker.
Public CoffeeTrackers As New Collection

' Indicateur d'annulation.
Public CancelAll As Boolean

' Nombre de tâches courtes à exécuter.
Private mintHowManyShort As Integer

Private Sub cmdCancel_Click()
    ' Lorsque l'utilisateur clique sur Annuler,
    '   définit un indicateur que l'objet CoffeeTracker
    '   peut utiliser pour annuler toutes les
    '   tâches longues lorsqu'elles déclenchent
    '   l'événement Progress suivant.
    CancelAll = True
End Sub

' Exécute quelques tâches courtes en série,
'   pour avoir un aperçu de leur vitesse
'   lorsqu'il n'y a pas de conflit pour
'   l'utilisation du processeur.
Private Sub cmdShortOnly_Click()
    lstResults.Clear
    CancelAll = False
    mintHowManyShort = 10
    tmrShort.Interval = 250
    tmrShort.Enabled = True
End Sub

' Démarre l'exécution d'une tâche longue,
'   puis l'exécution de tâches courtes en
'   série avant la fin de la tâche longue.
Private Sub cmdShortLong_Click()
    Dim cft As CoffeeTracker
    
    lstResults.Clear
    CancelAll = False
    Set cft = NewTracker(macfe(1).ThreadID, LONGTASKSIZE)
    Set cft.Coffee = macfe(1)
    Call macfe(1).StartLongTask(LONGTASKSIZE)
    '
    ' Met en ligne quelques tâches courtes à
    '   exécuter (une tous les quarts de seconde)
    '   pendant l'exécution de la tâche.
    mintHowManyShort = 10
    tmrShort.Enabled = True
    tmrShort.Interval = 250
End Sub

' Démarre N tâches longues (1 - 9), puis exécute
'   une série de tâches courtes.
Private Sub cmdNLong_Click()
    Dim intCt As Integer
    Dim cft As CoffeeTracker
    
    lstResults.Clear
    CancelAll = False
    For intCt = 1 To CLng("0" & txtN)
        Set cft = NewTracker(macfe(intCt).ThreadID, LONGTASKSIZE)
        Set cft.Coffee = macfe(intCt)
        Call macfe(intCt).StartLongTask(LONGTASKSIZE)
    Next
    '
    ' Met en ligne quelques tâches courtes
    '   à exécuter pendant l'exécution de
    '   la tâche longue.
    mintHowManyShort = 10 + CLng("0" & txtN)
    tmrShort.Enabled = True
    tmrShort.Interval = 250
End Sub

' Compare la dépréciation des appels pour
'   des appels à un objet de la même thread,
'   et pour des appels à un objet d'une
'   autre thread.
'
Private Sub cmdXThread_Click()
    Dim cfeSame As Coffee
    Dim cfeNew As Coffee
    
    cmdXThread.Caption = "Exécution..."
    cmdXThread.Enabled = False
    
    ' Crée un objet Coffee sur une autre thread.
    Set cfeNew = macfe(10).GetCoffeeOnNewThread
    ' En cas de regroupement de threads, une
    '   thread différente sera obtenue la
    '   deuxième fois, sauf s'il n'existe qu'une
    '   thread dans le regroupement.
    If cfeNew.ThreadID = macfe(10).ThreadID Then
        Set cfeNew = macfe(10).GetCoffeeOnNewThread
        If cfeNew.ThreadID = macfe(10).ThreadID Then
            MsgBox "Impossible de comparer les appels sur une même thread avec ceux effectués entre threads; impossible d'obtenir un objet sur une autre thread."
            Exit Sub
        End If
    End If
    '
    ' Crée un objet Coffee sur la même thread.
    Set cfeSame = macfe(10).GetCoffeeOnSameThread
    
    ' Utilise les derniers objets Coffee
    '   pour effectuer le test.
    MsgBox "Même thread:  " & macfe(10).CallAnotherCoffee(cfeSame) & " sec/appel" & vbCrLf _
        & "Interthread:  " & macfe(10).CallAnotherCoffee(cfeNew) & " sec/appel"
    
    cmdXThread.Caption = "Dépréciation interthreads"
    cmdXThread.Enabled = True
    '
    ' Les objets Coffee créés pour ce test
    '   se terminent lorsque cfeNew et cfeSame
    '   se trouvent hors de portée à la fin
    '   de cette procédure.
End Sub

' Liste les ID des thread des objets Coffee
'   créés lors du chargement de cette feuille.
'
Private Sub cmdIDs_Click()
    Dim intCt As Integer
    lstResults.Clear
    For intCt = 1 To 10
        lstResults.AddItem macfe(intCt).ThreadID _
            & "  (" & macfe(intCt).NumberOnThread & " sur la thread)"
    Next
End Sub

' Crée une série d'objets Coffee, chacun sur sa
'   propre thread. Si vous recompilez MTCoffee
'   lorsque le nombre maximum de threads est
'   inférieur à 10, certains partageront la
'   thread et l'état global.
'
Private Sub Form_Load()
    Dim intCt As Integer
    For intCt = 1 To 10
        Set macfe(intCt) = New Coffee
    Next
    Form1.cmdMT.Enabled = True
    Form1.cmdMT.MousePointer = vbDefault
End Sub

Private Sub Text1_KeyPress(KeyAscii As Integer)
    Select Case KeyAscii
        Case 48 To 57, 8
        Case Else
            Beep
            KeyAscii = 0
    End Select
End Sub

' Fournit des clés uniques pour les objets CoffeeTracker.
'
Private Function NewKey() As String
    Static lngLastKey As Long
    lngLastKey = lngLastKey + 1
    NewKey = "K" & lngLastKey
End Function

' Ajoute un nouvel objet CoffeeTracker. En fait, cela
'   devrait être une méthode d'une classe de la
'   collection CoffeeTrackers.
'
Private Function NewTracker(ByVal ThreadID As Long, _
        ByVal Size As Long) As CoffeeTracker
        
    Dim cft As New CoffeeTracker
    '
    ' Place en mémoire cache l'ID de la thread
    '   de l'objet Coffee dont le traqueur
    '   garde la trace.
    cft.ThreadID = ThreadID
    '
    ' Définit la taille de la tâche affectée à
    '   l'objet Coffee dont le traqueur garde
    '   la trace.
    cft.Size = Size
    '
    ' Donne au traqueur une clé unique pour
    '   la collection.
    cft.ID = NewKey
    '
    ' Met le nouveau traqueur dans une collection.
    CoffeeTrackers.Add cft, cft.ID
    '
    ' Renvoie une référence au nouveau traqueur.
    Set NewTracker = cft
End Function

' La minuterie est utilisée pour démarrer une
'   série de tâches courtes, à intervalles
'   réguliers, en utilisant un objet Coffee
'   (en fait, une thread unique). Avant de
'   démarrer une nouvelle tâche, elle vérifie
'   si la tâche précédente est terminée.
'
' Si vous exécutez le projet MTCoffee dans l'environnement
'   de développement, mettez en commentaire le code qui
'   vérifie si la tâche précédente est terminée.
'
Private Sub tmrShort_Timer()
    Static intCt As Integer
    Static strWaitingFor As String
    Dim cft As CoffeeTracker
    
    ' Si la variable strWaitingFor contient une clé de l'objet
    ' CoffeeTracker, l'objet Coffee exécute (ou exécutait)
    ' une tâche en étant surveillé par l'objet CoffeeTracker.
    If strWaitingFor <> "" Then
        On Error Resume Next
        '
        ' Si l'objet CoffeeTracker attendu
        '   ne fait plus partie de la
        '   collection, une erreur se produit;
        '   cela signifie qu'il convient d'en
        '   démarrer un autre.
        Set cft = CoffeeTrackers(strWaitingFor)
        If Err.Number = 0 Then Exit Sub
    Else
        ' Si la variable de chaîne statique est
        '   vide, la série de tâches courtes
        '   précédentes est terminée. Une nouvelle
        '   série commence; le compteur statique
        '   est donc réinitialisé (intCt).
        intCt = 0
    End If
    
    If Not CancelAll Then
        intCt = intCt + 1
        '
        ' Crée un objet CoffeeTracker attendant
        '   la demande à terminer.
        Set cft = NewTracker(macfe(10).ThreadID, SHORTTASKSIZE)
        '
        ' Donne à l'objet CoffeeTracker son
        '   objet Coffee à surveiller.
        Set cft.Coffee = macfe(10)
        '
        ' Démarre la tâche.
        Call macfe(10).StartLongTask(SHORTTASKSIZE)
        '
        ' Se prépare à attendre l'objet
        '   CoffeeTracker.
        strWaitingFor = cft.ID
    End If
    '
    ' Vérifie si la série de tâches courtes
    '   est terminée ou si elle a été interrompue
    '   par un clic sur le bouton Annuler:
    If (intCt >= mintHowManyShort) Or CancelAll Then
        intCt = 0
        tmrShort.Enabled = False
        strWaitingFor = ""
    End If
End Sub
