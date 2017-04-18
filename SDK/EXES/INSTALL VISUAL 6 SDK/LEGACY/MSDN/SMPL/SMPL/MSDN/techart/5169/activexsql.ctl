VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.1#0"; "COMCTL32.OCX"
Begin VB.UserControl ctlActiveXSQL 
   ClientHeight    =   3000
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4815
   PropertyPages   =   "ActiveXSQL.ctx":0000
   ScaleHeight     =   3000
   ScaleWidth      =   4815
   ToolboxBitmap   =   "ActiveXSQL.ctx":0019
   Begin ComctlLib.TreeView TreeView1 
      Height          =   2775
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   4575
      _ExtentX        =   8070
      _ExtentY        =   4895
      _Version        =   327680
      Indentation     =   529
      LabelEdit       =   1
      Sorted          =   -1  'True
      Style           =   7
      ImageList       =   "ImageList1"
      BorderStyle     =   1
      Appearance      =   1
      MouseIcon       =   "ActiveXSQL.ctx":032B
   End
   Begin ComctlLib.ImageList ImageList1 
      Left            =   2760
      Top             =   120
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483648
      ImageWidth      =   18
      ImageHeight     =   18
      MaskColor       =   -2147483638
      _Version        =   327680
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   16
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":0347
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":04B1
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":0627
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":0791
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":0B2B
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":0C95
            Key             =   ""
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":0DE7
            Key             =   ""
         EndProperty
         BeginProperty ListImage8 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":0F11
            Key             =   ""
         EndProperty
         BeginProperty ListImage9 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":106F
            Key             =   ""
         EndProperty
         BeginProperty ListImage10 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":11C1
            Key             =   ""
         EndProperty
         BeginProperty ListImage11 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":1313
            Key             =   ""
         EndProperty
         BeginProperty ListImage12 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":1489
            Key             =   ""
         EndProperty
         BeginProperty ListImage13 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":15DB
            Key             =   ""
         EndProperty
         BeginProperty ListImage14 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":175D
            Key             =   ""
         EndProperty
         BeginProperty ListImage15 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":18D3
            Key             =   ""
         EndProperty
         BeginProperty ListImage16 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "ActiveXSQL.ctx":1BFD
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuDevice 
      Caption         =   "Device"
      Visible         =   0   'False
      Begin VB.Menu mnuNewDevice 
         Caption         =   "&New Device..."
      End
      Begin VB.Menu mnuDeleteDevice 
         Caption         =   "&Delete"
      End
   End
   Begin VB.Menu mnuDatabase 
      Caption         =   "Database"
      Begin VB.Menu mnuNewDatabase 
         Caption         =   "&New Database..."
      End
      Begin VB.Menu mnuDeleteDatabase 
         Caption         =   "&Delete"
      End
   End
End
Attribute VB_Name = "ctlActiveXSQL"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private pvtLoginID As String
Private pvtPassword As String
Private pvtSQLServer As String

Private mnuContextMenu As Menu
Private SelectedDatabase As String
Private SelectedDevice As String
Public Function AddDatabase(ByVal DatabaseName As String, ByVal DeviceName As String, ByVal DeviceSizeinMegabytes As Integer, ByVal LogDevice As String, ByVal LogSizeInMegabytes As Integer)
Attribute AddDatabase.VB_Description = "Allows you to add databases dynamically."
    'This is a publicly exposed method of the control
    'so that you may call the add database method without
    'using my visual interface.
    On Error GoTo errorhandler
    
    Dim objSQLServer As sqlole.SQLServer
    Dim MyDatabase As sqlole.Database
    Dim MyDevice As String, mylogdevice As String
    
    'The device size needs to be in the form: Mydevice=2000
    ' for a 2MB device named mydevice
    MyDevice = DeviceName & "=" & DeviceSizeinMegabytes & "000"
    mylogdevice = LogDevice & "=" & LogSizeInMegabytes & "000"
    
    Set objSQLServer = CreateObject("SQLOLE.SQLSERVER")
    
    'Connect to SQL Server
    objSQLServer.Connect ServerName:=pvtSQLServer, login:=pvtLoginID, Password:=pvtPassword
    
    Set MyDatabase = CreateObject("SQLOLE.Database")
    With MyDatabase
        .CreateForLoad = False
        .ExtendOnDevices DeviceNames:=MyDevice
        .Name = DatabaseName
        .TransactionLog.DedicateLogDevices DeviceNames:=mylogdevice
    End With
    
    objSQLServer.Databases.Add MyDatabase
    objSQLServer.Databases.Refresh
    
    'Clean Up
    objSQLServer.DisConnect
    Set MyDatabase = Nothing
    Set objSQLServer = Nothing
        
    'Add the new database to the TreeView control
    AddDatabaseToTree DatabaseName
    
