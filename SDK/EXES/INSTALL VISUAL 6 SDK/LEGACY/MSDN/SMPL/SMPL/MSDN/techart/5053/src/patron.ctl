VERSION 5.00
Begin VB.UserControl Patron 
   BackStyle       =   0  'Transparent
   ClientHeight    =   2040
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   3975
   ScaleHeight     =   2040
   ScaleWidth      =   3975
   Begin VB.Frame frameMain 
      Caption         =   "Patron - "
      Height          =   1905
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   3855
      Begin VB.CommandButton btRepay 
         Caption         =   "Repay Loan"
         Height          =   315
         Left            =   2385
         TabIndex        =   8
         Top             =   1470
         Width           =   1350
      End
      Begin VB.CommandButton btApply 
         Caption         =   "Apply For Loan"
         Height          =   315
         Left            =   2385
         TabIndex        =   6
         Top             =   1125
         Width           =   1350
      End
      Begin VB.CommandButton btDebit 
         Caption         =   "Debit"
         Height          =   315
         Left            =   2385
         TabIndex        =   3
         Top             =   675
         Width           =   1350
      End
      Begin VB.CommandButton btCredit 
         Caption         =   "Credit"
         Height          =   315
         Left            =   2385
         TabIndex        =   2
         Top             =   330
         Width           =   1350
      End
      Begin VB.TextBox txtAmount 
         Height          =   285
         Left            =   1065
         TabIndex        =   1
         Top             =   690
         Width           =   1275
      End
      Begin VB.Label lblLender 
         Caption         =   "Lender -"
         Height          =   225
         Left            =   360
         TabIndex        =   7
         Top             =   1335
         Width           =   1935
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
         Left            =   90
         TabIndex        =   5
         Top             =   270
         Width           =   2220
      End
      Begin VB.Label lblBank 
         Alignment       =   1  'Right Justify
         Appearance      =   0  'Flat
         AutoSize        =   -1  'True
         BackColor       =   &H80000005&
         BackStyle       =   0  'Transparent
         Caption         =   "Transaction Amount "
         ForeColor       =   &H80000008&
         Height          =   390
         Index           =   6
         Left            =   120
         TabIndex        =   4
         Top             =   615
         Width           =   900
         WordWrap        =   -1  'True
      End
   End
End
Attribute VB_Name = "Patron"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
'Property Variables:
Private m_Bank As Bank
Private m_Lender As Lender
Attribute m_Lender.VB_VarHelpID = -1
Private m_sAcctNum As String

Private Sub btApply_Click()
Dim cAmount As Currency
If Not (m_Lender Is Nothing) Then
    If Len(Trim$(txtAmount)) Then
        cAmount = CCur(txtAmount)
        If m_Lender.SubmitLoan(Me, cAmount) Then
            MsgBox "Submitted loan application successfully.", vbOKOnly, "Application Submitted"
        Else
            MsgBox "Failed to submitted loan application.", vbOKOnly, "Application Not Submitted"
        End If
        Refresh
    End If
End If
End Sub

Private Sub btCredit_Click()
Dim cAmount As Currency
If Not (m_Bank Is Nothing) Then
    If Len(Trim$(txtAmount)) Then
        cAmount = CCur(txtAmount)
        If m_Bank.Credit(m_sAcctNum, cAmount) Then
            MsgBox "Account balance has been credited. [" & Format$(cAmount, "Currency") & "]", vbOKOnly, "Credit Successful"
        Else
            MsgBox "Failed to credit account balance.", vbOKOnly, "Credit Failed"
        End If
        Refresh
    End If
End If
End Sub

Private Sub btDebit_Click()
Dim cAmount As Currency
If Not (m_Bank Is Nothing) Then
    If Len(Trim$(txtAmount)) Then
        cAmount = CCur(txtAmount)
        If m_Bank.Debit(m_sAcctNum, cAmount) Then
            MsgBox "Account balance has been debited. [" & Format$(cAmount, "Currency") & "]", vbOKOnly, "Debit Successful"
        Else
            MsgBox "Failed to debit account balance.", vbOKOnly, "Debit Failed"
        End If
        Refresh
    End If
End If
End Sub

Public Sub LoanDenied()
MsgBox "Your loan request has been denied.", vbOKOnly, "Loan Denied"
Refresh
End Sub

Public Sub LoanGranted()
MsgBox "Your loan request has been approved.", vbOKOnly, "Loan Approved"
Refresh
End Sub

Private Sub btRepay_Click()
Dim cAmount As Currency
Dim sDest   As String

