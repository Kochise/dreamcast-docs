VERSION 5.00
Object = "{831FDD16-0C5C-11d2-A9FC-0000F8754DA1}#1.0#0"; "comctl32.ocx"
Begin VB.Form frmProperties 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Propriétés CommPort"
   ClientHeight    =   4185
   ClientLeft      =   2085
   ClientTop       =   2055
   ClientWidth     =   6390
   Icon            =   "frmProps.frx":0000
   LinkTopic       =   "Form3"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4185
   ScaleWidth      =   6390
   ShowInTaskbar   =   0   'False
   Begin VB.Frame fraSettings 
      BorderStyle     =   0  'None
      Height          =   3495
      Left            =   255
      TabIndex        =   1
      Top             =   570
      Width           =   5985
      Begin VB.CommandButton cmdCancel 
         Caption         =   "Annuler"
         Height          =   300
         Left            =   4845
         TabIndex        =   22
         Top             =   1065
         Width           =   1080
      End
      Begin VB.Frame Frame1 
         Caption         =   "Vitesse maximum"
         Height          =   870
         Left            =   120
         TabIndex        =   20
         Top             =   630
         Width           =   2610
         Begin VB.ComboBox cboSpeed 
            Height          =   315
            Left            =   675
            Style           =   2  'Dropdown List
            TabIndex        =   21
            Top             =   330
            Width           =   1695
         End
      End
      Begin VB.Frame fraConnection 
         Caption         =   "Préférences de connexion"
         Height          =   1770
         Left            =   120
         TabIndex        =   12
         Top             =   1620
         Width           =   2625
         Begin VB.ComboBox cboStopBits 
            Height          =   315
            Left            =   1350
            Style           =   2  'Dropdown List
            TabIndex        =   16
            Top             =   1260
            Width           =   1020
         End
         Begin VB.ComboBox cboParity 
            Height          =   315
            Left            =   1350
            Style           =   2  'Dropdown List
            TabIndex        =   15
            Top             =   810
            Width           =   1020
         End
         Begin VB.ComboBox cboDataBits 
            Height          =   315
            Left            =   1350
            Style           =   2  'Dropdown List
            TabIndex        =   14
            Top             =   330
            Width           =   1020
         End
         Begin VB.Label Label5 
            Caption         =   "Bits d'arrêt:"
            Height          =   285
            Left            =   480
            TabIndex        =   19
            Top             =   1320
            Width           =   885
         End
         Begin VB.Label Label4 
            Caption         =   "Parité:"
            Height          =   285
            Left            =   810
            TabIndex        =   18
            Top             =   855
            Width           =   465
         End
         Begin VB.Label Label3 
            Caption         =   "Bits de données:"
            Height          =   285
            Left            =   90
            TabIndex        =   17
            Top             =   375
            Width           =   1215
         End
      End
      Begin VB.ComboBox cboPort 
         Height          =   315
         Left            =   1050
         Style           =   2  'Dropdown List
         TabIndex        =   11
         Top             =   150
         Width           =   1425
      End
      Begin VB.CommandButton cmdOK 
         Caption         =   "OK"
         Default         =   -1  'True
         Height          =   300
         Left            =   4845
         MaskColor       =   &H00000000&
         TabIndex        =   10
         Top             =   705
         Width           =   1080
      End
      Begin VB.Frame Frame7 
         Caption         =   "&Écho"
         Height          =   870
         Left            =   2970
         TabIndex        =   7
         Top             =   630
         Width           =   1620
         Begin VB.OptionButton optEcho 
            Caption         =   "Non"
            Height          =   315
            Index           =   0
            Left            =   150
            MaskColor       =   &H00000000&
            TabIndex        =   9
            Top             =   360
            Width           =   615
         End
         Begin VB.OptionButton optEcho 
            Caption         =   "Oui"
            Height          =   195
            Index           =   1
            Left            =   795
            MaskColor       =   &H00000000&
            TabIndex        =   8
            Top             =   420
            Width           =   555
         End
      End
      Begin VB.Frame Frame5 
         Caption         =   "Contrôle du &Flux"
         Height          =   1770
         Left            =   2970
         TabIndex        =   2
         Top             =   1620
         Width           =   1620
         Begin VB.OptionButton optFlow 
            Caption         =   "Aucun"
            Height          =   255
            Index           =   0
            Left            =   180
            MaskColor       =   &H00000000&
            TabIndex        =   6
            Top             =   345
            Width           =   855
         End
         Begin VB.OptionButton optFlow 
            Caption         =   "XOn/XOff"
            Height          =   255
            Index           =   1
            Left            =   180
            MaskColor       =   &H00000000&
            TabIndex        =   5
            Top             =   645
            Width           =   1095
         End
         Begin VB.OptionButton optFlow 
            Caption         =   "RTS"
            Height          =   255
            Index           =   2
            Left            =   180
            MaskColor       =   &H00000000&
            TabIndex        =   4
            Top             =   945
            Width           =   1125
         End
         Begin VB.OptionButton optFlow 
            Caption         =   "XOn/RTS"
            Height          =   255
            Index           =   3
            Left            =   180
            MaskColor       =   &H00000000&
            TabIndex        =   3
            Top             =   1245
            Width           =   1065
         End
      End
      Begin VB.Label Label1 
         Caption         =   "Port:"
         Height          =   315
         Left            =   660
         TabIndex        =   13
         Top             =   210
         Width           =   495
      End
   End
   Begin MSComCtlLib.TabStrip tabSettings 
      Height          =   4065
      Left            =   90
      TabIndex        =   0
      Top             =   105
      Width           =   6300
      _ExtentX        =   11113
      _ExtentY        =   7170
      BeginProperty Tabs {0713E432-850A-101B-AFC0-4210102A8DA7} 
         NumTabs         =   1
         BeginProperty Tab1 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Propriétés"
            ImageVarType    =   2
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "frmProperties"
Attribute VB_Base = "0{7B2E0C91-D502-11CF-9BF3-00AA002FFD8F}"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_TemplateDerived = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private iFlow As Integer, iTempEcho As Boolean


Sub LoadPropertySettings()
Dim i As Integer, Settings As String, Offset As Integer

' Charge les paramètres du port de communication.
For i = 1 To 16
    cboPort.AddItem "Com" & Trim$(Str$(i))
Next i

' Charge les paramètres de vitesse.
cboSpeed.AddItem "110"
cboSpeed.AddItem "300"
cboSpeed.AddItem "600"
cboSpeed.AddItem "1200"
cboSpeed.AddItem "2400"
cboSpeed.AddItem "4800"
cboSpeed.AddItem "9600"
cboSpeed.AddItem "14400"
cboSpeed.AddItem "19200"
cboSpeed.AddItem "28800"
cboSpeed.AddItem "38400"
cboSpeed.AddItem "56000"
cboSpeed.AddItem "57600"
cboSpeed.AddItem "115200"
cboSpeed.AddItem "128000"
cboSpeed.AddItem "256000"

' Charge les paramètres de bit de donnée.
cboDataBits.AddItem "4"
cboDataBits.AddItem "5"
cboDataBits.AddItem "6"
cboDataBits.AddItem "7"
cboDataBits.AddItem "8"

' Charge les paramètres de parité.
cboParity.AddItem "Even"
cboParity.AddItem "Odd"
cboParity.AddItem "None"
cboParity.AddItem "Mark"
cboParity.AddItem "Space"

' Charge les paramètres de bit d'arrêt.
cboStopBits.AddItem "1"
cboStopBits.AddItem "1.5"
cboStopBits.AddItem "2"

' Définit les paramètres par défaut.

Settings = frmTerminal.MSComm1.Settings