exitfunction:
    Exit Function

errorhandler:
    MsgBox Error
    Resume exitfunction
End Function

Public Function AddDevice(ByVal DeviceName As String, ByVal Location As String, ByVal DeviceSizeinMegabytes As Integer)
    'This is a publicly exposed method of the control
    'so that you may call the add device method without
    'using my visual interface.

    On Error GoTo errorhandler
    
    Dim objSQLServer As sqlole.SQLServer
    Dim MyDevice As sqlole.device
    
    Set MyDevice = CreateObject("SQLOLE.DEVICE")
        
    'Set the properties of the new device
    MyDevice.PhysicalLocation = Location
    MyDevice.Name = DeviceName
    MyDevice.Size = DeviceSizeinMegabytes
    MyDevice.Type = SQLOLEDevice_Database
        
    Set objSQLServer = CreateObject("SQLOLE.SQLSERVER")
    
    'Connect to SQL Server
    objSQLServer.Connect ServerName:=pvtSQLServer, login:=pvtLoginID, Password:=pvtPassword
        
    'Add the device to SQL Server
    objSQLServer.Devices.Add MyDevice
    
    'Refresh the list in SQL Server
    objSQLServer.Databases.Refresh
    
    'Clean up
    objSQLServer.DisConnect
    Set MyDevice = Nothing
    Set objSQLServer = Nothing
    
    'Add the new device to the TreeView control
    AddDeviceToTree DeviceName
    
exitfunction:
    Exit Function

errorhandler:
    MsgBox Error
    Resume exitfunction
End Function


Public Function DeleteDatabase(ByVal DatabaseName As String)
    'This is a publicly exposed method of the control
    'so that you may call the delete database method without
    'using my visual interface.
    On Error GoTo errorhandler
    
    Dim objSQLServer As sqlole.SQLServer
    
    Set objSQLServer = CreateObject("SQLOLE.SQLSERVER")
    
    'Connect to SQL Server
    objSQLServer.Connect ServerName:=pvtSQLServer, login:=pvtLoginID, Password:=pvtPassword
    
    'Remove the database from SQL Server
    objSQLServer.Databases.Remove DatabaseName
    
     'Refresh the list in SQL Server
    objSQLServer.Databases.Refresh
    
    'Clean up
    objSQLServer.DisConnect
    Set objSQLServer = Nothing
    
    'Remove the database from the treeview control
    RemoveDatabaseFromTree DatabaseName
    
exitfunction:
    Exit Function

errorhandler:
    MsgBox Error
    Resume exitfunction
End Function
Public Function DeleteDevice(ByVal DeviceName As String)
    'This is a publicly exposed method of the control
    'so that you may call the delete device method without
    'using my visual interface.
    On Error GoTo errorhandler
    
    Dim objSQLServer As sqlole.SQLServer
    
    Set objSQLServer = CreateObject("SQLOLE.SQLSERVER")
    
    'Connect to SQL Server
    objSQLServer.Connect ServerName:=pvtSQLServer, login:=pvtLoginID, Password:=pvtPassword
    
    objSQLServer.Devices.Remove DeviceName
    objSQLServer.Devices.Refresh
    
    'Clean up
    objSQLServer.DisConnect
    Set objSQLServer = Nothing
    
    'Remove the device from the treeview control
    RemoveDeviceFromTree DeviceName
    
