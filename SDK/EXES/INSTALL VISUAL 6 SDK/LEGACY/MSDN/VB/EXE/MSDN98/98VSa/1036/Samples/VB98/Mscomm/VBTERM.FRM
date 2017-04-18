VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.0#0"; "comdlg32.ocx"
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.0#0"; "mscomm32.ocx"
Object = "{831FDD16-0C5C-11d2-A9FC-0000F8754DA1}#1.0#0"; "mscomctl32.ocx"
Begin VB.Form frmTerminal
   Caption         =   "Terminal Visual Basic"
   ClientHeight    =   4935
   ClientLeft      =   2940
   ClientTop       =   2055
   ClientWidth     =   7155
   ForeColor       =   &H00000000&
   Icon            =   "vbterm.frx":0000
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4935
   ScaleWidth      =   7155
   Begin VB.Timer Timer2 
      Enabled         =   0   'False
      Interval        =   2000
      Left            =   210
      Top             =   3645
   End
   Begin VB.TextBox txtTerm 
      Height          =   3690
      Left            =   1245
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   3
      Top             =   1140
      Width           =   5790
   End
   Begin MSComCtlLib.Toolbar tbrToolBar 
      Align           =   1  'Align Top
      Height          =   390
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   7155
      _ExtentX        =   12621
      _ExtentY        =   688
      ButtonWidth     =   609
      ButtonHeight    =   582
      ImageList       =   "ImageList1"
      BeginProperty Buttons {0713E452-850A-101B-AFC0-4210102A8DA7} 
         NumButtons      =   10
         BeginProperty Button1 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Style           =   3
            Value           =   1
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button2 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "OpenLogFile"
            Description     =   "Ouverture du fichier journal..."
            Object.ToolTipText     =   "Ouverture du fichier journal"
            ImageIndex      =   1
         EndProperty
         BeginProperty Button3 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Key             =   "CloseLogFile"
            Description     =   "Fermeture du fichier journal"
            Object.ToolTipText     =   "Fermeture du fichier journal"
            ImageIndex      =   2
         EndProperty
         BeginProperty Button4 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Style           =   3
            Value           =   1
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button5 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "DialPhoneNumber"
            Description     =   "Compose le numéro de téléphone..."
            Object.ToolTipText     =   "Compose le numéro de téléphone"
            ImageIndex      =   3
         EndProperty
         BeginProperty Button6 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Key             =   "HangUpPhone"
            Description     =   "Raccroche"
            Object.ToolTipText     =   "Raccroche"
            ImageIndex      =   4
         EndProperty
         BeginProperty Button7 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Style           =   3
            Value           =   1
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button8 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Properties"
            Description     =   "Propriétés..."
            Object.ToolTipText     =   "Propriétés"
            ImageIndex      =   5
         EndProperty
         BeginProperty Button9 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Style           =   3
            Value           =   1
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button10 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Key             =   "TransmitTextFile"
            Description     =   "Transmet le fichier Texte..."
            Object.ToolTipText     =   "Transmet le fichier Texte"
            ImageIndex      =   6
         EndProperty
      EndProperty
      MouseIcon       =   "vbterm.frx":030A
      Begin VB.Frame Frame1 
         BorderStyle     =   0  'None
         Caption         =   "Frame1"
         Height          =   240
         Left            =   4000
         TabIndex        =   2
         Top             =   75
         Width           =   240
         Begin VB.Image imgConnected 
            Height          =   240
            Left            =   0
            Picture         =   "vbterm.frx":0326
            Stretch         =   -1  'True
            ToolTipText     =   "Bascule les ports"
            Top             =   0
            Width           =   240
         End
         Begin VB.Image imgNotConnected 
            Height          =   240
            Left            =   0
            Picture         =   "vbterm.frx":0470
            Stretch         =   -1  'True
            ToolTipText     =   "Bascule les ports"
            Top             =   0
            Width           =   240
         End
      End
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   165
      Top             =   1815
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   45
      Top             =   510
      _ExtentX        =   1005
      _ExtentY        =   1005
      DTREnable       =   -1  'True
      NullDiscard     =   -1  'True
      RThreshold      =   1
      RTSEnable       =   -1  'True
      SThreshold      =   1
      InputMode       =   1
   End
   Begin MSComDlg.CommonDialog OpenLog 
      Left            =   105
      Top             =   1170
      _ExtentX        =   847
      _ExtentY        =   847
      DefaultExt      =   "LOG"
      FileName        =   "Ouverture du fichier journal Communications"
      Filter          =   "Fichier journal (*.log)|*.log;"
      FilterIndex     =   501
      FontSize        =   9.02458e-38
   End
   Begin MSComCtlLib.StatusBar sbrStatus 
      Align           =   2  'Align Bottom
      Height          =   315
      Left            =   0
      TabIndex        =   0
      Top             =   4620
      Width           =   7155
      _ExtentX        =   12621
      _ExtentY        =   556
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   3
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   2
            Object.Width           =   2540
            MinWidth        =   2540
            Text            =   "État:"
            TextSave        =   "État:"
            Key             =   "Status"
            Object.ToolTipText     =   "État du port des communications"
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   1
            Object.Width           =   8310
            MinWidth        =   2
            Text            =   "Paramètres:"
            TextSave        =   "Paramètres:"
            Key             =   "Settings"
            Object.ToolTipText     =   "Paramètre du port des communications"
         EndProperty
         BeginProperty Panel3 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   2
            Object.Width           =   1244
            MinWidth        =   1244
	    Key = "ConnectTime"
          
           Object.ToolTipText     =   "Heure de connexion"
         EndProperty
      EndProperty
      MouseIcon       =   "vbterm.frx":05BA
   End
   Begin MSComCtlLib.ImageList ImageList1 
      Left            =   165
      Top             =   2445
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   6
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "vbterm.frx":05D6
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "vbterm.frx":08F0
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "vbterm.frx":0C0A
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "vbterm.frx":0F24
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "vbterm.frx":123E
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "vbterm.frx":1558
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&Fichier"
      Begin VB.Menu mnuOpenLog 
         Caption         =   "&Ouvrir un fichier journal..."
      End
      Begin VB.Menu mnuCloseLog 
         Caption         =   "F&ermer un fichier journal"
         Enabled         =   0   'False
      End
      Begin VB.Menu M3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuSendText 
         Caption         =   "&Transmettre un fichier Texte..."
         Enabled         =   0   'False
      End
      Begin VB.Menu Bar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "&Quitter"
      End
   End
   Begin VB.Menu mnuPort 
      Caption         =   "Port de &communication"
      Begin VB.Menu mnuOpen 
         Caption         =   "&Ouvrir le port de communication"
      End
      Begin VB.Menu MBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuProperties 
         Caption         =   "Propriétés..."
      End
   End
   Begin VB.Menu mnuMSComm 
      Caption         =   "&MSComm"
      Begin VB.Menu mnuInputLen 
         Caption         =   "&InputLen..."
      End
      Begin VB.Menu mnuRThreshold 
         Caption         =   "&RThreshold..."
      End
      Begin VB.Menu mnuSThreshold 
         Caption         =   "&SThreshold..."
      End
      Begin VB.Menu mnuParRep 
         Caption         =   "P&arityReplace..."
      End
      Begin VB.Menu mnuDTREnable 
         Caption         =   "&DTREnable"
      End
      Begin VB.Menu Bar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHCD 
         Caption         =   "&CDHolding..."
      End
      Begin VB.Menu mnuHCTS 
         Caption         =   "C&TSHolding..."
      End
      Begin VB.Menu mnuHDSR 
         Caption         =   "DSR&Holding..."
      End
   End
   Begin VB.Menu mnuCall 
      Caption         =   "&Appelle"
      Begin VB.Menu mnuDial 
         Caption         =   "&Compose le numéro de téléphone..."
      End
      Begin VB.Menu mnuHangUp 
         Caption         =   "&Raccroche"
         Enabled         =   0   'False
      End
   End
