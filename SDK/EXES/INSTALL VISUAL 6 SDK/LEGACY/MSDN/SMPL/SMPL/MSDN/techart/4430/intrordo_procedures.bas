Attribute VB_Name = "IntroRDO_Procedures"
Option Explicit
#If Win32 Then
Declare Function timeGetTime Lib "winmm.dll" () As Long
#Else
Declare Function timeGetTime Lib "MMSYSTEM" () As Long
#End If

Function VB3_FillLstFromSQL(Lst As Control, ByVal DBName$, ByVal SQLQuery$, ByVal DBConnect$, ByVal ReadOnly%, ByVal RSType%, ByVal Options%)
'On Error GoTo VB3_Error
Dim DB As Database
Dim RS As Recordset
Dim nRecords&
VB3Consistent_DAOOpenRecordset DBName$, RSType%, Options, DBConnect$
If ReadOnly% <> 0 Then ReadOnly% = True 'Validate

Lst.Clear
Set DB = OpenDatabase(DBName$, False, ReadOnly%, DBConnect$)
Set RS = DB.OpenRecordset(SQLQuery$, RSType%, Options%)
While Not RS.EOF
    Lst.AddItem (RS(0))
    RS.MoveNext
    nRecords& = nRecords& + 1
Wend

VB3_Exit:
VB3_FillLstFromSQL = nRecords& 'Return # added to Lst
On Error GoTo 0
Exit Function

VB3_Error: 'Display message and exit procedure
MsgBox Error$, vbExclamation, "Error:" & Err
Resume VB3_Exit
End Function

Sub VB3Consistent_DAOOpenRecordset(DBName$, RSType%, Options%, DBConnect$)
'We want to change values so NO ByVal
Select Case RSType% 'Must be ONE of the following values
    Case dao.dbOpenTable, dao.dbOpenSnapshot
    Case Else
        RSType% = dao.dbOpenDynaset
End Select
'Because value may be a result of multiple values we have a series of ifs.
If (Options And dao.dbDenyRead) > 0 Then RSType% = dao.dbOpenTable
'Prevent conflicting values
If (Options And dao.dbConsistent) > 0 _
    And (Options And dao.dbInconsistent) > 0 _
    Then Options = Options - dao.dbInconsistent
'Must this be a recordset?
If (Options And dao.dbAppendOnly) > 0 _
    Or (Options And dao.dbConsistent) > 0 _
    Or (Options And dao.dbInconsistent) > 0 _
    Then RSType% = dao.dbOpenDynaset
'Invalid if not ODBC
If (Options And dao.dbSQLPassThrough) > 0 _
    And InStr(UCase(DBConnect$), "ODBC") = 0 _
    Then Options = Options - dao.dbSQLPassThrough
End Sub

Function DAO_FillLstFromSQL( _
    LstControl As Control, _
    ByVal DBName$, _
    ByVal SQLQuery$, _
    Optional DBConnect, _
    Optional ReadOnly, _
    Optional RSType, _
    Optional Options, _
    Optional Exclusive, Optional cycles _
    )
On Error GoTo DAO_Error
Dim DE As New dao.DBEngine
Dim DB As dao.Database
Dim RS As dao.Recordset
Dim nRecords&, i%, QueryTicks&
VB4Consistant_DAOOpenRecordset _
    DBConnect:=DBConnect, _
    RSType:=RSType, _
    Options:=Options
    
If IsMissing(ReadOnly) Then
   ReadOnly = True 'Validate
ElseIf Not IsNumeric(ReadOnly) Then
    ReadOnly = True
ElseIf ReadOnly <> 0 Then
    ReadOnly = True
End If
If IsMissing(cycles) Then
    cycles = 1
Else
    cycles = cycles + 1
End If

LstControl.Clear
'I prefer to see Connect and name together:
Set DB = DE.OpenDatabase( _
    Name:=DBName$, _
    Connect:=DBConnect, _
    Exclusive:=Exclusive, _
    ReadOnly:=dbReadOnly _
    )
For i% = 1 To cycles
QueryTicks& = timeGetTime()
Set RS = DB.OpenRecordset( _
    Name:=SQLQuery$, _
    Type:=RSType, _
    Options:=Options _
    )
While Not RS.EOF
    LstControl.AddItem (RS(0))
    RS.MoveNext
    nRecords& = nRecords& + 1
Wend
QueryTicks& = timeGetTime() - QueryTicks&
RS.Close
AddNewTime QueryTicks&
Next i%

DAO_Exit:
DAO_FillLstFromSQL = nRecords& 'Return # added to Lst
On Error GoTo 0
Exit Function

DAO_Error: 'Display message and exit procedure
MsgBox Error$, vbExclamation, "Error:" & Err
Resume DAO_Exit
End Function
Sub VB4Consistant_DAOOpenRecordset( _
    Optional DBName, _
    Optional RSType, _
    Optional Options, _
    Optional DBConnect _
    )
'The tests applied depends on arguments supplied
If Not IsMissing(RSType) Then
    Select Case RSType 'Must be ONE of the following values
        Case dbOpenTable, dbOpenSnapshot
        Case Else
            RSType = dbOpenDynaset
    End Select
    If Not IsMissing(Options) Then
    'Because value may be a result of multiple values we have a series of ifs.
    If (Options And dbDenyRead) > 0 Then RSType = dbOpenTable
    'Prevent conflicting values
    If (Options And dbConsistent) > 0 _
        And (Options And dbInconsistent) > 0 _
        Then Options = Options - dbInconsistent
    'Must this be a recordset?
    If (Options And dbAppendOnly) > 0 _
        Or (Options And dbConsistent) > 0 _
        Or (Options And dbInconsistent) > 0 _
        Then RSType = dbOpenDynaset
