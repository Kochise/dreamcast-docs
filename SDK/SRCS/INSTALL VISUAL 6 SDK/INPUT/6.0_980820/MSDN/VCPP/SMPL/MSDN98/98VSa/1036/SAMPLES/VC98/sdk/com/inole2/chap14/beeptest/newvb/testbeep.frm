VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "Beeper Test"
   ClientHeight    =   1725
   ClientLeft      =   1275
   ClientTop       =   1860
   ClientWidth     =   3375
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   1
      weight          =   700
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   Height          =   2100
   Left            =   1230
   LinkTopic       =   "Form1"
   ScaleHeight     =   1725
   ScaleWidth      =   3375
   Top             =   1530
   Width           =   3465
   Begin VB.CommandButton GermanNames 
      Caption         =   "&German Names"
      Height          =   615
      Left            =   1800
      TabIndex        =   3
      Top             =   960
      Width           =   1455
   End
   Begin VB.CommandButton BogusName 
      Caption         =   "Bogus &Name"
      Height          =   615
      Left            =   1800
      TabIndex        =   2
      Top             =   120
      Width           =   1455
   End
   Begin VB.CommandButton Exception 
      Caption         =   "E&xception"
      Height          =   615
      Left            =   120
      TabIndex        =   1
      Top             =   960
      Width           =   1455
   End
   Begin VB.CommandButton TestBeeps 
      Caption         =   "Test &Beeps"
      Height          =   615
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1455
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False

Private Sub BogusName_Click()
    Dim Beeper As Object
    Set Beeper = CreateObject("Beeper.Object")

    Beeper.Foo = 5  'Invalid property
    
    Set Beeper = Nothing
End Sub

Private Sub Exception_Click()
    Dim Beeper As Object
    Set Beeper = CreateObject("Beeper.Object")

    Beeper.Sound = 555  'Generate an exception
    
    Set Beeper = Nothing
End Sub

Private Sub GermanNames_Click()
    Dim PlayedSound As Integer
    Dim Pieper As Object
    Set Pieper = CreateObject("Beeper.Object")

    Pieper.Ton = 0
    Pieper.Piep

    Pieper.Ton = 16   'MB_ICONHAND
    Ton = Pieper.Piep

    Pieper.Ton = 32   'MB_ICONEXCLAMATION
    Ton = Pieper.Piep

    Pieper.Ton = 48   'MB_ICONQUESTION
    Ton = Pieper.Piep

    Pieper.Ton = 64   'MB_ICONASTERISK
    Ton = Pieper.Piep

    Set Pieper = Nothing
End Sub

Private Sub TestBeeps_Click()
    Dim PlayedSound As Integer
    Dim Beeper As Object
    Set Beeper = CreateObject("Beeper.Object")

    Beeper.Sound = 0
    Beeper.Beep

    Beeper.Sound = 16   'MB_ICONHAND
    Sound = Beeper.Beep

    Beeper.Sound = 32   'MB_ICONEXCLAMATION
    Sound = Beeper.Beep

    Beeper.Sound = 48   'MB_ICONQUESTION
    Sound = Beeper.Beep

    Beeper.Sound = 64   'MB_ICONASTERISK
    Sound = Beeper.Beep

    Set Beeper = Nothing
End Sub

