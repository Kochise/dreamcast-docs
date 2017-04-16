; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDialerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dialit.h"
LastPage=0

ClassCount=6
Class1=CDialitApp
Class2=CDialitDoc
Class3=CDialitView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CDialerDlg
Resource3=IDD_DIAL

[CLS:CDialitApp]
Type=0
HeaderFile=dialit.h
ImplementationFile=dialit.cpp
Filter=N

[CLS:CDialitDoc]
Type=0
HeaderFile=dialidoc.h
ImplementationFile=dialidoc.cpp
Filter=N

[CLS:CDialitView]
Type=0
HeaderFile=dialivw.h
ImplementationFile=dialivw.cpp
Filter=C

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=dialit.cpp
ImplementationFile=dialit.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_APP_EXIT
Command3=ID_APP_ABOUT
CommandCount=3

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

[DLG:IDD_DIAL]
Type=1
Class=CDialerDlg
ControlCount=4
Control1=IDE_PHONE,edit,1350631552
Control2=ID_DIAL,button,1342242817
Control3=ID_HANGUP,button,1342242816
Control4=IDC_STATIC,static,1342308352

[CLS:CDialerDlg]
Type=0
HeaderFile=dialerdl.h
ImplementationFile=dialerdl.cpp
Filter=D
VirtualFilter=dWC
LastObject=CDialerDlg

