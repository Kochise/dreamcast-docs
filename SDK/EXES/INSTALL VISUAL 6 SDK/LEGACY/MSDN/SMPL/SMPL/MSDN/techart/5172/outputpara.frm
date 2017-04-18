VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   5340
   ClientLeft      =   48
   ClientTop       =   276
   ClientWidth     =   5124
   LinkTopic       =   "Form1"
   ScaleHeight     =   5340
   ScaleWidth      =   5124
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton BLOB 
      Caption         =   "BLOB"
      Height          =   372
      Left            =   3360
      TabIndex        =   17
      Top             =   4080
      Width           =   1332
   End
   Begin VB.CommandButton ServerCurs 
      Caption         =   "ServerCurs"
      Height          =   372
      Left            =   1800
      TabIndex        =   16
      Top             =   4080
      Width           =   1332
   End
   Begin VB.CommandButton UpdateBatch 
      Caption         =   "UpdateBatch"
      Height          =   372
      Left            =   3360
      TabIndex        =   15
      Top             =   3600
      Width           =   1332
   End
   Begin VB.CommandButton StoredProc 
      Caption         =   "StoredProc"
      Height          =   372
      Left            =   240
      TabIndex        =   14
      Top             =   3600
      Width           =   1332
   End
   Begin VB.CommandButton DDL 
      Caption         =   "DDL"
      Height          =   372
      Left            =   240
      TabIndex        =   13
      Top             =   3120
      Width           =   1332
   End
   Begin VB.CommandButton Prepared 
      Caption         =   "prepared"
      Height          =   372
      Left            =   1800
      TabIndex        =   12
      Top             =   3120
      Width           =   1332
   End
   Begin VB.CommandButton Field 
      Caption         =   "Field"
      Height          =   372
      Left            =   1800
      TabIndex        =   11
      Top             =   1800
      Width           =   1332
   End
   Begin VB.CommandButton Recordset1 
      Caption         =   "Recordset1"
      Height          =   372
      Left            =   240
      TabIndex        =   10
      Top             =   1800
      Width           =   1332
   End
   Begin VB.CommandButton Parameter 
      Caption         =   "Parameter"
      Height          =   372
      Left            =   3360
      TabIndex        =   9
      Top             =   1200
      Width           =   1332
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Command2"
      Height          =   372
      Left            =   1800
      TabIndex        =   8
      Top             =   1200
      Width           =   1332
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Command1"
      Height          =   372
      Left            =   240
      TabIndex        =   7
      Top             =   1200
      Width           =   1332
   End
   Begin VB.CommandButton Transaction 
      Caption         =   "Transaction"
      Height          =   372
      Left            =   3360
      TabIndex        =   6
      Top             =   120
      Width           =   1332
   End
   Begin VB.CommandButton GetError 
      Caption         =   "GetError"
      Height          =   372
      Left            =   240
      TabIndex        =   5
      Top             =   720
      Width           =   1332
   End
   Begin VB.CommandButton Connection2 
      Caption         =   "Connection2"
      Height          =   372
      Left            =   1800
      TabIndex        =   4
      Top             =   120
      Width           =   1332
   End
   Begin VB.CommandButton Connection1 
      Caption         =   "Connection1"
      Height          =   372
      Left            =   240
      TabIndex        =   3
      Top             =   120
      Width           =   1332
   End
   Begin VB.CommandButton GetProperties 
      Caption         =   "GetProperties"
      Height          =   372
      Left            =   240
      TabIndex        =   2
      Top             =   2520
      Width           =   1332
   End
   Begin VB.CommandButton NextRecord 
      Caption         =   "NextRecord"
      Height          =   372
      Left            =   240
      TabIndex        =   1
      Top             =   4080
      Width           =   1332
   End
   Begin VB.CommandButton OutputPara 
      Caption         =   "OutputPara"
      Height          =   372
      Left            =   1800
      TabIndex        =   0
      Top             =   3600
      Width           =   1332
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'
' Use the default OLE DB provider, the ODBC provider,
' to connect to SQL Server.
'
Private Sub Connection1_Click()
Dim Cn As New ADODB.Connection
        
