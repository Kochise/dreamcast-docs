**************************************************
*-- Class:        cmdexit (c:\pfl\pfl0895\classes\mylib.vcx)
*-- ParentClass:  commandbutton
*-- BaseClass:    commandbutton
*
DEFINE CLASS cmdexit AS commandbutton


	AutoSize = .F.
	Height = 25
	Width = 40
	FontSize = 9
	Caption = " E\<xit"
	ToolTipText = "Exit this screen"
	select = .T.
	Name = "cmdexit"


	PROCEDURE Click
		THISFORM.Release
	ENDPROC


ENDDEFINE
*
*-- EndDefine: cmdexit
**************************************************
