VERSION 4.00
Begin VB.Form frmMain 
   Caption         =   "SQL-DMO Explorer"
   ClientHeight    =   6705
   ClientLeft      =   180
   ClientTop       =   390
   ClientWidth     =   9240
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   1
      weight          =   700
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   Height          =   7110
   Left            =   120
   LinkTopic       =   "Form1"
   ScaleHeight     =   6705
   ScaleWidth      =   9240
   Top             =   45
   Width           =   9360
   Begin VB.TextBox txtProperties 
      Height          =   2535
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   13
      Top             =   4080
      Width           =   9015
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   8640
      TabIndex        =   4
      Top             =   120
      Width           =   495
   End
   Begin VB.ComboBox cboFour 
      Height          =   315
      Left            =   6960
      Sorted          =   -1  'True
      Style           =   2  'Dropdown List
      TabIndex        =   11
      Top             =   600
      Width           =   2175
   End
   Begin VB.ListBox lstFour 
      Height          =   2985
      Left            =   6960
      Sorted          =   -1  'True
      TabIndex        =   12
      Top             =   960
      Width           =   2175
   End
   Begin VB.CommandButton cmdConnect 
      Caption         =   "&Connect"
      Height          =   375
      Left            =   7560
      TabIndex        =   3
      Top             =   120
      Width           =   975
   End
   Begin VB.TextBox txtPassword 
      Height          =   285
      Left            =   5880
      PasswordChar    =   "*"
      TabIndex        =   2
      Top             =   120
      Width           =   1455
   End
   Begin VB.TextBox txtLogin 
      Height          =   285
      Left            =   3360
      TabIndex        =   1
      Top             =   120
      Width           =   1455
   End
   Begin VB.TextBox txtServer 
      Height          =   285
      Left            =   1200
      TabIndex        =   0
      Top             =   120
      Width           =   1455
   End
   Begin VB.ListBox lstThree 
      Height          =   2985
      Left            =   4680
      Sorted          =   -1  'True
      TabIndex        =   10
      Top             =   960
      Width           =   2175
   End
   Begin VB.ListBox lstTwo 
      Height          =   2985
      Left            =   2400
      Sorted          =   -1  'True
      TabIndex        =   8
      Top             =   960
      Width           =   2175
   End
   Begin VB.ListBox lstOne 
      Height          =   2985
      Left            =   120
      Sorted          =   -1  'True
      TabIndex        =   6
      Top             =   960
      Width           =   2175
   End
   Begin VB.ComboBox cboThree 
      Height          =   315
      Left            =   4680
      Sorted          =   -1  'True
      Style           =   2  'Dropdown List
      TabIndex        =   9
      Top             =   600
      Width           =   2175
   End
   Begin VB.ComboBox cboTwo 
      Height          =   315
      Left            =   2400
      Sorted          =   -1  'True
      Style           =   2  'Dropdown List
      TabIndex        =   7
      Top             =   600
      Width           =   2175
   End
   Begin VB.ComboBox cboOne 
      Height          =   315
      Left            =   120
      Sorted          =   -1  'True
      Style           =   2  'Dropdown List
      TabIndex        =   5
      Top             =   600
      Width           =   2175
   End
   Begin VB.Label lblPassword 
      Caption         =   "Password:"
      Height          =   255
      Left            =   4920
      TabIndex        =   16
      Top             =   120
      Width           =   855
   End
   Begin VB.Label lblLogin 
      Caption         =   "Login:"
      Height          =   255
      Left            =   2760
      TabIndex        =   15
      Top             =   120
      Width           =   615
   End
   Begin VB.Label lblServer 
      Caption         =   "SQL Server:"
      Height          =   255
      Left            =   120
      TabIndex        =   14
      Top             =   120
      Width           =   1095
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Private Sub FillProperties(oObject As Object, txtText As Object)
    On Error Resume Next
    Dim oProperty As Object

    frmMain.MousePointer = 11
    With txtText
        Select Case oObject.TypeOf
        Case SQLOLEObj_Subscription
            .Text = "Properties for " & oObject.ServerName & NL
        Case Else
            .Text = "Properties for " & oObject.Name & NL
        End Select
        For Each oProperty In oObject.Properties
            .Text = .Text & oProperty.Name & ": " & oProperty.Value & NL
        Next
    End With
    frmMain.MousePointer = 0

End Sub

Private Sub cboFour_Click()

    If oCurrentThree Is Nothing Then Exit Sub

    FillFour

