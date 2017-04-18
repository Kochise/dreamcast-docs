VERSION 5.00
Begin VB.Form frmProcessClaim 
   Caption         =   "Form1"
   ClientHeight    =   3435
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5415
   LinkTopic       =   "Form1"
   ScaleHeight     =   3435
   ScaleWidth      =   5415
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdSubmitClaim 
      Caption         =   "&Soumettre réclamation"
      Height          =   255
      Left            =   2880
      TabIndex        =   9
      Top             =   3000
      Visible         =   0   'False
      Width           =   2055
   End
   Begin VB.CommandButton cmdNewClaim 
      Caption         =   "&Nouvelle réclamation"
      Height          =   255
      Left            =   120
      TabIndex        =   10
      Top             =   3000
      Visible         =   0   'False
      Width           =   2055
   End
   Begin VB.CommandButton cmdApprove 
      Caption         =   "&Approve"
      Height          =   255
      Left            =   2880
      TabIndex        =   16
      Top             =   3000
      Width           =   2055
   End
   Begin VB.TextBox txtName 
      BackColor       =   &H8000000F&
      Height          =   285
      Left            =   2040
      TabIndex        =   0
      Text            =   "John Doe"
      Top             =   120
      Width           =   3135
   End
   Begin VB.TextBox txtStreet 
      BackColor       =   &H8000000F&
      Height          =   285
      Left            =   2040
      TabIndex        =   1
      Text            =   "1600 Pennsilvania Ave"
      Top             =   600
      Width           =   3135
   End
   Begin VB.TextBox txtCity 
      BackColor       =   &H8000000F&
      Height          =   285
      Left            =   2040
      TabIndex        =   2
      Text            =   "Washington"
      Top             =   1080
      Width           =   3135
   End
   Begin VB.TextBox txtState 
      BackColor       =   &H8000000F&
      Height          =   285
      Left            =   2040
      TabIndex        =   3
      Text            =   "D.C."
      Top             =   1560
      Width           =   3135
   End
   Begin VB.OptionButton optAuto 
      Caption         =   "Véhicule"
      Enabled         =   0   'False
      Height          =   255
      Left            =   1800
      TabIndex        =   4
      Top             =   2040
      Value           =   -1  'True
      Width           =   975
   End
   Begin VB.OptionButton optHome 
      Caption         =   "Maison"
      Enabled         =   0   'False
      Height          =   255
      Left            =   3000
      TabIndex        =   5
      Top             =   2040
      Width           =   975
   End
   Begin VB.OptionButton optBoat 
      Caption         =   "Bateau"
      Enabled         =   0   'False
      Height          =   255
      Left            =   4200
      TabIndex        =   6
      Top             =   2040
      Width           =   975
   End
   Begin VB.TextBox txtAmountOfClaim 
      BackColor       =   &H8000000F&
      Height          =   285
      Left            =   2040
      TabIndex        =   8
      Text            =   "2000"
      Top             =   2520
      Width           =   3135
   End
   Begin VB.Label Label1 
      Caption         =   "Nom:"
      Height          =   255
      Left            =   120
      TabIndex        =   15
      Top             =   120
      Width           =   1335
   End
   Begin VB.Label lblStreet 
      Caption         =   "Rue:"
      Height          =   255
      Left            =   120
      TabIndex        =   14
      Top             =   600
      Width           =   1335
   End
   Begin VB.Label lblCity 
      Caption         =   "Ville:"
      Height          =   255
      Left            =   120
      TabIndex        =   13
      Top             =   1080
      Width           =   1335
   End
   Begin VB.Label lblState 
      Caption         =   "État:"
      Height          =   255
      Left            =   120
      TabIndex        =   12
      Top             =   1560
      Width           =   1335
   End
   Begin VB.Label lblClaim 
      Caption         =   "Réclamation:"
      Height          =   255
      Left            =   120
      TabIndex        =   11
      Top             =   2040
      Width           =   1335
   End
   Begin VB.Label lblClaimAmmount 
      Caption         =   "Montant de la réclamation:"
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   2520
      Width           =   1935
   End
