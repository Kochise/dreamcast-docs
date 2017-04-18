VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "VbBusObjCls"
Attribute VB_GlobalNameSpace = True
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private Sub Class_Initialize()
  'class setup code here
End Sub

Public Function Test()
  'this is here to test minimum functionality
  Test = "Functional test verified."
End Function

Public Function GetMachineName() As String
  'this is here to show that not all methods need to be database related
  On Error GoTo ehGetMachineName
  Dim pc_name As String * 255
  Dim x As Long
  x = GetComputerName(pc_name, 255)
  GetMachineName = Trim(pc_name)
  Exit Function
ehGetMachineName:
  Err.Raise Err.Number, Err.Source, Err.Description
End Function

Public Function ExecuteSQL(ByVal Connect As String, ByVal SQL As String) As Long
  'this function executes and SQL string and returns the number of records affected
  On Error GoTo ehExecuteSQL
  Dim objADOCn As New ADODB.Connection    'ADO must be registered locally
  objADOCn.Open Connect                   'open connection
  objADOCn.BeginTrans                     'begin a transaction
  objADOCn.Execute SQL, ExecuteSQL        'recordsetAffected is returned
  objADOCn.CommitTrans                    'no errors, commit
Exit Function
ehExecuteSQL:
  'if transactions is not committed, it will be rolled back
  Err.Raise Err.Number, Err.Source, Err.Description
End Function

Public Function GetRecordset(ByVal Connect As String, ByVal SQL As String) As ADOR.Recordset
  'this function returns an ADODB recordset object
  On Error GoTo ehGetRecordset
  Dim objADORs As New ADODB.Recordset                      'ADO must be registered locally
  objADORs.CursorLocation = adUseClientBatch               'this property is not visible in v1.0 typelib
  objADORs.Open SQL, Connect, adOpenUnspecified, adLockBatchOptimistic, adCmdUnspecified
  Set GetRecordset = objADORs                              'set object pointer for ADOR type recordset
Exit Function
ehGetRecordset:
  Err.Raise Err.Number, Err.Source, Err.Description
End Function

Private Sub Class_Terminate()
  'class cleanup code here
End Sub
