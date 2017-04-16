VERSION 5.00
Begin VB.UserControl Bank 
   BackStyle       =   0  'Transparent
   ClientHeight    =   2835
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   6570
   FontTransparent =   0   'False
   PropertyPages   =   "bank.ctx":0000
   ScaleHeight     =   2835
   ScaleWidth      =   6570
   Begin VB.Frame frameMain 
      Caption         =   "Bank"
      Height          =   2490
      Left            =   15
      TabIndex        =   0
      Top             =   0
      Width           =   6330
      Begin VB.ListBox lstAccounts 
         Height          =   1230
         IntegralHeight  =   0   'False
         Left            =   105
         Sorted          =   -1  'True
         TabIndex        =   10
         Top             =   1140
         Width           =   2940
      End
      Begin VB.Frame frameAddress 
         Caption         =   "Address"
         Height          =   1335
         Left            =   3120
         TabIndex        =   4
         Top             =   1050
         Width           =   3100
         Begin VB.TextBox txtAdd1 
            Height          =   285
            Left            =   555
            Locked          =   -1  'True
            TabIndex        =   7
            Top             =   240
            Width           =   2445
         End
         Begin VB.TextBox txtAdd2 
            Height          =   285
            Left            =   555
            Locked          =   -1  'True
            TabIndex        =   6
            Top             =   570
            Width           =   2445
         End
         Begin VB.TextBox txtCity 
            Height          =   285
            Left            =   555
            Locked          =   -1  'True
            TabIndex        =   5
            Top             =   930
            Width           =   2445
         End
         Begin VB.Label lblBank 
            Appearance      =   0  'Flat
            AutoSize        =   -1  'True
            BackColor       =   &H80000005&
            BackStyle       =   0  'Transparent
            Caption         =   "City"
            ForeColor       =   &H80000008&
            Height          =   195
            Index           =   3
            Left            =   225
            TabIndex        =   9
            Top             =   945
            Width           =   255
         End
         Begin VB.Label lblBank 
            Appearance      =   0  'Flat
            AutoSize        =   -1  'True
            BackColor       =   &H80000005&
            BackStyle       =   0  'Transparent
            Caption         =   "Street"
            ForeColor       =   &H80000008&
            Height          =   195
            Index           =   2
            Left            =   75
            TabIndex        =   8
            Top             =   270
            Width           =   420
         End
      End
      Begin VB.ComboBox cmbBankType 
         Height          =   315
         Left            =   105
         Locked          =   -1  'True
         Sorted          =   -1  'True
         Style           =   2  'Dropdown List
         TabIndex        =   1
         Top             =   540
         Width           =   2940
      End
      Begin VB.Label lblWorth 
         Alignment       =   2  'Center
         Caption         =   "Net Worth: $0.0"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FF0000&
         Height          =   255
         Left            =   3120
         TabIndex        =   13
         Top             =   765
         Width           =   3105
      End
      Begin VB.Label lblDebits 
         Alignment       =   2  'Center
         Caption         =   "Debits: $0.0"
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
         Height          =   255
         Left            =   3120
         TabIndex        =   12
         Top             =   480
         Width           =   3105
      End
      Begin VB.Label lblCredits 
         Alignment       =   2  'Center
         Caption         =   "Credits: $0.0"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00000000&
         Height          =   255
         Left            =   3120
         TabIndex        =   11
         Top             =   180
         Width           =   3105
      End
      Begin VB.Label lblBank 
         Appearance      =   0  'Flat
         AutoSize        =   -1  'True
         BackColor       =   &H80000005&
         BackStyle       =   0  'Transparent
         Caption         =   "Type"
         ForeColor       =   &H80000008&
         Height          =   195
         Index           =   4
         Left            =   120
         TabIndex        =   3
         Top             =   300
         Width           =   360
      End
      Begin VB.Label lblBank 
         Appearance      =   0  'Flat
         AutoSize        =   -1  'True
         BackColor       =   &H80000005&
         BackStyle       =   0  'Transparent
         Caption         =   "Accounts"
         ForeColor       =   &H80000008&
         Height          =   195
         Index           =   0
         Left            =   105
         TabIndex        =   2
         Top             =   915
         Width           =   675
      End
   End
