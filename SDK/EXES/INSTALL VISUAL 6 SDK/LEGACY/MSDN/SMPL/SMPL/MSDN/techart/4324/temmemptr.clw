; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTemMemPtrDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TemMemPtr.h"
LastPage=0

ClassCount=6
Class1=CTemMemPtrApp
Class2=CTemMemPtrDoc
Class3=CTemMemPtrView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CTheDialog
Resource3=IDD_DIALOG1

[CLS:CTemMemPtrApp]
Type=0
HeaderFile=TemMemPtr.h
ImplementationFile=TemMemPtr.cpp
Filter=N
LastObject=ID_CALLIT_FROMDOC

[CLS:CTemMemPtrDoc]
Type=0
HeaderFile=TemMedoc.h
ImplementationFile=TemMedoc.cpp
Filter=N
VirtualFilter=DC
LastObject=ID_CALLIT_FROMDOC

[CLS:CTemMemPtrView]
Type=0
HeaderFile=TemMevw.h
ImplementationFile=TemMevw.cpp
Filter=C
VirtualFilter=VWC
LastObject=ID_CALLIT_FROMVIEW

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=TemMemPtr.cpp
ImplementationFile=TemMemPtr.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=ID_CALLIT_FROMDOC
Command3=ID_CALLIT_FROMVIEW
Command4=ID_APP_ABOUT
CommandCount=4

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
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

[DLG:IDD_DIALOG1]
Type=1
Class=CTheDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_CHANGE,static,1342308352
Control4=IDC_STATIC,button,1342177287

[CLS:CTheDialog]
Type=0
HeaderFile=thedialog.h
ImplementationFile=thedialog.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_CHANGE

