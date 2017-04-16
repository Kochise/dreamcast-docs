**************************************************
*-- Class:        inputfield (c:\pfl\pfl0895\classes\mylib.vcx)
*-- ParentClass:  textbox
*-- BaseClass:    textbox
*
DEFINE CLASS inputfield AS textbox


	FontBold = .T.
	FontName = "Courier New"
	FontSize = 8
	Enabled = .F.
	Format = ""
	Height = 23
	Width = 113
	ColorScheme = 1
	Name = "inputfield"


	PROCEDURE GotFocus
		THIS.ForeColor=RGB ( 255, 255, 255 )
		THIS.BackColor=RGB ( 255,   0,   0 )
	ENDPROC


	PROCEDURE LostFocus
		THIS.BackColor=RGB ( 255, 255, 255 )
		THIS.ForeColor=RGB (   0,   0,   0 )
	ENDPROC


ENDDEFINE
*
*-- EndDefine: inputfield
**************************************************
