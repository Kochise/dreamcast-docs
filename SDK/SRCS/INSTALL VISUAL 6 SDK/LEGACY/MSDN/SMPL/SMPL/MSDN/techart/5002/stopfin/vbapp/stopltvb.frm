VERSION 4.00
Begin VB.Form StopLiteTest 
   Caption         =   "StopLite Visual Basic Test App"
   ClientHeight    =   4245
   ClientLeft      =   1830
   ClientTop       =   2385
   ClientWidth     =   5490
   Height          =   4650
   Icon            =   "StopLtVB.frx":0000
   Left            =   1770
   LinkTopic       =   "StopLiteTest"
   ScaleHeight     =   4245
   ScaleWidth      =   5490
   Top             =   2040
   Width           =   5610
   Begin VB.CommandButton Next 
      Caption         =   "Next light"
      Height          =   735
      Left            =   1320
      TabIndex        =   10
      Top             =   960
      Width           =   1095
   End
   Begin VB.CommandButton Off 
      Caption         =   "Off"
      Height          =   375
      Left            =   4200
      TabIndex        =   7
      Top             =   1080
      Width           =   975
   End
   Begin VB.CommandButton TestAll 
      Caption         =   "Test All"
      Height          =   375
      Left            =   4200
      TabIndex        =   6
      Top             =   480
      Width           =   975
   End
   Begin VB.CommandButton Exit 
      Caption         =   "Exit"
      Height          =   375
      Left            =   4200
      TabIndex        =   5
      Top             =   1680
      Width           =   975
   End
   Begin VB.CommandButton Green 
      Caption         =   "Green"
      Height          =   375
      Left            =   2760
      TabIndex        =   4
      Top             =   1680
      Width           =   975
   End
   Begin VB.Frame Frame1 
      Caption         =   "Color"
      Height          =   2175
      Left            =   2640
      TabIndex        =   1
      Top             =   120
      Width           =   1215
      Begin VB.CommandButton Yellow 
         Caption         =   "Yellow"
         Height          =   375
         Left            =   120
         TabIndex        =   3
         Top             =   960
         Width           =   975
      End
      Begin VB.CommandButton Red 
         Caption         =   "Red"
         Height          =   375
         Left            =   120
         TabIndex        =   2
         Top             =   360
         Width           =   975
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Special"
      Height          =   2175
      Left            =   4080
      TabIndex        =   8
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   $"StopLtVB.frx":0442
      Height          =   615
      Left            =   120
      TabIndex        =   11
      Top             =   3480
      Width           =   5175
   End
   Begin VB.Label Status 
      Alignment       =   2  'Center
      Caption         =   "Welcome! Click around!"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   400
         size            =   18
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   120
      TabIndex        =   9
      Top             =   2760
      Width           =   5175
   End
   Begin STOPLITELib.StopLite StopLite1 
      Height          =   1575
      Left            =   120
      TabIndex        =   0
      Top             =   480
      Width           =   1095
      _Version        =   65536
      _ExtentX        =   1931
      _ExtentY        =   2778
      _StockProps     =   9
   End
End
Attribute VB_Name = "StopLiteTest"
Attribute VB_Creatable = False
Attribute VB_Exposed = False

Private Sub Exit_Click()
    End
End Sub

Private Sub Green_Click()
    StopLite1.Color = 2
End Sub

Private Sub Next_Click()
    StopLite1.Next
End Sub

Private Sub Off_Click()
    StopLite1.Color = 0
End Sub

Private Sub Red_Click()
    StopLite1.Color = 1
End Sub


Private Sub StopLite1_Caution()
    Status.Caption = "Caution!"
End Sub

Private Sub StopLite1_Click()
    MsgBox "StopLite clicked--try other button!"
End Sub

Private Sub StopLite1_Go()
    Status.Caption = "Go"
End Sub

Private Sub StopLite1_Off()
    Status.Caption = "Warning! StopLite not working!"
End Sub


Private Sub StopLite1_Stop()
    Status.Caption = "Stop!"
End Sub

Private Sub StopLite1_Testing()
    Status.Caption = "Warning! StopLite being tested!"
End Sub


Private Sub TestAll_Click()
    StopLite1.Color = 4
End Sub

Private Sub Yellow_Click()
    StopLite1.Color = 3
End Sub