exitfunction:
    Exit Function

errorhandler:
    MsgBox Error
    Resume exitfunction
End Function

Private Function AddDatabaseToTree(DatabaseName As String)
    'This function adds the database (DatabaseName) into
    'the treeview control.
    
    On Error GoTo errorhandler
    
    Dim nodx As comctllib.node

    'Add the database to the tree
    Set nodx = TreeView1.Nodes.Add("RTDatabases", tvwChild, "db" & DatabaseName, DatabaseName, 7)
    
    'Add Sub Member - Groups
    Set nodx = TreeView1.Nodes.Add("db" & DatabaseName, tvwChild, "GUGroups/Users" & DatabaseName, "Groups/Users", 4)
    
    'Add Sub Member - Objects
    Set nodx = TreeView1.Nodes.Add("db" & DatabaseName, tvwChild, "RTObjects" & DatabaseName, "Objects", 4)
    
    'Add Objects-Sub Members - Tables
    Set nodx = TreeView1.Nodes.Add("RTObjects" & DatabaseName, tvwChild, "TBTables" & DatabaseName, "Tables", 4)
    
    'Add Objects-Sub Members - Views
    Set nodx = TreeView1.Nodes.Add("RTObjects" & DatabaseName, tvwChild, "VWViews" & DatabaseName, "Views", 4)
    
    'Add Objects-Sub Members - Stored Procedures
    Set nodx = TreeView1.Nodes.Add("RTObjects" & DatabaseName, tvwChild, "SPStored Procedures" & DatabaseName, "Stored Procedures", 4)
    
    'Add Objects-Sub Members - Rules
    Set nodx = TreeView1.Nodes.Add("RTObjects" & DatabaseName, tvwChild, "RURules" & DatabaseName, "Rules", 4)
    
    'Add Objects-Sub Members - Defaults
    Set nodx = TreeView1.Nodes.Add("RTObjects" & DatabaseName, tvwChild, "DFDefaults" & DatabaseName, "Defaults", 4)
    
    'Add Objects-Sub Members - User Defined Types
    Set nodx = TreeView1.Nodes.Add("RTObjects" & DatabaseName, tvwChild, "UDUser Defined Types" & DatabaseName, "User Defined Types", 4)
exitfunction:
    Exit Function
errorhandler:
        Select Case Err
        Case 91
            'Duplicate key in collection
        Case 35602
            'Duplicate Key in collection
            Resume Next
        Case 35601
            'Duplicate Key in collection
            Resume Next
        Case Else
            MsgBox Error
    End Select
    
    Resume exitfunction
End Function
Private Function AddDeviceToTree(DeviceName As String)
    'This function adds the device (DeviceName) into
    'the treeview control.
    
    On Error GoTo errorhandler
    
    Dim nodx As comctllib.node
       
    'Add the Device to the treeview control
    Set nodx = TreeView1.Nodes.Add("RTDevices", tvwChild, "dv" & DeviceName, DeviceName, 5)
        
exitfunction:
    Exit Function
errorhandler:
        Select Case Err
        Case 91
            'Duplicate key in collection
        Case 35602
            'Duplicate Key in collection
            Resume Next
        Case 35601
            'Duplicate Key in collection
            Resume Next
        Case Else
            MsgBox Error
    End Select
    
    Resume exitfunction
End Function

Private Function RemoveDatabaseFromTree(DatabaseName As String)
    'This function removes the database (DatabaseName) from
    'the treeview control.
    On Error GoTo errorhandler
    
    Dim nodx As comctllib.node
    
    'Remove the database from the treeview control
    TreeView1.Nodes.Remove "db" & DatabaseName
    