End Sub


Private Sub cboOne_Click()

    cboTwo.Clear
    lstTwo.Clear
    cboThree.Clear
    lstThree.Clear
    cboFour.Clear
    lstFour.Clear

    Set oCurrentOne = Nothing

    Select Case cboOne.Text
    Case "Databases"
        cboTwo.AddItem "Defaults"
        cboTwo.AddItem "Groups"
        cboTwo.AddItem "Publications"
        cboTwo.AddItem "Rules"
        cboTwo.AddItem "StoredProcedures"
        cboTwo.AddItem "SystemDataTypes"
        cboTwo.AddItem "Tables"
        cboTwo.AddItem "UserDefinedDataTypes"
        cboTwo.AddItem "Users"
        cboTwo.AddItem "Views"
    Case "RemoteServers"
        cboTwo.AddItem "RemoteLogins"
    End Select

    FillOne

End Sub

Private Sub cboThree_Click()

    cboFour.Clear
    lstFour.Clear
    
    Set oCurrentThree = Nothing
    
    Select Case cboThree.Text
    Case "Articles"
        cboFour.AddItem "Subscriptions"
    End Select

    If oCurrentTwo Is Nothing Then Exit Sub

    FillThree

End Sub

Private Sub cboTwo_Click()

    cboThree.Clear
    lstThree.Clear
    cboFour.Clear
    lstFour.Clear

    Set oCurrentTwo = Nothing

    Select Case cboTwo.Text
    Case "Tables"
        cboThree.AddItem "Checks"
        cboThree.AddItem "Columns"
        cboThree.AddItem "Indexes"
        cboThree.AddItem "Keys"
        cboThree.AddItem "Triggers"
    Case "Publications"
        cboThree.AddItem "Articles"
    End Select

    If oCurrentOne Is Nothing Then Exit Sub

    FillTwo

End Sub

Private Sub FillOne()
    On Error Resume Next

    lstOne.Clear
    If cboOne.ListIndex = -1 Then Exit Sub

    ReDim oCollection(0) As Object
    GetCollection oSQLServer, (cboOne.Text), oCollection()

    Dim i As Integer
    For i = 1 To oCollection(0).Count
        lstOne.AddItem oCollection(0)(i).Name
    Next i

End Sub

Private Sub FillThree()
    On Error Resume Next

    lstThree.Clear
    If cboThree.ListIndex = -1 Then Exit Sub

    ReDim oCollection(0) As Object
    GetCollection oCurrentTwo, (cboThree.Text), oCollection()
    
    Dim i As Integer
    For i = 1 To oCollection(0).Count
        lstThree.AddItem oCollection(0)(i).Name
    Next i

End Sub

Private Sub FillFour()
    On Error Resume Next

    lstFour.Clear
    If cboFour.ListIndex = -1 Then Exit Sub

    ReDim oCollection(0) As Object
    GetCollection oCurrentThree, (cboFour.Text), oCollection()

    Dim i As Integer
    For i = 1 To oCollection(0).Count
    Select Case oCollection(0)(i).TypeOf
    Case SQLOLEObj_Subscription
        lstFour.AddItem oCollection(0)(i).ServerName
    Case Else
        lstFour.AddItem oCollection(0)(i).Name
    End Select
    Next i

End Sub


Private Sub FillTwo()
    On Error Resume Next

    lstTwo.Clear
    If cboTwo.ListIndex = -1 Then Exit Sub

    ReDim oCollection(0) As Object
    GetCollection oCurrentOne, (cboTwo.Text), oCollection()

    Dim i As Integer
    For i = 1 To oCollection(0).Count
        lstTwo.AddItem oCollection(0)(i).Name
    Next i

End Sub


Private Sub cmdConnect_Click()
    On Error Resume Next
        
    frmMain.MousePointer = 11
    oSQLServer.DisConnect
    oSQLServer.Connect txtServer.Text, txtLogin.Text, txtPassword.Text
    With txtProperties
        If Err.Number = 0 Then
            .Text = "Properties for SQL Server " & oSQLServer.TrueName & NL
            FillProperties oSQLServer, txtProperties
        Else
            .Text = Err.Source & " Error " & Err.Number - vbObjectError & ":" & NL
            .Text = .Text & "    " & Err.Description
        End If
    End With
    
    frmMain.MousePointer = 0
        
    lstOne.Clear
    lstTwo.Clear
    lstThree.Clear
    lstFour.Clear
    
