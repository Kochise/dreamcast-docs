'$INCLUDE: 'VBQUERY.BI'
'$INCLUDE: 'VBDSQL.BI'

Sub ChangePrimaryWindowCaption ()
	PrimaryWindow.Caption = PrimaryWindowTitle + " - " + Servername$ + "/" + DatabaseName$
End Sub

Function CheckServerConnection () As Integer
	If SqlConn <> 0 Then
	    CheckServerConnection = 1
	Else
	    CheckServerConnection = 0
	End If
End Function

Sub DoubleQuotes (InString As String)

Rem
Rem This will replace all double quotes with ""
Rem and all single quotes with ''
Rem

DOUBLEQUOTE$ = Chr$(34) + Chr$(34)
SINGLEQUOTE$ = Chr$(39) + Chr$(39)
Static mychar As String * 1

Rem
Rem Get the length of the string coming in
Rem Set the length of TmpString to length of string coming in + 100 new chars
Rem

y% = Len(InString)
TmpString$ = Space$(y% + 100)
i% = 1

For x% = 1 To y%

	mychar$ = Mid$(InString, x%, 1)
	If mychar$ = Chr$(34) Then
	Mid$(TmpString$, i%, 2) = DOUBLEQUOTE$
	i% = i% + 1
	Else
	If mychar$ = Chr$(39) Then
		Mid$(TmpString$, i%, 2) = SINGLEQUOTE$
		i% = i% + 1
	Else
		mychar$ = Mid$(InString, x%, 1)
		Mid$(TmpString$, i%) = mychar$
	End If
	End If
	i% = i% + 1
Next x%

InString$ = RTrim$(TmpString$)

End Sub

Function ExecuteSQLCommand (cmd As String) As Integer

Rem
Rem This routine executes a command(s) and returns whether the
Rem execute succeeded or failed.
Rem

SQLStatus% = SUCCEED
ExecuteSQLCommand = SUCCEED
If SqlCmd(SqlConn, cmd$) = FAIL% Then
	SQLStatus% = FAIL
	ExecuteSQLCommand = FAIL
End If
If SqlExec(SqlConn) = FAIL% Then
	SQLStatus% = FAIL
	ExecuteSQLCommand = FAIL
End If
End Function

Sub FixTextLineFeeds (InString As String)

Rem
Rem This will replace all LF characters in the InString with CRLF
Rem

CRLF$ = Chr$(13) + Chr$(10)
LF$ = Chr$(10)

Rem
Rem Get the length of the string coming in
Rem Set the length of TmpString to length of string coming in + 100 new chars
Rem

y% = Len(InString)
TmpString$ = Space$(y% + 100)
i% = 1

For x% = 1 To y%

	mychar$ = Mid$(InString, x%, 1)
	If mychar$ = LF$ Then
	Mid$(TmpString$, i%, 1) = CRLF$
	i% = i% + 1
	Else
	mychar$ = Mid$(InString, x%, 1)
	Mid$(TmpString$, i%) = mychar$
	End If
	i% = i% + 1
Next x%

InString$ = RTrim$(TmpString$)
End Sub

Function GetDatabases (Database_Control As Control) As Integer

Rem
Rem This routine gets the name of all the databases on the SQL Server.
Rem Fill each element in the combobox or list box which is passed into this procedure
Rem execute the command.  Get each database name and fill the combobox.
Rem

	If ExecuteSQLCommand("Select name from master..sysdatabases") = FAIL% Then
	GetDatabases = FAIL
	Exit Function
	Else
	If SqlResults(SqlConn) = FAIL% Then Exit Function
	While SqlNextRow(SqlConn) <> NOMOREROWS%
		Database_Control.AddItem SqlData(SqlConn, 1)
	Wend
	End If

Rem If this is a combobox we are filling, then display the first database in the list to start with

	If TypeOf Database_Control Is ComboBox Then
	Database_Control.Text = Database_Control.List(0)
	End If

	GetDatabases = SUCCEED
End Function

Function LoginToServer () As Integer

LoginToServer = SUCCEED

Rem
Rem Check to see if the connection is live, if so, then close it
Rem Set the max time to login to 30 seconds
Rem Open the new connection
Rem Change the caption of the application to reflect the server name and the database
Rem Set the max time we will wait for a SQL Server response
Rem

If SqlConn <> 0 Then SqlClose (SqlConn)
Status% = SqlSetLoginTime%(LoginTimeout%)
SqlConn = SqlOpenConnection(Servername$, LoginID$, password$, ProgramName$, ProgramName$)
If SqlConn <> 0 Then
	DatabaseName$ = SqlName(SqlConn)
	ChangePrimaryWindowCaption
	Result% = SqlSetTime%(QueryTimeout%)
Else
	DatabaseName$ = ""
	Servername$ = ""
	LoginToServer = FAIL
End If

End Function

Sub Logoff ()
	If SqlConn <> 0 Then
	SqlClose (SqlConn)
	Servername$ = "[No server]"
	DatabaseName$ = "[no database]"
	ChangePrimaryWindowCaption
	End If
End Sub

Function MakeRuleList (Rawtext As String) As String

