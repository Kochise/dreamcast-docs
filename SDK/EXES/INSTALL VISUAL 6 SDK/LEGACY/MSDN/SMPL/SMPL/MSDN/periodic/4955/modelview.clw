; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMatrixDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Modelview.h"
LastPage=0

ClassCount=6
Class1=CModelviewApp
Class2=CModelviewDoc
Class3=CModelviewView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_DIALOG1
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CMatrixDialog
Resource3=IDD_ABOUTBOX

[CLS:CModelviewApp]
Type=0
HeaderFile=Modelview.h
ImplementationFile=Modelview.cpp
Filter=N

[CLS:CModelviewDoc]
Type=0
HeaderFile=ModelviewDoc.h
ImplementationFile=ModelviewDoc.cpp
Filter=N

[CLS:CModelviewView]
Type=0
HeaderFile=ModelviewView.h
ImplementationFile=ModelviewView.cpp
Filter=C
BaseClass=COpenGLView
VirtualFilter=VWC
LastObject=CModelviewView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=Modelview.cpp
ImplementationFile=Modelview.cpp
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
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_APP_ABOUT
CommandCount=11

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

[DLG:IDD_DIALOG1]
Type=1
Class=CMatrixDialog
ControlCount=35
Control1=IDC_EDIT11,edit,1350631552
Control2=IDC_EDIT12,edit,1350631552
Control3=IDC_EDIT13,edit,1350631552
Control4=IDC_EDIT14,edit,1350631552
Control5=IDC_EDIT21,edit,1350631552
Control6=IDC_EDIT22,edit,1350631552
Control7=IDC_EDIT23,edit,1350631552
Control8=IDC_EDIT24,edit,1350631552
Control9=IDC_EDIT31,edit,1350631552
Control10=IDC_EDIT32,edit,1350631552
Control11=IDC_EDIT33,edit,1350631552
Control12=IDC_EDIT34,edit,1350631552
Control13=IDC_EDIT41,edit,1350631552
Control14=IDC_EDIT42,edit,1350631552
Control15=IDC_EDIT43,edit,1350631552
Control16=IDC_EDIT44,edit,1350631552
Control17=ID_B_RESET_APPLY,button,1342242816
Control18=ID_B_APPEND_APPLY,button,1342242816
Control19=ID_B_IDENTITY,button,1342242817
Control20=IDC_B_LETTER,button,1342308361
Control21=IDC_B_TEAPOT,button,1342177289
Control22=IDC_STATIC,button,1342308359
Control23=IDC_STATIC,static,1342308353
Control24=IDC_STATIC,static,1342308353
Control25=IDC_STATIC,static,1342308353
Control26=IDC_STATIC,static,1342308353
Control27=IDC_STATIC,static,1342308353
Control28=IDC_STATIC,static,1342308353
Control29=IDC_STATIC,static,1342308353
Control30=IDC_STATIC,static,1342308353
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352

[CLS:CMatrixDialog]
Type=0
HeaderFile=MatrixDialog.h
ImplementationFile=MatrixDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CMatrixDialog

