; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CResultsDlg
LastTemplate=CCmdTarget
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "VContain.h"
ODLFile=VContain.odl
LastPage=0

ClassCount=14
Class1=CVContainApp
Class2=CVContainDoc
Class3=CErrorLog
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_PRE_VERIFY
Class7=VCliSite
Class8=CCliSite
Class9=CAdvSink
Class10=CSpecInterfaceDlg
Resource4=IDD_SPECIFIC_INTERFACES
Class11=CResultsDlg
Class12=CPreVerifyDlg
Class6=CDataObject
Class13=CPropBag
Class14=CVContainView
Resource5=IDD_RESULTS

[CLS:CVContainApp]
Type=0
HeaderFile=VContain.h
ImplementationFile=VContain.cpp
Filter=N
LastObject=CVContainApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CVContainDoc]
Type=0
HeaderFile=VContainDoc.h
ImplementationFile=VContainDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CVContainDoc

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC



[CLS:CAboutDlg]
Type=0
HeaderFile=VContain.cpp
ImplementationFile=VContain.cpp
Filter=D
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_INSERT_CONTROL
Command2=ID_DELETECONTROL
Command3=ID_APP_EXIT
Command4=ID_VERIFY_CONTROL
Command5=ID_VERIFY_SPECIFIC
Command6=ID_VIEW_RESULTS
Command7=ID_VIEW_TOOLBAR
Command8=ID_VIEW_STATUS_BAR
Command9=ID_APP_ABOUT
CommandCount=9

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[CLS:CDataObject]
Type=0
HeaderFile=VCDatObj.h
ImplementationFile=VCDatObj.cpp
BaseClass=CCmdTarget
Filter=N
LastObject=CDataObject

[CLS:VCliSite]
Type=0
HeaderFile=VCliSite.h
ImplementationFile=VCliSite.cpp
BaseClass=CCmdTarget
Filter=N
LastObject=ID_APP_ABOUT

[CLS:CCliSite]
Type=0
HeaderFile=VCliSite.h
ImplementationFile=VCliSite.cpp
BaseClass=CCmdTarget
Filter=N
LastObject=CCliSite

[CLS:CAdvSink]
Type=0
HeaderFile=VCAdvSnk.h
ImplementationFile=VCAdvSnk.cpp
BaseClass=CCmdTarget
Filter=N
LastObject=CAdvSink

[DLG:IDD_RESULTS]
Type=1
Class=CResultsDlg
ControlCount=20
Control1=IDC_STATIC,button,1342177287
Control2=IDC_CHK_MANDATORY,button,1342242819
Control3=IDC_CHK_OPTIONAL,button,1342242819
Control4=IDC_CHK_SUCCESS,button,1342242819
Control5=IDC_CHK_FAIL,button,1342242819
Control6=IDC_CHK_NOT_VERIFIED,button,1342242819
Control7=IDC_LIST_RESULT_TEXT,listbox,1353777537
Control8=IDC_PRE_VERIFY,button,1342242816
Control9=IDC_SAVE_TO_FILE,button,1342242816
Control10=IDOK,button,1342242817
Control11=IDC_MAN_SUCCESS,edit,1342179328
Control12=IDC_MAN_FAILURES,edit,1342179328
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_OPT_SUCCESS,edit,1342179328
Control17=IDC_STATIC,static,1342308352
Control18=IDC_MAN_NOT_VERIFIED,edit,1342179328
Control19=IDC_STATIC,static,1342308352
Control20=IDC_OPT_NOT_VERIFIED,edit,1342179328

[DLG:IDD_SPECIFIC_INTERFACES]
Type=1
Class=CSpecInterfaceDlg
ControlCount=22
Control1=IDC_CONNINTERFACES,button,1342251011
Control2=IDC_DATAOBJECT,button,1342242819
Control3=IDC_DISPATCH,button,1342242819
Control4=IDC_EXTCONN,button,1342242819
Control5=IDC_OLECACHE,button,1342242819
Control6=IDC_OLECACHE2,button,1342242819
Control7=IDC_OLECACHECONTROL,button,1342242819
Control8=IDC_OLECONTROL,button,1342242819
Control9=IDC_OLEINPLACEACTIVEOBJECT,button,1342242819
Control10=IDC_OLEINPLACEOJBECT,button,1342242819
Control11=IDC_OLEOBJECT,button,1342242819
Control12=IDC_PROVIDECLASSINFO,button,1342242819
Control13=IDC_PERSISTSTORAGE,button,1342242819
Control14=IDC_PERSISTPROPBAG,button,1342242819
Control15=IDC_PERSISTSTREAM,button,1342242819
Control16=IDC_PERSISTSTREAMINIT,button,1342242819
Control17=IDC_RUNOBJECT,button,1342242819
Control18=IDC_SPECPROPPAGES,button,1342242819
Control19=IDC_VIEWOBJECT2,button,1342242819
Control20=IDOK,button,1342242817
Control21=IDCANCEL,button,1342242816
Control22=IDC_STATIC,static,1342308352

[CLS:CSpecInterfaceDlg]
Type=0
HeaderFile=SpIntDlg.h
ImplementationFile=SpIntDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSpecInterfaceDlg
VirtualFilter=dWC

[CLS:CResultsDlg]
Type=0
HeaderFile=ResltDlg.h
ImplementationFile=ResltDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST_RESULT_TEXT

[DLG:IDD_PRE_VERIFY]
Type=1
Class=CPreVerifyDlg
ControlCount=14
Control1=IDC_MNEMONICS_YES,button,1342242819
Control2=IDC_ACCELERATORS_YES,button,1342242819
Control3=IDC_PROP_SET_YES,button,1342242819
Control4=IDC_AMBIENT_YES,button,1342242819
Control5=IDC_LICENSING_YES,button,1073807363
Control6=IDC_UI_YES,button,1073807363
Control7=IDC_PROPSMETHODS_YES,button,1073807363
Control8=IDC_NOTIFICATIONS_YES,button,1073807363
Control9=IDC_PROP_PAGES_YES,button,1073807363
Control10=IDC_LINKS_YES,button,1073807363
Control11=IDOK,button,1342242817
Control12=IDCANCEL,button,1342242816
Control13=IDC_INTRO_PRE_VERIFY,static,1342308352
Control14=IDC_INTRO_RESULTS,static,1073872896

[CLS:CPreVerifyDlg]
Type=0
HeaderFile=PreVeDlg.h
ImplementationFile=PreVeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CPreVerifyDlg
VirtualFilter=dWC

[CLS:CPropBag]
Type=0
HeaderFile=VCPrpBag.h
ImplementationFile=VCPrpBag.cpp
BaseClass=CCmdTarget
Filter=N
LastObject=CPropBag

[CLS:CErrorLog]
Type=0
HeaderFile=VCErrLog.h
ImplementationFile=VCErrLog.cpp
BaseClass=CCmdTarget
Filter=N
LastObject=CErrorLog

[TB:IDR_MAINFRAME]
Type=1
Command1=ID_INSERT_CONTROL
Command2=ID_DELETECONTROL
Command3=ID_VERIFY_CONTROL
Command4=ID_VERIFY_SPECIFIC
Command5=ID_VIEW_RESULTS
CommandCount=5

[CLS:CVContainView]
Type=0
HeaderFile=vconview.h
ImplementationFile=vconview.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=ID_INSERT_CONTROL

