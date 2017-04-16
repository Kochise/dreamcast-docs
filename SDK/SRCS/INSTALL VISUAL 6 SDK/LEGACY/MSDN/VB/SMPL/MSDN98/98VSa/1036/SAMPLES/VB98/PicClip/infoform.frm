VERSION 5.00
Begin VB.Form infoform 
   Caption         =   "Information"
   ClientHeight    =   2160
   ClientLeft      =   1140
   ClientTop       =   1545
   ClientWidth     =   5475
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "infoform.frx":0000
   LinkMode        =   1  'Source
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   ScaleHeight     =   2160
   ScaleMode       =   0  'User
   ScaleWidth      =   5475
   Begin VB.PictureBox btrfly2 
      AutoSize        =   -1  'True
      Height          =   1215
      Left            =   75
      Picture         =   "infoform.frx":030A
      ScaleHeight     =   1185.8
      ScaleMode       =   0  'User
      ScaleWidth      =   1185.8
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   2865
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.Timer Timer2 
      Interval        =   200
      Left            =   4965
      Top             =   1680
   End
   Begin VB.PictureBox btrfly1 
      AutoSize        =   -1  'True
      Height          =   1215
      Left            =   90
      Picture         =   "infoform.frx":0F94
      ScaleHeight     =   1185.8
      ScaleMode       =   0  'User
      ScaleWidth      =   1185.8
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   1635
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Okay 
      Cancel          =   -1  'True
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   405
      Left            =   2760
      TabIndex        =   0
      Top             =   1500
      Width           =   1110
   End
   Begin VB.PictureBox btrfly 
      AutoSize        =   -1  'True
      BorderStyle     =   0  'None
      Height          =   1155
      Left            =   240
      Picture         =   "infoform.frx":1C1E
      ScaleHeight     =   1155
      ScaleMode       =   0  'User
      ScaleWidth      =   1155
      TabIndex        =   3
      TabStop         =   0   'False
      Top             =   240
      Width           =   1155
   End
   Begin VB.Label Label1 
      Caption         =   $"infoform.frx":28A8
      Height          =   1185
      Left            =   1680
      TabIndex        =   4
      Top             =   270
      Width           =   3360
   End
End
Attribute VB_Name = "infoform"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim flap As Integer

Private Sub butterfly()
    ' Alternance entre les deux images bitmap.
    If flap = 0 Then
        btrfly.Picture = btrfly1.Picture
        flap = 1
    Else
        btrfly.Picture = btrfly2.Picture
        flap = 0
    End If
End Sub

Private Sub Form_Load()
    infoform.Left = Form1.Left + 150
    infoform.Top = Form1.Top + 400
End Sub

Private Sub Okay_Click()
    Unload infoform
End Sub

Private Sub Timer2_Timer()
    ' Note: la propriété Interval de la minuterie détermine
    ' la vitesse de battement des ailes du papillon.
    butterfly
End Sub

