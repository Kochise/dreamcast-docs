VERSION 5.00
Begin VB.UserControl BankView 
   ClientHeight    =   4965
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   7575
   ScaleHeight     =   4965
   ScaleWidth      =   7575
   Begin VB.Frame frBank 
      Caption         =   "Accounts"
      Height          =   4815
      Index           =   1
      Left            =   3840
      TabIndex        =   15
      Top             =   0
      Width           =   3615
      Begin VB.CommandButton cmdAcct 
         Caption         =   "&Delete"
         Height          =   255
         Index           =   4
         Left            =   2520
         TabIndex        =   32
         Top             =   4440
         Width           =   855
      End
      Begin VB.TextBox txtAcct 
         Height          =   285
         Index           =   3
         Left            =   2040
         TabIndex        =   30
         Top             =   3480
         Width           =   1335
      End
      Begin VB.TextBox txtAcct 
         Height          =   285
         Index           =   2
         Left            =   120
         TabIndex        =   29
         Top             =   3480
         Width           =   1335
      End
      Begin VB.ListBox lstAcctType 
         Height          =   840
         ItemData        =   "BankView.ctx":0000
         Left            =   840
         List            =   "BankView.ctx":0002
         TabIndex        =   28
         Top             =   2040
         Width           =   2535
      End
      Begin VB.CommandButton cmdAcct 
         Caption         =   "&Save"
         Height          =   255
         Index           =   3
         Left            =   1320
         TabIndex        =   25
         Top             =   4440
         Width           =   855
      End
      Begin VB.CommandButton cmdAcct 
         Caption         =   "&Add"
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   24
         Top             =   4440
         Width           =   855
      End
      Begin VB.CommandButton cmdAcct 
         Caption         =   "&Withdrawal"
         Height          =   255
         Index           =   1
         Left            =   2040
         TabIndex        =   23
         Top             =   3840
         Width           =   1335
      End
      Begin VB.CommandButton cmdAcct 
         Caption         =   "De&posit"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   22
         Top             =   3840
         Width           =   1335
      End
      Begin VB.TextBox txtAcct 
         Height          =   285
         Index           =   0
         Left            =   840
         TabIndex        =   21
         Top             =   1680
         Width           =   2535
      End
      Begin VB.ListBox lstAcct 
         Height          =   1230
         ItemData        =   "BankView.ctx":0004
         Left            =   120
         List            =   "BankView.ctx":0006
         TabIndex        =   20
         Top             =   240
         Width           =   3255
      End
      Begin VB.Label lblBalance 
         Alignment       =   2  'Center
         Caption         =   "Balance: $0.00"
         Height          =   255
         Left            =   120
         TabIndex        =   33
         Top             =   3000
         Width           =   3255
      End
      Begin VB.Label Label1 
         Caption         =   "Number:"
         Height          =   255
         Index           =   11
         Left            =   120
         TabIndex        =   17
         Top             =   1680
         Width           =   735
      End
      Begin VB.Label Label1 
         Caption         =   "Type:"
         Height          =   255
         Index           =   10
         Left            =   120
         TabIndex        =   16
         Top             =   2040
         Width           =   735
      End
   End
   Begin VB.Frame frBank 
      Caption         =   "Bank"
      Height          =   4815
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   3615
      Begin VB.CommandButton cmdBank 
         Caption         =   "&Delete"
         Height          =   255
         Index           =   2
         Left            =   2520
         TabIndex        =   31
         Top             =   4440
         Width           =   855
      End
      Begin VB.ListBox lstBankType 
         Height          =   840
         ItemData        =   "BankView.ctx":0008
         Left            =   840
         List            =   "BankView.ctx":000A
         TabIndex        =   27
         Top             =   2040
         Width           =   2535
      End
      Begin VB.CommandButton cmdBank 
         Caption         =   "&Save"
         Height          =   255
         Index           =   1
         Left            =   1320
         TabIndex        =   19
         Top             =   4440
         Width           =   855
      End
      Begin VB.CommandButton cmdBank 
         Caption         =   "&Add"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   18
         Top             =   4440
         Width           =   855
      End
      Begin VB.TextBox txtBank 
         Height          =   285
         Index           =   4
         Left            =   840
         TabIndex        =   14
         Top             =   1680
         Width           =   2535
      End
      Begin VB.TextBox txtBank 
         Height          =   285
         Index           =   3
         Left            =   840
         TabIndex        =   13
         Top             =   1320
         Width           =   2535
      End
      Begin VB.TextBox txtBank 
         Height          =   285
         Index           =   2
         Left            =   840
         TabIndex        =   12
         Top             =   960
         Width           =   2535
      End
      Begin VB.TextBox txtBank 
         Height          =   285
         Index           =   1
         Left            =   840
         TabIndex        =   11
         Top             =   600
         Width           =   2535
      End
      Begin VB.TextBox txtBank 
         Height          =   285
         Index           =   0
         Left            =   840
         TabIndex        =   10
         Top             =   240
         Width           =   2535
      End
      Begin VB.CommandButton cmdNav 
         Height          =   255
         Index           =   0
         Left            =   120
         Picture         =   "BankView.ctx":000C
         Style           =   1  'Graphical
         TabIndex        =   4
         Top             =   4080
         Width           =   375
      End
      Begin VB.CommandButton cmdNav 
         Height          =   255
         Index           =   1
         Left            =   600
         Picture         =   "BankView.ctx":00F6
         Style           =   1  'Graphical
         TabIndex        =   3
         Top             =   4080
         Width           =   375
      End
      Begin VB.CommandButton cmdNav 
         Height          =   255
         Index           =   2
         Left            =   2520
         Picture         =   "BankView.ctx":01E0
         Style           =   1  'Graphical
         TabIndex        =   2
         Top             =   4080
         Width           =   375
      End
      Begin VB.CommandButton cmdNav 
         Height          =   255
         Index           =   3
         Left            =   3000
         Picture         =   "BankView.ctx":02CA
         Style           =   1  'Graphical
         TabIndex        =   1
         Top             =   4080
         Width           =   375
      End
      Begin VB.Label lblNetValue 
         Alignment       =   2  'Center
         Caption         =   "Net Acct Value: $0.00"
         Height          =   255
         Left            =   120
         TabIndex        =   34
         Top             =   3000
         Width           =   3255
      End
      Begin VB.Label Label1 
         Caption         =   "Type:"
         Height          =   255
         Index           =   6
         Left            =   120
         TabIndex        =   26
         Top             =   2040
         Width           =   735
      End
      Begin VB.Label Label1 
         Caption         =   "City:"
         Height          =   255
         Index           =   5
         Left            =   120
         TabIndex        =   9
         Top             =   1680
         Width           =   735
      End
      Begin VB.Label Label1 
         Caption         =   "Addr2:"
         Height          =   255
         Index           =   3
         Left            =   120
         TabIndex        =   8
         Top             =   1320
         Width           =   735
      End
      Begin VB.Label Label1 
         Caption         =   "Addr1:"
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   7
         Top             =   960
         Width           =   735
      End
      Begin VB.Label Label1 
         Caption         =   "Code:"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   6
         Top             =   600
         Width           =   735
      End
      Begin VB.Label Label1 
         Caption         =   "Name:"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   5
         Top             =   240
         Width           =   735
      End
   End
