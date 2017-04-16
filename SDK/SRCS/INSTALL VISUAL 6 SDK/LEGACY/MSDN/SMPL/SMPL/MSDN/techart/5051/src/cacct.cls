VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CAccount"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private m_oAdmin            As CAdmin
Private m_cBalance          As Currency
Private m_lPKId             As Long
Private m_oBank             As CBank
Private m_sNumber             As String
Private m_lTypeId           As Long

Private Sub Clear()
On Error Resume Next
m_lTypeId = 0
m_sNumber = ""
m_cBalance = 0
Set m_oBank = Nothing
End Sub

'Refresh
'Purpose     - do look ups and fill in all object properties
Public Sub Refresh()
Dim cData       As Collection
Dim sQry        As String
Dim oBank       As CBank

On Error Resume Next
'Nothing to do without m_lPKId
If ((CBool(m_lPKId)) And (Not m_oAdmin Is Nothing)) Then
    'Set up SQL for Bank query
    sQry = "SELECT Number, PKId, AccountTypeId, Balance FROM tbAccount WHERE PKId = " & CStr(m_lPKId)
    Clear
    'Initialize list for Bank query data
    Set cData = New Collection
    'If Bank query fills list, populate member variables
    If m_oAdmin.FillCollection(sQry, cData) Then
        'Assign member variables
        If Not IsNull(cData("AccountTypeId")) Then m_lTypeId = cData("AccountTypeId")
        If Not IsNull(cData("Balance")) Then m_cBalance = cData("Balance")
        If Not IsNull(cData("Number")) Then m_sNumber = cData("Number")
    End If
End If
End Sub

Public Property Get TypeId() As Long
On Error Resume Next
TypeId = m_lTypeId
End Property

Public Property Let TypeId(ByVal lTypeId As Long)
m_lTypeId = lTypeId
End Property

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

Public Property Get Bank() As CBank
On Error Resume Next
Set Bank = m_oBank
End Property

Public Property Set Bank(oNewBank As CBank)
On Error Resume Next
Set m_oBank = oNewBank
End Property

Public Property Get Balance() As Currency
On Error Resume Next
Balance = m_cBalance
End Property

Public Property Get Number() As String
On Error Resume Next
Number = m_sNumber
End Property

Public Property Let Number(ByVal sNumber As String)
m_sNumber = sNumber
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


