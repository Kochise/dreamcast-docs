VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CBank"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'CBank.cls   - Copyright (C) 1996 Microsoft Corporation
'            - All rights reserved.
'Date        - 2/5/97
'Authors     - Ken Bergmann

Option Explicit

Private m_cAccounts         As Collection
Private m_oAdmin            As CAdmin
Private m_lPKId             As Long
Private m_sAddress1         As String
Private m_sAddress2         As String
Private m_sCity             As String
Private m_sCode             As String
Private m_sName             As String
Private m_lTypeId           As Long

Private Sub Clear()
On Error Resume Next
m_sAddress1 = ""
m_sAddress2 = ""
m_sCity = ""
m_sCode = ""
m_sName = ""
m_lTypeId = 0
Set m_cAccounts = Nothing
End Sub

'Refresh
'Purpose     - do look ups and fill in all object properties
Public Sub Refresh()
Dim oAcct       As CAccount
Dim cData       As Collection
Dim iIndex      As Integer
Dim lIndexPos   As Long
Dim sQry        As String
Dim sTemp()     As String

On Error Resume Next
'Nothing to do without m_lPKId
If ((CBool(m_lPKId)) And (Not m_oAdmin Is Nothing)) Then
    'Set up SQL for Bank query
    sQry = "SELECT * FROM tbBank WHERE PKId = " & CStr(m_lPKId)
    Clear
    'Initialize list for Bank query data
    Set cData = New Collection
    'If Bank query fills list, populate member variables
    If m_oAdmin.FillCollection(sQry, cData) Then
        'Assign member variables
        If Not IsNull(cData("Address1")) Then m_sAddress1 = cData("Address1")
        If Not IsNull(cData("Address2")) Then m_sAddress2 = cData("Address2")
        If Not IsNull(cData("City")) Then m_sCity = cData("City")
        If Not IsNull(cData("Code")) Then m_sCode = cData("Code")
        If Not IsNull(cData("Name")) Then m_sName = cData("Name")
        If Not IsNull(cData("BankTypeId")) Then m_lTypeId = cData("BankTypeId")
        'Initialize Accounts list
        Set m_cAccounts = New Collection
        'Set up SQL for Accounts query
        sQry = "SELECT Number, PKId FROM tbAccount WHERE BankId = " & CStr(m_lPKId)
        'If Accounts query fills list, populate Accounts list
        If m_oAdmin.ExecFillArray(sQry, sTemp()) Then
            For iIndex = LBound(sTemp, 2) To UBound(sTemp, 2)
                Set oAcct = New CAccount
                oAcct.PKId = CLng(sTemp(1, iIndex))
                Set oAcct.Admin = m_oAdmin
                oAcct.Refresh
                Set oAcct.Bank = Me
                m_cAccounts.Add oAcct, "Id=" & Trim$(CStr(oAcct.PKId))
            Next iIndex
        End If
    End If
End If
End Sub

'Term
'Purpose     - Terminate an object, release all object references
Public Sub Term()
On Error Resume Next
Clear
Set m_oAdmin = Nothing
End Sub

Public Property Set Admin(oNewAdmin As CAdmin)
On Error Resume Next
Set m_oAdmin = oNewAdmin
End Property

Public Property Get Address1() As String
On Error Resume Next
Address1 = m_sAddress1
End Property

Public Property Let Address1(ByVal sAddress1 As String)
m_sAddress1 = sAddress1
End Property

Public Property Get Address2() As String
On Error Resume Next
Address2 = m_sAddress2
End Property

Public Property Let Address2(ByVal sAddress2 As String)
m_sAddress2 = sAddress2
End Property

Public Property Get City() As String
On Error Resume Next
City = m_sCity
End Property

Public Property Let City(ByVal sCity As String)
m_sCity = sCity
End Property

Public Property Get Code() As String
On Error Resume Next
Code = m_sCode
End Property

Public Property Let Code(ByVal sCode As String)
m_sCode = sCode
End Property

Public Property Get TypeId() As Long
On Error Resume Next
TypeId = m_lTypeId
End Property

Public Property Let TypeId(ByVal lTypeId As Long)
m_lTypeId = lTypeId
End Property

Property Get Accounts() As Collection
On Error Resume Next
Set Accounts = m_cAccounts
End Property

Public Property Get Name() As String
On Error Resume Next
Name = m_sName
End Property

Public Property Let Name(ByVal sName As String)
m_sName = sName
End Property

Public Property Get PKId() As Long
On Error Resume Next
PKId = m_lPKId
End Property

Public Property Let PKId(ByVal lPKId As Long)
On Error Resume Next
m_lPKId = lPKId
End Property

Private Sub Class_Terminate()
On Error Resume Next
Term
End Sub

