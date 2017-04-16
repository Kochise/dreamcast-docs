VERSION 4.00
Begin VB.Form frmMain 
   Caption         =   "SQL-DMO Generic"
   ClientHeight    =   5790
   ClientLeft      =   1320
   ClientTop       =   2415
   ClientWidth     =   7815
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   0
      weight          =   700
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   Height          =   6150
   Left            =   1260
   LinkTopic       =   "Form1"
   ScaleHeight     =   5790
   ScaleWidth      =   7815
   Top             =   2115
   Width           =   7935
   Begin Threed.SSPanel pnlTop 
      Align           =   1  'Align Top
      Height          =   1245
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   7815
      _Version        =   65536
      _ExtentX        =   13785
      _ExtentY        =   2196
      _StockProps     =   15
      BackColor       =   12632256
      Begin VB.TextBox txtServer 
         BeginProperty Font 
            name            =   "MS Sans Serif"
            charset         =   0
            weight          =   400
            size            =   8.25
            underline       =   0   'False
            italic          =   0   'False
            strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Left            =   1020
         TabIndex        =   6
         Text            =   "rainmaker"
         Top             =   105
         Width           =   1605
      End
      Begin VB.TextBox txtLogin 
         BeginProperty Font 
            name            =   "MS Sans Serif"
            charset         =   0
            weight          =   400
            size            =   8.25
            underline       =   0   'False
            italic          =   0   'False
            strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Left            =   1020
         TabIndex        =   5
         Text            =   "sa"
         Top             =   465
         Width           =   1605
      End
      Begin VB.TextBox txtPassword 
         BeginProperty Font 
            name            =   "MS Sans Serif"
            charset         =   0
            weight          =   400
            size            =   8.25
            underline       =   0   'False
            italic          =   0   'False
            strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Left            =   1020
         PasswordChar    =   "*"
         TabIndex        =   4
         Top             =   825
         Width           =   1605
      End
      Begin VB.CommandButton btConnect 
         Caption         =   "&Connect"
         Height          =   375
         Left            =   2745
         TabIndex        =   3
         Top             =   90
         Width           =   975
      End
      Begin VB.CommandButton btExit 
         Caption         =   "E&xit"
         Height          =   375
         Left            =   3855
         TabIndex        =   2
         Top             =   90
         Width           =   975
      End
      Begin VB.ComboBox cmbView 
         BeginProperty Font 
            name            =   "MS Sans Serif"
            charset         =   0
            weight          =   400
            size            =   8.25
            underline       =   0   'False
            italic          =   0   'False
            strikethrough   =   0   'False
         EndProperty
         Height          =   315
         Left            =   5685
         Style           =   2  'Dropdown List
         TabIndex        =   1
         Top             =   120
         Width           =   1980
      End
      Begin VB.Label lblMsg 
         BackStyle       =   0  'Transparent
         Caption         =   "DoubleClick a database name to show its stored procs."
         Height          =   195
         Left            =   2805
         TabIndex        =   18
         Top             =   870
         Width           =   4800
      End
      Begin VB.Label lblServer 
         BackStyle       =   0  'Transparent
         Caption         =   "Server:"
         Height          =   255
         Left            =   90
         TabIndex        =   11
         Top             =   120
         Width           =   1095
      End
      Begin VB.Label lblLogin 
         BackStyle       =   0  'Transparent
         Caption         =   "Login:"
         Height          =   255
         Left            =   90
         TabIndex        =   10
         Top             =   480
         Width           =   615
      End
      Begin VB.Label lblPassword 
         BackStyle       =   0  'Transparent
         Caption         =   "Password:"
         Height          =   255
         Left            =   90
         TabIndex        =   9
         Top             =   840
         Width           =   855
      End
      Begin VB.Label lblStatus 
         BackStyle       =   0  'Transparent
         Height          =   270
         Left            =   2805
         TabIndex        =   8
         Top             =   570
         Width           =   4800
         WordWrap        =   -1  'True
      End
      Begin ComctlLib.ImageList imgTask 
         Left            =   4125
         Top             =   735
         _Version        =   65536
         _ExtentX        =   1005
         _ExtentY        =   1005
         _StockProps     =   1
         BackColor       =   -2147483643
         ImageWidth      =   32
         ImageHeight     =   32
         NumImages       =   1
         i1              =   "DMOMAIN.frx":0000
      End
      Begin ComctlLib.ImageList imgDatabase 
         Left            =   3645
         Top             =   735
         _Version        =   65536
         _ExtentX        =   1005
         _ExtentY        =   1005
         _StockProps     =   1
         BackColor       =   -2147483643
         ImageWidth      =   32
         ImageHeight     =   32
         NumImages       =   1
         i1              =   "DMOMAIN.frx":03BF
      End
      Begin VB.Label lblMain 
         BackStyle       =   0  'Transparent
         Caption         =   "View:"
         Height          =   195
         Left            =   5100
         TabIndex        =   7
         Top             =   165
         Width           =   540
      End
   End
   Begin Threed.SSPanel pnlServer 
      Align           =   1  'Align Top
      Height          =   1710
      Left            =   0
      TabIndex        =   12
      Top             =   1245
      Width           =   7815
      _Version        =   65536
      _ExtentX        =   13785
      _ExtentY        =   3016
      _StockProps     =   15
      BackColor       =   12632256
      Autosize        =   3
      Begin VB.TextBox txtOut 
         BeginProperty Font 
            name            =   "Courier New"
            charset         =   0
            weight          =   400
            size            =   8.25
            underline       =   0   'False
            italic          =   0   'False
            strikethrough   =   0   'False
         EndProperty
         Height          =   1545
         Left            =   75
         Locked          =   -1  'True
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   13
         Top             =   75
         Width           =   7545
      End
   End
   Begin Threed.SSPanel pnlTask 
      Align           =   1  'Align Top
      Height          =   1230
      Left            =   0
      TabIndex        =   14
      Top             =   4245
      Width           =   7815
      _Version        =   65536
      _ExtentX        =   13785
      _ExtentY        =   2170
      _StockProps     =   15
      Caption         =   " Tasks"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   400
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Alignment       =   0
      Begin ComctlLib.ListView lvTask 
         Height          =   930
         Left            =   75
         TabIndex        =   15
         Top             =   210
         Width           =   4995
         _Version        =   65536
         _ExtentX        =   8811
         _ExtentY        =   1640
         _StockProps     =   205
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            name            =   "MS Sans Serif"
            charset         =   0
            weight          =   400
            size            =   8.25
            underline       =   0   'False
            italic          =   0   'False
            strikethrough   =   0   'False
         EndProperty
         Appearance      =   1
         Arrange         =   1
         Icons           =   "imgTask"
         SmallIcons      =   "imgTask"
      End
   End
   Begin Threed.SSPanel pnlDatabase 
      Align           =   1  'Align Top
      Height          =   1290
      Left            =   0
      TabIndex        =   16
      Top             =   2955
      Width           =   7815
      _Version        =   65536
      _ExtentX        =   13785
      _ExtentY        =   2275
      _StockProps     =   15
      Caption         =   " Databases"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   400
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Alignment       =   0
      Begin ComctlLib.ListView lvDatabase 
         Height          =   1035
         Left            =   75
         TabIndex        =   17
         Top             =   225
         Width           =   7650
         _Version        =   65536
         _ExtentX        =   13494
         _ExtentY        =   1826
         _StockProps     =   205
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            name            =   "MS Sans Serif"
            charset         =   0
            weight          =   400
            size            =   8.25
            underline       =   0   'False
            italic          =   0   'False
            strikethrough   =   0   'False
         EndProperty
         Appearance      =   1
         Arrange         =   1
         Icons           =   "imgDatabase"
         SmallIcons      =   "imgDatabase"
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Private Sub btConnect_Click()
'This sub is in very bad form
'I have left all the pieces in this sub for simplicity
'In reality, each piece of this preparation should be
'coded into a seperate routine.
Dim oTask     As Task
Dim oDB       As Database
Dim liTemp    As ListItem
Dim chTemp    As ColumnHeader
Dim iIndex    As Integer

