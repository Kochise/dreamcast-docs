; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMfcAtlDlg
LastTemplate=CCmdTarget
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MfcAtl.h"
ODLFile=MfcAtl.odl

ClassCount=5
Class1=CMfcAtlApp
Class2=CMfcAtlDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CObjectOne
Class5=CObjectTwo
Resource3=IDD_MFCATL_DIALOG

[CLS:CMfcAtlApp]
Type=0
HeaderFile=MfcAtl.h
ImplementationFile=MfcAtl.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CMfcAtlApp

[CLS:CMfcAtlDlg]
Type=0
HeaderFile=MfcAtlDl.h
ImplementationFile=MfcAtlDl.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDCLOSE

[CLS:CAboutDlg]
Type=0
HeaderFile=MfcAtlDl.h
ImplementationFile=MfcAtlDl.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MFCATL_DIALOG]
Type=1
Class=CMfcAtlDlg
ControlCount=1
Control1=IDCLOSE,button,1342242817

[CLS:CObjectOne]
Type=0
HeaderFile=ObjOne.h
ImplementationFile=ObjOne.cpp
BaseClass=CCmdTarget
Filter=N
VirtualFilter=C

[CLS:CObjectTwo]
Type=0
HeaderFile=ObjTwo.h
ImplementationFile=ObjTwo.cpp
BaseClass=CCmdTarget
Filter=N
VirtualFilter=C
LastObject=CObjectTwo

