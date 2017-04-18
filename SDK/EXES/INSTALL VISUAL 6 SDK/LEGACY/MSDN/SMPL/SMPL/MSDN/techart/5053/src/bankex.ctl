VERSION 5.00
Begin VB.UserControl BankEx 
   BackStyle       =   0  'Transparent
   ClientHeight    =   3180
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   6690
   FontTransparent =   0   'False
   LockControls    =   -1  'True
   PropertyPages   =   "bankex.ctx":0000
   ScaleHeight     =   3180
   ScaleWidth      =   6690
   Begin VB.Frame frameDetails 
      Caption         =   "Bank"
      Height          =   3120
      Left            =   15
      TabIndex        =   0
      Top             =   0
      Width           =   6630
      Begin VB.PictureBox pnlBottom 
         Height          =   330
         Left            =   90
         ScaleHeight     =   270
         ScaleWidth      =   6390
         TabIndex        =   23
         Top             =   2715
         Width           =   6450
         Begin VB.CommandButton btFirst 
            Height          =   270
            Left            =   0
            Picture         =   "bankex.ctx":0035
            Style           =   1  'Graphical
            TabIndex        =   30
            TabStop         =   0   'False
            Top             =   0
            Width           =   315
         End
         Begin VB.CommandButton btPrev 
            Height          =   270
            Left            =   315
            Picture         =   "bankex.ctx":011F
            Style           =   1  'Graphical
            TabIndex        =   29
            TabStop         =   0   'False
            Top             =   0
            Width           =   315
         End
         Begin VB.CommandButton btNext 
            Height          =   270
            Left            =   5760
            Picture         =   "bankex.ctx":0209
            Style           =   1  'Graphical
            TabIndex        =   28
            TabStop         =   0   'False
            Top             =   0
            Width           =   315
         End
         Begin VB.CommandButton btLast 
            Height          =   270
            Left            =   6075
            Picture         =   "bankex.ctx":02F3
            Style           =   1  'Graphical
            TabIndex        =   27
            TabStop         =   0   'False
            Top             =   0
            Width           =   315
         End
         Begin VB.CommandButton btInsBank 
            Caption         =   "Create"
            Height          =   270
            Left            =   630
            TabIndex        =   26
            Top             =   0
            Width           =   1710
         End
         Begin VB.CommandButton btUpdBank 
            Caption         =   "Save"
            Height          =   270
            Left            =   2340
            TabIndex        =   25
            Top             =   0
            Width           =   1710
         End
         Begin VB.CommandButton btDelBank 
            Caption         =   "Delete"
            Height          =   270
            Left            =   4050
            TabIndex        =   24
            Top             =   0
            Width           =   1710
         End
      End
      Begin VB.Frame frameAccts 
         Caption         =   "Accounts"
         Height          =   2505
         Left            =   3270
         TabIndex        =   13
         Top             =   135
         Width           =   3270
         Begin VB.ComboBox cmbAccountType 
            Height          =   315
            Left            =   750
            Sorted          =   -1  'True
            Style           =   2  'Dropdown List
            TabIndex        =   19
            Top             =   1440
            Width           =   2415
         End
         Begin VB.TextBox txtNumber 
            Height          =   285
            Left            =   750
            TabIndex        =   18
            Top             =   1110
            Width           =   2415
         End
         Begin VB.ListBox lstAccounts 
            Height          =   825
            IntegralHeight  =   0   'False
            Left            =   105
            Sorted          =   -1  'True
            TabIndex        =   17
            Top             =   225
            Width           =   3060
         End
         Begin VB.CommandButton btInsAcct 
            Caption         =   "Create"
            Height          =   315
            Left            =   90
            TabIndex        =   16
            Top             =   2085
            Width           =   1020
         End
         Begin VB.CommandButton btUpdAcct 
            Caption         =   "Save"
            Height          =   315
            Left            =   1125
            TabIndex        =   15
            Top             =   2085
            Width           =   1020
         End
         Begin VB.CommandButton btDelAcct 
            Caption         =   "Delete"
            Height          =   315
            Left            =   2160
            TabIndex        =   14
            Top             =   2085
            Width           =   1020
         End
         Begin VB.Label lblBank 
            Appearance      =   0  'Flat
            AutoSize        =   -1  'True
            BackColor       =   &H80000005&
            BackStyle       =   0  'Transparent
            Caption         =   "Number"
            ForeColor       =   &H80000008&
            Height          =   195
            Index           =   6
            Left            =   150
            TabIndex        =   22
            Top             =   1155
            Width           =   555
         End
         Begin VB.Label lblBank 
            Appearance      =   0  'Flat
            AutoSize        =   -1  'True
            BackColor       =   &H80000005&
            BackStyle       =   0  'Transparent
            Caption         =   "Type"
            ForeColor       =   &H80000008&
            Height          =   195
            Index           =   8
            Left            =   330
            TabIndex        =   21
            Top             =   1500
            Width           =   360
         End
         Begin VB.Label lblBalance 
            Alignment       =   2  'Center
            Appearance      =   0  'Flat
            BackColor       =   &H80000005&
            BackStyle       =   0  'Transparent
            Caption         =   "Balance: $0.0"
            ForeColor       =   &H80000008&
            Height          =   225
            Left            =   90
            TabIndex        =   20
            Top             =   1815
            Width           =   3090
         End
      End
      Begin VB.Frame frameAddress 
         Caption         =   "Address"
         Height          =   1335
         Left            =   90
         TabIndex        =   7
         Top             =   1305
         Width           =   3100
         Begin VB.TextBox txtAdd1 
            Height          =   285
            Left            =   555
            TabIndex        =   10
            Top             =   240
            Width           =   2445
         End
         Begin VB.TextBox txtAdd2 
            Height          =   285
            Left            =   555
            TabIndex        =   9
            Top             =   570
            Width           =   2445
         End
         Begin VB.TextBox txtCity 
            Height          =   285
            Left            =   555
            TabIndex        =   8
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
            TabIndex        =   12
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
            TabIndex        =   11
            Top             =   270
            Width           =   420
         End
      End
      Begin VB.ComboBox cmbBankType 
         Height          =   315
         Left            =   555
         Sorted          =   -1  'True
         Style           =   2  'Dropdown List
         TabIndex        =   3
         Top             =   945
         Width           =   2625
      End
      Begin VB.TextBox txtName 
         Height          =   285
         Left            =   555
         TabIndex        =   2
         Top             =   225
         Width           =   2625
      End
      Begin VB.TextBox txtCode 
         Height          =   285
         Left            =   555
         TabIndex        =   1
         Top             =   540
         Width           =   2625
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
         TabIndex        =   6
         Top             =   990
         Width           =   360
      End
      Begin VB.Label lblBank 
         Appearance      =   0  'Flat
         AutoSize        =   -1  'True
         BackColor       =   &H80000005&
         BackStyle       =   0  'Transparent
         Caption         =   "Code"
         ForeColor       =   &H80000008&
         Height          =   195
         Index           =   1
         Left            =   120
         TabIndex        =   5
         Top             =   570
         Width           =   375
      End
      Begin VB.Label lblBank 
         Appearance      =   0  'Flat
         AutoSize        =   -1  'True
         BackColor       =   &H80000005&
         BackStyle       =   0  'Transparent
         Caption         =   "Name"
         ForeColor       =   &H80000008&
         Height          =   195
         Index           =   0
         Left            =   90
         TabIndex        =   4
         Top             =   255
         Width           =   420
      End
   End