exitfunction:
    Exit Function
errorhandler:
        Select Case Err
        Case 91
            'Duplicate key in collection
        Case 35602
            'Duplicate Key in collection
            Resume Next
        Case 35601
            'Duplicate Key in collection
            Resume Next
        Case Else
            MsgBox Error
    End Select
    
    Resume exitfunction
End Function
Private Function RemoveDeviceFromTree(DeviceName As String)
    'This function removes the device (DeviceName) from
    'the treeview control.
    On Error GoTo errorhandler
    
    Dim nodx As comctllib.node
    
    'Remove the device from the treeview control
    TreeView1.Nodes.Remove "dv" & DeviceName
    
exitfunction:
    Exit Function
errorhandler:
        Select Case Err
        Case 91
            'Duplicate key in collection
        Case 35602
            'Duplicate Key in collection
            Resume Next
        Case 35601
            'Duplicate Key in collection
            Resume Next
        Case Else
            MsgBox Error
    End Select
    
    Resume exitfunction
End Function

Private Sub AddTables(node As comctllib.node)
    'This function inserts all the tables of the selected database
    'into the treeview control.
    
    On Error GoTo errorhandler
    Dim objSQLServer As sqlole.SQLServer, CurrentDatabase As String
    Dim Table As sqlole.Table, Database As sqlole.Database
    
    Set objSQLServer = CreateObject("SQLOLE.SQLserver")
    
    'Connect to SQL Server
    objSQLServer.Connect ServerName:=pvtSQLServer, login:=pvtLoginID, Password:=pvtPassword
    
    'Retrieve the current database name
    CurrentDatabase = node.Parent.Parent.Text
    
    'Connect to that database in SQL Server
    Set Database = objSQLServer.Databases(CurrentDatabase)
    
    'Add each table in the database
    For Each Table In Database.Tables
        TreeView1.Nodes.Add node.Key, tvwChild, "TA" & Table.Name & CurrentDatabase, Table.Name, 9
    Next
    
    'Expand the treeview node
    node.Expanded = True
    
    'Clean up
    objSQLServer.DisConnect
    Set objSQLServer = Nothing
    Set Table = Nothing
    Set Database = Nothing
    
exitsub:
    Exit Sub
    
errorhandler:
    MsgBox Error
    Resume exitsub
End Sub
Private Sub AddViews(node As comctllib.node)
    'This function inserts all the views of the selected database
    'into the treeview control.
    
    On Error GoTo errorhandler
    Dim objSQLServer As sqlole.SQLServer, CurrentDatabase As String
    Dim view As sqlole.view, Database As sqlole.Database
    
    Set objSQLServer = CreateObject("SQLOLE.SQLserver")
    
    'Connect to SQL Server
    objSQLServer.Connect ServerName:=pvtSQLServer, login:=pvtLoginID, Password:=pvtPassword
    
    'Retrieve the name of the current database
    CurrentDatabase = node.Parent.Parent.Text
    
    'Connect to the database
    Set Database = objSQLServer.Databases(CurrentDatabase)
    
    'Iterate through the views in the database
    For Each view In Database.Views
        TreeView1.Nodes.Add node.Key, tvwChild, "VI" & view.Name & CurrentDatabase, view.Name, 10
    Next
    
    'Expand the treeview node
    node.Expanded = True
    
    'Clean up
    objSQLServer.DisConnect
    Set objSQLServer = Nothing
    Set view = Nothing
    Set Database = Nothing
    
exitsub:
    Exit Sub
    
errorhandler:
    MsgBox Error
    Resume exitsub
End Sub

