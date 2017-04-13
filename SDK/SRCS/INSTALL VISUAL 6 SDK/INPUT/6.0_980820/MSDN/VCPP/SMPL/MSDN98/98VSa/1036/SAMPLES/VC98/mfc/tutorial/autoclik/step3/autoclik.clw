; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAutoClickDoc
LastTemplate=CCmdTarget
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "AutoClik.h"
ODLFile=AutoClik.odl
LastPage=0

ClassCount=8
Class1=CAutoClickApp
Class2=CAutoClickDoc
Class3=CAutoClickView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_ACLICKTYPE
Class5=CAboutDlg
Class6=CChildFrame
Resource4=IDD_CHANGE_TEXT
Class7=CChangeText
Class8=CAutoClickPoint

[CLS:CAutoClickApp]
Type=0
HeaderFile=AutoClik.h
ImplementationFile=AutoClik.cpp
Filter=N

[CLS:CAutoClickDoc]
Type=0
HeaderFile=AClikDoc.h
ImplementationFile=AClikDoc.cpp
Filter=N
VirtualFilter=DC
LastObject=CAutoClickDoc

[CLS:CAutoClickView]
Type=0
HeaderFile=AClikVw.h
ImplementationFile=AClikVw.cpp
Filter=C
LastObject=CAutoClickView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M

[CLS:CAboutDlg]
Type=0
HeaderFile=AutoClik.cpp
ImplementationFile=AutoClik.cpp
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
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_ACLICKTYPE]
Type=1
Class=CAutoClickView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_CHANGETEXT
Command16=ID_VIEW_TOOLBAR
Command17=ID_VIEW_STATUS_BAR
Command18=ID_WINDOW_NEW
Command19=ID_WINDOW_CASCADE
Command20=ID_WINDOW_TILE_HORZ
Command21=ID_WINDOW_ARRANGE
Command22=ID_APP_ABOUT
CommandCount=22

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_CHANGE_TEXT]
Type=1
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Class=CChangeText

[CLS:CChangeText]
Type=0
HeaderFile=Dialogs.h
ImplementationFile=Dialogs.cpp
Filter=D
LastObject=CChangeText
VirtualFilter=dWC

[CLS:CAutoClickPoint]
Type=0
HeaderFile=ClikPnt.h
ImplementationFile=ClikPnt.cpp
Filter=N
VirtualFilter=C
LastObject=CAutoClickPoint

