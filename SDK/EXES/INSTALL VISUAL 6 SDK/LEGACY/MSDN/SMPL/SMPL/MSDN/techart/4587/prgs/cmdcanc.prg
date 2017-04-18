**************************************************
*-- Class:        cmdcancel (c:\pfl\pfl0895\classes\mylib.vcx)
*-- ParentClass:  commandbutton
*-- BaseClass:    commandbutton
*
DEFINE CLASS cmdcancel AS commandbutton


	Height = 25
	Width = 40
	Picture = "..\bmps\undo.bmp"
	Caption = ""
	ToolTipText = "Abandon changes"
	select = .T.
	Name = "cmdcancel"


	PROCEDURE Click
		IF NOT EMPTY ( THISFORM.PrimaryTable )
		   SELECT	 ( THISFORM.PrimaryTable )
		ENDIF

		=TableRevert()	&& PriaryTables must be buffered

		IF NOT THISFORM.Adding
		   GO ( THISFORM.SaveRecord )
		ENDIF

		THISFORM.Refresh

		THISFORM.Adding = .F.

		THISFORM.SetAll("Enabled", .F., "Combobox" 	  	)
		THISFORM.SetAll("Enabled", .F., "Spinner" 	  	)
		THISFORM.SetAll("Enabled", .F., "Commandbutton" )
		THISFORM.SetAll("Enabled", .F., "Editbox"		)

		* Can't use SetAll on user-defined classes that aren't on the form
		THISFORM.SetAll("Enabled", .F., "Inputfield"	)

		* Buttons must be referred to as classes, since we don't have any control over the names
		THISFORM.SetAll("Enabled", .T., "cmdAdd"   )
		THISFORM.SetAll("Enabled", .T., "cmdEdit"  )
		THISFORM.SetAll("Enabled", .T., "cmdNext"  )
		THISFORM.SetAll("Enabled", .T., "cmdPrev"  )
		THISFORM.SetAll("Enabled", .T., "cmdDelete")
		THISFORM.SetAll("Enabled", .T., "cmdExit"  )
		THISFORM.SetAll("Enabled", .T., "cmdFind"  )

		THISFORM.SetAll("Enabled", .F., "cmdSave"  )
		THISFORM.SetAll("Enabled", .F., "cmdCancel")
	ENDPROC


ENDDEFINE
*
*-- EndDefine: cmdcancel
**************************************************
