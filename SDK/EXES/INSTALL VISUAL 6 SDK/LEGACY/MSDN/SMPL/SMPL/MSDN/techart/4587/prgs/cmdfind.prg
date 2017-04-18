**************************************************
*-- Class:        cmdfind (c:\pfl\pfl0895\classes\mylib.vcx)
*-- ParentClass:  commandbutton
*-- BaseClass:    commandbutton
*
DEFINE CLASS cmdfind AS commandbutton


	Height = 25
	Width = 40
	Picture = "..\bmps\find.bmp"
	Caption = ""
	ToolTipText = "Open/Find a record"
	select = .T.
	Name = "cmdfind"


	PROCEDURE Click
		IF NOT EMPTY(THISFORM.PrimaryTable)
			SELECT (THISFORM.PrimaryTable)
		ENDIF
		IF NOT "JKEY" $ SET("CLASSLIB")
		   SET LIBRARY TO JKEY ADDITIVE
		ENDIF
		_JExitKey = 13
		=JKeyInit("U")
		IF EMPTY (THISFORM.BrowseFields)
			BROWSE 					TITLE "Highlight your selection and press ENTER"
		ELSE
			LOCAL lFields
			lFields = THISFORM.BrowseFields
			BROWSE FIELDS &lFields	TITLE "Highlight your selection and press ENTER" 
		ENDIF
		=JKeyCanc()
		THISFORM.TestBofEof
		*THISFORM.SetAll("Enabled", .F., "cmdSave"  )
		*THISFORM.SetAll("Enabled", .F., "cmdCancel")
		THISFORM.Refresh
	ENDPROC


ENDDEFINE
*
*-- EndDefine: cmdfind
**************************************************
