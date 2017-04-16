VERSION 2.00
Begin Form frmVBODBC1 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Database Logon"
   ClientHeight    =   2535
   ClientLeft      =   945
   ClientTop       =   3975
   ClientWidth     =   4575
   ControlBox      =   0   'False
   Height          =   2940
   Left            =   885
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2535
   ScaleWidth      =   4575
   Top             =   3630
   Width           =   4695
   Begin ComboBox cboDSN 
      Height          =   300
      Left            =   240
      TabIndex        =   1
      Text            =   "cboDSN"
      Top             =   2040
      Width           =   3015
   End
   Begin CommandButton pbCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3480
      TabIndex        =   3
      Top             =   720
      Width           =   855
   End
   Begin CommandButton pbOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   3480
      TabIndex        =   2
      Top             =   240
      Width           =   855
   End
   Begin TextBox txtPWD 
      Height          =   285
      Left            =   240
      PasswordChar    =   "*"
      TabIndex        =   0
      Text            =   "txtUID"
      Top             =   1200
      Width           =   3015
   End
   Begin TextBox txtUID 
      Height          =   285
      Left            =   240
      TabIndex        =   4
      Text            =   "txtUID"
      Top             =   480
      Width           =   3015
   End
   Begin Label lblDSN 
      BackColor       =   &H00C0C0C0&
      Caption         =   "&Data Source Name:"
      Height          =   255
      Left            =   240
      TabIndex        =   7
      Top             =   1680
      Width           =   3015
   End
   Begin Label lblPWD 
      BackColor       =   &H00C0C0C0&
      Caption         =   "&Password:"
      Height          =   255
      Left            =   240
      TabIndex        =   6
      Top             =   960
      Width           =   3015
   End
   Begin Label lblUID 
      BackColor       =   &H00C0C0C0&
      Caption         =   "User &ID:"
      Height          =   255
      Left            =   240
      TabIndex        =   5
      Top             =   240
      Width           =   3015
   End
End
Option Explicit

' VBODBC
' Version 1.1 3/4/95
' Copyright 1995 Clarity Consulting, Inc.
' May not be sold or otherwise reproduced without express written consent
' of Clarity Consulting, Inc.
'
' Craig Goren
' Clarity Consulting, Inc.
' CIS:      72773,1062
' Internet: cgoren@claritycnslt.com
'
' VBODBC is a Visual Basic library that provides an easy method of accessing
' data from an ODBC data source.  It has the following characteristics:
'   - Maintains all database handles internally.
'   - Supports asynchronous query execution (if the driver supports it), so the user can perform tasks in other applications while the server is processing.
'   - A global error buffer, VBODBC_LastErr, containing detailed information regarding the last ODBC error.
'   - Supports only one open database and one open SQL statement at a time.
'   - Has been tested only with SQL Server, Access, and Oracle.
' It also provides includes all ODBC constant and function declarations.
'
' Comments, suggestions, and consulting opportunities welcome!
'
' Files:
'       1. VBODBC.BAS       VB module
'       2. VBODBC1.FRM      VB logon form
'       3. VBODBC2.FRM      VB query executing form
'
' APIs:
'       1. VBODBC_OpenDatabaseDialog() - Establishes an ODBC database connection, prompting the user for connection information.
'       2. VBODBC_OpenDatabase() - Establishes an ODBC database connection without prompting, for use with integrated security and custom dialogs.
'       3. VBODBC_OpenSqlProcDialog() - Executes a stored procedure statement.
'       4. VBODBC_OpenSqlStmtDialog() - Executes a SQL statement.
'       5. VBODBC_GetNextRow() - Retrieves another row of the SQL statement’s result set.  The row is retrieved into a variant array parameter, with each element corresponding the equivalent column number.  Element 0 contains all column values separated by tabs.
'       6. VBODBC_CloseSqlStmt() - Closes the SQL statement.
'       7. VBODBC_CloseDatabase() - Closes the database connection.
'
' Instructions:
'       1. Add VBODBC.BAS, VBODBC1.FRM, VBODBC2.FRM to your project.
'       2. Verify that you have a proper ODBC data source configured.
'       3. Follow the function flowchart within your code.  Note that only one SQL statement and one database connection can be active at a time, so that you don’t have to maintain any handles.
'       4. Inspect the global structure VBODBC_LastErr if you encounter an error.
'       5. Inspect the global structure VBODBC_ColDesc for a description of the last SQL statements columns.
'-----------------------------------------------------------------------------------------------------

Sub Form_Activate ()


'initially set focus to password dialog, since the program should
'have provided a default data source and UID
If VBODBC_Logon.UID <> "" Then
    txtPWD.SetFocus
End If

End Sub

Sub Form_Load ()

Dim ResCode As Integer

'center
top = (screen.Height - Height) / 2
left = (screen.Width - Width) / 2

'assign data sources to combo box
ResCode = VBODBC_GetDataSources(cboDSN)'fill data source box

'set optional defualts
txtUID = VBODBC_Logon.UID
txtPWD = VBODBC_Logon.PWD
cboDSN = VBODBC_Logon.DSN


End Sub

Sub pbCancel_Click ()

'user cancelled
VBODBC_Logon.Connected = False
Unload Me


End Sub

Sub pbOK_Click ()

'lets try and connect!

'the ODBC connection string
Dim ConnStr As String
Dim ResCode As Integer
Dim RowBuf() As Variant

Dim cr As String
Dim s As String

cr = Chr$(13)

'build ODBC connection string
ConnStr = ""
ConnStr = ConnStr & "DSN=" & Trim$(cboDSN)
ConnStr = ConnStr & ";UID=" & Trim$(txtUID)
ConnStr = ConnStr & ";PWD=" & Trim$(txtPWD)
ConnStr = ConnStr & ";APP=" & Trim$(VBODBC_Logon.AppName)

'hourglass
screen.MousePointer = 11
'try and open the database connection
ResCode = VBODBC_OpenDatabase(ConnStr)
If ResCode <> SQL_SUCCESS Then
    'error message, include some native error messsage info
    s = "Verify Name, Password, and Data Source and try again, or press Cancel to exit." & cr & cr & "Error: " & VBODBC_LastErr.ErrorMsg
    'display message
    ResCode = MsgBox(s, 48, "Logon Failed")
    txtPWD.SetFocus
    screen.MousePointer = 0
    'exit
    Exit Sub
End If

'Success!
'fill buffer
VBODBC_Logon.UID = Trim$(txtUID)
VBODBC_Logon.PWD = Trim$(txtPWD)
VBODBC_Logon.DSN = Trim$(cboDSN)
VBODBC_Logon.ConnStrOut = ConnStr
VBODBC_Logon.Connected = True
screen.MousePointer = 0

Unload Me

End Sub

Sub txtPWD_GotFocus ()

txtPWD.SelStart = 0
txtPWD.SelLength = Len(txtPWD)


End Sub

Sub txtUID_GotFocus ()

txtUID.SelStart = 0
txtUID.SelLength = Len(txtUID)

End Sub

