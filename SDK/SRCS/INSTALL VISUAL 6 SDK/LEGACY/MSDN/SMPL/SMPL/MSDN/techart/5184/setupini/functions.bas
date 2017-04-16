Attribute VB_Name = "Functions"
Global LicensedUsers As Integer

Global LocalServer As New sqlole.SQLServer         ' current instance of SQL Server
Global SQLConnected As Integer  ' are we connected?
Global CurrentDevice As String  ' working dump device


Declare Function WritePrivateProfileString% Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal AppName$, ByVal KeyName$, ByVal keydefault$, ByVal FileName$)
Declare Function GetPrivateProfileString% Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal AppName$, ByVal KeyName$, ByVal keydefault$, ByVal ReturnString$, ByVal NumBytes As Integer, ByVal FileName$)

Declare Function GetLogicalDriveStrings Lib "kernel32" Alias "GetLogicalDriveStringsA" (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long
Declare Function GetDriveType Lib "kernel32" Alias "GetDriveTypeA" (ByVal nDrive As String) As Long
Declare Function GetDiskFreeSpace Lib "kernel32" Alias "GetDiskFreeSpaceA" (ByVal lpRootPathName As String, lpSectorsPerCluster As Long, lpBytesPerSector As Long, lpNumberOfFreeClusters As Long, lpTtoalNumberOfClusters As Long) As Long
Declare Function GetLogicalDrives Lib "kernel32" () As Long

Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long _
)
' GetDriveType return values
Public Const DRIVE_REMOVABLE = 2
Public Const DRIVE_FIXED = 3
Public Const DRIVE_REMOTE = 4
Public Const DRIVE_CDROM = 5
Public Const DRIVE_RAMDISK = 6


Public Type DrArray
    Name As String
    FreeSpace As Long
    RequiredSpace As Long
End Type

Public DriveArray(24) As DrArray
   Private Type STARTUPINFO
      cb As Long
      lpReserved As String
      lpDesktop As String
      lpTitle As String
      dwX As Long
      dwY As Long
      dwXSize As Long
      dwYSize As Long
      dwXCountChars As Long
      dwYCountChars As Long
      dwFillAttribute As Long
      dwFlags As Long
      wShowWindow As Integer
      cbReserved2 As Integer
      lpReserved2 As Long
      hStdInput As Long
      hStdOutput As Long
      hStdError As Long
   End Type

   Private Type PROCESS_INFORMATION
      hProcess As Long
      hThread As Long
      dwProcessID As Long
      dwThreadID As Long
   End Type

   Private Declare Function WaitForSingleObject Lib "kernel32" (ByVal _
      hHandle As Long, ByVal dwMilliseconds As Long) As Long
      
   Private Declare Function CreateProcessA Lib "kernel32" (ByVal _
      lpApplicationName As Long, ByVal lpCommandLine As String, ByVal _
      lpProcessAttributes As Long, ByVal lpThreadAttributes As Long, _
      ByVal bInheritHandles As Long, ByVal dwCreationFlags As Long, _
      ByVal lpEnvironment As Long, ByVal lpCurrentDirectory As Long, _
      lpStartupInfo As STARTUPINFO, lpProcessInformation As _
      PROCESS_INFORMATION) As Long

   Private Declare Function CloseHandle Lib "kernel32" (ByVal _
      hObject As Long) As Long

   Private Const NORMAL_PRIORITY_CLASS = &H20&
   Private Const INFINITE = -1&

Declare Function MsgWaitForMultipleObjects Lib "user32" (ByVal nCount As Long, ByRef pHandles As Long, ByVal fWaitAll As Long, ByVal dwMilliseconds As Long, ByVal dwWakeMask As Long) As Long

' GetQueueStatus flags
Public Const QS_KEY = &H1
Public Const QS_MOUSEMOVE = &H2
Public Const QS_MOUSEBUTTON = &H4
Public Const QS_POSTMESSAGE = &H8
Public Const QS_TIMER = &H10
Public Const QS_PAINT = &H20
Public Const QS_SENDMESSAGE = &H40
Public Const QS_HOTKEY = &H80

