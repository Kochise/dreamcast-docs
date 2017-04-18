VERSION 5.00
Begin VB.Form Strings 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Chaînes & fichiers"
   ClientHeight    =   4590
   ClientLeft      =   1575
   ClientTop       =   2100
   ClientWidth     =   7515
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
   ScaleHeight     =   4590
   ScaleWidth      =   7515
   ShowInTaskbar   =   0   'False
   Tag             =   "Real"
   Begin VB.CommandButton cmdString 
      Caption         =   "Construit une boucle externe"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   450
      Index           =   1
      Left            =   120
      TabIndex        =   1
      Top             =   1320
      Width           =   2265
   End
   Begin VB.TextBox txtCount2 
      Height          =   280
      Left            =   6060
      TabIndex        =   5
      Text            =   "1000"
      Top             =   2520
      Width           =   1400
   End
   Begin VB.CommandButton cmdFiles 
      Caption         =   "Binaire"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   450
      Index           =   1
      Left            =   120
      TabIndex        =   3
      Top             =   3840
      Width           =   2265
   End
   Begin VB.CommandButton cmdFiles 
      Caption         =   "Aléatoire"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   450
      Index           =   0
      Left            =   120
      TabIndex        =   2
      Top             =   3120
      Width           =   2265
   End
   Begin VB.CommandButton cmdString 
      Caption         =   "Construit une boucle interne"
      Default         =   -1  'True
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   450
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   660
      Width           =   2265
   End
   Begin VB.TextBox txtCounter 
      Height          =   280
      Left            =   6060
      TabIndex        =   4
      Text            =   "txtCounter"
      Top             =   120
      Width           =   1400
   End
   Begin VB.Label lblFiles 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "0,00 sec."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   285
      Index           =   1
      Left            =   6060
      TabIndex        =   8
      Top             =   3840
      Width           =   1395
   End
   Begin VB.Label lblFiles 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "0,00 sec."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   285
      Index           =   0
      Left            =   6060
      TabIndex        =   10
      Top             =   3120
      Width           =   1395
   End
   Begin VB.Label Label2 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "Lit && écrit des enregistrements en utilisant une E/S binaire."
      ForeColor       =   &H80000008&
      Height          =   450
      Left            =   2505
      TabIndex        =   13
      Top             =   3840
      Width           =   3105
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "Lit && écrit des enregistrements en utilisant un accès aléatoire."
      ForeColor       =   &H80000008&
      Height          =   450
      Index           =   4
      Left            =   2505
      TabIndex        =   15
      Top             =   3120
      Width           =   3105
   End
   Begin VB.Label lblTitle 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "Fichier E/S"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   300
      Index           =   2
      Left            =   120
      TabIndex        =   14
      Top             =   2400
      Width           =   1875
   End
   Begin VB.Line Line2 
      BorderColor     =   &H00808080&
      X1              =   120
      X2              =   7455
      Y1              =   2100
      Y2              =   2100
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "Copie les chaînes dans une variable temporaire, puis copie les données temporaires dans une nouvelle variable."
      ForeColor       =   &H80000008&
      Height          =   570
      Index           =   3
      Left            =   2505
      TabIndex        =   12
      Top             =   1320
      Width           =   3585
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "Copie des chaînes de façon explicite vers une nouvelle variable."
      ForeColor       =   &H80000008&
      Height          =   450
      Index           =   2
      Left            =   2505
      TabIndex        =   11
      Top             =   660
      Width           =   3105
   End
   Begin VB.Label lblString 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "0,00 sec."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   285
      Index           =   0
      Left            =   6060
      TabIndex        =   9
      Top             =   660
      Width           =   1395
   End
   Begin VB.Label lblString 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "0,00 sec."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   285
      Index           =   1
      Left            =   6060
      TabIndex        =   7
      Top             =   1320
      Width           =   1395
   End
   Begin VB.Label lblTitle 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "Chaînes"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   300
      Index           =   1
      Left            =   120
      TabIndex        =   6
      Top             =   60
      Width           =   1875
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00FFFFFF&
      BorderWidth     =   2
      Index           =   0
      X1              =   120
      X2              =   7455
      Y1              =   2115
      Y2              =   2115
   End
End
Attribute VB_Name = "Strings"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub cmdFiles_Click(Index As Integer)
' Utilise un fichier E/S binaire au lieu d'un fichier aléatoire.
    On Error Resume Next
    Dim allrecs() As BookAuthor
    ReDim allrecs(txtCount2)
    Me.MousePointer = 11
    For x = 1 To txtCount2
        allrecs(x).ID = x
        allrecs(x).Name = "Jacques Durand - Une personne quelconque"
    Next x
    Kill App.Path & "\" & "files.out"
    If Index = 0 Then
        Open App.Path & "\" & "files.out" For Random As #1
    Else
        Open App.Path & "\" & "files.out" For Binary As #1
    End If
    start# = Timer
    For x = 1 To txtCount2
       Put #1, , allrecs(x)
    Next x
    Seek #1, 1
    For x = 1 To txtCount2
        Get #1, , allrecs(x)
    Next x
    Finish# = Timer
    lblFiles(Index) = Format(Finish# - start#, "##.##") & " sec."
    Close #1
    Me.MousePointer = 0
End Sub

Private Sub cmdString_Click(Index As Integer)
    strfirst$ = "Chaîne très longue. "
    strsecond$ = "Autre chaîne très longue. "
    strthird$ = "Décidément, elle est vraiment très longue!"
    MousePointer = 11
    If Index = 0 Then
        start# = Timer
        For x = 1 To txtCounter
            result$ = strfirst$ & strsecond$ & strthird$
        Next x
        Finish# = Timer
    Else
        Temp$ = strfirst$ & strsecond$ & strthird$
        start# = Timer
        For x = 1 To txtCounter
            result$ = Temp$
        Next x
        Finish# = Timer
    End If
    lblString(Index) = Format$(Finish# - start#, "##.##") & " sec."
    MousePointer = 0
End Sub

Private Sub Form_Load()

  PosForm Me

  txtCounter = 10000
  txtCount2 = 1000

End Sub

