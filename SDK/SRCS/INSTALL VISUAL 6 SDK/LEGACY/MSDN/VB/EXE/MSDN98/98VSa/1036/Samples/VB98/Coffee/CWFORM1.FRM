VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "CoffeeWatch2"
   ClientHeight    =   3765
   ClientLeft      =   1800
   ClientTop       =   1500
   ClientWidth     =   5160
   LinkTopic       =   "Form1"
   ScaleHeight     =   3765
   ScaleWidth      =   5160
   Begin VB.CommandButton cmdMT 
      Caption         =   "Exemple de traitement &multithread"
      Height          =   375
      Left            =   840
      TabIndex        =   4
      Top             =   3240
      Width           =   3255
   End
   Begin VB.ListBox lstCallBacks 
      Height          =   2205
      Left            =   2640
      TabIndex        =   3
      Top             =   840
      Width           =   2175
   End
   Begin VB.CommandButton cmdCallBacks 
      Caption         =   "Démarre la réception des &rappels"
      Height          =   615
      Left            =   2640
      TabIndex        =   1
      Top             =   120
      Width           =   2175
   End
   Begin VB.CommandButton cmdEvents 
      Caption         =   "Démarre la réception des événements Coffee&Ready"
      Height          =   615
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2175
   End
   Begin VB.ListBox lstEvents 
      Height          =   2205
      Left            =   120
      TabIndex        =   2
      Top             =   840
      Width           =   2175
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
' Stockage de niveau module pour l'objet
'   CoffeeMonitor partagé. La variable est
'   déclarée en tant que WithEvents: les
'   événements CoffeeMonitor peuvent ainsi
'   être gérés.
Private WithEvents mwcmnEvents As CoffeeMonitor
Attribute mwcmnEvents.VB_VarHelpID = -1
' Objet Connector utilisé pour obtenir
'   une référence à l'objet CoffeeMonitor
'   partagé.
Private mcctEvents As Connector

' Stockage de niveau module pour une référence
'   à l'objet CoffeeMonitor2 utilisé dans
'   l'exemple de la méthode de rappel.
Private mcm2CallBacks As CoffeeMonitor2
' Stockage pour une référence à l'objet de rappel.
Private mNotifyMe As New NotifyMe

' Bouton de commande pour lancer et arrêter la
'   réception des événements.
Private Sub cmdEvents_Click()
    Static blnInUse As Boolean
    
    If blnInUse Then
        ' Affecter la valeur Nothing à la variable
        '   WithEvents pour déconnecter l'objet
        '   de ses procédures d'événement.
        '   Ainsi, les événements ne seront plus reçus.
        Set mwcmnEvents = Nothing
        '
        ' Libère de l'objet Connector.
        Set mcctEvents = Nothing
        cmdEvents.Caption = "Démarre la réception des événements Coffee&Ready"
    Else
        Set mcctEvents = New Connector
        '
        ' L'objet Connector fournit une référence
        '   à l'objet CoffeeMonitor partagé. Lorsque la
        '   référence est placée dans la variable
        '   WithEvents, l'objet est connecté à sa
        '   procédure d'événement. Ainsi ,l'objet
        '   peut commencer à recevoir des événements.
        Set mwcmnEvents = mcctEvents.CoffeeMonitor
        cmdEvents.Caption = "ARRÊTE la réception des événements CoffeeReady"
    End If
    blnInUse = True Xor blnInUse
End Sub

' Bouton de commande pour lancer et arrêter
'   les rappels.
Private Sub cmdCallBacks_Click()
    Static blnInUse As Boolean
    Dim ct2 As New Connector2
    
    If blnInUse Then
        ' Informe l'objet CoffeeMonitor2 que les
        '   rappels (Callbacks) ne sont plus nécessaires.
        Call mcm2CallBacks.CeaseCallBacks(mNotifyMe)
        '
        ' Libère la copie partagée de l'objet CoffeeMonitor2.
        Set mcm2CallBacks = Nothing
        cmdCallBacks.Caption = "Démarre la réception des rappels"
    Else
        ' Obtient un objet Connector2 et l'utilise pour
        '   obtenir une référence à la copie partagée
        '   de l'objet CoffeeMonitor2.
        Set ct2 = New Connector2
        Set mcm2CallBacks = ct2.CoffeeMonitor2
        '
        ' Informe l'objet CoffeeMonitor2 de commencer
        '   à exécuter des appels à l'objet NotifyMe
        '   (l'objet est créé ici implicitement puisque
        '   la variable est déclarée comme As New).
        Call mcm2CallBacks.TellMeReady(mNotifyMe)
        cmdCallBacks.Caption = "ARRÊTE la réception des rappels"
    End If
    blnInUse = True Xor blnInUse
End Sub

Private Sub cmdMT_Click()
    ' Le lancement de l'exemple de traitement
    '   multithread nécessite la désactivation
    '   des rappels et des événements.
    '   Demandez à l'utilisateur si cela peut être
    '   fait. Si la réponse est vbNo, continuez et
    '   démarrez l'exemple de traitement multithread
    '   quand même.
    If (Not mwcmnEvents Is Nothing) Or _
            (Not mcm2CallBacks Is Nothing) Then
        Select Case MsgBox("Les notifications d'évenements et de rappels devraient être arrêtées avant de lancer l'exemple de thread exigeant des activités importantes du processeur. Les arrêter maintenant?", _
                vbYesNoCancel, "Démarre l'exemple de traitement multithread")
            Case vbYes
                ' Ceci ne décharge pas la feuille;
                '   les exemples sont simplement arrêtés.
                Call Form_Unload(False)
            Case vbCancel
                Exit Sub
        End Select
    End If
    cmdMT.Enabled = False
    frmThread.Show vbModeless
End Sub

' Ferme tous les exemples en cours d'exécution.
'
Private Sub Form_Unload(Cancel As Integer)
    If Not mwcmnEvents Is Nothing Then
        Call cmdEvents_Click
    End If
    If Not mcm2CallBacks Is Nothing Then
        Call cmdCallBacks_Click
    End If
End Sub

' Lorsque l'objet CoffeeMonitor envoie un
'   événement CoffeeReady, l'ajoute à la zone
'   de liste. Si celle-ci contient plus de dix
'   éléments, le plus ancien est effacé.
'
Private Sub mwcmnEvents_CoffeeReady()
    With lstEvents
        .AddItem Format$(Now, "ddd hh:mm:ss"), 0
        If .ListCount > 10 Then .RemoveItem 10
    End With
End Sub