End
Attribute VB_Name = "BankView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'BankView.ctl - Copyright (C) 1997 Microsoft Corporation
'             - All rights reserved.
'Date         - 2/10/97
'Author       - Fred Pace
'Purpose      - BankView Control Palette Sample ActiveX Control

Option Explicit

' Frame Control Constants
Const icBank = 0
Const icAcct = 1

' Bank Control Constants
Const icBankName = 0
Const icBankCode = 1
Const icAddress1 = 2
Const icAddress2 = 3
Const icCity = 4
Const icNetValue = 5

' Bank Command Buttons
Const icBankAdd = 0
Const icBankSave = 1
Const icBankDelete = 2

' Navigation Buttons
Const icNavFirst = 0
Const icNavPre = 1
Const icNavNext = 2
Const icNavLast = 3

' Account Control Constants
Const icNumber = 0
Const icBalance = 1
Const icDeposit = 2
Const icWithdrawal = 3

' Bank Command Buttons
Const icAcctDeposit = 0
Const icAcctWithdrawal = 1
Const icAcctAdd = 2
Const icAcctSave = 3
Const icAcctDelete = 4

' Navigation Types
Enum iStyle
    [UserNavigate]
    [CodeNavigate]
End Enum

'Property Variables:
Private m_oAdmin        As CAdmin
Private m_iStyle        As iStyle
Private m_lBankCount    As Long
Private m_lCounter      As Long
Private m_sDataSrc      As String

