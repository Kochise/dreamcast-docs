VERSION 5.00
Begin VB.Form AlarmForm 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Horloge"
   ClientHeight    =   720
   ClientLeft      =   5010
   ClientTop       =   4245
   ClientWidth     =   2520
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "ALARM.frx":0000
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   720
   ScaleWidth      =   2520
   StartUpPosition =   2  'CenterScreen
   Begin VB.Timer Timer1 
      Interval        =   500
      Left            =   1920
      Top             =   120
   End
   Begin VB.Label lblTime 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1455
   End
End
Attribute VB_Name = "AlarmForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim AlarmTime
Const conMinimized = 1


Private Sub Form_Click()
    AlarmTime = InputBox("Tapez l'heure du réveil", "Alarme VB", AlarmTime)
    If AlarmTime = "" Then Exit Sub
    If Not IsDate(AlarmTime) Then
        MsgBox "L'heure spécifiée n'est pas valable."
    Else                                    ' La chaîne renvoyée par la fonction InputBox est une heure valide.
        AlarmTime = CDate(AlarmTime)        ' Stockée comme valeur date/heure dans la variable AlarmTime.
    End If
End Sub

Private Sub Form_Load()
    AlarmTime = ""
End Sub

Private Sub Form_Resize()
    If WindowState = conMinimized Then      ' Si la feuille est réduite affiche l'heure dans le titre.
        SetCaptionTime
    Else
        Caption = "Horloge"
    End If
End Sub

Private Sub SetCaptionTime()
    Caption = Format(Time, "Medium Time")   ' Affiche l'heure dans le format "medium time".
End Sub

Private Sub Timer1_Timer()
Static AlarmSounded As Integer
    If lblTime.Caption <> CStr(Time) Then
        ' Secondes différentes de celles qui sont affichées.
        If Time >= AlarmTime And Not AlarmSounded Then
            Beep
            MsgBox "Réveil à " & Time
            AlarmSounded = True
        ElseIf Time < AlarmTime Then
            AlarmSounded = False
        End If
        If WindowState = conMinimized Then
            ' Si réduite, mise à jour du titre de la feuille à chaque minute.
            If Minute(CDate(Caption)) <> Minute(Time) Then SetCaptionTime
        Else
            ' Mise à jour de l'étiquette à chaque seconde.
            lblTime.Caption = Time
        End If
    End If
End Sub

