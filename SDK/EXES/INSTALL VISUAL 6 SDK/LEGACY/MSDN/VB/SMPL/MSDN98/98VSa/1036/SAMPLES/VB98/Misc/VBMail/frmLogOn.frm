VERSION 5.00
Object = "{20C62CAE-15DA-101B-B9A8-444553540000}#1.1#0"; "MSMAPI32.OCX"
Object = "{831FDD16-0C5C-11d2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{CDE57A40-8B86-11D0-B3C6-00A0C90AEA82}#1.0#0"; "MSDATGRD.OCX"
Begin VB.Form frmMain 
   Caption         =   "VB Mail"
   ClientHeight    =   6510
   ClientLeft      =   1410
   ClientTop       =   1440
   ClientWidth     =   9480
   LinkTopic       =   "Form1"
   NegotiateMenus  =   0   'False
   ScaleHeight     =   6510
   ScaleWidth      =   9480
   Begin MSComCtlLib.Toolbar tbrMail 
      Align           =   1  'Align Top
      Height          =   630
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   9480
      _ExtentX        =   16722
      _ExtentY        =   1111
      ButtonWidth     =   2408
      ButtonHeight    =   953
      Appearance      =   1
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   8
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Connecter"
            Key             =   "LogOn"
            Description     =   "Connexion"
            Object.ToolTipText     =   "Log On"
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Enabled         =   0   'False
            Caption         =   "Déconnecter"
            Key             =   "logOff"
            Description     =   "Déconnexion"
            Object.ToolTipText     =   "Log Off"
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Enabled         =   0   'False
            Style           =   4
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Enabled         =   0   'False
            Caption         =   "Extraire"
            Key             =   "fetch"
            Description     =   "Extraire les messages non lus"
            Object.ToolTipText     =   "Fetch unread messages"
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Enabled         =   0   'False
            Caption         =   "Carnet d'adresses"
            Key             =   "address"
            Description     =   "Afficher le carnet d'adresses"
            Style           =   5
            BeginProperty ButtonMenus {66833FEC-8583-11D1-B16A-00C0F0283628} 
               NumButtonMenus  =   2
               BeginProperty ButtonMenu1 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Enabled         =   0   'False
                  Key             =   "global"
                  Text            =   "Global"
               EndProperty
               BeginProperty ButtonMenu2 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Enabled         =   0   'False
                  Key             =   "recepient"
                  Text            =   "Recepient"
               EndProperty
            EndProperty
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Enabled         =   0   'False
            Style           =   4
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Enabled         =   0   'False
            Caption         =   "Composer"
            Key             =   "compose"
            Description     =   "Compose les messages"
            Object.ToolTipText     =   "Compose new message"
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
      EndProperty
   End
   Begin MSComCtlLib.ImageList imlMail 
      Left            =   240
      Top             =   5160
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   32
      ImageHeight     =   32
      MaskColor       =   12632256
      _Version        =   393216
   End
   Begin MSDataGridLib.DataGrid grdMess 
      Height          =   3780
      Left            =   60
      TabIndex        =   1
      Top             =   1155
      Width           =   9435
      _ExtentX        =   16642
      _ExtentY        =   6668
      _Version        =   393216
      AllowUpdate     =   0   'False
      HeadLines       =   1
      RowHeight       =   15
      BeginProperty HeadFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
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
      ColumnCount     =   2
      BeginProperty Column00 
         DataField       =   ""
         Caption         =   ""
         BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
            Type            =   0
            Format          =   ""
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1024
         EndProperty
      EndProperty
      BeginProperty Column01 
         DataField       =   ""
         Caption         =   ""
         BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
            Type            =   0
            Format          =   ""
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1024
         EndProperty
      EndProperty
      SplitCount      =   1
      BeginProperty Split0 
         BeginProperty Column00 
         EndProperty
         BeginProperty Column01 
         EndProperty
      EndProperty
   End
   Begin MSComCtlLib.StatusBar sbrMapi 
      Align           =   2  'Align Bottom
      Height          =   255
      Left            =   0
      TabIndex        =   0
      Top             =   6255
      Width           =   9480
      _ExtentX        =   16722
      _ExtentY        =   450
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
   End
   Begin MSMAPI.MAPIMessages mapMess 
      Left            =   615
      Top             =   615
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      AddressEditFieldCount=   1
      AddressModifiable=   0   'False
      AddressResolveUI=   0   'False
      FetchSorted     =   0   'False
      FetchUnreadOnly =   0   'False
   End
   Begin MSMAPI.MAPISession mapSess 
      Left            =   -45
      Top             =   570
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DownloadMail    =   -1  'True
      LogonUI         =   -1  'True
      NewSession      =   0   'False
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&Fichier"
      Begin VB.Menu mnuExit 
         Caption         =   "&Quitter"
      End
   End
   Begin VB.Menu mnuMail 
      Caption         =   "&Messagerie"
      Begin VB.Menu mnuLogOn 
         Caption         =   "&Connexion"
      End
      Begin VB.Menu mnuLogOff 
         Caption         =   "&Déconnexion"
         Enabled         =   0   'False
      End
   End
   Begin VB.Menu mnuTools 
      Caption         =   "&Outils"
      Enabled         =   0   'False
      Begin VB.Menu mnuCheck 
         Caption         =   "&Vérifier les nouveaux messages"
         Enabled         =   0   'False
         Shortcut        =   {F5}
      End
      Begin VB.Menu mnuAddress 
         Caption         =   "Carnet d'adresses"
         Enabled         =   0   'False
         Shortcut        =   ^{F1}
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private bNewSession As Boolean ' Indique le status du signal de connexion.
' Configure l'événement gbIgnoreEvent sur True à chaque fois
' qu'opération génératrice de l'événement BeforeColEdit du contrôle DataGrid
' est sur le point d'être réalisée. Si True est configurée,
' l'événement quittera sans autres exécutions.
Private gbIgnoreEvent As Boolean
Private WithEvents rsUnread As ADODB.Recordset
Attribute rsUnread.VB_VarHelpID = -1
Private gbGridConfigured As Boolean ' Indique la configuration du contrôle DataGrid
Private gbRSalreadyPopulated As Boolean ' Indique le remplissage du signal RS


