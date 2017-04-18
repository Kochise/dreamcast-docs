VERSION 5.00
Begin VB.Form DBParams 
   Caption         =   "XYZ Co. Database Installation"
   ClientHeight    =   5544
   ClientLeft      =   408
   ClientTop       =   1068
   ClientWidth     =   6288
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   12
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5544
   ScaleWidth      =   6288
   Begin VB.CommandButton Remove 
      Caption         =   "&Remove"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.6
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4560
      TabIndex        =   30
      Top             =   600
      Width           =   1455
   End
   Begin VB.CommandButton Install 
      Caption         =   "&Install"
      Default         =   -1  'True
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.6
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4560
      TabIndex        =   9
      Top             =   120
      Width           =   1455
   End
   Begin VB.CommandButton Exit 
      Caption         =   "E&xit"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.6
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4560
      TabIndex        =   10
      Top             =   1080
      Width           =   1455
   End
   Begin VB.CommandButton Help 
      Caption         =   "&Help"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.6
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4560
      TabIndex        =   11
      Top             =   1560
      Width           =   1455
   End
   Begin VB.Frame Frame2 
      Caption         =   "Server Machine"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.6
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1215
      Left            =   240
      TabIndex        =   7
      Top             =   600
      Width           =   4095
      Begin VB.OptionButton SharedOption 
         Caption         =   "&Shared with other applications"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   32
         Top             =   720
         Width           =   3735
      End
      Begin VB.OptionButton DedicatedOption 
         Caption         =   "&Dedicated to XYZ application"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   31
         Top             =   360
         Value           =   -1  'True
         Width           =   3735
      End
   End
   Begin VB.CheckBox CaseSensitive 
      Caption         =   "&Case sensitive searches"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.6
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   3735
   End
   Begin VB.Frame Frame1 
      Caption         =   "File locations"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.6
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3495
      Left            =   240
      TabIndex        =   1
      Top             =   2040
      Width           =   5775
      Begin VB.ComboBox drivecombo 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   360
         Index           =   2
         Left            =   2040
         TabIndex        =   14
         Top             =   1560
         Width           =   615
      End
      Begin VB.ComboBox drivecombo 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   360
         Index           =   1
         Left            =   2040
         TabIndex        =   13
         Top             =   1080
         Width           =   615
      End
      Begin VB.ComboBox drivecombo 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   360
         Index           =   0
         ItemData        =   "DBParams.frx":0000
         Left            =   2040
         List            =   "DBParams.frx":0002
         TabIndex        =   12
         Top             =   600
         Width           =   630
      End
      Begin VB.TextBox xyzlogpath_list 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   360
         Left            =   2760
         TabIndex        =   5
         Text            =   "\xyz\data"
         Top             =   1080
         Width           =   2175
      End
      Begin VB.TextBox xyzdbpath_list 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   360
         Left            =   2760
         TabIndex        =   3
         Text            =   "\xyz\data"
         Top             =   600
         Width           =   2175
      End
      Begin VB.TextBox sqlpath_list 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   2760
         TabIndex        =   8
         Top             =   1560
         Width           =   2175
      End
      Begin VB.Label DriveLabel 
         Caption         =   "x"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   2
         Left            =   960
         TabIndex        =   29
         Top             =   3000
         Width           =   375
      End
      Begin VB.Label DriveLabel 
         Caption         =   "x"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   1
         Left            =   960
         TabIndex        =   28
         Top             =   2760
         Width           =   375
      End
      Begin VB.Label DriveLabel 
         Caption         =   "x"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   0
         Left            =   960
         TabIndex        =   27
         Top             =   2520
         Width           =   375
      End
      Begin VB.Label Label10 
         Caption         =   "Drive"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   840
         TabIndex        =   26
         Top             =   2280
         Width           =   615
      End
      Begin VB.Label Available 
         Alignment       =   1  'Right Justify
         Caption         =   "0"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   2
         Left            =   3360
         TabIndex        =   25
         Top             =   3000
         Width           =   615
      End
      Begin VB.Label Available 
         Alignment       =   1  'Right Justify
         Caption         =   "0"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   1
         Left            =   3480
         TabIndex        =   24
         Top             =   2760
         Width           =   495
      End
      Begin VB.Label Available 
         Alignment       =   1  'Right Justify
         Caption         =   "0"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   0
         Left            =   3360
         TabIndex        =   23
         Top             =   2520
         Width           =   615
      End
      Begin VB.Label Label9 
         AutoSize        =   -1  'True
         Caption         =   "Required (MB)"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   1680
         TabIndex        =   22
         Top             =   2280
         Width           =   1515
      End
      Begin VB.Label Reqd 
         Alignment       =   1  'Right Justify
         Caption         =   "0"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   2
         Left            =   1680
         TabIndex        =   21
         Top             =   3000
         Width           =   495
      End
      Begin VB.Label Reqd 
         Alignment       =   1  'Right Justify
         Caption         =   "0"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   1
         Left            =   1560
         TabIndex        =   20
         Top             =   2760
         Width           =   615
      End
      Begin VB.Label Reqd 
         Alignment       =   1  'Right Justify
         Caption         =   "0"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   0
         Left            =   1560
         TabIndex        =   19
         Top             =   2520
         Width           =   615
      End
      Begin VB.Label Label8 
         AutoSize        =   -1  'True
         Caption         =   "Available (MB)"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   3360
         TabIndex        =   18
         Top             =   2280
         Width           =   1545
      End
      Begin VB.Label Label7 
         Caption         =   "Space "
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   1680
         TabIndex        =   17
         Top             =   2040
         Width           =   1095
      End
      Begin VB.Label Label6 
         Caption         =   "Directory"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   2760
         TabIndex        =   16
         Top             =   240
         Width           =   1575
      End
      Begin VB.Label Label5 
         Caption         =   "Drive"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   2040
         TabIndex        =   15
         Top             =   240
         Width           =   615
      End
      Begin VB.Label Label4 
         Caption         =   "S&QL Server database"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   6
         Top             =   1560
         Width           =   1695
      End
      Begin VB.Label Label3 
         Caption         =   "XYZ &log"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   4
         Top             =   1080
         Width           =   1695
      End
      Begin VB.Label Label2 
         Caption         =   "XYZ &database"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   2
         Top             =   600
         Width           =   1815
      End
   End
