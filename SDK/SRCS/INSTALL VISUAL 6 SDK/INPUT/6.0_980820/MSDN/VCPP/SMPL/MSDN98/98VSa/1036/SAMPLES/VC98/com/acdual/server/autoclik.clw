; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAutoClickDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "autoclik.h"
LastPage=0

ClassCount=8
Class1=CAutoClickDoc
Class2=CAutoClickView
Class3=CAutoClickApp
Class4=CAboutDlg
Class5=CChildFrame
Class6=CAutoClickPoint
Class7=CChangeText
Class8=CMainFrame

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDR_ACLICKTYPE
Resource3=IDD_ABOUTBOX
Resource4=IDD_CHANGE_TEXT

[CLS:CAutoClickDoc]
Type=0
BaseClass=CDocument
HeaderFile=aclikdoc.h
ImplementationFile=aclikdoc.cpp
LastObject=CAutoClickDoc

[CLS:CAutoClickView]
Type=0
BaseClass=CView
HeaderFile=aclikvw.h
ImplementationFile=aclikvw.cpp

[CLS:CAutoClickApp]
Type=0
BaseClass=CWinApp
HeaderFile=autoclik.h
ImplementationFile=autoclik.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=autoclik.cpp
ImplementationFile=autoclik.cpp
LastObject=CAboutDlg

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=childfrm.h
ImplementationFile=childfrm.cpp

[CLS:CAutoClickPoint]
Type=0
BaseClass=CCmdTarget
HeaderFile=clikpnt.h
ImplementationFile=clikpnt.cpp

[CLS:CChangeText]
Type=0
BaseClass=CDialog
HeaderFile=dialogs.h
ImplementationFile=dialogs.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CHANGE_TEXT]
Type=1
Class=CChangeText
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME]
Type=1
Class=?
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
Class=?
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
Class=?
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

