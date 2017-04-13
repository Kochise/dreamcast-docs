; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mtrecalc.h"
VbxHeaderFile=mtrecalc.h
VbxImplementationFile=mtrecalc.cpp
LastPage=0

ClassCount=7
Class1=CMainFrame
Class2=CRecalcApp
Class3=CAboutDlg
Class4=CRecalcView
Class5=CRecalcDoc
Class6=CSpeedDlg

ResourceCount=6
Resource1=IDD_RECALC_PROGRESS
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_SPEED
Resource5=IDD_MTRECALC_FORM
Class7=CProgressDlg
Resource6=IDR_RECALCTYPE

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
LastObject=ID_EDIT_PASTE

[CLS:CRecalcApp]
Type=0
HeaderFile=mtrecalc.h
ImplementationFile=mtrecalc.cpp

[CLS:CAboutDlg]
Type=0
HeaderFile=mtrecalc.cpp
ImplementationFile=mtrecalc.cpp

[CLS:CRecalcView]
Type=0
HeaderFile=recalcvw.h
ImplementationFile=recalcvw.cpp
Filter=D
LastObject=CRecalcView
VirtualFilter=RVWC

[CLS:CRecalcDoc]
Type=0
HeaderFile=recaldoc.h
ImplementationFile=recaldoc.cpp
LastObject=CRecalcDoc
Filter=N
VirtualFilter=DC

[CLS:CSpeedDlg]
Type=0
HeaderFile=speeddlg.h
ImplementationFile=speeddlg.cpp
Filter=D
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MTRECALC_FORM]
Type=1
Class=CRecalcView
ControlCount=7
Control1=IDC_INT1,edit,1350631552
Control2=IDC_INT2,edit,1350631552
Control3=IDC_SUM,edit,1350633600
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_SPEED]
Type=1
Class=CSpeedDlg
ControlCount=4
Control1=IDC_SPEED,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

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

[MNU:IDR_RECALCTYPE]
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
Command15=ID_SINGLE_THREAD
Command16=ID_WORKER_THREAD
Command17=ID_RECALCULATE_NOW
Command18=ID_KILL_WORKER_THREAD
Command19=ID_RECALC_SPEED
Command20=ID_VIEW_TOOLBAR
Command21=ID_VIEW_STATUS_BAR
Command22=ID_WINDOW_NEW
Command23=ID_WINDOW_CASCADE
Command24=ID_WINDOW_TILE_HORZ
Command25=ID_WINDOW_ARRANGE
Command26=ID_APP_ABOUT
CommandCount=26

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_RECALCULATE_NOW
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[DLG:IDD_RECALC_PROGRESS]
Type=1
Class=CProgressDlg
ControlCount=3
Control1=IDCANCEL,button,1342242816
Control2=IDC_PERCENT_DONE,edit,1350633600
Control3=IDC_STATIC,static,1342308352

[CLS:CProgressDlg]
Type=0
HeaderFile=progress.h
ImplementationFile=progress.cpp
Filter=D
VirtualFilter=dWC