End
Attribute VB_Name = "BankEx"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "PropPageWizardRun" ,"Yes"
Option Explicit

Enum bcStyles
    [User Navigate] = False
    [Code Navigate] = True
End Enum

'Property Variables:
Private m_Style     As bcStyles
Private m_lCurrent  As Long
Private m_lTotal    As Long

Private m_oAdmin    As CAdmin
Private m_sDataSrc  As String

'Event Declarations:
Event OnMoveEnter(bCancel As Boolean)
Event OnMoveExit()

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
        If m_oAdmin.ExecFillArray("SELECT Desc, PKId FROM tbAccountType", sTemp()) Then
            For iRow = LBound(sTemp, 2) To UBound(sTemp, 2)
                cmbAccountType.AddItem sTemp(0, iRow)
                cmbAccountType.ItemData(cmbAccountType.NewIndex) = CInt(sTemp(1, iRow))
            Next iRow
        End If
        If m_oAdmin.Banks.Count Then
            m_lTotal = m_oAdmin.Banks.Count
            m_lCurrent = 1
            DisplayBank
        End If
        Init = True
    End If
End If
End Function

Private Sub Clear()
txtName = ""
txtCode = ""
txtAdd1 = ""
txtAdd2 = ""
txtCity = ""
cmbBankType.ListIndex = 0
lstAccounts.Clear
txtNumber = ""
lblBalance = ""
cmbAccountType.ListIndex = 0
frameDetails.Caption = "No Current Bank"
End Sub

