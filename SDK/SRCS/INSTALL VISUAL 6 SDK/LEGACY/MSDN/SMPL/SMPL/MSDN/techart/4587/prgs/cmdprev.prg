**************************************************
*-- Class:        cmdprev (c:\pfl\pfl0895\classes\mylib.vcx)
*-- ParentClass:  commandbutton
*-- BaseClass:    commandbutton
*
DEFINE CLASS cmdprev AS commandbutton


	Height = 25
	Width = 40
	Picture = "..\bmps\wzback.bmp"
	Caption = ""
	ToolTipText = "Previous record"
	select = .T.
	Name = "cmdprev"


	PROCEDURE Click
		SaveAlias = ALIAS()
		IF NOT EMPTY ( THISFORM.PrimaryTable )
		   SELECT    ( THISFORM.PrimaryTable )
		ENDIF
		IF NOT BOF()
		   SKIP -1
		   IF BOF()
		      GO TOP
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
*-- EndDefine: cmdprev
**************************************************
