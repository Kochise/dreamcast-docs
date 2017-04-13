; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CCmdTarget
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "thrddemo.h"
LastPage=0

ClassCount=9
Class1=CThreadApp
Class2=CThreadDoc
Class3=CThreadView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CBallThread
Class7=CGDIThread
Class8=CRectThread
Class9=CLineThread
Resource2=IDD_ABOUTBOX

[CLS:CThreadApp]
Type=0
HeaderFile=mtgdi.h
ImplementationFile=mtgdi.cpp

[CLS:CThreadDoc]
Type=0
HeaderFile=mtgdidoc.h
ImplementationFile=mtgdidoc.cpp

[CLS:CThreadView]
Type=0
HeaderFile=mtgdivw.h
ImplementationFile=mtgdivw.cpp

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=mtgdi.h
ImplementationFile=mtgdi.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_THREAD_NEWBALL
Command2=ID_THREAD_10NEWBALLS
Command3=ID_THREAD_25NEWBALLS
Command4=ID_THREAD_NEWRECTANGLE
Command5=ID_THREAD_10NEWRECTANGLES
Command6=ID_THREAD_25NEWRECTANGLES
Command7=ID_THREAD_NEWLINE
Command8=ID_THREAD_10NEWLINES
Command9=ID_THREAD_25NEWLINES
Command10=ID_THREAD_KILLTHREADS
Command11=ID_THREAD_KILLTHREADSSLOW
Command12=ID_APP_EXIT
Command13=ID_APP_ABOUT
CommandCount=13

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_THREAD_KILLTHREADS
Command2=ID_APP_ABOUT
Command3=ID_THREAD_25NEWBALLS
Command4=ID_THREAD_25NEWRECTANGLES
Command5=ID_THREAD_25NEWLINES
Command6=ID_THREAD_NEWBALL
Command7=ID_THREAD_NEWRECTANGLE
Command8=ID_THREAD_NEWLINE
Command9=ID_THREAD_10NEWBALLS
Command10=ID_THREAD_10NEWRECTANGLES
Command11=ID_THREAD_10NEWLINES
CommandCount=11

[CLS:CBallThread]
Type=0
HeaderFile=threads.h
ImplementationFile=threads.cpp

[CLS:CGDIThread]
Type=0
HeaderFile=threads.h
ImplementationFile=threads.cpp
Filter=N

[CLS:CRectThread]
Type=0
HeaderFile=threads.h
ImplementationFile=threads.cpp
Filter=N

[CLS:CLineThread]
Type=0
HeaderFile=threads.h
ImplementationFile=threads.cpp
Filter=N