Cn.ConnectionTimeout = 100
'dsn connection
Cn.Open "pubs", "sa"
'dsn-less connection for SQL Server
'Cn.Open "Driver={SQL Server};Server=joycec3;Uid=sa;Pwd=;Database=pubs"
    
Cn.Close
    
End Sub
'
'Use the Provider property to specify an alternative OLE DB provider
'
Private Sub Connection2_Click()
Dim Cn As New ADODB.Connection
Dim rs As ADODB.Recordset

Cn.Provider = "sampprov"
Cn.Open "data source=c:\sdks\oledbsdk\samples\sampclnt\"
Set rs = Cn.Execute("customer.csv")
        For i = 0 To rs.Fields.Count - 1
            Debug.Print rs.Fields(i).Name
        Next i
        While Not rs.EOF
            Debug.Print rs(0)
            rs.MoveNext
        Wend
Cn.Close
End Sub
'
' Use the OpenTrans and CommitTrans or RollbackTrans method
'
Private Sub Transaction_Click()
Dim Cn As New ADODB.Connection
Dim rs As New ADODB.Recordset

' Open connection.
Cn.Open "pubs", "sa"

' Open titles table.
rs.Open "select * from titles", Cn, adOpenDynamic, adLockPessimistic
Cn.BeginTrans
'<<make changes>>
Cn.CommitTrans
'or rollback
'cn.RollbackTrans
Cn.Close
End Sub
'
' Retrieve SQL state, native error and error description
' from the error object when using the ODBC provider
'
Private Sub GetError_Click()
Dim Cn As New ADODB.Connection
Dim Errs1 As ADODB.Errors
Dim rs As New ADODB.Recordset
Dim i As Integer
Dim StrTmp

On Error GoTo AdoError
Cn.Open "pubs", "sa"
Set rs = Cn.Execute("select * from DoesnotExistTable")
Done:
      ' Close all open objects
      Cn.Close
      ' Destroy anything not destroyed yet
      Set Cn = Nothing
      ' We're outta here
      Exit Sub

AdoError:
      Dim errLoop As Error
      Dim strError As String

      ' Enumerate Errors collection and display properties of
      ' each Error object.
      Set Errs1 = Cn.Errors
      For Each errLoop In Errs1
            Debug.Print errLoop.SQLState
            Debug.Print errLoop.NativeError
            Debug.Print errLoop.Description
      Next

      GoTo Done

End Sub
'
' Execute a select statement that returns a Recordset object
'
Private Sub Command1_Click()
Dim Cmd As New ADODB.Command
Dim rs As New ADODB.Recordset

'use a connection string or a Connection object
Cmd.ActiveConnection = "DSN=pubs;UID=sa"
Cmd.CommandText = "select * from titles"
Cmd.CommandTimeout = 15
Cmd.CommandType = adCmdText

Set rs = Cmd.Execute()
rs.Close

End Sub
'
' Executing a stored procedure that does not return a Recordset object.
'
' stored procedure syntax
' drop proc myADOProc
' go
' create proc myADOProc as
' create table #tmpADO (id int not NULL, name char(10) NOT NULL)
' insert into #tmpADO values(1, 'test')
'
Private Sub Command2_Click()
Dim Cmd As New ADODB.Command

' use a connection string or a Connection object
Cmd.ActiveConnection = "DSN=pubs;UID=sa"
Cmd.CommandText = "myADOProc"
Cmd.CommandTimeout = 15
Cmd.CommandType = adCmdStoredProc

Cmd.Execute

End Sub
'
' Create parameters for a stored procedure
'
' the stored procedure syntax:
'
' drop proc myADOParaProc
' go
' create proc myADOParaProc
' @type char(12)
' as
' select * from titles where type
'
Private Sub Parameter_Click()
Dim Cmd As New ADODB.Command
Dim rs As New ADODB.Recordset
Dim prm As ADODB.Parameter
           
' Define a command object for a stored procedure.
Cmd.ActiveConnection = "DSN=pubs;uid=sa"
Cmd.CommandText = "myADOParaProc"
Cmd.CommandType = adCmdStoredProc
Cmd.CommandTimeout = 15
        
Set prm = Cmd.CreateParameter("Type", adChar, adParamInput, 12, "Business")
Cmd.Parameters.Append prm

