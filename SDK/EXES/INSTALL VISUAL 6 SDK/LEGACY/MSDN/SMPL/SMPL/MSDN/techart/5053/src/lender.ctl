VERSION 5.00
Begin VB.UserControl Lender 
   ClientHeight    =   3540
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4245
   LockControls    =   -1  'True
   ScaleHeight     =   3540
   ScaleWidth      =   4245
   Begin VB.Frame frameMain 
      Caption         =   "Lender Account - "
      Height          =   3135
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   3900
      Begin VB.CommandButton btDeny 
         Caption         =   "Deny"
         Height          =   315
         Left            =   2745
         TabIndex        =   9
         Top             =   1935
         Width           =   1020
      End
      Begin VB.CommandButton btGrant 
         Caption         =   "Grant"
         Height          =   315
         Left            =   2745
         TabIndex        =   8
         Top             =   1590
         Width           =   1020
      End
      Begin VB.ListBox lstLoans 
         Height          =   1425
         Left            =   120
         Sorted          =   -1  'True
         TabIndex        =   6
         Top             =   1590
         Width           =   2535
      End
      Begin VB.TextBox txtAmount 
         Height          =   285
         Left            =   1050
         TabIndex        =   3
         Top             =   810
         Width           =   1605
      End
      Begin VB.CommandButton btCredit 
         Caption         =   "Credit"
         Height          =   315
         Left            =   2775
         TabIndex        =   2
         Top             =   645
         Width           =   1020
      End
      Begin VB.CommandButton btDebit 
         Caption         =   "Debit"
         Height          =   315
         Left            =   2775
         TabIndex        =   1
         Top             =   990
         Width           =   1020
      End
      Begin VB.Label lblLender 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BackStyle       =   0  'Transparent
         Caption         =   "Amount"
         ForeColor       =   &H80000008&
         Height          =   195
         Index           =   2
         Left            =   2745
         TabIndex        =   11
         Top             =   2565
         Width           =   1020
      End
      Begin VB.Label lblAmount 
         Alignment       =   2  'Center
         Caption         =   "$0.0"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   210
         Left            =   2745
         TabIndex        =   10
         Top             =   2790
         Width           =   1020
      End
      Begin VB.Label lblLender 
         Alignment       =   1  'Right Justify
         Appearance      =   0  'Flat
         AutoSize        =   -1  'True
         BackColor       =   &H80000005&
         BackStyle       =   0  'Transparent
         Caption         =   "Loans Requested"
         ForeColor       =   &H80000008&
         Height          =   195
         Index           =   1
         Left            =   135
         TabIndex        =   7
         Top             =   1365
         Width           =   1260
      End
      Begin VB.Label lblLender 
         Alignment       =   1  'Right Justify
         Appearance      =   0  'Flat
         AutoSize        =   -1  'True
         BackColor       =   &H80000005&
         BackStyle       =   0  'Transparent
         Caption         =   "Transaction Amount "
         ForeColor       =   &H80000008&
         Height          =   390
         Index           =   0
         Left            =   120
         TabIndex        =   5
         Top             =   735
         Width           =   900
         WordWrap        =   -1  'True
      End
      Begin VB.Label lblBalance 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BackStyle       =   0  'Transparent
         Caption         =   "Balance: $0.0"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FF0000&
         Height          =   300
         Left            =   75
         TabIndex        =   4
         Top             =   270
         Width           =   3780
      End
   End
End
Attribute VB_Name = "Lender"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

'Property Variables:
Private m_Bank As Bank
Attribute m_Bank.VB_VarHelpID = -1
Private m_sAcctNum As String
Private m_cPatrons As Collection
Private m_cAmounts As Collection


Public Function SubmitLoan(ctlPatron As Patron, ByVal mnyAmount As Currency) As Boolean
On Error Resume Next
If Not (ctlPatron Is Nothing) Then
    Err = False
    m_cPatrons.Add ctlPatron, ctlPatron.AccountNumber
    If CBool(Err) Then Exit Function
    m_cAmounts.Add mnyAmount, ctlPatron.AccountNumber
    lstLoans.AddItem ctlPatron.AccountNumber
    SubmitLoan = True
End If
End Function

Private Sub btCredit_Click()
Dim cAmount As Currency
If Not (m_Bank Is Nothing) Then
    cAmount = CCur(txtAmount)
    If m_Bank.Credit(m_sAcctNum, cAmount) Then
        MsgBox "Account balance has been credited. [" & Format$(cAmount, "Currency") & "]", vbOKOnly, "Credit Successful"
    Else
        MsgBox "Failed to credit account balance.", vbOKOnly, "Credit Failed"
    End If
    Refresh
End If
End Sub

Private Sub btDebit_Click()
Dim cAmount As Currency
If Not (m_Bank Is Nothing) Then
    cAmount = CCur(txtAmount)
    If m_Bank.Debit(m_sAcctNum, cAmount) Then
        MsgBox "Account balance has been debited. [" & Format$(cAmount, "Currency") & "]", vbOKOnly, "Debit Successful"
    Else
        MsgBox "Failed to debit account balance.", vbOKOnly, "Debit Failed"
    End If
    Refresh
