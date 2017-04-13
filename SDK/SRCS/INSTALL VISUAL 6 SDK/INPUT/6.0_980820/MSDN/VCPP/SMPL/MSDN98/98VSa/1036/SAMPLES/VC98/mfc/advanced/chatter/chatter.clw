; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSetupDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chatter.h"
LastPage=0

ClassCount=7
Class1=CChatDoc
Class2=CChatterApp
Class3=CAboutDlg
Class4=CChatView
Class5=CMainFrame
Class6=CSendView
Class7=CSetupDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_SETUP

[CLS:CChatDoc]
Type=0
BaseClass=CDocument
HeaderFile=chatdoc.h
ImplementationFile=chatdoc.cpp

[CLS:CChatterApp]
Type=0
BaseClass=CWinApp
HeaderFile=chatter.h
ImplementationFile=chatter.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=chatter.cpp
ImplementationFile=chatter.cpp
Filter=D
LastObject=CAboutDlg

[CLS:CChatView]
Type=0
BaseClass=CEditView
HeaderFile=chatvw.h
ImplementationFile=chatvw.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T

[CLS:CSendView]
Type=0
BaseClass=CEditView
HeaderFile=sendvw.h
ImplementationFile=sendvw.cpp

[CLS:CSetupDlg]
Type=0
BaseClass=CDialog
HeaderFile=setupdlg.h
ImplementationFile=setupdlg.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SETUP]
Type=1
Class=CSetupDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_HANDLE,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SERVER,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_CHANNEL,edit,1350631424
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_SAVE
Command3=ID_AUTOCHATTER
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_SAVE
Command3=ID_NEXT_PANE
Command4=ID_PREV_PANE
CommandCount=4

