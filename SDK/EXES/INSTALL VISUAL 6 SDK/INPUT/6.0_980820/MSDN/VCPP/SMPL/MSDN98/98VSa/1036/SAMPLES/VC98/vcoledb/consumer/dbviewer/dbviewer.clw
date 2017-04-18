; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDBListView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dbviewer.h"
LastPage=0

ClassCount=18
Class1=CListCtrlEx
Class2=CTreeCtrlEx
Class3=CDBViewDoc
Class4=CDBListView
Class5=CDBTreeView
Class6=CDBViewApp
Class7=CAboutDlg
Class8=CDBViewView
Class9=CDlgParams
Class10=CDlgSQL
Class11=CEditDlg
Class12=CMainFrame
Class13=COptionsDlg
Class14=CRenameDlg
Class15=CUpdatesDlg

ResourceCount=11
Resource1=IDR_POPUP_QUERY
Resource2=IDD_EDIT_DIALOG
Resource3=IDR_POPUP_TABLE
Resource4=IDD_DLGUPDATES (English (U.K.))
Resource5=IDD_ABOUTBOX
Resource6=IDD_DLGOPTIONS
Resource7=IDD_DLGSQL
Resource8=IDD_DLGUPDATES (English (U.K.))
Resource9=IDD_ERRORS
Class16=CDlgProgress
Class17=CProgressDlg
Resource10=IDD_RENAME
Class18=CErrorsDialog
Resource11=IDR_MAINFRAME

[CLS:CListCtrlEx]
Type=0
BaseClass=CListCtrl
HeaderFile=ctrlext.h
ImplementationFile=ctrlext.cpp

[CLS:CTreeCtrlEx]
Type=0
BaseClass=CTreeCtrl
HeaderFile=ctrlext.h
ImplementationFile=ctrlext.cpp

[CLS:CDBViewDoc]
Type=0
BaseClass=CDocument
HeaderFile=DBDoc.h
ImplementationFile=DBDoc.cpp
LastObject=CDBViewDoc

[CLS:CDBListView]
Type=0
BaseClass=CListView
HeaderFile=DBListVw.h
ImplementationFile=dblistvw.cpp
LastObject=CDBListView
Filter=C
VirtualFilter=VWC

[CLS:CDBTreeView]
Type=0
BaseClass=CTreeView
HeaderFile=DBTreeVw.h
ImplementationFile=dbtreevw.cpp
LastObject=CDBTreeView

[CLS:CDBViewApp]
Type=0
BaseClass=CWinApp
HeaderFile=DBView.h
ImplementationFile=dbviewer.cpp
LastObject=CDBViewApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=dbviewer.cpp
ImplementationFile=dbviewer.cpp
LastObject=CAboutDlg

[CLS:CDBViewView]
Type=0
BaseClass=CTreeView
HeaderFile=dbviewvw.h
ImplementationFile=dbviewvw.cpp
LastObject=CDBViewView

[CLS:CDlgParams]
Type=0
BaseClass=CDialog
HeaderFile=dlgparam.h
ImplementationFile=dlgparam.cpp
LastObject=CDlgParams

[CLS:CDlgSQL]
Type=0
BaseClass=CDialog
HeaderFile=dlgsql.h
ImplementationFile=dlgsql.cpp
LastObject=ID_CALL_PROCEDURE

[CLS:CEditDlg]
Type=0
BaseClass=CDialog
HeaderFile=EditDlg.h
ImplementationFile=EditDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CEditDlg

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=mainfrm.cpp

[CLS:COptionsDlg]
Type=0
BaseClass=CPropertyPage
HeaderFile=optiondg.h
ImplementationFile=optiondg.cpp

[CLS:CRenameDlg]
Type=0
BaseClass=CDialog
HeaderFile=rendlg.h
ImplementationFile=rendlg.cpp

[CLS:CUpdatesDlg]
Type=0
BaseClass=CPropertyPage
HeaderFile=upddlg.h
ImplementationFile=upddlg.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DLGSQL]
Type=1
Class=CDlgSQL
ControlCount=4
Control1=IDC_EDITSQL,edit,1350635652
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_EDIT_DIALOG]
Type=1
Class=CEditDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_LIST1,listbox,1353777409
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2,edit,1350631552

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
Command8=ID_QUERY_EDIT
Command9=ID_VIEW_TOOLBAR
Command10=ID_VIEW_STATUS_BAR
Command11=ID_VIEW_OPTIONS
Command12=ID_APP_ABOUT
CommandCount=12

[MNU:IDR_POPUP_QUERY]
Type=1
Class=?
Command1=ID_QUERY_RUN
CommandCount=1

[MNU:IDR_POPUP_TABLE]
Type=1
Class=?
Command1=ID_TABLE_SCHEMA
Command2=ID_TABLE_DATA
Command3=ID_TABLE_INSERT
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

[DLG:IDD_DLGUPDATES (English (U.K.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_POSITON_UPATDE,button,1342242819

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_NEXT_RESULT
Command6=ID_APP_CLONE
Command7=ID_CALL_PROCEDURE
Command8=ID_APP_ABOUT
CommandCount=8

[CLS:CDlgProgress]
Type=0
HeaderFile=dlgprog.h
ImplementationFile=dlgprog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgProgress

[CLS:CProgressDlg]
Type=0
HeaderFile=ProgDlg.h
ImplementationFile=ProgDlg.cpp
BaseClass=CDialog

[DLG:IDD_ERRORS]
Type=1
Class=CErrorsDialog
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_LIST_SOURCE,listbox,1353777411
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_DESCRIPTION,edit,1350633540
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_GUID,edit,1350633600
Control7=IDOK,button,1342242817
Control8=IDHELP,button,1342242817

[CLS:CErrorsDialog]
Type=0
HeaderFile=ErrorDlg.h
ImplementationFile=ErrorDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_NEXT_RESULT