End
Attribute VB_Name = "frmTerminal"
Attribute VB_Base = "0{3E2D207C-D67B-11CF-9BF3-00AA002FFD8F}"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_TemplateDerived = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'--------------------------------------------------
' VBTerm - Ceci est un programme de démonstration pour
' le contrôle ActiveX de communications MSComm.
'
' Copyright (c) 1994, Crescent Software, Inc.
' par Don Malin et Carl Franklin.
'
' Mis à jour par Mike Maddox
'--------------------------------------------------
Option Explicit
                        
Dim Ret As Integer      ' Variable de travail sous forme d'entier.
Dim Temp As String      ' Variable de travail sous forme de chaîne de caractère.
Dim hLogFile As Integer ' Descripteur du fichier d'informations ouvert.
Dim StartTime As Date   ' Enregistre l'heure de début pour la minuterie du port.

Private Sub Form_Load()
    Dim CommPort As String, Handshaking As String, Settings As String
        
    On Error Resume Next
    
    ' Définit la couleur par défaut du terminal.
    txtTerm.SelLength = Len(txtTerm)
    txtTerm.SelText = ""
    txtTerm.ForeColor = vbBlue
       
    ' Définit le titre.
    App.Title = "Terminal Visual Basic"
    
    ' Définit les voyants de signalisation de l'état.
    imgNotConnected.ZOrder
       
    ' Centre la feuille.
    frmTerminal.Move (Screen.Width - Width) / 2, (Screen.Height - Height) / 2
    
    ' Charge les paramètres de la base de registres.
    
    Settings = GetSetting(App.Title, "Properties", "Settings", "") ' frmTerminal.MSComm1.Settings]\
    If Settings <> "" Then
        MSComm1.Settings = Settings
        If Err Then
            MsgBox Error$, 48
            Exit Sub
        End If
    End If
    
    CommPort = GetSetting(App.Title, "Properties", "CommPort", "") ' frmTerminal.MSComm1.CommPort
    If CommPort <> "" Then MSComm1.CommPort = CommPort
    
    Handshaking = GetSetting(App.Title, "Properties", "Handshaking", "") ' frmTerminal.MSComm1.Handshaking
    If Handshaking <> "" Then
        MSComm1.Handshaking = Handshaking
        If Err Then
            MsgBox Error$, 48
            Exit Sub
        End If
    End If
    
    Echo = GetSetting(App.Title, "Properties", "Echo", "") ' Echo
    On Error GoTo 0

