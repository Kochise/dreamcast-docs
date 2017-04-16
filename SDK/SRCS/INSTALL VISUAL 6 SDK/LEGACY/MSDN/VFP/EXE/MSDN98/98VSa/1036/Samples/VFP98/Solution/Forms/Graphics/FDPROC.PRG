* FDPROC.PRG
* Procedure File for FoxDraw Graphics Methods Demo
* Defines: ToolBar 'fdToolBar'
* Procs  : Hide & Show ToolBars, FdMainErr

* Toolbar Object captions and tooltips
#INCLUDE "foxdraw.h"

* FDMAIN Class definitions & procedures

* FDToolBar Class Def
DEFINE CLASS fdToolBar  AS ToolBar

iLastDockWidth = 0

ADD OBJECT lbl1		AS LABEL WITH ;
	Caption = LBL1CAP_LOC, ;
	AutoSize = .T., ;
	BackStyle = 0, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

* Following object Caption changes when clicked
ADD OBJECT cmdDraw	AS commandbutton WITH ;
	HEIGHT = CMDHT_LOC,;
	WIDTH = CMDWIDTH1_LOC, ;
	Caption = CMDDRAWCAP2_LOC, ;
	ToolTipText = CMDDRAWTIP_LOC, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

ADD OBJECT sepL2	    AS SEPARATOR

ADD OBJECT lbl2		AS LABEL WITH ;
	Caption = LBL2CAP_LOC, ;
	AutoSize = .T., ;
	BackStyle = 0, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

* Following object Caption changes when clicked
ADD OBJECT cmdDrawMode	AS commandbutton WITH ;
	HEIGHT = CMDHT_LOC,;
	WIDTH = CMDWIDTH1_LOC, ;
	Caption = CMDDRAWMODECAP1_LOC, ;
	ToolTipText = CMDDRAWMODETIP_LOC, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

ADD OBJECT sepD2	    AS SEPARATOR

ADD OBJECT lbl3 	AS LABEL WITH ;
	Caption = LBL3CAP_LOC, ;
	AutoSize = .T.,;
	BackStyle = 0, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

ADD OBJECT spnPenWidth AS SPINNER WITH ;
	VALUE = 1, ;
	SpinnerLowValue = 1, ;
	SpinnerHighValue = 99, ;
	InputMask = "99", ;
	WIDTH = CMDWIDTH1_LOC, ;
	HEIGHT = CMDHT_LOC,;
	ToolTipText = SPNPENWIDTHTIP_LOC, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

ADD OBJECT sepS		AS SEPARATOR

ADD OBJECT lbl4 	AS LABEL WITH ;
	Caption = LBL4CAP_LOC,;
	AutoSize = .T., ;
	BackStyle = 0, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

ADD OBJECT cboPenMode	AS combobox WITH ;
	VALUE = 13, ;
	STYLE = 2, ;
	WIDTH = CMDWIDTH2_LOC, ;
	ToolTipText = CBOPENMODETIP_LOC, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

ADD OBJECT sepC1	AS SEPARATOR

ADD OBJECT cmdRed	AS commandbutton WITH ;
	HEIGHT = CMDHT_LOC, ;
	WIDTH = CMDWIDTH2_LOC, ;
	Caption = CMDREDCAP_LOC, ;
	ForeColor = RGB(255,0,0), ;
	ToolTipText = CMDREDTIP_LOC, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

ADD OBJECT cmdGreen	AS commandbutton WITH ;
	HEIGHT = CMDHT_LOC, ;
	WIDTH = CMDWIDTH2_LOC, ;
	Caption = CMDGREENCAP_LOC, ;
	ForeColor = RGB(0,255,0), ;
	ToolTipText = CMDGREENTIP_LOC, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

ADD OBJECT cmdBlue  AS commandbutton WITH ;
	HEIGHT = CMDHT_LOC,;
	WIDTH = CMDWIDTH2_LOC,;
	Caption = CMDBLUECAP_LOC, ;
	ForeColor = RGB(0,0,255),;
	ToolTipText = CMDBLUETIP_LOC, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

