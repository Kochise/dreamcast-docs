VERSION 5.00
Begin VB.Form frmImpTbls 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Importer des tables"
   ClientHeight    =   1560
   ClientLeft      =   2280
   ClientTop       =   3165
   ClientWidth     =   6480
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   HelpContextID   =   2016130
   Icon            =   "IMPTBLS.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form2"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1560
   ScaleWidth      =   6480
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton cmdClose 
      Cancel          =   -1  'True
      Caption         =   "Fermer"
      Height          =   375
      Left            =   4920
      MaskColor       =   &H00000000&
      TabIndex        =   2
      Top             =   1080
      Width           =   1455
   End
   Begin VB.CommandButton cmdImport 
      Caption         =   "Importer"
      Default         =   -1  'True
      Enabled         =   0   'False
      Height          =   375
      Left            =   4920
      MaskColor       =   &H00000000&
      TabIndex        =   1
      Top             =   480
      Width           =   1455
   End
   Begin VB.ListBox lstTables 
      Height          =   450
      Left            =   120
      TabIndex        =   0
      Top             =   480
      Width           =   4695
   End
   Begin VB.Label lblLabel1 
      AutoSize        =   -1  'True
      Caption         =   " Tables dans "
      Height          =   195
      Left            =   120
      TabIndex        =   3
      Top             =   120
      Width           =   720
   End
End
Attribute VB_Name = "frmImpTbls"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "Importer des tables"
Const Label1 = "Tables dans:"
Const BUTTON1 = "&Importer"
Const BUTTON2 = "&Fermer"
'>>>>>>>>>>>>>>>>>>>>>>>>


Private Sub cmdClose_Click()
  Unload Me
End Sub

Private Sub cmdImport_Click()
  Import (lstTables.Text)
End Sub

Private Sub lstTables_Click()
  cmdImport.Enabled = True
End Sub

Private Sub lstTables_DblClick()
  Call cmdImport_Click
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016130
  End If
End Sub

Private Sub Form_Load()

  Dim tdf As TableDef
  Dim i As Integer
  
  Me.Caption = FORMCAPTION
  lblLabel1.Caption = Label1
  cmdImport.Caption = BUTTON1
  cmdClose.Caption = BUTTON2
  
  lstTables.Clear
  For Each tdf In gImpDB.TableDefs
    If (tdf.Attributes And dbSystemObject) = 0 Then
      lstTables.AddItem tdf.Name
    End If
  Next

End Sub