Screen.MousePointer = 11
oSQLServer.DisConnect
lblStatus = "Connecting..."
DoEvents
oSQLServer.Connect CStr(txtServer), CStr(txtLogin), CStr(txtPassword)
DoEvents
lblStatus = "Connected... Building Main..."
DoEvents
With txtOut
    If Err.Number = 0 Then
        '.ListItems.Clear
        'Set chTemp = .ColumnHeaders.Add(, , "Name", .Width / 14)
        'Set chTemp = .ColumnHeaders.Add(, , "HostName", .Width / 14)
        'Set chTemp = .ColumnHeaders.Add(, , "Language", .Width / 14)
        'Set chTemp = .ColumnHeaders.Add(, , "Login", .Width / 14)
        'Set chTemp = .ColumnHeaders.Add(, , "Password", .Width / 14)
        'Set chTemp = .ColumnHeaders.Add(, , "LoginSecure", .Width / 14)
        'Set chTemp = .ColumnHeaders.Add(, , "LoginTimeout", .Width / 14)
        'Set chTemp = .ColumnHeaders.Add(, , "SaLogin", .Width / 14)
        'Set chTemp = .ColumnHeaders.Add(, , "TrueLogin", .Width / 14)
        'Set chTemp = .ColumnHeaders.Add(, , "TrueName", .Width / 14)
        'Set chTemp = .ColumnHeaders.Add(, , "QueryTimeout", .Width / 14)
        'Set chTemp = .ColumnHeaders.Add(, , "CommandTerminator", .Width / 14)
        'Set chTemp = .ColumnHeaders.Add(, , "AutoReConnect", .Width / 14)
        'Set chTemp = .ColumnHeaders.Add(, , "ApplicationName", .Width / 14)
    
        'Set liTemp = .ListItems.Add()
        'With liTemp
        '    .Icon = 1
        '    .SmallIcon = 1
            .Text = ""
            .Text = "ServerName  : " & oSQLServer.Name & NL
            .Text = .Text & "HostName    : " & oSQLServer.HostName & NL
            .Text = .Text & "Language    : " & oSQLServer.Language & NL
            .Text = .Text & "Login       : " & oSQLServer.Login & NL
            .Text = .Text & "Password    : " & oSQLServer.Password & NL
            .Text = .Text & "LoginSecure : " & oSQLServer.LoginSecure & NL
            .Text = .Text & "SaLogin     : " & oSQLServer.SaLogin & NL
            .Text = .Text & "TrueLogin   : " & oSQLServer.TrueLogin & NL
            .Text = .Text & "TrueName    : " & oSQLServer.TrueName & NL
            .Text = .Text & "QueryTimeout: " & oSQLServer.QueryTimeout & NL
            .Text = .Text & "CommandTerm : " & oSQLServer.CommandTerminator & NL
            .Text = .Text & "AutoReConn  : " & oSQLServer.AutoReConnect
            
            '.SubItems(1) = oSQLServer.HostName
            '.SubItems(2) = oSQLServer.Language
            '.SubItems(3) = oSQLServer.Login
            '.SubItems(4) = oSQLServer.Password
            '.SubItems(5) = oSQLServer.LoginSecure
            '.SubItems(6) = oSQLServer.SaLogin
            '.SubItems(7) = oSQLServer.TrueLogin
            '.SubItems(8) = oSQLServer.TrueName
            '.SubItems(9) = oSQLServer.QueryTimeout
            '.SubItems(10) = oSQLServer.CommandTerminator
            '.SubItems(11) = oSQLServer.AutoReConnect
        'End With
    Else
        lblStatus = Err.Source & " Error " & Err.Number - vbObjectError & ":"
        lblStatus = lblStatus & "    " & Err.Description
    End If
