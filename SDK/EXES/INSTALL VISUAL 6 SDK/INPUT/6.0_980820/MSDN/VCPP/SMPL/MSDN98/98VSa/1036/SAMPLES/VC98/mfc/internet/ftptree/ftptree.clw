; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFTPTREEDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ftptree.h"
LastPage=0

ClassCount=4
Class1=CMyTreeCtrl
Class2=CAboutDlg
Class3=CFTPTREEDlg
Class4=CFTPTREEApp

ResourceCount=2
Resource1=IDD_ABOUTBOX
Resource2=IDD_FTPTREE_DIALOG

[CLS:CMyTreeCtrl]
Type=0
BaseClass=CTreeCtrl
HeaderFile=FtpTrCtl.h
ImplementationFile=FtpTrCtl.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=FTPtrDlg.cpp
ImplementationFile=FTPtrDlg.cpp
LastObject=CAboutDlg

[CLS:CFTPTREEDlg]
Type=0
BaseClass=CDialog
HeaderFile=FTPtrDlg.h
ImplementationFile=FTPtrDlg.cpp
LastObject=CFTPTREEDlg

[CLS:CFTPTREEApp]
Type=0
BaseClass=CWinApp
HeaderFile=FTPTREE.h
ImplementationFile=FTPTREE.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_FTPTREE_DIALOG]
Type=1
Class=CFTPTREEDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_FTPSITE,edit,1350631552
Control3=ID_BROWSE_SITE,button,1342242817
Control4=IDC_FTPTREE,SysTreeView32,1350631431