End Sub

Private Sub Form_Resize()
   ' Redimensionne le contrôle Term (affichage).
   txtTerm.Move 0, tbrToolBar.Height, frmTerminal.ScaleWidth, frmTerminal.ScaleHeight - sbrStatus.Height - tbrToolBar.Height
   
   ' Positionne le voyant de signalisation de l'état.
   Frame1.Left = ScaleWidth - Frame1.Width * 1.5
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Dim Counter As Long

    If MSComm1.PortOpen Then
       ' Attend 10 secondes pour la transmission des données.
       Counter = Timer + 10
       Do While MSComm1.OutBufferCount
          Ret = DoEvents()
          If Timer > Counter Then
             Select Case MsgBox("Impossible de transmettre les données", 34)
                ' Annuler.
                Case 3
                   Cancel = True
                   Exit Sub
                ' Réessayer.
                Case 4
                   Counter = Timer + 10
                ' Ignorer.
                Case 5
                   Exit Do
             End Select
          End If
       Loop

       MSComm1.PortOpen = 0
    End If

    ' Si le fichier d'informations est ouvert, le vider et le fermer.
    If hLogFile Then mnuCloseLog_Click
    End
End Sub

Private Sub imgConnected_Click()
    ' Appelle la procédure mnuOpen_Click pour basculer entre la connexion et la déconnexion.
    Call mnuOpen_Click
End Sub

Private Sub imgNotConnected_Click()
    ' Appelle la procédure mnuOpen_Click pour basculer entre la connexion et la déconnexion.
    Call mnuOpen_Click
End Sub

Private Sub mnuCloseLog_Click()
    ' Ferme le fichier journal.
    Close hLogFile
    hLogFile = 0
    mnuOpenLog.Enabled = True
    tbrToolBar.Buttons("OpenLogFile").Enabled = True
    mnuCloseLog.Enabled = False
    tbrToolBar.Buttons("CloseLogFile").Enabled = False
    frmTerminal.Caption = "Terminal Visual Basic"
