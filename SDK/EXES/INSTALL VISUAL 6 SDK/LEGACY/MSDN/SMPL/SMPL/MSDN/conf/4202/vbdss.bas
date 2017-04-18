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




'-------------------------------------------
'Input parms for frmDssSnapshot
'-------------------------------------------
'Buffer that holds all information passed from frmDssDelect
'to frmDssSnapshot when a new snapshot is requested.  It is all the info
'the new child form needs to create the snapshot.
Type SnapshotType
    Level As Integer                'whether sum or detail chosen, defined by LEVEL_ constants below
    AllStatesChosen As Integer      'true if user selected <all states>
    StateChosen As String           'the specific state chosen, if any
End Type
Global Const LEVEL_SUM = 0     'state summary selected
Global Const LEVEL_DETAIL = 1  'state detail selected
Global NextSnapshot As SnapshotType



'used by StatusMsg to indicate no message
Global Const NO_MSG = ""

'-----------------------------------------------------
'CHILD FORM INFORMATION
'-----------------------------------------------------
'array that holds all child form pointers
Global ChildForms() As form
'keeps track of the number fo chile forms
Global NumChildForms As Integer


'------------------------------------------------------------------------
'Windows and VB constants used by VBDSS
'------------------------------------------------------------------------


'nCmdShow Show window options, others available
Global Const SW_SHOW = 5            'active
Global Const SW_SHOWMINIMIZE = 2    'active
Global Const SW_SHOWMAXIMIZE = 3    'active
Global Const SW_MINNOACTIVE = 7     'not active, minimized


' Arrange Method
' for MDI Forms
Global Const CASCADE = 0
Global Const TILE_HORIZONTAL = 1
Global Const TILE_VERTICAL = 2
Global Const ARRANGE_ICONS = 3

' Show parameters
Global Const SHOW_MODAL = 1
Global Const SHOW_MODELESS = 0

Sub ShutDown ()

'Shuts down the MDI application

Dim n As Integer
Dim x As Integer
Dim ResCode As Integer

'since this is an all-encompassing redundant shutdown routine,
'we may get error msgs to ignore since we are trying to do things
On Error Resume Next

'tell user whats going on
Call StatusMsg("Shutting Down...")


'close all child windows even though they should already be closed
n = UBound(ChildForms)
For x = n To 1 Step -1
    If Not (ChildForms(x) Is Nothing) Then
	Unload ChildForms(x)
    End If
Next x

'close down Excel if applicable
Call VBEXCEL_CloseAppObj

'close the database connection
ResCode = VBODBC_CloseDatabase()
If ResCode <> SQL_SUCCESS Then
    ResCode = MsgBox(VBODBC_LastErr.AllErrorInfo, 16, "ODBC Error")
End If

End Sub

Sub StatusMsg (Msg1 As String)

'Logs a status message to an application-specific
'control and changes mousepointer.

'Pass NO_MSG as Msg1 to erase msg and reset mousepointer.

Dim NewMsg As String
Dim StatusControl As control

'!!! CHANGE THIS LINE TO REFLECT THE CONTROL THAT GETS STATUS MSGS !!!
Set StatusControl = frmDssMDI.lblStatus


If Msg1 = NO_MSG Then
    NewMsg = "Ready."
    Screen.MousePointer = 0
Else
    NewMsg = Msg1
    Screen.MousePointer = 11
End If


StatusControl.Caption = NewMsg
StatusControl.Refresh


End Sub