Private Sub AddDatabaseObject(node As comctllib.node, DatabaseObject As String, Prefix As String, ImageListPosition As Integer)
    'This function inserts all the Stored Procedures of the selected database
    'into the treeview control.
    On Error GoTo errorhandler
    Dim objSQLServer As sqlole.SQLServer, CurrentDatabase As String
    Dim dbObject As Object, Database As sqlole.Database
    
    Set objSQLServer = CreateObject("SQLOLE.SQLserver")
    
    'Connect to SQL Server
    objSQLServer.Connect ServerName:=pvtSQLServer, login:=pvtLoginID, Password:=pvtPassword
    
    'Get the name of the current database
    CurrentDatabase = node.Parent.Parent.Text
    
    'Connect to the database in SQL Server
    Set Database = objSQLServer.Databases(CurrentDatabase)
    
    'Iterate through the list of objects adding them to the treeview
    For Each dbObject In Database.[DatabaseObject]
        TreeView1.Nodes.Add node.Key, tvwChild, Prefix & dbObject.Name & CurrentDatabase, dbObject.Name, ImageListPosition
    Next
    
    'Expand the treeview node
    node.Expanded = True
    
    'Clean Up
    objSQLServer.DisConnect
    Set objSQLServer = Nothing
    Set dbObject = Nothing
    Set Database = Nothing
    
exitsub:
    Exit Sub
    
errorhandler:
    MsgBox Error
    Resume exitsub
End Sub

Private Sub AddStoredProcedures(node As comctllib.node)
    'This function inserts all the Stored Procedures of the selected database
    'into the treeview control.
    On Error GoTo errorhandler
    Dim objSQLServer As sqlole.SQLServer, CurrentDatabase As String
    Dim StoredProc As sqlole.StoredProcedure, Database As sqlole.Database
    
    Set objSQLServer = CreateObject("SQLOLE.SQLserver")
    
    'Connect to SQL Server
    objSQLServer.Connect ServerName:=pvtSQLServer, login:=pvtLoginID, Password:=pvtPassword
    
    'Get the name of the current database
    CurrentDatabase = node.Parent.Parent.Text
    
    '
    Set Database = objSQLServer.Databases(CurrentDatabase)
    For Each StoredProc In Database.StoredProcedures
        TreeView1.Nodes.Add node.Key, tvwChild, "ST" & StoredProc.Name & CurrentDatabase, StoredProc.Name, 11
    Next
    
    node.Expanded = True
    
    objSQLServer.DisConnect
    
exitsub:
    Exit Sub
    
errorhandler:
    MsgBox Error
    Resume exitsub
End Sub


Private Sub AddRules(node As comctllib.node)
    On Error GoTo errorhandler
    Dim objSQLServer As sqlole.SQLServer, CurrentDatabase As String
    Dim Rule As sqlole.Rule, Database As sqlole.Database
    
    Set objSQLServer = CreateObject("SQLOLE.SQLserver")
    
    'Connect to SQL Server
    objSQLServer.Connect ServerName:=pvtSQLServer, login:=pvtLoginID, Password:=pvtPassword
    
    CurrentDatabase = node.Parent.Parent.Text
    
    Set Database = objSQLServer.Databases(CurrentDatabase)
    For Each Rule In Database.Rules
        TreeView1.Nodes.Add node.Key, tvwChild, "R1" & Rule.Name & CurrentDatabase, Rule.Name, 12
    Next
    
    node.Expanded = True
    
    objSQLServer.DisConnect
    
exitsub:
    Exit Sub
    
errorhandler:
    MsgBox Error
    Resume exitsub
End Sub



Private Sub AddDefaults(node As comctllib.node)
    On Error GoTo errorhandler
    Dim objSQLServer As sqlole.SQLServer, CurrentDatabase As String
    Dim default As sqlole.default, Database As sqlole.Database
    
    Set objSQLServer = CreateObject("SQLOLE.SQLserver")
    
    'Connect to SQL Server
    objSQLServer.Connect ServerName:=pvtSQLServer, login:=pvtLoginID, Password:=pvtPassword
    
    CurrentDatabase = node.Parent.Parent.Text
    
    Set Database = objSQLServer.Databases(CurrentDatabase)
    For Each default In Database.Defaults
        TreeView1.Nodes.Add node.Key, tvwChild, "DE" & default.Name & CurrentDatabase, default.Name, 13
    Next
    
    node.Expanded = True
    
    objSQLServer.DisConnect
    
