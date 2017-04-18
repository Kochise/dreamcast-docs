VERSION 5.00
Object = "*\A..\src\concon.vbp"
Begin VB.Form FormEx 
   Caption         =   "Form1"
   ClientHeight    =   3435
   ClientLeft      =   60
   ClientTop       =   300
   ClientWidth     =   10215
   LinkTopic       =   "Form1"
   ScaleHeight     =   3435
   ScaleWidth      =   10215
   StartUpPosition =   3  'Windows Default
   Begin ConCon.BankEx BankEx1 
      Height          =   3150
      Left            =   105
      TabIndex        =   7
      Top             =   180
      Width           =   6645
      _ExtentX        =   11721
      _ExtentY        =   5556
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      DataSource      =   "\\rainmaker\d$\banking.mdb"
   End
   Begin VB.CommandButton btAcctDelete 
      Caption         =   "Acct Delete"
      Height          =   345
      Left            =   8790
      TabIndex        =   6
      Top             =   2535
      Width           =   1350
   End
   Begin VB.CommandButton btAcctSave 
      Caption         =   "Acct Save"
      Height          =   345
      Left            =   8790
      TabIndex        =   5
      Top             =   2076
      Width           =   1350
   End
   Begin VB.CommandButton btBankDelete 
      Caption         =   "Bank Delete"
      Height          =   345
      Left            =   8790
      TabIndex        =   4
      Top             =   1617
      Width           =   1350
   End
   Begin VB.CommandButton btBankSave 
      Caption         =   "Bank Save"
      Height          =   345
      Left            =   8790
      TabIndex        =   3
      Top             =   1158
      Width           =   1350
   End
   Begin VB.CommandButton btStyle 
      Caption         =   "Style"
      Height          =   345
      Left            =   8790
      TabIndex        =   2
      Top             =   240
      Width           =   1350
   End
   Begin VB.CommandButton btMovement 
      Caption         =   "Yes Move"
      Height          =   345
      Left            =   8790
      TabIndex        =   1
      Top             =   699
      Width           =   1350
   End
   Begin VB.ListBox lstOut 
      Height          =   2985
      Left            =   6825
      TabIndex        =   0
      Top             =   195
      Width           =   1725
   End
End
Attribute VB_Name = "FormEx"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private m_bDoCancel As Boolean

Private Sub BankEx1_OnMoveEnter(bCancel As Boolean)
bCancel = m_bDoCancel
lstOut.AddItem "OnMoveEnter"
End Sub

Private Sub BankEx1_OnMoveExit()
lstOut.AddItem "OnMoveExit"
End Sub

Private Sub btAcctDelete_Click()
If BankEx1.DeleteAccount() Then
    lstOut.AddItem "Account Deleted"
Else
    lstOut.AddItem "Account Not Deleted"
End If
End Sub

Private Sub btAcctSave_Click()
If BankEx1.UpdateAccount() Then
    lstOut.AddItem "Account Updated"
Else
    lstOut.AddItem "Account Not Updated"
End If
End Sub

Private Sub btBankDelete_Click()
If BankEx1.DeleteBank() Then
    lstOut.AddItem "Bank Deleted"
Else
    lstOut.AddItem "Bank Not Deleted"
End If
End Sub

Private Sub btBankSave_Click()
If BankEx1.UpdateBank() Then
    lstOut.AddItem "Bank Updated"
Else
    lstOut.AddItem "Bank Not Updated"
End If
End Sub

Private Sub btMovement_Click()
If btMovement.Caption = "Yes Move" Then
    m_bDoCancel = True
    btMovement.Caption = "No Move"
Else
    m_bDoCancel = False
    btMovement.Caption = "Yes Move"
End If
End Sub

Private Sub btStyle_Click()
If BankEx1.Style = [Code Navigate] Then
    BankEx1.Style = [User Navigate]
Else
    BankEx1.Style = [Code Navigate]
End If
End Sub

Private Sub Form_Load()
If Not BankEx1.Init() Then MsgBox "Didn't Work"
End Sub
