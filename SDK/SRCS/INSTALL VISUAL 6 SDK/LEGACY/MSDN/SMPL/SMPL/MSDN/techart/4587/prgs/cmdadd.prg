**************************************************
*-- Class:        cmdadd (c:\pfl\pfl0895\classes\mylib.vcx)
*-- ParentClass:  commandbutton
*-- BaseClass:    commandbutton
*
DEFINE CLASS cmdadd AS commandbutton


	Height = 25
	Width = 40
	Picture = "..\bmps\wznew.bmp"
	Caption = ""
	ToolTipText = "Add a record"
	select = .T.
	Name = "cmdadd"


	PROCEDURE Click
		IF NOT EMPTY ( THISFORM.PrimaryTable )
		   SELECT    ( THISFORM.PrimaryTable )
		ENDIF
		THISFORM.Adding = .T.
		THISFORM.SaveRecord = RECNO()
		* Recycle deleted records
		LOCATE FOR DELETED()
		IF NOT FOUND()
		   APPEND BLANK
		ENDIF
		THISFORM.Refresh

		* Activate any base class objects and disable command buttons
		THISFORM.SetAll("Enabled", .T., "Combobox" 	  	)
		THISFORM.SetAll("Enabled", .T., "Spinner" 	  	)
		THISFORM.SetAll("Enabled", .T., "Commandbutton" )
		THISFORM.SetAll("Enabled", .T., "Editbox"		)

		* The only derived class that is expected on every form is InputField:
		THISFORM.SetAll("Enabled", .T., "Inputfield"	)

		* To add others, type the following into the edit button click event code window:
		*cmdEdit::Click
		*THISFORM.SetAll("Enabled", .T., "Classname"	)	&& Classname is case-sensitive
		*THISFORM.FirstField.SetFocus

		* Buttons must be referred to as classes, since we don't have any control over the names
		THISFORM.SetAll("Enabled", .F., "cmdAdd" 		)
		THISFORM.SetAll("Enabled", .F., "cmdEdit"		)
		THISFORM.SetAll("Enabled", .F., "cmdNext"		)
		THISFORM.SetAll("Enabled", .F., "cmdPrev" 		)
		THISFORM.SetAll("Enabled", .F., "cmdDelete"		)
		THISFORM.SetAll("Enabled", .F., "cmdExit" 		)
		THISFORM.SetAll("Enabled", .F., "cmdFind" 		)

		THISFORM.SetAll("Enabled", .T., "cmdSave" 		)
		THISFORM.SetAll("Enabled", .T., "cmdCancel"		)
	ENDPROC


ENDDEFINE
*
*-- EndDefine: cmdadd
**************************************************
