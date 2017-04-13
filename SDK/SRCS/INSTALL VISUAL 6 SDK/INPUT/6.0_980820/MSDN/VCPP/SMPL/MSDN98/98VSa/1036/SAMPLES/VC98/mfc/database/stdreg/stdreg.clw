; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CStdRegSetupApp
LastTemplate=CRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "stdreg.h"

ClassCount=10
Class1=CStdRegSetupApp
Class2=CStdRegSetupDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_COLUMN_SYNTAX_DLG
Class4=CColSyntaxDlg
Class5=CCourseSet
Class6=CStudentSet
Class7=CEnrollmentSet
Class8=CSectionSet
Class9=CDynabindSectionSet
Class10=CInstructorSet
Resource4=IDD_STDREG_DIALOG

[CLS:CStdRegSetupApp]
Type=0
HeaderFile=stdreg.h
ImplementationFile=stdreg.cpp
LastObject=CStdRegSetupApp

[CLS:CStdRegSetupDlg]
Type=0
HeaderFile=dialog.h
ImplementationFile=dialog.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_PROGRESS

[CLS:CAboutDlg]
Type=0
HeaderFile=dialog.h
ImplementationFile=dialog.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_STDREG_DIALOG]
Type=1
Class=CStdRegSetupDlg
ControlCount=4
Control1=IDOK,button,1342242816
Control2=IDC_ADD_DATA_SOURCE,button,1342242816
Control3=IDC_INITIALIZE_DATA,button,1342242817
Control4=IDC_PROGRESS,static,1342308352

[DLG:IDD_COLUMN_SYNTAX_DLG]
Type=1
Class=CColSyntaxDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SYNTAX,edit,1350631552
Control5=IDC_LIST_BOX_INSTRUCTION,static,1342308352
Control6=IDC_TYPE_INFO_LIST,listbox,1353777411
Control7=IDC_COL_TYPE_INSTRUCTION,static,1342308352

[CLS:CColSyntaxDlg]
Type=0
HeaderFile=columdlg.h
ImplementationFile=columdlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CColSyntaxDlg

[CLS:CCourseSet]
Type=0
HeaderFile=coursset.h
ImplementationFile=coursset.cpp
Filter=N
VirtualFilter=r

[DB:CCourseSet]
DB=1
ColumnCount=3
Column1=CourseID,12,8,1
Column2=CourseTitle,12,50,1
Column3=Hours,6,8,1

[CLS:CStudentSet]
Type=0
HeaderFile=stdset.h
ImplementationFile=stdset.cpp
Filter=N
VirtualFilter=r

[DB:CStudentSet]
DB=1
ColumnCount=3
Column1=StudentID,4,4,1
Column2=Name,12,40,1
Column3=GradYear,5,2,1

[CLS:CEnrollmentSet]
Type=0
HeaderFile=enrolset.h
ImplementationFile=enrolset.cpp
Filter=N
VirtualFilter=r

[DB:CEnrollmentSet]
DB=1
ColumnCount=4
Column1=StudentID,4,4,1
Column2=CourseID,12,8,1
Column3=SectionNo,12,4,1
Column4=Grade,12,1,1

[CLS:CSectionSet]
Type=0
HeaderFile=sectset.h
ImplementationFile=sectset.cpp
Filter=N
VirtualFilter=r

[DB:CSectionSet]
DB=1
ColumnCount=6
Column1=CourseID,12,8,1
Column2=SectionNo,12,4,1
Column3=InstructorID,12,8,1
Column4=RoomNo,12,10,1
Column5=Schedule,12,24,1
Column6=Capacity,5,2,1

[CLS:CDynabindSectionSet]
Type=0
HeaderFile=dsectset.h
ImplementationFile=dsectset.cpp
Filter=N
VirtualFilter=r

[DB:CDynabindSectionSet]
DB=1
ColumnCount=8
Column1=CourseID,12,8,1
Column2=SectionNo,12,4,1
Column3=InstructorID,12,8,1
Column4=RoomNo,12,10,1
Column5=Schedule,12,24,1
Column6=Capacity,5,2,1
Column7=LabRoomNo,12,10,1
Column8=LabSchedule,12,24,1

[CLS:CInstructorSet]
Type=0
HeaderFile=instrset.h
ImplementationFile=instrset.cpp
Filter=N
VirtualFilter=r

[DB:CInstructorSet]
DB=1
ColumnCount=3
Column1=InstructorID,12,8,1
Column2=Name,12,40,1
Column3=RoomNo,12,10,1



