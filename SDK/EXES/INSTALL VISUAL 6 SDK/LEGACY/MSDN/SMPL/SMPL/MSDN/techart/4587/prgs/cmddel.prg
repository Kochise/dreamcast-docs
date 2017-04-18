**************************************************
*-- Class:        cmddelete (c:\pfl\pfl0895\classes\mylib.vcx)
*-- ParentClass:  commandbutton
*-- BaseClass:    commandbutton
*
DEFINE CLASS cmddelete AS commandbutton


	Height = 25
	Width = 40
	Picture = "..\bmps\delete.bmp"
	Caption = ""
	ToolTipText = "Delete this record"
	select = .T.
	Name = "cmddelete"


	PROCEDURE Click
		SaveAlias = ALIAS()
		IF TYPE  ( "THISFORM.PrimaryTable" ) <> [U]
		   SELECT ( THISFORM.PrimaryTable )
		ENDIF
		IF MessageBox("Delete this record?", 4 + 32 + 256 , "Note: Can't undo" ) = 6
		   DELETE NEXT 1
		   SET DELETED ON
		   GO TOP
		ENDIF
		THISFORM.Refresh
		IF NOT EMPTY ( SaveAlias )
		   SELECT    ( SaveAlias )
		ENDIF
		THISFORM.TestBofEof
	ENDPROC


ENDDEFINE
*
*-- EndDefine: cmddelete
**************************************************
