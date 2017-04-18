; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "catalog.h"
LastPage=0

ClassCount=7
Class1=CCatalogDoc
Class2=CCatalogApp
Class3=CAboutDlg
Class4=CCatalogView
Class5=CColumns
Class6=CMainFrame
Class7=CTables

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_CATALOG_FORM

[CLS:CCatalogDoc]
Type=0
BaseClass=CDocument
HeaderFile=cataldoc.h
ImplementationFile=cataldoc.cpp

[CLS:CCatalogApp]
Type=0
BaseClass=CWinApp
HeaderFile=catalog.h
ImplementationFile=catalog.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=catalog.cpp
ImplementationFile=catalog.cpp

[CLS:CCatalogView]
Type=0
BaseClass=CRecordView
HeaderFile=catalvw.h
ImplementationFile=catalvw.cpp

[CLS:CColumns]
Type=0
HeaderFile=columnst.h
ImplementationFile=columnst.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp

[CLS:CTables]
Type=0
HeaderFile=tableset.h
ImplementationFile=tableset.cpp

[DB:CColumns]
DB=1

[DB:CTables]
DB=1

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CATALOG_FORM]
Type=1
Class=CCatalogView
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_NAME,edit,1350631552
Control6=IDC_OWNER,edit,1350631552
Control7=IDC_REMARK,edit,1350631552
Control8=IDC_TYPE,edit,1350631552
Control9=IDC_COLUMNS,listbox,1352728835
Control10=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Command1=ID_APP_EXIT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_RECORD_FIRST
Command7=ID_RECORD_PREV
Command8=ID_RECORD_NEXT
Command9=ID_RECORD_LAST
Command10=ID_VIEW_TOOLBAR
Command11=ID_VIEW_STATUS_BAR
Command12=ID_APP_ABOUT
CommandCount=12

[ACL:IDR_MAINFRAME]
Type=1
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
CommandCount=10

