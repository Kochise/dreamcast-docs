; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSnapPropertySheet
LastTemplate=CPropertySheet
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "snapvw.h"
LastPage=0

ClassCount=10
Class1=CChildFrame
Class2=CMainFrame
Class3=CSnapDoc
Class4=CSnapView
Class5=CSnapApp
Class6=CAboutDlg

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDD_DINNER
Resource3=IDR_MAINFRAME
Resource4=IDR_SNAPTYPE
Resource5=IDD_BREAKFAST
Class7=CBkfstPage
Class8=CLunchPage
Class9=CDinnerPage
Class10=CSnapPropertySheet
Resource6=IDD_LUNCH

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=childfrm.h
ImplementationFile=childfrm.cpp
LastObject=CChildFrame

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
LastObject=CMainFrame

[CLS:CSnapDoc]
Type=0
BaseClass=CDocument
HeaderFile=snapdoc.h
ImplementationFile=Snapdoc.cpp
LastObject=CSnapDoc

[CLS:CSnapView]
Type=0
BaseClass=CFormView
HeaderFile=snapview.h
ImplementationFile=snapview.cpp
LastObject=CSnapView
Filter=C
VirtualFilter=VWC

[CLS:CSnapApp]
Type=0
BaseClass=CWinApp
HeaderFile=snapvw.h
ImplementationFile=snapvw.cpp
LastObject=CSnapApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=snapvw.cpp
ImplementationFile=snapvw.cpp
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_APP_ABOUT
CommandCount=2

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_VIEW_TOOLBAR
Command4=ID_VIEW_STATUS_BAR
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_SNAPTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_APP_EXIT
Command4=ID_VIEW_TOOLBAR
Command5=ID_VIEW_STATUS_BAR
Command6=ID_WINDOW_NEW
Command7=ID_WINDOW_CASCADE
Command8=ID_WINDOW_TILE_HORZ
Command9=ID_APP_ABOUT
CommandCount=9

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_DINNER]
Type=1
Class=CDinnerPage
ControlCount=11
Control1=IDC_STATIC,button,1342177287
Control2=IDC_BEER,button,1342373897
Control3=IDC_COFFEE1,button,1342177289
Control4=IDC_MILK,button,1342177289
Control5=IDC_SODA,button,1342177289
Control6=IDC_STATIC,button,1342177287
Control7=IDC_GREASY2,button,1342373897
Control8=IDC_ROMANTIC,button,1342177289
Control9=IDC_STATIC,button,1342177287
Control10=IDC_NEIGHBOR,button,1342373891
Control11=IDC_TABLOID2,button,1342177283

[DLG:IDD_BREAKFAST]
Type=1
Class=CBkfstPage
ControlCount=13
Control1=IDC_STATIC,button,1342177287
Control2=IDC_HOT_TEA,button,1342373897
Control3=IDC_ORANGE_JUICE,button,1342177289
Control4=IDC_PRUNE_JUICE2,button,1342177289
Control5=IDC_COFFEE,button,1342177289
Control6=IDC_PRUNE_JUICE,button,1342177289
Control7=IDC_STATIC,button,1342177287
Control8=IDC_CONTINENTAL,button,1342373897
Control9=IDC_CONTINENTAL2,button,1342177289
Control10=IDC_AMERICAN,button,1342177289
Control11=IDC_STATIC,button,1342177287
Control12=IDC_FINANCE,button,1342373891
Control13=IDC_HOCKEY,button,1342177283

[DLG:IDD_LUNCH]
Type=1
Class=CLunchPage
ControlCount=9
Control1=IDC_STATIC,button,1342177287
Control2=IDC_SODA,button,1342373897
Control3=IDC_MILK,button,1342177289
Control4=IDC_STATIC,button,1342177287
Control5=IDC_GREASY,button,1342373897
Control6=IDC_HEALTHY,button,1342177289
Control7=IDC_STATIC,button,1342177287
Control8=IDC_NERDY,button,1342373891
Control9=IDC_TABLOID,button,1342177283

[CLS:CBkfstPage]
Type=0
HeaderFile=BkfstPg.h
ImplementationFile=BkfstPg.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CBkfstPage
VirtualFilter=idWC

[CLS:CLunchPage]
Type=0
HeaderFile=LunchPg.h
ImplementationFile=LunchPg.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CLunchPage
VirtualFilter=idWC

[CLS:CDinnerPage]
Type=0
HeaderFile=DinnerPg.h
ImplementationFile=DinnerPg.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CDinnerPage
VirtualFilter=idWC

[CLS:CSnapPropertySheet]
Type=0
HeaderFile=SnapPs.h
ImplementationFile=SnapPs.cpp
BaseClass=CPropertySheet
Filter=W
VirtualFilter=hWC
LastObject=CSnapPropertySheet