Rem
Rem This functions takes a rule of type "IN" from sp_helptext and makes it a
Rem comma delimited list for easy use in list boxes
Rem

start% = InStr(1, Rawtext$, "'")
MakeRuleList = Mid$(Rawtext$, start%, Len(Rawtext$) - 2)
End Function

Sub ParseRule (Rulename() As String)

Rem
Rem This routine takes the comma delimeted rules,which came from the
Rem MakeRuleList procedure, removes the quotes and stores the values
Rem in an array.  This is good for use in combo and list boxes.
Rem

in$ = Rulename$(0)

start% = 1
For i% = 0 To 100
	endpos% = InStr(start% + 1, in$, "'")
	Rulename(i%) = Mid$(in$, start% + 1, (endpos% - start%) - 1)
	start% = InStr(endpos% + 1, in$, "'")
	If start% = 0 Then Exit For
Next i%

End Sub

Function Process_SQL_query (cmd As String, OutputData() As String) As Long

Rem
Rem This routine will process query rows and output the total number
Rem of rows which reflects the number of items in the output array.
Rem
Rem Define array for column lengths, column positions, and column types
Rem Define structures for getting a compute column's information and getting
Rem a regular column's information
Rem

Rem Declare a local error handler for string overflows
On Error GoTo CancelQuery

Static ColValue$
Static collengths() As Long
ReDim Preserve collengths(255) As Long
Static colpositions() As Integer
ReDim Preserve colpositions(255) As Integer
Static Coltypes() As Integer
ReDim Preserve Coltypes(50) As Integer

Process_SQL_query = 0

Rem
Rem Define the new line character and the tab key
Rem Get the command from the QUERY_FIELD.
Rem Fill the command buffer. If fail, then exit the subroutine.
Rem Execute the command
Rem

NL$ = Chr$(13) + Chr$(10)
COLSEP$ = " "

If cmd$ <> "" Then
	If ExecuteSQLCommand(cmd$) = FAIL% Then Exit Function
End If

outputrowcnt% = 0

Rem
Rem Get each set of results
Rem Get the number of compute columns, order by columns, and select columns
Rem Get the exact position of each column (for lining up compute columns)
Rem

Do Until ResultProcess% = NOMORERESULTS%
    ResultProcess% = SqlResults(SqlConn)
    If ResultProcess% = NOMORERESULTS% Or ResultProcess% = FAIL Then Exit Do

    numcol% = SqlNumCols%(SqlConn)
    If numcol% > 0 Then
	numorder% = SqlNumOrders%(SqlConn)
	colline$ = ""
	coluline$ = ""

Rem
Rem Get the column name and length for each column
Rem Format and output the column headings (max 256 chars wide).
Rem

	For x% = 1 To numcol%
	colname$ = SqlColName(SqlConn, x%)
	Coltypes(x%) = SqlColType(SqlConn, x%)
	collengths(x%) = SqlColLen(SqlConn, x%)
	
	' templen holds length of column data.  truncate text and image
	tmplen% = collengths(x%)
	If tmplen% > 255 Then tmplen% = 255
	
	actuallen& = Len(colname$)
	
	If x% = 1 Then
	   colpositions(x%) = 1
	Else
		colpositions(x%) = Len(colline$) + Len(COLSEP$)
	End If
	 
	If actuallen& < tmplen% Then
		colline$ = colline$ + colname$ + Space$((tmplen% - actuallen&) + 1) + COLSEP$
		coluline$ = coluline$ + String$(Len(colname$), "_") + Space$((tmplen% - actuallen&) + 1) + COLSEP$
	Else
		colline$ = colline$ + colname$ + COLSEP$
		coluline$ = coluline$ + String$(Len(colname$), "_") + COLSEP$
	End If
	
	Next x%

    
	OutputData(outputrowcnt%) = colline$
	outputrowcnt% = outputrowcnt% + 1
	OutputData(outputrowcnt%) = coluline$
	outputrowcnt% = outputrowcnt% + 1
	OutputData(outputrowcnt%) = " "
	outputrowcnt% = outputrowcnt% + 1

    End If   'end of numcol% > 0 test


Rem
Rem Get each row of data, and process according to type of row
Rem Output each row into the list box
Rem

    RowProcess% = 99
    Do Until RowProcess% = NOMOREROWS%
	DataStr$ = ""
	Result% = SqlNextRow(SqlConn)
	If Result% = NOMOREROWS% Or Result% = FAIL Then Exit Do

Rem
Rem Process a COMPUTE Row  (Available in VB Win only).
Rem In DOS, this function pops up a message box saying COMPUTE rows are not supported.
Rem

	If Result% <> REGROW Then
	Process_altrows Result%, OutputData(), outputrowcnt%, colpositions()
	Else

