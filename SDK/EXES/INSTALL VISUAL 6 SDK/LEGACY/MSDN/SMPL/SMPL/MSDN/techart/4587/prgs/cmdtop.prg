**************************************************
*-- Class:        cmdtop (c:\pfl\pfl0895\classes\mylib.vcx)
*-- ParentClass:  commandbutton
*-- BaseClass:    commandbutton
*
DEFINE CLASS cmdtop AS commandbutton


	Height = 31
	Width = 39
	Picture = "..\bmps\wztop.bmp"
	Caption = ""
	ToolTipText = "Go to the first record"
	Name = "cmdtop"


	PROCEDURE Click
		IF NOT EMPTY(THISFORM.PrimaryTable) 
			SELE (THISFORM.PrimaryTable)
			GO TOP
		ENDIF
		THISFORM.Refresh
		THISFORM.TestBofEof

	ENDPROC


ENDDEFINE
*
*-- EndDefine: cmdtop
**************************************************
