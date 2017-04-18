VERSION 2.00
Begin Form frmDssSnapshot 
   BackColor       =   &H00C0C0C0&
   Caption         =   "SnapShot"
   ClientHeight    =   3870
   ClientLeft      =   1425
   ClientTop       =   2250
   ClientWidth     =   7575
   ForeColor       =   &H00000000&
   Height          =   4275
   HelpContextID   =   20038
   Left            =   1365
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   3870
   ScaleWidth      =   7575
   Tag             =   "3"
   Top             =   1905
   Width           =   7695
   Begin TextBox txtInfo 
      FontBold        =   0   'False
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   1695
      Left            =   4800
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   5
      Text            =   "txtInfo"
      Top             =   120
      Width           =   2655
   End
   Begin ComboBox cboOrientation 
      Height          =   300
      Left            =   2640
      Style           =   2  'Dropdown List
      TabIndex        =   3
      Top             =   600
      Width           =   1935
   End
   Begin ListBox lstPivotFields 
      Height          =   1200
      Left            =   120
      TabIndex        =   1
      Top             =   600
      Width           =   2295
   End
   Begin Grid grdPivot 
      Cols            =   15
      FixedCols       =   0
      FixedRows       =   0
      FontBold        =   0   'False
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   1815
      Left            =   120
      Rows            =   100
      TabIndex        =   0
      Top             =   1920
      Width           =   7335
   End
   Begin Label lblOrientation 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Orientation:"
      Height          =   255
      Left            =   2640
      TabIndex        =   4
      Top             =   240
      Width           =   2295
   End
   Begin Label lblPivotFields 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Pivot Fields:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   240
      Width           =   2295
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



'a copy ofthe buffer the the Snapshot Manager built that described
'the snapshot used by this particular chile form.
Dim SnapShot As SnapshotType

'Set to true when changing the pivot field selection
'in the list box, so the orientation list box knows it
'doesn't have to refresh the grid.
Dim ChangingPivotSelection As Integer


'object handles to corresponding xls workbook
Dim WorkBook As object
Dim PivotTableSheet As object
Dim PivotDataSheet As object
Dim PivotTable As object

Sub cboOrientation_Click ()

'change pivot table to reflect the orintation from the
'correponding field selected in lstPivotFields

Call StatusMsg("Changing field...")


'Copy new pivot table to grid, but only if user made value change,
'not if change is occuring because user changed pivot field selection
If Not ChangingPivotSelection Then
    'reset orientation to whatever the user selected
    PivotTable.PivotFields(lstPivotFields.ListIndex + 1).Orientation = cboOrientation.ListIndex
    'refresh the grid to reflect the changes
    Call CopyPivotTableToGrid
End If
     
'done! update status box
Call StatusMsg(NO_MSG)

End Sub

Sub CopyPivotTableToGrid ()

'copies the pivot table associated with this child onto the
'grid on this child.

Dim ResCode As Integer

'prepare for automation
Call VBEXCEL_WorkBookShow(WorkBook)

'select whole grid
grdPivot.SelStartRow = 0
grdPivot.SelEndRow = grdPivot.Rows - 1
grdPivot.SelStartCol = 0
grdPivot.SelEndCol = grdPivot.Cols - 1
'clear clipboard first
clipboard.Clear
'copy entire pivot table, including page fields, to clipboard
PivotTable.TableRange2.copy
'copy to clipboard
grdPivot.Clip = clipboard.GetText(1)
clipboard.Clear

'reset selection
grdPivot.SelStartRow = 0
grdPivot.SelEndRow = 0
grdPivot.SelStartCol = 0
grdPivot.SelEndCol = 0


'done with automation
ResCode = VBEXCEL_WorkBookHide(WorkBook)

End Sub

Sub Form_Load ()

Dim ResCode As Integer
Dim SP As String
Dim Parms() As String

Dim NumPageFields As Integer
Dim i As Integer

'-------------------------------
'initial display mode
'-------------------------------

'sum helpful text info
txtInfo = "This screen shows the incredible flexibility of pivot tables, and doesn't even include 'change page' or 'drill-down' functionality."
txtInfo = txtInfo & Chr$(13) & Chr$(10) & Chr$(13) & Chr$(10) & "Notice how only a couple lines of code are executed when moving data, Excel does all the work."
txtInfo = txtInfo & Chr$(13) & Chr$(10) & Chr$(13) & Chr$(10) & "Of course, a more suitable table and graphing interface should be designed for your specific users' requirements."