Private Sub Form_Load()
    ' Configure StatusBar.
    sbrMapi.Panels(1).Key = "SessID"
    sbrMapi.Panels.Add , "MsgCnt" ' Ajoute le panneau
End Sub
Private Sub tbrMail_ButtonClick(ByVal Button As MSComCtlLib.Button)
    ' Utilise l'instruction Select Case pour déterminer le bouton
    ' sélectionné. La réaction se fera en fonction du bouton sélectionné.
    On Error GoTo ButtonErr
    
    Select Case Button.Key
    Case "LogOn"
    ' Exécute et extrait les messages non lus. CheckRS vérifie
    ' si l'objet Recordset ADO est déjà rempli
    ' et effectue un remplissage si nécessaire. La fonction DoGrid configure la
    ' grille et le remplit avec le jeu d'enregistrements.
        If LogOn = True Then
            FetchUnreadOnly
            CheckRS
            DoGrid
        Else
            Exit Sub
        End If
    Case "logOff" ' Déconnecte
        LogOff
    Case "fetch"
        FetchUnreadOnly
        ' Vérifie si l'objet Recordset ADO est
        ' déjà rempli. Effectue ensuite le remplissage de la grille.
        CheckRS
        DoGrid
    Case "compose" ' Crée un nouveau message.
        ComposeMessage
    Case "address"
        Debug.Print "quelque chose d'autre"
    Case Else
        Debug.Print Button.Key
    End Select
    Exit Sub
ButtonErr:
    Debug.Print Err.Number, Err.Description
    Resume Next
End Sub

Private Sub grdMess_BeforeColEdit(ByVal ColIndex As Integer, ByVal KeyAscii As Integer, Cancel As Integer)
    ' La configuration de la source de données dans la procédure de grille ConfigureGrid
    ' entraîne cet événement. Comme aucun message n'est à afficher pour le moment,
    ' il faut vérifier si un indicateur a été configuré
    ' dans la procédure. Si True est configuré, quitter.
    
    If gbIgnoreEvent Then Exit Sub
  
    On Error GoTo RowERR
    mapMess.MsgIndex = grdMess.Columns(0).Value ' Définit l'événement MsgIndex.
    
    Load frmRead ' Charge la feuille.
    ' Lit le message et les en-têtes et les place dans
    ' les contrôles Textbox appropriés.
    With frmRead
        .lblFrom = mapMess.MsgOrigDisplayName
        .lblCC = GetList(mapCcList)
        .lblTo = GetList(mapToList)
        .lblSubject = mapMess.MsgSubject
        .txtRead = mapMess.MsgNoteText
    End With
    grdMess.Columns("Read").Text = "X"
    
    frmRead.Show vbModal
    
    Exit Sub
RowERR:
    Debug.Print Err.Number, Err.Description
    Resume Next

End Sub



Private Sub CheckRS()
    ' Vérifie un indicateur avant de continuer la fonction gbRSalreadyPopulated
    ' . Efface le jeu d'enregistrements avant de
    ' le remplir à nouveau.
    If gbRSalreadyPopulated Then
        ClearRS
        PopulateRS
    Else
        PopulateRS
        gbRSalreadyPopulated = True
    End If