End
Attribute VB_Name = "frmProcessClaim"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
' --------------------------------------------------------
' La feuille Template pour le processus UI du déroulement des opérations
' Ce feuille Template est utilisée par différentes applications :
'  CLAIM_ENTRY       : App qui entre la réclamation (débute le déroulement des opérations)
'  CLAIM_PROCESSING  : App qui effectue le processus de réclamation (déplace le déroulement des opérations de l'une des files vers une autre file)
'  ACCOUNTING_PROCESSING  : App qui finit le déroulement des opérations (procède au déroulement dans la file finale)
'
'  Il est bon de savoir que la logique du noyau au cours de chacune de ces étapes est la même :
'  a) Obtention des informations
'  b) Processus des informations
'  c) Déplacement des informations
'
'  [11/13/97, IvoSa] Créée
' --------------------------------------------------------

#If CLAIM_PROCESSING Then
    Const FORM_CAPTION = "Processus de réclamation d'assurance"
#ElseIf ACCOUNTING_PROCESSING Then
    Const FORM_CAPTION = "Processus de réclamation de comptabilité"
#ElseIf CLAIM_ENTRY Then
    Const FORM_CAPTION = "Entrée de réclamation"
#End If

Private m_mqSendQueue As MSMQQueue 'File pour le service des réclamations

' Couleurs souhaitées
Const WINDOW_BACKGROUND = &H80000005
Const BUTTON_FACE = &H8000000F
' --------------------------------------------
' Configure la feuille avec les données de réclamation
'  [in] objStrBag      : Objet qui contient les données
'  [in] objMQNextQueue : File d'emplacement des éléments approuvés
' --------------------------------------------
Public Sub Initailzie(ByVal objStrBag As StringBag, ByVal objMQNextQueue As MSMQQueue)
    Set m_mqSendQueue = objMQNextQueue
    
    txtName = objStrBag.Retrieve(KEY_NAME)

' -------------------------------------------------
' Les messages dans la file de comptabilité ne prennent pas en charge rue, ville, état, etc...
' -------------------------------------------------
#If CLAIM_PROCESSING Then
    txtStreet = objStrBag.Retrieve(KEY_STREET)
    txtCity = objStrBag.Retrieve(KEY_CITY)
    txtState = objStrBag.Retrieve(KEY_STATE)
        
    Dim strClaim As String
    strClaim = objStrBag.Retrieve(KEY_CLAIM)
    
    If (strClaim = CLAIM_AUTO) Then
        optAuto.Value = True
    ElseIf (strClaim = CLAIM_HOME) Then
        optHome.Value = True
    Else
        optBoat.Value = True
    End If
#End If
    txtAmountOfClaim = CStr(objStrBag.Retrieve(KEY_AMOUNT))
End Sub

Private Sub cmdApprove_Click()
    ApproveClaim
End Sub

' ------------------------------------------------
' La réclamation a été approuvée, envoyer vers la file suivante
'  [11/13/97, IvoSa]
' ------------------------------------------------
Sub ApproveClaim()
    ' Si aucune file suivante, alors quitter
    If (m_mqSendQueue Is Nothing) Then
        MsgBox "Déroulement des opérations fini"
        Unload Me
        Exit Sub
    End If

    ' Réunit les propriétés bag avec le déroulement des opérations & l'envoyer
    Dim objStringBag As StringBag
    Set objStringBag = New StringBag
    objStringBag.Add KEY_NAME, txtName
    objStringBag.Add KEY_AMOUNT, txtAmountOfClaim

    objStringBag.serilizeToQueue m_mqSendQueue, txtName

    MsgBox "Envoie du message fini"
    Unload Me
End Sub

Private Sub cmdNewClaim_Click()
    ClearClaimInfo
End Sub

' ----------------------------------------------
' Soumet une réclamation
' ----------------------------------------------
Private Sub cmdSubmitClaim_Click()
    SubmitClaim
    MsgBox "Réclamation soumise avec succès !"
End Sub

' ------------------------------------------------
' Configure l'UI de la feuille
' ------------------------------------------------
Private Sub Form_Load()
    Me.Caption = FORM_CAPTION
#If CLAIM_PROCESSING Then
    ' Couleur
    txtName.BackColor = BUTTON_FACE
    txtStreet.BackColor = BUTTON_FACE
    txtCity.BackColor = BUTTON_FACE
    txtState.BackColor = BUTTON_FACE
    txtAmountOfClaim.BackColor = BUTTON_FACE
    
