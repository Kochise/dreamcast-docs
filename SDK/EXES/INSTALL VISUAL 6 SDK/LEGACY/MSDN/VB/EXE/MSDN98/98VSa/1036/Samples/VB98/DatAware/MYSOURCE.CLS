VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 1  'vbDataSource
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "MySource"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
Private rs As ADODB.Recordset

Private Sub Class_GetDataMember(DataMember As String, Data As Object)
    ' Affecte le Recordset à l'objet Data
    Set Data = rs
End Sub

Private Sub Class_Initialize()
    Dim strPath As String, strName As String
    Dim i As Integer
    
    ' Crée une instance du Recordset
    Set rs = New ADODB.Recordset
    
    ' Définit les propriétés du Recordset
    With rs
        .Fields.Append "DirID", adInteger
        .Fields.Append "Directory", adBSTR, 255
        .CursorType = adOpenStatic
        .LockType = adLockOptimistic
        .Open
    End With
    
    ' Itère dans les répertoires et remplit
    ' le Recordset.
    strPath = "C:\"
    strName = Dir(strPath, vbDirectory)
    i = 0
    Do While strName <> ""
        If strName <> "." And strName <> ".." _
            And strName <> "pagefile.sys" Then
            If (GetAttr(strPath & strName) And _
                vbDirectory) = vbDirectory Then
                i = i + 1
                With rs
                    .AddNew
                    .Fields.Item("DirID") = i
                    .Fields.Item("Directory") = strName
                    .Update
                End With
            End If
        End If
        strName = Dir
    Loop
    
    ' Retourne au premier enregistrement
    rs.MoveFirst
End Sub
Public Sub Cycle()
    ' Parcours le Recordset
    rs.MoveNext
    If rs.EOF = True Then
        rs.MoveFirst
    End If
End Sub

