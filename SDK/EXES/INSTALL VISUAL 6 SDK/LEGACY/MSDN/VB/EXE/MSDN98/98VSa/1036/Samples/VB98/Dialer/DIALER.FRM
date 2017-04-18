VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form DIALER 
   Caption         =   "Numéroteur téléphonique"
   ClientHeight    =   1545
   ClientLeft      =   2310
   ClientTop       =   2610
   ClientWidth     =   4590
   LinkTopic       =   "Form2"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   1545
   ScaleWidth      =   4590
   WhatsThisHelp   =   -1  'True
   Begin MSCommLib.MSComm MSComm1 
      Left            =   0
      Top             =   0
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Annuler"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   348
      Left            =   1800
      TabIndex        =   3
      Top             =   885
      Width           =   1095
   End
   Begin VB.CommandButton QuitButton 
      Cancel          =   -1  'True
      Caption         =   "Quitter"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   348
      Left            =   3000
      TabIndex        =   1
      Top             =   885
      Width           =   1095
   End
   Begin VB.CommandButton DialButton 
      Caption         =   "Composer"
      Default         =   -1  'True
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   348
      Left            =   600
      TabIndex        =   0
      Top             =   885
      Width           =   1095
   End
   Begin VB.Label Status 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Pour appeler, cliquez sur Composer"
      Height          =   255
      Left            =   720
      TabIndex        =   2
      Top             =   360
      Width           =   2775
   End
End
Attribute VB_Name = "DIALER"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'--------------------------------------------------------
'   DIALER.FRM
'   Copyright (c) 1994 Crescent Software, Inc.
'   par Carl Franklin
'
'   Modifié par Anton de Jong
'
'   Montre comment composer des numéros de téléphone avec un modem.
'
'   Pour que ce programme fonctionne, votre téléphone et
'   votre modem doivent êtres connectés sur la même ligne
'   téléphonique.
'--------------------------------------------------------
Option Explicit

DefInt A-Z

' Cet indicateur est défini quand l'utilisateur choisit Annuler.
Dim CancelFlag

Private Sub CancelButton_Click()
    ' CancelFlag indique à la procédure de composition de sortir.
    CancelFlag = True
    CancelButton.Enabled = False
End Sub

Private Sub Dial(Number$)
    Dim DialString$, FromModem$, dummy

    ' AT est la commande ATTENTION compatible Hayes et elle est
    ' requise pour envoyer des commandes au modem.
    ' DT signifie "Dial Tone" (Composition par tonalité).
    ' La commande Composer utilise alors la tonalité des touches du téléphone.
    ' DP signifie "Dial Pulse" (Composition par impulsion).
    ' PhoneNumbers$(Index) contient le numéro de téléphone à composer.
    ' Un point virgule (;) à la fin indique au modem de revenir
    ' en mode commande après la composition (important, certains modems
    ' peuvent ne pas avoir cette fonctionnalité).
    ' Un retour chariot (Carriage Return ou Chr$(13)) est requis
    ' quand la commande est envoyée au modem.
    DialString$ = "ATDT" + Number$ + ";" + vbCr

    ' Paramétrage du port de communication.

    ' En supposant qu'une souris est reliée à COM1,
    ' et que la propriété CommPort a pour valeur 2.
    MSComm1.CommPort = 2
    MSComm1.Settings = "9600,N,8,1"
    
    ' Ouvre le port de communication.
    On Error Resume Next
    MSComm1.PortOpen = True
    If Err Then
       MsgBox "COM2: n'est pas disponible. Changez la propriété CommPort pour un autre port."
       Exit Sub
    End If
    
    ' Vide le tampon d'entrée.
    MSComm1.InBufferCount = 0
    
    ' Compose le numéro.
    MSComm1.Output = DialString$
    
    ' Attend la chaîne "OK" venant du modem.
    Do
       dummy = DoEvents()
       ' S'il y a des données dans le tampon, les lire.
       If MSComm1.InBufferCount Then
          FromModem$ = FromModem$ + MSComm1.Input
          ' Vérifie si c'est "OK".
          If InStr(FromModem$, "OK") Then
             ' Indique à l'utilisateur de décrocher le combiné du téléphone.
             Beep
             MsgBox "Veuillez décrocher le combiné du téléphone et ensuite appuyer sur Entrée ou cliquer sur OK"
             Exit Do
          End If
       End If
        
       ' Est-ce que l'utilisateur a choisi Annuler?
       If CancelFlag Then
          CancelFlag = False
          Exit Do
       End If
    Loop
    
    ' Déconnecte le modem.
    MSComm1.Output = "ATH" + vbCr
    
    ' Ferme le port de communication.
    MSComm1.PortOpen = False
End Sub

Private Sub DialButton_Click()
    Dim Number$, Temp$
    
    DialButton.Enabled = False
    QuitButton.Enabled = False
    CancelButton.Enabled = True
    
    ' Obtient le numéro à composer.
    Number$ = InputBox$("Tapez le numéro de téléphone:", Number$)
        If Number$ = "" Then Exit Sub
    Temp$ = Status
    Status = "Composition - " + Number$
    
    ' Compose le numéro de téléphone tapé.
    Dial Number$

    DialButton.Enabled = True
    QuitButton.Enabled = True
    CancelButton.Enabled = False

    Status = Temp$
End Sub

Private Sub Form_Load()
    ' Affecte la valeur 0 à la propriété InputLen: indique au
    ' contrôle MSComm de lire le contenu entier du tampon d'entrée
    ' quand la propriété Input est utilisée.
    MSComm1.InputLen = 0
    
End Sub

Private Sub QuitButton_Click()
    End
End Sub

