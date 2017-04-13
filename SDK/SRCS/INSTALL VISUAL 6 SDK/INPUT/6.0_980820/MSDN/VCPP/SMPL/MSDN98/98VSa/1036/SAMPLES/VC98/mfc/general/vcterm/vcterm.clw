; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSettingsDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "vcterm.h"
LastPage=0

ClassCount=7
Class1=CInputDlg
Class2=CMainFrame
Class3=CSettingsDlg
Class4=CTermEdit
Class5=CVCTermApp
Class6=CAboutDlg

ResourceCount=5
Resource1=IDD_INPUTDLG
Resource2=IDD_SETTINGS
Resource3=IDR_MAINFRAME
Resource4=IDD_ABOUTBOX
Class7=CCancelDlg
Resource5=IDD_CANCELDLG

[CLS:CInputDlg]
Type=0
BaseClass=CDialog
HeaderFile=InputDlg.h
ImplementationFile=InputDlg.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CSettingsDlg]
Type=0
BaseClass=CDialog
HeaderFile=setdlg.h
ImplementationFile=setdlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CSettingsDlg

[CLS:CTermEdit]
Type=0
BaseClass=CEdit
HeaderFile=termedit.h
ImplementationFile=termedit.cpp
Filter=C
LastObject=ID_TEST
VirtualFilter=WC

[CLS:CVCTermApp]
Type=0
BaseClass=CWinApp
HeaderFile=vcterm.h
ImplementationFile=vcterm.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=vcterm.cpp
ImplementationFile=vcterm.cpp

[DLG:IDD_INPUTDLG]
Type=1
Class=CInputDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC1,static,1342308352
Control4=IDC_EDIT1,edit,1350631552

[DLG:IDD_SETTINGS]
Type=1
Class=CSettingsDlg
ControlCount=32
Control1=IDC_STATIC,button,1342308359
Control2=IDC_BAUD1,button,1342373897
Control3=IDC_BAUD2,button,1342177289
Control4=IDC_BAUD3,button,1342177289
Control5=IDC_BAUD4,button,1342177289
Control6=IDC_BAUD5,button,1342177289
Control7=IDC_BAUD6,button,1342177289
Control8=IDC_STATIC,button,1342308359
Control9=IDC_DATABITS1,button,1342373897
Control10=IDC_DATABITS2,button,1342177289
Control11=IDC_STATIC,button,1342308359
Control12=IDC_STOPBITS1,button,1342373897
Control13=IDC_STOPBITS2,button,1342177289
Control14=IDC_STATIC,button,1342308359
Control15=IDC_ECHO1,button,1342373897
Control16=IDC_ECHO2,button,1342177289
Control17=IDC_STATIC,button,1342308359
Control18=IDC_PARITY1,button,1342373897
Control19=IDC_PARITY2,button,1342177289
Control20=IDC_PARITY3,button,1342177289
Control21=IDC_STATIC,button,1342308359
Control22=IDC_COM1,button,1342373897
Control23=IDC_COM2,button,1342177289
Control24=IDC_COM3,button,1342177289
Control25=IDC_COM4,button,1342177289
Control26=IDC_STATIC,button,1342308359
Control27=IDC_FLOW1,button,1342373897
Control28=IDC_FLOW2,button,1342177289
Control29=IDC_FLOW3,button,1342177289
Control30=IDC_FLOW4,button,1342177289
Control31=IDOK,button,1342373888
Control32=IDCANCEL,button,1342373888

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308480
Control6=IDC_STATIC,static,1342308480

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPENLOG
Command2=ID_FILE_CLOSELOG
Command3=ID_FILE_TRANSMIT
Command4=ID_COMM_DIAL
Command5=ID_COMM_HANGUP
Command6=ID_APP_ABOUT
CommandCount=6

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPENLOG
Command2=ID_FILE_CLOSELOG
Command3=ID_FILE_TRANSMIT
Command4=ID_APP_EXIT
Command5=ID_COMM_OPEN
Command6=ID_COMM_SETTINGS
Command7=ID_COMM_DIAL
Command8=ID_COMM_HANGUP
Command9=ID_PROP_INPUTLEN
Command10=ID_PROP_RTHRESHOLD
Command11=ID_PROP_STHRESHOLD
Command12=ID_PROP_PARITYREPLACE
Command13=ID_PROP_DTRENABLE
Command14=ID_PROP_CDHOLDING
Command15=ID_PROP_CTSHOLDING
Command16=ID_PROP_DSRHOLDING
Command17=ID_VIEW_TOOLBAR
Command18=ID_VIEW_STATUS_BAR
Command19=ID_APP_ABOUT
CommandCount=19

[ACL:IDR_MAINFRAME]
Type=1
Class=?
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

[DLG:IDD_CANCELDLG]
Type=1
Class=CCancelDlg
ControlCount=2
Control1=IDCANCEL,button,1342242817
Control2=IDC_STATIC,static,1342308352

[CLS:CCancelDlg]
Type=0
HeaderFile=CanDlg.h
ImplementationFile=CanDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CCancelDlg
VirtualFilter=dWC