Private Sub DisplayBank()
Dim oBank As CBank
Dim oAcct As CAccount

Clear
If (m_lCurrent > 0) And (m_lCurrent <= m_oAdmin.Banks.Count) Then
    Set oBank = m_oAdmin.Banks(m_lCurrent)
    With oBank
        frameDetails.Caption = "Bank - " & .Name
        txtName = .Name
        txtCode = .Code
        txtAdd1 = .Address1
        txtAdd2 = .Address2
        txtCity = .City
        FindItem cmbBankType, .TypeId
        
        For Each oAcct In .Accounts
            lstAccounts.AddItem Trim$(oAcct.Number) & " " & Format$(oAcct.Balance, "Currency")
            lstAccounts.ItemData(lstAccounts.NewIndex) = oAcct.PKId
        Next oAcct
        If lstAccounts.ListCount Then lstAccounts.ListIndex = 0
    End With
End If
End Sub

Private Sub DisplayAccount()
Dim oBank As CBank
Dim oAcct As CAccount
If (m_lCurrent > 0) And (m_lCurrent <= m_oAdmin.Banks.Count) Then
    Set oBank = m_oAdmin.Banks(m_lCurrent)
    If lstAccounts.ListIndex <> -1 Then
        Set oAcct = oBank.Accounts("Id=" & Trim$(CStr(lstAccounts.ItemData(lstAccounts.ListIndex))))
        With oAcct
            FindItem cmbAccountType, .TypeId
            txtNumber = .Number
            lblBalance = "Balance:" & Format$(.Balance, "Currency")
        End With
    End If
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
Enabled = frameDetails.Enabled
End Property

Public Property Let Enabled(ByVal New_Enabled As Boolean)
frameDetails.Enabled = New_Enabled
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

Public Property Get Style() As bcStyles
Style = m_Style
End Property

Public Property Let Style(ByVal New_Style As bcStyles)
m_Style = New_Style
UserControl_Resize
PropertyChanged "Style"
End Property

Public Sub Refresh()
m_oAdmin.FillListBanks
If m_oAdmin.Banks.Count Then
    m_lTotal = m_oAdmin.Banks.Count
    m_lCurrent = 1
    DisplayBank
End If
End Sub

Public Sub MoveFirst()
If m_lTotal Then
    Dim bCancel As Boolean
    RaiseEvent OnMoveEnter(bCancel)
    If bCancel Then Exit Sub
    m_lCurrent = 1
    DisplayBank
    RaiseEvent OnMoveExit
End If
End Sub

Public Sub MoveNext()
If m_lCurrent < m_lTotal Then
    Dim bCancel As Boolean
    RaiseEvent OnMoveEnter(bCancel)
    If bCancel Then Exit Sub
    m_lCurrent = m_lCurrent + 1
    DisplayBank
    RaiseEvent OnMoveExit
End If
End Sub

Public Sub MovePrevious()
If m_lCurrent > 1 Then
    Dim bCancel As Boolean
    RaiseEvent OnMoveEnter(bCancel)
    If bCancel Then Exit Sub
    m_lCurrent = m_lCurrent - 1
    DisplayBank
    RaiseEvent OnMoveExit
End If
End Sub

Public Sub MoveLast()
If m_lTotal Then
    Dim bCancel As Boolean
    RaiseEvent OnMoveEnter(bCancel)
    If bCancel Then Exit Sub
    m_lCurrent = m_lTotal
    DisplayBank
    RaiseEvent OnMoveExit
End If
End Sub

Public Function DeleteAccount() As Boolean
Dim oBank As CBank
Dim oAcct As CAccount

On Error Resume Next
If (m_lCurrent > 0) And (m_lCurrent <= m_oAdmin.Banks.Count) Then
    Set oBank = m_oAdmin.Banks(m_lCurrent)
    If lstAccounts.ListIndex <> -1 Then
        Set oAcct = oBank.Accounts("Id=" & Trim$(CStr(lstAccounts.ItemData(lstAccounts.ListIndex))))
        DeleteAccount = m_oAdmin.Delete(oAccount:=oAcct)
        m_oAdmin.FillListBanks
        If m_oAdmin.Banks.Count Then
            m_lTotal = m_oAdmin.Banks.Count
            DisplayBank
        End If
    End If
End If
End Function

Private Sub btDelAcct_Click()
On Error Resume Next
txtName.SetFocus
frameDetails.Enabled = False
If DeleteAccount() Then
    If m_Style = [User Navigate] Then MsgBox "Successfully deleted account. [" & Trim$(txtNumber) & "]", vbOKOnly, "Delete Successful"
