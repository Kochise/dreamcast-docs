; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "enroll.h"
VbxHeaderFile=enroll.h
VbxImplementationFile=enroll.cpp
LastPage=0

ClassCount=8
Class1=CCourseSet
Class2=CCourseForm
Class3=CEnrollDoc
Class4=CEnrollApp
Class5=CAboutDlg
Class6=CMainFrame
Class7=CSectionForm
Class8=CSectionSet

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_COURSE_FORM
Resource4=IDD_ENROLL_FORM

[CLS:CCourseSet]
Type=0
HeaderFile=coursset.h
ImplementationFile=coursset.cpp

[CLS:CCourseForm]
Type=0
HeaderFile=crsform.h
ImplementationFile=crsform.cpp

[CLS:CEnrollDoc]
Type=0
HeaderFile=enroldoc.h
ImplementationFile=enroldoc.cpp

[CLS:CEnrollApp]
Type=0
HeaderFile=enroll.h
ImplementationFile=enroll.cpp

[CLS:CAboutDlg]
Type=0
HeaderFile=enroll.cpp
ImplementationFile=enroll.cpp
Filter=D

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T

[CLS:CSectionForm]
Type=0
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

[DLG:IDD_COURSE_FORM]
Type=1
Class=CCourseForm
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COURSEID,edit,1350633600
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TITLE,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_HOURS,edit,1350631552

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
Class=?
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_SECTION,edit,1350633600
Control4=IDC_STATIC,static,1342308352
Control5=IDC_INSTRUCTOR,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ROOM,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_SCHEDULE,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_CAPACITY,edit,1350631552
Control12=IDC_COURSELIST,combobox,1344340227

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_PRINT
Command2=ID_FILE_PRINT_PREVIEW
Command3=ID_FILE_PRINT_SETUP
Command4=ID_APP_EXIT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_FORM_COURSES
Command10=ID_FORM_SECTIONS
Command11=ID_RECORD_ADD
Command12=ID_RECORD_REFRESH
Command13=ID_RECORD_DELETE
Command14=ID_RECORD_FIRST
Command15=ID_RECORD_PREV
Command16=ID_RECORD_NEXT
Command17=ID_RECORD_LAST
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_APP_ABOUT
CommandCount=20

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_PRINT
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_RECORD_REFRESH
Command6=ID_NEXT_PANE
Command7=ID_PREV_PANE
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_EDIT_CUT
Command11=ID_EDIT_UNDO
CommandCount=11

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

