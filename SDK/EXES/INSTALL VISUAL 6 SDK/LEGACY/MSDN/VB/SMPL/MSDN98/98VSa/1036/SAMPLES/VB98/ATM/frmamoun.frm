VERSION 5.00
Begin VB.Form frmAmountWithdrawn 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   3045
   ClientLeft      =   5250
   ClientTop       =   3585
   ClientWidth     =   4170
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3045
   ScaleWidth      =   4170
   Begin VB.Frame fraMoney 
      Caption         =   "fraMoney"
      Height          =   1215
      Left            =   120
      TabIndex        =   2
      Top             =   1080
      Width           =   3855
      Begin VB.TextBox txtConvertedAmt 
         Height          =   285
         Left            =   2040
         TabIndex        =   4
         Top             =   600
         Width           =   1575
      End
      Begin VB.TextBox txtUSDollarsAmt 
         Height          =   285
         Left            =   240
         TabIndex        =   3
         TabStop         =   0   'False
         Top             =   600
         Width           =   1575
      End
      Begin VB.Label lblCurrency 
         Caption         =   "lblCurrency"
         Height          =   195
         Left            =   2040
         TabIndex        =   6
         Top             =   360
         Width           =   1575
      End
      Begin VB.Label lblUSDollars 
         Caption         =   "Dollars US"
         Height          =   195
         Left            =   240
         TabIndex        =   5
         Top             =   360
         Width           =   1575
      End
   End
   Begin VB.CommandButton cmdOKEnd 
      Caption         =   "cmdOKEnd"
      Default         =   -1  'True
      Height          =   375
      Left            =   2880
      TabIndex        =   1
      Top             =   2520
      Width           =   1095
   End
   Begin VB.Image imgFlag 
      BorderStyle     =   1  'Fixed Single
      Height          =   735
      Left            =   120
      Stretch         =   -1  'True
      Top             =   120
      Width           =   735
   End
   Begin VB.Label lblAmountWith 
      Caption         =   "lblAmountWith"
      Height          =   735
      Left            =   1080
      TabIndex        =   0
      Top             =   120
      Width           =   2895
   End
End
Attribute VB_Name = "frmAmountWithdrawn"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdOKEnd_Click()
   ' Pour écouter du son, une carte son avec le gestionnaire CODEC Microsoft ADPCM Audio est
   ' nécessaire. Ce gestionnaire est inclus dans Microsoft Windows 95 et Microsoft Windows NT 3.51.
    BeginPlaySound i
    MsgBox LoadResString(8 + i)   ' Affiche un message de remerciement.
    Unload Me
End Sub

Private Sub Form_Load()
    Dim ConversionValue As Currency
    ConversionValue = ConversionTable((i - 16) \ 32)
    imgFlag = LoadResPicture(i, vbResBitmap)
    lblAmountWith = LoadResString(9 + i) & " " & _
        IIf(frmInput.optChecking, LoadResString(3 + i), LoadResString(4 + i))
    lblCurrency = LoadResString(10 + i)
    cmdOKEnd.Caption = LoadResString(6 + i)
    fraMoney = "1 USD ($) = " & CStr(ConversionValue) & " " & lblCurrency.Caption
    txtUSDollarsAmt = Val(frmInput.txtUSDollarsAmt.Text)
    txtConvertedAmt = ConversionValue * CCur(txtUSDollarsAmt.Text)
    SetCursor cmdOKEnd
    
    ' Pour DBCS, le nom de police doit être spécifié par VB au moment
    ' du chargement du projet. Pour que cet exemple fonctionne dans tous
    ' les cas, il est nécessaire de spécifier les propriétés des polices par programme.

    lblAmountWith.FontBold = True
End Sub
