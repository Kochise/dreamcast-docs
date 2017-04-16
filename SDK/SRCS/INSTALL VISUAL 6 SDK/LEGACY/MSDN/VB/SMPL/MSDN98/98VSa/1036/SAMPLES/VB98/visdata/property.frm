VERSION 5.00
Begin VB.Form frmProperty 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Valeurs de propriétés"
   ClientHeight    =   1215
   ClientLeft      =   2655
   ClientTop       =   3135
   ClientWidth     =   5400
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1215
   ScaleWidth      =   5400
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.TextBox txtPropValue 
      Height          =   300
      Left            =   135
      TabIndex        =   1
      Top             =   315
      Width           =   5070
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Annuler"
      Height          =   360
      Left            =   3735
      TabIndex        =   3
      Top             =   720
      Width           =   1335
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Default         =   -1  'True
      Height          =   360
      Left            =   2190
      TabIndex        =   2
      Top             =   720
      Width           =   1335
   End
   Begin VB.CheckBox chkPropValue 
      Caption         =   "Check1"
      Height          =   300
      Left            =   135
      TabIndex        =   4
      Top             =   315
      Width           =   5070
   End
   Begin VB.Label lblLabel 
      Caption         =   "&Entrez la valeur de propriétés:"
      Height          =   225
      Left            =   135
      TabIndex        =   0
      Top             =   60
      Width           =   4365
   End
End
Attribute VB_Name = "frmProperty"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = " Valeur de propriété"
Const BUTTON1 = "&OK"
Const BUTTON2 = "&Annuler"
Const Label1 = "&Entrez la valeur de propriété:"
'>>>>>>>>>>>>>>>>>>>>>>>>

Public PropObject As DAO.Property
Public OK As Boolean

Private Sub cmdCancel_Click()
  OK = False
  Me.Hide
End Sub

Private Sub cmdOK_Click()
  On Error GoTo cmdOK_ClickErr
  
  ' Fait une tentative pour le définir
  If PropObject.Type = dbBoolean Then
    PropObject.Value = (chkPropValue.Value = vbChecked)
  Else
    If txtPropValue.Text <> PropObject.Value Then
      ' Réinitialisation en cas de modification
      PropObject.Value = txtPropValue.Text
    End If
  End If
  
  OK = True
  Me.Hide
  
  Exit Sub
  
cmdOK_ClickErr:
  MsgBox Err.Description
  If PropObject.Type = dbBoolean Then
    chkPropValue.SetFocus
  Else
    txtPropValue.SetFocus
  End If
End Sub

Private Sub Form_Load()
  Me.Caption = PropObject.Name & FORMCAPTION
  cmdOK.Caption = BUTTON1
  cmdCancel.Caption = BUTTON2
  lblLabel.Caption = Label1
  
  ' Initialise les contrôles pour le type de propriété
  If PropObject.Type = dbBoolean Then
    txtPropValue.Visible = False
    chkPropValue.TabIndex = 1
    chkPropValue.Caption = PropObject.Name
    chkPropValue.Value = (PropObject.Value And vbChecked)
  Else
    txtPropValue.Text = PropObject.Value
  End If
  
End Sub
