; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "oleview.h"
LastPage=0

ClassCount=7
Class1=COle2ViewDoc
Class2=CMainFrame
Class3=CObjTreeView
Class4=COle2ViewApp
Class5=CAboutDlg
Class6=CRegistryView
Class7=CDropTargetView

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_REGVIEW

[CLS:COle2ViewDoc]
Type=0
BaseClass=CDocument
HeaderFile=doc.h
ImplementationFile=doc.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp

[CLS:CObjTreeView]
Type=0
BaseClass=CTreeView
HeaderFile=obj_vw.h
ImplementationFile=obj_vw.cpp

[CLS:COle2ViewApp]
Type=0
BaseClass=CWinApp
HeaderFile=oleview.h
ImplementationFile=oleview.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=oleview.cpp
ImplementationFile=oleview.cpp
LastObject=CAboutDlg

[CLS:CRegistryView]
Type=0
BaseClass=CFormView
HeaderFile=regview.h
ImplementationFile=regview.cpp

[CLS:CDropTargetView]
Type=0
BaseClass=CView
HeaderFile=view.h
ImplementationFile=view.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_APPNAME,static,1342308352
Control3=IDC_COPYRIGHT,static,1342308352
Control4=IDCANCEL,button,1342373889
Control5=IDC_ALLRIGHTSRESERVED,static,1342308352
Control6=IDC_WRITTENBY,static,1342308352
Control7=IDC_GROUP,static,1342308352
Control8=IDC_VERSION,static,1342308352

[DLG:IDD_REGVIEW]
Type=1
Class=CRegistryView
ControlCount=4
Control1=IDC_OBJICON,static,1342177283
Control2=IDC_OBJECTNAME,static,1342308492
Control3=IDC_OBJECTCLSID,static,1342308492
Control4=IDC_TREEVIEW,SysTreeView32,1350631450

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_HELP_INDEX
Command9=ID_VIEW_REFRESH
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_BINDTOAFILE
Command2=ID_FILE_VIEWTYPELIB
Command3=ID_FILE_RUNREGEDIT
Command4=ID_APP_EXIT
Command5=ID_OBJECT_DELETE
Command6=ID_OBJECT_VERIFY
Command7=ID_IFACES_USEINPROCSERVER
Command8=ID_IFACES_USEINPROCHANDLER
Command9=ID_IFACES_USELOCALSERVER
Command10=ID_VIEW_TOOLBAR
Command11=ID_VIEW_STATUS_BAR
Command12=ID_VIEW_REFRESH
Command13=ID_HELP_INDEX
Command14=ID_HELP_USING
Command15=ID_APP_ABOUT
CommandCount=15

