VERSION 5.00
Begin VB.Form frmNumbers 
   Caption         =   "Types de données numériques"
   ClientHeight    =   5220
   ClientLeft      =   1125
   ClientTop       =   1575
   ClientWidth     =   5580
   ClipControls    =   0   'False
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5220
   ScaleWidth      =   5580
   Begin VB.CommandButton cmdType 
      Caption         =   "Double"
      Height          =   450
      Index           =   5
      Left            =   135
      TabIndex        =   7
      Top             =   4680
      Width           =   2895
   End
   Begin VB.CommandButton cmdType 
      Caption         =   "Currency"
      Height          =   450
      Index           =   4
      Left            =   135
      TabIndex        =   6
      Top             =   4185
      Width           =   2895
   End
   Begin VB.TextBox txtLoopCount 
      Height          =   320
      Index           =   2
      Left            =   4200
      TabIndex        =   8
      Text            =   "200"
      Top             =   3765
      Width           =   1300
   End
   Begin VB.CommandButton cmdType 
      Caption         =   "Compteur de données de type Long"
      Height          =   450
      Index           =   3
      Left            =   135
      TabIndex        =   4
      Top             =   2910
      Width           =   2895
   End
   Begin VB.CommandButton cmdType 
      Caption         =   "Compteur de données de type Variant"
      Height          =   450
      Index           =   2
      Left            =   135
      TabIndex        =   3
      Top             =   2415
      Width           =   2895
   End
   Begin VB.TextBox txtLoopCount 
      Height          =   320
      Index           =   1
      Left            =   4200
      TabIndex        =   5
      Text            =   "200"
      Top             =   1995
      Width           =   1300
   End
   Begin VB.CommandButton cmdType 
      Caption         =   "Compteur de données de type Integer"
      Height          =   450
      HelpContextID   =   1
      Index           =   1
      Left            =   120
      TabIndex        =   1
      Top             =   975
      Width           =   2895
   End
   Begin VB.CommandButton cmdType 
      Caption         =   "Compteur de données de type Long"
      Height          =   450
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   480
      Width           =   2895
   End
   Begin VB.TextBox txtLoopCount 
      Height          =   320
      Index           =   0
      Left            =   4200
      TabIndex        =   2
      Text            =   "200"
      Top             =   60
      Width           =   1300
   End
   Begin VB.Label lblResult 
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
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   5
      Left            =   4200
      TabIndex        =   17
      Top             =   4785
      Width           =   1800
   End
   Begin VB.Label lblResult 
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
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   4
      Left            =   4200
      TabIndex        =   16
      Top             =   4290
      Width           =   1800
   End
   Begin VB.Label lblTitle 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFFF&
      BackStyle       =   0  'Transparent
      Caption         =   "Variables Double et Currency"
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
      Left            =   135
      TabIndex        =   15
      Top             =   3750
      Width           =   3525
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00808080&
      Index           =   0
      X1              =   0
      X2              =   7335
      Y1              =   3465
      Y2              =   3465
   End
   Begin VB.Label lblResult 
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
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   3
      Left            =   4200
      TabIndex        =   14
      Top             =   3015
      Width           =   1800
   End
   Begin VB.Label lblResult 
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
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   2
      Left            =   4200
      TabIndex        =   13
      Top             =   2520
      Width           =   1800
   End
   Begin VB.Label lblTitle 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFFF&
      BackStyle       =   0  'Transparent
      Caption         =   "Variables Long et Variant"
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
      Left            =   135
      TabIndex        =   12
      Top             =   1980
      Width           =   3075
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00808080&
      Index           =   3
      X1              =   0
      X2              =   7335
      Y1              =   1680
      Y2              =   1680
   End
   Begin VB.Label lblResult 
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
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   1
      Left            =   4200
      TabIndex        =   11
      Top             =   1080
      Width           =   1800
   End
   Begin VB.Label lblResult 
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
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   0
      Left            =   4200
      TabIndex        =   10
      Top             =   585
      Width           =   1800
   End
   Begin VB.Label lblTitle 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFFF&
      BackStyle       =   0  'Transparent
      Caption         =   "Variables Integer et Long"
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
      Index           =   0
      Left            =   120
      TabIndex        =   9
      Top             =   45
      Width           =   3075
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00FFFFFF&
      BorderWidth     =   2
      Index           =   2
      X1              =   15
      X2              =   7350
      Y1              =   1695
      Y2              =   1680
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00FFFFFF&
      BorderWidth     =   2
      Index           =   1
      X1              =   15
      X2              =   7350
      Y1              =   3480
      Y2              =   3465
   End
