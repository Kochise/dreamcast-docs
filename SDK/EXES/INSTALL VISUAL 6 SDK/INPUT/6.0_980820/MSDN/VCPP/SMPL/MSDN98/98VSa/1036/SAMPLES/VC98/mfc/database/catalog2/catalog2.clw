; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "catalog2.h"
LastPage=0

ClassCount=8
Class1=CCatalog2Doc
Class2=CCatalog2View
Class3=CCatalog2App
Class4=CAboutDlg
Class5=CColumnPage
Class6=CMainFrame
Class7=CTableSettings
Class8=CTablePage

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_TABLEPAGE
Resource4=IDD_COLUMNPAGE

[CLS:CCatalog2Doc]
Type=0
BaseClass=CDocument
HeaderFile=cat2doc.h
ImplementationFile=cat2doc.cpp

[CLS:CCatalog2View]
Type=0
BaseClass=CListView
HeaderFile=cat2view.h
ImplementationFile=cat2view.cpp

[CLS:CCatalog2App]
Type=0
BaseClass=CWinApp
HeaderFile=catalog2.h
ImplementationFile=catalog2.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=catalog2.cpp
ImplementationFile=catalog2.cpp
LastObject=CAboutDlg

[CLS:CColumnPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=colpage.h
ImplementationFile=colpage.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp

[CLS:CTableSettings]
Type=0
BaseClass=CPropertyPage
HeaderFile=settings.h
ImplementationFile=settings.cpp

[CLS:CTablePage]
Type=0
BaseClass=CPropertyPage
HeaderFile=tabpage.h
ImplementationFile=tabpage.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_COLUMNPAGE]
Type=1
Class=CColumnPage
ControlCount=3
Control1=IDC_LENGTH,button,1342242819
Control2=IDC_PRECISION,button,1342242819
Control3=IDC_NULLABILITY,button,1342242819

[DLG:IDD_TABLEPAGE]
Type=1
Class=CTableSettings
ControlCount=3
Control1=IDC_SYSTABLES,button,1342242819
Control2=IDC_ALIAI,button,1342242819
Control3=IDC_VIEWS,button,1342242819

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_VIEW_TABLES
Command3=ID_APP_ABOUT
CommandCount=3

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_APP_EXIT
Command3=ID_VIEW_TABLES
Command4=ID_VIEW_COLUMNINFO
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_VIEW_SETTINGS
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=?
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

