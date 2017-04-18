**************************************************
*-- Class:        standardscreen (c:\pfl\pfl0895\classes\mylib.vcx)
*-- ParentClass:  form
*-- BaseClass:    form
*
DEFINE CLASS standardscreen AS form


	Top = 6
	Left = -6
	Height = 418
	Width = 630
	DoCreate = .T.
	ShowTips = .T.
	BackColor = RGB(192,192,192)
	Caption = "Form"
	Closable = .F.
	WindowState = 0
	primarytable = ""
	saverecord = 0
	searchkey = ""
	Name = "standardscreen"
	adding = .F.
	savealias = .F.

	*-- list of fields for the Find button to be used in the Browse command
	browsefields = .F.


	ADD OBJECT box3d1 AS box3d WITH ;
		Height = 36, ;
		Left = 4, ;
		Top = 3, ;
		Width = 279, ;
		Name = "Box3d1"


	ADD OBJECT cmdadd1 AS cmdadd WITH ;
		Top = 6, ;
		Left = 68, ;
		Height = 29, ;
		Width = 30, ;
		TabIndex = 3, ;
		Name = "Cmdadd1"


	ADD OBJECT cmdedit2 AS cmdedit WITH ;
		Top = 6, ;
		Left = 98, ;
		Height = 29, ;
		Width = 30, ;
		TabIndex = 4, ;
		Name = "Cmdedit2"


	ADD OBJECT cmdfind3 AS cmdfind WITH ;
		Top = 6, ;
		Left = 128, ;
		Height = 29, ;
		Width = 30, ;
		TabIndex = 5, ;
		Name = "Cmdfind3"


	ADD OBJECT cmddelete4 AS cmddelete WITH ;
		Top = 6, ;
		Left = 158, ;
		Height = 29, ;
		Width = 30, ;
		TabIndex = 6, ;
		Name = "Cmddelete4"


	ADD OBJECT cmdsave5 AS cmdsave WITH ;
		Top = 6, ;
		Left = 188, ;
		Height = 29, ;
		Width = 30, ;
		TabIndex = 7, ;
		Name = "Cmdsave5"


	ADD OBJECT cmdcancel6 AS cmdcancel WITH ;
		Top = 6, ;
		Left = 218, ;
		Height = 29, ;
		Width = 30, ;
		TabIndex = 8, ;
		Name = "Cmdcancel6"


	ADD OBJECT cmdexit7 AS cmdexit WITH ;
		Top = 6, ;
		Left = 248, ;
		Height = 29, ;
		Width = 30, ;
		Picture = "..\bmps\close.bmp", ;
		Caption = "", ;
		TabIndex = 9, ;
		Name = "Cmdexit7"


	ADD OBJECT cmdnext8 AS cmdnext WITH ;
		Top = 6, ;
		Left = 38, ;
		Height = 29, ;
		Width = 30, ;
		TabIndex = 2, ;
		Name = "Cmdnext8"


	ADD OBJECT cmdprev9 AS cmdprev WITH ;
		Top = 6, ;
		Left = 8, ;
		Height = 29, ;
		Width = 30, ;
		TabIndex = 1, ;
		Name = "Cmdprev9"


	PROCEDURE buttonson
		IF Granted("SCR"+UPPER(THISFORM.Name),"CREATE")
			THISFORM.cmdAdd1.Enabled     = .T.
		ELSE
			THISFORM.cmdAdd1.Enabled     = .F.
		ENDIF
		IF Granted("SCR"+UPPER(THISFORM.Name),"WRITE")
			THISFORM.cmdEdit2.Enabled    = .T.
		ELSE
			THISFORM.cmdEdit2.Enabled    = .F.
		ENDIF
		THISFORM.cmdFind3.Enabled    = .T.
		IF Granted("SCR"+UPPER(THISFORM.Name),"DELETE")
			THISFORM.cmdDelete4.Enabled  = .T.
		ELSE
			THISFORM.cmdDelete4.Enabled  = .F.
		ENDIF
		THISFORM.cmdSave5.Enabled    = .F.
		THISFORM.cmdCancel6.Enabled  = .F.
		THISFORM.cmdExit7.Enabled    = .T.
		THISFORM.cmdNext8.Enabled    = .T.
		THISFORM.cmdPrev9.Enabled    = .T.

		THISFORM.TestBofEof()
	ENDPROC


	PROCEDURE buttonsoff
		THISFORM.cmdAdd1.Enabled     = .F.
		THISFORM.cmdEdit2.Enabled    = .F.
		THISFORM.cmdFind3.Enabled    = .F.
		THISFORM.cmdDelete4.Enabled  = .F.
		THISFORM.cmdSave5.Enabled    = .F.
		THISFORM.cmdCancel6.Enabled  = .F.
		THISFORM.cmdExit7.Enabled    = .F.
		THISFORM.cmdNext8.Enabled    = .F.
		THISFORM.cmdPrev9.Enabled    = .F.

		THISFORM.TestBofEof()
	ENDPROC


	PROCEDURE testbofeof
		IF NOT EMPTY ( THISFORM.PrimaryTable )
		   SELECT    ( THISFORM.PrimaryTable )
		ENDIF

		IF ! EOF()
			SaveRec = RECNO()
			COUNT TO LocalCount FOR NOT DELETED()
		ELSE
			LocalCount = 0
		ENDIF

		IF LocalCount = 0
		   THISFORM.SetAll("Enabled", .F., "cmdNext" 	)
		   THISFORM.SetAll("Enabled", .F., "cmdPrev" 	)
		   THISFORM.SetAll("Enabled", .F., "cmdEdit" 	)
		   THISFORM.SetAll("Enabled", .F., "cmdDelete"	)
		   RETURN
		ENDIF

		GO ( SaveRec )
		THISFORM.SetAll   ("Enabled", .T., "cmdNext" 	)
		SKIP
		IF EOF()
		   THISFORM.SetAll("Enabled", .F., "cmdNext" 	)
		ENDIF
		GO ( SaveRec )
		THISFORM.SetAll   ("Enabled", .T., "cmdPrev" 	)
		SKIP -1
		IF BOF()
		   THISFORM.SetAll("Enabled", .F., "cmdPrev" 	)
		ENDIF
		GO ( SaveRec )
	ENDPROC


	PROCEDURE financialfields
		IF NOT Granted("OTHFINANCE","READ")
		   THISFORM.SetAll ( "Visible",  .F., "Financialfield" )
		ENDIF
		IF NOT Granted("OTHFINANCE","WRITE")
		   THISFORM.SetAll ( "Readonly", .T., "Financialfield" )
		ENDIF
	ENDPROC


	PROCEDURE showbutton
		THISFORM.cmdAdd1.Visible	= IIF(THISFORM.cmdAdd1.Select	 = .T., .T., .F.)
		THISFORM.cmdEdit2.Visible	= IIF(THISFORM.cmdEdit2.Select	 = .T., .T., .F.)
		THISFORM.cmdFind3.Visible	= IIF(THISFORM.cmdFind3.Select	 = .T., .T., .F.)
		THISFORM.cmdDelete4.Visible	= IIF(THISFORM.cmdDelete4.Select = .T., .T., .F.)
		THISFORM.cmdSave5.Visible	= IIF(THISFORM.cmdSave5.Select	 = .T., .T., .F.)
		THISFORM.cmdCancel6.Visible	= IIF(THISFORM.cmdCancel6.Select = .T., .T., .F.)
		THISFORM.cmdExit7.Visible	= IIF(THISFORM.cmdExit7.Select	 = .T., .T., .F.)
		THISFORM.cmdPrev9.Visible	= IIF(THISFORM.cmdPrev9.Select = .T., .T., .F.)
		THISFORM.cmdNext8.Visible	= IIF(THISFORM.cmdNext8.Select = .T., .T., .F.)

		I = 10
		IF THISFORM.cmdFind3.Select = .T.
			THISFORM.cmdFind1.Left = I
			I = I + THISFORM.CmdFind1.Width + 1
		ENDIF
		IF THISFORM.cmdPrev9.Select = .T.
			THISFORM.cmdPrev9.Left = I
			I = I + THISFORM.cmdPrev9.Width + 1
		ENDIF
		IF THISFORM.cmdNext8.Select = .T.
			THISFORM.cmdNext8.Left = I
			I = I + THISFORM.cmdNext8.Width + 1
		ENDIF
		IF THISFORM.cmdAdd1.Select = .T.
			THISFORM.cmdAdd1.Left = I
			I = I + THISFORM.cmdAdd1.Width + 1
		ENDIF
		IF THISFORM.cmdEdit2.Select = .T.
			THISFORM.cmdEdit2.Left = I
			I = I + THISFORM.cmdEdit2.Width + 1
		ENDIF
		IF THISFORM.cmdDelete4.Select = .T.
			THISFORM.cmdDelete4.Left = I
			I = I + THISFORM.cmdDelete4.Width + 1
		ENDIF
		IF THISFORM.cmdSave5.Select = .T.
			THISFORM.cmdSave5.Left = I
			I = I + THISFORM.cmdSave5.Width + 1
		ENDIF
		IF THISFORM.cmdCancel6.Select = .T.
			THISFORM.cmdCancel6.Left = I
			I = I + THISFORM.cmdCancel6.Width + 1
		ENDIF
		IF THISFORM.cmdPrev9.Select = .T.
			THISFORM.cmdPrev9.Left = I
			I = I + THISFORM.cmdPrev9.Width + 1
		ENDIF
		IF THISFORM.cmdNext8.Select = .T.
			THISFORM.cmdNext8.Left = I
			I = I + THISFORm.cmdNext8.Width + 1
		ENDIF
		IF THISFORM.cmdExit7.Select = .T.
			THISFORM.cmdExit7.Left = I
			I = I + THISFORM.cmdExit7.Width + 1
		ENDIF
		IF I>10
			THISFORM.Box3d1.Width = I + 2
		ELSE
			THISFORM.Box3d1.Visible = .F.
		ENDIF
	ENDPROC


	PROCEDURE Init
		THIS.AutoCenter = .T.
		THIS.ButtonsOn
	ENDPROC


ENDDEFINE
*
*-- EndDefine: standardscreen
**************************************************