End
Attribute VB_Name = "DBParams"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False




Private Sub DisplayRequiredSpace()
    'update the req'd MB field
    For j% = 0 To 23
        DriveArray(j%).RequiredSpace = 0
    Next j%
    
    'Required MB for each component
    Dim Required%(3)
    Required%(0) = 40
    Required%(1) = 20
    Required%(2) = 90
    
        
    For i% = 0 To 2
        DriveStr = drivecombo(i%).List(drivecombo(i%).ListIndex)
        For j% = 0 To 23
            If DriveArray(j%).Name = DriveStr Then
                DriveArray(j%).RequiredSpace = DriveArray(j%).RequiredSpace + Required(i%)
                Exit For
            End If
        Next j%
    Next i%
        
    'Now Show totals
    j% = 0
    For i% = 0 To 23
        If DriveArray(i%).RequiredSpace > 0 Then
            DriveLabel(j%).Caption = DriveArray(i%).Name
            Available(j%).Caption = DriveArray(i%).FreeSpace
            Reqd(j%).Caption = DriveArray(i%).RequiredSpace
            j% = j% + 1
        End If
        If j% = 3 Then Exit For
    Next i%
    
    ' blank out other labels
    For k% = j% To 2
           DriveLabel(k%).Caption = ""
            Available(k%).Caption = ""
            Reqd(k%).Caption = ""
    Next k%

End Sub







Private Sub drivecombo_Click(Index As Integer)
    DisplayRequiredSpace
End Sub


Private Sub Exit_Click()
    End
End Sub