Public Function Init(Optional sDBName As String) As Boolean
Dim sTemp() As String
Dim iRow    As Integer

On Error Resume Next
If Len(Trim$(sDBName)) Then m_sDataSrc = sDBName

If Len(Trim$(m_sDataSrc)) Then
    Set m_oAdmin = New CAdmin
    If m_oAdmin.Init(m_sDataSrc) Then
        m_oAdmin.FillListBanks
        If m_oAdmin.ExecFillArray("SELECT Desc, PKId FROM tbBankType", sTemp()) Then
            For iRow = LBound(sTemp, 2) To UBound(sTemp, 2)
                lstBankType.AddItem sTemp(0, iRow)
                lstBankType.ItemData(lstBankType.NewIndex) = CInt(sTemp(1, iRow))
            Next iRow
        End If
        If m_oAdmin.ExecFillArray("SELECT Desc, PKId FROM tbAccountType", sTemp()) Then
            For iRow = LBound(sTemp, 2) To UBound(sTemp, 2)
                lstAcctType.AddItem sTemp(0, iRow)
                lstAcctType.ItemData(lstAcctType.NewIndex) = CInt(sTemp(1, iRow))
            Next iRow
        End If
        If m_oAdmin.Banks.Count Then
            m_lBankCount = m_oAdmin.Banks.Count
            m_lCounter = 1
            DisplayBank
        End If
        Init = True
    End If
End If
End Function

Public Sub MoveFirst()
If m_lCounter > 1 Then
    m_lCounter = 1
    DisplayBank
End If
End Sub

Public Sub MoveNext()
If m_lCounter < m_lBankCount Then
    m_lCounter = m_lCounter + 1
    DisplayBank
End If
End Sub

Public Sub MovePrevious()
If m_lCounter > 1 Then
    m_lCounter = m_lCounter - 1
    DisplayBank
End If
End Sub

Public Sub MoveLast()
If m_lCounter < m_lBankCount Then
    m_lCounter = m_lBankCount
    DisplayBank
End If
End Sub

Private Sub DisplayBank()
Dim oBank As CBank
Dim oAcct As CAccount

Clear
If (m_lCounter > 0) And (m_lCounter <= m_oAdmin.Banks.Count) Then
    Set oBank = m_oAdmin.Banks(m_lCounter)
    With oBank
        txtBank(icBankName) = .Name
        txtBank(icBankCode) = .Code
        txtBank(icAddress1) = .Address1
        txtBank(icAddress2) = .Address2
        txtBank(icCity) = .City
        lblNetValue = "Net Acct Value: " & Format$(NetValue, "Currency")
        FindItem lstBankType, .TypeId
        
        For Each oAcct In .Accounts
            lstAcct.AddItem Trim$(oAcct.Number) & " " & Format$(oAcct.Balance, "Currency")
            lstAcct.ItemData(lstAcct.NewIndex) = oAcct.PKId
        Next oAcct
        If lstAcct.ListCount Then lstAcct.ListIndex = 0
    End With
End If
End Sub

Private Sub DisplayAcct()
Dim oBank As CBank
Dim oAcct As CAccount
If (m_lCounter > 0) And (m_lCounter <= m_oAdmin.Banks.Count) Then
    Set oBank = m_oAdmin.Banks(m_lCounter)
    If lstAcct.ListIndex <> -1 Then
        Set oAcct = oBank.Accounts("Id=" & Trim$(CStr(lstAcct.ItemData(lstAcct.ListIndex))))
        With oAcct
            FindItem lstAcctType, .TypeId
            txtAcct(icNumber) = .Number
            lblBalance = "Balance: " & Format$(.Balance, "Currency")
        End With
    End If
End If
End Sub

Public Sub AddBank()
Dim oBank As CBank

On Error Resume Next
txtBank(icBankName).SetFocus
   
Set oBank = New CBank
With oBank
    .Name = txtBank(icBankName)
    .Code = txtBank(icBankCode)
    .Address1 = txtBank(icAddress1)
    .Address2 = txtBank(icAddress2)
    .City = txtBank(icCity)
    .TypeId = lstBankType.ItemData(lstBankType.ListIndex)