End
Attribute VB_Name = "Bank"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "PropPageWizardRun" ,"Yes"
Option Explicit

'Property Variables:
Private m_PKId  As Long
Private m_sCode As String

Private m_oAdmin    As CAdmin
Private m_sDataSrc  As String

Public Function GetAccountBalance(ByVal sAccount As String) As Currency
Dim cTemp As Collection

On Error Resume Next
If m_oAdmin.FillCollection("SELECT Balance FROM tbAccount WHERE Number = '" & Trim$(sAccount) & "'", cTemp) Then
    GetAccountBalance = CCur(cTemp("Balance"))
End If
End Function

Public Function Credit(ByVal sAccount As String, ByVal mnyAmount As Currency) As Boolean
Dim cParms As Collection

On Error Resume Next
Set cParms = New Collection
mnyAmount = Abs(mnyAmount)
cParms.Add sAccount, "[@Number]"
cParms.Add mnyAmount, "[@Amount]"
Credit = m_oAdmin.ExecBoolean("pcUpd_AccountBalance", cParms)
Refresh
End Function

Public Function Debit(ByVal sAccount As String, ByVal mnyAmount As Currency) As Boolean
Dim cParms As Collection

On Error Resume Next
Set cParms = New Collection
mnyAmount = Abs(mnyAmount)
mnyAmount = -mnyAmount
cParms.Add sAccount, "[@Number]"
cParms.Add mnyAmount, "[@Amount]"
Debit = m_oAdmin.ExecBoolean("pcUpd_AccountBalance", cParms)
Refresh
End Function

Public Function ExecuteLoan(ctlLender As Lender, ctlPatron As Patron, ByVal mnyAmount As Currency) As Boolean
ExecuteLoan = m_oAdmin.Transfer(ctlLender.AccountNumber, ctlPatron.AccountNumber, mnyAmount)
Refresh
End Function

Public Function RepayLoan(ctlPatron As Patron, ctlLender As Lender, ByVal mnyAmount As Currency) As Boolean
RepayLoan = m_oAdmin.Transfer(ctlPatron.AccountNumber, ctlLender.AccountNumber, mnyAmount)
Refresh
End Function

Public Function Init() As Boolean
Dim sTemp() As String
Dim iRow    As Integer

On Error Resume Next
If Len(Trim$(m_sDataSrc)) Then
    Set m_oAdmin = New CAdmin
    If m_oAdmin.Init(m_sDataSrc) Then
        m_oAdmin.FillListBanks
        If m_oAdmin.ExecFillArray("SELECT Desc, PKId FROM tbBankType", sTemp()) Then
            For iRow = LBound(sTemp, 2) To UBound(sTemp, 2)
                cmbBankType.AddItem sTemp(0, iRow)
                cmbBankType.ItemData(cmbBankType.NewIndex) = CInt(sTemp(1, iRow))
            Next iRow
        End If
        Refresh
        Init = True
    End If
End If
End Function

Private Sub Clear()
txtAdd1 = ""
txtAdd2 = ""
txtCity = ""
If cmbBankType.ListCount Then cmbBankType.ListIndex = 0
lstAccounts.Clear
frameMain.Caption = "No Current Bank"
End Sub

Private Sub DisplayBank()
Dim oBank As CBank
Dim oAcct As CAccount
Dim cPos  As Currency
Dim cNeg  As Currency

Clear
If m_PKId Then
    Set oBank = m_oAdmin.Banks("Id=" & Trim$(CStr(m_PKId)))
    With oBank
        frameMain.Caption = "Bank - " & .Name & " [" & .Code & "]"
        txtAdd1 = .Address1
        txtAdd2 = .Address2
        txtCity = .City
        FindItem cmbBankType, .TypeId
        
        For Each oAcct In .Accounts
            lstAccounts.AddItem Trim$(oAcct.Number) & Chr$(9) & Format$(oAcct.Balance, "Currency")
            lstAccounts.ItemData(lstAccounts.NewIndex) = oAcct.PKId
            If oAcct.Balance > 0 Then
                cPos = cPos + oAcct.Balance
            Else
                cNeg = cNeg + oAcct.Balance
            End If
        Next oAcct
        lblCredits = "Credits: " & Format$(cPos, "Currency")
        lblDebits = "Debits: " & Format$(cNeg, "Currency")
        lblWorth = "Net Worth: " & Format$(cPos + cNeg, "Currency")
    End With