End Sub

Private Sub DoGrid()
    ' Vérifie un indicateur avant de continuer la fonction gbGridConfigured before
    ' . Si l'indicateur est déjà configuré, effacer.
    If gbGridConfigured Then
        gbIgnoreEvent = True
        grdMess.HoldFields ' Garde la configuration de la grille.
        Set grdMess.DataSource = rsUnread
        gbIgnoreEvent = False
    Else
        ConfigureGrid
    End If

End Sub

Private Sub ComposeMessage()
    On Error GoTo ComposeErr
    Dim strMessage As String
    ' Utilise la méthode Compose et extrait
    ' la méthode Send. Lorsque l'argument facultatif est configuré sur
    ' True, la feuille du système de messagerie sous-jacent
    ' est alors utilisée. Si la configuration est autre que sur True vous devez
    ' devez créer votre configuration.
    mapMess.Compose
    mapMess.Send True
    
    Exit Sub
ComposeErr:
    Debug.Print Err.Number, Err.Description
    Resume Next
End Sub

Private Sub CreateRS()
    ' Crée un objet Recordset ADO et ajoute des champs. Chaque champ devient une
    ' colonne dans le contrôle DataGrid.
    
    Set rsUnread = New ADODB.Recordset
    With rsUnread.Fields
        .Append "ID", adSmallInt
        .Append "Read", adBSTR
        .Append "Date  received", adDate
        .Append "From", adBSTR
        .Append "Subject", adBSTR
    End With
    rsUnread.Open
End Sub


Private Sub FetchUnreadOnly()
    With mapMess
         ' Extrait les messages non lus uniquement, puis affiche le nombre
         ' des messages non lus dans la barre d'état.
        .FetchUnreadOnly = True
        .Fetch
        sbrMapi.Panels("MsgCnt").Text = .MsgCount & " Messages"
    End With
End Sub

Private Sub ClearRS()
    ' Efface le jeu d'enregistrements de toutes les lignes.
    If rsUnread.RecordCount = 0 Then Exit Sub
    Dim i As Integer
    gbIgnoreEvent = True
    
    rsUnread.MoveFirst
    For i = 1 To rsUnread.RecordCount
        rsUnread.Delete adAffectCurrent
        DoEvents
    Next i
    gbIgnoreEvent = False

End Sub
Private Sub PopulateRS()
    gbIgnoreEvent = True ' Indique pour empêcher le processus de l'événement RowColChanged.
    Dim i As Integer
    For i = 0 To mapMess.MsgCount - 1
        mapMess.MsgIndex = i
        rsUnread.AddNew
        rsUnread!ID = i
        rsUnread![date received] = mapMess.MsgDateReceived
        rsUnread!From = mapMess.MsgOrigDisplayName
        rsUnread!Subject = mapMess.MsgSubject
    Next i
    gbIgnoreEvent = False ' Reconfigure l'indicateur.
    
End Sub
Private Sub ConfigureGrid()
    ' Configure la largeur des colonnes de la grille avant
    ' de configurer la source de données sur le jeu d'enregistrement.
    
    gbIgnoreEvent = True
    With grdMess
        Set .DataSource = rsUnread ' Efface l'événement.
        .Columns("ID").Width = 0   ' Masque la colonne ID.
        .Columns("Read").Width = 500
        .Columns("Date received").Width = 900
        .Columns("From").Width = 2000
        .Columns("Subject").Width = 5000
    End With
    Dim fmtdate As StdDataFormat
    
    ' Utilise l'objet Format pour configurer la
    '  colonne date.
    Set fmtdate = New StdDataFormat
    With fmtdate
        .Type = fmtCustom
        .Format = "Short Date"
     End With
    Set grdMess. _
    Columns("Date received").DataFormat = fmtdate
    
    gbIgnoreEvent = False
    gbGridConfigured = True ' Définit l'indicateur pour informer que
    ' cette opération n'est plus à faire.
End Sub


Private Function LogOn() As Boolean
    ' Crée un objet Recordset appelé rsUnread
    CreateRS

    ' Si une session a déjà débutée,
    ' quitter la procédure.
    If mapSess.NewSession Then
        MsgBox "Session déja en cours"
        Exit Function
    End If
    
    On Error GoTo errLogInFail
    With mapSess
        ' Définit la propriété DownLoadMail sur False pour empêcher un téléchargement immédiat.
        .DownLoadMail = False
        .LogonUI = True ' Utilise l'UI de connexion du système de messagerie sous-jacent.
        .SignOn ' Méthode Signon.
        ' Si cette opération a réussi, retourner sur True
        LogOn = True
        ' Définit la propriété NewSession sur True et définit
        ' l'indicateur de la variable sur True.
        .NewSession = True
        bNewSession = .NewSession
        mapMess.SessionID = .SessionID ' Ceci doit être défini avant de continuer.
        sbrMapi.Panels("SessID") = "ID = " & .SessionID ' Permet l'affichage de la propriété SessionID.
    End With
    ' Boutons activés et désactivés.
    ToggleButtonEnabled
    Exit Function
    
