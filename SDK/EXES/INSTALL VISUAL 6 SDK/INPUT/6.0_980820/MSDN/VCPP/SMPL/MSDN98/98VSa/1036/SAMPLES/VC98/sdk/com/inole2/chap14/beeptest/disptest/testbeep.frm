VERSION 2.00
Begin Form Form1 
   Caption         =   "Beeper Test"
   ClientHeight    =   1725
   ClientLeft      =   1275
   ClientTop       =   1860
   ClientWidth     =   3375
   Height          =   2100
   Left            =   1230
   LinkTopic       =   "Form1"
   ScaleHeight     =   1725
   ScaleWidth      =   3375
   Top             =   1530
   Width           =   3465
   Begin CommandButton GermanNames 
      Caption         =   "&German Names"
      Height          =   615
      Left            =   1800
      TabIndex        =   3
      Top             =   960
      Width           =   1455
   End
   Begin CommandButton BogusName 
      Caption         =   "Bogus &Name"
      Height          =   615
      Left            =   1800
      TabIndex        =   2
      Top             =   120
      Width           =   1455
   End
   Begin CommandButton Exception 
      Caption         =   "E&xception"
      Height          =   615
      Left            =   120
      TabIndex        =   1
      Top             =   960
      Width           =   1455
   End
   Begin CommandButton TestBeeps 
      Caption         =   "Test &Beeps"
      Height          =   615
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1455
   End
End

Sub BogusName_Click ()
    Dim Beeper As Object
    Set Beeper = CreateObject("Beeper.Object")

    Beeper.Foo = 5  'Invalid property
    
    Set Beeper = Nothing
End Sub

Sub Exception_Click ()
    Dim Beeper As Object
    Set Beeper = CreateObject("Beeper.Object")

    Beeper.Sound = 555  'Generate an exception
    
    Set Beeper = Nothing
End Sub

Sub GermanNames_Click ()
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

Sub TestBeeps_Click ()
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

