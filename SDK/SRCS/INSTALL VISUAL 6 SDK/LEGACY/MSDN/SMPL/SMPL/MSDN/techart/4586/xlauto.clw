; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChartDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "XlAuto.h"
ODLFile=XlAuto.odl
LastPage=0

ClassCount=6
Class1=CXlAutoApp
Class2=CXlAutoDoc
Class3=CXlAutoView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDR_CNTR_INPLACE
Resource4=IDD_CHARTDLG
Class6=CChartDlg

[CLS:CXlAutoApp]
Type=0
HeaderFile=XlAuto.h
ImplementationFile=XlAuto.cpp
Filter=N

[CLS:CXlAutoDoc]
Type=0
HeaderFile=XlAutdoc.h
ImplementationFile=XlAutdoc.cpp
Filter=N

[CLS:CXlAutoView]
Type=0
HeaderFile=XlAutvw.h
ImplementationFile=XlAutvw.cpp
Filter=C
VirtualFilter=VWC
LastObject=ID_ADDSTUFF_ADDDATA

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T
LastObject=ID_OLE_INSERT_NEW



[CLS:CAboutDlg]
Type=0
HeaderFile=XlAuto.cpp
ImplementationFile=XlAuto.cpp
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
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_PASTE_LINK
Command15=ID_OLE_INSERT_NEW
Command16=ID_OLE_EDIT_LINKS
Command17=ID_OLE_VERB_FIRST
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_APP_ABOUT
CommandCount=20

[MNU:IDR_CNTR_INPLACE]
Type=1
Class=CXlAutoView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_ADDSTUFF_ADDDATA
Command11=ID_ADDSTUFF_ADDCHART
CommandCount=11

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CANCEL_EDIT_CNTR
CommandCount=15

[ACL:IDR_CNTR_INPLACE]
Type=1
Class=CXlAutoView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_CANCEL_EDIT_CNTR
CommandCount=7

[DLG:IDD_CHARTDLG]
Type=1
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO1,combobox,1344340226
Class=CChartDlg

[CLS:CChartDlg]
Type=0
HeaderFile=chartdlg.h
ImplementationFile=chartdlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDOK

