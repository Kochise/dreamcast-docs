VERSION 5.00
Begin VB.Form frmAboutBox 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "À propos de MCITest"
   ClientHeight    =   2100
   ClientLeft      =   2055
   ClientTop       =   1935
   ClientWidth     =   4755
   BeginProperty Font 
      Name            =   "System"
      Size            =   9.75
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2100
   ScaleWidth      =   4755
   Begin VB.CommandButton BTN_OK 
      Caption         =   "OK"
      Height          =   360
      Left            =   1920
      TabIndex        =   1
      Top             =   1500
      Width           =   1080
   End
   Begin VB.PictureBox picAbout 
      BackColor       =   &H00808000&
      Enabled         =   0   'False
      Height          =   1140
      Left            =   1170
      ScaleHeight     =   1080
      ScaleWidth      =   3345
      TabIndex        =   2
      Top             =   225
      Width           =   3405
      Begin VB.Label lblAbout3 
         Alignment       =   2  'Center
         BackColor       =   &H00808000&
         Caption         =   "Version 1.01"
         Height          =   240
         Left            =   120
         TabIndex        =   5
         Top             =   735
         Width           =   2775
      End
      Begin VB.Label lblAbout2 
         Alignment       =   2  'Center
         BackColor       =   &H00808000&
         Caption         =   "Application pour le Contrôle MCI"
         Height          =   240
         Left            =   60
         TabIndex        =   4
         Top             =   375
         Width           =   3195
      End
      Begin VB.Label lblAbout1 
         Alignment       =   2  'Center
         BackColor       =   &H00808000&
         Caption         =   "Microsoft Visual Basic"
         Height          =   240
         Left            =   120
         TabIndex        =   3
         Top             =   75
         Width           =   2775
      End
   End
   Begin VB.PictureBox PIC_Icon 
      BorderStyle     =   0  'None
      Enabled         =   0   'False
      Height          =   495
      Left            =   480
      Picture         =   "aboutbox.frx":0000
      ScaleHeight     =   495
      ScaleWidth      =   480
      TabIndex        =   0
      Top             =   225
      Width           =   480
   End
End
Attribute VB_Name = "frmAboutBox"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub BTN_OK_Click()
    Unload frmAboutBox
End Sub

Private Sub BTN_OK_GotFocus()
    Dim i As Integer
    
    ' Glisse les étiquettes dans le contrôle PictureBox.
    ' Appelle la procédure WaitForEventsToFinish pour redessiner les étiquettes.
    While lblAbout1.Left <= 120
        lblAbout1.Left = lblAbout1.Left + 50
        WaitForEventsToFinish 1
    Wend

    While lblAbout2.Left > 120
        lblAbout2.Left = lblAbout2.Left - 50
        WaitForEventsToFinish 1
    Wend

    While lblAbout3.Left <= 120
        lblAbout3.Left = lblAbout3.Left + 50
        WaitForEventsToFinish 1
    Wend
End Sub

Private Sub BTN_OK_KeyPress(KeyAscii As Integer)
    ' Appuyer sur une touche du clavier a le même effet que cliquer sur le bouton OK.
    BTN_OK_Click
End Sub

Private Sub Form_Load()
    ' Force les étiquettes à s'afficher en dehors du contrôle PictureBox.
    lblAbout1.Left = -2500
    lblAbout2.Left = 4000
    lblAbout3.Left = -2500
End Sub

