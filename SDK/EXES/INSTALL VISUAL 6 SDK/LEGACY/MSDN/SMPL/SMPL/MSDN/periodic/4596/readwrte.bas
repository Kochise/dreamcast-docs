Attribute VB_Name = "ReadWrite"
Option Explicit

Public Function DBRead(DataName As String, ReadOnly As Boolean, _
FieldName As String, FieldType As String, connect As String, action As Integer) As Long
Dim MyDb As Database, MyRs As Recordset
Dim RetBuf As String * 100
Dim recCount As Long

On Error GoTo catchError
Select Case action
Case 0
  recCount = 0
  Set MyDb = DBEngine.Workspaces(0).OpenDatabase("", False, False, connect)
  Set MyRs = MyDb.OpenRecordset(TableName, dbOpenDynaset)
  Do Until MyRs.EOF
    If ReadOnly = False Then MyRs.Edit
    If ReadOnly Then
      RetBuf = MyRs(FieldName)
    Else
      MyRs(FieldName) = Reverse(MyRs(FieldName))
    End If
    If ReadOnly = False Then MyRs.Update
    recCount = recCount + 1
    MyRs.MoveNext
  Loop
  MyDb.Close
Case 1
  recCount = 10
  Dim mrdoEnv As rdoEnvironment, mrdoConn As Object, sSQL As String
  Dim MyrdoRs As rdoResultset '
  rdoEngine.rdoDefaultCursorDriver = rdUseIfNeeded
  Set mrdoEnv = rdoEngine.rdoCreateEnvironment("", "", "")
  Set mrdoConn = mrdoEnv.OpenConnection("", rdDriverNoPrompt, True, Right(connect, _
          Len(connect) - Len("ODBC;")))
  sSQL = "Select " & FieldName & " from " & TableName
  Set MyrdoRs = mrdoConn.OpenResultset(sSQL, rdOpenKeyset, rdConcurValues)
    
  Do Until MyrdoRs.EOF
  If ReadOnly = False Then MyrdoRs.Edit
  If ReadOnly Then
    RetBuf = MyrdoRs.rdoColumns(FieldName)
  Else
    MyrdoRs.rdoColumns(FieldName).Value = Reverse(MyrdoRs.rdoColumns(FieldName).Value)
  End If
  If ReadOnly = False Then MyrdoRs.Update
  recCount = recCount + 1
  MyrdoRs.MoveNext
  Loop
  
  MyrdoRs.Close
  mrdoConn.Close

Case 2
  recCount = 0
  Dim phenv As Long, phdbc As Long, hstmt As Long, cbData As Long, cbRetBuf As Long
  Dim rc As Integer, pszData As String
  pszData = String(100, 0)
  rc = SQLAllocEnv(phenv)
  If (CheckSuccess(HNDL_HENV, 0, rc) = False) Then Exit Function
  rc = SQLAllocConnect(ByVal phenv, phdbc)
  If (CheckSuccess(HNDL_HENV, 0, rc) = False) Then Exit Function
  Dim szConnStrIn As String, szConnStrOut As String, cbConnStrOut As Integer
  szConnStrOut = String(256, 0)
  szConnStrIn = Right(connect, Len(connect) - Len("ODBC;"))
  rc = SQLDriverConnect(ByVal phdbc, 0, ByVal szConnStrIn, _
  SQL_NTS, ByVal szConnStrOut, 255, cbConnStrOut, SQL_DRIVER_COMPLETE)
  If (CheckSuccess(HNDL_HDBC, 0, rc) = False) Then Exit Function
  rc = SQLAllocStmt(ByVal phdbc, hstmt)
  If (CheckSuccess(HNDL_HENV, hstmt, rc) = False) Then Exit Function
  SQLSetScrollOptions ByVal hstmt, SQL_CONCUR_LOCK, SQL_SCROLL_KEYSET_DRIVEN, 1
  sSQL = "SELECT " & FieldName & " from " & TableName
  rc = SQLExecDirect(ByVal hstmt, sSQL, SQL_NTS)
  If (CheckSuccess(HNDL_HSTMT, hstmt, rc) = False) Then Exit Function
  Dim cbrow As Long, RowStatus As Integer
  Dim retbuft(100) As Byte
  Dim temp(100) As Byte, TempStr As String, LenStr As Integer
  If ReadOnly = False Then
    rc = SQLBindCol(ByVal hstmt, 1, SQL_C_CHAR, retbuft(0), 100, cbRetBuf)
    rc = SQLExtendedFetch(ByVal hstmt, SQL_FETCH_NEXT, 1, cbrow, RowStatus)
  Else
    rc = SQLFetch(ByVal hstmt) ' for simple reading fetch is faster
  End If
  While (rc = SQL_SUCCESS Or rc = SQL_SUCCESS_WITH_INFO)
    If ReadOnly Then
      rc = SQLGetData(ByVal hstmt, 1, SQL_C_CHAR, ByVal pszData, 100, cbData)
      rc = SQLFetch(ByVal hstmt) ' for simple reading fetch is faster
    Else
      Dim i As Integer
      TempStr = StrConv(retbuft, vbUnicode)
      LenStr = InStr(TempStr, Chr(0)) - 1
   
      For i = 0 To LenStr - 1
        temp(i) = retbuft(i)
      Next
      For i = 0 To LenStr - 1
        retbuft(i) = temp(LenStr - i - 1)
      Next
      rc = SQLSetPos(ByVal hstmt, 1, SQL_UPDATE, SQL_LOCK_NO_CHANGE)
      If (CheckSuccess(HNDL_HSTMT, hstmt, rc) = False) Then Exit Function
      rc = SQLExtendedFetch(ByVal hstmt, SQL_FETCH_NEXT, 1, cbrow, RowStatus)
   End If
  recCount = recCount + 1
  Wend
  
  SQLFreeStmt ByVal hstmt, SQL_DROP
  SQLDisconnect ByVal phdbc
  SQLFreeConnect ByVal phdbc
  SQLFreeEnv ByVal phenv

End Select

DBRead = recCount
Exit Function
catchError:
If Err.Number = 94 Then
  Beep
  MsgBox "Null field encoutered: " + DataName + "  " + TableName + "  " + FieldName + _
    vbCrLf + "Please choose another field", vbOKOnly, "Error!"
End If
Beep
End Function

Private Function Reverse(str As String) As String
Dim i As Integer
Reverse = ""
For i = Len(LTrim(str)) To 1 Step -1
   Reverse = Reverse & Mid(str, i, 1)
Next i
End Function