#ElseIf ACCOUNTING_PROCESSING Then
    ' Visibilité
    lblStreet.Visible = False
    lblCity.Visible = False
    lblState.Visible = False
    lblClaim.Visible = False
    
    optAuto.Visible = False
    optBoat.Visible = False
    optHome.Visible = False

    txtStreet.Visible = False
    txtCity.Visible = False
    txtState.Visible = False
    
    ' Couleur
    txtAmountOfClaim.BackColor = BUTTON_FACE
#ElseIf CLAIM_ENTRY Then
    ' Visible
    cmdApprove.Visible = False
    cmdNewClaim.Visible = True
    cmdSubmitClaim.Visible = True
    
    ' Couleur de fond
    txtName.BackColor = WINDOW_BACKGROUND
    txtStreet.BackColor = WINDOW_BACKGROUND
    txtCity.BackColor = WINDOW_BACKGROUND
    txtState.BackColor = WINDOW_BACKGROUND
    txtAmountOfClaim.BackColor = WINDOW_BACKGROUND
    
    ' Verrouillage
    txtName.Locked = False
    txtStreet.Locked = False
    txtCity.Locked = False
    txtState.Locked = False
    txtAmountOfClaim.Locked = False
    
    ' Activée
    optAuto.Enabled = True
    optBoat.Enabled = True
    optHome.Enabled = True

    ' Ouvre une file de soumissions...
    OpenMessageQueueForSubmit
#End If

End Sub

' -----------------------------
' Efface les informations de réclamation
' -----------------------------
Sub ClearClaimInfo()
    txtName = ""
    txtStreet = ""
    txtCity = ""
    txtState = ""
    
    optAuto.Value = True
    txtAmountOfClaim = ""
    
End Sub

' ----------------------------------------------
' Soumet une réclamation
' ----------------------------------------------
Private Sub SubmitClaim()

' Remplit une propriété bag avec les valeurs à envoyer...
Dim objStrBag As StringBag
    Set objStrBag = New StringBag
    objStrBag.Add KEY_NAME, Trim(txtName)
    objStrBag.Add KEY_STREET, Trim(txtStreet)
    objStrBag.Add KEY_CITY, Trim(txtCity)
    objStrBag.Add KEY_STATE, Trim(txtState)
    
    If (optAuto.Value) Then
        objStrBag.Add KEY_CLAIM, CLAIM_AUTO
    ElseIf (optHome.Value) Then
        objStrBag.Add KEY_CLAIM, CLAIM_HOME
    Else
        objStrBag.Add KEY_CLAIM, CLAIM_BOAT
    End If
    
    ' Prend en charge en tant que valeur monnétaire
    objStrBag.Add KEY_AMOUNT, CCur(txtAmountOfClaim)
    
    ' --------------------------------------------------
    ' GARDE LA COLLECTION DE DONNÉES DANS UN MESSAGE DE LA FILE
    ' --------------------------------------------------
    objStrBag.serilizeToQueue m_mqSendQueue, objStrBag.Retrieve(KEY_NAME)
End Sub


' ---------------------------------------------------------
' Ouvre la file du message 'Réclamations' pour soumettre les messages
'  [11/13/97, IvoSa] Créée
'  [12/6/97, IvoSa] Vérification des erreurs ajoutée
' ---------------------------------------------------------
Sub OpenMessageQueueForSubmit()
Dim lngError As Long
Dim strError As String

    On Error Resume Next
        Set m_mqSendQueue = openMessageQueue(INSURANCE_CLAIMS_QUEUE_NAME, MQ_SEND_ACCESS, True)
        lngError = Err
        strError = Err.Description
    On Error GoTo 0

    If lngError Then
        MsgBox ERROR_TEXT_RUNADMINTOOL & "(texte d'erreur spécifique lu: " & strError & ")"
        
        Stop ' Permet à l'app d'être déboguée maintenant...
        End ' Continuation de l'exécution non recommandée à ce stade
    End If
End Sub

Private Sub lblClaimAmmount_Click()

End Sub

Private Sub txtCity_Change()

End Sub

Private Sub txtName_Change()

End Sub
