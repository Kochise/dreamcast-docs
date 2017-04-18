; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "enroll.h"
LastPage=0

ClassCount=7
Class1=CCourseSet
Class2=CEnrollDoc
Class3=CEnrollApp
Class4=CAboutDlg
Class5=CMainFrame
Class6=CSectionForm
Class7=CSectionSet

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_ENROLL_FORM

[CLS:CCourseSet]
Type=0
HeaderFile=coursset.h
ImplementationFile=coursset.cpp

[CLS:CEnrollDoc]
Type=0
BaseClass=CDocument
HeaderFile=enroldoc.h
ImplementationFile=enroldoc.cpp

[CLS:CEnrollApp]
Type=0
BaseClass=CWinApp
HeaderFile=enroll.h
ImplementationFile=enroll.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=enroll.cpp
ImplementationFile=enroll.cpp
Filter=D

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T

[CLS:CSectionForm]
Type=0
BaseClass=CRecordView
HeaderFile=sectform.h
ImplementationFile=sectform.cpp

[CLS:CSectionSet]
Type=0
HeaderFile=sectset.h
ImplementationFile=sectset.cpp

[DB:CCourseSet]
DB=1

[DB:CSectionSet]
DB=1

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ENROLL_FORM]
Type=1
Class=CSectionForm
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COURSELIST,combobox,1344340227
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SECTION,edit,1350633600
Control5=IDC_STATIC,static,1342308352
Control6=IDC_INSTRUCTOR,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_ROOM,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_SCHEDULE,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_CAPACITY,edit,1350631552

[TB:IDR_MAINFRAME]
Type=1
Command1=ID_EDIT_CUT
Command2=ID_EDIT_PASTE
Command3=ID_FILE_PRINT
Command4=ID_RECORD_FIRST
Command5=ID_RECORD_NEXT
Command6=ID_APP_ABOUT
CommandCount=6
Class=CMainFrame

[MNU:IDR_MAINFRAME]
Type=1
Command1=ID_FILE_PRINT
Command2=ID_FILE_PRINT_PREVIEW
Command3=ID_FILE_PRINT_SETUP
Command4=ID_APP_EXIT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_RECORD_ADD
Command10=ID_RECORD_REFRESH
Command11=ID_RECORD_DELETE
Command12=ID_RECORD_FIRST
Command13=ID_RECORD_PREV
Command14=ID_RECORD_NEXT
Command15=ID_RECORD_LAST
Command16=ID_VIEW_TOOLBAR
Command17=ID_VIEW_STATUS_BAR
Command18=ID_APP_ABOUT
CommandCount=18
Class=CMainFrame

[ACL:IDR_MAINFRAME]
Type=1
Command1=ID_EDIT_COPY
Command2=ID_FILE_PRINT
Command3=ID_EDIT_PASTE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_RECORD_REFRESH
Command7=ID_NEXT_PANE
Command8=ID_PREV_PANE
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_CUT
Command12=ID_EDIT_UNDO
CommandCount=12
Class=CMainFrame