End With

DoEvents
lblStatus = "Building Database List..."
DoEvents

Err.Number = 0
With lvDatabase
    If Err.Number = 0 Then
        .Visible = False
        .ListItems.Clear
        Set chTemp = .ColumnHeaders.Add(, "Name", "Name", 800)
        Set chTemp = .ColumnHeaders.Add(, "Size", "Size", 350)
        Set chTemp = .ColumnHeaders.Add(, "SpaceAvailable", "SpaceAvailable", 1010)
        Set chTemp = .ColumnHeaders.Add(, "DataSpaceUsage", "DataSize", 600)
        Set chTemp = .ColumnHeaders.Add(, "IndexSpaceUsage", "IndexSize", 600)
        Set chTemp = .ColumnHeaders.Add(, "SystemObject", "System", 420)
        Set chTemp = .ColumnHeaders.Add(, "CreateDate", "CreateDate", 1550)
        
        For Each oDB In oSQLServer.Databases
            Set liTemp = .ListItems.Add()
            lblStatus = "Building Database List..." & oDB.Name
            DoEvents
            With liTemp
                .Icon = 1
                .SmallIcon = 1
                .Text = oDB.Name
                .SubItems(1) = oDB.Size
                .SubItems(2) = Format$(oDB.SpaceAvailableInMB, "0.00") & " mb"
                .SubItems(3) = Format$(oDB.DataSpaceUsage, "0.00") & " mb"
                .SubItems(4) = Format$(oDB.IndexSpaceUsage, "0.00") & " mb"
                .SubItems(5) = oDB.SystemObject
                .SubItems(6) = oDB.CreateDate
            End With
        Next
        .Visible = True
    End If