' Create a recordset by executing the command.
Set rs = Cmd.Execute
    While (Not rs.EOF)
        Debug.Print rs(0)
        rs.MoveNext
    Wend
End Sub
'
' Use the Recordset object to open a connection and retrieve a resultset
'
Private Sub Recordset1_Click()
Dim rs As New ADODB.Recordset

rs.Open "select * from titles", "DSN=pubs;UID=sa"

While (Not rs.EOF)
    Debug.Print rs(0)
    rs.MoveNext
Wend
rs.Close
End Sub
'
' Use the Field object to retrieve the name, type and values of
' each data field of the current record
'
Private Sub Field_Click()
Dim rs As New ADODB.Recordset
Dim fld As ADODB.Field

rs.Open "select * from titles", "DSN=pubs;UID=sa"
Set Flds = rs.Fields
Dim TotalCount As Integer
TotalCount = Flds.Count
i = 0
For Each fld In Flds
    Debug.Print fld.Name
    Debug.Print fld.Type
    Debug.Print fld.Value
Next
rs.Close
End Sub
'
' Retrieve "Connection Timeout", "Command Time Out"
' and "Updatability" property
'
Private Sub GetProperties_Click()
Dim Cn As New ADODB.Connection
Dim Cmd As New ADODB.Command
Dim rs As New ADODB.Recordset
    
Cn.Open "pubs", "sa"
' find out connection timeout property
Set prop1 = Cn.Properties("Connect Timeout")
Debug.Print prop1.Value
    
Set Cmd.ActiveConnection = Cn
Cmd.CommandText = "titles"
Cmd.CommandType = adCmdTable
Set rs = Cmd.Execute()
    
' find out command timeout property
Set prop2 = Cmd.Properties("Command Time out")
Debug.Print prop2.Value
    
Set prop3 = rs.Properties("Updatability")
Debug.Print prop3.Value
    
End Sub
'
' Use the Command object to create a table
'
Private Sub DDL_Click()
Dim Cn As New ADODB.Connection
Dim Cmd As New ADODB.Command

'if the ADOTestTable does not exist
On Error GoTo AdoError

Cn.Open "pubs", "sa"
Set Cmd.ActiveConnection = Cn
Cmd.CommandText = "drop table ADOTestTable"
Cmd.CommandType = adCmdText
Cmd.Execute

Done:
    Cmd.CommandText = "set nocount on"
    Cmd.Execute
    Cmd.CommandText = "create table ADOTestTable (id int, name char(100))"
    Cmd.Execute
    Cmd.CommandText = "insert into ADOTestTable values(1, 'Jane Doe')"
    Cmd.Execute
    Cn.Close
Exit Sub

AdoError:
      Dim errLoop As Error
      Dim strError As String

      ' Enumerate Errors collection and display properties of
      ' each Error object.
      Set Errs1 = Cn.Errors
      For Each errLoop In Errs1
            Debug.Print errLoop.SQLState
            Debug.Print errLoop.NativeError
            Debug.Print errLoop.Description
      Next

      GoTo Done

End Sub
'
' Prepared an updating query and dynamically construct the query
' with different set of parameters at execution time
'
Private Sub Prepared_Click()
Dim Cn As New ADODB.Connection
Dim Cmd As New ADODB.Command
Dim prm1 As New ADODB.Parameter
Dim prm2 As New ADODB.Parameter

Cn.Open "DSN=pubs", "sa"
Set Cmd.ActiveConnection = Cn
Cmd.CommandText = "update titles set type=? where title_id=?"
Cmd.CommandType = adCmdText
Cmd.Prepared = True
  
Set prm1 = Cmd.CreateParameter("Type", adChar, adParamInput, 12, "New Bus")
Cmd.Parameters.Append prm1
  
Set prm2 = Cmd.CreateParameter("Title_id", adChar, adParamInput, 6, "BU7832")
Cmd.Parameters.Append prm2

Cmd("Type") = "New Cook"
Cmd("title_id") = "TC7777"
Cmd.Execute

