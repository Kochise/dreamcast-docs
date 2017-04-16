VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Service"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit

Public DBSvc    As LayerDatabaseJet.Service
Public DBSrc    As Collection

Public Function Init() As Boolean
On Error GoTo initdbcon
Set DBSrc = New Collection
Set DBSvc = New LayerDatabaseJet.Service
Init = True
Exit Function

initdbcon:
    Init = False
    Exit Function
End Function

Public Function SourceInit(ByVal sKey As String, ByVal sDBN As String, _
                             ByVal sConnStr As String, ByVal fEX As Boolean, _
                             ByVal fRO As Boolean, ByVal iTO As Integer, _
                             ByVal iRmt As Integer, _
                             objSysErr As Object, objSysLog As Object) As Boolean
On Error GoTo adddserr
Dim clsDataSource As New LayerDatabaseJet.Source

clsDataSource.sDBName = sDBN
clsDataSource.sConnStr = sConnStr
clsDataSource.fExclusive = fEX
clsDataSource.fReadOnly = fRO
clsDataSource.iTimeOut = iTO
clsDataSource.iRemote = iRmt

DBSrc.Add Item:=clsDataSource, Key:=sKey
SourceInit = DBSvc.Init(clsDataSource, objSysErr, objSysLog)
Exit Function

adddserr:
    SourceInit = False
    Exit Function

End Function

Public Sub SourceTerm(ByVal sKey As String)
On Error Resume Next
DBSvc.Term DBSrc(sKey)
DBSrc.Remove sKey
End Sub

Public Sub Term()
Dim ds As LayerDatabaseJet.Source
On Error Resume Next
For Each ds In DBSrc
    DBSvc.Term ds
Next ds
For Each ds In DBSrc
    DBSrc.Remove 1
Next ds
End Sub

Private Sub Class_Terminate()
On Error Resume Next
Term
End Sub
