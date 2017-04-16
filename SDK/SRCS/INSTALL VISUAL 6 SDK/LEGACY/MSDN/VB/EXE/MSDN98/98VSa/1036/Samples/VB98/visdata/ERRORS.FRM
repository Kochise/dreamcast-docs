VERSION 5.00
Begin VB.Form frmErrors 
   Caption         =   "Liste des erreurs"
   ClientHeight    =   2640
   ClientLeft      =   3210
   ClientTop       =   2385
   ClientWidth     =   6630
   HelpContextID   =   2016081
   Icon            =   "ERRORS.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MDIChild        =   -1  'True
   ScaleHeight     =   2640
   ScaleWidth      =   6630
   ShowInTaskbar   =   0   'False
   Begin VB.ListBox lstErrors 
      Height          =   2040
      Left            =   105
      TabIndex        =   3
      Top             =   75
      Width           =   6435
   End
   Begin VB.PictureBox picButtons 
      Align           =   2  'Align Bottom
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   400
      Left            =   0
      ScaleHeight     =   405
      ScaleWidth      =   6630
      TabIndex        =   0
      Top             =   2235
      Width           =   6630
      Begin VB.CommandButton cmdClose 
         Cancel          =   -1  'True
         Caption         =   "&Fermer"
         Height          =   330
         Left            =   2040
         MaskColor       =   &H00000000&
         TabIndex        =   2
         Top             =   45
         Width           =   1695
      End
      Begin VB.CommandButton cmdRefresh 
         Caption         =   "&Actualiser"
         Height          =   330
         Left            =   240
         MaskColor       =   &H00000000&
         TabIndex        =   1
         Top             =   40
         Width           =   1695
      End
   End
End
Attribute VB_Name = "frmErrors"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "Liste des erreurs"
Const BUTTON1 = "&Actualiser"
Const BUTTON2 = "&Fermer"
'>>>>>>>>>>>>>>>>>>>>>>>>


Private Sub cmdClose_Click()
  Unload Me
End Sub

Private Sub cmdRefresh_Click()
  RefreshErrors
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016081
  End If
End Sub

Private Sub Form_Load()
  On Error GoTo LErr
  
  Me.Caption = FORMCAPTION
  cmdRefresh.Caption = BUTTON1
  cmdClose.Caption = BUTTON2
  
  Me.Height = 3105
  Me.Width = 6750
  Me.Top = 1000
  Me.Left = 1000
  
  Screen.MousePointer = vbDefault
  Exit Sub
    
LErr:
  ShowError
  Unload Me
End Sub

Private Sub Form_Resize()
  On Error Resume Next
  
  If Me.WindowState = 1 Then Exit Sub
  
  lstErrors.Width = Me.ScaleWidth - (lstErrors.Left * 2)
  lstErrors.Height = Me.Height - 970
End Sub