Cmd("Type") = "Cook"
Cmd("title_id") = "TC7778"
Cmd.Execute
Cn.Close
End Sub
'
' Executing the SP_WHO SQL server system stored procedure
'
Private Sub StoredProc_Click()
Dim Cmd As New ADODB.Command
Dim rs As New ADODB.Recordset

Cmd.ActiveConnection = "DSN=pubs;uid=sa"
Cmd.CommandText = "sp_who"
Cmd.CommandType = adCmdStoredProc

Set rs = Cmd.Execute()
Debug.Print rs(0)
rs.Close

End Sub
'
' retrieve the return and output parameter from a stored procedure
'
' the stored procedure syntax:
'
' CREATE PROCEDURE myProc @ioparm int OUTPUT AS
' SELECT name FROM sysusers WHERE uid < 2
' SELECT @ioparm = 88
' RETURN 99
'
Private Sub OutputPara_Click()
Dim Cmd As New ADODB.Command
Dim rs As New ADODB.Recordset
Dim param As Parameter
    
Cmd.ActiveConnection = "DSN=pubs;UID=sa"
Cmd.CommandText = "myproc"
Cmd.CommandType = adCmdStoredProc

'setup Parameters
Set param = Cmd.CreateParameter("Return", adInteger, adParamReturnValue, , 0)
Cmd.Parameters.Append param
            
Set param = Cmd.CreateParameter("Output", adInteger, adParamOutput, , 0)
Cmd.Parameters.Append param

Set rs = Cmd.Execute
If Not rs.EOF And Not rs.BOF Then
   Debug.Print rs(0)
End If
rs.Close
Debug.Print Cmd(0) 'The return code
Debug.Print Cmd(1) 'The Output Paramater

End Sub
'
' Use the UpdateBatch method to apply all the pending changes
'
Private Sub UpdateBatch_Click()
Dim rs As New ADODB.Recordset

rs.CursorType = adOpenKeyset
rs.LockType = adLockBatchOptimistic
rs.Open "select * from titles", "DSN=pubs;uid=sa"
        
' change the type for a specified title.
While (Not rs.EOF)
    If Trim(rs("Type")) = "trad_cook" Then
       rs("Type") = "Cook"
    End If
    rs.MoveNext
Wend
rs.UpdateBatch
rs.Close
    
End Sub
'
' Use NextRecordset method to fetch multiple recordsets
'
' the stored procedure syntax:
' drop proc myNextproc
' go
' create proc myNextproc
' as
' select * from titles
' select * from publishers
' go
Private Sub NextRecord_Click()
Dim Cmd As New ADODB.Command
Dim rs As ADODB.Recordset
    
Cmd.ActiveConnection = "DSN=pubs;UID=sa"
Cmd.CommandText = "myNextProc"
Cmd.CommandType = adCmdStoredProc

Set rs = Cmd.Execute()
While Not rs Is Nothing
    If (Not rs.EOF) Then
        Debug.Print rs(0)
    End If
    Set rs = rs.NextRecordset()
Wend
End Sub
'
' Open a dynamic server side cursor,
'
Private Sub ServerCurs_Click()
Dim rs As New ADODB.Recordset

rs.Open "select * from titles", "DSN=pubs;UID=sa", adOpenDynamic, adLockOptimistic

rs.Close
End Sub
'
' Read and write data using AppendChunk and GetChunk methods
'
Private Sub BLOB_Click()
Dim Cn As New ADODB.Connection
Dim rsRead As New ADODB.Recordset
Dim rsWrite As New ADODB.Recordset
Dim strChunk As String
Dim Offset As Long
Dim Totalsize As Long
Dim ChunkSize As Long

Cn.Open "pubs", "sa"

rsRead.CursorType = adOpenStatic
rsRead.Open "select pr_info from pub_info", Cn

rsWrite.CursorType = adOpenKeyset
rsWrite.LockType = adLockBatchOptimistic
rsWrite.Open "select * from myBLOB", Cn

ChunkSize = 1000
Totalsize = rsRead("pr_info").ActualSize

Do While Offset < Totalsize
    strChunk = rsRead("pr_info").GetChunk(ChunkSize)
    Offset = Offset + ChunkSize
    rsWrite("info").AppendChunk strChunk
Loop
rsWrite.UpdateBatch
rsWrite.Close
rsRead.Close
End Sub