End With
If m_oAdmin.Insert(oBank:=oBank) Then
    MsgBox "Successfully inserted bank. [" & Trim$(txtBank(icBankName)) & "]", vbOKOnly, "Insert Successful"
Else
    MsgBox "Failed to insert bank. [" & Trim$(txtBank(icBankName)) & "]", vbOKOnly, "Insert Failed"
End If
m_oAdmin.FillListBanks
If m_oAdmin.Banks.Count Then
    m_lBankCount = m_oAdmin.Banks.Count
    m_lCounter = m_lBankCount
    DisplayBank
End If
End Sub

Public Sub RemoveBank()
Dim oBank As CBank

On Error Resume Next
txtBank(icBankName).SetFocus

If (m_lCounter > 0) And (m_lCounter <= m_oAdmin.Banks.Count) Then
    Set oBank = m_oAdmin.Banks(m_lCounter)
    If m_oAdmin.Delete(oBank:=oBank) Then
        MsgBox "Successfully deleted bank. [" & Trim$(txtBank(icBankName)) & "]", vbOKOnly, "Delete Successful"
    Else
        MsgBox "Failed to delete bank. [" & Trim$(txtBank(icBankName)) & "]", vbOKOnly, "Delete Failed"
    End If
    m_oAdmin.FillListBanks
    If m_oAdmin.Banks.Count Then
        m_lBankCount = m_oAdmin.Banks.Count
        m_lCounter = 1
        DisplayBank
    End If
End If
End Sub

Public Sub SaveBank()
Dim oBank As CBank
Dim lPrev As Long

On Error Resume Next
txtBank(icBankName).SetFocus
   
If (m_lCounter > 0) And (m_lCounter <= m_oAdmin.Banks.Count) Then
    lPrev = m_lCounter
    Set oBank = m_oAdmin.Banks(m_lCounter)
    With oBank
        .Name = txtBank(icBankName)
        .Code = txtBank(icBankCode)
        .Address1 = txtBank(icAddress1)
        .Address2 = txtBank(icAddress2)
        .City = txtBank(icCity)
        .TypeId = lstBankType.ItemData(lstBankType.ListIndex)
    End With
    If m_oAdmin.Update(oBank:=oBank) Then
        MsgBox "Successfully updated bank. [" & Trim$(txtBank(icBankName)) & "]", vbOKOnly, "Update Successful"
    Else
        MsgBox "Failed to update bank. [" & Trim$(txtBank(icBankName)) & "]", vbOKOnly, "Update Failed"
    End If
    m_oAdmin.FillListBanks
    If m_oAdmin.Banks.Count Then
        m_lBankCount = m_oAdmin.Banks.Count
        m_lCounter = lPrev
        DisplayBank
    End If
End If
End Sub

Public Sub AddAcct()
Dim oBank As CBank
Dim oAcct As CAccount

On Error Resume Next
txtBank(icBankName).SetFocus
   
If (m_lCounter > 0) And (m_lCounter <= m_oAdmin.Banks.Count) Then
    Set oBank = m_oAdmin.Banks(m_lCounter)
    Set oAcct = New CAccount
    With oAcct
        .Number = txtAcct(icNumber)
        .TypeId = lstAcctType.ItemData(lstAcctType.ListIndex)
        Set .Bank = oBank
    End With
    If m_oAdmin.Insert(oAccount:=oAcct) Then
        MsgBox "Successfully inserted account. [" & Trim$(txtAcct(icNumber)) & "]", vbOKOnly, "Insert Successful"
    Else
        MsgBox "Failed to insert account. [" & Trim$(txtAcct(icNumber)) & "]", vbOKOnly, "Insert Failed"
    End If
    m_oAdmin.FillListBanks
    If m_oAdmin.Banks.Count Then
        m_lBankCount = m_oAdmin.Banks.Count
        DisplayBank
    End If
End If
End Sub

Public Sub RemoveAcct()
Dim oBank As CBank
Dim oAcct As CAccount

On Error Resume Next
txtBank(icBankName).SetFocus

