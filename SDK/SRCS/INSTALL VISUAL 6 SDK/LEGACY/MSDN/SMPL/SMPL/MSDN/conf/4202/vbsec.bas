Option Explicit


'-----------------------------------------------------------------------------------------------------
' VBSEC
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
' VBSEC is a Visual Basic library that provides an easy method of inquiring
' whether or not a user has execute privileges on a particular SQL Server
' stored procedure.  It requires the use of VBODBC and the sp_security
' stored procedure.
'
' Comments, suggestions, and consulting opportunities welcome!
'
' Files
'       1. VBSEC.BAS        VB module
'       2. VBSEC.SQL        SQL Server sp_security stored procedure script
'
' APIs:
'       1. VBSEC_InitSecurity() - Retrieves the server, with sp_security, a list of stored procedures that the current VBODBC connection can execute.
'       2. VBSEC_ExecSecurity() - Given a stored procedure, returns true if the current database connection is able to execute it.
'
' Instructions:
'       1. Add VBSEC.BAS to your project.
'       2. Follow the instructions later in this presentation and add the VBODBC files to your project.
'       3. Have the VB application connect to a data source.
'       4. Make sure the stored procedure sp_security has been installed in the data source’s database.
'       5. Call VBSEC_InitSecurity to initialize security and receive server stored procedure security parms.
'       6. Call VBSEC_ExecSecurity whenever the application needs to determine whether the database connection has execute privileges on a stored procedure.
'-----------------------------------------------------------------------------------------------------

'name of SQL Server security stored procedure
Global Const VBSEC_SP_NAME = "sp_security"

'array storing stored procedure information
Type VBSEC_SPType
    SPName As String
End Type
Global VBSEC_SPs() As VBSEC_SPType

Function VBSEC_ExecSecurity (ByVal SPName As String) As Integer

'Returns TRUE if user has execute privliges on stored
'procedure SPName

Dim i As Integer

'clean up string
SPName = Trim$(UCase$(SPName))


'loop through array
For i = 1 To UBound(VBSEC_SPs)
    If VBSEC_SPs(i).SPName = SPName Then
	'we have a match!
	VBSEC_ExecSecurity = True
	Exit Function
    End If
Next

'no match
VBSEC_ExecSecurity = False







End Function

Function VBSEC_InitSecurity () As Integer

'Requires VBODBC module.

'Initializes internal array that stores all SPs that current user
'has access to execute.


Dim Cancelled As Integer
Dim ResCode As Integer
Dim RowBuf() As Variant
Dim i As Integer
Dim Parms() As String

ReDim VBSEC_SPs(0)

ReDim Parms(0)
ResCode = VBODBC_OpenSqlProcDialog(VBSEC_SP_NAME, Parms(), Cancelled, "Retrieving Security Information...")
If ResCode <> SQL_SUCCESS Then
    VBSEC_InitSecurity = SQL_ERROR
    Exit Function
End If

'retrieve results
Do
    
    'try to get next record
    ResCode = VBODBC_GetNextRow(RowBuf())
    
    'if error or end of data then exit loop
    If ResCode = SQL_ERROR Then
	VBSEC_InitSecurity = SQL_ERROR
	Exit Function
    ElseIf ResCode = SQL_NO_DATA_FOUND Then
	Exit Do
    End If
    
    'got another one
    'increment counter
    i = i + 1
    'make room for another element
    ReDim Preserve VBSEC_SPs(i)
    'assign SP infor to structure
    VBSEC_SPs(i).SPName = Trim$(UCase$(RowBuf(1)))


Loop 'loop through each row

'close stmt
ResCode = VBODBC_CloseSqlStmt()
If ResCode <> SQL_SUCCESS Then
    VBSEC_InitSecurity = SQL_ERROR
    Exit Function
End If

VBSEC_InitSecurity = SQL_SUCCESS


End Function

