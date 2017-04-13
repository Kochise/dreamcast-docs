; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDaoViewApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "daoview.h"
LastPage=0

ClassCount=10
Class1=CDaoViewApp
Class2=CAboutDlg
Class3=CDaoViewDoc
Class4=CDlgParams
Class5=CDlgSQL
Class6=CDaoListView
Class7=CMainFrame
Class8=COptionsDlg
Class9=CRenameDlg
Class10=CDaoTreeView

ResourceCount=8
Resource1=IDD_DLGPARAMS
Resource2=IDR_POPUP_QUERY
Resource3=IDR_POPUP_TABLE
Resource4=IDD_DLGOPTIONS
Resource5=IDD_ABOUTBOX
Resource6=IDD_DLGSQL
Resource7=IDD_RENAME
Resource8=IDR_MAINFRAME

[CLS:CDaoViewApp]
Type=0
HeaderFile=daoview.h
ImplementationFile=daoview.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=daoview.cpp
ImplementationFile=daoview.cpp
LastObject=CAboutDlg

[CLS:CDaoViewDoc]
Type=0
BaseClass=CDocument
HeaderFile=daovwdoc.h
ImplementationFile=daovwdoc.cpp

[CLS:CDlgParams]
Type=0
BaseClass=CDialog
HeaderFile=dlgparam.h
ImplementationFile=dlgparam.cpp

[CLS:CDlgSQL]
Type=0
BaseClass=CDialog
HeaderFile=dlgsql.h
ImplementationFile=dlgsql.cpp

[CLS:CDaoListView]
Type=0
BaseClass=CListView
HeaderFile=listview.h
ImplementationFile=listview.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp

[CLS:COptionsDlg]
Type=0
BaseClass=CPropertyPage
HeaderFile=optionsd.h
ImplementationFile=optionsd.cpp

[CLS:CRenameDlg]
Type=0
BaseClass=CDialog
HeaderFile=renamedl.h
ImplementationFile=renamedl.cpp

[CLS:CDaoTreeView]
Type=0
BaseClass=CTreeView
HeaderFile=treeview.h
ImplementationFile=treeview.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=9
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_VERSION,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1350701057

[DLG:IDD_DIALOG2]
Type=1
Class=CDlgParams

[DLG:IDD_DLGSQL]
Type=1
Class=CDlgSQL
ControlCount=6
Control1=IDC_EDITNAME,edit,1350631552
Control2=IDC_EDITSQL,edit,1350635652
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_DLGOPTIONS]
Type=1
Class=COptionsDlg
ControlCount=5
Control1=IDC_BSYSTEMOBJECTS,button,1342242819
Control2=IDC_BWARNINGS,button,1342242819
Control3=IDC_BOPENODBC,button,1476460547
Control4=IDC_STATIC,static,1342308352
Control5=IDC_MAXRECS,edit,1350631552

[DLG:IDD_RENAME]
Type=1
Class=CRenameDlg
ControlCount=6
Control1=IDC_ITEMNAME,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_NEWQUERY
Command9=ID_VIEW_TOOLBAR
Command10=ID_VIEW_STATUS_BAR
Command11=ID_VIEW_OPTIONS
Command12=ID_APP_ABOUT
CommandCount=12

[MNU:IDR_POPUP_TABLE]
Type=1
Class=?
Command1=ID_TABLE_SCHEMA
Command2=ID_TABLE_DATA
CommandCount=2

[MNU:IDR_POPUP_QUERY]
Type=1
Class=?
Command1=ID_QUERY_DEFINITION
Command2=ID_QUERY_RUN
Command3=ID_QUERY_EDIT
CommandCount=3

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

[DLG:IDD_DLGPARAMS]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_LISTVIEW1,SysListView32,1350631941

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_EDIT_CUT
Command3=ID_EDIT_PASTE
Command4=ID_APP_CLONE
CommandCount=4

