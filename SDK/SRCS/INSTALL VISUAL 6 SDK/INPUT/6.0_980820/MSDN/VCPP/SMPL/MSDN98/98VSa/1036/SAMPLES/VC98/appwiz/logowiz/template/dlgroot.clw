; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=$$DLG_CLASS$$
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "$$root$$.h"
$$IF(AUTOMATION)
ODLFile=$$root$$.odl
$$ENDIF
$$IF(PRESS_ME_DIALOG)
NewFileInclude3=#include "pressdlg.h"
$$ENDIF	//PRESS_ME_DIALOG

ClassCount=5
Class1=$$APP_CLASS$$
Class2=$$DLG_CLASS$$
$$IF(ABOUT)
Class3=CAboutDlg
$$ENDIF //ABOUT
$$IF(AUTOMATION)
Class4=$$DLGAUTOPROXY_CLASS$$
$$ENDIF //AUTOMATION
$$IF(PRESS_ME_DIALOG)
Class5=CPressMeDlg
$$ENDIF	//PRESS_ME_DIALOG

ResourceCount=3
$$IF(ABOUT)
Resource1=IDD_ABOUTBOX
$$ENDIF //ABOUT
Resource2=IDR_MAINFRAME
Resource3=IDD_$$SAFE_ROOT$$_DIALOG

[CLS:$$APP_CLASS$$]
Type=0
HeaderFile=$$root$$.h
ImplementationFile=$$root$$.cpp
Filter=N

[CLS:$$DLG_CLASS$$]
Type=0
HeaderFile=$$dlg_hfile$$.h
ImplementationFile=$$dlg_ifile$$.cpp
Filter=D

$$IF(ABOUT)
[CLS:CAboutDlg]
Type=0
HeaderFile=$$dlg_hfile$$.h
ImplementationFile=$$dlg_ifile$$.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg
$$ENDIF //ABOUT
$$IF(AUTOMATION)

[CLS:$$DLGAUTOPROXY_CLASS$$]
Type=0
HeaderFile=$$dlgautoproxy_hfile$$.h
ImplementationFile=$$dlgautoproxy_ifile$$.cpp
BaseClass=$$DLGAUTOPROXY_BASE_CLASS$$
Filter=N
$$ENDIF //AUTOMATION
$$IF(PRESS_ME_DIALOG)

[CLS:CPressMeDlg]
Type=0
HeaderFile=pressdlg.h
ImplementationFile=pressdlg.cpp
Filter=D

[DLG:IDD_PRESS_ME]
Type=1
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Class=CPressMeDlg
$$ENDIF	//PRESS_ME_DIALOG

[DLG:IDD_$$SAFE_ROOT$$_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=$$DLG_CLASS$$