'Invalid if not ODBC
End If
If Not (IsMissing(Options) Or IsMissing(DBConnect)) Then
    If (Options And dbSQLPassThrough) > 0 _
        And InStr(UCase(DBConnect), "ODBC") = 0 _
        Then Options = Options - dbSQLPassThrough
    End If
End If
End Sub
Function RDO_FillLstFromSQL( _
    LstControl As Control, _
    ByVal DBName$, _
    ByVal SQLQuery$, _
    Optional DBConnect, _
    Optional ReadOnly, _
    Optional RSType, _
    Optional Options, _
    Optional LockType, Optional Prompt, Optional cycles _
    ) 'NOTE This is the line continuation limit
On Error GoTo rDO_Error
Dim DB As rdo.rdoConnection
Dim Env As rdo.rdoEnvironment
Dim RS As rdo.rdoResultset
Dim nRecords&, i%, QueryTicks&

'Consistant_RDOOpenRecordset _
    DBConnect:=DBConnect, _
    RSType:=RSType, _
    Options:=Options
If IsMissing(Options) Then Options = 0

If IsMissing(ReadOnly) Then
   ReadOnly = True 'Validate
ElseIf Not IsNumeric(ReadOnly) Then
    ReadOnly = True
ElseIf ReadOnly <> 0 Then
    ReadOnly = True
End If
If IsMissing(cycles) Then
    cycles = 1
Else
    cycles = cycles + 1
End If

Set DB = rdoEngine.rdoEnvironments(0).OpenConnection( _
    dsName:=DBName$, _
    Prompt:=Prompt, _
    ReadOnly:=ReadOnly, _
    Connect:=DBConnect _
    )
For i% = 1 To cycles
QueryTicks& = timeGetTime()
Set RS = DB.OpenResultset( _
    Name:=SQLQuery, _
    Type:=RSType, _
    LockType:=LockType, _
    Option:=Options _
    )
If Options <> rdAsyncEnable Then
While Not RS.EOF
    LstControl.AddItem (RS(0))
    RS.MoveNext
    nRecords& = nRecords& + 1
Wend
Else
While RS.StillExecuting
    DoEvents
    While RS.MoreResults
        LstControl.AddItem (RS(0))
        RS.MoveNext
        nRecords& = nRecords& + 1
    Wend
Wend
End If
QueryTicks& = timeGetTime() - QueryTicks&
RS.Close
AddNewTime QueryTicks&
Next i%
rDO_Exit:
RDO_FillLstFromSQL = nRecords& 'Return # added to Lst
On Error GoTo 0
Exit Function

rDO_Error: 'Display message and exit procedure
MsgBox Error$, vbExclamation, "Error:" & Err
Resume rDO_Exit

End Function
Static Sub AddNewTime(ByVal QueryTicks&)
Dim sUM As Double, COUNT As Long, MinT As Long, maxt As Long
Dim Method$, fno%, Options$, ReadOnly$, i%
    Select Case QueryTicks
    Case Is >= 0
        sUM = sUM + QueryTicks&
    COUNT = COUNT + 1
    If MinT > QueryTicks& Then MinT = QueryTicks&
    If maxt < QueryTicks& Then maxt = QueryTicks&

    Case True 'rEPORT
        If COUNT = 0 Then Exit Sub
        IntroRDO.lstTimes.AddItem "Average:" + Format(sUM / COUNT, "0.00") + " Milliseconds"
        IntroRDO.lstTimes.AddItem "Fastest:" + Format(MinT, "0") + " Milliseconds"
        IntroRDO.lstTimes.AddItem "Slowest:" + Format(maxt, "0.00") + " Milliseconds"
        If IntroRDO.cbLogToFile Then
            If IntroRDO.DBObject(0) Then
                Method$ = "DAO"
            Else
                Method$ = "RDO"
            End If
            Options$ = ""
            For i% = 0 To IntroRDO.lstOptions.ListCount - 1
                If IntroRDO.lstOptions.Selected(i%) Then
                    Options$ = Options$ + IntroRDO.lstOptions.List(i%) + "+"
                End If
            Next i%
            If Len(Options$) > 0 Then Options$ = Left$(Options$, Len(Options$) - 1)
            If IntroRDO.cbDBReadOnly(0) <> 0 Then
                ReadOnly$ = "ReadOnly"
            Else
                ReadOnly$ = "Read/Write"
            End If
            fno% = FreeFile
            Open "intrordo.LOG" For Append As #fno%
            If LOF(fno%) = 0 Then
            Write #fno%, "Using Object", _
                "Average", _
                "Min Time", _
                "Max Time", _
                "RSet Type", "DB Name", _
                "DB Connect", _
                "Options", _
                "LockType(RDO)", _
                "Prompt (RDO)", _
                "Type of Access", "SQL Query"
            End If
            Write #fno%, Method$, _
                Int(sUM / COUNT), _
                MinT, _
                maxt, _
                IntroRDO.lstType, IntroRDO.DBName, _
                IntroRDO.DBConnect, _
                Options$, _
                IntroRDO.lstLockType, _
                IntroRDO.lstPrompt, _
                ReadOnly$, IntroRDO.SQLText
            Close #fno%
        End If
    Case Else 'NEW QUERIES
        IntroRDO.lstTimes.Clear
        MinT = 999999
        maxt = 0
        sUM = 0
        COUNT = 0
    End Select
End Sub