If (m_lCounter > 0) And (m_lCounter <= m_oAdmin.Banks.Count) Then
    Set oBank = m_oAdmin.Banks(m_lCounter)
    If lstAcct.ListIndex <> -1 Then  'Nothing selected
        Set oAcct = oBank.Accounts("Id=" & Trim$(CStr(lstAcct.ItemData(lstAcct.ListIndex))))
        If m_oAdmin.Delete(oAccount:=oAcct) Then
            MsgBox "Successfully deleted account. [" & Trim$(txtAcct(icNumber)) & "]", vbOKOnly, "Delete Successful"
        Else
            MsgBox "Failed to delete account. [" & Trim$(txtAcct(icNumber)) & "]", vbOKOnly, "Delete Failed"
        End If
        m_oAdmin.FillListBanks
        If m_oAdmin.Banks.Count Then
            m_lBankCount = m_oAdmin.Banks.Count
            DisplayBank
        End If
    End If
End If
End Sub

Public Sub SaveAcct()
Dim oBank As CBank
Dim oAcct As CAccount

On Error Resume Next
txtBank(icBankName).SetFocus
   
If (m_lCounter > 0) And (m_lCounter <= m_oAdmin.Banks.Count) Then
    Set oBank = m_oAdmin.Banks(m_lCounter)
    If lstAcct.ListIndex <> -1 Then
        Set oAcct = oBank.Accounts("Id=" & Trim$(CStr(lstAcct.ItemData(lstAcct.ListIndex))))
        With oAcct
            .Number = txtAcct(icNumber)
            .TypeId = lstAcctType.ItemData(lstAcctType.ListIndex)
        End With
        If m_oAdmin.Update(oAccount:=oAcct) Then
            MsgBox "Successfully updated account. [" & Trim$(txtAcct(icNumber)) & "]", vbOKOnly, "Insert Successful"
        Else
            MsgBox "Failed to update account. [" & Trim$(txtAcct(icNumber)) & "]", vbOKOnly, "Insert Failed"
        End If
        m_oAdmin.FillListBanks
        If m_oAdmin.Banks.Count Then
            m_lBankCount = m_oAdmin.Banks.Count
            DisplayBank
        End If
    End If
End If
End Sub

Private Sub Deposit()
If Val(txtAcct(icDeposit)) > 0 Then
    If (m_lCounter > 0) And (m_lCounter <= m_oAdmin.Banks.Count) Then
        If lstAcct.ListIndex <> -1 Then
            If UpdateAcctBalance(Val(txtAcct(icDeposit))) Then
                MsgBox "Successfully updated balance. [" & Trim$(txtAcct(icNumber)) & "]", vbOKOnly, "Update Successful"
            Else
                MsgBox "Failed to update balance. [" & Trim$(txtAcct(icNumber)) & "]", vbOKOnly, "Update Failed"
            End If
        End If
    End If
Else
    MsgBox "Amount must be greater than zero.", vbOKOnly, "Update Failed"
End If
txtAcct(icDeposit) = ""
End Sub

Private Sub Withdrawal()
If Val(txtAcct(icWithdrawal)) > 0 Then
    If (m_lCounter > 0) And (m_lCounter <= m_oAdmin.Banks.Count) Then
        If lstAcct.ListIndex <> -1 Then
            If UpdateAcctBalance(-Val(txtAcct(icWithdrawal))) Then
                MsgBox "Successfully updated balance. [" & Trim$(txtAcct(icNumber)) & "]", vbOKOnly, "Update Successful"
            Else
                MsgBox "Failed to update balance. [" & Trim$(txtAcct(icNumber)) & "]", vbOKOnly, "Update Failed"
            End If
        End If
    End If
Else
    MsgBox "Amount must be greater than zero.", vbOKOnly, "Update Failed"
End If
txtAcct(icWithdrawal) = ""
End Sub

Private Function UpdateAcctBalance(curAmount As Currency) As Boolean
Dim oBank As CBank
Dim oAcct As CAccount
Dim cParms As New Collection

On Error Resume Next
txtBank(icBankName).SetFocus

Set oBank = m_oAdmin.Banks(m_lCounter)
Set oAcct = oBank.Accounts("Id=" & Trim$(CStr(lstAcct.ItemData(lstAcct.ListIndex))))
Set cParms = New Collection
cParms.Add oAcct.Number, "[@Number]"
cParms.Add curAmount, "[@Amount]"
If m_oAdmin.ExecBoolean("pcUpd_AccountBalance", cParms) Then
    UpdateAcctBalance = True
