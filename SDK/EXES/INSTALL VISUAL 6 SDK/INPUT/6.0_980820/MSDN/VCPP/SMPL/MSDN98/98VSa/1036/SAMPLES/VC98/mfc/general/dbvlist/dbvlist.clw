; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dbvlist.h"
LastPage=0

ClassCount=7
Class1=CDBVListApp
Class2=CAboutDlg
Class3=CDBVListDoc
Class4=CDBVListSet
Class5=CDBVListView
Class6=CEmpView
Class7=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_DBVLIST_FORM

[CLS:CDBVListApp]
Type=0
BaseClass=CWinApp
HeaderFile=DBVList.h
ImplementationFile=DBVList.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=DBVList.cpp
ImplementationFile=DBVList.cpp
LastObject=CAboutDlg

[CLS:CDBVListDoc]
Type=0
BaseClass=CDocument
HeaderFile=DBVListDoc.h
ImplementationFile=DBVListDoc.cpp

[CLS:CDBVListSet]
Type=0
HeaderFile=DBVListSet.h
ImplementationFile=DBVListSet.cpp

[CLS:CDBVListView]
Type=0
BaseClass=CFormView
HeaderFile=DBVListView.h
ImplementationFile=DBVListView.cpp

[CLS:CEmpView]
Type=0
BaseClass=CListView
HeaderFile=EmpView.h
ImplementationFile=EmpView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[DB:CDBVListSet]
DB=1

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_DBVLIST_FORM]
Type=1
Class=CDBVListView
ControlCount=2
Control1=IDC_FETCH,button,1342242816
Control2=IDC_DIV,combobox,1344340226

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_APP_ABOUT
CommandCount=4

[MNU:IDR_MAINFRAME]
Type=1
Class=?
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
Command12=ID_WINDOW_SPLIT
Command13=ID_APP_ABOUT
CommandCount=13

[ACL:IDR_MAINFRAME]
Type=1
Class=?
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