Else
    If m_Style = [User Navigate] Then MsgBox "Failed to delete account." & Trim$(txtNumber) & "]", vbOKOnly, "Delete Failed"
End If
frameDetails.Enabled = True
End Sub

Public Function DeleteBank() As Boolean
Dim oBank As CBank

On Error Resume Next
If (m_lCurrent > 0) And (m_lCurrent <= m_oAdmin.Banks.Count) Then
    Set oBank = m_oAdmin.Banks(m_lCurrent)
    DeleteBank = m_oAdmin.Delete(oBank:=oBank)
    m_oAdmin.FillListBanks
    If m_oAdmin.Banks.Count Then
        m_lTotal = m_oAdmin.Banks.Count
        m_lCurrent = 1
        DisplayBank
    End If
End If
End Function

Private Sub btDelBank_Click()
On Error Resume Next
txtName.SetFocus
frameDetails.Enabled = False
If DeleteBank() Then
    If m_Style = [User Navigate] Then MsgBox "Successfully deleted bank. [" & Trim$(txtName) & "]", vbOKOnly, "Delete Successful"
Else
    If m_Style = [User Navigate] Then MsgBox "Failed to delete bank. [" & Trim$(txtName) & "]", vbOKOnly, "Delete Failed"
End If
frameDetails.Enabled = True
End Sub

Private Sub btFirst_Click()
On Error Resume Next
txtName.SetFocus
MoveFirst
End Sub

Public Function InsertAccount() As Boolean
Dim oBank As CBank
Dim oAcct As CAccount

On Error Resume Next
If (m_lCurrent > 0) And (m_lCurrent <= m_oAdmin.Banks.Count) Then
    Set oBank = m_oAdmin.Banks(m_lCurrent)
    Set oAcct = New CAccount
    With oAcct
        .Number = txtNumber
        .TypeId = cmbAccountType.ItemData(cmbAccountType.ListIndex)
        Set .Bank = oBank
    End With
    InsertAccount = m_oAdmin.Insert(oAccount:=oAcct)
    m_oAdmin.FillListBanks
    If m_oAdmin.Banks.Count Then
        m_lTotal = m_oAdmin.Banks.Count
        DisplayBank
    End If
End If
End Function

Private Sub btInsAcct_Click()
On Error Resume Next
txtName.SetFocus
frameDetails.Enabled = False
If InsertAccount() Then
    If m_Style = [User Navigate] Then MsgBox "Successfully inserted account. [" & Trim$(txtNumber) & "]", vbOKOnly, "Insert Successful"
Else
    If m_Style = [User Navigate] Then MsgBox "Failed to insert account. [" & Trim$(txtNumber) & "]", vbOKOnly, "Insert Failed"
End If
frameDetails.Enabled = True
End Sub

Public Function InsertBank() As Boolean
Dim oBank As CBank

On Error Resume Next
Set oBank = New CBank
With oBank
    .Name = txtName
    .Code = txtCode
    .Address1 = txtAdd1
    .Address2 = txtAdd2
    .City = txtCity
    .TypeId = cmbBankType.ItemData(cmbBankType.ListIndex)
End With
InsertBank = m_oAdmin.Insert(oBank:=oBank)
m_oAdmin.FillListBanks
If m_oAdmin.Banks.Count Then
    m_lTotal = m_oAdmin.Banks.Count
    m_lCurrent = m_lTotal
    DisplayBank
End If
End Function

Private Sub btInsBank_Click()
On Error Resume Next
txtName.SetFocus
frameDetails.Enabled = False
If InsertBank() Then
    If m_Style = [User Navigate] Then MsgBox "Successfully inserted bank. [" & Trim$(txtName) & "]", vbOKOnly, "Insert Successful"
Else
    If m_Style = [User Navigate] Then MsgBox "Failed to insert bank. [" & Trim$(txtName) & "]", vbOKOnly, "Insert Failed"
End If
frameDetails.Enabled = True
End Sub

Private Sub btLast_Click()
On Error Resume Next
txtName.SetFocus
MoveLast
End Sub

Private Sub btNext_Click()
On Error Resume Next
txtName.SetFocus
MoveNext
End Sub

Private Sub btPrev_Click()
On Error Resume Next
txtName.SetFocus
MovePrevious
End Sub

Public Function UpdateAccount() As Boolean
Dim oBank As CBank
Dim oAcct As CAccount

