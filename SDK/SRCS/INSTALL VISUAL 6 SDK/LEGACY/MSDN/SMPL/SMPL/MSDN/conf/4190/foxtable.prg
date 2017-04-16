** NOTE **
*-- For now, make sure Word is running before
*-- running this program. This program will dump the
*-- structure of all DBF files in a directory to a word
*-- document. An good enhancement to this program would
*-- be a front end that would allow the user to specify
*-- a database and tables for which to print structures for. 

CLOSE ALL
SET TALK OFF

#DEFINE TAB						CHR(9)
#DEFINE CR						CHR(13)

LOCAL laDBFs[1], ;
			i, ;
			lnDBFCount, ;
			lnField

**** OPEN YOUR DATABASE HERE ****
OPEN DATA TASTRADE
lnDBFCount = ADBOBJECTS(laDBFs, "TABLE")

SET PROC TO ..\OLECLASS.PRG

IF lnDBFCount > 0
	loWord = CREA("SpecialWinWord")
	loWord.Do("FileNew")

	FOR i = 1 TO lnDBFCount
		USE (laDBFs[i])
		loWord.BoldInsert(UPPER(laDBFs[i]) + CR)
		loWord.Do("TableInsertTable(0, 4, FCOUNT() + 1, 0, 0, 23, 1)")
		loWord.BoldInsertCell("Field Name")
		loWord.BoldInsertCell("Field Description")
		loWord.BoldInsertCell("Type")
		loWord.BoldInsertCell("Width")
		
		FOR lnField = 1 TO FCOUNT()
			loWord.InsertCell(FIELD(lnField))
			loWord.InsertCell(DBGETPROP(ALIAS() + "." + FIELD(lnField), "FIELD", "Comment"))
			loWord.InsertCell(TYPE("EVAL(FIELD(lnField))"))
			loWord.InsertCell(STR(FSIZE(FIELD(lnField))))
			IF lnField = FCOUNT()
				loWord.Do("EndOfDocument")
				loWord.Insert(CR)
			ENDIF
		ENDFOR
	ENDFOR
ENDIF

SET PROC TO
CLOSE ALL

DEFINE CLASS SpecialWinWord AS WinWord
	*-- Turns bold on, and delegates the actual
	*-- insertion of text to the Insert() method
	FUNCTION BoldInsert(tcText)
		this.oOLEApp.Bold
		this.Insert(tcText)
	ENDFUNC

	*-- Turns bold on, and delegates the actual
	*-- insertion of text to the InsertCell method
	FUNCTION BoldInsertCell(tcText)
		this.oOLEApp.Bold
		this.InsertCell(tcText)
	ENDFUNC
	
	*-- Delegates the actual insertion of text to the
	*-- Insert() method, and moves the insertion point
	*-- to the next available cell
	FUNCTION InsertCell(tcText)
		this.Insert(tcText)
		this.oOLEApp.NextCell
ENDDEFINE