End With

DoEvents
lblStatus = "Building tasks..."
DoEvents

Err.Number = 0
With lvTask
    If Err.Number = 0 Then
        .Visible = False
        .ListItems.Clear
        
        'If you have tasks in your database,
        'this is how to make them execute in real time.
        'oSQLServer.Executive.Tasks("Kens").Invoke
    
        Set chTemp = .ColumnHeaders.Add(, "Name", "Name", 1400)
        Set chTemp = .ColumnHeaders.Add(, "Command", "Command", 1500)
        Set chTemp = .ColumnHeaders.Add(, "DateCreated", "CreateDate", 1550)
        Set chTemp = .ColumnHeaders.Add(, "EmailOperator", "Email", 400)
        Set chTemp = .ColumnHeaders.Add(, "Enabled", "Enabled", 500)
        Set chTemp = .ColumnHeaders.Add(, "LastRunDate", "LastRun", 1550)
        Set chTemp = .ColumnHeaders.Add(, "NextRunDate", "NextRunDate", 920)
        Set chTemp = .ColumnHeaders.Add(, "SubSystem", "Type", 600)
    
        For Each oTask In oSQLServer.Executive.Tasks
            Set liTemp = .ListItems.Add()
            lblStatus = "Building tasks..." & oTask.Name
            DoEvents
            With liTemp
                .Icon = 1
                .SmallIcon = 1
                .Text = oTask.Name
                .Tag = Trim$(CStr(oTask.ID))
                .SubItems(1) = oTask.Command
                .SubItems(2) = oTask.DateCreated
                .SubItems(3) = oTask.EmailOperator
                .SubItems(4) = oTask.Enabled
                .SubItems(5) = oTask.LastRunDate
                .SubItems(6) = oTask.NextRunDate
                .SubItems(7) = oTask.SubSystem
            End With
        Next
    .Visible = True
    End If
End With

DoEvents
lblStatus = ""
lblMsg.Visible = True
Screen.MousePointer = 0
End Sub

Private Sub btExit_Click()
On Error Resume Next
While Forms.Count > 1
    If Forms(0).hWnd = Me.hWnd Then
        Unload Forms(1)
    Else
        Unload Forms(0)
    End If
Wend
Unload Me
End Sub

Private Sub cmbView_Click()
'lvMain.View = cmbView.ListIndex
lvTask.View = cmbView.ListIndex
lvDatabase.View = cmbView.ListIndex
End Sub
Private Sub Form_Load()
NL = Chr$(13) & Chr$(10)
lblMsg.Visible = False
With cmbView
    .AddItem "Icon"         ' 0
    .AddItem "Small Icon"    ' 1
    .AddItem "List"         ' 2
    .AddItem "Report"       ' 3
    .ListIndex = 0
End With
End Sub

Private Sub Form_Resize()
On Error Resume Next
txtOut.Width = pnlServer.Width - (txtOut.Left / 2) - 100
pnlTask.Height = (Me.ScaleHeight - (pnlTop.Height + pnlServer.Height)) / 2
pnlDatabase.Height = (Me.ScaleHeight - (pnlTop.Height + pnlServer.Height)) / 2
lvTask.Height = pnlTask.Height - lvTask.Top - lvTask.Left
lvTask.Width = pnlTask.Width - (lvTask.Left * 2)
lvDatabase.Height = pnlDatabase.Height - lvDatabase.Top - lvDatabase.Left
lvDatabase.Width = pnlDatabase.Width - (lvDatabase.Left * 2)
End Sub

Private Sub Form_Unload(Cancel As Integer)
On Error Resume Next
oSQLServer.DisConnect
oSQLServer.Close
End
End Sub

Private Sub lvDatabase_ColumnClick(ByVal ColumnHeader As ColumnHeader)
lvDatabase.SortKey = ColumnHeader.Index - 1
' Set Sorted to True to sort the list.
lvDatabase.Sorted = True
End Sub

Private Sub lvDatabase_DblClick()
'This sub displays the forms with stored procedure information.
'I have also included the form to display table information.
'The code is below in a sub called LoadTables
'Remove the form frmSProc and load the form frmTable
'Then replace this code with the code in the LoadTables sub.
Dim oSProc    As StoredProcedure
Dim liTemp    As ListItem
Dim chTemp    As ColumnHeader
Dim iIndex    As Integer
Dim frmTemp   As frmSProc
Dim fIsNew    As Boolean