Rem
Rem Process a regular row.
Rem Get the column value and length.
Rem If it is a Text column, then change the LF to CRLF if they exist
Rem Align columns even with the column headings.
Rem
	For x% = 1 To numcol%
		ColValue$ = SqlData(SqlConn, x%)
		actuallen& = Len(ColValue$)
		If actuallen& > 255 Then
		ColValue$ = Left$(ColValue$, 255)
		actuallen& = 255
		End If
			  
		If Coltypes(x%) = SQLTEXT% Then
		FixTextLineFeeds ColValue$
		End If

		If x% <> numcol% Then
		DataStr$ = DataStr$ + ColValue$ + Space$(colpositions(x% + 1) - colpositions(x%) - actuallen&)
		Else
		DataStr$ = DataStr$ + ColValue$
		End If

		ColValue$ = ""
	Next x%

	OutputData(outputrowcnt%) = DataStr$
	End If
	outputrowcnt% = outputrowcnt% + 1

    Loop        'End of row loop

Rem
Rem Output the number of rows affected by the query (if applicable)
Rem Output the sort order (if applicable)
Rem

    rowcnt& = SqlCount(SqlConn)
    If SqlIsCount(SqlConn) Then
	DataStr$ = "(" + Str$(rowcnt&) + " rows affected)"
	OutputData(outputrowcnt%) = " "
	OutputData(outputrowcnt% + 1) = DataStr$
	outputrowcnt% = outputrowcnt% + 2
    End If

    If numorder% > 0 Then
	OutputData(outputrowcnt%) = " "
	DataStr$ = "Sort Order: "
	For y% = 1 To numorder%
		ordercol$ = SqlColName(SqlConn, SqlOrderCol(SqlConn, y%))
		DataStr$ = DataStr$ + " " + ordercol$
	Next y%
	OutputData(outputrowcnt% + 1) = DataStr$
	outputrowcnt% = outputrowcnt% + 2
    End If

Loop        'End of result loop

Rem
Rem Check for return parameters and return status from stored procedures at the end
Rem of every result set.  Available in VBWin only.
Rem

Process_rpc_returns OutputData(), outputrowcnt%
Process_SQL_query = outputrowcnt%

Exit Function

CancelQuery:
	Result% = SqlCancel%(SqlConn)
	Msg$ = "Error number " + Str$(Err) + ":  " + Error$ + NL$
	Msg$ = Msg$ + "Query Cancelled" + NL$
	MsgBox Msg$, MB_ICONEXCLAMATION, "Visual Basic Error"
	Exit Function

End Function

Function UserSqlErrorHandler% (SqlConn As Integer, Severity As Integer, ErrorNum As Integer, OsErr As Integer, ErrorStr As String, OsErrStr As String)
'UserSqlErrorHander% - This function is REQUIRED for all VBDSQL applications.  It
'is called by the VB-DOS interface code for DB-LIBRARY whenever a
'DB-LIBRARY error occurs.  In VB-Win, it can be called from the error event handler.

'This function can do anything EXCEPT call another
'DB-LIBRARY function (with the exception of SqlDead%, which you can
'call to determine if the connection is still intact).
'
'You can return 1 of 3 values:
' INTEXIT     - exit the program
' INTCANCEL   - cancel the operation
' INTCONTINUE - continue the operation (can only continue on timeout read
'                    errors, which usually occur if a table that is locked
'                    is updated or read)
'

Rem
Rem Only display message if it's not a notification that there's a server error
Rem

	If ErrorNum% <> SQLESMSG% Then
	MsgBox ("DBLibrary Error: " + Str$(ErrorNum%) + " " + ErrorStr$)
	End If



	'If an operating-system error occurred, print the error string.
	 If OsErr% <> -1 Then
		MsgBox ("Operating-System Error: " + OsErrStr$)
	 End If

	'Exit if the error is fatal.
	If Severity% = EXFATAL Then
		UserSqlErrorHandler% = INTEXIT
	Else
		UserSqlErrorHandler% = INTCANCEL
	End If


End Function

Sub UserSqlMsgHandler (SqlConn As Integer, Message As Long, State As Integer, Severity As Integer, MsgStr As String)
'UserSqlMsgHandler - This procedure is REQUIRED for VBDSQL applicaitons.
'In VB-DOS, it is called by BASIC DB-LIBRARY whenever a connected server needs to
'issue a message to the client.  You can call it from the message handler event
'in VB-Win

NL$ = Chr$(13) + Chr$(10)

Rem
Rem Only display the message if it's not a general msg or a change language message
Rem

	If Message& <> 5701 And Message& <> 5703 Then
	Msg$ = "SQL Server Error: " + Str$(Message&) + " " + MsgStr$ + NL$
	Msg$ = Msg$ + "State=" + Str$(State%) + ", Severity=" + Str$(Severity)

	MsgBox Msg$
	End If
	

End Sub

Function WarningMessage (MsgStr As String) As Integer

Rem
Rem This routine displays a warning message with a YES and NO button
Rem and returns the result.
Rem

Const MB_YESNO = 4
Const MB_ICONEXLAMATION = 48
Const IDYES = 6
Const IDNO = 7
Const DEFBUTTON2 = 256

DgDef% = MB_YESNO + MB_ICONEXCLAMATION + MB_DEFBUTTON2
Response% = MsgBox(MsgStr$, DgDef%, "System Warning")
If Response% = IDNO Then
	WarningMessage = 0
Else
	WarningMessage = 1
End If
End Function

