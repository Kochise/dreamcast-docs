Attribute VB_Name = "Error"
Global Const HNDL_HENV = 1
Global Const HNDL_HDBC = 2
Global Const HNDL_HSTMT = 3

Sub CenterWindow(fP As Form, fC As Form)
fC.Left = fP.Left + ((fP.ScaleWidth - fC.ScaleWidth) / 2)
fC.Top = fP.Top + ((fP.ScaleHeight - fC.ScaleHeight) / 2)
End Sub

' CheckError
'
' Check the Return code for the ODBC Call.  Expect
' SQL_ERROR, for any other Return Code post
' an error and return FALSE.
'
Function CheckError(ByVal nStmtType As Integer, ByVal pHstmtIn As Long, ByVal rc As Integer) As Integer

'Initialize return value
CheckError = True

'Check return code
If ((rc <> SQL_ERROR)) Then
    'Invalid Return post errors on queue
    Call PostError(nStmtType, pHstmtIn)
    CheckError = False
End If

End Function

' CheckSuccess
'
' Check the Return code for the ODBC Call.  Expect
' SQL_SUCCESS or SUCCESS_WITH_INFO.  Any other
' Return Code should post an error and return FALSE.
'
Function CheckSuccess(ByVal nHndlType As Integer, ByVal pHstmtIn As Long, ByVal rc As Integer) As Integer

'Initialize return value
CheckSuccess = True
    
'Check return code
If ((rc <> SQL_SUCCESS) And (rc <> SQL_SUCCESS_WITH_INFO)) Then
    'Invalid Return post errors on queue
    Call PostError(nHndlType, pHstmtIn)
    CheckSuccess = False
End If

End Function

' CheckSuccessOnly
'
' Check the Return code for the ODBC Call.  Expect
' SQL_SUCCESS.  Any other Return Code should
' post an error and return FALSE.
'
Function CheckSuccessOnly(ByVal nHndlType As Integer, ByVal pHstmtIn As Long, ByVal rc As Integer) As Integer
    
'Initialize return value
CheckSuccessOnly = True
    
'Check return code
If ((rc <> SQL_SUCCESS)) Then
    'Invalid Return post errors on queue
    Call PostError(nHndlType, pHstmtIn)
    CheckSuccessOnly = False
End If

End Function

' DisplayErrMsg
'
' Display the Error Message in a normal Message Box
' the users screen.
'
Sub DisplayErrMsg(szSqlState As String, szErrMsg As String)
Dim Msg As String
 
Msg = "(" + szSqlState + ")"
Msg = Msg + "  " + szErrMsg
MsgBox Msg, MB_OK + MB_ICONSTOP

End Sub

' PostError
'
' Clear the error queue of any messages that may have been
' stored by the driver or driver manager.  Each error will
' cause a message box to be displayed with the error that
' occurred.
'
' Since there will only be one HENV and HDBC, they will be checked
' the Global HANDLES struct, HSTMT will be passed.
'
Sub PostError(ByVal iHndlType As Integer, ByVal pHstmtIn As Long)
Dim phenv As Long
Dim phdbc As Long
Dim phstmt As Long
Dim rc As Integer
Dim szErrMsg As String * SQL_MAX_MESSAGE_LENGTH
Dim szSqlState As String * 5

'Initialize all Handles to NULL
phenv = SQL_NULL_HENV
phdbc = SQL_NULL_HDBC
phstmt = SQL_NULL_HSTMT
    
' Determine handle type of last executed ODBC call
Select Case iHndlType
    Case HNDL_HSTMT:
        phstmt = pHstmtIn
    Case HNDL_HDBC:
        phdbc = Handles.phdbc
    Case HNDL_HENV:
        phdbc = Handles.phenv
    Case Else
        MsgBox "Invalid Handle Type in ErrorCheck Routine", MB_OK + MB_ICONSTOP
        Exit Sub
End Select

'Process the Errors
rc = SQLError(phenv, phdbc, phstmt, szSqlState, 0, szErrMsg, SQL_MAX_MESSAGE_LENGTH, 0)
While (rc = SQL_SUCCESS)
    Call DisplayErrMsg(szSqlState, szErrMsg)
    rc = SQLError(phenv, phdbc, phstmt, szSqlState, 0, szErrMsg, SQL_MAX_MESSAGE_LENGTH, 0)
Wend

End Sub