End If
End Sub

Private Sub FindItem(ctlThis As Control, ByVal iItem As Integer)
Dim iIndex As Integer

ctlThis.ListIndex = -1
For iIndex = 0 To ctlThis.ListCount - 1
    If ctlThis.ItemData(iIndex) = iItem Then
        ctlThis.ListIndex = iIndex
        Exit For
    End If
Next iIndex
End Sub

Public Property Get DataSource() As String
DataSource = m_sDataSrc
End Property

Public Property Let DataSource(ByVal New_DataSource As String)
m_sDataSrc = New_DataSource
PropertyChanged "DataSource"
End Property

'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=UserControl,UserControl,-1,BackColor
Public Property Get BackColor() As OLE_COLOR
Attribute BackColor.VB_Description = "Returns/sets the background color used to display text and graphics in an object."
BackColor = UserControl.BackColor
End Property

Public Property Let BackColor(ByVal New_BackColor As OLE_COLOR)
UserControl.BackColor() = New_BackColor
PropertyChanged "BackColor"
End Property

'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=UserControl,UserControl,-1,ForeColor
Public Property Get ForeColor() As OLE_COLOR
Attribute ForeColor.VB_Description = "Returns/sets the foreground color used to display text and graphics in an object."
ForeColor = UserControl.ForeColor
End Property

Public Property Let ForeColor(ByVal New_ForeColor As OLE_COLOR)
UserControl.ForeColor() = New_ForeColor
PropertyChanged "ForeColor"
End Property

'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=UserControl,UserControl,-1,Enabled
Public Property Get Enabled() As Boolean
Attribute Enabled.VB_Description = "Returns/sets a value that determines whether an object can respond to user-generated events."
Enabled = frameMain.Enabled
End Property

Public Property Let Enabled(ByVal New_Enabled As Boolean)
frameMain.Enabled = New_Enabled
PropertyChanged "Enabled"
End Property

'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=UserControl,UserControl,-1,Font
Public Property Get Font() As Font
Attribute Font.VB_Description = "Returns a Font object."
Attribute Font.VB_UserMemId = -512
Set Font = UserControl.Font
End Property

Public Property Set Font(ByVal New_Font As Font)
Set UserControl.Font = New_Font
PropertyChanged "Font"
End Property

Public Property Get BankCode() As String
BankCode = m_sCode
End Property

Public Property Let BankCode(ByVal New_BankCode As String)
m_sCode = New_BankCode
PropertyChanged "BankCode"
End Property

Public Sub Refresh()
Dim oBank As CBank
If Not (m_oAdmin Is Nothing) Then
    m_oAdmin.FillListBanks
    For Each oBank In m_oAdmin.Banks
        If oBank.Code = m_sCode Then
            m_PKId = oBank.PKId
            DisplayBank
            Exit For
        End If
    Next oBank
Else
    Clear
End If
End Sub

'Load property values from storage
Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
UserControl.BackColor = PropBag.ReadProperty("BackColor", &H8000000F)
UserControl.ForeColor = PropBag.ReadProperty("ForeColor", &H80000012)
frameMain.Enabled = PropBag.ReadProperty("Enabled", True)
Set Font = PropBag.ReadProperty("Font", Ambient.Font)
m_sDataSrc = PropBag.ReadProperty("DataSource", "")
m_sCode = PropBag.ReadProperty("BankCode", "")
Refresh
End Sub

Private Sub UserControl_Resize()
Height = frameMain.Height
Width = frameMain.Width
End Sub

'Write property values to storage
Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
Call PropBag.WriteProperty("BackColor", UserControl.BackColor, &H8000000F)
Call PropBag.WriteProperty("ForeColor", UserControl.ForeColor, &H80000012)
Call PropBag.WriteProperty("Enabled", frameMain.Enabled, True)
Call PropBag.WriteProperty("Font", Font, Ambient.Font)
Call PropBag.WriteProperty("DataSource", m_sDataSrc, "")
Call PropBag.WriteProperty("BankCode", m_sCode, "")
End Sub

