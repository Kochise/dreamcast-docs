; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAllControlsSheet
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "cmnctrl1.h"
LastPage=0

ClassCount=10
Class1=CAnimateCtrlPage
Class2=CCmnCtrl1App
Class3=CDateTimePage
Class4=CMonthCalPage
Class5=CMyTreeCtrl
Class6=CAllControlsSheet
Class7=CStandardBar
Class8=CPaletteBar
Class9=CToolBarCtrlPage
Class10=CTreeCtrlPage

ResourceCount=6
Resource1=IDD_DATETIME
Resource2=IDD_TOOLBARCTRL
Resource3=IDD_MONTHCAL
Resource4=IDD_TREECTRL
Resource5=IDD_ANIMCTRL
Resource6=IDD_ABOUTBOX

[CLS:CAnimateCtrlPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=animctrl.h
ImplementationFile=animctrl.cpp

[CLS:CCmnCtrl1App]
Type=0
BaseClass=CWinApp
HeaderFile=CmnCtrl1.h
ImplementationFile=CmnCtrl1.cpp

[CLS:CDateTimePage]
Type=0
BaseClass=CPropertyPage
HeaderFile=DateTime.h
ImplementationFile=DateTime.cpp

[CLS:CMonthCalPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=MonthCal.h
ImplementationFile=MonthCal.cpp
LastObject=CMonthCalPage

[CLS:CMyTreeCtrl]
Type=0
BaseClass=CTreeCtrl
HeaderFile=mtreectl.h
ImplementationFile=mtreectl.cpp
LastObject=CMyTreeCtrl

[CLS:CAllControlsSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=propsht.h
ImplementationFile=propsht.cpp
LastObject=CAllControlsSheet
Filter=W
VirtualFilter=hWC

[CLS:CStandardBar]
Type=0
BaseClass=CToolBarCtrl
HeaderFile=toolbar1.h
ImplementationFile=toolbar1.cpp

[CLS:CPaletteBar]
Type=0
BaseClass=CToolBarCtrl
HeaderFile=toolbar2.h
ImplementationFile=toolbar2.cpp

[CLS:CToolBarCtrlPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=toolpage.h
ImplementationFile=toolpage.cpp

[CLS:CTreeCtrlPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=treecpg.h
ImplementationFile=treecpg.cpp
Filter=D
VirtualFilter=idWC
LastObject=CTreeCtrlPage

[DLG:IDD_ANIMCTRL]
Type=1
Class=CAnimateCtrlPage
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_BROWSE,button,1342242816
Control4=1032,button,1342308359
Control5=IDC_CENTER,button,1342373891
Control6=IDC_TRANSPARENT,button,1342242819
Control7=IDC_AUTOPLAY,button,1342242819
Control8=IDC_PLAY,button,1342242816
Control9=IDC_STOP,button,1342242816
Control10=IDC_ANIMFRAME,static,1342308352
Control11=IDC_ANIMSTATUS,static,1342308352
Control12=IDC_STATIC,button,1342177287

[DLG:IDD_DATETIME]
Type=1
Class=CDateTimePage
ControlCount=12
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,button,1342177287
Control4=IDC_CKUPDOWN,button,1342242819
Control5=IDC_CKSHOWNONE,button,1342242819
Control6=IDC_CKAPPCANPARSE,button,1342242819
Control7=IDC_CKTIMEFORMAT,button,1342177289
Control8=IDC_CKSHORTDATEFORMAT,button,1342177289
Control9=IDC_CKLONGDATEFORMAT,button,1342177289
Control10=IDC_LBNOTIFY,listbox,1352728833
Control11=IDC_STATIC,static,1342308352
Control12=IDC_DTFRAME,static,1342308352

[DLG:IDD_MONTHCAL]
Type=1
Class=CMonthCalPage
ControlCount=15
Control1=IDC_MCFRAME,static,1342308352
Control2=IDC_CKDAYSTATE,button,1342242819
Control3=IDC_CMULTISELECT,button,1342242819
Control4=IDC_CKNOTODAY,button,1342242819
Control5=IDC_CKNOTODAYCIRCLE,button,1342242819
Control6=IDC_CKWEEKNUMBERS,button,1342242819
Control7=IDC_STATIC,button,1342177287
Control8=IDC_NOTIFYLIST,listbox,1352728833
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDSELRANGE,edit,1484857472
Control14=IDC_STRSELECTION,static,1342308352
Control15=IDC_STRRANGE,static,1342308352

[DLG:IDD_TOOLBARCTRL]
Type=1
Class=CToolBarCtrlPage
ControlCount=15
Control1=IDC_ALTDRAG,button,1342373891
Control2=IDC_STATIC,button,1342177287
Control3=ID_TOOLBARSTYLE,static,1342308352
Control4=ID_BUTTONSTYLE,static,1342308352
Control5=ID_TBSTYLEBUTTON,static,1342308352
Control6=IDC_STATIC,button,1342177287
Control7=ID_TOOLBARSTYLE2,static,1342308352
Control8=ID_BUTTONSTYLE2,static,1342308352
Control9=ID_TBSTYLECHECKGROUP,static,1342308352
Control10=ID_CCSBOTTOM,static,1342308352
Control11=ID_CCSTOP,static,1342308352
Control12=ID_CCSADJUSTABLE,static,1342308352
Control13=ID_TBSTYLETOOLTIPS,static,1342308352
Control14=ID_TBSTYLEWRAPABLE,static,1342308352
Control15=ID_TBSTYLETOOLTIPS2,static,1342308352

[DLG:IDD_TREECTRL]
Type=1
Class=CTreeCtrlPage
ControlCount=9
Control1=IDC_TREEVIEW1,SysTreeView32,1342242816
Control2=IDC_TVEDITLABELS,button,1342242819
Control3=IDC_TVHASBUTTONS,button,1342242819
Control4=IDC_TVHASLINES,button,1342242819
Control5=IDC_TVLINESATROOT,button,1342242819
Control6=IDC_TVDISABLEDDRAGDROP,button,1342242819
Control7=IDC_TVSHOWSELALWAYS,button,1342242819
Control8=IDC_TREESTATUS,edit,1352730692
Control9=IDC_TVSSINGELEXPAND,button,1342242819

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

