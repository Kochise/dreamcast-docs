VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Service"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
'VB Component - DataSrc - 06/95
'by Ken Bergmann
'
'Purpose:
'   This module contains the data source code that should be
'   used as the foundation of a Visual Basic Client/Server Application.
'
'Modification Log:
'   When    Who     What
'   ----------------------------------------------------------------------------
'   06/95   kenbe   Original Creation
'
'Usage Notes:
'   Call these procedures to do all database access.
'   These function can be used as models for custom work like interpreting
'   multiple return sets.
'   They all include error logging.
'   When errors or unexpected results are returned, check the value of
'   ds.fGoodConn to see if the connection is valid.
'
'Procedures:
'Private Function CheckConn(ds As LayerDatabaseJet.Source) As Boolean
'Public Function BooleanQuery(ds As LayerDatabaseJet.Source, ByVal sQry As String) As Boolean
'Public Function FillArray(ds As LayerDatabaseJet.Source, ByVal sQry As String, sArray() As String, Optional lRowLimit As Variant) As Long
'Public Function FillCollection(ds As LayerDatabaseJet.Source, ByVal sQry As String, cTmp As Collection) As Boolean
'Public Sub FillListBox(ds As LayerDatabaseJet.Source, ctlMe, ByVal sQry As String, Optional lRowLimit As Variant)
'Public Sub FillListView(ds As LayerDatabaseJet.Source, ctlMe, ByVal sQry As String, Optional lRowLimit As Variant)
'Public Function GetText(ds As LayerDatabaseJet.Source, ByVal sQry As String) As String
'Public Function Init(ds As LayerDatabaseJet.Source, objSysErr As LayerError.Service, objSysLog As LayerLogAll.Services) As Boolean
'Public Function NoResultQuery(ds As LayerDatabaseJet.Source, ByVal sQry As String) As Boolean
'Public Sub Term(ds As LayerDatabaseJet.Source)
Option Explicit

Private rsTemp      As Recordset
Private objError    As Error

'BooleanQuery - DataSrc - 06/95
'by Ken Bergmann
'Purpose - Execute a sp with boolean return data
'Inputs -
'       ds        LayerDatabaseJet.Source
'       sQry      string
'Outputs -
'       True, False for success failure
'Calls -
'       CheckConn
Public Function BooleanQuery(ds As LayerDatabaseJet.Source, ByVal sQry As String) As Boolean
BooleanQuery = False
'Open the connection
If Not CheckConn(ds) Then Exit Function

On Error Resume Next
rsTemp.Close

ds.objEvtLog.PostItem 1, "BooleanQuery", sQry
ds.objTrnLog.PostItem 1, "BooleanQuery", sQry

Err = 0
Set rsTemp = ds.dbMe.OpenRecordset(sQry, dbOpenSnapshot, dbForwardOnly + ds.iRemote)
If Err Then
    If Errors.Count Then
        For Each objError In Errors
            ds.objError.Raise False, objError.Number, "BooleanQuery.Error", objError.Description
        Next objError
        Set objError = Nothing
    Else
        ds.objError.Raise False, Err, "BooleanQuery.Error", Error$
    End If
Else
    If Not (rsTemp.BOF And rsTemp.EOF) Then
        Do Until rsTemp.EOF
            If CBool(rsTemp(0)) Then
                BooleanQuery = False
            Else
                BooleanQuery = True
            End If
            rsTemp.MoveNext
        Loop
    End If
End If
rsTemp.Close
End Function

'CheckConn - DataSrc - 06/95
'by Ken Bergmann
'Purpose - Checks the status of a connection.
'          If required, it attempts reconnect
'Inputs -
'       ds        LayerDatabaseJet.Source
'       sQry      string
'Outputs -
'       True, False for success failure
'Calls -
'       CheckConn
Private Function CheckConn(ds As LayerDatabaseJet.Source) As Boolean
CheckConn = False
'Open the connection
If ds.dbMe Is Nothing Then
    ds.fGoodConn = False
    On Error Resume Next
    Err = 0
    Set ds.dbMe = OpenDatabase(ds.sDBName, ds.fExclusive, ds.fReadOnly, ds.sConnStr)
    If Err Then
        If Errors.Count Then
            For Each objError In Errors
                ds.objError.Raise False, objError.Number, "CheckConn", objError.Description
            Next objError
            Set objError = Nothing
        Else
            ds.objError.Raise False, Err, "CheckConn", Error$
        End If
        Exit Function
    End If
    ds.dbMe.QueryTimeout = ds.iTimeOut
End If
ds.fGoodConn = True
CheckConn = True
End Function

