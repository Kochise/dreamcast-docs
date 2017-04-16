VERSION 5.00
Object = "*\ACtlPlus.vbp"
Begin VB.Form Form1 
   AutoRedraw      =   -1  'True
   Caption         =   "Test du contrôle ShapeLabel"
   ClientHeight    =   3195
   ClientLeft      =   5085
   ClientTop       =   2055
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   213
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   312
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   1200
      TabIndex        =   3
      Top             =   1920
      Width           =   3135
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   1200
      TabIndex        =   1
      Top             =   1320
      Width           =   3135
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Cycle"
      Height          =   375
      Left            =   2910
      TabIndex        =   4
      Top             =   2640
      Width           =   1215
   End
   Begin CtlPlus.ShapeLabel ShapeLabel2 
      Height          =   495
      Index           =   0
      Left            =   240
      TabIndex        =   0
      Top             =   1080
      Width           =   1335
      _ExtentX        =   1720
      _ExtentY        =   873
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Alignment       =   0
      BorderWidth     =   6
      Caption         =   "&Prénom"
   End
   Begin CtlPlus.ShapeLabel ShapeLabel1 
      Height          =   855
      Left            =   480
      TabIndex        =   5
      Top             =   120
      Width           =   3735
      _ExtentX        =   6588
      _ExtentY        =   1508
      ForeColor       =   16777215
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      BorderStyle     =   1
      BorderColor     =   16776960
      BorderWidth     =   2
      Caption         =   "Votre message ici"
   End
   Begin CtlPlus.ShapeLabel ShapeLabel2 
      Height          =   495
      Index           =   1
      Left            =   240
      TabIndex        =   2
      Top             =   1680
      Width           =   1335
      _ExtentX        =   1720
      _ExtentY        =   873
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   6
      Caption         =   "&Nom"
   End
   Begin VB.Image Image1 
      Height          =   960
      Left            =   3600
      Picture         =   "TCPForm1.frx":0000
      Top             =   2040
      Width           =   960
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()
    On Error Resume Next
    ShapeLabel1.Alignment = ShapeLabel1.Alignment + 1
    If Err.Number <> 0 Then ShapeLabel1.Alignment = 0
    Err.Number = 0
    ShapeLabel1.BackColor = QBColor(Int(Rnd * 16))
    ShapeLabel1.BorderColor = QBColor(Int(Rnd * 16))
    ShapeLabel1.BorderStyle = ShapeLabel1.BorderStyle + 1
    If Err.Number <> 0 Then ShapeLabel1.BorderStyle = 0
    Err.Number = 0
    ShapeLabel1.BorderWidth = ShapeLabel1.BorderWidth + 1
    If ShapeLabel1.BorderWidth > 7 Then ShapeLabel1.BorderWidth = 1
    ShapeLabel1.ForeColor = QBColor(Int(Rnd * 16))
    ShapeLabel1.Font.Bold = ShapeLabel1.Font.Bold Xor True
    ShapeLabel1.Font.Italic = ShapeLabel1.Font.Italic Xor True
    ShapeLabel1.Font.Size = ShapeLabel1.Font.Size + 1
    If ShapeLabel1.Font.Size > 16 Then ShapeLabel1.Font.Size = 10
    ShapeLabel1.MousePointer = ShapeLabel1.MousePointer + 1
    If Err.Number <> 0 Then ShapeLabel1.MousePointer = 0
    Err.Number = 0
    ShapeLabel1.Shape = ShapeLabel1.Shape + 1
    If Err.Number <> 0 Then ShapeLabel1.Shape = 0
    Err.Number = 0
    If ShapeLabel1.ToolTipText <> "" Then
        ShapeLabel1.ToolTipText = ""
    Else
        ShapeLabel1.ToolTipText = "Ceci est une info-bulle"
    End If
End Sub

Private Sub Form_Load()
    Dim intX As Integer
    Dim intY As Integer
    Dim sngWidth As Single
    Dim sngHeight As Single
    
    sngWidth = Image1.Width
    sngHeight = Image1.Height
    For intX = 0 To Int(ScaleWidth / sngWidth)
        For intY = 0 To Int(ScaleHeight / sngHeight)
            PaintPicture Image1.Picture, intX * sngWidth, intY * sngHeight, sngWidth, sngHeight, 0, 0
        Next
    Next
End Sub

Private Sub Form_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ShapeLabel2(0).BackColor = vbRed
    ShapeLabel2(1).BackColor = vbRed
End Sub

Private Sub ShapeLabel2_MouseMove(Index As Integer, Button As Integer, Shift As Integer, X As Single, Y As Single)
    ShapeLabel2(Index).BackColor = vbGreen
End Sub
