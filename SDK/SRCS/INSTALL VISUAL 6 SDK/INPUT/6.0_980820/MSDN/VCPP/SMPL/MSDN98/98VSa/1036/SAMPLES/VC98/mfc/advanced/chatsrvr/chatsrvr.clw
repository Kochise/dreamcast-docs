; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CServerView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chatsrvr.h"
LastPage=0

ClassCount=6
Class1=CServerApp
Class2=CServerDoc
Class3=CServerView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDD_DISCUSSION
Class5=CAboutDlg
Class6=CDiscussionDlg
Resource3=IDR_MAINFRAME

[CLS:CServerApp]
Type=0
HeaderFile=chatsrvr.h
ImplementationFile=chatsrvr.cpp
Filter=N
VirtualFilter=AC
LastObject=ID_EDIT_CUT

[CLS:CServerDoc]
Type=0
HeaderFile=srvrdoc.h
ImplementationFile=srvrdoc.cpp
Filter=N
VirtualFilter=DC
LastObject=CServerDoc

[CLS:CServerView]
Type=0
HeaderFile=srvrvw.h
ImplementationFile=srvrvw.cpp
Filter=C

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=chatsrvr.cpp
ImplementationFile=chatsrvr.cpp
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
Command2=ID_FILE_SAVE
Command3=ID_APP_EXIT
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_STATUS_BAR
Command10=ID_APP_ABOUT
CommandCount=10

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_SAVE
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_NEXT_PANE
Command8=ID_PREV_PANE
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_CUT
Command12=ID_EDIT_UNDO
CommandCount=12

[DLG:IDD_DISCUSSION]
Type=1
Class=CDiscussionDlg
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631424
Control3=IDOK,button,1342242817

[CLS:CDiscussionDlg]
Type=0
HeaderFile=dialogs.h
ImplementationFile=dialogs.cpp
Filter=D
VirtualFilter=dWC