'FillArray - DataSrc - 06/95
'by Ken Bergmann
'Purpose - Retrieve undetermined number of rows
'          into an array of undetermined cols
'          Array is stored (COL, ROW) format
'Inputs -
'       ds        LayerDatabaseJet.Source
'       sQry      string
'       sArray()  string
'Outputs -
'       (LONG) Returns the number of rows actually retrieved
'Calls -
'       CheckConn
Public Function FillArray(ds As LayerDatabaseJet.Source, ByVal sQry As String, sArray() As String, Optional lRowLimit As Variant) As Long
Dim iCols   As Integer
Dim iCurCol As Integer
Dim lCurRow As Long

If IsMissing(lRowLimit) Then lRowLimit = 32000
If (lRowLimit <= 0) Or (lRowLimit > 32000) Then lRowLimit = 32000

'Open the connection
If Not CheckConn(ds) Then Exit Function

On Error Resume Next
rsTemp.Close

ds.objEvtLog.PostItem 1, "FillArray", sQry
ds.objTrnLog.PostItem 1, "FillArray", sQry

On Error GoTo fllarray
Set rsTemp = ds.dbMe.OpenRecordset(sQry, dbOpenSnapshot, ds.iRemote)
If Not (rsTemp.BOF And rsTemp.EOF) Then
    rsTemp.MoveLast
    iCols = rsTemp.Fields.Count - 1
    lCurRow = rsTemp.RecordCount - 1
    ReDim sArray(iCols, lCurRow) As String
    lCurRow = 0
    rsTemp.MoveFirst
    Do Until rsTemp.EOF
        For iCurCol = 0 To iCols
            If IsNull(rsTemp(iCurCol)) Then
                sArray(iCurCol, lCurRow) = ""
            Else
                sArray(iCurCol, lCurRow) = Trim$(CStr(rsTemp(iCurCol)))
            End If
        Next iCurCol
        lCurRow = lCurRow + 1
        If lCurRow >= lRowLimit Then rsTemp.MoveLast
        rsTemp.MoveNext
    Loop
End If
rsTemp.Close
FillArray = lCurRow
Exit Function

fllarray:
    If Errors.Count Then
        For Each objError In Errors
            ds.objError.Raise False, objError.Number, "FillArray", objError.Description
        Next objError
        Set objError = Nothing
    Else
        ds.objError.Raise False, Err, "FillArray", Error$
    End If
    ReDim sArray(0, 0) As String
    If Not (rsTemp Is Nothing) Then rsTemp.Close
    FillArray = 0
    Exit Function

End Function

'FillCollection - DataSrc - 06/95
'by Ken Bergmann
'Purpose - Retrieve single row to a collection
'Inputs -
'       ds      LayerDatabaseJet.Source
'       sQry    string
'       cTmp    Collection
'Outputs -
'       True/False - success or failure
'Calls -
'       CheckConn
Public Function FillCollection(ds As LayerDatabaseJet.Source, ByVal sQry As String, cTmp As Collection) As Boolean
Dim iCols   As Integer
Dim iCurCol As Integer

'Open the connection
If Not CheckConn(ds) Then Exit Function

On Error Resume Next
rsTemp.Close

ds.objEvtLog.PostItem 1, "FillCollection", sQry
ds.objTrnLog.PostItem 1, "FillCollection", sQry

On Error GoTo fllcollect
Set cTmp = Nothing
Set cTmp = New Collection
Set rsTemp = ds.dbMe.OpenRecordset(sQry, dbOpenSnapshot, dbForwardOnly + ds.iRemote)
If Not (rsTemp.BOF And rsTemp.EOF) Then
    iCols = rsTemp.Fields.Count - 1
    For iCurCol = 0 To iCols
        cTmp.Add (rsTemp(iCurCol)), CStr(rsTemp(iCurCol).Name)
    Next iCurCol
    FillCollection = True
End If
rsTemp.Close
Exit Function

fllcollect:
    If Errors.Count Then
        For Each objError In Errors
            ds.objError.Raise False, objError.Number, "FillCollection", objError.Description
        Next objError
        Set objError = Nothing
    Else
        ds.objError.Raise False, Err, "FillCollection", Error$
    End If
    If Not (rsTemp Is Nothing) Then rsTemp.Close
    FillCollection = False
    Exit Function

End Function

'FillListBox - DataSrc - 06/95
'by Ken Bergmann
'Purpose - Fill a list box with col(0)
'          Fills item data with col(1)
'Inputs -
'       ds       LayerDatabaseJet.Source
'       ctlMe    Control
'       sQry     String
'Calls -
'       CheckConn
Public Sub FillListBox(ds As LayerDatabaseJet.Source, ctlMe, ByVal sQry As String, Optional lRowLimit As Variant)
Dim lCurRow As Long

