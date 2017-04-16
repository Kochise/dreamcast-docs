VERSION 4.00
Begin VB.Form frmMain 
   Caption         =   "Cryptographic Filter Box"
   ClientHeight    =   5670
   ClientLeft      =   2475
   ClientTop       =   2025
   ClientWidth     =   6615
   Height          =   6075
   Left            =   2415
   LinkTopic       =   "Form1"
   ScaleHeight     =   5670
   ScaleWidth      =   6615
   Top             =   1680
   Width           =   6735
   Begin VB.TextBox txtStatus 
      Enabled         =   0   'False
      Height          =   375
      Left            =   240
      ScrollBars      =   3  'Both
      TabIndex        =   10
      Top             =   5160
      Width           =   6135
   End
   Begin VB.TextBox txtPassword 
      Height          =   375
      Left            =   240
      ScrollBars      =   3  'Both
      TabIndex        =   8
      Top             =   3720
      Width           =   6135
   End
   Begin VB.ListBox lstMethod 
      Height          =   645
      Left            =   240
      TabIndex        =   7
      Top             =   4320
      Width           =   2895
   End
   Begin VB.CommandButton cmbGo 
      Caption         =   "&Go"
      Height          =   375
      Left            =   5040
      TabIndex        =   6
      Top             =   4320
      Width           =   1335
   End
   Begin VB.TextBox txtInput 
      Height          =   735
      Left            =   240
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   4
      Top             =   600
      Width           =   6135
   End
   Begin VB.TextBox txtOutput 
      Height          =   735
      Left            =   240
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   2
      Top             =   1680
      Width           =   6135
   End
   Begin VB.TextBox txtSignature 
      Height          =   375
      Left            =   240
      ScrollBars      =   3  'Both
      TabIndex        =   0
      Top             =   2880
      Width           =   6135
   End
   Begin VB.Label Label4 
      Caption         =   "Password"
      Height          =   255
      Left            =   240
      TabIndex        =   9
      Top             =   3480
      Width           =   6135
   End
   Begin VB.Label Label3 
      Caption         =   "Input"
      Height          =   255
      Left            =   240
      TabIndex        =   5
      Top             =   360
      Width           =   6135
   End
   Begin VB.Label Label1 
      Caption         =   "Output"
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   1440
      Width           =   6135
   End
   Begin VB.Label Label2 
      Caption         =   "Signature"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   2640
      Width           =   6135
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Private objCryptoFilterBox As Object

Private Const CFB_BUSY = 0
Private Const CFB_READY = 1
Private Const CFB_VALID = 2


Private Sub cmbGo_Click()
    
    On Error GoTo ErrcmbGo_Click
    
    Select Case lstMethod.Text
        
        Case "Decrypt"
            txtStatus.Text = ""
            objCryptoFilterBox.InBuffer = txtInput.Text
            objCryptoFilterBox.Password = txtPassword.Text
            objCryptoFilterBox.Decrypt
            txtOutput.Text = objCryptoFilterBox.OutBuffer
            Select Case objCryptoFilterBox.Status
                Case CFB_READY
                    txtStatus.Text = "Ready"
                Case Else
                    txtStatus.Text = ""
            End Select
        
        Case "Encrypt"
            txtStatus.Text = ""
            objCryptoFilterBox.InBuffer = txtInput.Text
            objCryptoFilterBox.Password = txtPassword.Text
            objCryptoFilterBox.Encrypt
            txtOutput.Text = objCryptoFilterBox.OutBuffer
            Select Case objCryptoFilterBox.Status
                Case CFB_READY
                    txtStatus.Text = "Ready"
                Case Else
                    txtStatus.Text = ""
            End Select
        
        Case "Sign"
            txtStatus.Text = ""
            objCryptoFilterBox.InBuffer = txtInput.Text
            objCryptoFilterBox.Sign
            txtSignature.Text = objCryptoFilterBox.Signature
            Select Case objCryptoFilterBox.Status
                Case CFB_READY
                    txtStatus.Text = "Ready"
                Case Else
                    txtStatus.Text = ""
            End Select
        
        Case "Validate"
            txtStatus.Text = ""
            objCryptoFilterBox.InBuffer = txtInput.Text
            objCryptoFilterBox.Signature = txtSignature.Text
            objCryptoFilterBox.Validate
            Select Case objCryptoFilterBox.Status
                Case CFB_VALID
                    txtStatus.Text = "Signature is valid"
                Case Else
                    txtStatus.Text = "Invalid signature"
            End Select
        
        Case ""
            MsgBox ("Method not selected")
            Select Case objCryptoFilterBox.Status
                Case CFB_READY
                    txtStatus.Text = "Ready"
                Case Else
                    txtStatus.Text = ""
            End Select
        
        Case Else
            MsgBox ("Unknown method selected.")
            Select Case objCryptoFilterBox.Status
                Case CFB_READY
                    txtStatus.Text = "Ready"
                Case Else
                    txtStatus.Text = ""
            End Select
    
    End Select
    
Exit Sub

ErrcmbGo_Click:
    MsgBox ("ErrcmbGo_Click " & Error$)
    Resume
    
End Sub

Private Sub Form_Load()
    
Dim lResult As Long
    
On Error GoTo ErrForm_Load

Set objCryptoFilterBox = New clsCryptoFilterBox
    
lstMethod.AddItem "Decrypt"
lstMethod.AddItem "Encrypt"
lstMethod.AddItem "Sign"
lstMethod.AddItem "Validate"

Exit Sub

ErrForm_Load:
    
MsgBox ("ErrForm_Load " & Error$)
Resume

End Sub

Private Sub Form_Unload(Cancel As Integer)
    End
End Sub
