VERSION 2.00
Begin Form frmVBODBC2 
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Server Processing"
   ClientHeight    =   1320
   ClientLeft      =   1080
   ClientTop       =   4365
   ClientWidth     =   2970
   ControlBox      =   0   'False
   Height          =   1725
   Left            =   1020
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1320
   ScaleWidth      =   2970
   Top             =   4020
   Width           =   3090
   Begin CommandButton pbCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   960
      TabIndex        =   1
      Top             =   720
      Width           =   1095
   End
   Begin Label lblStatus 
      Alignment       =   2  'Center
      Caption         =   "lblStatus"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2775
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

Dim OldMousePointer As Integer

Dim Parms() As String
Dim ParmNum As Integer

'This will only be run once, after the form is visible,
'since its a modal non-child form.

'set mousepointer to hourglass, execept cancel button
Me.MousePointer = 11
pbCancel.MousePointer = 1
Me.Refresh

'execute the sql statement asynchronously
If VBODBC_SqlStmt.StmtType = VBODBC_STMTTYPE_SQL Then
    VBODBC_SqlStmt.ResCode = VBODBC_OpenSqlStmt(VBODBC_SqlStmt.SqlStmt)
ElseIf VBODBC_SqlStmt.StmtType = VBODBC_STMTTYPE_PROC Then
    'get rid of extra baggage elements from communication structer
    ReDim Parms(VBODBC_SqlStmt.NumParms)
    For ParmNum = 1 To VBODBC_SqlStmt.NumParms
        Parms(ParmNum) = VBODBC_SqlStmt.Parms(ParmNum)
    Next

    VBODBC_SqlStmt.ResCode = VBODBC_OpenSqlProc(VBODBC_SqlStmt.SqlStmt, Parms())
End If





'sql done, unload form
Unload Me


End Sub

Sub Form_Load ()

'center
top = (screen.Height - Height) / 2
left = (screen.Width - Width) / 2

'change caption to whatever the caller wants or a default
If VBODBC_SqlStmt.Caption = "" Then
    lblStatus.Caption = "Please wait, or press Cancel to abandon the server's work."
Else
    lblStatus.Caption = VBODBC_SqlStmt.Caption
End If


End Sub

Sub pbCancel_Click ()

Dim ResCode As Integer

'confimr the calcel
ResCode = MsgBox("Are you sure you want to cancel the server's work?", 4 + 64 + 256, "Confirm Cancel")

If ResCode = 6 Then 'cancelled

    'let the sql loop know that the user pressed cancel
    VBODBC_SqlStmt.Cancelled = True
    lblStatus.Caption = "Cancelling..."
    pbCancel.Enabled = False

End If


End Sub

