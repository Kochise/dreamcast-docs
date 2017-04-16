**************************************************
*-- Class:        cmdnext (c:\pfl\pfl0895\classes\mylib.vcx)
*-- ParentClass:  commandbutton
*-- BaseClass:    commandbutton
*
DEFINE CLASS cmdnext AS commandbutton


	Height = 25
	Width = 40
	Picture = "..\bmps\wznext.bmp"
	Caption = ""
	ToolTipText = "Next record"
	select = .T.
	Name = "cmdnext"


	PROCEDURE Click
		SaveAlias = ALIAS()
		IF NOT EMPTY ( THISFORM.PrimaryTable )
		   SELECT    ( THISFORM.PrimaryTable )
		ENDIF
		IF NOT EOF()
		   SKIP
		   IF EOF()
		      GO BOTTOM
		   ENDIF
		ENDIF
		THISFORM.Refresh
		IF NOT EMPTY ( SaveAlias )
		   SELECT    ( SaveAlias )
		ENDIF
		THISFORM.TestBofEof
	ENDPROC


ENDDEFINE
*
*-- EndDefine: cmdnext
**************************************************