ADD OBJECT cmdCustom	AS commandbutton WITH;
	HEIGHT = CMDHT_LOC, ;
	WIDTH = CMDWIDTH2_LOC, ;
	Caption = CMDCUSTOMCAP_LOC, ;
	ForeColor = 16711935, ;
	ToolTipText = CMDCUSTOMTIP_LOC, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

ADD OBJECT cmdErase	AS commandbutton WITH ;
	HEIGHT = CMDHT_LOC, ;
	WIDTH = CMDWIDTH2_LOC, ;
	Caption = CMDERASECAP_LOC, ;
	ForeColor = RGB(255,255,255), ;
	ToolTipText = CMDERASETIP_LOC, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

ADD OBJECT cmdClear	AS commandbutton WITH ;
	HEIGHT = CMDHT_LOC,;
	WIDTH = CMDWIDTH2_LOC, ;
	Caption = CMDCLEARCAP_LOC, ;
	ToolTipText = CMDCLEARTIP_LOC, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

ADD OBJECT sepClr1   AS SEPARATOR

ADD OBJECT lbl5 	AS LABEL WITH ;
	Caption = LBL5CAP_LOC, ;
	AutoSize = .T., ;
	BackStyle = 0, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

ADD OBJECT cboGDemo	AS combobox WITH ;
	VALUE = 1, ;
	STYLE = 2, ;
	WIDTH = CMDWIDTH2_LOC, ;
	ToolTipText = CBOGDEMOTIP_LOC, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

ADD OBJECT sepCG1	AS SEPARATOR

ADD OBJECT cmdDone	AS commandbutton WITH ;
	HEIGHT = CMDHT_LOC, ;
	WIDTH = CMDWIDTH2_LOC, ;
	Caption = CMDDONECAP_LOC, ;
	ToolTipText = CMDDONETIP_LOC, ;
	FontName = CMDFONTNAME, ;
	FontSize = CMDFONTSIZE

PROCEDURE Init
	*- Setup and Dock ToolBar
	THIS.Dock(1)
	THIS.ScaleMode = 3
	THIS.Caption = TBRCAP_LOC
	THIS.ControlBox = .F.
	THIS.SetAll('FontSize',8)
	THIS.Visible = .T.
	PUSH KEY
	ON KEY LABEL CTRL+D _SCREEN.ActiveForm.Parent.Release
ENDPROC

PROCEDURE BeforeDock
	parameters iLocation
	IF THIS.DockPosition = -1
		THIS.Width = THIS.iLastDockWidth
	ENDIF
ENDPROC

PROCEDURE AfterDock
  PARAMETERS iIndex
	IF THIS.DockPosition = 3 OR THIS.DockPosition = 0
		??chr(7)
		THIS.Dock(-1)
	ENDIF
ENDPROC

PROCEDURE Undock
	parameters iIndex
	THIS.WIDTH = 130
ENDPROC

PROCEDURE Destroy
	LOCAL lcProcToClose, lcErrorSave
	THIS.Visible = .F.
	THISFORMSET.frmFD.Visible = .F.
	WAIT WINDOW WUNLOAD_LOC NOWAIT NOCLEAR
	RELEASE frmFD, fdmain
	WAIT CLEAR
	RELEASE CLASSLIB foxdraw
	IF TYPE('Main') = "O" AND NOT ISNULL(Main)
		Main.Show
	ELSE
		IF WEXIST('main')
			ACTI WIND main
		ENDIF
	ENDIF
	ON KEY LABEL CTRL+D
	POP KEY
ENDPROC

PROCEDURE cmdDraw.Click
	THISFORMSET.frmFD.DrawAction (THISFORMSET.frmFD.MousePointer)
	IF THISFORMSET.frmFD.MousePointer = 1
		THIS.Caption = CMDDRAWCAP1_LOC
	ELSE
		THIS.Caption = CMDDRAWCAP2_LOC
	ENDIF
ENDPROC