End Sub

Private Sub mnuDial_Click()
    On Local Error Resume Next
    Static Num As String
    
    Num = "1-206-936-6735" ' Ceci est le numéro de téléphone MSDN.
    
    ' Obtient un numéro de téléphone de l'utilisateur.
    Num = InputBox$("Veuillez composer un numéro de téléphone:", "Numéro composé", Num)
    If Num = "" Then Exit Sub
    
    ' Ouvre le port de communication s'il n'était pas déjà ouvert.
    If Not MSComm1.PortOpen Then
       mnuOpen_Click
       If Err Then Exit Sub
    End If
      
    ' Active le bouton Raccroche et les éléments de menu.
    mnuHangUp.Enabled = True
    tbrToolBar.Buttons("HangUpPhone").Enabled = True
              
    ' Compose le numéro.
    MSComm1.Output = "ATDT" & Num & vbCrLf
    
    ' Lance la minuterie du port.
    StartTiming
End Sub

' Bascule la propriété DTREnabled.
Private Sub mnuDTREnable_Click()
    ' Bascule la propriété DTREnabled.
    MSComm1.DTREnable = Not MSComm1.DTREnable
    mnuDTREnable.Checked = MSComm1.DTREnable
End Sub


Private Sub mnuFileExit_Click()
    ' Utilise Form_Unload car il contient du code pour vérifier la
    ' présence de données non transmises et l'ouverture du fichier
    ' journal.
    Form_Unload Ret
End Sub



' Bascule la propriété DTREnable pour raccrocher.
Private Sub mnuHangup_Click()
    On Error Resume Next
    
    MSComm1.Output = "ATH"      ' Envoie la chaîne pour raccrocher.
    Ret = MSComm1.DTREnable     ' Enregistre le paramètre en cours.
    MSComm1.DTREnable = True    ' Active Terminal de données prêt (DTR).
    MSComm1.DTREnable = False   ' Désactive Terminal de données prêt (DTR).
    MSComm1.DTREnable = Ret     ' Restaure l'ancien paramètre.
    mnuHangUp.Enabled = False
    tbrToolBar.Buttons("HangUpPhone").Enabled = False
    
    ' Si le port est encore ouvert, vous devez le fermer.
    If MSComm1.PortOpen Then MSComm1.PortOpen = False
    
    ' Informe l'utilisateur d'une erreur.
    If Err Then MsgBox Error$, 48
    
    mnuSendText.Enabled = False
    tbrToolBar.Buttons("TransmitTextFile").Enabled = False
    mnuHangUp.Enabled = False
    tbrToolBar.Buttons("HangUpPhone").Enabled = False
    mnuDial.Enabled = True
    tbrToolBar.Buttons("DialPhoneNumber").Enabled = True
    sbrStatus.Panels("Settings").Text = "Paramètres: "
    
    ' Éteint le voyant de signalisation et décoche le menu ouvert.
    mnuOpen.Checked = False
    imgNotConnected.ZOrder
            
    ' Arrête la minuterie du port.
    StopTiming
    sbrStatus.Panels("Status").Text = "État: "
    On Error GoTo 0
End Sub

' Affiche la valeur de la propriété CDHolding.
Private Sub mnuHCD_Click()
    If MSComm1.CDHolding Then
        Temp = "True"
    Else
        Temp = "False"
    End If
    MsgBox "CDHolding = " + Temp
End Sub

' Affiche la valeur de la propriété CTSHolding.
Private Sub mnuHCTS_Click()
    If MSComm1.CTSHolding Then
        Temp = "True"
    Else
        Temp = "False"
    End If
    MsgBox "CTSHolding = " + Temp
End Sub

' Affiche la valeur de la propriété DSRHolding.
Private Sub mnuHDSR_Click()
    If MSComm1.DSRHolding Then
        Temp = "True"
    Else
        Temp = "False"
    End If
    MsgBox "DSRHolding = " + Temp
End Sub