exitsub:
    Exit Sub
    
errorhandler:
    MsgBox Error
    Resume exitsub
End Sub



Private Sub AddLogins(node As comctllib.node)
    On Error GoTo errorhandler
    Dim objSQLServer As sqlole.SQLServer, CurrentDatabase As String
    Dim login As sqlole.login, Database As sqlole.Database
    
    Set objSQLServer = CreateObject("SQLOLE.SQLserver")
    
    'Connect to SQL Server
    objSQLServer.Connect ServerName:=pvtSQLServer, login:=pvtLoginID, Password:=pvtPassword
    
    For Each login In objSQLServer.Logins
        TreeView1.Nodes.Add node.Key, tvwChild, "L1" & login.Name, login.Name, 8
    Next
    
    node.Expanded = True
    
    objSQLServer.DisConnect
    
exitsub:
    Exit Sub
    
errorhandler:
    MsgBox Error
    Resume 'exitsub
End Sub




Private Sub AddUserDefinedTypes(node As comctllib.node)
    On Error GoTo errorhandler
    Dim objSQLServer As sqlole.SQLServer, CurrentDatabase As String
    Dim udt As sqlole.UserDefinedDatatype, Database As sqlole.Database
    
    Set objSQLServer = CreateObject("SQLOLE.SQLserver")
    
    'Connect to SQL Server
    objSQLServer.Connect ServerName:=pvtSQLServer, login:=pvtLoginID, Password:=pvtPassword
    
    CurrentDatabase = node.Parent.Parent.Text
    
    Set Database = objSQLServer.Databases(CurrentDatabase)
    For Each udt In Database.UserDefinedDatatypes
        TreeView1.Nodes.Add node.Key, tvwChild, "US" & udt.Name & CurrentDatabase, udt.Name, 14
    Next
    
    node.Expanded = True
    
    objSQLServer.DisConnect
    
exitsub:
    Exit Sub
    
errorhandler:
    MsgBox Error
    Resume exitsub
End Sub




Private Sub AddGroups(node As comctllib.node)
    On Error GoTo errorhandler
    Dim objSQLServer As sqlole.SQLServer, CurrentDatabase As String
    Dim groups As sqlole.Group, Database As sqlole.Database
    
    Set objSQLServer = CreateObject("SQLOLE.SQLserver")
    
    'Connect to SQL Server
    objSQLServer.Connect ServerName:=pvtSQLServer, login:=pvtLoginID, Password:=pvtPassword
    
    CurrentDatabase = node.Parent.Text
    
    Set Database = objSQLServer.Databases(CurrentDatabase)
    For Each groups In Database.groups
        TreeView1.Nodes.Add node.Key, tvwChild, "GR" & groups.Name & CurrentDatabase, groups.Name, 14
    Next
    
    node.Expanded = True
    
    objSQLServer.DisConnect
    
exitsub:
    Exit Sub
    
errorhandler:
    MsgBox Error
    Resume exitsub
End Sub










Private Sub ClearAllChildren(node As comctllib.node)
    On Error GoTo errorhandler
    'Clear all Child nodes
    Do
        If node.Index = node.Child.Index Then
            Exit Do 'All children are gone
        End If
        TreeView1.Nodes.Remove node.Child.Index
    Loop

exitsub:
    Exit Sub

errorhandler:
    Select Case Err
        Case 91
            'Do nothing
        Case Else
            MsgBox Error
    End Select
    Resume exitsub
End Sub

Public Property Get LoginID() As String
    LoginID = pvtLoginID
End Property

Public Property Let LoginID(LoginID As String)
    pvtLoginID = LoginID
    PropertyChanged "LoginID"
