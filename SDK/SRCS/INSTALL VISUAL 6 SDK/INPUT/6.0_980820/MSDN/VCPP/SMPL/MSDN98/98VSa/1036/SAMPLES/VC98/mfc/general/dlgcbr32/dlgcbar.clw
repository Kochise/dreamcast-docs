; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CModelessMain
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dlgcbar.h"
LastPage=0

ClassCount=8
Class1=CAboutDlg
Class2=CDlgToolBar
Class3=CDlgStatusBar
Class4=CTheApp
Class5=CModelessMain
Class6=CModelessDialog
Class7=CRateDlg
Class8=CWndListDlg

ResourceCount=3
Resource1=IDD_RATE
Resource2=IDD_ABOUT
Resource3=IDR_MAIN

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Aboutdlg.h
ImplementationFile=Aboutdlg.cpp
LastObject=CAboutDlg

[CLS:CDlgToolBar]
Type=0
BaseClass=CToolBar
HeaderFile=Dlgbars.h
ImplementationFile=Dlgbars.cpp
LastObject=CDlgToolBar

[CLS:CDlgStatusBar]
Type=0
BaseClass=CStatusBar
HeaderFile=Dlgbars.h
ImplementationFile=Dlgbars.cpp
LastObject=CDlgStatusBar

[CLS:CTheApp]
Type=0
BaseClass=CWinApp
HeaderFile=Dlgcbar.h
ImplementationFile=Dlgcbar.cpp
LastObject=CTheApp

[CLS:CModelessMain]
Type=0
BaseClass=CModelessDialog
HeaderFile=Mdlsmain.h
ImplementationFile=Mdlsmain.cpp
LastObject=CModelessMain

[CLS:CModelessDialog]
Type=0
BaseClass=CDialog
HeaderFile=Modeless.h
ImplementationFile=Modeless.cpp
LastObject=CModelessDialog

[CLS:CRateDlg]
Type=0
BaseClass=CDialog
HeaderFile=Ratedlg.h
ImplementationFile=Ratedlg.cpp
LastObject=CRateDlg

[CLS:CWndListDlg]
Type=0
BaseClass=CModelessMain
HeaderFile=Wndlist.h
ImplementationFile=Wndlist.cpp
LastObject=CWndListDlg

[DLG:IDD_ABOUT]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDR_MAIN,static,1342177283
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_RATE]
Type=1
Class=CRateDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_INTERVAL,edit,1350631424
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[DLG:IDR_MAIN]
Type=1
Class=CWndListDlg
ControlCount=12
Control1=IDC_WNDLIST,listbox,1352728963
Control2=IDC_STATIC,static,1342308352
Control3=IDC_CLASS,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_MODULE,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_PARENT,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_RECT,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STYLE,static,1342308352
Control12=IDC_STATIC,static,1342308352

[MNU:IDR_MAIN]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_OPTION_NOW
Command3=ID_OPTION_RATE
Command4=ID_VIEW_STATUS_BAR
Command5=ID_VIEW_TOOLBAR
Command6=ID_HELP_ABOUT
CommandCount=6

[TB:IDR_MAIN]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_OPTION_NOW
Command3=ID_OPTION_RATE
Command4=ID_HELP_ABOUT
CommandCount=4

