VERSION 4.00
Begin VB.Form frmMain 
   Caption         =   "SQL-DMO Generic"
   ClientHeight    =   6015
   ClientLeft      =   510
   ClientTop       =   675
   ClientWidth     =   6735
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   1
      weight          =   700
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   Height          =   6420
   Left            =   450
   LinkTopic       =   "Form1"
   ScaleHeight     =   6015
   ScaleWidth      =   6735
   Top             =   330
   Width           =   6855
   Begin VB.TextBox txtOut 
      Height          =   4695
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   5
      Top             =   1200
      Width           =   6495
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   5640
      TabIndex        =   4
      Top             =   120
      Width           =   975
   End
   Begin VB.CommandButton cmdConnect 
      Caption         =   "&Connect"
      Height          =   375
      Left            =   4560
      TabIndex        =   3
      Top             =   120
      Width           =   975
   End
   Begin VB.TextBox txtPassword 
      Height          =   285
      Left            =   1320
      PasswordChar    =   "*"
      TabIndex        =   2
      Top             =   840
      Width           =   2775
   End
   Begin VB.TextBox txtLogin 
      Height          =   285
      Left            =   1320
      TabIndex        =   1
      Top             =   480
      Width           =   2775
   End
   Begin VB.TextBox txtServer 
      Height          =   285
      Left            =   1320
      TabIndex        =   0
      Top             =   120
      Width           =   2775
   End
   Begin VB.Label lblPassword 
      Caption         =   "Password:"
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   840
      Width           =   855
   End
   Begin VB.Label lblLogin 
      Caption         =   "Login:"
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   480
      Width           =   615
   End
   Begin VB.Label lblServer 
      Caption         =   "SQL Server:"
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   120
      Width           =   1095
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

' Global variables
Dim oSQLServer As SQLOLE.SQLServer
Dim NL As String






Private Sub cmdConnect_Click()
    On Error Resume Next
    
    frmMain.MousePointer = 11
    oSQLServer.DisConnect
    oSQLServer.Connect txtServer.Text, txtLogin.Text, txtPassword.Text
    With txtOut
        If Err.Number = 0 Then
            .Text = "Connected to SQL Server " & oSQLServer.TrueName & NL
            Dim oProperty As Object
            .Text = .Text & "Properties for " & oSQLServer.Name & NL
            For Each oProperty In oSQLServer.Properties
                .Text = .Text & oProperty.Name & ": " & oProperty.Value & NL
            Next
        Else
            .Text = Err.Source & " Error " & Err.Number - vbObjectError & ":" & NL
            .Text = .Text & "    " & Err.Description
        End If
    End With
    frmMain.MousePointer = 0
   
        
End Sub


Private Sub cmdExit_Click()
    Unload frmMain
End Sub

Private Sub Form_Load()
    On Error Resume Next
    NL = Chr$(13) & Chr$(10)
    
    Set oSQLServer = New SQLOLE.SQLServer
    oSQLServer.LoginTimeout = 10
    
End Sub


Private Sub Form_Unload(Cancel As Integer)
    On Error Resume Next
    
    oSQLServer.DisConnect
    oSQLServer.Close

End Sub