Screen.MousePointer = 11
lblStatus = "Building Stored Procedures List..."
DoEvents
fIsNew = True
For iIndex = 0 To Forms.Count - 1
    If InStr(Forms(iIndex).Caption, CStr(lvDatabase.SelectedItem) & " - Stored Procedures") Then
        Set frmTemp = Forms(iIndex)
        fIsNew = False
        Exit For
    End If
Next iIndex
If fIsNew Then
    Set frmTemp = New frmSProc
End If

frmTemp.Caption = CStr(lvDatabase.SelectedItem) & " - Stored Procedures"
Err.Number = 0
With frmTemp.lvSProc
    If Err.Number = 0 Then
        .ListItems.Clear
        If fIsNew Then
            .ColumnHeaders.Clear
            Set chTemp = .ColumnHeaders.Add(, "Name", "Name", 1000)
            Set chTemp = .ColumnHeaders.Add(, "SystemObject", "System", 500)
            Set chTemp = .ColumnHeaders.Add(, "CreateDate", "CreateDate", 1000)
            Set chTemp = .ColumnHeaders.Add(, "Startup", "Startup", 500)
            Set chTemp = .ColumnHeaders.Add(, "TypeOf", "Type", 500)
        End If
        
        For Each oSProc In oSQLServer.Databases(CStr(lvDatabase.SelectedItem)).StoredProcedures
            Set liTemp = .ListItems.Add()
            lblStatus = "Building Stored Procedures List..." & oSProc.Name
            With liTemp
                .Icon = 1
                .SmallIcon = 1
                .Text = oSProc.Name
                .Tag = CStr(lvDatabase.SelectedItem)
                .SubItems(1) = oSProc.SystemObject
                .SubItems(2) = oSProc.CreateDate
                .SubItems(3) = oSProc.Startup
                .SubItems(4) = oSProc.TypeOf
            End With
        Next
    End If
End With

frmTemp.Show

DoEvents
lblStatus = ""
Screen.MousePointer = 0
End Sub
Private Sub lvTask_ColumnClick(ByVal ColumnHeader As ColumnHeader)
lvTask.SortKey = ColumnHeader.Index - 1
' Set Sorted to True to sort the list.
lvTask.Sorted = True
End Sub

Private Sub LoadTables()
Dim oTable    As Table
Dim liTemp    As ListItem
Dim chTemp    As ColumnHeader
Dim iIndex    As Integer
Dim frmTemp   As frmTable
Dim fIsNew    As Boolean

Screen.MousePointer = 11
lblStatus = "Building Tables List..."
DoEvents
fIsNew = True
For iIndex = 0 To Forms.Count - 1
    If InStr(Forms(iIndex).Caption, CStr(lvDatabase.SelectedItem) & " - Tables") Then
        Set frmTemp = Forms(iIndex)
        fIsNew = False
        Exit For
    End If
Next iIndex
If fIsNew Then
    Set frmTemp = New frmTable
End If

frmTemp.Caption = CStr(lvDatabase.SelectedItem) & " - Tables"
Err.Number = 0
With frmTemp.lvSProcs
    If Err.Number = 0 Then
        .ListItems.Clear
        If fIsNew Then
            .ColumnHeaders.Clear
            Set chTemp = .ColumnHeaders.Add(, "Name", "Name", 1000)
            Set chTemp = .ColumnHeaders.Add(, "Rows", "Rows", 800)
            Set chTemp = .ColumnHeaders.Add(, "SystemObject", "System", 500)
            Set chTemp = .ColumnHeaders.Add(, "CreateDate", "CreateDate", 1000)
            Set chTemp = .ColumnHeaders.Add(, "Attributes", "Attrib", 500)
            Set chTemp = .ColumnHeaders.Add(, "TypeOf", "Type", 500)
        End If
        
        For Each oTable In oSQLServer.Databases(CStr(lvDatabase.SelectedItem)).Tables
            Set liTemp = .ListItems.Add()
            lblStatus = "Building Tables List..." & oTable.Name
            With liTemp
                .Icon = 1
                .SmallIcon = 1
                .Text = oTable.Name
                .SubItems(1) = oTable.Rows
                .SubItems(2) = oTable.SystemObject
                .SubItems(3) = oTable.CreateDate
                .SubItems(4) = oTable.Attributes
                .SubItems(5) = oTable.TypeOf
            End With
        Next
    End If
End With

frmTemp.Show

DoEvents
lblStatus = ""
Screen.MousePointer = 0
End Sub
