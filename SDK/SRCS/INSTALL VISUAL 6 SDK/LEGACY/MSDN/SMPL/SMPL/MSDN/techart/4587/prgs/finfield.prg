PROCEDURE financialfields
	IF NOT Granted("OTHFINANCE","READ")
	   THISFORM.SetAll ( "Visible",  .F., "Financialfield" )
	ENDIF
	IF NOT Granted("OTHFINANCE","WRITE")
	   THISFORM.SetAll ( "Readonly", .T., "Financialfield" )
	ENDIF
ENDPROC
