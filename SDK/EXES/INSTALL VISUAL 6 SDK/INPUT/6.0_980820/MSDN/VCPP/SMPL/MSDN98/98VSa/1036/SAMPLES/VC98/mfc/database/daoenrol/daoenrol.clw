; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCourseSet
LastTemplate=CDaoRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DaoEnrol.h"
LastPage=0

ClassCount=7
Class1=CDaoEnrolApp
Class2=CDaoEnrolDoc
Class3=CSectionForm
Class4=CMainFrame
Class6=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CsectionSet
Resource3=IDD_DAOENROL_FORM
Class7=CCourseSet
Resource4=IDD_COURSE_FORM

[CLS:CDaoEnrolApp]
Type=0
HeaderFile=DaoEnrol.h
ImplementationFile=DaoEnrol.cpp
Filter=N

[CLS:CDaoEnrolDoc]
Type=0
HeaderFile=denrldoc.h
ImplementationFile=denrldoc.cpp
Filter=N

[CLS:CSectionForm]
Type=0
HeaderFile=sectform.h
ImplementationFile=sectform.cpp
Filter=D
BaseClass=CDaoRecordView
VirtualFilter=XVWC
LastObject=CSectionForm

[CLS:CsectionSet]
Type=0
HeaderFile=sectset.h
ImplementationFile=sectset.cpp
Filter=N

[DB:CsectionSet]
DB=1
DBType=DAO
ColumnCount=6
Column1=[CourseID], 12, 8
Column2=[SectionNo], 12, 4
Column3=[InstructorID], 12, 8
Column4=[RoomNo], 12, 10
Column5=[Schedule], 12, 24
Column6=[Capacity], 5, 2


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=DaoEnrol.cpp
ImplementationFile=DaoEnrol.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

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
Command11=ID_RECORD_FIRST
Command12=ID_RECORD_PREV
Command13=ID_RECORD_NEXT
Command14=ID_RECORD_LAST
Command15=ID_RECORD_ADD
Command16=ID_RECORD_REFRESH
Command17=ID_RECORD_DELETE
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_APP_ABOUT
CommandCount=20

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
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

[DLG:IDD_DAOENROL_FORM]
Type=1
Class=CSectionForm
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COURSELIST,combobox,1344340227
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SECTION,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_INSTRUCTOR,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_ROOM,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_SCHEDULE,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_CAPACITY,edit,1350631552

[CLS:CCourseSet]
Type=0
HeaderFile=coursese.h
ImplementationFile=coursese.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x
LastObject=CCourseSet

[DB:CCourseSet]
DB=1
DBType=DAO
ColumnCount=3
Column1=[CourseID], 12, 8
Column2=[CourseTitle], 12, 50
Column3=[Hours], 5, 2

[DLG:IDD_COURSE_FORM]
Type=1
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COURSEID,edit,1350633600
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TITLE,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_HOURS,edit,1350631552

[TB:IDR_MAINFRAME]
Type=1
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_RECORD_FIRST
Command6=ID_RECORD_PREV
Command7=ID_RECORD_NEXT
Command8=ID_RECORD_LAST
Command9=ID_APP_ABOUT
Command10=ID_RECORD_ADD
Command11=ID_RECORD_REFRESH
Command12=ID_RECORD_DELETE
CommandCount=12