Private Sub Form_Load()
        Dim Numdrives As Integer, i As Integer, j As Integer
                                       
         sqlpath_list.Text = ReadIni("SQLPath", "SQLPath")
          
         'Call Routine to find all local harddrives and space free
        Numdrives = GetFixedDrives()
        
         ' load drive dropdowns with available local drives
         For i = 0 To 2
            For j = 1 To Numdrives%
                drivecombo(i%).AddItem DriveArray(j% - 1).Name
            Next j
        Next i
        
        ' Set the defaults based on number of drives
        drivecombo(2).ListIndex = 0
        Select Case Numdrives
        Case 0
            MsgBox "Couldn't find any drives to install on."
        Case 1
            drivecombo(0).ListIndex = 0
            drivecombo(1).ListIndex = 0
        Case 2
            drivecombo(0).ListIndex = 1
            drivecombo(1).ListIndex = 0
        Case Else
            drivecombo(0).ListIndex = 2
            drivecombo(1).ListIndex = 1
        End Select
         DisplayRequiredSpace
         
         
         Exit Sub
End Sub





Private Sub Install_Click()
       
'Check to see if db and log dirs already exist, if not create them
    Succeed = CheckForDir(drivecombo(0).List(drivecombo(0).ListIndex), xyzdbpath_list.Text)
    If Succeed = False Then Exit Sub
    
    Call CheckForDir(drivecombo(1).List(drivecombo(1).ListIndex), xyzlogpath_list.Text)
    If Succeed = False Then Exit Sub
    
'Write out sort order value in setup.ini based on case sensitive checkbox
    If CaseSensitive.Value = 0 Then
        Call WriteIni("SortOrder", "SortFileName", "nocase.iso")
        Call WriteIni("SortOrder", "SortConfigValue", "52")
    Else
        Call WriteIni("SortOrder", "SortFileName", "diction.iso")
        Call WriteIni("SortOrder", "SortConfigValue", "51")
    End If
    
