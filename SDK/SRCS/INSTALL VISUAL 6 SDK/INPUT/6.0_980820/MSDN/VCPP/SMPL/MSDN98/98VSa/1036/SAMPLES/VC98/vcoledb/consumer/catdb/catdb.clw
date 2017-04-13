; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "catdb.h"
LastPage=0

ClassCount=8
Class1=CCatDBApp
Class2=CAboutDlg
Class3=CCatDBDoc
Class4=CCatDBView
Class5=CColumnPage
Class6=CEnumSourcesDlg
Class7=CMainFrame
Class8=CTablePage

ResourceCount=5
Resource1=IDD_TABLEPAGE
Resource2=IDD_COLUMNPAGE
Resource3=IDD_ENUM_SOURCES
Resource4=IDD_ABOUTBOX
Resource5=IDR_MAINFRAME

[CLS:CCatDBApp]
Type=0
BaseClass=CWinApp
HeaderFile=CatDB.h
ImplementationFile=CatDB.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=CatDB.cpp
ImplementationFile=CatDB.cpp
LastObject=IDOK

[CLS:CCatDBDoc]
Type=0
BaseClass=CDocument
HeaderFile=CatDBDoc.h
ImplementationFile=CatDBDoc.cpp

[CLS:CCatDBView]
Type=0
BaseClass=CListView
HeaderFile=CatDBvw.h
ImplementationFile=CatDBvw.cpp

[CLS:CColumnPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=COLPAGE.H
ImplementationFile=COLPAGE.CPP

[CLS:CEnumSourcesDlg]
Type=0
BaseClass=CDialog
HeaderFile=EnumDlg.h
ImplementationFile=EnumDlg.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MAINFRM.H
ImplementationFile=MAINFRM.CPP

[CLS:CTablePage]
Type=0
BaseClass=CPropertyPage
HeaderFile=TABLEPAG.H
ImplementationFile=TABLEPAG.CPP

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_COLUMNPAGE]
Type=1
Class=CColumnPage
ControlCount=3
Control1=IDC_LENGTH,button,1342242819
Control2=IDC_PRECISION,button,1342242819
Control3=IDC_NULLABILITY,button,1342242819

[DLG:IDD_ENUM_SOURCES]
Type=1
Class=CEnumSourcesDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TREE_ENUM,SysTreeView32,1350631462
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_USER,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_PASSWORD,edit,1350631584

[DLG:IDD_TABLEPAGE]
Type=1
Class=CTablePage
ControlCount=3
Control1=IDC_SYSTABLES,button,1342242819
Control2=IDC_ALIAI,button,1342242819
Control3=IDC_VIEWS,button,1342242819

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

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_VIEW_TABLES
Command3=ID_APP_ABOUT
CommandCount=3