End Property



Public Property Get Password() As String
    Password = pvtPassword
End Property

Public Property Let Password(Password As String)
    pvtPassword = Password
    PropertyChanged "Password"
End Property

Public Property Get SQLServer() As String
    SQLServer = pvtSQLServer
End Property

Public Property Let SQLServer(ByVal sSQLServer As String)
    pvtSQLServer = sSQLServer
    PropertyChanged "SQLServer"
End Property

Private Sub mnuDeleteDatabase_Click()
    On Error GoTo errorhandler
    
    If SelectedDatabase <> "" Then
        DeleteDatabase SelectedDatabase
    End If
exitsub:
    Exit Sub
    
errorhandler:
    MsgBox Error
    
    Resume exitsub

End Sub

Private Sub mnuDeleteDevice_Click()
    On Error GoTo errorhandler
    
    If SelectedDevice <> "" Then
        DeleteDevice SelectedDevice
    End If
exitsub:
    Exit Sub
    
errorhandler:
    MsgBox Error
    
    Resume exitsub

End Sub


Private Sub mnuNewDatabase_Click()
    On Error GoTo errorhandler
    
    PublicVariables.DatabaseName = ""
    
    Dim myform As New NewDatabase
    myform.SQLServer = pvtSQLServer
    myform.LoginID = pvtLoginID
    myform.Password = pvtPassword
    myform.Show 1
    
    'Determine if the user cancelled the dialog
    If PublicVariables.DatabaseName <> "" Then
        AddDatabase PublicVariables.DatabaseName, PublicVariables.DeviceName, _
            PublicVariables.DeviceSize, PublicVariables.LogDeviceName, _
            PublicVariables.LogDeviceSize
    End If
exitsub:
    Exit Sub
    
errorhandler:
    MsgBox Error
    
    Resume exitsub
End Sub

Private Sub mnuNewDevice_Click()
    On Error GoTo errorhandler
    
    PublicVariables.DeviceName = ""
    
    Dim myform As New NewDevice
    myform.SQLServer = pvtSQLServer
    myform.LoginID = pvtLoginID
    myform.Password = pvtPassword
    myform.Show 1
    
    'Determine if the user cancelled the dialog
    If PublicVariables.DeviceName <> "" Then
        AddDevice PublicVariables.DeviceName, _
            PublicVariables.DeviceLocation, _
            PublicVariables.DeviceSize
    End If
exitsub:
    Exit Sub
    
errorhandler:
    MsgBox Error
    
    Resume exitsub

End Sub

Private Sub TreeView1_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    On Error GoTo errorhandler
    
    If Button = 2 Then
        If Len(mnuContextMenu.Caption) Then   ' Right Mouse Button
            PopupMenu mnuContextMenu
        End If
    End If
    
exitsub:
    Exit Sub

errorhandler:
    Resume exitsub
    
End Sub

Private Sub TreeView1_NodeClick(ByVal node As comctllib.node)
    
    'Initialize variables
    Set mnuContextMenu = Nothing
    SelectedDevice = ""
    SelectedDatabase = ""

    Select Case Left(node.Key, 2)
        Case "RT" 'Root Node
        Case "dv" 'Device
            Set mnuContextMenu = UserControl.mnuDevice
            SelectedDevice = node.Text
        Case "db" 'Database
            Set mnuContextMenu = UserControl.mnuDatabase
            SelectedDatabase = node.Text
        Case "TB" 'Table Node
            ClearAllChildren node
            AddTables node
        Case "VW" 'View Node
            ClearAllChildren node
            AddDatabaseObject node, "Databases", "VI", 10
            'AddViews node
        Case "SP" 'Stored Procedure node
            ClearAllChildren node
            AddStoredProcedures node
        Case "RU" 'Rules node
            ClearAllChildren node
            AddRules node
        Case "DF" 'Defaults node
            ClearAllChildren node
            AddDefaults node
        Case "UD" 'User Defined Datatypes node
            ClearAllChildren node
            AddUserDefinedTypes node
        Case "GU" 'Groups/Users node
            ClearAllChildren node
            AddGroups node
        Case "LI" 'Logins node
            ClearAllChildren node
            AddLogins node
    End Select
    