Width = 7695
Height = 4275
Show
Refresh

'Copy buffer to form level variable.  This was set when the
'user pressed the frmDssSnapshotMgr!pbSnapShot button.
SnapShot = NextSnapShot


'--------------------------------------------------
'build SQL - if we
'--------------------------------------------------
'Given the snapshot selection, build the appropriate SQL statement
'Notice the use of {} and the generic ODBC SQL, not native SQl Server
'SQL syntax
'If SnapShot.Level = LEVEL_SUM Then
'    'summary level
'    Sql = "{call sp_dss_sum}"
'    NumPageFields = 3 'year,month,title
'ElseIf SnapShot.Level = LEVEL_DETAIL Then
'    'detail level
'    If SnapShot.AllStatesChosen Then
'        'all states
'        Sql = "{call sp_dss_detail ('%')}"
'    Else
'        'specific state
'        Sql = "{call sp_dss_detail ('" & SnapShot.StateChosen & "')}"
'    End If
'    NumPageFields = 4 'year,month,title,state
'End If


'--------------------------------------------------
'determing stored procedure and parms
'--------------------------------------------------
If SnapShot.Level = LEVEL_SUM Then
    'summary level
    SP = "sp_dss_sum"
    ReDim Parms(0)
    NumPageFields = 3 'year,month,title
ElseIf SnapShot.Level = LEVEL_DETAIL Then
    'detail level
    If SnapShot.AllStatesChosen Then
	'all states
	SP = "sp_dss_detail"
	ReDim Parms(1)
	Parms(1) = ""
    Else
	'specific state
	SP = "sp_dss_detail"
	ReDim Parms(1)
	Parms(1) = SnapShot.StateChosen
    End If
    NumPageFields = 4 'year,month,title,state
End If


'--------------------------------------------------
'build pivot table
'--------------------------------------------------
Call StatusMsg("Building Pivot Table...")
ResCode = VBEXCEL_OpenPivotWorkbook(SP, Parms(), NumPageFields)
Me.Refresh
'Assign form level variables to object handles, since VB wouldn't
'let us pass them as a parm.
Set WorkBook = VBEXCEL_NextWorkBook
Set PivotTableSheet = VBEXCEL_NextPivotTableSheet
Set PivotTable = VBEXCEL_NextPivotTable
Set PivotDataSheet = VBEXCEL_NextPivotDataSheet


'--------------------------------------------------
'fill combo box with orientations
'--------------------------------------------------

cboOrientation.AddItem "0 - xlHidden"
cboOrientation.AddItem "1 - xlRowField"
cboOrientation.AddItem "2 - xlColumnField"
cboOrientation.AddItem "3 - xlPageField"
cboOrientation.AddItem "4 - xlDataField"


'--------------------------------------------------
'fill list box with pivot fields
'--------------------------------------------------
'loop through all pivot fields and place their names in the
'list box
For i = 1 To PivotTable.PivotFields.Count
    lstPivotFields.AddItem PivotTable.PivotFields(i).name
Next
lstPivotFields.ListIndex = 0


'--------------------------------------------------
'initilize and copy pivot table to grid
'--------------------------------------------------
Refresh
'make grid columns a little widet
For i = 0 To grdPivot.Cols - 1
    grdPivot.ColWidth(i) = 1500
Next
Call CopyPivotTableToGrid



Call StatusMsg(NO_MSG)


End Sub

Sub Form_Resize ()

'adjust grid to fit form
If windowstate <> 1 Then
    grdPivot.Width = Me.Width - 360
    grdPivot.Height = Me.Height - 2460
End If

End Sub

Sub Form_Unload (Cancel As Integer)

'close the workbook, we're done with this snapshot
Call VBEXCEL_ClosePivotWorkbook(WorkBook)


'erase object variables
Set WorkBook = Nothing
Set PivotTableSheet = Nothing
Set PivotDataSheet = Nothing
Set ChildForms((Me.Tag)) = Nothing


End Sub

Sub lstPivotFields_Click ()

'change cboOrientation to reflect the orintation from the
'correponding field selected in lstPivotFields


'tell the cboOrientation that its lstPivotFields making the change,
'and that the pivot table doesn't needs to be modifed.
ChangingPivotSelection = True
cboOrientation.ListIndex = PivotTable.PivotFields(lstPivotFields.ListIndex + 1).Orientation
ChangingPivotSelection = False

End Sub

