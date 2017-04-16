; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CThreadlibtestView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "threadlibtest.h"
LastPage=0

ClassCount=7
Class1=CThreadlibtestApp
Class2=CThreadlibtestDoc
Class3=CThreadlibtestView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDD_NOTHREADDIALOG
Class5=CAboutDlg
Class6=CEasyOutputView
Class7=CNoThreadDialog
Resource3=IDR_MAINFRAME

[CLS:CThreadlibtestApp]
Type=0
HeaderFile=threadlibtest.h
ImplementationFile=threadlibtest.cpp
Filter=N
LastObject=CThreadlibtestApp

[CLS:CThreadlibtestDoc]
Type=0
HeaderFile=threadlibtestDoc.h
ImplementationFile=threadlibtestDoc.cpp
Filter=N

[CLS:CThreadlibtestView]
Type=0
HeaderFile=threadlibtestView.h
ImplementationFile=threadlibtestView.cpp
Filter=C
BaseClass=CEasyOutputView
VirtualFilter=VWC
LastObject=CThreadlibtestView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=threadlibtest.cpp
ImplementationFile=threadlibtest.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
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
Command7=ID_SETUPPARAMETERS_RANDOMDELAYS
Command8=ID_SETUPPARAMETERS_CONSTANTDELAYS
Command9=IDC_WORSTCASE
Command10=IDM_SETNOTHREADS
Command11=IDM_SERIAL
Command12=IDM_CONCURRENT
Command13=IDM_SINGLETEST
Command14=IDM_MULTIPLE
Command15=IDM_DOALL
Command16=ID_APP_ABOUT
CommandCount=16

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

[CLS:CEasyOutputView]
Type=0
HeaderFile=easyview.h
ImplementationFile=easyview.cpp
BaseClass=CView
LastObject=CEasyOutputView

[DLG:IDD_NOTHREADDIALOG]
Type=1
Class=CNoThreadDialog
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_DELAYFACTOR,edit,1350631552
Control7=IDC_STATIC,button,1342177287
Control8=IDM_CPUBOUND,button,1342177289
Control9=IDC_IOBOUND,button,1342177289

[CLS:CNoThreadDialog]
Type=0
HeaderFile=NoThreadDialog.h
ImplementationFile=NoThreadDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDM_CPUBOUND

