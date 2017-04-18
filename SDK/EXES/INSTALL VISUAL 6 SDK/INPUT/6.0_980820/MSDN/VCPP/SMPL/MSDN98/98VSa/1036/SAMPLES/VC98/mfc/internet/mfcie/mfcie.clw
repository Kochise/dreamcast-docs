; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mfcie.h"
LastPage=0

ClassCount=5
Class1=CMfcieApp
Class2=CMfcieDoc
Class3=CMfcieView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDR_MAINFRAME
Resource3=IDR_FAVORITES_POPUP
Resource4=IDR_FONT_POPUP

[CLS:CMfcieApp]
Type=0
HeaderFile=mfcie.h
ImplementationFile=mfcie.cpp
Filter=N

[CLS:CMfcieDoc]
Type=0
HeaderFile=mfcieDoc.h
ImplementationFile=mfcieDoc.cpp
Filter=N

[CLS:CMfcieView]
Type=0
HeaderFile=mfcievw.h
ImplementationFile=mfcievw.cpp
BaseClass=CHtmlView
Filter=C
VirtualFilter=VWC
LastObject=ID_FILE_NEW_WINDOW

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=mfcie.cpp
ImplementationFile=mfcie.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308480

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_PRINT
Command3=ID_APP_EXIT
Command4=ID_VIEW_TOOLBAR
Command5=ID_VIEW_STATUS_BAR
Command6=ID_VIEW_FONTS_LARGEST
Command7=ID_VIEW_FONTS_LARGE
Command8=ID_VIEW_FONTS_MEDIUM
Command9=ID_VIEW_FONTS_SMALL
Command10=ID_VIEW_FONTS_SMALLEST
Command11=ID_VIEW_STOP
Command12=ID_VIEW_REFRESH
Command13=ID_GO_BACK
Command14=ID_GO_FORWARD
Command15=ID_GO_START_PAGE
Command16=ID_GO_SEARCH_THE_WEB
Command17=ID_HELP_WEB_TUTORIAL
Command18=ID_HELP_MICROSOFT_ON_THE_WEB_FREE_STUFF
Command19=ID_HELP_MICROSOFT_ON_THE_WEB_GET_FASTER_INTERNET_ACCESS
Command20=ID_HELP_MICROSOFT_ON_THE_WEB_FREQUENTLY_ASKED_QUESTIONS
Command21=ID_HELP_MICROSOFT_ON_THE_WEB_INTERNET_START_PAGE
Command22=ID_HELP_MICROSOFT_ON_THE_WEB_SEND_FEEDBACK
Command23=ID_HELP_MICROSOFT_ON_THE_WEB_BEST_OF_THE_WEB
Command24=ID_HELP_MICROSOFT_ON_THE_WEB_SEARCH_THE_WEB
Command25=ID_HELP_MICROSOFT_ON_THE_WEB_MICROSOFT_HOME_PAGE
Command26=ID_HELP_ONLINE_SUPPORT
Command27=ID_APP_ABOUT
CommandCount=27

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_PRINT
Command3=ID_VIEW_STOP
Command4=ID_VIEW_REFRESH
Command5=ID_GO_BACK
Command6=ID_GO_FORWARD
CommandCount=6

[MNU:IDR_FONT_POPUP]
Type=1
Command1=ID_VIEW_FONTS_LARGEST
Command2=ID_VIEW_FONTS_LARGE
Command3=ID_VIEW_FONTS_MEDIUM
Command4=ID_VIEW_FONTS_SMALL
Command5=ID_VIEW_FONTS_SMALLEST
CommandCount=5

[MNU:IDR_FAVORITES_POPUP]
Type=1
Command1=ID_BOGUS
CommandCount=1

