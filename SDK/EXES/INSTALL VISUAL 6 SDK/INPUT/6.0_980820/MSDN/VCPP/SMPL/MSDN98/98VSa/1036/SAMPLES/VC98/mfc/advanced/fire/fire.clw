; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFireDlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "fire.h"

ClassCount=4
Class1=CFireApp
Class2=CFireDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CFireWnd
Resource3=IDD_FIRE_DIALOG

[CLS:CFireApp]
Type=0
HeaderFile=fire.h
ImplementationFile=fire.cpp
Filter=N

[CLS:CFireDlg]
Type=0
HeaderFile=firedlg.h
ImplementationFile=firedlg.cpp
Filter=W
LastObject=CFireDlg
VirtualFilter=dWC
BaseClass=CDialog

[CLS:CAboutDlg]
Type=0
HeaderFile=firedlg.h
ImplementationFile=firedlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_FIRE_DIALOG]
Type=1
Class=CFireDlg
ControlCount=10
Control1=IDC_COLOR,SysTabControl32,1342242816
Control2=IDC_FIRE,static,1342177284
Control3=IDC_STATIC,static,1342308352
Control4=IDC_HEIGHT,msctls_trackbar32,1342242823
Control5=IDC_STATIC,button,1342177287
Control6=IDC_SETTING,edit,1484849280
Control7=IDC_SETTINGCTRL,msctls_updown32,1476395190
Control8=IDC_PROPERTY,SysTreeView32,1342242871
Control9=IDC_APPLY,button,1476460545
Control10=IDC_BURN,msctls_progress32,1350565889

[CLS:CFireWnd]
Type=0
HeaderFile=firewnd.h
ImplementationFile=firewnd.cpp
Filter=W
LastObject=CFireWnd