' Dans tous les cas, l'élément le plus à droite des paramètres
' sera de 1 caractère, sauf lorsque le bit d'arrêt est 1.5.
If InStr(Settings, ".") > 0 Then
    Offset = 2
Else
    Offset = 0
End If

cboSpeed.Text = Left$(Settings, Len(Settings) - 6 - Offset)
Select Case Mid$(Settings, Len(Settings) - 4 - Offset, 1)
Case "e"
    cboParity.ListIndex = 0
Case "m"
    cboParity.ListIndex = 1
Case "n"
    cboParity.ListIndex = 2
Case "o"
    cboParity.ListIndex = 3
Case "s"
    cboParity.ListIndex = 4
End Select

cboDataBits.Text = Mid$(Settings, Len(Settings) - 2 - Offset, 1)
cboStopBits.Text = Right$(Settings, 1 + Offset)
    
cboPort.ListIndex = frmTerminal.MSComm1.CommPort - 1

optFlow(frmTerminal.MSComm1.Handshaking).Value = True
If Echo Then
    optEcho(1).Value = True
Else
    optEcho(0).Value = True
End If

End Sub


Private Sub cmdCancel_Click()
Unload Me
End Sub

Private Sub cmdOK_Click()
Dim OldPort As Integer, ReOpen As Boolean

On Error Resume Next

Echo = iTempEcho
OldPort = frmTerminal.MSComm1.CommPort
NewPort = cboPort.ListIndex + 1

If NewPort <> OldPort Then                   ' Si le numéro de port change, ferme l'ancien port.
    If frmTerminal.MSComm1.PortOpen Then
           frmTerminal.MSComm1.PortOpen = False
           ReOpen = True
    End If

    frmTerminal.MSComm1.CommPort = NewPort          ' Définit le nouveau numéro de port.
    
    If Err = 0 Then
        If ReOpen Then
            frmTerminal.MSComm1.PortOpen = True
            frmTerminal.mnuOpen.Checked = frmTerminal.MSComm1.PortOpen
            frmTerminal.mnuSendText.Enabled = frmTerminal.MSComm1.PortOpen
            frmTerminal.tbrToolBar.Buttons("TransmitTextFile").Enabled = frmTerminal.MSComm1.PortOpen
        End If
    End If
        
    If Err Then
        MsgBox Error$, 48
        frmTerminal.MSComm1.CommPort = OldPort
        Exit Sub
    End If
End If


frmTerminal.MSComm1.Settings = Trim$(cboSpeed.Text) & "," & Left$(cboParity.Text, 1) _
    & "," & Trim$(cboDataBits.Text) & "," & Trim$(cboStopBits.Text)

If Err Then
    MsgBox Error$, 48
    Exit Sub
End If

frmTerminal.MSComm1.Handshaking = iFlow
If Err Then
    MsgBox Error$, 48
    Exit Sub
End If

SaveSetting App.Title, "Properties", "Settings", frmTerminal.MSComm1.Settings
SaveSetting App.Title, "Properties", "CommPort", frmTerminal.MSComm1.CommPort
SaveSetting App.Title, "Properties", "Handshaking", frmTerminal.MSComm1.Handshaking
SaveSetting App.Title, "Properties", "Echo", Echo

Unload Me

End Sub

Private Sub Form_Load()

' Définit la taille de la feuille.
Me.Left = (Screen.Width - Me.Width) / 2
Me.Top = (Screen.Height - Me.Height) / 2

' Dimensionne le cadre pour l'ajuster au contrôle Tabstrip.
fraSettings.Move tabSettings.ClientLeft, tabSettings.ClientTop

' Vérifie que le cadre est le contrôle de premier plan.
fraSettings.ZOrder

' Charge les paramètres de la propriété courante.
LoadPropertySettings

End Sub

Private Sub optEcho_Click(Index As Integer)
If Index = 1 Then
    iTempEcho = True
Else
    iTempEcho = False
End If
End Sub

Private Sub optFlow_Click(Index As Integer)
iFlow = Index
End Sub