exitsub:
    Exit Sub
    
errorhandler:
    MsgBox Error
    Resume exitsub
End Sub

Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    On Error GoTo errorhandler
    Dim objSQLServer As sqlole.SQLServer
    
    With PropBag
        LoginID = .ReadProperty("LoginID", "")
        Password = .ReadProperty("Password", "")
        SQLServer = .ReadProperty("SQLServer", "")
    End With
    
    'If Not AmbientProperties.UserMode Then
        'We are in Design Time
    '    GoTo ExitSub
    'End If
    
    Set objSQLServer = CreateObject("SQLOLE.SQLserver")
    
    'Logon if necessary
    If pvtSQLServer = "" Then
        MsgBox "Insert Logon Code Here"
        GoTo exitsub
    End If
    
    'Connect to SQL Server
    objSQLServer.Connect ServerName:=pvtSQLServer, login:=pvtLoginID, Password:=pvtPassword
    
    Dim nodx As node    ' Create a tree.
    Set nodx = TreeView1.Nodes.Add(, , "RTSQLServers", "Microsoft SQL Servers", 16)
    nodx.EnsureVisible  ' Show all nodes.
    
    'Add Groups
    Set nodx = TreeView1.Nodes.Add("RTSQLServers", tvwChild, "RTGroups", "SQL 6.x", 2)
    Dim SQLApp As sqlole.Application
    Set SQLApp = objSQLServer.Application
    
    Dim sServer As sqlole.SQLServer
    For Each sServer In SQLApp.SQLServers
        Set nodx = TreeView1.Nodes.Add("RTGroups", tvwChild, sServer.Name, sServer.Name, 3)
        
        Set nodx = TreeView1.Nodes.Add(sServer.Name, tvwChild, "RTDevices", "Devices", 4, 15)
        Set nodx = TreeView1.Nodes.Add(sServer.Name, tvwChild, "RTDump Devices", "Dump Devices", 4)
        Set nodx = TreeView1.Nodes.Add(sServer.Name, tvwChild, "RTDatabases", "Databases", 4)
        Set nodx = TreeView1.Nodes.Add(sServer.Name, tvwChild, "LILogins", "Logins", 4)

        Dim device As sqlole.device
        sServer.Devices.Refresh
        For Each device In sServer.Devices
            If device.Type = 0 Then 'Database Devices
                Set nodx = TreeView1.Nodes.Add("RTDevices", tvwChild, "dv" & device.Name, device.Name, 5)
            Else
                Set nodx = TreeView1.Nodes.Add("RTDump Devices", tvwChild, device.Name, device.Name, 6)
            End If
            
            Dim Database As sqlole.Database
            sServer.Databases.Refresh
            For Each Database In device.ListDatabases
                AddDatabaseToTree Database.Name
            Next
        Next
        Dim login As sqlole.login
        For Each login In sServer.Logins
            Set nodx = TreeView1.Nodes.Add("Logins", tvwChild, login.Name, login.Name, 8)
        Next
    Next
    objSQLServer.DisConnect
exitsub:
    Exit Sub


errorhandler:

    Select Case Err
        Case 91
            'Duplicate key in collection
        Case 35602
            'Duplicate Key in collection
            Resume Next
        Case 35601
            '
        Case Else
            MsgBox Error
    End Select
    
    Resume exitsub

End Sub


Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
    With PropBag
        Call .WriteProperty("LoginID", pvtLoginID, "")
        Call .WriteProperty("Password", pvtPassword, "")
        Call .WriteProperty("SQLServer", pvtSQLServer, "")
    End With
End Sub


