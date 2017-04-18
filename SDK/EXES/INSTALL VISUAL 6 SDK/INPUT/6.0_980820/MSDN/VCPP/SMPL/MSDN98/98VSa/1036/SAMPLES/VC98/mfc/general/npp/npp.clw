; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "npp.h"
LastPage=0

ClassCount=9
Class1=CComboToolBar
Class2=CTBComboBox
Class3=CFindDlg
Class4=CGotoDlg
Class5=CMainFrame
Class6=CNotepadApp
Class7=CAboutDlg
Class8=CNotepadDoc
Class9=CNotepadView

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_GOTO
Resource4=IDD_FIND

[CLS:CComboToolBar]
Type=0
BaseClass=CToolBar
HeaderFile=combobar.h
ImplementationFile=combobar.cpp

[CLS:CTBComboBox]
Type=0
BaseClass=CComboBox
HeaderFile=combobar.h
ImplementationFile=combobar.cpp

[CLS:CFindDlg]
Type=0
BaseClass=CDialog
HeaderFile=finddlg.h
ImplementationFile=finddlg.cpp

[CLS:CGotoDlg]
Type=0
BaseClass=CDialog
HeaderFile=gotodlg.h
ImplementationFile=gotodlg.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp

[CLS:CNotepadApp]
Type=0
BaseClass=CWinApp
HeaderFile=np.h
ImplementationFile=np.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=np.cpp
ImplementationFile=np.cpp
LastObject=CAboutDlg

[CLS:CNotepadDoc]
Type=0
BaseClass=CDocument
HeaderFile=npdoc.h
ImplementationFile=npdoc.cpp

[CLS:CNotepadView]
Type=0
BaseClass=CEditView
HeaderFile=npview.h
ImplementationFile=npview.cpp

[DLG:IDD_FIND]
Type=1
Class=CFindDlg
ControlCount=8
Control1=IDC_COMBO1,combobox,1344339970
Control2=IDC_CHECK1,button,1342242819
Control3=IDC_RADIO1,button,1342373897
Control4=IDC_RADIO2,button,1342242825
Control5=ID_EDIT_FIND_NEXT,button,1342373889
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_GOTO]
Type=1
Class=CGotoDlg
ControlCount=4
Control1=IDC_GOTO_LINE,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

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
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_SEND_MAIL
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_FIND
Command16=ID_EDIT_REPLACE
Command17=ID_EDIT_GOTO
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_APP_ABOUT
CommandCount=20

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_FIND_COMBO
Command3=ID_EDIT_GOTO
Command4=ID_FILE_NEW
Command5=ID_FILE_OPEN
Command6=ID_FILE_PRINT
Command7=ID_FILE_SAVE
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_VIEW_FIND_NEXT
Command12=ID_EDIT_FIND
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_EDIT_COPY
Command16=ID_EDIT_PASTE
Command17=ID_EDIT_CUT
CommandCount=17

