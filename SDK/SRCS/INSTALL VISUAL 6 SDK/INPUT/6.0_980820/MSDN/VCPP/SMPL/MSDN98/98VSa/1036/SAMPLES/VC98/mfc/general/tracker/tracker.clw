; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTrackerView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "trackapp.h"
VbxHeaderFile=trackapp.h
VbxImplementationFile=trackapp.cpp
LastPage=0

ClassCount=7
Class1=CHandleSize
Class2=CMinSize
Class3=CMainFrame
Class4=CTrackerApp
Class5=CAboutDlg
Class6=CTrackerDoc
Class7=CTrackerView

ResourceCount=5
Resource1=IDR_TRACKETYPE
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_HANDLE_SIZE
Resource5=IDD_MIN_SIZE

[CLS:CHandleSize]
Type=0
HeaderFile=dialogs.h
ImplementationFile=dialogs.cpp
Filter=D

[CLS:CMinSize]
Type=0
HeaderFile=dialogs.h
ImplementationFile=dialogs.cpp
Filter=D
LastObject=IDC_EDIT1

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp

[CLS:CTrackerApp]
Type=0
HeaderFile=trackapp.h
ImplementationFile=trackapp.cpp

[CLS:CAboutDlg]
Type=0
HeaderFile=trackapp.cpp
ImplementationFile=trackapp.cpp

[CLS:CTrackerDoc]
Type=0
HeaderFile=trackdoc.h
ImplementationFile=trackdoc.cpp

[CLS:CTrackerView]
Type=0
HeaderFile=trackvw.h
ImplementationFile=trackvw.cpp

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

[MNU:IDR_TRACKETYPE]
Type=1
Class=CTrackerView
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
Command15=ID_EDIT_SOLIDLINE
Command16=ID_EDIT_DOTTEDLINE
Command17=ID_EDIT_HATCHEDBORDER
Command18=ID_EDIT_HATCHEDINSIDE
Command19=ID_EDIT_RESIZEINSIDE
Command20=ID_EDIT_RESIZEOUTSIDE
Command21=ID_EDIT_ALLOWINVERT
Command22=ID_VIEW_TOOLBAR
Command23=ID_VIEW_STATUS_BAR
Command24=ID_VIEW_SETHANDLESIZE
Command25=ID_VIEW_SETMINIMUMSIZE
Command26=ID_WINDOW_NEW
Command27=ID_WINDOW_CASCADE
Command28=ID_WINDOW_TILE_HORZ
Command29=ID_WINDOW_ARRANGE
Command30=ID_APP_ABOUT
CommandCount=30

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

[DLG:IDD_HANDLE_SIZE]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Class=CHandleSize

[DLG:IDD_MIN_SIZE]
Type=1
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDD_MIN_SIZE,edit,1350631552
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Class=CMinSize