On Error Resume Next
If (m_lCurrent > 0) And (m_lCurrent <= m_oAdmin.Banks.Count) Then
    Set oBank = m_oAdmin.Banks(m_lCurrent)
    If lstAccounts.ListIndex <> -1 Then
        Set oAcct = oBank.Accounts("Id=" & Trim$(CStr(lstAccounts.ItemData(lstAccounts.ListIndex))))
        With oAcct
            .Number = txtNumber
            .TypeId = cmbAccountType.ItemData(cmbAccountType.ListIndex)
        End With
        UpdateAccount = m_oAdmin.Update(oAccount:=oAcct)
        m_oAdmin.FillListBanks
        If m_oAdmin.Banks.Count Then
            m_lTotal = m_oAdmin.Banks.Count
            DisplayBank
        End If
    End If
End If
End Function

Private Sub btUpdAcct_Click()
On Error Resume Next
txtName.SetFocus
frameDetails.Enabled = False
If UpdateAccount() Then
    If m_Style = [User Navigate] Then MsgBox "Successfully updated account. [" & Trim$(txtNumber) & "]", vbOKOnly, "Insert Successful"
Else
    If m_Style = [User Navigate] Then MsgBox "Failed to update account. [" & Trim$(txtNumber) & "]", vbOKOnly, "Insert Failed"
End If
frameDetails.Enabled = True
End Sub

Public Function UpdateBank() As Boolean
Dim oBank As CBank
Dim lPrev As Long

On Error Resume Next
If (m_lCurrent > 0) And (m_lCurrent <= m_oAdmin.Banks.Count) Then
    lPrev = m_lCurrent
    Set oBank = m_oAdmin.Banks(m_lCurrent)
    With oBank
        .Name = txtName
        .Code = txtCode
        .Address1 = txtAdd1
        .Address2 = txtAdd2
        .City = txtCity
        .TypeId = cmbBankType.ItemData(cmbBankType.ListIndex)
    End With
    UpdateBank = m_oAdmin.Update(oBank:=oBank)
    m_oAdmin.FillListBanks
    If m_oAdmin.Banks.Count Then
        m_lTotal = m_oAdmin.Banks.Count
        m_lCurrent = lPrev
        DisplayBank
    End If
End If
End Function

Private Sub btUpdBank_Click()
On Error Resume Next
txtName.SetFocus
frameDetails.Enabled = False
If UpdateBank() Then
    If m_Style = [User Navigate] Then MsgBox "Successfully updated bank. [" & Trim$(txtName) & "]", vbOKOnly, "Update Successful"
Else
    If m_Style = [User Navigate] Then MsgBox "Failed to update bank. [" & Trim$(txtName) & "]", vbOKOnly, "Update Failed"
End If
frameDetails.Enabled = True
End Sub

Private Sub lstAccounts_Click()
If lstAccounts.ListIndex <> -1 Then DisplayAccount
End Sub

'Load property values from storage
Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
UserControl.BackColor = PropBag.ReadProperty("BackColor", &H8000000F)
UserControl.ForeColor = PropBag.ReadProperty("ForeColor", &H80000012)
frameDetails.Enabled = PropBag.ReadProperty("Enabled", True)
Set Font = PropBag.ReadProperty("Font", Ambient.Font)
m_Style = PropBag.ReadProperty("Style", [User Navigate])
m_sDataSrc = PropBag.ReadProperty("DataSource", "")
End Sub

Private Sub UserControl_Resize()
Width = frameDetails.Width + 10
If m_Style = [User Navigate] Then
    frameDetails.Height = pnlBottom.Top + pnlBottom.Height + 90
    pnlBottom.Visible = True
    btInsAcct.Visible = True
    btUpdAcct.Visible = True
    btDelAcct.Visible = True
Else
    frameDetails.Height = frameAddress.Top + frameAddress.Height + 90
    pnlBottom.Visible = False
    btInsAcct.Visible = False
    btUpdAcct.Visible = False
    btDelAcct.Visible = False
End If
Height = frameDetails.Height + 20
End Sub

'Write property values to storage
Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
Call PropBag.WriteProperty("BackColor", UserControl.BackColor, &H8000000F)
Call PropBag.WriteProperty("ForeColor", UserControl.ForeColor, &H80000012)
Call PropBag.WriteProperty("Enabled", frameDetails.Enabled, True)
Call PropBag.WriteProperty("Font", Font, Ambient.Font)
Call PropBag.WriteProperty("Style", m_Style, [User Navigate])
Call PropBag.WriteProperty("DataSource", m_sDataSrc, "")
End Sub

