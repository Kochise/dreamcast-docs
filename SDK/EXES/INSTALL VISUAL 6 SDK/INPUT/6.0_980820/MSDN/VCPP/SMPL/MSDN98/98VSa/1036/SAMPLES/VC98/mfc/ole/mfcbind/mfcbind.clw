; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mfcbind.h"
LastPage=0

ClassCount=7
Class1=CMFCBindDoc
Class2=CMFCBindView
Class3=CMainFrame
Class4=CMFCBindApp
Class5=CAboutDlg
Class6=CObjListView
Class7=CCustomList

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDR_CNTR_INPLACE
Resource3=IDD_ABOUTBOX
Resource4=IDD_GETURL

[CLS:CMFCBindDoc]
Type=0
BaseClass=COleDocument
HeaderFile=BindDoc.h
ImplementationFile=BindDoc.cpp

[CLS:CMFCBindView]
Type=0
BaseClass=CView
HeaderFile=BindView.h
ImplementationFile=BindView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CMFCBindApp]
Type=0
BaseClass=CWinApp
HeaderFile=MFCBind.h
ImplementationFile=MFCBind.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=MFCBind.cpp
ImplementationFile=MFCBind.cpp
LastObject=CAboutDlg

[CLS:CObjListView]
Type=0
BaseClass=CView
HeaderFile=ObjView.h
ImplementationFile=ObjView.cpp

[CLS:CCustomList]
Type=0
BaseClass=CListBox
HeaderFile=ObjView.h
ImplementationFile=ObjView.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

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
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_OLE_INSERT_NEW
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_CNTR_INPLACE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_OLE_INSERT_NEW
Command8=ID_SECTION_REMOVE
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_PRINT
Command11=ID_FILE_PRINTALLSECTIONS
CommandCount=11

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_OLE_INSERT_NEW
Command2=ID_EDIT_COPY
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_PRINT
Command6=ID_FILE_SAVE
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_CANCEL_EDIT_CNTR
Command11=ID_NEXT_PANE
Command12=ID_PREV_PANE
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_CUT
Command16=ID_EDIT_UNDO
CommandCount=16

[ACL:IDR_CNTR_INPLACE]
Type=1
Class=?
Command1=ID_OLE_INSERT_NEW
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_CANCEL_EDIT_CNTR
Command7=ID_NEXT_PANE
Command8=ID_PREV_PANE
CommandCount=8

[DLG:IDD_GETURL]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352