' Cette procédure définit la propriété InputLen, qui détermine
' le nombre d'octets de données devant être lu chaque fois que
' la propriété Input est utilisée pour lire des données du
' tampon d'entrée.
' Affecter la valeur 0 à la propriété InpuLen spécifie que le
' contenu entier du tampon doit être lu.
Private Sub mnuInputLen_Click()
    On Error Resume Next

    Temp = InputBox$("Entrez une nouvelle valeur pour InputLen:", "InputLen", Str$(MSComm1.InputLen))
    If Len(Temp) Then
        MSComm1.InputLen = Val(Temp)
        If Err Then MsgBox Error$, 48
    End If
End Sub

Private Sub mnuProperties_Click()
  ' Affiche la feuille des propriétés CommPort.
  frmProps.Show vbModal
  
End Sub

' Bascule l'état du port (ouvert ou fermé).
Private Sub mnuOpen_Click()
    On Error Resume Next
    Dim OpenFlag

    MSComm1.PortOpen = Not MSComm1.PortOpen
    If Err Then MsgBox Error$, 48
    
    OpenFlag = MSComm1.PortOpen
    
    mnuOpen.Checked = OpenFlag
    mnuSendText.Enabled = OpenFlag
    tbrToolBar.Buttons("TransmitTextFile").Enabled = OpenFlag
        
    If MSComm1.PortOpen Then
        ' Active le bouton Composer et les éléments du menu.
        mnuDial.Enabled = True
        tbrToolBar.Buttons("DialPhoneNumber").Enabled = True
        
        ' Active le bouton Raccrocher et les éléments du menu.
        mnuHangUp.Enabled = True
        tbrToolBar.Buttons("HangUpPhone").Enabled = True
        
        imgConnected.ZOrder
        sbrStatus.Panels("Settings").Text = "Paramètres: " & MSComm1.Settings
        StartTiming
    Else
        ' Active le bouton Composer et les éléments du menu.
        mnuDial.Enabled = True
        tbrToolBar.Buttons("DialPhoneNumber").Enabled = True
        
        ' Désactive le bouton Raccrocher et les éléments du menu.
        mnuHangUp.Enabled = False
        tbrToolBar.Buttons("HangUpPhone").Enabled = False
        
        imgNotConnected.ZOrder
        sbrStatus.Panels("Settings").Text = "Paramètres: "
        StopTiming
    End If
    
End Sub

Private Sub mnuOpenLog_Click()
   Dim replace
   On Error Resume Next
   OpenLog.Flags = cdlOFNHideReadOnly Or cdlOFNExplorer
   OpenLog.CancelError = True
      
   ' Obtient le nom du fichier journal de l'utilisateur.
   OpenLog.DialogTitle = "Ouvrir le fichier journal des communications"
   OpenLog.Filter = "Fichiers journal (*.LOG)|*.log|Tous les fichiers (*.*)|*.*"
   
   Do
      OpenLog.filename = ""
      OpenLog.ShowOpen
      If Err = cdlCancel Then Exit Sub
      Temp = OpenLog.filename

      ' Si le fichier existe déjà, demande si l'utilisateur veut l'écraser ou l'ajouter au fichier existant.
Ret = Len(Dir$(Temp))
      If Err Then
         MsgBox Error$, 48
         Exit Sub
      End If
      If Ret Then
         replace = MsgBox("Replacer le fichier existant - " + Temp + "?", 35)
      Else
         replace = 0
      End If
   Loop While replace = 2

   ' L'utilisateur a cliqué sur le bouton Oui; le fichier sera supprimé.
   If replace = 6 Then
      Kill Temp
      If Err Then
         MsgBox Error$, 48
         Exit Sub
      End If
   End If

   ' Ouvre le fichier journal.
   hLogFile = FreeFile
   Open Temp For Binary Access Write As hLogFile
   If Err Then
      MsgBox Error$, 48
      Close hLogFile
      hLogFile = 0
      Exit Sub
   Else
      ' Va à la fin du fichier pour ajouter de nouvelles données.
      Seek hLogFile, LOF(hLogFile) + 1
   End If

   frmTerminal.Caption = "Terminal Visual Basic - " + OpenLog.FileTitle
   mnuOpenLog.Enabled = False
   tbrToolBar.Buttons("OpenLogFile").Enabled = False
   mnuCloseLog.Enabled = True
   tbrToolBar.Buttons("CloseLogFile").Enabled = True
