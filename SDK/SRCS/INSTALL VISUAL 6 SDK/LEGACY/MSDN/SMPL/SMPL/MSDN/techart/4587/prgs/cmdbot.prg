**************************************************
*-- Class:        cmdbott (c:\pfl\pfl0895\classes\mylib.vcx)
*-- ParentClass:  commandbutton
*-- BaseClass:    commandbutton
*
DEFINE CLASS cmdbott AS commandbutton


	Height = 29
	Width = 44
	Picture = "..\bmps\wzend.bmp"
	Caption = ""
	ToolTipText = "Go to the last record"
	Name = "cmdbott"


	PROCEDURE Click
		IF NOT EMPTY(THISFORM.PrimaryTable)
			SELECT (THISFORM.PrimaryTable)
			GO BOTTOM
		ENDIF
		THISFORM.Refresh
		THISFORM.TestBofEof
	ENDPROC


ENDDEFINE
*
*-- EndDefine: cmdbott
**************************************************
