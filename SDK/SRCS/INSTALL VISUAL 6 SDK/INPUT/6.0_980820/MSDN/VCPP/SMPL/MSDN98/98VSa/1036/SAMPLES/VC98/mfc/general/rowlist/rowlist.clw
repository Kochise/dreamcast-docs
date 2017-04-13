; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRowListView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RowList.h"
LastPage=0

ClassCount=6
Class1=CRowListApp
Class2=CRowListDoc
Class3=CRowListView
Class4=CMainFrame

ResourceCount=2
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CListViewEx
Resource2=IDR_MAINFRAME

[CLS:CRowListApp]
Type=0
HeaderFile=RowList.h
ImplementationFile=RowList.cpp
Filter=N

[CLS:CRowListDoc]
Type=0
HeaderFile=RListDoc.h
ImplementationFile=RListDoc.cpp
Filter=N

[CLS:CRowListView]
Type=0
HeaderFile=RListVw.h
ImplementationFile=RListVw.cpp
Filter=C
BaseClass=CListViewEx
VirtualFilter=VWC
LastObject=ID_VIEW_CLIENTWIDTHSEL

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_EXTRA_COLOR



[CLS:CAboutDlg]
Type=0
HeaderFile=RowList.cpp
ImplementationFile=RowList.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=ID_VIEW_TOOLBAR
Command3=ID_VIEW_STATUS_BAR
Command4=ID_VIEW_LARGEICONS
Command5=ID_VIEW_SMALLICONS
Command6=ID_VIEW_LISTMODE
Command7=ID_VIEW_DETAILSMODE
Command8=ID_VIEW_ROWDETAILS
Command9=ID_VIEW_STATEICONS
Command10=ID_VIEW_CLIENTWIDTHSEL
Command11=ID_APP_ABOUT
CommandCount=11

[TB:IDR_MAINFRAME]
Type=1
Command1=ID_VIEW_LARGEICONS
Command2=ID_VIEW_SMALLICONS
Command3=ID_VIEW_LIST
Command4=ID_VIEW_DETAILS
Command5=ID_VIEW_ROWDETAILS
Command6=ID_VIEW_STATEICONS
Command7=ID_VIEW_CLIENTWIDTHSEL
Command8=ID_APP_ABOUT
CommandCount=8

[CLS:CListViewEx]
Type=0
HeaderFile=listvwex.h
ImplementationFile=listvwex.cpp
BaseClass=CListView
LastObject=CListViewEx
Filter=C
VirtualFilter=VWC

