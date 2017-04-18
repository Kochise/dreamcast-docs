VERSION 5.00
Begin VB.Form frmShow1 
   Caption         =   "Form1"
   ClientHeight    =   1425
   ClientLeft      =   1755
   ClientTop       =   2130
   ClientWidth     =   4485
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
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   1425
   ScaleWidth      =   4485
   Begin VB.TextBox txtFooValue 
      Appearance      =   0  'Flat
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   450
      Left            =   2310
      TabIndex        =   1
      Top             =   420
      Width           =   1215
   End
   Begin VB.CommandButton cmd 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Définit la variable Foo de la feuille"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   645
      Left            =   480
      TabIndex        =   0
      Top             =   315
      Width           =   1455
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "="
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   360
      Left            =   2010
      TabIndex        =   2
      Top             =   435
      Width           =   195
   End
End
Attribute VB_Name = "frmShow1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim iFoo As Integer

Private Sub cmd_Click()
  
  iFoo = Val(txtFooValue)
  frmShow2.lblStatus.Caption = "Form1.CMD définit iFoo = " & Str$(iFoo)

End Sub

Private Sub Form_Load()
  
  Me.Left = frmExplore.Width + 600
  Me.Top = (Screen.Height - Me.Height) * 0.3
  
  txtFooValue = Str$(iFoo)
  frmShow2.lblStatus.Caption = "Form1_Load iFoo = " & Str$(iFoo)

End Sub