Public Const QS_MOUSE = (QS_MOUSEMOVE Or QS_MOUSEBUTTON)

Public Const QS_INPUT = (QS_MOUSE Or QS_KEY)

Public Const QS_ALLEVENTS = (QS_INPUT Or QS_POSTMESSAGE Or QS_TIMER Or QS_PAINT Or QS_HOTKEY)

Public Const QS_ALLINPUT = (QS_SENDMESSAGE Or QS_PAINT Or QS_TIMER Or QS_POSTMESSAGE Or QS_MOUSEBUTTON Or QS_MOUSEMOVE Or QS_HOTKEY Or QS_KEY)

'possible returns from MsgWaitForMultipleObjects
Public Const WAIT_OBJECT_0 = 0&
Public Const WAIT_TIMEOUT = &H102&
Public Const WAIT_ABANDONED_0 = &H80&

Public Function CreateDB(DbName As String, DbDevice As String, LogDevice As String) As Boolean
On Error GoTo CreateDBError
    
    Dim NewDB As New sqlole.Database
    
    'We want the database to take up the full device sizes as defined
    DBSize% = LocalServer.Devices(DbDevice).Size
    LogSize% = LocalServer.Devices(LogDevice).Size
    
    NewDB.Name = DbName
    DbDevice = DbDevice + "=" + Trim(Str(DBSize%))
    NewDB.ExtendOnDevices (DbDevice)
    LogDevice = LogDevice + "=" + Trim(Str(LogSize%))
    NewDB.TransactionLog.DedicateLogDevices (LogDevice)

    LocalServer.Databases.Add NewDB
    
    LocalServer.Databases(DbName).DBOption.SelectIntoBulkCopy = True
    LocalServer.Databases(DbName).DBOption.TruncateLogOnCheckpoint = True
    
    CreateDB = True
    Exit Function

CreateDBError:
    ErrorStr$ = "Create Database failed.  " + Chr(13) + "SQL-DMO error:  " _
            + Str(Err.Number - vbObjectError) + " " + Err.Description
    MsgBox ErrorStr$
    CreateDB = False
    Exit Function

End Function


   Public Sub ExecCmd(cmdline$)
      Dim Proc As PROCESS_INFORMATION
      Dim Start As STARTUPINFO
      Dim hProc As Long
      

      ' Initialize the STARTUPINFO structure:
      Start.cb = Len(Start)

      ' Start the shelled application:
      ret& = CreateProcessA(0&, cmdline$, 0&, 0&, 1&, _
         NORMAL_PRIORITY_CLASS, 0&, 0&, Start, Proc)

      ' Wait for the shelled application to finish.  Note that SQL Server setup does some
      ' posting of messages to the desktop.  If we simply waited for SQL setup to finish
      ' via WaitForSingleObject, the VB application would not be processing these messages
      ' and SQL Setup would hang.  So we use MsgWaitForMultipleObjects and the DoEvents()
      ' function to allow the VB app to process these messages and allow SQL Setup to finish
      
      'i% = 0
    Do
        ret& = MsgWaitForMultipleObjects(1&, Proc.hProcess, 0&, INFINITE, _
            (QS_POSTMESSAGE Or QS_SENDMESSAGE))
        If ret& = (WAIT_OBJECT_0) Then Exit Do   'process really ended
        OpenForms% = DoEvents()
        'i% = i% + 1
    Loop
    
      'MsgBox "returned from MsgWait " + Str(i%) + "times"
      ret& = CloseHandle(Proc.hProcess)
   End Sub

Public Function CheckForDir(DriveStr As String, DirStr As String) As Boolean

On Error GoTo CheckForDirError