End Sub


Private Sub cmdExit_Click()
    Unload frmMain
End Sub

Private Sub Form_Load()
    On Error Resume Next
    NL = Chr$(13) & Chr$(10)
    
    Set oSQLServer = New SQLOLE.SQLServer
    oSQLServer.LoginTimeout = 10
    
    With cboOne
        .Clear
        .AddItem "Alerts"
        .AddItem "Databases"
        .AddItem "Devices"
        .AddItem "Languages"
        .AddItem "Logins"
        .AddItem "Operators"
        .AddItem "RemoteServers"
    End With

End Sub


Private Sub Form_Unload(Cancel As Integer)
    On Error Resume Next
    
    oSQLServer.DisConnect
    oSQLServer.Close

End Sub



Private Sub lstFour_Click()
    On Error Resume Next

    Select Case cboFour.Text
    Case "Subscriptions"
        Set oCurrentFour = oCurrentThree.Subscriptions(lstFour.Text)
    End Select

    FillProperties oCurrentFour, txtProperties

End Sub

Private Sub lstOne_Click()
    On Error Resume Next
    
    Select Case cboOne.Text
    Case "Databases"
        Set oCurrentOne = oSQLServer.Databases(lstOne.Text)
    Case "Devices"
        Set oCurrentOne = oSQLServer.Devices(lstOne.Text)
    Case "Languages"
        Set oCurrentOne = oSQLServer.Languages(lstOne.Text)
    Case "Logins"
        Set oCurrentOne = oSQLServer.Logins(lstOne.Text)
    Case "RemoteServers"
        Set oCurrentOne = oSQLServer.RemoteServers(lstOne.Text)
    Case "Alerts"
        Set oCurrentOne = oSQLServer.Alerts(lstOne.Text)
    Case "Operators"
        Set oCurrentOne = oSQLServer.Operators(lstOne.Text)
    End Select

    lstTwo.Clear
    lstThree.Clear
    lstFour.Clear

    FillTwo

    FillProperties oCurrentOne, txtProperties

End Sub



Private Sub lstThree_Click()
    On Error Resume Next

    Select Case cboThree.Text
    Case "Columns"
        Set oCurrentThree = oCurrentTwo.Columns(lstThree.Text)
    Case "Indexes"
        Set oCurrentThree = oCurrentTwo.Indexes(lstThree.Text)
    Case "Triggers"
        Set oCurrentThree = oCurrentTwo.Triggers(lstThree.Text)
    Case "Keys"
        Set oCurrentThree = oCurrentTwo.Keys(lstThree.Text)
    Case "Checks"
        Set oCurrentThree = oCurrentTwo.Checks(lstThree.Text)
    Case "Articles"
        Set oCurrentThree = oCurrentTwo.Articles(lstThree.Text)
    End Select

    lstFour.Clear

    FillFour

    FillProperties oCurrentThree, txtProperties

End Sub

Private Sub lstTwo_Click()
    On Error Resume Next

    Select Case cboTwo.Text
    Case "Defaults"
        Set oCurrentTwo = oCurrentOne.Defaults(lstTwo.Text)
    Case "Groups"
        Set oCurrentTwo = oCurrentOne.Groups(lstTwo.Text)
    Case "Rules"
        Set oCurrentTwo = oCurrentOne.Rules(lstTwo.Text)
    Case "StoredProcedures"
        Set oCurrentTwo = oCurrentOne.StoredProcedures(lstTwo.Text)
    Case "SystemDataTypes"
        Set oCurrentTwo = oCurrentOne.SystemDatatypes(lstTwo.Text)
    Case "Tables"
        Set oCurrentTwo = oCurrentOne.Tables(lstTwo.Text)
    Case "UserDefinedDataTypes"
        Set oCurrentTwo = oCurrentOne.UserDefinedDatatypes(lstTwo.Text)
    Case "Users"
        Set oCurrentTwo = oCurrentOne.Users(lstTwo.Text)
    Case "Views"
        Set oCurrentTwo = oCurrentOne.Views(lstTwo.Text)
    Case "RemoteLogins"
        Set oCurrentTwo = oCurrentOne.RemoteLogins(lstTwo.Text)
    Case "Publications"
        Set oCurrentTwo = oCurrentOne.Publications(lstTwo.Text)
    End Select
    
    lstThree.Clear
    lstFour.Clear

    FillThree

    FillProperties oCurrentTwo, txtProperties

End Sub