If Not (m_Bank Is Nothing) Then
    If Not (m_Lender Is Nothing) Then
        If Len(Trim$(txtAmount)) Then
            cAmount = CCur(txtAmount)
            If m_Bank.RepayLoan(Me, m_Lender, cAmount) Then
                MsgBox "Loan has been repaid successfully. [" & Format$(cAmount, "Currency") & "]", vbOKOnly, "Transfer Successful"
            Else
                MsgBox "Loan could not be repaid.", vbOKOnly, "Transfer Failed"
            End If
            m_Lender.Refresh
            Refresh
        End If
    End If
End If
End Sub

Private Sub UserControl_Resize()
Height = frameMain.Height
Width = frameMain.Width
End Sub

'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=frameMain,frameMain,-1,BackColor
Public Property Get BackColor() As OLE_COLOR
Attribute BackColor.VB_Description = "Returns/sets the background color used to display text and graphics in an object."
BackColor = frameMain.BackColor
End Property

Public Property Let BackColor(ByVal New_BackColor As OLE_COLOR)
frameMain.BackColor() = New_BackColor
PropertyChanged "BackColor"
End Property

'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=lblBalance,lblBalance,-1,ForeColor
Public Property Get ForeColor() As OLE_COLOR
Attribute ForeColor.VB_Description = "Returns/sets the foreground color used to display text and graphics in an object."
ForeColor = lblBalance.ForeColor
End Property

Public Property Let ForeColor(ByVal New_ForeColor As OLE_COLOR)
lblBalance.ForeColor() = New_ForeColor
PropertyChanged "ForeColor"
End Property

'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=frameMain,frameMain,-1,Enabled
Public Property Get Enabled() As Boolean
Attribute Enabled.VB_Description = "Returns/sets a value that determines whether an object can respond to user-generated events."
Enabled = frameMain.Enabled
End Property

Public Property Let Enabled(ByVal New_Enabled As Boolean)
frameMain.Enabled() = New_Enabled
PropertyChanged "Enabled"
End Property

'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=lblBalance,lblBalance,-1,Font
Public Property Get Font() As Font
Attribute Font.VB_Description = "Returns a Font object."
Attribute Font.VB_UserMemId = -512
Set Font = lblBalance.Font
End Property

Public Property Set Font(ByVal New_Font As Font)
Set lblBalance.Font = New_Font
PropertyChanged "Font"
End Property

Public Sub Refresh()
Attribute Refresh.VB_Description = "Forces a complete repaint of a object."
On Error Resume Next
lblBalance = "Balance: " & Format$(m_Bank.GetAccountBalance(m_sAcctNum), "Currency")
If m_Lender Is Nothing Then
    lblLender = "No Lender Account"
    btApply.Enabled = False
Else
    lblLender = "Lender - " & m_Lender.AccountNumber
    btApply.Enabled = True
End If
End Sub

Public Property Get Bank() As Bank
Set Bank = m_Bank
End Property

Public Property Set Bank(ByVal New_Bank As Bank)
Set m_Bank = New_Bank
End Property

Public Property Get Lender() As Lender
Set Lender = m_Lender
End Property

Public Property Set Lender(ByVal New_Lender As Lender)
Set m_Lender = New_Lender
If m_Lender Is Nothing Then
    lblLender = "No Lender Account"
    btApply.Enabled = False
Else
    lblLender = "Lender - " & m_Lender.AccountNumber
    btApply.Enabled = True
End If
End Property

'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=frameMain,frameMain,-1,Caption
Public Property Get AccountNumber() As String
Attribute AccountNumber.VB_Description = "Returns/sets the text displayed in an object's title bar or below an object's icon."
AccountNumber = m_sAcctNum
End Property

Public Property Let AccountNumber(ByVal New_AccountNumber As String)
m_sAcctNum = Trim$(New_AccountNumber)
If Len(m_sAcctNum) Then
    frameMain.Caption = "Patron Of Account - " & m_sAcctNum
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
Set m_Bank = PropBag.ReadProperty("Bank", Nothing)
AccountNumber = PropBag.ReadProperty("AccountNumber", "")
End Sub

'Write property values to storage
Private Sub UserControl_WriteProperties(PropBag As PropertyBag)

Call PropBag.WriteProperty("BackColor", frameMain.BackColor, &H8000000F)
Call PropBag.WriteProperty("ForeColor", lblBalance.ForeColor, &HFF0000)
Call PropBag.WriteProperty("Enabled", frameMain.Enabled, True)
Call PropBag.WriteProperty("Font", Font, Ambient.Font)
Call PropBag.WriteProperty("Bank", m_Bank, Nothing)
Call PropBag.WriteProperty("AccountNumber", m_sAcctNum, "")
End Sub