End
Attribute VB_Name = "frmNumbers"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdVariant_Click(Index As Integer)

End Sub


Private Sub lblInteger_Click(Index As Integer)

End Sub


Private Sub cmdType_Click(Index As Integer)
  Dim vCounter1 As Variant, vCounter2 As Variant, vCounter3 As Variant, vResult As Variant
  Dim lCounter1 As Long, lCounter2 As Long, lCounter3 As Long, lResult As Long
  Dim iCounter1 As Integer, iCounter2 As Integer, iCounter3 As Integer, iResult As Integer
  Dim dCounter1 As Double, dCounter2 As Double, dCounter3 As Double, dResult As Double
  Dim cCounter1 As Currency, cCounter2 As Currency, cCounter3 As Currency, cResult As Currency
  
  Dim start As Double, Finish As Double
  
  On Error GoTo cmd_Error
  
  Screen.MousePointer = vbHourglass
  lblResult(Index).Caption = "0,00 sec."
  lblResult(Index).Refresh
  
  Select Case Index
    Case 0 ' Compteur de données de type Long.
      start = Timer
      For lCounter1 = 1 To txtLoopCount(0).Text
          For lCounter2 = 1 To lCounter1
              For lCounter3 = 1 To lCounter2
                  lResult = lCounter3 * 100 + lCounter2 * 10 + lCounter1
              Next lCounter3
          Next lCounter2
      Next lCounter1
      Finish = Timer

    Case 1  ' Compteur de données de type Integer.
      start = Timer
      For iCounter1 = 1 To txtLoopCount(0).Text
          For iCounter2 = 1 To iCounter1
              For iCounter3 = 1 To iCounter2
                  iResult = iCounter3 * 100 + iCounter2 * 10 + iCounter1
              Next iCounter3
          Next iCounter2
      Next iCounter1
      Finish = Timer
    
    Case 2  ' Compteur de données de type Variant.
      start = Timer
      For vCounter1 = 1 To txtLoopCount(1).Text
          For vCounter2 = 1 To vCounter1
              For vCounter3 = 1 To vCounter2
                  vResult = vCounter3 * 100 + vCounter2 * 10 + vCounter1
              Next vCounter3
          Next vCounter2
      Next vCounter1
      Finish = Timer
    
    Case 3  ' Compteur de données de type Long.
      start = Timer
      For lCounter1 = 1 To txtLoopCount(1).Text
          For lCounter2 = 1 To lCounter1
              For lCounter3 = 1 To lCounter2
                  lResult = lCounter3 * 100 + lCounter2 * 10 + lCounter1
              Next lCounter3
          Next lCounter2
      Next lCounter1
      Finish = Timer
    
    Case 4  ' Currency.
      start = Timer
      For cCounter1 = 1 To txtLoopCount(2).Text
          For cCounter2 = 1 To cCounter1
              For cCounter3 = 1 To cCounter2
                  cResult = (cCounter3 * 9.0123456789) + (cCounter2 * 0.001) + (cCounter1 / 0.125) - (cCounter2 * 0.001)
              Next cCounter3
          Next cCounter2
      Next cCounter1
      Finish = Timer
    
    
    Case 5  ' Double.
      start = Timer
      For dCounter1 = 1 To txtLoopCount(2).Text
          For dCounter2 = 1 To dCounter1
              For dCounter3 = 1 To dCounter2
                  ' dResult = dCounter3 * 9.0123456789 + dCounter2 * 0.001 + dCounter1 / 0.125
                  cResult = (dCounter3 * 9.0123456789) + (dCounter2 * 0.001) + (dCounter1 / 0.125) - (dCounter2 * 0.001)
              Next dCounter3
          Next dCounter2
      Next dCounter1
      Finish = Timer
    
  End Select
  
  lblResult(Index).Caption = Format$(Finish - start, "00.00") & " sec."
  Screen.MousePointer = vbDefault
  Exit Sub

cmd_Error:
  Screen.MousePointer = vbDefault
  MsgBox "Erreur " & Str$(Err) & ".  " & Error$ & vbCrLf & "Nous allons sortir de cette procédure.", vbExclamation, "Erreur de type de données numérique"
  Exit Sub
  
End Sub


Private Sub Form_Load()
  PosForm Me
End Sub