End Sub

' Cette procédure définit la propriété ParityReplace contenant un
' caractère qui remplace tous les caractères incorrects reçus à
' cause d'une erreur de parité.
Private Sub mnuParRep_Click()
    On Error Resume Next

    Temp = InputBox$("Entrez le caractère de remplacement", "ParityReplace", frmTerminal.MSComm1.ParityReplace)
    frmTerminal.MSComm1.ParityReplace = Left$(Temp, 1)
    If Err Then MsgBox Error$, 48
End Sub

' Cette procédure définit la propriété RThreshold, qui détermine
' le nombre d'octets de données pouvant arriver dans le tampon
' d'entrée, avant le déclenchement de l'événement OnComm et
' l'affectation de la valeur comEvReceive à la propriété
' CommEvent.
Private Sub mnuRThreshold_Click()
    On Error Resume Next
    
    Temp = InputBox$("Entrez une nouvelle valeur pour RThreshold:", "RThreshold", Str$(MSComm1.RThreshold))
    If Len(Temp) Then
        MSComm1.RThreshold = Val(Temp)
        If Err Then MsgBox Error$, 48
    End If

End Sub




' L'événement OnComm est utilisé pour récupérer des événements et des erreurs de communication.
Private Static Sub MSComm1_OnComm()
    Dim EVMsg$
    Dim ERMsg$
    
    ' Sélectionne en fonction de la propriété CommEvent.
    Select Case MSComm1.CommEvent
        ' Messages d'événement.
        Case comEvReceive
            Dim Buffer As Variant
            Buffer = MSComm1.Input
            Debug.Print "Réception - " & StrConv(Buffer, vbUnicode)
            ShowData txtTerm, (StrConv(Buffer, vbUnicode))
        Case comEvSend
        Case comEvCTS
            EVMsg$ = "Changement de Prêt à émettre (CTS) détecté"
        Case comEvDSR
            EVMsg$ = "Changement de Modem prêt (DSR) détecté"
        Case comEvCD
            EVMsg$ = "Changement de Détection de porteuse (CD) détecté"
        Case comEvRing
            EVMsg$ = "Le téléphone sonne"
        Case comEvEOF
            EVMsg$ = "Fin de fichier détectée"

        ' Messages d'erreur.
        Case comBreak
            ERMsg$ = "Pause reçue"
        Case comCDTO
            ERMsg$ = "Délai d'attente de Détection de porteuse (CD) expiré"
        Case comCTSTO
            ERMsg$ = "Délai d'attente de Prêt à émettre (CTS) expiré"
        Case comDCB
            ERMsg$ = "Erreur d'extraction de Bloc de contrôle de périphérique (DCB)"
        Case comDSRTO
            ERMsg$ = "Délai d'attente de Modem prêt (DSR) expiré"
        Case comFrame
            ERMsg$ = "Erreur de cadrage"
        Case comOverrun
            ERMsg$ = "Erreur de cadence"
        Case comRxOver
            ERMsg$ = "Dépassement du tampon de réception"
        Case comRxParity
            ERMsg$ = "Erreur de parité"
        Case comTxFull
            ERMsg$ = "Tampon de transmission plein"
        Case Else
            ERMsg$ = "Erreur ou événement inconnus"
    End Select
    
    If Len(EVMsg$) Then
        ' Affiche les messages d'erreur dans la barre d'état.
        sbrStatus.Panels("Status").Text = "État: " & EVMsg$
                
        ' Active la minuterie pour effacer le message contenu dans
        ' la barre d'état après 2 secondes.
        Timer2.Enabled = True
        
    ElseIf Len(ERMsg$) Then
        ' Affiche les messages d'événement dans la barre d'état.
        sbrStatus.Panels("Status").Text = "État: " & ERMsg$
        
        ' Affiche les messages d'erreur dans une boîte de message.
        Beep
        Ret = MsgBox(ERMsg$, 1, "Cliquer sur Annuler pour quitter, sur OK pour ignorer.")
        
        ' Si l'utilisateur clique sur Annuler (2)...
        If Ret = 2 Then
            MSComm1.PortOpen = False    ' Ferme le port et quitte.
        End If
        
        ' Active la minuterie pour effacer le message contenu dans
        ' la barre d'état après 2 secondes.
