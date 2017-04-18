VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CExec"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'Copyright (C) 1998 Microsoft Corporation
'All rights reserved.
'
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
'EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
'MERCHANTIBILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
'
'Date    - 02/01/98
'Authors - Robert Coleridge, Steve Kirk, Fred Pace, Kevin Marzec, Dale Smith
'
Option Explicit

Private Const OBJNAME = "CExec"

'=======================================================================
'Synopsis:              This function opens a connection using ADO and
'                       executes the action query passed to it.
'Function input:        Connect string which is a registered DSN
'                       Query string to be executed.
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function ExecQuery(ByVal sConnect As String, ByVal sQry As String) As Boolean
Dim oConn       As ADODB.Connection
Dim lErrNo      As Long
Dim sErrDesc    As String

'default to false for function
ExecQuery = False

'enable error handler
On Error GoTo ErrorHandler

'Get connection, execute query, and shut everything down
Set oConn = New ADODB.Connection
oConn.Open sConnect
oConn.Execute sQry
oConn.Close
Set oConn = Nothing

#If bUseMTS Then
    'let MTS know everything worked
    GetObjectContext.SetComplete
#End If

ExecQuery = True              'Return TRUE for function
Exit Function

ErrorHandler:
    'store incoming values
    lErrNo = Err.Number
    sErrDesc = Err.Description

    'close down what we can and signal failure
    On Error Resume Next
    oConn.Close
#If bUseMTS Then
    GetObjectContext.SetAbort
#End If
    ExecQuery = False
    
    If Err < vbObjectError Then
        lErrNo = lErrNo + vbObjectError
    End If
    On Error GoTo 0
    
    Err.Raise lErrNo, OBJNAME, sErrDesc
    
End Function

'=======================================================================
'Synopsis:              Function opens a connection using ADO and executes
'                       a query passed to it. This function returns
'                       records in a string array.
'Function input:        Connect string which is a registered DSN
'                       Query string to be executed.
'                       A string array to return records
'                       ColumName to be added(Optional & Internal).
'Function output:       Returns TRUE if the function succeeds
'=======================================================================
Public Function ExecFillArray(ByVal sConnect As String, ByVal sQry As String, sTemp As Variant, Optional ByVal bAddColumnName As Boolean) As Boolean
Dim oConn       As ADODB.Connection
Dim rsTemp      As ADODB.Recordset
Dim lCurRow     As Long
Dim lErrNo      As Long
Dim iCols       As Integer
Dim iCurCol     As Integer
Dim sErrDesc    As String

'default to false for function
ExecFillArray = False

'enable error handler
On Error GoTo ErrorHandler

Set oConn = New ADODB.Connection
Set rsTemp = New ADODB.Recordset

oConn.Open sConnect

Set rsTemp.ActiveConnection = oConn
rsTemp.CursorLocation = ADODB.CursorLocationEnum.adUseClient

rsTemp.Open sQry

'Check the existence of records before filling up array
If Not (rsTemp.BOF And rsTemp.EOF) And rsTemp.RecordCount > 0 Then
    iCols = rsTemp.Fields.Count - 1
    lCurRow = rsTemp.RecordCount - 1
    
    If bAddColumnName Then
        ReDim sTemp(iCols, lCurRow + 1) As String
    Else
        ReDim sTemp(iCols, lCurRow) As String
    End If
    
    lCurRow = 0
    rsTemp.MoveFirst
    Do Until rsTemp.EOF
        For iCurCol = 0 To iCols
            If IsNull(rsTemp(iCurCol)) Then
                sTemp(iCurCol, lCurRow) = scSpace
            Else
                sTemp(iCurCol, lCurRow) = Trim$(CStr(rsTemp(iCurCol)))
            End If
            If bAddColumnName Then
                sTemp(iCurCol, 1) = rsTemp(iCurCol).Name
            End If
        Next iCurCol
        lCurRow = lCurRow + 1
        rsTemp.MoveNext
    Loop
    
    rsTemp.Close
    Set rsTemp = Nothing
    
    oConn.Close
    Set oConn = Nothing

#If bUseMTS Then
    GetObjectContext.SetComplete
#End If
    
    ExecFillArray = True
End If

Exit Function

ErrorHandler:
    'store incoming values
    lErrNo = Err.Number
    sErrDesc = Err.Description
    
    'close down what we can and signal failure
    On Error Resume Next
    Set rsTemp = Nothing
#If bUseMTS Then
    GetObjectContext.SetAbort
#End If
    ExecFillArray = False
    
    If Err < vbObjectError Then
        lErrNo = lErrNo + vbObjectError
    End If
    On Error GoTo 0
    
    Err.Raise lErrNo, OBJNAME, sErrDesc

End Function