Else
    UpdateAcctBalance = False
End If
m_oAdmin.FillListBanks
If m_oAdmin.Banks.Count Then
    m_lBankCount = m_oAdmin.Banks.Count
    DisplayBank
End If
End Function

Private Sub Clear()
txtBank(icBankName) = ""
txtBank(icBankCode) = ""
txtBank(icBankCode) = ""
txtBank(icAddress1) = ""
txtBank(icAddress2) = ""
txtBank(icCity) = ""
lstBankType.ListIndex = 0
lstAcct.Clear
txtAcct(icNumber) = ""
txtAcct(icDeposit) = ""
txtAcct(icWithdrawal) = ""
lblNetValue = "Net Acct Value: $0.00"
lblBalance = "Balance: $0.00"
lstAcctType.ListIndex = 0
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

Public Property Get NetValue()
Dim oBank As CBank
Dim oAcct As CAccount
Dim cAccumulate As Currency

Set oBank = m_oAdmin.Banks(m_lCounter)
For Each oAcct In oBank.Accounts
    cAccumulate = cAccumulate + oAcct.Balance
Next oAcct
NetValue = cAccumulate
End Property

Public Property Get Style() As iStyle
Style = m_iStyle
End Property

Public Property Let Style(ByVal New_Style As iStyle)
m_iStyle = New_Style
UserControl_Resize
PropertyChanged "Style"
End Property

Private Sub cmdAcct_Click(Index As Integer)
Select Case Index
Case icAcctDeposit
    Deposit
Case icAcctWithdrawal
    Withdrawal
Case icAcctAdd
    AddAcct
Case icAcctDelete
    RemoveAcct
Case icAcctSave
    SaveAcct
Case Else
    ' uh-oh
End Select
End Sub

Private Sub cmdBank_Click(Index As Integer)
Select Case Index
Case icBankAdd
    AddBank
Case icBankDelete
    RemoveBank
Case icBankSave
    SaveBank
Case Else
    ' Uh-oh
End Select
End Sub

Private Sub cmdNav_Click(Index As Integer)
On Error Resume Next
txtBank(icBankName).SetFocus
Select Case Index
Case icNavFirst
    MoveFirst
Case icNavPre
    MovePrevious
Case icNavNext
    MoveNext
Case icNavLast
    MoveLast
Case Else
    'uh-oh
End Select
End Sub

Private Sub lstAcct_Click()
If lstAcct.ListIndex <> -1 Then DisplayAcct
End Sub

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

Private Sub UserControl_InitProperties()
Set Font = Ambient.Font
End Sub

Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
m_iStyle = PropBag.ReadProperty("Style", [UserNavigate])
UserControl.BackColor = PropBag.ReadProperty("BackColor", &H8000000F)
Set Font = PropBag.ReadProperty("Font", Ambient.Font)
UserControl.ForeColor = PropBag.ReadProperty("ForeColor", &H80000012)
End Sub

Private Sub UserControl_Resize()
Dim i As Integer
Width = 7550
If m_iStyle = [UserNavigate] Then
    frBank(icBank).Height = 4815
    frBank(icAcct).Height = 4815
    For i = 0 To 3
        cmdNav(i).Visible = True
    Next i
    For i = 0 To 2
        cmdBank(i).Visible = True
    Next i
    For i = 2 To 4
        cmdAcct(i).Visible = True
    Next i
Else
    frBank(icBank).Height = 4215
    frBank(icAcct).Height = 4215
    For i = 0 To 3
        cmdNav(i).Visible = False
    Next i
    For i = 0 To 2
        cmdBank(i).Visible = False
    Next i
    For i = 2 To 4
        cmdAcct(i).Visible = False
    Next i
End If
Height = frBank(icBank).Height + 20
End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
Call PropBag.WriteProperty("Style", m_iStyle, [UserNavigate])
Call PropBag.WriteProperty("BackColor", UserControl.BackColor, &H8000000F)
Call PropBag.WriteProperty("Font", Font, Ambient.Font)
Call PropBag.WriteProperty("ForeColor", UserControl.ForeColor, &H80000012)
End Sub