Timer2.Enabled = True
    End If
End Sub

Private Sub mnuSendText_Click()
   Dim hSend, BSize, LF&
   
   On Error Resume Next
   
   mnuSendText.Enabled = False
   tbrToolBar.Buttons("TransmitTextFile").Enabled = False
   
   ' Obtient le nom du fichier texte de l'utilisateur.
OpenLog.DialogTitle = "Transmettre un fichier Texte"
   OpenLog.Filter = "Fichiers Texte (*.TXT)|*.txt|Tous les fichiers (*.*)|*.*"
   Do
      OpenLog.CancelError = True
      OpenLog.filename = ""
      OpenLog.ShowOpen
      If Err = cdlCancel Then
        mnuSendText.Enabled = True
        tbrToolBar.Buttons("TransmitTextFile").Enabled = True
        Exit Sub
      End If
      Temp = OpenLog.filename

      ' Si le fichier n'existe pas, revient en arrière.
      Ret = Len(Dir$(Temp))
      If Err Then
         MsgBox Error$, 48
         mnuSendText.Enabled = True
         tbrToolBar.Buttons("TransmitTextFile").Enabled = True
         Exit Sub
      End If
      If Ret Then
         Exit Do
      Else
         MsgBox Temp + " introuvable!", 48
      End If
   Loop

   ' Ouvre le fichier journal.
   hSend = FreeFile
   Open Temp For Binary Access Read As hSend
   If Err Then
      MsgBox Error$, 48
   Else
      ' Affiche la boîte de dialogue Annuler.
CancelSend = False
      frmCancelSend.Label1.Caption = "Transmission d'un fichier texte - " + Temp
      frmCancelSend.Show
      
      ' Lit le fichier par blocs de la taille du tampon de transmission.
      BSize = MSComm1.OutBufferSize
      LF& = LOF(hSend)
      Do Until EOF(hSend) Or CancelSend
         ' Ne pas en lire autant à la fin.
         If LF& - Loc(hSend) <= BSize Then
            BSize = LF& - Loc(hSend) + 1
         End If
      
         ' Lit un bloc de données.
         Temp = Space$(BSize)
         Get hSend, , Temp
      
         ' Transmet le bloc.
         MSComm1.Output = Temp
         If Err Then
            MsgBox Error$, 48
            Exit Do
         End If
      
         ' Attend que toutes les données soient transmises.
         Do
            Ret = DoEvents()
         Loop Until MSComm1.OutBufferCount = 0 Or CancelSend
      Loop
   End If
   
   Close hSend
   mnuSendText.Enabled = True
   tbrToolBar.Buttons("TransmitTextFile").Enabled = True
   CancelSend = True
   frmCancelSend.Hide
End Sub

' Cette procédure définit la propriété SThreshold, qui détermine
' le nombre d'octets de données (au maximum) pouvant attendre dans
' le tampon de sortie, avant l'affectation de la valeur comEvSend
' à la propriété CommEvent et le déclenchement de l'événement
' OnComm.
Private Sub mnuSThreshold_Click()
    On Error Resume Next
    
    Temp = InputBox$("Entrez une nouvelle valeur pour SThreshold", "SThreshold", Str$(MSComm1.SThreshold))
    If Len(Temp) Then
        MSComm1.SThreshold = Val(Temp)
        If Err Then MsgBox Error$, 48
    End If
End Sub