If IsMissing(lRowLimit) Then lRowLimit = 32000
If (lRowLimit <= 0) Or (lRowLimit > 32000) Then lRowLimit = 32000

'Open the connection
If Not CheckConn(ds) Then Exit Sub

On Error Resume Next
rsTemp.Close

ds.objEvtLog.PostItem 1, "FillListBox", sQry
ds.objTrnLog.PostItem 1, "FillListBox", sQry

On Error GoTo flbierr
Set rsTemp = ds.dbMe.OpenRecordset(sQry, dbOpenSnapshot, dbForwardOnly + ds.iRemote)
If Not (rsTemp.BOF And rsTemp.EOF) Then
    Do Until rsTemp.EOF
        ctlMe.AddItem Trim$(CStr(rsTemp(0)))
        ctlMe.ItemData(ctlMe.NewIndex) = CLng(rsTemp(1))
        lCurRow = lCurRow + 1
        If lCurRow >= lRowLimit Then rsTemp.MoveLast
        rsTemp.MoveNext
    Loop
End If
rsTemp.Close
Exit Sub

flbierr:
    If Errors.Count Then
        For Each objError In Errors
            ds.objError.Raise False, objError.Number, "FillListBox", objError.Description
        Next objError
        Set objError = Nothing
    Else
        ds.objError.Raise False, Err, "FillListBox", Error$
    End If
    On Error Resume Next
    ctlMe.Clear
    Exit Sub

End Sub

'FillListView - DataSrc - 06/95
'by Ken Bergmann
'Purpose - Fill a list view with data
'          Fills list item with col(0)
'          Fills item data with col(1)
'          Fills sub items with col(2...x)
'Inputs -
'       ds       LayerDatabaseJet.Source
'       ctlMe    Control
'       sQry     String
'Calls -
'       CheckConn
Public Sub FillListView(ds As LayerDatabaseJet.Source, ctlMe, ByVal sQry As String, Optional lRowLimit As Variant)
Dim iCols       As Integer
Dim iCurCol     As Integer
Dim liTemp      As ListItem
Dim chTemp      As ColumnHeader
Dim lCurRow     As Long

If IsMissing(lRowLimit) Then lRowLimit = 32000
If (lRowLimit <= 0) Or (lRowLimit > 32000) Then lRowLimit = 32000

'Open the connection
If Not CheckConn(ds) Then Exit Sub

On Error Resume Next
rsTemp.Close

ds.objEvtLog.PostItem 1, "FillListView", sQry
ds.objTrnLog.PostItem 1, "FillListView", sQry

On Error GoTo flvierr
Set rsTemp = ds.dbMe.OpenRecordset(sQry, dbOpenSnapshot, dbForwardOnly + ds.iRemote)
If Not (rsTemp.BOF And rsTemp.EOF) Then
    ctlMe.ColumnHeaders.Clear
    iCols = rsTemp.Fields.Count - 1
    'Add the first column
    Set chTemp = ctlMe.ColumnHeaders.Add(, CStr(rsTemp(0).Name), CStr(rsTemp(0).Name))
    'Skip the id, and add all the rest
    For iCurCol = 2 To iCols
        Set chTemp = ctlMe.ColumnHeaders.Add(, CStr(rsTemp(iCurCol).Name), CStr(rsTemp(iCurCol).Name))
    Next iCurCol
    Set chTemp = Nothing
    
    ctlMe.ListItems.Clear
    Do Until rsTemp.EOF
        Set liTemp = ctlMe.ListItems.Add()
        liTemp.Tag = Trim$(rsTemp(1))
        liTemp.Text = Trim$(CStr(rsTemp(0)))
        For iCurCol = 2 To iCols
            If Not IsNull(rsTemp(iCurCol)) Then
                liTemp.SubItems(iCurCol - 1) = Trim$(CStr(rsTemp(iCurCol)))
            End If
        Next iCurCol
        lCurRow = lCurRow + 1
        If lCurRow >= lRowLimit Then rsTemp.MoveLast
        rsTemp.MoveNext
    Loop
    Set liTemp = Nothing
End If
rsTemp.Close
Exit Sub

flvierr:
    If Errors.Count Then
        For Each objError In Errors
            ds.objError.Raise False, objError.Number, "FillListView", objError.Description
        Next objError
        Set objError = Nothing
    Else
        ds.objError.Raise False, Err, "FillListView", Error$
    End If
    On Error Resume Next
    ctlMe.ListItems.Clear
    Exit Sub

End Sub

