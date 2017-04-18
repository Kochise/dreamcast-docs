VERSION 1.0 CLASS
BEGIN
  MultiUse = 0   'False
END
Attribute VB_Name = "Persistence"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"3237F8CE0359"
'Reuse pattern for persistent storage of business object
'states and values. The persistence class is based on
'existing database tables and a set of predefined queries.

Option Base 0

'##ModelId=3237F8CC025A
Private pRecordset As Recordset

'##ModelId=3237F8CC025D
Private pQueryDef As QueryDef

'Flag indicating the existence of records.
'##ModelId=3237F8CE03C1
Private pRecordsExists As Boolean

'##ModelId=330248950398
Public Property Get theRecordset() As Recordset
    Set theRecordset = pRecordset
End Property

'##ModelId=3302489602EE
Public Property Get theQueryDef() As QueryDef
    Set theQueryDef = pQueryDef
End Property

'Connects to an existing QueryDef object in the database.
'##ModelId=3237F8CE038E
Public Sub Connect(Query_Name As String)
    On Error GoTo Persistence_Connect__exception
    Set pQueryDef = OrderSys_Db.QueryDefs(Query_Name)
    Exit Sub
Persistence_Connect__exception:
    Resume Persistence_Connect__end
Persistence_Connect__end:
    Exit Sub
End Sub

'Runs the SQL query and builds the recordset. Modifies the
'records_exists flag.
'##ModelId=3237F8CE0390
Public Sub Execute()
    On Error GoTo Persistence_Execute__exception
    Set pRecordset = pQueryDef.OpenRecordset()
    pRecordset.MoveFirst
    If Not pRecordset.EOF Then
        pRecordsExists = True
    Else
        pRecordsExists = False
    End If
    Exit Sub
Persistence_Execute__exception:
    Resume Persistence_Execute__end
Persistence_Execute__end:
    Exit Sub
End Sub

'Flag indicating the existence of records.
'##ModelId=3237F8CE0391
Public Property Get RecordsExists() As Boolean
    On Error GoTo Persistence_RecordsExists__exception
    RecordsExists = pRecordsExists
    Exit Property
Persistence_RecordsExists__exception:
    Resume Persistence_RecordsExists__end
Persistence_RecordsExists__end:
    Exit Property
End Property

'##ModelId=3237F8CE0392
Private Sub Class_Initialize()
    On Error GoTo Persistence_Class_Initialize__exception
    Set pQueryDef = New QueryDef
    pRecords_Exists = False
    Exit Sub
Persistence_Class_Initialize__exception:
    Resume Persistence_Class_Initialize__end
Persistence_Class_Initialize__end:
    Exit Sub
End Sub

'##ModelId=3237F8CE03C0
Private Sub Class_Terminate()
    On Error GoTo Persistence_Class_Terminate__exception
    Exit Sub
Persistence_Class_Terminate__exception:
    Resume Persistence_Class_Terminate__end
Persistence_Class_Terminate__end:
    Exit Sub
End Sub

