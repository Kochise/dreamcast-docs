**************************************************
*-- Class:        cmdsave (c:\pfl\pfl0895\classes\mylib.vcx)
*-- ParentClass:  commandbutton
*-- BaseClass:    commandbutton
*
DEFINE CLASS cmdsave AS commandbutton


	Height = 25
	Width = 40
	Picture = "..\bmps\wzsave.bmp"
	Caption = ""
	ToolTipText = "Save changes"
	select = .T.
	Name = "cmdsave"


	PROCEDURE Click
		IF NOT EMPTY ( THISFORM.PrimaryTable )
		   SELECT	 ( THISFORM.PrimaryTable )
		ENDIF

		=TableUpdate()

		THISFORM.Adding = .F.

		THISFORM.SetAll("Enabled", .F., "Combobox" 	  	)
		THISFORM.SetAll("Enabled", .F., "Spinner" 	  	)
		THISFORM.SetAll("Enabled", .F., "Commandbutton" )
		THISFORM.SetAll("Enabled", .F., "Editbox"		)

		* Derived classes assumed to exist in every form (otherwise, an error results)
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
		THISFORM.Refresh
	ENDPROC


ENDDEFINE
*
*-- EndDefine: cmdsave
**************************************************
