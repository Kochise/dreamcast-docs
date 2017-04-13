; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChkBookApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chkbook.h"

ClassCount=5
Class1=CChkBookDoc
Class2=CCheckView
Class3=CChkBookApp
Class4=CMainFrame
Class5=CRowView

ResourceCount=5
Resource1=IDR_CHECKFRAME
Resource2=IDR_BOOKFRAME
Resource3=IDR_MAINFRAME
Resource4=IDD_ABOUTBOX
Resource5=IDD_CHECK

; ClassWizard DDX information for custom DDX functions
ExtraDDXCount=1
ExtraDDX1=E;;Cents;DWORD;0;DollarsCents;(100*dollars)+cents

[CLS:CChkBookDoc]
Type=0
HeaderFile=checkdoc.h
ImplementationFile=checkdoc.cpp

[CLS:CCheckView]
Type=0
HeaderFile=checkvw.h
ImplementationFile=checkvw.cpp

[CLS:CChkBookApp]
Type=0
HeaderFile=chkbook.h
ImplementationFile=chkbook.cpp
LastObject=ID_APP_EXIT

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp

[CLS:CRowView]
Type=0
HeaderFile=rowview.h
ImplementationFile=rowview.cpp

[MNU:IDR_MAINFRAME]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8
Class=?

[MNU:IDR_BOOKFRAME]
Type=1
Command1=ID_FILE_PRINT
Command2=ID_FILE_PRINT_PREVIEW
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_CLOSE
Command5=ID_APP_EXIT
Command6=ID_EDIT_NEW_CHECK
Command7=ID_NEXT_CHECK
Command8=ID_PREV_CHECK
Command9=ID_VIEW_CHECK
Command10=ID_VIEW_BOOK
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_WINDOW_CASCADE
Command14=ID_WINDOW_TILE_HORZ
Command15=ID_WINDOW_ARRANGE
Command16=ID_APP_ABOUT
CommandCount=16
Class=?

[MNU:IDR_CHECKFRAME]
Type=1
Command1=ID_FILE_CLOSE
Command2=ID_APP_EXIT
Command3=ID_EDIT_NEW_CHECK
Command4=ID_EDIT_COMMIT_CHECK
Command5=ID_NEXT_CHECK
Command6=ID_PREV_CHECK
Command7=ID_VIEW_CHECK
Command8=ID_VIEW_BOOK
Command9=ID_VIEW_TOOLBAR
Command10=ID_VIEW_STATUS_BAR
Command11=ID_WINDOW_CASCADE
Command12=ID_WINDOW_TILE_HORZ
Command13=ID_WINDOW_ARRANGE
Command14=ID_APP_ABOUT
CommandCount=14
Class=?

[ACL:IDR_MAINFRAME]
Type=1
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
CommandCount=14
Class=?

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=?

[DLG:IDD_CHECK]
Type=1
ControlCount=11
Control1=IDC_DATE,edit,1350631552
Control2=IDC_PAYTO,edit,1350631552
Control3=IDC_AMOUNTNUM,edit,1350631552
Control4=IDC_MEMO,edit,1350631552
Control5=IDC_STATIC,static,1342308354
Control6=IDC_STATIC,static,1342308354
Control7=IDC_STATIC,static,1342308352
Control8=IDC_AMOUNTTEXT,static,1342308354
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308354
Control11=IDC_CHECKNO,static,1342308352
Class=CCheckView