' Cette procédure ajoute des données dans la propriété Text du
' contrôle Term. Elle filtre également les caractères de contrôle,
' comme le retour arrière, le retour chariot, et les sauts de
' ligne, et inscrit les données dans un fichier journal ouvert.
' Les caractères de retour arrière suppriment le caractère de
' gauche dans la propriété Text ou dans la chaîne passée. Les
' caractères de saut de ligne sont ajoutés à tous les retours
' chariot. La taille de la propriété Text du contrôle Term est
' également contrôlée de façon à ne pas excéder les caractères de
' la constante MAXTERMSIZE.
Private Static Sub ShowData(Term As Control, Data As String)
    On Error GoTo Handler
    Const MAXTERMSIZE = 16000
    Dim TermSize As Long, i
    
    ' Vérifie que le texte existant ne devient pas trop grand.
    TermSize = Len(Term.Text)
    If TermSize > MAXTERMSIZE Then
       Term.Text = Mid$(Term.Text, 4097)
       TermSize = Len(Term.Text)
    End If

    ' Pointe à la fin des données du contrôle Term.
    Term.SelStart = TermSize

    ' Filtre/manipule les caractères de retour arrière.
    Do
       i = InStr(Data, Chr$(8))
       If i Then
          If i = 1 Then
             Term.SelStart = TermSize - 1
             Term.SelLength = 1
             Data = Mid$(Data, i + 1)
          Else
             Data = Left$(Data, i - 2) & Mid$(Data, i + 1)
          End If
       End If
    Loop While i

    ' Élimine les sauts de ligne.
    Do
       i = InStr(Data, Chr$(10))
       If i Then
          Data = Left$(Data, i - 1) & Mid$(Data, i + 1)
       End If
    Loop While i

    ' Vérifie que tous les retours chariot ont un saut de ligne.
    i = 1
    Do
       i = InStr(i, Data, Chr$(13))
       If i Then
          Data = Left$(Data, i) & Chr$(10) & Mid$(Data, i + 1)
          i = i + 1
       End If
    Loop While i

    ' Ajoute les données filtrées à la propriété SelText.
    Term.SelText = Data
  
    ' Inscrit les données dans le fichier sur demande.
    If hLogFile Then
       i = 2
       Do
          Err = 0
          Put hLogFile, , Data
          If Err Then
             i = MsgBox(Error$, 21)
             If i = 2 Then
                mnuCloseLog_Click
             End If
          End If
       Loop While i <> 2
    End If
    Term.SelStart = Len(Term.Text)
Exit Sub

Handler:
    MsgBox Error$
    Resume Next
End Sub

Private Sub Timer2_Timer()
sbrStatus.Panels("Status").Text = "État: "
Timer2.Enabled = False

End Sub

' Les touches de clavier récupérées ici sont envoyées au contrôle
' MSComm qui les renvoie (en écho) par l'intermédiaire de
' l'événement OnComm (comEvReceive), et les affiche avec la
' procédure ShowData.
Private Sub txtTerm_KeyPress(KeyAscii As Integer)
    ' Si le port de communication est ouvert...
    If MSComm1.PortOpen Then
        ' Envoie les touches frappées vers le port de communication.
        MSComm1.Output = Chr$(KeyAscii)
        
        ' À moins que le mode Écho ne soit activé,
        ' le contrôle texte n'a pas besoin d'afficher les touches.
        ' En général, un modem renvoie un caractère en retour.
        If Not Echo Then
            ' Place la position à la fin du terminal.
            txtTerm.SelStart = Len(txtTerm)
            KeyAscii = 0
        End If
    End If
     
End Sub


Private Sub tbrToolBar_ButtonClick(ByVal Button As MSComCtlLib.Button)
Select Case Button.Key
Case "OpenLogFile"
    Call mnuOpenLog_Click
Case "CloseLogFile"
    Call mnuCloseLog_Click
Case "DialPhoneNumber"
    Call mnuDial_Click
Case "HangUpPhone"
    Call mnuHangup_Click
Case "Properties"
    Call mnuProperties_Click
Case "TransmitTextFile"
    Call mnuSendText_Click
End Select
End Sub

Private Sub Timer1_Timer()
    ' Affiche l'heure de connexion
    sbrStatus.Panels("ConnectTime").Text = Format(Now - StartTime, "hh:mm:ss") & " "
End Sub
' Appelle cette fonction pour exécuter la minuterie de l'heure de connexion.
Private Sub StartTiming()
    StartTime = Now
    Timer1.Enabled = True
End Sub
' Appelle cette fonction pour arrêter la minuterie.
Private Sub StopTiming()
    Timer1.Enabled = False
    sbrStatus.Panels("ConnectTime").Text = ""
End Sub
