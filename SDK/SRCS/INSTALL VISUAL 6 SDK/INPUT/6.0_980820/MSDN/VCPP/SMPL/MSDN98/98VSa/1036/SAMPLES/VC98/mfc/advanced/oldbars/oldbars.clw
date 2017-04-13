; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COldbarsView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "oldbars.h"
LastPage=0

ClassCount=8
Class1=COldbarsApp
Class2=COldbarsDoc
Class3=COldbarsView
Class4=CMainFrame
Class7=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_OLDBARTYPE

[CLS:COldbarsApp]
Type=0
HeaderFile=oldbars.h
ImplementationFile=oldbars.cpp
Filter=N

[CLS:COldbarsDoc]
Type=0
HeaderFile=oldbadoc.h
ImplementationFile=oldbadoc.cpp
Filter=N

[CLS:COldbarsView]
Type=0
HeaderFile=oldbavw.h
ImplementationFile=oldbavw.cpp
Filter=C

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=oldbars.cpp
ImplementationFile=oldbars.cpp
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
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command10=ID_APP_ABOUT
CommandCount=10

[MNU:IDR_OLDBARTYPE]
Type=1
Class=COldbarsView
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
Command23=ID_VIEW_TOOLBAR
Command24=ID_VIEW_STATUS_BAR
Command25=ID_WINDOW_NEW
Command26=ID_WINDOW_CASCADE
Command27=ID_WINDOW_TILE_HORZ
Command28=ID_WINDOW_ARRANGE
Command31=ID_APP_ABOUT
CommandCount=31

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
CommandCount=17

