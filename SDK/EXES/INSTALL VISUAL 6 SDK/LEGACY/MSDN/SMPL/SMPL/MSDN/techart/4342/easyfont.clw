; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEasyFontApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "EasyFont.h"
LastPage=0

ClassCount=6
Class1=CEasyFontApp
Class2=CEasyFontDoc
Class3=CSceneView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDD_FONTPARAMDLG
Class5=CAboutDlg
Class6=CFontParamDlg
Resource3=IDR_MAINFRAME

[CLS:CEasyFontApp]
Type=0
HeaderFile=EasyFont.h
ImplementationFile=EasyFont.cpp
Filter=N
VirtualFilter=AC
LastObject=CEasyFontApp

[CLS:CEasyFontDoc]
Type=0
HeaderFile=EasyFdoc.h
ImplementationFile=EasyFdoc.cpp
Filter=N

[CLS:CSceneView]
Type=0
HeaderFile=SceneVw.h
ImplementationFile=SceneVw.cpp
Filter=C
LastObject=ID_ROTATE_STOP
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=EasyFont.cpp
ImplementationFile=EasyFont.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=ID_ROTATE_START
Command3=ID_ROTATE_STOP
Command4=ID_OPTIONS_CHANGE
Command5=ID_VIEW_STATUS_BAR
Command6=ID_APP_ABOUT
CommandCount=6

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
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

[DLG:IDD_FONTPARAMDLG]
Type=1
Class=CFontParamDlg
ControlCount=13
Control1=IDC_EDIT_STRING,edit,1350631552
Control2=IDC_EDIT_EXTRUSION,edit,1350631552
Control3=IDC_EDIT_DEVIATION,edit,1350631552
Control4=IDC_RADIO_POLYGONS,button,1342373897
Control5=IDC_RADIO_LINES,button,1342242825
Control6=IDC_BTN_FONT,button,1342373888
Control7=IDC_BTN_DEFAULT,button,1342242816
Control8=IDOK,button,1342242817
Control9=IDCANCEL,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,button,1342177287

[CLS:CFontParamDlg]
Type=0
HeaderFile=fontparamdlg.h
ImplementationFile=fontparamdlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_BTN_DEFAULT

