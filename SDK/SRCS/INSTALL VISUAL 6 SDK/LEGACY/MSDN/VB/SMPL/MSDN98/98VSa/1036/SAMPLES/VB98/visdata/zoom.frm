VERSION 5.00
Begin VB.Form frmZoom 
   Caption         =   "Zoom"
   ClientHeight    =   1455
   ClientLeft      =   3600
   ClientTop       =   3930
   ClientWidth     =   6975
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   HelpContextID   =   2016148
   Icon            =   "ZOOM.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   ScaleHeight     =   1455
   ScaleWidth      =   6975
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Fermer"
      Height          =   300
      Left            =   4620
      MaskColor       =   &H00000000&
      TabIndex        =   4
      Top             =   105
      Visible         =   0   'False
      Width           =   2250
   End
   Begin VB.TextBox txtZoomData 
      Height          =   285
      Left            =   0
      TabIndex        =   0
      Top             =   360
      Width           =   4245
   End
   Begin VB.CommandButton cmdSave 
      Caption         =   "&Enregistrer les changements"
      Height          =   300
      Left            =   4620
      MaskColor       =   &H00000000&
      TabIndex        =   2
      Top             =   525
      Visible         =   0   'False
      Width           =   2250
   End
   Begin VB.CommandButton cmdCloseNoSave 
      Cancel          =   -1  'True
      Caption         =   "Fermer &sans enregistrer"
      Height          =   300
      Left            =   4620
      MaskColor       =   &H00000000&
      TabIndex        =   3
      Top             =   40
      Visible         =   0   'False
      Width           =   1932
   End
   Begin VB.TextBox txtMemo 
      Height          =   1332
      Left            =   48
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   1
      Top             =   360
      Visible         =   0   'False
      Width           =   4452
   End
End
Attribute VB_Name = "frmZoom"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const BUTTON1 = "&Fermer"
Const BUTTON2 = "&Enregistrer les changements"
Const BUTTON3 = "Fermer &sans enregistrer"
'>>>>>>>>>>>>>>>>>>>>>>>>


Private Sub txtZoomData_KeyPress(KeyAscii As Integer)
  ' Se débarrasse de la touche si l'enregistrement n'est pas autorisé.
  If cmdSave.Visible = False Then KeyAscii = 0
End Sub

Private Sub cmdCloseNoSave_Click()
  gsZoomData = "__CANCELLED__"
  Unload Me
End Sub

Private Sub cmdClose_Click()
  Call cmdCloseNoSave_Click
  Unload Me
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016148
  End If
End Sub

Private Sub Form_KeyPress(KeyAscii As Integer)
  ' Vérifie la touche Échap.
  If KeyAscii = vbKeyEscape Then
    Call cmdCloseNoSave_Click
    Exit Sub
  End If
End Sub

Private Sub Form_Load()
  cmdClose.Caption = BUTTON1
  cmdSave.Caption = BUTTON2
  cmdCloseNoSave.Caption = BUTTON3
  
  Me.Width = 4600
  SendKeys "{End}"
End Sub

Private Sub Form_Resize()
  On Error Resume Next

  If txtZoomData.Visible Then
    txtZoomData.Width = Me.Width - 200
  Else
    txtMemo.Width = Me.Width - 200
    txtMemo.Height = Me.Height - 850
  End If
End Sub

Private Sub cmdSave_Click()
  If txtZoomData.Visible Then
    gsZoomData = txtZoomData.Text
  Else
    gsZoomData = txtMemo.Text
  End If
  Unload Me
End Sub