PROCEDURE cmdDrawMode.Click
	THISFORMSET.frmFD.ChgDrawMode
	IF THISFORMSET.frmFD.nDrawMode = 1
		THIS.Caption = CMDDRAWMODECAP1_LOC
	ELSE
		THIS.Caption = CMDDRAWMODECAP2_LOC
	ENDIF
ENDPROC

PROCEDURE spnPenWidth.InteractiveChange
	THISFORMSET.frmFD.SetPenWidth ( THIS.value )
	THISFORMSET.frmFD.SetCaption
ENDPROC

PROCEDURE cboPenMode.InteractiveChange
	THISFORMSET.frmFD.SetDrawMode ( THIS.value )
ENDPROC

PROCEDURE cboGDemo.Click
	THISFORMSET.frmFD.GraphDemo ( THIS.value )
ENDPROC

PROCEDURE cmdRed.CLICK
	THISFORMSET.frmFD.DrawColor ( RGB(255,0,0), THIS.caption )
ENDPROC

PROCEDURE cmdGreen.CLICK
	THISFORMSET.frmFD.DrawColor ( RGB(0,255,0), THIS.caption )
ENDPROC

PROCEDURE cmdBlue.CLICK
	THISFORMSET.frmFD.DrawColor ( RGB(0,0,255),THIS.caption )
ENDPROC

PROCEDURE cmdCustom.CLICK
	LOCAL lnColor
	lnColor = GETCOLOR()
	THISFORMSET.frmFD.DrawColor ( lnColor, THIS.caption )
	THIS.forecolor = lnColor
ENDPROC

PROCEDURE cmdErase.CLICK
	THISFORMSET.frmFD.DrawColor ( RGB(255,255,255), THIS.caption )
ENDPROC

PROCEDURE cmdClear.CLICK
	THISFORMSET.frmFD.ClearForm
ENDPROC

PROCEDURE cmdDone.Click
	_SCREEN.ActiveForm.Hide
	RELEASE THISFORMSET
ENDPROC

PROCEDURE cboPenMode.Init
	THIS.AddItem ( CBOPENMODE1_LOC,1)
	THIS.AddItem ( CBOPENMODE2_LOC,2 )
	THIS.AddItem ( CBOPENMODE3_LOC,3 )
	THIS.AddItem ( CBOPENMODE4_LOC,4 )
	THIS.AddItem ( CBOPENMODE5_LOC,5 )
	THIS.AddItem ( CBOPENMODE6_LOC,6 )
	THIS.AddItem ( CBOPENMODE7_LOC,7 )
	THIS.AddItem ( CBOPENMODE8_LOC,8 )
	THIS.AddItem ( CBOPENMODE9_LOC,9 )
	THIS.AddItem ( CBOPENMODE10_LOC,10 )
	THIS.AddItem ( CBOPENMODE11_LOC,11 )
	THIS.AddItem ( CBOPENMODE12_LOC,12 )
	THIS.AddItem ( CBOPENMODE13_LOC,13 )
	THIS.AddItem ( CBOPENMODE14_LOC,14 )
	THIS.AddItem ( CBOPENMODE15_LOC,15 )
	THIS.AddItem ( CBOPENMODE16_LOC,16 )
ENDPROC

PROCEDURE cboGDemo.Init
	THIS.AddItem ( CBOGDEMOITEM1_LOC,1 )
	THIS.AddItem ( CBOGDEMOITEM2_LOC,2 )
	THIS.AddItem ( CBOGDEMOITEM3_LOC,3 )
	THIS.AddItem ( CBOGDEMOITEM4_LOC,4 )
	THIS.AddItem ( CBOGDEMOITEM5_LOC,5 )
	THIS.AddItem ( CBOGDEMOITEM6_LOC,6 )
	THIS.AddItem ( CBOGDEMOITEM7_LOC,7 )
	THIS.AddItem ( CBOGDEMOITEM8_LOC,8 )
ENDPROC

ENDDEFINE
** EOF FdProc.prg
