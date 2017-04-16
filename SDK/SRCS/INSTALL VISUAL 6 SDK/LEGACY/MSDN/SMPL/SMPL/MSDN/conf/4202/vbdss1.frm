VERSION 2.00
Begin MDIForm frmDssMDI 
   Caption         =   "DSS"
   ClientHeight    =   3045
   ClientLeft      =   1230
   ClientTop       =   2835
   ClientWidth     =   7470
   Enabled         =   0   'False
   Height          =   3735
   Left            =   1170
   LinkTopic       =   "MDIForm1"
   Top             =   2205
   Width           =   7590
   Begin PictureBox picStatus 
      Align           =   2  'Align Bottom
      BackColor       =   &H00C0C0C0&
      Height          =   285
      Left            =   0
      ScaleHeight     =   255
      ScaleWidth      =   7440
      TabIndex        =   0
      Top             =   2760
      Width           =   7470
      Begin Label lblStatus 
         BackColor       =   &H00C0C0C0&
         Caption         =   "lblStatus"
         Height          =   255
         Left            =   0
         TabIndex        =   1
         Top             =   0
         Width           =   8055
      End
   End
   Begin Menu mnuFile 
      Caption         =   "&File"
      Begin Menu mnuExit 
         Caption         =   "E&xit"
      End
   End
   Begin Menu mnuWindow 
      Caption         =   "&Window"
      WindowList      =   -1  'True
      Begin Menu mnuCasCade 
         Caption         =   "&Casacade"
      End
      Begin Menu mnuTileHorizontal 
         Caption         =   "Tile &Horizontal"
      End
      Begin Menu mnuTileVertical 
         Caption         =   "Tile &Vertical"
      End
      Begin Menu mnuArrangeIcons 
         Caption         =   "&Arrange Icons"
      End
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

Sub MDIForm_Load ()

Dim ResCode As Integer
Dim ConnStrOut As String

'---------------------------------------
'set screen parms
'---------------------------------------
StatusMsg (NO_MSG)
Me.Height = (Screen.Height) * .85  'leave some room to see excel stop and start
Me.Width = Screen.Width
Me.Top = 0
Me.Left = 0
Show        'display while loading


'---------------------------------------
'open database
'---------------------------------------
'The last successful UID and DSN should be provided as defaults.
ResCode = VBODBC_OpenDatabaseDialog("dss_rep", "", "<Data Source Here>", "VBDSS Sample App", ConnStrOut)
If ResCode <> SQL_SUCCESS Then
    ResCode = MsgBox(VBODBC_LastErr.AllErrorInfo, 16, "ODBC Error")
    End 'logon failed
End If
'<save UID and DSN to an INI file here, so its provided as a default next time>


'---------------------------------------
'Initialize security
'---------------------------------------
'This queries the server and stored locally all the SPs the user
'can execute in the current database.
Call StatusMsg("Initilizing Security...")
ResCode = VBSEC_InitSecurity()
If ResCode <> SQL_SUCCESS Then
    MsgBox "Security Initilization Failed."
    MsgBox VBODBC_LastErr.AllErrorInfo
    End 'failed
End If

'---------------------------------------
'Check for minimum security
'---------------------------------------
'since at a bare mininium, a user needs to be ables to
'execute sp_dss_states to load the selection form frmDssNewSnapshotMgr,
'exit the program if the user doesn't have server permission to do so.
If Not VBSEC_ExecSecurity("sp_dss_states") Then
    MsgBox "You don't have access to run any part of this application!"
    End
End If



'---------------------------------------
'Load excel
'---------------------------------------
Call StatusMsg("Loading Excel...")
ResCode = VBEXCEL_OpenAppObj()
If ResCode Then
    ResCode = MsgBox("Could not load Microsoft Excel.", 16, "Error Launching Excel")
End If


'-----------------------------------------------
'prepare child form array and load select form
'-----------------------------------------------
'initialize array of child forms and assign first form
'to select form
Call StatusMsg("Loading Select form...")
ReDim ChildForms(1)
Set ChildForms(1) = frmDssSnapshotMgr
'show the SnapShot Manager
ChildForms(1).Show
NumChildForms = NumChildForms + 1

'done! reset status bar
Call StatusMsg(NO_MSG)


End Sub

Sub MDIForm_Unload (Cancel As Integer)

'call our generic shutdown routine
Call ShutDown

End Sub

Sub mnuArrangeIcons_Click ()

frmDssMDI.Arrange ARRANGE_ICONS


End Sub

Sub mnuCasCade_Click ()

frmDssMDI.Arrange CASCADE

End Sub

Sub mnuExit_Click ()

'call out generic shutdown routine.
Call ShutDown
End

End Sub

Sub mnuTileHorizontal_Click ()

frmDssMDI.Arrange TILE_HORIZONTAL


End Sub

Sub mnuTileVertical_Click ()

frmDssMDI.Arrange TILE_VERTICAL


End Sub