CheckForDir = False

    'check the format of the dir string and see if it has correct format
    If (Left(DirStr, 1) <> "\") Or (Right(DirStr, 1) = "\") Then
        MsgBox "Directory name must start with a \ and end with a letter or number"
        Exit Function
    End If
    
    
    ' check to see if db and log dirs exist, if not create them
    fulldir$ = DriveStr + DirStr
    
    On Error Resume Next
    'Save off the current dir to reset at end
    CurrentDir$ = CurDir(DriveStr)
    
    ChDir fulldir$
    If CurDir(DriveStr) <> fulldir$ Then
        'dir does  not exist
        dirleftpart$ = DriveStr
         Startpos% = 1
         Do
            Endpos% = InStr(Startpos%, DirStr, "\")
            If Endpos% = 0 Then
                'did we get rightmost subdir?
                If Startpos% < Len(DirStr) Then
                    Length% = Len(DirStr) - Startpos% + 1
                    dirpart$ = Right(DirStr, Length%)
                    dirleftpart$ = dirleftpart$ + "\" + dirpart$
                    MkDir dirleftpart$
                End If
                Exit Do
            End If
            
            If Endpos% > 1 Then
                Length% = Endpos% - Startpos%
                dirpart$ = Mid(DirStr, Startpos%, Length%)
                dirleftpart$ = dirleftpart$ + "\" + dirpart$
                MkDir dirleftpart$
            End If
            Startpos% = Endpos% + 1
         Loop
        
    'Else
       ' MsgBox "dir exists"
    End If
    
    ChDir CurrentDir$
    
    CheckForDir = True
    Exit Function
    
CheckForDirError:
    MsgBox "Error finding or creating directory"
    
End Function
Public Function ReadIni(Section As String, KeyName As String) As String
' read the default drive and directory from setup.ini (as example)
         On Error GoTo FileError

         Dim Default$, ReturnString$, FileName$
         Dim Size%, Valid%, ReturnStr$, Succ%
         
         FileName$ = CurDir("") + "\setup.ini"
         Default$ = "Not found"
           
         ReturnString$ = String$(100, Chr$(0))
         Size% = Len(ReturnString) + 1
         
        Valid% = GetPrivateProfileString(Section, KeyName, _
                    Default$, ReturnString$, Len(ReturnString) + 1, FileName$)
     
         ReturnStr$ = Left$(ReturnString$, Valid%)
         If ReturnStr$ = "not found" Then
            MsgBox "Can't find SETUP.INI in current directory"
            End
        End If
        ReadIni = ReturnStr$
        
        Exit Function
        
FileError:
         MsgBox "Error reading INI file"
         Resume Next


End Function





Public Function GetFixedDrives() As Long
         Dim Buffer As String * 100, Drive$, DriveType%
         Dim SectorsPerCluster As Long, BytesPerSector As Long, NumberOfFreeClusters As Long, TotalNumberOfClusters As Long

   On Error GoTo DriveError
   
         DriveBits = GetLogicalDrives()
         Valid% = GetLogicalDriveStrings(100, Buffer)
         
         Startpos% = 1
         Numdrives% = 0
         For i% = 1 To 26
            Endpos% = InStr(Startpos%, Buffer, Chr$(0))
            Length% = Endpos% - Startpos%
            Drive$ = Mid(Buffer, Startpos%, Length%)
            If Drive$ = "" Then Exit For
            DriveType% = GetDriveType(Drive$)
            If DriveType% = DRIVE_FIXED Then
                DriveArray(Numdrives%).Name = Left(Drive$, 2) 'skip the \ char
                Succ% = GetDiskFreeSpace(Drive$, SectorsPerCluster, _
                    BytesPerSector, NumberOfFreeClusters, TotalNumberOfClusters)
                DriveArray(Numdrives%).FreeSpace = SectorsPerCluster * BytesPerSector * NumberOfFreeClusters / 1000000
                Numdrives% = Numdrives% + 1
            End If
            Startpos% = Endpos% + 1
         Next i%
                                  
        GetFixedDrives = Numdrives%
        Exit Function

DriveError:
         MsgBox "Error using drive query functions"
         Resume Next
        

End Function

Public Sub WriteIni(Section As String, KeyName As String, Value As String)
' read the default drive and directory from setup.ini (as example)
On Error GoTo FileError

         Dim FileName$, Valid%
         
         FileName$ = CurDir("") + "\setup.ini"
         
        Valid% = WritePrivateProfileString(Section, KeyName, Value, FileName$)
        
        If Valid% = False Then
            MsgBox "Error writing INI file"
        End If
        
        Exit Sub
        
FileError:
         MsgBox "Error writing INI file"
         Resume Next


End Sub

Public Function StartSQL() As Boolean
On Error GoTo StartSQLError

    LocalServer.LoginSecure = True

    If (LocalServer.Status = SQLOLESvc_Running) Then
        LocalServer.Connect ServerName:=""
    Else
        LocalServer.Start Server:="", StartMode:=SQLOLEStart_StartAndConnect
    End If
    
On Error Resume Next
    StartSQL = LocalServer.VerifyConnection()
    
    If StartSQL = False Then
       ErrorStr$ = "Could not start or connect to SQL Server"
        MsgBox ErrorStr$
    End If
    Exit Function
    
StartSQLError:
    ErrorStr$ = "Error starting or connecting to SQL Server  " + Chr(13) + "SQL-DMO error:  " _
            + Str(Err.Number - vbObjectError) + " " + Err.Description
    MsgBox ErrorStr$
    StartSQL = False
    Exit Function

   
End Function

Public Function CreateDevice(DevName As String, DevPath As String, DevSize As Integer) As Boolean
 On Error GoTo CreateDeviceError
 
    Dim DbDevice As New sqlole.Device
    
    DbDevice.Name = DevName
    DbDevice.PhysicalLocation = DevPath
    DbDevice.Type = SQLOLEDevice_Database
    DbDevice.Size = DevSize

    LocalServer.Devices.Add DbDevice
    CreateDevice = True
    Exit Function

CreateDeviceError:
    ErrorStr$ = "Device creation failed.  " + Chr(13) + "SQL-DMO error:  " _
            + Str(Err.Number - vbObjectError) + " " + Err.Description
    MsgBox ErrorStr$
    CreateDevice = False
    Exit Function
   
End Function

Public Function CreateTables() As Boolean
On Error GoTo CreateTablesError

    'Following is an illustration of how to use SQL-DMO to create tables.
    'An alternative is to use the Execute method to run a CREATE TABLE script
    
    Dim Table As New sqlole.Table
    Table.Name = "account"
    AddColumn Table, "id", "int"
    AddColumn Table, "branch_id", "int"
    AddColumn Table, "balance", "float"
    AddColumn Table, "filler", "char", 84
    LocalServer.Databases("xyz").Tables.Add Table
      
    Set Table = New sqlole.Table
    Table.Name = "branch"
    AddColumn Table, "id", "int"
    AddColumn Table, "branch_id", "int"
    AddColumn Table, "balance", "float"
    AddColumn Table, "filler", "char", 84
    LocalServer.Databases("xyz").Tables.Add Table
    
    Set Table = New sqlole.Table
    Table.Name = "teller"
    AddColumn Table, "id", "int"
    AddColumn Table, "branch_id", "int"
    AddColumn Table, "balance", "float"
    AddColumn Table, "filler", "char", 84
    LocalServer.Databases("xyz").Tables.Add Table
    
    Set Table = New sqlole.Table
    Table.Name = "history1"
    AddColumn Table, "account_id", "int"
    AddColumn Table, "teller_id", "int"
    AddColumn Table, "branch_id", "int"
    AddColumn Table, "amount", "float"
    AddColumn Table, "timestamp", "datetime"
    AddColumn Table, "filler", "char", 22
    LocalServer.Databases("xyz").Tables.Add Table
    
    CreateTables = True
    Exit Function
    
CreateTablesError:
    ErrorStr$ = "Create Tables failed.  " + Chr(13) + "SQL-DMO error:  " _
            + Str(Err.Number - vbObjectError) + " " + Err.Description
    MsgBox ErrorStr$
    CreateTables = False
    Exit Function

End Function

Public Sub AddColumn(Table As Object, Name As String, DataType As String, Optional Length As Variant)
    Dim Col As New sqlole.Column
    Col.Name = Name
    Col.DataType = DataType
    If Not IsMissing(Length) Then Col.Length = Length
    Col.AllowNulls = False
    Table.Columns.Add Col
End Sub

Public Function CreateProcs() As Boolean
On Error GoTo CreateProcsError
    Dim Proc As New sqlole.StoredProcedure
    Proc.Name = "TPCB_1"
    
    Cmd$ = "CREATE PROCEDURE TPCB_1 @acct   int, @teller int, @branch int, @delta  float, "
    Cmd$ = Cmd$ + " @balance float output, @filler  char(22) AS BEGIN TRANSACTION "
    Cmd$ = Cmd$ + " Update account SET   balance = balance + @delta WHERE id = @acct "
    Cmd$ = Cmd$ + " SELECT @balance = balance From account where id = @acct "
    Cmd$ = Cmd$ + " Update teller SET   balance = balance + @delta WHERE id  = @teller "
    Cmd$ = Cmd$ + " Update branch SET   balance = balance + @delta WHERE id  = @branch "
    Cmd$ = Cmd$ + " Insert history1 (account_id,teller_id,branch_id,amount,timestamp,filler) "
    Cmd$ = Cmd$ + " Values(@acct,@teller,@branch,@delta,getdate(),@filler) "
    Cmd$ = Cmd$ + " COMMIT TRANSACTION "
    
    Proc.Text = Cmd$

    LocalServer.Databases("xyz").StoredProcedures.Add Proc

    CreateProcs = True
    Exit Function
    
CreateProcsError:
    ErrorStr$ = "Create Procs failed.  " + Chr(13) + "SQL-DMO error:  " _
            + Str(Err.Number - vbObjectError) + " " + Err.Description
    MsgBox ErrorStr$
    CreateProcs = False
    Exit Function


End Function

Public Function BulkCopy() As Boolean
On Error GoTo BulkCopyError
    Dim BCPobj As New sqlole.BulkCopy
    
    BCPobj.DataFilePath = "account.dat"
    BCPobj.DataFileType = SQLOLEDataFile_TabDelimitedChar
    BCPobj.LogFilePath = "bcp.log"
    BCPobj.ErrorFilePath = "bcp.err"

    Rows = LocalServer!xyz!Account.ImportData(BCPobj)
    
    BulkCopy = True
    Exit Function
    
BulkCopyError:
    ErrorStr$ = "Bulk copy failed.  " + Chr(13) + "SQL-DMO error:  " _
            + Str(Err.Number - vbObjectError) + " " + Err.Description
    MsgBox ErrorStr$
    BulkCopy = False
    Exit Function
    
End Function

Public Function ConfigureServer(Dedicated As Boolean, Users As Integer) As Boolean
On Error GoTo ConfigureServerError
    Dim config As sqlole.Configuration
    Dim cvalue As sqlole.ConfigValue
    Dim qresults As sqlole.QueryResults
    
    Dim OrigMemory As Long, NewMemory As Long, PhysicalMemory As Long, OrigUsers As Long
    Dim ServerRunning As Boolean
    
    ServerRunning = True  'assumed coming in to this function
        
    ' Use the built-in "msver" call to get the physical memory on the machine
    Set qresults = LocalServer.ExecuteWithResults(Command:="exec xp_msver 'PhysicalMemory'")
    PhysicalMemory = qresults.GetColumnLong(Row:=1, Column:=3) + 1  'round up
    If PhysicalMemory < 16 Then
        MsgBox "Machine has less than minimum recommended memory"
        ConfigureServer = False
        Exit Function
    End If
            
    Set config = LocalServer.Configuration
    Set cvalue = config.ConfigValues("memory")
    
    OrigMemory = cvalue.CurrentValue
    
    'Configure memory based on table from admin guide
    If Dedicated = True Then
        If PhysicalMemory < 24 Then
            NewMemory = PhysicalMemory - 12
        ElseIf PhysicalMemory >= 24 And PhysicalMemory < 48 Then
            NewMemory = PhysicalMemory - 16
        ElseIf PhysicalMemory >= 48 And PhysicalMemory < 128 Then
            NewMemory = PhysicalMemory - 24
        ElseIf PhysicalMemory >= 128 And PhysicalMemory < 256 Then
            NewMemory = PhysicalMemory - 28
        ElseIf PhysicalMemory >= 256 And PhysicalMemory < 512 Then
            NewMemory = PhysicalMemory - 40
        Else
            NewMemory = PhysicalMemory - 50
        End If
    Else
        ' Following configs for non-dedicated servers are just rough suggestions
        If PhysicalMemory < 24 Then
            NewMemory = 4
        ElseIf PhysicalMemory >= 24 And PhysicalMemory < 32 Then
            NewMemory = 8
        ElseIf PhysicalMemory >= 32 And PhysicalMemory < 48 Then
            NewMemory = 12
        ElseIf PhysicalMemory >= 48 And PhysicalMemory < 64 Then
            NewMemory = 16
         Else
            NewMemory = PhysicalMemory / 2
        End If
    End If
    'convert new memory to pages
    NewMemory = NewMemory * 1048576 / 2048
       
    cvalue.CurrentValue = NewMemory
    
    'Set user connections as passed in
    Set cvalue = config.ConfigValues("user connections")
    OrigUsers = cvalue.CurrentValue
    cvalue.CurrentValue = Users
    
On Error Resume Next  'from here out need to check errors after every step

    config.ReconfigureCurrentValues
    If Err.Number <> 0 Then
        'some problem in reconfiguring, just reset back to old values
        ErrorStr$ = "Unable to reconfigure server.  " + Chr(13) + "SQL-DMO error:  " _
            + Str(Err.Number - vbObjectError) + " " + Err.Description
        MsgBox ErrorStr$
        Set config = LocalServer.Configuration
        Set cvalue = config.ConfigValues("memory")
        cvalue.CurrentValue = OrigMemory
        Set cvalue = config.ConfigValues("user connections")
        cvalue.CurrentValue = OrigUsers
        ConfigureServer = False
        Exit Function
    End If
    
    LocalServer.Shutdown
    'wait until server really shuts down
    i% = 0
    Do
    Sleep (500)
    i% = i% + 1
    If i% > 60 Then ' wait 30 seconds
        MsgBox "Could not shut down server after reconfigure."
        ConfigureServer = False
        Exit Function
    End If
    Loop Until LocalServer.Status = SQLOLESvc_Stopped
    
    ServerRunning = StartSQL()
    
    If ServerRunning = False Then
        ' SQL Server can't restart under the new settings.  This can happen if
        ' the memory is set too high for the system.
        ' Need to restart from cmd line in minimal mode and restore.
        ErrorStr$ = "Unable to reconfigure server. Attempting to reset defaults."
        MsgBox ErrorStr$
        Cmd$ = "sqlservr -c -f"
        Shell Cmd$
        Sleep (5000)
        'the SQL-DMO objects won't work in -f minimal mode so need to run an isql script
        Cmd$ = "isql -E -irestore.sql"
        Shell Cmd$
        Sleep (10000)
        ServerRunning = StartSQL()
        ConfigureServer = False
        Exit Function
    End If
    
    ConfigureServer = True
    Exit Function
    
ConfigureServerError:
    ErrorStr$ = "Unable to reconfigure server.  " + Chr(13) + "SQL-DMO error:  " _
            + Str(Err.Number - vbObjectError) + " " + Err.Description
    MsgBox ErrorStr$
    ConfigureServer = False
    Exit Function

End Function

Public Function CreateIndexes() As Boolean
On Error GoTo CreateIndexesError

    'Following is an illustration of how to use SQL-DMO to create tables.
    'An alternative is to use the Execute method to run a CREATE TABLE script
    
    Dim Table As sqlole.Table
    Dim Index As sqlole.Index
    
    Set Table = LocalServer!xyz!Account
    Set Index = New sqlole.Index
    Index.Name = "accountididx"
    Index.Type = SQLOLEIndex_Unique + SQLOLEIndex_Clustered
    'note following step-- you use IndexedColumns as a write-only property even though
    ' the documentation lists it as a method
    Index.IndexedColumns = "id"
    Table.Indexes.Add Index
    
    Set Table = LocalServer!xyz!teller
    Set Index = New sqlole.Index
    Index.Name = "tellerididx"
    Index.Type = SQLOLEIndex_Unique + SQLOLEIndex_Clustered
    Index.IndexedColumns = "id"
    Index.FillFactor = 10
    Table.Indexes.Add Index
    
    Set Table = LocalServer!xyz!branch
    Set Index = New sqlole.Index
    Index.Name = "branchididx"
    Index.Type = SQLOLEIndex_Unique + SQLOLEIndex_Clustered
    Index.IndexedColumns = "id"
    Index.FillFactor = 1
    Table.Indexes.Add Index
    
    Set Table = LocalServer!xyz!Account
    Set Index = New sqlole.Index
    Index.Name = "accountbranchidx"
    Index.Type = SQLOLEIndex_Default
    Index.IndexedColumns = "branch_id"
    Table.Indexes.Add Index
    
    
    CreateIndexes = True
    Exit Function
    
CreateIndexesError:
    ErrorStr$ = "Create Indexes failed.  " + Chr(13) + "SQL-DMO error:  " _
            + Str(Err.Number - vbObjectError) + " " + Err.Description
    MsgBox ErrorStr$
    CreateIndexes = False
    Exit Function


End Function

Public Function AddUsers() As Boolean
On Error GoTo AddUsersError

'In this case we will configure the server for integrated security.  All members of
'the local "Administrators" group are by default system administrators in SQL Server
'(This is done by Setup).  We will configure the server so that all members of the local
'"Users" group access the xyz database as user "xyzuser".
'Note the the integrated security mode takes effect next time the server is started.

    Dim Login As New sqlole.Login
    Dim User As New sqlole.User
    Dim Permission As sqlole.Permission
    
    LocalServer.IntegratedSecurity.SecurityMode = SQLOLESecurity_Integrated
    LocalServer.IntegratedSecurity.DefaultLogin = "xyzuser"
    LocalServer.IntegratedSecurity.GrantNTLogin Account:="Users", LoginType:=SQLOLEIntSecLogin_User
    
    Login.Name = "xyzuser"
    Login.Database = "xyz"
    LocalServer.Logins.Add Login
    ' though this password won't be used in integrated security, best to set
    ' it to non-null in case security mode is changed
    Login.SetPassword OldPassword:="", NewPassword:="random"
    
    User.Name = "xyzuser"
    User.Login = "xyzuser"
    LocalServer.Databases("xyz").Users.Add User
    
    'now grant select on all tables to xyzuser, but only let them update via the
    'stored procedure
    
    LocalServer.Databases("xyz").Tables("account").Grant _
            GranteeNames:="xyzuser", Privileges:=SQLOLEPriv_Select
    LocalServer.Databases("xyz").Tables("branch").Grant _
            GranteeNames:="xyzuser", Privileges:=SQLOLEPriv_Select
    LocalServer.Databases("xyz").Tables("teller").Grant _
            GranteeNames:="xyzuser", Privileges:=SQLOLEPriv_Select
    LocalServer.Databases("xyz").StoredProcedures("TPCB_1").Grant _
            GranteeNames:="xyzuser", Privileges:=SQLOLEPriv_Execute
    
    AddUsers = True
    Exit Function

AddUsersError:
    ErrorStr$ = "Security setup failed.  " + Chr(13) + "SQL-DMO error:  " _
            + Str(Err.Number - vbObjectError) + " " + Err.Description
    MsgBox ErrorStr$
    AddUsers = False
    Exit Function

End Function

Public Function AddTasks() As Boolean
On Error GoTo AddTasksError
    Dim Task As sqlole.Task
    'Add tasks to do daily and weekly maintenance.
    Set Task = New sqlole.Task
    Task.Name = "XYZ Daily Scheduled Maintenance"
    Task.ActiveStartDate = Date + #2:00:00 AM#  'run at 2am every night, starting today
    Task.Command = "SQLMAINT.EXE -D xyz -CkDB -CkAl -CkTxtAl -CkCat -BkUpLog E:\MSSQL\BACKUP -BkUpMedia DISK -Rpt E:\MSSQL\LOG\xyz_maint.rpt"
    Task.Database = "master"
    Task.Description = "Performs database checks and backs up transaction log"
    Task.EmailCompletionLevel = SQLOLEComp_None
    Task.Enabled = True
    Task.FrequencyType = SQLOLEFreq_Weekly
    Task.FrequencySubDay = SQLOLEFreqSub_Once
    Task.FrequencyInterval = SQLOLEWeek_Monday + SQLOLEWeek_Tuesday + SQLOLEWeek_Wednesday + SQLOLEWeek_Thursday + SQLOLEWeek_Friday + SQLOLEWeek_Saturday
    Task.LogHistoryCompletionLevel = SQLOLEComp_Failure
    Task.RetryAttempts = 0
    Task.SubSystem = "CmdExec"
    
    LocalServer.Executive.Tasks.Add Task
    
    Set Task = New sqlole.Task
    Task.Name = "XYZ Weekly Scheduled Maintenance"
    Task.ActiveStartDate = Date + #2:00:00 AM#  'run at 2am starting today
    Task.Command = "SQLMAINT.EXE -D xyz -UpdSts -RebldIdx 100 -BkUpDB E:\MSSQL\BACKUP -BkUpMedia DISK -DelBkUps 4 -Rpt E:\MSSQL\LOG\xyz_maint.rpt"
    Task.Database = "master"
    Task.Description = "Backs up entire database, updates statistics and rebuilds indexes"
    Task.EmailCompletionLevel = SQLOLEComp_None
    Task.Enabled = True
    Task.FrequencyType = SQLOLEFreq_Weekly
    Task.FrequencySubDay = SQLOLEFreqSub_Once
    Task.FrequencyInterval = SQLOLEWeek_Sunday  'run this task only on Sunday night
    Task.LogHistoryCompletionLevel = SQLOLEComp_Failure
    Task.RetryAttempts = 0
    Task.SubSystem = "CmdExec"
    
    LocalServer.Executive.Tasks.Add Task
    
    'Now that transaction log backup task is defined, we need to turn off the truncate on
    'checkpoint option and initiate a full database backup in order to allow this to succeed.
    'We'll backup to the diskdump device because we don't need to save it.
    Dim dummy_backup As New sqlole.Backup
    dummy_backup.DumpDevices = "diskdump"
    
    LocalServer.Databases("xyz").DBOption.TruncateLogOnCheckpoint = False
    LocalServer.Databases("xyz").Dump dummy_backup
    
    
    AddTasks = True
    Exit Function

AddTasksError:
    ErrorStr$ = "Scheduled Maintenance setup failed  " + Chr(13) + "SQL-DMO error:  " _
            + Str(Err.Number - vbObjectError) + " " + Err.Description
    MsgBox ErrorStr$
    AddTasks = False
    Exit Function



End Function
