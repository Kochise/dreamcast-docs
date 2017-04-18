VERSION 4.00
Begin VB.Form LDBUser 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "LDB User List"
   ClientHeight    =   5835
   ClientLeft      =   765
   ClientTop       =   1590
   ClientWidth     =   8010
   Height          =   6300
   Left            =   705
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   5835
   ScaleWidth      =   8010
   Top             =   1185
   Width           =   8130
   Begin VB.CommandButton Command7 
      Caption         =   "&Wipe Viewer"
      Height          =   492
      Left            =   6000
      TabIndex        =   13
      Top             =   4920
      Width           =   1572
   End
   Begin VB.CommandButton Command6 
      Caption         =   "&Hide Viewer"
      Height          =   492
      Left            =   6000
      TabIndex        =   12
      Top             =   4320
      Width           =   1572
   End
   Begin VB.CommandButton Command4 
      Caption         =   "S&how Viewer"
      Height          =   492
      Left            =   6000
      TabIndex        =   11
      Top             =   3720
      Width           =   1572
   End
   Begin VB.CommandButton Command5 
      Caption         =   "&Execute or Refresh"
      Enabled         =   0   'False
      Height          =   372
      Left            =   5640
      TabIndex        =   2
      Top             =   2160
      Width           =   2172
   End
   Begin VB.Frame Frame1 
      Caption         =   "LDB User Options"
      Height          =   2052
      Left            =   480
      TabIndex        =   4
      Top             =   3480
      Width           =   4932
      Begin VB.OptionButton optLDB 
         Caption         =   "About"
         Height          =   252
         Index           =   4
         Left            =   240
         TabIndex        =   9
         Top             =   1680
         Width           =   3612
      End
      Begin VB.OptionButton optLDB 
         Caption         =   "Just show a count of users connected"
         Height          =   192
         Index           =   3
         Left            =   240
         TabIndex        =   8
         Top             =   1320
         Width           =   4212
      End
      Begin VB.OptionButton optLDB 
         Caption         =   "Show users that left database in a suspect state"
         Height          =   252
         Index           =   2
         Left            =   240
         TabIndex        =   7
         Top             =   960
         Width           =   4092
      End
      Begin VB.OptionButton optLDB 
         Caption         =   "Show all logged in users to the database"
         Height          =   252
         Index           =   1
         Left            =   240
         TabIndex        =   6
         Top             =   600
         Width           =   3252
      End
      Begin VB.OptionButton optLDB 
         Caption         =   "Show all users listed in the database"
         Height          =   252
         Index           =   0
         Left            =   240
         TabIndex        =   5
         Top             =   240
         Value           =   -1  'True
         Width           =   3012
      End
   End
   Begin VB.ListBox List1 
      Height          =   2010
      Left            =   480
      TabIndex        =   14
      Top             =   1200
      Width           =   4935
   End
   Begin VB.CommandButton Command3 
      Caption         =   "&Clear"
      Enabled         =   0   'False
      Height          =   372
      Left            =   5640
      TabIndex        =   1
      Top             =   1680
      Width           =   2172
   End
   Begin VB.CommandButton Command2 
      Caption         =   "&Select Database"
      Default         =   -1  'True
      Height          =   372
      Left            =   5640
      TabIndex        =   0
      Top             =   1200
      Width           =   2172
   End
   Begin VB.CommandButton Command1 
      Caption         =   "E&xit"
      Height          =   372
      Left            =   5640
      TabIndex        =   3
      Top             =   2640
      Width           =   2172
   End
   Begin VB.Frame Frame2 
      Height          =   2052
      Left            =   5640
      TabIndex        =   10
      Top             =   3480
      Width           =   2172
   End
   Begin VB.Label Label5 
      Caption         =   "Users"
      Height          =   252
      Left            =   480
      TabIndex        =   19
      Top             =   960
      Width           =   1332
   End
   Begin VB.Label Label3 
      Caption         =   "#"
      Height          =   252
      Left            =   2760
      TabIndex        =   17
      Top             =   240
      Width           =   972
   End
   Begin VB.Label Label1 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      Height          =   252
      Left            =   1320
      TabIndex        =   15
      Top             =   600
      Width           =   4092
   End
   Begin VB.Label Label2 
      Caption         =   "Number of Users Connected:"
      Height          =   252
      Left            =   480
      TabIndex        =   16
      Top             =   240
      Width           =   2292
   End
   Begin VB.Label Label4 
      Caption         =   "Database:"
      Height          =   252
      Left            =   480
      TabIndex        =   18
      Top             =   600
      Width           =   972
   End
End
Attribute VB_Name = "LDBUser"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
'
'   LDB User List
'   A Quick and easy demo utilizing the MSLDBUSR.DLL
'   Written and Developed by Bob Delavan
'

Dim miLDBOption As Integer
Dim msLDBFile As String


Sub Execute()

    ReDim msString(1) As String
    Dim miLoop As Integer

    Command5.Enabled = True
    Command3.Enabled = True
    List1.Clear
    LDBView.Cls
    Label1.Caption = msLDBFile
    miLoop = LDBUser_GetUsers(msString, msLDBFile, miLDBOption)
    label3.Caption = Str$(miLoop)
    LDBView.Print "Return value         = "; miLoop
    If miLoop < 0 Then
        LDBView.Print "Error:"; LDBUser_GetError(miLoop)
    End If
    LDBView.Print "Lower Bound of Array = "; LBound(msString)
    LDBView.Print "Upper Bound of Array = "; UBound(msString)
    For miLoop = LBound(msString) To UBound(msString)
        If Len(msString(miLoop)) = 0 Then
            Exit For
        End If
        LDBView.Print "Name:"; msString(miLoop); "   Length:"; Len(msString(miLoop))
        List1.AddItem msString(miLoop)
    Next miLoop
    LDBView.Print

End Sub

Private Sub Command1_Click()
    End
End Sub


Private Sub Command2_Click()

    Dim msExistMDB As String
    If Len(Label1) Then
        msExistMDB = Label1
    Else
        msExistMDB = "*.MDB"
    End If
    
    
    msLDBFile = InputBox("Enter a database:", "LDB User", msExistMDB)
    If msLDBFile <> "-z" Then
        If Len(msLDBFile) = 0 Then
            Exit Sub
        End If
    End If
    msLDBFile = msLDBFile + Chr$(0) + Chr$(0)
    Command5.Enabled = True
    Command3.Enabled = True
    Label1.Caption = msLDBFile


    
End Sub


Private Sub Command3_Click()
    List1.Clear
    label3.Caption = "#"
    Label1.Caption = ""
    msLDBFile = ""
End Sub


Private Sub Command4_Click()
    LDBView.Show
    
End Sub


Private Sub Command5_Click()
    If Len(msLDBFile) And miLDBOption >= 0 Then
        Execute
    End If
    
End Sub

Private Sub Command6_Click()
    LDBView.Hide
End Sub

Private Sub Command7_Click()
    LDBView.Cls
End Sub

Private Sub Form_Load()
    miLDBOption = OptAllLDBUsers
    Load LDBView
End Sub

Private Sub Option1_Click()

End Sub

Private Sub optLDB_Click(Index As Integer)
    Select Case Index
        Case 0
            miLDBOption = OptAllLDBUsers
        Case 1
            miLDBOption = OptLDBLoggedUsers
        Case 2
            miLDBOption = OptLDBCorruptUsers
        Case 3
            miLDBOption = OptLDBUserCount
        Case 4
            miLDBOption = OptLDBUserAuthor
    End Select
End Sub


