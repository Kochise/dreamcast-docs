VERSION 2.00
Begin Form frmDssSnapshotMgr 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "SnapShot Manager"
   ClientHeight    =   2805
   ClientLeft      =   1440
   ClientTop       =   1755
   ClientWidth     =   6180
   ControlBox      =   0   'False
   Height          =   3210
   HelpContextID   =   20002
   Left            =   1380
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   ScaleHeight     =   2805
   ScaleWidth      =   6180
   Tag             =   "1"
   Top             =   1410
   Width           =   6300
   Begin CommandButton pbSnapShot 
      Caption         =   "Take SnapShot"
      Height          =   495
      Left            =   4440
      TabIndex        =   4
      Top             =   2160
      Width           =   1575
   End
   Begin TextBox txtInfo 
      FontBold        =   0   'False
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   1575
      Left            =   3480
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   5
      Text            =   "txtInfo"
      Top             =   360
      Width           =   2535
   End
   Begin ListBox lstStates 
      Height          =   1005
      Left            =   240
      TabIndex        =   2
      Top             =   1560
      Width           =   2415
   End
   Begin OptionButton rbDetail 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Detail of states (Mgrs)"
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   840
      Width           =   2535
   End
   Begin OptionButton rbSum 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Sum of all states (Mgrs && Reps)"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Value           =   -1  'True
      Width           =   3015
   End
   Begin Label lblStates 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Show detail for the following state:"
      FontBold        =   0   'False
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   1320
      Width           =   2535
   End
End
Option Explicit

'-----------------------------------------------------------------------------------------------------
' VBDSS
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
' VBDSS is a MDI VB and SQL Server project template that demonstrates the
' decision support architecture concepts of this presentation.  It is
' designed to provide a sample shell of all the presentation concepts for
' easy modification to your own specification.
'
' It utilizes and requires the other reusable components of this
' presentation: VBODBC, VBSEC, and VBEXCEL.  It also utilizes the pubs
' database as its source for its DSS table.
'
' Comments, suggestions, and consulting opportunities welcome!
'
' Files
'       1. VBDSS.MAK    VB project make file
'       2. VBDSS.BAS    VB code module
'       3. VBDSS1.FRM   VB project MDI container form
'       4. VBDSS2.FRM   VB project "New SnapShot Manager" child form
'       5. VBDSS3.FRM   VB project "SnapShot" child form
'       6. VBDSS.SQL    SQL Server pubs script
'       7. (Other files from VBODBC, VBSEC, and VBEXCEL libraries.)
'
' Installation Instructions:
'       1. Login to SQL Server as sa and execute the VBDSS.SQL script.  This will:
'           - Create sample logins and pubs accounts: dss_manager, dss_rep, dss_programmer with passwords the same as the ID
'           - Create sample pubs groups: dss_managers, dss_reps, dss_programmers
'           - Create a sample table, dss, in pubs
'           - Create a data warehouse refresh stored procedure, sp_dss_refresh
'           - Create client application stored procedures, sp_dss_detail, sp_dss_sum, sp_dss_states
'           - Assign permissions to client-application stored procedures
'           - Executes sp_dss_refresh to populate table dss and simulate an overnight “batch refresh”
'       2. Login to SQL Server as sa.  Execute the VBSEC.SQL script against the pubs database.  This will install the sp_security stored procedure, used by VBDSS to query user security rights.
'       3. Install an ODBC data source on the client workstation that points to the SQL Server.
'       4. If the SQL Server supports only integrated security, you will need to create NT accounts for the SQL Server users sp_manager, sp_rep, and sp_programmer.
'       5. Verify that MS Excel 5.0 exists on the client workstation.
'-----------------------------------------------------------------------------------------------------

Sub Form_Load ()

Dim ResCode As Integer
Dim RowBuf() As Variant
Dim Parms() As String

'-------------------------------
'initial display mode
'-------------------------------

