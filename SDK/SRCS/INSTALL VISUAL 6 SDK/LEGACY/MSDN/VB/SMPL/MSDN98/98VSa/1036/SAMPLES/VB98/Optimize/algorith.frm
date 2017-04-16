VERSION 5.00
Begin VB.Form Algorithms 
   Appearance      =   0  'Flat
   AutoRedraw      =   -1  'True
   BackColor       =   &H00FFFFFF&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Algorithmes"
   ClientHeight    =   3810
   ClientLeft      =   2265
   ClientTop       =   1875
   ClientWidth     =   6060
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3810
   ScaleWidth      =   6060
   ShowInTaskbar   =   0   'False
   Tag             =   "Display"
   WhatsThisHelp   =   -1  'True
   Begin VB.Frame Frame1 
      Caption         =   "Redéfinit la vitesse"
      Height          =   1575
      Left            =   195
      TabIndex        =   0
      Top             =   120
      Width           =   5655
      Begin VB.CheckBox Check1 
         Caption         =   "AutoRedraw"
         Height          =   255
         Left            =   240
         TabIndex        =   6
         Top             =   1200
         Value           =   1  'Checked
         Width           =   2175
      End
      Begin VB.OptionButton optLineStyle 
         Caption         =   "Lignes utilisant des variables"
         Height          =   375
         Index           =   1
         Left            =   240
         TabIndex        =   2
         Top             =   720
         Width           =   2895
      End
      Begin VB.OptionButton optLineStyle 
         Caption         =   "Lignes utilisant des propriétés"
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Width           =   2895
      End
      Begin VB.Label Label1 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "Étiquette1"
         ForeColor       =   &H80000008&
         Height          =   255
         Left            =   240
         TabIndex        =   5
         Top             =   1200
         Width           =   1455
      End
      Begin VB.Label lblAlgorithm 
         Caption         =   "0,00 sec."
         Height          =   255
         Index           =   1
         Left            =   4080
         TabIndex        =   4
         Top             =   840
         Width           =   1335
      End
      Begin VB.Label lblAlgorithm 
         AutoSize        =   -1  'True
         Caption         =   "0,00 sec."
         Height          =   195
         Index           =   0
         Left            =   4080
         TabIndex        =   3
         Top             =   360
         Width           =   1215
         WordWrap        =   -1  'True
      End
   End
End
Attribute VB_Name = "Algorithms"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Check1_Click()
    ' Bascule vers la propriété AutoRedraw.
    Cls
    Me.AutoRedraw = Not Me.AutoRedraw
End Sub

Private Sub Form_Load()
  
  PosForm Me
  Label1 = "AutoRedraw = " & Me.AutoRedraw
End Sub

Private Sub optLineStyle_Click(Index As Integer)
    Cls
    If optLineStyle(0) Then
        start = Timer
        For y = 1 To Me.ScaleHeight Step 5
            Line (0, (Me.ScaleHeight - y))-(Me.ScaleWidth, (Me.ScaleHeight - y))
        Next y
        Finish = Timer
        lblAlgorithm(0) = Format$(Finish - start, "##.##") & " sec."
    Else
        frmWidth = Me.ScaleWidth
        frmHeight = Me.ScaleHeight
        start = Timer
        For y = 1 To frmHeight Step 5
            x = frmHeight - y
            Line (0, x)-(frmWidth, x)
        Next y
        Finish = Timer
        lblAlgorithm(1) = Format$(Finish - start, "##.##") & " sec."
    End If
End Sub

