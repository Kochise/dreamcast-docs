; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHttpSvrDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "httpsvr.h"
LastPage=0

ClassCount=10
Class1=CGenPage
Class2=CHttpSvrDoc
Class3=CHttpSvrApp
Class4=CAboutDlg
Class5=CHttpSvrView
Class6=CMainFrame
Class7=CBadRootDlg
Class8=CRootPage

ResourceCount=8
Resource1=IDD_BADROOT
Resource2=IDR_MAINFRAME
Resource3=IDM_POPUPS
Resource4=IDD_ABOUTBOX
Resource5=IDD_ROOTPAGE
Resource6=IDD_GENPAGE
Resource7=IDD_NAMEPAGE
Class9=CNamePage
Class10=CNoRootDlg
Resource8=IDD_NOROOT

[CLS:CGenPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=GenPage.h
ImplementationFile=GenPage.cpp
Filter=D
VirtualFilter=idWC
LastObject=CGenPage

[CLS:CHttpSvrDoc]
Type=0
BaseClass=CDocument
HeaderFile=HttpDoc.h
ImplementationFile=HttpDoc.cpp
Filter=N
VirtualFilter=DC
LastObject=ID_FILE_RESTART

[CLS:CHttpSvrApp]
Type=0
BaseClass=CWinApp
HeaderFile=HttpSvr.h
ImplementationFile=HttpSvr.cpp
LastObject=CHttpSvrApp
Filter=N
VirtualFilter=AC

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=HttpSvr.cpp
ImplementationFile=HttpSvr.cpp
LastObject=CAboutDlg

[CLS:CHttpSvrView]
Type=0
BaseClass=CListView
HeaderFile=HttpView.h
ImplementationFile=HttpView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CBadRootDlg]
Type=0
BaseClass=CDialog
HeaderFile=RootDlg.h
ImplementationFile=RootDlg.cpp

[CLS:CRootPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=RootPage.h
ImplementationFile=RootPage.cpp
Filter=D
VirtualFilter=idWC
LastObject=CRootPage

[DLG:IDD_GENPAGE]
Type=1
Class=CGenPage
ControlCount=4
Control1=IDC_STATIC,button,1342177287
Control2=IDC_ALLOWLIST,button,1342242819
Control3=IDC_LISTICONS,button,1342242819
Control4=IDC_LOGGINGON,button,1342242819

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_ROOTPAGE]
Type=1
Class=CRootPage
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_ROOTDIR,edit,1350631552
Control3=IDC_RESET,button,1342242816

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_RESTART
Command6=IDM_SVR_OPTIONS
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=ID_VIEW_STATUS_BAR
Command10=IDM_VIEW_LARGE
Command11=IDM_VIEW_SMALL
Command12=IDM_VIEW_LIST
Command13=IDM_VIEW_REPORT
Command14=IDM_VIEW_CLEAR
Command15=ID_APP_ABOUT
CommandCount=15

[MNU:IDM_POPUPS]
Type=1
Class=?
Command1=IDM_POPUP_OPEN
Command2=IDM_POPUP_EDIT
Command3=IDM_POPUP_CLEAR
Command4=IDM_POPUP_CLEAR
Command5=IDM_POPUP_CLEAR
CommandCount=5

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_NEXT_PANE
Command2=ID_PREV_PANE
CommandCount=2

[DLG:IDD_NAMEPAGE]
Type=1
Class=CNamePage
ControlCount=5
Control1=IDC_DEFNAME,button,1342308361
Control2=IDC_USENAME,button,1342177289
Control3=IDC_SVRNAME,edit,1350762624
Control4=IDC_STATIC,static,1342308354
Control5=IDC_PORT,edit,1350639744

[CLS:CNamePage]
Type=0
HeaderFile=NamePage.h
ImplementationFile=NamePage.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CNamePage

[DLG:IDD_NOROOT]
Type=1
Class=CNoRootDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308353
Control2=IDC_ROOTDIR,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[CLS:CNoRootDlg]
Type=0
HeaderFile=NoRoot.h
ImplementationFile=NoRoot.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CNoRootDlg

[DLG:IDD_BADROOT]
Type=1
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ROOTDIR,edit,1350631552
Control4=IDC_STATIC,static,1342308353