errLogInFail:
    Debug.Print Err.Number, Err.Description
    If Err.Number = 32003 Then
        MsgBox "Annuler la connection"
        LogOn = False
    End If
    Exit Function
End Function
Private Sub LogOff()
    ' Déconnecte le contrôle MapSessions .
    With mapSess
        .SignOff ' Ferme la cession.
        .NewSession = False ' Indicateur pour la nouvelle cession.
        bNewSession = .NewSession ' Réhinitialiser l'indicateur.
    End With
    ' Bouttons activés et désactivés.
    ToggleButtonEnabled
    
    rsUnread.Close ' Ferme l'objet Recordset ADO et configure la variable à Nothing.
    Set rsUnread = Nothing
    gbRSalreadyPopulated = False
    Unload frmRead ' Décharge la feuille.
    grdMess.ClearFields ' Efface la grille.
End Sub

Private Sub ToggleButtonEnabled()
    ' Bascule la propriété Enabled de divers bouttons.
    With tbrMail
        .Buttons("LogOn").Enabled = Abs(.Buttons("LogOn").Enabled) - 1
        .Buttons("logOff").Enabled = Abs(.Buttons("logOff").Enabled) - 1
        .Buttons("fetch").Enabled = Abs(.Buttons("fetch").Enabled) - 1
        .Buttons("compose").Enabled = Abs(.Buttons("compose").Enabled) - 1
        .Buttons("address").Enabled = Abs(.Buttons("address").Enabled) - 1
        .Buttons("address").ButtonMenus(1).Enabled = Abs(.Buttons("address").ButtonMenus(1).Enabled) - 1
        .Buttons("address").ButtonMenus(2).Enabled = Abs(.Buttons("address").ButtonMenus(2).Enabled) - 1
        
    End With
    
    ' Bascule le menu enabled.
    mnuLogOn.Enabled = Abs(mnuLogOn.Enabled) - 1
    mnuLogOff.Enabled = Abs(mnuLogOff.Enabled) - 1
    mnuTools.Enabled = Abs(mnuTools.Enabled) - 1
    mnuCheck.Enabled = Abs(mnuCheck.Enabled) - 1
    mnuAddress.Enabled = Abs(mnuAddress.Enabled) - 1

End Sub

Private Function GetList(ListType As Integer) As String
    ' La fonction prend seulement chacun des récipiants
    ' du message et les concatennent.
    Dim i As Integer
    Dim strList As String
    For i = 0 To mapMess.RecipCount - 1
        mapMess.RecipIndex = i
        If mapMess.RecipType = ListType Then
            strList = strList & mapMess.RecipDisplayName & "; "
        End If
    Next i
    If strList = "" Then
        GetList = ""
        Exit Function
    End If
    ' Strip semicolon from last recipient name.
    GetList = Left(strList, Len(strList) - 2)

End Function


Private Sub mnuAddress_Click()
    ' Affiche la carnet d'addresse.
    On Error GoTo AddressErr
    mapMess.Show True
    Exit Sub
AddressErr:
    Debug.Print Err.Number, Err.Description
    Resume Next
End Sub

Private Sub mnuCheck_Click()
    FetchUnreadOnly ' Extrait les messages non lus.
    CheckRS ' Vérifie l'objet Recordset et le rempli
    DoGrid ' Ajuste la source de données de la grille au jeu d'enregistrement.
    
End Sub

Private Sub mnuExit_Click()
    ' Sign off if not done yet, alors décharge la feuille.
    If mapSess.SessionID <> 0 Then mapSess.SignOff
    Unload Me
End Sub

Private Sub mnuLogOff_Click()
    LogOff
End Sub

Private Sub mnuLogOn_Click()
    If LogOn = True Then
        FetchUnreadOnly
        CheckRS
        DoGrid
    Else
        Exit Sub
    End If
End Sub

Private Sub tbrMail_ButtonMenuClick(ByVal ButtonMenu As MSComCtlLib.ButtonMenu)
    On Error GoTo btnClickErr
    Select Case ButtonMenu.Key
    Case "global"
        mapMess.Show False
    Case "recepient"
        mapMess.Show True
    End Select
    Exit Sub
btnClickErr:
    If Err.Number = mapUserAbort Then
        Resume Next
    Else
        MsgBox Err.Number & ": " & Err.Description
    End If
    
End Sub
