; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLogViewDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "LogView.h"

ClassCount=4
Class1=CLogViewApp
Class2=CLogViewDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_NEWENTRY
Class4=CNewEntryDlg
Resource4=IDD_LOGVIEW_DIALOG

[CLS:CLogViewApp]
Type=0
HeaderFile=LogView.h
ImplementationFile=LogView.cpp
Filter=N

[CLS:CLogViewDlg]
Type=0
HeaderFile=LogViewDlg.h
ImplementationFile=LogViewDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CLogViewDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=LogViewDlg.h
ImplementationFile=LogViewDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_LOGVIEW_DIALOG]
Type=1
Class=CLogViewDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_FREQ,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_LOGS,listbox,1352732929
Control7=IDC_STATIC,static,1342308352
Control8=IDC_BAND,listbox,1352728833
Control9=IDC_NEW,button,1342242816
Control10=IDC_DELETE,button,1342242816

[DLG:IDD_NEWENTRY]
Type=1
Class=CNewEntryDlg
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_FREQ,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_MODE,combobox,1344339971
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATION,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_DESC,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_DATE,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_TIME,static,1342308352
Control15=IDC_STATIC,static,1342308352

[CLS:CNewEntryDlg]
Type=0
HeaderFile=NewEntryDlg.h
ImplementationFile=NewEntryDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CNewEntryDlg