'Set LicensedUsers for this install (could be read from a file to make configurable)
     LicensedUsers = 20
     ConnectsPerUser = 3

     Call WriteIni("License", "PerServerUsers", Trim(Str(LicensedUsers)))
         

  Status.Show
  
    Status.StatusText.Caption = "Launching SQL Server setup"
    Status.ProgressBar1.Value = 5
    Status.Refresh
    
    DBParams.Hide
    
    ' following line launches SQL Setup using the modified setup.ini file
    ' as input.  For demo purposes, it runs SQL Server setup
    ' from the default installed location rather than from a distribution CD
    ' SQLCmd$ = "E:\mssql\binn\setup.exe /tIniFilePath = .\setup.ini "
    'SQLCmd$ = ".\i386\setup.exe /tIniFilePath = .\setup.ini "
    ' ExecCmd SQLCmd$
    
    Status.StatusText.Caption = "Starting SQL Server"
    Status.ProgressBar1.Value = 35
    Status.Refresh
    Succeed = StartSQL()
    If Succeed = False Then
        DBParams.Show
        Status.Hide
        Exit Sub
    End If
    
    Status.StatusText.Caption = "Creating XYZ database "
    Status.ProgressBar1.Value = 40
    Status.Refresh
    
    DevPath$ = drivecombo(0).List(drivecombo(0).ListIndex) + xyzdbpath_list.Text + "\xyzdb.dat"
    Succeed = CreateDevice("xyzdb", DevPath$, 5)
    If Succeed = False Then
        DBParams.Show
        Status.Hide
        Exit Sub
    End If

    Status.ProgressBar1.Value = 45
    Status.Refresh
    
    DevPath$ = drivecombo(1).List(drivecombo(1).ListIndex) + xyzdbpath_list.Text + "\xyzlog.dat"
    Succeed = CreateDevice("xyzlog", DevPath$, 5)
    If Succeed = False Then
        DBParams.Show
        Status.Hide
        Exit Sub
    End If

    Status.ProgressBar1.Value = 50
    Status.Refresh
    Succeed = CreateDB("xyz", "xyzdb", "xyzlog")
    If Succeed = False Then
        DBParams.Show
        Status.Hide
        Exit Sub
    End If
       
    Status.StatusText.Caption = "Creating tables "
    Status.ProgressBar1.Value = 55
    Status.Refresh
    Succeed = CreateTables()
    If Succeed = False Then
        DBParams.Show
        Status.Hide
        Exit Sub
    End If
  
    Status.StatusText.Caption = "Creating stored procedures "
    Status.ProgressBar1.Value = 60
    Status.Refresh
    Succeed = CreateProcs()
    If Succeed = False Then
        DBParams.Show
        Status.Hide
        Exit Sub
    End If

    Status.StatusText.Caption = "Loading data "
    Status.ProgressBar1.Value = 65
    Status.Refresh
    Succeed = BulkCopy()
    If Succeed = False Then
        DBParams.Show
        Status.Hide
        Exit Sub
    End If
    
    Status.StatusText.Caption = "Building indexes"
    Status.ProgressBar1.Value = 70
    Status.Refresh
    Succeed = CreateIndexes()
    If Succeed = False Then
        DBParams.Show
        Status.Hide
        Exit Sub
    End If

    Status.StatusText.Caption = "Adding users"
    Status.ProgressBar1.Value = 75
    Status.Refresh
    Succeed = AddUsers()
    If Succeed = False Then
        DBParams.Show
        Status.Hide
        Exit Sub
    End If
    
    Status.StatusText.Caption = "Adding scheduled maintenance tasks"
    Status.ProgressBar1.Value = 80
    Status.Refresh
    Succeed = AddTasks()
    If Succeed = False Then
        DBParams.Show
        Status.Hide
        Exit Sub
    End If
  
    ' save the auto configuration for last, as it can fail
    Status.StatusText.Caption = "Configuring server for optimal performance"
    Status.ProgressBar1.Value = 85
    Status.Refresh
    Succeed = ConfigureServer(DedicatedOption.Value, LicensedUsers * ConnectsPerUser)
    
    Status.StatusText.Caption = "Insatll complete"
    Status.ProgressBar1.Value = 100
    Status.Refresh

    Sleep (1000)
    Congrats.Show
    
   
End Sub


Private Sub Remove_Click()
On Error GoTo RemoveError
    MousePointer = 11
    Succeed = StartSQL()
    If Succeed = False Then Exit Sub
    
    'After the server is just started, we need to wait to let the db recover
    ' before trying to drop it.
    i% = 0
    Do While LocalServer.Databases("xyz").Status <> SQLOLEDBStat_Normal
        Sleep (1000)
        i% = i% + 1
       If i% > 30 Then Exit Do
    Loop
       
    LocalServer.Databases("xyz").Remove
    LocalServer.Devices("xyzdb").Remove
    LocalServer.Devices("xyzlog").Remove
    LocalServer.Logins("xyzuser").Remove
    LocalServer.IntegratedSecurity.RevokeNTLogin Account:="Users"
    LocalServer.IntegratedSecurity.DefaultLogin = ""
    LocalServer.Executive.Tasks("XYZ Daily Scheduled Maintenance").Remove
    LocalServer.Executive.Tasks("XYZ Weekly Scheduled Maintenance").Remove

    LocalServer.Shutdown
    
    DevPath$ = drivecombo(0).List(drivecombo(0).ListIndex) + xyzdbpath_list.Text + "\xyzdb.dat"
    Kill DevPath$
    DevPath$ = drivecombo(1).List(drivecombo(1).ListIndex) + xyzdbpath_list.Text + "\xyzlog.dat"
    Kill DevPath$
        
    MousePointer = 0
    
    MsgBox "xyz database, devices and logins removed"
    
    
    Exit Sub
    
   
RemoveError:
    ErrorStr$ = "Remove Failed " + Chr(13) + "Error:  " _
            + Str(Err.Number - vbObjectError) + " " + Err.Description
    MsgBox ErrorStr$
    Resume Next
    

End Sub






