; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDriverView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ipdrive.h"
ODLFile=ipdrive.odl
LastPage=0

ClassCount=5
Class1=CDriveApp
Class2=CDriverDoc
Class3=CDriverView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_IPDRIVE_FORM

[CLS:CDriveApp]
Type=0
HeaderFile=ipdrive.h
ImplementationFile=ipdrive.cpp
Filter=N

[CLS:CDriverDoc]
Type=0
HeaderFile=ipdridoc.h
ImplementationFile=ipdridoc.cpp
Filter=N
LastObject=CDriverDoc

[CLS:CDriverView]
Type=0
HeaderFile=ipdrivw.h
ImplementationFile=ipdrivw.cpp
Filter=D
VirtualFilter=VWC
LastObject=IDC_COMBO3

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=ipdrive.cpp
ImplementationFile=ipdrive.cpp
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
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_APP_ABOUT
CommandCount=13

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

[DLG:IDD_IPDRIVE_FORM]
Type=1
Class=CDriverView
ControlCount=16
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_COMBO2,combobox,1344339971
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_COMBO3,combobox,1344339971
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT2,edit,1350631552
Control11=IDC_CURRENT_COUNT,static,1342308352
Control12=ID_LOOKUP,button,1342242816
Control13=ID_ADD,button,1342242816
Control14=ID_REMOVE,button,1342242816
Control15=IDC_BUTTON1,button,1342242816
Control16=IDC_BUTTON2,button,1342242816