'GetText - DataSrc - 06/95
'by Ken Bergmann
'Purpose - Retrieve single piece of data
'Inputs -
'       ds       LayerDatabaseJet.Source
'       sQry     string
'Outputs -
'       (STRING) The returned text
'Calls -
'       CheckConn
Public Function GetText(ds As LayerDatabaseJet.Source, ByVal sQry As String) As String
GetText = ""

'Open the connection
If Not CheckConn(ds) Then Exit Function

On Error Resume Next
rsTemp.Close

ds.objEvtLog.PostItem 1, "GetText", sQry
ds.objTrnLog.PostItem 1, "GetText", sQry

Err = 0
Set rsTemp = ds.dbMe.OpenRecordset(sQry, dbOpenSnapshot, dbForwardOnly + ds.iRemote)
If Err Then
    If Errors.Count Then
        For Each objError In Errors
            ds.objError.Raise False, objError.Number, "GetText", objError.Description
        Next objError
        Set objError = Nothing
    Else
        ds.objError.Raise False, Err, "GetText", Error$
    End If
Else
    If rsTemp.BOF And rsTemp.EOF Then
        GetText = ""
    Else
        Do Until rsTemp.EOF
            If IsNull(rsTemp(0)) Then
                GetText = ""
            Else
                GetText = Trim$(CStr(rsTemp(0)))
            End If
            rsTemp.MoveNext
        Loop
    End If
End If
rsTemp.Close

End Function

'Init - DataSrc - 06/95
'by Ken Bergmann
'Purpose - Opens a standard ODBC connection
'Inputs -
'       ds As LayerDatabaseJet.Source
'       objE As objErrHnd
'       objL As objLogTrans
'Outputs -
'       True, False for success failure
Public Function Init(ds As LayerDatabaseJet.Source, objSysErr As LayerError.Service, objSysLog As LayerLogAll.Services) As Boolean
Init = False
ds.fGoodConn = False

On Error Resume Next
ds.dbMe.Close
Set ds.dbMe = Nothing

Err = 0
'Open the connection
Set ds.dbMe = OpenDatabase(ds.sDBName, ds.fExclusive, ds.fReadOnly, ds.sConnStr)
If Err Then
    If Errors.Count Then
        For Each objError In Errors
            objSysErr.Raise False, objError.Number, "Init", objError.Description
        Next objError
        Set objError = Nothing
    Else
        objSysErr.Raise False, Err, "Init", Error$
    End If
    Exit Function
End If
ds.dbMe.QueryTimeout = ds.iTimeOut

Err = 0
Set ds.objError = objSysErr
If Err Then
    objSysErr.Raise False, Err, "Init", Error$
    Exit Function
End If

Err = 0
Set ds.objEvtLog = objSysLog.Event
If Err Then
    ds.objError.Raise False, Err, "Init", Error$
    Exit Function
End If

Err = 0
Set ds.objTrnLog = objSysLog.Trans
If Err Then
    ds.objError.Raise False, Err, "Init", Error$
    Exit Function
End If

ds.fGoodConn = True
Init = True
End Function

'NoResultQuery - DataSrc - 06/95
'by Ken Bergmann
'Purpose - Execute an action with no return
'Inputs -
'       ds        LayerDatabaseJet.Source
'       sQry      string
'Outputs -
'       True, False for success failure
'Calls -
'       CheckConn
Public Function NoResultQuery(ds As LayerDatabaseJet.Source, ByVal sQry As String) As Boolean
Dim iErrors As Integer
On Error GoTo excaqryerr
BeginTrans
'Open the connection
If Not CheckConn(ds) Then Exit Function

ds.objEvtLog.PostItem 1, "NoResultQuery", sQry
ds.objTrnLog.PostItem 1, "NoResultQuery", sQry

ds.dbMe.Execute sQry, dbFailOnError + ds.iRemote

CommitTrans
NoResultQuery = True
Exit Function

excaqryerr:
    Rollback
    If Errors.Count Then
        For Each objError In Errors
            ds.objError.Raise False, objError.Number, "NoResultQuery", objError.Description
        Next objError
        Set objError = Nothing
    Else
        ds.objError.Raise False, Err, "NoResultQuery", Error$
    End If
    NoResultQuery = False
    Exit Function

End Function

'Terminate - DataSrc - 06/95
'by Ken Bergmann
'Purpose - Closes and cleans up a data source
'Inputs - ds        LayerDatabaseJet.Source
Public Sub Term(ds As LayerDatabaseJet.Source)
On Error Resume Next
Set ds.dbMe = Nothing
Set ds.objError = Nothing
Set ds.objEvtLog = Nothing
Set ds.objTrnLog = Nothing
End Sub
