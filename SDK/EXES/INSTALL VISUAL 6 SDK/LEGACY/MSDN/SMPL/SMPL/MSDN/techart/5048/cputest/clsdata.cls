VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsDatabaseOp"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
Private Declare Function GetTickCount Lib "kernel32" () As Long
Private Const TIMINGDATABASEPATH As String = "c:\inetpub\MachTime.mdb"

'Retrieve the current time
Public Function GetTime() As Long
    GetTime = GetTickCount()
End Function


'***********************************************************
'Sets a 0 0 record in the MachineData table to indicate that
'logging can begin
'***********************************************************
Public Sub SetLogFlag()

    Dim db As Database
    Dim rs As Recordset
    
    'Open the database
    Set db = DAO.OpenDatabase(TIMINGDATABASEPATH)
    
    'Query for a recordset
    db.Execute ("Delete * From MachineData")
    
    'Add the new record - which acts as a Flag to indicate the others can write
    Set rs = db.OpenRecordset("Select * From MachineData")
    rs.AddNew
    rs("MachineName") = "0"
    rs("Time") = 0
    rs.Update
    
    'Erase objects used
    rs.Close
    Set rs = Nothing
    
    db.Close
    Set db = Nothing


End Sub

'***********************************************************
'Sets a 0 0 record in the MachineData table to indicate that
'logging can begin
'***********************************************************
Public Sub SetStopLogFlag()

    Dim db As Database
    Dim rs As Recordset
    
    'Open the database
    Set db = DAO.OpenDatabase(TIMINGDATABASEPATH)
    
    
    'Add the new record - which acts as a Flag to indicate the others can write
    Set rs = db.OpenRecordset("Select * From MachineData")
    rs.AddNew
    rs("MachineName") = "1"
    rs("Time") = 1
    rs.Update
    
    'Erase objects used
    rs.Close
    Set rs = Nothing
    
    db.Close
    Set db = Nothing


End Sub





'**********************************************************
'Obtains the data from NWind.mdb, and places the rows into
'a Variant array
'***********************************************************
Public Function GetData(ByVal vstrSQLQuery As String) As Variant

    Dim db As Database
    Dim rs As Recordset
    Dim ulNumRecords As Long
    
    'Open the database
    Set db = DAO.OpenDatabase("c:\inetpub\nwind.mdb")
    
    'Query for a recordset
    Set rs = db.OpenRecordset(vstrSQLQuery, dbOpenSnapshot)
    
    'Find out the number of records
    rs.MoveLast
    ulNumRecords = rs.RecordCount
    rs.MoveFirst
    
    'Copy the all the rows into an array
    GetData = rs.GetRows(ulNumRecords)
    
    'Erase objects used
    rs.Close
    Set rs = Nothing
    
    db.Close
    Set db = Nothing

End Function


'**********************************************************************
'Accepts a two-dimensional array of Unit Price and Quantity, and
'divides unit price by quantity. Calculates average Unit price/Quantity
'***********************************************************************
Public Function CalculatePriceQuantityAverage(ByVal vvntData As Variant) As Variant

    Dim ulNumberRows As Long
    Dim nRow As Long
    Dim dCumAverage As Double
    Dim ulCounter As Long
    
    ulNumberRows = UBound(vvntData, 2)
    
    dCumAverage = 0
    
    For ulCounter = 1 To 20
    For nRow = 1 To ulNumberRows
        dCumAverage = (vvntData(0, nRow) / vvntData(1, nRow)) + dCumAverage
    Next nRow
    Next ulCounter
    
    CalculatePriceQuantityAverage = (dCumAverage / ulNumberRows)

End Function


'**************************************************************************
'Logs the amount of time for the client request
'**************************************************************************
Public Function LogMachineTime(ByVal vstrMachineName As String, ByVal vulElapsedTime As Long)

    Dim db As Database
    Dim rs As Recordset
    
    'Open the database
    Set db = DAO.OpenDatabase(TIMINGDATABASEPATH)
    
    'Query for a recordset
    Set rs = db.OpenRecordset("Select * From MachineData", dbOpenDynaset)
    
    'Add the new record
    If ((IsOKToLogData(db)) And (vstrMachineName <> "")) Then
        rs.AddNew
        rs("MachineName") = vstrMachineName
        rs("Time") = vulElapsedTime
        rs.Update
    End If
    
    'Erase objects used
    rs.Close
    Set rs = Nothing
    
    db.Close
    Set db = Nothing

End Function

Private Function IsOKToLogData(db As Database) As Boolean

Dim rsStart As Recordset
Dim rsFinish As Recordset

'Query for the Flag start record
Set rsStart = db.OpenRecordset("Select * From MachineData Where (MachineName = '0' And Time = 0)")

'Query for the Flag Finish record
Set rsFinish = db.OpenRecordset("Select * From MachineData Where (MachineName = '1' And Time = 1)")

    'If there is a record, then Flag record is present
    If ((rsStart.EOF <> True) And (rsFinish.EOF = True)) Then
            IsOKToLogData = True
        Else
            IsOKToLogData = False
    End If
    
rsStart.Close
Set rsStart = Nothing

rsFinish.Close
Set rsFinish = Nothing

End Function
