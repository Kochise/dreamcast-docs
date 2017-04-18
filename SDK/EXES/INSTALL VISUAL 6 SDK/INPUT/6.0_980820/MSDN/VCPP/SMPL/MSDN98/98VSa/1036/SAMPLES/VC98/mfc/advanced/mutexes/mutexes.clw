; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mutexes.h"
LastPage=0

ClassCount=5
Class1=CAboutDlg
Class2=CMutexesDlg
Class3=CMutexesApp
Class4=CCounterThread
Class5=CDisplayThread

ResourceCount=2
Resource1=IDD_MUTEXES_DIALOG
Resource2=IDD_ABOUTBOX

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=mutexdlg.cpp
ImplementationFile=mutexdlg.cpp
LastObject=CAboutDlg

[CLS:CMutexesDlg]
Type=0
BaseClass=CDialog
HeaderFile=mutexdlg.h
ImplementationFile=mutexdlg.cpp

[CLS:CMutexesApp]
Type=0
BaseClass=CWinApp
HeaderFile=mutexes.h
ImplementationFile=mutexes.cpp

[CLS:CCounterThread]
Type=0
BaseClass=CWinThread
HeaderFile=threads.h
ImplementationFile=threads.cpp

[CLS:CDisplayThread]
Type=0
BaseClass=CWinThread
HeaderFile=threads.h
ImplementationFile=threads.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MUTEXES_DIALOG]
Type=1
Class=CMutexesDlg
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PRIORITYCLASS,combobox,1342373891
Control3=IDC_STATIC,static,1342373900
Control4=IDC_DSPYTHRDPRIORITY,combobox,1342373891
Control5=IDC_STATIC,static,1342373900
Control6=IDC_CNTRTHRDPRIORITY,combobox,1342373891
Control7=IDC_SYNCHRONIZE,button,1342242819
Control8=IDC_SHOWCNTRTHRD,button,1342242819
Control9=IDC_PAUSE,button,1342242819
Control10=IDC_DATABOX,listbox,1352859649

