
Sub Process_altrows (Result As Integer, OutputData() As String, outputrowcnt As Integer, colpositions() As Integer)

Rem Alternate rows (from COMPUTE clause) only available in VBWin
Rem Get the number of columns in the compute row.
Rem Determine what type of aggregate each column uses
Rem Line up the column in the correct position
Rem Output the row.

	OutputData(outputrowcnt%) = " "
	outputrowcnt% = outputrowcnt% + 1
	AltStr1$ = Space$(256)
	AltStr2$ = Space$(256)
	AltStr3$ = Space$(256)

	numalts% = SqlNumAlts%(SqlConn, Result%)
	For x% = 1 To numalts%
	    altcol% = SqlAltColId%(SqlConn, Result%, x%)
	    alttype$ = SQLPRTYPE(SqlAltOp(SqlConn, Result%, x%))
	    altvalue$ = SqlAData$(SqlConn, Result%, x%)

	    Mid$(AltStr1$, colpositions(altcol%), Len(alttype$)) = alttype$
	    Mid$(AltStr2$, colpositions(altcol%), Len(alttype$)) = String$(Len(alttype$), "-")
	    Mid$(AltStr3$, colpositions(altcol%), Len(altvalue$)) = altvalue$
	    
	Next x%

	OutputData(outputrowcnt%) = AltStr1$
	outputrowcnt% = outputrowcnt% + 1
	OutputData(outputrowcnt%) = AltStr2$
	outputrowcnt% = outputrowcnt% + 1
	OutputData(outputrowcnt%) = AltStr3$
	outputrowcnt% = outputrowcnt% + 1
	OutputData(outputrowcnt%) = " "
	outputrowcnt% = outputrowcnt% + 1


End Sub

Sub Process_rpc_returns (OutputData() As String, outputrowcnt As Integer)

Rem See if there are any return parameters from a stored procedure (available in VBWin only).
Rem Then See if there is a return status

    numrets% = SQLNumRets(SqlConn)
    If numrets% <> 0 Then
	OutputData(outputrowcnt%) = " "
	outputrowcnt% = outputrowcnt% + 1
	For i% = 1 To numrets%
	    DataStr$ = "NAME: " + SQLRetName(SqlConn, i%)
	    DataStr$ = DataStr$ + "  TYPE: " + SQLPRTYPE(SQLRetType(SqlConn, i%))
	    DataStr$ = DataStr$ + "  LENGTH: " + Str$(SQLRetLen(SqlConn, i%))
	    DataStr$ = DataStr$ + "  VALUE: " + SQLRetData(SqlConn, i%)
	    OutputData(outputrowcnt%) = DataStr$
	    outputrowcnt% = outputrowcnt% + 1
	Next i%
    End If

    If (SQLHasRetStat(SqlConn) = SUCCEED%) Then
	OutputData(outputrowcnt%) = " "
	outputrowcnt% = outputrowcnt% + 1
	OutputData(outputrowcnt%) = "RETURN STATUS: " + Str$(SQLRetStatus(SqlConn))
	outputrowcnt% = outputrowcnt% + 1
    End If

End Sub