End If
End Sub

Private Sub btDeny_Click()
If lstLoans.ListIndex <> -1 Then
    m_cPatrons(lstLoans.Text).LoanDenied
    m_cPatrons.Remove lstLoans.Text
    m_cAmounts.Remove lstLoans.Text
    lstLoans.RemoveItem lstLoans.ListIndex
    Refresh
End If
End Sub

Private Sub btGrant_Click()
Dim cAmount As Currency
Dim sDest   As String

If lstLoans.ListIndex <> -1 Then
    sDest = lstLoans.Text
    If Not (m_Bank Is Nothing) Then
        cAmount = CCur(m_cAmounts(sDest))
        If m_Bank.ExecuteLoan(Me, m_cPatrons(sDest), cAmount) Then
            MsgBox "Loan has been executed successfully. [" & Format$(cAmount, "Currency") & "]", vbOKOnly, "Transfer Successful"
            m_cPatrons(sDest).LoanGranted
            m_cPatrons.Remove sDest
            m_cAmounts.Remove sDest
            lstLoans.RemoveItem lstLoans.ListIndex
        Else
            MsgBox "Loan could not be executed.", vbOKOnly, "Transfer Failed"
        End If
        Refresh
    End If
End If
End Sub

Private Sub lstLoans_Click()
If lstLoans.ListIndex <> -1 Then
    lblAmount = Format$(m_cAmounts(lstLoans.Text), "Currency")
Else
    lblAmount = Format$(0, "Currency")
End If
End Sub

Private Sub UserControl_Initialize()
Set m_cPatrons = New Collection
Set m_cAmounts = New Collection
End Sub

Private Sub UserControl_Resize()
Height = frameMain.Height
Width = frameMain.Width
End Sub

'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=frameMain,frameMain,-1,BackColor
Public Property Get BackColor() As OLE_COLOR
BackColor = frameMain.BackColor
End Property

Public Property Let BackColor(ByVal New_BackColor As OLE_COLOR)
frameMain.BackColor() = New_BackColor
PropertyChanged "BackColor"
End Property

'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=lblBalance,lblBalance,-1,ForeColor
Public Property Get ForeColor() As OLE_COLOR
ForeColor = lblBalance.ForeColor
End Property

Public Property Let ForeColor(ByVal New_ForeColor As OLE_COLOR)
lblBalance.ForeColor() = New_ForeColor
PropertyChanged "ForeColor"
End Property

'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=frameMain,frameMain,-1,Enabled
Public Property Get Enabled() As Boolean
Enabled = frameMain.Enabled
End Property

Public Property Let Enabled(ByVal New_Enabled As Boolean)
frameMain.Enabled() = New_Enabled
PropertyChanged "Enabled"
End Property

'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=lblBalance,lblBalance,-1,Font
Public Property Get Font() As Font
Set Font = lblBalance.Font
End Property

Public Property Set Font(ByVal New_Font As Font)
Set lblBalance.Font = New_Font
PropertyChanged "Font"
End Property

Public Sub Refresh()
On Error Resume Next
lblBalance = "Balance: " & Format$(m_Bank.GetAccountBalance(m_sAcctNum), "Currency")
lblAmount = Format$(0, "Currency")
lstLoans.ListIndex = -1
End Sub

Public Property Get Bank() As Bank
Set Bank = m_Bank
End Property

Public Property Set Bank(ByVal New_Bank As Bank)
Set m_Bank = New_Bank
End Property

'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=frameMain,frameMain,-1,Caption
Public Property Get AccountNumber() As String
AccountNumber = m_sAcctNum
End Property

Public Property Let AccountNumber(ByVal New_AccountNumber As String)
m_sAcctNum = Trim$(New_AccountNumber)
If Len(m_sAcctNum) Then
    frameMain.Caption = "Lender Account - " & m_sAcctNum
Else
    frameMain.Caption = "No Current Account"
End If
PropertyChanged "AccountNumber"
End Property

'Load property values from storage
Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
frameMain.BackColor = PropBag.ReadProperty("BackColor", &H8000000F)
lblBalance.ForeColor = PropBag.ReadProperty("ForeColor", &HFF0000)
frameMain.Enabled = PropBag.ReadProperty("Enabled", True)
Set Font = PropBag.ReadProperty("Font", Ambient.Font)
AccountNumber = PropBag.ReadProperty("AccountNumber", "")
End Sub

'Private Sub UserControl_Terminate()
'Dim oPatron As Patron
'For Each oPatron In m_cPatrons
'    oPatron.LoanDenied
'Next oPatron
'Set m_cPatrons = Nothing
'Set m_cAmounts = Nothing
'End Sub

'Write property values to storage
Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
Call PropBag.WriteProperty("BackColor", frameMain.BackColor, &H8000000F)
Call PropBag.WriteProperty("ForeColor", lblBalance.ForeColor, &HFF0000)
Call PropBag.WriteProperty("Enabled", frameMain.Enabled, True)
Call PropBag.WriteProperty("Font", Font, Ambient.Font)
Call PropBag.WriteProperty("AccountNumber", m_sAcctNum, "")
End Sub


