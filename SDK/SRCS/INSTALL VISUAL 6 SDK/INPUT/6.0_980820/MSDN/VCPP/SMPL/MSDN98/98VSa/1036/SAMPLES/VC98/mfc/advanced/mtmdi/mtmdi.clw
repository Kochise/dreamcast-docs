; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBounceMDIChildWnd
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mtmdi.h"
VbxHeaderFile=mtmdi.h
VbxImplementationFile=mtmdi.cpp
LastPage=0

ClassCount=6
Class1=CBounceMDIChildWnd
Class2=CBounceWnd
Class3=CHelloWnd
Class4=CMainFrame
Class5=CMdiApp
Class6=CBounceThread

ResourceCount=4
Resource1=IDR_HELLO
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDR_BOUNCE

[CLS:CBounceMDIChildWnd]
Type=0
HeaderFile=bounce.h
ImplementationFile=bounce.cpp
LastObject=CBounceMDIChildWnd
Filter=W
VirtualFilter=mfWC

[CLS:CBounceWnd]
Type=0
HeaderFile=bounce.h
ImplementationFile=bounce.cpp
LastObject=CBounceWnd
Filter=W
VirtualFilter=WC

[CLS:CHelloWnd]
Type=0
HeaderFile=hello.h
ImplementationFile=hello.cpp

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
LastObject=CMainFrame
Filter=T
VirtualFilter=fWC

[CLS:CMdiApp]
Type=0
HeaderFile=mdi.h
ImplementationFile=mdi.cpp

[CLS:CBounceThread]
Type=0
HeaderFile=mtbounce.h
ImplementationFile=mtbounce.cpp
LastObject=CBounceThread

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_ABOUT
CommandCount=1

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342308353
Control2=IDC_STATIC,static,1342308353
Control3=IDC_STATIC,static,1342308353
Control4=IDC_STATIC,static,1342308353
Control5=IDC_STATIC,static,1342177283
Control6=IDOK,button,1342373889

[MNU:IDR_BOUNCE]
Type=1
Class=?
Command1=IDM_BOUNCE
Command2=IDM_HELLO
Command3=ID_APP_EXIT
Command4=IDM_BLACK
Command5=IDM_RED
Command6=IDM_GREEN
Command7=IDM_BLUE
Command8=IDM_WHITE
Command9=IDM_CUSTOM
Command10=IDM_SLOW
Command11=IDM_FAST
Command12=ID_WINDOW_CASCADE
Command13=ID_WINDOW_TILE_VERT
Command14=ID_WINDOW_ARRANGE
Command15=ID_APP_ABOUT
CommandCount=15

[MNU:IDR_HELLO]
Type=1
Class=?
Command1=IDM_BOUNCE
Command2=IDM_HELLO
Command3=ID_APP_EXIT
Command4=IDM_BLACK
Command5=IDM_RED
Command6=IDM_GREEN
Command7=IDM_BLUE
Command8=IDM_WHITE
Command9=IDM_CUSTOM
Command10=ID_WINDOW_CASCADE
Command11=ID_WINDOW_TILE_VERT
Command12=ID_WINDOW_ARRANGE
Command13=ID_APP_ABOUT
CommandCount=13

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDM_BOUNCE
Command2=IDM_HELLO
Command3=ID_APP_EXIT
Command4=ID_APP_ABOUT
CommandCount=4

