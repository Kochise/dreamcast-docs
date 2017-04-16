; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAdvancedFTPDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "AdvancedFTP.h"

ClassCount=3
Class1=CAdvancedFTPApp
Class2=CAdvancedFTPDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_ADVANCEDFTP_DIALOG

[CLS:CAdvancedFTPApp]
Type=0
HeaderFile=AdvancedFTP.h
ImplementationFile=AdvancedFTP.cpp
Filter=N

[CLS:CAdvancedFTPDlg]
Type=0
HeaderFile=AdvancedFTPDlg.h
ImplementationFile=AdvancedFTPDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAdvancedFTPDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=AdvancedFTPDlg.h
ImplementationFile=AdvancedFTPDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ADVANCEDFTP_DIALOG]
Type=1
Class=CAdvancedFTPDlg
ControlCount=26
Control1=IDC_FTPSITE,edit,1350631552
Control2=IDC_USERNAME,edit,1350631552
Control3=IDC_PASSWORD,edit,1350631552
Control4=IDC_GETDIRECTORYLISTING,button,1342242816
Control5=IDC_DOWNLOADDIR,edit,1350631552
Control6=IDC_BROWSEDIR,button,1342242816
Control7=IDC_ADDSELECTED,button,1342242816
Control8=IDC_REMOVESELECTED,button,1342242816
Control9=IDC_ADDALL,button,1342242816
Control10=IDC_REMOVEALL,button,1342242816
Control11=IDC_DOWNLOAD,button,1342242816
Control12=IDOK,button,1342242817
Control13=ID_HELP,button,1342242816
Control14=IDC_FTPLISTNG,SysListView32,1350631441
Control15=IDC_DOWNLOADLISTING,SysListView32,1350631441
Control16=IDC_STATIC,static,1342308352
Control17=IDC_TOTALPROGRESS,msctls_progress32,1350565888
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,static,1342308352
Control22=IDC_PROXYSERVER,edit,1350631552
Control23=IDC_STATIC,button,1342177287
Control24=IDC_CANCELOPERATION,button,1342242816
Control25=IDC_SITECONNECT,button,1342242816
Control26=IDC_SITEDISCONNECT,button,1342242816