Top = 0
Left = 0
'throw some info text on the screen
txtInfo = "Notice how a logon from the 'rep' group has a greyed out detail button, since they don't have access to the server procedure sp_dss_managers."
txtInfo = txtInfo & Chr$(13) & Chr$(10) & Chr$(13) & Chr$(10) & "Pressing the 'Snapshot' button retrieves a creates a child form, which retrieves a result set into a pivot table based on the user's selction here."



'-------------------------------
'retrieve state info
'-------------------------------
'retrieve the state detail list from the server to populate in the
'states list box

Call StatusMsg("Retrieving state info...")

'add an "all" element to first entry, so the user can select all states
lstStates.AddItem "<All States>"
lstStates.ListIndex = 0


'Open sql statement

'This is what you would use for imbeded SQL
'Notice the ODBC generic SQL statement, as opposed to the SQL Server
'specific "execute sp_dss_states".
'ResCode = VBODBC_OpenSqlStmtDialog("{call sp_dss_states}", 0, "Loading states...")

ReDim Parms(0)
ResCode = VBODBC_OpenSqlProcDialog("sp_dss_states", Parms(), 0, "Loading states...")
Me.Refresh
If ResCode <> SQL_SUCCESS Then
    ResCode = MsgBox(VBODBC_LastErr.AllErrorInfo, 16, "ODBC Error")
End If

'populate state list box
ResCode = VBODBC_GetNextRow(RowBuf()) 'get 1st row
Do Until ResCode <> SQL_SUCCESS
    'add row to list box.  1st column of sp is the state name.
    lstStates.AddItem RowBuf(1)
    'get next row, if any
    ResCode = VBODBC_GetNextRow(RowBuf())
Loop

'close sql statement
ResCode = VBODBC_CloseSqlStmt()
If ResCode <> SQL_SUCCESS Then
    ResCode = MsgBox(VBODBC_LastErr.AllErrorInfo, 16, "ODBC Error")
End If

'----------------------------------------------------
'set control enable/disabled based on server security
'----------------------------------------------------
'since the SnapShot button runs sp_dss_sum when rbSum is
'selected, disable rbSum if the user doesn't have access to
'this stored procedure
If Not VBSEC_ExecSecurity("sp_dss_sum") Then
    rbSum.Enabled = False
End If

'since the SnapShot button runs sp_dss_detail when rbSum is
'selected, disable rbSum and its list box if the user doesn't have access to
'this stored procedure
If Not VBSEC_ExecSecurity("sp_dss_detail") Then
    rbDetail.Enabled = False
    lstStates.Enabled = False
End If



End Sub

Sub pbSnapShot_Click ()

Dim n As Integer
Dim ResCode As Integer


'---------------------------------------
'record selection
'---------------------------------------
'populate input buffer to new instance of frmDssSnapshot
If rbDetail Then 'detail information chosen
    'assign level
    NextSnapshot.Level = LEVEL_DETAIL
    'determin if all states have been chosen or not
    If lstStates.ListIndex > 0 Then
        NextSnapshot.AllStatesChosen = False
    Else
        NextSnapshot.AllStatesChosen = True
    End If
    'determin which state chosen, if any
    NextSnapshot.StateChosen = lstStates.List(lstStates.ListIndex)
Else 'summary info chosen
    'assign level
    NextSnapshot.Level = LEVEL_SUM
    'not applicable
    NextSnapshot.AllStatesChosen = False
    'not applicable
    NextSnapshot.StateChosen = ""
End If


'---------------------------------------
'build child form
'---------------------------------------
'create view form and load in array
n = UBound(ChildForms) + 1
ReDim Preserve ChildForms(n)
Set ChildForms(n) = New frmDssSnapshot
'show the child form.  It will take care of getting its data.
ChildForms(n).Show
ChildForms(n).Tag = n
NumChildForms = NumChildForms + 1


End Sub

